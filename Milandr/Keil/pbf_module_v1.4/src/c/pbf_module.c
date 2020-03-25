#include "MDR32Fx.h" 
#include "main.h"
#include "pbf_module.h"

//======================== USER FUNCS ===========================//
PORT_InitTypeDef PortInitStructure;

// measured counts to clean I conversion
uint16_t CalcCurrent(uint16_t V_meas, uint16_t Imeas)
{
	uint32_t Iload_meas = 0;
	float 	 Iload_int  = 0;
	
	Iload_meas = (uint32_t)(((float)Imeas * DAC_lsb)/k); // load current
	Iload_meas = (Iload_meas * 1000)/Rs; 								 // load current V to I converison

	Iload_int  = ((float)V_meas * 1000000.0)/Rint;		 // internal load calc
	Iload_meas -= Iload_int;														 // internal load compensation

	if(Iload_meas < 0)		// correct if minus
	 Iload_meas = 0;
	
	return (uint16_t)Iload_meas;
}


//===============================================================//
// MCU periph init

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
  
  MDR_PORTA->OE      = 0xFFDD;          // PA1- вход синхронизации, PA5 - тумблер режима упр
  MDR_PORTA->FUNC    = (2<<2);          // функция - порт, для РА1 альтернативная функция 
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
	
	MDR_PORTB->FUNC |= ((2 << 5*2) | (2 << 6*2)) & (~JTAG_PINS(MDR_PORTB)); //режим работы порта
  MDR_PORTB->ANALOG |= ((1 << 5) | (1 << 6));   //цифровой
  MDR_PORTB->PWR |= ((3 << 5*2) | (3 << 6*2));  //максимально быcтрый
	
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
  MDR_PORTE->FUNC = 0x0000;  					  // функция - порт 
  MDR_PORTE->ANALOG  = 0xfffe;          // режим потра - цифровой, PE0 - DAC2 out
  MDR_PORTE->PWR    = 0xFFFFFFFE;       // максимально быстрый фронт	
  //---------------------------------------------------------------------------//
  MDR_PORTF->OE = 0xffb7;               // порт F на выход,PF3 - RxD
  MDR_PORTF->FUNC = (2 << 6)|		    	  // режим  пинов 1, 2, 3, 4 порта 
					(2 << 4) |										// - альтернативный, задействован модуль SSP1
					(2 << 2) |
					(2 << 0);
  MDR_PORTF->ANALOG  = 0xffff;          // режим потра - цифровой
  MDR_PORTF->PWR     = 0xFFFFFFFF;      // максимально быстрый фронт ( порядка 10 нс)
}



void T1_init(void) 
{
          
  MDR_RST_CLK->TIM_CLOCK  |= (1 << 24);      // разрешение тактирования Timer1, TIM1_CLK = HCLK/8 = 10МГц												

  MDR_TIMER1->CNTRL = 4<<8;                           // источник событий - событие на 1 канале «Режим 1» 
  MDR_TIMER1->CH1_CNTRL = (1<<15)| (1<<4);            // канал работает в режиме Захват | отрицательный фронт
  MDR_TIMER1->CH1_CNTRL1 = (1<<2)|(1<<1);	      			// спад по CCR11; отрицательный фронт по Chi
                                                      // начальное значение - число из регистра CNT 
  MDR_TIMER1->PSG   = 0;                           
  MDR_TIMER1->ARR   = 1999;                	      
  MDR_TIMER1->CNT   = 0;       	                      // начальное значение счетчика 
  MDR_TIMER1->IE    = (1<<13);              					//по переднему и заднему фронту 1 канала
  MDR_TIMER1->STATUS= 0;                              // сбрасываем флаги
  
 }

void T2_init(void) 
{
          
 // 200 us int 
    
 MDR_RST_CLK->TIM_CLOCK  |= (1 << 25) | (3<<8); // разрешение тактирования Timer2, TIM2_CLK = HCLK/8											
 MDR_TIMER2->CNTRL = 0x00000000;        	// Режим инициализации таймера, откл
 MDR_TIMER2->CNT   = 0x0000;       			  // Начальное значение счетчика
 MDR_TIMER2->PSG   = 0;                   // Предделитель частоты
 MDR_TIMER2->ARR   = 1999;                // Основание счета, прерывание каждые 200 us - 1999
 MDR_TIMER2->IE    = 0x00000002;          // разрешение прерывания по переполнению TIMER2  
 MDR_TIMER2->STATUS= 0x00000000;          // сбрасываем флаги
	
}



// DAC
void MCU_DAC2_init (void)
{
    
    MDR_DAC->CFG = (0<<4) | // DAC1 DAC2 асинхронны
                   (1<<3) | // DAC2 enabled  
                   (0<<2) | // DAC1 disabled
                   (0<<1) | // DAC2 ref - AUcc voltage
                   (0<<1);  // DAC1 ref - AUcc voltage
 }



//===============================================================//