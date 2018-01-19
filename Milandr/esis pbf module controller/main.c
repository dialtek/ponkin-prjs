/// Рабочий код ,программа для микроконтроллера  
/// устройство - универсальный опторазвязанный контроллер 3U оптика/ modbus

#include "MDR32Fx.h"
#define F_CPU 80000000

#define U8  uint8_t
#define U16 uint16_t 
#define S16 int16_t 
#define U32 uint32_t
#define S32 int32_t

#include "mdr_delay.h"

// сигналы запуска и остановки блока ресинхронизации данных в ПЛИС
#define SYNC_LED_ON  	MDR_PORTE->RXTX |=  1<<3 
#define SYNC_LED_OFF  	MDR_PORTE->RXTX &= ~(1<<3) 

#define RS485_RX_EN     MDR_PORTB->RXTX &= ~(1<<10)  // вкл.  приемник RS485   \_ 
#define RS485_RX_DIS    MDR_PORTB->RXTX |=  (1<<10)  // выкл. приемник RS485   _/
#define RS485_TX_EN     MDR_PORTB->RXTX |=  (1<<9)   // вкл.  передатчик RS485 _/
#define RS485_TX_DIS    MDR_PORTB->RXTX &= ~(1<<9)  // выкл. передатчик RS485 \_

// сигнал готовности данных АЦП для чтения 
#define RXFE                1<<4                    // равен 1 если пуст буфер FIFO приемника 
#define FIFO_has_byte       !(MDR_UART1->FR & RXFE)
#define CH1_CCR_CAP_EVENT   (1<<13)                 // Событие ?переднего? фронта на входе CAP каналов таймера 
                                                    // Бит 7 – третий канал
#define ADC_Vref            3.3		    // измеренное вольтметром напряжение питания МК

