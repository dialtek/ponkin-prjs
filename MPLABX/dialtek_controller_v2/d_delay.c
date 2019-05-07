#include "xc.h"
#include "d_delay.h"
/*=========================================================================== */
// Timer 8 - delay timer
void TIMER8_delay_init (void)
{
    //TMR8 0; 
    TMR8 = 0x00;
    //Period = 1 us; Frequency = 60000000 Hz; PR8 60; 
    PR8 = 50; // 60 - calculated, 50 - real
    //TCKPS 1:1; T32 16 Bit; TON enabled; TSIDL disabled; TCS FOSC/2; TGATE disabled; 
    T8CON = 0x8000;
 
    IFS3bits.T8IF = 0;
    IEC3bits.T8IE = 0;
    /* Start the Timer */
    T8CONbits.TON = 1;
}

volatile void delay_us(unsigned long us_delay)
{
    for(unsigned long i = 0; i < us_delay; i++)
    {
       T8CONbits.TON = 1;
       
       while(!IFS3bits.T8IF) { }
       IFS3bits.T8IF = 0;
       TMR8 = 0x00;
    }
}

volatile void delay_ms(unsigned int ms_delay)
{
    for(unsigned int i = 0; i < ms_delay; i++) // x ms
    {
      // 1 ms
      for(unsigned long i = 0; i < 1000; i++)
        {
         T8CONbits.TON = 1;
       
         while(!IFS3bits.T8IF) { }
         IFS3bits.T8IF = 0;
         TMR8 = 0x00;
        }
    }
}

// delays
/*=========================================================================== */