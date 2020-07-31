/******************************************************************************
 * @File: clk.h
 * @Author: Milandr, L.
 * @Project: Generic
 * @Version: 1.0.0
 * @Compiler: ARM Compiler V5.06 (build 750)
 * @Microcontroller: К1986ВЕ92QI
 * @Device: Отладочная плата «МилКиТЭС»
 * @Date: 12.03.2020
 * @Purpose: Конфигурация системы тактирования микроконтроллера
 ******************************************************************************/

#ifndef __CLK_H
#define __CLK_H

// Подключение библиотеки микроконтроллера
#include <1986VE9x.h>

// Макрос задержки (1 TICK = 1 мс)
#define WAIT(TICK) for (volatile uint32_t i = 0;                                       \
                                          i < SystemCoreClock / (34 * 1000) * (TICK);  \
                                          i++)

// Кроссмодульные переменные
extern uint32_t SystemCoreClock;

// Прототипы функций
void CPU_Reset(void);
void CPU_Init(void);

#endif
