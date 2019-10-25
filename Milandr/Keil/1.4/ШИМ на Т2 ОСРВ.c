#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "main.h"
#include "mdr_modbus.h"
#include "mdr_adc.h"
#include <MDR32F9Qx_timer.h>
#include <MDR32F9Qx_port.h>



PORT_InitTypeDef PortInitStructure;

TIMER_CntInitTypeDef 		TimerInitStructure;
TIMER_ChnInitTypeDef 		TimerChnInitStructure;
TIMER_ChnOutInitTypeDef TimerChnOutInitStructure;

void OSC_init(void)
{

#define	_HSEBYP	0   // 0 - режим осциллятора, 1 - режим внешнего генератора
#define	_HSEON  1	  // 0 - выключен, 1 - включен

//---CLK-----------------------------------------------------------------------------------------------------

  MDR_RST_CLK->HS_CONTROL = (_HSEBYP<<1) + _HSEON; 
  while ((MDR_RST_CLK->CLOCK_STATUS & 0x04) != 0x04);     // ждем пока HSE выйдет в рабочий режим
  MDR_RST_CLK->PLL_CONTROL = ((1 << 2) | (7 << 8)); 	  // вкл. PLL | коэф. умножения = 2

  while((MDR_RST_CLK->CLOCK_STATUS & 0x02) != 0x02);      // ждем когда PLL выйдет в раб. режим

  MDR_RST_CLK->CPU_CLOCK  = (2                           // источник для CPU_C1 - HSE
						   |(1 << 2)                      // источник для CPU_C2 - PLLCPUo 
						   |(1 << 4)                      // предделитель для CPU_C3 - CPU_C2
						   |(1 << 8));                    // источник для HCLK
  MDR_RST_CLK->PER_CLOCK = 0xFFFFFFFF;        // вкл. тактирование всей перефирии
  // HCLK = 80 МГц
}
   







void GPIO_init (void)
{  
  
  MDR_PORTA->OE      = 0xFFFD;          // PA1 - вход синхронизации
  MDR_PORTA->FUNC    = (2<<2);          // функция - порт, для РА5 альтернативная функция 
  MDR_PORTA->ANALOG  = 0xFFFF;          // режим потра - цифровой
  MDR_PORTA->PWR     = 0xFFFFFFFF;      // максимально быстрый фронт ( порядка 10 нс)
  //---------------------------------------------------------------------------//
  // Инициализация структуры для настройки порта
	PORT_InitTypeDef PORTB_config_struct;
	PORT_StructInit(&PORTB_config_struct);
	
	// Настройка порта
	PORTB_config_struct.PORT_Pin = PORT_Pin_9  & (~JTAG_PINS(MDR_PORTB));  // Чтобы не отваливался JTAG,
																																				 // исключаем из инициализации JTAG-овские пины
	PORTB_config_struct.PORT_OE = PORT_OE_OUT;
	PORTB_config_struct.PORT_MODE = PORT_MODE_DIGITAL;
	PORTB_config_struct.PORT_SPEED = PORT_SPEED_MAXFAST;
	PORT_Init(MDR_PORTB, &PORTB_config_struct);
  //---------------------------------------------------------------------------//  
  MDR_PORTC->OE     = 0xffff;                    
  MDR_PORTC->FUNC   = 0x0000;                
  MDR_PORTC->ANALOG = 0xFFFF;      
  MDR_PORTC->PWR    = 0xFFFFFFFF;       // максимально быстрый фронт
  //---------------------------------------------------------------------------//
  MDR_PORTD->OE      = 0x00ca;          // порт D на вход, PD2 - ADC_CH2, PD4 - ADC_CH4, PD5 - ADC_CH5
  MDR_PORTD->FUNC    = 0x0000;          // функция - порт 
  MDR_PORTD->ANALOG  = 0xffcb;          // режим потра - цифровой, но PD2 - ADC_CH2, PD4 - ADC_CH4, PD5 - ADC_CH5
  MDR_PORTD->PWR     = 0xFFFFFFFF;      // максимально быстрый фронт ( порядка 10 нс)
  //---------------------------------------------------------------------------//
  MDR_PORTE->OE = 0xffbf;               // порт E на выход, PE6 - вход - анализ вкл. тумблера высокого
  MDR_PORTE->FUNC = 0x0000 | 3 << 5;  					  // функция - порт 
  MDR_PORTE->ANALOG  = 0xfffe;          // режим потра - цифровой, PE0 - DAC2 out
  MDR_PORTE->PWR    = 0xFFFFFFFE;       // максимально быстрый фронт
	
//	PORT_StructInit(&PortInitStructure);
//	PortInitStructure.PORT_FUNC = PORT_FUNC_ALTER;
//	PortInitStructure.PORT_OE = PORT_OE_OUT;
//	PortInitStructure.PORT_MODE = PORT_MODE_DIGITAL;
//	PortInitStructure.PORT_Pin = PORT_Pin_2;
//	PortInitStructure.PORT_SPEED = PORT_SPEED_MAXFAST;
//	PORT_Init (MDR_PORTE, &PortInitStructure);
	
  //---------------------------------------------------------------------------//
  MDR_PORTF->OE = 0xffb7;               // порт F на выход,PF3 - RxD
  MDR_PORTF->FUNC = (2 << 6)|		    	  // режим  пинов 1, 2, 3, 4 порта 
					(2 << 4) |										// - альтернативный, задействован модуль SSP1
					(2 << 2) |
					(2 << 0);
  MDR_PORTF->ANALOG  = 0xffff;          // режим потра - цифровой
  MDR_PORTF->PWR     = 0xFFFFFFFF;      // максимально быстрый фронт ( порядка 10 нс)
}

