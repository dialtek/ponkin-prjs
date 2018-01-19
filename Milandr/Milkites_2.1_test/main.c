#include "MDR32Fx.h"
// HCLK frequency
#define F_CPU  80000000 

#include "milkites_delay.h"
#include "milkites_spi.h"
#include "MT_12864B_LCD.h"
#include "milkites_uart.h"

#define right_button !(MDR_PORTB->RXTX & (0x0400))
#define left_button  !(MDR_PORTB->RXTX & (0x0200))
#define down_button  !(MDR_PORTD->RXTX & (0x0010))
#define up_button    !(MDR_PORTB->RXTX & (0x0100))

uint16_t sec_counter = 0; // счетчик секунд

void OSC_init(void) {   // функция инициализации системы тактирования МК
  
  // вкл. PLL | коэф. умножения = 7
  MDR_RST_CLK->PLL_CONTROL = ((1 << 2) | (7 << 8)); 
  // ждем когда PLL выйдет в раб. режим	 
  while((MDR_RST_CLK->CLOCK_STATUS & 0x02) != 0x02);      
  
  MDR_RST_CLK->HS_CONTROL = 0x01;                         // вкл. осцилятор HSE
  while ((MDR_RST_CLK->CLOCK_STATUS & (1 << 2)) == 0x00); // ждем готовности
  
  MDR_RST_CLK->CPU_CLOCK  =(2                // источник для CPU_C1
                            |(1 << 2)        // источник для CPU_C2
                            |(1 << 4)        // предделитель для CPU_C3
                            |(1 << 8));      // источник для HCLK  
 MDR_RST_CLK->PER_CLOCK = 0xFFFFFFFF; // вкл. тактирование всей периферии
 // HCLK = 80 МГц	  
  }

void GPIO_init (void) { // функция инициализации портов ввода/вывода
  
  MDR_PORTA->OE      = 0xFFFF;
  MDR_PORTA->FUNC    = 0x0000;          // функция - порт 
  MDR_PORTA->ANALOG  = 0xFFFF;          // режим потра - цифровой
  MDR_PORTA->PWR     = 0xFFFFFFFF;      // максимально быстрый фронт 

  MDR_PORTC->OE      = 0xFFFF;
  MDR_PORTC->FUNC    = 0x0000;          // функция - порт 
  MDR_PORTC->ANALOG  = 0xFFFF;          // режим потра - цифровой
  MDR_PORTC->PWR     = 0xFFFFFFFF;      // максимально быстрый фронт 

  MDR_PORTF->OE      = 0xFFFF;          // порт F на выход, модуль SSP1 
  MDR_PORTF->FUNC = (2 << 6) |		// режим  пинов 1, 2, 3, 4 порта 
                    (2 << 4) |          // - альтернативный, задействован  SSP1
                    (2 << 2) |
                    (2 << 0);
  MDR_PORTF->ANALOG  = 0xFFFF;          // режим потра - цифровой
  MDR_PORTF->PWR     = 0xFFFFFFFF;      // максимально быстрый фронт
  
  MDR_PORTB->OE      = 0x0400;
  MDR_PORTB->FUNC    = 0x0000;          // функция - порт 
  MDR_PORTB->ANALOG  = 0xFFFF;          // режим потра - цифровой
  MDR_PORTB->PWR     = 0xFFFFFFFF;      // максимально быстрый фронт   
  
  MDR_PORTD->OE = 0x00ca;               // порт D на вход, PD2 - ADC_CH2, PD4 - ADC_CH4, PD5 - ADC_CH5
  MDR_PORTD->FUNC = 0x0000;             // функция - порт 
  MDR_PORTD->ANALOG  = 0xffcb;          // режим потра - цифровой, но PD2 - ADC_CH2, PD4 - ADC_CH4, PD5 - ADC_CH5
  MDR_PORTD->PWR     = 0xFFFFFFFF;      // максимально быстрый фронт ( порядка 10 нс)
  MDR_PORTD->PD =     ((0 << (2 << 16))); //режим работы входа 2 = АЦП
  
  MDR_PORTE->OE      = 0xFFF3;          // PE2 - Comp in1, PE3 - Comp in2
  MDR_PORTE->FUNC    = 0x0000;          // функция - порт 
  MDR_PORTE->PWR     = 0xFFFFFFFF;      // максимально быстрый фронт 
  MDR_PORTE->ANALOG  = 0xfff2;          // режим потра - цифровой, PE0 - DAC2 out, PE2 - Comp in1, PE3 - Comp in2
}

/*=========================================================================== */


