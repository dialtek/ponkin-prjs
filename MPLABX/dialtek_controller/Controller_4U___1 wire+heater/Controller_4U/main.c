#include "xc.h"
#include "fuses.h"
// прототипы функций, используемые в Modbus библиотеке
void delay_ms(unsigned int);
void delay_us(unsigned long);

#include "one_wire.h"     
#include "dialtek_modbus.h"

#define _ISR_PSV __attribute__((__interrupt__, __auto_psv__))

#define MOXA_active LATBbits.LATB0

void OSC_init(void)
{
    // FRCDIV FRC/1; PLLPRE 2; DOZE 1:8; PLLPOST 1:2; DOZEN disabled; ROI disabled; 
    CLKDIV = 0x3000;
    // TUN Center frequency; 
    OSCTUN = 0x0;
    // ROON disabled; ROSEL disabled; RODIV Base clock value; ROSSLP disabled; 
    REFOCON = 0x0;
    // PLLDIV 46; 
    PLLFBD = 0x2E;
    // RND disabled; SATB disabled; SATA disabled; ACCSAT disabled; 
	CORCONbits.RND = 0;
	CORCONbits.SATB = 0;
	CORCONbits.SATA = 0;
	CORCONbits.ACCSAT = 0;
    // CF no clock failure; NOSC PRIPLL; LPOSCEN disabled; CLKLOCK unlocked; OSWEN Switch is Complete; IOLOCK not-active; 
    __builtin_write_OSCCONH((unsigned char) ((0x300 >> _OSCCON_NOSC_POSITION) & 0x00FF));
    __builtin_write_OSCCONL((unsigned char) ((0x300 | _OSCCON_OSWEN_MASK) & 0xFF));
    // Wait for Clock switch to occur
    while (OSCCONbits.OSWEN != 0);
    
    // Fosc = 120M, Fcy(Fp) = 60M

}

void GPIO_init(void)
{
    /*
    The ANSELx register has a default value of 0xFFFF;
    therefore, all pins that share analog functions are
    analog (not digital) by default.
     */       
   	
   ANSELA = 0x0000;
   ANSELB = 0x0000;
   ANSELC = 0x0000;
   ANSELD = 0x0000;
   ANSELE = 0x0000;
   ANSELF = 0x0000;
   ANSELG = 0x0000;
   
   TRISBbits.TRISB0 = 0;    // MOXA RESET pin
   
   TRISDbits.TRISD1 = 0;    // LED 1
   TRISDbits.TRISD2 = 0;    // LED 2
   TRISDbits.TRISD3 = 0;    // LED 3
   TRISDbits.TRISD4 = 0;    // LED 4
   
   TRISGbits.TRISG1 = 0;    // one wire TX
   TRISGbits.TRISG0 = 1;    // one wire RX
   
   TRISGbits.TRISG14 = 0;   // SPI2 SCK, R126
   TRISGbits.TRISG13 = 0;   // SPI2 SDO, RP125
   TRISGbits.TRISG12 = 1;   // SPI2 SDI, RPI124
   TRISGbits.TRISG15 = 0;   // SPI2 nCS, digital IO
   
   TRISDbits.TRISD6 = 0;    // SPI3 SCK, RP70
   TRISCbits.TRISC9 = 0;    // SPI3 SDO, RP57, а должен быть RD7 RP71
   TRISDbits.TRISD8 = 1;    // SPI3 SDI, RPI72
   TRISBbits.TRISB5 = 0;    // SPI3 nCS, Должен быть RD9
   
   TRISFbits.TRISF0 = 1;    // U1RX - RPI96
   TRISFbits.TRISF1 = 0;    // U1TX - RP97
   
   TRISCbits.TRISC2 = 1;    // U2 RX, RPI50, Hamilton Pump
   TRISCbits.TRISC1 = 0;    // U2 TX, RP49,  Hamilton Pump
   
   TRISEbits.TRISE8 = 0;    // Modbus TX EN
   
   TRISCbits.TRISC0 = 0;    // temperary heater
            
   // перекинул U1RX c RE9 на RA12
   // RPn RPi setup
   __builtin_write_OSCCONL(OSCCON & ~(1<<6)); // Разблокировать настройку выводов RPX
   
   // MODBUS, UART1 peripheral pin select
   RPOR9bits.RP97R = 1;     // RF1 as U1TX
   RPINR18bits.U1RXR = 96;  // 001 1100 I RPI96, table 11-2 in big datasheet
   
   // Hamilton PUMP, UART2 peripheral pin select
   RPOR5bits.RP49R   = 3;   // RC1 as U2TX
   RPINR19bits.U2RXR = 50;  // RPI50
   
   // SPI2 peripheral pin select
   RPINR22bits.SDI2R = 124; // RPI124
   
   RPOR12bits.RP126R = 0b001001;  // SCK2 - 001001 RPn tied to SPI2 Clock Output
   RPINR22bits.SCK2R = 126;       // SCK2 - IN setup
   
   RPOR11bits.RP125R = 0x08;      // SDO2 - 001000 RPn tied to SPI2 Slave Output 
   
   // SPI3 peripheral pin select
   RPINR29bits.SDI3R = 72; // RPI72
   
   RPOR8bits.RP70R = 0x20; // SCK3 - 100000 RPn tied to SPI3 Clock Output
   RPINR29bits.SCK3R = 70; // SCK3 - in setup
   
   RPOR7bits.RP57R = 0x1F; // SDO3 - 011111 RPn tied to SPI3 Slave Output 

   __builtin_write_OSCCONL(OSCCON | (1<<6));  // Заблокировать настройку выводов RPX
}

