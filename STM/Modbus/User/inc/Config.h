#ifndef CONFIG_H
#define CONFIG_H

#include "stm32f4xx.h"                  // Device header
#include "stm32f4xx_gpio.h"							// ���������� ������� �����/������
#include "stm32f4xx_rcc.h"							// ���������� ������������ ������
#include "stm32f4xx_tim.h"							// ���������� ��������
#include "misc.h"												// ���������� NVIC - �������� ����������

#define LED_PORT GPIOD
#define LED_GREEN (1<<12)
#define LED_RED (1<<14)

// ��������� �������
#define cPLLM 4 
#define cPLLN 210 
#define cPLLP 4 
#define cPLLQ 8  

void InitClock(void);																									// Setting: ����. �������
void GPIO_Config(void);																								// Setting: IO pins
void TIM_Config(void);																								// Setting: ������
void delay_us(uint32_t value);
void delay_ms(uint16_t value);																				// TIM: 		�������������� ��������


#endif 

