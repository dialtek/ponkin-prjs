/// ������� ��� ,��������� ��� ����������������  
/// ���������� - �������������� ����������� ����� ���������� ������

/// ���� �������� CPLD ��������� � ������� DIGILENT ADEPT

// modbus ������ 2.0

#include "MDR32Fx.h"
#define F_CPU 80000000

#define U8  uint8_t
#define U16 uint16_t 
#define S16 int16_t 
#define U32 uint32_t
#define S32 int32_t

#include "mdr_delay.h"

//========================== USER DEFINES AND VARS==============================
  
// ������� ������� � ��������� ����� ��������������� ������ � ����
#define CPLD_CE_ON  	 MDR_PORTB->RXTX |=   1<<7   
#define CPLD_CE_OFF  	 MDR_PORTB->RXTX &=  ~(1<<7) 

#define SYNC_LED_ON  	 MDR_PORTE->RXTX |=   1<<3 
#define SYNC_LED_OFF  	 MDR_PORTE->RXTX &=  ~(1<<3) 

#define ADC4_RST_ON 	 MDR_PORTE->RXTX |=  (1<<7)  
#define ADC4_RST_OFF 	 MDR_PORTE->RXTX &= ~(1<<7)
#define ADC3_RST_ON 	 MDR_PORTE->RXTX |=  (1<<2)  
#define ADC3_RST_OFF 	 MDR_PORTE->RXTX &= ~(1<<2)
#define ADC2_RST_ON 	 MDR_PORTE->RXTX |=  (1<<1)  
#define ADC2_RST_OFF 	 MDR_PORTE->RXTX &= ~(1<<1)
#define ADC1_RST_ON 	 MDR_PORTE->RXTX |=  1; 
#define ADC1_RST_OFF 	 MDR_PORTE->RXTX &= ~1;

#define RXFE 1<<4         // ����� 1 ���� ���� ����� FIFO ��������� 
#define FIFO_has_byte    !(MDR_UART1->FR & RXFE)
#define CH3_CCR_CAP_EVENT (1<<7) // ������� ?���������? ������ �� ����� CAP ������� ������� 
                                 // ��� 7 � ������ �����
  U8 meas_mode = 1;    // ���� ������ ���������, 0 - ����������� 1 - ����������
  U8 meas_updated = 0; // ���� ���������� ������ � ���������� ������
  U8 new_meas = 0;     // ���� ������ �������� ����������� ������ � ���������� ������

  U16 int_time = 30;   // ���������� ������� ��������������, ���
  U32 ADC1_data[16];   // ������ �������� ������ ��� 
  U32 ADC2_data[16];
  U32 ADC3_data[16];
  U32 ADC4_data[16];
  
  U16 InputConnPin [65];// ���� �������
  U16 ADCsChDataNum[64];// ������ ���� ���� ��� � ����� �������
   
  U8  SYNC_RE = 0;
  
  U8 ADC_scale = 2;                     // '2' - 12 pC
  U8 ADC_scale_upd_fl = 0;              // ���� ���������� ����� ���
  U8 ADC_full_scale = 12;               // ������ ����� ���, pC 
  U8 trig_timeout = 0;                  // ���������� �������� ��������� �������� � ���. ������     
    
  U32 full_current = 0;                 // ��� ������
//==============================================================================  

  #include "dialtek_modbus.h"
  
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
  
  MDR_PORTA->OE      = 0xFF95; // PA6 - dvalid4 PA5 - dvalid3, PA3 - DVALID2, PA1 - DVALID1, PA0 - MCU_CONV
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
 