void T2_init(void) {
          
  // настройка таймера для работы в режиме ШИМ - f = 625 кГц
    
 MDR_RST_CLK->TIM_CLOCK  |= (1 << 25) | (3<<8); // разрешение тактирования Timer2, TIM2_CLK = HCLK/128											
// MDR_TIMER2->PSG   = 0;               		 // предделитель частоты = 0
// MDR_TIMER2->CNTRL = 0x00000000;        	 // направление счета основного счетчика от нуля до ARR,
//						 // начальное значение - число из регистра CNT 
// MDR_TIMER2->ARR   = 63;                	 // основание счета. 
// MDR_TIMER2->CNT   = 0;       	           // начальное значение счетчика 
////Режим работы каналов - ШИМ 
// MDR_TIMER2->CCR3 = 50;                  // начальная скважность - 0  
//	
// //канал 2 - ШИМ
// MDR_TIMER2->CH3_CNTRL  =  6 << 9;      // 1, если DIR= 0 (счет вверх)
// MDR_TIMER2->CH3_CNTRL1 =  (2<<2); 
//	
// MDR_TIMER2->IE = 0x0000;              // 
// MDR_TIMER2->STATUS= 0;                // сбрасываем флаги
	
	MDR_TIMER2->CNT = 0; // Считай с 0.
	MDR_TIMER2->PSG = 0; // На таймер идет частота TIM_CLK/32000.
	MDR_TIMER2->ARR = 399; //PWM_speed;
	//MDR_TIMER1->CH1_CNTRL = 3<<TIMER_CH_CNTRL_OCCM_Pos; // Переключение REF, если CNT = CCR;
	MDR_TIMER2->CH3_CNTRL = 6<<TIMER_CH_CNTRL_OCCM_Pos; // REF = 1, когда CNT < CCR1, 0 - CNT >= CCR1;
	MDR_TIMER2->CH3_CNTRL1 = (2<<TIMER_CH_CNTRL1_SELO_Pos) // На выход выдается сигнал c REF.
	| (1<<TIMER_CH_CNTRL1_SELOE_Pos); // Канал всегда работает на выход.
	MDR_TIMER2->CCR3 = 0;//timeEnabledState;

  MDR_TIMER2->CNTRL = TIMER_CNTRL_CNT_EN; // Включаем таймер.
}


// DAC
  void MCU_DAC2_init (void){
    
    MDR_DAC->CFG = (0<<4) | // DAC1 DAC2 асинхронны
                   (1<<3) | // DAC2 enabled  
                   (0<<2) | // DAC1 disabled
                   (0<<1) | // DAC2 ref - AUcc voltage
                   (0<<1);  // DAC1 ref - AUcc voltage
  }


//===============================================================//

//__irq void Timer2_IRQHandler(void)
//{
//		MDR_PORTA->RXTX |= (1<<3);
//	  
//	  MDR_TIMER2->CNT = 0;                     // установка знач. счетчика на 0
//    MDR_TIMER2->STATUS = 0x0000;             // сброс статуса прерывания
//    NVIC_ClearPendingIRQ(Timer2_IRQn);       // обязательно!
//}

