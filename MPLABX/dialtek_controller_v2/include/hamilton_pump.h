/* 
 * File:   hamilton_pump.h
 * Author: D_LHEP_DESKTOP
 *
 * Created on 29 но€бр€ 2018 г., 10:13
 */
#include "xc.h"
#include "dialtek_uart.h"

#ifndef HAMILTON_PUMP_H
#define	HAMILTON_PUMP_H
/*=========================================================================== */ 
#define PUMP_TX_EN  LATFbits.LATF13 = 1  
#define PUMP_TX_DIS LATFbits.LATF13 = 0 
#define ERROR_CODE 65535  // value on reading error
#define default_id (unsigned char)1

#define CMD_get_syr_pos     (unsigned int)200
#define CMD_get_syr_vel     (unsigned int)201
#define CMD_get_valve_angle (unsigned int)202
#define CMD_set_syr_pos     (unsigned int)203
#define CMD_set_syr_vel     (unsigned int)204
#define CMD_set_valve_angle (unsigned int)205

// cmds struct
//typedef struct PSD4cmd_t
//{ 
//    unsigned int init_protocol;      
//    unsigned int init_valve; 
//    unsigned int init_syringe; 
//    
//    unsigned int get_syr_pos; 
//    unsigned int set_syr_pos; 
//    
//    unsigned int get_syr_vel;     
//    unsigned int set_syr_vel;
//    
//    unsigned int get_valve_angle;
//    unsigned int set_valve_angle;
//    
//} PSD4cmds;

// HAMILTON PUMP   
//void PSD4_struct_init(PSD4cmds cmd);

// start/stop async delay timer
void TmOutTimer_state(unsigned int state);

// T2/3 - async delay timer set
void TmOutTimer_set(unsigned int ms);
 
// T2/3 - async delay timer
void TmOutTimer_init(void);

void _ISR_PSV _T5Interrupt(void);

unsigned char char2num (unsigned char ch); // convert char to number

unsigned char num2char (unsigned char ch); // convert number to char

unsigned int check_cmd_answer(unsigned char index_1); // check the answer to a cmd 

void answer_refresh(void);		   // clear bufs and rx ptr

unsigned int init_protocol(unsigned char pump_id);

unsigned int init_valve(unsigned char pump_id);	

unsigned int init_syringe(unsigned char pump_id);

unsigned int get_syr_pos (unsigned char pump_id);	   // get syringe position

unsigned int rd_syr_pos(void);

unsigned int set_syr_pos(unsigned char pump_id, unsigned int pos); // set syringe position

unsigned int rd_syr_vel(void);

void get_syr_vel(unsigned char pump_id);	   // get syringe velocity

unsigned int set_syr_vel(unsigned char pump_id, unsigned int vel); // set syringe velocity

unsigned int rd_valve_angle(void);

void get_valve_angle (unsigned char pump_id);      // get current valve angle

unsigned int set_valve_angle(unsigned char pump_id, unsigned int angle, unsigned int dir);  // set valve angle

/*=========================================================================== */ 
#endif	/* HAMILTON_PUMP_H */

