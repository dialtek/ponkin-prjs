#include "FreeRTOS.h"
#include "d_SPI.h"
/*=========================================================================== */
// SPI2 - serial EEPROM

void SPI2_init(void)
{
    SPI2STATbits.SPIEN = 0;         // Turn off spi module before initialization 
    IFS2bits.SPI2EIF   = 0;         // Clear the Interrupt Flag
    IFS2bits.SPI2IF = 0;            // Disable the Interrupt
    // SPI2CON1 Register Settings:
    SPI2CON1bits.DISSCK = 0;        //Internal Serial Clock is Enabled
    SPI2CON1bits.DISSDO = 0;        //SDOx pin is controlled by the module
    SPI2CON1bits.MODE16 = 0;        //Communication is byte-wide (8 bits)
    SPI2CON1bits.SMP = 1;           //Input Data is sampled at the end of data output time
    SPI2CON1bits.CKE = 1;           // Serial output data changes on transition from active clock state to Idle clock state
    SPI2CON1bits.CKP = 0;           // Idle state for clock is a low level; active state is a high level

    // SPI2STAT Register Settings
    SPI2STATbits.SPISIDL = 0; // Continue module operation in Idle mode
    SPI2STATbits.SPIROV = 0;  // No Receive Overflow has occurred

    // SPI2 SCK f = 1M @ 80M Fosc, Fcy 40M  
    // Fsck = 833.3 kHz
    SPI2CON1bits.SPRE = 5;          //Secondary prescale 3:1
    SPI2CON1bits.PPRE = 1;          //Primary prescale 16:1

    SPI2CON2bits.FRMEN = 0;         //Framed SPIx support is disabled
    SPI2CON1bits.MSTEN = 1;         //Master Mode Enabled

    SPI2STATbits.SPIEN = 1;         //Enable SPI Module
                                //Interrupt Controller Settings
}

volatile void SPI2_write_byte (unsigned char buf)
{
    unsigned char temp;

    SPI2BUF = buf;

    while(!SPI2STATbits.SPIRBF);

    // reading register to clear it
    temp = SPI2BUF; 

    SPI2STATbits.SPIROV = 0;
}

volatile unsigned char SPI2_read_byte(void)
{
 unsigned char ret_value = 0;
  
 unsigned int buf = 0; 

 if(SPI2STATbits.SPIROV) 
 { 
    buf = SPI2BUF; 
    SPI2STATbits.SPIROV = 0; 
 } 

  SPI2BUF = 0x00;      // initiate bus cycle 
  
  while(!SPI2STATbits.SPIRBF);

  SPI2STATbits.SPIROV = 0;
  ret_value = SPI2BUF;    /* return byte read */

  return ret_value;     
}

// SPI
/*=========================================================================== */