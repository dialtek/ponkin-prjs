#include <16F88.h>
#device *=16
#device adc=10

#FUSES NOWDT                    //No Watch Dog Timer
#FUSES HS                       //High speed Osc (> 4mhz)
#FUSES NOPUT                    //No Power Up Timer
#FUSES MCLR                     //Master Clear pin enabled
#FUSES NOBROWNOUT               //No brownout reset
#FUSES NOLVP                    //No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O
#FUSES NOCPD                    //No EE protection
#FUSES NOWRT                    //Program memory not write protected
#FUSES NODEBUG                  //No Debug mode for ICD
#FUSES NOPROTECT                //Code not protected from reading
#FUSES NOFCMEN                  //Fail-safe clock monitor disabled
#FUSES NOIESO                    //Internal External Switch Over mode enabled
//#FUSES CCPMX   

//#fuses   HS,NOPROTECT,NOWDT,PUT,NOMCLR,NOBROWNOUT,NOLVP,NOCPD


#use delay(clock=8000000)
#use rs232(baud=9600,parity=N,xmit=PIN_A3,rcv=PIN_A2,bits=8)

