#define F_CPU 80000000

#include "MDR32Fx.h"
//#include "MDR32F9Qx_config.h"
#include "milkites_delay.h"
#include "milkites_spi.h"
#include "MT_12864B_LCD.h"

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
  
  MDR_PORTB->OE      = 0x0000;
  MDR_PORTB->FUNC    = 0x0000;          // функция - порт 
  MDR_PORTB->ANALOG  = 0xFFFF;          // режим потра - цифровой
  MDR_PORTB->PWR     = 0xFFFFFFFF;      // максимально быстрый фронт   
  
  MDR_PORTD->OE = 0x00ca;               // порт D на вход, PD2 - ADC_CH2, PD4 - ADC_CH4, PD5 - ADC_CH5
  MDR_PORTD->FUNC = 0x0000;             // функция - порт 
  MDR_PORTD->ANALOG  = 0xffcb;          // режим потра - цифровой, но PD2 - ADC_CH2, PD4 - ADC_CH4, PD5 - ADC_CH5
  MDR_PORTD->PWR     = 0xFFFFFFFF;      // максимально быстрый фронт ( порядка 10 нс)
  //MDR_PORTD->PD =     ((0 << (2 << 16))); //режим работы входа 2 = АЦП
  
  MDR_PORTE->OE      = 0xFFFF;
  MDR_PORTE->FUNC    = 0x0000;          // функция - порт 
  MDR_PORTE->ANALOG  = 0xFFFF;          // режим потра - цифровой
  MDR_PORTE->PWR     = 0xFFFFFFFF;      // максимально быстрый фронт 
}

/*=========================================================================== */

int main()
{
	int x = 0;
	int counter = 0;
	
	OSC_init();
	GPIO_init();
	SysTickTimer_init();
	
	MDR32_SSP1_init();    // инициализация модуля SSP1

  LCD_init(); 					// иницализация дисплея MT12864B
  LCD_clear(); 	        // очистка дисплея
  LCD_set_cursor(0);    // уст. курсора в 0ую стр. 

while(1)
{
	MDR_PORTA->RXTX = 1<<x;
	delay_ms(200);
	x++;
	if(x > 7) x = 0;
	
	LCD_set_cursor(3);
	LCD_print("Всем привет! сработало!!");
  LCD_wr_num(counter);
  counter++;
  delay_ms(100);
}
}

