//Project name: PWM_for_Ports (Lab)//
//=========================================================================================================================//
#include "MDR32Fx.h"                  										  // Device header
#define   F_CPU 8000000																		// Clock frequency
#include "milkites_delay.h"																	// Library of delay
#include "milkites_display.h"																// Library of display
#define LCD_led_en 		MDR_PORTE->RXTX |= (1 << 2) 				  // Illumination is ON
#define LCD_led_dis		MDR_PORTE->RXTX &= ~(1 << 2) 				  // Illumination is OFF
float brightness = 0;
int state_A = 0xAA;
//=========================================================================================================================//
// Initialization of use ports
void Ports_initialization()
{
	MDR_PORTE->OE			= 0b1111111100110111;										// Bytes 7, 6, 3 are input
	MDR_PORTE->FUNC 	= 0x0000;																// Function is Port, Basic function
	MDR_PORTE->PWR		= 0xFF37;																// The fastest front 
	MDR_PORTE->ANALOG	= 0xFFFF;																// Operation mode - I/O
	
	MDR_PORTA->OE 		= state_A;															// All pins are output
	MDR_PORTA->FUNC		= ((10 << 2)|(10 << 4));								// Function is port
	MDR_PORTA->ANALOG	= 0xFFFF;																// Operation mode - I/O
	MDR_PORTA->PWR		= state_A;															// The fastest front
	
	MDR_PORTC->OE 		= 0b100;
	MDR_PORTC->FUNC 	= 0b100000;
	MDR_PORTC->ANALOG = 0b000;
	MDR_PORTC->PWR 		= 0b110000;
	
}
/*=========================================================================================================================*/
// Initializing Timer3
void Timer3_init(void)
{
	MDR_RST_CLK->TIM_CLOCK |= (1 << 26);   										// Clocking of the Timer1
	MDR_RST_CLK->TIM_CLOCK |= 0b000; 													// Frequency devider - 1:1
	MDR_TIMER3->CNTRL = 0x00000041;				 										// Mode is up and down
	MDR_TIMER3->PSG = 100;														  			// Frequency devider
	MDR_TIMER3->ARR = 511;								 							  		// CNT + 1 = 1000
	MDR_TIMER3->CNT = 0;									 										// Start value
	MDR_TIMER3->CH1_CNTRL1 = (2 << 2)|1;
	MDR_TIMER3->CCR2 = 0;
	MDR_TIMER3->CH1_CNTRL = 6 << 9;
	
	MDR_TIMER3->CH1_CNTRL1 = (2 << 2)|1;
	MDR_TIMER3->CH1_CNTRL = 6 << 9;
}
/*=========================================================================================================================*/
// Starting Timer 3
void Timer3_start(void)
{
	MDR_TIMER3 -> CNTRL = 1; 																	// Timer1 start
}
//=========================================================================================================================//
int main()
{
	MDR_RST_CLK->PER_CLOCK = 0xFFFFFFFF;											// Clocking of all periphery
	Ports_initialization();																		// Initializing ports settings
	delay_init();																					  	// Initializing delay library
	LCD_init();																								// Initializing display library
	LCD_clear();																							// Cleaning display
	LCD_led_en;																								// Illumination is enable
	Timer3_init();																						// Initializing Timer 3
	Timer3_start();
	
	while(1)
	{
		LCD_set_cursor(0);
		LCD_print_text("Подсветка");
		MDR_PORTC->RXTX = 1 << 2;
		for(uint16_t i = 0; i < 511; i++)
		{
			MDR_TIMER3->CCR1 = i;
			delay_ms(10);
			LCD_set_cursor(1);
			LCD_print_num(i);
		}
//		for(uint16_t i = 511; i > 0; i--)
//		{
//			MDR_TIMER1->CCR1 = i;
//			delay_ms(10);
//		}
//		for(uint16_t i = 0; i < 511; i++)
//		{
//			MDR_TIMER1->CCR2 = i;
//			delay_ms(10);
//		}
//		for(uint16_t i = 511; i > 0; i--)
//		{
//			MDR_TIMER1->CCR2 = i;
//			delay_ms(10);
//		}
	}
}
//============================================END_OF_CODE=======================================================================//