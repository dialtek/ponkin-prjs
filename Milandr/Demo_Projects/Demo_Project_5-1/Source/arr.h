/******************************************************************************
 * @File: arr.h
 * @Author: Milandr, L.
 * @Project: Demo_Project_5-1
 * @Version: 1.0.0
 * @Compiler: ARM Compiler V5.06 (build 750)
 * @Microcontroller: К1986ВЕ92QI
 * @Device: Отладочная плата «МилКиТЭС»
 * @Date: 30.04.2020
 * @Purpose: Работа с массивами
 ******************************************************************************/

// Условная компиляция
#ifndef __ARR_H
#define __ARR_H

// Подключение заголовков
#include "link.h"

// Размер массивов
#define ARR_S 16

// Кроссмодульные переменные
extern volatile uint8_t source_array[ARR_S];
extern volatile uint8_t result_array[ARR_S];

// Прототипы функций
void PrintElement(uint8_t element, uint8_t x, uint8_t y);
void PrintArray(volatile uint8_t *array);
void FillArray(volatile uint8_t *array);

#endif
