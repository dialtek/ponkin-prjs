#include "Config.h"

/*-----------------------------------------------------------------------------*/
/*---------------------------��������� � �������������-------------------------*/
/*-----------------------------------------------------------------------------*/

//-----------------------------------------------
//��������� ������������ �������
//-----------------------------------------------
void InitClock(void){
	
	// Fcy(PLLCLK)   = 105M
	// Fpclk 				 = 26.25M 
	
	//��������� �������� ������� ��� �������
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
	
	//��������� ������� �������� �������
	//RCC register page 224
  RCC->CR |=RCC_CR_HSEON; // Enable external quartz
  while (!(RCC->CR & RCC_CR_HSERDY)); //wait for quartz ready 
    
  //Config Flash
  //Latency page 80 Refman
	//PRETEN - �������� ����� ����������� FLASH
	//ICEN - Instruction cache enable
	//DCEN - Data cache enable
	//LANENCY - ������������� Flash �� 5 ������ ��������
  FLASH->ACR = FLASH_ACR_PRFTEN | FLASH_ACR_ICEN | FLASH_ACR_DCEN | FLASH_ACR_LATENCY_5WS;

  //Config PLL
	/* ������������� ��������� PLL configuration: PLLCLK = 105 MHz */
  /* ��� �������, ��� ����� �� 8��� */								//	210 MHz !!!!
  RCC->PLLCFGR=(cPLLQ<<24) | (cPLLP<<16) | (cPLLN<<6) | cPLLM | RCC_PLLCFGR_PLLSRC_HSE; //page 263
    
  RCC->CR |=    RCC_CR_PLLON;
    
  while (!(RCC->CR & RCC_CR_PLLRDY)); //wait for PLL ready 
    
  RCC->CFGR |= RCC_CFGR_HPRE_DIV8; 		//page 151 Max freq AHB 180 MHz, current 26.25M
  RCC->CFGR |= RCC_CFGR_PPRE2_DIV2;   // 16 	13.125 MHz SPI
  RCC->CFGR |= RCC_CFGR_PPRE1_DIV1; 	//page 151 Max freq APB1 45 MHz, current 26.25M -> UART2 TIM2

  //page 228, PLL selected as system clock
	/* �������� PLL ��� �������� ��������� ������� */
	//SW - System clock switch (10: PLL selected as system clock)
   RCC->CFGR = (RCC->CFGR & ~RCC_CFGR_SW) | RCC_CFGR_SW_PLL;
	/* �������, ���� PLL ��������� ��� �������� ��������� ������� */
  while ((RCC->CFGR & RCC_CFGR_SWS ) != RCC_CFGR_SWS_PLL);

	RCC->CR &= ~RCC_CR_HSION; // page 224, HSI clock 16 MHz Off 
	
		  // ������������ ������ SPI1 � ����� �
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

}

//-----------------------------------------------
//��������� ������
//-----------------------------------------------
void GPIO_Config(void){
	
	GPIO_InitTypeDef GPIO_InitStructure;
	
	//����������
	GPIO_InitTypeDef gpioConf;														// ���������� ���������
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE); // �������� ������������ ����� D
	//������������� �����, ������������� � ����������
	//������ ����� ������
	gpioConf.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_12|GPIO_Pin_14; 											
	gpioConf.GPIO_Mode = GPIO_Mode_OUT; 									// ����� ������
	gpioConf.GPIO_Speed = GPIO_Speed_50MHz;							// C�������
	gpioConf.GPIO_OType = GPIO_OType_PP;									// �������� ���������
	gpioConf.GPIO_PuPd = GPIO_PuPd_NOPULL;							  // 
	GPIO_Init(GPIOD,&gpioConf); 													// ����� ������� �������������
	
	// Regulator ctrl 
//	GPIO_InitTypeDef gpioCConf;														
//	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE); // �������� ������������ ����� 

//	gpioCConf.GPIO_Pin = GPIO_Pin_8; 											
//	gpioCConf.GPIO_Mode = GPIO_Mode_OUT; 									// ����� ������
//	gpioCConf.GPIO_Speed = GPIO_Speed_50MHz;							  // C�������
//	gpioCConf.GPIO_OType = GPIO_OType_PP;									// �������� ���������
//	gpioCConf.GPIO_PuPd = GPIO_PuPd_NOPULL;							  // 
//	GPIO_Init(GPIOC, &gpioCConf); 													// ����� ������� �������������
	
	
	//6 ADC CS 
	GPIO_InitTypeDef gpioEConf;														
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE); // �������� ������������ ����� E

	gpioEConf.GPIO_Pin = GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15; 											
	gpioEConf.GPIO_Mode = GPIO_Mode_OUT; 									// ����� ������
	gpioEConf.GPIO_Speed = GPIO_Speed_50MHz;							  // C�������
	gpioEConf.GPIO_OType = GPIO_OType_PP;									// �������� ���������
	gpioEConf.GPIO_PuPd = GPIO_PuPd_NOPULL;							  // 
	GPIO_Init(GPIOE,&gpioEConf); 													// ����� ������� �������������
	
			// ����������� ���� SPI1 ��� ������ � ������ �������������� �������
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource7, GPIO_AF_SPI1);
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource5, GPIO_AF_SPI1);
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource6, GPIO_AF_SPI1);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_6 | GPIO_Pin_5;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4; 											
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; 									// ����� ������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;							  // C�������
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;									// ��������� �������� 
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;							  // 
	GPIO_Init(GPIOA,&GPIO_InitStructure); 													// ����� ������� �������������
}

//-----------------------------------------------
//��������� ������� �� 1000 ����� � �������
//-----------------------------------------------
void TIM_Config(void){
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;   								//��������� ������ �������� ��������� �� TIM2 
	TIM2->CNT = 0;																				//������� �������
	//TIM2->CR1 |= TIM_CR1_ARPE;														//��������� ��������� ARR
	TIM2->PSC     = 0;             												//��������� �������� ��� ������������ us
	TIM2->ARR 		= 26; 
  //TIM2->DIER    = TIM_DIER_UIE;        	 								//��������� ������� �� �������
  //��������� ������������ 
  TIM2->CR1     = TIM_CR1_ARPE;
  //��������� ���������� �� �������              
  NVIC_DisableIRQ (TIM2_IRQn);	
}

/*-----------------------------------------------------------------------------*/
/*---------------------------����������� �������-------------------------------*/
/*-----------------------------------------------------------------------------*/

//-----------------------------------------------
//�������������� ��������
//-----------------------------------------------
void delay_us(uint32_t value)
{
  for(uint32_t i = 0; i < value; i++)
	{
		TIM2->CNT = 0;													// ������� �������
		TIM2->CR1 = TIM_CR1_CEN | TIM_CR1_OPM;	    				  // ��������� ������
		while((TIM2->SR & TIM_SR_CC1IF)==0){} 		// ��������� ����� ��������
    TIM2->SR &= ~TIM_SR_CC1IF;	    				  // �������� ����
		TIM2->CR1 = TIM_CR1_UDIS;	    				  // ���� ������
	}
}

void delay_ms(uint16_t value)
{
  TIM2->ARR = value;                 		  // ��������� �������� ��������
  TIM2->CNT = 0;													// ������� �������
  TIM2->CR1 = TIM_CR1_CEN;	    				  // ��������� ������
	while((TIM2->SR & TIM_SR_UIF)==0){} 		// ��������� ����� ��������
  TIM2->SR &= ~TIM_SR_UIF;	    				  // �������� ����
}

