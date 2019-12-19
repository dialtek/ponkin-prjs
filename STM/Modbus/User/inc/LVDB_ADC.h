#ifndef LVDB_ADC_H
#define	LVDB_ADC_H

#ifdef	__cplusplus
extern "C"
{
#endif

#include <stdint.h>
#include "Config.h"
#include "SPI.h"
	
#define LVDBxChNum 56
	
	
//================================ ADC CSs =============================//
// LVDB 1
	
#define SPI1_CSn_PORT GPIOC

#define L1_CS1_LOW  GPIO_WriteBit(SPI1_CSn_PORT, GPIO_Pin_0, Bit_RESET)
#define L1_CS1_HIGH GPIO_WriteBit(SPI1_CSn_PORT, GPIO_Pin_0, Bit_SET)

#define L1_CS2_LOW  GPIO_WriteBit(SPI1_CSn_PORT, GPIO_Pin_1, Bit_RESET)
#define L1_CS2_HIGH GPIO_WriteBit(SPI1_CSn_PORT, GPIO_Pin_1, Bit_SET)

#define L1_CS3_LOW  GPIO_WriteBit(SPI1_CSn_PORT, GPIO_Pin_2, Bit_RESET)
#define L1_CS3_HIGH GPIO_WriteBit(SPI1_CSn_PORT, GPIO_Pin_2, Bit_SET)

#define L1_CS4_LOW  GPIO_WriteBit(SPI1_CSn_PORT, GPIO_Pin_3, Bit_RESET)
#define L1_CS4_HIGH GPIO_WriteBit(SPI1_CSn_PORT, GPIO_Pin_3, Bit_SET)

#define L1_CS5_LOW  GPIO_WriteBit(SPI1_CSn_PORT, GPIO_Pin_4, Bit_RESET)
#define L1_CS5_HIGH GPIO_WriteBit(SPI1_CSn_PORT, GPIO_Pin_4, Bit_SET)

#define L1_CS6_LOW  GPIO_WriteBit(SPI1_CSn_PORT, GPIO_Pin_5, Bit_RESET)
#define L1_CS6_HIGH GPIO_WriteBit(SPI1_CSn_PORT, GPIO_Pin_5, Bit_SET)

#define L1_CS7_LOW  GPIO_WriteBit(SPI1_CSn_PORT, GPIO_Pin_6, Bit_RESET)
#define L1_CS7_HIGH GPIO_WriteBit(SPI1_CSn_PORT, GPIO_Pin_6, Bit_SET)

//----

#define SPI2_CSn_PORT GPIOD

#define L2_CS1_LOW  GPIO_WriteBit(SPI2_CSn_PORT, GPIO_Pin_0, Bit_RESET)
#define L2_CS1_HIGH GPIO_WriteBit(SPI2_CSn_PORT, GPIO_Pin_0, Bit_SET)

#define L2_CS2_LOW  GPIO_WriteBit(SPI2_CSn_PORT, GPIO_Pin_1, Bit_RESET)
#define L2_CS2_HIGH GPIO_WriteBit(SPI2_CSn_PORT, GPIO_Pin_1, Bit_SET)

#define L2_CS3_LOW  GPIO_WriteBit(SPI2_CSn_PORT, GPIO_Pin_2, Bit_RESET)
#define L2_CS3_HIGH GPIO_WriteBit(SPI2_CSn_PORT, GPIO_Pin_2, Bit_SET)

#define L2_CS4_LOW  GPIO_WriteBit(SPI2_CSn_PORT, GPIO_Pin_3, Bit_RESET)
#define L2_CS4_HIGH GPIO_WriteBit(SPI2_CSn_PORT, GPIO_Pin_3, Bit_SET)

#define L2_CS5_LOW  GPIO_WriteBit(SPI2_CSn_PORT, GPIO_Pin_4, Bit_RESET)
#define L2_CS5_HIGH GPIO_WriteBit(SPI2_CSn_PORT, GPIO_Pin_4, Bit_SET)

#define L2_CS6_LOW  GPIO_WriteBit(SPI2_CSn_PORT, GPIO_Pin_5, Bit_RESET)
#define L2_CS6_HIGH GPIO_WriteBit(SPI2_CSn_PORT, GPIO_Pin_5, Bit_SET)

#define L2_CS7_LOW  GPIO_WriteBit(SPI2_CSn_PORT, GPIO_Pin_6, Bit_RESET)
#define L2_CS7_HIGH GPIO_WriteBit(SPI2_CSn_PORT, GPIO_Pin_6, Bit_SET)

//========================== Voltage regulators ENs ======================//

#define nTurnOn_1_1_LOW   GPIO_WriteBit(GPIOC, GPIO_Pin_7, Bit_RESET)
#define nTurnOn_1_1_HIGH  GPIO_WriteBit(GPIOC, GPIO_Pin_7, Bit_SET)
#define nTurnOn_1_2_LOW   GPIO_WriteBit(GPIOC, GPIO_Pin_8, Bit_RESET)
#define nTurnOn_1_2_HIGH  GPIO_WriteBit(GPIOC, GPIO_Pin_8, Bit_SET)
#define nTurnOn_1_3_LOW   GPIO_WriteBit(GPIOC, GPIO_Pin_9, Bit_RESET)
#define nTurnOn_1_3_HIGH  GPIO_WriteBit(GPIOC, GPIO_Pin_9, Bit_SET)
#define nTurnOn_1_4_LOW   GPIO_WriteBit(GPIOC, GPIO_Pin_10, Bit_RESET)
#define nTurnOn_1_4_HIGH  GPIO_WriteBit(GPIOC, GPIO_Pin_10, Bit_SET)
#define nTurnOn_1_5_LOW   GPIO_WriteBit(GPIOC, GPIO_Pin_11, Bit_RESET)
#define nTurnOn_1_5_HIGH  GPIO_WriteBit(GPIOC, GPIO_Pin_11, Bit_SET)
#define nTurnOn_1_6_LOW   GPIO_WriteBit(GPIOC, GPIO_Pin_12, Bit_RESET)
#define nTurnOn_1_6_HIGH  GPIO_WriteBit(GPIOC, GPIO_Pin_12, Bit_SET)
#define nTurnOn_1_7_LOW   GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_RESET)
#define nTurnOn_1_7_HIGH  GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_SET)
#define nTurnOn_1_8_LOW   GPIO_WriteBit(GPIOC, GPIO_Pin_14, Bit_RESET)
#define nTurnOn_1_8_HIGH  GPIO_WriteBit(GPIOC, GPIO_Pin_14, Bit_SET)
#define nTurnOn_1_9_LOW   GPIO_WriteBit(GPIOC, GPIO_Pin_15, Bit_RESET)
#define nTurnOn_1_9_HIGH  GPIO_WriteBit(GPIOC, GPIO_Pin_15, Bit_SET)

//======================= ADCx and meas channel select ===================//

#define ADCstartCmd (uint8_t)0x80
#define ADC_1				(uint8_t)0
#define ADC_2				(uint8_t)1
#define ADC_3				(uint8_t)2
#define ADC_4				(uint8_t)3
#define ADC_5				(uint8_t)4
#define ADC_6				(uint8_t)5
#define ADC_7				(uint8_t)6

#define Ch0					(uint8_t)0
#define Ch1					(uint8_t)1
#define Ch2					(uint8_t)2
#define Ch3					(uint8_t)3
#define Ch4					(uint8_t)4
#define Ch5					(uint8_t)5
#define Ch6					(uint8_t)6
#define Ch7					(uint8_t)7

#define aEN					(uint8_t)1
#define aDIS				(uint8_t)0

#define ADC_lsb     0.001220703125

//============================= func prototypes =========================//
void LVDB_init(void);

void ADCxEnDis(SPI_TypeDef* SPIx, uint8_t ADCx, uint8_t state);

void ADCxSetCh(SPI_TypeDef* SPIx, uint8_t ch);

uint16_t ADCxRdCHx(SPI_TypeDef* SPIx, uint8_t ADCx, uint8_t ch);

unsigned int ADCxChxMeasV(SPI_TypeDef* SPIx, uint8_t ADCx, uint8_t ch);

void ADCxSetRdFreq(uint16_t f);
	
//=======================================================================//

#ifdef	__cplusplus
}
#endif

#endif	/* LVDB_ADC_H */