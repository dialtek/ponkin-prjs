#ifndef DIALTEK_ONE_WIRE_H
#define	DIALTEK_ONE_WIRE_H
 
#ifdef	__cplusplus
extern "C"
{
#endif
///=====	
// 1-wire
#define One_wire_TX_pin   LATDbits.LATD6  // RD6	  
#define One_wire_RX_pin   PORTDbits.RD5   // RD5	
	
#define ID_lenght	8     // ���-�� ���� � ID �������
#define MaxSensQty 20   // ����. ����� �������� 

/*--------------------------------------------------------------------------- */
#define CRC8INIT   0x00  
#define CRC8POLY   0x18  
#define Skip_ROM   0xCC         // команда обращения ко всем датчикам на шине
#define Convert_T  0x44         // команда начала измерения температуры
#define Match_ROM  0x55         // команда обращения к отдельному датчику
#define Read_scr   0xBE         // команда чтения показаний температуры датчика      
#define Read_ROM   0x33         // команда чтения ID одного подключенного к шине устройства
/*--------------------------------------------------------------------------- */
// 1-wire ������ � ������������
/*--------------------------------------------------------------------------- */

 void OneWire_tx_state(unsigned char state);
 
 unsigned int OneWire_rx_state();

 unsigned char OneWire_reset();
 
 void OneWire_send_bit(unsigned char b);

 unsigned char OneWire_read_bit();

 unsigned char OneWire_read();

 void OneWire_send(unsigned char b);

 unsigned char crc8 (unsigned char data, unsigned char crc);

 unsigned char OneWire_skip();

 unsigned char OneWire_all_rd_t();
 
 unsigned char onewire_read_rom(unsigned char *sens_ID);

 unsigned char OneWire_match_ID(unsigned char *sens_ID);
		
 long ds18b20_i_rd_t();

// 1-wire
/*=========================================================================== */
//=====
#ifdef	__cplusplus
}
#endif

#endif	/* DIALTEK_ONE_WIRE_H */
