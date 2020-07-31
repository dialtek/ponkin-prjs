/* 
 * File:   d_one_wire.h
 * Author: D_LHEP_DESKTOP
 *
 * Created on 5 ������ 2019 �., 13:49
 */

#ifndef D_ONE_WIRE_H
#define	D_ONE_WIRE_H

#ifdef	__cplusplus
extern "C"
{
#endif
///=====	
// 1-wire
#define One_wire_TX_pin   LATGbits.LATG1  // RG1	  
#define One_wire_RX_pin   PORTGbits.RG0   // RG0		

/*--------------------------------------------------------------------------- */
#define CRC8INIT   0x00  
#define CRC8POLY   0x18  
#define Skip_ROM   0xCC         // ������� ��������� �� ���� �������� �� ����
#define Convert_T  0x44         // ������� ������ ��������� �����������
#define Match_ROM  0x55         // ������� ��������� � ���������� �������
#define Read_scr   0xBE         // ������� ������ ��������� ����������� �������      
#define Read_ROM   0x33         // ������� ������ ID ������ ������������� � ���� ����������
/*--------------------------------------------------------------------------- */
#define ID_lenght	8                   // OW ID lenght in bytes
#define MAX_sens_qty 10U                    // MAX sensors qty

#define SEND_MEAS_CMD (unsigned char)100
#define IDLE          (unsigned char)101
#define READ_SENSORS  (unsigned char)102
	
/*=========================================================================== */
// 1-wire 

	void OneWire_tx_state(unsigned char state);
		// ������������ ���. ������� �� ����� 1-wire
 
	unsigned int OneWire_rx_state();
		// ������ �������� ������ �� ���� 1-wire
	
	unsigned char OneWire_reset();
		// ����� ������� ������ (reset), ������� �������� ������� �����������.
		// ���� ������� ����������� �������, ���������� ��� ���������� � ���������� 1, ����� ���������� 0 
	
	void OneWire_send_bit(unsigned char bit);
		// ���������� ���� ���
		// bit ������������ ��������, 0 - ����, ����� ������ �������� - �������
	
	unsigned char OneWire_read_bit();
		// ������ �������� ����, ������������ ������������.
		// ���������� 0 - ���� ������� 0, �������� �� ���� �������� - ���� �������� �������
	
	unsigned char OneWire_read();
		// ������ ���� ����, ���������� �����������, 
		// ������� ��� �����, ���������� ����������� ��������
	
	void OneWire_send(unsigned char b);
		// ���������� ���� ����, ������ ������ ���, ������� ��� �����
		// b - ������������ ��������
	
	unsigned char crc8 (unsigned char data, unsigned char crc);
		// ������ ����������� �����

	unsigned char OneWire_skip();
		// ��������� ������������������ ������������� (reset + ������� ������� �����������)
		// ���� ������� ����������� �������, ��������� ������� SKIP ROM
		// ���������� 1, ���� ������� ����������� �������, 0 - ���� ���
	
	unsigned char OneWire_all_rd_t();
		// ��������� ������������������ ������������� (reset + ������� ������� �����������)
		// ���� ������� ����������� �������, ��������� ������� SKIP ROM
		// ���� ������� ��������� �����������
			// ���� 760�� ���� ������ ������� �����������   
	
	unsigned char onewire_read_rom(unsigned char *sens_ID);
		// ��������� ������������������ ������������� (reset + ������� ������� �����������)
		// ���� ������� ����������� �������, ��������� ������� READ ROM, ����� ������ 8-�������� ��� ����������
		// ��������� ��� � ����� �� ��������� buf, ������� � �������� �����
		// ���������� 1, ���� ��� ��������, 0 - ���� ������� ����������� �� �������
	
	unsigned char OneWire_match_ID(unsigned char *sens_ID);
		// ��������� � ������� �� id
	
	long ds18b20_i_rd_t();
		// ������ ��������� ����������� �������
	
	unsigned char get_sensor_ID(unsigned char *sens_ID);
		
	// 1-wire
/*=========================================================================== */
	
//=====
#ifdef	__cplusplus
}
#endif

#endif	/* D_ONE_WIRE_H */

