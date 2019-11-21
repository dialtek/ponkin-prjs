#include "LVDB_ADC.h"

static uint16_t SPIfreq = 6; // F = 102.5 kHz by default

void ADCxSetRdFreq(uint16_t f)
{
	if(f > 7) f = 7;
	
	SPIfreq = f;
}
void LVDB_init(void)
{

	nTurnOn2_HIGH;
	CS1_HIGH;
	CS2_HIGH;
	CS3_HIGH;
	CS4_HIGH;
	CS5_HIGH;
	CS6_HIGH;
	CS7_HIGH;
}

void ADCxEnDis(uint8_t ADCx, uint8_t state)
{
	switch (ADCx)
	{
		case ADC_1: (state == aEN) ? CS1_LOW : CS1_HIGH; break;
		case ADC_2: (state == aEN) ? CS2_LOW : CS2_HIGH; break;
		case ADC_3: (state == aEN) ? CS3_LOW : CS3_HIGH; break;
		case ADC_4: (state == aEN) ? CS4_LOW : CS4_HIGH; break;
		case ADC_5: (state == aEN) ? CS5_LOW : CS5_HIGH; break;
		case ADC_6: (state == aEN) ? CS6_LOW : CS6_HIGH; break;
		case ADC_7: (state == aEN) ? CS7_LOW : CS7_HIGH; break;
	}
}
	
void ADCsetCh(uint8_t ch)
{
 	if(ch > 7) ch = 7;
	
	SPI_I2S_SendData(SPI1, (ADCstartCmd | ch << 4));
	// Проверка статуса передачи данных
  //while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET) { }	
	while(!(SPI1->SR & SPI_I2S_FLAG_TXE));
	while (SPI1->SR & (SPI_I2S_FLAG_BSY));

	SPI_I2S_ReceiveData(SPI1); // нужно вычитать после записи 
}	
	

uint16_t ADCxRdCHx(uint8_t ADCx, uint8_t ch)
{
		if(ADCx > 7) ADCx = 7;
	
		uint16_t data = 0;		// var to store ADC meas data
	
		Spi1Init(0,SPIfreq);					// set SPI1 to send ADC cmd mode

		ADCxEnDis(ADCx,aEN);
		ADCsetCh(ch);					// set ADC ch
	  ADCxEnDis(ADCx,aDIS);

		// Tconv = 11 us, ADS SPS = 110 kSPS 
		
		Spi1Init(1,SPIfreq);					// set SPI1 to read ADC counts mode
	
		ADCxEnDis(ADCx,aEN); 
		SPI_I2S_SendData(SPI1, 0x00); // SPI1 toggle clocks
		while(!(SPI1->SR & SPI_I2S_FLAG_RXNE));		// wait SPI1 busy
		while(SPI1->SR & (SPI_I2S_FLAG_BSY));
		
		if (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == SET) 
		{   // if the data received
				data = SPI_I2S_ReceiveData(SPI1);
			  data = data >> 4; // 16 bit to 12 bit ADC counts
		} 
		ADCxEnDis(ADCx,aDIS);
		
		return data;
}


uint16_t ADCxChxMeasV(uint8_t ADCx, uint8_t ch)
{
	return (uint16_t)(((float)ADCxRdCHx(ADCx,ch) * ADC_lsb)*1000.0);
}

