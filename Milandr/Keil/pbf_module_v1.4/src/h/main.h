#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

#include "mdr_modbus.h"
#include "mdr_adc.h"
#include <MDR32F9Qx_timer.h>
#include <MDR32F9Qx_port.h>
#include "pbf_module.h"

#define Modbus_LED_ON   			   MDR_PORTA->RXTX |=   (1<<3)		// Modbus LED 
#define Modbus_LED_OFF 			  	 MDR_PORTA->RXTX &=  ~(1<<3)					

#define OverCurrLED_ON   				 MDR_PORTA->RXTX |=   (1<<4)		// светодиод защиты по току 
#define OverCurrLED_OFF  				 MDR_PORTA->RXTX &=  ~(1<<4)					

#define TRIG_LED_ON       			 MDR_PORTA->RXTX |= 1 << 2     
#define TRIG_LED_OFF      			 MDR_PORTA->RXTX &= ~(1 << 2)

#define HV_SWITCH_ST 		 (uint16_t)((MDR_PORTE->RXTX & 1<<6) >> 6)  // анализ состояния тумблера высокого
#define REMOTE_SWITCH_ST (uint16_t)((MDR_PORTA->RXTX & 1<<5) >> 5)  // анализ состояния тумблера режима упр: с пер. панели/дист

#define HV_SUPPLY_ON  					 MDR_PORTC->RXTX |=  (1<<2)     // для версии платы 1.4
#define HV_SUPPLY_OFF   				 MDR_PORTC->RXTX &= ~(1<<2)

#define Rs 			100
#define Rint  	7000000.0 			// internal device load
#define k 			3.0					 		// OP-amp inverting amplifier coefficient
#define DAC_lsb 0.8056640625	  // (3.3/4096) * 1000
#define MAX_CURRENT 9500U				// 9500 mA max 

#define ON  1U
#define OFF 0U

// ADC measurements group
typedef struct ADC_measured_t
{ 
    uint16_t VsetCounts; 
    uint16_t VmeasCounts;
    uint16_t ImeasCounts;
} ADC_meas; 	

typedef struct PIDreg_t
{ 
    float P; 
    float I;
    float D;
	
		float kP;
		float kI;
		float kD;
	
		float curr_error;
	  float prev_error;
	
		float result;
	
} PIDreg; 
