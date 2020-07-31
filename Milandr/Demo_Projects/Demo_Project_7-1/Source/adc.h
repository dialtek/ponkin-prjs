/******************************************************************************
 * @File: adc.h
 * @Author: Milandr, L.
 * @Project: Demo_Project_7-1
 * @Version: 1.0.0
 * @Compiler: ARM Compiler V5.06 (build 750)
 * @Microcontroller: К1986ВЕ92QI
 * @Device: Отладочная плата «МилКиТЭС»
 * @Date: 18.03.2020
 * @Purpose: Управление аналого-цифровым преобразователем
 ******************************************************************************/

// Условная компиляция
#ifndef __ADC_H
#define __ADC_H

// Подключение заголовков
#include "link.h"

// Константы АЦП
#define ADC_CH_NUMBER 8  // Количество каналов АЦП
#define ADC_REF 3.30F    // Опорное напряжение (в вольтах)
#define ADC_MAX 4095     // Разрешение АЦП
#define ANG_MAX 300     

// Макрос вычисления напряжения
#define ADC_TO_VLT(VAL) ADC_REF * (VAL) / ADC_MAX
#define ADC_TO_ANG(VAL) (uint16_t)( ANG_MAX * (VAL) / ADC_MAX)

// Кроссмодульные переменные
extern volatile uint32_t adc_result[ADC_CH_NUMBER];
extern volatile bool flg_adc_eoc;

// Прототипы функций
void ADC_Reset(void);
void ADC_Init(void);

#endif