/*
void Timer1_init(void) {// функция инициализации Таймера 1

 // прерывание каждую секунду при HCLK = 80 M
 
  // Тактирование блока Timer1 в регистре PER_CLOCK было разрешено в OSC_init() //
 
 MDR_RST_CLK->TIM_CLOCK  |= (1 << 24) | 0x03;	// разрешение тактирования Timer1, TIM1_CLK = HCLK/8 
 MDR_TIMER1->CNTRL = 0x00000000;        	// режим счета вверх для счетчика, 
						// начальное значение - число из регистра CNT
 MDR_TIMER1->PSG   = 99;               	        // Предделитель частоты = 50 000
 MDR_TIMER1->ARR   = 199;                	// Основание счета = 200, 200 * 5 мс = 1 сек 
 MDR_TIMER1->CNT   = 0;       	                // начальное значение счетчика 
 MDR_TIMER1->IE    = 0x00000002;         	// Разрешение генерировать прерывание при CNT=ARR
}

void Timer1_IRQHandler(void) // обработчик прерывания от Таймера 1
{   
    // прерывание каждую секунду
 
    sec_counter++;

    MDR_TIMER1->CNT = 0;                // установка значения счетчика в ноль
    MDR_TIMER1->STATUS = 0;             // сброс статуса прерывания от Таймера 1
    NVIC_ClearPendingIRQ(Timer1_IRQn);  // сброс флага прерывания
}
//================================================================= //
int main() {

  OSC_init();           // инициализация системы тактирования МК
  SysTickTimer_Init();  // инициализация системного таймера
  GPIO_init();          // инициализация портов ввода/вывода
  MDR32_SSP1_init();    // инициализация модуля SSP1
  Uart2_init();
  
  LCD_init(); 		    // иницализация дисплея MT12864B
  LCD_clear(); 			// очистка дисплея
  
  //Timer1_init();				// инициализация Таймера 1
  //NVIC_EnableIRQ(Timer1_IRQn);  // разрешение прерывания от Таймера 1
  //__enable_irq();               // глобальное разрешение прерываний от Таймера 1
  //MDR_TIMER1->CNTRL = 1;        // запуск счетчика Таймера 1
  int x = 0;
  while(1)
  { 
//    LCD_set_cursor(0); 
//    LCD_print("MDR_TIMER1->CNT=");
//    LCD_wr_num(MDR_TIMER1->CNT);
//    
//    LCD_set_cursor(2);
//    LCD_print("Счетчик секунд: ");
//    LCD_wr_num(sec_counter);  
    x++;
    if(x > 9) x = 0;
    Uart_send_text("x-000"); Uart_send_num(x); Uart_CR_LF_send();
    delay_ms(25);
        Uart_send_text("y0000"); Uart_send_num(x); Uart_CR_LF_send();
    delay_ms(25);
        Uart_send_text("z-000"); Uart_send_num(x); Uart_CR_LF_send();
    delay_ms(25);
  } // while
} // main 
//================================================================= //
*/


uint16_t MCU_ADC_aver_param = 10;
uint8_t  MCU_current_ADC_channel = 4;

#define ADC_Vref 3.295	// измеренное вольтметром напряжение питания МК



