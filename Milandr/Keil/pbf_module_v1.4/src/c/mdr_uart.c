#include "FreeRTOS.h"
#include "queue.h"
#include "semphr.h"
#include "mdr_uart.h"
#include "main.h"

static volatile QueueHandle_t xRxedBytes; 
static volatile uint8_t RxByte;
static UBaseType_t RxBytesCnt;

static BaseType_t rez = pdFALSE;

volatile unsigned char timer_state = 0;
extern SemaphoreHandle_t RxSemaphore;

static BaseType_t xHigherPriorityTaskWoken; 

void UartInit(void)								// U1 init
{
	
	// UART1 init - MODBUS	
		
  MDR_RST_CLK->PER_CLOCK |= (1UL << 6); 	//������������ UART1
  MDR_RST_CLK->UART_CLOCK = (4 						/*��������� �������� ��� UART1 = */
  |(0 << 8) 															/*��������� �������� ��� UART2 = undefined*/
  |(1 << 24) 															/*���������� �������� ������� UART1*/
  |(0 << 25)); 														/*���������� �������� ������� UART2*/ 
  
  //��������� �������� ��� ������� = 5000000�� � �������� = 115200
	MDR_UART1->IBRD = 0x2; 			   // ����� ����� �������� ��������
	MDR_UART1->FBRD = 0x2e; 			 // ������� ����� �������� ��������
	MDR_UART1->LCR_H = ((0 << 1) 	 // ���������� �������� ��������
		|(0 << 2) 									 // ��������/����������
		|(0 << 3) 									 // ����-���
		|(0 << 4) 								 	 // ����. ������ FIFO ��������� � ����������� 12 ���, ������� 16 ����
		|(3 << 5) 									 // ����� ����� = 8 ���
		|(0 << 7)); 							   // �������� ���� ��������

	MDR_UART1->IMSC = 1 << 4;                  // RXIM ���������� ���������� �� ��������� UARTRXINTR. 1 � �����������;   
	MDR_UART1->CR = ((1 << 8)|(1 << 9)|1);     // ��������� � �������� ��������, 
	
	// create UART RX bytes queue
  xRxedBytes = xQueueCreate(32, sizeof(unsigned char));
}
	
void UartSendByte(uint8_t sByte)	// U1 send byte
{  
	while(MDR_UART1->FR & (1<<5)) { }; // ���� ���������� UART1;
	
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
	MDR_UART1->ICR  = 1<<4; // ����� ���������� �� ���������  

	rez = pdFALSE; 
	
	xQueueSendFromISR(xRxedBytes, (void*)&RxByte, &rez);

	if(uxQueueMessagesWaitingFromISR(xRxedBytes) > 7)
		xSemaphoreGiveFromISR(RxSemaphore,&xHigherPriorityTaskWoken);
	
	 if(rez == pdTRUE)
			portEND_SWITCHING_ISR(rez);
}

UBaseType_t UartGetQcnt(void)
{
   return uxQueueMessagesWaiting(xRxedBytes); 
}


void UartResetQueue(void)
{ 
   xQueueReset(xRxedBytes);
}