/*=========================================================================== */
// Timer 8 - delay timer
void TIMER8_delay_init (void)
{
    //TMR8 0; 
    TMR8 = 0x00;
    //Period = 1 us; Frequency = 60000000 Hz; PR8 60; 
    PR8 = 50; // 60 - calculated, 50 - real
    //TCKPS 1:1; T32 16 Bit; TON enabled; TSIDL disabled; TCS FOSC/2; TGATE disabled; 
    T8CON = 0x8000;
 
    IFS3bits.T8IF = 0;
    IEC3bits.T8IE = 0;
    /* Start the Timer */
    T8CONbits.TON = 1;
}

void delay_us(unsigned long us_delay)
{
    for(unsigned long i = 0; i < us_delay; i++)
    {
       T8CONbits.TON = 1;
       
       while(!IFS3bits.T8IF) { }
       IFS3bits.T8IF = 0;
       TMR8 = 0x00;
    }
}

void delay_ms(unsigned int ms_delay)
{
    for(unsigned int i = 0; i < ms_delay; i++) // x ms
    {
      // 1 ms
      for(unsigned long i = 0; i < 1000; i++)
        {
         T8CONbits.TON = 1;
       
         while(!IFS3bits.T8IF) { }
         IFS3bits.T8IF = 0;
         TMR8 = 0x00;
        }
    }
}

/*=========================================================================== */
// UART 1 - Modbus
void UART1_init(void)
{
    // RX interrupt UART1 settings 
    IPC2bits.U1RXIP = 7; // Set UART1 RX interrupt priority to 1 
    IFS0bits.U1RXIF = 0; // Reset UART1 RX interrupt flag

    U1BRG = 0x20;           // Baud Rate setting for 460k uart
    U1MODEbits.UARTEN = 1;  // 1 = UARTx is enabled; all UARTx pins are controlled by UARTx as defined by UEN <1:0>
    U1MODEbits.UEN = 0;     // 0 = UxTX and UxRX pins are enabled and used; UxCTS and UxRTS/BCLK pins controlled by port latches
    U1MODEbits.PDSEL = 0;   // 0 = No Parity, 8-Data bits
    U1MODEbits.ABAUD = 0;   // 0 = Baud rate measurement disabled or completed
    U1MODEbits.BRGH = 1;    // 1 = BRG generates 4 clocks per bit period (4x baud clock, High-Speed mode)
    U1MODEbits.STSEL = 0;   // 0 = 1-Stop bit

    U1STAbits.UTXISEL0 = 0; // Interrupt when a unsigned character is transferred to the Transmit Shift Register (this implies there isat least one unsigned character open in the transmit buffer
    U1STAbits.UTXISEL1 = 0;
    U1STAbits.UTXINV = 0;
    U1STAbits.UTXEN = 1;    // 1 = Transmit enabled, UxTX pin controlled by UARTx
    U1STAbits.URXISEL = 0;  // 0x = Interrupt is set when any unsigned character is received and transferred from the UxRSR to the receive buffer. Receive buffer has one or more unsigned characters.
                         // The URXISEL<1:0> (UxSTA<7:6>) control bits determine when the UART receiver generates an interrupt.
    IEC0bits.U1RXIE = 1; // Enable UART1 RX interrupt
}

