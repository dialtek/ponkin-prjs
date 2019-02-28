/*                D I A L T E K    M O D B U S   R T U   v 3.1               */

/* ЗАГОЛОВКИ, ПЕРЕМЕННЫЕ И СЛУЖЕБНЫЕ ФУНКЦИИ */

/* изменения необходимо вносить в файл dialtek_modbus.с */

///================================ STATE MACHINE ===============================

#define MODBUS_RHR_CMD       0x03     // read holding registers cmd id
#define MODBUS_RIR_CMD       0x04     // read input registers cmd id
#define MODBUS_WSR_CMD       0x06     // write single register cmd id

#define max_regs_cnt         125      // макс. кол-во регистров для чтения за 1 раз

//==========================  VARIABLES AND PROTOTYPES  ========================

volatile unsigned int rx_buf_ptr = 0; // указатель записи в массив UART
// буфер для сохр. принятных команд
unsigned char rx_buf[512];

unsigned char modbus_cmd = 0; // 0x03 | 0x06 | 0x04

unsigned char rx_byte;        // байт принятый с ПК
 
unsigned char answer = 0;     // тип ответа на команду с ПК
unsigned int modbus_reg_addr = 0;       // адрес регистра для R/W по запросу от modbus мастера
unsigned int addr_buf_1 = 0, addr_buf_2 = 0;
unsigned int regs2read = 0;             // число регистров для чтения по команде modbus rhr
unsigned int CRC16 = 0;			// полученная контрольная сумма
unsigned char crc_buf[250];             // буфер для хранения байтов для расчета CRC16
unsigned char modbus_id = 0;		// буфер для хранения ID из запроса мастера
unsigned int reg_wr_data = 0;
volatile unsigned int holding_register[125];  // буфер для хранения R/W переменных чтения, макс. число регистров - 124
volatile unsigned int input_register[125];    // буфер для хранения Read-only переменных чтения, макс. число регистров - 124

unsigned char rx_flag = 0, timer_state = 0;

void modbus_int_mode (unsigned char mode);     // упр. прерываниями MODBUS UART     
void modbus_refresh  (unsigned char cmd_type); // работа с пользовательскими пермеменными
unsigned char is_reg (unsigned int reg_addr);  // был ли прочитан регистр
void U1_send_byte (unsigned char ch);          // функция чтения 1 байта UART
void UART1_init();
void Timer9_init(unsigned long);

#define DEFAULT_DEV_ID (unsigned char) 70
#define MODBUS_RX_LED LATBbits.LATB0 // LED_RX_485
#define MODBUS_TX_LED LATBbits.LATB1 // LED_TX_485

#include "dialtek_modbus.c"

  /* очистка массивов регистров */
  void modbus_init (void) {
   /// обнуление регистров
    
   for(unsigned char i = 0; i < 125; i++) 
   {
      holding_register[i] = 0;   // clearing RW resgisters 
      input_register[i] = 0;     // clearing read-only resgisters 
   }
   
   modbus_reset();
   }
  
