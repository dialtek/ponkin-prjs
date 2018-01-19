#include <18F4320.h>
#FUSES NOWDT                    //No Watch Dog Timer
#FUSES WDT128                   //Watch Dog Timer uses 1:128 Postscale
//#FUSES H4                       //High speed osc with HW enabled 4X PLL
#FUSES HS                       //High speed osc 
#FUSES NOFCMEN                  //Fail-safe clock monitor disabled
#FUSES NOBROWNOUT                 //Reset when brownout detected
#FUSES BORV45                   //Brownout reset at 4.5V
#FUSES NOPUT                    //No Power Up Timer
#FUSES NOCPD                    //No EE protection
#FUSES STVREN                   //Stack full/underflow will cause reset
#FUSES NODEBUG                  //No Debug mode for ICD
#FUSES NOLVP                      //NO Low Voltage Programming on B3(PIC16) or B5(PIC18)
#FUSES NOWRT                    //Program memory not write protected
#FUSES NOWRTD                   //Data EEPROM not write protected
#FUSES IESO                     //Internal External Switch Over mode enabled
#FUSES NOEBTR                   //Memory not protected from table reads
#FUSES NOEBTRB                  //Boot block not protected from table reads
#FUSES MCLR                     //Master Clear pin enabled
#FUSES NOPROTECT                //Code not protected from reading
#FUSES NOCPB                    //No Boot Block code protection
#FUSES NOWRTB                   //Boot block not write protected
#FUSES NOWRTC                   //configuration not registers write protected
#FUSES PBADEN                   //PORTB pins are configured as analog input channels on RESET

#use delay(clock=8000000)
#use rs232(uart1,baud=9600,parity=N,xmit=PIN_C6,rcv=PIN_C7,bits=8)