/*=========================================================================== */
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
      ADC4_RST_ON;
      delay_ms(1);
      ADC_config(ADC_scale_code);
      delay_ms(1);
  
	}
       
  void ADC_change_scale(void) {
    
      // ���������� ����� ���
    
      ADC1_RST_OFF; // ����� ���� ���
      ADC2_RST_OFF; 
      ADC3_RST_OFF; 
      ADC4_RST_OFF;
      delay_ms(1);
      ADC_init(ADC_scale);
      
    }    
    
  void ADC_read_all(void) {
        // � ������ ������. ������ �������
        // ����������� ������� ��������� ���� ���, ����� ������������� � ��   
      
        //-- ������ ������ ��� 4
        for (U8 i = 0; i < 16; i++)
          ADC4_data[i] = SPI1_Rd_Data();
        //-- ������ ������ ��� 3
        for (U8 i = 0; i < 16; i++)
          ADC3_data[i] = SPI1_Rd_Data();
        //-- ������ ������ ��� 2
        for (U8 i = 0; i < 16; i++) 
          ADC2_data[i] = SPI1_Rd_Data();
        //-- ������ ������ ��� 1
        for (U8 i = 0; i < 16; i++) 
          ADC1_data[i] = SPI1_Rd_Data();

    }
    
  void convert_to_charge(void) {
      
       for (U8 i = 0; i < 16; i++) 
        {     
          /// ������ pC �� ������� ���, ��� ��������� pC ���� ������ �� 10 �� �� 
          
          // ��� 4
          ADC4_data[i] = ADC4_data[i] >> 4;       
          //ADC2_data[i] = (U32)(((ADC2_data[i] * ADC_full_scale*10)/4096.0));

          // ��� 3
          //ADC3_data[i] = ADC3_data[i] & 0xfff0;   // ����������� �� ��������� 4 ���, �� 12 ���. �����
          ADC3_data[i] = ADC3_data[i] >> 4;        // �������� � 12 ���. ��������
          //ADC3_data[i] = (U32)(((ADC3_data[i] * ADC_full_scale*10)/4096.0)); 
          
          // ��� 2
          //ADC2_data[i] = ADC2_data[i] & 0xfff0;   
          ADC2_data[i] = ADC2_data[i] >> 4;       
          //ADC2_data[i] = (U32)(((ADC2_data[i] * ADC_full_scale*10)/4096.0));
          
          // ��� 1
          //ADC1_data[i] = ADC1_data[i] & 0xfff0;  
          ADC1_data[i] = ADC1_data[i] >> 4;       
          //ADC1_data[i] = (U32)(((ADC1_data[i] * ADC_full_scale*10)/4096.0)); 
          
        }
    
    }
     
  void ADC_ch_swap(void) {
      // ���������� ������� ���� ���� ��� 
     // ADC 1
     for(U8 i = 0; i <= 15; i++) 
        ADCsChDataNum[i] = (U16)ADC1_data[i];
     // ADC 2
     for(U8 i = 0; i <= 15; i++) 
        ADCsChDataNum[i+16] = (U16)ADC2_data[i];
     // ADC 3
     for(U8 i = 0; i <= 15; i++) 
        ADCsChDataNum[i+32] = (U16)ADC3_data[i]; 
     // ADC 4
     for(U8 i = 0; i <= 15; i++) 
        ADCsChDataNum[i+48] = (U16)ADC4_data[i]; 
      
      // connector <== ADCs channels, ���������� ������� ��� � ����� �������
     
      InputConnPin[1]  = ADCsChDataNum[0]; 
      InputConnPin[2]  = ADCsChDataNum[2];  
      InputConnPin[3]  = ADCsChDataNum[6];  
      InputConnPin[4]  = ADCsChDataNum[14]; 
      InputConnPin[5]  = ADCsChDataNum[18]; 
      InputConnPin[6]  = ADCsChDataNum[20]; 
      InputConnPin[7]  = ADCsChDataNum[30]; 
      InputConnPin[8]  = ADCsChDataNum[25]; 
      InputConnPin[9]  = ADCsChDataNum[23]; 
      InputConnPin[10] = ADCsChDataNum[32]; 
      InputConnPin[11] = ADCsChDataNum[40]; 
      InputConnPin[12] = ADCsChDataNum[36]; 
      InputConnPin[13] = ADCsChDataNum[44]; 
      InputConnPin[14] = ADCsChDataNum[33]; 
      InputConnPin[15] = ADCsChDataNum[42]; 
      InputConnPin[16] = ADCsChDataNum[39]; 
      InputConnPin[17] = ADCsChDataNum[50]; 
      InputConnPin[18] = ADCsChDataNum[59]; 
      InputConnPin[19] = ADCsChDataNum[62];    
      InputConnPin[20] = ADCsChDataNum[57]; 
      InputConnPin[21] = ADCsChDataNum[11]; 
      InputConnPin[22] = ADCsChDataNum[4];  
      InputConnPin[23] = ADCsChDataNum[13]; 
      InputConnPin[24] = ADCsChDataNum[16]; 
      InputConnPin[25] = ADCsChDataNum[24]; 
      InputConnPin[26] = ADCsChDataNum[17]; 
      InputConnPin[27] = ADCsChDataNum[12]; 
      InputConnPin[28] = ADCsChDataNum[21]; 
      InputConnPin[29] = ADCsChDataNum[29]; 
      InputConnPin[30] = ADCsChDataNum[34]; 
      InputConnPin[31] = ADCsChDataNum[43];
      InputConnPin[32] = ADCsChDataNum[38]; 
      InputConnPin[33] = ADCsChDataNum[10]; 
      InputConnPin[34] = ADCsChDataNum[1];
      InputConnPin[35] = ADCsChDataNum[7];  
      InputConnPin[36] = ADCsChDataNum[9];  
      InputConnPin[37] = ADCsChDataNum[8];  
      InputConnPin[38] = ADCsChDataNum[28]; 
      InputConnPin[39] = ADCsChDataNum[31]; 
      InputConnPin[40] = ADCsChDataNum[22]; 
      InputConnPin[41] = ADCsChDataNum[27]; 
      InputConnPin[42] = ADCsChDataNum[26];  
      InputConnPin[43] = ADCsChDataNum[47];
      InputConnPin[44] = ADCsChDataNum[41];  
      InputConnPin[45] = ADCsChDataNum[46];  
      InputConnPin[46] = ADCsChDataNum[35]; 
      InputConnPin[47] = ADCsChDataNum[37]; 
      InputConnPin[48] = ADCsChDataNum[56];    
      InputConnPin[49] = ADCsChDataNum[60]; 
      InputConnPin[50] = ADCsChDataNum[58]; 
      InputConnPin[51] = ADCsChDataNum[51]; 
      InputConnPin[52] = ADCsChDataNum[61]; 
      InputConnPin[53] = ADCsChDataNum[3];  
      InputConnPin[54] = ADCsChDataNum[15]; 
      InputConnPin[55] = ADCsChDataNum[19]; 
      InputConnPin[56] = ADCsChDataNum[5];  
      InputConnPin[57] = ADCsChDataNum[49]; 
      InputConnPin[58] = ADCsChDataNum[54];    
      InputConnPin[59] = ADCsChDataNum[45]; 
      InputConnPin[60] = ADCsChDataNum[48]; 
      InputConnPin[61] = ADCsChDataNum[52]; 
      InputConnPin[62] = ADCsChDataNum[53]; 
      InputConnPin[63] = ADCsChDataNum[55]; 
      InputConnPin[64] = ADCsChDataNum[63];  
    }
    
  void perform_integrate(void) {
        
        // ���� ����� ��������� ��� ������ ��� �� ��� � ���������� � ����� ���.
        MDR_PORTC->RXTX = ~ MDR_PORTC->RXTX;  
        delay_us(10); 
        MDR_PORTC->RXTX = ~ MDR_PORTC->RXTX;  
        delay_us(10); 
        
        // ������ ��������������
        MDR_PORTC->RXTX = ~ MDR_PORTC->RXTX;    
        
        delay_us(int_time);                 // �������������� � ������� ���. t
        
        MDR_PORTC->RXTX = ~ MDR_PORTC->RXTX;// ����� �������������� IVC     
    }
    
    
