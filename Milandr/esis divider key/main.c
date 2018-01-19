/// ������� ��� ,��������� ��� ����������������  
/// ���������� - ���� ���������� ��������� ������ 7 ��������� ������

#include "MDR32Fx.h"

#define F_CPU 80000000

#define U8  char
#define U16 unsigned short 
#define S16 signed short 
#define U32 unsigned long 
#define S32 signed long 

#include "mdr_delay.h"

// ������ ���������� ������ ��� ��� ������ 
#define RXFE                1<<4                    // ����� 1 ���� ���� ����� FIFO ��������� 
#define FIFO_has_byte       !(MDR_UART1->FR & RXFE)
#define CH1_CCR_CAP_EVENT   (1<<13)                 // ������� ?���������? ������ �� ����� CAP ������� ������� 
                                                    // ��� 7 � ������ �����
#define ADC_Vref            3.33		    // ���������� ����������� ���������� ������� ��

#define Status_LED_ON     MDR_PORTA->RXTX |= 1 << 3 
#define Status_LED_OFF    MDR_PORTA->RXTX &= ~(1 << 3)
#define Error_LED_ON      MDR_PORTA->RXTX |= 1 << 4 
#define Error_LED_OFF     MDR_PORTA->RXTX &= ~(1 << 4)

// ������������ ������ ������� IR2184, ������� ����� �������� � �������� ������
#define S1_ON      MDR_PORTB->RXTX |= 1 
#define S1_OFF     MDR_PORTB->RXTX &=~1
#define S2_ON      MDR_PORTB->RXTX |= 1 << 1
#define S2_OFF     MDR_PORTB->RXTX &=~(1 << 1)
#define S3_ON      MDR_PORTB->RXTX |= 1 << 2
#define S3_OFF     MDR_PORTB->RXTX &=~(1 << 2)

//================================ state-machine ===============================
#define detect_dev_id      10      // ��� 0 ��������� ���.��������
#define get_cmd_header     11      // ��� 1 ��������� ���.��������
#define get_modbus_word_msb   12   // ��� 2 ��������� ���.��������
#define get_modbus_word_lsb   13   // ��� 3 ��������� ���.��������
#define get_reg_cnt_msb    14      // ��� 4 ��������� ���.��������
#define get_reg_cnt_lsb    15      // ��� 5 ��������� ���.��������
#define calc_crc1          16      // ��� 6 ��������� ���.��������
#define calc_crc2          17      // ��� 7 ��������� ���.��������
#define get_modbus_word    18      // ��� 8 ��������� ���.��������

  U8 wr_ptr = 0, rd_ptr = 0;   // �������� ������ � ������ � ������ UART
  // ����� ��� ����. ��������� ������
  U8 rx_buf[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}; 
//==============================================================================

//============================== RS485 defines =================================
#define RS485_RX_EN     MDR_PORTB->RXTX &= ~(1<<10)  // ���.  �������� RS485   \_ 
#define RS485_RX_DIS    MDR_PORTB->RXTX |=  (1<<10)  // ����. �������� RS485   _/
#define RS485_TX_EN     MDR_PORTB->RXTX |=  (1<<9)   // ���.  ���������� RS485 _/
#define RS485_TX_DIS    MDR_PORTB->RXTX &= ~(1<<9)  // ����. ���������� RS485 \_

#define modbus_rhr_cmd  0x03    // read holding registers cmd id
#define modbus_wsr_cmd  0x06    // write single register cmd id

#define com_dev_id 0            // � ����������������� ������ ������������ ����� 0
#define dev_id 42               // modbus id �������� ����������                        <<<<<<<<<<=========================== ID
#define firmware_ver 1          // ������ �������� �������� ����������
#define device_family 4         // ��� ��������� ���������: 1 - PBF modules, 2 - extraction modules, 3 - dc hv modules, 4 - divider keys
#define max_regs_cnt    125     // ����. ���-�� ��������� ��� ������ �� 1 ���

#define volt_lvl_reg    1000    // ����� �������� ����������� ���������� � HV-��������

  U8 reg_addr_flag = 0;
  U8 reg_wr_flag = 0;
  U8 reg_qty_flag = 0;
  U8 get_crc_flag = 0;

  U8 rx_byte;       // ���� �������� � ��
 
  U8 answer = 0;    // ��� ������ �� ������� � ��
  U8 rd_state = detect_dev_id; // ������ ��������� �� ��������� ���� ��������� �� id ��������� modbus
  U16 modbus_reg_addr = 0;     // ����� �������� ��� R/W �� ������� �� modbus �������
  U16 temp_buf = 0;            // ��������� �����
 
  U16 regs2read = 0;           // ����� ��������� ��� ������ �� ������� modbus rhr
  U8  crc_buf[250];            // ����� ��� �������� ������ ��� ������� CRC16
  U16 CRC16 = 0;               // ��� �������� ����������� ����������� �����
  U16 addr_buf_1, addr_buf_2;

  U16 reg_wr_data = 0;
  U16 holding_register[125];   // ����� ��� �������� ���������� ������, ����. ����� ��������� - 124
//==============================================================================

  U32 MCU_current_ADC_channel = 0;
  U16 MCU_ADC_aver_param = 20;    // �������� ����������� ������ ���
  S32 ADC_code = 0;               // ������� ��� ���������� �� HV-�����
  U32 ADC_V = 0;		  // ��� �������� �������� ����������� ���. ����������
  
  U16 resistor_sw_state = 0;      // ��������� ������������� ������: 0 - 510R, 1 - 1k, 2 - 2k

  
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
  MDR_PORTB->OE = 0xFFFF;               // ���� B �� �����, PB0 - S1, PB1 - S2, PB2 - S3
  MDR_PORTB->FUNC = 0x0000;             // ������� - ����
  MDR_PORTB->ANALOG  = 0xffff;          // ����� ����� - ��������
  MDR_PORTB->PWR     = 0xFFFFFFFF;      // ����������� ������� ����� ( ������� 10 ��)
  //---------------------------------------------------------------------------//  
  MDR_PORTC->OE     = 0xffff;                    
  MDR_PORTC->FUNC   = 0x0000;                
  MDR_PORTC->ANALOG = 0xFFFF;      
  MDR_PORTC->PWR    = 0xFFFFFFFF;       // ����������� ������� �����
  //---------------------------------------------------------------------------//
  MDR_PORTD->OE = 0xffd3;               // ���� D �� ����, PD2 - ADC_CH2, PD3 - ADC_CH3, PD5 - ADC_CH5
  MDR_PORTD->FUNC = 0x0000;             // ������� - ���� 
  MDR_PORTD->ANALOG  = 0xffd3;          // ����� ����� - ��������, �� PD2 - ADC_CH2, PD3 - ADC_CH3, PD5 - ADC_CH5
  MDR_PORTD->PWR     = 0xFFFFFFFF;      // ����������� ������� ����� ( ������� 10 ��)
  //---------------------------------------------------------------------------//
  MDR_PORTE->OE = 0xffbf;               // ���� E �� �����, PB6 - ���� - ������ ���. �������� ��������
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
          
  // ��������� ������� ��� ����������   
  MDR_RST_CLK->TIM_CLOCK  |= (1 << 24) | 3;      // ���������� ������������ Timer1, TIM1_CLK = HCLK/8 = 10���												

  MDR_TIMER1->CNTRL = 0x00000000;        	 // ����������� ����� ��������� �������� �� ���� �� ARR,
						 // ��������� �������� - ����� �� �������� CNT 
  MDR_TIMER1->PSG   = 1999;                       // ������������ ������� = 2000, TIM1_CLK = 5 ���
  MDR_TIMER1->ARR   = 4;                	 // ��������� ����� = 5, 200 ��� * 5 = 1 ��
  MDR_TIMER1->CNT   = 0;       	                 // ��������� �������� �������� 
  MDR_TIMER1->IE    = (1 << 1);                  // ���������� ���������� �� ����������

 }

  void timer3_init(void) {
          
  // ��������� ������� ��� ����������   
 MDR_RST_CLK->TIM_CLOCK  |= (1 << 26) | (3<<16);  // ���������� ������������ Timer3, TIM3_CLK = HCLK/8 = 10���													

 MDR_TIMER3->CNTRL = 0x00000000;        	 // ����������� ����� ��������� �������� �� ���� �� ARR,
						 // ��������� �������� - ����� �� �������� CNT 
 MDR_TIMER3->PSG   = 49999;                      // ������������ ������� = 50 000
 MDR_TIMER3->ARR   = 199;                	 // ��������� ����� = 200, 200 * 5 �� = 1000 ��
 MDR_TIMER3->CNT   = 0;       	                 // ��������� �������� �������� 
 MDR_TIMER3->IE    = (1 << 1);                   // ���������� ���������� �� ����������

}
      
