/******************************************************************************
 * @File: led.c
 * @Author: Milandr, L.
 * @Project: Demo_Project_2-1
 * @Version: 1.0.0
 * @Compiler: ARM Compiler V5.06 (build 750)
 * @Microcontroller: К1986ВЕ92QI
 * @Device: Отладочная плата «МилКиТЭС»
 * @Date: 11.03.2020
 * @Purpose: Конфигурация портов для работы светодиодов
 ******************************************************************************/

// Подключение заголовка
#include "led.h"

// Инициализация системы для работы светодиодов
void LED_Init(void)
{
  // Включение тактирования порта A
  MDR_RST_CLK->PER_CLOCK |= RST_CLK_PCLK_PORTA_Msk;

  // конфигурация линий PA0...PA7 
  MDR_PORTA->OE     |= 0x000000ff;    // навправление порта - выход
  MDR_PORTA->FUNC   &= 0xffff0000;    // функция - порт
  MDR_PORTA->ANALOG |= 0x000000ff;    // порты - цифровые, АЦП отключен
  MDR_PORTA->PULL   &= 0xff00ff00;    // внутренние подтягивающие - резисторы выключены 
  MDR_PORTA->PD     &= 0xff00ff00;    // управление - драйвер
  MDR_PORTA->PWR    =  0xffff0000;    // сброс битов регистра
  MDR_PORTA->PWR    |= 0x00005555;    // крутизна фронта импульса - низкая
  MDR_PORTA->GFEN   &= 0xffffff00;    // фильтр коротких импульсов - откл.

  // Исходное отключение светодиодов
  MDR_PORTA->RXTX &= ~0x000000FF;
}

// Реализация состояний светодиодов
void LED_SwitchState(void)
{
  // Состояние светодиодов
  static uint8_t led_num = 0;

  // Отключение всех светодиодов (PA0...PA3)
  MDR_PORTA->RXTX &= ~0x000000FF;

  // Включение целевого светодиода
  MDR_PORTA->RXTX = (1 << led_num);

  // Переход к следующему состоянию
  led_num  = (led_num  + 1) % 8;
}
