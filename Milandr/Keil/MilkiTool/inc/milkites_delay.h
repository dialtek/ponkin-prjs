#ifndef __DELAY_H__
#define __DELAY_H__

#ifndef F_CPU
#error F_CPU must be defined
#endif

static __IO uint32_t TimingDelay;
void delay_ms(__IO uint32_t msTime);	
void delay_us(__IO uint16_t usTime);	

static __INLINE void delay_init(void)
{
    /// ������������� ���������� �������
  
	SysTick->CTRL |= (1<<2) | (0<<1); // �������� �������������: HCLK 									  
					  // ������ ��������� �� ���� �  ���������� �� ���������
        MDR_RST_CLK->TIM_CLOCK  |= (1 << 25);    // �������� �������|���������� ������������ ������� 2
        MDR_TIMER2->CNTRL = 0x00000000;        	// ����� ������������� �������, ����
        MDR_TIMER2->CNT   = 0x0000;       	        // ��������� �������� ��������
        MDR_TIMER2->PSG   = 0;                  	// ������������ ������� = 100
        MDR_TIMER2->ARR   = 65535;                 // ��������� �����, ���������� ������   1 ���. 
        MDR_TIMER2->IE    = 0x00000000;         	// ������������ ���������� ��� CNT=ARR
        MDR_TIMER2->STATUS= 0x00000000;               // ���������� �����
        MDR_TIMER2->CNTRL = 0x00000001;;
}

static __INLINE uint8_t SysTickTimer_Set (uint32_t ticks)
{
	
    // ������� Reload - 24 ���, �������� �� ������������
    if (ticks > 0x00FFFFFF)  return (1);           /* Reload value impossible */
	
	SysTick->VAL  = 0;                             /* Load the SysTick Counter Value */
	SysTick->LOAD = ticks;
	
	SysTick->CTRL |= (0<<16) | 1;				   // J,yektybt COUNTFLAG, SysTickTimerStart
	return (0);                                    /* Function successful */
	
/*
��� ������������ ���������� ���������� ����� �������� � N ������ ���������� 
������������ �������� N. ��������, ���� ��������� ���������� ����� 400 ������ 
����������, �� ��������������� RELOAD, ������ 400.  
*/
}

void __INLINE delay_ms(uint32_t delay)
	{
	    for(uint32_t i = 0; i < delay; i++)
		{
			SysTickTimer_Set((F_CPU/1000)-1); // 1 ms ��� HCLK = 80 M
			while(!(SysTick->CTRL & (1<<16)));
		}
	}

 void __INLINE delay_us(uint16_t us)
{

 MDR_TIMER2->CNT = 0;
 us *= 79;
 while((MDR_TIMER2->CNT) <= us) {  }
}
 

#endif