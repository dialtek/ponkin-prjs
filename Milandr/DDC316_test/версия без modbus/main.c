/// ������� ��� ,��������� ��� ����������������  
/// ���������� - �������������� ����������� ����� ���������� ������

// ��� "����� ����"

#include "MDR32Fx.h"
#define F_CPU 80000000

#define U8  uint8_t
#define U16 uint16_t 
#define S16 int16_t 
#define U32 uint32_t
#define S32 int32_t

#include "mdr_delay.h"

// ������� ������� � ��������� ����� ��������������� ������ � ����
#define CPLD_CE_ON  	 MDR_PORTB->RXTX |=   1<<7   
#define CPLD_CE_OFF  	 MDR_PORTB->RXTX &=  ~(1<<7) 

#define SYNC_LED_ON  	 MDR_PORTE->RXTX |=   1<<3 
#define SYNC_LED_OFF  	 MDR_PORTE->RXTX &=  ~(1<<3) 

#define ADC3_RST_ON 	 MDR_PORTE->RXTX |=  (1<<2)  
#define ADC3_RST_OFF 	 MDR_PORTE->RXTX &= ~(1<<2)
#define ADC2_RST_ON 	 MDR_PORTE->RXTX |=  (1<<1)  
#define ADC2_RST_OFF 	 MDR_PORTE->RXTX &= ~(1<<1)
#define ADC1_RST_ON 	 MDR_PORTE->RXTX |=  1; 
#define ADC1_RST_OFF 	 MDR_PORTE->RXTX &= ~1;

#define IVC_STOP_INT	 MDR_PORTD->RXTX |= (1<<5)
#define IVC_START_INT 	 MDR_PORTD->RXTX &=~(1<<5)
#define IVC_SET 	 MDR_PORTD->RXTX |= (1<<3)
#define IVC_RESET 	 MDR_PORTD->RXTX &=~(1<<3)

 /* OpAmpK - ������������� �����. ������. ������� �����������  
 ��� ��������� � �������. �������� ��� �� 
 OpAmpK = -R2/R1 = 1100R/5100R = 0.2155, 1/0.2155 = 4.64 ! 
�2 - 1099/5080 R = 4,66
*/
#define OpAmpK   464 

#define ADC_CONV_UP  	 MDR_PORTC->RXTX = 0xffff //MDR_PORTE->RXTX |=  (1<<6);
#define ADC_CONV_DOWN  	 MDR_PORTC->RXTX = 0x0000 //MDR_PORTE->RXTX &= ~(1<<6); 

#define RXFE 1<<4         // ����� 1 ���� ���� ����� FIFO ��������� 
#define FIFO_has_byte    !(MDR_UART1->FR & RXFE)
#define CH3_CCR_CAP_EVENT (1<<7) // ������� ?���������? ������ �� ����� CAP ������� ������� 
                                 // ��� 7 � ������ �����
