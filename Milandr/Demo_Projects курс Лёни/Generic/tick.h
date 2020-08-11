/******************************************************************************
 * @File: tick.h
 * @Author: Milandr, L.
 * @Project: Generic
 * @Version: 1.0.0
 * @Compiler: ARM Compiler V5.06 (build 750)
 * @Microcontroller: К1986ВЕ92QI
 * @Device: Отладочная плата «МилКиТЭС»
 * @Date: 20.03.2020
 * @Purpose: Реализация временной базы
 ******************************************************************************/

// Условная компиляция
#ifndef __TICK_H
#define __TICK_H

// Подключение библиотеки микроконтроллера
#include <1986VE9x.h>

// Подключение конфигурации системы тактирования
#include <clk.h>

// Частота системных квантов (в Гц)
#define SYSTEM_TICK_RATE 1000

// Кол-во независимых интервалов ожидания
#define WAIT_NUMBER 16

// Кроссмодульные переменные
extern uint32_t system_ticks;
extern uint32_t ticks_mark[WAIT_NUMBER];

// Прототипы функций
void TICK_Init(void);
bool Wait(uint32_t *ticks_mark, uint32_t wait_ticks);

#endif
