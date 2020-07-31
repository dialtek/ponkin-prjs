#include "xc.h"
#include "d_SPI.h"
#include "d_delay.h"

void SPI1_init()
{
        SPI1STATbits.SPIEN = 0;         // Turn off spi module before initialization 
        IFS0bits.SPI1EIF   = 0;         // Clear the Interrupt Flag
        IFS0bits.SPI1IF = 0;            // Disable the Interrupt
        // SPI2CON1 Register Settings:
        SPI1CON1bits.DISSCK = 0;        //Internal Serial Clock is Enabled
        SPI1CON1bits.DISSDO = 0;        //SDOx pin is controlled by the module
        SPI1CON1bits.MODE16 = 1;        //Communication is byte-wide (8 bits)
        SPI1CON1bits.SMP = 0;           //Input Data is sampled at the end of data output time
        SPI1CON1bits.CKE = 0;           // Serial output data changes on transition from active clock state to Idle clock state
        SPI1CON1bits.CKP = 0;           // Idle state for clock is a low level; active state is a high level
        
        // SPI1STAT Register Settings
        SPI1STATbits.SPISIDL = 0; // Continue module operation in Idle mode
        SPI1STATbits.SPIBEC = 0; // Buffer Length = 1 Word
        SPI1STATbits.SPIROV = 0; // No Receive Overflow has occurred
      
        // SPI1 SCK f = 30M @ 120M Fosc, Fcy 60M     
        //SPI3CON1bits.SPRE = 6;          //Secondary prescale 1:1
        //SPI3CON1bits.PPRE = 3;          //Primary prescale 1:1
        
        // SPI1 SCK f = 7.5M @ 120M Fosc, Fcy 60M     
        // SPI1CON1bits.SPRE = 6;          //Secondary prescale 1:1
        // SPI1CON1bits.PPRE = 2;          //Primary prescale 4:1
        
       // SPI1 SCK f = 3.75M @ 120M Fosc, Fcy 60M     
        SPI1CON1bits.SPRE = 4;          //Secondary prescale 4:1
        SPI1CON1bits.PPRE = 4;          //Primary prescale 4:1
        
        SPI1CON2bits.FRMEN = 0;         //Framed SPIx support is disabled
        SPI1CON2bits.SPIBEN = 0;        //Enhanced buffer is disabled (Legacy mode)
        SPI1CON1bits.MSTEN = 1;         //Master Mode Enabled
        SPI1CON2bits.FRMPOL = 1;        // CS(SS) Sync Pulse Polarity bit; 0 = Frame sync pulse is active-low
        SPI1CON2bits.FRMDLY = 0;        // 1 = Frame sync pulse coincides with first bit clock                                 
        SPI1STATbits.SPIEN = 1;         //Enable SPI Module
                                        //Interrupt Controller Settings
        SPI1STATbits.SPIEN = 1;         //Enable SPI Module
        SPI1BUF = 0x0000; 
        
        // при вкл. модуля на линии SDO мастера появл. лог.1
        
    }

void SPI1_PUT_int (unsigned int buf)               
{
        unsigned int buf1;
        CS2_LOW;
        delay_us(1);
         SPI1STATbits.SPIEN = 1;
         buf1 = SPI1BUF;                  // сбросили SPI2STATbits.SPIRBF
         SPI1BUF = buf;                   // старт клоков 
         while(!SPI1STATbits.SPIRBF){ }   // ждЄм SPI2STATbits.SPIRBF, как оконсание передачи
               SPI1STATbits.SPIROV = 0;   // сброс флага оверфлоу (на вс¤кий случай)
               buf = SPI1BUF;
        delay_us(1);
        CS2_HIGH;
}

unsigned int SPI1_GET_int ()
{
        unsigned int buf = 0;
       CS2_LOW; 
       if(SPI1STATbits.SPIROV)
       {
           buf = SPI1BUF;
           SPI1STATbits.SPIROV = 0;
       }
      
        SPI1BUF = 0x0000;               // »нициируем выработку клоков
        
        
      while(!SPI1STATbits.SPIRBF){}     // ?дЄм бит готовности буфера приЄмника 
               buf = SPI1BUF;           // считываем актуальные данные
               SPI1STATbits.SPIROV = 0;
        CS2_HIGH;
        
        return buf; 
    }

unsigned int SPI_READ_WORD (unsigned int ADDR)       // ѕроцедура чтени¤ байта по SPI
{
          unsigned int spi_buf;   
          
          SPI1_PUT_int(ADDR);
          delay_us(1);
          spi_buf = SPI1_GET_int();
               
          return spi_buf;
    }

void CPLD_SPI_WR (unsigned int  hold_reg_addr, unsigned int hold_reg_data) 		// функци§ отправки по SPI Ю† >>> ЊОїЧ  
{ // прогон§етс§ 2 раза в цикле по counter

            unsigned int SPI_frame = 0x0000;                      // создали переменную кадра SPI
			unsigned int MSByte_data = 0x0000;
            unsigned int LSByte_data = 0x0000;                         
            unsigned int i;
             
            
            LSByte_data = hold_reg_data & 0x00ff;         // выделили младший байт слова   
            MSByte_data = hold_reg_data >> 8;             // выделили старший байт слова
            
            for (i=0;i<2;i=i+1)	
				{
                  SPI_frame = 0x0000;
                  if(i==0) SPI_frame = LSByte_data;        // заполн§ем младшие 8 бит данными
                  if(i==1) SPI_frame = MSByte_data;        // младший байт на 1 итерации, старший на 2-ой   
                   
                                                                            // формирование значени¤ адреса
                                                                            // установка переменной адреса в нужную позицию <<8			
                  SPI_frame = (((hold_reg_addr*2-1)+i) << 8) + SPI_frame;   // склеиваем адрес и данные
                  SPI1_PUT_int (SPI_frame);  
                
                }   
        }

