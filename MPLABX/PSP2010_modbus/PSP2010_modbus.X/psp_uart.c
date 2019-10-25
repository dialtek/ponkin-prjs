#include "main.h"
#include "psp_uart.h"

extern volatile unsigned char uart2_rx_buf[40];
extern volatile unsigned char rx_msg[40];
extern volatile unsigned char uart2_rx_ptr;
extern volatile unsigned char data_ready;

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
