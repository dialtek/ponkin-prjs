#include <18F25K80.h>
#device adc=12

#FUSES NOWDT                    //No Watch Dog Timer  на самом деле не отключается
#FUSES WDT8192                   //Watch Dog Timer uses 1:128 Postscale
#FUSES NOXINST                  //Extended set extension and Indexed Addressing mode disabled (Legacy mode)
#FUSES HSH                      //High speed Osc, high power 16MHz-25MHz
#FUSES NOFCMEN                  //Fail-safe clock monitor disabled
#FUSES NOIESO                   //Internal External Switch Over mode disabled
#FUSES NOBROWNOUT               //No brownout reset
#FUSES WDT_NOSLEEP              //Watch Dog Timer, disabled during SLEEP

#use delay(clock=40000000)
#use rs232(UART1,baud=19200,parity=N,xmit=PIN_C6,rcv=PIN_C7,bits=8,stream=PORT1)


