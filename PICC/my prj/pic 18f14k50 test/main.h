#include <18F14K50.h>
#device adc=10

#FUSES CPUDIV1                   //No System Clock Postscaler
#FUSES NOWDT                    //No Watch Dog Timer
//#FUSES INTRC  // Internal RC Osc           
#FUSES HS   //High speed Osc
#FUSES PLLEN                      // 4X HW PLL enabled
//#FUSES LP                       //Low power osc < 200 khz
#FUSES NOBROWNOUT               //No brownout reset
#FUSES NOLVP                    //No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O
//#FUSES NOXINST                  //Extended set extension and Indexed Addressing mode disabled (Legacy mode)
#FUSES USBDIV1
#FUSES PCLKEN //1.13   PCLKEN   Primary External Clock Enabled

//#use delay(clock=12000000)

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

#BIT RB4 = PORTB.4
#BIT RB5 = PORTB.5
#BIT RB6 = PORTB.6

