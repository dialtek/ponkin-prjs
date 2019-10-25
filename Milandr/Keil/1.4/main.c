#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "main.h"
#include "mdr_modbus.h"
#include "mdr_adc.h"
#include <MDR32F9Qx_timer.h>
#include <MDR32F9Qx_port.h>

PORT_InitTypeDef PortInitStructure;

volatile ADC_meas MeasDataTx;
volatile PIDreg PID;

/*============================ RTOS OBJECTS ================================= */
volatile TickType_t T = 0;									// Queue send GLOBAL timeout

volatile QueueHandle_t FPsetCounts_q; 		  // front panel sets measurements queue 
volatile QueueHandle_t FBvoltage_q; 				// HV feedback measurements
volatile QueueHandle_t LoadCurrent_q; 		  // HV load current 
volatile QueueHandle_t DistVsetRamp_q; 		  // Modbus sets Ramp  	
volatile QueueHandle_t DistVsetNum_q; 		  // Modbus sets From User   	
volatile QueueHandle_t VzeroLvl_q; 		  	  // V zero level
	
volatile uint16_t V2set = 0;		
volatile uint32_t DAC2set = 0;	
	
TaskHandle_t ModbusTaskHandle;
//===============================================================//
void PIDregInit(void)
{
	PID.curr_error = 0;
	PID.prev_error = 0;
	PID.result = 0;
	
	PID.kP = 2.5;
	PID.kI = 0.04;
	PID.kD = 0.25;
}
void OSC_init(void)
{

#define	_HSEBYP	0   // 0 - ����� �����������, 1 - ����� �������� ����������
#define	_HSEON  1	  // 0 - ��������, 1 - �������

//---CLK-----------------------------------------------------------------------------------------------------

  MDR_RST_CLK->HS_CONTROL = (_HSEBYP<<1) + _HSEON; 
  while ((MDR_RST_CLK->CLOCK_STATUS & 0x04) != 0x04);     // ���� ���� HSE ������ � ������� �����
  MDR_RST_CLK->PLL_CONTROL = ((1 << 2) | (7 << 8)); 	  // ���. PLL | ����. ��������� = 2

  while((MDR_RST_CLK->CLOCK_STATUS & 0x02) != 0x02);      // ���� ����� PLL ������ � ���. �����

  MDR_RST_CLK->CPU_CLOCK  = (2                           // �������� ��� CPU_C1 - HSE
						   |(1 << 2)                      // �������� ��� CPU_C2 - PLLCPUo 
						   |(1 << 4)                      // ������������ ��� CPU_C3 - CPU_C2
						   |(1 << 8));                    // �������� ��� HCLK
  MDR_RST_CLK->PER_CLOCK = 0xFFFFFFFF;        // ���. ������������ ���� ���������
  // HCLK = 80 ���
}
   







