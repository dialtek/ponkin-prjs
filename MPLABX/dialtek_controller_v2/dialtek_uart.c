#include "xc.h"
#include "dialtek_uart.h"
/*=========================================================================== */
volatile unsigned char timer_state = 0;

extern volatile unsigned int rx_buf_ptr;
extern volatile unsigned char rx_buf[128];
extern volatile char rx_flag;
/*=========================================================================== */
void Timer9_init(unsigned long baudrate)
{
       IPC13bits.T9IP = 6;
       T9CONbits.TON = 0;           // Timer on/off bit; 0 - Disable Timer
       IFS3bits.T9IF = 0;           // Clear Timer interrupt flag
       TMR9 = 0x0000;               // reset if timer is on, 460800
       T9CONbits.TCS = 0;           // Timer Clock Source Select bit; 0 - Internal clock (FOSC/2)
       T9CONbits.TGATE = 0;         // Disable Gated Timer mode
       T9CONbits.TCKPS = 0;         // Prescaler = (00=1, 01=8, 10=64, 11=256) 
       T8CONbits.T32 = 0;
       
       // f timer = 60M => 1x timer tick = 0.016 us
       
       switch(baudrate)
       {

           case 460800: PR9 = 4000; break; // 1 byte - 18 us (1125 ticks), 4000 = 64 us;
               
           default: PR9 = 4000; // Load the period value
       }
       
       IEC3bits.T9IE = 1;           // Enable T9 interrupt 
}

// UART 1 - Modbus
void Uart1Init(void)
{
    // RX interrupt UART1 settings 
    
    // speed = 460800  
    
    // RX interrupt UART1 settings 
    IPC2bits.U1RXIP = 6; // Set UART1 RX interrupt priority to 1 
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

    // create UART RX bytes queue
    Timer9_init(460800UL);
 }

// UART 2 - Hamilton PUMP
void Uart2Init(void)
{
    // speed = 9600  
    
    // RX interrupt UART2 settings 
    IPC7bits.U2RXIP = 5; // Set UART2 RX interrupt priority
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
    while (*s != 0) 
        uart2_send_byte(*s++);
}

 void uart2_CR_LF_send (void)
{  
    
	uart2_send_byte(0x0D);
    uart2_send_byte(0x0A);
}

void UartSendByte(unsigned char Ch)
{ // отправка 1 байта данных

        U1TXREG = Ch;

        //for(volatile int i = 0; i < 10; i++) 
        //    asm volatile ( "NOP" );
       
        while(U1STAbits.TRMT == 0); //waiting for trancsaction to be complete 
        //  should wait at least one instruction cycle between 
        //  writing UxTXREG and reading the TRMT bit 
 }

void _ISR_PSV _U1RXInterrupt(void)      //interupt UART 1 RX MODBUS
{
      // rx buffer has data, at least one more character can be read
      //while(U1STAbits.URXDA == 0){ }
      
      rx_buf[rx_buf_ptr++] = U1RXREG;

      IFS0bits.U1RXIF = 0;    // Clear UART1 RX interrupt  
      
      if(timer_state == 0)
      {
            TMR9 = 0x0000;
            IFS3bits.T9IF = 0;    // Clear Timer interrupt flag
            timer_state = 1;
            T9CONbits.TON = 1;
      }
      else TMR9 = 0x0000;         // reset if timer is on, 115200       
}

void _ISR_PSV _U2RXInterrupt(void)      //interupt UART 2 RX PUMP
{
      IFS1bits.U2RXIF = 0;              // Clear  UART2 Rx interrupt  
}

void _ISR_PSV _T9Interrupt(void)        //interupt Timer 9
{      
        T9CONbits.TON = 0;   // stop the timer
        timer_state = 0;
        TMR9 = 0x0000;       // reset if timer is on
        
        rx_flag = 1;         // fire modbus cmd rx flag
        
        IFS3bits.T9IF = 0;   // Clear Timer interrupt flag
} 

// UART
/*=========================================================================== */