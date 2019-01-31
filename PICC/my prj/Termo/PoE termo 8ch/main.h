#include <24HJ128GP506.h>


//#FUSES PROTECT_HIGH            //General Segment Code Protect High Security
#FUSES WRTB                      //Boot block write protected
#FUSES CKSFSM                    //Clock Switching is enabled, fail Safe clock monitor is enabled
#FUSES WDT                       //no Watch Dog Timer
#FUSES WPOSTS14                  //Watch Dog Timer PreScalar 1:8192
#FUSES PR_PLL                    //Primary Oscillator with PLL
#FUSES HS                        //High speed Osc (> 4mhz for PCM/PCH) (>10mhz for PCD)
#FUSES NOPROTECT                 //Code not protected from reading
#FUSES NOWRT                     //Program memory not write protected
#use delay(clock=40M)

#WORD PLLFBD=0x0746 // osc PLL div reg

#WORD CLKDIV=0x0744  // osc con reg
#BIT PLLPOST1=CLKDIV.7
#BIT PLLPOST0=CLKDIV.6
#BIT PLLPRE4=CLKDIV.4
#BIT PLLPRE3=CLKDIV.3
#BIT PLLPRE2=CLKDIV.2
#BIT PLLPRE1=CLKDIV.1
#BIT PLLPRE0=CLKDIV.0

#WORD LATA=0x02C4 
#WORD LATB=0x02CA
#WORD LATD=0x02D6
#WORD LATF=0x02E2
#WORD LATG=0x02E8  
#WORD LATC=0x02D0

#use spi(spi2, FORCE_HW)
#use standard_io(B)//(B_outputs=PIN_B1, PIN_B2)

#define STATUS 0x00     // ADC1256 Register map
#define MUX 0x01 
#define ADCON 0x02
#define DRATE 0x03
#define IO 0x04
#define OFCO 0x05
#define OFC1 0x06
#define OFC2 0x07
#define FSCO 0x08
#define FSC1 0x09
#define FSC2 0x0A
#define uV 10000000  // для калибровки 
//#define uV 100000 // по умолчанию
#define mV 1000

#WORD PORTB=0x02C8
#WORD TRISB=0x02C6
#BIT  TRB0=TRISB.0
#BIT  TRB1=TRISB.1
#BIT  CN1_TRIS=TRISB.5
#BIT  CN2_TRIS=TRISB.4
#BIT  CN4_TRIS=TRISB.3
#BIT  CN3_TRIS=TRISB.2
#BIT  CN1=PORTB.5
#BIT  CN4=PORTB.3
#BIT  CN2=PORTB.4
#BIT  CN3=PORTB.2
#BIT  XPORT_RST_n=TRISB.15
#BIT  Status_LED_TRIS=TRISB.13
#BIT  TRB14=TRISB.14
#BIT  XPORT_RST_TRIS=TRISB.15
#BIT  RB1=LATB.1
#BIT  RB0=LATB.0
#BIT  Status_LED=LATB.13

#WORD PORTC=0x02CE
#WORD TRISC=0x02CC
//#BIT RC13=LATC.13
//#BIT RC14=LATC.14
#BIT RC13=PORTC.13
#BIT RC14=PORTC.14
#BIT  TRC13=TRISC.13
#BIT  TRC14=TRISC.14
#BIT  TRC1=TRISC.1
#BIT  TRC2=TRISC.2
#BIT  TRC4=TRISC.4
//_______________________________________
#WORD PORTD=0x02D4
#WORD TRISD=0x02D2
#WORD ODCD=0x06D2

#BIT  TRD4=TRISD.4
#BIT  TRD5=TRISD.5
#BIT  TRD6=TRISD.6
#BIT  TRD7=TRISD.7
#BIT  TRD8=TRISD.8

#BIT  RD4=LATD.4
#BIT  RD5=LATD.5
#BIT  RD6=LATD.6
#BIT  RD7=LATD.7
#BIT  RD8=LATD.8
//_________________________________________________
#WORD PORTF=0x02E0
#WORD TRISF=0x02DE
#BIT  UART2_RX_TRIS=TRISF.4
#BIT  UART2_TX_TRIS=TRISF.5

#WORD PORTG=0x02E6
#WORD TRISG=0x02E4
#BIT RG0=LATG.0
#BIT RG1=LATG.1
#BIT LCD_RW=LATG.12
#BIT LCD_RS=LATG.13
#BIT LCD_E=LATG.14
#BIT RG15=LATG.15
#BIT SCK2=LATG.6 // SPI2 pins
#BIT SDI2=LATG.7
#BIT SDO2=LATG.8
//#BIT SS2=LATG.9
#BIT SCK2_TRIS=TRISG.6 // SPI2 tris
#BIT SDI2_TRIS=TRISG.7
#BIT SDO2_TRIS=TRISG.8
#BIT TRG0=TRISG.0
#BIT TRG1=TRISG.1
#BIT LCD_RW_TRIS=TRISG.12
#BIT LCD_RS_TRIS=TRISG.13
#BIT LCD_E_TRIS=TRISG.14

//#BIT SS2_TRIS=TRISG.9

#define ADC_Dout SDI2 //???? Din ??
#define ADC_Din SDO2  //???? Dout ??

#BIT  ADC_RESET_TRIS=TRISD.3
#BIT  ADC2_RESET_TRIS=TRISD.0
#BIT  ADC_RESET=LATD.3
#BIT  ADC2_RESET=LATD.0

#BIT  ADC_SYNC_TRIS=TRISD.2
#BIT  ADC2_SYNC_TRIS=TRISD.11
#BIT  ADC_SYNC=LATD.2
#BIT  ADC2_SYNC=LATD.11

#BIT  ADC_CS_TRIS =TRISG.9
#BIT  ADC2_CS_TRIS=TRISD.10
#BIT  ADC_CS = LATG.9
#BIT  ADC2_CS= LATD.10

#BIT  ADC_DRDY_TRIS = TRISD.1
#BIT  ADC2_DRDY_TRIS= TRISD.9
#BIT  ADC_DRDY = PORTD.1
#BIT  ADC2_DRDY= PORTD.9

#WORD U2TXREG = 0x0234 
#WORD U2RXREG = 0x0236 // регистр принимаемых Uart2 данных  
#Word U2STA = 0x0232
#WORD U2BRG=0x0238
#WORD U2MODE=0x0230
#WORD U2STA=0x0232
#BIT  U2_TRMT  = U2STA.8   // Transmit Shift Register is Empty bit (read-only)
#BIT  U2_UTXBF = U2STA.9   // Transmit Buffer Full Status bit (read-only)
#BIT  U2_UTXEN = U2STA.10  // Transmit Enable bit

#define FCY      40000000
#define BAUDRATE 230400                
#define BRGVAL   ((FCY/BAUDRATE)/16)-1

#define CK_FLASH_END       (getenv("PROGRAM_MEMORY")-1)      
#define CK_FLASH_PAGE_SIZE (getenv("FLASH_ERASE_SIZE")/2) 
#define CK_NUM_PAGES (CK_FLASH_END/CK_FLASH_PAGE_SIZE) 

#define CK_USER_PAGE (CK_FLASH_PAGE_SIZE*(CK_NUM_PAGES-1)) 

#org CK_USER_PAGE,CK_FLASH_END {} 

   typedef unsigned int16 U16;
   typedef unsigned int8 U8;
   typedef unsigned int32 U32;
   typedef signed int32 S32;
   typedef signed int16 S16;
   typedef signed int8 S8;

