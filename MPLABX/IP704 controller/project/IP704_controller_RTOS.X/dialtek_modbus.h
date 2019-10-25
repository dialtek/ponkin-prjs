#ifndef DIALTEK_MODBUS_H
#define	DIALTEK_MODBUS_H

#ifdef	__cplusplus
extern "C"
{
#endif
	
//================================ STATE MACHINE ===============================

#define MODBUS_RHR_CMD       (unsigned char)0x03     // read holding registers cmd id
#define MODBUS_RIR_CMD       (unsigned char)0x04     // read input registers cmd id
#define MODBUS_WSR_CMD       (unsigned char)0x06     // write single register cmd id

/* RS485 EN/DIS DEFINE */
#define TX_EN  TRISBbits.TRISB14 = 0;   LATBbits.LATB14 = 1
#define TX_DIS TRISBbits.TRISB14 = 0;   LATBbits.LATB14 = 0

#define default_devID (unsigned char) 3
	

  /* расчет контрольной суммы */
  static unsigned int modbus_CRC16(unsigned char buf[], unsigned int len); 

  /* формирование и отправка ответа на команду записи одного регистра */
  volatile void modbus_wsr_answer(void); 

  /* формирование и отправка ответа на команду чтения RW регистров */
  volatile void modbus_rhr_answer(void); 

  /* формирование и отправка ответа на команду чтения Read-only регистров */
  volatile void modbus_rir_answer(void);
  
  /* анализ контрольной суммы полученной посылки */
  unsigned char modbus_rx_CRC_check(unsigned char modbus_cmd);

  /* был ли прочитан регистр */
  volatile unsigned char is_reg (unsigned int reg_addr);

  /* парсинг команды и работа с регистрами */
  volatile unsigned char modbus_get_poll(void);  
 
  /* сброс modbus приемника */
  void modbus_reset();

  /* очистка массивов регистров */
  void modbus_init (void);
  
  volatile void holding_reg_write(unsigned int red_addr, unsigned int value);
  
  volatile void holding_reg_read(unsigned int red_addr, unsigned int *usr_var_ptr);
  
  volatile void input_reg_read(unsigned int red_addr, unsigned int *usr_var_ptr);

  volatile void input_reg_write(unsigned int red_addr, unsigned int value);
  
  volatile unsigned int get_wr_reg_val(void);
  
  volatile void set_modbus_id(unsigned char newID);
    
  volatile unsigned char get_modbus_id(void);
  
#ifdef	__cplusplus
}
#endif

#endif	/* DIALTEK_MODBUS_H */

