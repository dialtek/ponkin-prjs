#ifndef __MILKITES_SPI_H__
#define __MILKITES_SPI_H__

#define LCD_CS_OFF 	     MDR_PORTF->RXTX &=  ~(1<<2)

/*--------------------------------------------------------------------------- */
// SPI
void MDR32_SSP1_init(void);

void SPI1_Wr_Data (uint16_t data);

uint16_t SPI1_Rd_Data(void);

#endif
	