#define Status_LED_ON     MDR_PORTC->RXTX |= 1 
#define Status_LED_OFF    MDR_PORTC->RXTX &= ~1
#define Error_LED_ON      MDR_PORTC->RXTX |= 1 << 1 
#define Error_LED_OFF     MDR_PORTC->RXTX &= ~(1 << 1)

  U8 need2send = 0;    // флаг запроса на выдачу данных по UART	
  U8 need2update = 0; 
  U8 need2setDAC = 0;  // флаг обновления напряжения DAC

  U32 MCU_current_ADC_channel = 0;
  U16 MCU_ADC_aver_param = 10;    // величина усренднения данных АЦП
  S32 DAC_code = 0;                // код DAC - управление выходным напряжением 
  S32 ADC_code = 0;                // отсчеты АЦП напряжения ОС HV-части
  float k = 0;          // пропорциональный коэффициент П-регулятора
  S32 error = 0;        // ошибка показаний АЦП и кода ЦАП 
  S32 mDAC_code = 0;    // скорректированное значение кода ЦАП
  S16 ADC_zero_lvl = 0; // сдвиг 0 АЦП 
  
  U16 rx_data = 0;
  
  void OSC_init(void){

#define	_HSEBYP	0       // 0 - режим осциллятора, 1 - режим внешнего генератора
#define	_HSEON  1	// 0 - выключен, 1 - включен

//---CLK-----------------------------------------------------------------------------------------------------

  MDR_RST_CLK->HS_CONTROL = (_HSEBYP<<1) + _HSEON; 
  while ((MDR_RST_CLK->CLOCK_STATUS & 0x04) != 0x04);     // ждем пока HSE выйдет в рабочий режим
  MDR_RST_CLK->PLL_CONTROL = ((1 << 2) | (7 << 8)); 	  // вкл. PLL | коэф. умножения = 2

  while((MDR_RST_CLK->CLOCK_STATUS & 0x02) != 0x02);      // ждем когда PLL выйдет в раб. режим

  MDR_RST_CLK->CPU_CLOCK  = (2                           // источник для CPU_C1 - HSE
						   |(1 << 2)                      // источник для CPU_C2 - PLLCPUo 
						   |(1 << 4)                      // предделитель для CPU_C3 - CPU_C2
						   |(1 << 8));                    // источник для HCLK
  MDR_RST_CLK->PER_CLOCK = 0xFFFFFFFF;                    // вкл. тактирование всей перефирии
  // HCLK = 80 МГц
  MDR_RST_CLK->TIM_CLOCK = 0x00000000;
  }
   
  void GPIO_init (void){  
  
  MDR_PORTA->OE      = 0xFFFD;          //  PA1 - вход синхронизации
  MDR_PORTA->FUNC    = (2<<2);          // функция - порт, для РА5 альтернативная функция 
  MDR_PORTA->ANALOG  = 0xFFFF;          // режим потра - цифровой
  MDR_PORTA->PWR     = 0xFFFFFFFF;      // максимально быстрый фронт ( порядка 10 нс)
  //---------------------------------------------------------------------------//
  MDR_PORTB->OE = 0xFFFF;               // порт B на выход, PB9, PB10 - разрешение работы приемопередатчика RS485 на UART2
  MDR_PORTB->FUNC = 0x0000;             // функция - порт, PB0 - альтернативная функция
  MDR_PORTB->ANALOG  = 0xffff;          // режим потра - цифровой
  MDR_PORTB->PWR     = 0xFFFFFFFF;      // максимально быстрый фронт ( порядка 10 нс)
  //---------------------------------------------------------------------------//  
  MDR_PORTC->OE     = 0xffff;                    
  MDR_PORTC->FUNC   = 0x0000;                
  MDR_PORTC->ANALOG = 0xFFFF;      
  MDR_PORTC->PWR    = 0xFFFFFFFF;       // максимально быстрый фронт
  //---------------------------------------------------------------------------//
  MDR_PORTD->OE = 0x007f;               // порт D на вход, PD7 - ADC_CH7
  MDR_PORTD->FUNC = 0x0000;             // функция - порт 
  MDR_PORTD->ANALOG  = 0xff7f;          // режим потра - цифровой, но PD7 - ADC_CH7
  MDR_PORTD->PWR     = 0xFFFFFFFF;      // максимально быстрый фронт ( порядка 10 нс)
  MDR_PORTD->PD      =  0x0000;
  //---------------------------------------------------------------------------//
  MDR_PORTE->OE = 0xffff;               // порт E на выход
  MDR_PORTE->FUNC = 0x0000;             // функция - порт 
  MDR_PORTE->ANALOG  = 0xfff0;          // режим потра - цифровой, PE0 - DAC2 out
  
  //---------------------------------------------------------------------------//
  MDR_PORTF->OE = 0xffb7;               // порт F на выход,PF3 - RxD
  MDR_PORTF->FUNC = (2 << 6) |		    // режим  пинов 1, 2, 3, 4 порта 
					(2 << 4) |			// - альтернативный, задействован модуль SSP1
					(2 << 2) |
					(2 << 0);
  MDR_PORTF->ANALOG  = 0xffff;          // режим потра - цифровой
  MDR_PORTF->PWR     = 0xFFFFFFFF;      // максимально быстрый фронт ( порядка 10 нс)

   }
 
  void timer1_init(void) {
          
  // настройка таймера для режима захвата падающего фронта -> \_ 
          
  MDR_TIMER1->CNTRL = 4<<8;                               // источник событий - событие на 1 канале «Режим 1» 
  MDR_TIMER1->CH1_CNTRL = (1<<15) | (1<<4);               // канал работает в режиме Захват | отрицательный фронт
  MDR_TIMER1->CH1_CNTRL1 = 0;
  MDR_TIMER1->CNT   = 0;                                  // Начальное значение счетчика - 0
  MDR_TIMER1->PSG   = 0;                         	  // Предделитель частоты тактирования Т1 - 1
  MDR_TIMER1->ARR   = 0xffff;                             // Основание счета, таймер тикает до 65535
  MDR_TIMER1->IE    = (1<<5)|(1<<13);                     // разрешения прерывания по переднему и заднему фронту 1 канала
  MDR_RST_CLK->TIM_CLOCK  |= (1 << 24);                   // делитель частоты|разрешение тактирования Таймера 1
  MDR_TIMER1->STATUS= 0;                                  // сбрасываем флаги
  
 }

  void timer3_init(void) {
          
  // настройка таймера для прерывания каждые ~ 100 мкс
          
 MDR_RST_CLK->TIM_CLOCK  |= (1 << 26);           // разрешение тактирования Timer1, TIM1_CLK = HCLK/8 												
 MDR_TIMER3->PSG   = 0;               		 // предделитель частоты = 0
 MDR_TIMER3->CNTRL = 0x00000000;        	 // направление счета основного счетчика от нуля до ARR,
						 // начальное значение - число из регистра CNT 
 MDR_TIMER3->ARR   = 7999;                	 // основание счета
 MDR_TIMER3->CNT   = 0;       	                 // начальное значение счетчика 
 MDR_TIMER3->IE    = (1 << 1);                   //разрешение прерывания по совпадению

}
      
