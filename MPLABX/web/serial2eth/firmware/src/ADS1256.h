/* 
 * File:   ADC1256.h
 * Author: ADM
 *
 * Created on 22 апреля 2020 г., 11:41
 */

#ifndef ADC1256_H
#define	ADC1256_H

#ifdef	__cplusplus
extern "C"
{
#endif

// ADC

// ADC1256 Register map
#define STATUS 0x00     
#define MUX 0x01 
#define ADCON 0x02
#define DRATE 0x03
#define IO 0x04
#define OFCO 0x05
#define OFC1 0x06
#define OFC2 0x07
#define FSCO 0x08
#define FSC1 0x09
#define FSC2 0x0A
#define uV 10000000  // для калибровки 
//#define uV 100000 // по умолчанию
#define mV 1000

#define SET_CH      10
#define GET_CH_DATA 20
	
#define ADC_MAX_RANGE 6U	
#define ADC_MAX_SPS   11U
	
#define CURR_SRC_VAL 100.0           // divider for 10 uA current module

 unsigned char RdReg(unsigned char RegName);
 
 void WrReg(unsigned char RegName, unsigned char CommandByte);

 void ADCs_change_SPS(unsigned int SPS);
  
// настройка и инициализация АЦП
 void ADC_set_SPS(unsigned char SPS);

 unsigned int ADCs_get_SPS(void);
 
 void ADCs_change_PGA(unsigned int PGA);
 
 unsigned int ADCs_get_PGA(void);
  
 void ADC_set_PGA(unsigned char _PGA_val);

 void ADC_SelfCal();

 void ADCs_init(unsigned char buf_state);
 
//---------------------- уст. каналов и чтение АЦП --------------------------//

 void ADC_sync(unsigned char state);

 void ADC_select(unsigned char command);

 void ADCx_setCh(unsigned char ADCx, unsigned char CHx);

 signed long ADC_read(unsigned char ADC_number);

 signed long ADCx_read_aver(unsigned char ADCx, unsigned char CHx);

 void ADC_par_rd_ch(signed long *ADC1_ArrPtr, signed long *ADC2_ArrPtr);
 
 unsigned int ADCs_meas_ready(void);
 
  unsigned int ADCs_get_CurrMeasCh(void);
 
#ifdef	__cplusplus
}
#endif

#endif	/* ADC1256_H */

