/* 
 * File:   opto_controller.h
 * Author: D_LHEP_DESKTOP
 *
 * Created on 24 мая 2019 г., 9:52
 */

#ifndef OPTO_CONTROLLER_H
#define	OPTO_CONTROLLER_H

#ifdef	__cplusplus
extern "C"
{
#endif

void GPIO_init(void);
void OSC_init(void);
void SystemInit(void);
void SendTmeasCmd(void);
void ConfigReset(void);
unsigned int UpdateIDregs(unsigned char);
void RestoreCfg(void);

#ifdef	__cplusplus
}
#endif

#endif	/* OPTO_CONTROLLER_H */

