#ifndef MODBUS_H
#define	MODBUS_H

#ifdef	__cplusplus
extern "C"
{
#endif

#include "Config.h"	
#include "UART.h"
	
//============================== TRANSMITTER ENABLE ============================

/* RS485 EN/DIS DEFINE */
#define TX_EN  GPIO_WriteBit(GPIOE, GPIO_Pin_13, Bit_SET)		// TX_EN active LOW
#define TX_DIS GPIO_WriteBit(GPIOE, GPIO_Pin_13, Bit_RESET)
#define RX_EN  GPIO_WriteBit(GPIOE, GPIO_Pin_14, Bit_RESET)	// RX_N active HIGH
#define RX_DIS GPIO_WriteBit(GPIOE, GPIO_Pin_14, Bit_SET)
	
//================================ STATE MACHINE ===============================

#define MODBUS_RHR_CMD       (unsigned char)0x03     // read holding registers cmd id
#define MODBUS_RIR_CMD       (unsigned char)0x04     // read input registers cmd id
#define MODBUS_WSR_CMD       (unsigned char)0x06     // write single register cmd id
	
  /* расчет контрольной суммы */
  static unsigned int modbus_CRC16(unsigned char buf[], unsigned int len); 

  /* формирование и отправка ответа на команду записи одного регистра */
  volatile void modbus_wsr_answer(void); 

  /* формирование и отправка ответа на команду чтения RW регистров */
  volatile void modbus_rhr_answer(void); 

  /* формирование и отправка ответа на команду чтения Read-only регистров */
  volatile void modbus_rir_answer(void);
  
  /* анализ контрольной суммы полученной посылки */
  static unsigned char modbus_rx_CRC_check(unsigned char modbus_cmd);
  
  //static void modbus_refresh(unsigned char cmd_type);
   
  /* был ли прочитан регистр */
  volatile unsigned char is_reg (unsigned int reg_addr);

  /* парсинг команды и работа с регистрами */
  unsigned char modbus_get_poll(void); 
 
  /* сброс modbus приемника */
  void modbus_reset(void);

  /* очистка массивов регистров */
  void modbus_init (void);
  
  volatile void holding_reg_write(unsigned int red_addr, unsigned int value);
  
  volatile void holding_reg_read(unsigned int red_addr, unsigned int *usr_var_ptr);
  
  volatile void input_reg_read(unsigned int red_addr, unsigned int *usr_var_ptr);

  volatile void input_reg_write(unsigned int red_addr, unsigned int value);
   
  /* получение адреса записываемого регистра */
  volatile unsigned int get_wr_reg_addr(void);
 
	volatile unsigned int get_wr_reg_val(void);
  
  volatile unsigned char get_modbus_id(void);

  volatile void set_modbus_id(unsigned char newID);
  
#ifdef	__cplusplus
}
#endif

#endif	/* MODBUS_H */

