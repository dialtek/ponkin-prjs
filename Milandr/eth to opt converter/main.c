/// ������� ��� ,��������� ��� ����������������  
/// ���������� - ��������������� ethernet � ���������� uart 

#include "MDR32Fx.h"
#define F_CPU 80000000

#define U8  uint8_t
#define U16 uint16_t 
#define S16 int16_t 
#define U32 uint32_t
#define S32 int32_t

#include "mdr_delay.h"

#define RS485_RX_EN     MDR_PORTB->RXTX &= ~(1<<10)  // ���.  �������� RS485   \_ 
#define RS485_RX_DIS    MDR_PORTB->RXTX |=  (1<<10)  // ����. �������� RS485   _/
#define RS485_TX_EN     MDR_PORTB->RXTX |=  (1<<9)   // ���.  ���������� RS485 _/
#define RS485_TX_DIS    MDR_PORTB->RXTX &= ~(1<<9)  // ����. ���������� RS485 \_

  
  U16 rx_data = 0;
  
  void OSC_init(void){

#define	_HSEBYP	0       // 0 - ����� �����������, 1 - ����� �������� ����������
#define	_HSEON  1	// 0 - ��������, 1 - �������

//---CLK-----------------------------------------------------------------------------------------------------

  MDR_RST_CLK->HS_CONTROL = (_HSEBYP<<1) + _HSEON; 
  while ((MDR_RST_CLK->CLOCK_STATUS & 0x04) != 0x04);     // ���� ���� HSE ������ � ������� �����
  MDR_RST_CLK->PLL_CONTROL = ((1 << 2) | (7 << 8)); 	  // ���. PLL | ����. ��������� = 2

  while((MDR_RST_CLK->CLOCK_STATUS & 0x02) != 0x02);      // ���� ����� PLL ������ � ���. �����

  MDR_RST_CLK->CPU_CLOCK  = (2                           // �������� ��� CPU_C1 - HSE
						   |(1 << 2)                      // �������� ��� CPU_C2 - PLLCPUo 
						   |(1 << 4)                      // ������������ ��� CPU_C3 - CPU_C2
						   |(1 << 8));                    // �������� ��� HCLK
  MDR_RST_CLK->PER_CLOCK = 0xFFFFFFFF;                    // ���. ������������ ���� ���������
  // HCLK = 80 ���
  MDR_RST_CLK->TIM_CLOCK = 0x00000000;
  }
   
  void GPIO_init (void){  
  
  MDR_PORTA->OE      = 0xFFFD;          //  PA1 - ���� �������������
  MDR_PORTA->FUNC    = (2<<2);          // ������� - ����, ��� ��5 �������������� ������� 
  MDR_PORTA->ANALOG  = 0xFFFF;          // ����� ����� - ��������
  MDR_PORTA->PWR     = 0xFFFFFFFF;      // ����������� ������� ����� ( ������� 10 ��)
  //---------------------------------------------------------------------------//
  MDR_PORTB->OE = 0xFFFF;               // ���� B �� �����, PB9, PB10 - ���������� ������ ����������������� RS485 �� UART2
  MDR_PORTB->FUNC = 0x0000;             // ������� - ����, PB0 - �������������� �������
  MDR_PORTB->ANALOG  = 0xffff;          // ����� ����� - ��������
  MDR_PORTB->PWR     = 0xFFFFFFFF;      // ����������� ������� ����� ( ������� 10 ��)
  //---------------------------------------------------------------------------//  
  MDR_PORTC->OE     = 0xffff;                    
  MDR_PORTC->FUNC   = 0x0000;                
  MDR_PORTC->ANALOG = 0xFFFF;      
  MDR_PORTC->PWR    = 0xFFFFFFFF;       // ����������� ������� �����
  //---------------------------------------------------------------------------//
  MDR_PORTD->OE = 0x007f;               // ���� D �� ����, PD7 - ADC_CH7
  MDR_PORTD->FUNC = 0x0000;             // ������� - ���� 
  MDR_PORTD->ANALOG  = 0xff7f;          // ����� ����� - ��������, �� PD7 - ADC_CH7
  MDR_PORTD->PWR     = 0xFFFFFFFF;      // ����������� ������� ����� ( ������� 10 ��)
  MDR_PORTD->PD      =  0x0000;
  //---------------------------------------------------------------------------//
  MDR_PORTE->OE = 0xffff;               // ���� E �� �����
  MDR_PORTE->FUNC = 0x0000;             // ������� - ���� 
  MDR_PORTE->ANALOG  = 0xfff0;          // ����� ����� - ��������, PE0 - DAC2 out
  
  //---------------------------------------------------------------------------//
  MDR_PORTF->OE = 0xffb7;               // ���� F �� �����,PF3 - RxD
  MDR_PORTF->FUNC = (2 << 6) |		    // �����  ����� 1, 2, 3, 4 ����� 
					(2 << 4) |			// - ��������������, ������������ ������ SSP1
					(2 << 2) |
					(2 << 0);
  MDR_PORTF->ANALOG  = 0xffff;          // ����� ����� - ��������
  MDR_PORTF->PWR     = 0xFFFFFFFF;      // ����������� ������� ����� ( ������� 10 ��)

   }
 
  void timer1_init(void) {
          
  // ��������� ������� ��� ������ ������� ��������� ������ -> \_ 
          
  MDR_TIMER1->CNTRL = 4<<8;                               // �������� ������� - ������� �� 1 ������ ������ 1� 
  MDR_TIMER1->CH1_CNTRL = (1<<15) | (1<<4);               // ����� �������� � ������ ������ | ������������� �����
  MDR_TIMER1->CH1_CNTRL1 = 0;
  MDR_TIMER1->CNT   = 0;                                  // ��������� �������� �������� - 0
  MDR_TIMER1->PSG   = 0;                         	  // ������������ ������� ������������ �1 - 1
  MDR_TIMER1->ARR   = 0xffff;                             // ��������� �����, ������ ������ �� 65535
  MDR_TIMER1->IE    = (1<<5)|(1<<13);                     // ���������� ���������� �� ��������� � ������� ������ 1 ������
  MDR_RST_CLK->TIM_CLOCK  |= (1 << 24);                   // �������� �������|���������� ������������ ������� 1
  MDR_TIMER1->STATUS= 0;                                  // ���������� �����
  
 }

  void timer3_init(void) {
          
  // ��������� ������� ��� ���������� ������ ~ 100 ���
          
 MDR_RST_CLK->TIM_CLOCK  |= (1 << 26);           // ���������� ������������ Timer1, TIM1_CLK = HCLK/8 												
 MDR_TIMER3->PSG   = 0;               		 // ������������ ������� = 0
 MDR_TIMER3->CNTRL = 0x00000000;        	 // ����������� ����� ��������� �������� �� ���� �� ARR,
						 // ��������� �������� - ����� �� �������� CNT 
 MDR_TIMER3->ARR   = 7999;                	 // ��������� �����
 MDR_TIMER3->CNT   = 0;       	                 // ��������� �������� �������� 
 MDR_TIMER3->IE    = (1 << 1);                   //���������� ���������� �� ����������

}
      