/*=========================================================================== */
// ADC MCU
  void MCU_ADC_init(){

  MDR_RST_CLK->PER_CLOCK |= (1 << 17); //тактирование АЦП
  
  MDR_ADC->ADC1_CFG = (1 //Включение АЦП  
  |(0 << 2)   	// источник синхросигнала*/
  |(1 << 3)   	// Выбор способа запуска АЦП - послед. 
  |(0 << 4)  	// номер канала преобразования*/ - не важно, так как установим канал позже
  |(1 << 9)  	// переключение включено (перебираются каналы, выбранные в регистре выбора канала)
  |(0 << 10) 	// автоматический контроль уровней откл.
  |(0 << 11)  	// источник опорного - внутренний (VDD)
  |(2 << 12)  	// коэффициент деления частоты ADC_clk = HCLK/4
  |(0 << 16)  	//  работа двух АЦП одновременн откл.
  |(0 << 17)    //  TS_EN датчик температуры и источника опорного напряжения откл
  |(0 << 18)    // TS_BUF_EN усилитель для датчика температуры и источника опорного напряжения откл.
  |(0 << 19) 	// оцифровка датчика температуры откл./
  |(0 << 20));  // оцифровка источника опорного напряжения на 1.23 В откл
}

  void MCU_ADC_start_conv(void){
  
  	MDR_ADC->ADC1_CFG |= 1<<1;
  
}

  U32 MCU_ADC_read(void){
	  
	  // чтение АЦП, t выборки + t преобразования канала = 3.2 мкС при HCLK = 10М и предделителе АЦП = 1
	  //		     t выборки + t преобразования канала = 0.5 мкС при HCLK = 70М и предделителе АЦП = 1					
	  // вес младшего разряда АЦП = 3,3/4095 = 0,8 мВ
	  
	  U32 ADC_data = 0;
	  
  	  MCU_ADC_start_conv(); // начало преобразований данных
	  
	  while(!(MDR_ADC->ADC1_STATUS) & (1<<2)) {} // ждем готовность 
	  ADC_data = MDR_ADC->ADC1_RESULT;			 // читаем
	  
	  MCU_current_ADC_channel = ADC_data << 11;  //вытаскиваем номер 
	  MCU_current_ADC_channel = MCU_current_ADC_channel >> 27;  //канала чьи измерения
	  
	  ADC_data = ADC_data << 20;    // отбрасываем инфу о 
	  ADC_data = ADC_data >> 20;    // канале измерений
	  
	  return ADC_data;
}
					   
  void MCU_ADC_set_ch(U8 channel){
	  
	if (channel > 16) return;
	
	MDR_ADC->ADC1_CHSEL = 1 << channel; 
	
	
}

  U32 MCU_ADC_Rd_average(U16 AverValue){
	  
	  // чтение АЦП, t выборки + t преобразования канала = 3.2 мкС при HCLK = 10М и предделителе АЦП = 1
	  // t выборки + t преобразования канала = 0.5 мкС при HCLK = 70М и предделителе АЦП = 1	
	  // усреднение результатов преобразований АЦП
	  
	  U32 Aver_ADC_data = 0;
	  
	  for(int i = 0; i < AverValue; i++ )
	  {
	   Aver_ADC_data += MCU_ADC_read();
	  }
  
	  Aver_ADC_data = Aver_ADC_data/AverValue; 
	  
	  return Aver_ADC_data;
}

  U32 Get_ADC_ch_voltage(U8 ADC_channel){
	  // чтение усредненного результата преобраз. канала АЦП, преобразование в мВ
	  
	  U32 ADC_rd_data = 0;
 	  U32 ADC_meas_voltage = 0;
	  
	  MCU_ADC_set_ch(ADC_channel);	// установка канала АЦП
	  ADC_rd_data = MCU_ADC_Rd_average(MCU_ADC_aver_param);		// читаем среднее значение отсчетов АЦП
	  ADC_meas_voltage = (U32)((ADC_Vref*ADC_rd_data*1000.0)/4096.0);	// преобразуем в волты  
	  return ADC_meas_voltage; 

}
/*=========================================================================== */

