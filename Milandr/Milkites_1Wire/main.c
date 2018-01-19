//// ���� ���������: 14.04.15
//
#include "MDR32Fx.h"

#define F_CPU  80000000 // HCLK frequency

#include "mdr_delay.h"
#include "mdr_spi.h"
#include "MT_12864B_abc.h"

#define right_b (!(MDR_PORTB->RXTX & (1<<10))) 
#define up_b    (!(MDR_PORTB->RXTX & (1<<8)))
#define left_b  (!(MDR_PORTB->RXTX & (1<<9)))
#define down_b  (!(MDR_PORTD->RXTX & (1<<4))) 

	void OSC_init(void){

  //---CLK-----------------------------------------------------------------------------------------------------
  MDR_RST_CLK->PER_CLOCK = 0xFFFFFFFF;                    // ���. ������������ ���� ���������
  MDR_RST_CLK->HS_CONTROL = 0x01;                         // ���. HSE ���������
  while ((MDR_RST_CLK->CLOCK_STATUS & (1 << 2)) == 0x00); // ���� ���� HSE ������ � ������� �����
  MDR_RST_CLK->PLL_CONTROL = ((1 << 2) | (7 << 8)); 	  // ���. PLL | ����. ��������� = 7
  									  // 7 ��� ������ 10 ���
  									  // 9 ��� ������ 8 ���
  while((MDR_RST_CLK->CLOCK_STATUS & 0x02) != 0x02);      // ���� ����� PLL ������ � ���. �����

  MDR_RST_CLK->CPU_CLOCK  = (2                            // �������� ��� CPU_C1
						   |(1 << 2)                      // �������� ��� CPU_C2
						   |(1 << 4)                      // ������������ ��� CPU_C3
						   |(1 << 8));                    // �������� ��� HCLK
 
  // HCLK = 80 ���
  
  }
   
	void GPIO_init (void){  
  
  MDR_PORTA->OE      = 1 | (1<<5) | (1<<7);      // ���� A1 - ����, A0,A5,A6 �� �����
  MDR_PORTA->FUNC    = 0x0000;          // ������� - ���� 
  MDR_PORTA->ANALOG  = 0xffff;          // ����� ����� - ��������
  MDR_PORTA->PWR     = 0xFFFFFFFF;      // ����������� ������� ����� ( ������� 10 ��)
  //---------------------------------------------------------------------------//
  MDR_PORTB->OE = 0xf8bf;               // ���� B �� �����, PB6 - UART1 RX + ������ SB..
  MDR_PORTB->FUNC = 0x0000;             // ������� - ���� 
  MDR_PORTB->ANALOG  = 0xffff;          // ����� ����� - ��������
  MDR_PORTB->PWR     = 0xFFFFFFFF;      // ����������� ������� ����� ( ������� 10 ��)
  //---------------------------------------------------------------------------//  
  MDR_PORTC->OE      = 0xFFFF;
  //MDR_PORTC->OE      = 0x0000;   		// LCD_A0 ��� �� �����
  MDR_PORTC->FUNC    = 0x0000;          // ������� - ���� 
  MDR_PORTC->ANALOG  = 0xffff;          // ����� ����� - ��������
  MDR_PORTC->PWR     = 0xFFFFFFFF;      // ����������� ������� ����� ( ������� 10 ��)
  //---------------------------------------------------------------------------//
  MDR_PORTD->OE = 0x0000;               // ���� D �� ����, PD4 - LCD_reset
  MDR_PORTD->FUNC = 0x0000;             // ������� - ���� 
  MDR_PORTD->ANALOG  = 0xffff;          // ����� ����� - ��������
  MDR_PORTD->PWR     = 0xFFFFFFFF;      // ����������� ������� ����� ( ������� 10 ��)
  //---------------------------------------------------------------------------//
  MDR_PORTE->OE = 0xffff;               // ���� E �� �����
  MDR_PORTE->FUNC = 0x0000;             // ������� - ���� 
  MDR_PORTE->ANALOG  = 0xffff;          // ����� ����� - ��������
  MDR_PORTE->PWR     = 0xFFFFFFFF;      // ����������� ������� ����� ( ������� 10 ��)
  //---------------------------------------------------------------------------//
  MDR_PORTF->OE = 0xffff;               // ���� D �� �����, ������ SSP1 
  MDR_PORTF->FUNC = (2 << 6) |			// �����  ����� 1, 2, 3, 4 ����� 
					(2 << 4) |			// - ��������������, ������������ ������ SSP1
					(2 << 2) |
					(2 << 0);

  MDR_PORTF->ANALOG  = 0xffff;          // ����� ����� - ��������
  MDR_PORTF->PWR     = 0xFFFFFFFF;      // ����������� ������� ����� ( ������� 10 ��)
   }
 
	void MCU_init (void) {
	  
 	 OSC_init();
	 SysTickTimer_Init();
 	 GPIO_init();  
  	 MDR32_SSP1_init();
	}

