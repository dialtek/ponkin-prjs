#define Modbus_LED_ON   			   MDR_PORTA->RXTX |=   (1<<3)		// Modbus LED 
#define Modbus_LED_OFF 			  	 MDR_PORTA->RXTX &=  ~(1<<3)					

#define LED2_ON   							 MDR_PORTA->RXTX |=   (1<<4)		// Modbus LED 
#define LED2_OFF  						   MDR_PORTA->RXTX &=  ~(1<<4)					


#define HV_SWITCH_ON (uint16_t)((MDR_PORTE->RXTX & 1<<6) >> 6)  // анализ состояния тумблера высокого

#define HV_SUPPLY_ON  					 MDR_PORTC->RXTX |=  (1<<2)     // для версии платы 1.4
#define HV_SUPPLY_OFF   				 MDR_PORTC->RXTX &= ~(1<<2)

#define Rs 			100
#define Rint  	7000000.0 			// internal device load
#define k 			3.0					 		// OP-amp inverting amplifier coefficient
#define DAC_lsb 0.8056640625	  // (3.3/4096) * 1000

// ADC measurements group
typedef struct ADC_measured_t
{ 
    unsigned int VsetCounts; 
    unsigned int VmeasCounts;
    unsigned int IloadCounts;
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
