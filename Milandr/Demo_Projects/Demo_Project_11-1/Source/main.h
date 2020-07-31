/******************************************************************************
 * @File: main.h
 * @Author: Milandr, L.
 * @Project: Demo_Project_11-1
 * @Version: 1.0.0
 * @Compiler: ARM Compiler V5.06 (build 750)
 * @Microcontroller: К1986ВЕ92QI
 * @Device: Отладочная плата «МилКиТЭС»
 * @Date: 29.06.2020
 * @Purpose: Основной модуль
 ******************************************************************************/

// Условная компиляция
#ifndef __MAIN_H
#define __MAIN_H

// Подключение заголовков
#include "link.h"

// Размер буфера приёмника
#define RX_BUF_SIZE 21

// Прототипы функций
void UART_TransmitEx(void);
void UART_ReceiveEx(void);

#endif
