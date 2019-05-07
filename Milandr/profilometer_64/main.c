/// Рабочий код ,программа для микроконтроллера  
/// устройство - многоканальный профилометр пучка заряженных частиц

/// ФАЙЛ ПРОШИВКИ CPLD ЗАГРУЖАТЬ С ПОМОЩЬЮ DIGILENT ADEPT

// modbus версия 2.0

#include "MDR32Fx.h"
#define F_CPU 80000000

#define U8  uint8_t
#define U16 uint16_t 
#define S16 int16_t 
#define U32 uint32_t
#define S32 int32_t

#include "mdr_delay.h"

//========================== USER DEFINES AND VARS==============================
  
// сигналы запуска и остановки блока ресинхронизации данных в ПЛИС
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

#define RXFE 1<<4         // равен 1 если пуст буфер FIFO приемника 
#define FIFO_has_byte    !(MDR_UART1->FR & RXFE)
#define CH3_CCR_CAP_EVENT (1<<7) // Событие ?переднего? фронта на входе CAP каналов таймера 
                                 // Бит 7 – третий канал
  U8 meas_mode = 1;    // флаг режима измерений, 0 - непрерывный 1 - импульсный
  U8 meas_updated = 0; // флаг обновления данных в импульсном режиме
  U8 new_meas = 0;     // флаг чтения мастером обновленных данных в импульсном режиме

  U16 int_time = 30;   // переменная времени интегрирования, мкс
  U32 ADC1_data[16];   // буферы хранения данных АЦП 
  U32 ADC2_data[16];
  U32 ADC3_data[16];
  U32 ADC4_data[16];
  
  U16 InputConnPin [65];// пины разъема
  U16 ADCsChDataNum[64];// каналы всех трех АЦП в одном массиве
   
  U8  SYNC_RE = 0;
  
  U8 ADC_scale = 2;                     // '2' - 12 pC
  U8 ADC_scale_upd_fl = 0;              // флаг обновления шкалы АЦП
  U8 ADC_full_scale = 12;               // полная шкала АЦП, pC 
  U8 trig_timeout = 0;                  // переменная таймаута получения импульса в имп. режиме     
    
  U32 full_current = 0;                 // ток мишени
