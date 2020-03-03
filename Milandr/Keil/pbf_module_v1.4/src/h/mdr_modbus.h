#ifndef MDR_MODBUS_H
#define	MDR_MODBUS_H

#ifdef	__cplusplus
extern "C"
{
#endif
	
//================================ STATE MACHINE ===============================

#define MODBUS_RHR_CMD       (uint8_t)0x03     // read holding registers cmd id
#define MODBUS_RIR_CMD       (uint8_t)0x04     // read input registers cmd id
#define MODBUS_WSR_CMD       (uint8_t)0x06     // write single register cmd id

//============================== RS485 defines =================================

#define default_devID (uint8_t) 3
	

  /* расчет контрольной суммы */
  static uint16_t modbus_CRC16(uint8_t buf[], uint16_t len); 

  /* формирование и отправка ответа на команду записи одного регистра */
  volatile void modbus_wsr_answer(void); 

  /* формирование и отправка ответа на команду чтения RW регистров */
  volatile void modbus_rhr_answer(void); 

  /* формирование и отправка ответа на команду чтения Read-only регистров */
  volatile void modbus_rir_answer(void);
  
  /* анализ контрольной суммы полученной посылки */
  uint8_t modbus_rx_CRC_check(uint8_t modbus_cmd);

  /* был ли прочитан регистр */
  volatile uint8_t is_reg (uint16_t reg_addr);

  /* парсинг команды и работа с регистрами */
  volatile uint8_t modbus_get_poll(void);  
 
  /* сброс modbus приемника */
  void modbus_reset();

  /* очистка массивов регистров */
  void modbus_init (void);
  
  volatile void holding_reg_write(uint16_t red_addr, uint16_t value);
  
  volatile void holding_reg_read(uint16_t red_addr, uint16_t *usr_var_ptr);
  
  volatile void input_reg_read(uint16_t red_addr, uint16_t *usr_var_ptr);

  volatile void input_reg_write(uint16_t red_addr, uint16_t value);
  
  volatile uint16_t get_wr_reg_val(void);
  
  volatile void set_modbus_id(uint8_t newID);
    
  volatile uint8_t get_modbus_id(void);
  
#ifdef	__cplusplus
}
#endif

#endif	/* MDR_MODBUS_H */

