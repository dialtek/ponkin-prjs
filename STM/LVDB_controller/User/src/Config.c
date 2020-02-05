#include "Config.h"

/*-----------------------------------------------------------------------------*/
/*---------------------------Настройка и инициализация-------------------------*/
/*-----------------------------------------------------------------------------*/

//-----------------------------------------------
//Настройка максимальной частоты
//-----------------------------------------------
void InitClock(void){
	
	// Fcy(PLLCLK)   = 105M
	// Fpclk 				 = 26.25M 
	
	//Включение тактовой частоты для питания
	// Page 224
	RCC->APB1ENR |= RCC_APB1ENR_PWREN;    
  //PWR_CR Page 116
	//PLC - Power Voltage Detector (0xE0) -> 2.9V
	//PVDE - Power voltage detector enable (0X10) -> ON
	//VOS - Regulator voltage scaling output selection (0x4000) -> 1 mode
  PWR->CR |= PWR_CR_PLS | PWR_CR_PVDE | ((uint32_t)0x00004000);
	//While flag no 0x4000 
	//VOSRDY - Under-drive ready flag	
  while (!(PWR->CSR & PWR_CSR_VOSRDY));
	
	//Включение внешней тактовой частоты
	//RCC register page 224
  RCC->CR |=RCC_CR_HSEON; // Enable external quartz
  while (!(RCC->CR & RCC_CR_HSERDY)); //wait for quartz ready 
    
  //Config Flash
  //Latency page 80 Refman
	//PRETEN - Включаем буфер предвыборки FLASH
	//ICEN - Instruction cache enable
	//DCEN - Data cache enable
	//LANENCY - Конфигурируем Flash на 5 циклов ожидания
  FLASH->ACR = FLASH_ACR_PRFTEN | FLASH_ACR_ICEN | FLASH_ACR_DCEN | FLASH_ACR_LATENCY_5WS;

  //Config PLL
	/* Конфигурируем множитель PLL configuration: PLLCLK = 105 MHz */
  /* При условии, что кварц на 8МГц */								//	210 MHz !!!!
  RCC->PLLCFGR=(cPLLQ<<24) | (cPLLP<<16) | (cPLLN<<6) | cPLLM | RCC_PLLCFGR_PLLSRC_HSE; //page 263
    
  RCC->CR |=    RCC_CR_PLLON;
    
  while (!(RCC->CR & RCC_CR_PLLRDY)); //wait for PLL ready 
    
  RCC->CFGR |= RCC_CFGR_HPRE_DIV8; 		//page 151 Max freq AHB 180 MHz, current 26.25M
  RCC->CFGR |= RCC_CFGR_PPRE2_DIV2;   // 16 	13.125 MHz SPI1
  RCC->CFGR |= RCC_CFGR_PPRE1_DIV2; 	//page 151 Max freq APB1 45 MHz, current 13.125M -> UART2 TIM2 SPI2 SPI3

  //page 228, PLL selected as system clock
	/* Выбираем PLL как источник системной частоты */
	//SW - System clock switch (10: PLL selected as system clock)
   RCC->CFGR = (RCC->CFGR & ~RCC_CFGR_SW) | RCC_CFGR_SW_PLL;
	/* Ожидаем, пока PLL выберется как источник системной частоты */
  while ((RCC->CFGR & RCC_CFGR_SWS ) != RCC_CFGR_SWS_PLL);

	RCC->CR &= ~RCC_CR_HSION; // page 224, HSI clock 16 MHz Off 
	
	// Тактирование модуля SPI1, SPI2, PORTА
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1,  ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2,  ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,  ENABLE);
	//RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;   								//разрешить подачу тактовых импульсов на TIM2 
	//T2 sclk = 13.125M
	
	//RCC->APB1RSTR |=  RCC_APB1RSTR_SPI2RST;
  //RCC->APB1RSTR &= ~RCC_APB1RSTR_SPI2RST;   ??
	
}

