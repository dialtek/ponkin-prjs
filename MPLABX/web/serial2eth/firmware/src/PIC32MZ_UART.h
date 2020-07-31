/* 
 * File:   PIC32MZ_UART.h
 * Author: ADM
 *
 * Created on 23 мая 2020 г., 13:36
 */

#include "device.h"

#ifndef PIC32MZ_UART_H
#define	PIC32MZ_UART_H

#ifdef	__cplusplus
extern "C"
{
#endif

#define _ISR_PSV __attribute__((__interrupt__, __auto_psv__))
#define FPB 100000000UL // 100 M
#define Desired_Baud_Rate 115200
#define U1BRG1 ((FPB/Desired_Baud_Rate)/4) - 1
#define UART_RX_BUF_SIZE 1024	

void Uart1Init(void);

void Uart1SendByte(unsigned char byte);

void TIMER8_init(void);

unsigned char Uart1_rx_complete(void);

void Uart1_rx_reset(void);

unsigned int Uart1_bytes_get(void);

unsigned char* Uart1_RxBuf_ptr(void);

#ifdef	__cplusplus
}
#endif

#endif	/* PIC32MZ_UART_H */

