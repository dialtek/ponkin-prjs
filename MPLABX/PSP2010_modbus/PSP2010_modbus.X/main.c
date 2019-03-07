#include "fuses.h"
#include <p24HJ128GP506.h>
#define FCY 40000000UL
#include <libpic30.h>
#include <stdio.h>
#include <stdint.h>
#define _ISR_PSV __attribute__((__interrupt__, __auto_psv__))
  
#define FP 40000000
#define U1_BAUDRATE 115200
#define U2_BAUDRATE 2400
#define U1BRGVAL ((FP/U1_BAUDRATE)/16)-1
#define U2BRGVAL ((FP/U2_BAUDRATE)/16)-1 

#define MAX_VOLTAGE 40000 // PSP405 max voltage
#define MAX_CURRENT 5000  // PSP405 max current
#define MAX_POWER   200   // PSP405 max power
#define ERROR_CODE 65535  // value on reading error
#define READ_TIMEOUT 1000 // reading timeout in ms 
#define RX_BUF_SIZE 38    // rx buf size 

#define EEPROM_READ  0x03  // Read data from memory array beginning at selected address
#define EEPROM_WRITE 0x02  // Write data to memory array beginning at selected address  
#define EEPROM_WREN  0x06  // Set the write enable latch (enable write operations)
#define EEPROM_RDSR  0x05  // Read STATUS register

#define K1_ON  LATGbits.LATG12 = 1   // K1 relay ON 
#define K1_OFF LATGbits.LATG12 = 0   // K1 relay OFF 

#define POL_RELAY_LED LATBbits.LATB2 // LED_RELAY
#define RS232_TX_LED  LATBbits.LATB3 // LED_TX_232
#define RS232_RX_LED  LATBbits.LATB4 // LED_RX_232

#define SPI_nCS_HIGH LATCbits.LATC2 = 1    // CS set HIGH
#define SPI_nCS_LOW  LATCbits.LATC2 = 0    // CS set LOW

#define RES_BUT PORTBbits.RB8             // modbus dev id reset btn

#define POL_CHANGE_1     1    // polarity change cmd code 1 step
#define POL_CHANGE_2     2    // polarity change cmd code 2 step
#define SET_OUTPUT       3    // output state change cmd code
#define NO_CMD_RUNNING   4    // no cmd running state
#define SRC_CMD          5    // all src cmds

volatile unsigned char uart2_rx_buf[40] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};   
volatile unsigned char rx_msg[40] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};  
volatile unsigned char uart2_rx_ptr = 0;
volatile unsigned char data_ready = 0;
unsigned int rd_status, rd_voltage = 0, rd_current = 0, 
             rd_voltage_lim = 0, rd_current_lim = 0, rd_power_lim = 0;

unsigned char id_change = 0;  // modbus ID change 
unsigned char curr_cmd  = 0;  // user cmd ID

// funcs prototypes
void uart2_text_send(char *s);

#include "dialtek_modbus.h"

void enableInterrupts(void)
{
    /* Set CPU IPL to 0, enable level 1-7 interrupts */
    /* No restoring of previous CPU IPL state performed here */
    SRbits.IPL = 0;
    /* Interrupt nesting enabled here */
    INTCON1bits.NSTDIS =0;

}

