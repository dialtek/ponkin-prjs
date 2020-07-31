// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef LINK_H
#define	LINK_H

#define _XTAL_FREQ 40000000

#include "xc.h"
#include "25k80_uart.h"
#include "25k80_adc.h"
#include "dialtek_modbus.h"

#define LED_ON  LATBbits.LATB4 = 1
#define LED_OFF LATBbits.LATB4 = 0

#define MX_EN	LATCbits.LATC3 = 1
#define MX_DIS	LATCbits.LATC3 = 0

#define ADC_ZERO_LVL 62U

#endif	/* LINK_H */
