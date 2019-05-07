/* 
 * File:   d_one_wire.h
 * Author: D_LHEP_DESKTOP
 *
 * Created on 5 апреля 2019 г., 13:49
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
#define Skip_ROM   0xCC         // команда обращения ко всем датчикам на шине
#define Convert_T  0x44         // команда начала измерения температуры
#define Match_ROM  0x55         // команда обращения к отдельному датчику
#define Read_scr   0xBE         // команда чтения показаний температуры датчика      
#define Read_ROM   0x33         // команда чтения ID одного подключенного к шине устройства
/*--------------------------------------------------------------------------- */
#define ID_lenght	8                   // OW ID lenght in bytes
#define MAX_sens_qty 10U                    // MAX sensors qty

#define SEND_MEAS_CMD (unsigned char)100
#define IDLE          (unsigned char)101
#define READ_SENSORS  (unsigned char)102
	
/*=========================================================================== */
// 1-wire 

	void OneWire_tx_state(unsigned char state);
		// установление лог. упровня на линии 1-wire
 
	unsigned int OneWire_rx_state();
		// Читает значение уровня на шине 1-wire
	
	unsigned char OneWire_reset();
		// Выдаёт импульс сброса (reset), ожидает ответный импульс присутствия.
		// Если импульс присутствия получен, дожидается его завершения и возвращает 1, иначе возвращает 0 
	
	void OneWire_send_bit(unsigned char bit);
		// Отправляет один бит
		// bit отправляемое значение, 0 - ноль, любое другое значение - единица
	
	unsigned char OneWire_read_bit();
		// читает значение бита, передаваемое уйстройством.
		// Возвращает 0 - если передан 0, отличное от нуля значение - если передана единица
	
	unsigned char OneWire_read();
		// Читает один байт, переданный устройством, 
		// младший бит вперёд, возвращает прочитанное значение
	
	void OneWire_send(unsigned char b);
		// Отправляет один байт, восемь подряд бит, младший бит вперёд
		// b - отправляемое значение
	
	unsigned char crc8 (unsigned char data, unsigned char crc);
		// расчет контрольной суммы

	unsigned char OneWire_skip();
		// Выполняет последовательность инициализации (reset + ожидает импульс присутствия)
		// Если импульс присутствия получен, выполняет команду SKIP ROM
		// Возвращает 1, если импульс присутствия получен, 0 - если нет
	
	unsigned char OneWire_all_rd_t();
		// Выполняет последовательность инициализации (reset + ожидает импульс присутствия)
		// Если импульс присутствия получен, выполняет команду SKIP ROM
		// Дает команду измерение температуры
			// Ждет 760мс пока датчик измерит температуру   
	
	unsigned char onewire_read_rom(unsigned char *sens_ID);
		// Выполняет последовательность инициализации (reset + ожидает импульс присутствия)
		// Если импульс присутствия получен, выполняет команду READ ROM, затем читает 8-байтовый код устройства
		// сохраняет его в буфер по указателю buf, начиная с младшего байта
		// Возвращает 1, если код прочитан, 0 - если импульс присутствия не получен
	
	unsigned char OneWire_match_ID(unsigned char *sens_ID);
		// Обращение к датчику по id
	
	long ds18b20_i_rd_t();
		// чтение показаний конкретного датчика
	
	unsigned char get_sensor_ID(unsigned char *sens_ID);
		
	// 1-wire
/*=========================================================================== */
	
//=====
#ifdef	__cplusplus
}
#endif

#endif	/* D_ONE_WIRE_H */