void uart_send_hex (unsigned char byte)
{ 
    U1TXREG = byte;
    while(U1STAbits.TRMT == 0){ }
}

void _ISR_PSV _U1RXInterrupt( void )
{
    // UART1 1 byte receive interrupt 

    modbus_uart_byte(U1RXREG);
    IFS0bits.U1RXIF = 0; 
}

/*=========================================================================== */
// UART 2 - Hamilton PUMP
void UART2_init(void)
{
       // RX interrupt UART2 settings 
    IPC7bits.U2RXIP = 6; // Set UART2 RX interrupt priority to 2 
    IFS1bits.U2RXIF = 0; // Reset UART2 RX interrupt flag
    IEC1bits.U2RXIE = 1; // Enable UART2 RX interrupt
    
    U2BRG = 390;            // Baud Rate setting for 9600 uart
    U2MODEbits.UARTEN = 1;  // 1 = UARTx is enabled; all UARTx pins are controlled by UARTx as defined by UEN <1:0>
    U2MODEbits.UEN = 0;     // 0 = UxTX and UxRX pins are enabled and used; UxCTS and UxRTS/BCLK pins controlled by port latches
    U2MODEbits.PDSEL = 0;   // 0 = No Parity, 8-Data bits
    U2MODEbits.ABAUD = 0;   // 0 = Baud rate measurement disabled or completed
    U2MODEbits.BRGH = 0;    // 0 = BRG generates 4 clocks per bit period (4x baud clock, High-Speed mode)
    U2MODEbits.STSEL = 0;   // 0 = 1-Stop bit

    U2STAbits.UTXISEL0 = 0; // Interrupt when a unsigned character is transferred to the Transmit Shift Register (this implies there isat least one unsigned character open in the transmit buffer
    U2STAbits.UTXISEL1 = 0;
    U2STAbits.UTXINV = 0;
    U2STAbits.UTXEN = 1;    // 1 = Transmit enabled, UxTX pin controlled by UARTx
    U2STAbits.URXISEL = 0;  // 0x = Interrupt is set when any unsigned character is received and transferred from the UxRSR to the receive buffer. Receive buffer has one or more unsigned characters.
                         // The URXISEL<1:0> (UxSTA<7:6>) control bits determine when the UART receiver generates an interrupt.
}

void uart2_send_hex (unsigned char byte)
{ 
    U2TXREG = byte;
    while(U2STAbits.TRMT == 0){ }
}

void _ISR_PSV _U2RXInterrupt( void )
{
    // UART2 byte receive interrupt
    input_register[6] = U2RXREG;
    IFS1bits.U2RXIF = 0; 
}

