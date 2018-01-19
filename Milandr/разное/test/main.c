#include "1986be91t1.h" 
#include <stdint.h>

static void MCU_init (){

  RST_CLK->PER_CLOCK = 0xFFFFFFFF;                    // ��������� ������ ���� ���������
  RST_CLK->HS_CONTROL = 0x01;                         // ���. HSE ����������
  while ((RST_CLK->CLOCK_STATUS & (1 << 2)) == 0x00); // ���� ���� HSE ������ � ������� �����
  RST_CLK->PLL_CONTROL = ((1 << 2) | (9 << 8));       // ���. PLL | ����. ��������� = 10
  while((RST_CLK->CLOCK_STATUS & 0x02) != 0x02);      // ���� ����� PLL ������ � ���. �����
  RST_CLK->CPU_CLOCK  = (2                            // �������� ��� CPU_C1
						   |(1 << 2)                      // �������� ��� CPU_C2
						   |(0 << 4)                      // ������������ ��� CPU_C3
						   |(1 << 8));                    // �������� ��� HCLK
}




int main()
{  
  MCU_init();
  PORTD->OE = 0xffff;          // ���� D �� �����
  PORTD->FUNC = 0x0000;        // ������� - ���� 
  PORTD->ANALOG  = 0xffff;     // ����� ����� - ��������
  PORTD->PWR     = 0xFFFFFFFF; //  ����������� ������� ����� ( ������� 10 ��)
  
  PORTC->OE = 0x0000;          // ���� C �� ����
  PORTC->FUNC = 0x0000;        // ������� - ���� 777
  PORTC->ANALOG  = 0xffff;     // ����� ����� - ��������
  PORTC->PWR     = 0x00000000; //  ����������� ������� ����� ( ������� 10 ��)
  
      uint16_t x;
  
      
  
  while(1){
  
    
    
    
    
    
    
    
    /*
    if (!(PORTC->RXTX & (1 << 10))){
    for(x=0;x<100000;x++){}
    if (!(PORTC->RXTX & (1 << 10))){
      PORTD->RXTX = 0xffff;
      for(x=0;x<100000;x++){}
   }
  }
      if ((PORTC->RXTX & (1 << 10))){
      
     PORTD->RXTX = 0x0000;
   }
    */
 }
}
