#ifndef KORAD_UART_H
#define	KORAD_UART_H
 
#ifdef	__cplusplus
extern "C"
{
#endif
	
#define _ISR_PSV __attribute__((__interrupt__, __auto_psv__))
#define FP 40000000
#define U2_BAUDRATE 9600
#define U2BRGVAL ((FP/U2_BAUDRATE)/16)-1 

void Uart2Init(void);

void Uart2SendByte(unsigned char Ch);

void Uart2SendText(char *s);

void Uart2ResetQueue(void);

UBaseType_t Uart2GetQcnt(void);

void _ISR_PSV _U2RXInterrupt(void);

#ifdef	__cplusplus
}
#endif

#endif	/* KORAD_UART_H */

