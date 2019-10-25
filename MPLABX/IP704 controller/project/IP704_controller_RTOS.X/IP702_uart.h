#ifndef IP702_UART_H
#define	IP702_UART_H
 
#ifdef	__cplusplus
extern "C"
{
#endif
	
#define _ISR_PSV __attribute__((__interrupt__, __auto_psv__))
#define FP 40000000
#define U2_BAUDRATE 57600
#define U2BRGVAL ((FP/U2_BAUDRATE)/16)-1 
	
/* TO IP702 RS485 EN/DIS DEFINE */
#define IP702_TX_EN  TRISGbits.TRISG9 = 0;   LATGbits.LATG9 = 1;
#define IP702_TX_DIS TRISGbits.TRISG9 = 0;   LATGbits.LATG9 = 0;

void Uart2Init(void);

void Uart2SendByte(unsigned char Ch);

void Uart2ResetQueue(void);

UBaseType_t Uart2GetQcnt(void);

void _ISR_PSV _U2RXInterrupt(void);

#ifdef	__cplusplus
}
#endif

#endif	/* IP702_UART_H */

