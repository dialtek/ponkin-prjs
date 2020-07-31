/******************************************************************************
 * @File: tmr.h
 * @Author: Milandr, L.
 * @Project: Demo_Project_3-1
 * @Version: 1.0.0
 * @Compiler: ARM Compiler V5.06 (build 750)
 * @Microcontroller: К1986ВЕ92QI
 * @Device: Отладочная плата «МилКиТЭС»
 * @Date: 06.04.2020
 * @Purpose: Конфигурация аппаратных таймеров
 ******************************************************************************/

// Условная компиляция
#ifndef __TMR_H
#define __TMR_H

// Подключение заголовков
#include "link.h"

// Кроссмодульные переменные
extern volatile bool flg_cd_over;
extern volatile uint32_t tmr_rld_cnt;

// Прототипы функций
void TIMER_Reset(MDR_TIMER_TypeDef *MDR_TIMERx);
void TIMER1_Init(void);
void TIMER2_Init(void);

#endif
