/*******************************************************************************
 * @File: can.h
 * @Author: Milandr, L.
 * @Project: Sample 12.1
 * @Microcontroller: 1986VE92U
 * @Device: Evaluation Board For MCU 1986VE92U
 * @Date: 31.08.2017
 * @Purpose: Работа с модулем CAN
 *******************************************************************************/

// Условная компиляция
#ifndef __CAN_H
#define __CAN_H

// Подключение заголовков
#include "link.h"

// Структура кадра
typedef struct
{
  uint32_t id;     // Идентификатор
  uint8_t  dlc;    // Код длины данных
  uint32_t datal;  // Байты данных 1...4
  uint32_t datah;  // Байты данных 5...8
} frame_t;

// Псевдонимы буферов CAN
#define RX_BUF 0  // Буфер приёма
#define TX_BUF 1  // Буфер передачи

// Кроссмодульные переменные
extern volatile bool flg_frm_rcvd;

// Прототипы функций
void CAN_Reset(MDR_CAN_TypeDef *MDR_CANx);
void CAN_Init(void);
void CAN_SendFrame(frame_t frame, uint8_t buf_number);
frame_t CAN_ExtractFrame(uint8_t buffer_number);
void CAN_PrintFrame(frame_t frame);

#endif
