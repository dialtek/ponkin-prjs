//#FUSES WPRES32                //Watch Dog Timer PreScalar 1:32
//#FUSES WPOSTS1                //Watch Dog Timer PostScalar 1:1
//#FUSES PROTECT_HIGH           //General Segment Code Protect High Security
//#FUSES CKSFSM                 //Clock Switching is enabled, fail Safe clock monitor is enabled
#FUSES NOWDT                    //No Watch Dog Timer
//#FUSES PR                        //Primary Oscillator
#FUSES PR_PLL                  //Primary Oscillator with PLL
#FUSES HS                       // High speed Osc (> 4mhz for PCM/PCH) (>10mhz for PCD)
#use delay(clock=80M)
#use rs232(UART2,baud=9600,parity=N,bits=8)
//#use spi(spi2, BAUD=100000, DI=PIN_G7, DO=PIN_G8, CLK=PIN_G6, ENABLE=PIN_B2, BITS=8)
#use spi(spi2, FORCE_HW)

#WORD AD1PCFGL=0x032C
#WORD ADCFGL=AD1PCFGL
#WORD AD1PCFGH=0x032A
#WORD ADCFGH=AD1PCFGH

#use fixed_io(B_outputs=PIN_B1, PIN_B2)

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

#WORD PLLFBD=0x0746 // osc PLL div reg
#WORD U2BRG=0x0238
#WORD U2MODE=0x0230

#WORD SPI2STAT=0x0260
#BIT SPIEN=SPI2STAT.15 //1  = Enables module and configures SCKx, SDOx, SDIx and SSx as serial port pins
#BIT SPIROV=SPI2STAT.6 // Receive Overflow Flag bit
                       // 1   =  A  new  byte/word  is  completely  received  and  discarded.  The  user  software  has  not  read  the
                       //previous data in the SPIxBUF register 0  = No overflow has occurred

#BIT SPITBF=SPI2STAT.1 //SPIx Transmit Buffer Full Status bit
                       //1  = Transmit not yet started, SPIxTXB is full
                       //0  = Transmit started, SPIxTXB is empty
                       //Automatically set in hardware when CPU writes SPIxBUF location, loading SPIxTXB.
                       //Automatically cleared in hardware when SPIx module transfers data from SPIxTXB to SPIxSR.

#BIT SPIRBF=SPI2STAT.0 //SPIx Receive Buffer Full Status bit
                       //1  = Receive complete, SPIxRXB is full
                       //0  = Receive is not complete, SPIxRXB is empty
                       //Automatically set in hardware when SPIx transfers data from SPIxSR to SPIxRXB.
                       //Automatically cleared in hardware when core reads SPIxBUF location, reading SPIxRXB.
#BYTE RegValue = 0x00
#BIT  ADC_DRDY = RegValue.0

                     
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

#WORD SPI2CON1=0x0262
#WORD SPI2CON2=0x0264
#WORD SPI2BUF=0x0268

#WORD PORTB=0x02C8
#WORD TRISB=0x02C6
#WORD LATB=0x02CA
#BIT  TRB0=TRISB.0
#BIT  TRB1=TRISB.1
#BIT  TRB5=TRISB.5
#BIT  TRB14=TRISB.14
#BIT  TRB15=TRISB.15

#WORD PORTC=0x02CE
#WORD LATC=0x02D0
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
#BIT  TRD0=TRISD.0
#BIT  TRD1=TRISD.1
#BIT  TRD2=TRISD.2
#BIT  TRD3=TRISD.3
#BIT  TRD4=TRISD.4
#BIT  TRD5=TRISD.5
#BIT  TRD6=TRISD.6
#BIT  TRD7=TRISD.7
#BIT  TRD8=TRISD.8
#BIT  TRD9=TRISD.9
#BIT  TRD10=TRISD.10
#BIT  TRD11=TRISD.11

#BIT  RD0=LATD.0
#BIT  RD1=LATD.1
#BIT  RD2=LATD.2
#BIT  RD3=LATD.3
#BIT  RD4=LATD.4
#BIT  RD5=LATD.5
#BIT  RD6=LATD.6
#BIT  RD7=LATD.7
#BIT  RD8=LATD.8
#BIT  RD9=LATD.9
#BIT  RD10=LATD.10
#BIT  RD11=LATD.11
//_________________________________________________
#WORD PORTF=0x02E0
#WORD TRISF=0x02DE
#BIT  UART2_RX_TRIS=TRISF.4
#BIT  UART2_TX_TRIS=TRISF.5

#WORD PORTG=0x02E6
#WORD TRISG=0x02E4
#BIT RG0=LATG.0
#BIT RG1=LATG.1
#BIT RG2=LATG.2
#BIT RG3=LATG.3
#BIT RG15=LATG.15
#BIT SCK2=LATG.6 // SPI2 pins
#BIT SDI2=LATG.7
#BIT SDO2=LATG.8
#BIT SS2=LATG.9
#BIT SCK2_TRIS=TRISG.6 // SPI2 tris
#BIT SDI2_TRIS=TRISG.7
#BIT SDO2_TRIS=TRISG.8
//#BIT SS2_TRIS=TRISG.9

