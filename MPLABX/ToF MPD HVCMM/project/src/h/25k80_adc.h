// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef _25K80_ADC_H
#define	_25K80_ADC_H

#include "link.h"

#ifdef	__cplusplus
extern "C"
{
#endif /* __cplusplus */


void ADC_Init(void);	

unsigned int ADC_read(void);

unsigned int ADC_read_aver(unsigned long aver_size);

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* 25k80 ADC */

