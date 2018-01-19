#include <18F25K80.h>
#device adc=16

#FUSES NOWDT                    //No Watch Dog Timer
//#FUSES WDT128                 //Watch Dog Timer uses 1:128 Postscale
#FUSES NOXINST                  //Extended set extension and Indexed Addressing mode disabled (Legacy mode)
#FUSES HSH                      //High speed Osc, high power 16MHz-25MHz
#FUSES NOBROWNOUT               //No brownout reset
#FUSES WDT_NOSLEEP              //Watch Dog Timer, disabled during SLEEP
#FUSES  PLLEN                   //4X HW PLL enabled

#use delay(clock=40M)
#use I2C(master, scl=PIN_C3, sda=PIN_C4, fast=400000)


#BYTE TRISA = 0xF92
#BYTE TRISB = 0xF93
#BYTE TRISC = 0xF94 

#BYTE PORTA = 0xF80
#BYTE PORTB = 0xF81
#BYTE PORTC = 0xF82 

#BYTE SSPCON2 = 0xFC5       //
#BYTE SSPCON1 = 0xFC6       //i2c config
#BYTE SSPSTAT = 0xFC7       // 
#BYTE SSPADD = 0xFC8        //       
#BYTE SSPBUF = 0xFC9        //

#BIT BF = SSPSTAT.0       // buf wr status, 1 - writing is in progress

#BIT SEN = SSPCON2.0       // i2c start en, 1 - start
#BIT RSEN = SSPCON2.1      // i2c repeited start en
#BIT PEN = SSPCON2.2       // i2c stop en
#BIT RCEN = SSPCON2.3      // i2c receive enable bit
#BIT ACKEN = SSPCON2.4      // i2c acknowledge sequence en bit
#BIT ACKDT = SSPCON2.5      // i2c acknowledge data bit, 1 - not acknowl, 0 - acknowl
#BIT ACKSTAT = SSPCON2.6    // i2c acknowledge status, 1 - not acknowl, 0 - acknowl
 
#BIT RA0 = PORTA.0
#BIT RA1 = PORTA.1
#BIT RA2 = PORTA.2
#BIT RA3 = PORTA.3
#BIT RA4 = PORTA.4
#BIT RA5 = PORTA.5

#BIT TRA5 = TRISA.5
#BIT TRA4 = TRISA.4
#BIT TRA3 = TRISA.3
#BIT TRA2 = TRISA.2
#BIT TRA1 = TRISA.1
#BIT TRA0 = TRISA.0

#BIT TRC5 = TRISC.5
#BIT TRC3 = TRISC.3
#BIT TRC4 = TRISC.4
#BIT TRC6 = TRISC.6
#BIT TRC7 = TRISC.7

#BIT RC3 = PORTC.3
#BIT RC4 = PORTC.4
#BIT RC5 = PORTC.5
#BIT RC6 = PORTC.6
#BIT RC7 = PORTC.7


void main()
{
   
   TRC3 = 1;
   TRC4 = 1;
   
   setup_timer_3(T3_DISABLED | T3_DIV_BY_1);
   setup_timer_4(T4_DISABLED,0,1);

   setup_comparator(NC_NC_NC_NC);// This device COMP currently not supported by the PICWizard

   while(TRUE)
   {
      i2c_start();
     //i2c_read();     // Device address
      //i2c_stop();      
   }

}
