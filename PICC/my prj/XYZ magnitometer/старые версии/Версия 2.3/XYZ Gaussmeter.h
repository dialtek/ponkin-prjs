#include <18F25K80.h>
//#device ADC=16

#FUSES NOWDT                      //Watch Dog Timer
//#FUSES WDT4096                  //Watch Dog Timer uses 1:4096 Postscale
#FUSES SOSC_DIG                 //Digital mode, I/O port functionality of RC0 and RC1
#FUSES NOXINST                  //Extended set extension and Indexed Addressing mode disabled (Legacy mode)
#FUSES NOBROWNOUT               //No brownout reset
//#fuses NOPLLEN                   //HW PLL disabled, PLL enabled in software
#fuses HSM                       //High speed Osc, medium power 4MHz-16MHz
//#fuses PLLEN                     //HW PLL enabled
#fuses NOPLLEN                     //HW PLL disabled, PLL enabled in software

#use delay(clock=10MHz,crystal=10MHz) // �������!!!!

//#use FIXED_IO( B_outputs=PIN_B6,PIN_B5,PIN_B4,PIN_B3,PIN_B0 )
//#use FIXED_IO( C_outputs=PIN_C6 )
//#use FIXED_IO( C_outputs=PIN_C6 )

#define RA0   PIN_A0
#define RA1   PIN_A1
#define RA2   PIN_A2
#define RA3   PIN_A3
#define RA4   PIN_A4
#define RA5   PIN_A5
#define RA6   PIN_A6
#define RA7   PIN_A7

//#define DRDY   PIN_B0
#define RB1   PIN_B1
#define RB2   PIN_B2
#define RB6   PIN_B6
#define RB7   PIN_B7
//#define SCL   PIN_C3
//#define SDA   PIN_C4
/*
#define LCD_E PIN_B3
#define LCD_RS PIN_B5
#define LCD_RW PIN_B4
#define DB4 PIN_C5
#define DB5 PIN_C2
#define DB6 PIN_C1
#define DB7 PIN_C0
*/
#BYTE TRISA = 0xF92
#BYTE TRISB = 0xF93
#BYTE TRISC = 0xF94
#BYTE PORTA = 0xF80
#BYTE PORTB = 0xF81
#BYTE PORTC = 0xF82 
#BYTE LATB = 0xF8A
#BYTE LATC = 0xF8B

#BYTE INTCON = 0xFF2    // �������� ������������ ����������
#BYTE INTCON2= 0xFF1

#BIT TRA3 = TRISA.3
#BIT TRB0 = TRISB.0
#BIT TRB3 = TRISB.3
#BIT TRB4 = TRISB.4
#BIT TRB5 = TRISB.5
#BIT TRC0 = TRISC.0
#BIT TRC1 = TRISC.1
#BIT TRC2 = TRISC.2
#BIT TRC3 = TRISC.3
#BIT TRC4 = TRISC.4
#BIT TRC5 = TRISC.5 
#BIT TRC6 = TRISC.6
#BIT TRC7 = TRISC.7

#BIT DRDY = PORTB.0

#BIT DB4 = LATC.5
#BIT DB5 = LATC.2
#BIT DB6 = LATC.1
#BIT DB7 = LATC.0

#BIT SDA_LAT = LATC.4

#BIT SW1 = PORTA.3
#BIT SW2 = PORTC.2
//#BIT SW3 = PORTC.5
//#BIT SW4 = PORTC.5

#BIT LCD_RS = LATB.5 
#BIT LCD_RW = LATB.4
#BIT LCD_E = LATB.3
#BIT LED = LATC.6
//#define RC6   PIN_C6

#use i2c(Master, sda = PIN_C4, scl = PIN_C3, SLOW)//Fast = 400000)

#use rs232(uart1,baud=9600,parity=N,xmit=PIN_C6,rcv=PIN_C7,bits=8)

//#define LED PIN_C6
#define DELAY 200

#define one   0x00
#define two   0x40

//#DEFINE DRDY RB0

//#define three 0x10
//#define four  0x50

typedef unsigned int32 U32;
typedef int16 U16;
typedef signed int16 S16;
typedef int8 U8;
typedef signed int32 S32;

static U8 buf;

#BIT buf4=buf.4
#BIT buf5=buf.5
#BIT buf6=buf.6
#BIT buf7=buf.7
