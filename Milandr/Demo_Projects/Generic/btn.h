/*******************************************************************************
 * @File: btn.h
 * @Author: Milandr, L.
 * @Project: Generic
 * @Version: 1.0.0
 * @Compiler: ARM Compiler V5.06 (build 750)
 * @Microcontroller: К1986ВЕ92QI
 * @Device: Отладочная плата «МилКиТЭС»
 * @Date: 24.03.2020
 * @Purpose: Библиотека для работы кнопок
 *******************************************************************************/

// Условная компиляция
#ifndef __BTN_H
#define __BTN_H

// Подключение библиотеки микроконтроллера
#include <1986VE9x.h>

// Количество кнопок
#define BTN_AMNT 6

// Насыщение накопителя
// (Accumulator Saturation)
#define BTN_ACC_SAT 1024

// Псевдонимы кнопок
typedef enum {
  BTN_U = 0,  // Кнопка UP
  BTN_D = 1,  // Кнопка DOWN
  BTN_L = 2,  // Кнопка LEFT
  BTN_R = 3,  // Кнопка RIGHT
  BTN_M = 4,  // Кнопка MID
  BTN_S = 5   // Кнопка SENSE
} btn_alias_t;

// Псевдонимы состояний конечного автомата
// (Finite-State Machine, FSM)
typedef enum {
  BTN_FSM_PRESS_CHECK   = 0,  // «Ожидание нажатия»
  BTN_FSM_ACC_CHARGE    = 1,  // «Заряд накопителя»
  BTN_FSM_RELEASE_CHECK = 2,  // «Ожидание отпускания»
  BTN_FSM_ACC_DRAIN     = 3   // «Разряд накопителя»
} btn_fsm_t;

// Прототипы функций
void BTN_Init(void);
bool BTN_Handler(btn_alias_t alias);

#endif
