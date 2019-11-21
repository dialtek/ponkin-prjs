//-----------------------------------------------
//Настройка USART
//-----------------------------------------------
void USART2_INIT(void){	
	
//	// Включаем прерывания
//    __enable_irq();
	RCC->APB2ENR |= RCC_AHB1LPENR_GPIOALPEN;// GPIOA Clock ON. Alter function clock ON
	
	//------------настройка выводов
	GPIO_InitTypeDef usartConf;														// Объявление структуры
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); // Включаем тактирование порта A
	// Инициализация входа, подключенного к светодиоду
	usartConf.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_3; 					// Задаем номер вывода
	usartConf.GPIO_Mode = GPIO_Mode_AF; 									// Режим работы
	usartConf.GPIO_Speed = GPIO_Speed_50MHz;							// Cкорость
	usartConf.GPIO_OType = GPIO_OType_PP;									// Подтяжка резистора
	usartConf.GPIO_PuPd = GPIO_PuPd_UP;							  		// 
	GPIO_Init(GPIOA,&usartConf); 													// Вызов функции инициализации структуры	
	// настройка usart2 и пинов
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_USART2);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_USART2);
	
	//------------настройка UART
	RCC->APB1ENR	|= RCC_APB1ENR_USART2EN;	//USART2 Clock ON
	USART2->BRR = 0x16D;										// Bodrate for 115200 on 42
	USART2->CR1  |= USART_CR1_UE | USART_CR1_TE | USART_CR1_RE; // USART2 ON, TX ON, RX ON
}