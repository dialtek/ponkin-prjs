/// ������� ��� ,��������� ��� ����������������  
/// ���������� - ���� ������������ ������������� �������� ��������� ������ �����-6�

#include "MDR32Fx.h"

#define F_CPU 80000000

#define U8  uint8_t
#define U16 uint16_t 
#define S16 int16_t 
#define U32 uint32_t
#define S32 int32_t

#include "mdr_delay.h"

// ������� ������� � ��������� ����� ��������������� ������ � ����
#define HV_SUPPLY_ON  	MDR_PORTC->RXTX |=  1   
#define HV_SUPPLY_OFF   MDR_PORTC->RXTX &= ~1

#define SYNC_LED_ON  	MDR_PORTE->RXTX |=  1<<3 
#define SYNC_LED_OFF  	MDR_PORTE->RXTX &= ~(1<<3) 

// ������ ���������� ������ ��� ��� ������ 
#define RXFE                1<<4                    // ����� 1 ���� ���� ����� FIFO ��������� 
#define FIFO_has_byte       !(MDR_UART1->FR & RXFE)
#define CH1_CCR_CAP_EVENT   (1<<13)                 // ������� ?���������? ������ �� ����� CAP ������� ������� 
                                                    // ��� 7 � ������ �����
#define ADC_Vref            3.3		    // ���������� ����������� ���������� ������� ��

#define Status_LED_ON     MDR_PORTA->RXTX |= 1 << 3 
#define Status_LED_OFF    MDR_PORTA->RXTX &= ~(1 << 3)
#define Error_LED_ON      MDR_PORTA->RXTX |= 1 << 4 
#define Error_LED_OFF     MDR_PORTA->RXTX &= ~(1 << 4)

#define du 1.12 // ����������� ��� ���������� �������� ��� � �������� ���

//============================== RS485 defines =================================
#define RS485_RX_EN     MDR_PORTB->RXTX |=  1<<9   // ���.  �������� RS485   _/
#define RS485_RX_DIS    MDR_PORTB->RXTX &= ~(1<<9) // ����. �������� RS485   
#define RS485_TX_EN     MDR_PORTB->RXTX &= ~(1<<10)// ���.  ���������� RS485 \_
#define RS485_TX_DIS    MDR_PORTB->RXTX |=  1<<10  // ����. ���������� RS485 

#define modbus_rhr_cmd  0x03    // read holding registers cmd id
#define modbus_wsr_cmd  0x06    // write single register cmd id

#define com_dev_id 0            // � ����������������� ������ ������������ ����� 0
#define dev_id 100              // modbus id �������� ����������
#define max_regs_cnt    125     // ����. ���-�� ��������� ��� ������ �� 1 ���

#define volt_lvl_reg    1000     // ����� �������� ����������� ���������� � HV-��������
//==============================================================================

//================================ state-machine ===============================
#define detect_dev_id      10      // ��� 0 ��������� ���.��������
#define get_cmd_header     11      // ��� 1 ��������� ���.��������
#define get_reg_addr_msb   12      // ��� 2 ��������� ���.��������
#define get_reg_addr_lsb   13      // ��� 3 ��������� ���.��������
#define get_reg_cnt_msb    14      // ��� 4 ��������� ���.��������
#define get_reg_cnt_lsb    15      // ��� 5 ��������� ���.��������
#define calc_crc1          16      // ��� 6 ��������� ���.��������
#define calc_crc2          17      // ��� 7 ��������� ���.��������
#define send_answer        18      // ��� 8 ��������� ���.��������


