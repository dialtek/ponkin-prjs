/// ���� ������ � ����������� ��� ���-������� ���.

#include "MDR32Fx.h"

#define F_CPU 80000000

#define U8  uint8_t
#define U16 uint16_t 
#define S16 int16_t 
#define U32 uint32_t
#define S32 int32_t

#include "mdr_delay.h"


#define set_integrator      MDR_PORTC->RXTX = 0x0000  
#define reset_integrator    MDR_PORTC->RXTX = 0x0007 

#define SYNC_LED_ON  	MDR_PORTE->RXTX |=  1<<3 
#define SYNC_LED_OFF  	MDR_PORTE->RXTX &= ~(1<<3) 

// ������ ���������� ������ ��� ��� ������ 
#define RXFE                1<<4                    // ����� 1 ���� ���� ����� FIFO ��������� 
#define FIFO_has_byte       !(MDR_UART1->FR & RXFE)
#define CH1_CCR_CAP_EVENT   (1<<13)                 // ������� ?���������? ������ �� ����� CAP ������� ������� 
                                                    // ��� 7 � ������ �����
#define ADC_Vref            3.3		    // ���������� ����������� ���������� ������� ��

#define TRIG_LED_ON       MDR_PORTA->RXTX |= 1 << 6     
#define TRIG_LED_OFF      MDR_PORTA->RXTX &= ~(1 << 6)
#define HV_LED_ON         MDR_PORTA->RXTX |= 1 << 5     
#define HV_LED_OFF        MDR_PORTA->RXTX &= ~(1 << 5)
#define Status_LED_ON     MDR_PORTA->RXTX |= 1 << 3 
#define Status_LED_OFF    MDR_PORTA->RXTX &= ~(1 << 3)
#define Error_LED_ON      MDR_PORTA->RXTX |= 1 << 4 
#define Error_LED_OFF     MDR_PORTA->RXTX &= ~(1 << 4)

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

#define com_dev_id      0       // � ����������������� ������ ������������ ����� 0
#define dev_id 31               // modbus id �������� ����������                        <<<<<<<<<<=========================== ID
#define firmware_ver    12      // ������ �������� �������� ����������
#define device_family   2       // ��� ��������� ���������: 1 - PBF modules, 2 - extraction modules, 3 - dc hv modules
#define max_regs_cnt    125     // ����. ���-�� ��������� ��� ������ �� 1 ���

U8 reg_addr_flag = 0;
U8 reg_wr_flag = 0;
U8 reg_qty_flag = 0;
U8 get_crc_flag = 0;

U8 rx_byte;       // ���� �������� � ��
 
U8 answer = 0;    // ��� ������ �� ������� � ��
U8 rd_state = detect_dev_id; // ������ ��������� �� ��������� ���� ��������� �� id ��������� modbus
U16 modbus_reg_addr = 0;    // ����� �������� ��� R/W �� ������� �� modbus �������
U16 temp_buf = 0;           // ��������� �����
 
U16 regs2read = 0;          // ����� ��������� ��� ������ �� ������� modbus rhr
U8  crc_buf[250];           // ����� ��� �������� ������ ��� ������� CRC16
U16 CRC16 = 0;              // ��� �������� ����������� ����������� �����
U16 addr_buf_1, addr_buf_2;

