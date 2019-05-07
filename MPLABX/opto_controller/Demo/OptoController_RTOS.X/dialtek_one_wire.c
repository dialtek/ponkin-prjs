// 1-wire
#include "FreeRTOS.h"
#include "queue.h"
#include "dialtek_one_wire.h"
// 1-wire версия с транзистором
/*--------------------------------------------------------------------------- */

void Timer8_init(void)
{
       //IPC12bits.T8IP = configKERNEL_INTERRUPT_PRIORITY;
       
       T8CONbits.TON = 0;           // Timer on/off bit; 0 - Disable Timer
       IFS3bits.T8IF = 0;           // Clear Timer interrupt flag
       TMR8 = 0x0000;               // reset if timer is on, 115200
       T8CONbits.TCS = 0;           // Timer Clock Source Select bit; 0 - Internal clock (FOSC/2)
       T8CONbits.TGATE = 0;         // Disable Gated Timer mode
       T8CONbits.TCKPS = 0;         // Prescaler = (00=1, 01=8, 10=64, 11=256) 
       
       PR8 = 35;                    // 1 us = 41.6 ticks

 }

void OneWire_init(void)
{
    Timer8_init(); // us delay timer init;
}

void delay_us(unsigned int delay)
{
   for(unsigned int i = 0; i < delay; i++)
   {
        T8CONbits.TON = 1;               // Start Timer  
        while(!IFS3bits.T8IF);
        IFS3bits.T8IF = 0;               // claer int flag
        T8CONbits.TON = 0;                // Stop Timer  
   }
}

 void OneWire_tx_state(unsigned char state) {
	  
   // установление лог. упровня на линии 1-wire
   
  One_wire_TX_pin = state;
 
 }
 
 unsigned int OneWire_rx_state() {
	  
  // Читает значение уровня на шине 1-wire

  if(One_wire_RX_pin == 0)
    return 1;
  
  if(One_wire_RX_pin == 1)
    return 0;
}

 unsigned char OneWire_reset() {

  unsigned char answer = 0;
   
  OneWire_tx_state(1);
  delay_us(550);
  OneWire_tx_state(0);
  
  delay_us(50); // Время необходимое подтягивающему резистору, чтобы вернуть высокий уровень на шине
  // Ждём не менее 60 мс до появления импульса присутствия;
  
  for (unsigned char c = 100; c; c--) 
  {
    if (OneWire_rx_state() == 1) 
    {
      //while(!OneWire_rx_state())
	    delay_us(40);
        answer = 1;
    }
  }

  delay_us(10);
  return answer;
}
 
 void OneWire_send_bit(unsigned char bit) {
  
  // Отправляет один бит
  // bit отправляемое значение, 0 - ноль, любое другое значение - единица
	  
  OneWire_tx_state(1);
  if (bit) {
    delay_us(8); // Низкий импульс, от 1 до 15 мкс (с учётом времени восстановления уровня)
    OneWire_tx_state(0);
    delay_us(70); // Ожидание до завершения таймслота (не менее 60 мкс)
  } 
  else {
    delay_us(70); // Низкий уровень на весь таймслот (не менее 60 мкс, не более 120 мкс)
    OneWire_tx_state(0);
    delay_us(10); // Время восстановления высокого уровеня на шине + 1 мс (минимум)
  }

}

 unsigned char OneWire_read_bit() {
  
  // читает значение бита, передаваемое уйстройством.
  // Возвращает 0 - если передан 0, отличное от нуля значение - если передана единица
	  
  unsigned char retVal = 0;
  // 1 - линия в 0
  OneWire_tx_state(1);
  delay_us(10); // Длительность низкого уровня, минимум 1 мкс
  OneWire_tx_state(0);
  delay_us(5); // Пауза до момента сэмплирования, всего не более 15 мкс
  
  if(OneWire_rx_state() == 0) retVal = 1;
 
  delay_us(70); // Ожидание до следующего тайм-слота, минимум 60 мкс с начала низкого уровня
  
  return retVal;
}

 unsigned char OneWire_read() {
  
  // Читает один байт, переданный устройством, 
  // младший бит вперёд, возвращает прочитанное значение
  
  unsigned char r = 0;

  for (unsigned char p = 8; p; p--) {
    r >>= 1;
    if (OneWire_read_bit())
      r |= 0x80;
  }

  return r;
}

 void OneWire_send(unsigned char b) {
  
  // Отправляет один байт, восемь подряд бит, младший бит вперёд
  // b - отправляемое значение
	
  for (unsigned char p = 8; p; p--) 
  {
    OneWire_send_bit(b & 1);
    b >>= 1;
  }
}

 unsigned char crc8 (unsigned char data, unsigned char crc) {
	// расчет контрольной суммы
	  
	unsigned char i;

	crc = crc ^ data;
	for (i = 0; i < 8; i++)
	{
	    if (crc & 0x01)
	        crc = (crc >> 1) ^ 0x8C;
	    else
	        crc >>= 1;
	}

	return crc;
 }

 unsigned char OneWire_skip() {
	  
	// Выполняет последовательность инициализации (reset + ожидает импульс присутствия)
	// Если импульс присутствия получен, выполняет команду SKIP ROM
	// Возвращает 1, если импульс присутствия получен, 0 - если нет
	  
  if (!OneWire_reset())
    return 0;
  OneWire_send(0xCC);
  	return 1;
}

 unsigned char OneWire_all_rd_t() {
 
	// Выполняет последовательность инициализации (reset + ожидает импульс присутствия)
	// Если импульс присутствия получен, выполняет команду SKIP ROM
	// Дает команду измерение температуры
  if (OneWire_reset())
  {
      OneWire_send(Skip_ROM);             // Обращение ко всем датчикам на шине 
      OneWire_send(Convert_T); 		  //  запуск измерения Т 
      OneWire_tx_state(0);

      return 1;
  }
  else return 0;
  }

 unsigned char Onewire_read_rom(QueueHandle_t *ROM_queue) {
  // Выполняет последовательность инициализации (reset + ожидает импульс присутствия)
  // Если импульс присутствия получен, выполняет команду READ ROM, затем читает 8-байтовый код устройства
  // сохраняет его в буфер по указателю buf, начиная с младшего байта
  // Возвращает 1, если код прочитан, 0 - если импульс присутствия не получен
     
  unsigned char OwRxByte = 0;
     
  if (!OneWire_reset())
    return 0; 
  OneWire_send(Read_ROM);
  for (unsigned char p = 0; p < 8; p++) {
    OwRxByte = OneWire_read(); /// сохранение ID датчика в переменную

  }
  return 1;
  /*вывод данных памяти датчика 8 байт в 2 строки
  LCD_set_cursor(1); 
for (unsigned char i = 0; i < 4; i++)  //вывод данных памяти датчика 8 байт в 2 строки
	{
          LCD_Wr_num(sens_ID[i],3);
          LCD_print(" ");
        }
LCD_set_cursor(2);
for (unsigned char i = 4; i < 8; i++)  
	{
          LCD_Wr_num(sens_ID[i],3);
          LCD_print(" ");
        }
  */
}

 unsigned char OneWire_match_ID(unsigned char *sens_ID) {
  
  if (OneWire_reset() == 0)
    return 0;
  else
  {
    OneWire_send(Match_ROM);
    for (unsigned char p = 0; p < 8; p++) 
    {
     OneWire_send(sens_ID[p]);
    }
  return 1;
  }
}
		
 long ds18b20_i_rd_t () {
	  // чтение показаний конкретного датчика
	 	 
	 unsigned char scratchpad[8];		// буфер чтения датчика
	 unsigned char CRC_read = 0;
         unsigned char CRC_calc = 0;
	 unsigned char OneWireRdByte = 0;	
 	 long Temper = 0; 
	 
     //vTaskSuspendAll();
     
	 OneWire_send(Read_scr);			// Запрос на выдачу данных  
	 
     for (unsigned char i = 0; i < 9; i++) 
     {		// Считывание данных датчика
        OneWireRdByte = OneWire_read();
        scratchpad[i] = OneWireRdByte;
	
	 if(i == 8) CRC_read = scratchpad[8];// сохр црц
     }
     //xTaskResumeAll();
     
     for (unsigned char i = 0; i < 8; i++) 
     {		// Считывание даннх датчика
        CRC_calc = crc8(scratchpad[i], CRC_calc); // расчет CRC
     }

     if(CRC_calc == CRC_read) // CRC верна...
	{
	 		Temper = (scratchpad[1] << 8) | scratchpad[0]; // соединяем ст. и мл байты данных
			if(Temper < 2000)
	 			Temper = (625 * Temper)/10; 				   // приводим отсчеты к температуре
			 											   	   // +125 градусов - 2000 отсчетов
			else {
				Temper = Temper - 65535;					   // приводим отсчеты к температуре
				Temper = (55 * Temper*1000)/879;			   // отрицательная Т
			}
	}
 //	 }
 return Temper;	
}

 unsigned char get_sensor_ID(unsigned char *sens_ID)
 {
     
	 if (OneWire_reset())
	 { 
       OneWire_send(Read_ROM);
	   for(unsigned char i = 0; i < 8; i++)
       {
           sens_ID[i] = OneWire_read();
       }
       return 1;
	 }
     
     return 0;
 }

// 1-wire
/*=========================================================================== */
