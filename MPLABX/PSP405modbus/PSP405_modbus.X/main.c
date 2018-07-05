
#include <stdio.h>
#include <stdlib.h>
#include "fuses.h"
#include "p24Hxxxx.h"

#include "c30_delay.h"
#include <p24HJ128GP506A.h>

#define _ISR_PSV __attribute__((__interrupt__, __auto_psv__))
  
#define FCY 40000000UL
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


#define K1_ON LATGbits.LATG12 = 1   // K1 relay ON 
#define K1_OFF LATGbits.LATG12 = 0   // K1 relay OFF 

unsigned char uart2_rx_buf[40] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};   
unsigned char rx_msg[40] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};  
unsigned char uart2_rx_ptr = 0;
unsigned char data_ready = 0;
unsigned int rd_status, rd_voltage = 0, rd_current = 0, 
             rd_voltage_lim = 0, rd_current_lim = 0, rd_power_lim = 0;

// funcs prototypes
void uart2_text_send(char *s);
void uart_num_send(long data);

#include "dialtek_modbus.h"

void OSC_init()
{
    // FCY=FOSC/2, FOSC= FIN*M/(N1*N2) 
    CLKDIVbits.PLLPRE = 0;      // 0 - divider N1 = 2
    PLLFBD = 30;                // multiplier M = PLLFBD + 2
    CLKDIVbits.PLLPOST = 0;     // 0 - divider N2 = 2

    OSCTUN=0;                   // 000000 = Center frequency (7.37 MHz nominal)
    RCONbits.SWDTEN=0;          // Disable Watch Dog Timer

    while(OSCCONbits.LOCK !=1) {};   // 1 = Indicates that PLL is in lock, or PLL start-up timer is satisfied
                                    // 0 = Indicates that PLL is out of lock, start-up timer is in progress or PLL is disabled
    //note: FOSC= 10 MHz * 32/(2*2) = 80 MHz, FCY = 80/2
}   
/*=========================================================================== */
// UART 
void UART1_init()
{   /// modbus 
    // RX interrupt UART1 settings 
    IPC2bits.U1RXIP = 7; // Set UART1 RX interrupt priority to 1 
    IFS0bits.U1RXIF = 0; // Reset UART1 RX interrupt flag
    IEC0bits.U1RXIE = 1; // Enable UART1 RX interrupt
    
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
  
 //Once enabled, the UxTX and UxRX pins are configured as an output and an
 //input, respectively, overriding the TRIS and PORT register bit settings for the corresponding I/O port pins. 
}

void UART2_init()
{   /// RS-232 
    // RX interrupt UART2 settings 
    IPC7bits.U2RXIP = 7;   // Set UART2 RX interrupt priority to 4
    IFS1bits.U2RXIF = 0;   // Reset UART2 RX interrupt flag
    IEC1bits.U2RXIE = 1;   // EN UART2 RX interrupt
    
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
  
 //Once enabled, the UxTX and UxRX pins are configured as an output and an
 //input, respectively, overriding the TRIS and PORT register bit settings for the corresponding I/O port pins. 
}

unsigned char UART1GetChar ()
{
    unsigned char buf;
    while(IFS0bits.U1RXIF == 0) { }
    buf = U1RXREG;
    //IFS0bits.U1RXIF = 0;
    return buf; 
}
  
void uart_send_hex (unsigned char Ch)
{ // ??? ??????? ?????? ????????? ? ?????? ? ????. ??????
    
    U1TXREG = Ch;
    while(U1STAbits.TRMT == 0){ }
    delay_us(200);
    // waiting for trancsaction to be complete
   
}

void uart2_send_hex (unsigned char Ch)
{ // RS-232 send byte
    
    while(U2STAbits.TRMT == 0){ }
    U2TXREG = Ch;
     __delay_us(50);
    // waiting for trancsaction to be complete
}

void uart_CR_LF_send (void){
	  
    uart_send_hex(0x0A);
	uart_send_hex(0x0D);
	
	}

void uart_num_send(long data){
	  
  unsigned char temp[10],count=0;
  if (data<0) 
  {
    data=-data;
    uart_send_hex('-');
  }     
  if (data)
  {
    while (data)
    {
      temp[count++]=data%10+'0';
      data/=10;                 
    }                           
    while (count)           
      uart_send_hex(temp[--count]);          
  }
  else uart_send_hex('0');           
}

void uart_text_send(char *s){
  while (*s != 0)
    uart_send_hex(*s++);
}

void uart2_text_send(char *s){
  while (*s != 0)
    uart2_send_hex(*s++);
}

/*=========================================================================== */
void _ISR_PSV _U1RXInterrupt(void)      //interupt UART 1 RX
{ /// ?????????? ????????? ??? ??????????? 1 ????? ?? UART1
        
    modbus_uart_byte(U1RXREG);
    IFS0bits.U1RXIF = 0;   //Clear  UART1_Rx interrupt   
}

void _ISR_PSV _U2RXInterrupt(void)      //interupt UART 2 RX
{   /// RS2-232 RX int   
    
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
  
void GPIO_init()
{
    // PORT B
    TRISBbits.TRISB14 = 0;
    //PORT C
    TRISCbits.TRISC1 = 0; // OUT2
    TRISCbits.TRISC2 = 0; // OUT3
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
    TRISGbits.TRISG0=0;
    TRISGbits.TRISG6=0;   // OUT4
    TRISGbits.TRISG9=0;
    TRISGbits.TRISG12=0;  // coil 1
    TRISGbits.TRISG13=0;
    TRISGbits.TRISG14=0;
    TRISGbits.TRISG15=0;  // OUT1
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

/*=========================================================================== */

int main(void) 
{
    OSC_init();
    GPIO_init();
    UART1_init();
    UART2_init();
    //Timer1_init();
    modbus_init();

    unsigned int count = 0;

while(1)
{        
  
  modbus_rx_sm();
  modbus_poll();
  __delay_ms(1); 

   if(data_ready)
   { 
    PSP405_rx_parse(1);
    PSP405_get_all();
    data_ready = 0;
    count = 0;
   }
   else
   {   
    count++;
    if(count > 3000) 
    { 
      PSP405_rx_parse(0);
      PSP405_get_all();
      count = 0;
      data_ready=0;
    }
    
   }
  
  
  }
}