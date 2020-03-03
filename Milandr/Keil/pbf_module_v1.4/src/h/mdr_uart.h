#ifndef MDR_UART_H
#define	MDR_UART_H
 
#ifdef	__cplusplus
extern "C"
{
#endif
	
#define FP 40000000
#define U2_BAUDRATE 57600

void UartInit(void);

void UartSendByte(uint8_t sByte);
	
int8_t UartGetByte(uint8_t  *pcRxedChar, TickType_t xBlockTime);
	
__irq void UART1_IRQHandler(void); // U1 rx interrupt handler UART1

UBaseType_t UartGetQcnt(void);
	
void UartResetQueue(void);
	
#ifdef	__cplusplus
}
#endif

#endif	/* MDR_UART_H */