#include <Milandr\1986be9x.h>
      unsigned long x;
//#pragma vector=14
__irq void Timer1_IRQHandler( void )
//void Timer1_IRQHandler(void) //функция обработки прерывания irq
{
//void Timer1_IRQHandler(){

     PORTD->RXTX = 0x0000;
     for(x=0;x<3000000;x++){}
     TIMER1->CNT = 0x00000000;      // установка знач. счетчика на 0
     TIMER1->STATUS &= ~(1 << 1);   // сброс статуса прерывания от таймера 1
     NVIC_ClearPendingIRQ(Timer1_IRQn); // сброс флага прерывания от таймера 1
 
}

int main()
{
//---CLK-----------------------------------------------------------------------------------------------------
  RST_CLK->PER_CLOCK = 0xFFFFFFFF;                    // разрешили работу всей перефирии
  RST_CLK->HS_CONTROL = 0x01;                         // вкл. HSE осцилятора
  while ((RST_CLK->CLOCK_STATUS & (1 << 2)) == 0x00); // ждем пока HSE выйдет в рабочий режим
  RST_CLK->PLL_CONTROL = ((1 << 2) | (9 << 8));       // вкл. PLL | коэф. умножения = 10
  while((RST_CLK->CLOCK_STATUS & 0x02) != 0x02);      // ждем когда PLL выйдет в раб. режим

  RST_CLK->CPU_CLOCK  = (2                            // источник для CPU_C1
						   |(1 << 2)                      // источник для CPU_C2
						   |(0 << 4)                      // предделитель для CPU_C3
						   |(1 << 8));                    // источник для HCLK

  PORTD->OE = 0xffff;      // порт D на выход
  PORTD->FUNC = 0x0000;    // функция - порт 
  PORTD->ANALOG  = 0xffff; // режим потра - цифровой
  PORTD->PWR     = 0xFFFFFFFF;   // максимально быстрый фронт ( порядка 10 нс)
  
  //0x4002_0000  MDR_RST_CLK  Контроллер тактовой частоты
  
 
  
  RST_CLK->TIM_CLOCK = (1<<24);  // Разрешение тактовой частоты на TIM1                                  // Делитель тактовой частоты TIM1_CLK == HCLK/128   
  TIMER1->CNTRL = 0x00; // настраиваем работу основного счетчика
  TIMER1->CNT = 0x00;   // начальное значение счетчика
  TIMER1->PSG = 25;    // Счетчик считает на f = TIM_CLK/(PSG+1);
  TIMER1->ARR = 0x0F;   // Основание счета счетчика
  TIMER1->IE = 2;       // Флаг разрешения прерывания по событию совпадения CNT и ARR
  TIMER1->STATUS = 0x00000000; // сбросить все флаги
  NVIC_EnableIRQ(Timer1_IRQn); // Разрешение прерывания для Таймера 1
  __enable_irq(); // Enable Interrupts
  //TIMER1->CNTRL = 1; // включить таймер 1
  // timer 1 0x4007_0000 
  // PORTD 0x400C_0000 
  
  PORTC->OE = 0x0000;          // порт C на вход
  PORTC->FUNC = 0x0000;        // функция - порт 777
  PORTC->ANALOG  = 0xffff;     // режим потра - цифровой
  PORTC->PWR     = 0x00000000; //  максимально быстрый фронт ( порядка 10 нс)

  while(1){
   
  if (!(PORTC->RXTX & (1 << 10))){
    for(x=0;x<100000;x++){}
    if (!(PORTC->RXTX & (1 << 10))){
      PORTD->RXTX = 0xffff;
      for(x=0;x<100000;x++){}
      TIMER1->CNTRL = 1; // включить таймер 1
   }
  }
    
    
    
    
    
    
    //PORTD->RXTX = 0xffff;
    //for(x=0;x<3000000;x++){}
    /*
    PORTD->RXTX = 1<<10;
    for(x=0;x<3000000;x++){}
    PORTD->RXTX = 0<<10;
    for(x=0;x<3000000;x++){}
    */
    
    
  
  }
}