/* сброс modbus приемника */
  void modbus_reset()
  { 
   for(int i = 0; i < 512; i++) 
        rx_buf[i] = 0;
   
   rx_buf_ptr = 0;
   rx_flag = 0;

  }
  
  /* был ли прочитан регистр */
  unsigned char is_reg (unsigned int reg_addr){  
   /// проверка чтения конкретного регистра
    
   unsigned char rd_status = 0;
   
      for(unsigned int t = modbus_reg_addr; t <= regs2read; t++)
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
    crc_buf[0] = (modbus_id == dev_id) ? dev_id : com_dev_id;
    crc_buf[1] = (unsigned char) MODBUS_WSR_CMD;
    crc_buf[2] = (unsigned char)(modbus_reg_addr >> 8);
    crc_buf[3] = (unsigned char)(modbus_reg_addr & 0x00ff);
    crc_buf[4] = (unsigned char)(reg_wr_data >> 8);
    crc_buf[5] = (unsigned char)(reg_wr_data & 0x00ff);
    CRC16 = modbus_CRC16(crc_buf, 6);

    //--------------------------------------------------------------------
    // отправка пакета мастеру
    TX_EN;
    U1_send_byte((modbus_id == dev_id) ? dev_id : com_dev_id); // ID устройства
    U1_send_byte((unsigned char)MODBUS_WSR_CMD);                     // код команды
    U1_send_byte((unsigned char)(modbus_reg_addr >> 8));             // ст. байт адреса регистра
    U1_send_byte((unsigned char)(modbus_reg_addr & 0x00ff));         // мл. байт адреса регистра
    U1_send_byte((unsigned char)(reg_wr_data >> 8));
    U1_send_byte((unsigned char)(reg_wr_data & 0x00ff));
     // отправка CRC
    U1_send_byte((unsigned char)(CRC16 >> 8));      // msb
    U1_send_byte((unsigned char)(CRC16 & 0x00ff));  // lsb 
    TX_DIS;
    //--------------------------------------------------------------------
  }
  
  /* формирование и отправка ответа на команду чтения RW регистров */
  void modbus_rhr_answer() {
    
    /// ответ на команды чтения регистров
          addr_buf_1 = modbus_reg_addr; 
  	  addr_buf_2 = addr_buf_1;             // сохр. адрес в двух переменных	  
          // расчет CRC
          crc_buf[0] = (modbus_id == dev_id) ? dev_id : com_dev_id;
          crc_buf[1] = MODBUS_RHR_CMD;
          crc_buf[2] = regs2read*2;
          
          unsigned char cnt = 3;      // величина смещения данных при расчете CRC

          for(unsigned char j = 0; j < regs2read;j++)
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
          U1_send_byte((modbus_id == dev_id) ? dev_id : com_dev_id);   // ID устройства
          U1_send_byte((unsigned char)MODBUS_RHR_CMD);                       // код команды
          U1_send_byte((unsigned char)regs2read*2);                          // кол-во передаваемых байт 

          for(unsigned char i = 0; i < regs2read; i++)
          {   // отправка байт данных с инкрементом адреса
            U1_send_byte((unsigned char)(holding_register[addr_buf_2] >> 8));     // msb
            U1_send_byte((unsigned char)(holding_register[addr_buf_2] & 0x00ff)); // lsb
            ++addr_buf_2;
          }
          // отправка CRC
          U1_send_byte((unsigned char)(CRC16 >> 8));      // msb
          U1_send_byte((unsigned char)(CRC16 & 0x00ff));  // lsb  
	  TX_DIS;
          //--------------------------------------------------------------------
  
  }
 
  /* формирование и отправка ответа на команду чтения Read-only регистров */
  void modbus_rir_answer() {
    
    /// ответ на команды чтения input регистров
    
  	  addr_buf_1 = modbus_reg_addr; 
  	  addr_buf_2 = addr_buf_1;             // сохр. адрес в двух переменных		  
          // расчет CRC
          crc_buf[0] = (modbus_id == dev_id) ? dev_id : com_dev_id;
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
          U1_send_byte((modbus_id == dev_id) ? dev_id : com_dev_id);   // ID устройства
          U1_send_byte((unsigned char)MODBUS_RIR_CMD);                       // код команды
          U1_send_byte((unsigned char)regs2read*2);                          // кол-во передаваемых байт 

          for(unsigned char i = 0; i < regs2read; i++)
          {   // отправка байт данных с инкрементом адреса
            U1_send_byte((unsigned char)(input_register[addr_buf_2] >> 8));     // msb
            U1_send_byte((unsigned char)(input_register[addr_buf_2] & 0x00ff)); // lsb
            ++addr_buf_2;
          }
          // отправка CRC
          U1_send_byte((unsigned char)(CRC16 >> 8));      // msb
          U1_send_byte((unsigned char)(CRC16 & 0x00ff));  // lsb   
	  TX_DIS;
          //--------------------------------------------------------------------
  
  }

  /* анализ контрольной суммы полученной посылки */
  void modbus_rx_CRC_check(unsigned char modbus_cmd) {
  /// заполнение массива CRC для рассчета и сравнения с прочитанным  
   unsigned int CRC16_calc = 0;  // рассчетная контрольная сумма
   
   modbus_reg_addr = (rx_buf[2] << 8) | rx_buf[3]; // get starting reg addr
   
   crc_buf[0] = (modbus_id == dev_id) ? dev_id : com_dev_id;
   crc_buf[2] = (unsigned char)(modbus_reg_addr >> 8);
   crc_buf[3] = (unsigned char)(modbus_reg_addr & 0x00ff);  
   
   switch(modbus_cmd)
   {
    case MODBUS_WSR_CMD:
	reg_wr_data	= (rx_buf[4] << 8) | rx_buf[5]; // get data to write into reg
	
	crc_buf[1] = (unsigned char) MODBUS_WSR_CMD;
	crc_buf[4] = (unsigned char)(reg_wr_data >> 8);
	crc_buf[5] = (unsigned char)(reg_wr_data & 0x00ff);
     break;
     //----
     case MODBUS_RHR_CMD:
	regs2read	= (rx_buf[4] << 8) | rx_buf[5]; // get number of regs to read
    
	crc_buf[1] = (unsigned char) MODBUS_RHR_CMD;
	crc_buf[4] = (unsigned char)(regs2read >> 8);
	crc_buf[5] = (unsigned char)(regs2read & 0x00ff);
     break;
     //----
     case MODBUS_RIR_CMD:
	regs2read	= (rx_buf[4] << 8) | rx_buf[5]; // get number of regs to read
    
	crc_buf[1] = (unsigned char) MODBUS_RIR_CMD;
	crc_buf[4] = (unsigned char)(regs2read >> 8);
	crc_buf[5] = (unsigned char)(regs2read & 0x00ff);
     break;
     //----
     default: modbus_reset();
   }
   
   CRC16 = (rx_buf[6] << 8) | rx_buf[7]; // get CRC16 from rx msg
   CRC16_calc = modbus_CRC16(crc_buf,6); // calc CRC16  

   if(CRC16_calc == CRC16) 
     answer = modbus_cmd;
   else
     modbus_reset();
  }
  
  /* анализа команд */
  void modbus_rx_sm (void) {
  /// обработка команд
	  
  if(rx_flag)			// state 1, rx timer overflows
  {  
   if(rx_buf_ptr == 8)		// state 2, rx buf has 8 bytes ?
   {   
    modbus_id = rx_buf[0];      // get device ID from master msg
		   
    if((modbus_id == dev_id) || (modbus_id == com_dev_id))     // state 3, ID check 
    {// ID OK

	switch(rx_buf[1])	// state 4, rx buf parsing
	{ 
	  case MODBUS_WSR_CMD:
	    modbus_rx_CRC_check(MODBUS_WSR_CMD); // write single reg cmd received
	  break;
	  //----
	  case MODBUS_RIR_CMD:
	   modbus_rx_CRC_check(MODBUS_RIR_CMD);  // read input reg cmd received
	  break;
	  //----
	  case MODBUS_RHR_CMD:
	   modbus_rx_CRC_check(MODBUS_RHR_CMD); // read holding reg cmd received
	  break;
	  //----
	  default: modbus_reset();		// unexpected cmd, reset
	}     
    } // if(my ID or common ID) 
    else modbus_reset();
   }  // if(rx_buf_ptr == 8)
   else modbus_reset();
   }  // if(rx_flag) 
  }//func
  
  /* работа с регистрами */
  void modbus_poll()  {
    /// update modbus regs and vars, send answer to master
   
    modbus_rx_sm(); // parse rx buffer

    //  чтение R/W регистров
    if(answer == MODBUS_RHR_CMD) 
    {    
	 MODBUS_RX_LED = 1;
	 MODBUS_TX_LED = 1;
         modbus_rhr_answer();  
	 modbus_reset(); 
	 answer = 0;   // сброс флага завершения ответа на запрос  
	 modbus_refresh(MODBUS_RHR_CMD);

         MODBUS_RX_LED = 0;
	 MODBUS_TX_LED = 0;
    }
//--------------------------------------------------------------------
    // запись в регистр
    if(answer == MODBUS_WSR_CMD) 
    {
	 MODBUS_RX_LED = 1;
	 MODBUS_TX_LED = 1;
	 
         holding_register[modbus_reg_addr] = reg_wr_data; 
         modbus_wsr_answer();  
	 modbus_reset();
	 answer = 0;   // сброс флага завершения ответа на запрос  
	 modbus_refresh(MODBUS_WSR_CMD);

         MODBUS_RX_LED = 0;
	 MODBUS_TX_LED = 0;
    }  
//--------------------------------------------------------------------
    // чтение Read-only регистров
    if(answer == MODBUS_RIR_CMD) 
    {    
	 MODBUS_RX_LED = 1;
	 MODBUS_TX_LED = 1;
	
         modbus_rir_answer();  
	 modbus_reset();
	 answer = 0;   // сброс флага завершения ответа на запрос 
	 modbus_refresh(MODBUS_RIR_CMD);  
 
         MODBUS_RX_LED = 0;
	 MODBUS_TX_LED = 0;
    }
 //--------------------------------------------------------------------
  }