U8 wr_ptr = 0, rd_ptr = 0;   // �������� ������ � ������ � ������ UART
U8 rx_buf[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}; // ����� ��� ����. ��������� ������
//==============================================================================

  U8 need2send = 0;    // ���� ������� �� ������ ������ �� UART	
  U8 need2update = 0; 
  U8 need2setDAC = 0;  // ���� ���������� ���������� DAC

  U32 MCU_current_ADC_channel = 0;
  U16 MCU_ADC_aver_param = 1000;   // �������� ����������� ������ ���
  S32 DAC_code = 0;                // ��� DAC - ���������� �������� ����������� 
  S32 ADC_code = 0;                // ������� ��� ���������� �� HV-�����
  float k = 0;          // ���������������� ����������� �-����������
  S32 error = 0;        // ������ ��������� ��� � ���� ��� 
  S32 mDAC_code = 0;    // ����������������� �������� ���� ���
  S16 ADC_zero_lvl = 0; // ����� 0 ��� 

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
  }
   
  void GPIO_init (void){  
  
  MDR_PORTA->OE      = 0xFFFD;          //  PA1 - ���� �������������
  MDR_PORTA->FUNC    = (2<<2);          // ������� - ����, ��� ��5 �������������� ������� 
  MDR_PORTA->ANALOG  = 0xFFFF;          // ����� ����� - ��������
  MDR_PORTA->PWR     = 0xFFFFFFFF;      // ����������� ������� ����� ( ������� 10 ��)
  //---------------------------------------------------------------------------//
  MDR_PORTB->OE = 0xFFFE;               // ���� B �� �����, PB0 - ���� ������� �������������
  MDR_PORTB->FUNC = 0x0002;             // ������� - ����, PB0 - �������������� �������
  MDR_PORTB->ANALOG  = 0xffff;          // ����� ����� - ��������
  MDR_PORTB->PWR     = 0xFFFFFFFF;      // ����������� ������� ����� ( ������� 10 ��)
  //---------------------------------------------------------------------------//  
  MDR_PORTC->OE     = 0xffff;                    
  MDR_PORTC->FUNC   = 0x0000;                
  MDR_PORTC->ANALOG = 0xFFFF;      
  MDR_PORTC->PWR    = 0xFFFFFFFF;       // ����������� ������� �����
  //---------------------------------------------------------------------------//
  MDR_PORTD->OE = 0x00ca;               // ���� D �� ����, PD2 - ADC_CH2, PD4 - ADC_CH4, PD5 - ADC_CH5
  MDR_PORTD->FUNC = 0x0000;             // ������� - ���� 
  MDR_PORTD->ANALOG  = 0xffcb;          // ����� ����� - ��������, �� PD2 - ADC_CH2, PD4 - ADC_CH4, PD5 - ADC_CH5
  MDR_PORTD->PWR     = 0xFFFFFFFF;      // ����������� ������� ����� ( ������� 10 ��)
  MDR_PORTD->PD =     ((0 << (2 << 16))); //����� ������ ����� 2 = ���
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
          
  // ��������� ������� ��� ���������� ������ 100 ���    
 MDR_RST_CLK->TIM_CLOCK  |= (1 << 26);           // ���������� ������������ Timer1, TIM1_CLK = HCLK/8 												
 MDR_TIMER3->PSG   = 0;               		 // ������������ ������� = 0
 MDR_TIMER3->CNTRL = 0x00000000;        	 // ����������� ����� ��������� �������� �� ���� �� ARR,
						 // ��������� �������� - ����� �� �������� CNT 
 MDR_TIMER3->ARR   = 7999;                	 // ��������� �����
 MDR_TIMER3->CNT   = 0;       	                 // ��������� �������� �������� 
 MDR_TIMER3->IE    = (1 << 1);                   //���������� ���������� �� ����������

}
      
