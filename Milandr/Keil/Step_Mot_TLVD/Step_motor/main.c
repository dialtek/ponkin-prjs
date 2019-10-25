#include "MDR32Fx.h"   
#include "GPIO.h"
#include "milkites_delay.h"
#include "milkites_display.h"
#include "milkites_spi.h"
#include "stdint.h"
#include "milkites_I2C.h"
#include "MyFunc.h"
#include "tlv493d.h"
#include "pwm_step_motor.h"
#include <MDR32F9Qx_port.h>

#define USE_JTAG_A

  int main(){
/*--------------------ПЕРЕМЕННЫЕ------------------------*/   

/*------------------------------------------------------*/
		
      
		
/*------------------INITIALIZATIONS---------------------*/
	GPIO();
	CPU_init();
	delay_init(); // инициализация системы задержек
  LCD_init(); // инициализация дисплея
  LCD_clear(); // очистка дисплея
  LCD_led_en; // вкл. подсветки дисплея
	I2C_Init();
	tlv493d_init();
		
		
//	PORT_InitTypeDef PORTB_config_struct;
//	PORT_StructInit(&PORTB_config_struct);
//	
//	// Настройка порта
//	PORTB_config_struct.PORT_Pin = PORT_Pin_All & (~JTAG_PINS(MDR_PORTB));  // Чтобы не отваливался JTAG,
//	                             //исключаем из инициализации JTAG-овские пины
//	PORTB_config_struct.PORT_OE = PORT_OE_OUT;
//	PORTB_config_struct.PORT_MODE = PORT_MODE_DIGITAL;
//	PORTB_config_struct.PORT_SPEED = PORT_SPEED_MAXFAST;
//	PORT_Init(MDR_PORTB, &PORTB_config_struct);
//  MDR_PORTB->RXTX = 0xffff & (~JTAG_PINS(MDR_PORTB));  // JTAG будет работать дальше
//	// Работоспособность разных способов записи в порт B:
//	
//	// Здесь поведение JTAG-а соответствует ожидаемому:
//	//MDR_PORTB->RXTX = 0xff & (~JTAG_PINS(MDR_PORTB));  // JTAG будет работать дальше
//	  MDR_PORTB->RXTX = 1<<10 & (~JTAG_PINS(MDR_PORTB));  // JTAG будет работать дальше
//		MDR_PORTB->RXTX = 0<<9 & (~JTAG_PINS(MDR_PORTB));  // JTAG будет работать дальше
	//MDR_PORTB->RXTX = 1 << 7;                          // JTAG будет работать дальше
	//MDR_PORTB->RXTX = 0xff;  
	
	
	//  initTimerPWMled(uint32_t timeEnabledState, uint32_t PWM_speed )	
	//  PWM_speed(1:1000), где 8000 - 1 Гц, 1 - 8000 Гц, 0 - светодиод просто горит...
	//  timeEnabledState (1:х), где 0 - светодиод не горит... зависит от частоты ШИМ сигнала, хотя не должно...
	//MDR_PortInit();
 // STEP_ENABLE();
	STEP_DISABLE();
	STEPPER_SPEED(100);
  

		 
/*------------------------------------------------------*/
while(1)
 {  
      read_all_tlv493d('x','y','z');
	    
	    delay_ms(100);
	    LCD_clear();
	 
	
 }//while	

}//main