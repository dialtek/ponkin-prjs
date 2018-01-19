#include "MDR32Fx.h"
// HCLK frequency
#define F_CPU  80000000 

#define U8  uint8_t
#define U16 uint16_t 
#define U32 uint32_t
#define S32 int32_t

#define One_wire_port MDR_PORTF->RXTX 
#define One_wire_pin_num 1 
#define One_wire_port_dir MDR_PORTF->FUNC 

#include "milkites_delay.h"
#include "milkites_uart.h"
#include "mdr_1_wire.h"


uint8_t need2send = 0;   // флаг запроса на выдачу данных по UART2	
uint16_t rx_data[16];    // буфер для чтения данных с ПК
 S32 t = 0;


//---------------------------LCD defines--------------------------------------//
//#define LCD_E1_ON   MDR_PORTE->RXTX |=  (1<<4) 
//#define LCD_E1_OFF  MDR_PORTE->RXTX &= ~(1<<4)
//#define LCD_E2_ON   MDR_PORTE->RXTX |=  (1<<5) 
//#define LCD_E2_OFF  MDR_PORTE->RXTX &= ~(1<<5)
//#define LCD_A0_ON   MDR_PORTE->RXTX |=  (1<<11) 
//#define LCD_A0_OFF  MDR_PORTE->RXTX &= ~(1<<11) 
//#define LCD_RES_ON  MDR_PORTE->RXTX |=  (1<<10) 
//#define LCD_RES_OFF MDR_PORTE->RXTX &= ~(1<<10)

#define LCD_E_ON    MDR_PORTC->RXTX |=  (1<<7) 
#define LCD_E_OFF   MDR_PORTC->RXTX &= ~(1<<7)
#define LCD_RW_ON   MDR_PORTC->RXTX |=  (1<<2) 
#define LCD_RW_OFF  MDR_PORTC->RXTX &= ~(1<<2)
//#define LCD_Wr_Data MDR_PORTA->RXTX             // LCD D0-D7

#define LCD_reset_ON	 MDR_PORTE->RXTX |=   (1<<6)  
#define LCD_reset_OFF 	 MDR_PORTE->RXTX &=  ~(1<<6)
#define LCD_A0_ON 	     MDR_PORTE->RXTX |=   (1<<7)  
#define LCD_A0_OFF 	     MDR_PORTE->RXTX &=  ~(1<<7)
#define LCD_CS_ON 	     MDR_PORTF->RXTX |=   (1<<2)  
#define LCD_CS_OFF 	     MDR_PORTF->RXTX &=  ~(1<<2)

//-----------------------End of LCD defines------------------------------------//

#define VD5_ON  		 MDR_PORTB->RXTX |=   1  
#define VD5_OFF  		 MDR_PORTB->RXTX &=   ~1  

#define VD6_ON  		 MDR_PORTB->RXTX |=   1<<3  
#define VD6_OFF  		 MDR_PORTB->RXTX &=  ~(1<<3) 