/*=========================================================================== */
// ADC MCU
  void MCU_ADC_init(){

  MDR_RST_CLK->PER_CLOCK |= (1 << 17); //������������ ���
  
  MDR_ADC->ADC1_CFG = (1 //��������� ���  
  |(0 << 2)   	// �������� �������������*/
  |(1 << 3)   	// ����� ������� ������� ��� - ������. 
  |(0 << 4)  	// ����� ������ ��������������*/ - �� �����, ��� ��� ��������� ����� �����
  |(1 << 9)  	// ������������ �������� (������������ ������, ��������� � �������� ������ ������)
  |(0 << 10) 	// �������������� �������� ������� ����.
  |(0 << 11)  	// �������� �������� - ���������� (VDD)
  |(2 << 12)  	// ����������� ������� ������� ADC_clk = HCLK/4
  |(0 << 16)  	//  ������ ���� ��� ����������� ����.
  |(0 << 17)    //  TS_EN ������ ����������� � ��������� �������� ���������� ����
  |(0 << 18)    // TS_BUF_EN ��������� ��� ������� ����������� � ��������� �������� ���������� ����.
  |(0 << 19) 	// ��������� ������� ����������� ����./
  |(0 << 20));  // ��������� ��������� �������� ���������� �� 1.23 � ����
}

  void MCU_ADC_start_conv(void){
  
  	MDR_ADC->ADC1_CFG |= 1<<1;
  
}

  U32 MCU_ADC_read(void){
	  
	  // ������ ���, t ������� + t �������������� ������ = 3.2 ��� ��� HCLK = 10� � ������������ ��� = 1
	  //		     t ������� + t �������������� ������ = 0.5 ��� ��� HCLK = 70� � ������������ ��� = 1					
	  // ��� �������� ������� ��� = 3,3/4095 = 0,8 ��
	  
	  U32 ADC_data = 0;
	  
  	  MCU_ADC_start_conv(); // ������ �������������� ������
	  
	  while(!(MDR_ADC->ADC1_STATUS) & (1<<2)) {} // ���� ���������� 
	  ADC_data = MDR_ADC->ADC1_RESULT;			 // ������
	  
	  MCU_current_ADC_channel = ADC_data << 11;  //����������� ����� 
	  MCU_current_ADC_channel = MCU_current_ADC_channel >> 27;  //������ ��� ���������
	  
	  ADC_data = ADC_data << 20;    // ����������� ���� � 
	  ADC_data = ADC_data >> 20;    // ������ ���������
	  
	  return ADC_data;
}

  void MCU_ADC_set_ch(U8 channel){
	  
	if (channel > 16) return;
	
	MDR_ADC->ADC1_CHSEL = 1 << channel; 
	
	
}

  U32 MCU_ADC_Rd_average(U16 AverValue){
	  
	  // ������ ���, t ������� + t �������������� ������ = 3.2 ��� ��� HCLK = 10� � ������������ ��� = 1
	  // t ������� + t �������������� ������ = 0.5 ��� ��� HCLK = 70� � ������������ ��� = 1	
	  // ���������� ����������� �������������� ���
	  
	  U32 Aver_ADC_data = 0;
	  
	  for(int i = 0; i < AverValue; i++ )
	  {
	   Aver_ADC_data += MCU_ADC_read();
	  }
  
	  Aver_ADC_data = Aver_ADC_data/AverValue; 
	  
	  return Aver_ADC_data;
}

  U32 Get_ADC_ch_voltage(U8 ADC_channel){
	  // ������ ������������ ���������� ��������. ������ ���, �������������� � ��
	  
	  U32 ADC_rd_data = 0;
 	  U32 ADC_meas_voltage = 0;
	  
	  MCU_ADC_set_ch(ADC_channel);	// ��������� ������ ���
	  ADC_rd_data = MCU_ADC_Rd_average(MCU_ADC_aver_param);		// ������ ������� �������� �������� ���
	  ADC_meas_voltage = (U32)((ADC_Vref*ADC_rd_data*1000)/4096);	// ����������� � �����  
	  return ADC_meas_voltage; 

}
/*=========================================================================== */

/*=========================================================================== */
// UART
  void Uart_init (void){
//UART	  
  MDR_RST_CLK->PER_CLOCK |= (1UL << 22); //������������ ����� B
  MDR_PORTB->FUNC |= ((2 << 5*2) | (2 << 6*2)); //����� ������ �����
  MDR_PORTB->ANALOG |= ((1 << 5) | (1 << 6)); //��������
  MDR_PORTB->PWR |= ((3 << 5*2) | (3 << 6*2)); //����������� ��c����

  MDR_RST_CLK->PER_CLOCK |= (1UL << 6); //������������ UART1
  MDR_RST_CLK->UART_CLOCK = (4 /*��������� �������� ��� UART1 = */
  |(0 << 8) /*��������� �������� ��� UART2 = undefined*/
  |(1 << 24) /*���������� �������� ������� UART1*/
  |(0 << 25)); /*���������� �������� ������� UART2*/ 
  
    //��������� �������� ��� ������� = 5000000�� � �������� = 115200
MDR_UART1->IBRD = 0x2; 					// ����� ����� �������� ��������
MDR_UART1->FBRD = 0x2e; 				// ������� ����� �������� ��������
MDR_UART1->LCR_H = ((0 << 1) 				// ���������� �������� ��������
  |(0 << 2) 						// ��������/����������
  |(0 << 3) 						// ����-���
  |(0 << 4) 						// ����. ������ FIFO ��������� � ����������� 12 ���, ������� 16 ����
  |(3 << 5) 						// ����� ����� = 8 ���
  |(0 << 7)); 						// �������� ���� ��������

MDR_UART1->IMSC = 1 << 4;                // RXIM ���������� ���������� �� ��������� UARTRXINTR. 1 � �����������;   
//MDR_UART1->IMSC = (1 << 10) | (1<<4 );     // �������������  ���������  ����������  ��  ������������  ������ UARTOEINTR 
//MDR_UART1->IFLS = 1<<4;                    // ���������� ���������� �� ������. 1/2 ������ ����

MDR_UART1->CR = ((1 << 8)|(1 << 9)|1);     // ��������� � �������� ��������, 
}
	
  void Uart_send_hex(U8 hex_data){
	  
      // ���� �����   FIFO   �����������   ��������...  
	while(MDR_UART1->FR & (1<<5)) { }; // ���� ���������� UART1;

    MDR_UART1->DR = hex_data;
  
	}
	  
  void Uart_CR_LF_send (void){
	  
        Uart_send_hex(0x0A);
	Uart_send_hex(0x0D);
	
	}

  void Uart_num_send(int32_t data){
	  
  unsigned char temp[10],count=0;
  if (data<0) 
  {
    data=-data;
    Uart_send_hex('-');
  }     
  if (data)
  {
    while (data)
    {
      temp[count++]=data%10+'0';
      data/=10;                 
    }                           
    while (count)           
      Uart_send_hex(temp[--count]);          
  }
  else Uart_send_hex('0');           
}

  void Uart_text_send(unsigned char *s){
  while (*s != 0)
    Uart_send_hex(*s++);
}