/*=========================================================================== */
	int main()							  
{
  const uint8_t pic1 [6][66] =
  { 
	0xFE, 0xFE, 0xFF, 0x03, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x03, 0x03, 0x03, 0x03, 0x03, 0x07, 0x07, 0x3E, 0xFC, 0xF8, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0xF8, 0x18, 0x18, 0x18, 0x18, 0xD8, 0xD8, 0xD8, 0xD8, 0xD8, 0xD8, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0xF8, 0xF8, 0x10, 0x00, 0x00, 0x00, 
	0x01, 0xFF, 0xFF, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 0xF0, 0xF8, 0xF8, 0xF8, 0xF0, 0xE0, 0x00, 0x00, 0x00, 0x01, 0xFF, 0xFF, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x07, 0x07, 0x07, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x1F, 0xFF, 0xF0, 0x00, 0x00, 
	0x00, 0x1F, 0x1F, 0x1F, 0x1E, 0x1C, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0x39, 0x39, 0x39, 0x39, 0x39, 0x38, 0x38, 0x38, 0x38, 0x38, 0x3F, 0x1F, 0x1F, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x0F, 0x0C, 0x0C, 0x0C, 0x0C, 0x0E, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x0C, 0x0C, 0x0C, 0x0F, 0x0F, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0xE0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF8, 0xF8, 0xF8, 0xF8, 0xF8, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0x7C, 0x7C, 0x7C, 0x7C, 0x7C, 0x7C, 0x7C, 0x7C, 0x7C, 0x7C, 0x7C, 0x7C, 0x7C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x78, 0x78, 0xF8, 0xF0, 0xF0, 0xF0, 0xE0, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x3F, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7C, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x7F, 0xFF, 0xDF, 0xFF, 0xF0, 
	0x00, 0x00, 0x00, 0x00, 0x0F, 0x0F, 0x1F, 0x1C, 0x1C, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x0F, 0x0F, 0x0F, 0x0E, 0x0E, 0x0E, 0x0C, 0x0F, 0x0F, 0x0C, 0x0F, 0x0F, 0x0F, 0x0F, 
};
  
const uint8_t pic2 [6][65] =
{                                                                                            
	0x04, 0xFE, 0xFC, 0x0C, 0x0C, 0x8C, 0x8C, 0xCC, 0xEC, 0xEC, 0xEC, 0xCC, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0xFC, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFE, 0xFF, 0x03, 0x03, 0x03, 0xF3, 0xFB, 0xFB, 0xFB, 0xFB, 0xFB, 0xFB, 0xFB, 0xFB, 0xFB, 0xFB, 0xFB, 0xFB, 0x03, 0x03, 0x03, 0x03, 0x3F, 0xFF, 0xE2, 0x00, 0x00, 0x00, 
	0x00, 0xFF, 0xFF, 0xC0, 0xC0, 0xC3, 0xC7, 0xC7, 0xC7, 0xC7, 0xC3, 0xC3, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC1, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x80, 0x80, 0x80, 0x8F, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xC0, 0xC0, 0xC0, 0x80, 0x80, 0x83, 0xFF, 0xFE, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0xFC, 0xFE, 0xFE, 0xFE, 0x7E, 0x1E, 0x1E, 0x1E, 0x1E, 0x1E, 0x1E, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x07, 0x07, 0x07, 0x87, 0xC7, 0xC7, 0xC7, 0xC7, 0xC7, 0xC7, 0xC7, 0xC7, 0xC7, 0xC7, 0xC7, 0x87, 0x07, 0x07, 0x07, 0x0F, 0x0F, 0xFF, 0xFE, 0xFE, 0xFE, 0xFC, 0xE0, 0x00, 
	0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x87, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x8F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xE0, 0xC0, 0xC0, 0xC0, 0x80, 0xFF, 0xFF, 0x8F, 0xFF, 0xFB, 0xFF, 0xFE, 
	0x00, 0x00, 0x00, 0x01, 0x01, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 
};




  
  int delay = 10;

 MCU_init();		// ������������ ������� ������������,
  					// ������� GPIO, SPI
 LCD_init();
 LCD_Clear();
 
 uint8_t coord_x = 0;
 uint8_t coord_y = 0;
 
 while(1)
  {	
	LCD_page_Adr_set(0); 	// ���. ���������� Y  
	LCD_Column_Adr_set(0); // ���. ���������� X 
	
	for(uint8_t p=0; p<6; p++) 
	{
  		LCD_page_Adr_set(p);
  		LCD_Column_Adr_set(0);
		
		for(uint8_t i=0; i<65; i++) 
		{
			LCD_Wr_Data(pic2[p][i]);
		}
	}
	
	LCD_page_Adr_set(0); 	// ���. ���������� Y  
	LCD_Column_Adr_set(0); // ���. ���������� X
	
	delay_ms(200);
	LCD_Clear();
	  
	for(uint8_t p=0; p<6; p++) 
	{
  		LCD_page_Adr_set(p);
  		LCD_Column_Adr_set(0);
		
		for(uint8_t i=0; i<65; i++) 
		{
			LCD_Wr_Data(pic1[p][i]);
		}
	}
	
  delay_ms(200);
  LCD_Clear();
  
//	delay_ms(20);
//	LCD_Clear();	
//	
//	LCD_page_Adr_set(coord_y); 	// ���. ���������� Y  
//	LCD_Column_Adr_set(coord_x); // ���. ���������� X 
//
//
//	for(int i =0; i < 8; i++) // ���� �� 8 ��������
//	{
//		LCD_Wr_Data(0xff);	 // 8 ��� ����� 8 ��������
//	}						 // �� ������������� ������
//							 // ����� 255	
//  
//	if(right_b)
//	{
//		coord_x += 8; // coord_x = coord_x + 8
//		delay_ms(30);
//	}
//	
//	if(left_b)
//	{
//		coord_x -= 8;; // coord_x++
//		delay_ms(30);
//	}
//	
//	if(up_b)
//	{   
//	    if(coord_y != 0)
//		{
//	   		coord_y--;
//			delay_ms(30);
//		}
//		
//	}
//	
//	if(down_b)
//	{
//		coord_y++;
//		delay_ms(30);
//	}
//	
//	if(coord_x >= 120)
//	{
//		coord_x = 120;
//	}

  }
}
 
 
/* 
 
	LCD_set_cursor(1);
	for(uint8_t i = 0; i < 64; i++)
	{
	  LCD_Wr_Data(1);
	}
	for(uint8_t i = 0; i < 64; i++)
	{
	  LCD_Wr_Data(2);
	}
	
	LCD_set_cursor(2);
	LCD_Wr_num(12345,5);
	
	LCD_set_cursor(4);
	for(uint8_t i = 0; i < 16; i++)
	{
	  LCD_Wr_Data(i);
	}
	
	LCD_print("  ");
	for(uint8_t i = 0; i < 8; i++)
	{
	  LCD_Wr_Data(0xaa);
	  LCD_Wr_Data(0xff);
	}
	
	LCD_print("  ");
	for(uint8_t i = 0; i < 16; i++)
	{
	  LCD_Wr_Data(0xff);
	}
	
	LCD_print(" ");
	for(uint8_t i = 0; i < 16; i++)
	{
	  LCD_Wr_Data(0x81);
	}
	
	LCD_print(" ");
	for(uint8_t i = 0; i < 8; i++)
	{
	  LCD_Wr_Data(i/2);
	}
	
	for(uint8_t i = 8; i != 0; i--)
	{
	  LCD_Wr_Data(i/2);
	}
	
	LCD_set_cursor(6);
	LCD_print(":D -> >> ? ! - ");
	
	delay_ms(100);

   }
  }	

*/