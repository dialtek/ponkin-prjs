#include "LVDB_ADC.h"

static uint16_t SPIfreq = 4; 					// F = 410.25 kHz by default; 				
static SPI_TypeDef* _SPIx;

// SPIfreq = 7 => F = 51.25  kHz
// SPIfreq = 6 => F = 102.5  kHz
// SPIfreq = 5 => F = 205    kHz // OK with termination
// SPIfreq = 4 => F = 410.25 kHz // OK with termination
// SPIfreq = 3 => F = 820.5  kHz // OK with termination

// SPIfreq = 2 => F = 1.64   MHz // err in RX data
// SPIfreq = 1 => F = 3.29   MHz // err in RX data
// SPIfreq = 0 => F = 6.57   MHz // err in RX data

// SPI frequency set
void ADCxSetRdFreq(uint16_t f)
{
	if(f > 7) f = 7;
	
	SPIfreq = f;
}
// init
void LVDB_init(void)
{
	nTurnOn_1_1_HIGH;
	nTurnOn_1_2_HIGH;
	nTurnOn_1_3_HIGH;
	nTurnOn_1_4_HIGH;
	nTurnOn_1_5_HIGH;
	nTurnOn_1_6_HIGH;
	nTurnOn_1_7_HIGH;
	nTurnOn_1_8_HIGH;
	nTurnOn_1_9_HIGH;
	
	nTurnOn_2_1_HIGH;
	nTurnOn_2_2_HIGH;
	nTurnOn_2_3_HIGH;
	nTurnOn_2_4_HIGH;
	nTurnOn_2_5_HIGH;
	nTurnOn_2_6_HIGH;
	nTurnOn_2_7_HIGH;
	nTurnOn_2_8_HIGH;
	nTurnOn_2_9_HIGH;
	
	L1_CS1_HIGH;
	L1_CS2_HIGH;
	L1_CS3_HIGH;
	L1_CS4_HIGH;
	L1_CS5_HIGH;
	L1_CS6_HIGH;
	L1_CS7_HIGH;
	
	L2_CS1_HIGH;
	L2_CS2_HIGH;
	L2_CS3_HIGH;
	L2_CS4_HIGH;
	L2_CS5_HIGH;
	L2_CS6_HIGH;
	L2_CS7_HIGH;
}

// ADC select func
void ADCxEnDis(SPI_TypeDef* SPIx, uint8_t ADCx, uint8_t state)
{
	if(SPIx == SPI1)
	{
		switch (ADCx)
		{
			case ADC_1: (state == aEN) ? L1_CS1_LOW : L1_CS1_HIGH; break;
			case ADC_2: (state == aEN) ? L1_CS2_LOW : L1_CS2_HIGH; break;
			case ADC_3: (state == aEN) ? L1_CS3_LOW : L1_CS3_HIGH; break;
			case ADC_4: (state == aEN) ? L1_CS4_LOW : L1_CS4_HIGH; break;
			case ADC_5: (state == aEN) ? L1_CS5_LOW : L1_CS5_HIGH; break;
			case ADC_6: (state == aEN) ? L1_CS6_LOW : L1_CS6_HIGH; break;
			case ADC_7: (state == aEN) ? L1_CS7_LOW : L1_CS7_HIGH; break;
		}
	}
	
  if(SPIx == SPI2)
	{
		switch (ADCx)
		{
			case ADC_1: (state == aEN) ? L2_CS1_LOW : L2_CS1_HIGH; break;
			case ADC_2: (state == aEN) ? L2_CS2_LOW : L2_CS2_HIGH; break;
			case ADC_3: (state == aEN) ? L2_CS3_LOW : L2_CS3_HIGH; break;
			case ADC_4: (state == aEN) ? L2_CS4_LOW : L2_CS4_HIGH; break;
			case ADC_5: (state == aEN) ? L2_CS5_LOW : L2_CS5_HIGH; break;
			case ADC_6: (state == aEN) ? L2_CS6_LOW : L2_CS6_HIGH; break;
			case ADC_7: (state == aEN) ? L2_CS7_LOW : L2_CS7_HIGH; break;
		}
	}

		
}
	
// ADC set meas channel func
void ADCxSetCh(SPI_TypeDef* SPIx, uint8_t ch)
{
 	if(ch > 7) ch = 7;
	
	SPI_I2S_SendData(SPIx, (ADCstartCmd | ch << 4));
	// Проверка статуса передачи данных
  //while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET) { }	
	
	while(!(SPIx->SR & SPI_I2S_FLAG_TXE));
	while (SPIx->SR & (SPI_I2S_FLAG_BSY));

	SPI_I2S_ReceiveData(SPIx); // следует вычитать после записи 
}	

// read ADC channel func - counts
uint16_t ADCxRdCHx(SPI_TypeDef* SPIx, uint8_t ADCx, uint8_t ch)
{
		if(ADCx > 7) ADCx = 7;
	
		uint16_t data = 0;								  // var to store ADC meas data
	
		SPIxInit(SPIx, 0, SPIfreq);					// set SPI1 to send ADC cmd mode

		ADCxEnDis(SPIx,ADCx,aEN);
		ADCxSetCh(SPIx,ch);								// set ADC ch
	  ADCxEnDis(SPIx,ADCx,aDIS);

																				// Tconv = 11 us, ADS SPS = 110 kSPS 
		
		SPIxInit(SPIx, 1, SPIfreq);					// set SPI1 to read ADC counts mode
	
		ADCxEnDis(SPIx,ADCx,aEN); 
		SPI_I2S_SendData(SPIx, 0x00); 			// SPI1 toggle clocks
		while(!(SPIx->SR & SPI_I2S_FLAG_RXNE));		// wait SPI1 busy
		while(SPIx->SR & (SPI_I2S_FLAG_BSY));
	
		if (SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_RXNE) == SET) 
		{   // if the data received
				data = SPI_I2S_ReceiveData(SPIx);
			  data = data >> 4; // 16 bit to 12 bit ADC counts
		} 
		ADCxEnDis(SPIx, ADCx,aDIS);
		
		return data;
}


// read ADC channel func - voltage
unsigned int ADCxChxMeasV(SPI_TypeDef* SPIx, uint8_t ADCx, uint8_t ch)
{
	return (unsigned int)(((float)ADCxRdCHx(SPIx, ADCx, ch) * ADC_lsb) * 1000.0);
}

// read both ADC
void LVDBxChxMeasV(uint8_t LVDBx, unsigned int *Arr)
{
	_SPIx = (LVDBx == 1) ? SPI1 : SPI2;
	
	for(uint8_t i = 0; i < 7; i++)
	{
		for(uint8_t j = 0; j < 8; j++)
			*Arr++ = ADCxChxMeasV(_SPIx, i, j);
	}
}

