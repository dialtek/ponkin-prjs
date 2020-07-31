/*                D I A L T E K    M O D B U S   R T U   v 5.1                */
#ifndef DIALTEK_MODBUS_H
#define	DIALTEK_MODBUS_H

#ifdef	__cplusplus
extern "C"
{
#endif

//============================== TRANSMITTER ENABLE ============================

/* RS485 EN/DIS DEFINE */
#define TX_EN  LATEbits.LATE8=1
#define TX_DIS LATEbits.LATE8=0
	
//================================ STATE MACHINE ===============================

#define MODBUS_RHR_CMD       (unsigned char)0x03     // read holding registers cmd id
#define MODBUS_RIR_CMD       (unsigned char)0x04     // read input registers cmd id
#define MODBUS_WSR_CMD       (unsigned char)0x06     // write single register cmd id
	
  /* ������ ����������� ����� */
  //static unsigned int modbus_CRC16(unsigned char buf[], unsigned int len);     // NO STATICs IN HEADER!!!

  /* ������������ � �������� ������ �� ������� ������ ������ �������� */
  void modbus_wsr_answer(void); 

  /* ������������ � �������� ������ �� ������� ������ RW ��������� */
  void modbus_rhr_answer(void); 

  /* ������������ � �������� ������ �� ������� ������ Read-only ��������� */
  void modbus_rir_answer(void);
  
  /* ������ ����������� ����� ���������� ������� */
  unsigned char modbus_rx_CRC_check(unsigned char modbus_cmd);
  
  //static void modbus_refresh(unsigned char cmd_type);
   
  /* ��� �� �������� ������� */
  unsigned char is_reg (unsigned int reg_addr);

  /* ������� ������� � ������ � ���������� */
  unsigned char modbus_get_poll(void); 
 
  /* ����� modbus ��������� */
  void modbus_reset(void);

  /* ������� �������� ��������� */
  void modbus_init (void);
  
  void holding_reg_write(unsigned int red_addr, unsigned int value);
  
  void holding_reg_read(unsigned int red_addr, unsigned int *usr_var_ptr);
  
  void input_reg_read(unsigned int red_addr, unsigned int *usr_var_ptr);

  void input_reg_write(unsigned int red_addr, unsigned int value);
   
  /* ��������� ������ ������������� �������� */
  unsigned int get_wr_reg_addr(void);
  
  unsigned int get_wr_reg_val(void);
  
  unsigned char get_modbus_id(void);
  
  void set_modbus_id(unsigned char newID);
   
  
#ifdef	__cplusplus
}
#endif

#endif	/* DIALTEK_MODBUS_H */

