#include "main.h"

// structs
volatile ADC_meas MeasDataTx;
volatile PIDreg PID;

//============================== RTOS OBJECTS =================================//
volatile TickType_t T = 0;									// Queue send GLOBAL timeout

volatile QueueHandle_t FPsetCounts_q; 		  // front panel sets measurements queue 
volatile QueueHandle_t FBvoltage_q; 				// HV feedback measurements
volatile QueueHandle_t LoadCurrent_q; 		  // HV load current  	
volatile QueueHandle_t DistVset_q; 		  		// Modbus sets From User   
volatile QueueHandle_t OvercurrBit_q; 		  // overcurrent status to modbus
volatile QueueHandle_t DistHVenStatus_q; 		// HV state queue 
volatile QueueHandle_t DistHVenStatus_q; 		// HV state queue 

volatile TaskHandle_t TrigTaskHandle;

SemaphoreHandle_t ExtTrigSemph;

//=============================== USER VARS ==================================//

volatile uint16_t V2set = 0;		
volatile uint16_t DAC2set = 0;	
volatile uint16_t VsetCnts = 0;
volatile uint16_t VsetCntsDist = 0;
volatile uint16_t RampCounter = 0;

volatile uint16_t Imeas_old = 0;						// temp I meas buffer

volatile uint16_t DistHVen = 0;

volatile BaseType_t ExtTrigInt = pdFALSE;
volatile BaseType_t PIDregInt  = pdFALSE;

void PIDregInit(void)
{
	PID.curr_error = 0;
	PID.prev_error = 0;
	PID.result = 0;
	
	DAC2set = 0;
	
	PID.kP = 55.0;
	PID.kI = 0.0005;
	PID.kD = 0;
}

//=============================== IRQs ======================================//
	
