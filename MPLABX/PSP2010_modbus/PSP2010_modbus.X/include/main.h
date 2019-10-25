/* 
 * File:   main.h
 * Author: D_LHEP_DESKTOP
 *
 * Created on 27 мая 2019 г., 14:23
 */

#ifndef MAIN_H
#define	MAIN_H

#ifdef	__cplusplus
extern "C"
{
#endif
	
#include <p24HJ128GP506.h>
#include <libpic30.h>
	
#define RES_BUT PORTBbits.RB8             // modbus dev id reset btn

#define K1_ON  LATGbits.LATG12 = 1   // K1 relay ON 
#define K1_OFF LATGbits.LATG12 = 0   // K1 relay OFF 

#define POL_RELAY_LED LATBbits.LATB2 // LED_RELAY
#define RS232_TX_LED  LATBbits.LATB3 // LED_TX_232
#define RS232_RX_LED  LATBbits.LATB4 // LED_RX_232

#define POL_CHANGE_1     1    // polarity change cmd code 1 step
#define POL_CHANGE_2     2    // polarity change cmd code 2 step
#define SET_OUTPUT       3    // output state change cmd code
#define NO_CMD_RUNNING   4    // no cmd running state
#define SRC_CMD          5    // all src cmds
#define IDLE             6

#define READ_TIMEOUT     100   

#define _ISR_PSV __attribute__((__interrupt__, __auto_psv__))
	
volatile unsigned char uart2_rx_buf[40];
volatile unsigned char rx_msg[40];
volatile unsigned char uart2_rx_ptr;

#ifdef	__cplusplus
}
#endif

#endif	/* MAIN_H */

