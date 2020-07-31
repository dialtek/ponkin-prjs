// SERIAL EEPROM lib, RTOS MOD

#ifndef D_EEPROM_H
#define	D_EEPROM_H

#ifdef	__cplusplus
extern "C"
{
#endif
/*================================ EEPROM =================================== */
	
// 25LC128 SPI EEPROM
#define EEPROM_READ  0x03  // Read data from memory array beginning at selected address
#define EEPROM_WRITE 0x02  // Write data to memory array beginning at selected address  
#define EEPROM_WREN  0x06  // Set the write enable latch (enable write operations)
#define EEPROM_RDSR  0x05  // Read STATUS register

#define HOLD_REGS    (unsigned char)10 	
#define INPUT_REGS   (unsigned char)11

#define INPUT_REGS_ADDR 256U
#define CRC_ADDR 512U
#define START_ADDR 0U
	
#define Data2saveLen 2U
	
unsigned int EEPROM_CRC16(unsigned char buf[], unsigned int len);

void eeprom_wr_page(unsigned char reg_type, unsigned int address);

void eeprom_wr_regs(unsigned char reg_type);

void eeprom_wr_CRC(unsigned int CRC);

unsigned eeprom_rd_CRC(void);

void eeprom_clear_page(unsigned int address);

void eeprom_clear(void);

void eeprom_rd_regs_H(void);


#ifdef	__cplusplus
}
#endif

#endif	/* D_EEPROM_H */
/*================================ EEPROM =================================== */
