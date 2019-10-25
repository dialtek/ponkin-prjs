#ifndef MILKITES_ADC_H
#define	MILKITES_ADC_H

#ifdef	__cplusplus
extern "C"
{
#endif

//------------------------------------------------------------------------------------//
void ADC_init(void);

void ADC_set_ch(uint8_t channel);

void ADC_start_conv(void);

void ADC_stop_conv(void);

uint32_t ADC_read(void);

#ifdef	__cplusplus
}
#endif

#endif	/* MILKITES_ADC_H */