void GPIO_init (void)
{  
  
  MDR_PORTA->OE      = 0xFFFD;          // PA1 - ���� �������������
  MDR_PORTA->FUNC    = (2<<2);          // ������� - ����, ��� ��5 �������������� ������� 
  MDR_PORTA->ANALOG  = 0xFFFF;          // ����� ����� - ��������
  MDR_PORTA->PWR     = 0xFFFFFFFF;      // ����������� ������� ����� ( ������� 10 ��)
  //---------------------------------------------------------------------------//
  // ������������� ��������� ��� ��������� �����
	PORT_InitTypeDef PORTB_config_struct;
	PORT_StructInit(&PORTB_config_struct);
	
	// ��������� �����
	PORTB_config_struct.PORT_Pin = PORT_Pin_9  & (~JTAG_PINS(MDR_PORTB));  // ����� �� ����������� JTAG,
																																				 // ��������� �� ������������� JTAG-������ ����
	PORTB_config_struct.PORT_OE = PORT_OE_OUT;
	PORTB_config_struct.PORT_MODE = PORT_MODE_DIGITAL;
	PORTB_config_struct.PORT_SPEED = PORT_SPEED_MAXFAST;
	PORT_Init(MDR_PORTB, &PORTB_config_struct);
  //---------------------------------------------------------------------------//  
  MDR_PORTC->OE     = 0xffff;                    
  MDR_PORTC->FUNC   = 0x0000;                
  MDR_PORTC->ANALOG = 0xFFFF;      
  MDR_PORTC->PWR    = 0xFFFFFFFF;       // ����������� ������� �����
  //---------------------------------------------------------------------------//
  MDR_PORTD->OE      = 0x00ca;          // ���� D �� ����, PD2 - ADC_CH2, PD4 - ADC_CH4, PD5 - ADC_CH5
  MDR_PORTD->FUNC    = 0x0000;          // ������� - ���� 
  MDR_PORTD->ANALOG  = 0xffcb;          // ����� ����� - ��������, �� PD2 - ADC_CH2, PD4 - ADC_CH4, PD5 - ADC_CH5
  MDR_PORTD->PWR     = 0xFFFFFFFF;      // ����������� ������� ����� ( ������� 10 ��)
  //---------------------------------------------------------------------------//
  MDR_PORTE->OE = 0xffbf;               // ���� E �� �����, PE6 - ���� - ������ ���. �������� ��������
  MDR_PORTE->FUNC = 0x0000;  					  // ������� - ���� 
  MDR_PORTE->ANALOG  = 0xfffe;          // ����� ����� - ��������, PE0 - DAC2 out
  MDR_PORTE->PWR    = 0xFFFFFFFE;       // ����������� ������� �����	
  //---------------------------------------------------------------------------//
  MDR_PORTF->OE = 0xffb7;               // ���� F �� �����,PF3 - RxD
  MDR_PORTF->FUNC = (2 << 6)|		    	  // �����  ����� 1, 2, 3, 4 ����� 
					(2 << 4) |										// - ��������������, ������������ ������ SSP1
					(2 << 2) |
					(2 << 0);
  MDR_PORTF->ANALOG  = 0xffff;          // ����� ����� - ��������
  MDR_PORTF->PWR     = 0xFFFFFFFF;      // ����������� ������� ����� ( ������� 10 ��)
}

void T2_init(void) {
          
  // 200 us interrupt
    
 MDR_RST_CLK->TIM_CLOCK  |= (1 << 25) | (3<<8); // ���������� ������������ Timer2, TIM2_CLK = HCLK/8											
 MDR_TIMER2->CNTRL = 0x00000000;        	// ����� ������������� �������, ����
 MDR_TIMER2->CNT   = 0x0000;       			  // ��������� �������� ��������
 MDR_TIMER2->PSG   = 0;                   // ������������ �������
 MDR_TIMER2->ARR   = 1999;                // ��������� �����, ���������� ������ 200 us
 MDR_TIMER2->IE    = 0x00000002;          // ���������� ���������� �� ������������ TIMER2  
 MDR_TIMER2->STATUS= 0x00000000;          // ���������� �����
	
}


// DAC
  void MCU_DAC2_init (void){
    
    MDR_DAC->CFG = (0<<4) | // DAC1 DAC2 ����������
                   (1<<3) | // DAC2 enabled  
                   (0<<2) | // DAC1 disabled
                   (0<<1) | // DAC2 ref - AUcc voltage
                   (0<<1);  // DAC1 ref - AUcc voltage
  }


//===============================================================//

