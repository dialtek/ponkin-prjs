#define cMainFreq 8
#define cVCOClock 336
#define cPLLM 2
#define cPLLN (cVCOClock*cPLLM / cMainFreq)
#define cPLLP 2
#define cPLLQ (cVCOClock / 48)

//-----------------------------------------------
//Настройка максимальной частоты
//-----------------------------------------------
void InitClock(void){
	
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
	/* Конфигурируем множитель PLL configuration: PLLCLK = HSE * 21 = 168 MHz */
  /* При условии, что кварц на 8МГц */
  RCC->PLLCFGR=(cPLLQ<<24) | (cPLLP<<16) | (cPLLN<<6) | cPLLM | RCC_PLLCFGR_PLLSRC_HSE; //page 263
    
  RCC->CR |=    RCC_CR_PLLON;
    
  while (!(RCC->CR & RCC_CR_PLLRDY)); //wait for PLL ready 
    
  RCC->CFGR |= RCC_CFGR_HPRE_DIV1; //page 151 Max freq AHB 180 MHz, current 168
  RCC->CFGR |= RCC_CFGR_PPRE2_DIV2; //page 151 Max freq APB2 90 MHz, current 84
  RCC->CFGR |= RCC_CFGR_PPRE1_DIV4; //page 151 Max freq APB1 45 MHz, current 42

  //page 228, PLL selected as system clock
	/* Выбираем PLL как источник системной частоты */
	//SW - System clock switch (10: PLL selected as system clock)
   RCC->CFGR = (RCC->CFGR & ~RCC_CFGR_SW) | RCC_CFGR_SW_PLL;
	/* Ожидаем, пока PLL выберется как источник системной частоты */
  while ((RCC->CFGR & RCC_CFGR_SWS ) != RCC_CFGR_SWS_PLL);

	RCC->CR &= ~RCC_CR_HSION; // page 224, HSI clock 16 MHz Off 

}
