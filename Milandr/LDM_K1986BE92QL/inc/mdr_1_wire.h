#ifndef __mdr_1_wire_H__
#define __mdr_1_wire_H__

/*--------------------------------------------------------------------------- */
#define CRC8INIT   0x00
#define CRC8POLY   0x18  
/*--------------------------------------------------------------------------- */

/*=========================================================================== */
// 1-wire 

	void OneWirePin_SetDir(U8 direction) {
	  
   // инициализация пина 1-wire
  
  if(!direction) MDR_PORTF->FUNC &= ~(1 << 1); 			// пин PD2 на вход
  else           MDR_PORTF->FUNC |=  (1 << 1); 			// пин PD2 на выход
  
  //MDR_PORTF->FUNC    = 0x0000;          // функция - порт 
  MDR_PORTF->ANALOG  = 0xffff;          // режим потра - цифровой
  MDR_PORTF->PWR     = 0xffffffff;      // максимально быстрый фронт ( порядка 10 нс)

 }
 
 	void OneWirePin_Low() {
	  
   // инициализация нуля на пине 1-wire
   
  MDR_PORTF->RXTX &= ~ (1 << 1);
 
 }
 
  	void OneWirePin_High() {
	  
   // инициализация 1 на пине 1-wire
   
  MDR_PORTF->RXTX |= (1 << 1);
 
 }
 
 	U8 OneWirePin_level() {
	  
  // Читает значение уровня на шине 1-wire
	  
  return MDR_PORTF->RXTX & (1 << 1);
}

	U8 OneWire_reset() {
	  
  // Выдаёт импульс сброса (reset), ожидает ответный импульс присутствия.
  // Если импульс присутствия получен, дожидается его завершения и возвращает 1, иначе возвращает 0 
	  
  OneWirePin_SetDir(1); // порт на выход	  
  OneWirePin_Low();
  delay_us(640); // Пауза 480..960 мкс
  OneWirePin_High();
  delay_us(5); // Время необходимое подтягивающему резистору, чтобы вернуть высокий уровень на шине
  // Ждём не менее 60 мс до появления импульса присутствия;
  OneWirePin_SetDir(0); // порт на вход	
  for (U8 c = 100; c; c--) {
    if (!OneWirePin_level()) {
      // Если обнаружен импульс присутствия, ждём его окончания
      while (!OneWirePin_level()) { } // Ждём конца сигнала присутствия
      return 1;
    }
    delay_us(10);
  }
  return 0;
}
 
	void OneWire_send_bit(U8 bit) {
  
  // Отправляет один бит
  // bit отправляемое значение, 0 - ноль, любое другое значение - единица
	  
  OneWirePin_SetDir(1); // порт на выход
  OneWirePin_Low();
  if (bit) {
    delay_us(10); // Низкий импульс, от 1 до 15 мкс (с учётом времени восстановления уровня)
    OneWirePin_High();
    delay_us(80); // Ожидание до завершения таймслота (не менее 60 мкс)
  } 
  else {
    delay_us(80); // Низкий уровень на весь таймслот (не менее 60 мкс, не более 120 мкс)
    OneWirePin_High();
    delay_us(5); // Время восстановления высокого уровеня на шине + 1 мс (минимум)
  }
}

	U8 OneWire_read_bit() {
  
  // читает значение бита, передаваемое уйстройством.
  // Возвращает 0 - если передан 0, отличное от нуля значение - если передана единица
	  
  U8 r = 0;
  
  OneWirePin_SetDir(1); // пин на выход
  OneWirePin_Low();
  delay_us(10); // Длительность низкого уровня, минимум 1 мкс
  OneWirePin_High();
  delay_us(10); // Пауза до момента сэмплирования, всего не более 15 мкс
  OneWirePin_SetDir(0); // пин на вход
  r = OneWirePin_level();
  delay_us(70); // Ожидание до следующего тайм-слота, минимум 60 мкс с начала низкого уровня
  
  return r;
}

        U8 OneWire_read() {
  
  // Читает один байт, переданный устройством, 
  // младший бит вперёд, возвращает прочитанное значение
  
  U8 r = 0;
  
  for (U8 p = 8; p; p--) {
    r >>= 1;
    if (OneWire_read_bit())
      r |= 0x80;
  }
  return r;
}

	void OneWire_send(U8 b) {
  
  // Отправляет один байт, восемь подряд бит, младший бит вперёд
  // b - отправляемое значение
	  
  for (U8 p = 8; p; p--) {
    OneWire_send_bit(b & 1);
    b >>= 1;
  }
}

	U8 crc8 (U8 data, U8 crc) {
	// расчет контрольной суммы
	  
	U8 bit_counter;
	U8 feedback_bit;
	
	bit_counter = 8;
	
	do
	{
    	feedback_bit = (crc ^ data) & 0x01;
    	if ( feedback_bit == 0x01 ) crc = crc ^ CRC8POLY;
    	crc = (crc >> 1) & 0x7F;
    	if ( feedback_bit == 0x01 ) crc = crc | 0x80;
    	data = data >> 1;
    	bit_counter--;
	}  while (bit_counter > 0);
	
	return crc;
 }

	U8 OneWire_skip() {
	  
	// Выполняет последовательность инициализации (reset + ожидает импульс присутствия)
	// Если импульс присутствия получен, выполняет команду SKIP ROM
	// Возвращает 1, если импульс присутствия получен, 0 - если нет
	  
  if (!OneWire_reset())
    return 0;
  OneWire_send(0xCC);
  	return 1;
}
	
	S32 ds18b20_rd_t () {
	  // чтение показаний датчика
	  	 
	 U8 scratchpad[8];		// буфер чтения датчика
	 U8 CRC = 0;
	 U8 OneWireRdByte = 0;	
 	 S32 Temper = 0; 
	  
 if (OneWire_skip()) { 				// Проверка наличия датчика на шине
	   
      OneWire_send(0x44); 						// датчик найден, запуск измерения Т 
	  do OneWireRdByte = OneWire_read();		// ожидание от датчика данных отличных от нуля 
	  while (OneWireRdByte == 0);
 }
 
 if (OneWire_skip()) {				// Считывание данных - команда RESET обязательно! 
	  OneWire_send(0xBE);			// Запрос на выдачу данных  
	  delay_us(2);

     for (U8 i = 0; i < 9; i++) {		// Считывание даннх датчика
        OneWireRdByte = OneWire_read();
        scratchpad[i] = OneWireRdByte;
        CRC = crc8(scratchpad[i], CRC); // расчет CRC
     }	     
	 if(CRC == 0) // CRC верна...
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
 	 }
 return Temper;	
}

// 1-wire
/*=========================================================================== */

#endif
