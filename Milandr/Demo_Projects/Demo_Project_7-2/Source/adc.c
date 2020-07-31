/******************************************************************************
 * @File: adc.c
 * @Author: Milandr, L.
 * @Project: Demo_Project_7-2
 * @Version: 1.0.0
 * @Compiler: ARM Compiler V5.06 (build 750)
 * @Microcontroller: К1986ВЕ92QI
 * @Device: Отладочная плата «МилКиТЭС»
 * @Date: 18.03.2020
 * @Purpose: Управление аналого-цифровым преобразователем
 ******************************************************************************/

// Подключение заголовка
#include "adc.h"

// Инициализация глобальных переменных
volatile uint32_t adc_result[ADC_CH_NUMBER]   = {0};  // Результаты преобразований по каналам
volatile uint32_t adc_sample[ADC_SAMPLE_SIZE] = {0};  // Буфер хранения выборки преобразований
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

  // Конфигурация линии PD2
  MDR_PORTD->OE     &= ~0x00000002;
  MDR_PORTD->FUNC   &= ~0x00000030;
  MDR_PORTD->ANALOG &= ~0x00000002;  // Режим (аналоговый)
  MDR_PORTD->PULL   &= ~0x00020002;  // Подтяжка (отключена)
  MDR_PORTD->PD     &= ~0x00020002;
  MDR_PORTD->PWR    &= ~0x00000030;
  MDR_PORTD->GFEN   &= ~0x00000002;

  // Деинициализация АЦП
  ADC_Reset();

  // Конфигурация АЦП
  MDR_ADC->ADC1_CFG = (0 << ADC1_CFG_REG_ADON_Pos)     // Работа АЦП (пока отключён)
                    | (0 << ADC1_CFG_REG_CLKS_Pos)     // Источник тактирования АЦП (CPU)
                    | (1 << ADC1_CFG_REG_SAMPLE_Pos)   // Способ запуска АЦП (циклический)
                    | (2 << ADC1_CFG_REG_CHS_Pos)      // Целевой канал преобразователя (ADC2)
                    | (0 << ADC1_CFG_REG_CHCH_Pos)     // Режим последовательного переключения каналов (отключён)
                    | (0 << ADC1_CFG_REG_RNGC_Pos)     // Контроль границ преобразования (отключён)
                    | (0 << ADC1_CFG_M_REF_Pos)        // Источник опорного напряжения (внутренний)
                    | (3 << ADC1_CFG_REG_DIVCLK_Pos)   // Делитель тактовой частоты АЦП (2^3 = 8)
                    | (0 << ADC1_CFG_SYNC_CONVER_Pos)  // Режим запуска двух АЦП (независимый)

  // ...Конфигурация датчика температуры и внутреннего источника напряжения 1.23 В
                    | (0 << ADC1_CFG_TS_EN_Pos)        // Работа блока датчика температуры и внутреннего источника напряжения 1.23 В (отключён)
                    | (0 << ADC1_CFG_TS_BUF_EN_Pos)    // Работа усилителя для датчика температуры и внутреннего источника напряжения 1.23 В (отключён)
                    | (0 << ADC1_CFG_SEL_TS_Pos)       // Преобразование сигнала с датчика температуры (отключено)
                    | (0 << ADC1_CFG_SEL_VREF_Pos)     // Преобразование сигнала с внутреннего источника напряжения 1.23 В (отключено)
                    | (0 << ADC1_CFG_TR_Pos)           // Подстройка напряжения внутреннего источника 1.23 В

  // ...Настройка задержек при преобразовании
                    | (7 << ADC1_CFG_DELAY_GO_Pos)     // Дополнительная задержка при выборе канала (8 тактов ядра)
                    | (0 << ADC1_CFG_DELAY_ADC_Pos);   // Разность фаз между циклами преобразователей (не используется)

  // Инициализация DMA
  DMA_Init();

  // Включение АЦП
  MDR_ADC->ADC1_CFG |= (1 << ADC1_CFG_REG_ADON_Pos);
}

// Вычисление среднего арифметического выборки
void ADC_GetAverage(volatile uint32_t *buffer)
{
  // Инициализация переменных
  uint16_t ch_sample_size[ADC_CH_NUMBER] = {0};  // Размеры выборок для каналов
  uint8_t  ch_number = 0;                        // Номера каналов

  // Работа с флагом завершения цикла преобразований
  while (flg_adc_eoc == false);  // Ожидание флага
  flg_adc_eoc = false;           // Сброс флага

  // Цикл очистки массива результатов
  for (uint8_t i = 0; i < ADC_CH_NUMBER; i++) {
    adc_result[i] = 0;
  }

  // Цикл формирования выборки
  for (uint16_t i = 0; i < ADC_SAMPLE_SIZE; i++) {
    ch_number = ADC_GET_CH(buffer[i]);                    // Определение номера канала
    adc_result[ch_number] += buffer[i] & ADC_RESULT_Msk;  // Накопление преобразований
    ch_sample_size[ch_number]++;                          // Инкремент размера выборки
  }

  // Цикл усреднения преобразований выборки
  for (uint8_t i = 0; i < ADC_CH_NUMBER; i++) {
    if (ch_sample_size[i] != 0) {
      adc_result[i] /= ch_sample_size[i];
    }
  }

  // Включение АЦП
  MDR_ADC->ADC1_CFG |= (1 << ADC1_CFG_REG_ADON_Pos);
}