// ADC MCU
    void MCU_ADC_init(){

  //MDR_RST_CLK->PER_CLOCK |= (1 << 17); //тактирование АЦП
  
  MDR_ADC->ADC1_CFG = (1 //Включение АЦП  
  |(0 << 2)   	// источник синхросигнала
  |(1 << 3)   	// Выбор способа запуска АЦП - послед. 
  |(0 << 4)  	// номер канала преобразования - не важно, так как установим канал позже
  |(1 << 9)  	// переключение включено (перебираются каналы, выбранные в регистре выбора канала)
  |(0 << 10) 	// автоматический контроль уровней откл.
  |(0 << 11)  	// источник опорного - внутренний (VDD)
  |(4 << 12)  	// коэффициент деления частоты ADC_clk = HCLK/8 = 10 МГц
  |(0 << 16)  	//  работа двух АЦП одновременн откл.
  |(0 << 17)    //  TS_EN датчик температуры и источника опорного напряжения откл
  |(0 << 18)    // TS_BUF_EN усилитель для датчика температуры и источника опорного напряжения откл.
  |(0 << 19) 	// оцифровка датчика температуры откл./
  |(0 << 20));  // оцифровка источника опорного напряжения на 1.23 В откл
}

    void MCU_ADC_start_conv(void){
  
  	MDR_ADC->ADC1_CFG |= 1<<1;
  
}

    uint32_t MCU_ADC_read(void){
	  
	  // чтение АЦП, t выборки + t преобразования канала = 3.2 мкС при HCLK = 10М и предделителе АЦП = 1
	  //		     t выборки + t преобразования канала = 0.5 мкС при HCLK = 70М и предделителе АЦП = 1					
	  // вес младшего разряда АЦП = 3,3/4095 = 0,8 мВ
	  
	  uint32_t ADC_data = 0;
	  
  	  MCU_ADC_start_conv(); // начало преобразований данных
	  
	  //while(!(MDR_ADC->ADC1_STATUS) & (1<<2)) {} // ждем готовность 
          delay_us(20);
	  ADC_data = MDR_ADC->ADC1_RESULT;			 // читаем
	  
	  MCU_current_ADC_channel = ADC_data << 11;  //вытаскиваем номер 
	  MCU_current_ADC_channel = MCU_current_ADC_channel >> 27;  //канала чьи измерения
	  
	  ADC_data = ADC_data << 20;    // отбрасываем инфу о 
	  ADC_data = ADC_data >> 20;    // канале измерений
	  
	  return ADC_data;
}
					   
    void MCU_ADC_set_ch(uint8_t channel){
	  
	if (channel > 16) return;
	
	MDR_ADC->ADC1_CHSEL = 1 << channel; 
	
	
}

    uint32_t MCU_ADC_Rd_average(uint16_t AverValue){
	  
	  // чтение АЦП, t выборки + t преобразования канала = 3.2 мкС при HCLK = 10М и предделителе АЦП = 1
	  // t выборки + t преобразования канала = 0.5 мкС при HCLK = 70М и предделителе АЦП = 1	
	  // усреднение результатов преобразований АЦП
	  
	  uint32_t Aver_ADC_data = 0;
	  
	  for(int i = 0; i < AverValue; i++ )
	  {
	   Aver_ADC_data += MCU_ADC_read();
	  }
  
	  Aver_ADC_data = Aver_ADC_data/AverValue; 
	  
	  return Aver_ADC_data;
}

    uint32_t Get_ADC_ch_voltage(uint8_t ADC_channel){
	  // чтение усредненного результата преобраз. канала АЦП, преобразование в мВ
	  
	  uint32_t ADC_rd_data = 0;
 	  uint32_t ADC_meas_voltage = 0;
	  
	  MCU_ADC_set_ch(ADC_channel);	// установка канала АЦП
	  ADC_rd_data = MCU_ADC_Rd_average(MCU_ADC_aver_param);		// читаем среднее значение отсчетов АЦП
	  ADC_meas_voltage = (int)(ADC_Vref*ADC_rd_data*1000)/4096;	// преобразуем в волты  
	  return ADC_meas_voltage; 

}


/*=========================================================================== */
// DAC
  void MCU_DAC2_init (void)
  {
    
    MDR_DAC->CFG = (0<<4) | // DAC1 DAC2 асинхронны
                   (1<<3) | // DAC2 enabled  
                   (0<<2) | // DAC1 disabled
                   (0<<1) | // DAC2 ref - AUcc voltage
                   (0<<1);  // DAC1 ref - AUcc voltage
  }
/*=========================================================================== */
// comparator
  void comparator_init()
  {
    
    MDR_RST_CLK->PER_CLOCK |= (1 << 19); //тактирование компаратора
    
    MDR_COMP->CFG = (1  // вкл. компаратор   
        |(1 << 1)   	// источник CVREF работает в нижнем диапазоне 
        |(0 << 2)   	// источник CVREF работает в границах AVdd AGND;
        |(0 << 3)  	// CVREF не разрешен;  
        |(0 << 4)  	// Биты выбора сигнал управления мультиплексора выбора CVREF. Формирование внутренней шкалы 
        |(0 << 8) 	// на «+» компаратора сигнал подается с IN1; 
        |(0 << 9)  	// на «-» компаратора сигнал подается с IN2; 
        |(0 << 11)  	// нет инверсии выхода компаратора 
        |(0 << 12)  	// Сигнал готовности аналогового компаратора при включении:
        |(1 << 13));     // Флаг разрешения генерации прерывания по событию Rst_lch: разрешено прерывание  
  }
  
