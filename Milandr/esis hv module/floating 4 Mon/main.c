/// Рабочий код ,программа для микроконтроллера  
/// устройство - блок формирования высокого напряжения

// 04/05/19 переделан под полностью плавающий, нет ОС по вторичке и ПИД-регулятора

#include "MDR32Fx.h"

#define F_CPU 80000000

#define U8  uint8_t
#define U16 uint16_t 
#define S16 int16_t 
#define U32 uint32_t
#define S32 int32_t

#include "mdr_delay.h"

#define HV_SUPPLY_ON  	MDR_PORTC->RXTX |=  1   
#define HV_SUPPLY_OFF   MDR_PORTC->RXTX &= ~1

#define HV_SWITCH_ON MDR_PORTE->RXTX & 1<<6 // анализ состояния тумблера высокого

// сигнал готовности данных АЦП для чтения 
#define RXFE                1<<4                    // равен 1 если пуст буфер FIFO приемника 
#define FIFO_has_byte       !(MDR_UART1->FR & RXFE)
#define CH1_CCR_CAP_EVENT   (1<<13)                 // Событие ?переднего? фронта на входе CAP каналов таймера 
                                                    // Бит 7 – третий канал
#define ADC_Vref            3.33		    // измеренное вольтметром напряжение питания МК

#define Status_LED_ON     MDR_PORTA->RXTX |= 1 << 3 
#define Status_LED_OFF    MDR_PORTA->RXTX &= ~(1 << 3)
#define Error_LED_ON      MDR_PORTA->RXTX |= 1 << 4 
#define Error_LED_OFF     MDR_PORTA->RXTX &= ~(1 << 4)

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
  U8 rx_buf[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}; 
//==============================================================================

//============================== RS485 defines =================================
#define RS485_RX_EN     MDR_PORTB->RXTX &= ~(1<<10)  // вкл.  приемник RS485   \_ 
#define RS485_RX_DIS    MDR_PORTB->RXTX |=  (1<<10)  // выкл. приемник RS485   _/
#define RS485_TX_EN     MDR_PORTB->RXTX |=  (1<<9)   // вкл.  передатчик RS485 _/
#define RS485_TX_DIS    MDR_PORTB->RXTX &= ~(1<<9)  // выкл. передатчик RS485 \_

#define modbus_rhr_cmd  0x03    // read holding registers cmd id
#define modbus_wsr_cmd  0x06    // write single register cmd id

#define com_dev_id 0            // В широковещательном режиме используется адрес 0
//#define dev_id 24               // modbus id текущего устройства                        
U8 dev_id = 23;                                                                         // <<<<<<<<<<=========================== ID
#define firmware_ver    11      // версия прошивки текущего устройства
#define device_family   3       // код семейства устройств: 1 - PBF modules, 2 - extraction modules, 3 - dc hv modules
#define max_regs_cnt    125     // макс. кол-во регистров для чтения за 1 раз

#define volt_lvl_reg    1000    // адрес регистра измеренного напряжения с HV-делителя

  U8 reg_addr_flag = 0;
  U8 reg_wr_flag = 0;
  U8 reg_qty_flag = 0;
  U8 get_crc_flag = 0;

  U8 rx_byte;       // байт принятый с ПК
 
  U8 answer = 0;    // тип ответа на команду с ПК
  U8 rd_state = detect_dev_id; // машина состояний по умолчанию ждет обращения по id устройста modbus
  U16 modbus_reg_addr = 0;     // адрес регистра для R/W по запросу от modbus мастера
  U16 temp_buf = 0;            // временный буфер
 
  U16 regs2read = 0;           // число регистров для чтения по команде modbus rhr
  U8  crc_buf[250];            // буфер для хранения байтов для расчета CRC16
  U16 CRC16 = 0;               // для хранения рассчитаной контрольной суммы
  U16 addr_buf_1, addr_buf_2;

  U16 reg_wr_data = 0;
  U16 holding_register[125];   // буфер для хранения переменных чтения, макс. число регистров - 124