//==============================================================================  

  #include "dialtek_modbus.h"
  
  void OSC_init(void){

	#define	_HSEBYP				1		// 0 - режим осциллятора, 1 - режим внешнего генератора
	#define	_HSEON				1		// 0 - выключен, 1 - включен


//---CLK-----------------------------------------------------------------------------------------------------
  
  //MDR_RST_CLK->HS_CONTROL = 2;                            // режим внешнего генератора
  //MDR_RST_CLK->HS_CONTROL = 0x03;                         // вкл. HSE осцилятор

  MDR_RST_CLK->HS_CONTROL = (_HSEBYP<<1) + _HSEON; 
  while ((MDR_RST_CLK->CLOCK_STATUS & 0x04) != 0x04);   // ждем пока HSE выйдет в рабочий режим
  MDR_RST_CLK->PLL_CONTROL = ((1 << 2) | (1 << 8)); 	  // вкл. PLL | коэф. умножения = 2

  while((MDR_RST_CLK->CLOCK_STATUS & 0x02) != 0x02);      // ждем когда PLL выйдет в раб. режим

  MDR_RST_CLK->CPU_CLOCK  = (2                           // источник для CPU_C1 - HSE
						   |(1 << 2)                      // источник для CPU_C2 - PLLCPUo 
						   |(1 << 4)                      // предделитель для CPU_C3 - CPU_C2
						   |(1 << 8));                    // источник для HCLK
  MDR_RST_CLK->PER_CLOCK = 0xFFFFFFFF;                    // вкл. тактирование всей перефирии
  // HCLK = 80 МГц
  MDR_RST_CLK->TIM_CLOCK = 0x00000000;
  }
   
  void GPIO_init (void){  
  
  MDR_PORTA->OE      = 0xFF95; // PA6 - dvalid4 PA5 - dvalid3, PA3 - DVALID2, PA1 - DVALID1, PA0 - MCU_CONV
  MDR_PORTA->FUNC    = 0x0000; //0x0800; // функция - порт, для РА5 альтернативная функция 
  MDR_PORTA->ANALOG  = 0xFFFF;          // режим потра - цифровой
  MDR_PORTA->PWR     = 0xFFFFFFFF;      // максимально быстрый фронт ( порядка 10 нс)
  //---------------------------------------------------------------------------//
  MDR_PORTB->OE = 0xFFFE;               // порт B на выход, PB0 - вход внешней синхронизации
  MDR_PORTB->FUNC = 0x0002;             // функция - порт, PB0 - альтернативная функция
  MDR_PORTB->ANALOG  = 0xffff;          // режим потра - цифровой
  MDR_PORTB->PWR     = 0xFFFFFFFF;      // максимально быстрый фронт ( порядка 10 нс)
  //---------------------------------------------------------------------------//  
  MDR_PORTC->OE     = 0xffff;                    
  MDR_PORTC->FUNC   = 0x0000;                
  MDR_PORTC->ANALOG = 0xffff;
  MDR_PORTC->PWR     = 0xFFFFFFFF;      // максимально быстрый фронт ( порядка 10 нс)     
  //---------------------------------------------------------------------------//
  MDR_PORTD->OE = 0x0028;               // порт D на вход, PD2 - MCU_ADC_IN, PD5 - S1, PD3 - S2
  MDR_PORTD->FUNC = 0x0000;             // функция - порт 
  MDR_PORTD->ANALOG  = 0xffff;          // режим потра - цифровой, но PD2 - MCU_ADC_IN
  MDR_PORTD->PWR     = 0xFFFFFFFF;      // максимально быстрый фронт ( порядка 10 нс)
  MDR_PORTD->PD =     ((0 << (2 << 16))); //режим работы входа 2 = АЦП
  //---------------------------------------------------------------------------//
  MDR_PORTE->OE = 0xffff;               // порт E на выход
  MDR_PORTE->FUNC = 0x0000;             // функция - порт 
  MDR_PORTE->ANALOG  = 0xffff;          // режим потра - цифровой
  MDR_PORTE->PWR     = 0xFFFFFFFF;      // максимально быстрый фронт ( порядка 10 нс)
  //---------------------------------------------------------------------------//
  MDR_PORTF->OE = 0xffb7;               // порт F на выход,PF3 - RxD
  MDR_PORTF->FUNC = (2 << 6) |		    // режим  пинов 1, 2, 3, 4 порта 
					(2 << 4) |			// - альтернативный, задействован модуль SSP1
					(2 << 2) |
					(2 << 0);
  MDR_PORTF->ANALOG  = 0xffff;          // режим потра - цифровой
  MDR_PORTF->PWR     = 0xFFFFFFFF;      // максимально быстрый фронт ( порядка 10 нс)

   }

  void timer3_init(void) {
          
  // настройка таймера для режима захвата переднего фронта _/
  // + настройка прерывани каждые ~ 300 мкс, подача холостых импульсов CONV на АЦП 
          
  MDR_TIMER3->CNTRL = 4<<8;                               // источник событий - событие на 1 канале «Режим 1» 
  MDR_TIMER3->CH1_CNTRL = (1<<15) | (1<<4);               // канал работает в режиме Захват | отрицательный фронт
  MDR_TIMER3->CH1_CNTRL2 = (1<<2)|(1<<1);	          // спад по CCR11;отрицательный фронт по Chi;
  MDR_TIMER3->CNT   = 0;                                  // Начальное значение счетчика - 0
  MDR_TIMER3->PSG   = 49;                         	  // Предделитель частоты тактирования Т3 - 1
  MDR_TIMER3->ARR   = 399;                                // Основание счета, таймер тикает до
  MDR_TIMER3->IE    = (1<<5); //|(1<<1);//|(1<<13);          // разрешения прерывания по переднему и заднему фронту третьего канала, по переполнения таймера
  MDR_RST_CLK->TIM_CLOCK  |= (0|(1 << 26));               // делитель частоты|разрешение тактирования Таймера 3
  MDR_TIMER3->STATUS= 0;                                  // сбрасываем флаги
  
 }       
 