int main() {
 
  uint32_t V = 0;
  
  OSC_init();           // инициализация системы тактирования МК
  SysTickTimer_Init();  // инициализация системного таймера
  GPIO_init();          // инициализация портов ввода/вывода
  MDR32_SSP1_init();    // инициализация модуля SSP1
  
  MCU_ADC_init();
  MCU_DAC2_init();
  Uart2_init();  
  comparator_init();
  LCD_init(); 		// иницализация дисплея MT12864B
  LCD_clear(); 	        // очистка дисплея
  LCD_set_cursor(0);    // уст. курсора в 0ую стр. 
  U32 result = 0;
  
  MDR_DAC->DAC2_DATA = 0;
  U32 dac_data = 0;
   
  while(1)
  { 
   LCD_set_cursor(0);
   LCD_print("      МАКЕТ АЦП     "); 
   
   V = Get_ADC_ch_voltage(4);
   LCD_set_cursor(2);
   LCD_print("U вх = ");
   LCD_wr_num(V);
   LCD_print(" мВ     ");
 
   // DAC
   MDR_DAC->DAC2_DATA = dac_data;//(U32) (V/0.805664);
   // comparator result
   LCD_set_cursor(4);
   //LCD_print("result = ");
   while(! (MDR_COMP->CFG & 1<<12)) {}
   //LCD_wr_num(MDR_COMP->RESULT & 0x0001);
   result = MDR_COMP->RESULT_LATCH & 0x0001;
   LCD_print("Вых. компар. = ");
   LCD_wr_num(result);
   LCD_print("  ");
   
   if(!result) 
   {
     dac_data++;
     MDR_PORTC->RXTX = ~ MDR_PORTC->RXTX;
   }

   if(dac_data == 4084) dac_data = 0;
   
   LCD_set_cursor(6);
   LCD_print("U изм. = ");;
   LCD_wr_num((U32)(dac_data*0.805664));
   LCD_print(" мВ  ");
   
   while(MDR_PORTB->RXTX & 1<<5)
   { // светодиод сенсорной кнопки
    MDR_PORTA->RXTX |= 1;
    dac_data = 0;
    MDR_DAC->DAC2_DATA = dac_data;
    delay_ms(100);
    MDR_PORTA->RXTX &= ~1; 
   }

   while (!(MDR_PORTB->RXTX & 1<<4))
   {
     for(uint32_t x = 0; x < 100; x++  )
   {
      MDR_PORTC->RXTX = 1;
      delay_us((uint16_t)V/2);
      MDR_PORTC->RXTX = 0;
      delay_us((uint16_t)V/2);
   }
   
   }
    //delay_ms(1);

  }
}
    



    
//    LCD_print("Uart test");			// вывод текста дисплея
//    LCD_set_cursor(1); 				// установка курсора на вторую строку дисплея
//    LCD_print("Счетчик секунд: ");	// вывод текста на дисплей
//    LCD_wr_num(sec_counter);		// вывод числа на дисплей
//    

    
    
    
//    if(need2send == 1) // запрос с ПК получен
//    {
//      Uart_send_text(" Ok! Вы передали: ");
//      Uart_CR_LF_send();
//      for(uint8_t i = 0; i < 8; i++)
//        {
//          Uart_send_hex(rx_data[i]);
//        }
//		// отправка символов возврата коретки и перевода строки на ПК
//        Uart_CR_LF_send();		        
//      
//      need2send = 0;				// сброс флага отсылки данных на ПК
//    }
//    sec_counter++;					// инкремент счетчика секунд
//    delay_ms(1000);					// задержка 1000 мс
    
 // } // while
//} // main 
/*================================================================= */



//    LCD_print("   Вас приветствует ");
    
//    LCD_print("   отладочная плата");
//    LCD_set_cursor(3);
//    LCD_print(">>>>>> МилКиТЭС <<<<<<");
//    LCD_set_cursor(5);
//    LCD_print("Hello World! Rus Eng");
//    
//    LCD_set_cursor(7);
//    LCD_print("Счетчик секунд: "); 
//    LCD_wr_num(counter);
//    
//    counter++;
//    if(counter > 10000) counter = 0;
//    delay_ms(1000);
  /*
// пример чтения T
  int Temper = 0; // объявляем переменную для сохранения Т
  
  // 1-wire
#define One_wire_port_dir MDR_PORTD->OE     // регистр направленности порта 1-wire
#define One_wire_port 	  MDR_PORTD->RXTX   // регистр данных порта 1-wire
#define One_wire_pin_num 2  // PD2			// номер пина 1 - wire

#include "mdr_1_wire.h"     // подключение библиотеки 1 - wire 

#define right_b (!(MDR_PORTB->RXTX & (1<<10))) 
#define up_b    (!(MDR_PORTB->RXTX & (1<<8)))
#define left_b  (!(MDR_PORTB->RXTX & (1<<9)))
#define down_b  (!(MDR_PORTD->RXTX & (1<<4)))
  
  
Temper = ds18b20_rd_t();	 

LCD_set_cursor(1);  
         LCD_print("Т = ");       
         if(Temper<0)
         {
              LCD_print("-");
              Temper = Temper * -1;
         }
         else LCD_print("+");
         
int a = Temper/10000;
int b = (Temper-(a*10000))/1000;
int c = (Temper-(a*10000)-(b*1000))/100;

	 LCD_Wr_num(a,1);
	 LCD_Wr_num(b,1);
	 LCD_print(".");
	 LCD_Wr_num(c,1);
         LCD_print(" C");
         
         */