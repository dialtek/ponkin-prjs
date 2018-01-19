#include <18F2320.h>
#device adc=16

#FUSES NOWDT                 	//No Watch Dog Timer
#FUSES WDT128                	//Watch Dog Timer uses 1:128 Postscale
#FUSES LP                    	//Low power osc < 200 khz
#FUSES NOBROWNOUT            	//No brownout reset
#FUSES NOPBADEN              	//PORTB pins are configured as digital I/O on RESET
#FUSES NOLVP                 	//No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O

#use delay(clock=20000000)


