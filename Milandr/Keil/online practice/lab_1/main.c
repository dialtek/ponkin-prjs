//Project Name: lab_1 - current measurements
//------------------------------------------------------------------------------------//

#include "MDR32Fx.h"   
#include "milkites_delay.h"
#include "milkites_display.h"
#include "milkites_adc.h"

#define Rs 0.1 
#define k 200.0 

int main()
{

	uint32_t ch_2_counts = 0, ch_3_counts = 0, ch_5_counts = 0, ch_6_counts = 0; 										// ���������� ���������� �������������� ���
	delay_init(); 																// ������������� ������� ��������
	
	MDR_PORTE->OE = 0xff37; 											// ���� 7,6,3 PORTE - ����� (������), ��. - ������
	MDR_PORTE->FUNC = 0x0000; 										// ������� - ����, �������� �������
	MDR_PORTE->PWR = 0xff37; 											// ����. ������� �����
	MDR_PORTE->ANALOG = 0xffff; 									// ����� ������ ����� - �������� ����/�����
	
	MDR_PORTA->OE = 0xffff; 											// ���� 7,6,3 PORTE - ����� (������), ��. - ������
	MDR_PORTA->FUNC = 0x0000; 										// ������� - ����, �������� �������
	MDR_PORTA->PWR = 0xffff; 											// ����. ������� �����
	MDR_PORTA->ANALOG = 0xffff; 									// ����� ������ ����� - �������� ����/�����
	
	
	MDR_PORTD->OE &=~ 	0x6C; 									  // ��������� PD2, PD3, PD5, PD6 �� ����, ������ 2, 3, 5 ���
	MDR_PORTD->ANALOG &=~ 	0x6C; 							  // ������� PD2, PD3, PD5, PD6 � ���������� ����� ������
	MDR_PORTD->PULL |= 	0x6C;										  // �������� PD2, PD3, PD5, PD6 � ����
	
	ADC_init(); 															// ������������� ��� ��

	LCD_init(); 																	// ������������� �������
	LCD_clear(); 																	// ������� �������
	LCD_led_en; 															    // ���. ��������� �������
	
	MDR_PORTC->RXTX = 1 << 2; // com light


  
	while (1)
	{
		
		uint32_t current; 				// �������� ���������� current
	 	
		ADC_set_ch(5);					  // ��������� ������ ���
		current = ADC_read(); 		// ���������� ����������� ��������� � ����������
		
		
		
		
		
		
//		LCD_set_cursor(1);
//		LCD_print_text("Il - ch 3 = ");
//		LCD_print_num(ch_3_counts);
//		LCD_print_text("  ");
//		//------------------------
//		// I milky
//		MCU_ADC_set_ch(5);
//		ch_5_counts = MCU_ADC_read();
//		LCD_set_cursor(2);
//		LCD_print_text("Im - ch 5 = ");
//		LCD_print_num( (int32_t) ( (((float)ch_5_counts*0.0008) / (Rs * k)) * 1000) );
//		LCD_print_text("  ");
	} 
} 