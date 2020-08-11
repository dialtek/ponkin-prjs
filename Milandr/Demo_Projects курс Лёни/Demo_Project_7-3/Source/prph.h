/******************************************************************************
 * @File: prph.h
 * @Author: Milandr, L.
 * @Project: Demo_Project_7-3
 * @Version: 1.0.0
 * @Compiler: ARM Compiler V5.06 (build 750)
 * @Microcontroller: К1986ВЕ92QI
 * @Device: Отладочная плата «МилКиТЭС»
 * @Date: 27.03.2020
 * @Purpose: Конфигурация периферии (подсветка платы и дисплея, нагреватель)
 ******************************************************************************/

// Условная компиляция
#ifndef __PRPH_H
#define __PRPH_H

// Подключение заголовков модулей проекта
#include "link.h"

// Прототипы функций
void PRPH_Init(void);
void PRPH_Handler(void);

#endif
