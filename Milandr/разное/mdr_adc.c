

#define U8  uint8_t
#define U16 uint16_t 
#define S16 int16_t 
#define U32 uint32_t
#define S32 int32_t

#define ADC_Vref 3.302		 // измеренное вольтметром напряжение питания МК

uint16_t MCU_ADC_aver_param = 100;
uint8_t  MCU_current_ADC_channel = 4;

/*=========================================================================== */
// ADC MCU
    void MCU_ADC_init(){

  MDR_RST_CLK->PER_CLOCK |= (1 << 17); //тактирование АЦП
  
  MDR_ADC->ADC1_CFG = (1 //Включение АЦП  
  |(0 << 2)   	// источник синхросигнала*/
  |(1 << 3)   	// Выбор способа запуска АЦП - послед. 
  |(0 << 4)  	// номер канала преобразования*/ - не важно, так как установим канал позже
  |(1 << 9)  	// переключение включено (перебираются каналы, выбранные в регистре выбора канала)
  |(0 << 10) 	// автоматический контроль уровней откл.
  |(0 << 11)  	// источник опорного - внутренний (VDD)
  |(4 << 12)  	// коэффициент деления частоты ADC_clk = HCLK/8 = 10 МГц
  |(0 << 16)  	//  работа двух АЦП одновременн откл.
  |(0 << 17)    //  TS_EN датчик температуры и источника опорного напряжения откл
  |(0 << 18)    // TS_BUF_EN усилитель для датчика температуры и источника опорного напряжения откл.
  |(0 << 19) 	// оцифровка датчика температуры откл./
  |(0 << 20));  // оцифровка источника опорного напряжения на 1.23 В откл
}

    void MCU_ADC_start_conv(void){
  
  	MDR_ADC->ADC1_CFG |= 1<<1;
  
}

    U32 MCU_ADC_read(void){
	  
	  // чтение АЦП, t выборки + t преобразования канала = 3.2 мкС при HCLK = 10М и предделителе АЦП = 1
	  //		     t выборки + t преобразования канала = 0.5 мкС при HCLK = 70М и предделителе АЦП = 1					
	  // вес младшего разряда АЦП = 3,3/4095 = 0,8 мВ
	  
	  U32 ADC_data = 0;
	  
  	  MCU_ADC_start_conv(); // начало преобразований данных
	  
	  while(!(MDR_ADC->ADC1_STATUS) & (1<<2)) {} // ждем готовность 
	  ADC_data = MDR_ADC->ADC1_RESULT;			 // читаем
	  
	  MCU_current_ADC_channel = ADC_data << 11;  //вытаскиваем номер 
	  MCU_current_ADC_channel = MCU_current_ADC_channel >> 27;  //канала чьи измерения
	  
	  ADC_data = ADC_data << 20;    // отбрасываем инфу о 
	  ADC_data = ADC_data >> 20;    // канале измерений
	  
	  return ADC_data;
}
					   
    void MCU_ADC_set_ch(U8 channel){
	  
	if (channel > 16) return;
	
	MDR_ADC->ADC1_CHSEL = 1 << channel; 
	
	
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
	  ADC_meas_voltage = (int)(ADC_Vref*ADC_rd_data*1000)/4096;	// преобразуем в волты  
	  return ADC_meas_voltage; 

}

/*=========================================================================== */


 int main()
{
 U32 full_current = 0;
 U32 ADC_noise = 0;
 U32 HV_FB_V = 0;      // напряжение ОС HV-части
        
 MCU_init();	// иницализация систем тактирования, портов, SPI и UART  

 while(1)
  { 
    HV_FB_V = Get_ADC_ch_voltage(5);
    Uart_send_num(HV_FB_V);
    Uart_CR_LF_send();
    
    delay_ms(500);
    
  }
//---   
 }	