/*=========================================================================== */
// UART
  void Uart1_init (void){
//UART	  
  MDR_RST_CLK->PER_CLOCK |= (1UL << 22); //������������ ����� B
  MDR_PORTB->FUNC |= ((2 << 5*2) | (2 << 6*2)); //����� ������ �����
  MDR_PORTB->ANALOG |= ((1 << 5) | (1 << 6)); //��������
  MDR_PORTB->PWR |= ((3 << 5*2) | (3 << 6*2)); //����������� ��c����

 //��������� �������� ��� ������� = 80 ��� � �������� = 115200
MDR_UART1->IBRD = 43;   // ����� ����� �������� ��������
MDR_UART1->FBRD = 26;   // ������� ����� �������� ��������

MDR_UART1->LCR_H = ((0 << 1) // ������ ��� ������� �������� 
                   |(0 << 2) // ��� �������� ��������
                   |(0 << 3) // ���-�� �������� ��� = 1
                   |(0 << 4) // ��������� ������ FIFO, 0 - ����
                   |(3 << 5) // ������ ����� - 8 ���
                   |(0 << 7)); // �������� ���� �������� ���������

MDR_UART1->IMSC = (1 << 4); // ���������� �� ���������
MDR_UART1->CR = ((1 << 8)|(1 << 9) | 1);  // ������ ��������� � ����������� ���������
}
  
  void Uart2_init (void){
// ������������� ������ UART2
	  
MDR_PORTD->FUNC   |= ((2 << 2) | (2 << 0)); // ����� ������ ����� - UART2
MDR_PORTD->ANALOG |= ((1 << 1) | (1 << 0)); // �������� ����
MDR_PORTD->PWR    |= ((3 << 2) | (3 << 0)); // ����������� ��c���� �����

 //��������� �������� ��� ������� = 80 ��� � �������� = 115200
MDR_UART2->IBRD = 43;   // ����� ����� �������� ��������
MDR_UART2->FBRD = 26;   // ������� ����� �������� ��������

MDR_UART2->LCR_H = ((0 << 1) // ������ ��� ������� �������� 
                   |(0 << 2) // ��� �������� ��������
                   |(0 << 3) // ���-�� �������� ��� = 1
                   |(0 << 4) // ��������� ������ FIFO, 0 - ����
                   |(3 << 5) // ������ ����� - 8 ���
                   |(0 << 7)); // �������� ���� �������� ���������

MDR_UART2->IMSC = (1 << 4); // ���������� �� ���������
MDR_UART2->CR = ((1 << 8)|(1 << 9) | 1); 
}
  
  void Uart1_send_hex(U8 hex_data){
	  
      // ���� �����   FIFO   �����������   ��������...  
	while(MDR_UART1->FR & (1<<5)) { }; // ���� ���������� UART1;

    MDR_UART1->DR = hex_data;
  
	}
  
  void Uart2_send_hex(U8 hex_data){
	  
      // ���� �����   FIFO   �����������   ��������...  
	while(MDR_UART2->FR & (1<<5)) { }; // ���� ���������� UART2;

    MDR_UART2->DR = hex_data;
  
	}
	  
  void Uart1_CR_LF_send (void){
	  
        Uart1_send_hex(0x0A);
	Uart1_send_hex(0x0D);
	
	}
  
  void Uart2_CR_LF_send (void){
	  
        Uart2_send_hex(0x0A);
	Uart2_send_hex(0x0D);
	
	}

  void Uart1_num_send(int32_t data){
	  
  unsigned char temp[10],count=0;
  if (data<0) 
  {
    data=-data;
    Uart1_send_hex('-');
  }     
  if (data)
  {
    while (data)
    {
      temp[count++]=data%10+'0';
      data/=10;                 
    }                           
    while (count)           
      Uart1_send_hex(temp[--count]);          
  }
  else Uart1_send_hex('0');           
}

  void Uart2_num_send(int32_t data){
	  
  unsigned char temp[10],count=0;
  if (data<0) 
  {
    data=-data;
    Uart2_send_hex('-');
  }     
  if (data)
  {
    while (data)
    {
      temp[count++]=data%10+'0';
      data/=10;                 
    }                           
    while (count)           
      Uart2_send_hex(temp[--count]);          
  }
  else Uart2_send_hex('0');           
}

  void Uart1_send_text(unsigned char *s){
  while (*s != 0)
    Uart1_send_hex(*s++);
}

  void Uart2_send_text(unsigned char *s){
  while (*s != 0)
    Uart2_send_hex(*s++);
}

