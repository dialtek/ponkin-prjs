#include "FreeRTOS.h"
#include "queue.h"
#include "semphr.h"
#include "dialtek_uart.h"

static volatile QueueHandle_t xRxedChars; 
static volatile unsigned char RxByte;
static UBaseType_t RxBytesCnt;

volatile unsigned char timer_state = 0;
extern SemaphoreHandle_t RxSemaphore;

static BaseType_t xHigherPriorityTaskWoken; 

void Timer9_init(unsigned long baudrate)
{
       IPC13bits.T9IP = configKERNEL_INTERRUPT_PRIORITY;
       T9CONbits.TON = 0;           // Timer on/off bit; 0 - Disable Timer
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

void UartInit()
{
    // RX interrupt UART1 settings 
    IPC2bits.U1RXIP = configKERNEL_INTERRUPT_PRIORITY + 2;
    IFS0bits.U1RXIF = 0;   // Reset UART1 RX interrupt flag
    
    U1BRG = U1BRGVAL;      // Baud Rate setting for 115200 uart
    U1MODEbits.UARTEN = 1;  // 1 = UARTx is enabled; all UARTx pins are controlled by UARTx as defined by UEN <1:0>
    U1MODEbits.UEN = 0;     // 0 = UxTX and UxRX pins are enabled and used; UxCTS and UxRTS/BCLK pins controlled by port latches
    U1MODEbits.PDSEL = 0;   // 0 = No Parity, 8-Data bits
    U1MODEbits.ABAUD = 0;   // 0 = Baud rate measurement disabled or completed
    U1MODEbits.BRGH = 0;    // 1 = BRG generates 4 clocks per bit period (4x baud clock, High-Speed mode)
    U1MODEbits.STSEL = 0;   // 0 = 1-Stop bit

    U1STAbits.UTXINV = 0;
    U1STAbits.UTXEN = 1;    // 1 = Transmit enabled, UxTX pin controlled by UARTx
    U1STAbits.URXISEL = 0;  // 0x = Interrupt is set when any unsigned character is received and transferred from the UxRSR to the receive buffer. Receive buffer has one or more unsigned characters.
                            // The URXISEL<1:0> (UxSTA<7:6>) control bits determine when the UART receiver generates an interrupt.
 
    IEC0bits.U1RXIE = 1; // Enable UART1 RX interrupt  

    // create UART RX bytes queue
    xRxedChars = xQueueCreate(32, sizeof(unsigned char));
    Timer9_init(115200);
    //RxMsgReady = xSemaphoreCreateBinary();
 }

void UartSendByte(unsigned char Ch)
{ // отправка 1 байта данных

        U1TXREG = Ch;

        asm volatile ( "NOP" );
        asm volatile ( "NOP" );
        asm volatile ( "NOP" );
        asm volatile ( "NOP" );
        asm volatile ( "NOP" );
        asm volatile ( "NOP" );
        asm volatile ( "NOP" );
        asm volatile ( "NOP" );
        asm volatile ( "NOP" );
        asm volatile ( "NOP" );
        
        while(U1STAbits.TRMT == 0); //waiting for trancsaction to be complete 
        //  should wait at least one instruction cycle between 
        //  writing UxTXREG and reading the TRMT bit 
 }

signed short UartGetChar(unsigned char *pcRxedChar, TickType_t xBlockTime )
{
    
	if( xQueueReceive(xRxedChars, pcRxedChar, xBlockTime ) )
	{
		return pdTRUE;
	}
	else
	{
		return pdFALSE;
	}
}

void _ISR_PSV _U1RXInterrupt(void)      //interupt UART 1 RX MODBUS
{
      // rx buffer has data, at least one more character can be read
      //while(U1STAbits.URXDA == 0){ }
      
      RxByte = (unsigned char)U1RXREG;

      IFS0bits.U1RXIF = 0;    // Clear  UART1_Rx interrupt  
      
      if(timer_state == 0)
      {
            TMR9 = 0x0000;
            IFS3bits.T9IF = 0;    // Clear Timer interrupt flag
            timer_state = 1;
            T9CONbits.TON = 1;
      }
      else TMR9 = 0x0000;         // reset if timer is on, 115200       
      
      xQueueSendFromISR(xRxedChars, (void*)&RxByte, 0);
}

void _ISR_PSV _T9Interrupt(void)        //interupt Timer 9
{      
        T9CONbits.TON = 0;   // stop the timer
        timer_state = 0;
        TMR9 = 0x0000;       // reset if timer is on

        xSemaphoreGiveFromISR(RxSemaphore,&xHigherPriorityTaskWoken);
        
        IFS3bits.T9IF = 0;   // Clear Timer interrupt flag
        
        //if(xHigherPriorityTaskWoken)
        //    taskYIELD();
} 

UBaseType_t UartGetQcnt(void)
{
   return uxQueueMessagesWaiting(xRxedChars); 
}

void UartResetQueue(void)
{ 
    xQueueReset(xRxedChars);
}