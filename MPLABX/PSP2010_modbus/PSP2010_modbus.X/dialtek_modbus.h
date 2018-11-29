/*                D I A L T E K    M O D B U S   R T U   v 2.1               */

/* ЗАГОЛОВКИ, ПЕРЕМЕННЫЕ И СЛУЖЕБНЫЕ ФУНКЦИИ */

/* изменения необходимо вносить в файл dialtek_modbus.с */

//================================ STATE MACHINE ===============================
  
#define DETECT_DEV_ID         10      // 10 - ожидание id устройства 
#define GET_CMD_HEADER        11      // 11 - получение типа команды 
#define GET_MODBUS_WORD_MSB   12      // 12 - получение ст. байта 
#define GET_MODBUS_WORD_LSB   13      // 13 - получение мл. байта  
#define GET_REG_CNT_MSB       14      // 14 - получение ст. байта адр. рег.
#define GET_REG_CNT_LSB       15      // 15 - получение мл. байта адр. рег.
#define CALC_CRC1             16      // 16 - расчет контр. суммы 1
#define CALC_CRC2             17      // 17 - расчет контр. суммы 2
#define GET_MODBUS_WORD       18      // 18 состояния кон.автомата

#define MODBUS_RHR_CMD       0x03     // read holding registers cmd id
#define MODBUS_RIR_CMD       0x04     // read input registers cmd id
#define MODBUS_WSR_CMD       0x06     // write single register cmd id

#define EXC_ILLEG_FUNC       0x01     // код ошибки при запросе функции не неподдерживаемой устройством 
#define EXC_REG_QTY	     0x03     // код ошибки при не верном числе регистров для чтения
#define EXC_CRC_ERR	     0x04     // код ошибки при подсчете CRC

#define max_regs_cnt         125      // макс. кол-во регистров для чтения за 1 раз

//==========================  VARIABLES AND PROTOTYPES  ========================

unsigned char wr_ptr = 0, rd_ptr = 0; // указатели чтения и записи в массив UART
// буфер для сохр. принятных команд
unsigned char rx_buf[128]; //= {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}; 

// флаги промежуточных состояний state-machine 
unsigned char reg_addr_flag = 0;  
unsigned char ID_flag = 0;     // 0 - осн. ID, 1 - широковещательный 
unsigned char reg_wr_flag = 0;
unsigned char rir_flag = 0;    // read input regs cmd flag
unsigned char reg_qty_flag = 0;
unsigned char get_crc_flag = 0;

unsigned char rx_byte;       // байт принятый с ПК
 
unsigned char answer = 0;    // тип ответа на команду с ПК
unsigned char rd_state = DETECT_DEV_ID; // машина состояний по умолчанию ждет обращения по id устройста modbus
unsigned int modbus_reg_addr = 0;       // адрес регистра для R/W по запросу от modbus мастера
unsigned int temp_buf = 0;              // временный буфер
 
unsigned int regs2read = 0;             // число регистров для чтения по команде modbus rhr
unsigned char  crc_buf[250];            // буфер для хранения байтов для расчета CRC16
unsigned int CRC16 = 0;                 // для хранения рассчитаной контрольной суммы
unsigned int addr_buf_1, addr_buf_2;

unsigned int reg_wr_data = 0;
unsigned int holding_register[125];  // буфер для хранения R/W переменных чтения, макс. число регистров - 124
unsigned int input_register[125];    // буфер для хранения Read-only переменных чтения, макс. число регистров - 124

void modbus_int_mode (unsigned char mode);     // упр. прерываниями MODBUS UART     
void modbus_refresh  (unsigned char cmd_type); // работа с пользовательскими пермеменными
unsigned char is_reg (unsigned int reg_addr);  // был ли прочитан регистр
void uart_send_hex (unsigned char ch);         // функция чтения 1 байта UART

#define DEFAULT_DEV_ID (unsigned char) 70
#define MODBUS_RX_LED LATBbits.LATB0 // LED_RX_485
#define MODBUS_TX_LED LATBbits.LATB1 // LED_TX_485

