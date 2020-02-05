#ifndef UART_H
#define UART_H

#include "stm32f4xx.h"                  // Device header
#include "stm32f4xx_gpio.h"							// ���������� ������� �����/������
#include "stm32f4xx_rcc.h"							// ���������� ������������ ������
#include "stm32f4xx_tim.h"							// ���������� ��������
#include "stm32f4xx_usart.h"						// ���������� USART
#include "misc.h"												// ���������� NVIC - �������� ����������


void Uart2Init(void); 																									 	// Setting: USART
void UartSendByte(unsigned char TxByte);																	// USART: 	�������� 1 ���
unsigned char UartXreadByte(USART_TypeDef* USARTx);											 	// USART: 	������ 1 ���
void USART2_IRQHandler(void);
void init_timer_TIM2(void);
void TIM2_IRQHandler(void);

#endif


