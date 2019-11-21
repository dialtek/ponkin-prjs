#ifndef LVDB_ADC_H
#define	LVDB_ADC_H

#ifdef	__cplusplus
extern "C"
{
#endif

#include <stdint.h>
#include "Config.h"
#include "SPI.h"
	
//================================ ADC CSs =============================//
#define CS1_PORT GPIOA
#define CSn_PORT GPIOE

#define CS1_LOW  GPIO_WriteBit(GPIOA, GPIO_Pin_4, Bit_RESET)
#define CS1_HIGH GPIO_WriteBit(GPIOA, GPIO_Pin_4, Bit_SET)

#define CS2_LOW  GPIO_WriteBit(CSn_PORT, GPIO_Pin_7, Bit_RESET)
#define CS2_HIGH GPIO_WriteBit(CSn_PORT, GPIO_Pin_7, Bit_SET)

#define CS3_LOW  GPIO_WriteBit(CSn_PORT, GPIO_Pin_8, Bit_RESET)
#define CS3_HIGH GPIO_WriteBit(CSn_PORT, GPIO_Pin_8, Bit_SET)

#define CS4_LOW  GPIO_WriteBit(CSn_PORT, GPIO_Pin_9, Bit_RESET)
#define CS4_HIGH GPIO_WriteBit(CSn_PORT, GPIO_Pin_9, Bit_SET)

#define CS5_LOW  GPIO_WriteBit(CSn_PORT, GPIO_Pin_10, Bit_RESET)
#define CS5_HIGH GPIO_WriteBit(CSn_PORT, GPIO_Pin_10, Bit_SET)

#define CS6_LOW  GPIO_WriteBit(CSn_PORT, GPIO_Pin_11, Bit_RESET)
#define CS6_HIGH GPIO_WriteBit(CSn_PORT, GPIO_Pin_11, Bit_SET)

#define CS7_LOW  GPIO_WriteBit(CSn_PORT, GPIO_Pin_12, Bit_RESET)
#define CS7_HIGH GPIO_WriteBit(CSn_PORT, GPIO_Pin_12, Bit_SET)
//========================== Voltage regulators ENs ======================//

#define nTurnOn2_LOW   GPIO_WriteBit(GPIOE, GPIO_Pin_15, Bit_RESET)
#define nTurnOn2_HIGH  GPIO_WriteBit(GPIOE, GPIO_Pin_15, Bit_SET)

//======================= ADCx and meas channel select ===================//

#define ADCstartCmd (uint8_t)0x80
#define ADC_1				(uint8_t)0
#define ADC_2				(uint8_t)1
#define ADC_3				(uint8_t)2
#define ADC_4				(uint8_t)3
#define ADC_5				(uint8_t)4
#define ADC_6				(uint8_t)5
#define ADC_7				(uint8_t)6

#define Ch1					(uint8_t)0
#define Ch2					(uint8_t)1
#define Ch3					(uint8_t)2
#define Ch4					(uint8_t)3
#define Ch5					(uint8_t)4
#define Ch6					(uint8_t)5
#define Ch7					(uint8_t)6
#define Ch8					(uint8_t)7

#define aEN					(uint8_t)1
#define aDIS				(uint8_t)0

#define ADC_lsb     0.001220703125

//============================= func prototypes =========================//
void LVDB_init(void);

void ADCxEnDis(uint8_t ADCx, uint8_t state);

void ADCsetCh(uint8_t ch);

uint16_t ADCxRdCHx(uint8_t ADCx, uint8_t ch);

uint16_t ADCxChxMeasV(uint8_t ADCx, uint8_t ch);

void ADCxSetRdFreq(uint16_t f);
	
//=======================================================================//

#ifdef	__cplusplus
}
#endif

#endif	/* LVDB_ADC_H */