#define SW1_ON  		 MDR_PORTC->RXTX & (0<<2)  
#define SW1_OFF  		 MDR_PORTC->RXTX & (1<<2)    
#define SW3_ON  		 MDR_PORTE->RXTX & (0<<1)  
#define SW3_OFF  		 MDR_PORTE->RXTX & (1<<1)
#define SW4_ON  		 MDR_PORTE->RXTX & (0<<3)  
#define SW4_OFF  		 MDR_PORTE->RXTX & (1<<3)  



	void OSC_init(void){
//---CLK-----------------------------------------------------------------------------------------------------
  MDR_RST_CLK->PER_CLOCK = 0xFFFFFFFF;                    // вкл. тактирование всей перефирии
  MDR_RST_CLK->HS_CONTROL = 0x01;                         // вкл. HSE осцилятор
  while ((MDR_RST_CLK->CLOCK_STATUS & (1 << 2)) == 0x00); // ждем пока HSE выйдет в рабочий режим
  MDR_RST_CLK->PLL_CONTROL = ((1 << 2) | (9 << 8)); 	  // вкл. PLL | коэф. умножения = 10
  									  // 7 при кварце 10 мег
  									  // 9 при кварце 8 мег
  while((MDR_RST_CLK->CLOCK_STATUS & 0x02) != 0x02);      // ждем когда PLL выйдет в раб. режим

  MDR_RST_CLK->CPU_CLOCK  = (2                            // источник для CPU_C1
						   |(1 << 2)                      // источник для CPU_C2
						   |(1 << 4)                      // предделитель для CPU_C3
						   |(1 << 8));                    // источник для HCLK
 
  // HCLK = 80 МГц
  
  }
   
	void GPIO_init (void){  
  
  MDR_PORTA->OE      = 1 | (1<<5) | (1<<6);      // порт A1 - вход, A0,A5,A6 на выход
  MDR_PORTA->FUNC    = 0x0000;          // функция - порт 
  MDR_PORTA->ANALOG  = 0xffff;          // режим потра - цифровой
  MDR_PORTA->PWR     = 0xFFFFFFFF;      // максимально быстрый фронт ( порядка 10 нс)
  //---------------------------------------------------------------------------//
  MDR_PORTB->OE = 0xffff;               // порт B на выход, 9ый пин - вход DVALID АЦП
  MDR_PORTB->FUNC = 0x0000;             // функция - порт 
  MDR_PORTB->ANALOG  = 0xffff;          // режим потра - цифровой
  MDR_PORTB->PWR     = 0xFFFFFFFF;      // максимально быстрый фронт ( порядка 10 нс)
  //---------------------------------------------------------------------------//  
  MDR_PORTC->OE      = 0x0000;   		// LCD_A0 пин на выход
  MDR_PORTC->FUNC    = 0x0000;          // функция - порт 
  MDR_PORTC->ANALOG  = 0xffff;          // режим потра - цифровой
  MDR_PORTC->PWR     = 0xFFFFFFFF;      // максимально быстрый фронт ( порядка 10 нс)
  //---------------------------------------------------------------------------//
  MDR_PORTD->OE = 0x0000;               // порт D на вход, PD4 - LCD_reset
  MDR_PORTD->FUNC = 0x0000;             // функция - порт 
  MDR_PORTD->ANALOG  = 0xffff;          // режим потра - цифровой
  MDR_PORTD->PWR     = 0xFFFFFFFF;      // максимально быстрый фронт ( порядка 10 нс)
  //---------------------------------------------------------------------------//
  MDR_PORTE->OE = 0xffff;               // порт E на выход
  MDR_PORTE->FUNC = 0x0000;             // функция - порт 
  MDR_PORTE->ANALOG  = 0xffff;          // режим потра - цифровой
  MDR_PORTE->PWR     = 0xFFFFFFFF;      // максимально быстрый фронт ( порядка 10 нс)
  //---------------------------------------------------------------------------//
  MDR_PORTF->OE = 0xffff;               // 
  MDR_PORTF->FUNC = 0x0000; 
  MDR_PORTF->ANALOG  = 0xffff;          // режим потра - цифровой
  MDR_PORTF->PWR     = 0xFFFFFFFF;      // максимально быстрый фронт ( порядка 10 нс)
   }

   __irq void UART2_IRQHandler( void ) // функция обработки прерывания UART2
{
// прерывание возникает при поступлении 8 байт в буфер FIFO приемника UART2
// слово буфера FIFO - 12 бит, глубина - 16 слов, 0…7 биты - принятые данные  
#define RXFE 1 << 4  						   // бит RXFE равен 1 если буфер пуст
#define FIFO_has_byte  !(MDR_UART2->FR & RXFE) // проверка наличия байт в FIFO
 
  uint8_t  rd_byte_cntr = 0;    			   // счетчик прочитанных байт
  MDR_PORTB->RXTX = 0x000F;
  // очистка буфера перед чтением
  for(uint8_t i = 0; i < 16; i++) rx_data[i] = 0; 
  
  while(FIFO_has_byte)                     // читаем данные, 
  {                                        // пока есть байты в буфере FIFO
    rx_data[rd_byte_cntr] = MDR_UART2->DR; // чтение !
    rx_data[rd_byte_cntr] &= 0x00ff;       // очищаем старшие разряды
    rd_byte_cntr++;                        // инкремент счетчика байт
  }
  if(
        rx_data[0] == 'g' &
        rx_data[1] == 'e' & 
        rx_data[2] == 't' &
        rx_data[3] == '_' &
        rx_data[4] == 't' &
        rx_data[5] == 'e' &
        rx_data[6] == 'm' &
        rx_data[7] == 'p' 
     ) 
  {
  
    need2send = 1;         // запрос получен, выставлен флаг отсылки данных на ПК
  }
  else
  {
    need2send = 2;         // ошибка команды
  }
  
  
      if(need2send == 1) // запрос с ПК получен
    {
         Uart_send_num(t);
         Uart_CR_LF_send();
		// отправка т и возврата коретки и перевода строки на ПК		        
      
      need2send = 0;				// сброс флага отсылки данных на ПК
    }
    
    else if(need2send == 2) // ошибка
    {
             Uart_send_text("command error, please send 'get_temp' command");
             Uart_CR_LF_send();
             need2send = 0;
    }
  
  
  MDR_UART2->RSR_ECR = 0;   // сброс статуса заполнения FIFO                                    
  MDR_UART2->ICR = 1 << 4 | // сброс флага прерывания от приемника UARTRXINTR
                   1 << 10; // сброс флага прерывания по переполнению FIFO      
}
   
/*=========================================================================== */
	  
 	int main()
{

 OSC_init();
 SysTickTimer_Init();
 GPIO_init();
 Uart2_init();
   NVIC_EnableIRQ(UART2_IRQn);  // Разрешение прерывания для UART2
  __enable_irq();	       	   // Enable Interrupts global
 
 while(1)
  {
    t = ds18b20_rd_t();
    
    delay_ms(200);
    MDR_PORTB->RXTX = 0x0000;
    
   }	
}
