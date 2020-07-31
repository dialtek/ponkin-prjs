#ifndef D_DELAY_H
#define	D_DELAY_H
 
#ifdef	__cplusplus
extern "C"
{
#endif
/*=========================================================================== */	
// Timer 8 - delay timer
void TIMER8_delay_init (void);

volatile void delay_us(unsigned long us_delay);

volatile void delay_ms(unsigned int ms_delay);
// delays
/*=========================================================================== */
#ifdef	__cplusplus
}
#endif

#endif	/* D_DELAY_H */

