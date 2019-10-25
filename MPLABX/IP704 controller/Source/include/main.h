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
typedef struct IP704_state_t
{ 
    // status byte fields
    unsigned int ext_control_en; 
    unsigned int charge_en;
    unsigned int ready;
    unsigned int remote_ctrl;
    
    // error byte fields
    unsigned int overheat;
    unsigned int low_supply;
    unsigned int short_circuit;
    unsigned int load_break;
    unsigned int fault;
    unsigned int interlock;
  
} IP704_state; 	

// device info	
typedef struct FirmwareInfo_t {
	
	unsigned int ver;
	unsigned int developer;
    
} FirmwareInfo;

void task_ModbusSM(void *pvParameters);
void task_IP704(void *pvParameters);

#ifdef	__cplusplus
}
#endif

#endif	/* MAIN_H */

