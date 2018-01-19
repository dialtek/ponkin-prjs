/// Рабочий код ,программа для микроконтроллера  
/// устройство - блок формирования потенциальных барьеров структуры дрейфа КРИОН-6Т

#include "MDR32Fx.h"
#define F_CPU 80000000

#define U8  uint8_t
#define U16 uint16_t 
#define S16 int16_t 
#define U32 uint32_t
#define S32 int32_t

#include "mdr_delay.h"

// сигналы запуска и остановки блока ресинхронизации данных в ПЛИС
#define HV_SUPPLY_ON  	MDR_PORTC->RXTX |=  1   
#define HV_SUPPLY_OFF   MDR_PORTC->RXTX &= ~1

#define SYNC_LED_ON  	MDR_PORTE->RXTX |=  1<<3 
#define SYNC_LED_OFF  	MDR_PORTE->RXTX &= ~(1<<3) 

#define RS485_RX_EN     MDR_PORTB->RXTX |=  1<<9   // вкл.  приемник RS485   _/
#define RS485_RX_DIS    MDR_PORTB->RXTX &= ~(1<<9) // выкл. приемник RS485   
#define RS485_TX_EN     MDR_PORTB->RXTX &= ~(1<<10)// вкл.  передатчик RS485 \_
#define RS485_TX_DIS    MDR_PORTB->RXTX |=  1<<10  // выкл. передатчик RS485 

// сигнал готовности данных АЦП для чтения 
#define RXFE                1<<4                    // равен 1 если пуст буфер FIFO приемника 
#define FIFO_has_byte       !(MDR_UART1->FR & RXFE)
#define CH1_CCR_CAP_EVENT   (1<<13)                 // Событие ?переднего? фронта на входе CAP каналов таймера 
                                                    // Бит 7 – третий канал
#define ADC_Vref            3.3		    // измеренное вольтметром напряжение питания МК

#define Status_LED_ON     MDR_PORTA->RXTX |= 1 << 3 
#define Status_LED_OFF    MDR_PORTA->RXTX &= ~(1 << 3)
#define Error_LED_ON      MDR_PORTA->RXTX |= 1 << 4 
#define Error_LED_OFF     MDR_PORTA->RXTX &= ~(1 << 4)

#define du 1.12 // коэффициент для приведения отсчетов АЦП к отсчетам ЦАП


  U8 need2send = 0;    // флаг запроса на выдачу данных по UART	
  U8 need2update = 0; 
  U8 need2setDAC = 0;  // флаг обновления напряжения DAC

  U32 MCU_current_ADC_channel = 0;
  U16 MCU_ADC_aver_param = 1000;    // величина усренднения данных АЦП
  S32 DAC_code = 0;                // код DAC - управление выходным напряжением 
  S32 ADC_code = 0;                // отсчеты АЦП напряжения ОС HV-части
  float k = 0;          // пропорциональный коэффициент П-регулятора
  S32 error = 0;        // ошибка показаний АЦП и кода ЦАП 
  S32 mDAC_code = 0;    // скорректированное значение кода ЦАП
  S16 ADC_zero_lvl = 0; // сдвиг 0 АЦП 
  
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
  MDR_PORTB->OE = 0xFFFE;               // порт B на выход, PB0 - вход внешней синхронизации
  MDR_PORTB->FUNC = 0x0002;             // функция - порт, PB0 - альтернативная функция
  MDR_PORTB->ANALOG  = 0xffff;          // режим потра - цифровой
  MDR_PORTB->PWR     = 0xFFFFFFFF;      // максимально быстрый фронт ( порядка 10 нс)
  //---------------------------------------------------------------------------//  
  MDR_PORTC->OE     = 0xffff;                    
  MDR_PORTC->FUNC   = 0x0000;                
  MDR_PORTC->ANALOG = 0xFFFF;      
  MDR_PORTC->PWR    = 0xFFFFFFFF;       // максимально быстрый фронт
  //---------------------------------------------------------------------------//
  MDR_PORTD->OE = 0x00ca;               // порт D на вход, PD2 - ADC_CH2, PD4 - ADC_CH4, PD5 - ADC_CH5
  MDR_PORTD->FUNC = 0x0000;             // функция - порт 
  MDR_PORTD->ANALOG  = 0xffcb;          // режим потра - цифровой, но PD2 - ADC_CH2, PD4 - ADC_CH4, PD5 - ADC_CH5
  MDR_PORTD->PWR     = 0xFFFFFFFF;      // максимально быстрый фронт ( порядка 10 нс)
  MDR_PORTD->PD =     ((0 << (2 << 16))); //режим работы входа 2 = АЦП
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
          
  // настройка таймера для прерывания каждые 100 мкс
          
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
	  ADC_meas_voltage = (U32)((ADC_Vref*ADC_rd_data*1000)/4096);	// преобразуем в волты  
	  return ADC_meas_voltage; 

}
/*=========================================================================== */

