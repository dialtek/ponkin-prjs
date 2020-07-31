/******************************************************************************
 * @File: sort.h
 * @Author: Milandr, L.
 * @Project: Generic
 * @Version: 1.0.0
 * @Compiler: ARM Compiler V5.06 (build 750)
 * @Microcontroller: К1986ВЕ92QI
 * @Device: Отладочная плата «МилКиТЭС»
 * @Date: 31.03.2020
 * @Purpose: Функции сортировки
 ******************************************************************************/

// Условная компиляция
#ifndef __SORT_H
#define __SORT_H

// Подключение библиотеки микроконтроллера
#include "1986VE9x.h"

// Подключение стандартной библиотеки языка Си
#include <stdlib.h>

// Прототипы функций
void BubbleSort(uint32_t *sample, uint32_t size);
void InsertSort(uint32_t *sample, uint32_t size);
void CombSort(uint32_t *sample, uint32_t size);
bool Validate(uint32_t *sample, uint32_t size);
void Randomize(uint32_t *sample, uint32_t size, uint32_t lim);

#endif