__irq void Timer1_IRQHandler(void) 
//функция обработки прерывания irq Timer 1 - стробы запуска 
{ 
	 ExtTrigInt = pdFALSE; 
	
	 xSemaphoreGiveFromISR(ExtTrigSemph,NULL);
	 
	 MDR_TIMER1->CNT = 0;                     // установка знач. счетчика на 0
   MDR_TIMER1->STATUS = 0x0000;             // сброс статуса прерывания
   NVIC_ClearPendingIRQ(Timer1_IRQn);       // обязательно! 
	
	 if(ExtTrigInt == pdTRUE)
		portEND_SWITCHING_ISR(ExtTrigInt);

}
// IRQ, ADC measurements & PID - 200 us period
__irq void Timer2_IRQHandler(void)
{
	  //------------ meas & send to modbus ------------//
	
	  // TODO в отдельное прерывание измерения и отсылку
	
	  MCU_ADC_init(2);           		// ADC ch 2 - front panel sets 
	  MeasDataTx.VsetCounts = (uint16_t)MCU_ADC_read();
 
	  MCU_ADC_init(4);           		// ADC ch 4 - load current
	  MeasDataTx.ImeasCounts = (uint16_t)MCU_ADC_read();

	  MCU_ADC_init(5);           		// ADC ch 5 - HV feedback voltage
	  MeasDataTx.VmeasCounts = (uint16_t)MCU_ADC_read();
    
	  // sending new measurements to queues
		if(uxQueueMessagesWaitingFromISR(FPsetCounts_q) == 0) // V set
			xQueueSendFromISR(FPsetCounts_q, (void*) &MeasDataTx.VsetCounts,T);   
				
		if(uxQueueMessagesWaitingFromISR(LoadCurrent_q) == 0)	// I load			
			xQueueSendFromISR(LoadCurrent_q, (void*) &MeasDataTx.ImeasCounts,T);

		if(uxQueueMessagesWaitingFromISR(FBvoltage_q) == 0)		// V meas
			xQueueSendFromISR(FBvoltage_q, (void*) &MeasDataTx.VmeasCounts,T);   
		
		//------------ VOLTAGE SETTINGS ------------//
		
		if(uxQueueMessagesWaitingFromISR(DistHVenStatus_q))			// dist HV set status
			xQueueReceiveFromISR(DistHVenStatus_q, (void*) &DistHVen,T);  
				
		if(HV_SWITCH_ST == ON && DistHVen == ON)
		{
			if(REMOTE_SWITCH_ST == ON)			// remote control
			{
				if(uxQueueMessagesWaitingFromISR(DistVset_q))
				{
					xQueuePeekFromISR(DistVset_q, &VsetCntsDist);
					RampCounter = 0;
					PID.I = 0;	
				}
				
				VsetCnts = VsetCntsDist;
			}
			
			else													// front panel control
			{
								
				if(VsetCnts != MeasDataTx.VsetCounts)
				{
					VsetCnts = MeasDataTx.VsetCounts;
					RampCounter = 0;
				}
			}
			
			//------------ VOLTAGE SET RAMP ------------//
			
			if(VsetCnts > DAC2set)	  		// RAMP - increase voltage, 1 kV/s
				{
					RampCounter++;					  // 5 RampCounter ticks = 1 ms 
					if(RampCounter > 4)
					{
						DAC2set++;
						RampCounter = 0;
					}
				}
															
				if(VsetCnts < DAC2set)		// RAMP - decrease voltage, 1 kV/s
				{
					RampCounter++;
					if(RampCounter > 4) 		// 5 RampCounter ticks = 1 ms 
					{
						DAC2set--; 
						RampCounter = 0;
					}
				}
				
			  //------------------ PID -------------------//
					
				PID.curr_error = (float)DAC2set - (float)MeasDataTx.VmeasCounts;       // вычисление ошибки
				
				PID.P = (PID.kP * PID.curr_error);              		 // П-звено регулятора
				PID.I = (PID.I + PID.curr_error * PID.kI);     		   // I-звено регулятора
				PID.D = ((PID.prev_error - PID.curr_error)*PID.kD);  // I-звено регулятора
				PID.prev_error = PID.curr_error;
				
				if(PID.I > 5080)  PID.I = 5080;                      // ограничение интегрального звена регулятора
				if(PID.I < -5080) PID.I = -5080;
				
				PID.result = PID.P + PID.I + PID.D;      						 // суммирование составляющих ПИД-регулятора
					
				if(PID.result > 5080) PID.result = 5080;             // ограничение выходного кода ЦАП
				if(PID.result < 0) PID.result = 0; 
					
				MDR_DAC->DAC2_DATA = (uint32_t)(PID.result*DAC_lsb); // PID reg correction
				
				//------------------ PID -------------------//
		
		} 	// HV_SWITCH_ST
		
		 if(HV_SWITCH_ST == OFF || DistHVen == OFF)						 	 // HV_SWITCH_OFF or HV disabed from modbus
		 {  // clear PID regulator
		 	DAC2set = 0;
			PID.P = 0;
			PID.I = 0;
			PID.D = 0;
		 }
		 
		//PIDregInt = pdFALSE; 
	
	 // if(PIDregInt == pdTRUE)
		//	portEND_SWITCHING_ISR(PIDregInt);

	  MDR_TIMER2->CNT = 0;                     // установка знач. счетчика на 0
    MDR_TIMER2->STATUS = 0x0000;             // сброс статуса прерывания
    NVIC_ClearPendingIRQ(Timer2_IRQn);       // обязательно!
}


//===============================================================//
// USER TASKS