void OSC_init()
{
        // FCY=FOSC/2, FOSC= FIN*M/(N1*N2) 
        CLKDIVbits.PLLPRE = 0;      // 0 - divider N1 = 2
        PLLFBD = 30;                // multiplier M = PLLFBD + 2
        CLKDIVbits.PLLPOST = 0;     // 0 - divider N2 = 2
        
        OSCTUN=0;                   // 000000 = Center frequency (7.37 MHz nominal)
        RCONbits.SWDTEN=0;          // Disable Watch Dog Timer
        
        while(OSCCONbits.LOCK !=1); // 1 = Indicates that PLL is in lock, or PLL start-up timer is satisfied
                                    // 0 = Indicates that PLL is out of lock, start-up timer is in progress or PLL is disabled
        //note: FOSC= 10 MHz * 32/(2*2) = 80 MHz, FCY = 80/2
}   
/*=========================================================================== */
// UART 
void UART1_init()
{   /// modbus 
    // RX interrupt UART1 settings 
    IPC2bits.U1RXIP = 7;   // Set UART1 RX interrupt priority to 7
    IFS0bits.U1RXIF = 0;   // Reset UART1 RX interrupt flag
    
    U1BRG = U1BRGVAL;      // Baud Rate setting for 115200 uart
    U1MODEbits.UARTEN = 1;  // 1 = UARTx is enabled; all UARTx pins are controlled by UARTx as defined by UEN <1:0>
    U1MODEbits.UEN = 0;     // 0 = UxTX and UxRX pins are enabled and used; UxCTS and UxRTS/BCLK pins controlled by port latches
    U1MODEbits.PDSEL = 0;   // 0 = No Parity, 8-Data bits
    U1MODEbits.ABAUD = 0;   // 0 = Baud rate measurement disabled or completed
    U1MODEbits.BRGH = 0;    // 1 = BRG generates 4 clocks per bit period (4x baud clock, High-Speed mode)
    U1MODEbits.STSEL = 0;   // 0 = 1-Stop bit

    U1STAbits.UTXISEL0 = 0; // Interrupt when a unsigned character is transferred to the Transmit Shift Register (this implies there isat least one unsigned character open in the transmit buffer
    U1STAbits.UTXISEL1 = 0;
    U1STAbits.UTXINV = 0;
    U1STAbits.UTXEN = 1;    // 1 = Transmit enabled, UxTX pin controlled by UARTx
    U1STAbits.URXISEL = 0;  // 0x = Interrupt is set when any unsigned character is received and transferred from the UxRSR to the receive buffer. Receive buffer has one or more unsigned characters.
                         // The URXISEL<1:0> (UxSTA<7:6>) control bits determine when the UART receiver generates an interrupt.
 
    IEC0bits.U1RXIE = 1; // Enable UART1 RX interrupt 
}

// modbus timer
void Timer9_init(unsigned long baudrate)
{
       T9CONbits.TON = 0;           // Timer on/off bit; 0 - Disable Timer
       IPC13bits.T9IP = 6;          // 5th prior
       IFS3bits.T9IF = 0;           // Clear Timer interrupt flag
       TMR9 = 0x0000;               // reset if timer is on, 115200
       T9CONbits.TCS = 0;           // Timer Clock Source Select bit; 0 - Internal clock (FOSC/2)
       T9CONbits.TGATE = 0;         // Disable Gated Timer mode
       T9CONbits.TCKPS = 0;      // Prescaler = (00=1, 01=8, 10=64, 11=256) 
       T8CONbits.T32 = 0;
       
       switch(baudrate)
       {
           case 9600:   break; // 1 byte - 840 us
           case 57600:  break; // 1 byte - 140 us
           case 115200: PR9 = 8400; break; // 1 byte - 70 us, 2800 * 3 = 210 us
           case 230400: break; // 1 byte - 35 us
               
           default: PR9 = 8400; // Load the period value
       }
       
       IEC3bits.T9IE = 1;           // Enable T9 interrupt 
    }

// polarity change timer
void TimerX32_init(void)
{
      // timer tick = 1.6 us
       IPC2bits.T3IP = 4;           // Set UART1 RX interrupt priority to 2
       T2CONbits.TON = 0;           // Timer on/off bit; 0 - Disable Timer
       T3CONbits.TON = 0;           // Timer on/off bit; 0 - Disable Timer
       
       IFS0bits.T2IF = 0;           // Clear Timer interrupt flag
       IFS0bits.T3IF = 0;           // Clear Timer interrupt flag
       IEC0bits.T3IE = 0;           // DIS T3 interrupt
       IEC0bits.T2IE = 0;           // DIS T2 interrupt
       
       TMR2 = 0x0000;               // reset timer cntr
       TMR3 = 0x0000;               // reset timer cntr
       T2CONbits.TCS = 0;           // Timer Clock Source Select bit; 0 - Internal clock (FOSC/2)
       T2CONbits.TGATE = 0;         // Disable Gated Timer mode
       T2CONbits.TCKPS = 2;         // Prescaler = (00=1, 01=8, 10=64, 11=256) 
       T3CONbits.TCKPS = 2;         // Prescaler = (00=1, 01=8, 10=64, 11=256) 
       T2CONbits.T32 = 1;
       
       // 1 ms
       PR3 = 0;  
       PR2 = 625;
    }

