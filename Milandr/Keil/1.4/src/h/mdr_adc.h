#ifndef MDR_ADC_H
#define	MDR_ADC_H

#ifdef	__cplusplus
extern "C"
{
#endif

//------------------------------------------------------------------------------------//
void MCU_ADC_init(uint8_t ch);

void MCU_ADC_set_ch(uint8_t channel);

void MCU_ADC_start_conv(void);

void MCU_ADC_stop_conv(void);

uint32_t MCU_ADC_read(void);

#ifdef	__cplusplus
}
#endif

#endif	/* MDR_ADC_H */
