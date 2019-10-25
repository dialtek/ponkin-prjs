/* 
 * File:   psp_uart.h
 * Author: D_LHEP_DESKTOP
 *
 * Created on 27 мая 2019 г., 14:28
 */

#ifndef PSP_UART_H
#define	PSP_UART_H

#ifdef	__cplusplus
extern "C"
{
#endif
	
#define FP 40000000
#define U1_BAUDRATE 115200
#define U2_BAUDRATE 2400
#define U1BRGVAL ((FP/U1_BAUDRATE)/16)-1
#define U2BRGVAL ((FP/U2_BAUDRATE)/16)-1 

void Timer9_init(unsigned long baudrate);
	
void UART1_init(void);
void UART2_init(void);

void U1_send_byte(unsigned char Ch);
void uart2_send_hex (unsigned char Ch);

void uart_CR_LF_send (void);
void uart2_text_send(char *s);
	
void _ISR_PSV _U1RXInterrupt(void);      // U1 - Modbus
void _ISR_PSV _U2RXInterrupt(void);      // U2 - RS2-232 RX int 
void _ISR_PSV _T9Interrupt(void) 

#ifdef	__cplusplus
}
#endif

#endif	/* PSP_UART_H */

