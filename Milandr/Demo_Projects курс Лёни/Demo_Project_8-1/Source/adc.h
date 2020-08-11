/******************************************************************************
 * @File: adc.h
 * @Author: Milandr, L.
 * @Project: Demo_Project_8-1
 * @Version: 1.0.0
 * @Compiler: ARM Compiler V5.06 (build 750)
 * @Microcontroller: К1986ВЕ92QI
 * @Device: Отладочная плата «МилКиТЭС»
 * @Date: 27.03.2020
 * @Purpose: Управление аналого-цифровым преобразователем
 ******************************************************************************/

// Условная компиляция
#ifndef __ADC_H
#define __ADC_H

// Подключение заголовков
#include "link.h"

// Константы АЦП
#define ADC_CH_NUMBER 8      // Количество реализованных каналов АЦП
#define ADC_SAMPLE_SIZE 256  // Размер выборки АЦП
#define ADC_MAX 4095         // Разрешающая способность АЦП

// Константы скважности
#define S_MAX 100            // Макс. скважность (в процентах)

// Макрос вычисления скважности
#define ADC_TO_PRC(VAL) S_MAX * (VAL) / ADC_MAX

// Кроссмодульные переменные
extern volatile uint32_t adc_result[ADC_CH_NUMBER];
extern volatile uint32_t adc_sample[ADC_SAMPLE_SIZE];
extern volatile bool flg_adc_eoc;

// Прототипы функций
void ADC_Reset(void);
void ADC_Init(void);
void ADC_MedianFilter(volatile uint32_t *buffer);

#endif
