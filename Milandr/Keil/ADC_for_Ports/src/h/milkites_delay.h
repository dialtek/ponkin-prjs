#ifndef __MILKITES_DELAY_H__
#define __MILKITES_DELAY_H__

#ifdef	__cplusplus
extern "C"
{
#endif

#define F_CPU 8000000

static __IO uint32_t TimingDelay;

void delay_ms(__IO uint32_t msTime);	

void delay_init(void);

#ifdef	__cplusplus
}
#endif

#endif	/* __MILKITES_DELAY_H__ */