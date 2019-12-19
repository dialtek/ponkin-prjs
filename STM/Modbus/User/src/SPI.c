#include "SPI.h"

void SPIxInit(SPI_TypeDef* SPIx, uint8_t mode, uint8_t f)
{
	// mode = 0 - 8 bit  => cmd byte
	// mode = 1 - 16 bit => data word
	
	uint16_t SPIdataSize;	// SPI msg data size setup
	uint16_t SPIsclkEdge;	// SPI SCLK data latch setup
	uint16_t SPI_freq;
	SPI_InitTypeDef SPI_InitStructure;
	
	switch(f)
	{
		case 0: SPI_freq = SPI_BaudRatePrescaler_2;   break;
		case 1: SPI_freq = SPI_BaudRatePrescaler_4;   break;
		case 2: SPI_freq = SPI_BaudRatePrescaler_8;   break;
		case 3: SPI_freq = SPI_BaudRatePrescaler_16;  break;
		case 4: SPI_freq = SPI_BaudRatePrescaler_32;  break;
		case 5: SPI_freq = SPI_BaudRatePrescaler_64;  break;
		case 6: SPI_freq = SPI_BaudRatePrescaler_128; break;
		case 7: SPI_freq = SPI_BaudRatePrescaler_256; break;
		
		default: SPI_freq = SPI_BaudRatePrescaler_128;
	}
	
	SPI_Cmd(SPIx, DISABLE);
		
	if(mode == 0)
	{
		SPIdataSize = SPI_DataSize_8b;
		SPIsclkEdge = SPI_CPHA_1Edge;
	}
	if(mode == 1)
	{
		SPIdataSize = SPI_DataSize_16b;
 		SPIsclkEdge = SPI_CPHA_2Edge;
	}	

	// Поскольку сигнал NSS контролируется программно, установим его в единицу(МК - мастер)
  SPI_NSSInternalSoftwareConfig(SPIx, SPI_NSSInternalSoft_Set);
	
  //Заполняем структуру с параметрами SPI модуля
  SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex; 	// полный дуплекс
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low; 													// Полярность и
	
  SPI_InitStructure.SPI_DataSize = SPIdataSize; 											// передаем по 8 бит
  
  SPI_InitStructure.SPI_CPHA = SPIsclkEdge; 											  	// фаза тактового сигнала
	//Режим 1 - по переднему нарастающему фронту
  SPI_InitStructure.SPI_NSS = SPI_NSS_Soft; 													// Управлять состоянием сигнала NSS программно
  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_freq;								  // Предделитель SCK:
	
																																			// "0":	div 2   - 6.56	 MHz
																																			// "1": div 4   - 3.28	 MHz
																																			// "2":	div 8   - 1.64	 MHz
																																			// "3":	div 16  - 820		 kHz
																																			// "4":	div32   - 410    kHz
																																			// "5":	div64   - 205    kHz
																																			// "6":	div128  - 102.5  kHz
																																			// "7":	div256  - 51.275 kHz
																																			
  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB; 									// Первым отправляется старший бит
  SPI_InitStructure.SPI_Mode = SPI_Mode_Master; 											// Режим - мастер
  SPI_Init(SPIx, &SPI_InitStructure); 																// Настраиваем SPI1

  SPI_Cmd(SPIx, ENABLE); 																							// Включаем модуль SPI1
  
}