// ADC measurements
__irq void Timer2_IRQHandler(void)
{
	 //------------ meas & send ------------//
	
	  MCU_ADC_init(2);           // ADC ch 2 - front panel sets 
	  MeasDataTx.VsetCounts = MCU_ADC_read();
 
	  MCU_ADC_init(4);           // ADC ch 4 - load current
	  MeasDataTx.IloadCounts = MCU_ADC_read();

	  MCU_ADC_init(5);           // ADC ch 5 - HV feedback voltage
	  MeasDataTx.VmeasCounts = MCU_ADC_read();
    
	  // reset queues and sending new data
		if(uxQueueMessagesWaitingFromISR(FPsetCounts_q) == 0) // V set
			xQueueSendFromISR(FPsetCounts_q, (void*) &MeasDataTx.VsetCounts,T);   
				
		if(uxQueueMessagesWaitingFromISR(LoadCurrent_q) == 0)	// I load			
			xQueueSendFromISR(LoadCurrent_q, (void*) &MeasDataTx.IloadCounts,T); 
		
		if(uxQueueMessagesWaitingFromISR(FBvoltage_q) == 0)		// V meas
			xQueueSendFromISR(FBvoltage_q, (void*) &MeasDataTx.VmeasCounts,T);   
		
		//------------ PID ------------//
		if(uxQueueMessagesWaitingFromISR(DistVsetRamp_q))
			xQueueReceiveFromISR(DistVsetRamp_q, &DAC2set,T);
		
		PID.curr_error = (float)DAC2set - (float)MeasDataTx.VmeasCounts;       // ���������� ������
		
		PID.P = (PID.kP * PID.curr_error);              		// �-����� ����������
    PID.I = (PID.I + PID.curr_error * PID.kI);     		  // I-����� ����������
    PID.D = ((PID.prev_error - PID.curr_error)*PID.kD); // I-����� ����������
    PID.prev_error = PID.curr_error;
		
		if(PID.I > 5080)  PID.I = 5080;                     // ����������� ������������� ����� ����������
    if(PID.I < -5080) PID.I = -5080;
		
    PID.result = PID.P + PID.I + PID.D;      						// ������������ ������������ ���-����������
			
    if(PID.result > 5080) PID.result = 5080;            // ����������� ��������� ���� ���
    if(PID.result < 0) PID.result = 0;
		 	
		MDR_DAC->DAC2_DATA = (uint32_t)(PID.result*DAC_lsb);
		//------------ PID ------------//
		
	  MDR_TIMER2->CNT = 0;                     // ��������� ����. �������� �� 0
    MDR_TIMER2->STATUS = 0x0000;             // ����� ������� ����������
    NVIC_ClearPendingIRQ(Timer2_IRQn);       // �����������!
}

void task_HVramp(void *pvParameters)
{
	TickType_t xLastWakeTime;
  const TickType_t period = 1;
	
	uint16_t VsetCounts = 0;
	uint16_t VcurrCounts = 0;
	uint16_t VprevCounts = 0;
	
	// Initialise the var with the current time.
  xLastWakeTime = xTaskGetTickCount();
	
	MDR_TIMER2->CNTRL &= 0;
		VcurrCounts = (uint16_t)MDR_DAC->DAC2_DATA; 
	MDR_TIMER2->CNTRL |= 1;	
	
	xQueueReceive(DistVsetNum_q,  &VsetCounts,T);

	if(VsetCounts == 0)
		xQueueSend(DistVsetRamp_q, (void*) &VsetCounts,T);  
	
	if(VsetCounts < VcurrCounts)
	{
		while(VsetCounts != VcurrCounts)
		{
			VcurrCounts--;
			xQueueSend(DistVsetRamp_q, (void*) &VcurrCounts,T);   
			vTaskDelayUntil(&xLastWakeTime, period);
		}
	}

  if(VsetCounts > VcurrCounts)
	{
		while(VsetCounts != VcurrCounts)
		{
			VcurrCounts++;
			xQueueSend(DistVsetRamp_q, (void*) &VcurrCounts,T);   
			vTaskDelayUntil(&xLastWakeTime, period);
		}
	}
	
  holding_reg_write(13,(uint16_t)VsetCounts);
	holding_reg_write(14,(uint16_t)VcurrCounts);
	
	vTaskDelete(NULL);
}
				
