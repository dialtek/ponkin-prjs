//Project Name: ADC_for_Ports (lab)
//------------------------------------------------------------------------------------//
#include "MDR32Fx.h"   
#include "milkites_delay.h"
#include "milkites_display.h"
#include "milkites_adc.h"
#include "milkites_i2c.h"
#include "tlv493d.h"
#include "pwm_step_motor.h"

#include <MDR32F9Qx_port.h>
#include <MDR32F9Qx_rst_clk.h>

#define Rs 0.1 
#define k 200.0 

 void OSC_init ( void ){
     //??????????? ????? ??? ?????? Flash-?????? ????????
  MDR_RST_CLK->HS_CONTROL = 0x01;// ???. HSE ?????????? (??????? ?????? 8 ???)
	while ((MDR_RST_CLK->CLOCK_STATUS & 0x04) != 0x04);     // ???? ???? HSE ?????? ? ??????? ?????
	MDR_RST_CLK->PLL_CONTROL = ((1 << 2) | (7 << 8)); 	  // ???. PLL | ????. ????????? = 2

	while((MDR_RST_CLK->CLOCK_STATUS & 0x02) != 0x02);      // ???? ????? PLL ?????? ? ???. ?????

	MDR_RST_CLK->CPU_CLOCK  = (2                           // ???????? ??? CPU_C1 - HSE
							 |(1 << 2)                      // ???????? ??? CPU_C2 - PLLCPUo 
							 |(1 << 4)                      // ???????????? ??? CPU_C3 - CPU_C2
							 |(1 << 8));                    // ???????? ??? HCLK

	 
	   MDR_RST_CLK->PER_CLOCK = 0xffffffff; 					// вкл. тактирования всей периферии МК
	 
}//void CPU_init
 
//------------------------------------------------------------------------------------//
// Initializing Timer3
void Timer3_init(void)
{
	MDR_RST_CLK->TIM_CLOCK |= (1 << 26);   										// Clocking of the Timer1
//	MDR_RST_CLK->TIM_CLOCK |= 0b000; 													// Frequency devider - 1:1
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




void Timer3_start(void)
{
	MDR_TIMER3 -> CNTRL = 1; 																	// Timer1 start
}


int main()
{

	uint32_t ch_2_counts = 0, ch_3_counts = 0, ch_5_counts = 0, ch_6_counts = 0; 										// переменная результата преобразования АЦП
  MDR_RST_CLK->PER_CLOCK = 0xffffffff; 					// вкл. тактирования всей периферии МК
	//OSC_init();
	delay_init(); 																// инициализация системы задержек
	
	MDR_PORTE->OE = 0xff37; 											// биты 7,6,3 PORTE - входы (кнопки), др. - выходы
	MDR_PORTE->FUNC = 0x0000; 										// функция - порт, основная функция
	MDR_PORTE->PWR = 0xff37; 											// макс. быстрый фронт
	MDR_PORTE->ANALOG = 0xffff; 									// режим работы порта - цифровой ввод/вывод
	
	MDR_PORTA->OE = 0xffff; 											// биты 7,6,3 PORTE - входы (кнопки), др. - выходы
	MDR_PORTA->FUNC = 0x0000; 										// функция - порт, основная функция
	MDR_PORTA->PWR = 0xffff; 											// макс. быстрый фронт
	MDR_PORTA->ANALOG = 0xffff; 									// режим работы порта - цифровой ввод/вывод
	
//	MDR_PORTC->OE|=4;
//	MDR_PORTC->FUNC 	|= 1<<6;
//	MDR_PORTC->ANALOG = 0;
//	MDR_PORTC->PWR 		|= 3<<4;
	
	
    MDR_PORTC->OE = 0x4;     //??????????? ???????? ?????? - ????? ( PC: 2  )
    MDR_PORTC->ANALOG = 0x4;     //????? ?????? ??????????? - ???????? ( PC: 2  )
    MDR_PORTC->FUNC   = 0x0; 
    MDR_PORTC->PD   = (0x0 << 16) | (0x0);     //????? ?????? ???????
    MDR_PORTC->PWR   = 0x20; 
		
	
	MDR_PORTD->OE &=~ 	0x6C; 									  // настройка PD2, PD3, PD5, PD6 на вход, каналы 2, 3, 5 АЦП
	MDR_PORTD->ANALOG &=~ 	0x6C; 							  // перевод PD2, PD3, PD5, PD6 в аналоговый режим работы
	MDR_PORTD->PULL |= 	0x6C;										  // Подтяжка PD2, PD3, PD5, PD6 к нулю
	
	MCU_ADC_init(); 															// инициализация АЦП МК
	 
	I2C_Init();
	TLV493D_init();

	PORTB_Init();																	// по русски!

	LCD_init(); 																	// инициализация дисплея
	LCD_clear(); 																	// очистка дисплея
	LCD_led_en; 															    // вкл. подсветки дисплея

	Timer3_init();
	Timer3_start();
	
	//MDR_PORTC->RXTX &= ~1 << 2; // com light
	MDR_PORTE->RXTX &= ~1; 		 // heater off
	MDR_PORTE->RXTX |= 1; 		 // heater on
	
	STEP_DISABLE();
	STEPPER_SPEED(1);
	
	DIR_RIGHT();
	
  TLV493D_reset();
	//MDR_TIMER3->CCR1 = 32;
	
	while (1)
	{

		read_all_TLV493D('x','y','z');
	  
//		RGB('R', 1);
//	  delay_ms(500);
//		RGB('R', 0);
//		
//		RGB('G', 1);
//	  delay_ms(500);
//		RGB('G', 0);
//		
//		RGB('B', 1);
//	  delay_ms(500);
//		RGB('B', 0);
		
		// I heater
		MCU_ADC_set_ch(2); 													// уст. канала АЦП
		ch_2_counts = MCU_ADC_read(); 							// чтение 4 канала АЦП
		LCD_set_cursor(0);												  // установка курсора дисплея
		LCD_print_text("Ih - ch 2 = "); 							// вывод текста
		LCD_print_num(ch_2_counts); 								// вывод результатов АЦП в отсчетах
		LCD_print_text("  "); 											// очистка поля вывода
	  //------------------------
		// I light
		MCU_ADC_set_ch(3);
		ch_3_counts = MCU_ADC_read();
		LCD_set_cursor(1);
		LCD_print_text("Il - ch 3 = ");
		LCD_print_num(ch_3_counts);
		LCD_print_text("  ");
		//------------------------
		// I milky
		MCU_ADC_set_ch(5);
		ch_5_counts = MCU_ADC_read();
		LCD_set_cursor(2);
		LCD_print_text("Im - ch 5 = ");
		LCD_print_num( (int32_t) ( (((float)ch_5_counts*0.0008) / (Rs * k)) * 1000) );
		LCD_print_text("  ");
	  //------------------------
		// T sensor
		MCU_ADC_set_ch(6);
		ch_6_counts = MCU_ADC_read();
		LCD_set_cursor(3);
		LCD_print_text("Ts - ch 6 = ");
		LCD_print_num( (int32_t) ( (((float)ch_6_counts-500.0)*0.0008) / 0.0195) );
		LCD_print_text("  ");
		
	} 
} 