/*
__irq void UART1_IRQHandler( void )
 //������� ��������� ���������� irq UART
{
  /// ���������� ��������� ��� ����������� 8 ���� � ����� FIFO ��������� UART !!
         // 12 ���. ����� FIFO, ������� 16 ���� - 7�0 �������� ������ 
         U16 Rx_data[16];
         U8 rd_byte_cntr = 0;
         while(FIFO_has_byte)
         {
          Rx_data[rd_byte_cntr] = MDR_UART1->DR;
          Rx_data[rd_byte_cntr] &= 0x00ff; // ����������� �� �������  ���  ��������� 
          rd_byte_cntr++;
         }
         
         switch(Rx_data[0])      // ������� ���� - ��������� �������  
         {
              case 'U':          // ������� ������� ���������� ��������� ��� ��
                need2send = 1;   // ������ �������, ��������� ���� ������� �� ��
              break;
              //--
              case 'D':          // ������� ������� ���������� ��������� ��� 1,2,3 
                //MDR_TIMER3->CNTRL &= ~1; // ������ ���������� ��� T3 ��� ���. ����� ��������
                DAC_code = (S32)((Rx_data[2]<<8) + Rx_data[1]);
                need2setDAC = 1; // ������� ��������, ��������� ���� ��������� ����� ����. DAC
              break;

              //--
              default: 
                Uart_text_send("error"); // ����������� �������
                Uart_CR_LF_send();   
          }// switch
         
         MDR_UART1->RSR_ECR = 0x00000000;  //����� ������� ���������� FIFO
                                           // ����� ���������� �� ��������� UARTRXINTR
         MDR_UART1->ICR  = 1<<4 | 1 << 10; // ����� ���������� �� ������������ ������ UARTOEINTR 
         
}
	
__irq void Timer1_IRQHandler(void) 
//������� ��������� ���������� irq Timer 1 - ������ ������� �������������
{    
  U8 int_flag = MDR_TIMER1->STATUS; // ����. ����� ���������� ���������� �� �1 
  
  //if(int_flag & CH1_CCR_CAP_EVENT) //��������� ���������� ��������� ������ MDR_TIMER3->CH1    
  //{   
      Uart_num_send(int_flag);
      Uart_CR_LF_send();   
  //}

     MDR_TIMER1->CNT = 0;                  // ��������� ����. �������� �� 0
     MDR_TIMER1->STATUS = 0;        // ����� ������� ���������� �� ������. ������ �� ������ 3 �1 
}

*/

__irq void UART1_IRQHandler( void )
 //������� ��������� ���������� irq UART1
{
  /// ���������� ��������� ��� ����������� 1 ����� �� UART1
        wr_ptr++;               // ��������� �������� ���������� ����
        rx_buf[wr_ptr & 0x0f] = MDR_UART1->DR; 
      
        MDR_UART1->ICR  = 1<<4; // ����� ���������� �� ���������  
}


