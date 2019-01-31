#ifndef DIALTEK_MODBUS_H
#define DIALTEK_MODBUS_H

/*                D I A L T E K    M O D B U S   R T U   v 3.0                */

/* ���������, ���������� � ��������� ������� */

/* ��������� ���������� ������� � ���� dialtek_modbus.� */

//================================ STATE MACHINE ===============================

#define MODBUS_RHR_CMD       0x03     // read holding registers cmd id
#define MODBUS_RIR_CMD       0x04     // read input registers cmd id
#define MODBUS_WSR_CMD       0x06     // write single register cmd id

#define max_regs_cnt         125      // ����. ���-�� ��������� ��� ������ �� 1 ���

//void modbus_int_mode (unsigned char mode);     // ���. ������������ MODBUS UART     
//void modbus_refresh  (unsigned char cmd_type); // ������ � ����������������� ������������
//unsigned char is_reg (unsigned int reg_addr);  // ��� �� �������� �������
//void uart_send_byte (unsigned char ch);         // ������� ������ 1 ����� UART
//void UART_init();
//void Timer9_init(unsigned long);

/* ����� modbus ��������� */
  void modbus_reset();
  
  /* ������� �������� ��������� */
  void modbus_init();

  /* ��� �� �������� ������� */
  unsigned char is_reg (unsigned int reg_addr);
  
  /* ������ 1 ����� ������ */
//  void modbus_uart_byte (unsigned char rx_byte) {
//  /// ����� ����� ������ � ����� 
//  wr_ptr++;               // ��������� �������� ���������� ����
//  rx_buf[wr_ptr & 0x0f] = rx_byte;
//  }
   
  /* ������ ����������� ����� */
  unsigned int modbus_CRC16(unsigned char buf[], unsigned int len);
  
  /* ������������ � �������� ������ �� ������� ������ ������ �������� */
  void modbus_wsr_answer();
  
  /* ������������ � �������� ������ �� ������� ������ RW ��������� */
  void modbus_rhr_answer();
 
  /* ������������ � �������� ������ �� ������� ������ Read-only ��������� */
  void modbus_rir_answer();
   
  /* ������ ����������� ����� ���������� ������� */
  void modbus_rx_CRC_check(unsigned char modbus_cmd);
  
  /* ������� ������ */
  void modbus_rx_sm ();
  
  /* ������� ������� � ������ � ���������� */
  void modbus_poll();

#endif
