#ifndef D_SPI_H
#define	D_SPI_H

#ifdef	__cplusplus
extern "C"
{
#endif
	
/*=========================================================================== */
// SPI2 - Serial EEPROM
#define CS2_LOW   LATCbits.LATC2 = 0    // CS set LOW
#define CS2_HIGH  LATCbits.LATC2 = 1    // CS set HIGH

void SPI2_init(void);

volatile void SPI2_write_byte (unsigned char buf);             

volatile unsigned char SPI2_read_byte(void);

// SPI
/*=========================================================================== */

#ifdef	__cplusplus
}
#endif

#endif	/* D_SPI_H */