void task_OvercurrentSM(void *pvParameters)	//  overcurrent detect state machine
{
	ADC_meas MeasDataRx_OC;
	
	uint16_t I_meas_curr = 0;
	
  uint8_t overcurrent_bit = 0;      // статус-бит перегрузки по току: 0 - ок, 1 - сработала защита по току
  uint8_t overcurrent_count = 0;    // число срабатыаний перегрузки по току
  uint8_t overcurrent_lim = 20;     // порог откл. HV при перегрузке по току
  uint8_t overcurr_state = 0;              
	
  uint16_t HV_sw_state = 0;         // статус-бит тумблера высокого: 0 - выкл, 1 - вкл
  uint16_t HV_sw_state_prev = 0;    // статус-бит тумблера высокого с предыдущей итерации осн. цикла
	
	uint16_t V_curr = 0;
  uint16_t V_prev = 0;
	uint16_t V_set = 0;
	
  int16_t meas_delta = 0;
  int16_t set_delta = 0;
		
	MeasDataRx_OC.ImeasCounts = 0;		// clear I var
	MeasDataRx_OC.VmeasCounts = 0;		// clear V var
	
	TickType_t OCtaskPerod = 50;			// this task period var
	
		
	HV_SUPPLY_ON;										  // HV supply EN
	
	while(1)
	{
    //------------ measured V and I reading ------------//
		
		// get V counts
	  if(uxQueueMessagesWaiting(FBvoltage_q) > 0)
		{
			V_prev = V_curr;	// update prev measurements
			
			xQueueReceive(FBvoltage_q, &MeasDataRx_OC.VmeasCounts,T);
			V_curr = (uint16_t)((float)MeasDataRx_OC.VmeasCounts * DAC_lsb); 	// measured V counts receive  
		}
		
		// get I counts
		if(uxQueueMessagesWaiting(LoadCurrent_q) > 0)
		{
			xQueueReceive(LoadCurrent_q, &MeasDataRx_OC.ImeasCounts,5);				// measured I counts receive
			I_meas_curr = CalcCurrent(MeasDataRx_OC.VmeasCounts,MeasDataRx_OC.ImeasCounts);
		}
		
		// get V sets
		if(uxQueueMessagesWaiting(DistVset_q) > 0)
		{
			xQueueReceive(DistVset_q, &MeasDataRx_OC.VsetCounts,T);						// user V set receive 
			V_set = (uint16_t)((float)MeasDataRx_OC.VsetCounts * DAC_lsb); 		// counts to V convert  
		}	

		set_delta	 = (int16_t)V_set - (int16_t)V_curr;
			if(set_delta < 0) set_delta *= -1;
		meas_delta = (int16_t)V_curr - (int16_t)V_prev;		
			if(meas_delta < 0) meas_delta *= -1;
		//------------ overcurrent protect state machine ------------//
		
		switch (overcurr_state)
    {
			//=====
			case 0:	// IDLE
				if(I_meas_curr > MAX_CURRENT) 
					overcurr_state = 1;
			break;
		  //=====
			case 1:	// delta check	
				// if voltage is rising - it a cap. load - clear overcurrent state
			  if( (set_delta > 5) && (meas_delta > 0) )
					overcurr_state = 0;
				else
					overcurr_state = 2;	// it is not cap. load - its short 
				
				break;
			//=====
			case 2: // final OC check
				if(overcurrent_count > overcurrent_lim)
        {
          overcurrent_bit = 1;
          HV_SUPPLY_OFF;             // выкл. высокое
					OverCurrLED_ON;						 // OC LED EN
					PIDregInit();
					// overcurrent status send
					if(uxQueueMessagesWaiting(OvercurrBit_q) == 0)
              xQueueReceive(OvercurrBit_q, &overcurrent_bit,T);
					
					overcurr_state = 0;
        }
        else 
					overcurrent_count++;       // инкремент попыток подачи высокого в режиме перегрузки по току
			break;
			//=====
				default: overcurr_state = 0;
		}
		
		 HV_sw_state_prev = HV_sw_state; // save HV switch prev state
		 HV_sw_state = HV_SWITCH_ST;		 // save HV switch current state
			
		 if(HV_sw_state == OFF || DistHVen == OFF)	// HV_SWITCH_OFF or HV disabed from modbus
		 {
			overcurrent_count = 0;		
			overcurrent_bit = 0;
		  OverCurrLED_OFF;	
			 
			// overcurrent status send
			if(uxQueueMessagesWaiting(OvercurrBit_q) == 0)
				xQueueReceive(OvercurrBit_q, &overcurrent_bit,T);			 
		 }
		 
		 // HV swicth ON
		 if(HV_sw_state_prev == OFF && HV_sw_state == ON)
			HV_SUPPLY_ON;

//		 holding_reg_write(15,overcurrent_count);
//		 holding_reg_write(16,overcurr_state);
//		 holding_reg_write(17,set_delta);
//		 holding_reg_write(18,meas_delta);
// 
		vTaskDelay(OCtaskPerod);
		TRIG_LED_OFF;
	}
}



