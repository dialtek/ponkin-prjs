/// Рабочий код ,программа для микроконтроллера  
/// устройство - многоканальный профилометр пучка заряженных частиц

/// ФАЙЛ ПРОШИВКИ CPLD ЗАГРУЖАТЬ С ПОМОЩЬЮ DIGILENT ADEPT

// modbus версия

#include "MDR32Fx.h"
#define F_CPU 80000000

#define U8  uint8_t
#define U16 uint16_t 
#define S16 int16_t 
#define U32 uint32_t
#define S32 int32_t

#include "mdr_delay.h"

//================================ state-machine ===============================
#define detect_dev_id      10      // код 0 состояния кон.автомата
#define get_cmd_header     11      // код 1 состояния кон.автомата
#define get_modbus_word_msb   12   // код 2 состояния кон.автомата
#define get_modbus_word_lsb   13   // код 3 состояния кон.автомата
#define get_reg_cnt_msb    14      // код 4 состояния кон.автомата
#define get_reg_cnt_lsb    15      // код 5 состояния кон.автомата
#define calc_crc1          16      // код 6 состояния кон.автомата
#define calc_crc2          17      // код 7 состояния кон.автомата
#define get_modbus_word    18      // код 8 состояния кон.автомата


U8 wr_ptr = 0, rd_ptr = 0;   // счетчики чтения и записи в массив UART
// буфер для сохр. принятных команд
U8 rx_buf[32] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}; 
//==============================================================================

//============================== RS485 defines =================================
#define RS485_RX_EN     MDR_PORTB->RXTX &= ~(1<<10)  // вкл.  приемник RS485   \_ 
#define RS485_RX_DIS    MDR_PORTB->RXTX |=  (1<<10)  // выкл. приемник RS485   _/
#define RS485_TX_EN     MDR_PORTB->RXTX |=  (1<<9)   // вкл.  передатчик RS485 _/
#define RS485_TX_DIS    MDR_PORTB->RXTX &= ~(1<<9)  // выкл. передатчик RS485 \_

#define modbus_rhr_cmd  0x03    // read holding registers cmd id
#define modbus_wsr_cmd  0x06    // write single register cmd id

#define com_dev_id      0       // В широковещательном режиме используется адрес 0
#define dev_id 80               // modbus id текущего устройства                        <<<<<<<<<<=========================== ID
#define firmware_ver    10      // версия прошивки текущего устройства
#define device_family   5       // код семейства устройств: 5 - профилометры
#define max_regs_cnt    125     // макс. кол-во регистров для чтения за 1 раз

U8 reg_addr_flag = 0;
U8 reg_wr_flag = 0;
U8 reg_qty_flag = 0;
U8 get_crc_flag = 0;

U8 rx_byte;       // байт принятый с ПК
 
U8 answer = 0;    // тип ответа на команду с ПК
U8 rd_state = detect_dev_id; // машина состояний по умолчанию ждет обращения по id устройста modbus
U16 modbus_reg_addr = 0;    // адрес регистра для R/W по запросу от modbus мастера
U16 temp_buf = 0;           // временный буфер
 
U16 regs2read = 0;          // число регистров для чтения по команде modbus rhr
U8  crc_buf[250];           // буфер для хранения байтов для расчета CRC16
U16 CRC16 = 0;              // для хранения рассчитаной контрольной суммы
U16 addr_buf_1, addr_buf_2;

U16 reg_wr_data = 0;
U16  holding_register[125];  // буфер для хранения переменных чтения, макс. число регистров - 124
//==============================================================================

// сигналы запуска и остановки блока ресинхронизации данных в ПЛИС
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

 /* OpAmpK - отрицательный коэфф. ослабл. сигнала интегратора  
 для попадания в динамич. диапазон АЦП МК 
 OpAmpK = -R2/R1 = 1100R/5100R = 0.2155, 1/0.2155 = 4.64 ! 
№2 - 1099/5080 R = 4,66
*/
#define OpAmpK   464 

#define ADC_CONV_UP  	 MDR_PORTC->RXTX = 0xffff //MDR_PORTE->RXTX |=  (1<<6);
#define ADC_CONV_DOWN  	 MDR_PORTC->RXTX = 0x0000 //MDR_PORTE->RXTX &= ~(1<<6); 