//==============================================================================

  U32 MCU_current_ADC_channel = 0;
  U16 MCU_ADC_aver_param = 20;    // величина усренднения данных АЦП
  S32 DAC_code = 0;                // код DAC - управление выходным напряжением 
  S32 DAC_code_ramp = 0;           // код DAC - управление выходным напряжением 
  S32 DAC_code_ramp_prev = 0;
  U8 ramp_in_progress = 0;
  S32 ADC_code = 0;                // отсчеты АЦП напряжения ОС HV-части
  U32 ADC_V = 0;				   // для хранения текущего измерянного вых. напряжения
  U16 V2set = 0;                   // для хранения уставки с ПК
  
  float p = 0;           // П-звено регулятора 
  float i = 0;           // I-звено регулятора 
  float d = 0;           // D-звено регулятора 
  S32 pid = 0;           // скорректированное значение кода ЦАП
  float error = 0;       // текущая ошибка между ЦАП и АЦП
  float prev_error = 0;  // предыдущ. ошибка между ЦАП и АЦП
  float kp = 7.0;        // коэффициент П-звена регулятора
  float ki = 0.7;        // коэффициент I-звена регулятора
  float kd = 0.0;        // коэффициент D-звена регулятора
  
  float i_lim_r = 100.0;        // сопротивление резистора в возвратной цепи тока
  
  U8  I_lim_state = 0;
  U32 I_load = 0;               // ток в нагрузке в мкА
  U32 I_load_code = 0;          // отсчеты тока в нагрузке
  U16 I_lim_val = 10000;        // уровень срабатывания защиты по току в мкА
  U16 overcurrent_bit = 0;      // статус-бит перегрузки по току: 0 - ок, 1 - сработала защита по току
  U16 HV_EN_bit = 0;            // статус-бит вкл. высокого из регистра
  U8 overcurrent_count = 0;     // число срабатыаний перегрузки по току
  U8 overcurrent_lim = 9;       // порог откл. HV при перегрузке по току
  U8 overcurr_state = 0;              
  U8 HV_sw_state = 0;           // статус-бит тумблера высокого: 0 - выкл, 1 - вкл
  U8 HV_sw_state_prev = 0;      // статус-бит тумблера высокого с предыдущей итерации осн. цикла
  
  // для защиты по току
  U32 V_curr = 0;
  U32 V_prev = 0;
  S16 meas_delta = 0;
  U16 set_delta = 0;

  void OSC_init(void){

#define	_HSEBYP	0       // 0 - режим осциллятора, 1 - режим внешнего генератора
#define	_HSEON  1	// 0 - выключен, 1 - включен

//---CLK-----------------------------------------------------------------------------------------------------

  MDR_RST_CLK->HS_CONTROL = (_HSEBYP<<1) + _HSEON; 
  while ((MDR_RST_CLK->CLOCK_STATUS & 0x04) != 0x04);     // ждем пока HSE выйдет в рабочий режим
  MDR_RST_CLK->PLL_CONTROL = ((1 << 2) | (7 << 8)); 	  // вкл. PLL | коэф. умножения = 2

  while((MDR_RST_CLK->CLOCK_STATUS & 0x02) != 0x02);      // ждем когда PLL выйдет в раб. режим

  MDR_RST_CLK->CPU_CLOCK  = (2                           // источник для CPU_C1 - HSE
						   |(1 << 2)                      // источник для CPU_C2 - PLLCPUo 
						   |(1 << 4)                      // предделитель для CPU_C3 - CPU_C2
						   |(1 << 8));                    // источник для HCLK
  MDR_RST_CLK->PER_CLOCK = 0xFFFFFFFF;                    // вкл. тактирование всей перефирии
  // HCLK = 80 МГц
  }
   
  void GPIO_init (void){  
  
  MDR_PORTA->OE      = 0xFFFD;          //  PA1 - вход синхронизации
  MDR_PORTA->FUNC    = (2<<2);          // функция - порт, для РА5 альтернативная функция 
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
  MDR_PORTC->ANALOG = 0xFFFF;      
  MDR_PORTC->PWR    = 0xFFFFFFFF;       // максимально быстрый фронт
  //---------------------------------------------------------------------------//
  MDR_PORTD->OE = 0x00ca;               // порт D на вход, PD2 - ADC_CH2, PD4 - ADC_CH4, PD5 - ADC_CH5
  MDR_PORTD->FUNC = 0x0000;             // функция - порт 
  MDR_PORTD->ANALOG  = 0xffcb;          // режим потра - цифровой, но PD2 - ADC_CH2, PD4 - ADC_CH4, PD5 - ADC_CH5
  MDR_PORTD->PWR     = 0xFFFFFFFF;      // максимально быстрый фронт ( порядка 10 нс)
  //MDR_PORTD->PD =     ((0 << (2 << 16))); //режим работы входа 2 = АЦП
  //---------------------------------------------------------------------------//
  MDR_PORTE->OE = 0xffbf;               // порт E на выход, PB6 - вход - анализ вкл. тумблера высокого
  MDR_PORTE->FUNC = 0x0000;             // функция - порт 
  MDR_PORTE->ANALOG  = 0xfff0;          // режим потра - цифровой, PE0 - DAC2 out
  
  //---------------------------------------------------------------------------//
  MDR_PORTF->OE = 0xffb7;               // порт F на выход,PF3 - RxD
  MDR_PORTF->FUNC = (2 << 6) |		    // режим  пинов 1, 2, 3, 4 порта 
					(2 << 4) |			// - альтернативный, задействован модуль SSP1
					(2 << 2) |
					(2 << 0);
  MDR_PORTF->ANALOG  = 0xffff;          // режим потра - цифровой
  MDR_PORTF->PWR     = 0xFFFFFFFF;      // максимально быстрый фронт ( порядка 10 нс)

   }
 
  void timer1_init(void) {
          
  // настройка таймера для режима захвата падающего фронта -> \_ 
          
  // настройка таймера для прерывания   
  MDR_RST_CLK->TIM_CLOCK  |= (1 << 24) | 3;      // разрешение тактирования Timer1, TIM1_CLK = HCLK/8 = 10МГц												

  MDR_TIMER1->CNTRL = 0x00000000;        	 // направление счета основного счетчика от нуля до ARR,
						 // начальное значение - число из регистра CNT 
  MDR_TIMER1->PSG   = 1999;                      // предделитель частоты = 2000, TIM1_CLK = 5 кГц
  MDR_TIMER1->ARR   = 4;                	 // основание счета = 5, 0.2 мc * 5 = 1 мс
  MDR_TIMER1->CNT   = 0;       	                 // начальное значение счетчика 
  MDR_TIMER1->IE    = (1 << 1);                  // разрешение прерывания по совпадению

 }

  void timer3_init(void) {
          
  // настройка таймера для прерывания   
 MDR_RST_CLK->TIM_CLOCK  |= (1 << 26) | (3<<16);  // разрешение тактирования Timer3, TIM3_CLK = HCLK/8 = 10МГц													

 MDR_TIMER3->CNTRL = 0x00000000;        	 // направление счета основного счетчика от нуля до ARR,
						 // начальное значение - число из регистра CNT 
 MDR_TIMER3->PSG   = 49999;                      // предделитель частоты = 50 000
 MDR_TIMER3->ARR   = 19;                	 // основание счета = 200, 200 * 5 мс = 1000 мс
 MDR_TIMER3->CNT   = 0;       	                 // начальное значение счетчика 
 MDR_TIMER3->IE    = (1 << 1);                   // разрешение прерывания по совпадению

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
}

  void MCU_ADC_start_conv(void){
  
  	MDR_ADC->ADC1_CFG |= 1<<1;
        MDR_ADC->ADC1_CFG |= 1;
}

  void MCU_ADC_stop_conv(void){
  
  	MDR_ADC->ADC1_CFG &= ~(1<<1);
        MDR_ADC->ADC1_CFG &= ~1;
}

  U32 MCU_ADC_read(void){
	  
	  // чтение АЦП, t выборки + t преобразования канала = 3.2 мкС при HCLK = 10М и предделителе АЦП = 1
	  // t выборки + t преобразования канала = 0.5 мкС при HCLK = 70М и предделителе АЦП = 1					
	  // вес младшего разряда АЦП = 3,3/4095 = 0,8 мВ
	  
	  U32 ADC_data = 0;
	  
  	  MCU_ADC_start_conv(); // начало преобразований данных
	  
	  //while(!(MDR_ADC->ADC1_STATUS) & 0x04) {}//(1<<2)) {} // ждем готовность, но не работает
          delay_us(20);
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
          delay_us(100);
	  ADC_rd_data = MCU_ADC_Rd_average(MCU_ADC_aver_param);		// читаем среднее значение отсчетов АЦП
	  ADC_meas_voltage = (U32)((ADC_Vref*ADC_rd_data*1000)/4096);	// преобразуем в волты  
	  return ADC_meas_voltage; 

}
/*=========================================================================== */

