#ifndef __DELAY_H__
#define __DELAY_H__

#ifndef F_CPU
#error F_CPU must be defined
#endif

static __IO uint32_t TimingDelay;
void delay_ms(__IO uint32_t msTime);	
void delay_us(__IO uint16_t usTime);	
void delay_init(void);

static __INLINE void delay_init(void)
{
    /// инициализация системного таймера
  
	SysTick->CTRL |= (1<<2) | (0<<1); // источник синхросигнала: HCLK 									  
					  // таймер досчитает до нуля и  прерывание не возникнет
        MDR_RST_CLK->TIM_CLOCK  |= (1 << 25);    // делитель частоты|разрешение тактирования Таймера 2
        MDR_TIMER2->CNTRL = 0x00000000;        	// Режим инициализации таймера, откл
        MDR_TIMER2->CNT   = 0x0000;       	        // Начальное значение счетчика
        MDR_TIMER2->PSG   = 0;                  	// Предделитель частоты = 1
        MDR_TIMER2->ARR   = 65535;                 // Основание счета, прерывание каждые   1 мкс. 
        MDR_TIMER2->IE    = 0x00000000;         	// генерировать прерывание при CNT=ARR
        MDR_TIMER2->STATUS= 0x00000000;               // сбрасываем флаги
        MDR_TIMER2->CNTRL = 0x00000001;;
}

static __INLINE uint8_t SysTickTimer_set (uint32_t ticks)
{
	
    // регистр Reload - 24 бит, проверка на переполнение
    if (ticks > 0x00FFFFFF)  return (1);           /* Reload value impossible */
	
	SysTick->VAL  = 0;                             /* Load the SysTick Counter Value */
	SysTick->LOAD = ticks;
	
	SysTick->CTRL |= (0<<16) | 1;				   // J,yektybt COUNTFLAG, SysTickTimerStart
	return (0);                                    /* Function successful */
	
/*
Для формирования одиночного прерывания после задержки в N тактов процессора 
используется значение N. Например, если требуется прерывание после 400 тактов 
процессора, то устанавливается RELOAD, равное 400.  
*/
}

void __INLINE delay_ms(uint32_t delay)
	{
		  uint32_t i;
	    for(i = 0; i < delay; i++)
		{
			SysTickTimer_set((F_CPU/1000)-1); // 1 ms при HCLK = 80 M
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
