#include "MDR32Fx.h"
// HCLK frequency
#define F_CPU  80000000 

#include "milkites_delay.h"
#include "milkites_spi.h"
#include "MT_12864B_LCD.h"
#include "milkites_uart.h"

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
  }

/*=========================================================================== */
int main() {
  
  int sec_counter = 0;  // объявление переменной счетчика секунд
  
  OSC_init();           // инициализация системы тактирования МК
  SysTickTimer_init();  // инициализация системного таймера
  GPIO_init();          // инициализация портов ввода/вывода
  MDR32_SSP1_init();    // инициализация модуля SSP1
  
  Uart2_init();         // инициализация модуля UART2
  
  LCD_init(); 		    // иницализация дисплея MT12864B
  LCD_clear(); 			// очистка дисплея
  
  while(1)
  { 
    LCD_set_cursor(0); 				// установка курсора на первую строку дисплея
    LCD_print("Uart test");			// вывод текста дисплея
    LCD_set_cursor(2); 				// установка курсора на вторую строку дисплея
    LCD_print("Счетчик секунд: ");	// вывод текста на дисплей
    LCD_wr_num(sec_counter);		// вывод числа на дисплей
    
    Uart_send_num(sec_counter);		// отправка переменной счетчика секунд на ПК
    Uart_CR_LF_send();				// отправка символов возврата каретки и перевода строки на ПК
    
    sec_counter++;					// инкремент счетчика секунд
    delay_ms(1000);					// задержка 1000 мс  
  } // while
} // main 
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