void task_ModbusSM(void *pvParameters)		  // Modbus RTU over TCP state machine
{

  uint16_t wr_reg_addr = 0;       // modbus write reg addr
  uint16_t RegisterValue = 0;     // modbus write reg velue
	
	ADC_meas MeasDataRx;
	uint32_t Vfb_meas   = 0;
	uint32_t Vset_meas  = 0;
	uint16_t Vset_old   = 0;  			// temp Vset buf

	uint16_t V2setCounts = 0;
	uint16_t OvercurBit = 0;
	uint16_t HVsupplyState = ON;		// HV ins EN during power ON 

	// send the HVsupplyState init value to the queue to enable HV
	xQueueSend(DistHVenStatus_q, (void*) & HVsupplyState,T);	
	
	while(1)
    {   
     // если запрос был в переменной modbus_request сохранен его код 
     switch(modbus_get_poll())
     {
//////////////////////////// ЧТЕНИЕ HOLDING ////////////////////////// 
         case MODBUS_RHR_CMD:
					 
           Modbus_LED_ON;
				 
           // get measured data if queues are not empty 
           if(uxQueueMessagesWaiting(FPsetCounts_q) > 0)
              xQueueReceive(FPsetCounts_q, &MeasDataRx.VsetCounts,T);
					 
					 if(uxQueueMessagesWaiting(LoadCurrent_q) > 0)
              xQueuePeek(LoadCurrent_q, &MeasDataRx.ImeasCounts,T);
					            
					 if(uxQueueMessagesWaiting(FBvoltage_q) > 0)
              xQueuePeek(FBvoltage_q, &MeasDataRx.VmeasCounts,T);
					 
					 // overcurrent status
					 if(uxQueueMessagesWaiting(OvercurrBit_q) > 0)
              xQueueReceive(OvercurrBit_q, &OvercurBit,T);
					 
					 // 0.8056640625 = (ADC_Vref*1000)/4096 = DAC_lsb
					 
					 Vfb_meas   = (uint32_t)((float)MeasDataRx.VmeasCounts * DAC_lsb); 		 // HV feedback meas voltage
		  	   Vset_meas  = (uint32_t)((float)MeasDataRx.VsetCounts  * DAC_lsb);		 // front panel set voltage
					 
					 holding_reg_write(1,(uint16_t)(V2setCounts*DAC_lsb));
           holding_reg_write(2,(uint16_t)Vset_meas);
				   holding_reg_write(5,(uint16_t)Vfb_meas);
					 holding_reg_write(6,CalcCurrent(Vfb_meas, MeasDataRx.ImeasCounts));

					 holding_reg_write(9,HVsupplyState);
					 holding_reg_write(10,MAX_CURRENT);
					 holding_reg_write(11,HV_SWITCH_ST);
					 holding_reg_write(12,OvercurBit);					// 1 - overcurrent, 0 - normal work		
					 holding_reg_write(13,REMOTE_SWITCH_ST);		// 1 - remote, 0 - FP ctrl
           modbus_rhr_answer(); // modbus rhr cmd answer
           
           Modbus_LED_OFF; 		  // LED toggle
           
         break;
//////////////////////////// ЗАПИСЬ HOLDING ////////////////////////// 
          case MODBUS_WSR_CMD:  // запись holding регистров
           modbus_wsr_answer(); // ответ на запрос
          // заполнение переменных пользователя данными из Модбас регистров 
           
           wr_reg_addr = get_wr_reg_addr();    // get address
					 wr_reg_addr -= 1000;								 // избавляемся от смещения 
           RegisterValue = get_wr_reg_val();   // get the new value
           
           switch(wr_reg_addr)
           {
               //=====                     
               case 0: // set voltage
								if(RegisterValue <= 3200) 
								{
									V2setCounts = (uint16_t)((float)RegisterValue/DAC_lsb) + 1U; // 999 to 1000
									
									if(uxQueueMessagesWaiting(DistVset_q) > 0)
										xQueueReceive(DistVset_q, &Vset_old,T);					// delete prev Vset value
									
									xQueueSend(DistVset_q, (void*) &V2setCounts,T);	  // write the new sets to queue 
								}
               break;
							 //=====                     
               case 9: // HV enable
								 
								if(RegisterValue == ON || RegisterValue == OFF) 
								{
									PIDregInit();	
									
									if(RegisterValue == ON) 
										HV_SUPPLY_ON;
									if(RegisterValue == OFF) 
										HV_SUPPLY_OFF;
								
									HVsupplyState = RegisterValue; 
									xQueueSend(DistHVenStatus_q, (void*) & HVsupplyState,T);
								}
								break;
               //=====
                default: break;
           } 
          //eeprom_wr_regs(HOLD_REGS);
           
          break;
//////////////////////////// ЧТЕНИЕ INPUT ////////////////////////////
          case MODBUS_RIR_CMD:  // чтение input регистров
           
           //input_reg_write(0,FirmInfo.ver);
           //input_reg_write(1,FirmInfo.developer);
           input_reg_write(2,(unsigned int)get_modbus_id());
           
           modbus_rir_answer(); // ответ на запрос
          break;
          
       } // switch 
    } // while

} // end of task MODBUS


