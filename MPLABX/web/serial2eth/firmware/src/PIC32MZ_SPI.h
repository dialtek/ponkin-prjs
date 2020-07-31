/* 
 * File:   PIC32MZ_SPI.h
 * Author: ADM
 *
 * Created on 22 апреля 2020 г., 11:27
 */

#ifndef PIC32MZ_SPI_H
#define	PIC32MZ_SPI_H

#ifdef	__cplusplus
extern "C"
{
#endif

void SPI1_init(void);

void SPI1_write_byte(unsigned char buf);               

unsigned char SPI1_read_byte(void);

void SPI2_init(void);

void SPI2_write_byte(unsigned char buf);               

unsigned char SPI2_read_byte(void);

#ifdef	__cplusplus
}
#endif

#endif	/* PIC32MZ_SPI_H */

