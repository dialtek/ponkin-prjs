#ifndef DIALTEK_MODBUS_H
#define DIALTEK_MODBUS_H

/*                D I A L T E K    M O D B U S   R T U   v 3.0                */

/* ЗАГОЛОВКИ, ПЕРЕМЕННЫЕ И СЛУЖЕБНЫЕ ФУНКЦИИ */

/* изменения необходимо вносить в файл dialtek_modbus.с */

//================================ STATE MACHINE ===============================

#define MODBUS_RHR_CMD       0x03     // read holding registers cmd id
#define MODBUS_RIR_CMD       0x04     // read input registers cmd id
#define MODBUS_WSR_CMD       0x06     // write single register cmd id

#define max_regs_cnt         125      // макс. кол-во регистров для чтения за 1 раз

//void modbus_int_mode (unsigned char mode);     // упр. прерываниями MODBUS UART     
//void modbus_refresh  (unsigned char cmd_type); // работа с пользовательскими пермеменными
//unsigned char is_reg (unsigned int reg_addr);  // был ли прочитан регистр
//void uart_send_byte (unsigned char ch);         // функция чтения 1 байта UART
//void UART_init();
//void Timer9_init(unsigned long);

/* сброс modbus приемника */
  void modbus_reset();
  
  /* очистка массивов регистров */
  void modbus_init();

  /* был ли прочитан регистр */
  unsigned char is_reg (unsigned int reg_addr);
  
  /* чтение 1 байта данных */
//  void modbus_uart_byte (unsigned char rx_byte) {
//  /// прием байта данных в буфер 
//  wr_ptr++;               // инкремент счетчика записанных байт
//  rx_buf[wr_ptr & 0x0f] = rx_byte;
//  }
   
  /* расчет контрольной суммы */
  unsigned int modbus_CRC16(unsigned char buf[], unsigned int len);
  
  /* формирование и отправка ответа на команду записи одного регистра */
  void modbus_wsr_answer();
  
  /* формирование и отправка ответа на команду чтения RW регистров */
  void modbus_rhr_answer();
 
  /* формирование и отправка ответа на команду чтения Read-only регистров */
  void modbus_rir_answer();
   
  /* анализ контрольной суммы полученной посылки */
  void modbus_rx_CRC_check(unsigned char modbus_cmd);
  
  /* анализа команд */
  void modbus_rx_sm ();
  
  /* парсинг команды и работа с регистрами */
  void modbus_poll();

#endif