void task_OnExtTrig(void *pvParameters)			// ext trig event handler task
{
	
	while(1)
	{
    xSemaphoreTake(ExtTrigSemph,portMAX_DELAY); // wait for ext trig
		
		TRIG_LED_ON;                        	      // trig LED toggle
		vTaskDelay(50);
		TRIG_LED_OFF;
	}
}


//===============================================================//

int main()
{ 
	// queues
	FPsetCounts_q 	 = xQueueCreate(32, sizeof(uint32_t));
	LoadCurrent_q 	 = xQueueCreate(32, sizeof(uint32_t));
	FBvoltage_q   	 = xQueueCreate(32, sizeof(uint32_t));
  DistVset_q 			 = xQueueCreate(10, sizeof(uint16_t));
	OvercurrBit_q 	 = xQueueCreate(10, sizeof(uint16_t));
	DistHVenStatus_q = xQueueCreate(10, sizeof(uint16_t));
	
	// hardware init
	OSC_init();
	GPIO_init();
	T1_init();			// ext sync
	T2_init();			// PID regulator
	MCU_ADC_init(5);
	MCU_DAC2_init();
	
	// sys init
	PIDregInit();
	modbus_init();

	// tasks
	xTaskCreate(task_ModbusSM,"ModbusSM", configMINIMAL_STACK_SIZE * 4,NULL,2,NULL);
	xTaskCreate(task_OvercurrentSM,"OvercurrentSM",configMINIMAL_STACK_SIZE,NULL,1,NULL);
  xTaskCreate(task_OnExtTrig,"OnExtTrig",configMINIMAL_STACK_SIZE,NULL,1,&TrigTaskHandle);
	
	// semph
	ExtTrigSemph = xSemaphoreCreateCounting(100, 0);
	
	// interrupts
	NVIC_SetPriorityGrouping(4);
	NVIC_SetPriority(UART1_IRQn,  13);
	NVIC_SetPriority(Timer1_IRQn, 12);
	NVIC_SetPriority(Timer2_IRQn, 12);
	
	NVIC_EnableIRQ(Timer1_IRQn); // Разрешение прерывания для T1
	NVIC_EnableIRQ(Timer2_IRQn); // Разрешение прерывания для T2
	NVIC_EnableIRQ(UART1_IRQn);  // Разрешение прерывания для UART1
	__enable_irq();	      	     // Enable Interrupts global
	
	MDR_TIMER2->CNTRL |= 1;			 // V set PID-regulator timer start
	MDR_TIMER1->CNTRL |= 1;			 // ext trig timer start
	
	vTaskStartScheduler(); 			 // Запуск планировщика задач
}
//================================================================//