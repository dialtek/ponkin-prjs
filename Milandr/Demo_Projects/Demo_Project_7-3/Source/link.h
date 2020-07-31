/******************************************************************************
 * @File: main.h
 * @Author: Milandr, L.
 * @Project: Demo_Project_7-3
 * @Version: 1.0.0
 * @Compiler: ARM Compiler V5.06 (build 750)
 * @Microcontroller: К1986ВЕ92QI
 * @Device: Отладочная плата «МилКиТЭС»
 * @Date: 27.03.2020
 * @Purpose: Связывание модулей проекта
 ******************************************************************************/

// Условная компиляция
#ifndef __LINK_H
#define __LINK_H

// Подключение библиотеки микроконтроллера
#include <1986VE9x.h>

// Подключение заголовков модулей проекта
#include <clk.h>
#include <tick.h>
#include <btn.h>
#include <lcd.h>
#include "main.h"
#include "dma.h"
#include "adc.h"
#include "prph.h"

#endif
