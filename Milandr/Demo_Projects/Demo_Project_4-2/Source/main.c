﻿/******************************************************************************
 * @File: main.c
 * @Author: Milandr, L.
 * @Project: Demo_Project_4-2
 * @Version: 1.0.0
 * @Compiler: ARM Compiler V5.06 (build 750)
 * @Microcontroller: К1986ВЕ92QI
 * @Device: Отладочная плата «МилКиТЭС»
 * @Date: 29.04.2020
 * @Purpose: Основной модуль
 * @Description:
 * В данном проекте реализована работа микроконтроллера в режиме гибернации.
 * Переход в данный режим производится в основном цикле; выход из него -
 * по прерыванию от часов реального времени. Светодиоды отражают периоды гибернации
 * микроконтроллера. Также проект включается в себя использование детектора
 * напряжения питания: при снижении уровня ниже заданного порога выполняется
 * прерывание, которое записывает данные часов реального времени в регистр
 * аварийного сохранения. Обратите внимание, что для последующей прошивки
 * микроконтроллера режим гибернации должен быть отключён.
 ******************************************************************************/

// Подключение заголовка
#include "main.h"

// Основная функция
int main(void)
{
  // Общая инициализация
  CPU_Init();   // Система тактирования
  TICK_Init();  // Системный таймер
  BTN_Init();   // Кнопки
  LCD_Init();   // ЖК-дисплей

  // Конфигурация режима гибернации
  CPU_SleepCfg();

  // Инициализация детектора напряжения
  PVD_Init();

  // Инициализация RTC
  RTC_Init();

  // Инициализация светодиодов
  LED_Init();

  // Флаг гибернации
  bool flg_sleep_mode = false;

  // Отображение содержимого регистра аварийного сохранения
  LCD_PrintString("    REG_00 = %u", 4, MDR_BKP->REG_00);

  // Основной цикл
  while (true) {

    // Блок работы с режимом гибернации
    if (Wait(&ticks_mark[0], 100) == false) {

      // Обработка кнопки MID
      if (BTN_Handler(BTN_M) != false) {

        // Переключение флага гибернации
        flg_sleep_mode ^= true;
      }

      // Обработка флага гибернации
      if (flg_sleep_mode != false) {

        // Переход в режим гибернации
        CPU_PutToSleep();
      }
    }

    // Блок работы со светодиодами
    if (Wait(&ticks_mark[1], 100) == false) {

      // Переключение светодиодов
      LED_SwitchState();
    }
  }
}
