#include "MDR32Fx.h"
// HCLK frequency
#define F_CPU  80000000 

#include "milkites_delay.h"
#include "milkites_spi.h"
#include "MT_12864B_LCD.h"
#include "milkites_uart.h"

#define right_button !(MDR_PORTB->RXTX & (0x0400))
#define left_button  !(MDR_PORTB->RXTX & (0x0200))
#define down_button  !(MDR_PORTD->RXTX & (0x0010))
#define up_button    !(MDR_PORTB->RXTX & (0x0100))

uint16_t sec_counter = 0; // ������� ������

void OSC_init(void) {   // ������� ������������� ������� ������������ ��
  
  // ���. PLL | ����. ��������� = 7
  MDR_RST_CLK->PLL_CONTROL = ((1 << 2) | (7 << 8)); 
  // ���� ����� PLL ������ � ���. �����	 
  while((MDR_RST_CLK->CLOCK_STATUS & 0x02) != 0x02);      
  
  MDR_RST_CLK->HS_CONTROL = 0x01;                         // ���. ��������� HSE
  while ((MDR_RST_CLK->CLOCK_STATUS & (1 << 2)) == 0x00); // ���� ����������
  
  MDR_RST_CLK->CPU_CLOCK  =(2                // �������� ��� CPU_C1
                            |(1 << 2)        // �������� ��� CPU_C2
                            |(1 << 4)        // ������������ ��� CPU_C3
                            |(1 << 8));      // �������� ��� HCLK  
 MDR_RST_CLK->PER_CLOCK = 0xFFFFFFFF; // ���. ������������ ���� ���������
 // HCLK = 80 ���	  
  }

void GPIO_init (void) { // ������� ������������� ������ �����/������
  
  MDR_PORTA->OE      = 0xFFFF;
  MDR_PORTA->FUNC    = 0x0000;          // ������� - ���� 
  MDR_PORTA->ANALOG  = 0xFFFF;          // ����� ����� - ��������
  MDR_PORTA->PWR     = 0xFFFFFFFF;      // ����������� ������� ����� 

  MDR_PORTC->OE      = 0xFFFF;
  MDR_PORTC->FUNC    = 0x0000;          // ������� - ���� 
  MDR_PORTC->ANALOG  = 0xFFFF;          // ����� ����� - ��������
  MDR_PORTC->PWR     = 0xFFFFFFFF;      // ����������� ������� ����� 

  MDR_PORTF->OE      = 0xFFFF;          // ���� F �� �����, ������ SSP1 
  MDR_PORTF->FUNC = (2 << 6) |		// �����  ����� 1, 2, 3, 4 ����� 
                    (2 << 4) |          // - ��������������, ������������  SSP1
                    (2 << 2) |
                    (2 << 0);
  MDR_PORTF->ANALOG  = 0xFFFF;          // ����� ����� - ��������
  MDR_PORTF->PWR     = 0xFFFFFFFF;      // ����������� ������� �����
  
  MDR_PORTB->OE      = 0x0400;
  MDR_PORTB->FUNC    = 0x0000;          // ������� - ���� 
  MDR_PORTB->ANALOG  = 0xFFFF;          // ����� ����� - ��������
  MDR_PORTB->PWR     = 0xFFFFFFFF;      // ����������� ������� �����   
  
  MDR_PORTD->OE = 0x00ca;               // ���� D �� ����, PD2 - ADC_CH2, PD4 - ADC_CH4, PD5 - ADC_CH5
  MDR_PORTD->FUNC = 0x0000;             // ������� - ���� 
  MDR_PORTD->ANALOG  = 0xffcb;          // ����� ����� - ��������, �� PD2 - ADC_CH2, PD4 - ADC_CH4, PD5 - ADC_CH5
  MDR_PORTD->PWR     = 0xFFFFFFFF;      // ����������� ������� ����� ( ������� 10 ��)
  MDR_PORTD->PD =     ((0 << (2 << 16))); //����� ������ ����� 2 = ���
  
  MDR_PORTE->OE      = 0xFFF3;          // PE2 - Comp in1, PE3 - Comp in2
  MDR_PORTE->FUNC    = 0x0000;          // ������� - ���� 
  MDR_PORTE->PWR     = 0xFFFFFFFF;      // ����������� ������� ����� 
  MDR_PORTE->ANALOG  = 0xfff2;          // ����� ����� - ��������, PE0 - DAC2 out, PE2 - Comp in1, PE3 - Comp in2
}

/*=========================================================================== */


