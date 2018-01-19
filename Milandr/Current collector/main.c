#include "MDR32Fx.h"

#define U8  uint8_t
#define S8  int8_t
#define U16 uint16_t
#define S16 int16_t 
#define U32 uint32_t
#define S32 int32_t

#define ADC_Vref             3.3		// ���������� ����������� ���������� ������� ��

#define n_MX1_DIS			 MDR_PORTA->RXTX |=  (1<<3)
#define n_MX1_EN			 MDR_PORTA->RXTX &= ~(1<<3)
#define n_MX2_DIS			 MDR_PORTA->RXTX |=  (1<<4)
#define n_MX2_EN			 MDR_PORTA->RXTX &= ~(1<<4)
#define n_MX3_DIS			 MDR_PORTA->RXTX |=  (1<<5)
#define n_MX3_EN			 MDR_PORTA->RXTX &= ~(1<<5)
#define n_MX4_DIS			 MDR_PORTA->RXTX |=  (1<<6)
#define n_MX4_EN			 MDR_PORTA->RXTX &= ~(1<<6)
#define n_MX5_DIS			 MDR_PORTA->RXTX |=  (1<<7)
#define n_MX5_EN			 MDR_PORTA->RXTX &= ~(1<<7)
#define n_MX6_DIS			 MDR_PORTB->RXTX |=  (1<<10)
#define n_MX6_EN			 MDR_PORTB->RXTX &= ~(1<<10)
#define n_MX7_DIS			 MDR_PORTB->RXTX |=  (1<<1)
#define n_MX7_EN			 MDR_PORTB->RXTX &= ~(1<<1)
#define n_MX8_DIS			 MDR_PORTB->RXTX |=  (1<<2)
#define n_MX8_EN			 MDR_PORTB->RXTX &= ~(1<<2)

#define MX_S0_ON			 MDR_PORTA->RXTX |=  1
#define MX_S0_OFF			 MDR_PORTA->RXTX &= ~1
#define MX_S1_ON			 MDR_PORTA->RXTX |=  (1<<1)
#define MX_S1_OFF			 MDR_PORTA->RXTX &= ~(1<<1)
#define MX_S2_ON			 MDR_PORTA->RXTX |=  (1<<2)
#define MX_S2_OFF			 MDR_PORTA->RXTX &= ~(1<<2)

   U16 PC_sync_flag_cnt = 0;     // ������� ��� �������� �� �� ������� ����� � ������
   U8  PC_sync_flag = 0;         // ���� ������� �����
   U32 current_ADC_channel = 0;
   U16 ADC_aver_param = 10;		// �������� ����������� ������ ���
   
   U8 ext_int_fl = 0;			// ���� �������� ����������
   U8 current_int_index = 0;	// ���������� ������� �������� ����������
   U8 previous_int_index = 0;	// ���������� ���������� �������� ����������
   U8 sync_counter = 3;			// ����� �������������
   U8 sucess_sync_rd = 0;       // ������� �������� ��������������. ���������� 
   								// ������� �������������
 	
   void delay_1us (void){
	 
     uint8_t i;
     for(i = 0; i < 1; i++){} 
  }  
  
   void delay_5us (void){
     uint8_t i;
    for(i = 0; i < 3; i++){}  
  }
    
   void delay_100us (void){
    uint16_t i;
    for(i = 0; i < 20; i++){delay_5us();}  

  }
  
   void delay_1ms (void){
     uint32_t i;
    for(i = 0; i < 2400; i++){}  
  }
  
   void delay_50ms (void){
     uint32_t i;
    for(i = 0; i < 50; i++){ delay_1ms(); }  
  }

   void delay_200ms (void){
	 
     uint32_t i;
     for(i = 0; i < 200; i++){ delay_1ms(); }  
  }

   void delay_1s (void){
	 
     uint32_t i;
     for(i = 0; i < 1000; i++){ delay_1ms(); }  
  }

