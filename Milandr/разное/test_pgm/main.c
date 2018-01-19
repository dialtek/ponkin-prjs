#include "MDR32Fx.h"

int main()
{
  
//---CLK-----------------------------------------------------------------------------------------------------
  MDR_RST_CLK->PER_CLOCK = 0xFFFFFFFF;                    // вкл. тактирование всей перефирии
  MDR_RST_CLK->HS_CONTROL = 0x01;                         // вкл. HSE осцилятор
  while ((MDR_RST_CLK->CLOCK_STATUS & (1 << 2)) == 0x00); // ждем пока HSE выйдет в рабочий режим
  
  
  MDR_RST_CLK->PLL_CONTROL = ((1 << 2) | (0 << 8)); 	  // вкл. PLL | коэф. умножения = 1
  					
  while((MDR_RST_CLK->CLOCK_STATUS & 0x02) != 0x02);      // ждем когда PLL выйдет в раб. режим

  MDR_RST_CLK->CPU_CLOCK  = (2                            // источник для CPU_C1
						   |(1 << 2)                      // источник для CPU_C2
						   |(1 << 4)                      // предделитель для CPU_C3
						   //|(1 << 4)                    // предделитель для CPU_C3
						   |(1 << 8));                    // источник для HCLK
 
  MDR_PORTC->OE = 0xffff;               // порт A на выход
  MDR_PORTC->FUNC = 0x0000;             // функция - порт 
  MDR_PORTC->ANALOG  = 0xffff;          // режим потра - цифровой
  MDR_PORTC->PWR     = 0xFFFFFFFF;      // максимально быстрый фронт ( порядка 10 нс)
  
  while (1) {
	
	MDR_PORTC->RXTX = 0xFFFF;
  
  }

}