U16 reg_wr_data = 0;
U16  holding_register[125];  // ����� ��� �������� ���������� ������, ����. ����� ��������� - 124
//==============================================================================

  U16 MCU_ADC_aver_param = 25;  // �������� ����������� ������ ���

  S16 ADC_zero_lvl = 0;         // ����� 0 ��� 
  
  U16 frame_time[4] = {0,0,0,0};// ������������ �������� ����. ������           
  U16 frame_duty[4] = {0,0,0,0};// ���������� (������) �������� ����. ������
  U16 quick_extr_time = 800;    // ������������ �������� ������, �� �����. = 80 timer ticks * 10 ���
  U16 pulse_delay = 500;        // ������������ �������� ����� ����� ��������� ������, ������ 10 ���
  U16 pulse_count = 0;          // ����� ������������ ��������� �� ����
  U8  frame = 4;                // ������� ������
  
  U8  mode = 0;                 // ����� ������ ������: 0 - ��������� �����, 1 - �������
  U16 end_delay = 10;           // �������� ������ ������������ �����������
  U8 trig_in_progress = 0;      // ������ ������� �������� �������

  U8 trig_led_delay_cnt   = 0;  // ������� ������������ ���. ���������� �������
  U8 status_led_delay_cnt = 0;  // ������� ������������ ���. ���������� ����������
  
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
  MDR_PORTB->OE = 0xFFFF;               // ���� B �� �����, PB0 ��� ����. ������, PB1 - ��� �����. ������
  MDR_PORTB->FUNC = 0x0000;             // ������� - ����, PB0, PB2 - �������������� �������
  //MDR_PORTB->FUNC = (2<<4) | (1<<1);    // ������� - ����, PB0, PB2 - �������������� �������
  MDR_PORTB->ANALOG  = 0xffff;          // ����� ����� - ��������
  MDR_PORTB->PWR     = 0xFFFFFFFF;      // ����������� ������� ����� ( ������� 10 ��)
  MDR_PORTB->RXTX &= ~1;
  MDR_PORTB->RXTX &= ~(1<<3);
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
          
  // ��������� ������� ��� ������ ������� ��������� ������ -> _/ + ���������� 0,125 ���
          
  MDR_RST_CLK->TIM_CLOCK  |= (1 << 24);            // ���������� ������������ ������� 1
  
  MDR_TIMER1->CNTRL = 4<<8;                               // �������� ������� - ������� �� 1 ������ ������ 1� 
  MDR_TIMER1->CH1_CNTRL = (1<<15)| (1<<4);                // ����� �������� � ������ ������ | ������������� �����
  MDR_TIMER1->CH1_CNTRL1 = (1<<2)|(1<<1);	          // ���� �� CCR11; ������������� ����� �� Chi
  MDR_TIMER1->CNT   = 0;                                  // ��������� �������� �������� - 0
  MDR_TIMER1->PSG   = 0;                         	  // ������������ ������� ������������ �1 - 1
  MDR_TIMER1->ARR   = 1999;                               // ��������� �����, ������ ������ ��  
  MDR_TIMER1->IE    = (1<<5) | (1<<13);                   // ���������� ���������� �� ��������� � ������� ������ 1 ������, ����. ���������� �� ���������� CNT � ARR
  MDR_TIMER1->STATUS= 0;                                  // ���������� �����
  
 }
 
  void timer2_init() {
          
  // ���������� 0,125 ���
          
        MDR_RST_CLK->TIM_CLOCK  |= (1 << 25);   // �������� �������|���������� ������������ ������� 2
        MDR_TIMER2->CNTRL = 0x00000000;        	// ����� ������������� �������, ����
        MDR_TIMER2->CNT   = 0x0000;       	// ��������� �������� ��������
        MDR_TIMER2->PSG   = 0;                  // ������������ ������� = 1
        MDR_TIMER2->ARR   = 7999;               // ��������� �����, ���������� ������ 100 us
        MDR_TIMER2->IE    = 0x00000000;          // ������ ���������� �� ������������ TIMER2  
        MDR_TIMER2->STATUS= 0x00000000;         // ���������� �����
        MDR_TIMER2->CNTRL = 0x00000000;
 }

  void timer2_set_mode(U16 per) {
  
     // ������������ = 1, �2 � ������ ������� �������� �������� 
  if(per < 1)
        MDR_TIMER2->PSG   = 0;               // ������������ ������� = 1, ����� ���. ����. ������ �������� ������
  else
  {  // ������� �2 � ����� ����. ���������� � ����� 10 ���
     MDR_TIMER2->PSG   = 799;                // ������������ ������� = 800
     MDR_TIMER2->ARR   = per;                // ��������� �����
     MDR_TIMER2->CNT   = 0;                  // ����� �������� �2 
     MDR_TIMER2->IE    = 0x00000002;          // ���������� ���������� �� ������������ TIMER2 
     MDR_TIMER2->CNTRL |= 1;                  // ������ �2 
  }
}
 
  void timer3_init(void) {
          
  // ��������� ������� ��� ������ � ������ ��� - f = 1/25 ���, 64 �������
    
 MDR_RST_CLK->TIM_CLOCK  |= (1 << 26) | 1<<16;           // ���������� ������������ Timer3, TIM1_CLK = HCLK/4											
 MDR_TIMER3->PSG   = 0;               		 // ������������ ������� = 0
 MDR_TIMER3->CNTRL = 0x00000006;        	 // ����������� ����� ��������� �������� �� ���� �� ARR,
						 // ��������� �������� - ����� �� �������� CNT 
 MDR_TIMER3->ARR   = 63;                	 // ��������� �����. 
 MDR_TIMER3->CNT   = 0;       	                 // ��������� �������� �������� 
//����� ������ ������� - ��� 
 MDR_TIMER3->CCR1 = 0;                  // ��������� ���������� - 0  
 MDR_TIMER3->CCR2 = 0;                  // ��������� ���������� - 0 
 //����� 1 - ��� ����. ������
 MDR_TIMER3->CH1_CNTRL  =  6 << 9;      // 1, ���� DIR= 0 (���� �����)
 MDR_TIMER3->CH1_CNTRL1 =  (2<<2); 
 //����� 2 - ��� ����. ������
 MDR_TIMER3->CH2_CNTRL  =  6 << 9;      // 1, ���� DIR= 0 (���� �����)
 MDR_TIMER3->CH2_CNTRL1 =  (2<<2); 
 MDR_TIMER3->IE = 0x0000;              // ������ ����������
 MDR_TIMER3->STATUS= 0;                // ���������� �����
}
 
  void extraction_stop(void) {
     /// ���������� �������� ������
     
     // ��������� ��������� ��� � �����, ��� � ���� �������
     if(mode == 0) MDR_TIMER3->CH1_CNTRL1 =  (0<<2) | 1;    // ����. ����� - REF ��������� � CH1 TIMER1
     else          MDR_TIMER3->CH2_CNTRL1 =  (0<<2) | 1;    // ����. ����� - REF ���������  CH2 TIMER1
     MDR_TIMER3->CNTRL &= ~ 1;                 // ���� �3 -- ��� 
     MDR_TIMER2->CNTRL &= ~ 1;                 // ���� �2 -- ��������� ������� ��� 
     MDR_TIMER2->IE &= ~(1 << 1);              // ������ ���������� �� ������������ TIMER2
     
     for(U32 i = 0; i < end_delay * 5; i++)
     {
       __no_operation();     // ������������ �����
       __no_operation();
     }
     
     reset_integrator;                   // ����� ������ ���.������������
     
     // ���� ���� ������� �������
     if(trig_in_progress != 0)
     {
        
      timer2_set_mode(pulse_delay);      // �������� ����� ����� ���������
     }
}

  void extraction_start(void){
  
  timer2_set_mode(0);       // ���. �2 � ����� ������� ����. ���������� �������
  frame = 0;                // ���. ������� ��� = 1 �������     
  pulse_count++;            // ��������� �������� ���������

  
          // ���. ���������� ��� � ����������� �� ������ ������
          if(mode == 0) 
          { /// ������� ���������� ������
            MDR_TIMER2->ARR =(U32)frame_time[0];   // t ���� �����
            MDR_TIMER3->CH1_CNTRL1 =  (2<<2) | 1;  // ����. ����� - REF �������� �� CH1 TIMER1
            MDR_PORTB->FUNC |= (1<<1);             // PB0 �������� ��� ����� ������ 1 �3
            MDR_TIMER3->CCR2  =  0;
            MDR_TIMER3->CCR1  =  (U32)frame_duty[0]; // ���. ���������� 1 ������� ��� �� ������ ����. ������
          }
          else          
          {
            MDR_TIMER2->ARR =(U32)quick_extr_time; // t ����� �����           
            MDR_TIMER3->CH2_CNTRL1 =  (2<<2) | 1;  // ����. ����� - REF �������� �� CH2 TIMER1
            MDR_PORTB->FUNC &= ~(1<<1);            // PB0 ����. �� ������� 3
            MDR_PORTB->FUNC |= (2<<4);             // PB2 �������� ��� ����� ������ 2 �3
            MDR_TIMER3->CCR1  =  0;
            MDR_TIMER3->CCR2  =  64;               // ���. ���������� �������� ������ 
          }
                  
          MDR_TIMER2->IE    = 0x00000002;          // ���������� ���������� �� ������������ TIMER2 
          MDR_TIMER3->CNT = 0;
          MDR_TIMER2->CNT = 0;  
          
          set_integrator;                          // ���. ����� ������ �����������
          MDR_TIMER3->CNTRL |= 1;                  // ������ �3 -- ��� 
          MDR_TIMER2->CNTRL |= 1;                  // ������ �2 -- ��������� ������� ���    
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
          for(U16 i = 0; i < 100; i++) {}      // �������� ��������� ���
          //delay_ms(1);
	  ADC_data = MDR_ADC->ADC1_RESULT & 0x0FFF; // ������

	  return ADC_data;
}

  void MCU_ADC_set_ch(U8 channel){
	  
	if (channel > 15) return;
 
	MDR_ADC->ADC1_CFG  |= channel << 4; 
        for(U16 i = 0; i < 100; i++) {}      // �������� ��������� ���	
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
          //for(U16 i = 0; i < 200; i++) {}
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
    // �������� ������ �������
    RS485_TX_EN;                 // ���. ����������� RS485
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
    RS485_TX_DIS;                 // ����. ����������� RS485
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
          RS485_TX_EN;                 // ���. ����������� RS485
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
          RS485_TX_DIS;                 // ����. ����������� RS485
          //--------------------------------------------------------------------
  
  
  
  }

