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

	uint32_t ch_2_counts = 0, ch_3_counts = 0, ch_5_counts = 0, ch_6_counts = 0; 										// переменная результата преобразования АЦП
	delay_init(); 																// инициализация системы задержек
	
	MDR_PORTE->OE = 0xff37; 											// биты 7,6,3 PORTE - входы (кнопки), др. - выходы
	MDR_PORTE->FUNC = 0x0000; 										// функция - порт, основная функция
	MDR_PORTE->PWR = 0xff37; 											// макс. быстрый фронт
	MDR_PORTE->ANALOG = 0xffff; 									// режим работы порта - цифровой ввод/вывод
	
	MDR_PORTA->OE = 0xffff; 											// биты 7,6,3 PORTE - входы (кнопки), др. - выходы
	MDR_PORTA->FUNC = 0x0000; 										// функция - порт, основная функция
	MDR_PORTA->PWR = 0xffff; 											// макс. быстрый фронт
	MDR_PORTA->ANALOG = 0xffff; 									// режим работы порта - цифровой ввод/вывод
	
	
	MDR_PORTD->OE &=~ 	0x6C; 									  // настройка PD2, PD3, PD5, PD6 на вход, каналы 2, 3, 5 АЦП
	MDR_PORTD->ANALOG &=~ 	0x6C; 							  // перевод PD2, PD3, PD5, PD6 в аналоговый режим работы
	MDR_PORTD->PULL |= 	0x6C;										  // Подтяжка PD2, PD3, PD5, PD6 к нулю
	
	ADC_init(); 															// инициализация АЦП МК

	LCD_init(); 																	// инициализация дисплея
	LCD_clear(); 																	// очистка дисплея
	LCD_led_en; 															    // вкл. подсветки дисплея
	
	MDR_PORTC->RXTX = 1 << 2; // com light


  
	while (1)
	{
		
		uint32_t current; 				// создание переменной current
	 	
		ADC_set_ch(5);					  // установка канала АЦП
		current = ADC_read(); 		// сохранение результатов измерений в переменную
		
		
		
		
		
		
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