#define ADC_Vref 3.3		 // ���������� ����������� ���������� ������� ��

  U8 need2conv = 0;    // ���� ������ �������������� ��� DDC	
  U8 meas_mode = 0;    // ���� ������ ���������, 0 - ����������� 1 - ����������
  U8 need2send = 0;    // ���� ������� �� ������ ������ �� UART	
  U8 need2update = 0;
  U8 send_status = 0;  // ���� ������� �� ������ ������� �� UART	

  U16 int_time = 300;     // ���������� ������� ��������������, ���
  U32 ADC1_data[16];      // ������ �������� ������ ��� 
  U32 ADC2_data[16];
  U32 ADC3_data[16];
  
  U32 MCU_current_ADC_channel = 0;
  U16 MCU_ADC_aver_param = 20;		// �������� ����������� ������ ���
  U8  SYNC_RE = 0;
  
  U8 ADC_scale = 2;                     // '2' - 12 pC
  U8 ADC_scale_upd_fl = 0;              // ���� ���������� ����� ���
  U8 ADC_full_scale = 12;               // ������ ����� ���, pC 
  U8 trig_timeout = 0;                  // ���������� �������� ��������� �������� � ���. ������     
    
  U32 full_current = 0;                 // ��� ������
  U32 ADC_noise = 0;                    // �������� ��� �� � ������ ��������� ����
  U32 ADC_code = 0;                    
  
    void OSC_init(void){

	#define	_HSEBYP				1		// 0 - ����� �����������, 1 - ����� �������� ����������
	#define	_HSEON				1		// 0 - ��������, 1 - �������


//---CLK-----------------------------------------------------------------------------------------------------
  
  //MDR_RST_CLK->HS_CONTROL = 2;                            // ����� �������� ����������
  //MDR_RST_CLK->HS_CONTROL = 0x03;                         // ���. HSE ���������

  MDR_RST_CLK->HS_CONTROL = (_HSEBYP<<1) + _HSEON; 
  while ((MDR_RST_CLK->CLOCK_STATUS & 0x04) != 0x04);   // ���� ���� HSE ������ � ������� �����
  MDR_RST_CLK->PLL_CONTROL = ((1 << 2) | (1 << 8)); 	  // ���. PLL | ����. ��������� = 2

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
  
  MDR_PORTA->OE      = 0xFFD5; // PA5 - dvalid3, PA3 - DVALID2, PA1 - DVALID1, PA0 - MCU_CONV
  MDR_PORTA->FUNC    = 0x0000; //0x0800; // ������� - ����, ��� ��5 �������������� ������� 
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
  MDR_PORTC->ANALOG = 0xffff;
  MDR_PORTC->PWR     = 0xFFFFFFFF;      // ����������� ������� ����� ( ������� 10 ��)     
  //---------------------------------------------------------------------------//
  MDR_PORTD->OE = 0x0028;               // ���� D �� ����, PD2 - MCU_ADC_IN, PD5 - S1, PD3 - S2
  MDR_PORTD->FUNC = 0x0000;             // ������� - ���� 
  MDR_PORTD->ANALOG  = 0xffff;          // ����� ����� - ��������, �� PD2 - MCU_ADC_IN
  MDR_PORTD->PWR     = 0xFFFFFFFF;      // ����������� ������� ����� ( ������� 10 ��)
  MDR_PORTD->PD =     ((0 << (2 << 16))); //����� ������ ����� 2 = ���
  //---------------------------------------------------------------------------//
  MDR_PORTE->OE = 0xffff;               // ���� E �� �����
  MDR_PORTE->FUNC = 0x0000;             // ������� - ���� 
  MDR_PORTE->ANALOG  = 0xffff;          // ����� ����� - ��������
  MDR_PORTE->PWR     = 0xFFFFFFFF;      // ����������� ������� ����� ( ������� 10 ��)
  //---------------------------------------------------------------------------//
  MDR_PORTF->OE = 0xffb7;               // ���� F �� �����,PF3 - RxD
  MDR_PORTF->FUNC = (2 << 6) |		    // �����  ����� 1, 2, 3, 4 ����� 
					(2 << 4) |			// - ��������������, ������������ ������ SSP1
					(2 << 2) |
					(2 << 0);
  MDR_PORTF->ANALOG  = 0xffff;          // ����� ����� - ��������
  MDR_PORTF->PWR     = 0xFFFFFFFF;      // ����������� ������� ����� ( ������� 10 ��)

   }

    void timer3_init(void) {
          
  // ��������� ������� ��� ������ ������� ��������� ������ _/
  // + ��������� ��������� ������ ~ 300 ���, ������ �������� ��������� CONV �� ��� 
          
  MDR_TIMER3->CNTRL = 4<<8;                               // �������� ������� - ������� �� 1 ������ ������ 1� 
  MDR_TIMER3->CH1_CNTRL = (1<<15) | (1<<4);               // ����� �������� � ������ ������ | ������������� �����
  MDR_TIMER3->CH1_CNTRL2 = (1<<2)|(1<<1);	          // ���� �� CCR11;������������� ����� �� Chi;
  MDR_TIMER3->CNT   = 0;                                  // ��������� �������� �������� - 0
  MDR_TIMER3->PSG   = 49;                         	  // ������������ ������� ������������ �3 - 1
  MDR_TIMER3->ARR   = 399;                                // ��������� �����, ������ ������ ��
  MDR_TIMER3->IE    = (1<<5); //|(1<<1);//|(1<<13);          // ���������� ���������� �� ��������� � ������� ������ �������� ������, �� ������������ �������
  MDR_RST_CLK->TIM_CLOCK  |= (0|(1 << 26));               // �������� �������|���������� ������������ ������� 3
  MDR_TIMER3->STATUS= 0;                                  // ���������� �����
  
 }       
 
    void timer1_init(void) {

 // ���������� ������ ������� ��� HCLK = 80 M
 
 MDR_RST_CLK->TIM_CLOCK  |= (1 << 24) | 0x03;	// ���������� ������������ Timer1, TIM1_CLK = HCLK/8 
 MDR_TIMER1->CNTRL = 0x00000000;        	// ����� ����� ����� ��� ��������, 
						// ��������� �������� - ����� �� �������� CNT
 MDR_TIMER1->PSG   = 49999;               	// ������������ ������� = 50 000
 MDR_TIMER1->ARR   = 199;                	// ��������� ����� = 200, 200 * 5 �� = 1 ��� 
 MDR_TIMER1->CNT   = 0;       	                // ��������� �������� �������� 
 MDR_TIMER1->IE    = 0x00000002;         	// ���������� ������������ ���������� ��� CNT=ARR
} 
 
