/******************************************************************************
 * @File: led.h
 * @Author: Milandr, L.
 * @Project: Demo_Project_2-2
 * @Version: 1.0.0
 * @Compiler: ARM Compiler V5.06 (build 750)
 * @Microcontroller: К1986ВЕ92QI
 * @Device: Отладочная плата «МилКиТЭС»
 * @Date: 25.03.2020
 * @Purpose: Функции для работы RGB-светодиода
 ******************************************************************************/

// Условная компиляция
#ifndef __LED_H
#define __LED_H

// Подключение заголовков модулей проекта
#include "link.h"

// Псевдонимы состояний меню
typedef enum {
  MENU_RED   = 3,  // Красный светодиод
  MENU_GREEN = 2,  // Зелёный светодиод
  MENU_BLUE  = 1   // Синий светодиод
} item_alias_t;

// Прототипы функций
void LED_Init(void);
void LED_SwitchState(item_alias_t  menu_state);
void LED_MenuInit(item_alias_t menu_state);
void LED_MenuUpdate(item_alias_t menu_state);

#endif
