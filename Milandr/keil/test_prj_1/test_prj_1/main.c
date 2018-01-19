#define F_CPU 80000000

#include "MDR32Fx.h"
//#include "MDR32F9Qx_config.h"
#include "milkites_delay.h"
#include "milkites_spi.h"
#include "MT_12864B_LCD.h"

void OSC_init(void) {   // ������� ������������� ������� ������������ ��
  
  // ���. PLL | ����. ��������� = 7
  MDR_RST_CLK->PLL_CONTROL = ((1 << 2) | (7 << 8)); 
  // ���� ����� PLL ������ � ���. �����	 
  while((MDR_RST_CLK->CLOCK_STATUS & 0x02) != 0x02);      
  
  MDR_RST_CLK->HS_CONTROL = 0x01;                         // ���. ��������� HSE
  while ((MDR_RST_CLK->CLOCK_STATUS & (1 << 2)) == 0x00); // ���� ����������
  
  MDR_RST_CLK->CPU_CLOCK  =(2                // �������� ��� CPU_C1
                            |(1 << 2)        // �������� ��� CPU_C2
                            |(1 << 4)        // ������������ ��� CPU_C3
                            |(1 << 8));      // �������� ��� HCLK  
 MDR_RST_CLK->PER_CLOCK = 0xFFFFFFFF; // ���. ������������ ���� ���������
 // HCLK = 80 ���	  
  }




void GPIO_init (void) { // ������� ������������� ������ �����/������
  
  MDR_PORTA->OE      = 0xFFFF;
  MDR_PORTA->FUNC    = 0x0000;          // ������� - ���� 
  MDR_PORTA->ANALOG  = 0xFFFF;          // ����� ����� - ��������
  MDR_PORTA->PWR     = 0xFFFFFFFF;      // ����������� ������� ����� 

  MDR_PORTC->OE      = 0xFFFF;
  MDR_PORTC->FUNC    = 0x0000;          // ������� - ���� 
  MDR_PORTC->ANALOG  = 0xFFFF;          // ����� ����� - ��������
  MDR_PORTC->PWR     = 0xFFFFFFFF;      // ����������� ������� ����� 

  MDR_PORTF->OE      = 0xFFFF;          // ���� F �� �����, ������ SSP1 
  MDR_PORTF->FUNC = (2 << 6) |		// �����  ����� 1, 2, 3, 4 ����� 
                    (2 << 4) |          // - ��������������, ������������  SSP1
                    (2 << 2) |
                    (2 << 0);
  MDR_PORTF->ANALOG  = 0xFFFF;          // ����� ����� - ��������
  MDR_PORTF->PWR     = 0xFFFFFFFF;      // ����������� ������� �����
  
  MDR_PORTB->OE      = 0x0000;
  MDR_PORTB->FUNC    = 0x0000;          // ������� - ���� 
  MDR_PORTB->ANALOG  = 0xFFFF;          // ����� ����� - ��������
  MDR_PORTB->PWR     = 0xFFFFFFFF;      // ����������� ������� �����   
  
  MDR_PORTD->OE = 0x00ca;               // ���� D �� ����, PD2 - ADC_CH2, PD4 - ADC_CH4, PD5 - ADC_CH5
  MDR_PORTD->FUNC = 0x0000;             // ������� - ���� 
  MDR_PORTD->ANALOG  = 0xffcb;          // ����� ����� - ��������, �� PD2 - ADC_CH2, PD4 - ADC_CH4, PD5 - ADC_CH5
  MDR_PORTD->PWR     = 0xFFFFFFFF;      // ����������� ������� ����� ( ������� 10 ��)
  //MDR_PORTD->PD =     ((0 << (2 << 16))); //����� ������ ����� 2 = ���
  
  MDR_PORTE->OE      = 0xFFFF;
  MDR_PORTE->FUNC    = 0x0000;          // ������� - ���� 
  MDR_PORTE->ANALOG  = 0xFFFF;          // ����� ����� - ��������
  MDR_PORTE->PWR     = 0xFFFFFFFF;      // ����������� ������� ����� 
}

/*=========================================================================== */

int main()
{
	int x = 0;
	int counter = 0;
	
	OSC_init();
	GPIO_init();
	SysTickTimer_init();
	
	MDR32_SSP1_init();    // ������������� ������ SSP1

  LCD_init(); 					// ������������ ������� MT12864B
  LCD_clear(); 	        // ������� �������
  LCD_set_cursor(0);    // ���. ������� � 0�� ���. 

while(1)
{
	MDR_PORTA->RXTX = 1<<x;
	delay_ms(200);
	x++;
	if(x > 7) x = 0;
	
	LCD_set_cursor(3);
	LCD_print("���� ������! ���������!!");
  LCD_wr_num(counter);
  counter++;
  delay_ms(100);
}
}

