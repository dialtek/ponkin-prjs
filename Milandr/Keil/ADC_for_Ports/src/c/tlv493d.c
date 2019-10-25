
#include "MDR32Fx.h"   
#include "stdint.h"
#include "milkites_I2C.h"
//#include "GPIO.h"
#include "milkites_display.h"
#include "tlv493d.h"

/*==========================================================*/
 void TLV493D_reset(){
    I2C_Start();
    I2C_Send_Byte(0x00); 
    I2C_Stop();
}


 void TLV493D_init(void){
	  
	 /* ----------------------------------Переменные------------------------------------*/
	  uint8_t Fact_Set_7H_Reg = 0; // Bits 6:3 must be written into register 1H in case of write.
	  uint8_t Fact_Set_8H_Reg = 0; // Bits 7:0 must be written into register 2H in case of write.
	  uint8_t Fact_Set_9H_Reg = 0; // Bits 4:0 must be written into register 3H in case of write.
	 
	 /*----------------------------------------------------------------------------------*/
	 /* Чтение заводских настроек */
	   I2C_Start();
	   I2C_Send_Addr(0xbc);
	   I2C_Send_Addr(0x00);
	   I2C_Send_Addr(0x3);
	  	 
	   I2C_Start();
	   I2C_Send_Addr(0xbd);
	 
	   I2C_GetData();
	   I2C_GetData();
	   I2C_GetData();
	 
	   I2C_GetData();
	   I2C_GetData();
	   I2C_GetData();
		
		 I2C_GetData();
	 
	   Fact_Set_7H_Reg = I2C_GetData();
	   Fact_Set_8H_Reg = I2C_GetData();
		 Fact_Set_9H_Reg = I2C_GetData();
		 I2C_NACK();
		 I2C_Stop();
		 /*------------------------------------------------------------------------*/
		 /* Процесс записи считанных байтов */
		 I2C_Start();
			I2C_Send_Addr(0xbc);
			
	   I2C_Send_Byte(0x00);
	 	 I2C_Send_Byte(0 << 7|           // 0000 11011
	                0 << 5 |
		((Fact_Set_7H_Reg & 0x18) << 3)|
                  0 << 2 |
                  1 << 1 |
                       1);
                                
										 
	 	I2C_Send_Byte(Fact_Set_8H_Reg); //0
	 
	 	I2C_Send_Byte(1 << 7|  //1100 0000
	                1 << 6|
								  0 << 5|
		(Fact_Set_9H_Reg & 0x1f));
		
		 I2C_Stop();
		/*--------------------------------------------------------------------------*/ 
 }
 
 


 float TLV493D_calc_field (uint8_t nibble_h, uint8_t nibble_l){
      // расчет величины магнитного поля по оси X датчика
      // nibble_h - MSB, nibble_l содержит младший полубайт данных оси Х
         
      int16_t fi = 0;          // для хранения отсчетов магнитного поля
      float fl = 0;        // для хранения магнитного поля в Гс
      
      fi = (nibble_h << 4) | nibble_l;
      if ( fi >= 2048)   fi = fi - 4096;  // Interpret bit 12 as +/- 
      
      // LSB = 0.098 mT -> 0.98 Gs
      fl = fi * 0.098;    // перевод из отсчетов АЦП в mT
      fl *= 10;           // перевод из mT в Гауссы
      
      return fl;
  }
 
	

 void read_all_TLV493D(char X, char Y,char Z){
		
		uint8_t xh = 0;
	  uint8_t yh = 0;
	  uint8_t zh = 0;  // ст. байты данных
    uint8_t xl = 0, yl = 0, zl = 0;  // мл. полубайты
    uint8_t bz2 = 0, bx2by2 = 0, frame_ctr = 0;
	
		float x  = 0, y = 0, z = 0;
		float kx = 0.65, ky = 0.65, kz = 0.65;
		
//			 
			 
	/*=====================================================================================*/	
		 I2C_Start();
	   I2C_Send_Addr(0xbc);
	   I2C_Send_Addr(0x00);
	   I2C_Send_Addr(0x3);
	  	 
	   I2C_Start();
	   I2C_Send_Addr(0xbd);
	 
	   xh = I2C_GetData();
	   yh = I2C_GetData();
	   zh = I2C_GetData();
	 
	   frame_ctr = I2C_GetData();
	   bx2by2 = I2C_GetData();
	   bz2 = I2C_GetData();
		
		 I2C_GetData();
	 
	   I2C_GetData();
	   I2C_GetData();
		 I2C_GetData();
		 I2C_NACK();
		 I2C_Stop();
		 
     xl = bx2by2 >> 4;
		 yl = bx2by2 & 0x0f;
		 zl = bz2 & 0x0f;
			
		 x = (int16_t)(kx*TLV493D_calc_field(xh, xl));    // передача в функцию ст. и мл. байт для расчета поля по X
     y = (int16_t)(ky*TLV493D_calc_field(yh, yl));    // передача в функцию ст. и мл. байт для расчета поля по Y
     z = (int16_t)(kz*TLV493D_calc_field(zh, zl));    // передача в функцию ст. и мл. байт для расчета поля по Z
			
		 //x_dr = x*100 - (int)x*100;
			
			if (X == 'x'){
				
			if (x < 0){
				 
			 LCD_set_cursor(5);
			 LCD_column_set(0);
		//	 LCD_wr_char('-');
		  // LCD_column_set(10);
			 LCD_print_num(x);
				LCD_print_text("  "); 
				LCD_column_set(35);
				 LCD_print_text("Gs");
 			// LCD_wr_char('.'); 
	    // LCD_print_num(x_dr); 
			 } 
				else{
			 LCD_set_cursor(6);
       LCD_column_set(0);
    	 LCD_wr_char('+');
			// LCD_column_set(10);
			 LCD_print_num(x);
					LCD_print_text("  "); 
						LCD_column_set(35);
					 LCD_print_text("Gs");
			// LCD_wr_char('.'); 
	    // LCD_print_num(x_dr);
				}					
			} // if X == x	 
			
			if (Y == 'y'){
				if (y < 0){
				 
			 LCD_set_cursor(7);
			 LCD_column_set(0);
			// LCD_wr_char('-');
		  // LCD_column_set(10);
			 LCD_print_num(y);
					LCD_print_text("  "); 
					LCD_column_set(35);
					 LCD_print_text("Gs");
			 } 
				else{
			 LCD_set_cursor(5);
       LCD_column_set(0);
			 LCD_wr_char('+');
			// LCD_column_set(10);
			 LCD_print_num(y);
					LCD_print_text("  "); 
					LCD_column_set(35);
					 LCD_print_text("Gs");
				}					
			} // if Y == y
			
			if (Z == 'z'){
				if (z < 0){
				 
			 LCD_set_cursor(6);
			 LCD_column_set(0);
			// LCD_wr_char('-');
		 //  LCD_column_set(10);
			 LCD_print_num(z);
					LCD_print_text("  "); 
					LCD_column_set(35);
					 LCD_print_text("Gs");
			 } 
				else{
			 LCD_set_cursor(7);
       LCD_column_set(0);
			 LCD_wr_char('+');
			// LCD_column_set(10);
			 LCD_print_num(z);
					LCD_print_text("  "); 
					LCD_column_set(35);
			 LCD_print_text("Gs");
				}					
			} // if Z == z	
	}