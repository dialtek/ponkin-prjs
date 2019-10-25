#include "MDR32Fx.h"   
#include "stdint.h"
#include "milkites_display.h"

/*--------------Прототипы функций-----------------------------------*/
void print_time(int line, int hour, int min, int sec);
void print_mesure_limit(int line, int ch_4_counts, float limit);
void print_pixel(int set_cursor, int column_set, int wr_byte);
void LCD_wr_pixel(int set_column, int num_pixel);
/*------------------------------------------------------------------*/

/*-----------------Функция вывода времени на дисплей----------------*/
void print_time(int line, int hour, int min, int sec)
{

 LCD_set_cursor(line);
	LCD_print_text("      ");
	if (hour < 10)
	{
	  LCD_print_text("0");
		LCD_print_num(hour);
	}
	else
	{
	 LCD_print_num(hour);
	}
	LCD_print_text(":");
	if(min < 10)
	{
	 	LCD_print_text("0");
		LCD_print_num(min);
	}
	else
	{
	 LCD_print_num(min);
	}
	LCD_print_text(":");
	if(sec < 10)
	{
	 	LCD_print_text("0");
		LCD_print_num(sec);
	}
	else
	{
	 LCD_print_num(sec);
	}
}
/*----------------------------------------------------------------*/

/*------Функция измерения напряжения до введенного предела--------*/
void print_mesure_limit(int line, int ch_4_counts, float limit)
{	
	
  float Uiz = 0.00f; // для хранения результатов измерения
	float Uop = 3.3; // опорное напряжение
	int Nraz = 4096; // количество значений АЦП
	int Uizdr = 0; // для хранения дробной части
	
	Uiz = (Uop*ch_4_counts)/Nraz; // перевод в вольты
  Uizdr = Uiz*1000 - (int)Uiz*1000; // выделение значений после запятой
		
	LCD_set_cursor(line); // установка курсора дисплея
  LCD_print_text("Voltage = "); // вывод текста
  LCD_print_num(Uiz); // вывод целой части результатов АЦП в вольтах
  LCD_wr_char('.'); // вывод символа
	LCD_print_num(Uizdr); // вывод дробной части результатов АЦП в вольтах
  delay_ms(150);
	
	// оповещение пользователя морганием светодиодов и выводом сообщения на дисплей
	if(Uiz >= limit) 
	 {
	   MDR_PORTA->RXTX = 0xff;
		 delay_ms(100);
		 MDR_PORTA->RXTX = 0x00;
		 delay_ms(100);
		 
		 LCD_set_cursor(2); // установка курсора дисплея
     LCD_print_text(" LIMIT IS EXCEEDED!!!"); // вывод текста: "ЛИМИТ ПРЕВЫШЕН!!!"
	 }
	  else 
		 {
		  LCD_clear();
		 }
}

void print_pixel(int set_cursor, int column_set, int wr_byte)
	{
	 LCD_set_cursor(set_cursor); //установка строки на дисплее(0 - 7)
	 LCD_column_set(column_set); // в пределах строки (0 - 127)
	 LCD_wr_byte(wr_byte); // 
	}
	
	void LCD_wr_pixel(int set_column, int num_pixel)
	{
	  LCD_column_set(set_column);
		
	  int wr_pixel = 0;
	  int coeff = 0;
		
	 for(int n = 0; n <= 7; n++)
		{ /*Отслеживание положение сроки, в зависимости от введеннного значения (0...64)*/
        if (num_pixel <= 8)                   {coeff = 0;  LCD_page_set(0); }
			 	if (num_pixel <= 16 & num_pixel > 8)  {coeff = 1;  LCD_page_set(1); }
			 	if (num_pixel <= 24 & num_pixel > 16) {coeff = 2;  LCD_page_set(2); }
			 	if (num_pixel <= 32 & num_pixel > 24) {coeff = 3;  LCD_page_set(3); }
			 	if (num_pixel <= 40 & num_pixel > 32) {coeff = 4;  LCD_page_set(4); }
			 	if (num_pixel <= 48 & num_pixel > 40) {coeff = 5;  LCD_page_set(5); }
			 	if (num_pixel <= 56 & num_pixel > 48) {coeff = 6;  LCD_page_set(6); }
			 	if (num_pixel <= 64 & num_pixel > 56) {coeff = 7;  LCD_page_set(7); }
			 
	/*Введение коэффициента для сопоставления вводимого значения и значения выводимого на дисплей*/
			   if (num_pixel - 8*coeff == 1) wr_pixel = 0x01;//1
				 if (num_pixel - 8*coeff == 2) wr_pixel = 0x02;//2
				 if (num_pixel - 8*coeff == 3) wr_pixel = 0x04;//4
				 if (num_pixel - 8*coeff == 4) wr_pixel = 0x08;//8
				 if (num_pixel - 8*coeff == 5) wr_pixel = 0x10;//16
				 if (num_pixel - 8*coeff == 6) wr_pixel = 0x20;//32
				 if (num_pixel - 8*coeff == 7) wr_pixel = 0x40;//64
				 if (num_pixel - 8*coeff == 8) wr_pixel = 0x80;//128
	   }
		 LCD_wr_byte(wr_pixel);
	
	}
