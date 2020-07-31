/******************************************************************************
 * @File: led.c
 * @Author: Milandr, L.
 * @Project: Demo_Project_2-3
 * @Version: 1.0.0
 * @Compiler: ARM Compiler V5.06 (build 750)
 * @Microcontroller: К1986ВЕ92QI
 * @Device: Отладочная плата «МилКиТЭС»
 * @Date: 12.04.2020
 * @Purpose: Конфигурация портов для работы светодиодов
 ******************************************************************************/

// Подключение заголовка
#include "led.h"

// Инициализация системы для работы светодиодов
void LED_Init(void)
{
  // Включение тактирования портов A и B
  MDR_RST_CLK->PER_CLOCK |= RST_CLK_PCLK_PORTA_Msk
                          | RST_CLK_PCLK_PORTB_Msk;

  // Конфигурация линий PA0...PA7
  MDR_PORTA->OE     |=  0x000000FF;  // Направление (вывод)
  MDR_PORTA->FUNC   &= ~0x0000FFFF;  // Функция (ввод-вывод)
  MDR_PORTA->ANALOG |=  0x000000FF;  // Режим (цифровой)
  MDR_PORTA->PULL   &= ~0x00FF00FF;  // Подтяжка (отключена)
  MDR_PORTA->PD     &= ~0x00FF00FF;  // Управление (драйвер)
  MDR_PORTA->PWR    |=  0x0000FFFF;  // Крутизна (высокая)
  MDR_PORTA->GFEN   &= ~0x000000FF;  // Фильтр (не используется)

  // Конфигурация линий PB8...PB10
  MDR_PORTB->OE     |=  0x00000700;  // Направление (вывод)
  MDR_PORTB->FUNC   &= ~0x003F0000;  // Функция (ввод-вывод)
  MDR_PORTB->ANALOG |=  0x00000700;  // Режим (цифровой)
  MDR_PORTB->PULL   &= ~0x07000700;  // Подтяжка (отключена)
  MDR_PORTB->PD     &= ~0x07000700;  // Управление (драйвер)
  MDR_PORTB->PWR    |=  0x003F0000;  // Крутизна (высокая)
  MDR_PORTB->GFEN   &= ~0x00000700;  // Фильтр (не используется)

  // Исходное отключение светодиодов
  MDR_PORTA->RXTX &= ~0x000000FF;
  MDR_PORTB->RXTX = (MDR_PORTB->RXTX & ~PORT_JTAG_Msk) & ~0x00000700;
}

// Обновление состояния светодиодов
void LED_Handler(void)
{
  // Указатели на элементы управления светодиодами
  menu_t *i_ptr[8] = {&m_p1i0, &m_p1i1, &m_p1i2,
                      &m_p2i0, &m_p2i1, &m_p2i2,
                      &m_p3i0, &m_p3i1, };

  // Цикл определения актуального элемента
  for (uint8_t i = 0; i < 8; i++) {

    // Если актуальный элемент найден...
    if (m_curr == i_ptr[i]) {

      // Изменение состояния светодиода
      MDR_PORTA->RXTX ^= (1 << i);

      // Обновление данных элемента
      snprintf(m_data[i], 2, "%u", (MDR_PORTA->RXTX >> i) & 0x01);

      // Завершение цикла
      break;
    }
  }

  // Обновление страницы меню
  MENU_PrintPage(m_curr);

  // Отображение указателя
  MENU_PrintPtr(m_curr);
}

// Сброс состояния светодиодов
void LED_Reset(void)
{
  // Отключение всех светодиодов
  MDR_PORTA->RXTX &= ~0x000000FF;

  // Цикл сброса данных элементов
  for (uint8_t i = 0; i < 6; i++) {
    strcpy(m_data[i], "0");
  }
}
