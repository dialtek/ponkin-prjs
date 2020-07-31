﻿/******************************************************************************
 * @File: prph.c
 * @Author: Milandr, L.
 * @Project: Demo_Project_7-3
 * @Version: 1.0.0
 * @Compiler: ARM Compiler V5.06 (build 750)
 * @Microcontroller: К1986ВЕ92QI
 * @Device: Отладочная плата «МилКиТЭС»
 * @Date: 27.03.2020
 * @Purpose: Конфигурация периферии (подсветка платы и дисплея, нагреватель)
 ******************************************************************************/

// Подключение заголовка
#include "prph.h"

// Инициализация требуемой периферии
void PRPH_Init(void)
{
  // Включение тактирования портов С и E
  MDR_RST_CLK->PER_CLOCK |= RST_CLK_PCLK_PORTC_Msk
                          | RST_CLK_PCLK_PORTE_Msk;

  // Конфигурация линии PC2 для работы подсветки
  MDR_PORTC->OE     |=  0x00000004;  // Направление (вывод)
  MDR_PORTC->FUNC   &= ~0x00000030;  // Функция (ввод-вывод)
  MDR_PORTC->ANALOG |=  0x00000004;  // Режим (цифровой)
  MDR_PORTC->PULL   &= ~0x00040004;  // Подтяжка (отключена)
  MDR_PORTC->PD     &= ~0x00040004;  // Управление (драйвер)
  MDR_PORTC->PWR    |=  0x00000030;  // Крутизна (высокая)
  MDR_PORTC->GFEN   &= ~0x00000004;  // Фильтр (не используется)

  // Отключение подсветки
  MDR_PORTC->RXTX &= ~PORT_RXTX2_Msk;

  // Конфигурация линии PE0 для работы нагревателя
  MDR_PORTE->OE     |=  0x00000001;  // Направление (вывод)
  MDR_PORTE->FUNC   &= ~0x00000003;  // Функция (ввод-вывод)
  MDR_PORTE->ANALOG |=  0x00000001;  // Режим (цифровой)
  MDR_PORTE->PULL   &= ~0x00010001;  // Подтяжка (отключена)
  MDR_PORTE->PD     &= ~0x00010001;  // Управление (драйвер)
  MDR_PORTE->PWR    |=  0x00000003;  // Крутизна (высокая)
  MDR_PORTE->GFEN   &= ~0x00000001;  // Фильтр (не используется)

  // Отключение нагревателя
  MDR_PORTE->RXTX &= ~PORT_RXTX0_Msk;
}

// Работа с периферией
void PRPH_Handler(void)
{
  if (Wait(&ticks_mark[1], 100) == false) {

    // Нагреватель
    if (BTN_Handler(BTN_U) != false) {       // Обработка кнопки UP
      MDR_PORTE->RXTX ^= PORT_RXTX0_Msk;     // Переключение состояния нагревателя
    }

    // Подсветка дисплея
    if (BTN_Handler(BTN_M) != false) {       // Обработка кнопки MID
      MDR_PORTE->RXTX ^= PORT_RXTX2_Msk;     // Переключение состояния подсветки дисплея
    }

    // Подсветка платы
    if (BTN_Handler(BTN_D) == true) {        // Обработка кнопки DOWN
      MDR_PORTC->RXTX ^= PORT_RXTX2_Msk;     // Переключение состояния подсветки платы
    }
  }
}
