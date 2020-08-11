/******************************************************************************
 * @File: led.c
 * @Author: Milandr, L.
 * @Project: Demo_Project_2-2
 * @Version: 1.0.0
 * @Compiler: ARM Compiler V5.06 (build 750)
 * @Microcontroller: К1986ВЕ92QI
 * @Device: Отладочная плата «МилКиТЭС»
 * @Date: 25.03.2020
 * @Purpose: Функции для работы RGB-светодиода
 ******************************************************************************/

// Подключение заголовка
#include "led.h"

// Инициализация порта для работы RGB-светодиода
void LED_Init(void)
{
  // Включение тактирования порта B
  MDR_RST_CLK->PER_CLOCK |= RST_CLK_PCLK_PORTB_Msk;

  // Конфигурация линий PB8...PB10
  MDR_PORTB->OE     |=  0x00000700;  // Направление (вывод)
  MDR_PORTB->FUNC   &= ~0x003F0000;  // Функция (ввод-вывод)
  MDR_PORTB->ANALOG |=  0x00000700;  // Режим (цифровой)
  MDR_PORTB->PULL   &= ~0x07000700;  // Подтяжка (отключена)
  MDR_PORTB->PD     &= ~0x07000700;  // Управление (драйвер)
  MDR_PORTB->PWR    |=  0x003F0000;  // Крутизна (высокая)
  MDR_PORTB->GFEN   &= ~0x00000700;  // Фильтр (не используется)

  // Исходное отключение светодиодов
  MDR_PORTB->RXTX = (MDR_PORTB->RXTX & ~PORT_JTAG_Msk) & ~0x00000700;
}

// Изменение состояния RGB-светодиода
void LED_SwitchState(item_alias_t menu_state)
{
  if (menu_state == MENU_RED) {           // Переключение красного светодиода
    MDR_PORTB->RXTX = (MDR_PORTB->RXTX & ~PORT_JTAG_Msk) ^ PORT_RXTX9_Msk;
  } else if (menu_state == MENU_GREEN) {  // Переключение зелёного светодиода
    MDR_PORTB->RXTX = (MDR_PORTB->RXTX & ~PORT_JTAG_Msk) ^ PORT_RXTX8_Msk;
  } else if (menu_state == MENU_BLUE) {   // Переключение синего светодиода
    MDR_PORTB->RXTX = (MDR_PORTB->RXTX & ~PORT_JTAG_Msk) ^ PORT_RXTX10_Msk;
  }
}

// Инициализация меню
void LED_MenuInit(item_alias_t menu_state)
{
  // Отображение строк
  LCD_PrintString("   RED",   3);
  LCD_PrintString("   GREEN", 4);
  LCD_PrintString("   BLUE",  5);

  // Отображение указателя
  LED_MenuUpdate(menu_state);
}

// Обновление меню
void LED_MenuUpdate(item_alias_t menu_state)
{
  // Стирание столбца указателей
  for (uint8_t i = 0; i < 3; i++) {
    LCD_PrintSymbol(' ', 1, (3 + i));
  }

  // Отображение указателя требуемую строку
  LCD_PrintSymbol('#', 1, (6 - menu_state));
}
