/******************************************************************************
 * @File: led.h
 * @Author: Milandr, L.
 * @Project: Demo_Project_2-3
 * @Version: 1.0.0
 * @Compiler: ARM Compiler V5.06 (build 750)
 * @Microcontroller: К1986ВЕ92QI
 * @Device: Отладочная плата «МилКиТЭС»
 * @Date: 12.04.2020
 * @Purpose: Конфигурация портов для работы светодиодов
 ******************************************************************************/

// Условная компиляция
#ifndef __LED_H
#define __LED_H

// Подключение заголовков
#include "link.h"

// Пределы состояний системы
#define LED_STATE_MIN 0
#define LED_STATE_MAX 3

// Прототипы функций
void LED_Init(void);
void LED_Handler(void);
void LED_Reset(void);

#endif