/*--------------------------------------------------------------------------- */
// SPI
    void MDR32_SSP1_init (U8 data_lenght){
	  
	MDR_RST_CLK->PER_CLOCK |= 1 << 8;       // ���������� ������������ ������������� ����� SPI 1 (SSP1)
	MDR_RST_CLK->SSP_CLOCK = (1 << 24) | 0; // ���������� �������� ������� �� SSP 1
                                                // �������� �������� ������� SSP1, SSP1_CLK = HCLK (40 ���)
    
	MDR_SSP1->CR0 = (0 << 8) | 	        // ������ �������� SCR ������� F_SSP1 = SSP1_CLK / (CPSDVR*(1  + SCR)) 
  			(1 << 7) |		// ����  �������  SSPCLKOUT, ��������� ���� ����� ������������� �� ��������� ������
    			(0 << 6) |
			(0 << 5) |		// ����������  �������  SSPCLKOUT, 
   			(0 << 4) |		// ������ ��������������� ����� -  �������� SPI ����� Motorola
   			15;			// ������ ����� ������ - 0111 � 16 ���
   
	MDR_SSP1->CPSR = 4; 			// �����������  �������  ��������  ������ CPSDVR
						// ����� �������, ��� CPSDVR = 2, SCR = 0, F_SSP1 = 80 ���
						// ������� SSP1_CLK ���������� ������ 40 ���
	
	MDR_SSP1->CR1 = (0 << 2) |		// ����� �������� ��� �������� ������ ������: 0 � ������� ������ 
			(1 << 1); 	        // ���������� ������ �����������������
	}

    void SPI1_Wr_Data (U16 data){
	  
	  // ������� �������� ������ �� ���� SSP1
	  // ������� DR - 16 ��� !!!!
	  MDR_SSP1->DR = data;
	}

    U16 SPI1_Rd_Data (void){
	  
          
          #define SSP_SR_RNE ((uint32_t)0x00000004) // ��� ���������� FIFO SSP
          
	  // ������� ��������� ������ ���� SSP1
	  // ������� DR - 16 ��� !!!!
	  
	  S16 rx_buf = 0;
	  MDR_SSP1->DR = 0;	         // ������������ �������� ��������
	  while((MDR_SSP1->SR & 1<<4)) { } // ���� ���������� ������
          while((MDR_SSP1->SR & SSP_SR_RNE) != 0) rx_buf = MDR_SSP1->DR; // ������ ��� ��� � ������
	    
	  return rx_buf;

	}

/*--------------------------------------------------------------------------- */
// ADC DDC
    void ADC_config (U8 ADC_scale_code) {
	  
          U32 config_word; // cmd word 
            
	  CPLD_CE_ON;
          /*
	  //SPI1_Wr_Data(0xccc0);  //Test mode 3 (inputs opened and 1.5pC charge dumped into the integrators during each conversion) 12p
	  //SPI1_Wr_Data(0xc0c0);  //Test mode 3 (inputs opened and 1.5pC charge dumped into the integrators during each conversion) 1.5p
	  //SPI1_Wr_Data(0xc4c0);  //Test mode 3 (inputs opened and 1.5pC charge dumped into the integrators during each conversion) 6p
	  //SPI1_Wr_Data(0xcc80);  //Test mode 2 (inputs opened and 10pF internal capacitor connected to integrators)
	  //SPI1_Wr_Data(0xcc40);    //Test mode 1 (inputs opened)
	  //SPI1_Wr_Data(0xcc00);    //normal mode
	  //SPI1_Wr_Data(0xfc00);    //normal mode
          */
	  delay_us(10);
          switch (ADC_scale_code)
          {
            case 0: config_word = 0xc000; ADC_full_scale = 3;  break; // 3 pC
            case 1: config_word = 0xc400; ADC_full_scale = 6;  break; // 6 pC
            case 2: config_word = 0xcc00; ADC_full_scale = 12; break; // 12 pC
           default: config_word = 0xcc00;
          }

          SPI1_Wr_Data(config_word);    // send cmd 2 ADC 
          delay_us(10);
	  CPLD_CE_OFF;	
        }

    void ADC_init (U8 ADC_scale_code) {
	  
  ADC1_RST_ON;
  ADC2_RST_ON;
  ADC3_RST_ON;
  delay_ms(1);
  ADC_config(ADC_scale_code);
  delay_ms(1);
  
	}

