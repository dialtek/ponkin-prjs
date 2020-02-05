#include "UART.h"
#include "Config.h" // !!!!

/*=========================================================================== */
volatile unsigned char timer_state = 0;

extern volatile unsigned char rx_buf_ptr;
extern volatile unsigned char rx_buf[128];
extern volatile char rx_flag;
/*=========================================================================== */

//-----------------------------------------------
//Настройка USART
//-----------------------------------------------
void Uart2Init(void){	
   
	RCC->APB2ENR |= RCC_AHB1LPENR_GPIOALPEN;// GPIOA Clock ON. Alter function clock ON
	
	//------------настройка выводов
	GPIO_InitTypeDef usartConf;														// Объявление структуры
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); // Включаем тактирование порта A
	// Инициализация входа, подключенного к светодиоду
	usartConf.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_3; 					// Задаем номер вывода
	usartConf.GPIO_Mode = GPIO_Mode_AF; 									// Режим работы
	usartConf.GPIO_Speed = GPIO_Speed_50MHz;							// Cкорость
	usartConf.GPIO_OType = GPIO_OType_PP;									// Подтяжка резистора
	usartConf.GPIO_PuPd = GPIO_PuPd_NOPULL;							  // 
	GPIO_Init(GPIOA,&usartConf); 													// Вызов функции инициализации структуры	
	// настройка usart2 и пинов
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_USART2);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_USART2);
	
	//------------настройка UART 13.125M@230400
	RCC->APB1ENR	|= RCC_APB1ENR_USART2EN;													// USART2 Clock ON
	USART2->BRR = 0x39;//72;  																			// baudrate 230400, 0xE4 for 115200
	USART2->CR1  |= USART_CR1_UE | USART_CR1_TE | USART_CR1_RE; 		// USART2 ON, TX ON, RX ON
	NVIC_SetPriority(USART2_IRQn, 0); 															// Прерывание от UART, приоритет 0, самый высокий
	
			//Разрешение прерываний по приему данных
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE); 
	//------------включение UART
	USART_Cmd(USART2, ENABLE);	
	NVIC_EnableIRQ(USART2_IRQn);  																	//Разрешение прерываний
	
	init_timer_TIM2();

	
}

//-----------------------------------------------
//Настройка таймера
//-----------------------------------------------

//Функция инициализации таймера TIM6
void init_timer_TIM2(void) {
// Включить тактирование таймера

TIM_TimeBaseInitTypeDef base_timer;
TIM_TimeBaseStructInit(&base_timer);
	
base_timer.TIM_Prescaler = 1;
base_timer.TIM_Period    = 133;
TIM_TimeBaseInit(TIM2, &base_timer);

// Разрешить прерывание по переполнению счётчика таймера
TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
//Разрешить обработку прерывания по переполнению счётчика таймера
NVIC_EnableIRQ(TIM2_IRQn);
}



//-----------------------------------------------
//Отправка одного бита по UART
//-----------------------------------------------
void UartSendByte(unsigned char TxByte)
{
	  
		USART_SendData(USART2, (uint16_t)TxByte);
		while(USART_GetFlagStatus(USART2, USART_FLAG_TC)== RESET){}
		
}

//Функция обработки прерывания таймера
void TIM2_IRQHandler(void)
{
	// Если произошло прерывание по переполнению счётчика таймера TIM6
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) 
		//Обнулить бит обрабатываемого прерывания
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	
	timer_state = 0;
	rx_flag = 1;         // fire modbus cmd rx flag
}


//-----------------------------------------------
//Прерывание для USART (при окончании передачи и приема)
//-----------------------------------------------
void USART2_IRQHandler (void){
	/* Прерывание по приему байта по USART */
  if (USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
    {  
			while(USART_GetFlagStatus(USART2,USART_FLAG_RXNE) == RESET){}
				
			rx_buf[rx_buf_ptr++] = (unsigned char) USART2->DR;		
			// Очищаем флаг прерывания после считывания
			USART_ClearITPendingBit(USART2, USART_IT_RXNE);
				
			if(timer_state == 0)
      {
        timer_state = 1;
				//Включить таймер
			  TIM_Cmd(TIM2, ENABLE);
      }

   }
}