void TimerX32_setMs(unsigned long ms)
{
    /// 625 000 ticks = 1 sec, 625 ticks = 1 ms
    
    unsigned long tick = ms * 625;
    
    TMR2 = 0;
    TMR3 = 0;
    
    PR2 = (unsigned int) (tick & 0x0000ffff);     // set lsb
    PR3 = (unsigned int) (tick >> 16);            // set msb
}

void TimerX32_state(unsigned char state)
{
    T2CONbits.TON = state;           // Timer on/off bit; 0 - Disable Timer
    T3CONbits.TON = state;           // Timer on/off bit; 0 - Disable Timer
    IEC0bits.T3IE = state;           // Enable T3 interrupt
    
}

void UART2_init()
{   /// RS-232 
    // RX interrupt UART2 settings 
    IPC7bits.U2RXIP = 3;   // Set UART2 RX interrupt priority to 3
    IFS1bits.U2RXIF = 0;   // Reset UART2 RX interrupt flag

    U2BRG = U2BRGVAL;       // Baud Rate setting for 2400 
    U2MODEbits.UARTEN = 1;  // 1 = UARTx is enabled; all UARTx pins are controlled by UARTx as defined by UEN <1:0>
    U2MODEbits.UEN = 0;     // 0 = UxTX and UxRX pins are enabled and used; UxCTS and UxRTS/BCLK pins controlled by port latches
    U2MODEbits.PDSEL = 0;   // 0 = No Parity, 8-Data bits
    U2MODEbits.ABAUD = 0;   // 0 = Baud rate measurement disabled or completed
    U2MODEbits.BRGH = 0;    // 1 = BRG generates 4 clocks per bit period (4x baud clock, High-Speed mode)
    U2MODEbits.STSEL = 0;   // 0 = 1-Stop bit

    U2STAbits.URXISEL0 = 0; // Interrupt flag bit is set when a character is received
    U2STAbits.URXISEL1 = 0;
    U2STAbits.UTXINV = 0;
    U2STAbits.UTXEN = 1;    // 1 = Transmit enabled, UxTX pin controlled by UARTx
                            // The URXISEL<1:0> (UxSTA<7:6>) control bits determine when the UART receiver generates an interrupt.
    IEC1bits.U2RXIE = 1;   // EN UART2 RX interrupt
 //Once enabled, the UxTX and UxRX pins are configured as an output and an
 //input, respectively, overriding the TRIS and PORT register bit settings for the corresponding I/O port pins. 
}
  
void U1_send_byte (unsigned char Ch)
{ //  U1 send byte
    
        U1TXREG = Ch;
        //  should wait at least one instruction cycle between 
        //  writing UxTXREG and reading the TRMT bit
        __delay_us(1);
        while(U1STAbits.TRMT == 0); //waiting for trancsaction to be complete
   
}

void uart2_send_hex (unsigned char Ch)
{ // RS-232 send byte
    
    
        U2TXREG = Ch;
        //  should wait at least one instruction cycle between 
        //  writing UxTXREG and reading the TRMT bit
        __delay_us(1);
        while(U2STAbits.TRMT == 0); //waiting for trancsaction to be complete
}

void uart_CR_LF_send (void){
	  
    U1_send_byte(0x0A);
	U1_send_byte(0x0D);
	
	}

void uart2_text_send(char *s){
  while (*s != 0)
    uart2_send_hex(*s++);
}

