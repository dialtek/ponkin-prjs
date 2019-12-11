#ifndef DIALTEK_UART_H
#define	DIALTEK_UART_H
 
#ifdef	__cplusplus
extern "C"
{
#endif
	
#define _ISR_PSV __attribute__((__interrupt__, __auto_psv__))
#define FP 40000000
#define U1_BAUDRATE 115200
#define U1BRGVAL ((FP/U1_BAUDRATE)/16)-1

void UartInit(void);

void UartSendByte(unsigned char Ch);

void UartResetQueue(void);

UBaseType_t UartGetQcnt(void);

void _ISR_PSV _T9Interrupt(void);

void _ISR_PSV _U1RXInterrupt(void);

#ifdef	__cplusplus
}
#endif

#endif	/* DIALTEK_UART_H */