unsigned int CPLD_SPI_RD (unsigned int hold_reg_addr) 		// функци§ отправки по SPI Ю† >>> ЊОїЧ  
{ // прогон§етс§ 2 раза в цикле по counter

            unsigned int SPI_frame    = 0x0000;                 // создали переменную кадра SPI                        
			unsigned int SPI_addr     = 0x0000;
            unsigned int SPI_addr_buf = 0x0000;
            unsigned int spi_answer_0 = 0x0000;
            unsigned int spi_answer_1 = 0x0000;
            unsigned int spi_answer   = 0;
            unsigned int i;
            
            for (i=0;i<2;i=i+1)	
				{
                  SPI_frame = 0x8000;    
                  SPI_addr = ((hold_reg_addr*2)-1)+i;               // формирование значени¤ адреса
                  SPI_addr_buf = SPI_addr << 8;                     // установка переменной адреса в нужную позицию <<8											
                  SPI_frame = SPI_addr_buf + SPI_frame;             // склеиваем адрес и данные
                  //SPI_frame |= (1<<15);                           // уcтанавливаем бит 15 в 1 - режим "чтение"
                  
                 
                  if(i==0)  spi_answer_0 = SPI_READ_WORD (SPI_frame);          // заполн§ем младшие 8 бит данными
                  if(i==1)  spi_answer_1 = SPI_READ_WORD (SPI_frame);
                }   
                
                spi_answer = (spi_answer_0 & 0x00ff) + (spi_answer_1 << 8);
            return spi_answer;
    }

/*=========================================================================== */
// SPI3 - serial EEPROM
void SPI3_init()
{
                   
        SPI3STATbits.SPIEN = 0;         // Turn off spi module before initialization 
        IFS5bits.SPI3EIF = 0;           //Clear the Interrupt Flag
        IEC5bits.SPI3IE = 0;            //Disable the Interrupt
        // SPI2CON1 Register Settings:
        SPI3CON1bits.DISSCK = 0;        //Internal Serial Clock is Enabled
        SPI3CON1bits.DISSDO = 0;        //SDOx pin is controlled by the module
        SPI3CON1bits.MODE16 = 0;        //Communication is byte-wide (8 bits)
        SPI3CON1bits.SMP = 1;           //Input Data is sampled at the middle of data output time
        SPI3CON1bits.CKE = 1;           //Serial output data changes on transition from
        SPI3CON1bits.CKP = 0;           // Idle state for clock is a low level; active state is a high level
        
        // SPI1STAT Register Settings
        SPI3STATbits.SPISIDL = 0; // Continue module operation in Idle mode
        SPI3STATbits.SPIBEC = 0; // Buffer Length = 1 Word
        SPI3STATbits.SPIROV = 0; // No Receive Overflow has occurred
        
        
        // 2.5V < Vcc < 4.5V ----> fSCK <=  5M !!!
        
        // SPI1 SCK f = 30M @ 120M Fosc, Fcy 60M     
        //SPI3CON1bits.SPRE = 6;          //Secondary prescale 1:1
        //SPI3CON1bits.PPRE = 3;          //Primary prescale 1:1
        
        // SPI1 SCK f = 7.5M @ 120M Fosc, Fcy 60M     
        //SPI3CON1bits.SPRE = 6;          //Secondary prescale 1:1
        //SPI3CON1bits.PPRE = 2;          //Primary prescale 4:1
        
        // SPI1 SCK f = 3.75M @ 120M Fosc, Fcy 60M     
        SPI3CON1bits.SPRE = 4;          //Secondary prescale 4:1
        SPI3CON1bits.PPRE = 4;          //Primary prescale 4:1
        SPI3CON2bits.FRMEN = 0;         //Framed SPIx support is disabled
        SPI3CON2bits.SPIBEN = 0;        //Enhanced buffer is disabled (Legacy mode)
        SPI3CON1bits.MSTEN = 1;         //Master Mode Enabled
                                          
        SPI3STATbits.SPIEN = 1;         //Enable SPI Module
                                        //Interrupt Controller Settings
    }

void SPI3_write_byte (unsigned char buf)               
{

     unsigned char temp;

     SPI3BUF = buf;
     
     //while(!SPI3STATbits.SPIRBF);
     delay_us(100);
     
     // после записи необходимы вычитать содержание буфера SPI для сброса флага
     temp = SPI3BUF; 
     
     SPI3STATbits.SPIROV = 0;
 }

unsigned char SPI3_read_byte(void)
{
  unsigned int cnt = 0;
  unsigned char ret_value = 0;
  
  
 unsigned int buf = 0; 

 if(SPI3STATbits.SPIROV) 
 { 
    buf = SPI3BUF; 
    SPI3STATbits.SPIROV = 0; 
 } 

  SPI3BUF = 0x00;                  // initiate bus cycle 
  
  while(!SPI3STATbits.SPIRBF);

  SPI3STATbits.SPIROV = 0;
  ret_value = SPI3BUF;    /* return byte read */

  return ret_value;                  		  /* RBF bit is not set return error*/
}

// SPI
/*=========================================================================== */