/*=========================================================================== */
// SPI2 - Analog board CPLD 
#define SPI2_CS_ON  LATGbits.LATG15 = 0    // CS set LOW
#define SPI2_CS_OFF LATGbits.LATG15 = 1    // CS set HIGH

    void SPI2_init ()
    {
        // A series of 8/16 clock pulses shift out 8/16 bits of transmit data from Shift Register SPIxSR
        // to the SDOx pin and simultaneously shift the data at the SDIx pin into SPIxSR.
        // SPI interrupt
        // When the ongoing transmit and receive operations are completed, the content of the
        // SPIx Shift register (SPIxSR) is moved to the SPIx Receive Buffer (SPIxRXB).
        // c) The SPIx Receive Buffer Full Status (SPIRBF) bit in the SPIx Status and Control
        // (SPIxSTAT<0>) register is set by the module, indicating that the receive buffer is full.
        // Once the SPIxBUF register is read by the user code, the hardware clears the SPIRBF
        // bit.
        SPI2STATbits.SPIEN = 0;         // Turn off spi module before initialization 
        IFS2bits.SPI2IF = 0;            //Clear the Interrupt Flag
        IEC2bits.SPI2IE = 0;            //Disable the Interrupt
        // SPI2CON1 Register Settings:
        SPI2CON1bits.DISSCK = 0;        //Internal Serial Clock is Enabled
        SPI2CON1bits.DISSDO = 0;        //SDOx pin is controlled by the module
        SPI2CON1bits.MODE16 = 1;        //Communication is word-wide (16 bits)
        SPI2CON1bits.SMP = 0;           //Input Data is sampled at the middle of data output time
        SPI2CON1bits.CKE = 0;           //Serial output data changes on transition from
        SPI2CON1bits.CKP = 0;           //Serial output data changes on transition from
        SPI2CON1bits.PPRE = 2;          //Primary prescale 1:1
        SPI2CON1bits.SPRE = 4;          //Secondary prescale 1:1
        // SPI2CON2 Register Settings:
        SPI2CON1bits.MSTEN = 1;         //Master Mode Enabled
        SPI2CON2bits.FRMEN = 0;         // CS(SS) Support bit; 0 = Framed SPIx support disable 
        SPI2CON2bits.SPIFSD = 0;        // CS(SS) Pulse Direction; 0 = Frame sync pulse output (master)
        SPI2CON2bits.FRMPOL = 1;        // CS(SS) Sync Pulse Polarity bit; 0 = Frame sync pulse is active-low
        SPI2CON2bits.FRMDLY = 0;       // 1 = Frame sync pulse coincides with first bit clock
                                          
        
        SPI2STATbits.SPIEN = 1;         //Enable SPI Module
        SPI2BUF = 0x0000;               //Write data to be transmitted
                                        //Interrupt Controller Settings
        //IFS0bits.SPI1IF = 0;            //Clear the Interrupt Flag
        //IEC0bits.SPI1IE = 1;            //Enable the Interrupt
    }
    void SPI2_PUT_int (unsigned int buf)               
    {
        unsigned int buf1;
        SPI2_CS_ON;
        delay_us(1);
        SPI2STATbits.SPIEN = 1;
        buf1 = SPI2BUF;                  // сбросили SPI2STATbits.SPIRBF
        SPI2BUF = buf;                   // старт клоков 
        while(!SPI2STATbits.SPIRBF){}    // ждЄм SPI2STATbits.SPIRBF, как оконсание передачи
               SPI2STATbits.SPIROV = 0;   // сброс флага оверфлоу (на вс¤кий случай)
               buf = SPI2BUF;
        delay_us(1);
        SPI2_CS_OFF;
    }
    unsigned int SPI2_GET_int ()
    {
        unsigned int buf = 0;
       SPI2_CS_ON; 
       if(SPI2STATbits.SPIROV)
       {
           buf = SPI2BUF;
           SPI2STATbits.SPIROV = 0;
       }
      
        SPI2BUF = 0x0000;               // »нициируем выработку клоков
        
        
      while(!SPI2STATbits.SPIRBF){}     // ?дЄм бит готовности буфера приЄмника 
               buf = SPI2BUF;           // считываем актуальные данные
               SPI2STATbits.SPIROV = 0;
        SPI2_CS_OFF;
        
        return buf; 
    } 
    void SPI_WRITE_WORD (unsigned int DATA)              // ѕроцедура записи байта по SPI
    {
                    SPI2_PUT_int(DATA);	             
    }
    unsigned int SPI_READ_WORD (unsigned int ADDR)       // ѕроцедура чтени¤ байта по SPI
    {
          unsigned int spi_buf;   
          
          SPI2_PUT_int(ADDR);
          delay_us(1);
          spi_buf = SPI2_GET_int();
               
          return spi_buf;
    }
    void CPLD_SPI_WR (unsigned int hold_reg_data, unsigned int  hold_reg_addr) 		// функци§ отправки по SPI Ю† >>> ЊОїЧ  
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
                  SPI_WRITE_WORD (SPI_frame);              
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
     
     while(!SPI3STATbits.SPIRBF);
     
     // после записи необходимы вычитать содержание буфера SPI для сброса флага
     temp = SPI3BUF; 
     
     SPI3STATbits.SPIROV = 0;
 }

