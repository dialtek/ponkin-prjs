/******************************************************************************
 * @File: adc.h
 * @Author: Milandr, L.
 * @Project: Demo_Project_8-2
 * @Version: 1.0.0
 * @Compiler: ARM Compiler V5.06 (build 750)
 * @Microcontroller: К1986ВЕ92QI
 * @Device: Отладочная плата «МилКиТЭС»
 * @Date: 02.04.2020
 * @Purpose: Управление аналого-цифровым преобразователем
 ******************************************************************************/

// Условная компиляция
#ifndef __ADC_H
#define __ADC_H

// Подключение заголовков
#include "link.h"

// Количество реализованных каналов АЦП
#define ADC_CH_NUMBER 8

// Размер выборки АЦП
#define ADC_SAMPLE_SIZE 256

// Калибровочные константы частоты импульсов
#define F_MAX 3500  // Макс. частота импульсов (в герцах)
#define D_MAX 4095  // Разрешающая способность АЦП

// Макрос вычисления скважности
#define ADC_TO_FRQ(VAL) F_MAX * (VAL) / D_MAX

// Создание кроссмодульной видимости переменных
extern volatile uint32_t adc_result[ADC_CH_NUMBER];
extern volatile uint32_t adc_sample[ADC_SAMPLE_SIZE];
extern volatile bool flg_adc_eoc;

// Прототипы функций
void ADC_Reset(void);
void ADC_Init(void);
void ADC_MedianFilter(volatile uint32_t *buffer);

#endif