/*=========================================================================== */
// UART
  void Uart_init (void){
  MDR_RST_CLK->PER_CLOCK |= (1UL << 22); //������������ ����� B
  MDR_PORTB->FUNC |= ((2 << 5*2) | (2 << 6*2)); //����� ������ �����
  MDR_PORTB->ANALOG |= ((1 << 5) | (1 << 6)); //��������
  MDR_PORTB->PWR |= ((3 << 5*2) | (3 << 6*2)); //����������� ��c����

  MDR_RST_CLK->PER_CLOCK |= (1UL << 6); //������������ UART1
  MDR_RST_CLK->UART_CLOCK = (4 /*��������� �������� ��� UART1 = */
  |(0 << 8) /*��������� �������� ��� UART2 = undefined*/
  |(1 << 24) /*���������� �������� ������� UART1*/
  |(0 << 25)); /*���������� �������� ������� UART2*/ 
  
//��������� �������� ��� ������� = 80 MHz � �������� = 921 600 ���/�
MDR_UART1->IBRD = 0x2; 				// ����� ����� �������� ��������
MDR_UART1->FBRD = 0x2e; 				// ������� ����� �������� ��������
MDR_UART1->LCR_H = ((0 << 1) 				// ���������� �������� ��������
  |(0 << 2) 						// ��������/����������
  |(0 << 3) 						// ����-���
  |(0 << 4) 						// ����. ������ FIFO ��������� � ����������� 12 ���, ������� 16 ����
  |(3 << 5) 						// ����� ����� = 8 ���
  |(0 << 7)); 						// �������� ���� ��������

MDR_UART1->IMSC = 1 << 4;                // RXIM ���������� ���������� �� ��������� UARTRXINTR. 1 � �����������;   
//MDR_UART1->IMSC = (1 << 10) | (1<<4 ); // �������������  ���������  ����������  ��  ������������  ������ UARTOEINTR 
//MDR_UART1->IFLS = 1<<4;                // ���������� ���������� �� ������. 1/2 ������ ����

MDR_UART1->CR = ((1 << 8)|(1 << 9)|1);   // ��������� � �������� ��������, 

}
	
  void uart_send_hex(unsigned char hex_data){
	  
      // ���� �����   FIFO   �����������   ��������...  
   while(MDR_UART1->FR & (1<<5)) { }; // ���� ���������� UART1;

   MDR_UART1->DR = hex_data;
  
  }
	  
  void Uart_CR_LF_send (void){
	  
        uart_send_hex(0x0A);
	uart_send_hex(0x0D);
	
	}

  void Uart_num_send(int32_t data){
	  
  unsigned char temp[10],count=0;
  if (data<0) 
  {
    data=-data;
    uart_send_hex('-');
  }     
  if (data)
  {
    while (data)
    {
      temp[count++]=data%10+'0';
      data/=10;                 
    }                           
    while (count)           
      uart_send_hex(temp[--count]);          
  }
  else uart_send_hex('0');           
}

  void Uart_send_text(unsigned char *s){
  while (*s != 0)
    uart_send_hex(*s++);
}

