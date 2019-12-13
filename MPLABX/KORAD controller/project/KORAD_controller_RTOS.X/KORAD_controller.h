#ifndef KORAD_CONTROLLER_H
#define	KORAD_CONTROLLER_H

#ifdef	__cplusplus
extern "C"
{
#endif

#include "d_eeprom.h"
#include "dialtek_modbus.h"
#include "KORAD_cmds.h"
#include "dialtek_uart.h"
	
#define Data2saveLen 8U
	
#define ResetBtn    PORTBbits.RB3 
	
#define Modbus_LED  LATBbits.LATB0 
#define RS232_LED   LATBbits.LATB1 
#define Relay_1_LED TRISBbits.TRISB2 = 0;  LATBbits.LATB2  
#define Relay_2_LED TRISBbits.TRISB9 = 0;  LATBbits.LATB9   
	
#define POL_relay_1 TRISGbits.TRISG12 = 0; LATGbits.LATG12	
#define POL_relay_2 TRISGbits.TRISG13 = 0; LATGbits.LATG13		
	
void GPIO_init(void);
void OSC_init(void);
void SystemInit(void);

unsigned char NewID;
unsigned char EEPR_buf[Data2saveLen];

unsigned int pol_relay_1;
unsigned int pol_relay_2;
    
KORAD_state state_m;
KORAD_params KORAD_m;

FirmwareInfo FirmInfo;          // device info struct instance

#ifdef	__cplusplus
}
#endif

#endif	/* KORAD_CONTROLLER_H */