#define RXFE 1<<4         // равен 1 если пуст буфер FIFO приемника 
#define FIFO_has_byte    !(MDR_UART1->FR & RXFE)
#define CH3_CCR_CAP_EVENT (1<<7) // Событие ?переднего? фронта на входе CAP каналов таймера 
                                 // Бит 7 – третий канал
#define ADC_Vref 3.3		 // измеренное вольтметром напряжение питания МК

  U8 meas_mode = 0;    // флаг режима измерений, 0 - непрерывный 1 - импульсный
  U8 meas_updated = 0; // флаг обновления данных в импульсном режиме
  U8 new_meas = 0; // флаг чтения мастером обновленных данных в импульсном режиме

  U16 int_time = 300;     // переменная времени интегрирования, мкс
  U32 ADC1_data[16];      // буферы хранения данных АЦП 
  U32 ADC2_data[16];
  U32 ADC3_data[16];
  
  U16 InputConnPin [48];// пины разъема
  U16 ADCsChDataNum[48];// каналы всех трех АЦП в одном массиве
   
  U32 MCU_current_ADC_channel = 0;
  U16 MCU_ADC_aver_param = 20;		// величина усренднения данных АЦП
  U8  SYNC_RE = 0;
  
  U8 ADC_scale = 2;                     // '2' - 12 pC
  U8 ADC_scale_upd_fl = 0;              // флаг обновления шкалы АЦП
  U8 ADC_full_scale = 12;               // полная шкала АЦП, pC 
  U8 trig_timeout = 0;                  // переменная таймаута получения импульса в имп. режиме     
    
  U32 full_current = 0;                 // ток мишени
  U32 ADC_noise = 0;                    // смещение АЦП МК в режиме холостого хода
  U32 ADC_code = 0;                    
  
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
  
  MDR_PORTA->OE      = 0xFFD5; // PA5 - dvalid3, PA3 - DVALID2, PA1 - DVALID1, PA0 - MCU_CONV
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
 
