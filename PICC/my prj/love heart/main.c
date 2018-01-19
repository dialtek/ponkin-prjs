#include <33FJ64GP204.h>

#FUSES WPRES32                  //Watch Dog Timer PreScalar 1:32
#FUSES WPOSTS1                  //Watch Dog Timer PostScalar 1:1
//#FUSES PROTECT_HIGH             //General Segment Code Protect High Security
#FUSES CKSFSM                   //Clock Switching is enabled, fail Safe clock monitor is enabled
#FUSES FRC                      //Internal Fast RC Oscillator
#FUSES OSCIO                    //OSC2 is general purpose output

#use delay(clock=7.37M)
//7370000
 #WORD TRISA = 0x02C0
 #WORD TRISB = 0x02C8
 #WORD TRISC = 0x02D0
 
 #WORD PORTA = 0x02C2
 #WORD PORTB = 0x02CA
 #WORD PORTC = 0x02D2
 
 #WORD ODCA = 0x02C6
 #WORD ODCB = 0x02CE
 #WORD ODCC = 0x02D6
 
 #BIT TR_KN = TRISB.6
 
 #BIT RB6 = PORTB.6
 #BIT RB8 = PORTB.8
 #BIT RB5 = PORTB.5
 #BIT RB4 = PORTB.4
 #BIT RB2 = PORTB.2
 #BIT RB3 = PORTB.3
 #BIT RB1 = PORTB.1
 #BIT RB0 = PORTB.0
 #BIT RB15 = PORTB.15
 #BIT RB14 = PORTB.14
 #BIT RB10 = PORTB.10
 #BIT RB11 = PORTB.11
 #BIT RB12 = PORTB.12
 #BIT RB13= PORTB.13
 #BIT RB9 = PORTB.9
 #BIT RB7 = PORTB.7
 
 #BIT RC6 = PORTC.6
 #BIT RC7 = PORTC.7
 #BIT RC8 = PORTC.8
 #BIT RC9 = PORTC.9
  #BIT RC0 = PORTC.0
   #BIT RC1 = PORTC.1
    #BIT RC2 = PORTC.2
     #BIT RC3 = PORTC.3
      #BIT RC4 = PORTC.4
       #BIT RC5 = PORTC.5
 
  #BIT RA10 = PORTA.10
  #BIT RA7 = PORTA.7
  #BIT RA2 = PORTA.2
  #BIT RA3 = PORTA.3
  #BIT RA8 = PORTA.8
  #BIT RA4 = PORTA.4
  #BIT RA9 = PORTA.9
  #BIT RA0 = PORTA.0
  #BIT RA1 = PORTA.1
 
 #define LED1 RB7
 #define LED2 RB8
 #define LED3 RB9
 #define LED4 RC6
 #define LED5 RC7
 #define LED6 RC8
 #define LED7 RC9
 #define LED8 RB10
 #define LED9 RB11
 #define LED10 RB12
 #define LED11 RB13
 #define LED12 RA10
  #define LED13 RA7
  #define LED14 RB14
  #define LED15 RB15
  #define LED16 RA0
  #define LED17 RA1
  #define LED18 RB0
  #define LED19 RB1
  #define LED20 RB2
  #define LED21 RB3
  #define LED22 RC0
  #define LED23 RC1
  #define LED24 RC2
  #define LED25 RA2
  #define LED26 RA3
  #define LED27 RA8
  #define LED28 RB4
  #define LED29 RA4
  #define LED30 RA9
  #define LED31 RC3
 #define LED32 RC4
 #define LED33 RC5
 #define LED34 RB5
 #define KN RB6
 
 unsigned int16 i=0,b=20,n=0;
 int1 fl1=0;
 unsigned int8 t_out=0;
  unsigned int8 b_hold=0;
  unsigned int8 b_push=0;