/*
void Timer1_init(void) {// ������� ������������� ������� 1

 // ���������� ������ ������� ��� HCLK = 80 M
 
  // ������������ ����� Timer1 � �������� PER_CLOCK ���� ��������� � OSC_init() //
 
 MDR_RST_CLK->TIM_CLOCK  |= (1 << 24) | 0x03;	// ���������� ������������ Timer1, TIM1_CLK = HCLK/8 
 MDR_TIMER1->CNTRL = 0x00000000;        	// ����� ����� ����� ��� ��������, 
						// ��������� �������� - ����� �� �������� CNT
 MDR_TIMER1->PSG   = 99;               	        // ������������ ������� = 50 000
 MDR_TIMER1->ARR   = 199;                	// ��������� ����� = 200, 200 * 5 �� = 1 ��� 
 MDR_TIMER1->CNT   = 0;       	                // ��������� �������� �������� 
 MDR_TIMER1->IE    = 0x00000002;         	// ���������� ������������ ���������� ��� CNT=ARR
}

void Timer1_IRQHandler(void) // ���������� ���������� �� ������� 1
{   
    // ���������� ������ �������
 
    sec_counter++;

    MDR_TIMER1->CNT = 0;                // ��������� �������� �������� � ����
    MDR_TIMER1->STATUS = 0;             // ����� ������� ���������� �� ������� 1
    NVIC_ClearPendingIRQ(Timer1_IRQn);  // ����� ����� ����������
}
//================================================================= //
int main() {

  OSC_init();           // ������������� ������� ������������ ��
  SysTickTimer_Init();  // ������������� ���������� �������
  GPIO_init();          // ������������� ������ �����/������
  MDR32_SSP1_init();    // ������������� ������ SSP1
  Uart2_init();
  
  LCD_init(); 		    // ������������ ������� MT12864B
  LCD_clear(); 			// ������� �������
  
  //Timer1_init();				// ������������� ������� 1
  //NVIC_EnableIRQ(Timer1_IRQn);  // ���������� ���������� �� ������� 1
  //__enable_irq();               // ���������� ���������� ���������� �� ������� 1
  //MDR_TIMER1->CNTRL = 1;        // ������ �������� ������� 1
  int x = 0;
  while(1)
  { 
//    LCD_set_cursor(0); 
//    LCD_print("MDR_TIMER1->CNT=");
//    LCD_wr_num(MDR_TIMER1->CNT);
//    
//    LCD_set_cursor(2);
//    LCD_print("������� ������: ");
//    LCD_wr_num(sec_counter);  
    x++;
    if(x > 9) x = 0;
    Uart_send_text("x-000"); Uart_send_num(x); Uart_CR_LF_send();
    delay_ms(25);
        Uart_send_text("y0000"); Uart_send_num(x); Uart_CR_LF_send();
    delay_ms(25);
        Uart_send_text("z-000"); Uart_send_num(x); Uart_CR_LF_send();
    delay_ms(25);
  } // while
} // main 
//================================================================= //
*/


uint16_t MCU_ADC_aver_param = 10;
uint8_t  MCU_current_ADC_channel = 4;

#define ADC_Vref 3.295	// ���������� ����������� ���������� ������� ��



// ADC MCU
    void MCU_ADC_init(){

  //MDR_RST_CLK->PER_CLOCK |= (1 << 17); //������������ ���
  
  MDR_ADC->ADC1_CFG = (1 //��������� ���  
  |(0 << 2)   	// �������� �������������
  |(1 << 3)   	// ����� ������� ������� ��� - ������. 
  |(0 << 4)  	// ����� ������ �������������� - �� �����, ��� ��� ��������� ����� �����
  |(1 << 9)  	// ������������ �������� (������������ ������, ��������� � �������� ������ ������)
  |(0 << 10) 	// �������������� �������� ������� ����.
  |(0 << 11)  	// �������� �������� - ���������� (VDD)
  |(4 << 12)  	// ����������� ������� ������� ADC_clk = HCLK/8 = 10 ���
  |(0 << 16)  	//  ������ ���� ��� ����������� ����.
  |(0 << 17)    //  TS_EN ������ ����������� � ��������� �������� ���������� ����
  |(0 << 18)    // TS_BUF_EN ��������� ��� ������� ����������� � ��������� �������� ���������� ����.
  |(0 << 19) 	// ��������� ������� ����������� ����./
  |(0 << 20));  // ��������� ��������� �������� ���������� �� 1.23 � ����
}

    void MCU_ADC_start_conv(void){
  
  	MDR_ADC->ADC1_CFG |= 1<<1;
  
}

    uint32_t MCU_ADC_read(void){
	  
	  // ������ ���, t ������� + t �������������� ������ = 3.2 ��� ��� HCLK = 10� � ������������ ��� = 1
	  //		     t ������� + t �������������� ������ = 0.5 ��� ��� HCLK = 70� � ������������ ��� = 1					
	  // ��� �������� ������� ��� = 3,3/4095 = 0,8 ��
	  
	  uint32_t ADC_data = 0;
	  
  	  MCU_ADC_start_conv(); // ������ �������������� ������
	  
	  //while(!(MDR_ADC->ADC1_STATUS) & (1<<2)) {} // ���� ���������� 
          delay_us(20);
	  ADC_data = MDR_ADC->ADC1_RESULT;			 // ������
	  
	  MCU_current_ADC_channel = ADC_data << 11;  //����������� ����� 
	  MCU_current_ADC_channel = MCU_current_ADC_channel >> 27;  //������ ��� ���������
	  
	  ADC_data = ADC_data << 20;    // ����������� ���� � 
	  ADC_data = ADC_data >> 20;    // ������ ���������
	  
	  return ADC_data;
}
					   
    void MCU_ADC_set_ch(uint8_t channel){
	  
	if (channel > 16) return;
	
	MDR_ADC->ADC1_CHSEL = 1 << channel; 
	
	
}

    uint32_t MCU_ADC_Rd_average(uint16_t AverValue){
	  
	  // ������ ���, t ������� + t �������������� ������ = 3.2 ��� ��� HCLK = 10� � ������������ ��� = 1
	  // t ������� + t �������������� ������ = 0.5 ��� ��� HCLK = 70� � ������������ ��� = 1	
	  // ���������� ����������� �������������� ���
	  
	  uint32_t Aver_ADC_data = 0;
	  
	  for(int i = 0; i < AverValue; i++ )
	  {
	   Aver_ADC_data += MCU_ADC_read();
	  }
  
	  Aver_ADC_data = Aver_ADC_data/AverValue; 
	  
	  return Aver_ADC_data;
}

    uint32_t Get_ADC_ch_voltage(uint8_t ADC_channel){
	  // ������ ������������ ���������� ��������. ������ ���, �������������� � ��
	  
	  uint32_t ADC_rd_data = 0;
 	  uint32_t ADC_meas_voltage = 0;
	  
	  MCU_ADC_set_ch(ADC_channel);	// ��������� ������ ���
	  ADC_rd_data = MCU_ADC_Rd_average(MCU_ADC_aver_param);		// ������ ������� �������� �������� ���
	  ADC_meas_voltage = (int)(ADC_Vref*ADC_rd_data*1000)/4096;	// ����������� � �����  
	  return ADC_meas_voltage; 

}


/*=========================================================================== */
// DAC
  void MCU_DAC2_init (void)
  {
    
    MDR_DAC->CFG = (0<<4) | // DAC1 DAC2 ����������
                   (1<<3) | // DAC2 enabled  
                   (0<<2) | // DAC1 disabled
                   (0<<1) | // DAC2 ref - AUcc voltage
                   (0<<1);  // DAC1 ref - AUcc voltage
  }
/*=========================================================================== */
// comparator
  void comparator_init()
  {
    
    MDR_RST_CLK->PER_CLOCK |= (1 << 19); //������������ �����������
    
    MDR_COMP->CFG = (1  // ���. ����������   
        |(1 << 1)   	// �������� CVREF �������� � ������ ��������� 
        |(0 << 2)   	// �������� CVREF �������� � �������� AVdd AGND;
        |(0 << 3)  	// CVREF �� ��������;  
        |(0 << 4)  	// ���� ������ ������ ���������� �������������� ������ CVREF. ������������ ���������� ����� 
        |(0 << 8) 	// �� �+� ����������� ������ �������� � IN1; 
        |(0 << 9)  	// �� �-� ����������� ������ �������� � IN2; 
        |(0 << 11)  	// ��� �������� ������ ����������� 
        |(0 << 12)  	// ������ ���������� ����������� ����������� ��� ���������:
        |(1 << 13));     // ���� ���������� ��������� ���������� �� ������� Rst_lch: ��������� ����������  
  }
  
