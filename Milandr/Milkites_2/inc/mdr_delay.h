#ifndef __DELAY_H__
#define __DELAY_H__

#ifndef F_CPU
#	error F_CPU must be defined
#endif

static __IO uint32_t TimingDelay;
void Delay_ms(__IO uint32_t nTime);	
	
static __INLINE void SysTickTimer_Init(void)
{
    /// инициализаци€ системного таймера
  
	SysTick->CTRL |= (1<<2) | (0<<1); // источник синхросигнала: HCLK 									  
									  // таймер досчитает до нул€ и  прерывание не возникнет
}

static __INLINE uint8_t SysTickTimer_Set (uint32_t ticks)
{
    
    // регистр Reload - 24 бит, проверка на переполнение
    if (ticks > 0x00FFFFFF)  return (1);           /* Reload value impossible */
	
	SysTick->VAL  = 0;                             /* Load the SysTick Counter Value */
	SysTick->LOAD = ticks;
	
	SysTick->CTRL |= (0<<16) | 1;				   // J,yektybt COUNTFLAG, SysTickTimerStart
	return (0);                                    /* Function successful */
	
/*
ƒл€ формировани€ одиночного прерывани€ после задержки в N тактов процессора 
используетс€ значение N. Ќапример, если требуетс€ прерывание после 400 тактов 
процессора, то устанавливаетс€ RELOAD, равное 400.  
*/
}

void delay_ms(uint16_t delay)
	{
	    for(uint32_t i = 0; i < delay; i++)
		{
			SysTickTimer_Set(F_CPU/1000); // 1 us при HCLK = 80 M
			while(!(SysTick->CTRL & (1<<16)));
		}
	}

void delay_us(uint16_t delay)
	{
	    
		SysTickTimer_Set(20*delay); // 1 us при HCLK = 80 M
		while(!(SysTick->CTRL & (1<<16)));
	}


#endif