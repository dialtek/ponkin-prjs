#ifndef PBF_MODULE_H
#define	PBF_MODULE_H

#ifdef	__cplusplus
extern "C"
{
#endif
	
//======================== USER FUNCS ===========================//
#define	_HSEBYP	0   // 0 - режим осциллятора, 1 - режим внешнего генератора
#define	_HSEON  1	  // 0 - выключен, 1 - включен

// measured counts to clean I conversion
uint16_t CalcCurrent(uint16_t V_meas, uint16_t Imeas);

void OSC_init(void);

void GPIO_init (void);

void T1_init(void);

void T2_init(void);

// DAC
void MCU_DAC2_init (void);

//===============================================================//
#ifdef	__cplusplus
}
#endif

#endif	/* PBF_MODULE_H */