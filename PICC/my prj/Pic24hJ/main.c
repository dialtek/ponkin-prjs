#include <24HJ128GP506.h>
#include <Termo3.h>
#include <LCD_16X4_Termo3.h>

   U32 ADC_RByte1,ADC_RByte2,ADC_RByte3 = 0;
   U32 ADC_RByte_Sum = 0;

   void OscSetup(){
  //Fcy=Fosc/2
  //Fin=10M
  //Fosc=Fin(M/(N1*N2))
  U2BRG = 259;// BAUD Rate Setting for 9600
  U2MODE = 0b1010101010010000;
  PLLFBD = 30; // уст. коэф. формулы PLL M = 30
  
  PLLPRE4 = 0; // уст. коэф. формулы PLL N1 = 2
  PLLPRE3 = 0;
  PLLPRE2 = 0;
  PLLPRE1 = 0;
  PLLPRE0 = 0;
  
  PLLPOST0=0; // уст. коэф. формулы PLL N2 = 2
  PLLPOST1=0;
    
   }

   void SPI2_setup(){
   
   SPIEN = 1;
   SPI2CON1 = 0b0000001110100000;
   SPI2CON2 = 0b1000000000000000;  
   } 
 
/***************** ADC1256 functions *****************/


static int1 RdStatus()
{
   //U8 RegValue = 0;
   //1st Command Byte: 0001 rrrr where rrrr is the address of the first register to read.
   //2nd Command Byte: 0000 nnnn where nnnn is the number of bytes to read Ц 1
   ADC_CS = 0;
   delay_us(1);
   Spi_write2(0x10); // 1st Command Byte,команда записи
   Spi_write2(0x00); // 1st Command Byte, читаем только один байт
   delay_us(8); // 50 CLK_IN PEDIODS
   RegValue = Spi_read2(0);
   delay_us(1);
   ADC_CS =1;
   delay_us(1);
   Return ADC_SYNC;  
}

static U8 RdReg(U8 RegName)
{
   //U8 RegValue = 0; 
   //1st Command Byte: 0001 rrrr where rrrr is the address of the first register to read.
   //2nd Command Byte: 0000 nnnn where nnnn is the number of bytes to read Ц 1
   ADC_CS = 0;
   delay_us(1);
   Spi_write2(0x10+RegName); // 1st Command Byte,команда чтени€
   Spi_write2(0x00); // 1st Command Byte, читаем только один байт
   delay_us(8); // 50 CLK_IN PEDIODS
   RegValue = Spi_read2(0);
   delay_us(1);
   ADC_CS =1;
   delay_us(1);
   Return RegValue;  
}

static void WrReg(U8 RegName,CommandByte)
{
   ADC_CS = 0;
   delay_us(1);
   Spi_write2(0b0101+RegName); // 1st Command Byte: 0101 (0x50) rrrr where rrrr is the address to the first register to be written.
   Spi_write2(0);         // 2nd Command Byte: 0000 nnnn where nnnn is the number of bytes to be written Ц 1.
   Spi_write2(CommandByte);
   delay_us(1);
   ADC_CS = 1;
   delay_us(20);
}

static void ADC_Init(U8 StartRegId,CommandByte1,CommandByte2,CommandByte3,CommandByte4)

{

   ADC_CS = 0;
   delay_us(1);
   Spi_write2(0x50+StartRegId); // 1st Command Byte: 0101 (0x50) rrrr where rrrr is the address to the first register to be written.
   Spi_write2(3);         // 2nd Command Byte: 0000 nnnn where nnnn is the number of bytes to be written Ц 1.
   Spi_write2(CommandByte1);
   Spi_write2(CommandByte2);
   Spi_write2(CommandByte3);
   Spi_write2(CommandByte4);
   delay_us(1);
   ADC_CS = 1;
   
}

static U32 ADC_RDataC()
     {
     ADC_CS = 0;
     delay_us(10);
     Spi_write2(0x03);
     ADC_CS = 1;
     delay_ms(22); // 50 clk periods
    // l1:
     //RdReg(STATUS);
     //if(!ADC_SYNC){
     ADC_CS = 0;
     delay_us(10);
     ADC_Rbyte1 = Spi_read2(0);
     ADC_Rbyte2 = Spi_read2(0);
     ADC_Rbyte3 = Spi_read2(0);
     delay_us(10);
     ADC_CS = 1; 
     ADC_RByte_Sum = (ADC_Rbyte1<<16) + (ADC_Rbyte2<<8) + ADC_Rbyte3;
     return ADC_RByte_Sum;
    // }     
    // else goto l1;
     }

