#include "1986be91t1.h" 
#include <stdint.h>

static void MCU_init (){

  RST_CLK->PER_CLOCK = 0xFFFFFFFF;                    // разрешили работу всей перефирии
  RST_CLK->HS_CONTROL = 0x01;                         // вкл. HSE осцилятора
  while ((RST_CLK->CLOCK_STATUS & (1 << 2)) == 0x00); // ждем пока HSE выйдет в рабочий режим
  RST_CLK->PLL_CONTROL = ((1 << 2) | (9 << 8));       // вкл. PLL | коэф. умножения = 10
  while((RST_CLK->CLOCK_STATUS & 0x02) != 0x02);      // ждем когда PLL выйдет в раб. режим
  RST_CLK->CPU_CLOCK  = (2                            // источник для CPU_C1
						   |(1 << 2)                      // источник для CPU_C2
						   |(0 << 4)                      // предделитель для CPU_C3
						   |(1 << 8));                    // источник для HCLK
}




int main()
{  
  MCU_init();
  PORTD->OE = 0xffff;          // порт D на выход
  PORTD->FUNC = 0x0000;        // функция - порт 
  PORTD->ANALOG  = 0xffff;     // режим потра - цифровой
  PORTD->PWR     = 0xFFFFFFFF; //  максимально быстрый фронт ( порядка 10 нс)
  
  PORTC->OE = 0x0000;          // порт C на вход
  PORTC->FUNC = 0x0000;        // функция - порт 777
  PORTC->ANALOG  = 0xffff;     // режим потра - цифровой
  PORTC->PWR     = 0x00000000; //  максимально быстрый фронт ( порядка 10 нс)
  
      uint16_t x;
  
      
  
  while(1){
  
    
    
    
    
    
    
    
    /*
    if (!(PORTC->RXTX & (1 << 10))){
    for(x=0;x<100000;x++){}
    if (!(PORTC->RXTX & (1 << 10))){
      PORTD->RXTX = 0xffff;
      for(x=0;x<100000;x++){}
   }
  }
      if ((PORTC->RXTX & (1 << 10))){
      
     PORTD->RXTX = 0x0000;
   }
    */
 }
}