// Modbus RTU over TCP state machine
void task_ModbusSM(void *pvParameters)
{
  PIDregInit();
	
  uint16_t wr_reg_addr = 0;       // modbus write reg addr
  uint16_t RegisterValue = 0;     // modbus write reg velue
	
	ADC_meas MeasDataRx;
	uint32_t Vfb_meas   = 0;
	uint32_t Iload_meas = 0;
	uint32_t Iload_int  = 0;
	uint32_t Vset_meas  = 0;
	
	uint16_t V2setCounts = 0;
	uint16_t VprevCounts = 0;
	
	while(1)
    {   
     // ���� ������ ��� � ���������� modbus_request �������� ��� ��� 
     switch(modbus_get_poll())
     {
//////////////////////////// ������ HOLDING ////////////////////////// 
         case MODBUS_RHR_CMD:
					 
           Modbus_LED_ON;
				 
           // get measured data if queues are not empty 
           if(uxQueueMessagesWaiting(FPsetCounts_q) > 0)
              xQueueReceive(FPsetCounts_q, &MeasDataRx.VsetCounts,T);
					 
					 if(uxQueueMessagesWaiting(LoadCurrent_q) > 0)
              xQueueReceive(LoadCurrent_q, &MeasDataRx.IloadCounts,T);
					            
					 if(uxQueueMessagesWaiting(FBvoltage_q) > 0)
              xQueueReceive(FBvoltage_q, &MeasDataRx.VmeasCounts,T);
					 
					 // 0.8056640625 = (ADC_Vref*1000)/4096 = DAC_lsb
					 
					 Vfb_meas   = (uint32_t)((float)MeasDataRx.VmeasCounts * DAC_lsb); 		 // HV feedback meas voltage
		  	   Vset_meas  = (uint32_t)((float)MeasDataRx.VsetCounts  * DAC_lsb);		 // front panel set voltage
					 
					 Iload_meas = (uint32_t)(((float)MeasDataRx.IloadCounts * DAC_lsb)/k); // load current
					 Iload_meas = (Iload_meas * 1000)/Rs; 																 // load current V to I converison
					 
					 Iload_int  = (uint32_t)(((float)Vfb_meas * 1000000.0)/Rint);					 // internal load calc
					 Iload_meas -= Iload_int;																							 // internal load compensation
					 
           holding_reg_write(2,(uint16_t)Vset_meas);
				   holding_reg_write(5,(uint16_t)Vfb_meas);
					 holding_reg_write(6,(uint16_t)Iload_meas);
					
					 holding_reg_write(7,(uint16_t)PID.P);
					 holding_reg_write(8,(uint16_t)PID.I);
					 holding_reg_write(9,(uint16_t)PID.D);
					 
					 holding_reg_write(11,HV_SWITCH_ON);
					 
           modbus_rhr_answer(); // modbus rhr cmd answer
           
           Modbus_LED_OFF; 		  // LED toggle
           
         break;
//////////////////////////// ������ HOLDING ////////////////////////// 
          case MODBUS_WSR_CMD:  // ������ holding ���������
           modbus_wsr_answer(); // ����� �� ������
          // ���������� ���������� ������������ ������� �� ������ ��������� 
           
           wr_reg_addr = get_wr_reg_addr();    // get address
           RegisterValue = get_wr_reg_val();   // get the new value
           
           switch(wr_reg_addr)
           {
               //=====                     
               case 0: // set voltage
									if(RegisterValue < 3200) 
									{
										V2setCounts = (uint16_t)((float)RegisterValue/DAC_lsb);
										xQueueSend(DistVsetNum_q, (void*) &V2setCounts,T);
										xTaskCreate(task_HVramp,"task_HVramp", configMINIMAL_STACK_SIZE,NULL,1,NULL);
									}
               break;
							 //=====                     
               case 1: 
									
               break;

               //=====
               default: break;
           } 
          //eeprom_wr_regs(HOLD_REGS);
           
          break;
//////////////////////////// ������ INPUT ////////////////////////////
          case MODBUS_RIR_CMD:  // ������ input ���������
           
           //input_reg_write(0,FirmInfo.ver);
           //input_reg_write(1,FirmInfo.developer);
           input_reg_write(2,(unsigned int)get_modbus_id());
           
           modbus_rir_answer(); // ����� �� ������
          break;
          
       } // switch
    } // while

} // end of task


int main()
{ 

	OSC_init();
	GPIO_init();
	T2_init();
	MCU_ADC_init(5);
	MCU_DAC2_init();
	
	modbus_init();

	HV_SUPPLY_ON;
	
	FPsetCounts_q = xQueueCreate(32, sizeof(uint32_t));
	LoadCurrent_q = xQueueCreate(32, sizeof(uint32_t));
	FBvoltage_q   = xQueueCreate(32, sizeof(uint32_t));
  DistVsetRamp_q= xQueueCreate(32, sizeof(uint16_t));
  DistVsetNum_q = xQueueCreate(10, sizeof(uint16_t));
	//VzeroLvl_q	  = xQueueCreate(10, sizeof(uint16_t));

	xTaskCreate(task_ModbusSM,"ModbusSM",  configMINIMAL_STACK_SIZE*2,NULL,1,NULL);

	NVIC_EnableIRQ(Timer2_IRQn); // ���������� ���������� ��� T2
	NVIC_EnableIRQ(UART1_IRQn);  // ���������� ���������� ��� UART1
	__enable_irq();	      	     // Enable Interrupts global
	MDR_TIMER2->CNTRL |= 1;

	vTaskStartScheduler(); 			//������ ������������ �����
}
//================================================================//