/*=========================================================================== */
// SPI
  void MDR32_SSP1_init (U8 data_lenght){
	  
	MDR_RST_CLK->PER_CLOCK |= 1 << 8;       // Разрешения тактирования периферийного блока SPI 1 (SSP1)
	MDR_RST_CLK->SSP_CLOCK = (1 << 24) | 0; // Разрешение тактовой частоты на SSP 1
                                                // Делитель тактовой частоты SSP1, SSP1_CLK = HCLK (40 МГц)
    
	MDR_SSP1->CR0 = (0 << 8) | 	        // Задает параметр SCR формулы F_SSP1 = SSP1_CLK / (CPSDVR*(1  + SCR)) 
  			(1 << 7) |		// Фаза  сигнала  SSPCLKOUT, инверсная фаза клока стробирование по переднему фронту
    			(0 << 6) |
			(0 << 5) |		// Полярность  сигнала  SSPCLKOUT, 
   			(0 << 4) |		// Формат информационного кадра -  протокол SPI фирмы Motorola
   			15;			// Размер слова данных - 0111 – 16 бит
   
	MDR_SSP1->CPSR = 4; 			// Коэффициент  деления  тактовой  частоы CPSDVR
						// Таким образом, при CPSDVR = 2, SCR = 0, F_SSP1 = 80 МГц
						// частота SSP1_CLK получается равной 40 МГц
	
	MDR_SSP1->CR1 = (0 << 2) |		// Выбор ведущего или ведомого режима работы: 0 – ведущий модуль 
			(1 << 1); 	        // Разрешение работы приемопередатчика
	}

  void SPI1_Wr_Data (U16 data){
	  
	  // функция отправки данных на шину SSP1
	  // регистр DR - 16 бит !!!!
	  MDR_SSP1->DR = data;
	}

  U16 SPI1_Rd_Data (void){
	  
          
          #define SSP_SR_RNE ((uint32_t)0x00000004) // бит заполнения FIFO SSP
          
	  // функция считывния данных шины SSP1
	  // регистр DR - 16 бит !!!!
	  
	  S16 rx_buf = 0;
	  MDR_SSP1->DR = 0;	         // инициировать тактовые импульсы
	  while((MDR_SSP1->SR & 1<<4)) { } // ждем готовности модуля
          while((MDR_SSP1->SR & SSP_SR_RNE) != 0) rx_buf = MDR_SSP1->DR; // читаем все что в буфере
	    
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
    
      // обновление шкалы АЦП
    
      ADC1_RST_OFF; // сброс всех АЦП
      ADC2_RST_OFF; 
      ADC3_RST_OFF; 
      ADC4_RST_OFF;
      delay_ms(1);
      ADC_init(ADC_scale);
      
    }    
    
  void ADC_read_all(void) {
        // в режиме послед. чтения каналов
        // выдвигается сначала последний вход АЦП, потом предпоследний и тд   
      
        //-- чтение данных АЦП 4
        for (U8 i = 0; i < 16; i++)
          ADC4_data[i] = SPI1_Rd_Data();
        //-- чтение данных АЦП 3
        for (U8 i = 0; i < 16; i++)
          ADC3_data[i] = SPI1_Rd_Data();
        //-- чтение данных АЦП 2
        for (U8 i = 0; i < 16; i++) 
          ADC2_data[i] = SPI1_Rd_Data();
        //-- чтение данных АЦП 1
        for (U8 i = 0; i < 16; i++) 
          ADC1_data[i] = SPI1_Rd_Data();

    }
    
  void convert_to_charge(void) {
      
       for (U8 i = 0; i < 16; i++) 
        {     
          /// расчет pC из отчетов АЦП, для получения pC надо делить на 10 на ПК 
          
          // АЦП 4
          ADC4_data[i] = ADC4_data[i] >> 4;       
          //ADC2_data[i] = (U32)(((ADC2_data[i] * ADC_full_scale*10)/4096.0));

          // АЦП 3
          //ADC3_data[i] = ADC3_data[i] & 0xfff0;   // избавляемся от последних 4 бит, тк 12 бит. режим
          ADC3_data[i] = ADC3_data[i] >> 4;        // приводим к 12 бит. варианту
          //ADC3_data[i] = (U32)(((ADC3_data[i] * ADC_full_scale*10)/4096.0)); 
          
          // АЦП 2
          //ADC2_data[i] = ADC2_data[i] & 0xfff0;   
          ADC2_data[i] = ADC2_data[i] >> 4;       
          //ADC2_data[i] = (U32)(((ADC2_data[i] * ADC_full_scale*10)/4096.0));
          
          // АЦП 1
          //ADC1_data[i] = ADC1_data[i] & 0xfff0;  
          ADC1_data[i] = ADC1_data[i] >> 4;       
          //ADC1_data[i] = (U32)(((ADC1_data[i] * ADC_full_scale*10)/4096.0)); 
          
        }
    
    }
     
  void ADC_ch_swap(void) {
      // заполнение массива всех трех АЦП 
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
      
      // connector <== ADCs channels, приведение каналов АЦП к пинам разъема
     
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
        
        // этот дрызг необходим для вывода АЦП из сна и подготовке к новым изм.
        MDR_PORTC->RXTX = ~ MDR_PORTC->RXTX;  
        delay_us(10); 
        MDR_PORTC->RXTX = ~ MDR_PORTC->RXTX;  
        delay_us(10); 
        
        // начало интегрирования
        MDR_PORTC->RXTX = ~ MDR_PORTC->RXTX;    
        
        delay_us(int_time);                 // интегрирование в течении уст. t
        
        MDR_PORTC->RXTX = ~ MDR_PORTC->RXTX;// конец интегрирования IVC     
    }
    
    