__irq void Timer3_IRQHandler(void) 
{ 
  /// �-��������� ��� ��� ���������� HV, ���������� ������ 100 ���

  //if(DAC_code > 0)     // ��������� �������� ������ ��� ��������� ������ � ��
  //{
 
    MCU_ADC_set_ch(5); // ��������� ������ ��� � ��������� 
    ADC_code  = (S32)MCU_ADC_Rd_average(MCU_ADC_aver_param);     
    // ����� �-����������, �������������� ������
    error = (S32)(k*(DAC_code - ADC_code));  
    mDAC_code = DAC_code + error;          // ���� ������
   
    if(mDAC_code > 4000) mDAC_code = 4000; // �������� �� ������������ ����
    if(mDAC_code < 0) mDAC_code = 0;
    
    MDR_DAC->DAC2_DATA = (U32)mDAC_code;   // ������������� ������ �����
  //}
  MDR_TIMER3->CNT = 0;     // ��������� ����. �������� �� 0
  MDR_TIMER3->STATUS = 0;  // ����� ������� ���������� �� \_ �� ������ 1 �3  
}

/*=========================================================================== */
// DAC
  void MCU_DAC2_init (void){
    
    MDR_DAC->CFG = (0<<4) | // DAC1 DAC2 ����������
                   (1<<3) | // DAC2 enabled  
                   (0<<2) | // DAC1 disabled
                   (0<<1) | // DAC2 ref - AUcc voltage
                   (0<<1);  // DAC1 ref - AUcc voltage
  }

  char get_rx_ch (void)
{                                                     
// Get RX char
char rch;

   if (rd_ptr < wr_ptr) // ����� �� ����
   {
      rd_ptr++;                    // ��������� �������� �������� ����
      rch = rx_buf[rd_ptr & 0x0F]; // ����. �������� �� �������
   }
   else rch = 'x';   
   
   // ������ ���������� �� UART �� ����� ��������� ����������  
   // �� ����. � �����. �������� �������
   NVIC_DisableIRQ(UART1_IRQn);    
           
   if ((wr_ptr==rd_ptr) && (wr_ptr > 15)) // ���� ����� ��������                                            
   {  
      wr_ptr=0;                                                                   
      rd_ptr=0;                                                       
   } 

   NVIC_EnableIRQ(UART1_IRQn);         // ���������� ����������

return rch;
}

        //-------crc16
U16 modbus_CRC16(U8 buf[], int len)
{
  U16 crc = 0xFFFF;
  U8 crc_lsb, crc_msb;
  for (int pos = 0; pos < len; pos++)
  {
    crc ^= (U16)buf[pos];          // XOR byte into least sig. byte of crc
    for (int i = 8; i != 0; i--)
    {    // Loop over each bit
      if ((crc & 0x0001) != 0)
       {      // If the LSB is set
         crc >>= 1;                // Shift right and XOR 0xA001
         crc ^= 0xA001;
       }
       else                          // Else LSB is not set
         crc >>= 1;                  // Just shift right
     }
   }
  
   // Note, this number has low and high bytes swapped, 
   // so use it accordingly (or swap bytes)
   // swapping bytes
   crc = ((crc<<8)&0xff00)|((crc>>8)&0x00ff);
   
   return crc;
}
/*=========================================================================== */
 
  void MCU_init (void) {
	  
 	 OSC_init();
	 SysTickTimer_Init();
 	 GPIO_init();  
	 //timer1_init();
         timer3_init();
         
         Uart_init();           // UART1 - RS485
         MCU_DAC2_init();       // ������������� DAC2
  
	}
  
