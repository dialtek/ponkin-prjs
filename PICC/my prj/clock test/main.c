#include <18F2320.h>
#device adc=16

#FUSES NOWDT                    //No Watch Dog Timer
//#FUSES WDT128                   //Watch Dog Timer uses 1:128 Postscale
#FUSES HS                       //High speed Osc (> 4mhz for PCM/PCH) (>10mhz for PCD)                       
#FUSES NOBROWNOUT               //No brownout reset
#FUSES NOPBADEN                 //PORTB pins are configured as digital I/O on RESET
#FUSES NOLVP                    //No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O

#use delay(clock=10000000)

#BYTE TRISA = 0xF92
#BYTE TRISB = 0xF93
#BYTE TRISC = 0xF94 
#BYTE TRISD = 0xF95
#BYTE TRISE = 0xF96

#BYTE PORTA = 0xF80
#BYTE PORTB = 0xF81
#BYTE PORTC = 0xF82
#BYTE PORTD = 0xF83
#BYTE PORTE = 0xF84

#BIT RA0 = PORTA.0
#BIT RA1 = PORTA.1
#BIT RA2 = PORTA.2
#BIT RA3 = PORTA.3
#BIT RA4 = PORTA.4
#BIT RA5 = PORTA.5

#BIT TRA5 = TRISA.5
#BIT TRA4 = TRISA.4
#BIT TRA3 = TRISA.3
#BIT TRA2 = TRISA.2
#BIT TRA1 = TRISA.1
#BIT TRA0 = TRISA.0

void main()
{
  
   TRA0 = 0;

   while(TRUE)
   {
      RA0 = 1;
      delay_ms(1);
      RA0 = 0;
      delay_ms(1);
      
      }

}
