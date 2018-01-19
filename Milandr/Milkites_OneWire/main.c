#include "MDR32Fx.h"
// HCLK frequency
#define F_CPU  80000000 

#include "milkites_delay.h"
#include "milkites_spi.h"
#include "MT_12864B_LCD.h"

#define right_button !(MDR_PORTB->RXTX & (0x0400))
#define left_button  !(MDR_PORTB->RXTX & (0x0200))
#define down_button  !(MDR_PORTD->RXTX & (0x0010))
#define up_button    !(MDR_PORTB->RXTX & (0x0100))

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

  MDR_PORTF->OE      = 0xFFFF;          // ���� F �� �����, ������ SSP1 
  MDR_PORTF->FUNC = (2 << 6) |		// �����  ����� 1, 2, 3, 4 ����� 
                    (2 << 4) |          // - ��������������, ������������  SSP1
                    (2 << 2) |
                    (2 << 0);
  MDR_PORTF->ANALOG  = 0xFFFF;          // ����� ����� - ��������
  MDR_PORTF->PWR     = 0xFFFFFFFF;      // ����������� ������� �����
  
  MDR_PORTB->OE      = 0x0000;
  MDR_PORTB->FUNC    = 0x0000;          // ������� - ���� 
  MDR_PORTB->ANALOG  = 0xFFFF;          // ����� ����� - ��������
  MDR_PORTB->PWR     = 0xFFFFFFFF;      // ����������� ������� �����   
  
  MDR_PORTD->OE     = 0x0000;
  MDR_PORTD->FUNC    = 0x0000;          // ������� - ���� 
  MDR_PORTD->ANALOG  = 0xFFFF;          // ����� ����� - ��������
  MDR_PORTD->PWR     = 0xFFFFFFFF;      // ����������� ������� ����� 
}

/*=========================================================================== */
int main() {
 
  
  int counter = 0;
  int page = 0;
  int x = 0;            // ���������� ������ �� X 
  int snake = 1;            // ������
  
  OSC_init();           // ������������� ������� ������������ ��
  SysTickTimer_Init();  // ������������� ���������� �������
  GPIO_init();          // ������������� ������ �����/������
  MDR32_SSP1_init();    // ������������� ������ SSP1

  LCD_init(); 		// ������������ ������� MT12864B
  LCD_clear(); 	        // ������� �������
  LCD_set_cursor(0);     // ���. ������� � 0�� ���. 
  
  while(1)
  { 
   //LCD_clear();  // ������� �������
   
   if(right_button)
   {  // ��������� ������
      x++;   
      LCD_wr_data(0x00);
      LCD_wr_data(snake);
      LCD_column_adr_set(x);
   }
   
   if(left_button)
   {  // ��������� �����
      x--;
      LCD_wr_data(snake);
      LCD_wr_data(0x00);
      LCD_column_adr_set(x);
   }
   
   if(down_button)
   {  // ��������� ����
      snake = snake << 1;
      LCD_wr_data(snake);
      LCD_column_adr_set(x);
   }
   
   if(up_button)
   {  // ��������� �����
      snake = snake >> 1;
      LCD_wr_data(snake);
      LCD_column_adr_set(x);
   }
   
   delay_ms(100);
 
//   LCD_set_cursor(3);
//   LCD_print("�������: ");
//   LCD_wr_num(counter);
//   counter++;
//   delay_ms(100);

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