#include <p18f25k80.h>
#include <delays.h>
//#include "myFUSES.h"

#pragma config RETEN = OFF      // VREG Sleep Enable bit (Ultra low-power regulator is Disabled (Controlled by REGSLP bit))
#pragma config INTOSCSEL = HIGH // LF-INTOSC Low-power Enable bit (LF-INTOSC in High-power mode during Sleep)
#pragma config SOSCSEL = HIGH   // SOSC Power Selection and mode Configuration bits (High Power SOSC circuit selected)
#pragma config XINST = OFF       // Extended Instruction Set (Enabled)

// CONFIG1H
#pragma config FOSC = HS1       // Oscillator (HS oscillator (Medium power, 4 MHz - 16 MHz))
#pragma config PLLCFG = OFF     // PLL x4 Enable bit (Disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor (Disabled)
#pragma config IESO = OFF       // Internal External Oscillator Switch Over Mode (Disabled)

// CONFIG2L
#pragma config PWRTEN = OFF     // Power Up Timer (Disabled)
#pragma config BOREN = SBORDIS  // Brown Out Detect (Enabled in hardware, SBOREN disabled)
#pragma config BORV = 3         // Brown-out Reset Voltage bits (1.8V)
#pragma config BORPWR = ZPBORMV // BORMV Power level (ZPBORMV instead of BORMV is selected)

// CONFIG2H
#pragma config WDTEN = SWDTDIS  // Watchdog Timer (WDT enabled in hardware; SWDTEN bit disabled)
#pragma config WDTPS = 1048576  // Watchdog Postscaler (1:1048576)

// CONFIG3H
#pragma config CANMX = PORTB    // ECAN Mux bit (ECAN TX and RX pins are located on RB2 and RB3, respectively)
#pragma config MSSPMSK = MSK7   // MSSP address masking (7 Bit address masking mode)
#pragma config MCLRE = ON       // Master Clear Enable (MCLR Enabled, RE3 Disabled)

// CONFIG4L
#pragma config STVREN = ON      // Stack Overflow Reset (Enabled)
#pragma config BBSIZ = BB2K     // Boot Block Size (2K word Boot Block size)

// CONFIG5L
#pragma config CP0 = OFF        // Code Protect 00800-01FFF (Disabled)
#pragma config CP1 = OFF        // Code Protect 02000-03FFF (Disabled)
#pragma config CP2 = OFF        // Code Protect 04000-05FFF (Disabled)
#pragma config CP3 = OFF        // Code Protect 06000-07FFF (Disabled)

// CONFIG5H
#pragma config CPB = OFF        // Code Protect Boot (Disabled)
#pragma config CPD = OFF        // Data EE Read Protect (Disabled)

// CONFIG6L
#pragma config WRT0 = OFF       // Table Write Protect 00800-03FFF (Disabled)
#pragma config WRT1 = OFF       // Table Write Protect 04000-07FFF (Disabled)
#pragma config WRT2 = OFF       // Table Write Protect 08000-0BFFF (Disabled)
#pragma config WRT3 = OFF       // Table Write Protect 0C000-0FFFF (Disabled)

// CONFIG6H
#pragma config WRTC = OFF       // Config. Write Protect (Disabled)
#pragma config WRTB = OFF       // Table Write Protect Boot (Disabled)
#pragma config WRTD = OFF       // Data EE Write Protect (Disabled)

// CONFIG7L
#pragma config EBTR0 = OFF      // Table Read Protect 00800-03FFF (Disabled)
#pragma config EBTR1 = OFF      // Table Read Protect 04000-07FFF (Disabled)
#pragma config EBTR2 = OFF      // Table Read Protect 08000-0BFFF (Disabled)
#pragma config EBTR3 = OFF      // Table Read Protect 0C000-0FFFF (Disabled)

// CONFIG7H
#pragma config EBTRB = OFF      // Table Read Protect Boot (Disabled)

#define CLK PORTCbits.RC3
#define DAT PORTCbits.RC5
#define CS1 PORTBbits.RB4


void delay(void)
{
  unsigned char i,j;
  for(i=0;i<200;i++)
  {
    j++;
  }
}

void init_command(unsigned int command_data)
{
  unsigned int i,j;
  command_data=command_data&0xfff;
  command_data=command_data<<4;
  CS1=1;
  Delay1TCY();
  CS1=0;
      for(i=0;i<12;i++)
  {
    CLK=0;
    j=command_data&0x8000;
    command_data=command_data<<1;
    j=j>>15;
    DAT=j;
    CLK=1;
  }
  CS1=1;
}

void set2416(void)
{
  //sys en
  init_command(0b100000000010);
  //led on
  init_command(0b100000000110);
  //blink on
//  init_command(0b100000010010);
  //master mode
  init_command(0b100000101110);
  //RC
  init_command(0b100000110110);
  //commons option
  //init_command(0b100001011110);//2416
  init_command(0b100001010110);//0832
  //pwm duty
  init_command(0b100101111110);
}

void MCU_Address_2416(unsigned char address)
{
  unsigned char i,temp;

  temp = 0x40;                                          //address has 7 bits. MSB fisrt

  for(i=0;i<7;i++)
  {
    CLK= 0;          //clk = 0 for data ready
              if((temp & address) == 0)
      DAT= 0;
    else
      DAT= 1;
    CLK= 1;        //clk = 1 for data write into 1632
    temp >>= 1;
  }
}


void MCU_Data_0832(unsigned char Data1,unsigned char Data2)
{
  unsigned char i,j,databuffer;
  for(j=0;j<4;j++)
  {
    databuffer=Data1;
          for(i=0 ; i<8 ; i++)
    {
      CLK=0;        //clk = 0 for data ready
          if(databuffer & 0x80)
            DAT=1;
      else
        DAT=0;
                  CLK=1;                          //clk = 1 for data write into 2
      databuffer=databuffer<<1;
    }
        databuffer=Data2;
          for(i=0 ; i<8 ; i++)
    {
      CLK=0;        //clk = 0 for data ready
          if(databuffer & 0x80)
            DAT=1;
      else
        DAT=0;
                  CLK=1;                          //clk = 1 for data write into 2
      databuffer=databuffer<<1;
    }

  }
}


void senddata1(void)
{
  unsigned char i,data1,data2;


        CS1=1;
      delay();
       CS1=0;
            delay();

      CLK=0;
      DAT=1;
      CLK=1;


      CLK=0;
      DAT=0;
      CLK=1;


      CLK=0;
      DAT=1;
      CLK=1;



 MCU_Address_2416(0x00);
            data1=0x55;
            data2=0x55;

        for(i=0;i<4;i++)
        MCU_Data_0832(data1,data2);


        delay();
            CS1=1;
}


void main(void) {
    //TRISA = 0x00;
    TRISCbits.TRISC3 = 0;
    TRISCbits.TRISC5 = 0;
    TRISBbits.TRISB4 = 0;
    set2416();
    delay();
    while(1){

             senddata1();
             Delay100TCYx(10);
    
    }
    

}
