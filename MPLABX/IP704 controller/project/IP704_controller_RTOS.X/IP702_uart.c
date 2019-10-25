#include <p24HJ256GP206.h>
#include "FreeRTOS.h"
#include "queue.h"
#include "semphr.h"
#include "IP702_uart.h"

static volatile unsigned char RxByte;
static UBaseType_t RxBytesCnt;

volatile QueueHandle_t IP702RxBytes;

void Uart2Init()
{
   // RX interrupt UART2 settings 
    IPC7bits.U2RXIP = configKERNEL_INTERRUPT_PRIORITY + 3; // Set UART2 RX interrupt priority to 3
    IFS1bits.U2RXIF = 0; // Reset UART2 RX interrupt flag

    U2BRG = U2BRGVAL;      // Baud Rate setting  
    U2MODEbits.UARTEN = 1; // 1 = UARTx is enabled; all UARTx pins are controlled by UARTx as defined by UEN <1:0>
    U2MODEbits.UEN = 0;   // 0 = UxTX and UxRX pins are enabled and used; UxCTS and UxRTS/BCLK pins controlled by port latches
    U2MODEbits.PDSEL = 0; // 0 = No Parity, 8-Data bits
    U2MODEbits.ABAUD = 0; // 0 = Baud rate measurement disabled or completed
    U2MODEbits.BRGH = 0;  // 1 = BRG generates 4 clocks per bit period (4x baud clock, High-Speed mode)
    U2MODEbits.STSEL = 0; // 1 = 2-Stop bit !!!!!!!!!!!!!! IP702 needed

    U2STAbits.URXISEL0 = 0; // Interrupt flag bit is set when a character is received
    U2STAbits.URXISEL1 = 0;
    U2STAbits.UTXINV = 0;
    U2STAbits.UTXEN = 1; // 1 = Transmit enabled, UxTX pin controlled by UARTx
    // The URXISEL<1:0> (UxSTA<7:6>) control bits determine when the UART receiver generates an interrupt.
    IEC1bits.U2RXIE = 1; // EN UART2 RX interrupt
    //Once enabled, the UxTX and UxRX pins are configured as an output and an
    //input, respectively, overriding the TRIS and PORT register bit settings for the corresponding I/O port pins. 

    // create UART2 RX bytes queue
    IP702RxBytes = xQueueCreate(16, sizeof(unsigned char));
 }

void Uart2SendByte(unsigned char Ch)
{ // отправка 1 байта данных

        U2TXREG = Ch;

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
        
        while(U2STAbits.TRMT == 0); //waiting for trancsaction to be complete 
        //  should wait at least one instruction cycle between 
        //  writing UxTXREG and reading the TRMT bit 
 }

signed short Uart2GetChar(unsigned char *pcRxedChar, TickType_t xBlockTime )
{
    
	if( xQueueReceive(IP702RxBytes, pcRxedChar, xBlockTime ) )
	{
		return pdTRUE;
	}
	else
	{
		return pdFALSE;
	}
}

void _ISR_PSV _U2RXInterrupt(void)      //interupt UART 1 RX IP702C
{
      RxByte = (unsigned char)U2RXREG;

      IFS1bits.U2RXIF = 0;    // Clear  UART2_Rx interrupt  
              
      xQueueSendFromISR(IP702RxBytes, (void*)&RxByte, 0);
}

UBaseType_t Uart2GetQcnt(void)
{
   return uxQueueMessagesWaiting(IP702RxBytes); 
}

void Uart2ResetQueue(void)
{ 
    xQueueReset(IP702RxBytes);
}
