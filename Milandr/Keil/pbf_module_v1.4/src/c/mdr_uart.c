#include "FreeRTOS.h"
#include "queue.h"
#include "semphr.h"
#include "mdr_uart.h"
#include "main.h"

static volatile QueueHandle_t xRxedBytes; 
static volatile uint8_t RxByte;
static UBaseType_t RxBytesCnt;

volatile unsigned char timer_state = 0;
extern SemaphoreHandle_t RxSemaphore;

static BaseType_t xHigherPriorityTaskWoken; 

void UartInit(void)								// U1 init
{
	
	// UART1 init - MODBUS	
		
  MDR_PORTB->FUNC |= ((2 << 5*2) | (2 << 6*2)); //режим работы порта
  MDR_PORTB->ANALOG |= ((1 << 5) | (1 << 6));   //цифровой
  MDR_PORTB->PWR |= ((3 << 5*2) | (3 << 6*2));  //максимально быcтрый

  MDR_RST_CLK->PER_CLOCK |= (1UL << 6); 	//тактирование UART1
  MDR_RST_CLK->UART_CLOCK = (4 						/*установка делителя для UART1 = */
  |(0 << 8) 															/*установка делителя для UART2 = undefined*/
  |(1 << 24) 															/*разрешение тактовой частоты UART1*/
  |(0 << 25)); 														/*разрешение тактовой частоты UART2*/ 
  
  //Параметры делителя при частоте = 5000000Гц и скорости = 115200
	MDR_UART1->IBRD = 0x2; 			   // целая часть делителя скорости
	MDR_UART1->FBRD = 0x2e; 			 // дробная часть делителя скорости
	MDR_UART1->LCR_H = ((0 << 1) 	 // разрешение проверки четности
		|(0 << 2) 									 // четность/нечетность
		|(0 << 3) 									 // стоп-бит
		|(0 << 4) 								 	 // выкл. буфера FIFO приемника и передатчика 12 бит, глубину 16 слов
		|(3 << 5) 									 // длина слова = 8 бит
		|(0 << 7)); 							   // передача бита четности

	MDR_UART1->IMSC = 1 << 4;                  // RXIM разрешение прерывания от приемника UARTRXINTR. 1 – установлена;   
	MDR_UART1->CR = ((1 << 8)|(1 << 9)|1);     // передачик и приемник разрешен, 
	
	// create UART RX bytes queue
  xRxedBytes = xQueueCreate(32, sizeof(unsigned char));
}
	
void UartSendByte(uint8_t sByte)	// U1 send byte
{  
	while(MDR_UART1->FR & (1<<5)) { }; // ждем готовности UART1;
	
  MDR_UART1->DR = (uint32_t)sByte;
}



int8_t UartGetByte(uint8_t  *pcRxedChar, TickType_t xBlockTime )
{
    
	if( xQueueReceive(xRxedBytes, pcRxedChar, xBlockTime ) )
	{
		return pdTRUE;
	}
	else
	{
		return pdFALSE;
	}
}




__irq void UART1_IRQHandler(void) // U1 rx interrupt handler UART1
{

	RxByte = (uint8_t)MDR_UART1->DR; 
	MDR_UART1->ICR  = 1<<4; // сброс прерывания от приемника  

	xQueueSendFromISR(xRxedBytes, (void*)&RxByte, 0);

	if(uxQueueMessagesWaitingFromISR(xRxedBytes) > 7)
		xSemaphoreGiveFromISR(RxSemaphore,&xHigherPriorityTaskWoken);
}

UBaseType_t UartGetQcnt(void)
{
   return uxQueueMessagesWaiting(xRxedBytes); 
}


void UartResetQueue(void)
{ 
   xQueueReset(xRxedBytes);
}



