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
unsigned char char2num (unsigned char ch); // convert char to number

unsigned char num2char (unsigned char ch); // convert number to char

void answer_refresh(void);		   // clear bufs and rx ptr

void init_protocol(unsigned char pump_id);

void init_valve(unsigned char pump_id);	

void init_syringe(unsigned char pump_id);

unsigned int get_syr_pos (unsigned char pump_id);	   // get syringe position

void set_syr_pos(unsigned char pump_id, unsigned int pos); // set syringe position

unsigned int get_syr_vel(unsigned char pump_id);	   // get syringe velocity

void set_syr_vel(unsigned char pump_id, unsigned int vel); // set syringe velocity

unsigned int get_valve_angle (unsigned char pump_id);      // get current valve angle

void set_valve_angle(unsigned char pump_id, unsigned int angle, unsigned int dir);  // set valve angle
/*=========================================================================== */ 
#endif	/* HAMILTON_PUMP_H */

