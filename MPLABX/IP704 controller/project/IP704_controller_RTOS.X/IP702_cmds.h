#ifndef IP702_CMDS_H
#define	IP702_CMDS_H
 
#ifdef	__cplusplus
extern "C"
{
#endif
	
// IP702 commands
#define    begin_CMD     '#'
#define    chargeON_CMD  'C'
#define    chargeOFF_CMD 'D'	
#define    setU_CMD      'U'     
#define    measV_CMD     'A' 
#define    getSets_CMD   'u'
#define    getStatus_CMD 'E'		
	
#define    cmd_lenght1    3
#define    cmd_lenght2    5
#define    SrcAddr	  0xA0		// 160	
	
#define	   ERROR_CODE     65535U	// value on reading error
#define    MAX_VOLTAGE	  1000U		
#define	   SrcReadPeriod  (TickType_t)50
	
// src variables
typedef struct IP704_voltage_t
{ 
    unsigned int read_v; 
    unsigned int set_v;
    
} IP704_voltage; 
	
// заряд/разряд накопительных конденсаторов
unsigned int IP702_SetState(unsigned int state);

// измерения выходного напряжения (выход АЦП)
unsigned int IP702_GetVoltage(void);

// запрос текущего уровня уставки напряжения заряда конденсаторов
unsigned int IP702_GetSets(void);

// чтение статуса и ошибок 
IP704_state* IP702_GetStatus(void);

// установка напряжения
unsigned int IP702_SetVoltage(unsigned int V2set);

#ifdef	__cplusplus
}
#endif

#endif	/* IP702_CMDS_H */

