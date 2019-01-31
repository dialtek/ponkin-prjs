#include "fuses.h"

// прототипы функций, используемые в Modbus библиотеке
void delay_ms(unsigned int);
void delay_us(unsigned long);

unsigned char uart2_rx_buf[30] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};    
unsigned char uart2_rx_ptr = 0;
unsigned char answer_ready = 0;  // received data ready bit
unsigned char rx_msg[10] = {0,0,0,0,0,0,0,0,0,0}; 

#include "dialtek_modbus.h"
#include "hamilton_pump.h"   

#define _ISR_PSV __attribute__((__interrupt__, __auto_psv__))
#define MOXA_active LATBbits.LATB0
#define POWER_LED   LATCbits.LATC4 

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
    
    // Fosc = 120M, Fcy = 60M

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
   ANSELG = 0x0000;
   
   
   TRISBbits.TRISB0 = 0;    // MOXA RESET pin
   
   TRISBbits.TRISB6 = 0;    // PGC
   TRISBbits.TRISB7 = 0;    // PGD
   
   TRISCbits.TRISC1 = 0;    // LED 1, MODBUS
   TRISCbits.TRISC2 = 0;    // LED 2, MODBUS
   TRISCbits.TRISC3 = 0;    // LED 3
   TRISCbits.TRISC4 = 0;    // LED 4, power led
   
   TRISGbits.TRISG1 = 0;    // one wire TX
   TRISGbits.TRISG0 = 1;    // one wire RX
   
   TRISGbits.TRISG14 = 0;   // SPI2 SCK, R126
   TRISGbits.TRISG13 = 0;   // SPI2 SDO, RP125
   TRISGbits.TRISG12 = 1;   // SPI2 SDI, RPI124
   TRISGbits.TRISG15 = 0;   // SPI2 nCS, digital IO
   
   TRISDbits.TRISD6 = 0;    // SPI3 SCK, RP70
   //TRISCbits.TRISC9 = 0;    // SPI3 SDO, RP57, а должен быть RD7 RP71
   TRISDbits.TRISD8 = 1;    // SPI3 SDI, RPI72
   TRISBbits.TRISB5 = 0;    // SPI3 nCS, Должен быть RD9
   
   TRISEbits.TRISE9 = 1;    // U1RX - RPI89
   TRISFbits.TRISF0 = 0;    // U1TX - RP96
   
   TRISBbits.TRISB12 = 1;   // U2RX,  Hamilton Pump
   TRISFbits.TRISF12 = 0;   // U2TX, RP108, Hamilton Pumpp
   TRISFbits.TRISF13 = 0;   // U2/RS-485 TX EN
   
   TRISEbits.TRISE8 = 0;    // Modbus TX EN

   // RPn RPi setup
   __builtin_write_OSCCONL(OSCCON & ~(1<<6)); // Разблокировать настройку выводов RPX
   // UART1 peripheral pin select
   RPOR7bits.RP96R = 1;     // RF0 as U1TX
   RPINR18bits.U1RXR = 89;  // 001 1100 I RPI96, table 11-2 in big datasheet
   
   // Hamilton PUMP, UART2 peripheral pin select
   RPOR11bits.RP108R = 3;   // RF12 - U2TX, RP108
   RPINR19bits.U2RXR = 44;  // RB12 - U2RX, RPI44
   
   // SPI1 peripheral pin select
   RPINR20bits.SDI1R = 124;       // RPI124
   
   RPOR15bits.RP126R = 0b000110;  // SCK1 - 0b000110 RPn tied to SPI1 Clock Output
   RPINR20bits.SCK1R = 126;       // SCK1 - IN setup
   
   RPOR14bits.RP125R = 0b000101;  // SDO1 - 000101 RPn tied to SPI1 SDO 
   
//   // SPI3 peripheral pin select
//   RPINR29bits.SDI3R = 72; // RPI72
//   
//   RPOR8bits.RP70R = 0x20; // SCK3 - 100000 RPn tied to SPI3 Clock Output
//   RPINR29bits.SCK3R = 70; // SCK3 - in setup
//   
//   RPOR7bits.RP57R = 0x1F; // SDO3 - 011111 RPn tied to SPI3 Slave Output 

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
    IEC0bits.U1RXIE = 1; // Enable UART1 RX interrupt
    
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
    //IFS1bits.U2TXIF = 0; // Reset UART2 TX interrupt flag
    //IEC1bits.U2TXIE = 1; // Enable UART2 TX interrupt
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

void uart2_send_byte (unsigned char byte)
{ 
    U2TXREG = byte;
    while(U2STAbits.TRMT == 0){ }
}