/*=========================================================================== */
// MAIN    
        
 int main()
{     
 U32 ADC_V = 0;
 U16 sample = 30222;
 //float ADC_scaled_V = 0.0;
 
 U8 rx_byte;       // ���� �������� � ��
 
 U8 ans_flag = 0;  // ���� ������������� ������ �� ������� ��

 U8 rd_state = detect_dev_id; // ������ ��������� �� ��������� ���� ��������� �� id ��������� modbus
 U16 modbus_reg_addr = 0;    // ����� �������� ��� R/W �� ������� �� modbus �������
 U16 temp_buf = 0;           // ��������� �����
 
 U16 regs2read = 0;          // ����� ��������� ��� ������ �� ������� modbus rhr
 U8  crc_buf[16];            // ����� ��� �������� ������ ��� ������� CRC16
 U16 CRC16 = 0;              // ��� �������� ����������� ����������� �����

 //S32 ADCc_DACc_delta = 11; // ������� �/� ��������� ��� � ���. ���������� �� � �����������.
 MCU_init();	// ������������ ������ ������������, ������, SPI � UART  
 MCU_ADC_init();
 
 NVIC_EnableIRQ(Timer1_IRQn); // ���������� ���������� ��� T1 - MODBUS
 NVIC_EnableIRQ(UART1_IRQn);  // ���������� ���������� ��� UART1
  //NVIC_EnableIRQ(Timer3_IRQn); // ���������� ���������� ��� T3 - �-���������
 
 delay_ms(500);  // �������� ��� ������ �������� �������� ��� ���. �������
 HV_SUPPLY_ON;   // ���. ������� ������� �������������� 3 �� ������������� 
 
 RS485_RX_EN; // ���. ���������   RS485
 RS485_TX_EN; // ���. ����������� RS485
 
 //MDR_TIMER3->CNTRL |= 1;      // ������ �3 --
 MDR_DAC->DAC2_DATA = 0;      // ����� �������� ���
 __enable_irq();	      // Enable Interrupts global
 
 //Status_LED_ON;  // �������� ��������� ���������

 while(1)
  {
       
    if(need2setDAC) // �������� ��� ���������� ���� DAC2 � ��
    {
   
      if(DAC_code > 4096) Uart_text_send("Error, your DAC code > 4096");
      else
      {
        k = 13; // �������� ����������������� ������������ ����������
        //MDR_DAC->DAC2_DATA = DAC_code;
        Uart_text_send("DAC=");         // ����� ������������ - ������������ 
        Uart_num_send(DAC_code);        // ��������� �������
        Uart_CR_LF_send();              
      }     
      need2setDAC = 0;                  // ����� ����� ���������� ���� ����
      
      Status_LED_OFF;
      delay_ms(10);
    }
    
    if(need2send) // ��������� ��������� ���������� � ������� �� ��
    { 
      ADC_V = Get_ADC_ch_voltage(5);
      //ADC_scaled_V = ADC_V * du;
      Uart_CR_LF_send();
      Uart_text_send("U: ");
      Uart_num_send(ADC_V);//(ADC_scaled_V);          // ������� ����������� ��������� �� ��
      Uart_CR_LF_send();
      need2send = 0;                        // ����� ����� ������� ������
     
      Status_LED_OFF;   
      delay_ms(10);
    } // if   
    
    
//----------------------------------------------------------------------------- 
// ��������� ������

    while(rd_ptr < wr_ptr) // ����� �� ����, ������� ���� 
    {                                     
       rx_byte = get_rx_ch();  
              
       switch(rd_state)  // �������� ������� ��������� ������ ������
       {
       //====
         case detect_dev_id:              // ���� ��������� � ����������
           switch(rx_byte)
           {
             case dev_id:                 // �������� ������� ��������� �� �������� id ����������
               rd_state = get_cmd_header; // ������� � ��������� �������� ��������� �������
             break;
             //----  
             case com_dev_id:             // �������� ������� ������������������ ���������
               rd_state = get_cmd_header; // ������� � ��������� �������� ��������� �������
             break;
             //----    
             default:                     // �������� ��� ������ ������� 
               rd_state = detect_dev_id;  // ������� � ������ id ������� modbus
            }
          break;
       //=====                          
         case get_cmd_header:             // ������ ������� modbus
           switch (rx_byte)
           { // ������� � ����. ��������� ������ �������� modbus
             case modbus_rhr_cmd: rd_state = get_reg_addr_msb;  break;          
             case modbus_wsr_cmd: rd_state = get_reg_addr_msb;  break; 
             // ������� � ����. ������ id ���������� � ������ ������ �������  
             default: rd_state = detect_dev_id;
           }
         break;
        //=====
         case get_reg_addr_msb:              // ��������� ��. ����� ������ ��������
             temp_buf = (U16)rx_byte;        // ����. ��. ����
             temp_buf = temp_buf << 8;
             rd_state = get_reg_addr_lsb;    // ������� � ����. ������ ��. �����
         break;
         //=====
         case get_reg_addr_lsb:              // ��������� ��. ����� ������ ��������
             temp_buf |= (U16)rx_byte;       // ����. ��. ����
            // ������� ����� �������?
             if(temp_buf == volt_lvl_reg)
             {  // ��, ������� � ����. ������ ����� ��������� ��� ������
                modbus_reg_addr = temp_buf;    // ����. ���������� ������ ��������� ��� ������
                rd_state = get_reg_cnt_msb;    // ������� � ����. ������ ��. �����
             }
             // �� �������, ������� � ����. ������ id ����������
             else  rd_state = detect_dev_id;
         break;
         
         case get_reg_cnt_msb:              // ��������� ��. ����� ���-�� ��������� ��� ������
             temp_buf = (U16)rx_byte;       // ����. ��. ����
             temp_buf = temp_buf << 8;
             rd_state = get_reg_cnt_lsb;
         break;
         //=====
         case get_reg_cnt_lsb:              // ��������� ��. ����� ���-�� ��������� ��� ������
             temp_buf |= (U16)rx_byte;      // ����. ��. ����
             // ���������� �����?
             if(temp_buf < max_regs_cnt)
             {  // ��
                regs2read = temp_buf;      // ���������� ����� ��������� ��� ������
                rd_state = calc_crc1;//detect_dev_id;       // ������� � ��������� ������� CRC16 
             }
             // ���, ������� � ����. ������ id ����������
             else   rd_state = detect_dev_id;  
          break;  
         //=====
         case calc_crc1:                     // ��������� ��. ����� CRC
             temp_buf = (U16)rx_byte;      // ����. ��. ����
             temp_buf = temp_buf << 8;
             rd_state = calc_crc2; 
         break; 
         //===== 
         case calc_crc2:                    // ��������� ��. ����� CRC
             temp_buf |= (U16)rx_byte;      // ����. ��. ����

             crc_buf[0] = dev_id;
             crc_buf[1] = modbus_rhr_cmd;
             crc_buf[2] = (U8)(modbus_reg_addr >> 8);
             crc_buf[3] = (U8)(modbus_reg_addr & 0x00ff);
             crc_buf[4] = (U8)(regs2read >> 8);
             crc_buf[5] = (U8)(regs2read & 0x00ff);
             
             CRC16 = modbus_CRC16(crc_buf,6);
             
             if(CRC16 == temp_buf) 
             {
               ans_flag = 1;
               rd_state = detect_dev_id;
             }
             else rd_state = detect_dev_id;
             
//             Uart_num_send(CRC16);
//             Uart_text_send("_");
//             Uart_num_send(temp_buf);
             
             
         break; 
         
         
        //===== 
          default: rd_state = detect_dev_id;    
        } // switch
       
       
       if(ans_flag)
       {
          
          ans_flag = 0;
          
          crc_buf[0] = dev_id;
          crc_buf[1] = modbus_rhr_cmd;
          crc_buf[2] = 2; // ���-�� ���� ������ 
          crc_buf[3] = (U8)(sample >> 8);
          crc_buf[4] = (U8)(sample & 0x00ff);
             
          CRC16 = modbus_CRC16(crc_buf,5);
                
          Uart_send_hex(dev_id);
          Uart_send_hex(modbus_rhr_cmd);
          Uart_send_hex(0x02); // ���-�� ���� ������ 
          Uart_send_hex((U8)(sample >> 8));     // msb
          Uart_send_hex((U8)(sample & 0x00ff)); // lsb
          Uart_send_hex((U8)(CRC16 >> 8));      // msb
          Uart_send_hex((U8)(CRC16 & 0x00ff));  // lsb
       }
         
    }  // while  
//---------------------------------------------
  } // while  
} // main


/*
      /// ------------- ���������� ����������-----------------
      Uart_text_send("DAC code: ");
      Uart_num_send(DAC_code);
      Uart_CR_LF_send();
      
      Uart_text_send("ADC_counts: ");
      Uart_num_send(ADC_code);
      Uart_CR_LF_send();
      
      Uart_text_send("error: ");
      Uart_num_send(error);
      Uart_CR_LF_send();
      
      Uart_text_send("mDAC_code: ");
      Uart_num_send((U32)mDAC_code);
      Uart_CR_LF_send();
      /// ---------------------------------------------------
      Uart_CR_LF_send();

*/
