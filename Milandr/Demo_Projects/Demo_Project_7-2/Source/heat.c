/******************************************************************************
 * @File: heat.c
 * @Author: Milandr, L.
 * @Project: Demo_Project_7-2
 * @Version: 1.0.0
 * @Compiler: ARM Compiler V5.06 (build 750)
 * @Microcontroller: К1986ВЕ92QI
 * @Device: Отладочная плата «МилКиТЭС»
 * @Date: 18.03.2020
 * @Purpose: Управление нагревательным элементом
 ******************************************************************************/

// Подключение заголовка
#include "heat.h"

// Инициализация нагревателя
void HEAT_Init(void)
{
  // Включение тактирования порта E
  MDR_RST_CLK->PER_CLOCK |= RST_CLK_PCLK_PORTE_Msk;

  // Конфигурация линии PE0
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