int main() {
 
  uint32_t V = 0;
  
  OSC_init();           // ������������� ������� ������������ ��
  SysTickTimer_Init();  // ������������� ���������� �������
  GPIO_init();          // ������������� ������ �����/������
  MDR32_SSP1_init();    // ������������� ������ SSP1
  
  MCU_ADC_init();
  MCU_DAC2_init();
  Uart2_init();  
  comparator_init();
  LCD_init(); 		// ������������ ������� MT12864B
  LCD_clear(); 	        // ������� �������
  LCD_set_cursor(0);    // ���. ������� � 0�� ���. 
  U32 result = 0;
  
  MDR_DAC->DAC2_DATA = 0;
  U32 dac_data = 0;
   
  while(1)
  { 
   LCD_set_cursor(0);
   LCD_print("      ����� ���     "); 
   
   V = Get_ADC_ch_voltage(4);
   LCD_set_cursor(2);
   LCD_print("U �� = ");
   LCD_wr_num(V);
   LCD_print(" ��     ");
 
   // DAC
   MDR_DAC->DAC2_DATA = dac_data;//(U32) (V/0.805664);
   // comparator result
   LCD_set_cursor(4);
   //LCD_print("result = ");
   while(! (MDR_COMP->CFG & 1<<12)) {}
   //LCD_wr_num(MDR_COMP->RESULT & 0x0001);
   result = MDR_COMP->RESULT_LATCH & 0x0001;
   LCD_print("���. ������. = ");
   LCD_wr_num(result);
   LCD_print("  ");
   
   if(!result) 
   {
     dac_data++;
     MDR_PORTC->RXTX = ~ MDR_PORTC->RXTX;
   }

   if(dac_data == 4084) dac_data = 0;
   
   LCD_set_cursor(6);
   LCD_print("U ���. = ");;
   LCD_wr_num((U32)(dac_data*0.805664));
   LCD_print(" ��  ");
   
   while(MDR_PORTB->RXTX & 1<<5)
   { // ��������� ��������� ������
    MDR_PORTA->RXTX |= 1;
    dac_data = 0;
    MDR_DAC->DAC2_DATA = dac_data;
    delay_ms(100);
    MDR_PORTA->RXTX &= ~1; 
   }

   while (!(MDR_PORTB->RXTX & 1<<4))
   {
     for(uint32_t x = 0; x < 100; x++  )
   {
      MDR_PORTC->RXTX = 1;
      delay_us((uint16_t)V/2);
      MDR_PORTC->RXTX = 0;
      delay_us((uint16_t)V/2);
   }
   
   }
    //delay_ms(1);

  }
}
    



    
//    LCD_print("Uart test");			// ����� ������ �������
//    LCD_set_cursor(1); 				// ��������� ������� �� ������ ������ �������
//    LCD_print("������� ������: ");	// ����� ������ �� �������
//    LCD_wr_num(sec_counter);		// ����� ����� �� �������
//    

    
    
    
//    if(need2send == 1) // ������ � �� �������
//    {
//      Uart_send_text(" Ok! �� ��������: ");
//      Uart_CR_LF_send();
//      for(uint8_t i = 0; i < 8; i++)
//        {
//          Uart_send_hex(rx_data[i]);
//        }
//		// �������� �������� �������� ������� � �������� ������ �� ��
//        Uart_CR_LF_send();		        
//      
//      need2send = 0;				// ����� ����� ������� ������ �� ��
//    }
//    sec_counter++;					// ��������� �������� ������
//    delay_ms(1000);					// �������� 1000 ��
    
 // } // while
//} // main 
/*================================================================= */



//    LCD_print("   ��� ������������ ");
    
//    LCD_print("   ���������� �����");
//    LCD_set_cursor(3);
//    LCD_print(">>>>>> �������� <<<<<<");
//    LCD_set_cursor(5);
//    LCD_print("Hello World! Rus Eng");
//    
//    LCD_set_cursor(7);
//    LCD_print("������� ������: "); 
//    LCD_wr_num(counter);
//    
//    counter++;
//    if(counter > 10000) counter = 0;
//    delay_ms(1000);
  /*
// ������ ������ T
  int Temper = 0; // ��������� ���������� ��� ���������� �
  
  // 1-wire
#define One_wire_port_dir MDR_PORTD->OE     // ������� �������������� ����� 1-wire
#define One_wire_port 	  MDR_PORTD->RXTX   // ������� ������ ����� 1-wire
#define One_wire_pin_num 2  // PD2			// ����� ���� 1 - wire

#include "mdr_1_wire.h"     // ����������� ���������� 1 - wire 

#define right_b (!(MDR_PORTB->RXTX & (1<<10))) 
#define up_b    (!(MDR_PORTB->RXTX & (1<<8)))
#define left_b  (!(MDR_PORTB->RXTX & (1<<9)))
#define down_b  (!(MDR_PORTD->RXTX & (1<<4)))
  
  
Temper = ds18b20_rd_t();	 

LCD_set_cursor(1);  
         LCD_print("� = ");       
         if(Temper<0)
         {
              LCD_print("-");
              Temper = Temper * -1;
         }
         else LCD_print("+");
         
int a = Temper/10000;
int b = (Temper-(a*10000))/1000;
int c = (Temper-(a*10000)-(b*1000))/100;

	 LCD_Wr_num(a,1);
	 LCD_Wr_num(b,1);
	 LCD_print(".");
	 LCD_Wr_num(c,1);
         LCD_print(" C");
         
         */