/*=========================================================================== */

/*=========================================================================== */
// Interupts
	
__irq void UART1_IRQHandler( void )
 //������� ��������� ���������� irq UART1
{
  /// ���������� ��������� ��� ����������� 1 ����� �� UART1
        
        // ��������������� ������ �� ����������� ��������� � RS485
        RS485_TX_EN;                    // ���������� �����������
        //MDR_TIMER3->CNTRL |= 1;         // ������ �3, ������ ������� ������� ���������� �����������
        MDR_UART2->DR  = MDR_UART1->DR; 
        //Status_LED_OFF; // ����� ��������� ��������� ��� ��������� ���������� RS485
        MDR_UART1->ICR  = 1<<4; // ����� ���������� �� ���������  
        //MDR_TIMER3->CNT = 0;     // ��������� ����. �������� �� 0
}

__irq void UART2_IRQHandler( void )
 //������� ��������� ���������� irq UART2
{
  /// ���������� ��������� ��� ����������� 1 ����� �� UART2
        
        // ��������������� ������ �� RS485 � ���������� ����������
  
        MDR_UART1->DR  = MDR_UART2->DR; 
        MDR_UART2->ICR  = 1<<4; // ����� ���������� �� ���������  
}


__irq void Timer1_IRQHandler(void) 

