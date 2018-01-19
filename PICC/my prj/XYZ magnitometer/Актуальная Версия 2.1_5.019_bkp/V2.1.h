#include <18F25K80.h>
//#device ADC=16

#FUSES NOWDT                      //No Watch Dog Timer
//#FUSES WDT8192                  //Watch Dog Timer uses 1:4096 Postscale
#FUSES SOSC_DIG                 //Digital mode, I/O port functionality of RC0 and RC1
#FUSES NOXINST                  //Extended set extension and Indexed Addressing mode disabled (Legacy mode)
#FUSES NOBROWNOUT               //No brownout reset
#fuses HSM                       //High speed Osc, medium power 4MHz-16MHz
#fuses NOPLLEN                     //HW PLL disabled, PLL enabled in software

#use delay(clock=10MHz,crystal=10MHz)

#BYTE TRISA = 0xF92
#BYTE TRISB = 0xF93
#BYTE TRISC = 0xF94
#BYTE PORTA = 0xF80
#BYTE PORTB = 0xF81
#BYTE PORTC = 0xF82 
#BYTE LATB = 0xF8A
#BYTE LATC = 0xF8B

#BYTE INTCON = 0xFF2    // ???????? ???????????? ??????????
#BYTE INTCON2= 0xFF1
 
#BIT TRC7 = TRISC.7

/****** TEST ******/
#BIT TRC6 = TRISC.6
//#BIT TEST_PIN = LATC.6
/******************/

/****** SWITCHS ******/
#BIT TRA0 = TRISA.0
#BIT TRA3 = TRISA.3
#BIT TRA5 = TRISA.5
#BIT TRB2 = TRISB.2
#BIT SB1 = PORTA.0
#BIT SB2 = PORTA.3
#BIT SB3 = PORTB.2
#BIT SB4 = PORTA.5
/*********************/

/****** LCD ******/
#BIT TRB1 = TRISB.1
#BIT TRB3 = TRISB.3
#BIT TRB4 = TRISB.4
#BIT TRB5 = TRISB.5
#BIT TRC0 = TRISC.0
#BIT TRC1 = TRISC.1
#BIT TRC2 = TRISC.2
#BIT TRC5 = TRISC.5
#BIT DB4 = LATC.5
#BIT DB5 = LATC.2
#BIT DB6 = LATC.1
#BIT DB7 = LATC.0
#BIT LCD_RS = LATB.5 
#BIT LCD_RW = LATB.4
#BIT LCD_E = LATB.3
#BIT LED = LATB.1
/*****************/

/****** SENSOR ******/
#BIT TRB0 = TRISB.0
#BIT DRDY = PORTB.0
#BIT TRC3 = TRISC.3
#BIT TRC4 = TRISC.4
#use i2c(Master, sda = PIN_C4, scl = PIN_C3, Fast = 400000)
/********************/

#use rs232(uart1,baud=9600,parity=N,xmit=PIN_C6,rcv=PIN_C7,bits=8)

#define DELAY 200

#define one   0x00
#define two   0x40
#define three 0x10
#define four  0x50

typedef unsigned int32 U32;
typedef int16 U16;
typedef signed int16 S16;
typedef int8 U8;
typedef signed int32 S32;

static U8 buf;

#BIT buf4 = buf.4
#BIT buf5 = buf.5
#BIT buf6 = buf.6
#BIT buf7 = buf.7


