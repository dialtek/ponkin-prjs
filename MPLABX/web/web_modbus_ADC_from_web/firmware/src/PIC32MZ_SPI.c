#include "device.h"
#include "PIC32MZ_SPI.h"

// *****************************************************************************

void SPI1_init(void)
{
    SPI1CONbits.ON = 0; // Turn off spi module before initialization 
    IFS3CLR = _IFS3_SPI1EIF_MASK | _IFS3_SPI1RXIF_MASK;    //Clear the Interrupt Flag
    IEC3CLR = _IEC3_SPI1EIE_MASK | _IEC3_SPI1RXIE_MASK;    //Disable the Interrupt

    SPI1CONbits.DISSDO = 0;        //SDOx pin is controlled by the module
    SPI1CONbits.MODE16 = 0;        //Communication is word-wide (8 bits)
    SPI1CONbits.MODE32 = 0;        //
    SPI1CONbits.SMP = 1;           //Input Data is sampled at the middle of data output time
    SPI1CONbits.CKE = 0;           //Serial output data changes on transition from
    SPI1CONbits.CKP = 0;           //Serial output data changes on transition from
    SPI1CONbits.MCLKSEL = 0;       //PBCLK is used by the Baud Rate Generator
    SPI1BRG = 60;                  //Fsck=FPB/(2*(SPIxBRG + 1)) //Fsck = 833.3 kHz

    SPI1CONbits.MSTEN = 1;         //Master Mode Enabled
    SPI1CONbits.FRMEN = 0;         // CS(SS) Support bit; 0 = Framed SPIx support disable 

    SPI1CONbits.SIDL = 0; // Continue module operation in Idle mode
    SPI1STATbits.SPIROV = 0;  // No Receive Overflow has occurred     

    SPI1CONbits.ON = 1;         //Enable SPI Module
}

void SPI1_write_byte(unsigned char buf)               
{
     unsigned char temp;

     SPI1BUF = buf;
     
     while(!SPI1STATbits.SPIRBF);
     
     // РїРѕСЃР»Рµ Р·Р°РїРёСЃРё РЅРµРѕР±С…РѕРґРёР�?С‹ РІС‹С‡РёС‚Р°С‚СЊ СЃРѕРґРµСЂР¶Р°РЅРёРµ Р±СѓС„РµСЂР° SPI РґР»СЏ СЃР±СЂРѕСЃР° С„Р»Р°РіР°
     temp = SPI1BUF; 
     temp++; // РєРѕСЃС‚С‹Р»СЊ С‡С‚РѕР±С‹ СѓР±СЂР°С‚СЊ warninig ../src/app.c:34:20: error: variable 'temp' set but not used [-Werror=unused-but-set-variable]
     SPI1STATbits.SPIROV = 0;
 }

unsigned char SPI1_read_byte(void)
{
  
 unsigned int buf = 0; 

 if(SPI1STATbits.SPIROV) 
 { 
    buf = SPI1BUF; 
    SPI1STATbits.SPIROV = 0; 
    buf++;
 } 

  SPI1BUF = 0x00;                  // initiate bus cycle 
  
  while(!SPI1STATbits.SPIRBF);

  SPI1STATbits.SPIROV = 0;

  return (unsigned char)SPI1BUF;    /* return byte read */;
}

void SPI2_init(void)
{
    SPI2CONbits.ON = 0; // Turn off spi module before initialization 
    IFS4CLR = _IFS4_SPI2EIF_MASK | _IFS4_SPI2RXIF_MASK;    //Clear the Interrupt Flag
    IEC4CLR = _IEC4_SPI2EIE_MASK | _IEC4_SPI2RXIE_MASK;    //Disable the Interrupt

    SPI2CONbits.DISSDO = 0;        //SDOx pin is controlled by the module
    SPI2CONbits.MODE16 = 0;        //Communication is word-wide (8 bits)
    SPI2CONbits.MODE32 = 0;        //
    SPI2CONbits.SMP = 1;           //Input Data is sampled at the middle of data output time
    SPI2CONbits.CKE = 1;           //Serial output data changes on transition RE
    SPI2CONbits.CKP = 0;           //Serial output data changes on transition from
    SPI2CONbits.MCLKSEL = 0;       //PBCLK is used by the Baud Rate Generator
    SPI2BRG = 30;                  //Fsck=FPB/(2*(SPIxBRG + 1)) //Fsck = 1.6M

    SPI2CONbits.MSTEN = 1;         //Master Mode Enabled
    SPI2CONbits.FRMEN = 0;         // CS(SS) Support bit; 0 = Framed SPIx support disable 

    SPI2CONbits.SIDL = 0; // Continue module operation in Idle mode
    SPI2STATbits.SPIROV = 0;  // No Receive Overflow has occurred     

    SPI2CONbits.ON = 1;         //Enable SPI Module
}

void SPI2_write_byte(unsigned char buf)               
{
     unsigned char temp;

     SPI2BUF = buf;
     
     while(!SPI2STATbits.SPIRBF);
     
     // РїРѕСЃР»Рµ Р·Р°РїРёСЃРё РЅРµРѕР±С…РѕРґРёР�?С‹ РІС‹С‡РёС‚Р°С‚СЊ СЃРѕРґРµСЂР¶Р°РЅРёРµ Р±СѓС„РµСЂР° SPI РґР»СЏ СЃР±СЂРѕСЃР° С„Р»Р°РіР°
     temp = SPI2BUF; 
     temp++; // РєРѕСЃС‚С‹Р»СЊ С‡С‚РѕР±С‹ СѓР±СЂР°С‚СЊ warninig ../src/app.c:34:20: error: variable 'temp' set but not used [-Werror=unused-but-set-variable]
     SPI2STATbits.SPIROV = 0;
 }

unsigned char SPI2_read_byte(void)
{
  
 //unsigned int buf = 0; 

// if(SPI2STATbits.SPIROV) 
// { 
//    buf = SPI2BUF; 
//    SPI2STATbits.SPIROV = 0; 
//    buf++; // костыль, причина - проблемы компиляции - неиспользуемая пер. buf без этой строки
// } 

  SPI2BUF = 0x00;                  // initiate bus cycle 
  
 // while(!SPI2STATbits.SPIRBF);
  while(SPI2STATbits.SPIBUSY);

  SPI2STATbits.SPIROV = 0;

  return (unsigned char)SPI2BUF;    /* return byte read */;
}

//void __ISR(_SPI1_RX_VECTOR, IPL6AUTO) _SPI1_RX_Interrupt(void)    
//   {
//       IFS3CLR = _IFS3_SPI1RXIF_MASK; //clear flag
//   }

// *****************************************************************************
