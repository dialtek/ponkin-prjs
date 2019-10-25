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

	 
	   MDR_RST_CLK->PER_CLOCK = 0xffffffff; 					// ���. ������������ ���� ��������� ��
	 
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

	uint32_t ch_2_counts = 0, ch_3_counts = 0, ch_5_counts = 0, ch_6_counts = 0; 										// ���������� ���������� �������������� ���
  MDR_RST_CLK->PER_CLOCK = 0xffffffff; 					// ���. ������������ ���� ��������� ��
	//OSC_init();
	delay_init(); 																// ������������� ������� ��������
	
	MDR_PORTE->OE = 0xff37; 											// ���� 7,6,3 PORTE - ����� (������), ��. - ������
	MDR_PORTE->FUNC = 0x0000; 										// ������� - ����, �������� �������
	MDR_PORTE->PWR = 0xff37; 											// ����. ������� �����
	MDR_PORTE->ANALOG = 0xffff; 									// ����� ������ ����� - �������� ����/�����
	
	MDR_PORTA->OE = 0xffff; 											// ���� 7,6,3 PORTE - ����� (������), ��. - ������
	MDR_PORTA->FUNC = 0x0000; 										// ������� - ����, �������� �������
	MDR_PORTA->PWR = 0xffff; 											// ����. ������� �����
	MDR_PORTA->ANALOG = 0xffff; 									// ����� ������ ����� - �������� ����/�����
	
//	MDR_PORTC->OE|=4;
//	MDR_PORTC->FUNC 	|= 1<<6;
//	MDR_PORTC->ANALOG = 0;
//	MDR_PORTC->PWR 		|= 3<<4;
	
	
    MDR_PORTC->OE = 0x4;     //??????????? ???????? ?????? - ????? ( PC: 2  )
    MDR_PORTC->ANALOG = 0x4;     //????? ?????? ??????????? - ???????? ( PC: 2  )
    MDR_PORTC->FUNC   = 0x0; 
    MDR_PORTC->PD   = (0x0 << 16) | (0x0);     //????? ?????? ???????
    MDR_PORTC->PWR   = 0x20; 
		
	
	MDR_PORTD->OE &=~ 	0x6C; 									  // ��������� PD2, PD3, PD5, PD6 �� ����, ������ 2, 3, 5 ���
	MDR_PORTD->ANALOG &=~ 	0x6C; 							  // ������� PD2, PD3, PD5, PD6 � ���������� ����� ������
	MDR_PORTD->PULL |= 	0x6C;										  // �������� PD2, PD3, PD5, PD6 � ����
	
	MCU_ADC_init(); 															// ������������� ��� ��
	 
	I2C_Init();
	TLV493D_init();

	PORTB_Init();																	// �� ������!

	LCD_init(); 																	// ������������� �������
	LCD_clear(); 																	// ������� �������
	LCD_led_en; 															    // ���. ��������� �������

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
		MCU_ADC_set_ch(2); 													// ���. ������ ���
		ch_2_counts = MCU_ADC_read(); 							// ������ 4 ������ ���
		LCD_set_cursor(0);												  // ��������� ������� �������
		LCD_print_text("Ih - ch 2 = "); 							// ����� ������
		LCD_print_num(ch_2_counts); 								// ����� ����������� ��� � ��������
		LCD_print_text("  "); 											// ������� ���� ������
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