#include "dialtek_modbus.c"

  /* очистка массивов регистров */
  void modbus_init (void) {
   /// обнуление регистров
    
   for(unsigned char i = 0; i < 124; i++) 
   {
      holding_register[i] = 0;    // clearing RW resgisters 
      input_register[i]   = 0;    // clearing read-only resgisters 
   }
   }
  
  void modbus_reset(void)
  { 
   for(int i = 0; i < 126; i++) 
        rx_buf[i] = 0;
   
      //PIE1bits.RC1IE = 0;    // запрет UART recive // UART Int
      wr_ptr=0;                                                                   
      rd_ptr=0;       
      //PIE1bits.RC1IE = 1;    // разрешение UART recive   
  }
  
  /* был ли прочитан регистр */
  unsigned char is_reg (unsigned int reg_addr){  
   /// проверка чтения конкретного регистра
    
   unsigned char rd_status = 0;
   
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
  
  /* чтение 1 байта данных */
  void modbus_uart_byte (unsigned char rx_byte) {
  /// прием байта данных в буфер 
  wr_ptr++;               // инкремент счетчика записанных байт
  rx_buf[wr_ptr] = rx_byte;
  }
  
  /* заполнение буфера приемника */
  char get_rx_ch (void){   
  /// получение байта в массив чтения
    
   char rch;

   if (rd_ptr < wr_ptr) // буфер не пуст
   {
      rd_ptr++;                    // инкремент счетчика считаных байт
      rch = rx_buf[rd_ptr]; // сохр. элемента по индексу
   }
   else rch = 'x';   
   
   // запрет прерываний по UART на время сравнение указателей  
   // на счит. и запис. элементы массива
   //modbus_int_mode(0);
           
   if ((wr_ptr==rd_ptr) && (wr_ptr > 126)) // если буфер заполнен                                            
   {  
      wr_ptr=0;                                                                   
      rd_ptr=0;                                                       
   } 

   //modbus_int_mode(1);        // разрешение прерываний

return rch;
}
  
  /* расчет контрольной суммы */
  unsigned int modbus_CRC16(unsigned char buf[], unsigned int len) {
  /// расчет crc16
    
  unsigned int crc = 0xFFFF;
  //U8 crc_lsb, crc_msb;
  for (int pos = 0; pos < len; pos++)
  {
    crc ^= (unsigned int)buf[pos];          // XOR byte into least sig. byte of crc
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
  
  /* формирование и отправка ответа на команду записи одного регистра */
  void modbus_wsr_answer() { 
    /// ответ на команды записи в регистр
    
    // расчет CRC
    crc_buf[0] = (unsigned char) dev_id;
    crc_buf[1] = (unsigned char) MODBUS_WSR_CMD;
    crc_buf[2] = (unsigned char)(modbus_reg_addr >> 8);
    crc_buf[3] = (unsigned char)(modbus_reg_addr & 0x00ff);
    crc_buf[4] = (unsigned char)(reg_wr_data >> 8);
    crc_buf[5] = (unsigned char)(reg_wr_data & 0x00ff);
    CRC16 = modbus_CRC16(crc_buf, 6);

    //--------------------------------------------------------------------
    IEC1bits.U2RXIE = 0;      // DIS RS232 interrupt
    // отправка пакета мастеру
    TX_EN;
    uart_send_hex((unsigned char)dev_id); // ID устройства
    uart_send_hex((unsigned char)MODBUS_WSR_CMD);                     // код команды
    uart_send_hex((unsigned char)(modbus_reg_addr >> 8));             // ст. байт адреса регистра
    uart_send_hex((unsigned char)(modbus_reg_addr & 0x00ff));         // мл. байт адреса регистра
    uart_send_hex((unsigned char)(reg_wr_data >> 8));
    uart_send_hex((unsigned char)(reg_wr_data & 0x00ff));
     // отправка CRC
    uart_send_hex((unsigned char)(CRC16 >> 8));      // msb
    uart_send_hex((unsigned char)(CRC16 & 0x00ff));  // lsb   
    TX_DIS;
    IEC1bits.U2RXIE = 1;      // EN RS232 interrupt
    //--------------------------------------------------------------------
  }
  
  /* формирование и отправка ответа на команду чтения RW регистров */
  void modbus_rhr_answer() {
    
    /// ответ на команды чтения регистров
  	  addr_buf_2 = addr_buf_1;             // сохр. адрес без смещения в двух переменных	  
          // расчет CRC
          crc_buf[0] = dev_id;
          crc_buf[1] = MODBUS_RHR_CMD;
          crc_buf[2] = regs2read*2;
          
          unsigned char cnt = 3;      // величина смещения данных при расчете CRC

          for(unsigned char i = 0; i < regs2read; i++)
          { // заполнение буфера CRC для расчета
            crc_buf[cnt++] = (unsigned char)(holding_register[addr_buf_1] >> 8);
            crc_buf[cnt++] = (unsigned char)(holding_register[addr_buf_1] & 0x00ff);
            ++addr_buf_1;  
          }
            // расчет CRC  
          CRC16 = modbus_CRC16(crc_buf,(regs2read*2)+3);
          //--------------------------------------------------------------------
          // отправка пакета мастеру 
	  TX_EN;
          uart_send_hex((unsigned char)dev_id);   // ID устройства
          uart_send_hex((unsigned char)MODBUS_RHR_CMD);                       // код команды
          uart_send_hex((unsigned char)regs2read*2);                          // кол-во передаваемых байт 

          for(unsigned char i = 0; i < regs2read; i++)
          {   // отправка байт данных с инкрементом адреса
            uart_send_hex((unsigned char)(holding_register[addr_buf_2] >> 8));     // msb
            uart_send_hex((unsigned char)(holding_register[addr_buf_2] & 0x00ff)); // lsb
            ++addr_buf_2;
          }
          // отправка CRC
          uart_send_hex((unsigned char)(CRC16 >> 8));      // msb
          uart_send_hex((unsigned char)(CRC16 & 0x00ff));  // lsb  
	  TX_DIS;
          //--------------------------------------------------------------------
  
  }
 
  /* формирование и отправка ответа на команду чтения Read-only регистров */
  void modbus_rir_answer() {
    
    /// ответ на команды чтения input регистров
    
  	  addr_buf_2 = addr_buf_1;             // сохр. адрес без смещения в двух переменных	  
          // расчет CRC
          crc_buf[0] = dev_id;
          crc_buf[1] = MODBUS_RIR_CMD;
          crc_buf[2] = regs2read*2;
          
          unsigned char cnt = 3;      // величина смещения данных при расчете CRC

          for(unsigned char i = 0; i < regs2read; i++)
          { // заполнение буфера CRC для расчета
            crc_buf[cnt++] = (unsigned char)(input_register[addr_buf_1] >> 8);
            crc_buf[cnt++] = (unsigned char)(input_register[addr_buf_1] & 0x00ff);
            ++addr_buf_1;  
          }
            // расчет CRC  
          CRC16 = modbus_CRC16(crc_buf,(regs2read*2)+3);
          //--------------------------------------------------------------------
          // отправка пакета мастеру 
	  TX_EN;
          uart_send_hex((unsigned char)dev_id);   // ID устройства
          uart_send_hex((unsigned char)MODBUS_RIR_CMD);                       // код команды
          uart_send_hex((unsigned char)regs2read*2);                          // кол-во передаваемых байт 

          for(unsigned char i = 0; i < regs2read; i++)
          {   // отправка байт данных с инкрементом адреса
            uart_send_hex((unsigned char)(input_register[addr_buf_2] >> 8));     // msb
            uart_send_hex((unsigned char)(input_register[addr_buf_2] & 0x00ff)); // lsb
            ++addr_buf_2;
          }
          // отправка CRC
          uart_send_hex((unsigned char)(CRC16 >> 8));      // msb
          uart_send_hex((unsigned char)(CRC16 & 0x00ff));  // lsb   
	  __delay_ms(1);
	  TX_DIS;
          //--------------------------------------------------------------------
  
  }

  /* формирование и отправка ответа в случае ошибки запроса */
  void modbus_exc_rsp(unsigned char exc_code) {
   /// ответ мастеру, в случае возникновения ошибки запроса
	  
   crc_buf[0] = (unsigned char)(dev_id);     
   crc_buf[1] = (unsigned char)(0x80 | rx_byte); 
   crc_buf[2] = (unsigned char)(0x01); 
   CRC16 = modbus_CRC16(crc_buf,3); 
   TX_EN;		     
   uart_send_hex(dev_id);
   uart_send_hex(0x80 | rx_byte);
   uart_send_hex(exc_code);
   // отправка CRC
   uart_send_hex((unsigned char)(CRC16 >> 8));      // msb
   uart_send_hex((unsigned char)(CRC16 & 0x00ff));  // lsb 
   TX_DIS;
  }
   
  /* анализ контрольной суммы полученной посылки */
  void modbus_rx_CRC_check(unsigned char modbus_cmd) {
  /// заполнение массива CRC для рассчета и сравнения с прочитанным  
   // эл. 1,4,5 заполнены в rx_sm	
   crc_buf[0] = dev_id;
   crc_buf[2] = (unsigned char)(modbus_reg_addr >> 8);
   crc_buf[3] = (unsigned char)(modbus_reg_addr & 0x00ff);
   CRC16 = modbus_CRC16(crc_buf,6); 
   if(CRC16 == temp_buf) 
   { 
     answer = modbus_cmd;
     rd_state = DETECT_DEV_ID;
   }
   else 
   {
     rd_state = DETECT_DEV_ID;
     //modbus_exc_rsp(EXC_CRC_ERR);
   }
   
   get_crc_flag = 0;              // сброс флага расчета CRC16 
  }
  
  /* машина состояний анализа команд */
  void modbus_rx_sm (void) {
    /// обработка команд
    
    while(rd_ptr < wr_ptr) // буфер не пуст, получен байт 
    {                                     
       rx_byte = get_rx_ch();  
              
       switch(rd_state)  // конечный автомат состояний чтения команд
       {
       //====
         case DETECT_DEV_ID:              // ждем обращения к устройтсву по осн. ID
           if(rx_byte == dev_id) 
           {
                                          // получена команда обращения по текущему id устройтсва
               rd_state = GET_CMD_HEADER; // переход в состояние ожидания заголовка команды
           }
          break;
       //=====                          
         case GET_CMD_HEADER:             // анализ команды modbus
           switch (rx_byte)
           { 
             case MODBUS_RHR_CMD:                 // Read Holding Registers 
                  reg_addr_flag = 1;              // уст. флага чтения адреса регистра
                  regs2read = 0;
                  reg_wr_data = 0;
		  rir_flag = 0;
                  rd_state = GET_MODBUS_WORD_MSB; // переход в сост. получения двух байт с ПК
	     break;      
             //---- 
             case MODBUS_WSR_CMD:                 // запись в регистр
                  reg_addr_flag = 1;              // уст. флага чтения адреса регистра
                  reg_wr_flag   = 1;              // уст. флага записи в регистр 
                  regs2read = 0;
                  reg_wr_data = 0;
		  rir_flag = 0;
                  rd_state = GET_MODBUS_WORD_MSB; // переход в сост. получения двух байт с ПК 
             break; 
	     //---- 
             case MODBUS_RIR_CMD:                 // Read Input Registers 
                  reg_addr_flag = 1;              // уст. флага чтения адреса регистр
                  regs2read = 0;
                  reg_wr_data = 0;
		  rir_flag = 1;
                  rd_state = GET_MODBUS_WORD_MSB; // переход в сост. получения двух байт с ПК 
             break; 
             //---- 
             // возврат в сост. анализ id устройства в случае ошибки  
             default: 
		  //modbus_exc_rsp(EXC_ILLEG_FUNC);    
		  rd_state = DETECT_DEV_ID;	     
           }

         break;
        //=====
         case GET_MODBUS_WORD_MSB:              // получение ст. байта
             temp_buf = (unsigned int)rx_byte;           // сохр. ст. байт
             temp_buf = temp_buf << 8;
             rd_state = GET_MODBUS_WORD_LSB;    // переход в сост. чтения мл. байта
         break;
         //=====
         case GET_MODBUS_WORD_LSB:              // получение мл. байта 
             temp_buf |= (unsigned int)rx_byte;          // сохр. мл. байт
             /// анализ флагов для дальнейших действий
             if(reg_addr_flag)                 // флаг принятия байт адреса?
             {
               modbus_reg_addr = temp_buf;     // сохр. адреса начального регистра для чтения
               reg_addr_flag = 0;              // сброс флага чтения адреса
               if(reg_wr_flag) reg_qty_flag = 0; // сброс флага приема числа регистров для чтения если была команда записи             
               else reg_qty_flag = 1;            // уст. флага приема числа регистров для чтения если был запрос
               rd_state = GET_MODBUS_WORD_MSB;   // переход в сост. чтения 2 байт кол-ва регистров для чтения
               temp_buf = 0;                     // обнуление временного буфера
               break;
             }
             //---
             if(reg_wr_flag)                   // флаг записи в регистр?
             { 
                reg_wr_data = temp_buf;        // сохр. значения для записи
                reg_wr_flag = 0;               // сброс флага записи в регистр
                get_crc_flag = MODBUS_WSR_CMD; // уст. кода расчета CRC для команды записи
                rd_state = GET_MODBUS_WORD_MSB;// переход в сост. чтения 2 байт CRC
                break;
             }
             //---
             if(reg_qty_flag)                  // флаг приема ко-ва регистров для чтения?
             { 
               if(temp_buf < max_regs_cnt)     // проверка на предел числа регистров для чтения
               {  // ок
                regs2read = temp_buf;           // сохранение числа регистров для чтения
		get_crc_flag = (rir_flag == 0 ? MODBUS_RHR_CMD : MODBUS_RIR_CMD); // уст. кода расчета CRC для команды чтения
                rd_state = GET_MODBUS_WORD_MSB; // переход в сост. чтения 2 байт CRC
               }
                 // ошибка, возврат в сост. чтения id устройства
               else 
	       {
		 rd_state = DETECT_DEV_ID; 
		 //modbus_exc_rsp(EXC_REG_QTY);        
	       }
               reg_qty_flag = 0;                // сброс флага чтения кол-ва регистров       
               break;
             }
	     //---
	     switch(get_crc_flag)
	     {  // формирование массива для рассчета CRC16
		case MODBUS_WSR_CMD:
		  crc_buf[1] = (unsigned char) MODBUS_WSR_CMD;	
		  crc_buf[4] = (unsigned char)(reg_wr_data >> 8);
                  crc_buf[5] = (unsigned char)(reg_wr_data & 0x00ff);
		  modbus_rx_CRC_check(MODBUS_WSR_CMD);
		break;
		//---
		case MODBUS_RIR_CMD:
		  crc_buf[1] = (unsigned char) MODBUS_RIR_CMD;	
                  crc_buf[4] = (unsigned char)(regs2read >> 8);
                  crc_buf[5] = (unsigned char)(regs2read & 0x00ff);
		  modbus_rx_CRC_check(MODBUS_RIR_CMD);
		break;
		//---
		case MODBUS_RHR_CMD:
		  crc_buf[1] = (unsigned char) MODBUS_RHR_CMD;	
                  crc_buf[4] = (unsigned char)(regs2read >> 8);
                  crc_buf[5] = (unsigned char)(regs2read & 0x00ff);
		  modbus_rx_CRC_check(MODBUS_RHR_CMD);
		break;
		//---
	        default: rd_state = DETECT_DEV_ID; 
	     }     
         break; 
         //=====
          default:  rd_state = DETECT_DEV_ID; 
        } // switch
    }  // while 

  }
  
  /* работа с регистрами */
  void modbus_poll()  {
    /// update modbus regs and vars, send answer to master
    addr_buf_1 = modbus_reg_addr - 1000; // избавляемся от смещекния в адресе
    
    //  чтение R/W регистров
    if(answer == MODBUS_RHR_CMD) 
    {    
	 MODBUS_RX_LED = 1;
	 MODBUS_TX_LED = 1;
         modbus_refresh(MODBUS_RHR_CMD);
         modbus_rhr_answer();  
	 answer = 0;   // сброс флага завершения ответа на запрос   
	 modbus_reset(); 
	 
	 __delay_ms(10);
         MODBUS_RX_LED = 0;
	 MODBUS_TX_LED = 0;
    }
//--------------------------------------------------------------------
    // запись в регистр
    if(answer == MODBUS_WSR_CMD) 
    {
	 MODBUS_RX_LED = 1;
	 MODBUS_TX_LED = 1;
	 
         holding_register[addr_buf_1] = reg_wr_data; 
         modbus_refresh(MODBUS_WSR_CMD);
         modbus_wsr_answer();     
	 answer = 0;   // сброс флага завершения ответа на запрос   
	 modbus_reset();

         MODBUS_RX_LED = 0;
	 MODBUS_TX_LED = 0;
    }  
//--------------------------------------------------------------------
    // чтение Read-only регистров
    if(answer == MODBUS_RIR_CMD) 
    {    
	 MODBUS_RX_LED = 1;
	 MODBUS_TX_LED = 1;
	 
         modbus_refresh(MODBUS_RIR_CMD);
         modbus_rir_answer();   
	 answer = 0;   // сброс флага завершения ответа на запрос   
	 modbus_reset();
	 
	 __delay_ms(10);
         MODBUS_RX_LED = 0;
	 MODBUS_TX_LED = 0;
    }
 //--------------------------------------------------------------------
  }
 


