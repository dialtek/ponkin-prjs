#include <18F14K50.h>
#device adc=10

#FUSES NOWDT                    //No Watch Dog Timer
//#FUSES WDT128                   //Watch Dog Timer uses 1:128 Postscale
#FUSES CPUDIV1                  //System Clock by 4
#FUSES NOBROWNOUT               //No brownout reset
#FUSES NOLVP                    //No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O
#FUSES NOXINST                  //Extended set extension and Indexed Addressing mode disabled (Legacy mode)
#FUSES HS                       //High speed Osc (> 4mhz for PCM/PCH) (>10mhz for PCD)
#FUSES PLLEN                    //4X HW PLL enabled

#BYTE TRISA = 0xF92
#BYTE TRISB = 0xF93
#BYTE TRISC = 0xF94

#BYTE OSCCON = 0xFD3

#BYTE PORTA = 0xF80
#BYTE PORTB = 0xF81
#BYTE PORTC = 0xF82

#BIT RA0 = PORTA.0
#BIT RA1 = PORTA.1
#BIT RA3 = PORTA.2 // input only
#BIT RA4 = PORTA.3
#BIT RA5 = PORTA.5

#BIT TRA5 = TRISA.5
#BIT TRA4 = TRISA.3
#BIT TRA3 = TRISA.2
#BIT TRA1 = TRISA.1
#BIT TRA0 = TRISA.0

#BIT TRC5 = TRISC.5
#BIT RC5 = PORTC.5

#BIT RB4 = PORTB.4
#BIT RB5 = PORTB.5
#BIT RB6 = PORTB.6

#BIT TRB4 = TRISB.4
#BIT TRB6 = TRISB.6


#use delay(clock=48000000)
#use I2C(master, scl=PIN_B6, sda=PIN_B4, fast=400000) //sets the target speed to 450 KBSP

void main()
{
   TRC5 = 0;
   
   TRB4 = 1;
   TRB6 = 1;
   
   //TRA0 = 0;
   
   while(TRUE)
   {
     i2c_start();

i2c_write(0x81);     // Device addres
//i2c_write(0xa1);     // to change data direction

i2c_stop();


     
     
     RC5 = 1;
     delay_us(10);
     RC5 = 0;
     delay_us(15);
     
   }

}
