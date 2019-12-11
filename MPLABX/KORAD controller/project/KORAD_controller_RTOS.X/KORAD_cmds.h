#ifndef KORAD_CMDS_H
#define	KORAD_CMDS_H
 
#ifdef	__cplusplus
extern "C"
{
#endif
		
#define    cmd_lenght1    3
#define    cmd_lenght2    5
#define    SrcAddr	  0xA0		// 160	
	
#define	   ERROR_CODE     65535U	// value on reading error
#define    MAX_VOLTAGE	  1000U		
#define	   SrcReadPeriod  (TickType_t)50
	
// src variables
typedef struct KORAD_params_t
{ 
    unsigned int meas_v; 
    unsigned int set_v;
    
    unsigned int meas_i; 
    unsigned int set_i;
    
} KORAD_params; 

// converts char symbol into number
unsigned char char2num(unsigned char ch);

// converts number into char symbol
unsigned char num2char(unsigned char ch);

// ��������� ��������� ����������
unsigned int KORAD_GetVoltage(void);

// ������ �������� ������ ������� ����������
unsigned int KORAD_GetVSets(void);

// ��������� ����������
void KORAD_SetVoltage(unsigned int V2set);

// ��������� ��������� ����
unsigned int KORAD_GetCurrent(void);

// ������ ������� ������� ����
unsigned int KORAD_GetISets(void);

// ��������� ����������
void KORAD_SetCurrent(unsigned int I2set);

// ������ �������
KORAD_state* KORAD_GetStatus(void);

// ��������� ��������� ������
void KORAD_SetState(unsigned int state);

#ifdef	__cplusplus
}
#endif

#endif	/* KORAD_CMDS_H */