/*=========================================================================== */
// UART
  void Uart_init (void){
  MDR_RST_CLK->PER_CLOCK |= (1UL << 22); //тактирование порта B
  MDR_PORTB->FUNC |= ((2 << 5*2) | (2 << 6*2)); //режим работы порта
  MDR_PORTB->ANALOG |= ((1 << 5) | (1 << 6)); //цифровой
  MDR_PORTB->PWR |= ((3 << 5*2) | (3 << 6*2)); //максимально быcтрый

  MDR_RST_CLK->PER_CLOCK |= (1UL << 6); //тактирование UART1
  MDR_RST_CLK->UART_CLOCK = (4 /*установка делителя для UART1 = */
  |(0 << 8) /*установка делителя для UART2 = undefined*/
  |(1 << 24) /*разрешение тактовой частоты UART1*/
  |(0 << 25)); /*разрешение тактовой частоты UART2*/ 
  
//Параметры делителя при частоте = 80 MHz и скорости = 921 600 бит/с
MDR_UART1->IBRD = 0x2; 				// целая часть делителя скорости
MDR_UART1->FBRD = 0x2e; 				// дробная часть делителя скорости
MDR_UART1->LCR_H = ((0 << 1) 				// разрешение проверки четности
  |(0 << 2) 						// четность/нечетность
  |(0 << 3) 						// стоп-бит
  |(0 << 4) 						// выкл. буфера FIFO приемника и передатчика 12 бит, глубину 16 слов
  |(3 << 5) 						// длина слова = 8 бит
  |(0 << 7)); 						// передача бита четности

MDR_UART1->IMSC = 1 << 4;                // RXIM разрешение прерывания от приемника UARTRXINTR. 1 – установлена;   
//MDR_UART1->IMSC = (1 << 10) | (1<<4 ); // Маскированное  состояние  прерывания  по  переполнению  буфера UARTOEINTR 
//MDR_UART1->IFLS = 1<<4;                // разрешение прерывание по залолн. 1/2 буфера фифо

MDR_UART1->CR = ((1 << 8)|(1 << 9)|1);   // передачик и приемник разрешен, 

}
	
  void uart_send_hex(unsigned char hex_data){
	  
      // пока Буфер   FIFO   передатчика   заполнен...  
   while(MDR_UART1->FR & (1<<5)) { }; // ждем готовности UART1;

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
//функция обработки прерывания irq Timer 3 - СТРОБЫ ВНЕШНЕЙ СИНХРОНИЗАЦИИ
{   

    U32 int_flag = MDR_TIMER3->STATUS; // сохр. флаги источников прерываний от Т3 
     
    if(int_flag & (1<<5))   //  ___/ флаг прерывания по переднему фронту ОШИБКА !!! ЭТО ЗАДНИЙ ФРОНТ
    {   
        
        MDR_TIMER3->CNTRL &= ~ 1;           // стоп Т3 --
        
        MDR_UART1->IMSC = 0 << 4;           // запрет прерывания от приемника UART RX
        perform_integrate();      
        MDR_UART1->IMSC = 1 << 4;           // разрешение прерывания от приемника UART RX      
        
        meas_updated = 1; 
     } 
    
  MDR_TIMER3->CNT = 0;                // установка знач. счетчика на 0   
  MDR_TIMER3->STATUS = 0x0000;        // сброс статуса прерывания
  
}

__irq void UART1_IRQHandler( void )
 //функция обработки прерывания irq UART1
{
  /// прерывание возникает при поступлении 1 байта на UART1
       
        modbus_uart_byte((unsigned char)MDR_UART1->DR); 
      
        MDR_UART1->ICR  = 1<<4; // сброс прерывания от приемника  
}
/*=========================================================================== */
  void MCU_init (void) {  
      OSC_init();
      SysTickTimer_Init();
      GPIO_init();  
      Uart_init();
      MDR32_SSP1_init(16); 	// модулей GPIO, SPI, UART 
      timer3_init();            // для работы в импульсном режиме - захват переднего фронта
  }
       
 int main()
{
 U16 cnt = 0;   // счетчик длительности вкл. статусного светодиода
 
 MCU_init();	// иницализация систем тактирования, портов, SPI и UART
 modbus_init(); // инициализация MODBUS
 
 ADC_init(ADC_scale);
                 
 NVIC_EnableIRQ(Timer3_IRQn); // Разрешение прерывания для T3 - Вход внешней синхр.
 NVIC_EnableIRQ(UART1_IRQn);  // Разрешение прерывания для UART1
 __enable_irq();	      // Enable Interrupts global
 MDR_TIMER3->CNTRL |= 1;      // Запуск Т3 --
 
 while(1)
{   
  
  modbus_rx_sm(); // анализ команды мастера
  modbus_poll();  // работа с модбас регистрами, формирование и отсылка ответа на запросы
  
  // гасим статусный светодиод для индикации активности RS485 для текущего устройства 
  if(meas_mode == 0) // если режим непрерывных измерений
  {
    if(answer != 0) 
    {
      SYNC_LED_ON;  
      cnt = 0;
    }
  }   
    
  switch(meas_mode)      // режимы измерений
  {
    case 0:
    /// режим непрерывных измерений  
        perform_integrate();                // выполнение интегрирования 
        ADC_read_all();                     // чтение всех трех АЦП
        convert_to_charge();                // преобразование отсчетов в заряды
        ADC_ch_swap();                      // приведение каналов АЦП к пинам разъема    
    break;
  //----- 
    case 1:
    /// импульсный режим 
    if(meas_updated) // анализ флага обновления данных
     { 
        meas_updated = 0;
        cnt =0;
        SYNC_LED_ON;  
        // сигнал проинтегрирован
        delay_us(10);                       // ждем готовность данных, ~ 6 мкс    
        ADC_read_all();                     // чтение всех трех АЦП
        convert_to_charge();                // преобразование отсчетов в заряды
        ADC_ch_swap();                      // приведение каналов АЦП к пинам разъема
                
       MDR_TIMER3->CNTRL |= 1;            // запуск Т3 --          
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
	запись и чтение конфигурационно регистра
    	//запись и чтение конфигурационно регистра
	CPLD_CE_ON;
	SPI1_Wr_Data(0xcc00);    //normal mode
	delay_us(3);
	CPLD_CE_OFF;
	delay_us(20);
        SPI1_Rd_Data();
        delay_ms(1);
*/