/*=========================================================================== */
// Interupts
__irq void Timer3_IRQHandler(void) 
//������� ��������� ���������� irq Timer 3 - ������ ������� �������������
{   

    U32 int_flag = MDR_TIMER3->STATUS; // ����. ����� ���������� ���������� �� �3 
     
    if(int_flag & (1<<5))   //  ___/ ���� ���������� �� ��������� ������ ������ !!! ��� ������ �����
    {   
        
        MDR_TIMER3->CNTRL &= ~ 1;           // ���� �3 --
        
        MDR_UART1->IMSC = 0 << 4;           // ������ ���������� �� ��������� UART RX
        perform_integrate();      
        MDR_UART1->IMSC = 1 << 4;           // ���������� ���������� �� ��������� UART RX      
        
        meas_updated = 1; 
     } 
    
  MDR_TIMER3->CNT = 0;                // ��������� ����. �������� �� 0   
  MDR_TIMER3->STATUS = 0x0000;        // ����� ������� ����������
  
}

__irq void UART1_IRQHandler( void )
 //������� ��������� ���������� irq UART1
{
  /// ���������� ��������� ��� ����������� 1 ����� �� UART1
       
        modbus_uart_byte((unsigned char)MDR_UART1->DR); 
      
        MDR_UART1->ICR  = 1<<4; // ����� ���������� �� ���������  
}
/*=========================================================================== */
  void MCU_init (void) {  
      OSC_init();
      SysTickTimer_Init();
      GPIO_init();  
      Uart_init();
      MDR32_SSP1_init(16); 	// ������� GPIO, SPI, UART 
      timer3_init();            // ��� ������ � ���������� ������ - ������ ��������� ������
  }
       
 int main()
{
 U16 cnt = 0;   // ������� ������������ ���. ���������� ����������
 
 MCU_init();	// ������������ ������ ������������, ������, SPI � UART
 modbus_init(); // ������������� MODBUS
 
 ADC_init(ADC_scale);
                 
 NVIC_EnableIRQ(Timer3_IRQn); // ���������� ���������� ��� T3 - ���� ������� �����.
 NVIC_EnableIRQ(UART1_IRQn);  // ���������� ���������� ��� UART1
 __enable_irq();	      // Enable Interrupts global
 MDR_TIMER3->CNTRL |= 1;      // ������ �3 --
 
 while(1)
{   
  
  modbus_rx_sm(); // ������ ������� �������
  modbus_poll();  // ������ � ������ ����������, ������������ � ������� ������ �� �������
  
  // ����� ��������� ��������� ��� ��������� ���������� RS485 ��� �������� ���������� 
  if(meas_mode == 0) // ���� ����� ����������� ���������
  {
    if(answer != 0) 
    {
      SYNC_LED_ON;  
      cnt = 0;
    }
  }   
    
  switch(meas_mode)      // ������ ���������
  {
    case 0:
    /// ����� ����������� ���������  
        perform_integrate();                // ���������� �������������� 
        ADC_read_all();                     // ������ ���� ���� ���
        convert_to_charge();                // �������������� �������� � ������
        ADC_ch_swap();                      // ���������� ������� ��� � ����� �������    
    break;
  //----- 
    case 1:
    /// ���������� ����� 
    if(meas_updated) // ������ ����� ���������� ������
     { 
        meas_updated = 0;
        cnt =0;
        SYNC_LED_ON;  
        // ������ ���������������
        delay_us(10);                       // ���� ���������� ������, ~ 6 ���    
        ADC_read_all();                     // ������ ���� ���� ���
        convert_to_charge();                // �������������� �������� � ������
        ADC_ch_swap();                      // ���������� ������� ��� � ����� �������
                
       MDR_TIMER3->CNTRL |= 1;            // ������ �3 --          
       new_meas = 1;
      }
    break;
//-----     
    default: break;
  }//switch 
  
  delay_ms(10);
  cnt++;
  if(cnt > 10)
  {
    SYNC_LED_OFF;
    cnt = 0;
  }
    
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