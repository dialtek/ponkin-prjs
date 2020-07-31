#include "../h/25k80_adc.h"

void ADC_Init(void)
{
    ADCON0bits.GO_nDONE = 0; // Преобразования не выполняются пока 0
    
    ADCON0bits.CHS  = 0;  // Установка канала АЦП в диф. режиме (AN0+)
    ADCON1bits.CHSN = 2;  // Установка канала АЦП в диф. режиме (AN1+)
    
    ADCON1bits.VCFG = 1;  // Выбор опорного напряжения - ext 4,096 V
    ADCON1bits.VNCFG = 1; // External VREF
    
    ADCON2bits.ACQT = 6;  // 20 TAD
    ADCON2bits.ADCS = 1;  // частота преобразований Fosc/4 
    ADCON2bits.ADFM = 1;  // заполнение в 12-битный ргистр начинается с младшего полубайта
    ADCON0bits.ADON = 1;  // Вкл АЦП
}

unsigned int ADC_read(void)
{  
   unsigned int ADC_result = 0;
   
   __delay_us(500);
   GO_nDONE = 1;          // Начало преобразования, после преобразований он скинет регистр в 0
  
   while(GO_nDONE);
   
   ADC_result = (ADRESH << 8) | ADRESL; // Возвращаем "сумму" старшего и младшего полубайта
   PIR1bits.ADIF = 0;
   
   return ADC_result;
}

unsigned int ADC_read_aver(unsigned long aver_size)
{
    unsigned long ADC_aver = 0;
    
    for(unsigned int i = 0; i < aver_size; i++)
        ADC_aver += (unsigned long)ADC_read();
    
    return (unsigned int)(ADC_aver/aver_size);
}