static U32 ADC_Rdata(){
      
     ADC_CS = 0;
     delay_us(1);
     Spi_write2(0x01);
     delay_us(1);
     ADC_CS = 1;
     delay_ms(30); // 
     ADC_CS = 0;
     delay_us(1);
     ADC_Rbyte1 = Spi_read2(0);
     ADC_Rbyte2 = Spi_read2(0);
     ADC_Rbyte3 = Spi_read2(0);
     ADC_CS = 1; 
     delay_ms(1);
     
     ADC_RByte_Sum = (ADC_Rbyte1<<16) + (ADC_Rbyte2<<8) + ADC_Rbyte3;
     return ADC_RByte_Sum;
}

/***************** ADC1256 functions *****************/

/*
#int_timer1
void  TIMER1_isr(void)
{
       set_timer1(65526); // 65536 отсчетов таймера -> 1 отсчет - 200 нс -> 10 отсчетов 2 мкс
     //прерывание по таймеру каждые 2 мкс, переполнение один раз вызывает прерывание
       RdReg(STATUS);
       RD1 = ADC_DRDY; // status.0 bit
       
      clear_interrupt(int_timer1);
}

*/
void main()
{   
 // unsignedint16 temp;
  
   OscSetup();
   // SPI2_setup();
   SETUP_SPI2(SPI_MASTER|SPI_SCK_IDLE_LOW|SPI_XMIT_H_TO_L|SPI_MODE_8B|SPI_SAMPLE_AT_END|SPI_SS_ENABLED|SPI_CLK_DIV_128);
   // f SCLK SPI = 312,5 к√ц
   
   //ENABLE_INTERRUPTS(INTR_GLOBAL);
  // ENABLE_INTERRUPTS(INT_TIMER1);
   
   //setup_timer1(TMR_INTERNAL|TMR_DIV_BY_8, 1); 
   // 65536 отсчетов таймера -> 1 отсчет - 200 нс -> 10 отсчетов 2 мкс
   // прерывание по таймеру каждые 2 мкс, переполнение один раз вызывает прерывание
   
   TRISG=0x0000; // LCD_RS,LCD-RW,LCD_E
   UART2_RX_TRIS = 0; //Xport tx
   UART2_TX_TRIS = 1; //Xport rx
   SCK2_TRIS=0; // SPI2 tris
   SDI2_TRIS=1;
   SDO2_TRIS=0;
   SS2_TRIS=0;
   ADC_RESET_TRIS = 0;
   ADC_SYNC_TRIS = 0;
      
   TRC13 = 0;
   TRC14 = 0;
   
   TRD1=0;

   LCDInit();
   LCDWelcome();
   
   ADC_CS = 1;
   ADC_RESET = 0; //When using the RESET pin, take it low to force a reset.
   delay_us(50);
   ADC_SYNC =1;
   delay_us(50);
   ADC_SYNC = 0; //To use the SYNC/PDWN pin, take it low and then high
   
   ADC_Init(STATUS,0x06,0x76,0x03,0x63);
   //Spi_write2(0xF0);
   //delay_ms(30);
 //WrReg(STATUS,0x06);
 //WrReg(MUX,0x76);
 //WrReg(ADCON,0x03);
 //WrReg(DRATE,0b01100011);  
       //t18
   //set_timer1(65526);
   //ADC_Dout SDI2 - нога Din ћ   
   //ADC_Din SDO2 - нога Dout ћ 
   
WHILE(1) {
        
     
    lcdsetcursor(0x00);
    LCDputU32(ADC_RDataC(),8);
    
    delay_ms(100);
     
     
     
    /* 
   
     ADC_CS = 0; 
     delay_us(1);
     //Spi_write2(0xFC); // SYNC
     SPI_Write2(0x01);
     delay_us(1);
     ADC_CS = 1;     
     delay_ms(22);
    // m1:
    // RdStatus();
    // if(!adc_drdy)
    // { 
     //Spi_write2(0);
     ADC_CS = 0; 
     delay_us(1);
     Spi_read2(0);
     Spi_read2(0);
     Spi_read2(0);
     delay_us(1);
     ADC_CS = 0; 
    // }
     //else goto m1;
    
 */
 
   
   
   
   }
}