/*=========================================================================== */
// SPI
	void MDR32_SSP1_init (void){

  MDR_RST_CLK->SSP_CLOCK = ((4 << 0)|(1 << 24)); //������������ = 16, ���������� ������������ SSP1 

  MDR_SSP1->CPSR = 2; //�������� �������� �������;
  MDR_SSP1->CR0 = 1 << 6; //���������� �������
  MDR_SSP1->CR0 |= 1 << 7; //���� �������
  MDR_SSP1->CR0 |= 0 << 8; //����������� ��������
  MDR_SSP1->CR0 |= 0 << 4; //������ �����
  MDR_SSP1->CR0 |= 15; //����� ����� = 16 ���
  MDR_SSP1->CR1 |= ((0 << 2)|(1 << 1)); //����� ������ � ��������� ����������������� SSP

    // ���� SPI1_TxD � SPI1_CLK ��������� �� ����� � GPIO_init()
	// ����� ������� �������������� ����� ����� - ������������ ������ SSP1
	// ���� PF0 - PF3 ������������ ���� �������!
	    
   }

	void SPI1_Wr_Data (U16 data){
	  
	  // ������� �������� ������ �� ���� SSP1
	  // ������� DR - 16 ��� !!!!
	  MDR_SSP1->DR = data;
	}

	U16 SPI1_Rd_Data (void){
	  
	  // ������� ��������� ������ ���� SSP1
	  // ������� DR - 16 ��� !!!!
	  
	  U16 rx_buf = 0;
	  MDR_SSP1->DR = 0;				// ������������ �������� ��������
	  while(MDR_SSP1->SR & 1<<4) { } // ���� ���������� ������
	  
	  rx_buf = MDR_SSP1->DR;
	  
	  return rx_buf;

	}

	S16 TsensRd (void) {
	  
	  S32 TempInCelsius = 0;
	  U8 PrecisionCoef = 1;
	  S16  full_scaleCelsius = 127;
	  S16 full_scaleSensADC = 508;
	  	  
	  TempInCelsius = SPI1_Rd_Data();	  
	  TempInCelsius = TempInCelsius << 1; // ����������� �� "leading zero"
	  TempInCelsius = TempInCelsius >> 6; // �������� � 16-���. �������
	  if (TempInCelsius > 508)
	  {
	  	full_scaleCelsius = 128;
	  	full_scaleSensADC = 512;
		TempInCelsius = TempInCelsius - 1024;
		TempInCelsius = (TempInCelsius*full_scaleCelsius*PrecisionCoef)/full_scaleSensADC;
	  }
	  else {TempInCelsius = (PrecisionCoef*(TempInCelsius*full_scaleCelsius)/full_scaleSensADC);}
	   

	  //�������������� � �������: 508 = +127 ���� - ����. �����
	  
	  
	  return TempInCelsius;
	}