/*=========================================================================== */
// peripheral
void GPIO_init()
{
    // PORT B
    TRISBbits.TRISB0 = 0; // LED_RX_485
    TRISBbits.TRISB1 = 0; // LED_TX_485
    TRISBbits.TRISB2 = 0; // LED_RELAY
    TRISBbits.TRISB3 = 0; // LED_RX_232
    TRISBbits.TRISB4 = 0; // LED_TX_232
    TRISBbits.TRISB8 = 1; // reset button
    TRISBbits.TRISB14 = 0;// modbus TX EN
    
    TRISB = 0x0000 | 1 << 8;
    //PORT C
    TRISCbits.TRISC1 = 0;  // OUT2
    TRISCbits.TRISC2 = 0;  // SPI nCS
    //PORT D
    TRISDbits.TRISD1 = 0; 
    //PORT F
    TRISFbits.TRISF0 = 0;
    LATFbits.LATF0 = 0;
    TRISFbits.TRISF1 = 0;
    LATFbits.LATF1 = 0;
    //uart2
    TRISFbits.TRISF4 = 0;
    LATFbits.LATF4 = 0;
    TRISFbits.TRISF5 = 1;
    TRISFbits.TRISF6 = 0;
    //PORT G
    TRISGbits.TRISG6=0;   // SPI2 SCLK - serial EEPROM
    TRISGbits.TRISG7=1;   // SPI2 SDI  - serial EEPROM
    TRISGbits.TRISG8=0;   // SPI2 SDO  - serial EEPROM
    TRISGbits.TRISG12=0;  // POL_RELAY
    
    AD1PCFGL = 0xffff; // Port pin in Digital mode, port read input enabled, 
    AD1PCFGH = 0xffff; 
    
} 

 // SPI2 - serial EEPROM
void SPI2_init()
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

void SPI2_send_byte (unsigned char buf)               
{
     unsigned char temp;

     SPI2BUF = buf;
     
     while(!SPI2STATbits.SPIRBF);
     
     // после записи необходимы вычитать содержание буфера SPI дл€ сброса флага
     temp = SPI2BUF; 
     
     SPI2STATbits.SPIROV = 0;
 }

unsigned char SPI2_read_byte(void)
{
 unsigned char ret_value = 0;
  
 unsigned int buf = 0; 

 if(SPI2STATbits.SPIROV) 
 { 
    buf = SPI2BUF; 
    SPI2STATbits.SPIROV = 0; 
 } 

  SPI2BUF = 0x00;                  // initiate bus cycle 
  
  while(!SPI2STATbits.SPIRBF);

  SPI2STATbits.SPIROV = 0;
  ret_value = SPI2BUF;    /* return byte read */

  return ret_value;                  		  /* RBF bit is not set return error*/
}

/*=========================================================================== */
// interrupts
void _ISR_PSV _U1RXInterrupt(void)      // U1 - Modbus
{ 
     // rx buffer has data, at least one more character can be read
      while(U1STAbits.URXDA == 0){ }
    
      rx_buf[rx_buf_ptr++] = U1RXREG;

      IFS0bits.U1RXIF = 0;    // Clear  UART1_Tx interrupt  

      if(timer_state == 0)
      {
            TMR9 = 0x0000;
            IFS3bits.T9IF = 0;    // Clear Timer interrupt flag
            timer_state = 1;
            T9CONbits.TON = 1;
      }
      else TMR9 = 0x0000;         // reset if timer is on, 115200
}

void _ISR_PSV _U2RXInterrupt(void)      // U2 - RS2-232 RX int 
{   /// RS2-232 RX int   
    RS232_RX_LED = 1;
    uart2_rx_buf[uart2_rx_ptr] = U2RXREG; 
    
    if(uart2_rx_buf[uart2_rx_ptr] == 0x0A)
    {     
      uart2_rx_ptr = 0;
      data_ready = 1; 
    }
    else
     uart2_rx_ptr++;              // ????????? ???????? ?????????? ???? 

    IFS1bits.U2RXIF = 0;   //Clear  UART2_Rx interrupt  
  
}

void _ISR_PSV _T3Interrupt(void)        //interupt Timer 3 - async delays
    {         
        switch(curr_cmd)
        {
            case POL_CHANGE_1:
                if(holding_register[10] == 1) 
                {
                    K1_ON;
                    POL_RELAY_LED = 1;
                }
                else if(holding_register[10] == 0) 
                {
                    K1_OFF;
                    POL_RELAY_LED = 0;
                }
                curr_cmd = POL_CHANGE_2;
                TimerX32_setMs(500);
            break;
            //----------
            case POL_CHANGE_2:
                PSP405_set_output(holding_register[12]);
                TimerX32_state(0);
                curr_cmd = NO_CMD_RUNNING;
            break;
            //----------
            case SRC_CMD:
                curr_cmd = NO_CMD_RUNNING;
                TimerX32_state(0);
            break;   
        }     

        TMR3 = 0x0000;       // reset if timer is on
        TMR2 = 0x0000;
        IFS0bits.T3IF = 0;   // Clear Timer interrupt flag  

    } 

