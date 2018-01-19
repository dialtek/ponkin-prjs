#include "MDR32Fx.h"

// HCLK frequency
#define F_CPU  80000000 

#include "milkites_delay.h"
#include "milkites_spi.h"
#include "MT_12864B_LCD.h"

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
  
  MDR_PORTC->OE      = 0xFFFF;
  MDR_PORTC->FUNC    = 0x0000;          // ������� - ���� 
  MDR_PORTC->ANALOG  = 0xFFFF;          // ����� ����� - ��������
  MDR_PORTC->PWR     = 0xFFFFFFFF;      // ����������� ������� ����� 

  MDR_PORTF->OE      = 0xFFFF;               // ���� F �� �����, ������ SSP1 
  MDR_PORTF->FUNC = (2 << 6) |		// �����  ����� 1, 2, 3, 4 ����� 
                    (2 << 4) |          // - ��������������, ������������  SSP1
                    (2 << 2) |
                    (2 << 0);
  MDR_PORTF->ANALOG  = 0xFFFF;          // ����� ����� - ��������
  MDR_PORTF->PWR     = 0xFFFFFFFF;      // ����������� ������� �����
  }

void Timer1_init(void) {// ������� ������������� ������� 1

 // ���������� ������ ������� ��� HCLK = 80 M
 
  /* ������������ ����� Timer1 � �������� PER_CLOCK ���� ��������� � OSC_init() */
 
 MDR_RST_CLK->TIM_CLOCK  = (1 << 24) | 0x03;	// ���������� ������������ Timer1, TIM1_CLK = HCLK/8 
 MDR_TIMER1->CNTRL = 0x00000000;        	// ����� ����� ����� ��� ��������, 
						// ��������� �������� - ����� �� �������� CNT
 MDR_TIMER1->PSG   = 49999;               	// ������������ ������� = 50 000
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

/*================================================================= */
int main() {

  OSC_init();           // ������������� ������� ������������ ��
  SysTickTimer_init();  // ������������� ���������� �������
  GPIO_init();          // ������������� ������ �����/������
  MDR32_SSP1_init();    // ������������� ������ SSP1
  
  LCD_init(); 		    // ������������ ������� MT12864B
  LCD_clear(); 			// ������� �������
  
  Timer1_init();				// ������������� ������� 1
  NVIC_EnableIRQ(Timer1_IRQn);  // ���������� ���������� �� ������� 1
  __enable_irq();               // ���������� ���������� ���������� �� ������� 1
  MDR_TIMER1->CNTRL = 1;        // ������ �������� ������� 1
  
  while(1)
  { 
    LCD_set_cursor(0); 
    LCD_print("MDR_TIMER1->CNT=");
    LCD_wr_num(MDR_TIMER1->CNT);
    
    LCD_set_cursor(2);
    LCD_print("������� ������: ");
    LCD_wr_num(sec_counter);  
  } // while
} // main 
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