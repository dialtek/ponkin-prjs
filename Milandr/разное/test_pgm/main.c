#include "MDR32Fx.h"

int main()
{
  
//---CLK-----------------------------------------------------------------------------------------------------
  MDR_RST_CLK->PER_CLOCK = 0xFFFFFFFF;                    // ���. ������������ ���� ���������
  MDR_RST_CLK->HS_CONTROL = 0x01;                         // ���. HSE ���������
  while ((MDR_RST_CLK->CLOCK_STATUS & (1 << 2)) == 0x00); // ���� ���� HSE ������ � ������� �����
  
  
  MDR_RST_CLK->PLL_CONTROL = ((1 << 2) | (0 << 8)); 	  // ���. PLL | ����. ��������� = 1
  					
  while((MDR_RST_CLK->CLOCK_STATUS & 0x02) != 0x02);      // ���� ����� PLL ������ � ���. �����

  MDR_RST_CLK->CPU_CLOCK  = (2                            // �������� ��� CPU_C1
						   |(1 << 2)                      // �������� ��� CPU_C2
						   |(1 << 4)                      // ������������ ��� CPU_C3
						   //|(1 << 4)                    // ������������ ��� CPU_C3
						   |(1 << 8));                    // �������� ��� HCLK
 
  MDR_PORTC->OE = 0xffff;               // ���� A �� �����
  MDR_PORTC->FUNC = 0x0000;             // ������� - ���� 
  MDR_PORTC->ANALOG  = 0xffff;          // ����� ����� - ��������
  MDR_PORTC->PWR     = 0xFFFFFFFF;      // ����������� ������� ����� ( ������� 10 ��)
  
  while (1) {
	
	MDR_PORTC->RXTX = 0xFFFF;
  
  }

}
