/******************************************************************************
 * @File: adc.c
 * @Author: Milandr, L.
 * @Project: Demo_Project_8-2
 * @Version: 1.0.0
 * @Compiler: ARM Compiler V5.06 (build 750)
 * @Microcontroller: К1986ВЕ92QI
 * @Device: Отладочная плата «МилКиТЭС»
 * @Date: 02.04.2020
 * @Purpose: Управление аналого-цифровым преобразователем
 ******************************************************************************/

// Подключение заголовка
#include "adc.h"

// Инициализация глобальных переменных
volatile uint32_t adc_result[ADC_CH_NUMBER]   = {0};  // Результаты преобразований по каналам
volatile uint32_t adc_sample[ADC_SAMPLE_SIZE] = {0};  // Буфер для хранения выборки преобразований
volatile bool flg_adc_eoc = false;                    // Флаг завершения цикла преобразований

// Деинициализация АЦП
void ADC_Reset(void)
{
  // Деинициализация первого АЦП
  MDR_ADC->ADC1_CFG     = 0;
  MDR_ADC->ADC1_H_LEVEL = 0;
  MDR_ADC->ADC1_L_LEVEL = 0;
  MDR_ADC->ADC1_RESULT;
  MDR_ADC->ADC1_STATUS  = 0;
  MDR_ADC->ADC1_CHSEL   = 0;

  // Деинициализация второго АЦП
  MDR_ADC->ADC2_CFG     = 0;
  MDR_ADC->ADC2_H_LEVEL = 0;
  MDR_ADC->ADC2_L_LEVEL = 0;
  MDR_ADC->ADC2_RESULT;
  MDR_ADC->ADC2_STATUS  = 0;
  MDR_ADC->ADC2_CHSEL   = 0;
}

// Инициализация АЦП
void ADC_Init(void)
{
  // Включение тактирования порта D и АЦП
  MDR_RST_CLK->PER_CLOCK |= RST_CLK_PCLK_PORTD_Msk
                          | RST_CLK_PCLK_ADC_Msk;

  // Конфигурация линии PD4
  MDR_PORTD->OE     &= ~0x00000010;
  MDR_PORTD->FUNC   &= ~0x00000300;
  MDR_PORTD->ANALOG &= ~0x00000010;  // Режим (аналоговый)
  MDR_PORTD->PULL   &= ~0x00100010;  // Подтяжка (отключена)
  MDR_PORTD->PD     &= ~0x00100010;
  MDR_PORTD->PWR    &= ~0x00000300;
  MDR_PORTD->GFEN   &= ~0x00000010;

  // Деинициализация АЦП
  ADC_Reset();

  // Конфигурация АЦП
  MDR_ADC->ADC1_CFG = (0 << ADC1_CFG_REG_ADON_Pos)     // Работа АЦП (пока отключён)
                    | (0 << ADC1_CFG_REG_CLKS_Pos)     // Источник тактирования АЦП (CPU)
                    | (1 << ADC1_CFG_REG_SAMPLE_Pos)   // Способ запуска АЦП (циклический)
                    | (4 << ADC1_CFG_REG_CHS_Pos)      // Целевой канал преобразователя (ADC4)
                    | (0 << ADC1_CFG_REG_CHCH_Pos)     // Режим последовательного переключения каналов (отлючён)
                    | (0 << ADC1_CFG_REG_RNGC_Pos)     // Контроль границ преобразования (отключён)
                    | (0 << ADC1_CFG_M_REF_Pos)        // Источник опорного напряжения (внутренний)
                    | (3 << ADC1_CFG_REG_DIVCLK_Pos)   // Делитель тактовой частоты АЦП (2^3 = 8)
                    | (0 << ADC1_CFG_SYNC_CONVER_Pos)  // Режим запуска двух АЦП (независимый)

  // ...Конфигурация датчика температуры и внутреннего источника напряжения 1.23 В
                    | (0 << ADC1_CFG_TS_EN_Pos)        // Работа блока датчика температуры и внутреннего источника напряжения 1.23 В (отключён)
                    | (0 << ADC1_CFG_TS_BUF_EN_Pos)    // Работа усилителя для датчика температуры и внутреннего источника напряжения 1.23 В (отключён)
                    | (0 << ADC1_CFG_SEL_TS_Pos)       // Преобразование сигнала с датчика температуры (включено)
                    | (0 << ADC1_CFG_SEL_VREF_Pos)     // Преобразование сигнала с внутреннего источника напряжения 1.23 В (отключено)
                    | (0 << ADC1_CFG_TR_Pos)           // Подстройка напряжения внутреннего источника 1.23 В

  // ...Настройка задержек при преобразовании
                    | (7 << ADC1_CFG_DELAY_GO_Pos)     // Дополнительная задержка при выборе канала (8 такт ядра)
                    | (0 << ADC1_CFG_DELAY_ADC_Pos);   // Разность фаз между циклами преобразователей (не используется)

  // Инициализация DMA
  DMA_Init();

  // Включение АЦП
  MDR_ADC->ADC1_CFG |= ADC1_CFG_REG_ADON;
}

// Медианная фильтрация выборки
void ADC_MedianFilter(volatile uint32_t *buffer)
{
  // Инициализация переменных
  uint32_t ch_sample[ADC_SAMPLE_SIZE] = {0};  // Выборка канала
  uint8_t  ch_number      = 0;                // Номер канала
  uint16_t ch_sample_size = 0;                // Размер выборки канала
  uint16_t tt_sample_size = 0;                // Суммарный размер выборки

  // Работа с флагом завершения цикла преобразований
  while (flg_adc_eoc != true);  // Ожидание флага
  flg_adc_eoc = false;

  // Цикл обработки выборки
  for (uint16_t i = 0; tt_sample_size < ADC_SAMPLE_SIZE; i++) {

    // Определение актуального канала
    ch_number = ADC_GET_CH(buffer[i]);

    // Обнуление размера выборки
    ch_sample_size = 0;

    // Создание выборки канала
    for (uint16_t j = 0; j < ADC_SAMPLE_SIZE; j++) {

      // Если преобразование сделано по актуальному каналу -
      // результат добавляется к выборке канала
      if (ADC_GET_CH(buffer[i]) == ch_number) {
        ch_sample[ch_sample_size++] = buffer[j] & ADC_RESULT_Msk;
      }
    }

    // Сортировка выборки
    CombSort(ch_sample, ch_sample_size);

    // Запись медианного значения в массив результатов
    adc_result[ch_number] = ch_sample[ch_sample_size/2];

    // Добавление размера выборки канала
    // к суммарному размеру выборки
    tt_sample_size += ch_sample_size;
  }

  // Включение АЦП
  MDR_ADC->ADC1_CFG |= ADC1_CFG_REG_ADON;
}
