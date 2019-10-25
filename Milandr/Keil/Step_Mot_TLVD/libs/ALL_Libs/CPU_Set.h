//=========================================================================================================================//
void CPU_set()
{
	MDR_RST_CLK->HS_CONTROL = 1;															// External Source Clock is Enable 
	MDR_RST_CLK->PLL_CONTROL = 0b100100000000;								// Frequency Multiply
	MDR_RST_CLK->CPU_CLOCK = 0b0100000010;										// Select Clock source - HSE, PLL - OFF, frequency - 10 MHz
	while(MDR_RST_CLK->CLOCK_STATUS & 2){}
	MDR_RST_CLK->PER_CLOCK = 0xFFFFFFFF;											// Clocking of all periphery
	MDR_RST_CLK->TIM_CLOCK |= (1 << 24);   										// Clocking of the Timer1
}
//=========================================================================================================================//