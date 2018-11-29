/* 
 * File:   hamilton_pump.h
 * Author: D_LHEP_DESKTOP
 *
 * Created on 29 но€бр€ 2018 г., 10:13
 */
#include "xc.h"

#ifndef HAMILTON_PUMP_H
#define	HAMILTON_PUMP_H
/*=========================================================================== */ 
#define PUMP_TX_EN  LATFbits.LATF13 = 1  
#define PUMP_TX_DIS LATFbits.LATF13 = 0 
#define ERROR_CODE 65535  // value on reading error

// HAMILTON PUMP   
unsigned char char2num (unsigned char ch);

unsigned char num2char (unsigned char ch);

void answer_refresh(void);

void pump_init_protocol(unsigned char pump_id);

void pump_init_valve(unsigned char pump_id);

void pump_init_syringe(unsigned char pump_id);

unsigned int pump_get_pos (unsigned char pump_id);

void pump_set_pos(unsigned char pump_id, unsigned int pos);

/*=========================================================================== */ 
#endif	/* HAMILTON_PUMP_H */

