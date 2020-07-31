/******************************************************************************
 * @File: btn.c
 * @Author: Milandr, L.
 * @Project: Generic
 * @Version: 1.0.0
 * @Compiler: ARM Compiler V5.06 (build 750)
 * @Microcontroller: К1986ВЕ92QI
 * @Device: Отладочная плата «МилКиТЭС»
 * @Date: 24.03.2020
 * @Purpose: Библиотека для работы кнопок
 ******************************************************************************/

// Подключение заголовка
#include "btn.h"

// Инициализация портов для работы кнопок
void BTN_Init(void)
{
  // Включение тактирования портов B и Е
  MDR_RST_CLK->PER_CLOCK |= RST_CLK_PCLK_PORTB_Msk
                          | RST_CLK_PCLK_PORTE_Msk;

  // Конфигурация линий PB4, PB5 и PB10 (кнопки DOWN, SENSE и LEFT)
  MDR_PORTB->OE     &= ~0x00000430;  // Направление (ввод)
  MDR_PORTB->FUNC   &= ~0x00300F00;  // Функция (ввод-вывод)
  MDR_PORTB->ANALOG |=  0x00000430;  // Режим работы (цифровой)
  MDR_PORTB->PULL   &= ~0x04300430;  // Подтяжка (отключена)
  MDR_PORTB->PD     &= ~0x04300430;  // Триггер Шмитта (отключен)
  MDR_PORTB->PWR    &= ~0x00300F00;  // Крутизна фронтов (не используется)
  MDR_PORTB->GFEN   &= ~0x00000430;  // Цифровой фильтр (отключен)

  // Конфигурация линий PE3, PE6 и PE7 (кнопки RIGHT, UP и MID)
  MDR_PORTE->OE     &= ~0x000000C8;  // Направление (ввод)
  MDR_PORTE->FUNC   &= ~0x0000F0C0;  // Функция (ввод-вывод)
  MDR_PORTE->ANALOG |=  0x000000C8;  // Режим работы (цифровой)
  MDR_PORTE->PULL   &= ~0x00C800C8;  // Подтяжка (отключена)
  MDR_PORTE->PD     &= ~0x00C800C8;  // Триггер Шмитта (отключен)
  MDR_PORTE->PWR    &= ~0x0000F0C0;  // Крутизна фронтов (не используется)
  MDR_PORTE->GFEN   &= ~0x000000C8;  // Цифровой фильтр (отключен)
}

// Обработчик кнопок
bool BTN_Handler(btn_alias_t button)
{
  // Инициализация переменных
  static btn_fsm_t fsm_state[BTN_AMNT] = {BTN_FSM_PRESS_CHECK};  // Состояния конечного автомата
         bool      pin_state   = false;                          // Состояния линий
         uint32_t  accumulator = 0;                              // Значение накопителя (защита от дребезга)

  // Определение состояния линии
       if (button == BTN_U) {pin_state =  PORT_GET_STATE(E, 6);}   // Кнопка UP
  else if (button == BTN_D) {pin_state =  PORT_GET_STATE(B, 4);}   // Кнопка DOWN
  else if (button == BTN_L) {pin_state =  PORT_GET_STATE(B, 10);}  // Кнопка LEFT
  else if (button == BTN_R) {pin_state =  PORT_GET_STATE(E, 3);}   // Кнопка RIGHT
  else if (button == BTN_M) {pin_state =  PORT_GET_STATE(E, 7);}   // Кнопка MID
  else if (button == BTN_S) {pin_state = !PORT_GET_STATE(B, 5);}   // Кнопка SENSE

  /* --- Конечный автомат --- */
  // Состояние «Ожидание нажатия»
  if (fsm_state[button] == BTN_FSM_PRESS_CHECK) {

    // Проверка состояния кнопки
    if (pin_state == false) {                    // Если кнопка нажата...
      fsm_state[button] = BTN_FSM_ACC_CHARGE;    // Переход к следующему состоянию
    } else {                                     // Если кнопка не нажата...
      return false;                              // Негативный выход
    }
  }

  // Состояние «Заряд накопителя» (защита от дребезга)
  if (fsm_state[button] == BTN_FSM_ACC_CHARGE) {

    // Установка нулевого значения накопителя
    accumulator = 0;

    // Цикл заряда
    for (uint32_t i = 0; i < BTN_ACC_SAT; i++) {
      accumulator += !pin_state;
    }

    // Проверка состояния накопителя
    if (accumulator == BTN_ACC_SAT) {             // Если накопитель достиг насыщения...
      fsm_state[button] = BTN_FSM_RELEASE_CHECK;  // Переход к следующему состоянию
      return true;                                // Позитивный выход
    } else {                                      // Если накопитель не достиг насыщения...
      fsm_state[button] = BTN_FSM_PRESS_CHECK;    // Переход к исходному состоянию
      return false;                               // Негативный выход
    }
  }

  // Состояние «Ожидание отпускания»
  if (fsm_state[button] == BTN_FSM_RELEASE_CHECK) {

    // Проверка состояния кнопки
    if (pin_state != false) {                     // Если кнопка отпущена...
      fsm_state[button] = BTN_FSM_ACC_DRAIN;      // Переход к следующему состоянию
    } else {                                      // Если кнопка не отпущена...
      return false;                               // Негативный выход
    }
  }

  // Состояние «Разряд накопителя» (защита от дребезга)
  if (fsm_state[button] == BTN_FSM_ACC_DRAIN) {

    // Установка значения насыщения накопителя
    accumulator = BTN_ACC_SAT;

    // Цикл разряда
    for (uint32_t i = 0; i < BTN_ACC_SAT; i++) {
      accumulator -= pin_state;
    }

    // Проверка состояния накопителя
    if (accumulator == 0) {                       // Если накопитель достиг нуля...
      fsm_state[button] = BTN_FSM_PRESS_CHECK;    // Переход к исходному состоянию
    } else {                                      // Если накопитель не достиг нуля...
      fsm_state[button] = BTN_FSM_RELEASE_CHECK;  // Переход к предыдущему состоянию
    }
    return false;                                // Негативный выход
  }

  // Во всех неопределенных случаях
  // производится негативный выход
  return false;
}