/*=========================================================================== */
// UART
  void Uart_init (void){
//UART	  
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

  void Uart_text_send(unsigned char *s){
  while (*s != 0)
    Uart_send_hex(*s++);
}

/*========================================================================== */
// MODBUS

  char get_rx_ch (void)
  {                                                     
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

  U16 modbus_CRC16(U8 buf[], int len)
  {//-------crc16
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

  void modbus_wsr_answer()
  { // ответ на команды записи в регистр
    // расчет CRC
    crc_buf[0] = dev_id;
    crc_buf[1] = modbus_wsr_cmd;
    crc_buf[2] = (U8)(modbus_reg_addr >> 8);
    crc_buf[3] = (U8)(modbus_reg_addr & 0x00ff);
    crc_buf[4] = (U8)(reg_wr_data >> 8);
    crc_buf[5] = (U8)(reg_wr_data & 0x00ff);
    CRC16 = modbus_CRC16(crc_buf, 6);

    //--------------------------------------------------------------------
    RS485_TX_EN;
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
    delay_ms(1);    
    RS485_TX_DIS;
          //--------------------------------------------------------------------
  }

  void modbus_rhr_answer()
  {
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
          RS485_TX_EN;
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
          delay_ms(1);
          RS485_TX_DIS;
          //--------------------------------------------------------------------
  }

/*========================================================================== */
// INTERRUPTS
__irq void UART1_IRQHandler( void )
 // функция обработки прерывания irq UART1
{
  /// прерывание возникает при поступлении 1 байта на UART1
    wr_ptr++;               // инкремент счетчика записанных байт
    rx_buf[wr_ptr & 0x0f] = MDR_UART1->DR; 
    MDR_UART1->ICR  = 1<<4; // сброс прерывания от приемника  
}

__irq void Timer3_IRQHandler ( void )
 // функция обработки прерывания irq Timer3 - защита по току
{

    if(I_load >= (U32)I_lim_val) overcurr_state = 1;
    
    switch (overcurr_state)
    {
      case 0: 
        Error_LED_OFF;
        if(overcurrent_count > overcurrent_lim) overcurrent_bit = 1; // уст. флаг перегрузки по току 
        else overcurrent_bit = 0;       
        MDR_TIMER3->ARR   = 19;    // прерывание каждые 1000 мс.
      break;
      
      case 1:
        MCU_ADC_init();               // сброс предыдущих настроек
        MCU_ADC_set_ch(5);            // установка канала АЦП 
        // чтение отсчетов АЦП 
        ADC_code  = (S32)(MCU_ADC_Rd_average(MCU_ADC_aver_param)); 
       // преобразование в волты измеренного вых. напряжения
        ADC_V     = (U32)(ADC_code*0.8056640625);//ADC_Vref*1000.0)/4096.0);
        V_prev = V_curr;
        V_curr = ADC_V;
        set_delta  = V2set - (ADC_V & 0x00ff);
        meas_delta = (S16)(V_curr - V_prev);
        if ( (set_delta > 10) && (meas_delta < 2) ) overcurr_state = 2;
        else { overcurr_state = 0; break; }
      
      case 2: 
        if(overcurrent_count > overcurrent_lim)
        {
          overcurrent_bit = 1;
          MDR_TIMER3->ARR   = 199; 
          HV_SUPPLY_OFF;             // выкл. высокое
        }
        else overcurrent_count ++;   // инкремент попыток подачи высокого в режиме перегрузки по току
    
        overcurr_state = 0;
        MDR_TIMER3->ARR   = 19;    // уст. порог прерывания на каждые 100 мс.
        MDR_TIMER1->CNTRL |= 1;
      break;
      
    default: break;
    }
    
  MDR_TIMER3->CNT = 0x0000;
  MDR_TIMER3->STATUS = 0x0000;
  NVIC_ClearPendingIRQ(Timer3_IRQn); // обязательно!
}

__irq void Timer1_IRQHandler ( void )
 // функция обработки прерывания irq Timer1 - RAMP
{
 // прерывание 1 мс

    if((U32)DAC_code_ramp > MDR_DAC->DAC2_DATA)     // если установка больше текущей
     MDR_DAC->DAC2_DATA++;           // инкремент переменной уст. ЦАП, пока не достигнет заданн. знач.
    else                             // если установка меньше текущей  
    {   
     MDR_DAC->DAC2_DATA = DAC_code_ramp;       // записываем новую установку
     MDR_TIMER1->CNTRL &= ~1;        // стоп Т1 - RAMP
     ramp_in_progress = 0;           // сброс флага плавного поднятия напряжения
    }
 
  MDR_TIMER1->CNT = 0x0000;
  MDR_TIMER1->STATUS = 0x0000;
  NVIC_ClearPendingIRQ(Timer1_IRQn); // обязательно!
}

/*=========================================================================== */
// DAC
  void MCU_DAC2_init (void){
    
    MDR_DAC->CFG = (0<<4) | // DAC1 DAC2 асинхронны
                   (1<<3) | // DAC2 enabled  
                   (0<<2) | // DAC1 disabled
                   (0<<1) | // DAC2 ref - AUcc voltage
                   (0<<1);  // DAC1 ref - AUcc voltage
  }
  
  void MCU_init (void) {
	  
 	 OSC_init();
	 SysTickTimer_Init();
 	 GPIO_init();  
	 timer1_init();         // ramp, плавное поднятие напряжения
         timer3_init();         // защита по току
         
         Uart_init();           // UART1 - RS485
         MCU_DAC2_init();       // инициализация DAC2
         MCU_ADC_init();
	}
  
/*=========================================================================== */
// MAIN    
        
 int main()
{  
 U8 status_led_delay_cnt = 0;   // счетчик длительности вкл. статусного светодиода
 
 for(U8 i = 0; i < 125; i++) holding_register[i] = 0; // очистка буфера переменных чтения
 
 MCU_init();	               // иницализация систем МК
 NVIC_EnableIRQ(Timer1_IRQn);  // разрешение прерывания T1
 NVIC_EnableIRQ(Timer3_IRQn);  // разрешение прерывания T3
 NVIC_EnableIRQ(UART1_IRQn);   // разрешение прерывания UART1
 
 RS485_RX_EN;  // вкл. приемника   RS485
 RS485_TX_DIS; // вкл. передатчика RS485
 
 MDR_DAC->DAC2_DATA = 0;      // сброс значения ЦАП       
 MDR_TIMER3->CNTRL |= 1;      // старт Т3 - проверка защиты по току каждые 1000 мс
 __enable_irq();	      // Enable Interrupts global
 HV_SUPPLY_ON;                // вкл. питания HV-части
 HV_EN_bit = 1;               // вкл. при подаче питания по умолч. -> для работы без программы
 
 while(1)
  {     
//----------------------------------------------------------------------------- 
    // обработка команд
    while(rd_ptr < wr_ptr) // буфер не пуст, получен байт 
    {                                     
       rx_byte = get_rx_ch();  
              
       switch(rd_state)  // конечный автомат состояний чтения команд
       {
       //====
         case detect_dev_id:              // ждем обращения к устройтсву
           if((rx_byte == dev_id) || (rx_byte == com_dev_id))
           {
                                          // получена команда обращения по текущему id устройтсва
               rd_state = get_cmd_header; // переход в состояние ожидания заголовка команды
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
    // гасим статусный светодиод для индикации активности RS485 для текущего устройства 
    if(answer != 0)       
    {
      if(overcurrent_bit) Error_LED_OFF;
      else Status_LED_OFF;
      status_led_delay_cnt = 0;
    }
    
    // ЧТЕНИЕ
    if(answer == modbus_rhr_cmd) // ответ при команде чтения регистров
    {
         addr_buf_1 = modbus_reg_addr - 1000; // избавляемся от смещения в адресе
         // чтение установок из регистров
         holding_register[0] = V2set;     			// вых. напряжения в Вольтах в режиме удаленного упр. 
         
         holding_register[1] = (U16)kp;
         holding_register[2] = (U16)(ki*10.0);
         holding_register[3] = (U16)kd;
         
         holding_register[5] = (U16)ADC_V;                      // текущее значение выходного напряжения, В
         holding_register[6] = (U16)I_load;                     // ток в нагрузке, мкА
         holding_register[7] = (U16)overcurrent_count; 
         holding_register[9] = HV_EN_bit;                       // бит вкл. высокого
         holding_register[8] = (U16)ramp_in_progress;
         holding_register[10] = I_lim_val;                      // уровень срабатывания защиты по току в мкА  
         holding_register[11] = HV_sw_state;                    // статус бит состояния тумблера высокого напряжения
         holding_register[12] = overcurrent_bit;                // статус бит индикации защиты по току 
         holding_register[13] = (U16)dev_id;                    // modbus id текущего устройства
         holding_register[14] = (U16)firmware_ver;              // версия прошивки текущего устройства
         holding_register[15] = (U16)device_family;             // семейство устройства 3 - dc hv module
         
         modbus_rhr_answer();    // отсылка значений запрашиваемых регистров
         answer = 0;             // сброс флага ответа
     }
    //----------
    // ЗАПИСЬ 
    if(answer == modbus_wsr_cmd) // ответ при команде записи в регистр
    {
         addr_buf_1 = modbus_reg_addr-1000;          // избавление от смещения
         holding_register[addr_buf_1] = reg_wr_data; // запись переданных данных в регистр по адресу
	 //--------------------------------------------------------------------
         // заполнение переменных новыми значениями регистров
	 V2set = holding_register[0];                           // сохр. значения для установки
	 if(holding_register[0] > 3200) holding_register[0] = 3200;
    
         HV_EN_bit = holding_register[9];         // сохр. команды вкл. высокого
         DAC_code_ramp = (S32)(V2set / 0.805664); // преобразование вольт в отсчета ЦАП 

         if(HV_EN_bit == 1)  
         { 
           DAC_code_ramp_prev = 1;
           HV_SUPPLY_ON;   // вкл.  питания HV-части 
         }
         if(HV_EN_bit == 0)  
         {
           DAC_code = 0;
           HV_SUPPLY_OFF;  // выкл. питания HV-части 
         }

          // уровень срабатывания защиты по току в мкА  
         if(holding_register[10] > I_lim_val) holding_register[10] = I_lim_val;        // 10 мА - макс.
         else if (holding_register[10] < 500)  holding_register[10] = 500;   // 500 мкА - мин.
         I_lim_val = holding_register[10];       
         
         if( (holding_register[12] == 0) && overcurrent_bit )    
         { // сброс статуса защиты по току
          MDR_DAC->DAC2_DATA = 0;
          i = 0;
          DAC_code_ramp_prev = 0;
          DAC_code = 0;
          HV_SUPPLY_ON;
          overcurrent_count = 0; 
          overcurrent_bit = 0;  
         }

         modbus_wsr_answer();             // отсылка ответа на команду записи в регистр
         answer = 0;                      // сброс флага ответа
     }     
//--------------------------------------------------------------------  

//--------------------------------------------------------------------      
    MCU_ADC_init();               // сброс предыдущих настроек
    MCU_ADC_set_ch(5);            // установка канала АЦП 
     // чтение отсчетов АЦП 
    ADC_code  = (S32)(MCU_ADC_Rd_average(MCU_ADC_aver_param)); 
     // преобразование в волты измеренного вых. напряжения
    ADC_V     = (U32)(ADC_code*0.8056640625);//ADC_Vref*1000.0)/4096.0);
    
    // если вкл. тумблер и не сработала защита по току
    if(holding_register[9] & (!overcurrent_bit))
    {
    // плавное поднятие вых. напряжения
    if((DAC_code_ramp_prev != DAC_code_ramp)) // поступило новое значение напряжения?
    {
       DAC_code_ramp_prev = DAC_code_ramp;   // перезапись предыдущего значения переменной кода ЦАП  
       ramp_in_progress = 1;       // уст. флага плавного поднятия напряжения
       MDR_TIMER1->CNTRL |= 1;     // старт Т1 - RAMP
    }

    }
    else MDR_DAC->DAC2_DATA = 0;
//--------------------------------------------------------------------      
     // измерение тока в нагрузке в мкА  
     MCU_ADC_init();                             // сброс предыдущих настроек
     MCU_ADC_set_ch(4);                          // установка канала АЦП
     I_load_code  = (S32)(MCU_ADC_Rd_average(MCU_ADC_aver_param));  // чтение отсчетов АЦП 
     I_load = (U32)((I_load_code*0.8056640625/ i_lim_r) * 333.333); // коэффициент усиления оу = 3
//======================================     
     if(HV_SWITCH_ON)       // если тумблер высокого вкл.
     {
       HV_sw_state = 1;     // уст. флага вкл. тумблера высокого
       if(HV_sw_state_prev != HV_sw_state) 
       { // событие вкл. тумблера 
         MDR_DAC->DAC2_DATA = 0;
         i = 0;
         DAC_code_ramp_prev = 0;
         DAC_code = 0;
         HV_SUPPLY_ON;
       }
     }
     else 
     {
       HV_sw_state = 0;     // сброс флага вкл. тумблера высокого 
       if(HV_sw_state_prev != HV_sw_state) 
       {
        // событие выкл. тумблер
         overcurrent_count = 0; 
         overcurrent_bit = 0;  
       }
     }
     // перезапись предыдущего значения статуса тумблера высокого 
     HV_sw_state_prev = HV_sw_state;   
//======================================  
//индикация        
     status_led_delay_cnt++;
     if(status_led_delay_cnt > 35)
     {
      if(overcurrent_bit) { Status_LED_OFF; Error_LED_ON; }
      else                { Error_LED_OFF; Status_LED_ON; }
      status_led_delay_cnt=0;
     }
     
  } // while  
} // main