/*=========================================================================== */
// ADC MCU
  void MCU_ADC_init(){

  MDR_RST_CLK->PER_CLOCK |= (1 << 17); //������������ ���
  
  MDR_ADC->ADC1_CFG = (0 //��������� ���  
  |(0 << 1)     // stop conv
  |(0 << 2)   	// �������� �������������*/
  |(1 << 3)   	// ����� ������� ������� ��� - ������. 
  |(0 << 4)  	// ����� ������ ��������������*/ - �� �����, ��� ��� ��������� ����� �����
  |(0 << 9)  	// ������������ ���������
  |(0 << 10) 	// �������������� �������� ������� ����.
  |(0 << 11)  	// �������� �������� - ���������� (VDD)
  |(3 << 12)  	// ����������� ������� ������� ADC_clk = HCLK/8 = 10 �
  |(0 << 16)  	//  ������ ���� ��� ����������� ����.
  |(0 << 17)    //  TS_EN ������ ����������� � ��������� �������� ���������� ����
  |(0 << 18)    // TS_BUF_EN ��������� ��� ������� ����������� � ��������� �������� ���������� ����.
  |(0 << 19) 	// ��������� ������� ����������� ����./
  |(0 << 20));  // ��������� ��������� �������� ���������� �� 1.23 � ����
}

  void MCU_ADC_start_conv(void){
  
  	MDR_ADC->ADC1_CFG |= 1<<1;
        MDR_ADC->ADC1_CFG |= 1;
}

  void MCU_ADC_stop_conv(void){
  
  	MDR_ADC->ADC1_CFG &= ~(1<<1);
        MDR_ADC->ADC1_CFG &= ~1;
}

  U32 MCU_ADC_read(void){
	  
	  // ������ ���, t ������� + t �������������� ������ = 3.2 ��� ��� HCLK = 10� � ������������ ��� = 1
	  // t ������� + t �������������� ������ = 0.5 ��� ��� HCLK = 70� � ������������ ��� = 1					
	  // ��� �������� ������� ��� = 3,3/4095 = 0,8 ��
	  
	  U32 ADC_data = 0;
	  
  	  MCU_ADC_start_conv(); // ������ �������������� ������
	  
	  //while(!(MDR_ADC->ADC1_STATUS) & 0x04) {}//(1<<2)) {} // ���� ����������, �� �� ��������
          delay_us(20);
	  ADC_data = MDR_ADC->ADC1_RESULT & 0x0FFF; // ������

	  return ADC_data;
}

  void MCU_ADC_set_ch(U8 channel){
	  
	if (channel > 15) return;
 
	MDR_ADC->ADC1_CFG  |= channel << 4; 
        delay_us(20);	
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
          delay_us(100);
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

/*========================================================================== */
// MODBUS

  char get_rx_ch (void)
  {                                                     
// Get RX char
char rch;

   if (rd_ptr < wr_ptr) // ����� �� ����
   {
      rd_ptr++;                    // ��������� �������� �������� ����
      rch = rx_buf[rd_ptr & 0x0f]; // ����. �������� �� �������
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

  U16 modbus_CRC16(U8 buf[], int len)
  {//-------crc16
  U16 crc = 0xFFFF;
  //U8 crc_lsb, crc_msb;
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

  void modbus_wsr_answer()
  { // ����� �� ������� ������ � �������
    // ������ CRC
    crc_buf[0] = dev_id;
    crc_buf[1] = modbus_wsr_cmd;
    crc_buf[2] = (U8)(modbus_reg_addr >> 8);
    crc_buf[3] = (U8)(modbus_reg_addr & 0x00ff);
    crc_buf[4] = (U8)(reg_wr_data >> 8);
    crc_buf[5] = (U8)(reg_wr_data & 0x00ff);
    CRC16 = modbus_CRC16(crc_buf, 6);

    //--------------------------------------------------------------------
    RS485_TX_EN;
    // �������� ������ �������
    Uart_send_hex(dev_id);                // ID ����������
    Uart_send_hex(modbus_wsr_cmd);        // ��� �������
    Uart_send_hex((U8)(modbus_reg_addr >> 8));           // ��. ���� ������ ��������
    Uart_send_hex((U8)(modbus_reg_addr & 0x00ff));       // ��. ���� ������ ��������
    Uart_send_hex((U8)(reg_wr_data >> 8));
    Uart_send_hex((U8)(reg_wr_data & 0x00ff));
     // �������� CRC
    Uart_send_hex((U8)(CRC16 >> 8));      // msb
    Uart_send_hex((U8)(CRC16 & 0x00ff));  // lsb  
    delay_ms(1);    
    RS485_TX_DIS;
          //--------------------------------------------------------------------
  }

  void modbus_rhr_answer()
  {
    // ����� �� ������� ������ ���������
  	  addr_buf_2 = addr_buf_1;             // ����. ����� ��� �������� � ���� ����������	  
          // ������ CRC
          crc_buf[0] = dev_id;
          crc_buf[1] = modbus_rhr_cmd;
          crc_buf[2] = regs2read*2;
          
          U8 cnt = 3;      // �������� �������� ������ ��� ������� CRC

          for(U8 i = 0; i < regs2read; i++)
          { // ���������� ������ CRC ��� �������
            crc_buf[cnt++] = (U8)(holding_register[addr_buf_1] >> 8);
            crc_buf[cnt++] = (U8)(holding_register[addr_buf_1] & 0x00ff);
            ++addr_buf_1;
          }
            // ������ CRC  
          CRC16 = modbus_CRC16(crc_buf,(regs2read*2)+3);
          //--------------------------------------------------------------------
          // �������� ������ �������
          RS485_TX_EN;
          Uart_send_hex(dev_id);                // ID ����������
          Uart_send_hex(modbus_rhr_cmd);        // ��� �������
          Uart_send_hex(regs2read*2);           // ���-�� ������������ ���� 

          for(U8 i = 0; i < regs2read; i++)
          {   // �������� ���� ������ � ����������� ������
            Uart_send_hex((U8)(holding_register[addr_buf_2] >> 8));     // msb
            Uart_send_hex((U8)(holding_register[addr_buf_2] & 0x00ff)); // lsb
            ++addr_buf_2;
          }
          // �������� CRC
          Uart_send_hex((U8)(CRC16 >> 8));      // msb
          Uart_send_hex((U8)(CRC16 & 0x00ff));  // lsb    
          delay_ms(1);
          RS485_TX_DIS;
          //--------------------------------------------------------------------
  }

/*========================================================================== */
// INTERRUPTS
__irq void UART1_IRQHandler( void )
 // ������� ��������� ���������� irq UART1
{
  /// ���������� ��������� ��� ����������� 1 ����� �� UART1
    wr_ptr++;               // ��������� �������� ���������� ����
    rx_buf[wr_ptr & 0x0f] = MDR_UART1->DR; 
    MDR_UART1->ICR  = 1<<4; // ����� ���������� �� ���������  
}

__irq void Timer3_IRQHandler ( void )
 // ������� ��������� ���������� irq Timer3 - ������ �� ����
{

  MDR_TIMER3->CNT = 0x0000;
  MDR_TIMER3->STATUS = 0x0000;
  NVIC_ClearPendingIRQ(Timer3_IRQn); // �����������!
}

__irq void Timer1_IRQHandler ( void )
 // ������� ��������� ���������� irq Timer1 - RAMP
{
 // ���������� 1 ��
 
  MDR_TIMER1->CNT = 0x0000;
  MDR_TIMER1->STATUS = 0x0000;
  NVIC_ClearPendingIRQ(Timer1_IRQn); // �����������!
}

/*=========================================================================== */

  void MCU_init (void) {
	  
 	 OSC_init();
	 SysTickTimer_Init();
 	 GPIO_init();  
	 //timer1_init();         // 
         //timer3_init();         // 
         
         Uart_init();           // UART1 - RS485
         MCU_ADC_init();
	}
  
/*=========================================================================== */
// MAIN    
        
 int main()
{  
 U32 led_delay_cnt = 0;
 U32 section_2_volt = 0;        // ���������� �������� ������. � �������� ������ 2
 U32 section_7_volt = 0;        // ���������� �������� ������. � �������� ������ 7
 U32 section_24_volt = 0;       // ���������� �������� ������. � �������� ������ 24
 
 for(U8 i = 0; i < 125; i++) holding_register[i] = 0; // ������� ������ ���������� ������
 
 MCU_init();	               // ������������ ������ ��
 //NVIC_EnableIRQ(Timer1_IRQn);  // ���������� ���������� T1
 //NVIC_EnableIRQ(Timer3_IRQn);  // ���������� ���������� T3
 NVIC_EnableIRQ(UART1_IRQn);   // ���������� ���������� UART1
 
 RS485_RX_EN;  // ���. ���������   RS485
 RS485_TX_DIS; // ���. ����������� RS485
 
 S1_OFF;
 S3_OFF;
 delay_ms(10);
 S2_ON;  // ������ �������� 1�
 resistor_sw_state = 1;
    
 __enable_irq();	      // Enable Interrupts global

 while(1)
  {     
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
               Status_LED_OFF;            // ��������� ��������� �������
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
           { 
             case modbus_rhr_cmd:                 // ������ ���������
                  reg_addr_flag = 1;              // ���. ����� ������ ������ ��������
                  regs2read = 0;
                  reg_wr_data = 0;
                  rd_state = get_modbus_word_msb; // ������� � ����. ��������� ���� ���� � ��
             break;      
             //---- 
             case modbus_wsr_cmd:                 // ������ � �������
                  reg_addr_flag = 1;              // ���. ����� ������ ������ ��������
                  reg_wr_flag   = 1;              // ���. ����� ������ � ������� 
                  regs2read = 0;
                  reg_wr_data = 0;
                  rd_state = get_modbus_word_msb; // ������� � ����. ��������� ���� ���� � �� 
             break; 
             //---- 
             // ������� � ����. ������ id ���������� � ������ ������  
             default: rd_state = detect_dev_id;
           }
         break;
        //=====
         case get_modbus_word_msb:              // ��������� ��. �����
             temp_buf = (U16)rx_byte;           // ����. ��. ����
             temp_buf = temp_buf << 8;
             rd_state = get_modbus_word_lsb;    // ������� � ����. ������ ��. �����
         break;
         //=====
         case get_modbus_word_lsb:              // ��������� ��. ����� 
             temp_buf |= (U16)rx_byte;          // ����. ��. ����
             /// ������ ������ ��� ���������� ��������
             if(reg_addr_flag)                 // ���� �������� ���� ������?
             {
               modbus_reg_addr = temp_buf;     // ����. ������ ���������� �������� ��� ������
               reg_addr_flag = 0;              // ����� ����� ������ ������
               if(reg_wr_flag) reg_qty_flag = 0; // ����� ����� ������ ����� ��������� ��� ������ ���� ���� ������� ������             
               else reg_qty_flag = 1;            // ���. ����� ������ ����� ��������� ��� ������ ���� ��� ������
               rd_state = get_modbus_word_msb;   // ������� � ����. ������ 2 ���� ���-�� ��������� ��� ������
               temp_buf = 0;                     // ��������� ���������� ������
               break;
             }
             
             if(reg_wr_flag)                   // ���� ������ � �������?
             { 
                reg_wr_data = temp_buf;        // ����. �������� ��� ������
                reg_wr_flag = 0;               // ����� ����� ������ � �������
                get_crc_flag = modbus_wsr_cmd; // ���. ���� ������� CRC ��� ������� ������
                rd_state = get_modbus_word_msb;// ������� � ����. ������ 2 ���� CRC
                break;
             }
             
             if(reg_qty_flag)                  // ���� ������ ��-�� ��������� ��� ������?
             { 
               if(temp_buf < max_regs_cnt)     // �������� �� ������ ����� ��������� ��� ������
               {  // ��
                regs2read = temp_buf;           // ���������� ����� ��������� ��� ������
                get_crc_flag = modbus_rhr_cmd;  // ���. ���� ������� CRC ��� ������� ������
                rd_state = get_modbus_word_msb; // ������� � ����. ������ 2 ���� CRC
               }
                 // ������, ������� � ����. ������ id ����������
               else rd_state = detect_dev_id; 
               reg_qty_flag = 0;                // ����� ����� ������ ���-�� ���������       
               break;
             }
             
             if(get_crc_flag == modbus_rhr_cmd)// ������ CRC16 ��� ������� ������ ���������
             {
                crc_buf[0] = dev_id;
                crc_buf[1] = modbus_rhr_cmd;
                crc_buf[2] = (U8)(modbus_reg_addr >> 8);
                crc_buf[3] = (U8)(modbus_reg_addr & 0x00ff);
                crc_buf[4] = (U8)(regs2read >> 8);
                crc_buf[5] = (U8)(regs2read & 0x00ff);
                CRC16 = modbus_CRC16(crc_buf,6); 
                if(CRC16 == temp_buf) 
                { 
                  answer = modbus_rhr_cmd;
                  rd_state = detect_dev_id;
                }
                else rd_state = detect_dev_id; 
                get_crc_flag = 0;              // ����� ����� ������� CRC16 
             }
               
             if(get_crc_flag == modbus_wsr_cmd)// ������ ��� ������� ������ � �������
             { 
                crc_buf[0] = dev_id;
                crc_buf[1] = modbus_wsr_cmd;
                crc_buf[2] = (U8)(modbus_reg_addr >> 8);
                crc_buf[3] = (U8)(modbus_reg_addr & 0x00ff);
                crc_buf[4] = (U8)(reg_wr_data >> 8);
                crc_buf[5] = (U8)(reg_wr_data & 0x00ff);
             
                CRC16 = modbus_CRC16(crc_buf,6);
                if(CRC16 == temp_buf) 
                {
                  answer = modbus_wsr_cmd;
                  rd_state = detect_dev_id;
                }
                else rd_state = detect_dev_id; 
                get_crc_flag = 0;
               }
              
         break; 
         //=====
          default: rd_state = detect_dev_id;    
        } // switch
    }  // while 
//---------------------------------------------   
    // ����� ��������� ��������� ��� ��������� ���������� RS485 ��� �������� ����������
    if(answer != 0) Status_LED_OFF;       
    // ������
    if(answer == modbus_rhr_cmd) // ����� ��� ������� ������ ���������
    {
         addr_buf_1 = modbus_reg_addr - 1000; // ����������� �� �������� � ������
         // ������ ��������� �� ���������
         holding_register[0] = resistor_sw_state;    // ��������� ������������� ������: 0 - 510R, 1 - 1k, 2 - 2k
         holding_register[3] = (U16)section_2_volt;  // ������. � �������� ������ 2
         holding_register[4] = (U16)section_7_volt;  // ������. � �������� ������ 7
         holding_register[5] = (U16)section_24_volt; // ������. � �������� ������ 24
         
         holding_register[13] = (U16)dev_id;                    // modbus id �������� ����������
         holding_register[14] = (U16)firmware_ver;              // ������ �������� �������� ����������
         holding_register[15] = (U16)device_family;             // ��������� ���������� 1 - PBF modules
 
         modbus_rhr_answer();    // ������� �������� ������������� ���������
         answer = 0;             // ����� ����� ������
     }
    //----------
    // ������ 
    if(answer == modbus_wsr_cmd) // ����� ��� ������� ������ � �������
    {
         addr_buf_1 = modbus_reg_addr-1000;          // ���������� �� ��������
         holding_register[addr_buf_1] = reg_wr_data; // ������ ���������� ������ � ������� �� ������
	 //--------------------------------------------------------------------
         // ���������� ���������� ������ ���������� ���������

         // ��������� ������������� ������: 0 - 510R, 1 - 1k, 2 - 2k
         resistor_sw_state = holding_register[0];     
         
         switch(resistor_sw_state)
         {
            case 0:               
              S3_OFF; 
              S2_OFF;
              delay_ms(10);
              S1_ON;    // ������ �������� 510R
            break;
            //---
            case 1:
              S1_OFF;
              S3_OFF;
              delay_ms(10);
              S2_ON;    // ������ �������� 1k
              
            break;
            //---
            case 2:
              S1_OFF;
              S2_OFF;
              delay_ms(10);
              S3_ON;    // ������ �������� 2k
            
         default: break;
         }
         
         modbus_wsr_answer();             // ������� ������ �� ������� ������ � �������
         answer = 0;                      // ����� ����� ������
     }     
//--------------------------------------------------------------------  
     // ��������� ���������� � ���������
     MCU_ADC_init();                             // ����� ���������� ��������
     MCU_ADC_set_ch(2);                          // ��������� ������ ��� 
     // ������ �������� ��� 
     ADC_code  = (S32)MCU_ADC_Rd_average(MCU_ADC_aver_param); 
     // �������������� � ����� ���������� �������� � ������ 24
     section_24_volt     = (U32)(ADC_code*0.8056640625);//ADC_Vref*1000.0)/4096.0);
     
     MCU_ADC_init();                             // ����� ���������� ��������
     MCU_ADC_set_ch(3);                          // ��������� ������ ��� 
     // ������ �������� ��� 
     ADC_code  = (S32)MCU_ADC_Rd_average(MCU_ADC_aver_param); 
     // �������������� � ����� ���������� �������� � ������ 7
     section_7_volt     = (U32)(ADC_code*0.8056640625);//ADC_Vref*1000.0)/4096.0);
     
     MCU_ADC_init();                             // ����� ���������� ��������
     MCU_ADC_set_ch(5);                          // ��������� ������ ��� 
     // ������ �������� ��� 
     ADC_code  = (S32)MCU_ADC_Rd_average(MCU_ADC_aver_param); 
     // �������������� � ����� ���������� �������� � ������ 2
     section_2_volt     = (U32)(ADC_code*0.8056640625);//ADC_Vref*1000.0)/4096.0);
//---------------------------------------------
    led_delay_cnt++;
    if(led_delay_cnt > 35)
    {
      Status_LED_ON;
      led_delay_cnt=0;
    }
    
  } // while  
} // main
