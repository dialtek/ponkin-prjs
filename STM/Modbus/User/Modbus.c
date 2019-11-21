#include "Modbus.h"
/* 
UART ����: 
PA2 - TX
PA3 - RX
*/

char Buffer[512]; 	// ���������� ������ � USART

int main(){ 

  InitClock();
	TIM_Config();
	USART2_INIT();
	//���������� ���������� �� ������ ������
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE); 					
	while(1)	__NOP;
}

//-----------------------------------------------
//���������� ��� USART (��� ��������� �������� � ������)
//-----------------------------------------------
void USART2_IRQHandler (void){
	
	/* ���������� �� ������ ����� �� USART */
  if (USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
    {  
			for(int i = 0; i < 512; i++)	Buffer[i] = NULL;
			USART_ReadTXT(USART2,Buffer);
			// ������� ���� ���������� ����� ����������
			USART_ClearITPendingBit(USART2, USART_IT_RXNE);
			USART_SendTXT(USART2,Buffer);    
   }
}