void uart2_send_text(unsigned char *s)
{
    while (*s != 0) uart2_send_byte(*s++);
}

 void uart2_CR_LF_send (void)
{  
    
	uart2_send_byte(0x0D);
    uart2_send_byte(0x0A);
}

void _ISR_PSV _U2RXInterrupt( void )
{
    // UART2 byte receive interrupt, Hamilton pump 
    
    uart2_rx_buf[uart2_rx_ptr] = U2RXREG;
    input_register[10+uart2_rx_ptr] = uart2_rx_buf[uart2_rx_ptr];

    uart2_rx_ptr++; 
    
    IFS1bits.U2RXIF = 0; 
    
}

/*=========================================================================== */
// SPI2 - Analog board CPLD
#define SPI1_nCS_HIGH LATGbits.LATG15 = 1    // CS set HIGH
#define SPI1_nCS_LOW  LATGbits.LATG15 = 0    // CS set LOW

void SPI1_init()
{
                
        SPI1STATbits.SPIEN = 0;         // Turn off spi module before initialization 
        IFS0bits.SPI1EIF   = 0;         // Clear the Interrupt Flag
        IFS0bits.SPI1IF = 0;            // Disable the Interrupt
        // SPI2CON1 Register Settings:
        SPI1CON1bits.DISSCK = 0;        //Internal Serial Clock is Enabled
        SPI1CON1bits.DISSDO = 0;        //SDOx pin is controlled by the module
        SPI1CON1bits.MODE16 = 0;        //Communication is byte-wide (8 bits)
        SPI1CON1bits.SMP = 1;           //Input Data is sampled at the end of data output time
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
        SPI1CON1bits.SPRE = 6;          //Secondary prescale 1:1
        SPI1CON1bits.PPRE = 2;          //Primary prescale 4:1
        
        // SPI1 SCK f = 3.75M @ 120M Fosc, Fcy 60M     
        //SPI1CON1bits.SPRE = 4;          //Secondary prescale 4:1
        //SPI1CON1bits.PPRE = 4;          //Primary prescale 4:1
        
        SPI1CON2bits.FRMEN = 0;         //Framed SPIx support is disabled
        SPI1CON2bits.SPIBEN = 0;        //Enhanced buffer is disabled (Legacy mode)
        SPI1CON1bits.MSTEN = 1;         //Master Mode Enabled
                                          
        SPI1STATbits.SPIEN = 1;         //Enable SPI Module
                                        //Interrupt Controller Settings
        
        // при вкл. модуля на линии SDO мастера появл. лог.1
        
    }

void SPI1_write_byte (unsigned char buf)               
{
     unsigned char temp = 0;

     SPI1STATbits.SPIROV = 0;
     SPI1BUF = buf;
     while(!SPI1STATbits.SPIRBF);
     
     temp = SPI1BUF; 
     
     //SPI2STATbits.SPIEN = 0;         //Enable SPI Module
 }

unsigned char SPI1_read_byte(void)
{
  unsigned int cnt = 0;
  unsigned char ret_value = 255;
  
  SPI1STATbits.SPIROV = 0;
  SPI1BUF = 0x00;                  // initiate bus cycle 
  while(!SPI2STATbits.SPIRBF)
  {
      cnt++;
      if (cnt > 50) break; 
  }
   
   /* Check for Receive buffer full status bit of status register*/
  if (SPI1STATbits.SPIRBF)
  { 
      SPI1STATbits.SPIROV = 0;
      ret_value = SPI1BUF;    /* return byte read */
  }
  
  return ret_value;                  		  /* RBF bit is not set return error*/
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
   POWER_LED = 1;
   MOXA_active = 1;
   
   TX_DIS;            // release RS485 bus
   SPI3_nCS_HIGH;     // release SPI bus
   SPI1_nCS_HIGH;
   SPI1_init();       // Analog board CPLD communication
   SPI3_init();       // serial EEPROM 
   TIMER8_delay_init();
   UART1_init();      // Modbus UART
   UART2_init();      // Hamilton Pump UART2
   
   modbus_init();
   //eeprom_rd_regs();  // reading sets from SPI EEPROM
   __builtin_enable_interrupts(); // EN interrupts global

   while(1)
   {
     modbus_poll();     // contains ~40 ms delay, 20 - led, 20 - if read 120 reg 
     
     // CPLD SPI check
     SPI1_nCS_HIGH;
     SPI1_write_byte(0x81);
     SPI1_nCS_LOW;
     
     // RS-485 check
     get_syr_pos(1);
     
     // one wire TX check
     LATGbits.LATG1 = ~LATGbits.LATG1;
     delay_ms(1);
   
   }
}
