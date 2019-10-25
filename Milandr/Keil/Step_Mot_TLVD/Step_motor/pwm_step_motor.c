
#include "MDR32Fx.h"                    // Device header
#include "pwm_step_motor.h"

// Инициализация таймера в режиме ШИМ для работы со светодиодом. 
//void initTimerPWM_step(uint32_t PWM_speed){ 
//  MDR_RST_CLK->TIM_CLOCK |= RST_CLK_TIM_CLOCK_TIM1_CLK_EN; // Подаем тактирование без предделителя.
//	
//	MDR_TIMER1->CNT = 0; // Считай с 0.
//	MDR_TIMER1->PSG = 320000-1; // На таймер идет частота TIM_CLK/32000.
//	MDR_TIMER1->ARR = PWM_speed; //PWM_speed;
//	MDR_TIMER1->CH1_CNTRL = 3<<TIMER_CH_CNTRL_OCCM_Pos; // Переключение REF, если CNT = CCR;
//	MDR_TIMER1->CH1_CNTRL1 = (2<<TIMER_CH_CNTRL1_SELO_Pos) // На выход выдается сигнал c REF.
//	| (1<<TIMER_CH_CNTRL1_SELOE_Pos); // Канал всегда работает на выход.
//	MDR_TIMER1->CNTRL = TIMER_CNTRL_CNT_EN; // Включаем таймер.
//}

// Инициализация таймера в режиме ШИМ для работы со светодиодом. 



void STEPPER_SPEED(uint32_t PWM_speed ){  //uint32_t timeEnabledState, 
	  
   // MDR_RST_CLK->PER_CLOCK |= ((1 << 21));
	
    MDR_PORTA->OE |= 0x8;     //направление передачи данных - Выход ( PA: 3  )
    MDR_PORTA->ANALOG |= 0x8;     //режим работы контроллера - Цифровой ( PA: 3  )
    //режим работы пинов:
                          //Альтернативная фукция ( PA: 3  )
    MDR_PORTA->FUNC   |= 0x80; 
    MDR_PORTA->PD   |= (0x0 << 16) | (0x0);     //режим работы выводов
    //скорость :
                         // Быстрый фронт ( PA: 3  )
    MDR_PORTA->PWR   |= 0x80; 
	
//	
	   MDR_PORTA->OE |= 0x4;     //направление передачи данных - Выход ( PA: 2  )
    MDR_PORTA->ANALOG |= 0x4;     //режим работы контроллера - Цифровой ( PA: 2  )
    //режим работы пинов:
                         // Порт ( PA: 2  )
    MDR_PORTA->FUNC   |= 0x0; 
    MDR_PORTA->PD   |= (0x0 << 16) | (0x0);     //режим работы выводов
    //скорость :
                        //  Быстрый фронт ( PA: 2  )
    MDR_PORTA->PWR   |= 0x20;

	
	
	
	
  MDR_RST_CLK->TIM_CLOCK |= RST_CLK_TIM_CLOCK_TIM1_CLK_EN; // Подаем тактирование без предделителя.
			 										// Mode is up and down
// 	 for(int i = 1; i >= 100; i++){
//		
//		if (PWM_speed == i){
//			
//			PWM_speed = 100 - (i-1);
//		}
//	}

	MDR_TIMER1->CNT = 0; // Считай с 0.
	MDR_TIMER1->PSG = 80000-1; // На таймер идет частота TIM_CLK/32000.
	MDR_TIMER1->ARR = 10*PWM_speed; //PWM_speed;
	//MDR_TIMER1->CH1_CNTRL = 3<<TIMER_CH_CNTRL_OCCM_Pos; // Переключение REF, если CNT = CCR;
	MDR_TIMER1->CH2_CNTRL = 6<<TIMER_CH_CNTRL_OCCM_Pos; // REF = 1, когда CNT < CCR1, 0 - CNT >= CCR1;
	MDR_TIMER1->CH2_CNTRL1 = (2<<TIMER_CH_CNTRL1_SELO_Pos) // На выход выдается сигнал c REF.
	| (1<<TIMER_CH_CNTRL1_SELOE_Pos); // Канал всегда работает на выход.
	MDR_TIMER1->CCR2 = 10*PWM_speed/5;//timeEnabledState;

  MDR_TIMER1->CNTRL = TIMER_CNTRL_CNT_EN; // Включаем таймер.

//  MDR_TIMER1->CNT = 0; // Считай с 0.
//	MDR_TIMER1->PSG = 32000-1; // На таймер идет частота TIM_CLK/32000.
//	MDR_TIMER1->ARR = PWM_speed; // 1 секунда 250 тиков. У нас частота 2 герца. 
//	MDR_TIMER1->CH2_CNTRL = 3<<TIMER_CH_CNTRL_OCCM_Pos; // Переключение REF, если CNT = CCR;
//	MDR_TIMER1->CH2_CNTRL1 = (2<<TIMER_CH_CNTRL1_SELO_Pos) // На выход выдается сигнал c REF.
//	| (1<<TIMER_CH_CNTRL1_SELOE_Pos); // Канал всегда работает на выход.
//  //MDR_TIMER1->CCR2 = PWM_speed;
//	MDR_TIMER1->CNTRL = TIMER_CNTRL_CNT_EN; // Включаем таймер.
}

 void STEP_ENABLE(void){
	 
	 MDR_PORTA->RXTX = (0 << 2);
 }
  void STEP_DISABLE(void){
	 
	 MDR_PORTA->RXTX = (1 << 2);
 }