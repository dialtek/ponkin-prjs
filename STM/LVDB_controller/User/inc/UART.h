#ifndef UART_H
#define UART_H

#include "stm32f4xx.h"                  // Device header
#include "stm32f4xx_gpio.h"							// ”правление портами ввода/вывода
#include "stm32f4xx_rcc.h"							// ”правление тактирование портов
#include "stm32f4xx_tim.h"							// ”правление таймером
#include "stm32f4xx_usart.h"						// ”правление USART
#include "misc.h"												// ”правление NVIC - контроль прерываний


void Uart2Init(void); 																									 	// Setting: USART
void UartSendByte(unsigned char TxByte);																	// USART: 	отправка 1 бит
unsigned char UartXreadByte(USART_TypeDef* USARTx);											 	// USART: 	чтение 1 бит
void USART2_IRQHandler(void);
void init_timer_TIM2(void);
void TIM2_IRQHandler(void);

#endif


