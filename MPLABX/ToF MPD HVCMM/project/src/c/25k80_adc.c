#include "../h/25k80_adc.h"

void ADC_Init(void)
{
    ADCON0bits.GO_nDONE = 0; // �������������� �� ����������� ���� 0
    
    ADCON0bits.CHS  = 0;  // ��������� ������ ��� � ���. ������ (AN0+)
    ADCON1bits.CHSN = 2;  // ��������� ������ ��� � ���. ������ (AN1+)
    
    ADCON1bits.VCFG = 1;  // ����� �������� ���������� - ext 4,096 V
    ADCON1bits.VNCFG = 1; // External VREF
    
    ADCON2bits.ACQT = 6;  // 20 TAD
    ADCON2bits.ADCS = 1;  // ������� �������������� Fosc/4 
    ADCON2bits.ADFM = 1;  // ���������� � 12-������ ������ ���������� � �������� ���������
    ADCON0bits.ADON = 1;  // ��� ���
}

unsigned int ADC_read(void)
{  
   unsigned int ADC_result = 0;
   
   __delay_us(500);
   GO_nDONE = 1;          // ������ ��������������, ����� �������������� �� ������ ������� � 0
  
   while(GO_nDONE);
   
   ADC_result = (ADRESH << 8) | ADRESL; // ���������� "�����" �������� � �������� ���������
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