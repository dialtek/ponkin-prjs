/* 
 * File:   d_SPI.h
 * Author: D_LHEP_DESKTOP
 *
 * Created on 5 апреля 2019 г., 12:56
 */

#ifndef D_SPI_H
#define	D_SPI_H

#ifdef	__cplusplus
extern "C"
{
#endif
	
/*=========================================================================== */
// SPI2 - Analog board CPLD
#define CS2_LOW   LATGbits.LATG15 = 0    // CS set LOW
#define CS2_HIGH  LATGbits.LATG15 = 1    // CS set HIGH
	
// SPI3 - Serial EEPROM
#define CS3_HIGH LATDbits.LATD8 = 1     // CS set HIGH
#define CS3_LOW  LATDbits.LATD8 = 0      // CS set LOW

void SPI1_init(void);

void SPI1_PUT_int (unsigned int buf);

 unsigned int SPI1_GET_int(void);

unsigned int SPI_READ_WORD (unsigned int ADDR);      // ѕроцедура чтени¤ байта по SPI

void CPLD_SPI_WR (unsigned int hold_reg_data, unsigned int  hold_reg_addr); 		// функци§ отправки по SPI Ю† >>> ЊОїЧ  
 
unsigned int CPLD_SPI_RD (unsigned int hold_reg_addr); 		// функци§ отправки по SPI Ю† >>> ЊОїЧ  
 
/*=========================================================================== */
// SPI3 - serial EEPROM
void SPI3_init();

void SPI3_write_byte (unsigned char buf);             

unsigned char SPI3_read_byte(void);

// SPI
/*=========================================================================== */

#ifdef	__cplusplus
}
#endif

#endif	/* D_SPI_H */

