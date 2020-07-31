/******************************************************************************
 * @File: rtc.c
 * @Author: Milandr, L.
 * @Project: Demo_Project_4-1
 * @Version: 1.0.0
 * @Compiler: ARM Compiler V5.06 (build 750)
 * @Microcontroller: К1986ВЕ92QI
 * @Device: Отладочная плата «МилКиТЭС»
 * @Date: 28.04.2020
 * @Purpose: Конфигурация часов реального времени
 ******************************************************************************/

// Условная компиляция
#ifndef __RTC_H
#define __RTC_H

// Подключение заголовков
#include "link.h"

// Макрос ожидания завершения работы с регистрами RTC
// (данная процедура должна выполняться перед каждым взаимодействием с регистрами RTC)
#define RTC_WAIT_FOR_UPDATE while ((MDR_BKP->RTC_CS & BKP_RTC_CS_WEC) != false)

// Прототипы функций
void RTC_Init(void);
void RTC_SetTime(void);
void RTC_PrintTime(void);

#endif
