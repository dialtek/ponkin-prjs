/******************************************************************************
 * @File: eeprom.h
 * @Author: Milandr, L.
 * @Project: Demo_Project_12-1
 * @Version: 1.0.0
 * @Compiler: ARM Compiler V5.06 (build 750)
 * @Microcontroller: К1986ВЕ92QI
 * @Device: Отладочная плата «МилКиТЭС»
 * @Date: 16.04.2020
 * @Purpose: Функции работы с микросхемой памяти 25LCXXX (Microchip)
 ******************************************************************************/

// Условная компиляция
#ifndef __EEPROM_H
#define __EEPROM_H

// Подключение заголовков
#include "link.h"

// Константы EEPROM 25LCXXX
// Размер памяти (в байтах)
#define EEPROM_DENSITY 128 * 1024

// Размер страницы (в байтах)
#define EEPROM_PAGE_SIZE 64

// Инструкции
#define EEPROM_READ  0x03  // Чтение данных
#define EEPROM_WRITE 0x02  // Запись данных
#define EEPROM_WRDI  0x04  // Запрет записи данных
#define EEPROM_WREN  0x06  // Разрешение записи данных
#define EEPROM_RDSR  0x05  // Чтение регистра состояний
#define EEPROM_WRSR  0x01  // Запись регистра состояний

// Прототипы функций
uint8_t EEPROM_ReadStatus(void);
void EEPROM_WriteEnable(void);
void EEPROM_ReadData(uint32_t address, uint32_t number, uint8_t *data);
void EEPROM_WriteData(uint32_t address, uint32_t number, uint8_t *data);
void EEPROM_ErasePage(uint16_t page);
void EEPROM_EraseAll(void);

#endif