/*=========================================================================== */
// UART
  void Uart1_init (void){
//UART	  
  MDR_RST_CLK->PER_CLOCK |= (1UL << 22); //тактирование порта B
  MDR_PORTB->FUNC |= ((2 << 5*2) | (2 << 6*2)); //режим работы порта
  MDR_PORTB->ANALOG |= ((1 << 5) | (1 << 6)); //цифровой
  MDR_PORTB->PWR |= ((3 << 5*2) | (3 << 6*2)); //максимально быcтрый

 //Параметры делителя при частоте = 80 Мгц и скорости = 115200
MDR_UART1->IBRD = 43;   // целая часть делителя скорости
MDR_UART1->FBRD = 26;   // дробная часть делителя скорости

MDR_UART1->LCR_H = ((0 << 1) // работа без провеки четности 
                   |(0 << 2) // бит четности отключен
                   |(0 << 3) // кол-во стоповых бит = 1
                   |(0 << 4) // включение буфера FIFO, 0 - выкл
                   |(3 << 5) // размер кадра - 8 бит
                   |(0 << 7)); // передача бита четности запрещена

MDR_UART1->IMSC = (1 << 4); // прерывание от приемника
MDR_UART1->CR = ((1 << 8)|(1 << 9) | 1);  // работа приемника и передатчика разрешена
}
  
  void Uart2_init (void){
// инициализация модуля UART2
	  
MDR_PORTD->FUNC   |= ((2 << 2) | (2 << 0)); // режим работы порта - UART2
MDR_PORTD->ANALOG |= ((1 << 1) | (1 << 0)); // цифровой порт
MDR_PORTD->PWR    |= ((3 << 2) | (3 << 0)); // максимально быcтрый фронт

 //Параметры делителя при частоте = 80 Мгц и скорости = 115200
MDR_UART2->IBRD = 43;   // целая часть делителя скорости
MDR_UART2->FBRD = 26;   // дробная часть делителя скорости

MDR_UART2->LCR_H = ((0 << 1) // работа без провеки четности 
                   |(0 << 2) // бит четности отключен
                   |(0 << 3) // кол-во стоповых бит = 1
                   |(0 << 4) // включение буфера FIFO, 0 - выкл
                   |(3 << 5) // размер кадра - 8 бит
                   |(0 << 7)); // передача бита четности запрещена

MDR_UART2->IMSC = (1 << 4); // прерывание от приемника
MDR_UART2->CR = ((1 << 8)|(1 << 9) | 1); 
}
  
  void Uart1_send_hex(U8 hex_data){
	  
      // пока Буфер   FIFO   передатчика   заполнен...  
	while(MDR_UART1->FR & (1<<5)) { }; // ждем готовности UART1;

    MDR_UART1->DR = hex_data;
  
	}
  
  void Uart2_send_hex(U8 hex_data){
	  
      // пока Буфер   FIFO   передатчика   заполнен...  
	while(MDR_UART2->FR & (1<<5)) { }; // ждем готовности UART2;

    MDR_UART2->DR = hex_data;
  
	}
	  
  void Uart1_CR_LF_send (void){
	  
        Uart1_send_hex(0x0A);
	Uart1_send_hex(0x0D);
	
	}
  
  void Uart2_CR_LF_send (void){
	  
        Uart2_send_hex(0x0A);
	Uart2_send_hex(0x0D);
	
	}

  void Uart1_num_send(int32_t data){
	  
  unsigned char temp[10],count=0;
  if (data<0) 
  {
    data=-data;
    Uart1_send_hex('-');
  }     
  if (data)
  {
    while (data)
    {
      temp[count++]=data%10+'0';
      data/=10;                 
    }                           
    while (count)           
      Uart1_send_hex(temp[--count]);          
  }
  else Uart1_send_hex('0');           
}

  void Uart2_num_send(int32_t data){
	  
  unsigned char temp[10],count=0;
  if (data<0) 
  {
    data=-data;
    Uart2_send_hex('-');
  }     
  if (data)
  {
    while (data)
    {
      temp[count++]=data%10+'0';
      data/=10;                 
    }                           
    while (count)           
      Uart2_send_hex(temp[--count]);          
  }
  else Uart2_send_hex('0');           
}

  void Uart1_send_text(unsigned char *s){
  while (*s != 0)
    Uart1_send_hex(*s++);
}

  void Uart2_send_text(unsigned char *s){
  while (*s != 0)
    Uart2_send_hex(*s++);
}

/*=========================================================================== */

/*=========================================================================== */
// Interupts
	