/*=========================================================================== */
// UART
  void Uart_init (void){
//UART	  
  MDR_RST_CLK->PER_CLOCK |= (1UL << 22); //тактирование порта B
  MDR_PORTB->FUNC |= ((2 << 5*2) | (2 << 6*2)); //режим работы порта
  MDR_PORTB->ANALOG |= ((1 << 5) | (1 << 6)); //цифровой
  MDR_PORTB->PWR |= ((3 << 5*2) | (3 << 6*2)); //максимально быcтрый

  MDR_RST_CLK->PER_CLOCK |= (1UL << 6); //тактирование UART1
  MDR_RST_CLK->UART_CLOCK = (4 /*установка делителя для UART1 = */
  |(0 << 8) /*установка делителя для UART2 = undefined*/
  |(1 << 24) /*разрешение тактовой частоты UART1*/
  |(0 << 25)); /*разрешение тактовой частоты UART2*/ 
  
    //Параметры делителя при частоте = 5000000Гц и скорости = 115200
MDR_UART1->IBRD = 0x2; 					// целая часть делителя скорости
MDR_UART1->FBRD = 0x2e; 				// дробная часть делителя скорости
MDR_UART1->LCR_H = ((0 << 1) 				// разрешение проверки четности
  |(0 << 2) 						// четность/нечетность
  |(0 << 3) 						// стоп-бит
  |(1 << 4) 						// вкл. буфера FIFO приемника и передатчика 12 бит, глубину 16 слов
  |(3 << 5) 						// длина слова = 8 бит
  |(0 << 7)); 						// передача бита четности

//MDR_UART1->IMSC = 1 << 4;                // RXIM разрешение прерывания от приемника UARTRXINTR. 1 – установлена;   
MDR_UART1->IMSC = (1 << 10) | (1<<4 );     // Маскированное  состояние  прерывания  по  переполнению  буфера UARTOEINTR 
MDR_UART1->IFLS = 1<<4;                    // разрешение прерывание по залолн. 1/2 буфера фифо

MDR_UART1->CR = ((1 << 8)|(1 << 9)|1);     // передачик и приемник разрешен, 
}
	
  void Uart_send_hex(U8 hex_data){
	  
      // пока Буфер   FIFO   передатчика   заполнен...  
	while(MDR_UART1->FR & (1<<5)) { }; // ждем готовности UART1;

    MDR_UART1->DR = hex_data;
  
	}
	  
  void Uart_CR_LF_send (void){
	  
        Uart_send_hex(0x0A);
	Uart_send_hex(0x0D);
	
	}

  void Uart_num_send(int32_t data){
	  
  unsigned char temp[10],count=0;
  if (data<0) 
  {
    data=-data;
    Uart_send_hex('-');
  }     
  if (data)
  {
    while (data)
    {
      temp[count++]=data%10+'0';
      data/=10;                 
    }                           
    while (count)           
      Uart_send_hex(temp[--count]);          
  }
  else Uart_send_hex('0');           
}

  void Uart_send_text(unsigned char *s){
  while (*s != 0)
    Uart_send_hex(*s++);
}