/*========================================================================== */
// INTERRUPTS

__irq void UART1_IRQHandler( void )
 //������� ��������� ���������� irq UART1
{
  /// ���������� ��������� ��� ����������� 1 ����� �� UART1
        wr_ptr++;               // ��������� �������� ���������� ����
        rx_buf[wr_ptr & 0x0f] = MDR_UART1->DR; 
      
        MDR_UART1->ICR  = 1<<4; // ����� ���������� �� ���������  
}

__irq void Timer1_IRQHandler(void) 
//������� ��������� ���������� irq Timer 1 - ������ ������� 
{ 
    U32 int_flag = MDR_TIMER1->STATUS;       // ����. ����� ���������� ���������� �� �3   
    
    if(int_flag & (1<<5))   //  ___/ ���� ���������� �� ��������� ������
    {  
       TRIG_LED_ON;                          // ���. ��������� �������
       pulse_count = 0;                      // ����� �������� ��������� �� ������
       trig_in_progress = 1;                 // ���. ������-��� �������� ������� 
       trig_led_delay_cnt = 0;               // ����� �������� ���. ����������
       
       if((frame_time[0] > 1) || (mode > 0)) // ���� t ���� ������ > 1 ��� ������ �����. �����
          extraction_start();                // ����� ������ ��������    
    }
    
    if(int_flag & (1<<13))   //  \___ ���� ���������� �� ������� ������
    {  
      trig_in_progress = 0;                  // ����� ������-���� �������� ������� 
      extraction_stop();  
    }
    
    MDR_TIMER1->CNT = 0;                     // ��������� ����. �������� �� 0
    MDR_TIMER1->STATUS = 0x0000;             // ����� ������� ����������
    NVIC_ClearPendingIRQ(Timer1_IRQn);       // �����������!   
     
}