__irq void UART1_IRQHandler( void )
 //функция обработки прерывания irq UART1
{
  /// прерывание возникает при поступлении 1 байта на UART1
        
        // перенаправление данных от оптического приемника в RS485
        RS485_TX_EN;                    // разрешение передатчика
        MDR_TIMER3->CNTRL |= 1;         // Запуск Т3, начало отсчета времени разрешения передатчика
        MDR_UART2->DR  = MDR_UART1->DR; 
        //Status_LED_OFF; // гасим статусный светодиод для индикации активности RS485
        MDR_UART1->ICR  = 1<<4; // сброс прерывания от приемника  
        MDR_TIMER3->CNT = 0;     // установка знач. счетчика на 0
}

__irq void UART2_IRQHandler( void )
 //функция обработки прерывания irq UART2
{
  /// прерывание возникает при поступлении 1 байта на UART2
        
        // перенаправление данных от RS485 в оптический передатчик
  
        MDR_UART1->DR  = MDR_UART2->DR; 
       
        Status_LED_OFF; // гасим статусный светодиод для индикации активности RS485
        MDR_UART2->ICR  = 1<<4; // сброс прерывания от приемника  
}


__irq void Timer1_IRQHandler(void) 

{    

     MDR_TIMER1->CNT = 0;                  // установка знач. счетчика на 0
     MDR_TIMER1->STATUS = 0;        // сброс статуса прерывания по падяющ. фронта на канале 3 Т1 
}

__irq void Timer3_IRQHandler(void) 
{ 
  RS485_TX_DIS;            // запрет передатчика
  MDR_TIMER3->CNTRL &= ~1;
  MDR_TIMER3->STATUS = 0;  // сброс статуса прерывания по \_ на канале 1 Т3  
}

/*=========================================================================== */
/*=========================================================================== */

  void MCU_init (void) {
	  
 	 OSC_init();
	 SysTickTimer_Init();
 	 GPIO_init();  
	 //timer1_init();
         timer3_init();
         
         MDR_RST_CLK->PER_CLOCK |= (1 << 7) | (1 << 6);    // вкл. тактирование UART1 и UART2
         MDR_RST_CLK->UART_CLOCK = (0                      // установка делителя для UART1 = 1
                          |(0 << 8)                        // установка делителя для UART2 = 1
                          |(1 << 24)                       // разрешение тактовой частоты UART1
                          |(1 << 25));                     // разрешение тактовой частоты UART2 
         
         Uart1_init();           // UART1 - оптический приемопередатчик
         Uart2_init();           // UART2 - rs485

	}

/*=========================================================================== */
// MAIN    
        
 int main()
{     
 U32 ADC_V = 0;
 
 MCU_init();	// иницализация систем тактирования, портов, SPI и UART  
 MCU_ADC_init();
 
 RS485_RX_EN; // вкл. приемника   RS485
 RS485_TX_DIS; // вкл. передатчика RS485
 
 //NVIC_EnableIRQ(Timer1_IRQn); // Разрешение прерывания для T1 - внешние стробы
 NVIC_EnableIRQ(Timer3_IRQn); // Разрешение прерывания для T3 - П-регулятор
 NVIC_EnableIRQ(UART1_IRQn);  // Разрешение прерывания для UART1, Оптика -> RS485
 NVIC_EnableIRQ(UART2_IRQn);  // Разрешение прерывания для UART2, RS485 -> Оптика 
 __enable_irq();	      // Enable Interrupts global
 //MDR_TIMER1->CNTRL |= 1;    // Запуск Т1
 

 Error_LED_OFF;
 Status_LED_OFF;
 
 while(1)
  {
    //ADC_V = Get_ADC_ch_voltage(7); // канал 7 АЦП - контроль U пит. = 24 В
    delay_ms(35);
    Status_LED_ON; 
    
    
    // 24 В ~ 3.118 В через делитель на вх. 7 АЦП.
    // 22 В ~ 2.86  В
    // 25 В ~ 3.247 В
    //if((ADC_V > 3600) | (ADC_V < 2000))
    //{
    //  Status_LED_OFF;
    //  delay_us(100);
   //   Error_LED_ON;
   // }
   // else {Error_LED_OFF; Status_LED_ON;}
    
//    if(need2send) // измерение выходного напряжения и отсылка на ПК
//    { RS485_TX_EN;
//      Uart2_send_text("U: ");
//      Uart2_send_hex(rx_data);//ADC_V);          // отсылка результатов измерений на ПК
//      Uart2_CR_LF_send();
//      need2send = 0;                 // сброс флага запроса данных
//     
//      Status_LED_OFF; 
//      RS485_TX_DIS;   
//      
//    } // if   
    
  } // while  
} // main
