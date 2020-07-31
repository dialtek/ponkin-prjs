/******************************************************************************
 * @File: sort.c
 * @Author: Milandr, L.
 * @Project: Generic
 * @Version: 1.0.0
 * @Compiler: ARM Compiler V5.06 (build 750)
 * @Microcontroller: К1986ВЕ92QI
 * @Device: Отладочная плата «МилКиТЭС»
 * @Date: 31.03.2020
 * @Purpose: Функции сортировки
 ******************************************************************************/

// Подключение заголовка
#include "sort.h"

// Сортировка пузырьком
void BubbleSort(uint32_t *sample, uint32_t size)
{
  // Цикл сортировки
  for (uint32_t i = 0; i < size - 1; i++) {

    // Сброс флага перестановки
    bool flg_swap = false;

    // Иттерация прохождения выборки
    for (uint32_t j = 0; j < size - 1 - i; j++) {

      // Сравнение элементов выборки
      if (sample[j] > sample[j + 1]) {

        // Перестановка
        uint32_t t = sample[j];
        sample[j] = sample[j + 1];
        sample[j + 1] = t;

        // Установка флага перестановки
        flg_swap = true;
      }
    }

    // Если перестановок не зафиксировано -
    // сортировка завершается
    if (flg_swap == false) {
      break;
    }
  }
}

// Сортировка вставками
void InsertSort(uint32_t *sample, uint32_t size)
{
  // Цикл сортировки
  for (uint32_t i = 1; i < size; i++) {

    // Запись ключевого элемента
    uint32_t  k = sample[i];
    uint32_t j = i;

    // Сравнение ключевого элемента
    // с предшествующими элементами выборки
    for (; (j > 0) && (sample[j - 1] > k); j--) {

      // Перестановка
      sample[j] = sample[j - 1];
    }

    // Фиксация позиции ключевого элемента
    sample[j] = k;
  }
}

// Сортировка расчёской
void CombSort(uint32_t *sample, uint32_t size)
{
  // Инициализация переменных
  float    factor = 1.247331;     // Фактор уменьшения
  uint32_t step = size / factor;  // Шаг расчёски

  // Фаза 1: расчёска
  while (step >= 1) {

    // Иттерация прохождения выборки
    for (uint32_t i = 0; i + step < size; i++) {

      // Сравнение элементов выборки
      if (sample[i] > sample[i + step]) {

        // Перестановка
        uint32_t t = sample[i];
        sample[i] = sample[i + step];
        sample[i + step] = t;
      }
    }

    // Уменьшение шага расчёски
    step /= factor;
  }

  // Фаза 2: пузырёк
  for (uint32_t i = 0; i < size - 1; i++) {

    // Сброс флага перестановки
    bool flg_swap = false;

    // Иттерация прохождения выборки
    for (uint32_t j = 0; j < size - 1 - i; j++) {

      // Сравнение элементов выборки
      if (sample[j] > sample[j + 1]) {

        // Перестановка
        uint32_t t = sample[j];
        sample[j] = sample[j + 1];
        sample[j + 1] = t;

        // Установка флага перестановки
        flg_swap = true;
      }
    }

    // Если перестановок не зафиксировано -
    // сортировка завершается
    if (flg_swap == false) {
      break;
    }
  }
}

// Проверка сортировки
bool Validate(uint32_t *sample, uint32_t size)
{
  // Цикл проверки сортировки
  for (uint32_t i = 0; i < size - 1; i++) {

    // Если найден неотсортированный элемент,
    // то сортировна невалидна -
    // негативный выход
    if (sample[i] > sample[i + 1]) {
      return false;
    }
  }

  // Если весь цикл пройден,
  // то сортировка валидна -
  // позитивный выход
  return true;
}

// Генератор псевдослучайной выборки
void Randomize(uint32_t *sample, uint32_t size, uint32_t lim)
{
  // Цикл заполнения выборки псевдослучайными числами
  for (uint32_t i = 0; i < size; i++) {
    sample[i] = rand()%(lim + 1);
  }
}