void _ISR_PSV _T9Interrupt(void)        //interupt Timer 9
    {      
        T9CONbits.TON = 0;   // stop the timer
        timer_state = 0;
        TMR9 = 0x0000;       // reset if timer is on
        rx_flag = 1;
        
//        TX_EN;
//        for(int i = 0; i < 16; i++)
//             U1_send_byte(rx_buf[i]);
//  
//        TX_DIS;

        IFS3bits.T9IF = 0;   // Clear Timer interrupt flag
    } 

/*=========================================================================== */ 
// 25LC128 SPI EEPROM

void eeprom_wr_page(unsigned int address)
{
  // EEPROM write enable sequence
  SPI_nCS_LOW;
  __delay_us(1);
  SPI2_send_byte(EEPROM_WREN);
  __delay_us(1);
  SPI_nCS_HIGH;
  __delay_us(20);
  
  // EEPROM address and data write sequence
  SPI_nCS_LOW;
  __delay_us(1);
  SPI2_send_byte(EEPROM_WRITE);
  
  SPI2_send_byte((unsigned char)(address >> 8));      // set address ptr msb
  SPI2_send_byte((unsigned char)(address & 0x00ff));  // set address ptr lsb
  
  for(unsigned char i = 0; i < 32; i++) // max bytes to write - 64
  {
    SPI2_send_byte((unsigned char)(holding_register[i + address/2] >> 8));            // data msb    
    SPI2_send_byte((unsigned char)(holding_register[i + address/2] & 0x00ff));        // data lsb 
  }
  __delay_us(1);
  SPI_nCS_HIGH;
  __delay_ms(10);  // Internal Write Cycle Time Ч 5 ms
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
  SPI_nCS_LOW;
  SPI2_send_byte(EEPROM_READ);
  
  SPI2_send_byte((unsigned char)(address >> 8));      // set address ptr msb
  SPI2_send_byte((unsigned char)(address & 0x00ff));  // set address ptr lsb

  for(unsigned char i = 0; i < max_regs_cnt-1; i++)
  { 
  
    msb = SPI2_read_byte();
    lsb = SPI2_read_byte();
    
    holding_register[i] = (unsigned int)(((unsigned int)msb << 8) | (unsigned int)lsb);   
  }
  SPI_nCS_HIGH;
}
/*=========================================================================== */ 
/// PSP405 functions
unsigned char char2num (unsigned char ch)
{ // converts char symbol into number
  return ch - 0x30;
}

unsigned char num2char (unsigned char ch)
{ // converts number into char symbol
  return ch + 0x30;
}

void PSP405_set_voltage(unsigned int voltage)
{ 
  // get chars from number
  unsigned int first_num  = voltage/10000;
  unsigned int sec_num    = (voltage - first_num * 10000)/1000;
  unsigned int thidr_num  = (voltage - first_num * 10000- sec_num*1000)/100;
  unsigned int fourth_num = (voltage - first_num * 10000 - sec_num*1000 - thidr_num*100)/10;
  // send SV xx.xx<cr> cmd
  uart2_text_send("SV ");
  uart2_send_hex(num2char(first_num));
  uart2_send_hex(num2char(sec_num));
  uart2_text_send(".");
  uart2_send_hex(num2char(thidr_num));
  uart2_send_hex(num2char(fourth_num));
  uart2_send_hex(0x0D);
}
  
void PSP405_set_voltage_lim(unsigned int voltage_lim)
{
  // get chars from number
  unsigned int first_num  = voltage_lim/10;
  unsigned int sec_num    = (voltage_lim - first_num * 10);
  // send SU xx<cr> cmd
  uart2_text_send("SU ");
  uart2_send_hex(num2char(first_num));
  uart2_send_hex(num2char(sec_num));
  uart2_send_hex(0x0D);    
}

