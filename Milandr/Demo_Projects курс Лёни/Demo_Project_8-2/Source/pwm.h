/******************************************************************************
 * @File: pwm.h
 * @Author: Milandr, L.
 * @Project: Demo_Project_8-2
 * @Version: 1.0.0
 * @Compiler: ARM Compiler V5.06 (build 750)
 * @Microcontroller: К1986ВЕ92QI
 * @Device: Отладочная плата «МилКиТЭС»
 * @Date: 02.04.2020
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

// Скважность импульсов (в процентах)
#define PWM_S 50

// Шаг двигателя (в градусах)
#define HSM_STEP 0.9F

// Прототипы функций
void TIMER_Reset(MDR_TIMER_TypeDef *MDR_TIMERx);
void PWM_Init(void);
void PWM_SetFrequency(uint32_t frequency);
void HSM_Init(void);

#endif