//-----------------------------------------------
//Настройка портов
//-----------------------------------------------
void GPIO_Config(void){
	
	GPIO_InitTypeDef GPIO_InitStructure;
	
	//PORTA - Modbus LED, SPI1, Modbus UART, 2xTon
	//===================================================
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); // Включаем тактирование порта A
	// Настраиваем ноги SPI1 для работы в режиме альтернативной функции
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource7, GPIO_AF_SPI1);
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource5, GPIO_AF_SPI1);
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource6, GPIO_AF_SPI1);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_6 | GPIO_Pin_5;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0; 											
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; 									// Режим работы
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;							  // Cкорость
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;									
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;							  // Подтяжка выкл
	GPIO_Init(GPIOA,&GPIO_InitStructure); 													// Вызов функции инициализации
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9; 											
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN; 									  // Режим работы							
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;							  // Подтяжка выкл
	GPIO_Init(GPIOA,&GPIO_InitStructure); 													// Вызов функции инициализации
	//===================================================
	
	// PORTB - SPI2, ID, MCU mode, TX EN
	//===================================================
  GPIO_InitTypeDef gpioBConf;														
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE); // Включаем тактирование порта B
	// Настраиваем ноги SPI2 для работы в режиме альтернативной функции
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource13, GPIO_AF_SPI2);
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource14, GPIO_AF_SPI2);
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource15, GPIO_AF_SPI2);
	
  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
  // TX EN
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;																			
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; 				// Режим работы
	GPIO_Init(GPIOB,&GPIO_InitStructure); 								// Вызов функции инициализации
	// ID
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11;																	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN; 					// Режим работы
	GPIO_Init(GPIOB,&GPIO_InitStructure); 								// Вызов функции инициализации
	//===================================================

	// PORTC - SPI1 7 ADC nCS and 9 x nTurnONs 1.x
	//===================================================
	GPIO_InitTypeDef gpioCConf;														
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE); // Включаем тактирование порта C
	gpioCConf.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2 |GPIO_Pin_3 |GPIO_Pin_4 |GPIO_Pin_5 |GPIO_Pin_6|GPIO_Pin_7|    // SPI1 CSn
											 GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;	 // ToN 1.n
	gpioCConf.GPIO_Mode = GPIO_Mode_OUT; 									// Режим работы
	gpioCConf.GPIO_Speed = GPIO_Speed_50MHz;							// Cкорость
	gpioCConf.GPIO_OType = GPIO_OType_PP;									// 
	gpioCConf.GPIO_PuPd = GPIO_PuPd_NOPULL;							  // Подтяжка выкл
	GPIO_Init(GPIOC,&gpioCConf); 													// Вызов функции инициализации

	// PORTD - SPI1 7 ADC nCS and 9 x nTurnONs 2.x 
	//===================================================
	GPIO_InitTypeDef gpioDConf;														
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE); // Включаем тактирование порта D
	gpioDConf.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2 |GPIO_Pin_3 |GPIO_Pin_4 |GPIO_Pin_5 |GPIO_Pin_6|       												// SPI 2 CSn
											 GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9 |GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;	    // ToN 2.n
	gpioDConf.GPIO_Mode  = GPIO_Mode_OUT; 								// Режим работы
	gpioDConf.GPIO_Speed = GPIO_Speed_50MHz;							// Cкорость
	gpioDConf.GPIO_OType = GPIO_OType_PP;									
	gpioDConf.GPIO_PuPd  = GPIO_PuPd_NOPULL;							// Подтяжка выкл
	GPIO_Init(GPIOD,&gpioDConf); 													// Вызов функции инициализации
	
	// PORTE - nTurnONs 1 and 2 feedback 
	//===================================================
	GPIO_InitTypeDef gpioEConf;														
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE); // Включаем тактирование порта E
	gpioDConf.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2 |GPIO_Pin_3 |GPIO_Pin_4 |GPIO_Pin_5 |GPIO_Pin_6|       												
											 GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9 |GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;	    
	gpioDConf.GPIO_Mode  = GPIO_Mode_IN; 							  	// Режим работы					
	gpioDConf.GPIO_PuPd  = GPIO_PuPd_NOPULL;							// Подтяжка выкл
	GPIO_Init(GPIOE,&gpioEConf); 													// Вызов функции инициализации
}





