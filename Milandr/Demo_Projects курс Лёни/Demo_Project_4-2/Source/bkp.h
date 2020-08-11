/******************************************************************************
 * @File: bkp.h
 * @Author: Milandr, L.
 * @Project: Demo_Project_4-2
 * @Version: 1.0.0
 * @Compiler: ARM Compiler V5.06 (build 750)
 * @Microcontroller: К1986ВЕ92QI
 * @Device: Отладочная плата «МилКиТЭС»
 * @Date: 29.04.2020
 * @Purpose: Конфигурация батарейного домена
 ******************************************************************************/

// Условная компиляция
#ifndef __BKP_H
#define __BKP_H

// Подключение заголовков
#include "link.h"

// Макрос ожидания завершения работы с регистрами RTC
// (данная процедура должна выполняться перед каждым взаимодействием с регистрами RTC)
#define RTC_WAIT_FOR_UPDATE while ((MDR_BKP->RTC_CS & BKP_RTC_CS_WEC) != false)

// Прототипы функций
void IRQ_Mask(uint8_t priority);
void CPU_SleepCfg(void);
void CPU_PutToSleep(void);
void RTC_Init(void);
void PVD_Init(void);


#endif
