//=========================================================================================================================//
// ADC initialization
void MCU_ADC_init()
{
	MDR_RST_CLK->PER_CLOCK |= (1 << 17); 											// Clocking of ADC is enabled
	MDR_ADC->ADC1_CFG = (1																		// ADC is enabled
	|(0 << 1)																									// Reset of bit "begin conversation"
	|(0 << 2)																									// Source clock - CPU_CLK
	|(1 << 3)																									// Start after finish last transformation
	|(0 << 4)																									// Number of transformation channel
	|(0 << 9)																									// Switching of channel is disabled
	|(0 << 10)																								// Auto control of levels is disabled
	|(0 << 11)																								// Reference voltage source - internal
	|(3 << 12)																								// Division factor of frequency ADC_CLK = HCLK/8 = 10 M
	|(0 << 16)																								// Working of two ADC at the same time is disabled
	|(0 << 17)																								// Temperature sensor and reference voltage source are disabled
	|(0 << 18)																								// Temperature sensor amplifier and reference voltage source amplifier are disabled
	|(0 << 19)																								// Temperature sensor digitization os disabled
	|(0 << 20));																							// Reference voltage source digitization 1.23 V is disabled 
}
//=========================================================================================================================//
void Port_Set()
{
	MDR_PORTD->OE 	 	&=~ (1 << 4);
	MDR_PORTD->ANALOG &=~ (1 << 4);
}
//=========================================================================================================================//
void ADC_set_channel(uint8_t channel)
{
	// Scanning of number channel and return if it uot of range
	if (channel > 15){return;}
	MDR_ADC->ADC1_CFG |= channel << 4;												// Channel ADC setting
}
//=========================================================================================================================//
void ADC_start_conversion(void)
{
	MDR_ADC->ADC1_CFG |= 1 << 1; 															// The command of start conversion
}
//=========================================================================================================================//
uint32_t ADC_read(void)
{
	uint32_t ADC_data = 0;																		// The local variable for storage result
	ADC_start_conversion();																		// The command for start conversion
	while(!(MDR_ADC->ADC1_STATUS) & (1 << 2)) {}
		
		ADC_data = MDR_ADC->ADC1_RESULT;
		ADC_data = ADC_data & 0x0FFF;
		return ADC_data;
}
//=========================================================================================================================//
void DAC_init(uint16_t value)
{
	MDR_DAC->CFG = 0x8;
	MDR_DAC->DAC2_DATA = value;
}
//========================================================================================================================//

//NVIC_EnableIRQ(ADC_IRQn);																	Initialization of interrupt

/*int main()
{
	Initialization_All_Function();														
	uint32_t ch_4_counts = 0;
	while(1)
	{							  
		ADC_set_channel(4);
		ch_4_counts = ADC_read();
		LCD_set_cursor(0);
		LCD_print_text("־עסקועû ְײֿ: ");
		LCD_print_num(ch_4_counts);
		LCD_print_text("   ");
		delay_ms(100);
	}
}*/