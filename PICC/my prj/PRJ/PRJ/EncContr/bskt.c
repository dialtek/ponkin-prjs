//#include "C:\PRJ\BSKT-220\bskt.h"

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


//#fuses   HS,NOPROTECT,NOWDT,PUT,NOMCLR,NOBROWNOUT,NOLVP,NOCPD

#BYTE portA = 0x05
#BYTE portB = 0x06

#BYTE TRISA = 0x85               
#BYTE TRISB = 0x86

#BYTE CMCON = 0x9C

#BIT C1INV=CMCON.4
#BIT C2INV=CMCON.5

#BYTE SPBRG = 0x99
#BYTE TXSTA = 0x98
#BIT BRGH=TXSTA.2

#BIT B0=portB.0
#BIT B1=portB.1
#BIT B2=portB.2
#BIT B3=portB.3
#BIT B4=portB.4
#BIT B5=portB.5
#BIT B6=portB.6
#BIT B7=portB.7

#BIT TRB0=TRISB.0
#BIT TRB1=TRISB.1
#BIT TRB2=TRISB.2
#BIT TRB3=TRISB.3
#BIT TRB4=TRISB.4
#BIT TRB5=TRISB.5
#BIT TRB6=TRISB.6
#BIT TRB7=TRISB.7

#use delay(clock=20000000)

#use rs232(UART1,baud=38400,parity=N,xmit=PIN_B5,bits=8)

signed int8 x=0;
int1 fl1=0,fl2=0;
unsigned int8 phase=0,buf,buf1=0,buf2=0,buf3=0; 
unsigned int16 angle=0,buf4=0,buf5=0;
//int16 turns=0;
signed int16 turn_counter=0,sum1=0;
signed int16 counter=0;
#int_TIMER1
void  TIMER1_isr(void) 
{
clear_interrupt(int_timer1);
}

#int_TIMER2
void  TIMER2_isr(void) {

clear_interrupt(int_timer2);
}

#int_TIMER0
void  TIMER0_isr(void) 
{
clear_interrupt(int_timer0);
}




#int_EXT
void ExtInt(void)
{

 if (B1) {
 B4=0;
 counter --;
 }
 else {
       B4=1;
 counter ++;     
 }
delay_us(50);
clear_interrupt(INT_EXT);

}



void main()
{
 
   
   setup_adc_ports(NO_ANALOGS|VSS_VDD);
   setup_adc(ADC_OFF);
   setup_spi(SPI_SS_DISABLED);
   setup_timer_0(RTCC_INTERNAL|RTCC_DIV_1);
   setup_timer_1(T1_INTERNAL|T1_DIV_BY_2);
   setup_timer_2(T2_DIV_BY_16,89,1);
   setup_timer_1(T1_disabled);
  // setup_timer_2(T2_disabled);
  // setup_comparator(A0_A2_A1_A2_OUT_ON_A3_A4);
  // setup_comparator(NC_NC_NC_NC);
   //setup_vref(VREF_LOW|13|VREF_A2);//0.5Ucc �� RA2
   //setup_ccp1 (CCP_CAPTURE_FE); 
   enable_interrupts(INT_EXT);
   ext_int_edge(L_To_H);
  // enable_interrupts(INT_TIMER1);
  // enable_interrupts(INT_TIMER2);
   //enable_interrupts(INT_CCP1);
   //enable_interrupts(INT_TIMER0);
   //disable_interrupts(INT_TIMER0);
   enable_interrupts(GLOBAL);
   

   // TODO: USER CODE!!
   
   TRB0=1;
   TRB1=1;
   TRB3=0;
   TRB4=0;
   B1=0;
   B3=0;
while(true){

 
 
 if(counter < 0) {
    counter=9;
    B3=1;
    delay_us(50);
    B3=0;
     }else if(counter > 9){
    counter=0;
    B3=1;
    delay_us(50);
    B3=0;
 }
 }
 }