/*=========================================================================== */
//UART
	void Uart_init (void){
//UART	  
	MDR_RST_CLK->PER_CLOCK |= (1UL << 6); 			//������������ UART1
	MDR_RST_CLK->UART_CLOCK = (0 					// ��������� �������� ��� UART1
  	|(0 << 8) 									// ��������� �������� ��� UART2
  	|(1 << 24) 						// ���������� �������� ������� UART1
  	|(0 << 25));						// ���������� �������� ������� UART2*/ 

// 	//��������� �������� ��� ������� = 10000000�� � �������� = 115200
	MDR_UART1->IBRD = 0x5; 						// ����� ����� �������� ��������
	MDR_UART1->FBRD = 0x1b; 					// ������� ����� �������� ��������
	
//	//��������� �������� ��� ������� = 70000000�� � �������� = 115200
//    MDR_UART1->IBRD = 0x25; //����� ����� �������� ��������
//    MDR_UART1->FBRD = 0x3f; //������� ����� �������� ��������
	MDR_UART1->LCR_H = ((0 << 1) 				// ���������� �������� ��������
  	|(0 << 2) 								// ��������/����������
  	|(0 << 3) 								// ����-���
 	 |(0 << 5) 						// ����. ������ FIFO ��������� � �����������
 	 |(3 << 5) 								// ����� ����� = 8 ���
 	 |(0 << 7)); 							    // �������� ���� ��������

	MDR_UART1->CR = ((1 << 8)|(1 << 9)|1);   // ��������� � �������� ��������, 
  										 // ���������� ����������������� UART1
}
	
	void Uart_send_hex(U8 hex_data){
  
	  while(MDR_UART1->FR & (1<<3)) { }; // ���� ���������� UART;
	  
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

	void Uart_send_text(unsigned char *s){
    
	while (*s != 0)
    Uart_send_hex(*s++);
}

/*=========================================================================== */
// ADC
    void ADC_init(){

  MDR_RST_CLK->PER_CLOCK |= (1 << 17); //������������ ���
  
  MDR_ADC->ADC1_CFG = (1 //��������� ���  
  |(0 << 2)   	// �������� �������������*/
  |(1 << 3)   	// ����� ������� ������� ��� - ������. 
  |(0 << 4)  	// ����� ������ ��������������*/ - �� �����, ��� ��� ��������� ����� �����
  |(1 << 9)  	// ������������ �������� (������������ ������, ��������� � �������� ������ ������)
  |(0 << 10) 	// �������������� �������� ������� ����.
  |(0 << 11)  	// �������� �������� - ���������� (VDD)
  |(0 << 12)  	// ����������� ������� ������� ADC_clk = HCLK = 10 ���
  |(0 << 16)  	//  ������ ���� ��� ����������� ����.
  |(0 << 17)    //  TS_EN ������ ����������� � ��������� �������� ���������� ����
  |(0 << 18)    // TS_BUF_EN ��������� ��� ������� ����������� � ��������� �������� ���������� ����.
  |(0 << 19) 	// ��������� ������� ����������� ����./
  |(0 << 20));  // ��������� ��������� �������� ���������� �� 1.23 � ����
  //|(6 << 24));// ���������� �������� ���������� - ������� ���������� 1.2 �
  
  //MDR_ADC->ADC2_CFG |= 1 << 17; // ����� ��������� �������� ���������� 1.23 � �� ������� ����������� (������) 
}

	void ADC_start_conv(void){
  
  	MDR_ADC->ADC1_CFG |= 1<<1;
  
}

    U32 ADC_read(void){
	  
	  // ������ ���, t ������� + t �������������� ������ = 3.2 ��� ��� HCLK = 10� � ������������ ��� = 1
	  //		     t ������� + t �������������� ������ = 0.5 ��� ��� HCLK = 70� � ������������ ��� = 1					
	  // ��� �������� ������� ��� = 3,3/4095 = 0,8 ��
	  
	  U32 ADC_data = 0;
	  
  	  ADC_start_conv(); // ������ �������������� ������
	  
	  while(!(MDR_ADC->ADC1_STATUS) & (1<<2)) {} // ���� ���������� 
	  ADC_data = MDR_ADC->ADC1_RESULT;			 // ������
	  
	  current_ADC_channel = ADC_data << 11;  //����������� ����� 
	  current_ADC_channel = current_ADC_channel >> 27;  //������ ��� ���������
	  
	  ADC_data = ADC_data << 20;    // ����������� ���� � 
	  ADC_data = ADC_data >> 20;    // ������ ���������
	  
	  return ADC_data;
}
					   
    void ADC_set_ch(U8 channel){
	  
	if (channel > 16) return;
	
	MDR_ADC->ADC1_CHSEL = 1 << channel; 
	
	
}

    U32 ADC_Rd_average(U16 AverValue){
	  
	  // ������ ���, t ������� + t �������������� ������ = 3.2 ��� ��� HCLK = 10� � ������������ ��� = 1
	  // t ������� + t �������������� ������ = 0.5 ��� ��� HCLK = 70� � ������������ ��� = 1	
	  // ���������� ����������� �������������� ���
	  
	  U32 Aver_ADC_data = 0;
	  
	  for(int i = 0; i < AverValue; i++ )
	  {
	  		Aver_ADC_data += ADC_read();
	  }
  
	  Aver_ADC_data = Aver_ADC_data/AverValue; 
	  
	  return Aver_ADC_data;
}

	U32 Get_ADC_ch_voltage(U8 ADC_channel){
	  // ������ ������������ ���������� ��������. ������ ���, �������������� � ��
	  
	  U32 ADC_rd_data = 0;
 	  U32 ADC_meas_voltage = 0;
	  
	  ADC_set_ch(ADC_channel);	// ��������� ������ ���
	  ADC_rd_data = ADC_Rd_average(ADC_aver_param);				// ������ ������� �������� �������� ���
	  ADC_meas_voltage = (int)(ADC_Vref*ADC_rd_data*1000)/4095;	// ����������� � �����
	  
	  //MX_S0_OFF;
	  //MX_S1_OFF;
	  //MX_S2_OFF;
	  
	  //n_MX1_DIS; n_MX2_DIS; n_MX3_DIS; n_MX4_DIS; 
	  //n_MX5_DIS; n_MX6_DIS; n_MX7_DIS; n_MX8_DIS;
					  
	  
	  return ADC_meas_voltage; 

}
	
/*=========================================================================== */
// Multiplexers

	void Set_MX (U8 MxNumber){
	//��������� (�����) ��������������
	    
	  switch (MxNumber){
	  	
	  case 1:	// 1�� ������������� - U1
				n_MX1_EN;
				break;
	  case 2:	// 2�� ������������� - U3
				n_MX2_EN;
				break;
	  case 3:	// 3�� ������������� - U5	
				n_MX3_EN;
				break;
	  case 4:	// 4�� ������������� - U7	
				n_MX4_EN;
				break;	
	  case 5:	// 5�� ������������� - U11	
				n_MX5_EN;
				break;	
	  case 6:	// 6�� ������������� - U2	
				n_MX6_EN;
				break;
	  case 7:	// 7�� ������������� - U4		
				n_MX7_EN;
				break;
	  case 8:	// 8�� ������������� - U6		
				n_MX8_EN;
				break;
				
	  default: break; 	
	  }
	  
	  delay_1us();
}

	void Set_MX_ch (U8 channel){
	//��������� ������ ��������������
	  
	  // ��������� ��� �������������� ����� ������� ������ 
	  n_MX1_DIS; n_MX2_DIS; n_MX3_DIS; n_MX4_DIS; 
	  n_MX5_DIS; n_MX6_DIS; n_MX7_DIS; n_MX8_DIS;
	  
	  switch (channel){
	  	
	  case 0:	// 1 ����� �������������� S2,S1,S0 = 000  
				MX_S0_OFF;
				MX_S1_OFF;
				MX_S2_OFF;
				break;
	  case 1:	// 2 ����� �������������� S2,S1,S0 = 001 
				MX_S0_ON;
				MX_S1_OFF;
				MX_S2_OFF;
				break;
	  case 2:	// 3 ����� �������������� S2,S1,S0 = 001 
				MX_S0_OFF;
				MX_S1_ON;
				MX_S2_OFF;
				break;
	  case 3:	// 4 ����� �������������� S2,S1,S0 = 010  
				MX_S0_ON;
				MX_S1_ON;
				MX_S2_OFF;
				break;
	  case 4:	// 5 ����� �������������� S2,S1,S0 = 011 
				MX_S0_OFF;
				MX_S1_OFF;
				MX_S2_ON;
				break;
	  case 5:	// 6 ����� �������������� S2,S1,S0 = 100  
				MX_S0_ON;
				MX_S1_OFF;
				MX_S2_ON;
				break;
	  case 6:	// 7 ����� �������������� S2,S1,S0 = 101 
				MX_S0_OFF;
				MX_S1_ON;
				MX_S2_ON;
				break;
	  case 7:	// 8 ����� �������������� S2,S1,S0 = 110 
				MX_S0_ON;
				MX_S1_ON;
				MX_S2_ON;
				break;
	  default:
				MX_S0_OFF;
				MX_S1_OFF;
				MX_S2_OFF;
	  }
}

	void Set_meas_strip(U8 stripNum){
	
	  switch (stripNum){
	  // ��������� ������� �������� ��� ��������� ��������
	  case 1: 	Set_MX_ch(2); Set_MX(4); break; // in 3_7
	  case 2: 	Set_MX_ch(3); Set_MX(4);  break; // in 4_7
	  case 3: 	Set_MX_ch(5); Set_MX(5); break; // in 2_10
	  case 4: 	Set_MX_ch(1); Set_MX(4); break; // in 2_7
	  case 5: 	Set_MX_ch(6); Set_MX(5);  break; // in 3_10 
	  case 6: 	Set_MX_ch(0); Set_MX(4);  break; // in 1_7
	  case 7: 	Set_MX_ch(4); Set_MX(5);  break; // in 1_10
	  case 8: 	Set_MX_ch(7); Set_MX(4);  break; // in 4_8
	  
	  case 9: 	Set_MX_ch(7); Set_MX(5);  break; // in 4_10
	  case 10: 	Set_MX_ch(4); Set_MX(4);  break; // in 1_8
	  case 11: 	Set_MX_ch(0); Set_MX(5);  break; // in 1_9
	  case 12: 	Set_MX_ch(6); Set_MX(4);  break; // in 3_8
	  case 13: 	Set_MX_ch(3); Set_MX(5);  break; // in 4_9
	  case 14: 	Set_MX_ch(5); Set_MX(4);  break; // in 2_8
	  case 15: 	Set_MX_ch(2); Set_MX(5);  break; // in 3_9
	  case 16: 	Set_MX_ch(1); Set_MX(3);  break; // in 2_5
	  
	  case 17: 	Set_MX_ch(1); Set_MX(5);  break; // in 2_9
	  case 18: 	Set_MX_ch(2); Set_MX(3);  break; // in 3_5
	  case 19: 	Set_MX_ch(2); Set_MX(6);  break; // in 3_11
	  case 20: 	Set_MX_ch(0); Set_MX(3);  break; // in 1_5
	  case 21: 	Set_MX_ch(1); Set_MX(6);  break; // in 2_11
	  case 22: 	Set_MX_ch(3); Set_MX(3);  break; // in 4_5
	  case 23: 	Set_MX_ch(0); Set_MX(6);  break; // in 1_11
	  case 24: 	Set_MX_ch(7); Set_MX(3);  break; // in 4_6
	  
	  case 25: 	Set_MX_ch(3); Set_MX(6); break; // in 4_11
	  case 26: 	Set_MX_ch(4); Set_MX(3);  break; // in 1_6 !!!!!!!!!!!!!!!!!!!!!!!!
	  case 27: 	Set_MX_ch(5); Set_MX(6);  break; // in 2_12
	  case 28: 	Set_MX_ch(6); Set_MX(3);  break; // in 3_6
	  case 29: 	Set_MX_ch(4); Set_MX(6);  break; // in 1_12
	  case 30: 	Set_MX_ch(5); Set_MX(3);  break; // in 2_6
	  case 31: 	Set_MX_ch(7); Set_MX(6);  break; // in 4_12
	  case 32: 	Set_MX_ch(2); Set_MX(2);  break; // in 3_3
	  
	  case 33: 	Set_MX_ch(6); Set_MX(6);  break; // in 3_12
	  case 34: 	Set_MX_ch(1); Set_MX(2);  break; // in 2_3
	  case 35: 	Set_MX_ch(2); Set_MX(7);  break; // in 3_13
	  case 36: 	Set_MX_ch(3); Set_MX(2);  break; // in 4_3
	  case 37: 	Set_MX_ch(1); Set_MX(7);  break; // in 2_13
	  case 38: 	Set_MX_ch(0); Set_MX(2);  break; // in 1_3
	  case 39: 	Set_MX_ch(0); Set_MX(7);  break; // in 1_13
	  case 40: 	Set_MX_ch(4); Set_MX(2);  break; // in 1_4
	  
	  case 41: 	Set_MX_ch(3); Set_MX(7);  break; // in 4_13
	  case 42: 	Set_MX_ch(5); Set_MX(2);  break; // in 2_4
	  case 43: 	Set_MX_ch(4); Set_MX(7);  break; // in 1_14
	  case 44: 	Set_MX_ch(7); Set_MX(2);  break; // in 4_4
	  case 45: 	Set_MX_ch(7); Set_MX(7);  break; // in 4_14
	  case 46: 	Set_MX_ch(6); Set_MX(2);  break; // in 3_4
	  case 47: 	Set_MX_ch(5); Set_MX(7);  break; // in 2_14
	  case 48: 	Set_MX_ch(2); Set_MX(1);  break; // in 3_1
	  
	  case 49: 	Set_MX_ch(6); Set_MX(7);  break; // in 3_14
	  case 50: 	Set_MX_ch(3); Set_MX(1);  break; // in 4_1
	  case 51: 	Set_MX_ch(1); Set_MX(8);  break; // in 2_15
	  case 52: 	Set_MX_ch(0); Set_MX(1); break; // in 1_1
	  case 53: 	Set_MX_ch(0); Set_MX(8);  break; // in 1_15
	  case 54:  Set_MX_ch(1); Set_MX(1);  break; // in 2_1
	  case 55: 	Set_MX_ch(2); Set_MX(8);  break; // in 3_15
	  case 56: 	Set_MX_ch(4); Set_MX(1);  break; // in 1_2
	  
	  case 57: 	Set_MX_ch(3); Set_MX(8);  break; // in 4_15
	  case 58: 	Set_MX_ch(7); Set_MX(1);  break; // in 4_2
	  case 59: 	Set_MX_ch(7); Set_MX(8);  break; // in 4_16
	  case 60: 	Set_MX_ch(6); Set_MX(1);  break; // in 3_2
	  case 61: 	Set_MX_ch(6); Set_MX(8);  break; // in 3_16
	  case 62: 	Set_MX_ch(5); Set_MX(1);  break; // in 2_2
	  case 63: 	Set_MX_ch(4); Set_MX(8);  break; // in 1_16  
	  case 64: 	Set_MX_ch(5); Set_MX(8);  break; // in 2_16
	  // 65�� - ���������, ���� ���������� ����� ����� ���
	  default: break;
	  }

	  delay_100us(); // ����������� 100 ��� , ����� ������������ RC �������
}
/*=========================================================================== */
    
	void GPIO_init (void){  
  
  MDR_PORTA->OE      = 0xffff;			// ���� � �� �����, ������� ������ �������������� - ���� �0 - �7
  MDR_PORTA->FUNC    = 0x0000;          // ������� - ���� 
  MDR_PORTA->ANALOG  = 0xffff;          // ����� ����� - ��������
  MDR_PORTA->PWR     = 0xFFFFFFFF;      // ����������� ������� ����� ( ������� 10 ��)
//---------------------------------------------------------------------------//
  MDR_PORTB->OE 	 = 0xfdff;          // ���� B �� �����, ����� �������������� ���� B1, B2, B10
  										// ��� 9 - ���� ������� �������������
  MDR_PORTB->FUNC   = 0x00000000;       // ������� - ����
  MDR_PORTB->ANALOG = 0xffff;           // ����� ����� - ��������
  MDR_PORTB->PULL   = 0x00000000;       // �������� � "0" ���������, �������� � "1" ��������� 
  MDR_PORTB->PD     = 0x00000000;       // ������� ������ ��������, ���������� 200��
  MDR_PORTB->PWR    = 0xffffffff;       // ����������� ������� ����� ( ������� 10 ��)
  MDR_PORTB->GFEN   = 0x0000;           // ������ ��������
  // uart
  	MDR_PORTB->FUNC |= ((2 << 5*2) | (2 << 6*2)); 	//����� ������ �����
	MDR_PORTB->ANALOG |= ((1 << 5) | (1 << 6)); 	//��������
	MDR_PORTB->PWR |= ((3 << 5*2) | (3 << 6*2)); 	//����������� ��c����
  
  //---------------------------------------------------------------------------//
  MDR_PORTD->OE =     ((0 << 3)); //����������� �������� ������ = ����
  MDR_PORTD->ANALOG = ((0 << 3)); //����� ������ ����������� = 
  MDR_PORTD->PULL =   ((0 << 3)); //���������� �������� � GND
  MDR_PORTD->PULL =   ((0 << (3 << 16))); //���������� �������� � VCC
  MDR_PORTD->PD =     ((0 << (3 << 16))); //����� ������ ����� = 
  MDR_PORTD->PWR =    ((1 << 3*2)); //�������� ������ ������ = 
  MDR_PORTD->GFEN =   ((0 << 3)); //������� ������ ��������
  //---------------------------------------------------------------------------//
//  MDR_PORTE->OE = 0xffff;               // ���� E �� �����
//  MDR_PORTE->FUNC = 0x0000;             // ������� - ���� 
//  MDR_PORTE->ANALOG  = 0xffff;          // ����� ����� - ��������
//  MDR_PORTE->PWR     = 0xFFFFFFFF;      // ����������� ������� ����� ( ������� 10 ��)
//  //---------------------------------------------------------------------------//
  MDR_PORTF->OE = 0xffff;               // ���� D �� �����, ������ SSP1 
  MDR_PORTF->FUNC = (2 << 6) |			// �����  ����� 1, 2, 3, 4 ����� 
					(2 << 4) |			// - ��������������, ������������ ������ SSP1
					(2 << 2) |
					(2 << 0);

  MDR_PORTF->ANALOG  = 0xffff;          // ����� ����� - ��������
  MDR_PORTF->PWR     = 0xFFFFFFFF;      // ����������� ������� ����� ( ������� 10 ��)
   }
 
	void timer1_init(void) {
	  
  MDR_RST_CLK->PER_CLOCK |= 1 << 14; //���������� ������������ ������� 1 
  MDR_TIMER1->CNTRL = 0x00000000;                         // ����� ������������� �������
  MDR_TIMER1->CNT   = 0x00000000;                         // ��������� �������� ��������
  MDR_TIMER1->PSG   = 0x0;                         		 // ������������ �������
  MDR_TIMER1->ARR   = 0x1f3;                              // ��������� ����� 100 ���
  MDR_TIMER1->IE    = 0x00000002;                         // ���������� ������������ ���������� ��� CNT=ARR
  MDR_RST_CLK->TIM_CLOCK  = (0|(1 << 24));                // �������� �������|���������� ������������ ������� 1
  MDR_TIMER1->STATUS= 0x00000000;                         // ���������� ����� 
}

 	void OSC_init(void){

  //---CLK-----------------------------------------------------------------------------------------------------

	  
  MDR_RST_CLK->PER_CLOCK = 0xFFFFFFFF;                    // ���. ������������ ���� ���������
  MDR_RST_CLK->HS_CONTROL = 0x01; // ���. HSE ����������
  while (MDR_RST_CLK->CLOCK_STATUS & (1 << 2) == 0x00); // ���� ���� HSE ������ � ������� ����� 

  MDR_RST_CLK->PLL_CONTROL = ((1 << 2) | (0 << 8)); //����. PLL | ����. ��������� = 0
  while((MDR_RST_CLK->CLOCK_STATUS & 0x02) != 0x02); //���� ����� PLL ������ � ���. �����

  MDR_RST_CLK->CPU_CLOCK = (2 //�������� ��� CPU_C1
  | (1 << 2) //�������� ��� CPU_C2
  | (0 << 4) //������������ ��� CPU_C3
  | (1 << 8));//�������� ��� HCLK
	  
//  MDR_RST_CLK->PER_CLOCK = 0xFFFFFFFF;                    // ���. ������������ ���� ���������	  
//  MDR_RST_CLK->HS_CONTROL = 0x01; /* ���. HSE ���������� */
//  while (MDR_RST_CLK->CLOCK_STATUS & (1 << 2) == 0x00); /* ���� ���� HSE ������ � ������� ����� */
//
//  MDR_RST_CLK->PLL_CONTROL = ((1 << 2) | (6 << 8)); //���. PLL | ����. ��������� = 7
//  while((MDR_RST_CLK->CLOCK_STATUS & 0x02) != 0x02); //���� ����� PLL ������ � ���. �����
//
//  MDR_RST_CLK->CPU_CLOCK = (2 /*�������� ��� CPU_C1*/
//  | (1 << 2) /*�������� ��� CPU_C2*/
//  | (0 << 4) /*������������ ��� CPU_C3*/
//  | (1 << 8));/*�������� ��� HCLK*/
//  
//  // HCLK = 70 000 000 ��
	  
	  
}
	
	void MCU_init (void) {
	  
 	 OSC_init();
 	 GPIO_init();  
 	 Uart_init();
  	 MDR32_SSP1_init();
  
	}

__irq void Timer1_IRQHandler(void){
  //���������� ���������� ������� 1
  // ���������� ������ 100 ���
  
  // ���� ������������� ����������� � ������ ���������� ������ ��������
  // ���������������� ���������� ��������� ����� �������������
  
  PC_sync_flag_cnt++;
  
  if (PC_sync_flag_cnt >= 1000)
  {		PC_sync_flag_cnt = 0;
  		PC_sync_flag = 1;
  }
  
  // ����� ����� �������������
  if (MDR_PORTB->RXTX & (1<<9))
  { // ������ ������ �������������	  
	current_int_index = previous_int_index; // ���������� ����������� ������� ����������
    current_int_index++;					// ��������� ������� ����������
	  
  	if (current_int_index > previous_int_index) // ��������� ������� ?
	   	sucess_sync_rd++;    // ��������� �������� ������. ����������, �����
  }
  else current_int_index--; // ��������� ������� ���������� 
   
  if (sucess_sync_rd >= sync_counter)
  { // �����. ������������
	
	current_int_index = 0; // ����� �������� ������� ����������
    sucess_sync_rd = 0;    // ����� �������� �������� ���������� ��������������
	ext_int_fl = 1;        // ���. ����� ������ ��������� ��� 
  }
  
  MDR_TIMER1->CNT = 0x0000;			 // ���������� ������	
  NVIC_ClearPendingIRQ(Timer1_IRQn); // ����� ������ .. 
  MDR_TIMER1->STATUS &= ~(1 << 1);   // .. ����������
}


 	int main()
{

 U32 ADC_meas_voltage[65];				// ����� ��������� ���� �������
 S16 PCB_temper = 0; 				
 U8 StripNum = 65;						// ���������� ������� ����������
 
 MCU_init();							// ������������ ������� ������������,
  										// ������� GPIO, SPI, UART
 ADC_init();					
 timer1_init();
 
 __enable_irq();			    // Enable Interrupts global
 NVIC_EnableIRQ(Timer1_IRQn);   // Enable Timer1 Interrupt
 MDR_TIMER1->CNTRL = 1; // �������� ������ 1
 
 
 /// !!!
 /// ��� ���������� ������ ��� ����� �������� �� ����������
 /// ��������� ������������ �� USB. ���� ����� �� ������, 
 /// � ����������� ��������. ��� ���������� �������� (���)
 
 while(1)
  { // T ������ 65 ������� � 10-������� ����������� + t �������������� < 1 �� ��� HCLK = 70�
	// T ������ 65 ������� � 10-������� ����������� + t �������������� < 7 �� ��� HCLK = 10�
	
	// ����� ����� �������������
	if(ext_int_fl){
	  
	  NVIC_DisableIRQ(Timer1_IRQn);   // ��������� ���������� �� ����� ���������
	  
	  ext_int_fl = 0; // ���������� ���� ���������� �� ��������������
	  
	  for (U8 i = 1; i <= 65; i++){
	  //���� ��������� ���������� ������� 1-64
	  Set_meas_strip(i);
      //������ 1-64 �������� ����� 3�� (�����) ����� ���
	  ADC_meas_voltage[i-1] = Get_ADC_ch_voltage(3);	// ������	  	
	}
	  //������ �����, 65�� ����� - ��������� �� � ��������� ����� ���
	ADC_meas_voltage[64] = Get_ADC_ch_voltage(7);
	 
	PCB_temper = TsensRd() ; // �������� ����������� �����
	
	for (U8 i = 0; i <= 64; i++){
	  // ���� �������� ����������� �� ��
	  
	  Uart_num_send(ADC_meas_voltage[i]);		// �������� �� �� ��������� � ��
	  Uart_send_text(";");
	   }

	Uart_num_send(PCB_temper);
	Uart_send_text("E");       // ������ ����� �������
	
	// ���� �������, �� ���������� ������������� ����� 1 �������
	delay_200ms();
	
	NVIC_EnableIRQ(Timer1_IRQn);   // Enable Timer1 Interrupt
    MDR_TIMER1->CNTRL = 1; 		   // �������� ������ 1
	 }

	else
	{
		if(PC_sync_flag) {
	  
	  		PC_sync_flag = 0;
	  		Uart_send_text("Z");
	  		Uart_send_text("E");
		}
	}
	
	
	}	
}
