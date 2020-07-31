/******************************************************************************
 * @File: main.c
 * @Author: Milandr, L.
 * @Project: Demo_Project_6-2
 * @Version: 1.0.0
 * @Compiler: ARM Compiler V5.06 (build 750)
 * @Microcontroller: К1986ВЕ92QI
 * @Device: Отладочная плата «МилКиТЭС»
 * @Date: 19.05.2020
 * @Purpose: Связывание модулей проекта
 ******************************************************************************/

// Условная компиляция
#ifndef __LINK_H
#define __LINK_H

// Подключение библиотеки микроконтроллера
#include <1986VE9x.h>

// Подключение стандартной библиотеки языка Си
#include <stdlib.h>

// Подключение библиотеки математических операций
#include <math.h>

// Подключение заголовков модулей проекта
#include <clk.h>
#include <tick.h>
#include <btn.h>
#include <lcd.h>
#include "dac.h"
#include "tmr.h"
#include "dma.h"

#endif
