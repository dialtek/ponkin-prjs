// ���� ���������: 10.01.15
// ������ � �������� ����������� ds18b20

#include "MDR32Fx.h"

#define U8  uint8_t
#define U16 uint16_t 
#define U32 uint32_t

#define S8  int8_t
#define S16 int16_t 
#define S32 int32_t

   void delay_20us (void){
     uint8_t i;
    for(i = 0; i < 115; i++){}  
  }
  
   void delay_3us (void){
     uint8_t i;
    for(i = 0; i < 17; i++){}  
  }

   void delay_5us (void){
     uint8_t i;
    for(i = 0; i < 30; i++){}  
  }
  
   void delay_1us (void){
     uint8_t i;
    for(i = 0; i < 5; i++){}  
  }

   void delay_us (U16 uSeconds){
	 
     uint16_t i;
	 
    for(i = 0; i < (10 * uSeconds); i++) 
	{
	  
	} 
  }

   void delay_100us (void){
    uint16_t i;
    for(i = 0; i < 580; i++){}  

  }
  
   void delay_1ms (void){
     uint32_t i;
    for(i = 0; i < 1610; i++){}  
  }
  
   void uart_delay (void){
     U16 i;
    for(i = 0; i < 2000; i++){}  
  }

   void delay_50ms (void){
     uint32_t i;
    for(i = 0; i < 500000; i++){}  
  }

   void delay_200ms (void){
	delay_50ms();
	delay_50ms();
	delay_50ms();
	delay_50ms();
  }

#define LCD_reset_ON	 MDR_PORTE->RXTX |=   (1<<6)  
#define LCD_reset_OFF 	 MDR_PORTE->RXTX &=  ~(1<<6)
#define LCD_A0_ON 	     MDR_PORTE->RXTX |=   (1<<7)  
#define LCD_A0_OFF 	     MDR_PORTE->RXTX &=  ~(1<<7)
#define LCD_CS_ON 	     MDR_PORTF->RXTX |=   (1<<2)  
#define LCD_CS_OFF 	     MDR_PORTF->RXTX &=  ~(1<<2)

//-----------------------End of LCD defines------------------------------------//

#define ADC_RST_ON 	     MDR_PORTA->RXTX |=   (1<<5)  
#define ADC_RST_OFF 	 MDR_PORTA->RXTX &=  ~(1<<5)
#define ADC_CONV_ON 	 MDR_PORTA->RXTX |=   (1<<0)   	   // ������ ��� ������ ����������� � ��� � 
#define ADC_CONV_OFF 	 MDR_PORTA->RXTX &=  ~(1<<0)   	   // ��� ����������� ���������� ������
#define n_ADC_DVALID_ON  MDR_PORTA->RXTX & 	  (0<<1)  	  // ������ ���������� ������ ��� ��� ������ 

#define VD5_ON  		 MDR_PORTB->RXTX |=   1  
#define VD5_OFF  		 MDR_PORTB->RXTX &=   0  

#define VD6_ON  		 MDR_PORTB->RXTX |=   1<<3  
#define VD6_OFF  		 MDR_PORTB->RXTX &=   0<<3 

#define Charge_ON  		 MDR_PORTA->RXTX |=   1<<7  
#define Charge_OFF  	 MDR_PORTA->RXTX &=  ~(1<<7)  

#define SW1_ON  		 MDR_PORTC->RXTX & (0<<2)  
#define SW1_OFF  		 MDR_PORTC->RXTX & (1<<2)    
#define SW3_ON  		 MDR_PORTE->RXTX & (0<<1)  
#define SW3_OFF  		 MDR_PORTE->RXTX & (1<<1)
#define SW4_ON  		 MDR_PORTE->RXTX & (0<<3)  
#define SW4_OFF  		 MDR_PORTE->RXTX & (1<<3)  

#define ADC_full_scale   12.0								// ������ ����� ��� � �����������

/*--------------------------------------------------------------------------- */
// 1-wire
#define One_wire_port_dir MDR_PORTD->OE
#define One_wire_port 	  MDR_PORTD->RXTX
#define One_wire_pin_num  2  // PD2

#define CRC8INIT   0x00
#define CRC8POLY   0x18  
/*--------------------------------------------------------------------------- */

#include "MT_12864B_abc.h"
//
	U8 conv_fl = 0;
	U8 Uart_rx_fl = 0; // ���� ������� �� ������ ������ �� UART

static __IO uint32_t TimingDelay;

void Delay_ms(__IO uint32_t nTime);	
	
	
	void OSC_init(void){
	  
	/*  
   MDR_RST_CLK->PER_CLOCK = 0xFFFFFFFF;                    // ���. ������������ ���� ���������
  MDR_RST_CLK->HS_CONTROL = 0x01; // ���. HSE ���������� 
  while (MDR_RST_CLK->CLOCK_STATUS & (1 << 2) == 0x00); // ���� ���� HSE ������ � ������� ����� 

  MDR_RST_CLK->PLL_CONTROL = ((1 << 2) | (5 << 8)); //���. PLL | ����. ��������� = 10
  while((MDR_RST_CLK->CLOCK_STATUS & 0x02) != 0x02); //���� ����� PLL ������ � ���. �����

  MDR_RST_CLK->CPU_CLOCK = (2 //�������� ��� CPU_C1
  | (0 << 2) //�������� ��� CPU_C2
  | (0 << 4) //������������ ��� CPU_C3
  | (1 << 8));//�������� ��� HCLK

*/
	  //---CLK-----------------------------------------------------------------------------------------------------
  MDR_RST_CLK->PER_CLOCK = 0xFFFFFFFF;                    // ���. ������������ ���� ���������
  MDR_RST_CLK->HS_CONTROL = 0x01;                         // ���. HSE ���������
  while ((MDR_RST_CLK->CLOCK_STATUS & (1 << 2)) == 0x00); // ���� ���� HSE ������ � ������� �����
  MDR_RST_CLK->PLL_CONTROL = ((1 << 2) | (7 << 8)); 	  // ���. PLL | ����. ��������� = 10
  									  // 7 ��� ������ 10 ���
  									  // 9 ��� ������ 8 ���
  while((MDR_RST_CLK->CLOCK_STATUS & 0x02) != 0x02);      // ���� ����� PLL ������ � ���. �����

  MDR_RST_CLK->CPU_CLOCK  = (2                            // �������� ��� CPU_C1
						   |(1 << 2)                      // �������� ��� CPU_C2
						   |(1 << 4)                      // ������������ ��� CPU_C3
						   |(1 << 8));                    // �������� ��� HCLK
 
  // HCLK = 80 ���
  
  }
   
	void GPIO_init (void){  
  
  MDR_PORTA->OE      = 1 | (1<<5) | (1<<7);      // ���� A1 - ����, A0,A5,A6 �� �����
  MDR_PORTA->FUNC    = 0x0000;          // ������� - ���� 
  MDR_PORTA->ANALOG  = 0xffff;          // ����� ����� - ��������
  MDR_PORTA->PWR     = 0xFFFFFFFF;      // ����������� ������� ����� ( ������� 10 ��)
  //---------------------------------------------------------------------------//
  MDR_PORTB->OE = 0xff00;               // ���� B �� �����, PB6 - UART1 RX
  MDR_PORTB->FUNC = 0x0000;             // ������� - ���� 
  MDR_PORTB->ANALOG  = 0xffff;          // ����� ����� - ��������
  MDR_PORTB->PWR     = 0xFFFFFFFF;      // ����������� ������� ����� ( ������� 10 ��)
  //---------------------------------------------------------------------------//  
  MDR_PORTC->OE      = 0xFFFF;
  //MDR_PORTC->OE      = 0x0000;   		// LCD_A0 ��� �� �����
  MDR_PORTC->FUNC    = 0x0000;          // ������� - ���� 
  MDR_PORTC->ANALOG  = 0xffff;          // ����� ����� - ��������
  MDR_PORTC->PWR     = 0xFFFFFFFF;      // ����������� ������� ����� ( ������� 10 ��)
  //---------------------------------------------------------------------------//
  MDR_PORTD->OE = 0x0000;               // ���� D �� ����, PD4 - LCD_reset
  MDR_PORTD->FUNC = 0x0000;             // ������� - ���� 
  MDR_PORTD->ANALOG  = 0xffff;          // ����� ����� - ��������
  MDR_PORTD->PWR     = 0xFFFFFFFF;      // ����������� ������� ����� ( ������� 10 ��)
  //---------------------------------------------------------------------------//
  MDR_PORTE->OE = 0xffff;               // ���� E �� �����
  MDR_PORTE->FUNC = 0x0000;             // ������� - ���� 
  MDR_PORTE->ANALOG  = 0xffff;          // ����� ����� - ��������
  MDR_PORTE->PWR     = 0xFFFFFFFF;      // ����������� ������� ����� ( ������� 10 ��)
  //---------------------------------------------------------------------------//
  MDR_PORTF->OE = 0xffff;               // ���� D �� �����, ������ SSP1 
  MDR_PORTF->FUNC = (2 << 6) |			// �����  ����� 1, 2, 3, 4 ����� 
					(2 << 4) |			// - ��������������, ������������ ������ SSP1
					(2 << 2) |
					(2 << 0);

  MDR_PORTF->ANALOG  = 0xffff;          // ����� ����� - ��������
  MDR_PORTF->PWR     = 0xFFFFFFFF;      // ����������� ������� ����� ( ������� 10 ��)
   }
 
	void timer1_init(void) {
   
  MDR_TIMER1->CNTRL = 0x00000000;                         // ����� ������������� �������
  MDR_TIMER1->CNT   = 0x00000000;                         // ��������� �������� ��������
  MDR_TIMER1->PSG   = 127;                         		 // ������������ �������
  MDR_TIMER1->ARR   = 0xff;                              // ��������� �����
  MDR_TIMER1->IE    = 0x00000002;                         // ���������� ������������ ���������� ��� CNT=ARR
  MDR_RST_CLK->TIM_CLOCK  = (0|(1 << 24));                // �������� �������|���������� ������������ ������� 1
  MDR_TIMER1->STATUS= 0x00000000;                         // ���������� �����
  NVIC_EnableIRQ(Timer1_IRQn);                            // ���������� ���������� ��� ������� 1
  
  MDR_TIMER1->CNTRL = 1; // �������� ������ 1
 }

