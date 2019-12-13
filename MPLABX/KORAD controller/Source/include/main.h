#ifndef MAIN_H
#define	MAIN_H

#ifdef	__cplusplus
extern "C"
{
#endif

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
	
// src status & error bytes conent
typedef struct KORAD_state_t
{ 
    // status byte fields
    unsigned int out_state; 
    unsigned int ovp_ocp_mode;
    unsigned int cvcc_mode;
    unsigned int rd_process;
    
    unsigned int pol_relay_1;
    unsigned int pol_relay_2;
  
} KORAD_state; 	

// device info	
typedef struct FirmwareInfo_t {
	
	unsigned int ver;
	unsigned int developer;
    
} FirmwareInfo;

void task_ModbusSM(void *pvParameters);
void task_KORAD(void *pvParameters);

#ifdef	__cplusplus
}
#endif

#endif	/* MAIN_H */

