#include "MDR32Fx.h"

#define U8  uint8_t
#define S8  int8_t
#define U16 uint16_t
#define S16 int16_t 
#define U32 uint32_t
#define S32 int32_t

#define ADC_Vref             3.3		// измеренное вольтметром напряжение питания МК

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

   U16 PC_sync_flag_cnt = 0;     // счетчик для отправки на ПК сигнала связи с платой
   U8  PC_sync_flag = 0;         // флаг сигнала связи
   U32 current_ADC_channel = 0;
   U16 ADC_aver_param = 10;		// величина усренднения данных АЦП
   
   U8 ext_int_fl = 0;			// флаг внешнего прерывания
   U8 current_int_index = 0;	// переменная текущей итерации прерывания
   U8 previous_int_index = 0;	// переменная предыдущей итерации прерывания
   U8 sync_counter = 3;			// порог синхронизации
   U8 sucess_sync_rd = 0;       // счетчик успешных последовательн. считываний 
   								// сигнала синхронизации
 	
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

  MDR_RST_CLK->SSP_CLOCK = ((4 << 0)|(1 << 24)); //предделитель = 16, разрешение тактирования SSP1 

  MDR_SSP1->CPSR = 2; //делитель тактовой частоты;
  MDR_SSP1->CR0 = 1 << 6; //полярность сигнала
  MDR_SSP1->CR0 |= 1 << 7; //фаза сигнала
  MDR_SSP1->CR0 |= 0 << 8; //коэффициент скорости
  MDR_SSP1->CR0 |= 0 << 4; //формат кадра
  MDR_SSP1->CR0 |= 15; //длина слова = 16 бит
  MDR_SSP1->CR1 |= ((0 << 2)|(1 << 1)); //режим работы и включение приемопередатчика SSP

    // пины SPI1_TxD и SPI1_CLK настроены на выход в GPIO_init()
	// также включен альтернативный режим порта - задействован модуль SSP1
	// пины PF0 - PF3 используются этим модулем!
	    
   }

	void SPI1_Wr_Data (U16 data){
	  
	  // функция отправки данных на шину SSP1
	  // регистр DR - 16 бит !!!!
	  MDR_SSP1->DR = data;
	}

	U16 SPI1_Rd_Data (void){
	  
	  // функция считывния данных шины SSP1
	  // регистр DR - 16 бит !!!!
	  
	  U16 rx_buf = 0;
	  MDR_SSP1->DR = 0;				// инициировать тактовые импульсы
	  while(MDR_SSP1->SR & 1<<4) { } // ждем готовности модуля
	  
	  rx_buf = MDR_SSP1->DR;
	  
	  return rx_buf;

	}

	S16 TsensRd (void) {
	  
	  S32 TempInCelsius = 0;
	  U8 PrecisionCoef = 1;
	  S16  full_scaleCelsius = 127;
	  S16 full_scaleSensADC = 508;
	  	  
	  TempInCelsius = SPI1_Rd_Data();	  
	  TempInCelsius = TempInCelsius << 1; // избавляемся от "leading zero"
	  TempInCelsius = TempInCelsius >> 6; // приводим к 16-бит. формату
	  if (TempInCelsius > 508)
	  {
	  	full_scaleCelsius = 128;
	  	full_scaleSensADC = 512;
		TempInCelsius = TempInCelsius - 1024;
		TempInCelsius = (TempInCelsius*full_scaleCelsius*PrecisionCoef)/full_scaleSensADC;
	  }
	  else {TempInCelsius = (PrecisionCoef*(TempInCelsius*full_scaleCelsius)/full_scaleSensADC);}
	   

	  //преобразование в градусы: 508 = +127 град - полн. шкала
	  
	  
	  return TempInCelsius;
	}