// ��������� ������� ���
__irq void Timer2_IRQHandler(void)
{
      // ���� ���� ���������� � ������������ �2 > 0, ������ ����� ������� ������ 
      // � �������� �������� ������� -> ������������� ��� � �����
      if(MDR_TIMER2->PSG > 0) extraction_start();
      
      // ���� ���������� � ������������ = 0 -> ������������ �������� �������� ������
      else
      {
       if( (mode > 0) && (MDR_TIMER2->ARR > quick_extr_time) )  frame = 4;
         
       switch (frame)
       {
        case 0:
          if( (frame_time[1] < 1) || (mode == 1) ) extraction_stop(); // ���� t ��.2 < 1 � �� �����. �����, �� ����� ���������� 
          else 
          {
            MDR_TIMER2->ARR  =  (U32)frame_time[1];  
            MDR_TIMER3->CCR1 =  (U32)frame_duty[1]; // ���. ���������� 2 ������� ��� ��� ������ �����. ������
            frame = 1;
          }
        break;
        //----------
        case 1:       
          if( (frame_time[2] < 1) || (mode == 1) ) extraction_stop(); 
          else 
          {
            MDR_TIMER2->ARR  =  (U32)frame_time[2];  
            MDR_TIMER3->CCR1 =  (U32)frame_duty[2]; // ���. ���������� 3 ������� ��� ��� ������ �����. ������
            frame = 2;  
          }
        break;
        //----------
        case 2:
          if( (frame_time[3] < 1) || (mode == 1) ) extraction_stop();
          else
          {
            MDR_TIMER2->ARR  =  (U32)frame_time[3];  
            MDR_TIMER3->CCR1 =  (U32)frame_duty[3]; // ���. ���������� 4 ������� ��� ��� ������ �����. ������     
            frame = 3; 
          }
        break;
       case 3:  
         extraction_stop();
         break;
        //----------
       default: __no_operation();
       }
      }
      
    MDR_TIMER2->CNT = 0;                     // ��������� ����. �������� �� 0
    MDR_TIMER2->STATUS = 0x0000;             // ����� ������� ����������
    NVIC_ClearPendingIRQ(Timer2_IRQn);       // �����������!
}

