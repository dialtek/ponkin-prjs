#include "PIC32MZ_UART.h"

volatile unsigned char UART1_rx_buf[UART_RX_BUF_SIZE];
volatile unsigned int U1_rx_count = 0;
volatile unsigned char timer_state = 0;
volatile unsigned char rx_complete = 0;

// UART1
void Uart1Init(void)
{
    // RX interrupt UART1 settings 
    U1BRG = U1BRG1;
    U1MODEbits.UARTEN = 1;                                      
    U1MODEbits.UEN = 0;                                         // U1TX and U1RX are enabled and used
    U1MODEbits.PDSEL = 0;                                       // No parity, 8 bit data;
    U1MODEbits.ABAUD = 0;                                       // Baud rate measurment disabled or completed;
    U1MODEbits.BRGH = 1;                                        // High-speed mode - 4x baud clock enabled;
    U1MODEbits.STSEL = 0;                                       // 1 stop bit
    U1MODEbits.ON = 1;
    
    U1STAbits.URXISEL0 = 0;
    U1STAbits.URXISEL1 = 0;
    U1STAbits.UTXINV  = 0;
    U1STAbits.UTXEN = 1;
    U1STAbits.URXEN = 1;
    U1STAbits.URXISEL = 0;
    
    IFS3bits.U1TXIF = 0;
    IEC3bits.U1TXIE = 0;  
    
    IFS3bits.U1RXIF = 0;
    IEC3bits.U1RXIE = 1;                // Enable UART1 RX interrupt
    
    TIMER8_init();
}

void Uart1SendByte(unsigned char byte)
{ // отправка 1 байта данных
  
    U1TXREG = (uint32_t)byte;

    while(U1STAbits.TRMT == 0); //waiting for trancsaction to be complete 
        //  should wait at least one instruction cycle between 
        //  writing UxTXREG and reading the TRMT bit 
    //IEC3SET = _IEC3_U1TXIE_MASK;
 }

//interupt UART 1 RX
void __ISR(_UART1_RX_VECTOR, ipl1AUTO) UART1_RX_Handler (void)   
{
    UART1_rx_buf[U1_rx_count++] = (unsigned char)U1RXREG;

    IFS3bits.U1RXIF = 0;       //Clear UART1 RX interrupt 
    
    /* If it's a overrun error then clear it to flush FIFO */
    if(U1STA & _U1STA_OERR_MASK)
        U1STACLR = _U1STA_OERR_MASK;
    
    if(timer_state == 0)
    {
      TMR8 = 0x0000;
      IFS1bits.T8IF = 0;   // Clear Timer interrupt flag
      timer_state = 1;
      T8CONbits.TON = 1;
    }
    else 
      TMR8 = 0x0000;      // reset if timer is on  
}

void __ISR(_TIMER_8_VECTOR, ipl1AUTO) TIMER8_ISR_Handler (void)  
{      
    T8CONbits.TON = 0;   // stop the timer
    timer_state = 0;
    TMR8 = 0x0000;       // reset if timer is on
    
    rx_complete = 1;         // fire modbus cmd rx flag

    IFS1bits.T8IF = 0;   // Clear Timer interrupt flag
} 

void TIMER8_init(void)
{
    T8CONbits.ON = 0;                                  
    T8CONbits.TCS = 0;                                 
    T8CONbits.T32 = 0;    
    
    T8CONbits.TGATE = 0;
    T8CONbits.TCKPS = 0;   
    TMR8 = 0x0000;                   
    PR8  = 87*1000;            //  50 us;  16  TCKPS = 2 - 1 us
    IFS1bits.T8IF = 0;                          
    IEC1bits.T8IE = 1;      // dis T8 interrupt at startup
}

unsigned char Uart1_rx_complete(void)
{
  return (unsigned char) rx_complete;
}

void Uart1_rx_reset(void)
{
    U1_rx_count = 0; 
    rx_complete = 0;
}

unsigned int Uart1_bytes_get(void)
{
  return U1_rx_count;
}

unsigned char* Uart1_RxBuf_ptr(void)
{
  return (void*)&UART1_rx_buf;
}