/*=========================================================================== */
//UART
	void Uart_init (void){
//UART	  
	MDR_RST_CLK->PER_CLOCK |= (1UL << 6); 			//тактирование UART1
	MDR_RST_CLK->UART_CLOCK = (0 					// установка делителя для UART1
  	|(0 << 8) 									// установка делителя для UART2
  	|(1 << 24) 						// разрешение тактовой частоты UART1
  	|(0 << 25));						// разрешение тактовой частоты UART2*/ 

// 	//Параметры делителя при частоте = 10000000Гц и скорости = 115200
	MDR_UART1->IBRD = 0x5; 						// целая часть делителя скорости
	MDR_UART1->FBRD = 0x1b; 					// дробная часть делителя скорости
	
//	//Параметры делителя при частоте = 70000000Гц и скорости = 115200
//    MDR_UART1->IBRD = 0x25; //целая часть делителя скорости
//    MDR_UART1->FBRD = 0x3f; //дробная часть делителя скорости
	MDR_UART1->LCR_H = ((0 << 1) 				// разрешение проверки четности
  	|(0 << 2) 								// четность/нечетность
  	|(0 << 3) 								// стоп-бит
 	 |(0 << 5) 						// откл. буфера FIFO приемника и передатчика
 	 |(3 << 5) 								// длина слова = 8 бит
 	 |(0 << 7)); 							    // передача бита четности

	MDR_UART1->CR = ((1 << 8)|(1 << 9)|1);   // передачик и приемник разрешен, 
  										 // разрешение приемопередатчика UART1
}
	
	void Uart_send_hex(U8 hex_data){
  
	  while(MDR_UART1->FR & (1<<3)) { }; // ждем готовности UART;
	  
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

  MDR_RST_CLK->PER_CLOCK |= (1 << 17); //тактирование АЦП
  
  MDR_ADC->ADC1_CFG = (1 //Включение АЦП  
  |(0 << 2)   	// источник синхросигнала*/
  |(1 << 3)   	// Выбор способа запуска АЦП - послед. 
  |(0 << 4)  	// номер канала преобразования*/ - не важно, так как установим канал позже
  |(1 << 9)  	// переключение включено (перебираются каналы, выбранные в регистре выбора канала)
  |(0 << 10) 	// автоматический контроль уровней откл.
  |(0 << 11)  	// источник опорного - внутренний (VDD)
  |(0 << 12)  	// коэффициент деления частоты ADC_clk = HCLK = 10 МГц
  |(0 << 16)  	//  работа двух АЦП одновременн откл.
  |(0 << 17)    //  TS_EN датчик температуры и источника опорного напряжения откл
  |(0 << 18)    // TS_BUF_EN усилитель для датчика температуры и источника опорного напряжения откл.
  |(0 << 19) 	// оцифровка датчика температуры откл./
  |(0 << 20));  // оцифровка источника опорного напряжения на 1.23 В откл
  //|(6 << 24));// Подстройка опорного напряжения - выбрано напряжение 1.2 В
  
  //MDR_ADC->ADC2_CFG |= 1 << 17; // Выбор источника опорного напряжения 1.23 В от датчика температуры (точный) 
}

	void ADC_start_conv(void){
  
  	MDR_ADC->ADC1_CFG |= 1<<1;
  
}

    U32 ADC_read(void){
	  
	  // чтение АЦП, t выборки + t преобразования канала = 3.2 мкС при HCLK = 10М и предделителе АЦП = 1
	  //		     t выборки + t преобразования канала = 0.5 мкС при HCLK = 70М и предделителе АЦП = 1					
	  // вес младшего разряда АЦП = 3,3/4095 = 0,8 мВ
	  
	  U32 ADC_data = 0;
	  
  	  ADC_start_conv(); // начало преобразований данных
	  
	  while(!(MDR_ADC->ADC1_STATUS) & (1<<2)) {} // ждем готовность 
	  ADC_data = MDR_ADC->ADC1_RESULT;			 // читаем
	  
	  current_ADC_channel = ADC_data << 11;  //вытаскиваем номер 
	  current_ADC_channel = current_ADC_channel >> 27;  //канала чьи измерения
	  
	  ADC_data = ADC_data << 20;    // отбрасываем инфу о 
	  ADC_data = ADC_data >> 20;    // канале измерений
	  
	  return ADC_data;
}
					   
    void ADC_set_ch(U8 channel){
	  
	if (channel > 16) return;
	
	MDR_ADC->ADC1_CHSEL = 1 << channel; 
	
	
}

    U32 ADC_Rd_average(U16 AverValue){
	  
	  // чтение АЦП, t выборки + t преобразования канала = 3.2 мкС при HCLK = 10М и предделителе АЦП = 1
	  // t выборки + t преобразования канала = 0.5 мкС при HCLK = 70М и предделителе АЦП = 1	
	  // усреднение результатов преобразований АЦП
	  
	  U32 Aver_ADC_data = 0;
	  
	  for(int i = 0; i < AverValue; i++ )
	  {
	  		Aver_ADC_data += ADC_read();
	  }
  
	  Aver_ADC_data = Aver_ADC_data/AverValue; 
	  
	  return Aver_ADC_data;
}

	U32 Get_ADC_ch_voltage(U8 ADC_channel){
	  // чтение усредненного результата преобраз. канала АЦП, преобразование в мВ
	  
	  U32 ADC_rd_data = 0;
 	  U32 ADC_meas_voltage = 0;
	  
	  ADC_set_ch(ADC_channel);	// установка канала АЦП
	  ADC_rd_data = ADC_Rd_average(ADC_aver_param);				// читаем среднее значение отсчетов АЦП
	  ADC_meas_voltage = (int)(ADC_Vref*ADC_rd_data*1000)/4095;	// преобразуем в волты
	  
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
	//установка (выбор) мультиплексора
	    
	  switch (MxNumber){
	  	
	  case 1:	// 1ый мультиплескор - U1
				n_MX1_EN;
				break;
	  case 2:	// 2ой мультиплескор - U3
				n_MX2_EN;
				break;
	  case 3:	// 3ий мультиплескор - U5	
				n_MX3_EN;
				break;
	  case 4:	// 4ый мультиплескор - U7	
				n_MX4_EN;
				break;	
	  case 5:	// 5ый мультиплескор - U11	
				n_MX5_EN;
				break;	
	  case 6:	// 6ой мультиплескор - U2	
				n_MX6_EN;
				break;
	  case 7:	// 7ой мультиплескор - U4		
				n_MX7_EN;
				break;
	  case 8:	// 8ой мультиплескор - U6		
				n_MX8_EN;
				break;
				
	  default: break; 	
	  }
	  
	  delay_1us();
}

	void Set_MX_ch (U8 channel){
	//установка канала мультиплексора
	  
	  // отключаем все мультиплексоры перед выборов канала 
	  n_MX1_DIS; n_MX2_DIS; n_MX3_DIS; n_MX4_DIS; 
	  n_MX5_DIS; n_MX6_DIS; n_MX7_DIS; n_MX8_DIS;
	  
	  switch (channel){
	  	
	  case 0:	// 1 канал мультиплексора S2,S1,S0 = 000  
				MX_S0_OFF;
				MX_S1_OFF;
				MX_S2_OFF;
				break;
	  case 1:	// 2 канал мультиплексора S2,S1,S0 = 001 
				MX_S0_ON;
				MX_S1_OFF;
				MX_S2_OFF;
				break;
	  case 2:	// 3 канал мультиплексора S2,S1,S0 = 001 
				MX_S0_OFF;
				MX_S1_ON;
				MX_S2_OFF;
				break;
	  case 3:	// 4 канал мультиплексора S2,S1,S0 = 010  
				MX_S0_ON;
				MX_S1_ON;
				MX_S2_OFF;
				break;
	  case 4:	// 5 канал мультиплексора S2,S1,S0 = 011 
				MX_S0_OFF;
				MX_S1_OFF;
				MX_S2_ON;
				break;
	  case 5:	// 6 канал мультиплексора S2,S1,S0 = 100  
				MX_S0_ON;
				MX_S1_OFF;
				MX_S2_ON;
				break;
	  case 6:	// 7 канал мультиплексора S2,S1,S0 = 101 
				MX_S0_OFF;
				MX_S1_ON;
				MX_S2_ON;
				break;
	  case 7:	// 8 канал мультиплексора S2,S1,S0 = 110 
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
	  // нумерация каналов изменена для упрощения разводки
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
	  // 65ый - отдельный, надо выставлять новый канал АЦП
	  default: break;
	  }

	  delay_100us(); // выдерживаем 100 мкс , время установления RC фильтра
}
/*=========================================================================== */
    
	void GPIO_init (void){  
  
  MDR_PORTA->OE      = 0xffff;			// порт А на выход, сигналы выбора мультиплексора - пины А0 - А7
  MDR_PORTA->FUNC    = 0x0000;          // функция - порт 
  MDR_PORTA->ANALOG  = 0xffff;          // режим потра - цифровой
  MDR_PORTA->PWR     = 0xFFFFFFFF;      // максимально быстрый фронт ( порядка 10 нс)
//---------------------------------------------------------------------------//
  MDR_PORTB->OE 	 = 0xfdff;          // порт B на выход, выбор мультиплексара пины B1, B2, B10
  										// пин 9 - вход сигнала синхронизации
  MDR_PORTB->FUNC   = 0x00000000;       // функция - порт
  MDR_PORTB->ANALOG = 0xffff;           // режим потра - цифровой
  MDR_PORTB->PULL   = 0x00000000;       // подтяжка к "0" выключена, подтяжка к "1" выключена 
  MDR_PORTB->PD     = 0x00000000;       // триггер Шмитта выключен, гистерезис 200мВ
  MDR_PORTB->PWR    = 0xffffffff;       // максимально быстрый фронт ( порядка 10 нс)
  MDR_PORTB->GFEN   = 0x0000;           // фильтр выключен
  // uart
  	MDR_PORTB->FUNC |= ((2 << 5*2) | (2 << 6*2)); 	//режим работы порта
	MDR_PORTB->ANALOG |= ((1 << 5) | (1 << 6)); 	//цифровой
	MDR_PORTB->PWR |= ((3 << 5*2) | (3 << 6*2)); 	//максимально быcтрый
  
  //---------------------------------------------------------------------------//
  MDR_PORTD->OE =     ((0 << 3)); //направление передачи данных = Вход
  MDR_PORTD->ANALOG = ((0 << 3)); //режим работы контроллера = 
  MDR_PORTD->PULL =   ((0 << 3)); //запрещение подтяжки к GND
  MDR_PORTD->PULL =   ((0 << (3 << 16))); //запрещение подтяжки к VCC
  MDR_PORTD->PD =     ((0 << (3 << 16))); //режим работы входа = 
  MDR_PORTD->PWR =    ((1 << 3*2)); //скорость фронта вывода = 
  MDR_PORTD->GFEN =   ((0 << 3)); //входной фильтр выключен
  //---------------------------------------------------------------------------//
//  MDR_PORTE->OE = 0xffff;               // порт E на выход
//  MDR_PORTE->FUNC = 0x0000;             // функция - порт 
//  MDR_PORTE->ANALOG  = 0xffff;          // режим потра - цифровой
//  MDR_PORTE->PWR     = 0xFFFFFFFF;      // максимально быстрый фронт ( порядка 10 нс)
//  //---------------------------------------------------------------------------//
  MDR_PORTF->OE = 0xffff;               // порт D на выход, модуль SSP1 
  MDR_PORTF->FUNC = (2 << 6) |			// режим  пинов 1, 2, 3, 4 порта 
					(2 << 4) |			// - альтернативный, задействован модуль SSP1
					(2 << 2) |
					(2 << 0);

  MDR_PORTF->ANALOG  = 0xffff;          // режим потра - цифровой
  MDR_PORTF->PWR     = 0xFFFFFFFF;      // максимально быстрый фронт ( порядка 10 нс)
   }
 
	void timer1_init(void) {
	  
  MDR_RST_CLK->PER_CLOCK |= 1 << 14; //разрешение тактирования Таймера 1 
  MDR_TIMER1->CNTRL = 0x00000000;                         // Режим инициализации таймера
  MDR_TIMER1->CNT   = 0x00000000;                         // Начальное значение счетчика
  MDR_TIMER1->PSG   = 0x0;                         		 // Предделитель частоты
  MDR_TIMER1->ARR   = 0x1f3;                              // Основание счета 100 мкс
  MDR_TIMER1->IE    = 0x00000002;                         // Разрешение генерировать прерывание при CNT=ARR
  MDR_RST_CLK->TIM_CLOCK  = (0|(1 << 24));                // делитель частоты|разрешение тактирования Таймера 1
  MDR_TIMER1->STATUS= 0x00000000;                         // сбрасываем флаги 
}

 	void OSC_init(void){

  //---CLK-----------------------------------------------------------------------------------------------------

	  
  MDR_RST_CLK->PER_CLOCK = 0xFFFFFFFF;                    // вкл. тактирование всей перефирии
  MDR_RST_CLK->HS_CONTROL = 0x01; // вкл. HSE осцилятора
  while (MDR_RST_CLK->CLOCK_STATUS & (1 << 2) == 0x00); // ждем пока HSE выйдет в рабочий режим 

  MDR_RST_CLK->PLL_CONTROL = ((1 << 2) | (0 << 8)); //выкл. PLL | коэф. умножения = 0
  while((MDR_RST_CLK->CLOCK_STATUS & 0x02) != 0x02); //ждем когда PLL выйдет в раб. режим

  MDR_RST_CLK->CPU_CLOCK = (2 //источник для CPU_C1
  | (1 << 2) //источник для CPU_C2
  | (0 << 4) //предделитель для CPU_C3
  | (1 << 8));//источник для HCLK
	  
//  MDR_RST_CLK->PER_CLOCK = 0xFFFFFFFF;                    // вкл. тактирование всей перефирии	  
//  MDR_RST_CLK->HS_CONTROL = 0x01; /* вкл. HSE осцилятора */
//  while (MDR_RST_CLK->CLOCK_STATUS & (1 << 2) == 0x00); /* ждем пока HSE выйдет в рабочий режим */
//
//  MDR_RST_CLK->PLL_CONTROL = ((1 << 2) | (6 << 8)); //вкл. PLL | коэф. умножения = 7
//  while((MDR_RST_CLK->CLOCK_STATUS & 0x02) != 0x02); //ждем когда PLL выйдет в раб. режим
//
//  MDR_RST_CLK->CPU_CLOCK = (2 /*источник для CPU_C1*/
//  | (1 << 2) /*источник для CPU_C2*/
//  | (0 << 4) /*предделитель для CPU_C3*/
//  | (1 << 8));/*источник для HCLK*/
//  
//  // HCLK = 70 000 000 Гц
	  
	  
}
	
	void MCU_init (void) {
	  
 	 OSC_init();
 	 GPIO_init();  
 	 Uart_init();
  	 MDR32_SSP1_init();
  
	}