/*=========================================================================== */

  void MCU_init (void) {
	  
 	 OSC_init();
	 SysTickTimer_Init();
 	 GPIO_init();  
	 timer1_init();   // ������ ������ �������������
         timer2_init();   // ��������� ������� ���
         timer3_init();   // ���
         MCU_ADC_init();
         Uart_init();           // UART1 - RS485
	}
  
/*=========================================================================== */
// MAIN    
        
 int main()
{  
 U32 ADC_V = 0;
 S32 ADC_code = 0;
 
 MCU_init();	   // ������������ ������ ������������, ������, SPI � UART
 reset_integrator; // ����� ������ ���.������������ 
 
 NVIC_EnableIRQ(Timer1_IRQn); // ���������� ���������� ��� T1
 NVIC_EnableIRQ(Timer2_IRQn); // ���������� ���������� ��� T2
 NVIC_EnableIRQ(UART1_IRQn);  // ���������� ���������� ��� UART1
 RS485_RX_EN;                 // ���. ���������   RS485
 RS485_TX_DIS;                // ����. ����������� RS485
 MDR_TIMER1->CNTRL |= 1;      // ������ �1 -- ������� ������
 __enable_irq();	      // Enable Interrupts global
 
 for(U8 i = 0; i < 125; i++) holding_register[i] = 0; // ������� ������ ���������� ������

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
         
         holding_register[0] = (U16)frame_time[0]/80;   // ������������ 1 ������� ������ � us.   
         holding_register[1] = (U16)frame_duty[0];      // ���������� 1 �������   
         holding_register[2] = (U16)frame_time[1]/80;   // ������������ 2 ������� ������ � us.   
         holding_register[3] = (U16)frame_duty[1];      // ���������� 2 �������
         holding_register[4] = (U16)frame_time[2]/80;   // ������������ 3 ������� ������ � us.   
         holding_register[5] = (U16)frame_duty[2];      // ���������� 3 ������� 
         holding_register[6] = (U16)frame_time[3]/80;   // ������������ 2 ������� ������ � us.   
         holding_register[7] = (U16)frame_duty[3];      // ���������� 2 �������  
         
         holding_register[8] = end_delay;               // ������������ �����, ����� ��� ���������� ����� ����� �������� ����� ������ �����������                                           // � �������������
         holding_register[9] = pulse_delay*10;          // �������� ����� ����� ���������, ������ 10 ��� 
         
         holding_register[10]= (U16)mode;               // ����� ������: 0 - ����, 1 - �����.  
         holding_register[11]= (U16)ADC_V;              // ��������� �������� ����������
         holding_register[12]= quick_extr_time/80;      // ������������ �������� ������ � ���   
              
         holding_register[13] = (U16)dev_id;            // modbus id �������� ����������
         holding_register[14] = (U16)firmware_ver;      // ������ �������� �������� ����������
         holding_register[15] = (U16)device_family;     // ��������� ���������� 2 - extraction module
         holding_register[16] = pulse_count;            // ����� ��������� �� ������
         holding_register[17] = trig_in_progress;       // ������ ������� �������� �������
         
         modbus_rhr_answer();                 // ������� �������� ������������� ���������
         answer = 0;                          // ����� ����� ������
       }
    // ������ 
    if(answer == modbus_wsr_cmd) // ����� ��� ������� ������ � �������
    {
         addr_buf_1 = modbus_reg_addr-1000;          // ���������� �� ��������
         holding_register[addr_buf_1] = reg_wr_data; // ������ ���������� ������ � ������� �� ������
	 //--------------------------------------------------------------------
         // ���������� ���������� ������ ���������� ���������
         // 1 TIMER1 tick = 12,5 ns, 80 ticks = 1 us  /// ���� ����� - 800 ���
         frame_time[0] = holding_register[0] * 80;   // ������������ 1 ������� ������ � us.   
         frame_duty[0] = holding_register[1];        // ���������� 1 �������
         
         frame_time[1] = holding_register[2] * 80;   // ������������ 2 ������� ������ � us
         frame_duty[1] = holding_register[3];        // ���������� 2 �������
         
         frame_time[2] = holding_register[4] * 80;   // ������������ 3 ������� ������ � us
         frame_duty[2] = holding_register[5];        // ���������� 3 �������
         
         frame_time[3] = holding_register[6] * 80;   // ������������ 4 ������� ������ � us
         frame_duty[3] = holding_register[7];        // ���������� 4 �������
         
         if(holding_register[8] < 10)    holding_register[8] = 10;  // ���. � �����
         if(holding_register[8] > 2000)  holding_register[8] = 2000;// ����.� �����
         end_delay = holding_register[8];            // ������������ ����� 
         
         if(holding_register[9] < 100)   holding_register[9] = 100;  // ���. ��������
         if(holding_register[9] > 65000) holding_register[9] = 65000;// ����. ��������
         
         pulse_delay = holding_register[9]/10;       // �������� ����� ����� ���������, ������ 10 ��� 
         mode = holding_register[10];                // ����. �������� ������ ������ ����� ����� ������: 0 - ����, 1 - �����.

         if(holding_register[12] < 100)                    // �� ����� 100 ���
          quick_extr_time = holding_register[12] * 80;     // ������������ �������� ������ � ��� 
         else holding_register[12] = 100;
         
         if(holding_register[12] < 1)                     // �� ����� 1 ���
          quick_extr_time = holding_register[12] * 80;     // ������������ �������� ������ � ��� 
         else holding_register[12] = 1;
         //--------------------------------------------------------------------  
         modbus_wsr_answer();             // ������� ������ �� ������� ������ � �������
         answer = 0;                      // ����� ����� ������
       } 
//---------------------------------------------    
     MCU_ADC_init();               // ����� ���������� ��������
     MCU_ADC_set_ch(5);            // ��������� ������ ��� 
     // ������ �������� ��� 
     ADC_code  = (S32)MCU_ADC_Rd_average(MCU_ADC_aver_param); 
     // �������������� � ����� ����������� ���. ����������
     ADC_V     = (U32)(ADC_code*0.8056640625);//ADC_Vref*1000.0)/4096.0);
     
     if(ADC_V > 50) HV_LED_ON; // ���. ��������� �������� ���������� ���� ��� ����� 50�
     else HV_LED_OFF;  
    
//----------------------------------------------
//���������    
    
    if(trig_in_progress)
      trig_led_delay_cnt = 0;   // ����� �������� �������� ���������� �������
    else
      trig_led_delay_cnt++;     // ��������� �������� �������� ���������� �������
    
    if(trig_led_delay_cnt > 45)
    {
      TRIG_LED_OFF;
      trig_led_delay_cnt=0;
    }
    
    status_led_delay_cnt++;
    if(status_led_delay_cnt > 250)
    {
      Status_LED_ON;
      status_led_delay_cnt=0;
    }
    
//---------------------------------------------
  } // while  
} // main