/* 
 * File:   opto_controller.h
 * Author: D_LHEP_DESKTOP
 *
 * Created on 24 мая 2019 г., 9:52
 */

#ifndef IP702_CONTROLLER_H
#define	IP702_CONTROLLER_H

#ifdef	__cplusplus
extern "C"
{
#endif
	
void GPIO_init(void);
void OSC_init(void);
void SystemInit(void);
void RestoreCfg(void);

#ifdef	__cplusplus
}
#endif

#endif	/* IP702_CONTROLLER_H */