{    

     MDR_TIMER1->CNT = 0;                  // ��������� ����. �������� �� 0
     MDR_TIMER1->STATUS = 0;        // ����� ������� ���������� �� ������. ������ �� ������ 3 �1 
}

__irq void Timer3_IRQHandler(void) 
{ 
  RS485_TX_DIS;            // ������ �����������
  MDR_TIMER3->CNTRL &= ~1;
  MDR_TIMER3->STATUS = 0;  // ����� ������� ���������� �� \_ �� ������ 1 �3  
}

/*=========================================================================== */
/*=========================================================================== */

  void MCU_init (void) {
	  
 	 OSC_init();
	 SysTickTimer_Init();
 	 GPIO_init();  
	 //timer1_init();
         timer3_init();
         
         MDR_RST_CLK->PER_CLOCK |= (1 << 7) | (1 << 6);    // ���. ������������ UART1 � UART2
         MDR_RST_CLK->UART_CLOCK = (0                      // ��������� �������� ��� UART1 = 1
                          |(0 << 8)                        // ��������� �������� ��� UART2 = 1
                          |(1 << 24)                       // ���������� �������� ������� UART1
                          |(1 << 25));                     // ���������� �������� ������� UART2 
         
         Uart1_init();           // UART1 - ���������� ����������������
         Uart2_init();           // UART2 - rs485

	}

/*=========================================================================== */
// MAIN  

 int main()
{     
 MCU_init();	// ������������ ������ ������������, ������, SPI � UART  
 
 RS485_RX_EN;  // ���. ���������   RS485
 RS485_TX_DIS; // ���. ����������� RS485
 
 //NVIC_EnableIRQ(Timer1_IRQn); // ���������� ���������� ��� T1 - ������� ������
 //NVIC_EnableIRQ(Timer3_IRQn); // ���������� ���������� ��� T3 - �-���������
 NVIC_EnableIRQ(UART1_IRQn);    // ���������� ���������� ��� UART1, ������ -> RS485
 //NVIC_EnableIRQ(UART2_IRQn);  // ���������� ���������� ��� UART2, RS485 -> ������ 
 __enable_irq();	        // Enable Interrupts global
 //MDR_TIMER1->CNTRL |= 1;      // ������ �1
 
 delay_ms(2000);
 
 Uart1_send_text("AT+CWMODE=3");	
 Uart1_send_hex(0x0D);
 Uart1_send_hex(0x0A);
 delay_ms(100);
 
 Uart1_send_text("AT+CIPMUX=1");	
 Uart1_send_hex(0x0D);
 Uart1_send_hex(0x0A);
 delay_ms(100);
 
 Uart1_send_text("AT+CIPSERVER=1,4001");	
 Uart1_send_hex(0x0D);
 Uart1_send_hex(0x0A);	
 delay_ms(1000);
 
 unsigned char* msg = "11110000";
 //Uart2_num_send(sizeof(*msg));
 while(1)
  {


    Uart1_send_text("AT+CIPSEND=0,4");
    
    Uart1_send_hex(0x0D);
    Uart1_send_hex(0x0A);
    
    delay_ms(1);
    Uart1_send_text(msg);

    delay_ms(2000);

	
    
  } // while  
} // main
