
#include "MDR32Fx.h"                    // Device header
#include "pwm_step_motor.h"

#include <MDR32F9Qx_port.h>
#include <MDR32F9Qx_rst_clk.h>


 void PORTB_Init(){
	 
	        /*Настройка порта В*/
 // Инициализация структуры для настройки порта
  	PORT_InitTypeDef PORTB_config_struct;
	  PORT_StructInit(&PORTB_config_struct);
	
	// Настройка порта
  	PORTB_config_struct.PORT_Pin = PORT_Pin_All & (~JTAG_PINS(MDR_PORTB));  // Чтобы не отваливался JTAG,
	                             //исключаем из инициализации JTAG-овские пины
	  PORTB_config_struct.PORT_OE = PORT_OE_OUT;
	  PORTB_config_struct.PORT_MODE = PORT_MODE_DIGITAL;
	  PORTB_config_struct.PORT_SPEED = PORT_SPEED_MAXFAST;
  	PORT_Init(MDR_PORTB, &PORTB_config_struct);
 }

void STEPPER_SPEED(uint32_t PWM_speed ){  
	/*Настройка РА3 */
    MDR_PORTA->OE |= 0x8;     //направление передачи данных - Выход ( PA: 3  )
    MDR_PORTA->ANALOG |= 0x8;     //режим работы контроллера - Цифровой ( PA: 3  )     
    MDR_PORTA->FUNC   |= 0x80;  //Альтернативная фукция ( PA: 3  )
    MDR_PORTA->PD   |= (0x0 << 16) | (0x0);     //режим работы выводов
    MDR_PORTA->PWR   |= 0x80;  // Быстрый фронт ( PA: 3  )
													
    MDR_RST_CLK->TIM_CLOCK |= RST_CLK_TIM_CLOCK_TIM1_CLK_EN; // Подаем тактирование без предделителя.
  	MDR_TIMER1->CNT = 0; // Считай с 0.
	  MDR_TIMER1->PSG = 2000-1; // На таймер идет частота TIM_CLK/32000.
	  MDR_TIMER1->ARR = 10*PWM_speed; //PWM_speed;
   	//MDR_TIMER1->CH1_CNTRL = 3<<TIMER_CH_CNTRL_OCCM_Pos; // Переключение REF, если CNT = CCR;
  	MDR_TIMER1->CH2_CNTRL = 6<<TIMER_CH_CNTRL_OCCM_Pos; // REF = 1, когда CNT < CCR1, 0 - CNT >= CCR1;
	  MDR_TIMER1->CH2_CNTRL1 = (2<<TIMER_CH_CNTRL1_SELO_Pos) // На выход выдается сигнал c REF.
	| (1<<TIMER_CH_CNTRL1_SELOE_Pos); // Канал всегда работает на выход.
	  MDR_TIMER1->CCR2 = 10*PWM_speed/5;//timeEnabledState;

    MDR_TIMER1->CNTRL = TIMER_CNTRL_CNT_EN; // Включаем таймер.

}
	
		
 void STEP_ENABLE(void){
	 
	  MDR_PORTB->RXTX = (0 << 6) & (~JTAG_PINS(MDR_PORTB));  // JTAG будет работать дальше
 }
  void STEP_DISABLE(void){
	 
	  MDR_PORTB->RXTX = 1 << 6 & (~JTAG_PINS(MDR_PORTB));  // JTAG будет работать дальше
 }
	
 void DIR_RIGHT(void){
	 
	 MDR_PORTB->RXTX = 1 << 7 & (~JTAG_PINS(MDR_PORTB));  // JTAG будет работать дальше
 }
 
 void DIR_LEFT(void){
	 
	MDR_PORTB->RXTX = 0 << 7 & (~JTAG_PINS(MDR_PORTB));  // JTAG будет работать дальше
 }
 
  void RGB (char led, uint32_t state)
 {
	 if(led == 'R')
		MDR_PORTB->RXTX = state<<9 & (~JTAG_PINS(MDR_PORTB));
	 if(led == 'G')
		MDR_PORTB->RXTX = state<<8 & (~JTAG_PINS(MDR_PORTB));
	 if(led == 'B')
		MDR_PORTB->RXTX = state<<10 & (~JTAG_PINS(MDR_PORTB));
	 
 }
 