__irq void Timer1_IRQHandler(void){
  //Обработчик прерывания таймера 1
  // прерывание каждые 100 мкс
  
  // флаг синхронизации поднимается в случае превышения порога успешных
  // последовательных считываний состояния входа синхронизации
  
  PC_sync_flag_cnt++;
  
  if (PC_sync_flag_cnt >= 1000)
  {		PC_sync_flag_cnt = 0;
  		PC_sync_flag = 1;
  }
  
  // опрос входа синхронизации
  if (MDR_PORTB->RXTX & (1<<9))
  { // считан сигнал синхронизации	  
	current_int_index = previous_int_index; // сохранение предыдущего индекса прерывания
    current_int_index++;					// инкремент индекса прерывания
	  
  	if (current_int_index > previous_int_index) // инкремент индекса ?
	   	sucess_sync_rd++;    // инкремент счетчика послед. считываний, успех
  }
  else current_int_index--; // декремент индекса прерывания 
   
  if (sucess_sync_rd >= sync_counter)
  { // синхр. установалена
	
	current_int_index = 0; // сброс счетчика индекса прерываний
    sucess_sync_rd = 0;    // сброс счетчика успешных считываний синхроимпульса
	ext_int_fl = 1;        // уст. флага начала измерений АЦП 
  }
  
  MDR_TIMER1->CNT = 0x0000;			 // сбрасываем таймер	
  NVIC_ClearPendingIRQ(Timer1_IRQn); // сброс флагов .. 
  MDR_TIMER1->STATUS &= ~(1 << 1);   // .. прерывания
}


 	int main()
{

 U32 ADC_meas_voltage[65];				// буфер измерений всех каналов
 S16 PCB_temper = 0; 				
 U8 StripNum = 65;						// количество стрипов коллектора
 
 MCU_init();							// иницализация системы тактирования,
  										// модулей GPIO, SPI, UART
 ADC_init();					
 timer1_init();
 
 __enable_irq();			    // Enable Interrupts global
 NVIC_EnableIRQ(Timer1_IRQn);   // Enable Timer1 Interrupt
 MDR_TIMER1->CNTRL = 1; // включить таймер 1
 
 
 /// !!!
 /// Для нормальной работы АЦП после прошивки МК необходимо
 /// отключать программатор от USB. Если этого не делать, 
 /// в результатах преобраз. АЦП появляется смещение (шум)
 
 while(1)
  { // T чтения 65 стрипов с 10-кратным усреднением + t преобразования < 1 мс при HCLK = 70М
	// T чтения 65 стрипов с 10-кратным усреднением + t преобразования < 7 мс при HCLK = 10М
	
	// опрос флага синхронизации
	if(ext_int_fl){
	  
	  NVIC_DisableIRQ(Timer1_IRQn);   // запрещаем прерывание на время измерений
	  
	  ext_int_fl = 0; // сбрасываем флаг прерывания по синхроимпульсу
	  
	  for (U8 i = 1; i <= 65; i++){
	  //цикл измерения напряжения стрипов 1-64
	  Set_meas_strip(i);
      //стрипы 1-64 читаются через 3ий (общий) канал АЦП
	  ADC_meas_voltage[i-1] = Get_ADC_ch_voltage(3);	// чтение	  	
	}
	  //меняем канал, 65ый стрип - отдельный ОУ и отдельный канал АЦП
	ADC_meas_voltage[64] = Get_ADC_ch_voltage(7);
	 
	PCB_temper = TsensRd() ; // измеряем температуру платы
	
	for (U8 i = 0; i <= 64; i++){
	  // цикл отправки результатов на ПК
	  
	  Uart_num_send(ADC_meas_voltage[i]);		// отсылаем на ПК показания в мВ
	  Uart_send_text(";");
	   }

	Uart_num_send(PCB_temper);
	Uart_send_text("E");       // символ конца посылки
	
	// ждем немного, до следующего синхроимульса более 1 секунды
	delay_200ms();
	
	NVIC_EnableIRQ(Timer1_IRQn);   // Enable Timer1 Interrupt
    MDR_TIMER1->CNTRL = 1; 		   // включить таймер 1
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