unsigned char SPI3_read_byte(void)
{
  unsigned int cnt = 0;
  unsigned char ret_value = 255;
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
/*=========================================================================== */
// 25LC128 SPI EEPROM
#define EEPROM_READ  0x03  // Read data from memory array beginning at selected address
#define EEPROM_WRITE 0x02  // Write data to memory array beginning at selected address  
#define EEPROM_WREN  0x06  // Set the write enable latch (enable write operations)
#define EEPROM_RDSR  0x05  // Read STATUS register

#define SPI3_nCS_HIGH LATBbits.LATB5 = 1    // CS set HIGH
#define SPI3_nCS_LOW  LATBbits.LATB5 = 0    // CS set LOW

void eeprom_wr_page(unsigned int address)
{
  // EEPROM write enable sequence
  SPI3_nCS_LOW;
  SPI3_write_byte(EEPROM_WREN);
  SPI3_nCS_HIGH;
  delay_us(20);
  
  // EEPROM address and data write sequence
  SPI3_nCS_LOW;
  SPI3_write_byte(EEPROM_WRITE);
  
  SPI3_write_byte((unsigned char)(address >> 8));      // set address ptr msb
  SPI3_write_byte((unsigned char)(address & 0x00ff));  // set address ptr lsb
  
  for(unsigned char i = 0; i < 32; i++) // max bytes to write - 64
  {
    SPI3_write_byte((unsigned char)(holding_register[i + address/2] >> 8));            // data msb    
    SPI3_write_byte((unsigned char)(holding_register[i + address/2] & 0x00ff));        // data lsb 
  }
  
  delay_us(5);
  SPI3_nCS_HIGH;
  
  delay_ms(8);  // Internal Write Cycle Time Ч 5 ms
}

void eeprom_wr_regs(void)
{
  /// 124 modbus register saving sequence
    
  // 25LC128 SPI EEPROM addres pointer, 248 bytes beginning from 0x00 address
  unsigned int EEPROM_addr = 0; 

  eeprom_wr_page(EEPROM_addr);  // EEPROM memory page 1 - 0...31 regs
  EEPROM_addr += 64;
  eeprom_wr_page(EEPROM_addr);  // EEPROM memory page 2 - 32...63 regs
  EEPROM_addr += 64;
  eeprom_wr_page(EEPROM_addr);  // EEPROM memory page 3 - 64...95 regs
  EEPROM_addr += 64;
  eeprom_wr_page(EEPROM_addr);  // EEPROM memory page 4 - 96...124 regs
}

void eeprom_rd_regs(void)
{
  unsigned char lsb = 0, msb = 0;
  unsigned int address = 0;
  // EEPROM read sequence
  SPI3_nCS_LOW;
  SPI3_write_byte(EEPROM_READ);
  
  SPI3_write_byte((unsigned char)(address >> 8));      // set address ptr msb
  SPI3_write_byte((unsigned char)(address & 0x00ff));  // set address ptr lsb

  for(unsigned char i = 0; i < max_regs_cnt-1; i++)
  { 
    msb = SPI3_read_byte();
    lsb = SPI3_read_byte();
    
    holding_register[i] = (msb << 8) | lsb;   
  }
  SPI3_nCS_HIGH;
}
/*=========================================================================== */ 

int main(void) 
{
   OSC_init();
   GPIO_init();
   MOXA_active = 1;
   
   TX_DIS;            // release RS485 bus
   SPI3_nCS_HIGH;     // release SPI bus
   SPI2_init();       // Analog board CPLD communication
   SPI3_init();       // serial EEPROM 
   TIMER8_delay_init();
   UART1_init();      // Modbus UART1
   UART2_init();      // Hamilton Pump UART2
   
   modbus_init();
   //eeprom_rd_regs();  // reading sets from SPI EEPROM
   __builtin_enable_interrupts(); // EN interrupts global
   
   unsigned int bufCPLDRD;
   
   while(1)
   { 
    modbus_poll();     // contains ~40 ms delay, 20 - led, 20 - if read 120 regs
    
    uart2_send_hex(1);
    
//    CPLD_SPI_WR (0xABCD,1);
//    delay_us(10);
//    bufCPLDRD = CPLD_SPI_RD(1);
   }
    
}
