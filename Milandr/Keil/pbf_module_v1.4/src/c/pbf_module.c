#include "MDR32Fx.h" 
#include "main.h"
#include "pbf_module.h"

//======================== USER FUNCS ===========================//
PORT_InitTypeDef PortInitStructure;

// measured counts to clean I conversion
uint16_t CalcCurrent(uint16_t V_meas, uint16_t Imeas)
{
	uint32_t Iload_meas = 0;
	float 	 Iload_int  = 0;
	
	Iload_meas = (uint32_t)(((float)Imeas * DAC_lsb)/k); // load current
	Iload_meas = (Iload_meas * 1000)/Rs; 								 // load current V to I converison

	Iload_int  = ((float)V_meas * 1000000.0)/Rint;		 // internal load calc
	Iload_meas -= Iload_int;														 // internal load compensation

	if(Iload_meas < 0)		// correct if minus
	 Iload_meas = 0;
	
	return (uint16_t)Iload_meas;
}


//===============================================================//
// MCU periph init

void OSC_init(void)
{

#define	_HSEBYP	0   // 0 - ����� �����������, 1 - ����� �������� ����������
#define	_HSEON  1	  // 0 - ��������, 1 - �������

//---CLK-----------------------------------------------------------------------------------------------------

  MDR_RST_CLK->HS_CONTROL = (_HSEBYP<<1) + _HSEON; 
  while ((MDR_RST_CLK->CLOCK_STATUS & 0x04) != 0x04);     // ���� ���� HSE ������ � ������� �����
  MDR_RST_CLK->PLL_CONTROL = ((1 << 2) | (7 << 8)); 	  // ���. PLL | ����. ��������� = 2

  while((MDR_RST_CLK->CLOCK_STATUS & 0x02) != 0x02);      // ���� ����� PLL ������ � ���. �����

  MDR_RST_CLK->CPU_CLOCK  = (2                           // �������� ��� CPU_C1 - HSE
						   |(1 << 2)                      // �������� ��� CPU_C2 - PLLCPUo 
						   |(1 << 4)                      // ������������ ��� CPU_C3 - CPU_C2
						   |(1 << 8));                    // �������� ��� HCLK
  MDR_RST_CLK->PER_CLOCK = 0xFFFFFFFF;        // ���. ������������ ���� ���������
  // HCLK = 80 ���
}
   








