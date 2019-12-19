#include "UART.h"
#include "Config.h" // !!!!

extern volatile unsigned char rx_buf_ptr;
extern volatile unsigned char rx_buf[128];
extern volatile char rx_flag;

//-----------------------------------------------
//��������� USART
//-----------------------------------------------
void Uart2Init(void){	
   
	RCC->APB2ENR |= RCC_AHB1LPENR_GPIOALPEN;// GPIOA Clock ON. Alter function clock ON
	
	//------------��������� �������
	GPIO_InitTypeDef usartConf;														// ���������� ���������
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); // �������� ������������ ����� A
	// ������������� �����, ������������� � ����������
	usartConf.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_3; 					// ������ ����� ������
	usartConf.GPIO_Mode = GPIO_Mode_AF; 									// ����� ������
	usartConf.GPIO_Speed = GPIO_Speed_50MHz;							// C�������
	usartConf.GPIO_OType = GPIO_OType_PP;									// �������� ���������
	usartConf.GPIO_PuPd = GPIO_PuPd_NOPULL;							  // 
	GPIO_Init(GPIOA,&usartConf); 													// ����� ������� ������������� ���������	
	// ��������� usart2 � �����
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_USART2);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_USART2);
	
	//------------��������� UART 26.25M@115200
	RCC->APB1ENR	|= RCC_APB1ENR_USART2EN;													//USART2 Clock ON
	USART2->BRR = 0xE4;																					  	//Bodrate for 115200
	USART2->CR1  |= USART_CR1_UE | USART_CR1_TE | USART_CR1_RE; 		//USART2 ON, TX ON, RX ON
	NVIC_SetPriority(USART2_IRQn, 0); 															//���������� �� UART, ��������� 0, ����� �������
	
			//���������� ���������� �� ������ ������
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE); 
	//------------��������� UART
	USART_Cmd(USART2, ENABLE);	
	NVIC_EnableIRQ(USART2_IRQn);  																	//���������� ����������

	
}
//-----------------------------------------------
//�������� ������ ���� �� UART
//-----------------------------------------------
void UartSendByte(unsigned char TxByte)
{
	  
		USART_SendData(USART2, (uint16_t)TxByte);
		while(USART_GetFlagStatus(USART2, USART_FLAG_TC)== RESET){}
		
}

//-----------------------------------------------
//���������� ��� USART (��� ��������� �������� � ������)
//-----------------------------------------------
void USART2_IRQHandler (void){
	/* ���������� �� ������ ����� �� USART */
  if (USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
    {  
			while(USART_GetFlagStatus(USART2,USART_FLAG_RXNE) == RESET){}
				
			rx_buf[rx_buf_ptr] = (unsigned char) USART2->DR;
			rx_buf_ptr++;				
			// ������� ���� ���������� ����� ����������
			USART_ClearITPendingBit(USART2, USART_IT_RXNE);
   }
}