/******************************************************************************
 * @File: main.c
 * @Author: Milandr, L.
 * @Project: Demo_Project_11-2
 * @Version: 1.0.0
 * @Compiler: ARM Compiler V5.06 (build 750)
 * @Microcontroller: К1986ВЕ92QI
 * @Device: Отладочная плата «МилКиТЭС»
 * @Date: 30.06.2020
 * @Purpose: Основной модуль
 * @Description:
 * В данном проекте реализованы передача и приём данных по интерфейсу UART
 * с использованием DMA. Передаваемые данные представляют собой некоторую строку;
 * запуск передачи осуществляется по нажатию кнопки. Принимаемые данные 
 * записываются в массив. Содержание массива периодически отображается на дисплей.
 ******************************************************************************/

// Подключение заголовка
#include "main.h"

// Массив передаваемых данных
char tx_data[] = "Here is a very long string. \n\
But we can make it even longer - for sure! \n\
You don't want to transmit it manually, don't you? \n\
You want to use some sort of trick instead... \n\
And that's exactly what we're going to do! \n";

// Массив принимаемых данных
char rx_data[RX_SIZE] = {0};

// Разрмер массива передаваемых данных
// (длина строки)
uint32_t tx_size = 0;

// Основная функция
int main(void)
{
  // Общая инициализация
  CPU_Init();   // Система тактирования
  TICK_Init();  // Системный таймер
  BTN_Init();   // Кнопки
  LCD_Init();   // ЖК-дисплей

  // Инициализация UART
  UART_Init();

  // Инициализация DMA
  DMA_Init();

  // Основной цикл
  while (true) {

    // Блок работы с передачей данных
    if (Wait(&ticks_mark[0], 100) == false) {

      // Обработка кнопки MID
      if (BTN_Handler(BTN_M) != false) {

        // Включение запросов от UART к DMA на передачу данных
        MDR_UART2->DMACR |= UART_DMACR_TXDMAE;
      }
    }

    // Блок работы с приёмом данных
    if (Wait(&ticks_mark[1], 250) == false) {

      // Отображение массива принятых данных
      LCD_PrintString(rx_data, 4);
    }
  }
}