#INT_TIMER1
void  TIMER1_isr(void) 
{ // прерывание каждые 30 мкс.
SET_TIMER1(65504);
if (!KN){
char i;
   for (i=0;i<20;i++){
   delay_us(2);
   }
   if (!KN){
   delay_ms(100);
   n=n+1;
   
   if (n>6){
   n=0;
   }
   }
   }
   

clear_interrupt(int_timer1);
}
 
 void blink1 (unsigned int16 x){
 porta=0x0000;
 portb=0x0000;
 portc=0x0000;
  delay_ms(x);
   LED34=1;
   delay_ms(x);
   LED1=1;
   delay_ms(x);
   LED33=1;
   delay_ms(x);  
   LED2=1;
   delay_ms(x);  
   LED32=1;
   delay_ms(x);
   LED3=1;
   delay_ms(x);
   LED31=1;
   delay_ms(x);  
   LED4=1;
   delay_ms(x);  
   LED30=1;
   delay_ms(x);
   LED5=1;
   delay_ms(x);
   LED29=1;
   delay_ms(x); 
   LED6=1;
   delay_ms(x);
   LED28=1;
   delay_ms(x);
   LED7=1;
   delay_ms(x);  
   LED27=1;
   delay_ms(x);
   LED8=1;
   delay_ms(x);
   LED26=1;
   delay_ms(x);  
   LED9=1;
   delay_ms(x);  
   LED25=1;
   delay_ms(x);
   LED10=1;
   delay_ms(x);
   LED24=1;
   delay_ms(x);  
   LED11=1;
   delay_ms(x);  
   LED23=1;
   delay_ms(x);
   LED12=1;
   delay_ms(x);
   LED22=1;
   delay_ms(x);  
   LED13=1;
   delay_ms(x);  
   LED21=1;
   delay_ms(x);
   LED14=1;
   delay_ms(x);
   LED20=1;
   delay_ms(x);  
   LED15=1;
   delay_ms(x);  
   LED19=1;
   delay_ms(x);
   LED16=1;
   delay_ms(x);
   LED17=1;
   delay_ms(x);  
   LED18=1;
   delay_ms(x);  
 porta=0x0000;
 portb=0x0000;
 portc=0x0000;
   delay_ms(x);
 
 }
 
 void blink2 (unsigned int16 y){

LED1=1;
delay_ms(y);
LED2=1; 
delay_ms(y);
LED3=1; 
delay_ms(y);
LED4=1; 
delay_ms(y);
LED5=1; 
delay_ms(y);
LED6=1; 
delay_ms(y);
LED7=1; 
delay_ms(y);
LED8=1; 
delay_ms(y);
LED9=1; 
delay_ms(y);
LED10=1; 
delay_ms(y);
 LED11=1; 
 delay_ms(y);
LED12=1; 
delay_ms(y);
LED13=1; 
delay_ms(y);
LED14=1;
delay_ms(y);
LED15=1;
delay_ms(y);
LED16 =1;
delay_ms(y);
LED17 =1;
delay_ms(y);
 LED18 =1;
 delay_ms(y);
LED19 =1;
delay_ms(y);
LED20 =1;
delay_ms(y);
 LED21 =1;
 delay_ms(y);
LED22 =1;
delay_ms(y);
LED23 =1;
delay_ms(y);
LED24 =1;
delay_ms(y);
 LED25 =1;
 delay_ms(y);
 LED26 =1;
 delay_ms(y);
LED27 =1;
delay_ms(y);
LED28 =1;
delay_ms(y);
LED29 =1;
delay_ms(y);
LED30 =1;
delay_ms(y);
LED31=1;
delay_ms(y);
LED32 =1;
delay_ms(y);
LED33 =1;
delay_ms(y);
LED34 =1;
delay_ms(y);

LED1=0;
delay_ms(y);
LED2=0; 
delay_ms(y);
LED3=0; 
delay_ms(y);
LED4=0; 
delay_ms(y);
LED5=0; 
delay_ms(y);
LED6=0; 
delay_ms(y);
LED7=0; 
delay_ms(y);
LED8=0; 
delay_ms(y);
LED9=0; 
delay_ms(y);
LED10=0; 
delay_ms(y);
 LED11=0; 
 delay_ms(y);
LED12=0; 
delay_ms(y);
LED13=0; 
delay_ms(y);
LED14=0;
delay_ms(y);
LED15=0;
delay_ms(y);
LED16 =0;
delay_ms(y);
LED17 =0;
delay_ms(y);
 LED18 =0;
 delay_ms(y);
LED19 =0;
delay_ms(y);
LED20 =0;
delay_ms(y);
 LED21 =0;
 delay_ms(y);
LED22 =0;
delay_ms(y);
LED23 =0;
delay_ms(y);
LED24 =0;
delay_ms(y);
 LED25 =0;
 delay_ms(y);
 LED26 =0;
 delay_ms(y);
LED27 =0;
delay_ms(y);
LED28 =0;
delay_ms(y);
LED29 =0;
delay_ms(y);
LED30 =0;
delay_ms(y);
LED31=0;
delay_ms(y);
LED32 =0;
delay_ms(y);
LED33 =0;
delay_ms(y);
LED34 =0;
delay_ms(y);
 }
 
 void L1 (unsigned int16 x){
 
 porta=0x0000;
 portb=0x0000;
 portc=0x0000;
 delay_ms(x);
   LED1=1;
   delay_ms(x);  
   LED1=0;
 delay_ms(x);
   LED2=1;
   delay_ms(x);  
   LED2=0;
   delay_ms(x);  
   LED3=1;
   delay_ms(x);
   LED3=0;
   delay_ms(x);
   LED4=1;
   delay_ms(x);  
   LED4=0;
   delay_ms(x);  
   LED5=1;
   delay_ms(x);
   LED5=0;
   delay_ms(x);
   LED6=1;
   delay_ms(x); 
   LED6=0;
   delay_ms(x);
   LED7=1;
   delay_ms(x);
   LED7=0;
   delay_ms(x);  
   LED8=1;
   delay_ms(x);
   LED8=0;
   delay_ms(x);
   LED9=1;
   delay_ms(x);  
   LED9=0;
   delay_ms(x);  
   LED10=1;
   delay_ms(x);
   LED10=0;
   delay_ms(x);
   LED11=1;
   delay_ms(x);  
   LED11=0;
   delay_ms(x);  
   LED12=1;
   delay_ms(x);
   LED12=0;
   delay_ms(x);
   LED13=1;
   delay_ms(x);  
   LED13=0;
   delay_ms(x);  
   LED14=1;
   delay_ms(x);
   LED14=0;
   delay_ms(x);
   LED15=1;
   delay_ms(x);  
   LED15=0;
   delay_ms(x);  
   LED16=1;
   delay_ms(x);
   LED16=0;
   delay_ms(x);
   LED17=1;
   delay_ms(x);  
   LED17=0;
   delay_ms(x);;  
   LED18=1;
   delay_ms(x);
   LED18=0;
   delay_ms(x);
   LED19=1;
   delay_ms(x);  
   LED19=0;
   delay_ms(x);  
   LED20=1;
   delay_ms(x);
   LED20=0;
   delay_ms(x);
   LED21=1;
   delay_ms(x);  
   LED21=0;
   delay_ms(x);  
   LED22=1;
   delay_ms(x);
   LED22=0;
   delay_ms(x);
   LED23=1;
   delay_ms(x);  
   LED23=0;
   delay_ms(x);  
   LED24=1;
   delay_ms(x);
   LED24=0;
   delay_ms(x);
   LED25=1;
   delay_ms(x);  
   LED25=0;
   delay_ms(x);
    LED26=1;
   delay_ms(x);  
   LED26=0;
   delay_ms(x);  
   LED27=1;
   delay_ms(x);
   LED27=0;
   delay_ms(x);
   LED28=1;
   delay_ms(x);  
   LED28=0;
   delay_ms(x);  
   LED29=1;
   delay_ms(x);
   LED29=0;
   delay_ms(x);
   LED30=1;
   delay_ms(x);  
   LED30=0;
   delay_ms(x);  
   LED31=1;
   delay_ms(x);
   LED31=0;
   delay_ms(x);
   LED32=1;
   delay_ms(x);  
   LED32=0;
   delay_ms(x);
   LED33=1;
   delay_ms(x);
   LED33=0;
   delay_ms(x);
   LED34=1;
   delay_ms(x);  
   LED34=0;
   delay_ms(x);
   
 porta=0x0000;
 portb=0x0000;
 portc=0x0000;
   delay_ms(x);
 
 
 
 } 
 
 void all (){
 
PORTa=0xffff;
PORTb=0xffff;
PORTc=0xffff;
 }
 
 void rnd_blink (unsigned int8 delay){
 porta=0x0000;
 portb=0x0000;
 portc=0x0000;
 delay_ms(1);
 porta=0xaaaa;
 portb=0xaaaa;
 portc=0xaaaa;
 delay_ms(delay);
 porta=0x0a0a0;
 portb=0x0a0a0;
 portc=0x0a0a0;
 delay_ms(delay);
 porta=0xfafaf;
 portb=0xfafaf;
 portc=0xfafaf;
 delay_ms(delay);
 porta=0xeea3;
 portb=0xeea3;
 portc=0xeea3;
 delay_ms(delay);
 porta=0x3333;
 portb=0x3333;
 portc=0x3333;
 delay_ms(delay);
 porta=0x0a0a0;
 portb=0x0a0a0;
 portc=0x0a0a0;
 delay_ms(delay);
 porta=0xfafaf;
 portb=0xfafaf;
 portc=0xfafaf;
 delay_ms(delay);
 }
 
 void rnd_blink2(unsigned int8 x){
 
 porta=0x0000;
 portb=0x0000;
 portc=0x0000;
 delay_ms(x);
   LED1=1;
   delay_ms(x);  
   LED1=0;
 delay_ms(x);
   LED14=1;
   delay_ms(x);  
   LED14=0;
   delay_ms(x);  
   LED33=1;
   delay_ms(x);
   LED33=0;
   delay_ms(x);
   LED22=1;
   delay_ms(x);  
   LED22=0;
   delay_ms(x);  
   LED1=1;
   delay_ms(x);
   LED1=0;
   delay_ms(x);
   LED16=1;
   delay_ms(x); 
   LED16=0;
   delay_ms(x);
   LED27=1;
   delay_ms(x);
   LED27=0;
   delay_ms(x);  
   LED18=1;
   delay_ms(x);
   LED18=0;
   delay_ms(x);
   LED2=1;
   delay_ms(x);  
   LED2=0;
   delay_ms(x);  
   LED10=1;
   delay_ms(x);
   LED10=0;
   delay_ms(x);
   LED30=1;
   delay_ms(x);  
   LED30=0;
   delay_ms(x);  
   LED6=1;
   delay_ms(x);
   LED6=0;
   delay_ms(x);
   LED13=1;
   delay_ms(x);  
   LED13=0;
   delay_ms(x);  
   LED4=1;
   delay_ms(x);
   LED4=0;
   delay_ms(x);
   LED15=1;
   delay_ms(x);  
   LED15=0;
   delay_ms(x);  
   LED34=1;
   delay_ms(x);
   LED34=0;
   delay_ms(x);
   LED5=1;
   delay_ms(x);  
   LED5=0;
   delay_ms(x);;  
   LED19=1;
   delay_ms(x);
   LED19=0;
   delay_ms(x);
   LED9=1;
   delay_ms(x);  
   LED9=0;
   delay_ms(x);  
   LED20=1;
   delay_ms(x);
   LED20=0;
   delay_ms(x);
   LED1=1;
   delay_ms(x);  
   LED1=0;
   delay_ms(x);  
   LED17=1;
   delay_ms(x);
   LED17=0;
   delay_ms(x);
   LED23=1;
   delay_ms(x);  
   LED23=0;
   delay_ms(x);  
   LED28=1;
   delay_ms(x);
   LED28=0;
   delay_ms(x);
   LED25=1;
   delay_ms(x);  
   LED25=0;
   delay_ms(x);
    LED26=1;
   delay_ms(x);  
   LED26=0;
   delay_ms(x);
   LED13=1;
   delay_ms(x);
   LED13=0;
   delay_ms(x);  
   LED6=1;
   delay_ms(x);  
   LED6=0;
   delay_ms(x);
   LED11=1;
   delay_ms(x);
   LED11=0;
   delay_ms(x);  
   LED33=1;
   delay_ms(x);  
   LED33=0;
   delay_ms(x);
   LED21=1;
   delay_ms(x);
   LED21=0;
   delay_ms(x);  
   LED28=1;
   delay_ms(x);
   LED28=0;
   delay_ms(x);
   LED1=1;
   delay_ms(x);
   LED1=0;
   delay_ms(x);  
   LED33=1;
   delay_ms(x);
   LED33=0;
   delay_ms(x);
   
 porta=0x0000;
 portb=0x0000;
 portc=0x0000;
   delay_ms(x);
 
 }
 
 void main()
{
  
   ENABLE_INTERRUPTS(INTR_GLOBAL);
   ENABLE_INTERRUPTS(INT_TIMER1);
   setup_timer1(TMR_INTERNAL|TMR_DIV_BY_1);
   SET_TIMER1(65504);  // прерывание каждые 30 мкс.
   
   ODCA =0;
   ODCB =0;
   ODCC =0; 
      
   TRISA=0x0000;
   TRISB=0b0000000001000000; // кнопка на порте Б
   TRISC=0x0000;
  
   
  /*   
  void blink1 (char delay){
  
  LED1 =1;
 LED2 =1;
 LED3 =1;
 LED4 =1;
  LED5 =1;
  LED6 =1;
  LED7=1;
  LED8 =1;
  LED9 =1;
  LED10=1; 
  LED11=1; 
  LED12=1;
   LED13=1;
   LED14 =1;
   LED15 =1;
   LED16 =1;
   LED17 =1;
   LED18 =1;
   LED19 =1;
   LED20 =1;
   LED21 =1;
   LED22 =1;
   LED23 =1;
   LED24 =1;
   LED25=1;
   LED26 =1;
   LED27 =1;
   LED28 =1;
   LED29 =1;
   LED30 =1;
  LED31 =1;
  LED32 =1;
  LED33 =1;
  
   }
   */
   
    
   while (true){
   
   switch (n){
   
    case 0:
      //all();
PORTa=0xffff;
PORTb=0xffff;
PORTc=0xffff;
    break;
    
    case 1:
  blink1(50);    
    break;
    
    case 2: 
PORTa=0xffff;
PORTb=0xffff;
PORTc=0xffff;
delay_ms(100);
PORTa=0x0000;
PORTb=0x0000;
PORTc=0x0000;
delay_ms(100);
    break;
   
    case 3:
  blink2(50); 
    break;
    
    case 4:
  L1(50);
    break;
     
     case 5:
  rnd_blink(50);  
    break;
    
     case 6:
  rnd_blink2(80);  
    break;
    
 }



   
 /* 
   for (i=1;i<5;++i){
   b=b+50;
   blink1(b);
   }
   b=10;
   
   for (i=1;i<5;++i){
   b=b+10;
   blink2(b);
   }
   
   for (i=1;i<5;++i){
   blink2(20);
   }
   
   for (i=1;i<5;++i){
   blink2(10);
   }
   
   for (i=7;i<30;++i){
   
   blink2(i);
   }
 porta=0xffff;
 portb=0xffff;
 portc=0xffff;
   delay_ms(5000);
   /*
   for (i=0;i<16;++i){
   PORTB = 0b0000000000000001;
   delay_us(1);
   PORTb = PORTb<<1;
   delay_us(500);
   }
  */

   /*
   PORTB = 0b0000000000000001;
   delay_ms(500);
   PORTB = 0b0000000000000010;
   delay_ms(500);
   PORTB = 0b0000000000000100;
   delay_ms(500);
   PORTB = 0b0000000000001000;
   delay_ms(500);
   PORTB = 0b0000000000010000;
   delay_ms(500);
   PORTB = 0b0000000000100000;
   delay_ms(500);
   PORTB = 0b0000000001000000;
   delay_ms(500);
   PORTB = 0b0000000010000000;
   delay_ms(500);
   PORTB = 0b0000000100000000;
   delay_ms(500);
   PORTB = 0b0000001000000000;
   delay_ms(500);
   PORTB = 0b0000010000000000;
   delay_ms(500);
   PORTB = 0b0000100000000000;
   delay_ms(500);
   PORTB = 0b0001000000000000;
   delay_ms(500);
   PORTB = 0b0010000000000000;
   delay_ms(500);
   PORTB = 0b0100000000000000;
   delay_ms(500);
   PORTB = 0b1000000000000000;
   delay_ms(500);
  PORTB = 0b0000000000000000;
   delay_ms(1000);
   */
   
}
   
   
}