void PSP405_set_power_lim(unsigned int power_lim)
{
  // get chars from number
  unsigned int first_num  = power_lim/100;
  unsigned int sec_num    = (power_lim - first_num * 100)/10;
  unsigned int third_num  = (power_lim - first_num * 100 - sec_num * 10);
  // send Wwww.w<cr> 6 characters totally + CR/LF
  uart2_text_send("SP ");
  uart2_send_hex(num2char(first_num));
  uart2_send_hex(num2char(sec_num));
  uart2_send_hex(num2char(third_num));
  uart2_send_hex(0x0D);    
}

void PSP405_set_current(unsigned int current)
{ // current in mA
  // get chars from number
  unsigned int first_num  = current/1000;
  unsigned int sec_num    = (current - first_num * 1000)/100;
  unsigned int thidr_num  = (current - first_num * 1000 - sec_num*100)/10;
  // send SI x.xx<cr> cmd
  uart2_text_send("SI ");
  uart2_send_hex(num2char(first_num));
  uart2_text_send(".");
  uart2_send_hex(num2char(sec_num));
  uart2_send_hex(num2char(thidr_num));
  uart2_send_hex(0x0D);    
}

void PSP405_set_output(unsigned int state)
{   
    char *s = (state) ? "KOE" : "KOD"; 
    uart2_text_send(s);       // send get voltage cmd
    uart2_send_hex(0x0D);  
    
//    // повторна€ отправка, костыль тк не всегда срабатывает
//    __delay_ms(20); 
//    uart2_text_send(s);       // send get voltage cmd
//    uart2_send_hex(0x0D);    
}

void PSP405_get_all()
{
  uart2_send_hex('L');
  uart2_send_hex(0x0D);
}

void PSP405_rx_parse(unsigned char parse_state)
{   
  switch(parse_state)
  {
  case 0:
    rd_voltage     = ERROR_CODE;
    rd_current     = ERROR_CODE;
    rd_voltage_lim = ERROR_CODE;
    rd_current_lim = ERROR_CODE;
    rd_power_lim   = ERROR_CODE;
    rd_status      = ERROR_CODE;
  break;
  //====================================================
  case 1:
    // PSP2010 - uart2_rx_buf[37] == 0x0D, PSP4005 uart2_rx_buf[38] == 0x0D  !!!
      
    //------- checking answer to be Vvv.vv<cr>
    if(uart2_rx_buf[0] == 'V' && (uart2_rx_buf[37] == 0x0D || uart2_rx_buf[38] == 0x0D))
    {  // ok, got nice answer
       rd_voltage = char2num(uart2_rx_buf[1]) * 10000 + 
                    char2num(uart2_rx_buf[2]) * 1000  +
                    char2num(uart2_rx_buf[4]) * 100   +
                    char2num(uart2_rx_buf[5]) * 10;
         
    }
    //------- checking answer to be Av.vvv<cr>
    if(uart2_rx_buf[6] == 'A' && (uart2_rx_buf[37] == 0x0D || uart2_rx_buf[38] == 0x0D)) 
    {  // ok, got nice answer
       rd_current = char2num(uart2_rx_buf[7]) * 1000 + 
                    char2num(uart2_rx_buf[9]) * 100  +
                    char2num(uart2_rx_buf[10])* 10   +
                    char2num(uart2_rx_buf[11]);
    }
    //------- checking src answer to be Uuu<cr>
    if(uart2_rx_buf[18] == 'U' && (uart2_rx_buf[37] == 0x0D || uart2_rx_buf[38] == 0x0D))
    {  // ok, got nice answer
       rd_voltage_lim =  char2num(uart2_rx_buf[19]) * 10 + char2num(uart2_rx_buf[20]);
    }
    //------- checking src answer to be Ii.ii<cr>
    if(uart2_rx_buf[21] == 'I' && (uart2_rx_buf[37] == 0x0D || uart2_rx_buf[38] == 0x0D))
    {  // ok, got nice answer
       rd_current_lim = char2num((unsigned char)uart2_rx_buf[22]) * 1000 + 
                        char2num((unsigned char)uart2_rx_buf[24]) * 100  +
                        char2num((unsigned char)uart2_rx_buf[25]) * 10;
    }
    //------- checking src answer to be Pxxx<cr>
    if(uart2_rx_buf[26] == 'P' && (uart2_rx_buf[37] == 0x0D || uart2_rx_buf[38] == 0x0D))
    {  // ok, got nice answer
       rd_power_lim =   char2num((unsigned char)uart2_rx_buf[27]) * 100 + 
                        char2num((unsigned char)uart2_rx_buf[28]) * 10  +
                        char2num((unsigned char)uart2_rx_buf[29]);
    }
    //------- checking src answer to be Fffffff<cr> 
    if(uart2_rx_buf[30] == 'F' && (uart2_rx_buf[37] == 0x0D || uart2_rx_buf[38] == 0x0D))
    {  // ok, got nice answer
        rd_status = char2num(uart2_rx_buf[31]);
    }
    break;
    //====================================================
    default: break;
  }
}
  
