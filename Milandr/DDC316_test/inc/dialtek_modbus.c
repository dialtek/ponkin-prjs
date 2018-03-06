/*                D I A L T E K    M O D B U S   R T U   v 2.0                */

/* ИНСТРУМЕНТЫ ПОЛЬЗОВАТЕЛЯ */

/* README */
/*
Для работы библиотеки MODBUS RTU необходимо:

1. настроить прерывание UART RX по приему одного байта 

2. вставить в обработчик прерывания UART RX функцию modbus_uart_byte, например:
      modbus_uart_byte(MDR_UART1->DR); или modbus_uart_byte(U1RXREG);

3. создать функцию отправки одного байта UART TX следующего вида:
      void uart_send_hex(unsigned char hex_data){ }

4. поместить функцию modbus_rx_sm() в обработчик прерывания по таймеру (Т >= 1 мс) или цикл while(1)

5. поместить функцию modbus_init() в main()

6. поместить функцию modbus_poll() в цикл while(1) (Т >= 1 мс)

7. настроить порты для управления разрешением работы приемника (если необходимо) и передатчика в поле RS485 EN/DIS DEFINE

8. настроить аттрибуты устройства в поле HARDWARE INFO 

9. заполнить функцию modbus_int_mode() кодом с разрешением и запретом прерываний UART RX

10.составить регистровую карту устройства в фукции modbus_refresh() :
      А) при чтении регистров, выполняется код if(cmd_type == MODBUS_RHR_CMD)
      Б) при записи регистров, выполняется код if(cmd_type == MODBUS_WSR_CMD)

11. при необходимости использования своих функции внутри modbus_refresh(), следует создать их прототипы в поле ПРОТОТИПЫ  
*/

/*############################################################################*/ 
/*                    ПОЛЯ ИЗМЕНЯЕМЫЕ ПОЛЬЗОВАТЕЛЕМ !!!                       */ 

/* RS485 EN/DIS DEFINE */

#define RS485_RX_EN     MDR_PORTB->RXTX &= ~(1<<10) // вкл.  приемник RS485   \_ 
#define RS485_RX_DIS    MDR_PORTB->RXTX |=  (1<<10) // выкл. приемник RS485   _/
#define RS485_TX_EN     MDR_PORTB->RXTX |=  (1<<9)  // вкл.  передатчик RS485 _/
#define RS485_TX_DIS    MDR_PORTB->RXTX &= ~(1<<9)  // выкл. передатчик RS485 \_

/* HARDWARE INFO */

  unsigned char com_dev_id    = 247;                // MODBUS ID устройства для широковещательного режима, лучше не трогать 
  unsigned char dev_id        = 80;                 // MODBUS ID устройства                                      <<<<<<<<<<======== ID
  unsigned char firmware_ver  = 12;                 // версия прошивки текущего устройства
  unsigned char device_family = 5;                  // код семейства устройств

/* ПРОТОТИПЫ */

  void ADC_change_scale(void);                      // прототип функции смены шкалы DDC
  
/* USER FUNCS */
  
  void modbus_int_mode (unsigned char mode)  {      // управление прерыванием UART RX
  
    if(mode == 1) // разрешение прерываний RX UART MODBUS
    {
      NVIC_EnableIRQ(UART1_IRQn);
    }
    else         // запрет прерываний RX UART MODBUS
    {
      NVIC_DisableIRQ(UART1_IRQn);  
    }
  }
  
  void modbus_refresh(unsigned char cmd_type){      // работа с регистрами
    
  /// ЧТЕНИЕ, TODO - обновление переменных перед отправкой мастеру    
    
  if(cmd_type == MODBUS_RHR_CMD)
   {   
        holding_register[0] = new_meas;       // '0' - измерения не были обновлены, '1' - обновлены
        // ADCs
        for(U8 i = 1; i <= 42; i++) 
          holding_register[i] = InputConnPin[i]; // сохр. 42 каналов в ресгистры
        
        holding_register[50] = meas_mode;    // режим измерений 0 - непрерывные, 1 - импульсный по запуск   
        holding_register[51] = int_time;     // время интегирования
        holding_register[52] = ADC_scale;    // шкала измерений'0' - 3pC, '1' - 6pC, '2' - 12pC
         
        holding_register[55] = (unsigned int)dev_id;       
        holding_register[56] = (unsigned int)device_family;
        holding_register[57] = (unsigned int)firmware_ver;
         
        if(is_reg(42)) // если были прочитаны все измерения 
         new_meas = 0; // то сбрасываем флаг обновленных измерений
   }         
   //-------------------------------------------------------------------------//
  
   /// ЗАПИСЬ, TODO - получение новых значений от мастера
   //  addr_buf_1 = адрес регистра, в который идет запись (1000 = 0, 1001 = 1 и тд)
  
   if(cmd_type == MODBUS_WSR_CMD) 
   {  // анализ регистра записи 
      switch(addr_buf_1) {  
        case 50: // режим измерений
         meas_mode = holding_register[50]; // 0 - непрерывные, 1 - импульсный по запуску
        break;
        //---------
        case 51: // t интегрирования
         if(holding_register[51] > 65000)  
           holding_register[51] = 65000; // 65 ms max
         else if(holding_register[51] < 10)
           holding_register[51] = 10;    // 10 us min
         
         int_time = holding_register[51]; // сохр. t интегрирования
        break;
       //---------
        case 52: // шкала измерений
         if(holding_register[52] > 2)  
           holding_register[52] = 2;   // 12 pC max
         ADC_scale = holding_register[52]; // шкала измерений'0' - 3pC, '1' - 6pC, '2' - 12pC
         ADC_change_scale();   
        break;
        //---------
       default: break; } 
   } 
  }

/*############################################################################*/  
  
/*                         M O D B U S   E N D                                */




