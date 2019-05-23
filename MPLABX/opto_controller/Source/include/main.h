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
	
typedef struct modbus_reg_element_t 
{ 
    unsigned int reg_address; 
    long data;
} modbus_reg_element;

typedef struct Tsensor_t 
{ 
    unsigned int index; 
    unsigned char ID[8];
} Tsensor;

// device info	
typedef struct FirmwareInfo_t {
	
	unsigned int ver;
	unsigned int developer;
    
} FirmwareInfo;

FirmwareInfo FirmInfo;                   // device info struct instance

void GPIO_init(void);
void OSC_init(void);
void SystemInit(void);
void SendTmeasCmd(void);
void ConfigReset(void);
unsigned int UpdateIDregs(unsigned char);
void RestoreCfg(void);
	
void task_GetSensorID(void *pvParameters);
void task_ModbusSM(void *pvParameters);
void task_GetTemp(void *pvParameters);

volatile SemaphoreHandle_t NewSensSemph; // new sensor adding semph

#ifdef	__cplusplus
}
#endif

#endif	/* MAIN_H */