/*=========================================================================== */
// ADC MCU
    void MCU_ADC_init(){

  MDR_RST_CLK->PER_CLOCK |= (1 << 17); //тактирование АЦП
  
  MDR_ADC->ADC1_CFG = (0 //Включение АЦП  
  |(0 << 1)     // stop conv
  |(0 << 2)   	// источник синхросигнала*/
  |(1 << 3)   	// Выбор способа запуска АЦП - послед. 
  |(0 << 4)  	// номер канала преобразования*/ - не важно, так как установим канал позже
  |(0 << 9)  	// переключение выключено
  |(0 << 10) 	// автоматический контроль уровней откл.
  |(0 << 11)  	// источник опорного - внутренний (VDD)
  |(3 << 12)  	// коэффициент деления частоты ADC_clk = HCLK/8 = 10 М
  |(0 << 16)  	//  работа двух АЦП одновременн откл.
  |(0 << 17)    //  TS_EN датчик температуры и источника опорного напряжения откл
  |(0 << 18)    // TS_BUF_EN усилитель для датчика температуры и источника опорного напряжения откл.
  |(0 << 19) 	// оцифровка датчика температуры откл./
  |(0 << 20));  // оцифровка источника опорного напряжения на 1.23 В откл
  
  //MDR_ADC->ADC2_CFG |= 1 << 17; // Выбор источника опорного напряжения 1.23 В от датчика температуры (точный) 
}

    void MCU_ADC_start_conv(void){
  
  	MDR_ADC->ADC1_CFG |= 1<<1;
        MDR_ADC->ADC1_CFG |= 1;
  
}

    U32 MCU_ADC_read(void){
	  
	  // чтение АЦП, t выборки + t преобразования канала = 3.2 мкС при HCLK = 10М и предделителе АЦП = 1
	  //		     t выборки + t преобразования канала = 0.5 мкС при HCLK = 70М и предделителе АЦП = 1					
	  // вес младшего разряда АЦП = 3,3/4095 = 0,8 мВ
	  
	  U32 ADC_data = 0;
	  
  	  MCU_ADC_start_conv(); // начало преобразований данных
	  
	  //while(!(MDR_ADC->ADC1_STATUS) & 0x04) {}//(1<<2)) {} // ждем готовность, но не работает
          delay_us(10);
	  ADC_data = MDR_ADC->ADC1_RESULT & 0x0FFF; // читаем
	  
	  return ADC_data;
}
					   
    void MCU_ADC_set_ch(U8 channel){
	  
	if (channel > 15) return;
	
	MDR_ADC->ADC1_CFG  |= channel << 4; 
        delay_us(20);			
}

    U32 MCU_ADC_Rd_average(U16 AverValue){
	  
	  // чтение АЦП, t выборки + t преобразования канала = 3.2 мкС при HCLK = 10М и предделителе АЦП = 1
	  // t выборки + t преобразования канала = 0.5 мкС при HCLK = 70М и предделителе АЦП = 1	
	  // усреднение результатов преобразований АЦП
	  
	  U32 Aver_ADC_data = 0;
	  
	  for(int i = 0; i < AverValue; i++ )
	  {
	   Aver_ADC_data += MCU_ADC_read();
	  }
  
	  Aver_ADC_data = Aver_ADC_data/AverValue; 
	  
	  return Aver_ADC_data;
}

    U32 Get_ADC_ch_voltage(U8 ADC_channel){
	  // чтение усредненного результата преобраз. канала АЦП, преобразование в мВ
	  
	  U32 ADC_rd_data = 0;
 	  U32 ADC_meas_voltage = 0;
	  
	  MCU_ADC_set_ch(ADC_channel);	// установка канала АЦП
	  ADC_rd_data = MCU_ADC_Rd_average(MCU_ADC_aver_param);		// читаем среднее значение отсчетов АЦП
	  ADC_meas_voltage = (U32)((ADC_Vref*ADC_rd_data*1000)/4096);	// преобразуем в волты  
	  return ADC_meas_voltage; 
}   
/*=========================================================================== */
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
       
    void ADC_change_scale(void) {
    
      // обновление шкалы АЦП
      ADC1_RST_OFF; ADC2_RST_OFF; ADC3_RST_OFF; // сброс всех АЦП
      delay_ms(1);
      ADC_init(ADC_scale);
      
    }    
    
    void ADC_read_all(void) {
        // в режиме послед. чтения каналов
        // выдвигается сначала последний вход АЦП, потом предпоследний и тд   
      
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
          
          // АЦП 3
          //ADC3_data[i] = ADC3_data[i] & 0xfff0;   // избавляемся от последних 4 бит, тк 12 бит. режим
          ADC3_data[i] = ADC3_data[i] >> 4;       // приводим к 12 бит. варианту
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
      
      // connector <== ADCs channels, приведение каналов АЦП к пинам разъема
      
      InputConnPin[1] = ADCsChDataNum[6];   // Вход 7 АЦП
      InputConnPin[2] = ADCsChDataNum[12];  // Вход 13 АЦП
      InputConnPin[3] = ADCsChDataNum[4];   // Вход 5 АЦП
      InputConnPin[4] = ADCsChDataNum[5];   // Вход 6 АЦП
      InputConnPin[5] = ADCsChDataNum[14];  // Вход 15 АЦП
      InputConnPin[6] = ADCsChDataNum[15];  // Вход 16 АЦП
      InputConnPin[7] = ADCsChDataNum[23];  // Вход 24 АЦП
      InputConnPin[8] = ADCsChDataNum[26];  // Вход 27 АЦП
      InputConnPin[9] = ADCsChDataNum[19];  // Вход 20 АЦП
      InputConnPin[10] = ADCsChDataNum[20]; // Вход 21 АЦП
      InputConnPin[11] = ADCsChDataNum[43]; // Вход 43 АЦП
      InputConnPin[12] = ADCsChDataNum[40]; // Вход 40 АЦП
      InputConnPin[13] = ADCsChDataNum[42]; // Вход 42 АЦП
      InputConnPin[14] = ADCsChDataNum[38]; // Вход 35 АЦП
      InputConnPin[15] = ADCsChDataNum[46]; // Вход 47 АЦП

      InputConnPin[16] = ADCsChDataNum[2];  // Вход 3 АЦП
      InputConnPin[17] = ADCsChDataNum[8];  // Вход 9 АЦП
      InputConnPin[18] = ADCsChDataNum[11]; // Вход 12 АЦП
      InputConnPin[19] = ADCsChDataNum[10]; // Вход 11 АЦП
      InputConnPin[20] = ADCsChDataNum[7];  // Вход 8 АЦП
      InputConnPin[21] = ADCsChDataNum[13]; // Вход 14 АЦП
      InputConnPin[22] = ADCsChDataNum[31]; // Вход 32 АЦП
      InputConnPin[23] = ADCsChDataNum[21]; // Вход 22 АЦП
      InputConnPin[24] = ADCsChDataNum[25]; // Вход 26 АЦП
      InputConnPin[25] = ADCsChDataNum[29]; // Вход 30 АЦП
      InputConnPin[26] = ADCsChDataNum[30]; // Вход 31 АЦП
      InputConnPin[27] = ADCsChDataNum[37]; // Вход 34 АЦП
      InputConnPin[28] = ADCsChDataNum[39]; // Вход 41 АЦП
      InputConnPin[29] = ADCsChDataNum[36]; // Вход 37 АЦП
      InputConnPin[30] = ADCsChDataNum[47]; // Вход 47 АЦП

      InputConnPin[31] = ADCsChDataNum[0];  // Вход 1 АЦП
      InputConnPin[32] = ADCsChDataNum[3];  // Вход 4 АЦП
      InputConnPin[33] = ADCsChDataNum[9];  // Вход 10 АЦП
      InputConnPin[34] = ADCsChDataNum[1];  // Вход 2 АЦП
      InputConnPin[35] = ADCsChDataNum[16]; // Вход 17 АЦП
      InputConnPin[36] = ADCsChDataNum[18]; // Вход 19 АЦП
      InputConnPin[37] = ADCsChDataNum[24]; // Вход 25 АЦП
      InputConnPin[38] = ADCsChDataNum[27]; // Вход 28 АЦП
      InputConnPin[39] = ADCsChDataNum[28]; // Вход 29 АЦП
      InputConnPin[40] = ADCsChDataNum[17]; // Вход 18 АЦП
      InputConnPin[41] = ADCsChDataNum[22]; // Вход 23 АЦП
      InputConnPin[42] = ADCsChDataNum[44]; // Вход 44 АЦП    
      
    }
    
    void perform_integrate(void) {
        
        // этот дрызг необходим для вывода АЦП из сна и подготовке к новым изм.
        MDR_PORTC->RXTX = ~ MDR_PORTC->RXTX;  
        delay_us(10); 
        MDR_PORTC->RXTX = ~ MDR_PORTC->RXTX;  
        delay_us(10); 
        
        
        IVC_SET;                            // холостой ход IVC  
        IVC_START_INT;                      // начало интегрирования
        MDR_PORTC->RXTX = ~ MDR_PORTC->RXTX;    
        
        delay_us(int_time);                 // интегрирование в течении уст. t
        
        MDR_PORTC->RXTX = ~ MDR_PORTC->RXTX;// конец интегрирования IVC
        IVC_STOP_INT;      
    }
    
    void cacl_beam_Q(void) {   
      // расчет заряда мишени
        IVC_SET;                            // конец сброса интегратора
        delay_us(10);                       // необх. задержка  
        MCU_ADC_set_ch(2);                  // установка канала АЦП 
        // чтение отсчетов АЦП 
        ADC_code  = (S32)MCU_ADC_Rd_average(MCU_ADC_aver_param); 
        // преобразование в волты - смещение интегратора
        
        // преобразование в волты - чтение данных IVC
        full_current     = (U32)(ADC_code*0.8056640625);//ADC_Vref*1000.0)/4096.0);
        IVC_RESET;                            // сброс интегратора
        full_current -= ADC_noise;            // убираем смещение интегратора
        full_current *= OpAmpK;               // приводим к динамич. диапазону АЦП МК, см. define
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
  
    //Параметры делителя при частоте = 5000000Гц и скорости = 115200
MDR_UART1->IBRD = 0x2; 					// целая часть делителя скорости
MDR_UART1->FBRD = 0x2e; 				// дробная часть делителя скорости
MDR_UART1->LCR_H = ((0 << 1) 				// разрешение проверки четности
  |(0 << 2) 						// четность/нечетность
  |(0 << 3) 						// стоп-бит
  |(0 << 4) 						// выкл. буфера FIFO приемника и передатчика 12 бит, глубину 16 слов
  |(3 << 5) 						// длина слова = 8 бит
  |(0 << 7)); 						// передача бита четности

MDR_UART1->IMSC = 1 << 4;                // RXIM разрешение прерывания от приемника UARTRXINTR. 1 – установлена;   
//MDR_UART1->IMSC = (1 << 10) | (1<<4 );     // Маскированное  состояние  прерывания  по  переполнению  буфера UARTOEINTR 
//MDR_UART1->IFLS = 1<<4;                    // разрешение прерывание по залолн. 1/2 буфера фифо

MDR_UART1->CR = ((1 << 8)|(1 << 9)|1);     // передачик и приемник разрешен, 

}
	
    void Uart_send_hex(U8 hex_data){
	  
      // пока Буфер   FIFO   передатчика   заполнен...  
	while(MDR_UART1->FR & (1<<5)) { }; // ждем готовности UART1;

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

/*========================================================================== */
// MODBUS
  char get_rx_ch (void){                                                     
// Get RX char
char rch;

   if (rd_ptr < wr_ptr) // буфер не пуст
   {
      rd_ptr++;                    // инкремент счетчика считаных байт
      rch = rx_buf[rd_ptr & 0x0f]; // сохр. элемента по индексу
   }
   else rch = 'x';   
   
   // запрет прерываний по UART на время сравнение указателей  
   // на счит. и запис. элементы массива
   NVIC_DisableIRQ(UART1_IRQn);    
           
   if ((wr_ptr==rd_ptr) && (wr_ptr > 15)) // если буфер заполнен                                            
   {  
      wr_ptr=0;                                                                   
      rd_ptr=0;                                                       
   } 

   NVIC_EnableIRQ(UART1_IRQn);         // разрешение прерываний

return rch;
}

  U8 is_reg (U16 reg_addr)
  {  
   // был ли прочитан этот регистр
   U8 rd_status = 0;
      for(unsigned int t = addr_buf_1; t <= regs2read; t++)
      { 
        if (t == reg_addr) 
	{
	  rd_status = 1;  
	  break;
	}
      }
      if ( reg_addr == (1000 + reg_addr) ) rd_status = 1; 
      return rd_status;
  }
  
  U16 modbus_CRC16(U8 buf[], int len) {
    //-------crc16
  U16 crc = 0xFFFF;
  //U8 crc_lsb, crc_msb;
  for (int pos = 0; pos < len; pos++)
  {
    crc ^= (U16)buf[pos];          // XOR byte into least sig. byte of crc
    for (int i = 8; i != 0; i--)
    {    // Loop over each bit
      if ((crc & 0x0001) != 0)
       {      // If the LSB is set
         crc >>= 1;                // Shift right and XOR 0xA001
         crc ^= 0xA001;
       }
       else                          // Else LSB is not set
         crc >>= 1;                  // Just shift right
     }
   }
  
   // Note, this number has low and high bytes swapped, 
   // so use it accordingly (or swap bytes)
   // swapping bytes
   crc = ((crc<<8)&0xff00)|((crc>>8)&0x00ff);
   
   return crc;
}

  void modbus_wsr_answer() { 
    // ответ на команды записи в регистр
    
    // расчет CRC
    crc_buf[0] = dev_id;
    crc_buf[1] = modbus_wsr_cmd;
    crc_buf[2] = (U8)(modbus_reg_addr >> 8);
    crc_buf[3] = (U8)(modbus_reg_addr & 0x00ff);
    crc_buf[4] = (U8)(reg_wr_data >> 8);
    crc_buf[5] = (U8)(reg_wr_data & 0x00ff);
    CRC16 = modbus_CRC16(crc_buf, 6);

    //--------------------------------------------------------------------
    // отправка пакета мастеру
    Uart_send_hex(dev_id);                // ID устройства
    Uart_send_hex(modbus_wsr_cmd);        // код команды
    Uart_send_hex((U8)(modbus_reg_addr >> 8));           // ст. байт адреса регистра
    Uart_send_hex((U8)(modbus_reg_addr & 0x00ff));       // мл. байт адреса регистра
    Uart_send_hex((U8)(reg_wr_data >> 8));
    Uart_send_hex((U8)(reg_wr_data & 0x00ff));
     // отправка CRC
    Uart_send_hex((U8)(CRC16 >> 8));      // msb
    Uart_send_hex((U8)(CRC16 & 0x00ff));  // lsb   
          //--------------------------------------------------------------------
  }

  void modbus_rhr_answer() {
    // ответ на команды чтения регистров
  	  addr_buf_2 = addr_buf_1;             // сохр. адрес без смещения в двух переменных	  
          // расчет CRC
          crc_buf[0] = dev_id;
          crc_buf[1] = modbus_rhr_cmd;
          crc_buf[2] = regs2read*2;
          
          U8 cnt = 3;      // величина смещения данных при расчете CRC

          for(U8 i = 0; i < regs2read; i++)
          { // заполнение буфера CRC для расчета
            crc_buf[cnt++] = (U8)(holding_register[addr_buf_1] >> 8);
            crc_buf[cnt++] = (U8)(holding_register[addr_buf_1] & 0x00ff);
            ++addr_buf_1;
          }
            // расчет CRC  
          CRC16 = modbus_CRC16(crc_buf,(regs2read*2)+3);
          //--------------------------------------------------------------------
          // отправка пакета мастеру 
          Uart_send_hex(dev_id);                // ID устройства
          Uart_send_hex(modbus_rhr_cmd);        // код команды
          Uart_send_hex(regs2read*2);           // кол-во передаваемых байт 

          for(U8 i = 0; i < regs2read; i++)
          {   // отправка байт данных с инкрементом адреса
            Uart_send_hex((U8)(holding_register[addr_buf_2] >> 8));     // msb
            Uart_send_hex((U8)(holding_register[addr_buf_2] & 0x00ff)); // lsb
            ++addr_buf_2;
          }
          // отправка CRC
          Uart_send_hex((U8)(CRC16 >> 8));      // msb
          Uart_send_hex((U8)(CRC16 & 0x00ff));  // lsb    
          //--------------------------------------------------------------------
  
  }
/*=========================================================================== */
// Interupts
__irq void Timer3_IRQHandler(void) 
//функция обработки прерывания irq Timer 3 - СТРОБЫ ВНЕШНЕЙ СИНХРОНИЗАЦИИ
{   

    U32 int_flag = MDR_TIMER3->STATUS; // сохр. флаги источников прерываний от Т3 
     
    if(int_flag & (1<<5))   //  ___/ флаг прерывания по переднему фронту
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
        wr_ptr++;               // инкремент счетчика записанных байт
        rx_buf[wr_ptr & 0x0f] = MDR_UART1->DR; 
      
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
      
 ADC_init(ADC_scale);
 MCU_ADC_init();
                  
 NVIC_EnableIRQ(Timer3_IRQn); // Разрешение прерывания для T3 - Вход внешней синхр.
 NVIC_EnableIRQ(UART1_IRQn);  // Разрешение прерывания для UART1
 __enable_irq();	      // Enable Interrupts global
 MDR_TIMER3->CNTRL |= 1;      // Запуск Т3 --
 
 for(U8 i = 0; i < 125; i++) 
   holding_register[i] = 0;   // clearing resgisters  

 // предварительная уст. стробов интеграторов
 ADC_CONV_DOWN;
 IVC_SET;
 IVC_STOP_INT;
 delay_us(100);

 while(1)
{   
/// обработка команд
    while(rd_ptr < wr_ptr) // буфер не пуст, получен байт 
    {                                     
       rx_byte = get_rx_ch();  
              
       switch(rd_state)  // конечный автомат состояний чтения команд
       {
       //====
         case detect_dev_id:              // ждем обращения к устройтсву
           switch(rx_byte)
           {
             case dev_id:                 // получена команда обращения по текущему id устройтсва
               rd_state = get_cmd_header; // переход в состояние ожидания заголовка команды
             break;
             //----  
             case com_dev_id:             // получена команда широковещательного обращения
               rd_state = get_cmd_header; // переход в состояние ожидания заголовка команды
             break;
             //----    
             default:                     // действия при ошибке команды 
               rd_state = detect_dev_id;  // возврат в анализ id команды modbus
            }
          break;
       //=====                          
         case get_cmd_header:             // анализ команды modbus
           switch (rx_byte)
           { 
             case modbus_rhr_cmd:                 // чтение регистров
                  reg_addr_flag = 1;              // уст. флага чтения адреса регистра
                  regs2read = 0;
                  reg_wr_data = 0;
                  rd_state = get_modbus_word_msb; // переход в сост. получения двух байт с ПК
             break;      
             //---- 
             case modbus_wsr_cmd:                 // запись в регистр
                  reg_addr_flag = 1;              // уст. флага чтения адреса регистра
                  reg_wr_flag   = 1;              // уст. флага записи в регистр 
                  regs2read = 0;
                  reg_wr_data = 0;
                  rd_state = get_modbus_word_msb; // переход в сост. получения двух байт с ПК 
             break; 
             //---- 
             // возврат в сост. анализ id устройства в случае ошибки  
             default: rd_state = detect_dev_id;
           }
         break;
        //=====
         case get_modbus_word_msb:              // получение ст. байта
             temp_buf = (U16)rx_byte;           // сохр. ст. байт
             temp_buf = temp_buf << 8;
             rd_state = get_modbus_word_lsb;    // переход в сост. чтения мл. байта
         break;
         //=====
         case get_modbus_word_lsb:              // получение мл. байта 
             temp_buf |= (U16)rx_byte;          // сохр. мл. байт
             /// анализ флагов для дальнейших действий
             if(reg_addr_flag)                 // флаг принятия байт адреса?
             {
               modbus_reg_addr = temp_buf;     // сохр. адреса начального регистра для чтения
               reg_addr_flag = 0;              // сброс флага чтения адреса
               if(reg_wr_flag) reg_qty_flag = 0; // сброс флага приема числа регистров для чтения если была команда записи             
               else reg_qty_flag = 1;            // уст. флага приема числа регистров для чтения если был запрос
               rd_state = get_modbus_word_msb;   // переход в сост. чтения 2 байт кол-ва регистров для чтения
               temp_buf = 0;                     // обнуление временного буфера
               break;
             }
             
             if(reg_wr_flag)                   // флаг записи в регистр?
             { 
                reg_wr_data = temp_buf;        // сохр. значения для записи
                reg_wr_flag = 0;               // сброс флага записи в регистр
                get_crc_flag = modbus_wsr_cmd; // уст. кода расчета CRC для команды записи
                rd_state = get_modbus_word_msb;// переход в сост. чтения 2 байт CRC
                break;
             }
             
             if(reg_qty_flag)                  // флаг приема ко-ва регистров для чтения?
             { 
               if(temp_buf < max_regs_cnt)     // проверка на предел числа регистров для чтения
               {  // ок
                regs2read = temp_buf;           // сохранение числа регистров для чтения
                get_crc_flag = modbus_rhr_cmd;  // уст. кода расчета CRC для команды чтения
                rd_state = get_modbus_word_msb; // переход в сост. чтения 2 байт CRC
               }
                 // ошибка, возврат в сост. чтения id устройства
               else rd_state = detect_dev_id; 
               reg_qty_flag = 0;                // сброс флага чтения кол-ва регистров       
               break;
             }
             
             if(get_crc_flag == modbus_rhr_cmd)// расчет CRC16 для команды чтения регистров
             {
                crc_buf[0] = dev_id;
                crc_buf[1] = modbus_rhr_cmd;
                crc_buf[2] = (U8)(modbus_reg_addr >> 8);
                crc_buf[3] = (U8)(modbus_reg_addr & 0x00ff);
                crc_buf[4] = (U8)(regs2read >> 8);
                crc_buf[5] = (U8)(regs2read & 0x00ff);
                CRC16 = modbus_CRC16(crc_buf,6); 
                if(CRC16 == temp_buf) 
                { 
                  answer = modbus_rhr_cmd;
                  rd_state = detect_dev_id;
                }
                else rd_state = detect_dev_id; 
                get_crc_flag = 0;              // сброс флага расчета CRC16 
             }
               
             if(get_crc_flag == modbus_wsr_cmd)// расчет при команде записи в регистр
             { 
                crc_buf[0] = dev_id;
                crc_buf[1] = modbus_wsr_cmd;
                crc_buf[2] = (U8)(modbus_reg_addr >> 8);
                crc_buf[3] = (U8)(modbus_reg_addr & 0x00ff);
                crc_buf[4] = (U8)(reg_wr_data >> 8);
                crc_buf[5] = (U8)(reg_wr_data & 0x00ff);
             
                CRC16 = modbus_CRC16(crc_buf,6);
                if(CRC16 == temp_buf) 
                {
                  answer = modbus_wsr_cmd;
                  rd_state = detect_dev_id;
                }
                else rd_state = detect_dev_id; 
                get_crc_flag = 0;
               }
              
         break; 
         //=====
          default: rd_state = detect_dev_id;    
        } // switch
    }  // while 
//---------------------------------------------    
/// работа с модбас регистрами, формирование и отсылка ответа
    
    // гасим статусный светодиод для индикации активности RS485 для текущего устройства 
    if(meas_mode == 0) // если режим непрерывных измерений
    {
      if(answer != 0) 
      {
        SYNC_LED_ON;  
        cnt = 0;
      }
    }   
/// ЧТЕНИЕ
    if(answer == modbus_rhr_cmd) // ответ при команде чтения регистров
    {
         addr_buf_1 = modbus_reg_addr - 1000; // избавляемся от смещения в адресе
        //-----------------------------------
         holding_register[0] = new_meas;      // '0' - измерения не были обновлены, '1' - обновлены
        // ADCs
         for(U8 i = 1; i <= 48; i++) 
           holding_register[i] = InputConnPin[i];
         
         holding_register[50] = meas_mode;    // режим измерений 0 - непрерывные, 1 - импульсный по запуск   
         holding_register[51] = int_time;     // время интегирования
         holding_register[52] = ADC_scale;    // шкала измерений'0' - 3pC, '1' - 6pC, '2' - 12pC
         
         holding_register[55] = (U16)dev_id;
         holding_register[56] = (U16)device_family;
         holding_register[57] = (U16)firmware_ver;
         
         if(is_reg(49)) // если были прочитаны все измерения 
          new_meas = 0; // то сбрасываем флаг обновленных измерений
         
         modbus_rhr_answer();             // отсылка значений запрашиваемых регистров
         answer = 0;                      // сброс флага ответа
     }
/// ЗАПИСЬ 
    if(answer == modbus_wsr_cmd) // ответ при команде записи в регистр
    {
         addr_buf_1 = modbus_reg_addr-1000;          // избавление от смещения
         holding_register[addr_buf_1] = reg_wr_data; // запись переданных данных в регистр по адресу
	 //--------------------------------------------------------------------
         // заполнение переменных новыми значениями регистров
         meas_mode = holding_register[50];// режим измерений 0 - непрерывные, 1 - импульсный по запуску
                                 
         if(holding_register[51] > 65000)  
           holding_register[51] = 65000; // 65 ms max
         else if(holding_register[51] < 10)
           holding_register[51] = 10;    // 10 us min
         
         int_time = holding_register[51]; // сохр. t интегрирования
         
         if(addr_buf_1 == 52)
         {
            if(holding_register[52] > 2)  
              holding_register[52] = 2;   // 12 pC max
            ADC_scale = holding_register[52]; // шкала измерений'0' - 3pC, '1' - 6pC, '2' - 12pC
            ADC_change_scale();               // смена шкалы
         }
         //--------------------------------------------------------------------  
         modbus_wsr_answer();             // отсылка ответа на команду записи в регистр
         answer = 0;                      // сброс флага ответа
     }   
//------------------------------------------------------------------------------  
    switch(meas_mode)      // режимы измерений
    {
    case 0:
    /// режим непрерывных измерений  
        ADC_noise = (U32)(ADC_code*0.805664);//ADC_Vref*1000.0)/4096.0);   
        perform_integrate();                // выполнение интегрирования 
        cacl_beam_Q();                      // расчет заряда мишени для 43 канала
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
        ADC_noise = (U32)(ADC_code*0.805664);//ADC_Vref*1000.0)/4096.0);     
        cacl_beam_Q();                      // расчет заряда мишени для 43 канала
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