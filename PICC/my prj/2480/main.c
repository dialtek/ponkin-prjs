#include <main.h>

#Byte TRISA = 0xf92
#Byte TRISB = 0xf93
#Byte TRISC = 0xf94
#Byte TRISD = 0xf95

#Byte PORTA = 0xf80
#Byte PORTB = 0xf81
#Byte PORTC = 0xf82
#Byte PORTD = 0xf83

#BIT RA0 = PORTA.0
#BIT RA1 = PORTA.1
#BIT RA2 = PORTA.2
#BIT RA3 = PORTA.3
#BIT RA4 = PORTA.4

#BIT TRA5 = TRISA.5
#BIT TRA4 = TRISA.4
#BIT TRA3 = TRISA.3
#BIT TRA2 = TRISA.2
#BIT TRA1 = TRISA.1
#BIT TRA0 = TRISA.0

void main()
{
 TRA0=0;
 TRA1=0;
 TRA2=0;
 TRA3 = 0;

While (true){ 

   RA2=0;
   RA0 = 1;
   RA1 = 1;
   delay_us(1);
   RA2= 1;
   RA0 = 0;
   delay_us(1);
   RA2 = 0;
   RA0 = 1;
   delay_ms(1);
    RA1 = 0;
    delay_us(1);
   RA1 = 1; 
   delay_ms(100);
     
}


}
