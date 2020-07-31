/******************************************************************************
 * @File: pwm.h
 * @Author: Milandr, L.
 * @Project: Demo_Project_8-1
 * @Version: 1.0.0
 * @Compiler: ARM Compiler V5.06 (build 750)
 * @Microcontroller: К1986ВЕ92QI
 * @Device: Отладочная плата «МилКиТЭС»
 * @Date: 26.03.2020
 * @Purpose: Конфигурация аппаратных таймеров в режиме ШИМ
 ******************************************************************************/

// Условная компиляция
#ifndef __PWM_H
#define __PWM_H

// Подключение заголовков
#include "link.h"

// Константы таймера
#define TIMER_PSG_MAX 65535  // Разрешение делителя
#define TIMER_ARR_MAX 65535  // Разрешение счётчика
#define TIMER_ARR_MIN 100    // Мин. значение счётчика

// Частота ШИМ (в герцах)
#define PWM_F 10000

// Прототипы функций
void TIMER_Reset(MDR_TIMER_TypeDef *MDR_TIMERx);
void PWM_Init(void);
void PWM_SetFrequency(uint32_t frequency);
void PWM_SetPowerCycle(uint8_t power_cycle);

#endif