void GPIO_init (void)
{  
  
  MDR_PORTA->OE      = 0xFFDD;          // PA1- ���� �������������, PA5 - ������� ������ ���
  MDR_PORTA->FUNC    = (2<<2);          // ������� - ����, ��� ��1 �������������� ������� 
  MDR_PORTA->ANALOG  = 0xFFFF;          // ����� ����� - ��������
  MDR_PORTA->PWR     = 0xFFFFFFFF;      // ����������� ������� ����� ( ������� 10 ��)
  //---------------------------------------------------------------------------//
  // ������������� ��������� ��� ��������� �����
	PORT_InitTypeDef PORTB_config_struct;
	PORT_StructInit(&PORTB_config_struct);
	
	// ��������� �����
	PORTB_config_struct.PORT_Pin = PORT_Pin_9  & (~JTAG_PINS(MDR_PORTB));  // ����� �� ����������� JTAG,
																																				 // ��������� �� ������������� JTAG-������ ����
	PORTB_config_struct.PORT_OE = PORT_OE_OUT;
	PORTB_config_struct.PORT_MODE = PORT_MODE_DIGITAL;
	PORTB_config_struct.PORT_SPEED = PORT_SPEED_MAXFAST;
	PORT_Init(MDR_PORTB, &PORTB_config_struct);
	
	MDR_PORTB->FUNC |= ((2 << 5*2) | (2 << 6*2)) & (~JTAG_PINS(MDR_PORTB)); //����� ������ �����
  MDR_PORTB->ANALOG |= ((1 << 5) | (1 << 6));   //��������
  MDR_PORTB->PWR |= ((3 << 5*2) | (3 << 6*2));  //����������� ��c����
	
  //---------------------------------------------------------------------------//  
  MDR_PORTC->OE     = 0xffff;                    
  MDR_PORTC->FUNC   = 0x0000;                
  MDR_PORTC->ANALOG = 0xFFFF;      
  MDR_PORTC->PWR    = 0xFFFFFFFF;       // ����������� ������� �����
  //---------------------------------------------------------------------------//
  MDR_PORTD->OE      = 0x00ca;          // ���� D �� ����, PD2 - ADC_CH2, PD4 - ADC_CH4, PD5 - ADC_CH5
  MDR_PORTD->FUNC    = 0x0000;          // ������� - ���� 
  MDR_PORTD->ANALOG  = 0xffcb;          // ����� ����� - ��������, �� PD2 - ADC_CH2, PD4 - ADC_CH4, PD5 - ADC_CH5
  MDR_PORTD->PWR     = 0xFFFFFFFF;      // ����������� ������� ����� ( ������� 10 ��)
  //---------------------------------------------------------------------------//
  MDR_PORTE->OE = 0xffbf;               // ���� E �� �����, PE6 - ���� - ������ ���. �������� ��������
  MDR_PORTE->FUNC = 0x0000;  					  // ������� - ���� 
  MDR_PORTE->ANALOG  = 0xfffe;          // ����� ����� - ��������, PE0 - DAC2 out
  MDR_PORTE->PWR    = 0xFFFFFFFE;       // ����������� ������� �����	
  //---------------------------------------------------------------------------//
  MDR_PORTF->OE = 0xffb7;               // ���� F �� �����,PF3 - RxD
  MDR_PORTF->FUNC = (2 << 6)|		    	  // �����  ����� 1, 2, 3, 4 ����� 
					(2 << 4) |										// - ��������������, ������������ ������ SSP1
					(2 << 2) |
					(2 << 0);
  MDR_PORTF->ANALOG  = 0xffff;          // ����� ����� - ��������
  MDR_PORTF->PWR     = 0xFFFFFFFF;      // ����������� ������� ����� ( ������� 10 ��)
}



void T1_init(void) 
{
          
  MDR_RST_CLK->TIM_CLOCK  |= (1 << 24);      // ���������� ������������ Timer1, TIM1_CLK = HCLK/8 = 10���												

  MDR_TIMER1->CNTRL = 4<<8;                           // �������� ������� - ������� �� 1 ������ ������ 1� 
  MDR_TIMER1->CH1_CNTRL = (1<<15)| (1<<4);            // ����� �������� � ������ ������ | ������������� �����
  MDR_TIMER1->CH1_CNTRL1 = (1<<2)|(1<<1);	      			// ���� �� CCR11; ������������� ����� �� Chi
                                                      // ��������� �������� - ����� �� �������� CNT 
  MDR_TIMER1->PSG   = 0;                           
  MDR_TIMER1->ARR   = 1999;                	      
  MDR_TIMER1->CNT   = 0;       	                      // ��������� �������� �������� 
  MDR_TIMER1->IE    = (1<<13);              					//�� ��������� � ������� ������ 1 ������
  MDR_TIMER1->STATUS= 0;                              // ���������� �����
  
 }

void T2_init(void) 
{
          
 // 200 us int 
    
 MDR_RST_CLK->TIM_CLOCK  |= (1 << 25) | (3<<8); // ���������� ������������ Timer2, TIM2_CLK = HCLK/8											
 MDR_TIMER2->CNTRL = 0x00000000;        	// ����� ������������� �������, ����
 MDR_TIMER2->CNT   = 0x0000;       			  // ��������� �������� ��������
 MDR_TIMER2->PSG   = 0;                   // ������������ �������
 MDR_TIMER2->ARR   = 1999;                // ��������� �����, ���������� ������ 200 us - 1999
 MDR_TIMER2->IE    = 0x00000002;          // ���������� ���������� �� ������������ TIMER2  
 MDR_TIMER2->STATUS= 0x00000000;          // ���������� �����
	
}



// DAC
void MCU_DAC2_init (void)
{
    
    MDR_DAC->CFG = (0<<4) | // DAC1 DAC2 ����������
                   (1<<3) | // DAC2 enabled  
                   (0<<2) | // DAC1 disabled
                   (0<<1) | // DAC2 ref - AUcc voltage
                   (0<<1);  // DAC1 ref - AUcc voltage
 }



//===============================================================//