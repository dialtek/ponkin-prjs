/******************************************************************************
 * @File: main.c
 * @Author: Milandr, L.
 * @Project: Demo_Project_7-1
 * @Version: 1.0.0
 * @Compiler: ARM Compiler V5.06 (build 750)
 * @Microcontroller: К1986ВЕ92QI
 * @Device: Отладочная плата «МилКиТЭС»
 * @Date: 18.03.2020
 * @Purpose: Основной модуль
 * @Description:
 * В данном проекте выполняется однократное аналого-цифровое преобразование
 * сигнала с потенциометра. Результ преобразования - напряжение и цифровое
 * значение - отображается на дисплей.
 ******************************************************************************/

// Подключение заголовка
#include "main.h"

// Основная функция
int main(void)
{
  // Общая инициализация
  CPU_Init();   // Система тактирования
  TICK_Init();  // Системный таймер
  LCD_Init();   // ЖК-дисплей

  // Инициализация АЦП
  ADC_Init();

  // Расчётное напряжение
  float voltage = 0.00;

  // Основной цикл
  while (true) {

    // Блок работы с АЦП
    if ((Wait(&ticks_mark[0], 100) == false)) {

      // Запуск преобразователя
      MDR_ADC->ADC1_CFG |= (1 << ADC1_CFG_REG_GO_Pos);

      // Работа с флагом завершения преобразования
      while (flg_adc_eoc == false);  // Ожидание флага
      flg_adc_eoc = false;           // Сброс флага

      // Вычисление напряжения (в вольтах)
      voltage = ADC_TO_VLT(adc_result[4]);
      uint16_t x =  ADC_TO_ANG(adc_result[4]);

      // Отображение результатов
      LCD_PrintString("    V = %.3f V", 3, voltage);    // Напряжение
      LCD_PrintString("    D = %u", 5, adc_result[4]);  // Цифровое значение
      LCD_PrintString("    A = %u", 6,x);  // Цифровое значение
    }
  }
}
