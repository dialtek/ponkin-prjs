// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef _25K80_UART_H
#define	_25K80_UART_H

#include "link.h"

#ifdef	__cplusplus
extern "C"
{
#endif /* __cplusplus */


void UART_init(unsigned char bd_rate_code);	

void UART_send_byte(unsigned char byte);
	
	
#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* 25k80 UART */