void PSP405_state_restore(void)
{  
    eeprom_rd_regs(); // reading sets from SPI EEPROM
    
    PSP405_set_voltage(holding_register[7]);
    __delay_ms(400);
    //// reg 8 - set voltage limit
    if(holding_register[8] > MAX_VOLTAGE/100) holding_register[8] = MAX_VOLTAGE/100;
    PSP405_set_voltage_lim(holding_register[8]);
    __delay_ms(400);
    //// reg 9 - set current
    if(holding_register[9] > MAX_CURRENT) holding_register[9] = MAX_CURRENT;
    PSP405_set_current(holding_register[9]);
    __delay_ms(400);
    
    // polarity and LED state restore
    if (holding_register[10] == 1) 
    {
        K1_ON;
        POL_RELAY_LED = 1;
    }
    else if(holding_register[10] == 0) 
    {
        K1_OFF; 
        POL_RELAY_LED = 0;
    }
    
    // modbus device id
    if((holding_register[20] >= 254 ) || (dev_id == 0)) 
        dev_id = DEFAULT_DEV_ID;
    else
        dev_id = (unsigned char)holding_register[20];
}
/*=========================================================================== */

void reset_dev_id(void)
{
        if(!RES_BUT) 
        {       
            // сброс настроек на заводские
            // задержка 3 сек - проверка на длительное нажатие
          for(int i = 0; i < 60; i++)   __delay_ms(5);
          
          if(RES_BUT) { }
          else 
            dev_id = DEFAULT_DEV_ID;
        }
}

int main(void) 
{
unsigned int BaseCnt = 0, ErrCnt = 0;

OSC_init();
GPIO_init();

TX_DIS;       // release RS485 line
SPI_nCS_HIGH; // set SPI nCS line HIGH - EEPROM

modbus_init();

SPI2_init();  // Serial EEPROM 
PSP405_state_restore(); // restore PS state - V, I, relay state

UART1_init(); // Modbus UART
UART2_init(); // RS232 UART

Timer9_init(115200);
TimerX32_init();

RS232_TX_LED = 0;
RS232_RX_LED = 0;

curr_cmd = NO_CMD_RUNNING; // able to read src

enableInterrupts();

while(1)
{ 
    
  modbus_poll();  // answer, contains 10 ms delay
  reset_dev_id(); // id change event check
  //PSP405_get_all();   // send cmd via RS232 to get all src data
  if(curr_cmd == NO_CMD_RUNNING) // reading src if no cmds executed at the moment
  {    
    if(data_ready)  // if source asnwer is OK
    { 
        RS232_TX_LED = 0; 
        PSP405_rx_parse(1);
        data_ready = 0;
        BaseCnt = 0;
        ErrCnt = 0;
        PSP405_get_all();   // send cmd via RS232 to get all src data

        RS232_TX_LED = 1; 
        RS232_RX_LED = 0; 
    }
    else                    // if source no respond 
    {   
        BaseCnt++;
        __delay_ms(1);
        if(BaseCnt > 500) 
        {  
         RS232_TX_LED = 0; 
         BaseCnt = 0;
         ErrCnt++;
         if(ErrCnt > 3) PSP405_rx_parse(0);
         data_ready=0;
         PSP405_get_all();  // send cmd via RS232 to get all src data

         RS232_TX_LED = 1; 
         RS232_RX_LED = 0; 
        }
    }
} // NO_CMD_RUNNING
}
}