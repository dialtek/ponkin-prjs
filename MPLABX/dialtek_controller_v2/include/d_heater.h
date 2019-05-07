/* 
 * File:   main_heater.h
 * Author: D_LHEP_DESKTOP
 *
 * Created on 25 апреля 2019 г., 11:04
 */

#ifndef D_HEATER_H
#define	D_HEATER_H

#ifdef	__cplusplus
extern "C"
{
#endif

/*============================= ONE WIRE ===================================== */
// 1- wire 
#define MAX_T         80U               // MAX heater temperature - 80 degrees
#define HEATER_LED    LATCbits.LATC2    // heater LED 
#define HEATER        LATGbits.LATG6    // heater ctrl  
/*=========================================================================== */	
// sensor struct
typedef struct Tsensor_t 
{ 
    unsigned int index; 
    unsigned char ID[8];
} Tsensor;
// Heater struct
typedef struct xHeater_t 
{ 
    unsigned int state;       // 0 - idle, 1 - heating in prigess
    unsigned int sensorIndex; // sensor used to ctrl heater
    unsigned int SetT;       // T sets <= MAX_T
    unsigned int CurrT; 
    unsigned int hysteresis; 
    unsigned int enable;     
} xHeater;
/*=========================================================================== */

// OW timing timer
void Timer32_init(void);

// check if the sensor was added earlier
unsigned char MatchSensorID(void);

// search and add the new OW sensor
unsigned int AddNewSensor(unsigned int RegisterValue);

// reset config to default
void ConfigReset(void);

void UpdateIDregs(void);

void GetSensorsTemp(void);

// start/stop OW SM timer
void OWtimerState(unsigned int state);

// One wire sensors read state machine
void OWstateMachine(void);

// Restore One wire sensors ID from memory
void OWrestoreCfg(void);

unsigned int GetSensorsQty(void);

#ifdef	__cplusplus
}
#endif

#endif	/* D_HEATER_H */
/*=========================================================================== */