/*--------------------------------------------------------------------------- */
// SPI
	void MDR32_SSP1_init (void){
	  
	 
     // ��������� ������ SSP1 ��� ������ � MT-12864B: ����� ��������, 16-������ �����
   
	MDR_RST_CLK->PER_CLOCK |= 1 << 8;     // ���������� ������������ ������������� ����� SPI 1 (SSP1)
	MDR_RST_CLK->SSP_CLOCK = (1 << 24) |  // ���������� �������� ������� �� SSP 1
                                 2;       // �������� �������� ������� SSP1, SSP1_CLK = HCLK (40 ���)
    
	MDR_SSP1->CR0 = (0 << 8) | 			  // ������ �������� SCR ������� F_SSP1 = SSP1_CLK / (CPSDVR*(1  + SCR)) 
  					(1 << 7) |			  // ����  �������  SSPCLKOUT, ��������� ���� �����
    				(1 << 6) |			  // ����������  �������  SSPCLKOUT, ������������� �� ��������� ������
   					(0 << 4) |			  // ������ ��������������� ����� -  �������� SPI ����� Motorola
   						7;				  // ������ ����� ������ - 0111 � 16 ���
   
	MDR_SSP1->CPSR = 2; 				  // �����������  �������  ��������  ������ CPSDVR
										  // ����� �������, ��� CPSDVR = 2, SCR = 0, F_SSP1 = 80 ���
										  // ������� SSP1_CLK ���������� ������ 40 ���
	
	MDR_SSP1->CR1 = (0 << 2) |			  // ����� �������� ��� �������� ������ ������: 0 � ������� ������ 
					(1 << 1); 		      // ���������� ������ �����������������
	
    // ���� SPI1_TxD � SPI1_CLK ��������� �� ����� � GPIO_init()
	// ����� ������� �������������� ����� ����� - ������������ ������ SSP1
	// ���� PF0 - PF3 ������������ ���� �������!
	
    
/*	  
  MDR_RST_CLK->PER_CLOCK |= (1 << 8); //������������ SSP1
  MDR_RST_CLK->SSP_CLOCK = ((0 << 0)|(1 << 24)); //������������ = 1, ���������� ������������ SSP1 

  MDR_SSP1->CPSR = 2; //�������� �������� �������;
  MDR_SSP1->CR0 = 0 << 6; //���������� �������
  MDR_SSP1->CR0 |= 0 << 7; //���� �������
  MDR_SSP1->CR0 |= 0 << 8; //����������� ��������
  MDR_SSP1->CR0 |= 0 << 4; //������ �����
  MDR_SSP1->CR0 |= 15; //����� ����� = 16 ���
  MDR_SSP1->CR1 |= ((0 << 2)|(1 << 1)); //����� ������ � ��������� ����������������� SSP
*/
   }

	void SPI1_Wr_Data (U16 data){
	  
	  // ������� �������� ������ �� ���� SSP1
	  // ������� DR - 16 ��� !!!!
	  MDR_SSP1->DR = data;
	  
	  //------- ��� ������ � �������� MT 12864B --------------------------------
	  
	  delay_3us();			  // �������� ����������� �����!!!
	  LCD_CS_OFF;				  // ������������� �������� SSP1_FSS, 
	  							  // ������� ��� ����� ������ ���� ��������	
							  	  // ��������������� �� ������������� ��� ��������
	  //------- ��� ������ � �������� MT 12864B --------------------------------
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

/*--------------------------------------------------------------------------- */
// LCD
	void LCD_Wr_Cmd (U8 cmd){
	  
		LCD_A0_OFF;
		SPI1_Wr_Data(cmd);
		LCD_A0_ON;
	}

	void LCD_init (void) {
	  
	LCD_reset_OFF;
	delay_20us();
	LCD_reset_ON;
    LCD_A0_OFF;
	
	for(U8 i = 0; i<21;i++) {SPI1_Wr_Data(INIT_LCD_TABLE[i]); delay_3us();}
	
	}

	void LCD_Wr_Data (U8 data) {
	  
	  LCD_A0_ON;
	  SPI1_Wr_Data(data);
	  LCD_A0_OFF;
	}

  	void LCD_page_Adr_set (U8 page) {
    LCD_A0_OFF;
	SPI1_Wr_Data(0xB0 | page);

  	}

	void LCD_Column_Adr_set (U8 column) {

  	U8 i = 0;
	LCD_A0_OFF;
	i = column & 0x0F;
	SPI1_Wr_Data(0x00+i);
	SPI1_Wr_Data(0x10+(column >> 4));

	}
	
	void LCD_set_cursor (uint8_t setPoint){
	  
	  LCD_page_Adr_set(setPoint);
	  LCD_Column_Adr_set(0);
	 
   }
	
	void LCD_Clear (void) {
  		
	for(uint8_t p=0; p<8; p++) {    //���� �� ���� 8-�� ��������� ����������
		LCD_page_Adr_set(p);                 //��������� ������� �������� ��� ������ ��������� ����������
		LCD_Column_Adr_set(0);
		for(uint8_t c=0; c<130; c++) {   //���� ������ ������ � ����� �������� ����������
		  LCD_Wr_Data(0x00);     		 //����� ���������� ����� � ���������
		  
		}
  
  }
  }
	
    void LCD_space (uint8_t SpaceMulCoef){
    
     if (SpaceMulCoef>19) {SpaceMulCoef = 19;}                      //������������� ������ ������� �� ������� ������   
     for(uint8_t c=0; c<4*SpaceMulCoef; c++) {LCD_Wr_Data(0x00);}  //���� � ���������� ���� ������ ����� �� ��������� 
                                                                              
   }
  
    void LCD_inverse_ON (void) {
    // �������� �������������� ����� �������
	LCD_A0_OFF;
	SPI1_Wr_Data(0xA7);

	}
  
	void LCD_inverse_OFF (void) {
    // �������������� ����� �������
	  
	LCD_A0_OFF;
	SPI1_Wr_Data(0xA6);


	}
	
	void LCD_print_Uni_logo (void) {
	// ����� �� ������� ���� ������� � �������
	  	uint8_t logo [8][128] = { 

	0xFF, 0x01, 0xFD, 0xFD, 0xFD, 0xE1, 0xE1, 0xF1, 0x39, 0x1D, 0x0D, 0x05, 0x01, 0x01, 0x01, 0xFD, 0xFD, 0xFD, 0x01, 0x81, 0xC1, 0xE1, 0x71, 0x39, 0xFD, 0xFD, 0xFD, 0x01, 0x09, 0x0D, 0x05, 0x05, 0x05, 0xFD, 0xFD, 0xFD, 0x05, 0x05, 0x05, 0x0D, 0x09, 0x05, 0x85, 0x85, 0x85, 0x85, 0x85, 0x85, 0x85, 0xFD, 0xFD, 0xF9, 0x01, 0x01, 0xF9, 0xFD, 0xFD, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x81, 0xC1, 0xE1, 0xE1, 0xF1, 0xF9, 0xFD, 0xFD, 0xFF, 0xDF, 0xBF, 0x7F, 0x7F, 0xFF, 0x8F, 0x8F, 0xFF, 0x7F, 0x7F, 0xBF, 0xDF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0x3F, 0x9F, 0xDF, 0xDF, 0xDF, 0xDF, 0x3F, 0x3F, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0x00, 0x0F, 0x0F, 0x0F, 0x00, 0x01, 0x03, 0x07, 0x0E, 0x0C, 0x08, 0x00, 0x00, 0x00, 0x0F, 0x0F, 0x0F, 0x07, 0x03, 0x01, 0x00, 0x00, 0x00, 0x0F, 0x0F, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x0F, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x0F, 0x0F, 0x07, 0x00, 0x00, 0x07, 0x0F, 0x0F, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x80, 0xC0, 0xE0, 0xF8, 0xFC, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF3, 0xF3, 0x73, 0x9E, 0xA1, 0xC0, 0x40, 0x40, 0xC0, 0xA1, 0x9E, 0x73, 0xF3, 0xF3, 0xFF, 0xFF, 0xFF, 0xFF, 0x3F, 0x3F, 0x7F, 0xFF, 0xFF, 0xFF, 0xF9, 0xE0, 0x92, 0x13, 0xE7, 0xEF, 0xE7, 0xC7, 0xCF, 0xDF, 0x0E, 0x60, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0x00, 0x00, 0x00, 0x00, 0xC0, 0xF0, 0x3C, 0x0E, 0x06, 0x1C, 0x78, 0xE0, 0x80, 0x00, 0x00, 0x1E, 0x3E, 0x20, 0x20, 0x20, 0x20, 0x20, 0xFE, 0xFE, 0x00, 0xFE, 0xFE, 0x22, 0x22, 0x22, 0x22, 0xE2, 0xC2, 0x00, 0x00, 0x00, 0xFE, 0xFE, 0x20, 0x20, 0x20, 0x20, 0xFE, 0xFE, 0x00, 0x00, 0x00, 0x80, 0xE0, 0xF8, 0x9E, 0x86, 0x9E, 0xB8, 0xE0, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x80, 0xE0, 0xF8, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFC, 0xFC, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xFF, 0xFF, 0xCF, 0xCF, 0x81, 0x9C, 0x9F, 0x3E, 0x7E, 0x1C, 0x19, 0x3B, 0x73, 0x07, 0x4E, 0x1C, 0x00, 0xE0, 0x3C, 0x05, 0xF0, 0xFC, 0xFC, 0x78, 0x01, 0x07, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xE0, 0xE0, 0xE1, 0xE1, 0x81, 0x81, 0x81, 0x81, 0x81, 0xF1, 0xF1, 0x31, 0x31, 0x31, 0x30, 0x31, 0x31, 0x31, 0x31, 0x31, 0x31, 0x31, 0x31, 0x30, 0x30, 0x31, 0x31, 0xF1, 0xF1, 0x81, 0x81, 0x81, 0x80, 0x80, 0x80, 0x80, 0x81, 0x81, 0x80, 0x80, 0x80, 0x80, 0x81, 0xE1, 0xE0, 0xE0, 0xE1, 0xE1, 0xE0, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x81, 0x81, 0x80, 0xC0, 0xFC, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x9F, 0x1F, 0x7F, 0xFF, 0x7F, 0x8F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0x3F, 0x1F, 0x8F, 0xC7, 0xE3, 0xF0, 0xF8, 0x7C, 0x1C, 0x38, 0x7A, 0xF2, 0xF6, 0xE6, 0xC6, 0xE4, 0xE6, 0xC7, 0xCB, 0xDC, 0x06, 0x80, 0xF0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0x07, 0x07, 0x07, 0x07, 0x01, 0x01, 0x01, 0x01, 0x01, 0x0F, 0x0F, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0F, 0x0F, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x07, 0x07, 0xFF, 0xFF, 0x07, 0x07, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0xF9, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFC, 0x34, 0x80, 0x3B, 0x63, 0x1F, 0xFF, 0x3F, 0xFF, 0xFF, 0x9F, 0xAF, 0x37, 0x3B, 0x19, 0x10, 0x8E, 0x86, 0xC1, 0x47, 0x03, 0x03, 0x81, 0xE0, 0xF2, 0xF3, 0x03, 0x02, 0xF0, 0xF1, 0xE3, 0x83, 0x03, 0x03, 0x03, 0x41, 0x8C, 0x8E, 0x1F, 0x1F, 0x3F, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0x00, 0x00, 0xF8, 0xFC, 0x04, 0x04, 0xFC, 0xF8, 0x00, 0x04, 0x04, 0xFC, 0xFC, 0x00, 0x00, 0xF8, 0xFC, 0x04, 0x04, 0xFC, 0xF8, 0x00, 0x04, 0x04, 0xFC, 0xFC, 0x00, 0x00, 0xF8, 0xFC, 0x04, 0x04, 0xFC, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x3F, 0x3F, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x00, 0x00, 0x00, 0x0F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFC, 0xF1, 0xF3, 0xF7, 0xE0, 0x40, 0x0F, 0x07, 0x83, 0xE1, 0xF0, 0xF0, 0xE0, 0xC2, 0xC3, 0x07, 0x07, 0x01, 0x80, 0x08, 0x1E, 0x1F, 0x1F, 0x1F, 0x1F, 0x00, 0x00, 0x1F, 0x1F, 0x1F, 0x1F, 0x1E, 0x08, 0x00, 0x00, 0x01, 0x07, 0x03, 0xC2, 0xC0, 0xE0, 0xF0, 0xE1, 0x83, 0x07, 0x1F, 0x7F, 0xFF, 
	0xFF, 0x00, 0x00, 0x00, 0x21, 0x21, 0xE1, 0xE1, 0x00, 0x00, 0xC0, 0xE0, 0x21, 0x21, 0xE0, 0xC0, 0x00, 0x21, 0x21, 0xE1, 0xE1, 0x00, 0x00, 0xC0, 0xE0, 0x21, 0x21, 0xE0, 0xC0, 0x20, 0x21, 0xE1, 0xE1, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0xFE, 0xFE, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x00, 0x00, 0x00, 0x00, 0x03, 0x3F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x03, 0x00, 0x40, 0x7E, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x01, 0x00, 0x70, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x00, 0x00, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x70, 0x00, 0x00, 0x01, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7E, 0x40, 0x00, 0xFF, 
	0xFF, 0x80, 0x80, 0x80, 0x80, 0x80, 0x8F, 0x8F, 0x80, 0x80, 0x87, 0x8F, 0x88, 0x88, 0x8F, 0x87, 0x80, 0x80, 0x80, 0x8F, 0x8F, 0x80, 0x80, 0x87, 0x8F, 0x88, 0x88, 0x8F, 0x87, 0x80, 0x80, 0x8F, 0x8F, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x86, 0x86, 0x86, 0x86, 0x86, 0x86, 0x87, 0x87, 0x86, 0x86, 0x86, 0x86, 0x86, 0x86, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x81, 0x87, 0x9F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xC0, 0x80, 0x80, 0xF8, 0xF8, 0xF2, 0xF2, 0xE6, 0xE6, 0xEE, 0x80, 0x80, 0x8E, 0xDE, 0xDE, 0xDE, 0xDE, 0x9E, 0x9E, 0x9E, 0xBE, 0x80, 0x80, 0x9E, 0xBE, 0x9E, 0x9E, 0x9E, 0xDE, 0xDE, 0xDE, 0x8E, 0x80, 0x80, 0x80, 0xEE, 0xE6, 0xE6, 0xF2, 0xF2, 0xF8, 0x80, 0x80, 0xFF, 
};
	  
  		for(uint8_t p=0; p<8; p++) {
  			LCD_page_Adr_set(p);
  			LCD_Column_Adr_set(0);
			for(uint8_t i=0; i<128; i++) {
			  LCD_Wr_Data(logo[p][i]);
			}
		}
  }
	
    void LCD_Wr_small_single_num (uint8_t number){
     
     uint8_t t;
     //symbol_cnt++; // ��������� ���������� ���������� ������
     
     switch (number) {
                                                         // ������ ������ ����� - ���� ������
       case 0: for(t=0; t<6; t++) {LCD_Wr_Data(num_0_small[t]);} LCD_Wr_Data(0); break;
       case 1: LCD_Wr_Data(0);LCD_Wr_Data(0);          // ����� ������� ����� ��������� �������� ��������. �����
               for(t=0; t<3; t++) {LCD_Wr_Data(num_1_small[t]);} LCD_Wr_Data(0); break; // ��������� ���� 0 - 9
       case 2: for(t=0; t<5; t++) {LCD_Wr_Data(num_2_small[t]);} LCD_Wr_Data(0); break; 
       case 3: for(t=0; t<5; t++) {LCD_Wr_Data(num_3_small[t]);} LCD_Wr_Data(0); break;
       case 4: for(t=0; t<6; t++) {LCD_Wr_Data(num_4_small[t]);} LCD_Wr_Data(0); break;
       case 5: for(t=0; t<5; t++) {LCD_Wr_Data(num_5_small[t]);} LCD_Wr_Data(0); break;
       case 6: for(t=0; t<5; t++) {LCD_Wr_Data(num_6_small[t]);} LCD_Wr_Data(0); break;
       case 7: for(t=0; t<5; t++) {LCD_Wr_Data(num_7_small[t]);} LCD_Wr_Data(0); break;
       case 8: for(t=0; t<5; t++) {LCD_Wr_Data(num_8_small[t]);} LCD_Wr_Data(0); break;
       case 9: for(t=0; t<5; t++) {LCD_Wr_Data(num_9_small[t]);} LCD_Wr_Data(0); break; 
     }
    }
	
	void LCD_Wr_num (uint32_t number,uint8_t num_lenght){
   
     
    uint16_t first_num;
    uint32_t third_num, fourth_num, fifth_num, second_num;
    
    switch (num_lenght) {
     
    case 1: LCD_Wr_small_single_num(number); break;
  
    case 2: first_num = number/10;               LCD_Wr_small_single_num(first_num);
            number = number-(first_num*10);      LCD_Wr_small_single_num(number);
      break;
      
    case 3: first_num = number/100;              
              LCD_Wr_small_single_num(first_num);
            second_num = number-(first_num*100); 
            second_num = second_num/10; 
              LCD_Wr_small_single_num(second_num);
            number = number-(first_num*100+second_num*10); LCD_Wr_small_single_num(number);
      break;
      
    case 4: first_num = number/1000;              
              LCD_Wr_small_single_num(first_num);
            second_num = number-(first_num*1000); 
            second_num = second_num/100; 
              LCD_Wr_small_single_num(second_num);
            third_num = number-(first_num*1000+second_num*100); 
            third_num = third_num/10; 
              LCD_Wr_small_single_num(third_num);
            number = number-(first_num*1000+second_num*100+third_num*10); 
              LCD_Wr_small_single_num(number);
      break;
      
     case 5: first_num = number/10000;              
              LCD_Wr_small_single_num(first_num);
            second_num = number-(first_num*10000); 
            second_num = second_num/1000; 
              LCD_Wr_small_single_num(second_num);
            third_num = number-(first_num*10000+second_num*1000); 
            third_num = third_num/100; 
              LCD_Wr_small_single_num(third_num);
            fourth_num = number-(first_num*10000+second_num*1000+third_num*100);
            fourth_num = fourth_num/10;
              LCD_Wr_small_single_num(fourth_num);
            number = number-(first_num*10000+second_num*1000+third_num*100+fourth_num*10);
              LCD_Wr_small_single_num(number);
      break;
      
      case 6: first_num = number/100000;              
              LCD_Wr_small_single_num(first_num);
            second_num = number-(first_num*100000); 
            second_num = second_num/10000; 
              LCD_Wr_small_single_num(second_num);
            third_num = number-(first_num*100000+second_num*10000); 
            third_num = third_num/1000; 
              LCD_Wr_small_single_num(third_num);
            fourth_num = number-(first_num*100000+second_num*10000+third_num*1000);
            fourth_num = fourth_num/100;
              LCD_Wr_small_single_num(fourth_num);
            fifth_num = number-(first_num*100000+second_num*10000+third_num*1000+fourth_num*100);
            fifth_num = fifth_num/10;
              LCD_Wr_small_single_num(fifth_num);
            number = number-(first_num*100000+second_num*10000+third_num*1000+fourth_num*100+fifth_num*10);
              LCD_Wr_small_single_num(number);
      break;
      
    }
   }
	
    void LCD_Wr_small_single_word (char word){
   
    switch (word) {
    uint8_t t;                                           // ������ ������ ����� - ���� ������
      
    case '�': for(t=0; t<7; t++) {LCD_Wr_Data(word_A[t]);}  LCD_Wr_Data(0); break;
    case '�': for(t=0; t<7; t++) {LCD_Wr_Data(word_A[t]);}  LCD_Wr_Data(0); break; 
    case '�': for(t=0; t<5; t++) {LCD_Wr_Data(word_6e[t]);} LCD_Wr_Data(0); break;
    case '�': for(t=0; t<5; t++) {LCD_Wr_Data(word_6e[t]);} LCD_Wr_Data(0); break;
    case '�': for(t=0; t<5; t++) {LCD_Wr_Data(word_B[t]);}  LCD_Wr_Data(0); break;
    case '�': for(t=0; t<5; t++) {LCD_Wr_Data(word_B[t]);}  LCD_Wr_Data(0); break;
    case '�': for(t=0; t<5; t++) {LCD_Wr_Data(word_Ge[t]);}                 break; // ��� ������ ������ ����� �� �����
    case '�': for(t=0; t<5; t++) {LCD_Wr_Data(word_Ge[t]);}                 break; // ��� ������ ������ ����� �� �����
    case '�': for(t=0; t<8; t++) {LCD_Wr_Data(word_D[t]);}  LCD_Wr_Data(0); break;
    case '�': for(t=0; t<8; t++) {LCD_Wr_Data(word_D[t]);}  LCD_Wr_Data(0); break;
    case '�': for(t=0; t<5; t++) {LCD_Wr_Data(word_E[t]);}  LCD_Wr_Data(0); break;
    case '�': for(t=0; t<5; t++) {LCD_Wr_Data(word_E[t]);}  LCD_Wr_Data(0); break;
    case '�': for(t=0; t<5; t++) {LCD_Wr_Data(word_E[t]);}  LCD_Wr_Data(0); break;
    case '�': for(t=0; t<5; t++) {LCD_Wr_Data(word_E[t]);}  LCD_Wr_Data(0); break;
    case '�': for(t=0; t<10;t++) {LCD_Wr_Data(word_Je[t]);} LCD_Wr_Data(0); break;
    case '�': for(t=0; t<10;t++) {LCD_Wr_Data(word_Je[t]);} LCD_Wr_Data(0); break;
    case '�': for(t=0; t<5; t++) {LCD_Wr_Data(word_Z[t]);}  LCD_Wr_Data(0); break;
    case '�': for(t=0; t<5; t++) {LCD_Wr_Data(word_Z[t]);}  LCD_Wr_Data(0); break;
    case '�': for(t=0; t<6; t++) {LCD_Wr_Data(word_I[t]);}  LCD_Wr_Data(0); break;
    case '�': for(t=0; t<6; t++) {LCD_Wr_Data(word_I[t]);}  LCD_Wr_Data(0); break;
    case '�': for(t=0; t<6; t++) {LCD_Wr_Data(word_I[t]);} LCD_Wr_Data(0); break;
    case '�': for(t=0; t<6; t++) {LCD_Wr_Data(word_I[t]);} LCD_Wr_Data(0); break;
    case '�': for(t=0; t<6; t++) {LCD_Wr_Data(word_K[t]);}  LCD_Wr_Data(0); break;
    case '�': for(t=0; t<6; t++) {LCD_Wr_Data(word_K[t]);}  LCD_Wr_Data(0); break;
    case '�': for(t=0; t<6; t++) {LCD_Wr_Data(word_L[t]);}  LCD_Wr_Data(0); break;
    case '�': for(t=0; t<6; t++) {LCD_Wr_Data(word_L[t]);}  LCD_Wr_Data(0); break;
    case '�': for(t=0; t<8; t++) {LCD_Wr_Data(word_M[t]);}  LCD_Wr_Data(0); break;
    case '�': for(t=0; t<8; t++) {LCD_Wr_Data(word_M[t]);}  LCD_Wr_Data(0); break;
    case '�': for(t=0; t<6; t++) {LCD_Wr_Data(word_H[t]);}  LCD_Wr_Data(0); break;
    case '�': for(t=0; t<6; t++) {LCD_Wr_Data(word_H[t]);}  LCD_Wr_Data(0); break;
    case '�': for(t=0; t<6; t++) {LCD_Wr_Data(word_O[t]);}  LCD_Wr_Data(0); break;
    case '�': for(t=0; t<6; t++) {LCD_Wr_Data(word_O[t]);}  LCD_Wr_Data(0); break;
    case '�': for(t=0; t<6; t++) {LCD_Wr_Data(word_Pe[t]);} LCD_Wr_Data(0); break;
    case '�': for(t=0; t<6; t++) {LCD_Wr_Data(word_Pe[t]);} LCD_Wr_Data(0); break;
    case '�': for(t=0; t<6; t++) {LCD_Wr_Data(word_R[t]);}  LCD_Wr_Data(0); break;
    case '�': for(t=0; t<6; t++) {LCD_Wr_Data(word_R[t]);}  LCD_Wr_Data(0); break;
    case '�': for(t=0; t<6; t++) {LCD_Wr_Data(word_C[t]);}  LCD_Wr_Data(0); break;
    case '�': for(t=0; t<6; t++) {LCD_Wr_Data(word_C[t]);}  LCD_Wr_Data(0); break;
    case '�': for(t=0; t<6; t++) {LCD_Wr_Data(word_T[t]);}  LCD_Wr_Data(0); break;
    case '�': for(t=0; t<6; t++) {LCD_Wr_Data(word_T[t]);}  LCD_Wr_Data(0); break;
    case '�': for(t=0; t<7; t++) {LCD_Wr_Data(word_Y[t]);}  LCD_Wr_Data(0); break;
    case '�': for(t=0; t<7; t++) {LCD_Wr_Data(word_Y[t]);}  LCD_Wr_Data(0); break;
    case '�': for(t=0; t<8; t++) {LCD_Wr_Data(word_F[t]);}  LCD_Wr_Data(0); break;
    case '�': for(t=0; t<8; t++) {LCD_Wr_Data(word_F[t]);}  LCD_Wr_Data(0); break;
    case '�': for(t=0; t<7; t++) {LCD_Wr_Data(word_X[t]);}  LCD_Wr_Data(0); break;
    case '�': for(t=0; t<7; t++) {LCD_Wr_Data(word_X[t]);}  LCD_Wr_Data(0); break;
    case '�': for(t=0; t<7; t++) {LCD_Wr_Data(word_TCe[t]);}LCD_Wr_Data(0); break;
    case '�': for(t=0; t<7; t++) {LCD_Wr_Data(word_TCe[t]);}LCD_Wr_Data(0); break;
    case '�': for(t=0; t<5; t++) {LCD_Wr_Data(word_4e[t]);} LCD_Wr_Data(0); break;
    case '�': for(t=0; t<5; t++) {LCD_Wr_Data(word_4e[t]);} LCD_Wr_Data(0); break;
    case '�': for(t=0; t<8; t++) {LCD_Wr_Data(word_She[t]);}LCD_Wr_Data(0); break;
    case '�': for(t=0; t<8; t++) {LCD_Wr_Data(word_She[t]);}LCD_Wr_Data(0); break;
    case '�': for(t=0; t<9; t++) {LCD_Wr_Data(word_Sha[t]);}LCD_Wr_Data(0); break;
    case '�': for(t=0; t<9; t++) {LCD_Wr_Data(word_Sha[t]);}LCD_Wr_Data(0); break;
    case '�': for(t=0; t<5; t++) {LCD_Wr_Data(word_Mz[t]);} LCD_Wr_Data(0); break;
    case '�': for(t=0; t<5; t++) {LCD_Wr_Data(word_Mz[t]);} LCD_Wr_Data(0); break;
    case '�': for(t=0; t<7; t++) {LCD_Wr_Data(word_Tz[t]);} LCD_Wr_Data(0); break;
    case '�': for(t=0; t<7; t++) {LCD_Wr_Data(word_Tz[t]);} LCD_Wr_Data(0); break;
    case '�': for(t=0; t<8; t++) {LCD_Wr_Data(word_Ii[t]);} LCD_Wr_Data(0); break;
    case '�': for(t=0; t<8; t++) {LCD_Wr_Data(word_Ii[t]);} LCD_Wr_Data(0); break;
    case '�': for(t=0; t<5; t++) {LCD_Wr_Data(word_Ee[t]);} LCD_Wr_Data(0); break;
    case '�': for(t=0; t<5; t++) {LCD_Wr_Data(word_Ee[t]);} LCD_Wr_Data(0); break;
    case '�': for(t=0; t<8;t++) {LCD_Wr_Data(word_Uy[t]);}  LCD_Wr_Data(0); break;
    case '�': for(t=0; t<8;t++) {LCD_Wr_Data(word_Uy[t]);}  LCD_Wr_Data(0); break;
    case '�': for(t=0; t<6; t++) {LCD_Wr_Data(word_Ya[t]);} LCD_Wr_Data(0); break;
    case '�': for(t=0; t<6; t++) {LCD_Wr_Data(word_Ya[t]);} LCD_Wr_Data(0); break;
  
   
    case '>': for(t=0; t<6; t++) {LCD_Wr_Data(great_sign[t]);}               break; 
    case '<': for(t=0; t<6; t++) {LCD_Wr_Data(less_sign[t]);}                break;
      
    case '=': for(t=0; t<6; t++) {LCD_Wr_Data(eq_sign[t]);} LCD_Wr_Data(0); break;
    case '+': for(t=0; t<5; t++) {LCD_Wr_Data(plus_sign[t]);}LCD_Wr_Data(0);break; 
    case '-': for(t=0; t<5; t++) {LCD_Wr_Data(minus_sign[t]);}LCD_Wr_Data(0);break;
    case ':': for(t=0; t<3; t++) {LCD_Wr_Data(dvoetoch[t]);}                  break;
    case '!': for(t=0; t<3; t++) {LCD_Wr_Data(vosklit_zn[t]);}                break;
    case '?': for(t=0; t<5; t++) {LCD_Wr_Data(vopros_zn[t]);}                 break;
    case '_': for(t=0; t<7; t++) {LCD_Wr_Data(sign__[t]);}                    break; 
    case '*': for(t=0; t<7; t++) {LCD_Wr_Data(zvezd_zn[t]);} break;
    case '/': for(t=0; t<5; t++) {LCD_Wr_Data(sign_t2[t]);} LCD_Wr_Data(0); break; 
    //case '�': for(t=0; t<6; t++) {LCD_Wr_Data(sign_degree[t]);}              break; 
    case '.': for(t=0; t<3; t++) {LCD_Wr_Data(sign_dot[t]);}                 break; 
    case ',': for(t=0; t<3; t++) {LCD_Wr_Data(zap_zn[t]);}                   break; 

    case 'A': for(t=0; t<7; t++) {LCD_Wr_Data(word_A[t]);}  LCD_Wr_Data(0); break; //eng
    case 'a': for(t=0; t<7; t++) {LCD_Wr_Data(word_A[t]);}  LCD_Wr_Data(0); break; //eng
    case 'B': for(t=0; t<5; t++) {LCD_Wr_Data(word_B[t]);}  LCD_Wr_Data(0); break;
    case 'b': for(t=0; t<5; t++) {LCD_Wr_Data(word_B[t]);}  LCD_Wr_Data(0); break;
    case 'C': for(t=0; t<6; t++) {LCD_Wr_Data(word_C[t]);}  LCD_Wr_Data(0); break;
    case 'c': for(t=0; t<6; t++) {LCD_Wr_Data(word_C[t]);}  LCD_Wr_Data(0); break;
    case 'D': for(t=0; t<7; t++) {LCD_Wr_Data(word_D_EN[t]);}  LCD_Wr_Data(0); break;
    case 'd': for(t=0; t<7; t++) {LCD_Wr_Data(word_D_EN[t]);}  LCD_Wr_Data(0); break;
    case 'E': for(t=0; t<5; t++) {LCD_Wr_Data(word_E[t]);}  LCD_Wr_Data(0); break;
    case 'e': for(t=0; t<5; t++) {LCD_Wr_Data(word_E[t]);}  LCD_Wr_Data(0); break;
    case 'F': for(t=0; t<6; t++) {LCD_Wr_Data(word_F_EN[t]);}  LCD_Wr_Data(0); break;
    case 'f': for(t=0; t<6; t++) {LCD_Wr_Data(word_F_EN[t]);}  LCD_Wr_Data(0); break;
    case 'G': for(t=0; t<7; t++) {LCD_Wr_Data(word_G_EN[t]);}  LCD_Wr_Data(0); break;
    case 'g': for(t=0; t<7; t++) {LCD_Wr_Data(word_G_EN[t]);}  LCD_Wr_Data(0); break;    
    case 'H': for(t=0; t<6; t++) {LCD_Wr_Data(word_H[t]);}  LCD_Wr_Data(0); break;
    case 'h': for(t=0; t<6; t++) {LCD_Wr_Data(word_H[t]);}  LCD_Wr_Data(0); break;
    case 'I': for(t=0; t<4; t++) {LCD_Wr_Data(word_I_EN[t]);}  LCD_Wr_Data(0); break;
    case 'i': for(t=0; t<4; t++) {LCD_Wr_Data(word_I_EN[t]);}  LCD_Wr_Data(0); break;   
    case 'J': for(t=0; t<5; t++) {LCD_Wr_Data(word_J_EN[t]);}  LCD_Wr_Data(0); break;
    case 'j': for(t=0; t<5; t++) {LCD_Wr_Data(word_J_EN[t]);}  LCD_Wr_Data(0); break;
    case 'K': for(t=0; t<6; t++) {LCD_Wr_Data(word_K[t]);}  LCD_Wr_Data(0); break;
    case 'k': for(t=0; t<6; t++) {LCD_Wr_Data(word_K[t]);}  LCD_Wr_Data(0); break;
    case 'L': for(t=0; t<6; t++) {LCD_Wr_Data(word_L_EN[t]);}  LCD_Wr_Data(0); break;
    case 'l': for(t=0; t<6; t++) {LCD_Wr_Data(word_L_EN[t]);}  LCD_Wr_Data(0); break;
    case 'M': for(t=0; t<8; t++) {LCD_Wr_Data(word_M[t]);}  LCD_Wr_Data(0); break;   
    case 'm': for(t=0; t<8; t++) {LCD_Wr_Data(word_M[t]);}  LCD_Wr_Data(0); break;
    case 'N': for(t=0; t<7; t++) {LCD_Wr_Data(word_N_EN[t]);}  LCD_Wr_Data(0); break;
    case 'n': for(t=0; t<7; t++) {LCD_Wr_Data(word_N_EN[t]);}  LCD_Wr_Data(0); break;    
    case 'O': for(t=0; t<6; t++) {LCD_Wr_Data(word_O[t]);}  LCD_Wr_Data(0); break;
    case 'o': for(t=0; t<6; t++) {LCD_Wr_Data(word_O[t]);}  LCD_Wr_Data(0); break;
    case 'P': for(t=0; t<6; t++) {LCD_Wr_Data(word_R[t]);}  LCD_Wr_Data(0); break;
    case 'p': for(t=0; t<6; t++) {LCD_Wr_Data(word_R[t]);}  LCD_Wr_Data(0); break;
    case 'Q': for(t=0; t<8; t++) {LCD_Wr_Data(word_Q_EN[t]);}  LCD_Wr_Data(0); break;
    case 'q': for(t=0; t<8; t++) {LCD_Wr_Data(word_Q_EN[t]);}  LCD_Wr_Data(0); break;   
    case 'R': for(t=0; t<6; t++) {LCD_Wr_Data(word_R_EN[t]);}  LCD_Wr_Data(0); break;
    case 'r': for(t=0; t<6; t++) {LCD_Wr_Data(word_R_EN[t]);}  LCD_Wr_Data(0); break; 
    case 'S': for(t=0; t<6; t++) {LCD_Wr_Data(word_S_EN[t]);}  LCD_Wr_Data(0); break;
    case 's': for(t=0; t<6; t++) {LCD_Wr_Data(word_S_EN[t]);}  LCD_Wr_Data(0); break;
    case 'T': for(t=0; t<6; t++) {LCD_Wr_Data(word_T[t]);}  LCD_Wr_Data(0); break;
    case 't': for(t=0; t<6; t++) {LCD_Wr_Data(word_T[t]);}  LCD_Wr_Data(0); break;
    case 'U': for(t=0; t<7; t++) {LCD_Wr_Data(word_U_EN[t]);}  LCD_Wr_Data(0); break;
    case 'u': for(t=0; t<7; t++) {LCD_Wr_Data(word_U_EN[t]);}  LCD_Wr_Data(0); break;    
    case 'V': for(t=0; t<7; t++) {LCD_Wr_Data(word_V_EN[t]);}  LCD_Wr_Data(0); break;
    case 'v': for(t=0; t<7; t++) {LCD_Wr_Data(word_V_EN[t]);}  LCD_Wr_Data(0); break;
    case 'W': for(t=0; t<8; t++) {LCD_Wr_Data(word_W_EN[t]);}  LCD_Wr_Data(0); break;
    case 'w': for(t=0; t<8; t++) {LCD_Wr_Data(word_W_EN[t]);}  LCD_Wr_Data(0); break;
    case 'X': for(t=0; t<7; t++) {LCD_Wr_Data(word_X[t]);}  LCD_Wr_Data(0); break;
    case 'x': for(t=0; t<7; t++) {LCD_Wr_Data(word_X[t]);}  LCD_Wr_Data(0); break;   
    case 'Y': for(t=0; t<6; t++) {LCD_Wr_Data(word_Y_EN[t]);}  LCD_Wr_Data(0); break;
    case 'y': for(t=0; t<6; t++) {LCD_Wr_Data(word_Y_EN[t]);}  LCD_Wr_Data(0); break; 
    case 'Z': for(t=0; t<6; t++) {LCD_Wr_Data(word_Z_EN[t]);}  LCD_Wr_Data(0); break;
    case 'z': for(t=0; t<6; t++) {LCD_Wr_Data(word_Z_EN[t]);}  LCD_Wr_Data(0); break;       
    }
   }
   
    void LCD_print (char* full_word){
   
   uint8_t word_lenght = 0;                     //������������� ���������� ������� �����
   
   for(uint8_t i = 0; i<25; i++){               //���� ����������� ����� �����
     if(full_word[i]==0) {break;}               //����� �� ����� ����� ����� 
     word_lenght++;                             //��������� ��������� ������� �����
   }

   for(uint8_t j = 0; j<word_lenght; j++){      //���� ��������� ����� ����� �� ������
     if (full_word[j]== ' '){LCD_space(1);};    //���� ������� ������ ��� ������, ������ ������  
     LCD_Wr_small_single_word(full_word[j]); 
   }
   }

   	void LCD_print_sova (void) {
	// ����� �� ������� �������� � ������
	  	uint8_t sova [8][128] = {
		  
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x20, 0xC0, 0x80, 0xFC, 0x80, 0xC0, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0x40, 0x60, 0x20, 0x20, 0x20, 0x20, 0x10, 0x10, 0x13, 0x17, 0x1C, 0x18, 0x37, 0x18, 0x16, 0x11, 0x11, 0x31, 0x60, 0x40, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x18, 0x18, 0xF8, 0xFC, 0x43, 0x21, 0x10, 0x08, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFC, 0x07, 0x03, 0x1E, 0x30, 0x60, 0xF8, 0x0C, 0x06, 0x03, 0xC0, 0x70, 0x10, 0x38, 0x08, 0x0C, 0x04, 0x08, 0xF8, 0x00, 0x00, 0x00, 0x80, 0xF0, 0x18, 0x0C, 0x04, 0x0C, 0x04, 0x08, 0x18, 0xF0, 0x03, 0x0E, 0x38, 0xE0, 0x70, 0x18, 0x0E, 0x03, 0xC1, 0x7F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0xC0, 0x80, 0x00, 0x00, 0x00, 0x80, 0x80, 0xC0, 0x60, 0x20, 0x20, 0x30, 0x10, 0x30, 0x20, 0x20, 0x60, 0xC0, 0x80, 0x00, 0x00, 0x80, 0xC0, 0x40, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x07, 0x0C, 0xD8, 0x78, 0x00, 0x00, 0x00, 0xFC, 0x07, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x80, 0xF0, 0x1F, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0xC0, 0x7F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0xFE, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0xE3, 0x42, 0x06, 0x07, 0x00, 0x38, 0x08, 0x18, 0x30, 0x00, 0x00, 0x30, 0x18, 0x18, 0x30, 0x00, 0x01, 0x62, 0x83, 0x39, 0x0C, 0x06, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x07, 0x0C, 0x08, 0x08, 0x10, 0x10, 0x18, 0x0C, 0x07, 0x00, 0xE0, 0x80, 0x00, 0x80, 0xC0, 0x63, 0x0E, 0x08, 0x10, 0x10, 0x10, 0x1C, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0x7C, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFE, 0x83, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x3C, 0x18, 0x0C, 0x04, 0x00, 0x00, 0x00, 0x00, 0x80, 0xFC, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x1C, 0x30, 0x60, 0xC0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x06, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xC0, 0x30, 0x18, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0xC0, 0x60, 0x63, 0x64, 0x58, 0xF0, 0x50, 0x70, 0x70, 0x50, 0x50, 0x50, 0x50, 0x78, 0x78, 0x7C, 0xD7, 0x71, 0x60, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 
	0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x30, 0x30, 0x30, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x0D, 0x3D, 0x1E, 0x0A, 0x1E, 0x1C, 0x6C, 0x0C, 0x0C, 0x08, 0x08, 0x08, 0x08, 0x0C, 0x0C, 0x0C, 0x0C, 0x04, 0x04, 0xE4, 0x1C, 0x9E, 0xFE, 0x8B, 0x93, 0x92, 0x92, 0x92, 0x82, 0x82, 0x82, 0x82, 0x82, 0x81, 0x81, 0x81, 0x81, 0x41, 0x41, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 
	0x00, 0x00, 0x60, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
};

  		for(uint8_t p=0; p<8; p++) {
  			LCD_page_Adr_set(p);
  			LCD_Column_Adr_set(0);
			for(uint8_t i=0; i<128; i++) {
			  LCD_Wr_Data(sova[p][i]);
			}
		}
  }
 
    void Milkites_welcome (void) {
	  
	  LCD_Clear();
	  LCD_print_Uni_logo();
	  delay_200ms();
	  LCD_inverse_ON();
	  LCD_print_Uni_logo();
	  delay_200ms();
	  LCD_inverse_OFF();
	  LCD_Clear();
	  LCD_set_cursor(0);
	  LCD_print("       ��������");
	  LCD_set_cursor(1);
	  LCD_print("==================");
	  LCD_set_cursor(2);
	  LCD_print("     ����������   ");
	  LCD_set_cursor(4);
	  LCD_print(" ����� �� ������� ");	  
	  LCD_set_cursor(6);
	  LCD_print(" ����������� ����� ");
	  LCD_set_cursor(7);
	  LCD_print("������� �����������");
	  delay_200ms();
	  delay_200ms();	
	  delay_200ms();	
	  
		}
  // LCD
  /*--------------------------------------------------------------------------- */
 
	void SPI_clk_disable (void) {
	  
	// ���������� ������ ������ ������ ���
	// ������������� �� ��������� ������ ������� ���������� ��� !!!!!  
	  
	MDR_PORTF->FUNC = (2 << 6) |		// �����  ����� 1, 2, 3, 4 ����� 
					  (2 << 4) |		// - ��������������, ������������ ������ SSP1
					  (0 << 2) |		// ��������� ������������ SPI �������,  
					  					// ������������ �� ������ �����!!!
					  (2 << 0);
	}

	void SPI_clk_enable (void) {
	  
	// ���. ������������ ����� SPI ��� ���������� ����������� ������. ���\
	// ������������ �� ��������� ������ ������� SPI_CLK 
	  
	MDR_PORTF->FUNC = (2 << 6) |		// �����  ����� 1, 2, 3, 4 ����� 
					  (2 << 4) |		// - ��������������, ������������ ������ SSP1
					  (2 << 2) |		// ���. ������������ SPI,  
					  					// ����� ������ ������, ������������ �� ����� SPI
					  (2 << 0);
	}

  /*--------------------------------------------------------------------------- */

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
MDR_UART1->IBRD = 0x2; 						// ����� ����� �������� ��������
MDR_UART1->FBRD = 0x2e; 					// ������� ����� �������� ��������
MDR_UART1->LCR_H = ((0 << 1) 				// ���������� �������� ��������
  |(0 << 2) 								// ��������/����������
  |(0 << 3) 								// ����-���
  |(0 << 4) 						// ����. ������ FIFO ��������� � �����������
  |(3 << 5) 								// ����� ����� = 8 ���
  |(0 << 7)); 							    // �������� ���� ��������

MDR_UART1->CR = ((1 << 8)|(1 << 9)|1);   // ��������� � �������� ��������, 
MDR_UART1->IMSC = 1 << 4; // RXIM ���������� ���������� �� ��������� UARTRXINTR. 1 � �����������;  

// ���������� ����������������� UART1
}

	void Uart_send_hex(U8 hex_data){
  
  	while(MDR_UART1->FR & (1<<3) == 1); // ���� ���������� UART;
										// ������!!! ����� �����������!!!
	uart_delay();				  	    // ����������� � ���������!!!
										// ~ 200 ��� 
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

	void MCU_init (void) {
	  
 	 OSC_init();
 	 GPIO_init();  
 	 Uart_init();
  	 MDR32_SSP1_init();
  
	}

/*=========================================================================== */
// 1-wire 

	void OneWirePin_SetDir(U8 direction) {
	  
   // ������������� ���� 1-wire
  
  if(!direction) One_wire_port_dir &= ~(1 << 2); 			// ��� PD2 �� ����
  else           One_wire_port_dir |=  (1 << 2); 			// ��� PD2 �� �����
  
  MDR_PORTD->FUNC    = 0x0000;          // ������� - ���� 
  MDR_PORTD->ANALOG  = 0xffff;          // ����� ����� - ��������
  MDR_PORTD->PWR     = 0xffffffff;      // ����������� ������� ����� ( ������� 10 ��)

 }
 
 	void OneWirePin_Low() {
	  
   // ������������� ���� �� ���� 1-wire
   
  One_wire_port &= ~ (1 << One_wire_pin_num);
 
 }
 
  	void OneWirePin_High() {
	  
   // ������������� 1 �� ���� 1-wire
   
  One_wire_port |= (1 << One_wire_pin_num);
 
 }
 
 	U8 OneWirePin_level() {
	  
  // ������ �������� ������ �� ���� 1-wire
	  
  return One_wire_port & (1 << One_wire_pin_num);
}

	U8 OneWire_reset() {
	  
  // ����� ������� ������ (reset), ������� �������� ������� �����������.
  // ���� ������� ����������� �������, ���������� ��� ���������� � ���������� 1, ����� ���������� 0 
	  
  OneWirePin_SetDir(1); // ���� �� �����	  
  OneWirePin_Low();
  delay_us(640); // ����� 480..960 ���
  OneWirePin_High();
  delay_us(5); // ����� ����������� �������������� ���������, ����� ������� ������� ������� �� ����
  // ��� �� ����� 60 �� �� ��������� �������� �����������;
  OneWirePin_SetDir(0); // ���� �� ����	
  for (U8 c = 100; c; c--) {
    if (!OneWirePin_level()) {
      // ���� ��������� ������� �����������, ��� ��� ���������
      while (!OneWirePin_level()) { } // ��� ����� ������� �����������
      return 1;
    }
    delay_us(10);
  }
  return 0;
}
 
	void OneWire_send_bit(U8 bit) {
  
  // ���������� ���� ���
  // bit ������������ ��������, 0 - ����, ����� ������ �������� - �������
	  
  OneWirePin_SetDir(1); // ���� �� �����
  OneWirePin_Low();
  if (bit) {
    delay_us(10); // ������ �������, �� 1 �� 15 ��� (� ������ ������� �������������� ������)
    OneWirePin_High();
    delay_us(80); // �������� �� ���������� ��������� (�� ����� 60 ���)
  } 
  else {
    delay_us(80); // ������ ������� �� ���� �������� (�� ����� 60 ���, �� ����� 120 ���)
    OneWirePin_High();
    delay_us(5); // ����� �������������� �������� ������� �� ���� + 1 �� (�������)
  }
}

	U8 OneWire_read_bit() {
  
  // ������ �������� ����, ������������ ������������.
  // ���������� 0 - ���� ������� 0, �������� �� ���� �������� - ���� �������� �������
	  
  U8 r = 0;
  
  OneWirePin_SetDir(1); // ��� �� �����
  OneWirePin_Low();
  delay_us(10); // ������������ ������� ������, ������� 1 ���
  OneWirePin_High();
  delay_us(10); // ����� �� ������� �������������, ����� �� ����� 15 ���
  OneWirePin_SetDir(0); // ��� �� ����
  r = OneWirePin_level();
  delay_us(70); // �������� �� ���������� ����-�����, ������� 60 ��� � ������ ������� ������
  
  return r;
}

    U8 OneWire_read() {
  
  // ������ ���� ����, ���������� �����������, 
  // ������� ��� �����, ���������� ����������� ��������
  
  U8 r = 0;
  
  for (U8 p = 8; p; p--) {
    r >>= 1;
    if (OneWire_read_bit())
      r |= 0x80;
  }
  return r;
}

	void OneWire_send(U8 b) {
  
  // ���������� ���� ����, ������ ������ ���, ������� ��� �����
  // b - ������������ ��������
	  
  for (U8 p = 8; p; p--) {
    OneWire_send_bit(b & 1);
    b >>= 1;
  }
}

	U8 crc8 (U8 data, U8 crc) {
	// ������ ����������� �����
	  
	U8 bit_counter;
	U8 feedback_bit;
	
	bit_counter = 8;
	
	do
	{
    	feedback_bit = (crc ^ data) & 0x01;
    	if ( feedback_bit == 0x01 ) crc = crc ^ CRC8POLY;
    	crc = (crc >> 1) & 0x7F;
    	if ( feedback_bit == 0x01 ) crc = crc | 0x80;
    	data = data >> 1;
    	bit_counter--;
	}  while (bit_counter > 0);
	
	return crc;
 }

	U8 OneWire_skip() {
	  
	// ��������� ������������������ ������������� (reset + ������� ������� �����������)
	// ���� ������� ����������� �������, ��������� ������� SKIP ROM
	// ���������� 1, ���� ������� ����������� �������, 0 - ���� ���
	  
  if (!OneWire_reset())
    return 0;
  OneWire_send(0xCC);
  	return 1;
}
	
	S32 ds18b20_rd_t () {
	  // ������ ��������� �������
	  	 
	 U8 scratchpad[8];		// ����� ������ �������
	 U8 CRC = 0;
	 U8 OneWireRdByte = 0;	
 	 S32 Temper = 0; 
	  
 if (OneWire_skip()) { 				// �������� ������� ������� �� ����
	   
      OneWire_send(0x44); 						// ������ ������, ������ ��������� � 
	  do OneWireRdByte = OneWire_read();		// �������� �� ������� ������ �������� �� ���� 
	  while (OneWireRdByte == 0);
 }
 
 if (OneWire_skip()) {				// ���������� ������ - ������� RESET �����������! 
	  OneWire_send(0xBE);			// ������ �� ������ ������  
	  delay_us(2);

     for (U8 i = 0; i < 9; i++) {		// ���������� ����� �������
        OneWireRdByte = OneWire_read();
        scratchpad[i] = OneWireRdByte;
        CRC = crc8(scratchpad[i], CRC); // ������ CRC
     }	     
	 if(CRC == 0) // CRC �����...
	 	{
	 		Temper = (scratchpad[1] << 8) | scratchpad[0]; // ��������� ��. � �� ����� ������
			if(Temper < 2000)
	 			Temper = (625 * Temper)/10; 				   // �������� ������� � �����������
			 											   	   // +125 �������� - 2000 ��������
			else {
				Temper = Temper - 65535;					   // �������� ������� � �����������
				Temper = (55 * Temper*1000)/879;			   // ������������� �
			}
	 	}
 	 }
 return Temper;	
}

// 1-wire
/*=========================================================================== */
	
__irq void UART1_IRQHandler( void )
 //������� ��������� ���������� irq
{
	 char Rx_data = 0;
 	 
	 Rx_data = MDR_UART1->DR;

	 if (Rx_data == 't')
			Uart_rx_fl = 1; // ������ �������, ��������� ���� ������� �� ��
	 else 	Uart_rx_fl = 2; // ������ �������
	 
	 MDR_UART1->ICR  = 1 << 4; // RXIC ����� ���������� �� ��������� UARTRXINTR
}

/*
	void Timer1_IRQHandler(void) //������� ��������� ���������� irq
{
  if(conv_fl) {ADC_CONV_ON; conv_fl = 0;}
  else {ADC_CONV_OFF; conv_fl = 1;}				

  	Charge_ON;
	delay_20us();
	Charge_OFF;	
	
     MDR_TIMER1->CNT = 0x00000000;      // ��������� ����. �������� �� 0
     MDR_TIMER1->STATUS &= ~(1 << 1);   // ����� ������� ���������� �� ������� 1
     NVIC_ClearPendingIRQ(Timer1_IRQn); // ����� ����� ���������� �� ������� 1
 
}
*/
 

	static __INLINE void SysTickTimer_Init(void)
{
    /// ������������� ���������� �������
  
	SysTick->CTRL |= (1<<2) | (0<<1); // �������� �������������: HCLK 									  
									  // ������ ��������� �� ���� �  ���������� �� ���������
}

	static __INLINE uint8_t SysTickTimer_Set (uint32_t ticks)
{
    
    // ������� Reload - 24 ���, �������� �� ������������
    if (ticks > 0x00FFFFFF)  return (1);           /* Reload value impossible */
	
	SysTick->VAL  = 0;                             /* Load the SysTick Counter Value */
	SysTick->LOAD = ticks;
	
	SysTick->CTRL |= (0<<16) | 1;				   // J,yektybt COUNTFLAG, SysTickTimerStart
	return (0);                                    /* Function successful */
	
/*
��� ������������ ���������� ���������� ����� �������� � N ������ ���������� 
������������ �������� N. ��������, ���� ��������� ���������� ����� 400 ������ 
����������, �� ��������������� RELOAD, ������ 400.  
*/
}

	void _delay_ms(uint16_t delay)
	{
		SysTickTimer_Set(80000*delay); // 1 us ��� HCLK = 80 M
		while(!(SysTick->CTRL & (1<<16)));
	}
	
	void _delay_us(uint16_t delay)
	{
	    
		SysTickTimer_Set(20*delay); // 1 us ��� HCLK = 80 M
		while(!(SysTick->CTRL & (1<<16)));
	}

	int main()							  
{
 S32 Temper = 0;		// �����������
 U32 tens_t = 0;		// ������� �	
 U32 ones_t = 0;		// ������� T
 U32 hunds_t= 0;		// ������� �
 U32 subtens_t= 0;	 	// ����� �
 
 MCU_init();		// ������������ ������� ������������,
  					// ������� GPIO, SPI, UART
 SysTickTimer_Init();
 LCD_init();

 //MDR_PORTC->RXTX = 1; // ������� ���������
 LCD_Clear();
 
 NVIC_EnableIRQ(UART1_IRQn); // ���������� ���������� ��� UART1
 __enable_irq();			 // Enable Interrupts
  
       delay_200ms();
      delay_200ms();
      delay_200ms();
            delay_200ms();
      delay_200ms();
      delay_200ms();
 while(1)
  {
    

     Temper = ds18b20_rd_t();
	 
     tens_t = Temper/10000;  									// �������� ������� �            
     ones_t = Temper-(tens_t*10000); 							// �������� ������� �
     ones_t = ones_t/1000; 									 
     hunds_t = Temper-(tens_t*10000+ones_t*1000); 				// �������� ������� �
     hunds_t = hunds_t/100;
     subtens_t = Temper-(tens_t*10000+ones_t*1000+hunds_t*100);  // �������� ����� �
     subtens_t = subtens_t/10;
	 if(subtens_t >= 5) hunds_t++;							    // ���������� �������	 
	 
	 if(Uart_rx_fl == 1)
	 {  
	    Uart_rx_fl = 0; 		// ����� ����� �������

	 	Uart_num_send(tens_t);   // ������� T �� ��
		Uart_num_send(ones_t);   // ������� T �� ��
		Uart_send_text(".");
		Uart_num_send(hunds_t);  // ������� T �� ��
	 	Uart_CR_LF_send();
		// ������� - 6 ����, ������������� ������
	 }
	 else if (Uart_rx_fl == 2)
	 {
	    Uart_rx_fl = 0; 		// ����� ����� ������
	 	Uart_send_text("err.");  // ������� �����. �� ������ �� ��
	 	Uart_CR_LF_send();
		// ������� - 6 ����, ������������� ������
	 }
         


	 LCD_set_cursor(1);  
         LCD_print("� = ");       
         if(Temper<0)
              LCD_print("-");
         else LCD_print("+");
	 
	 LCD_Wr_num(tens_t,1);
	 LCD_Wr_num(ones_t,1);
	 LCD_print(".");
	 LCD_Wr_num(hunds_t,1);
         LCD_print(" C");
 
 	}
  }	

  

    
    
    