//=========================================================================================================================//
void Timer1_init(void)
{
	MDR_RST_CLK->TIM_CLOCK |= (1 << 24);																			// Clocking of Timer 1 is on
	MDR_TIMER1->CNTRL = 0x00000000;																						// Count mode - up
	MDR_TIMER1->PSG = 9999;																										// Frequency devider
	MDR_TIMER1->ARR = 999;																										// The basis of the count = CNT + 1 = 1000
	MDR_TIMER1->CNT = 0;																											// Start value of Timer
	MDR_TIMER1->IE  = 2; 																											// Permission of interrupt when CNT = ARR
}
//=========================================================================================================================//
void Timer1_start(uint8_t state)
{
	MDR_TIMER1->CNTRL = state;
}
//=========================================================================================================================//