__irq void UART1_IRQHandler( void )
 //функция обработки прерывания irq UART
{
  /// прерывание возникает при поступлении 8 байт в буфер FIFO приемника UART !!
         // 12 бит. буфер FIFO, глубина 16 слов - 7…0 Принятые данные 
         U16 Rx_data[16];
         U8 rd_byte_cntr = 0;
         while(FIFO_has_byte)
         {
          Rx_data[rd_byte_cntr] = MDR_UART1->DR;
          Rx_data[rd_byte_cntr] &= 0x00ff; // избавляемся от четырех  бит  состояния 
          rd_byte_cntr++;
         }
         
         switch(Rx_data[0])      // нулевой байт - заголовок команды  
         {
              case 'U':          // команда запроса результата измерений АЦП МК
                need2send = 1;   // запрос получен, выставлен флаг отсылки на ПК
              break;
              //--
              case 'D':          // команда запроса результата измерений АЦП 1,2,3 
                //MDR_TIMER3->CNTRL &= ~1;; // Запрет прерывания для T3 для уст. новых значений
                DAC_code = (S32)((Rx_data[2]<<8) + Rx_data[1]);
                need2setDAC = 1; // команда получена, выставлен флаг установки новго знач. DAC
              break;

              //--
              default: 
                Uart_send_text("error"); // неизвестная команда
                Uart_CR_LF_send();   
          }// switch
         
         MDR_UART1->RSR_ECR = 0x00000000;  //сброс статуса заполнения FIFO
                                           // Сброс прерывания от приемника UARTRXINTR
         MDR_UART1->ICR  = 1<<4 | 1 << 10; // Сброс прерывания по переполнению буфера UARTOEINTR 
         /**/
}
/*=========================================================================== */

/*=========================================================================== */
// Interupts
	
__irq void Timer1_IRQHandler(void) 
//функция обработки прерывания irq Timer 1 - СТРОБЫ ВНЕШНЕЙ СИНХРОНИЗАЦИИ
{    
  U8 int_flag = MDR_TIMER1->STATUS; // сохр. флаги источников прерываний от Т1 
  
  //if(int_flag & CH1_CCR_CAP_EVENT) //обработка прерывания переднего фронта MDR_TIMER3->CH1    
  //{   
      Uart_num_send(int_flag);
      Uart_CR_LF_send();   
  //}

     MDR_TIMER1->CNT = 0;                  // установка знач. счетчика на 0
     MDR_TIMER1->STATUS = 0;        // сброс статуса прерывания по падяющ. фронта на канале 3 Т1 
}

__irq void Timer3_IRQHandler(void) 
{ 
  /// П-регулятор для ШИМ конроллера HV, прерывания каждые 100 мкс

  //if(DAC_code > 0)     // регулятор начинает работу при получении данных с ПК
  //{
    
    MCU_ADC_set_ch(5); // установка канала АЦП и измерения 
    ADC_code  = (S32)MCU_ADC_Rd_average(MCU_ADC_aver_param);     
    // звено П-регулятора, масштабируется ошибка
    error = (S32)(k*(DAC_code - ADC_code));  
    mDAC_code = DAC_code + error;          // учет ошибки
   
    if(mDAC_code > 4000) mDAC_code = 4000; // проверка на переполнение ЦАПа
    if(mDAC_code < 0) mDAC_code = 0;
    
    MDR_DAC->DAC2_DATA = (U32)mDAC_code;   // корректировка ошибки ЦАПом
  //}
  MDR_TIMER3->CNT = 0;     // установка знач. счетчика на 0
  MDR_TIMER3->STATUS = 0;  // сброс статуса прерывания по \_ на канале 1 Т3  
}

