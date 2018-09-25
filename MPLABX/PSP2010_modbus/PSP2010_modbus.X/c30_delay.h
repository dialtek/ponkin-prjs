/*
	delay_us(x) and delay_ms(x) for C30
*/

#ifndef __DELAY_H

	#define FOSC		10000000LL		// clock-frequecy in Hz with suffix LL (64-bit-long), eg. 32000000LL for 32MHz
	#define FCY      	40000000UL      // MCU is running at FCY MIPS

	#define delay_us(x)	__delay32(((x*FCY)/1000000L))	// delays x us
	#define delay_ms(x)	__delay32(((x*FCY)/1000L))		// delays x ms

	#define __DELAY_H	1
	#include <libpic30.h>

#endif