#define ADC_Dout SDI2 //םמדא Din ÌÊ
#define ADC_Din SDO2  //םמדא Dout ÌÊ


#BIT  ADC_RESET_TRIS=TRISB.3
#BIT  ADC_RESET=LATB.3
#BIT  ADC_SYNC_TRIS=TRISB.4
#BIT  ADC_SYNC=LATB.4

#BIT  SS2_TRIS=TRISB.2
#BIT  ADC_CS = LATB.2


typedef unsigned int16 U16;
typedef unsigned int8 U8;
typedef unsigned int32 U32;
typedef signed int16 S16;

unsigned int16 Buf;
#BIT Buf0=Buf.0
#BIT Buf1=Buf.1
#BIT Buf2=Buf.2
#BIT Buf3=Buf.3
#BIT Buf4=Buf.4
#BIT Buf5=Buf.5
#BIT Buf6=Buf.6
#BIT Buf7=Buf.7
#BIT Buf8=Buf.8
#BIT Buf9=Buf.9
#BIT Buf10=Buf.10
#BIT Buf11=Buf.11
#BIT Buf12=Buf.12
#BIT Buf13=Buf.13
#BIT Buf14=Buf.14
#BIT Buf15=Buf.15

static U16 BufG;/////////////////////////////////////////////////////////////////
#BIT   BufG4=BufG.4
#BIT   BufG5=BufG.5
#BIT   BufG6=BufG.6
#BIT   BufG7=BufG.7
#BIT   BufG8=BufG.8
#BIT LCD_D7=BufG.3
#BIT LCD_D6=BufG.2
#BIT LCD_D5=BufG.1
#BIT LCD_D4=BufG.0
#BIT LCD_RW=BufG.12
#BIT LCD_RS=BufG.13
#BIT LCD_E=BufG.14

static U16 BufB;
#BIT   BufB0=BufB.0
#BIT   BufB1=BufB.1
#BIT   BufB2=BufB.2
#BIT   BufB3=BufB.3
#BIT   BufB4=BufB.4
#BIT   BufB5=BufB.5
#BIT   BufB6=BufB.6
#BIT   BufB7=BufB.7
#BIT   BufB8=BufB.8
#BIT   BufB9=BufB.9
#BIT   BufB10=BufB.10
#BIT   BufB11=BufB.11
#BIT   BufB12=BufB.12
#BIT   BufB13=BufB.13
#BIT   BufB14=BufB.14
#BIT   BufB15=BufB.15

static U16 BufC;
#BIT   BufC0=BufC.0
#BIT   BufC1=BufC.1
#BIT   BufC2=BufC.2
#BIT   BufC3=BufC.3
#BIT   BufC4=BufC.4
#BIT   BufC5=BufC.5
#BIT   BufC6=BufC.6
#BIT   BufC7=BufC.7
#BIT   BufC8=BufC.8
#BIT   BufC9=BufC.9
#BIT   BufC10=BufC.10
#BIT   BufC11=BufC.11
#BIT   BufC12=BufC.12
#BIT   BufC13=BufC.13
#BIT   BufC14=BufC.14
#BIT   BufC15=BufC.15

static U16 BufD;
#BIT   BufD0=BufD.0
#BIT   BufD1=BufD.1
#BIT   BufD2=BufD.2
#BIT   BufD3=BufD.3
#BIT   BufD4=BufD.4
#BIT   BufD5=BufD.5
#BIT   BufD6=BufD.6
#BIT   BufD7=BufD.7
#BIT   BufD8=BufD.8
#BIT   BufD9=BufD.9
#BIT   BufD10=BufD.10
#BIT   BufD11=BufD.11
#BIT   BufD12=BufD.12
#BIT   BufD13=BufD.13
#BIT   BufD14=BufD.14
#BIT   BufD15=BufD.15

static U16 BufF;
#BIT   BufF0=BufF.0
#BIT   BufF1=BufF.1
#BIT   BufF2=BufF.2
#BIT   BufF3=BufF.3
#BIT   BufF4=BufF.4
#BIT   BufF5=BufF.5
#BIT   BufF6=BufF.6
#BIT   BufF7=BufF.7
#BIT   BufF8=BufF.8
#BIT   BufF9=BufF.9
#BIT   BufF10=BufF.10
#BIT   BufF11=BufF.11
#BIT   BufF12=BufF.12
#BIT   BufF13=BufF.13
#BIT   BufF14=BufF.14
#BIT   BufF15=BufF.15

#define FCY      40000000
#define BAUDRATE 9600                
#define BRGVAL   ((FCY/BAUDRATE)/16)-1