/*=========================================================================== */
// DAC
  void MCU_DAC2_init (void){
    
    MDR_DAC->CFG = (0<<4) | // DAC1 DAC2 асинхронны
                   (1<<3) | // DAC2 enabled  
                   (0<<2) | // DAC1 disabled
                   (0<<1) | // DAC2 ref - AUcc voltage
                   (0<<1);  // DAC1 ref - AUcc voltage
  }

/*=========================================================================== */
 
  void MCU_init (void) {
	  
 	 OSC_init();
	 SysTickTimer_Init();
 	 GPIO_init();  
	 timer1_init();
         timer3_init();
         Uart_init();           // UART1 - RS485
         MCU_DAC2_init();       // инициализация DAC2
  
	}

/*=========================================================================== */
// MAIN    
        
 int main()
{     
 U32 ADC_V = 0;
 float ADC_scaled_V = 0.0;
 
 //S32 ADCc_DACc_delta = 11; // разница м/у отсчетами ЦАП и АЦП. приведение их к соотвествию.
 MCU_init();	// иницализация систем тактирования, портов, SPI и UART  
 MCU_ADC_init();
 
 delay_ms(500);  // задержка для сброса импульса высокого при вкл. питания
 HV_SUPPLY_ON;   // вкл. питания каскада раскачивающего 3 кВ трансформатор 
 
 RS485_RX_EN; // вкл. приемника   RS485
 RS485_TX_EN; // вкл. передатчика RS485
 
 NVIC_EnableIRQ(Timer1_IRQn); // Разрешение прерывания для T1 - внешние стробы
 NVIC_EnableIRQ(Timer3_IRQn); // Разрешение прерывания для T3 - П-регулятор
 NVIC_EnableIRQ(UART1_IRQn);  // Разрешение прерывания для UART1
 __enable_irq();	      // Enable Interrupts global
 //MDR_TIMER1->CNTRL |= 1;    // Запуск Т1
 MDR_TIMER3->CNTRL |= 1;      // Запуск Т3 --
 MDR_DAC->DAC2_DATA = 0;      // сброс значения ЦАП
 
 
 while(1)
  {
    Status_LED_ON;
    
    if(need2setDAC) // действия при обновлении кода DAC2 с ПК
    {
   
      if(DAC_code > 4096) Uart_send_text("Error, your DAC code > 4096");
      else
      {
        k = 13; // значение пропорционильного коэффициента регулятора
        //MDR_DAC->DAC2_DATA = DAC_code;
        Uart_send_text("DAC=");         // ответ пользователю - подтвержение 
        Uart_num_send(DAC_code);        // получения команды
        Uart_CR_LF_send();              
      }     
      need2setDAC = 0;                  // сброс флага обновления кода ЦАПа
      
      Status_LED_OFF;
      delay_ms(10);
    }
    
    if(need2send) // измерение выходного напряжения и отсылка на ПК
    { 
      ADC_V = Get_ADC_ch_voltage(5);
      //ADC_scaled_V = ADC_V * du;
      Uart_CR_LF_send();
      Uart_send_text("U: ");
      Uart_num_send(ADC_V);//(ADC_scaled_V);          // отсылка результатов измерений на ПК
      Uart_CR_LF_send();
      need2send = 0;                        // сброс флага запроса данных
     
      Status_LED_OFF;   
      delay_ms(10);
      
    } // if   

  } // while  
} // main

/*
      /// ------------- Отладочная информация-----------------
      Uart_send_text("DAC code: ");
      Uart_num_send(DAC_code);
      Uart_CR_LF_send();
      
      Uart_send_text("ADC_counts: ");
      Uart_num_send(ADC_code);
      Uart_CR_LF_send();
      
      Uart_send_text("error: ");
      Uart_num_send(error);
      Uart_CR_LF_send();
      
      Uart_send_text("mDAC_code: ");
      Uart_num_send((U32)mDAC_code);
      Uart_CR_LF_send();
      /// ---------------------------------------------------
      Uart_CR_LF_send();

*/
