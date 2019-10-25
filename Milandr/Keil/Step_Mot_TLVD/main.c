#include "MDR32Fx.h"                    // Device header
#include "GPIO.h"
#include "milkites_delay.h"
#include "milkites_display.h"
#include "milkites_spi.h"
#include "stdint.h"
#include "milkites_I2C.h"
#include "MyFunc.h"
#include "tlv493d.h"
#include "pwm_step_motor.h"


#define USE_JTAG_A
#include <MDR32F9Qx_port.h>

int main(){
	
	/*============Initializations======================*/
	GPIO();	
	CPU_init();
	delay_init(); // ????????????? ??????? ????????
  LCD_init(); // ????????????? ???????
  LCD_clear(); // ??????? ???????
  LCD_led_en; // ???. ????????? ???????
	I2C_Init();
	tlv493d_init();
	
	PORT_InitTypeDef PORTB_config_struct; 
	PORT_StructInit(&PORTB_config_struct);
	
	PORTB_config_struct.PORT_Pin = PORT_Pin_All & (~JTAG_PINS(MDR_PORTB));                  
	PORTB_config_struct.PORT_OE = PORT_OE_OUT;
	PORTB_config_struct.PORT_MODE = PORT_MODE_DIGITAL;
	PORTB_config_struct.PORT_SPEED = PORT_SPEED_MAXFAST;
	
	PORT_Init(MDR_PORTB, &PORTB_config_struct);
	
	
	MDR_PORTB->RXTX = 0<<6 & (~JTAG_PINS(MDR_PORTB)); 

/*========END Initializations===============================*/	

	STEPPER_SPEED(50);
	
	MDR_PORTC->RXTX = 0x4;
	
	while(1){
		
	  	read_all_tlv493d('x','y','z');
	    
	    delay_ms(100);
	    LCD_clear();	
	}
}
