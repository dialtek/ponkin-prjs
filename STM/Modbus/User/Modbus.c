#include "Modbus.h"
/* 
UART пины: 
PA2 - TX
PA3 - RX
*/

char Buffer[512]; 	// Считывание строки с USART

int main(){ 

  InitClock();
	TIM_Config();
	USART2_INIT();
	//Разрешение прерываний по приему данных
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE); 					
	while(1)	__NOP;
}

//-----------------------------------------------
//Прерывание для USART (при окончании передачи и приема)
//-----------------------------------------------
void USART2_IRQHandler (void){
	
	/* Прерывание по приему байта по USART */
  if (USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
    {  
			for(int i = 0; i < 512; i++)	Buffer[i] = NULL;
			USART_ReadTXT(USART2,Buffer);
			// Очищаем флаг прерывания после считывания
			USART_ClearITPendingBit(USART2, USART_IT_RXNE);
			USART_SendTXT(USART2,Buffer);    
   }
}