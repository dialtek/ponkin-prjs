#ifndef SPI_H
#define SPI_H

#include "stm32f4xx.h"                  // Device header
#include "stm32f4xx_gpio.h"							// ���������� ������� �����/������
#include "stm32f4xx_rcc.h"							// ���������� ������������ ������
#include "stm32f4xx_spi.h" 							// ����������� SPI

#define SetChMode (uint8_t)0
#define ReadMode 	(uint8_t)1


void Spi1Init(uint8_t mode, uint8_t f);

#endif