/*=========================================================================== */
// UART
    void Uart_init (void){
//UART	  
MDR_PORTB->FUNC |= ((2 << 5*2) | (2 << 6*2)); 	//����� ������ �����
MDR_PORTB->ANALOG |= ((1 << 5) | (1 << 6)); 	//��������
MDR_PORTB->PWR |= ((3 << 5*2) | (3 << 6*2)); 	//����������� ��c����

MDR_RST_CLK->PER_CLOCK |= (1UL << 6); 			//������������ UART1
MDR_RST_CLK->UART_CLOCK = (4 				// ��������� �������� ��� UART1
  |(0 << 8) 						// ��������� �������� ��� UART2
  |(1 << 24) 						// ���������� �������� ������� UART1
  |(0 << 25));						// ���������� �������� ������� UART2*/ 

  //��������� �������� ��� ������� = 5000000�� � �������� = 115200
MDR_UART1->IBRD = 0x2; 					// ����� ����� �������� ��������
MDR_UART1->FBRD = 0x2e; 				// ������� ����� �������� ��������
MDR_UART1->LCR_H = ((0 << 1) 				// ���������� �������� ��������
  |(0 << 2) 						// ��������/����������
  |(0 << 3) 						// ����-���
  |(1 << 4) 						// ���. ������ FIFO ��������� � ����������� 12 ���, ������� 16 ����
  |(3 << 5) 						// ����� ����� = 8 ���
  |(0 << 7)); 						// �������� ���� ��������

//MDR_UART1->IMSC = 1 << 4;                // RXIM ���������� ���������� �� ��������� UARTRXINTR. 1 � �����������;   
MDR_UART1->IMSC = (1 << 10) | (1<<4 );     // �������������  ���������  ����������  ��  ������������  ������ UARTOEINTR 
MDR_UART1->IFLS = 1<<4;                    // ���������� ���������� �� ������. 1/2 ������ ����

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

    void Uart_send_text(unsigned char *s){
  while (*s != 0)
    Uart_send_hex(*s++);
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
  
  //MDR_ADC->ADC2_CFG |= 1 << 17; // ����� ��������� �������� ���������� 1.23 � �� ������� ����������� (������) 
}

    void MCU_ADC_start_conv(void){
  
  	MDR_ADC->ADC1_CFG |= 1<<1;
        MDR_ADC->ADC1_CFG |= 1;
  
}

    U32 MCU_ADC_read(void){
	  
	  // ������ ���, t ������� + t �������������� ������ = 3.2 ��� ��� HCLK = 10� � ������������ ��� = 1
	  //		     t ������� + t �������������� ������ = 0.5 ��� ��� HCLK = 70� � ������������ ��� = 1					
	  // ��� �������� ������� ��� = 3,3/4095 = 0,8 ��
	  
	  U32 ADC_data = 0;
	  
  	  MCU_ADC_start_conv(); // ������ �������������� ������
	  
	  //while(!(MDR_ADC->ADC1_STATUS) & 0x04) {}//(1<<2)) {} // ���� ����������, �� �� ��������
          delay_us(10);
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
	  ADC_rd_data = MCU_ADC_Rd_average(MCU_ADC_aver_param);		// ������ ������� �������� �������� ���
	  ADC_meas_voltage = (U32)((ADC_Vref*ADC_rd_data*1000)/4096);	// ����������� � �����  
	  return ADC_meas_voltage; 

}

/*
    U32 Read_full_Q (U16 integration_time)
     { /// ������ ������� ������ ���������, IVC102
       
        U32 full_current = 0;
        U32 ADC_noise = 0;
 
        IVC_RESET;                         // ����� �����������
        delay_us(10);                      // �����. ��������
        IVC_SET;                           // ����� ������ �����������
        delay_us(10);                      // �����. ��������
        ADC_noise = Get_ADC_ch_voltage(2); // ������ �������� �����������
  
        IVC_START_INT;       // ������ ��������������
        delay_us(integration_time);  // Integration time !
        IVC_STOP_INT;        // ����� ��������������
        delay_us(5);         // �����. ��������
        full_current = Get_ADC_ch_voltage(2); // ������ ������
        full_current -= ADC_noise;            // ������� �������� �����������
        full_current *= OpAmpK;               // �������� � �������. ��������� ��� ��, ��. define
        
        return full_current;
     }
*/
/*=========================================================================== */
// Interupts

__irq void Timer3_IRQHandler(void) 
//������� ��������� ���������� irq Timer 3 - ������ ������� �������������
{

    U32 int_flag = MDR_TIMER3->STATUS; // ����. ����� ���������� ���������� �� �3 
  
    if(int_flag & (1<<5))   //  ___/ ���� ���������� �� ��������� ������
    {   
        MDR_TIMER3->CNTRL &= ~ 1;           // ���� �3 --
        
                                               
        MDR_PORTC->RXTX = ~ MDR_PORTC->RXTX;  
        delay_us(int_time); 
        MDR_PORTC->RXTX = ~ MDR_PORTC->RXTX;  
        delay_us(int_time); 
        
        MDR_PORTC->RXTX = ~ MDR_PORTC->RXTX;     
        delay_us(int_time); 
        MDR_PORTC->RXTX = ~ MDR_PORTC->RXTX; 
        
        IVC_SET;                            // �������� ��� IVC  
        
        IVC_START_INT;                      // ������ ��������������
        delay_us(int_time); 
        //delay_us(int_time);                   // ���� ������������� ����� ��������������
        //MDR_PORTC->RXTX = ~ MDR_PORTC->RXTX;  // ����� �������������� DDC, ��������� ���. ��������� ������ 
        IVC_STOP_INT;                         // ����� �������������� IVC
        need2update = 1;
        SYNC_LED_ON;   
     } 
    
//     else//if(int_flag & (1<<1)) //��������� ���������� ������� ���������� CNT � ARR
//    {   
//        MDR_PORTC->RXTX = ~ MDR_PORTC->RXTX;            
//        delay_us(50);
//        MDR_PORTC->RXTX = ~ MDR_PORTC->RXTX;   
//        delay_us(50);  
//        ADC_noise = Get_ADC_ch_voltage(2);  // ������ �������� �����������
//        //for (U8 i = 0; i < 64; i++) SPI1_Rd_Data();
//     }
   
  MDR_TIMER3->CNT = 0;                // ��������� ����. �������� �� 0   
  MDR_TIMER3->STATUS = 0x0000;        // ����� ������� ����������
  
}

__irq void UART1_IRQHandler( void )
 //������� ��������� ���������� irq UART
{
  /// ���������� ��������� ��� ����������� 8 ���� � ����� FIFO ��������� UART1

         // 12 ���. ����� FIFO, ������� 16 ���� - 7�0 �������� ������ 
         U16 Rx_data[16];
         U8 rd_byte_cntr = 0;
         while(FIFO_has_byte) // ���� ����� �� ����
         {
          Rx_data[rd_byte_cntr] = MDR_UART1->DR; // ������ ����������� ������
          Rx_data[rd_byte_cntr] &= 0x00ff;       // ����������� �� �������  ���  ��������� 
          rd_byte_cntr++;
         }

         switch(Rx_data[0])    // ������� ���� - ��������� �������  
         {
              case 'S':         // ������� �������� ����� � �������� 
                send_status = 1;// ������ �������, ��������� ���� ������� ������� �� ��
              break;
              //--
              case 'C':        // ������� ������� ���������� ��������� ��� 1,2,3 
                need2send = 1; // ������ �������, ��������� ���� ������� ������ �� ��
              break;
              //--
              case 'T':        // ������� ��������� ������� ��������������
                int_time = (Rx_data[2]<<8) + Rx_data[1];
                
                if(int_time > 65000)  int_time = 65000; // 65 ms max
                else if(int_time < 10)int_time = 10;    // 10 us min
                Uart_send_text("T=");
                Uart_num_send(int_time);
                Uart_CR_LF_send();
              break;
              //--
              case 'Q':        // ������� "���. ����� ���"
                ADC_scale_upd_fl = 1;   
                ADC_scale = Rx_data[1]; // '0' - 3pC, '1' - 6pC, '2' - 12pC
              break;
              //--
              case 'M':        // ������� "����� ������ �����", 0 - ����, 1 - ���
                meas_mode = Rx_data[1];

                Uart_send_text("Mode ");
                Uart_num_send(meas_mode);
                Uart_CR_LF_send();                
                
                if(meas_mode == 0)
                {
                  MDR_TIMER3->CNTRL &= ~1;      // ���� �3
                  MDR_TIMER1->CNTRL &= ~1;      // ���� �������� ������� �/� ���.
                  trig_timeout = 0;
                }
                else
                {
                  MDR_TIMER3->CNTRL |= 1;       // ����� ����� ���� ��������
                  MDR_TIMER1->CNTRL |= 1;       // ����� �������� ������� �/� ���.
                  trig_timeout = 0;
                }
              break; 
              //--
              default: Uart_send_text("error"); // ����������� �������
          }// switch
         MDR_UART1->RSR_ECR = 0x00000000;  // ����� ������� ���������� FIFO
                                           // c���� ���������� �� ��������� UARTRXINTR
         MDR_UART1->ICR  = 1<<4 | 1 << 10; // c���� ���������� �� ������������ ������ UARTOEINTR 
}
 
__irq void Timer1_IRQHandler(void) // ���������� ���������� �� ������� 1
{   
    // ���������� ������ �������
 
    trig_timeout++;

    MDR_TIMER1->CNT = 0;                // ��������� �������� �������� � ����
    MDR_TIMER1->STATUS = 0;             // ����� ������� ���������� �� ������� 1
    NVIC_ClearPendingIRQ(Timer1_IRQn);  // ����� ����� ����������
}

      void MCU_init (void) 
    {
	  
      OSC_init();
      SysTickTimer_Init();
      GPIO_init();  
      Uart_init();
      MDR32_SSP1_init(16); 	// ������� GPIO, SPI, UART 
      timer3_init();            // ��� ������ � ���������� ������ - ������ ��������� ������
      timer1_init();		// ������ 15 ��� ��� ������������� ����� � �� � ���������� ������
  
	}

/*=========================================================================== */
// MAIN    
        
 int main()
{
    
 MCU_init();	// ������������ ������ ������������, ������, SPI � UART
      
 ADC_init(ADC_scale);
 MCU_ADC_init();
                  
 NVIC_EnableIRQ(Timer3_IRQn); // ���������� ���������� ��� T3 - ���� ������� �����.
 NVIC_EnableIRQ(UART1_IRQn);  // ���������� ���������� ��� UART1
 NVIC_EnableIRQ(Timer1_IRQn); // ���������� ���������� �� ������� 1
 __enable_irq();	      // Enable Interrupts global
 MDR_TIMER3->CNTRL |= 1;      // ������ �3 --
 
 // ��������������� ���. ������� ������������
 ADC_CONV_DOWN;
 IVC_SET;
 IVC_STOP_INT;
 delay_us(100);

 while(1)
  { 
 
     if(send_status)          // ������� ������� �������
    {
       send_status = 0;      // ����� ����� ������� �������
       Uart_send_text("int_time=");
       Uart_num_send(int_time);
       Uart_send_text(";mode=");
       Uart_num_send(meas_mode);
       Uart_send_text(";q=");
       Uart_num_send(ADC_scale);
       Uart_send_text(";E");
       Uart_CR_LF_send(); 
    }
      
      
    if(ADC_scale_upd_fl)    // ���������� ����� ���
    {
      ADC_scale_upd_fl = 0; // ����� ����� ���. �����

      ADC1_RST_OFF; ADC2_RST_OFF; ADC3_RST_OFF; // ����� ���� ���
      delay_ms(1);
      ADC_init(ADC_scale);
      
      Uart_send_text("Q");
      Uart_num_send(ADC_scale);
      Uart_CR_LF_send();
    }
     
//------------------------------------------------------------------------------  
    switch(meas_mode)      // ������ ���������
    {
    case 0:
/// ����� ����������� ���������  
      if(need2send) // �������� ������� '�' "������ ������"
      { 
        SYNC_LED_ON;                  // ���. ���������
        need2send = 0;                // ����� ����� �������
        //-- DDC --
        for(U8 i = 0; i < 40; i++)
        {
          MDR_PORTC->RXTX = ~ MDR_PORTC->RXTX;      // ��������� ���. ��������� ������ ��������������        
          delay_us(int_time);
          MDR_PORTC->RXTX = ~ MDR_PORTC->RXTX;      // ��������� ���. ��������� ������ ��������������   
          delay_us(int_time);
          if(i == 37) 
          {
            IVC_SET;                            // ����� ������ �����������
            delay_us(10);                       // �����. ��������  
            MCU_ADC_set_ch(2);                  // ��������� ������ ��� 
            // ������ �������� ��� 
            ADC_code  = (S32)MCU_ADC_Rd_average(MCU_ADC_aver_param); 
            // �������������� � ����� - �������� �����������
            ADC_noise     = (U32)(ADC_code*0.8056640625);//ADC_Vref*1000.0)/4096.0);
          }
          if(i == 39){IVC_START_INT;}      // ������ ��������������
          delay_us(int_time);
        }       
        IVC_STOP_INT;        // ����� ��������������
        delay_us(10);        // �����. ��������
        MCU_ADC_set_ch(2);                  // ��������� ������ ��� 
       // ������ �������� ��� 
        ADC_code  = (S32)MCU_ADC_Rd_average(MCU_ADC_aver_param); 
            // �������������� � ����� - ������ ������ IVC
        full_current     = (U32)(ADC_code*0.8056640625);//ADC_Vref*1000.0)/4096.0);
        IVC_RESET;                            // ����� �����������
        full_current -= ADC_noise;            // ������� �������� �����������
        full_current *= OpAmpK;               // �������� � �������. ��������� ��� ��, ��. define
        // � ������ ������. ������ �������
        // ����������� ������� ��������� ���� ���, ����� ������������� � ��   
        
        //-- ������ ������ ��� 3
        for (U8 i = 0; i < 16; i++) ADC3_data[i] = SPI1_Rd_Data();
        //-- ������ ������ ��� 2
        for (U8 i = 0; i < 16; i++) ADC2_data[i] = SPI1_Rd_Data();
        //-- ������ ������ ��� 1
        for (U8 i = 0; i < 16; i++) ADC1_data[i] = SPI1_Rd_Data();
        
        for (U8 i = 0; i < 16; i++) 
        {     
          /// ������ pC �� ������� ���, ��� ��������� pC ���� ������ �� 10 �� �� 
          
          // ��� 3
          ADC3_data[i] = ADC3_data[i] & 0xfff0;   // ����������� �� ��������� 4 ���, �� 12 ���. �����
          ADC3_data[i] = ADC3_data[i] >> 4;       // �������� � 12 ���. ��������
          ADC3_data[i] = (U32)(((ADC3_data[i] * ADC_full_scale*10)/4096.0)); 
          // ��� 2
          ADC2_data[i] = ADC2_data[i] & 0xfff0;   
          ADC2_data[i] = ADC2_data[i] >> 4;       
          ADC2_data[i] = (U32)(((ADC2_data[i] * ADC_full_scale*10)/4096.0));
          // ��� 1
          ADC1_data[i] = ADC1_data[i] & 0xfff0;  
          ADC1_data[i] = ADC1_data[i] >> 4;       
          ADC1_data[i] = (U32)(((ADC1_data[i] * ADC_full_scale*10)/4096.0)); 
        }
        
        Uart_send_text("S;");
        // ������� �� �� ������ ��� 1
        for (U8 i = 0; i < 16; i++) { Uart_num_send(ADC1_data[i]); Uart_send_text(";"); } 
        // ������� �� �� ������ ��� 2
        for (U8 i = 0; i < 16; i++) { Uart_num_send(ADC2_data[i]); Uart_send_text(";"); }
        // ������� �� �� ������ ��� 3
        for (U8 i = 0; i < 16; i++) { Uart_num_send(ADC3_data[i]); Uart_send_text(";"); }
        Uart_num_send(full_current); // ������� ������� ����
        Uart_send_text(";E");
        Uart_CR_LF_send();     
        
        delay_ms(50); // ������ ��������� ����������
        SYNC_LED_OFF; // ����� ���������
      }
      break;
//------------------------------------------------------------------------------ 
    
    case 1:
/// ���������� ����� 

    if(trig_timeout > 14)
    { // ���� �� ��������� ��������..������������� ���������
      
      trig_timeout = 0;    // ����� ���������� �������� ��������
      Uart_send_text("Z"); // �������� ������� ������������� �����
      Uart_CR_LF_send();
    }  
      
    if(need2update) // ������ ����� ���������� ������
     { 
       // ������ ���������������, ���� ���������� ��������������
       delay_us(10);                         // ���� ���������� ������, ~ 6 ��� 
       
        MCU_ADC_set_ch(2);                  // ��������� ������ ��� 
       // ������ �������� ��� 
        ADC_code  = (S32)MCU_ADC_Rd_average(MCU_ADC_aver_param); 
            // �������������� � ����� - ������ ������ IVC
       full_current     = (U32)(ADC_code*0.8056640625);//ADC_Vref*1000.0)/4096.0);
       IVC_RESET;                            // ����� �����������
       full_current -= ADC_noise;            // ������� �������� �����������
       full_current *= OpAmpK;               // �������� � �������. ��������� ��� ��, ��. define
       need2update = 0;                      // ����� ����� ���������� ������
          
       //-- ������ ������ ��� 3
       for (U8 i = 0; i < 16; i++) ADC3_data[i] = SPI1_Rd_Data();
       //-- ������ ������ ��� 2
       for (U8 i = 0; i < 16; i++) ADC2_data[i] = SPI1_Rd_Data();
       //-- ������ ������ ��� 1
       for (U8 i = 0; i < 16; i++) ADC1_data[i] = SPI1_Rd_Data();

// � ������ ������. ������ �������
// ����������� ������� ��������� ���� ���, ����� ������������� � ��   

         for (U8 i = 0; i < 16; i++) 
	 {     
           /// ������ pC �� ������� ���, ��� ��������� pC ���� ������ �� 10 �� �� 
    
           // ��� 3
	   ADC3_data[i] = ADC3_data[i] & 0xfff0;   // ����������� �� ��������� 4 ���, �� 12 ���. �����
	   ADC3_data[i] = ADC3_data[i] >> 4;       // �������� � 12 ���. ��������
	   ADC3_data[i] = (U32)(((ADC3_data[i] * ADC_full_scale*10)/4096.0)); 
           // ��� 2
           ADC2_data[i] = ADC2_data[i] & 0xfff0;   
	   ADC2_data[i] = ADC2_data[i] >> 4;       
	   ADC2_data[i] = (U32)(((ADC2_data[i] * ADC_full_scale*10)/4096.0));
           // ��� 1
           ADC1_data[i] = ADC1_data[i] & 0xfff0;  
	   ADC1_data[i] = ADC1_data[i] >> 4;       
	   ADC1_data[i] = (U32)(((ADC1_data[i] * ADC_full_scale*10)/4096.0)); 
	 }


         Uart_send_text("S;");
         // ������� �� �� ������ ��� 1
         for (U8 i = 0; i < 16; i++) { Uart_num_send(ADC1_data[i]); Uart_send_text(";"); } 
         // ������� �� �� ������ ��� 2
         for (U8 i = 0; i < 16; i++) { Uart_num_send(ADC2_data[i]); Uart_send_text(";"); }
         // ������� �� �� ������ ��� 3
         for (U8 i = 0; i < 16; i++) { Uart_num_send(ADC3_data[i]); Uart_send_text(";"); }
         Uart_num_send(full_current); // ������� ������� ����
         Uart_send_text(";E");
	 Uart_CR_LF_send();         
       
         //delay_ms(20);                      // ������ ��������� ����������
         SYNC_LED_OFF;                      // ����� ���������
         trig_timeout = 0;                  // ����� ���������� �������� ��������
         MDR_TIMER3->CNTRL |= 1;            // ������ �3 --  
         break;             
//------------------------------------------------------------------------------          
      }// if
    
    }//switch 

    
  }// while	
}// main

/*
	������ � ������ ��������������� ��������
    	//������ � ������ ��������������� ��������
	CPLD_CE_ON;
	SPI1_Wr_Data(0xcc00);    //normal mode
	delay_us(3);
	CPLD_CE_OFF;
	delay_us(20);
        SPI1_Rd_Data();
        delay_ms(1);
*/