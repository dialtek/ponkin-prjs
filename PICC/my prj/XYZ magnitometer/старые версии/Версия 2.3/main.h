#include <18F25K80.h>
#device adc=16

#FUSES NOWDT                 	//No Watch Dog Timer
#FUSES WDT128                	//Watch Dog Timer uses 1:128 Postscale
#FUSES NOXINST               	//Extended set extension and Indexed Addressing mode disabled (Legacy mode)
#FUSES HSM                   	//High speed Osc, medium power 4MHz-16MHz
#FUSES NOBROWNOUT            	//No brownout reset
#FUSES WDT_NOSLEEP           	//Watch Dog Timer, disabled during SLEEP

#use delay(clock=20000000)


