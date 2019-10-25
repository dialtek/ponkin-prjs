//Project name: PWM 3.0//

//=========================================================================================================================//
#include "MDR32Fx.h"                  										  // Device header
#define   F_CPU 10000000																		// Clock frequency
#include "milkites_delay.h"																	// Library of delay
#include "milkites_display.h"																// Library of display
#include "stdbool.h"																				// Library of BOOL data types
#include "ADC_DAC_init.h"
//#define LCD_led_en 		MDR_PORTE->RXTX |= (1 << 2) 				// Illumination is ON
//#define LCD_led_dis		MDR_PORTE->RXTX &= ~(1 << 2) 				// Illumination is OFF
#define PD7 1 << 7																					// bit of the button PB7
#define Read_PD7 (MDR_PORTD->RXTX & PD7)										// Reading pin PD7
bool last_state_PD7 = 0 << 7;																// Last state of PD7
uint16_t value1 = 0;
float brightness = 0;
//=========================================================================================================================//
void CPU_set()
{
	MDR_RST_CLK->HS_CONTROL = 1;															// External Source Clock is Enable 
	MDR_RST_CLK->PLL_CONTROL = 0b100100000000;								// Frequency Multiply
	MDR_RST_CLK->CPU_CLOCK = 0b0100000010;										// Select Clock source - HSE, PLL - OFF, frequency - 10 MHz
	while(MDR_RST_CLK->CLOCK_STATUS & 2){}
	MDR_RST_CLK->PER_CLOCK = 0xFFFFFFFF;											// Clocking of all periphery
}
//=========================================================================================================================//
// Initialization of use ports
void Ports_initialization()
{
	MDR_PORTE->OE			= 0b1111111100110111;										// Bytes 7, 6, 3 are input
	MDR_PORTE->FUNC 	= 3 << 4;																// Function is Port, Basic function
	MDR_PORTE->PWR		= 0xFF37;																// The fastest front 
	MDR_PORTE->ANALOG	= 0xFFFF;																// Operation mode - I/O
	
	//MDR_PORTB->OE			= 0x10;																	// Byte 4 is input
//	MDR_PORTB->FUNC		= 0x0000;																// Function is port
	//MDR_PORTB->ANALOG = 0x10;																	// Operation mode - I/O
	///MDR_PORTB->PWR    = 0x10;																	// The fastest front
	
	MDR_PORTD->OE  		= 0x1;																	// Byte 0 is output
	MDR_PORTD->FUNC		= 3 << 0;																// Function is port
	MDR_PORTD->ANALOG	= 0x1;																	// Operation mode - Analog, byte 7 is I/O
	MDR_PORTD->PWR 		= 0x1;																	// The fastest front
	
	//MDR_PORTA->OE 		= 0xFFFF;																// All pins are output
//	MDR_PORTA->FUNC		= 0x0000;																// Function is port
//	MDR_PORTA->ANALOG	= 0xFFFF;																// Operation mode - I/O
	//MDR_PORTA->PWR		= 0xFFFF;																// The fastest front
}
/*=========================================================================================================================*/
// Initializing timer1
void Timer1_init(void)
{
	MDR_RST_CLK->TIM_CLOCK |= (1 << 24);   										// Clocking of the Timer1
	MDR_RST_CLK->TIM_CLOCK |= 0b000; 													// Frequency devider - 1:1
	MDR_TIMER1->CNTRL = 0x00000041;				 										// Mode is up and down
	MDR_TIMER1->PSG = 100;														  			// Frequency devider
	MDR_TIMER1->ARR = 20;								 							  			// CNT + 1 = 1000
	MDR_TIMER1->CNT = 0;									 										// Start value
	MDR_TIMER1->IE = 2;										 										// Permission of interrupt if CNT = ARR
}
/*=========================================================================================================================*/
// Interrupt handler of Timer1
void Timer1_IRQHandler(void)
{
	MDR_TIMER1->CNT = 0; 																			// Reset Counter of Timer
	MDR_TIMER1->STATUS = 0;																		// Interrupt reset state
	NVIC_ClearPendingIRQ(Timer1_IRQn);												// Interrupt reset state																								// Call seconds function
}
//=========================================================================================================================//
// Starting Timer1
void Timer1_start(void)
{
	MDR_TIMER1 -> CNTRL = 1; 																	// Timer1 start
}
/*=========================================================================================================================*/
// Stop Timer1
void Timer1_stop(void)
{
	MDR_TIMER1 -> CNTRL = 0;																	// Timer1 stop
}
//=========================================================================================================================//
// Timer 3 initializing
void Timer3_init(void)
{
	MDR_RST_CLK->TIM_CLOCK |= (1 << 26);   										// Clocking of the Timer3
	MDR_RST_CLK->TIM_CLOCK |= 0b000; 													// Frequency devider - 1:1
	MDR_TIMER3->CNTRL = 0xFFFFFFFF;				 										// Mode is up
	MDR_TIMER3->PSG = 0;																			// Frequency devider
	MDR_TIMER3->ARR = 4095;									 									// CNT + 1 = 1000
	MDR_TIMER3->CNT = 0;									 										// Start value
	
	MDR_TIMER3->CH1_CNTRL1 =  (2<<2) | 1; 
  MDR_TIMER3->CCR2  =  0;
  
	
	MDR_TIMER3->CH1_CNTRL  =  6 << 9;  
}
//=========================================================================================================================//
// Starting timer 3
void Timer3_start(void)
{
	MDR_TIMER3 -> CNTRL = 1; 																	// Timer 3 start
}
//=========================================================================================================================//
// Stop timer 3
void Timer3_stop(void)
{
	MDR_TIMER3 -> CNTRL = 0; 																	// Stop Timer 3
}
//=========================================================================================================================//
void Initialization_All_Function(void)
{
	CPU_set();																								// Initializing settings of CPU
	Ports_initialization();																		// Initializing ports settings
	delay_init();																					  	// Initializing delay library
	LCD_init();																								// Initializing display library
	LCD_clear();																							// Cleaning display
//	LCD_led_en;																							// Illumination is enable
	Timer1_init();																						// Initializing Timer 1
	NVIC_EnableIRQ(Timer1_IRQn);															// Permission interrupt from Timer 1
	__enable_irq();																						// Global permission of interrupt
	Timer3_init();																						// Initializing Timer 3
	NVIC_EnableIRQ(Timer3_IRQn);															// Permission interrupt from Timer 3
	Timer3_start();
	MCU_ADC_init();
}
//=========================================================================================================================//
// PD7 button
void Button_PD7_Action()
{
		if((Read_PD7)&&(last_state_PD7 == 0 << 7))							// Reading button PD7
		{
			last_state_PD7 = 1 << 7;															// Change of variable last state button
		}
		else{last_state_PD7 = Read_PD7;}												// Change of variable last state button
}
void Timer3_IRQHandler(void)
{ 																													// Counter increment
	MDR_TIMER3->CNT = 0; 																			// Reset Counter of Timer
	MDR_TIMER3->STATUS = 0;																		// Interrupt reset state
	NVIC_ClearPendingIRQ(Timer3_IRQn);												// Interrupt reset state	
}
//=========================================================================================================================//
int main()
{
	Initialization_All_Function();														//
	uint32_t ch_4_counts = 0;
	
	while(1)
	{
		ADC_set_channel(4);
		ch_4_counts = ADC_read();
		LCD_set_cursor(0);
		LCD_print_text("яркость диспле€: ");
		brightness = (ch_4_counts / 40.95);
		LCD_print_num(brightness);
		LCD_print_text("%");	
		LCD_print_text("  ");	
		MDR_TIMER3->CCR1  =  ch_4_counts;

	}
}
//============================================END_OF_CODE=======================================================================//