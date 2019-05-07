/* 
 * File:   main.h
 * Author: PONKIN
 *
 * Created on 29 апреля 2019 г.
 */

#ifndef MAIN_H
#define	MAIN_H

#ifdef	__cplusplus
extern "C"
{
#endif

#define FCY 40000000UL	
#define FP 40000000
	
#define BAUDRATE 115200
#define U1BRGVAL ((FP/BAUDRATE)/16)-1
	
#define _ISR_PSV __attribute__((__interrupt__, __auto_psv__))

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

// device info	
typedef struct FirmwareInfo_t {
	
	unsigned int ver;
	unsigned int developer;
    
} FirmwareInfo;


void OSC_init(void);
void GPIO_init();


#ifdef	__cplusplus
}
#endif

#endif	/* MAIN_H */