void task_PWM(void *pvParameters)
{
	while(1)
	{
		MDR_PORTE->RXTX |=   (1<<2);
		vTaskDelay(2);
		MDR_PORTE->RXTX &=  ~(1<<2);
		vTaskDelay(20);
	}
}
				
// Modbus RTU over TCP state machine
void task_ModbusSM(void *pvParameters)
{

  uint16_t wr_reg_addr = 0;       // modbus write reg addr
  uint16_t RegisterValue = 0;     // modbus write reg velue

	uint32_t Meas_Vset, Meas_CtsSet  = 0; 			  // front panel voltage sets
	uint32_t Meas_Vfb   = 0; 			  // HV feedback voltage
	uint32_t Meas_Iload = 0;				// load current measurements
	
	while(1)
    {   

     // если запрос был в переменной modbus_request сохранен его код 
     switch(modbus_get_poll())
     {
//////////////////////////// ЧТЕНИЕ HOLDING ////////////////////////// 
         case MODBUS_RHR_CMD:
					 
           Modbus_LED_ON;
           // get measured voltage if queue is not empty 
           //if(uxQueueMessagesWaiting(IP704_RdVoltage_q) > 0)
           //   xQueueReceive(IP704_RdVoltage_q, &IP704_m, (TickType_t)0);
				 

				   MCU_ADC_init(2);           // ADC ch 2 - front panel sets 
				   Meas_CtsSet = MCU_ADC_read();
				   Meas_Vset = (uint32_t)((float)Meas_CtsSet * 0.8056640625); // (ADC_Vref * 1000.0) /4096.0
				 
				 	 MCU_ADC_init(4);           // ADC ch 4 - load current
				   Meas_Iload = MCU_ADC_read();
					 Meas_Iload = (uint32_t)((float)Meas_Iload * 0.8056640625); 
				   Meas_Iload = ((Meas_Iload * 1000)/Rs)/3;
				 
				 	 MCU_ADC_init(5);           // ADC ch 5 - HV feedback voltage
				   Meas_Vfb = MCU_ADC_read();
					 Meas_Vfb = (uint32_t)((float)Meas_Vfb * 0.8056640625);
				 
           holding_reg_write(2,(uint16_t)Meas_Vset);
					 holding_reg_write(3,(uint16_t)Meas_CtsSet);
				   holding_reg_write(5,(uint16_t)Meas_Vfb);
					 holding_reg_write(6,(uint16_t)Meas_Iload);
					 holding_reg_write(11,HV_SWITCH_ON);
					 
				   MDR_TIMER2->CCR3 = (uint32_t)(Meas_CtsSet/);
					 
           modbus_rhr_answer(); // modbus rhr cmd answer
           
           Modbus_LED_OFF; 		  // LED toggle
           
         break;
//////////////////////////// ЗАПИСЬ HOLDING ////////////////////////// 
          case MODBUS_WSR_CMD:  // запись holding регистров
           modbus_wsr_answer(); // ответ на запрос
          // заполнение переменных пользователя данными из Модбас регистров 
           
           wr_reg_addr = get_wr_reg_addr();    // get address
           RegisterValue = get_wr_reg_val();   // get the new value
           
           switch(wr_reg_addr)
           {
               //=====                     
               case 0: // set voltage
									MDR_DAC->DAC2_DATA = (uint32_t)RegisterValue;
               break;
							 //=====                     
               case 1: 
									MDR_TIMER2->CCR3 = (uint32_t)RegisterValue;
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

} // end of task


int main()
{
	
	OSC_init();
	GPIO_init();

	modbus_init();
	MCU_ADC_init(5);
	MCU_DAC2_init();
	HV_SUPPLY_ON;
	
	//NVIC_EnableIRQ(Timer2_IRQn); // Разрешение прерывания для T2
	NVIC_EnableIRQ(UART1_IRQn); // Разрешение прерывания для UART1
	__enable_irq();	      	    // Enable Interrupts global

	xTaskCreate(task_ModbusSM,"ModbusSM", configMINIMAL_STACK_SIZE*2,NULL,1,NULL);
  //xTaskCreate(task_PWM,"PWM", configMINIMAL_STACK_SIZE,NULL,1,NULL);
	
  T2_init();
	
	vTaskStartScheduler(); 			//Запуск планировщика задач
}
//================================================================//