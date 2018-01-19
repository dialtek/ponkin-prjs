#include <18F2320.h>
#device adc=10

#FUSES NOWDT                 	//No Watch Dog Timer
#FUSES WDT128                	//Watch Dog Timer uses 1:128 Postscale
#FUSES H4                    	//High speed osc with HW enabled 4X PLL
#FUSES FCMEN                 	//Fail-safe clock monitor enabled
#FUSES BROWNOUT              	//Reset when brownout detected
#FUSES BORV45                	//Brownout reset at 4.5V
#FUSES PUT                   	//Power Up Timer
#FUSES NOCPD                 	//No EE protection
#FUSES STVREN                	//Stack full/underflow will cause reset
#FUSES NODEBUG               	//No Debug mode for ICD
#FUSES NOLVP                 	//No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O
#FUSES NOWRT                 	//Program memory not write protected
#FUSES NOWRTD                	//Data EEPROM not write protected
#FUSES IESO                  	//Internal External Switch Over mode enabled
#FUSES NOEBTR                	//Memory not protected from table reads
#FUSES NOEBTRB               	//Boot block not protected from table reads
#FUSES MCLR                  	//Master Clear pin enabled
#FUSES NOPROTECT             	//Code not protected from reading
#FUSES NOCPB                 	//No Boot Block code protection
#FUSES NOWRTB                	//Boot block not write protected
#FUSES NOWRTC                	//configuration not registers write protected
#FUSES PBADEN                	//PORTB pins are configured as analog input channels on RESET

#use delay(clock=40000000)
#use rs232(baud=9600,parity=N,xmit=PIN_C6,rcv=PIN_C7,bits=8)

