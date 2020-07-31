/******************************************************************************
 * @File: main.c
 * @Author: Milandr, L.
 * @Project: Demo_Project_2-2
 * @Version: 1.0.0
 * @Compiler: ARM Compiler V5.06 (build 750)
 * @Microcontroller: К1986ВЕ92QI
 * @Device: Отладочная плата «МилКиТЭС»
 * @Date: 25.03.2020
 * @Purpose: Основной модуль
 * @Description:
 * В данном проекте реализовано меню управления RGB-светодиодом. Меню состоит
 * из трёх пунктов; переключение между пунктами осуществляется кнопками UP/DOWN;
 * кнопка MID изменяет состояние - включение/отключение - выбранной линии.
 ******************************************************************************/

// Подключение заголовка
#include "main.h"

// Основная функция
int main(void)
{
  // Общая инициализация
  BTN_Init();  // Кнопки
  LCD_Init();  // ЖК-дисплей

  // Инициализация RGB-светодиода
  LED_Init();

  // Инициализация переменных
  item_alias_t menu_state = MENU_RED;  // Состояние меню

  // Инициализация меню
  LED_MenuInit(menu_state);

  uint8_t colour_state = 0;
  char *CurrColour;

  // Основной цикл
  while (true) {

    //for(int i = 0; i < 99999; i++);

    // Обработка кнопки UP
    if (BTN_Handler(BTN_U) == true) {
      menu_state++;                    // Переход к следующему состоянию
      if (menu_state > MENU_RED) {     // Проверка выхода за границу (верх)
        menu_state = MENU_RED;
      }
      LED_MenuUpdate(menu_state);      // Обновление меню
    }

    // Обработка кнопки DOWN
    if (BTN_Handler(BTN_D) == true) {
      menu_state--;                    // Переход к следующему состоянию
      if (menu_state < MENU_BLUE) {    // Проверка выхода за границу (низ)
        menu_state = MENU_BLUE;
        
      }
      LED_MenuUpdate(menu_state);      // Обновление меню
    }

    // Обработка кнопки MID
    if (BTN_Handler(BTN_M) == true) {
      LED_SwitchState(menu_state);     // Переключение выбранного светодиода

    if(menu_state == MENU_BLUE)
      CurrColour = "Blue";

    if(menu_state == MENU_RED)
      CurrColour = "Red";

    if(menu_state == MENU_GREEN)
      CurrColour = "Green";

      LCD_PrintString(CurrColour,7);
      //LCD_PrintString("menu_state %u", menu_state,6);

    }



  }
}
