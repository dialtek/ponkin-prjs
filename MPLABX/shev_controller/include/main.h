/* 
 * File:   main_steppers.h
 * Author: D_LHEP_DESKTOP
 *
 * Created on 5 апреля 2019 г., 11:26
 */

#ifndef MAIN_H
#define	MAIN_H

#ifdef	__cplusplus
extern "C"
{
#endif
	
#define _ISR_PSV __attribute__((__interrupt__, __auto_psv__))
	
#define MOXA_active   LATBbits.LATB0
	
#define POWER_LED     LATCbits.LATC4 
#define MODBUS_LED    LATCbits.LATC3 // LED_485
	
#define ON  1
#define OFF 0

// Dialtek developers code	
#define PONKIN    2U
#define SHIRIKOV  3U
#define DONETS    4U
#define BOGATOV   5U
#define JABIN     6U
#define LETKIN    7U
#define LEUSHIN   8U
	
// IO inputs
#define IN1 PORTAbits.RA0
#define IN2 PORTAbits.RA1	
#define IN3 PORTAbits.RA2
#define IN4 PORTAbits.RA3
#define IN5 PORTAbits.RA4
#define IN6 PORTAbits.RA5	
#define IN7 PORTAbits.RA6
#define IN8 PORTAbits.RA7	
#define IN9  PORTBbits.RB4
#define IN10 PORTBbits.RB5
#define IN11 PORTBbits.RB8
#define IN12 PORTBbits.RB9
	
// IO outputs
#define OUT1 LATEbits.LATE0
#define OUT2 LATEbits.LATE1
#define OUT3 LATEbits.LATE2
#define OUT4 LATEbits.LATE3
#define OUT5 LATEbits.LATE4
#define OUT6 LATEbits.LATE5
#define OUT7 LATEbits.LATE6
#define OUT8 LATEbits.LATE7
#define OUT9 LATFbits.LATF1
#define OUT10 LATFbits.LATF2
#define OUT11 LATFbits.LATF3
#define OUT12 LATFbits.LATF4

// device info	
typedef struct Imuno_t {
	
	unsigned int LineMv;
	unsigned int Heater;
	unsigned int Vibro;
	unsigned int DosingSys;
	unsigned int IO;

} ImunoDevice;

// device info	
typedef struct FirmwareInfo_t {
	
	unsigned int ver;
	unsigned int developer;
    
} FirmwareInfo;


#ifdef	__cplusplus
}
#endif

#endif	/* MAIN_H */

