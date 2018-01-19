#include <Milandr\1986be9x.h>
      unsigned long x;
//#pragma vector=14
__irq void Timer1_IRQHandler( void )
//void Timer1_IRQHandler(void) //������� ��������� ���������� irq
{
//void Timer1_IRQHandler(){

     PORTD->RXTX = 0x0000;
     for(x=0;x<3000000;x++){}
     TIMER1->CNT = 0x00000000;      // ��������� ����. �������� �� 0
     TIMER1->STATUS &= ~(1 << 1);   // ����� ������� ���������� �� ������� 1
     NVIC_ClearPendingIRQ(Timer1_IRQn); // ����� ����� ���������� �� ������� 1
 
}

int main()
{
//---CLK-----------------------------------------------------------------------------------------------------
  RST_CLK->PER_CLOCK = 0xFFFFFFFF;                    // ��������� ������ ���� ���������
  RST_CLK->HS_CONTROL = 0x01;                         // ���. HSE ����������
  while ((RST_CLK->CLOCK_STATUS & (1 << 2)) == 0x00); // ���� ���� HSE ������ � ������� �����
  RST_CLK->PLL_CONTROL = ((1 << 2) | (9 << 8));       // ���. PLL | ����. ��������� = 10
  while((RST_CLK->CLOCK_STATUS & 0x02) != 0x02);      // ���� ����� PLL ������ � ���. �����

  RST_CLK->CPU_CLOCK  = (2                            // �������� ��� CPU_C1
						   |(1 << 2)                      // �������� ��� CPU_C2
						   |(0 << 4)                      // ������������ ��� CPU_C3
						   |(1 << 8));                    // �������� ��� HCLK

  PORTD->OE = 0xffff;      // ���� D �� �����
  PORTD->FUNC = 0x0000;    // ������� - ���� 
  PORTD->ANALOG  = 0xffff; // ����� ����� - ��������
  PORTD->PWR     = 0xFFFFFFFF;   // ����������� ������� ����� ( ������� 10 ��)
  
  //0x4002_0000  MDR_RST_CLK  ���������� �������� �������
  
 
  
  RST_CLK->TIM_CLOCK = (1<<24);  // ���������� �������� ������� �� TIM1                                  // �������� �������� ������� TIM1_CLK == HCLK/128   
  TIMER1->CNTRL = 0x00; // ����������� ������ ��������� ��������
  TIMER1->CNT = 0x00;   // ��������� �������� ��������
  TIMER1->PSG = 25;    // ������� ������� �� f = TIM_CLK/(PSG+1);
  TIMER1->ARR = 0x0F;   // ��������� ����� ��������
  TIMER1->IE = 2;       // ���� ���������� ���������� �� ������� ���������� CNT � ARR
  TIMER1->STATUS = 0x00000000; // �������� ��� �����
  NVIC_EnableIRQ(Timer1_IRQn); // ���������� ���������� ��� ������� 1
  __enable_irq(); // Enable Interrupts
  //TIMER1->CNTRL = 1; // �������� ������ 1
  // timer 1 0x4007_0000 
  // PORTD 0x400C_0000 
  
  PORTC->OE = 0x0000;          // ���� C �� ����
  PORTC->FUNC = 0x0000;        // ������� - ���� 777
  PORTC->ANALOG  = 0xffff;     // ����� ����� - ��������
  PORTC->PWR     = 0x00000000; //  ����������� ������� ����� ( ������� 10 ��)

  while(1){
   
  if (!(PORTC->RXTX & (1 << 10))){
    for(x=0;x<100000;x++){}
    if (!(PORTC->RXTX & (1 << 10))){
      PORTD->RXTX = 0xffff;
      for(x=0;x<100000;x++){}
      TIMER1->CNTRL = 1; // �������� ������ 1
   }
  }
    
    
    
    
    
    
    //PORTD->RXTX = 0xffff;
    //for(x=0;x<3000000;x++){}
    /*
    PORTD->RXTX = 1<<10;
    for(x=0;x<3000000;x++){}
    PORTD->RXTX = 0<<10;
    for(x=0;x<3000000;x++){}
    */
    
    
  
  }
}
