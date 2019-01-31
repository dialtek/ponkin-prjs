/*                D I A L T E K    M O D B U S   R T U   v 3.0                */

/* README */
/*
„лЯ работы библиотеки MODBUS RTU необходимо:

1. настроить прерывание UART RX по приему одного байта 

2. вставить в обработчик прерываниЯ UART RX функцию modbus_uart_byte, например:
      modbus_uart_byte(MDR_UART1->DR); или modbus_uart_byte(U1RXREG);

3. создать функцию отправки одного байта UART TX следующего вида:
      void uart_send_byte(unsigned char hex_data){ }

4. поместить функцию modbus_rx_sm() в обработчик прерываниЯ по таймеру (’ >= 1 мс) или цикл while(1)

5. поместить функцию modbus_init() в main()

6. поместить функцию modbus_poll() в цикл while(1) (T >= 1 мс)

7. настроить порты длЯ управлениЯ разрешением работы приемника (если необходимо) и передатчика в поле RS485 EN/DIS DEFINE

8. настроить аттрибуты устройства в поле HARDWARE INFO 

9. заполнить функцию modbus_int_mode() кодом с разрешением и запретом прерываний UART RX

10.составить регистровую карту устройства в фукции modbus_refresh() :
      A) при чтении регистров, выполнЯетсЯ код if(cmd_type == MODBUS_RHR_CMD)
      B) при записи регистров, выполнЯетсЯ код if(cmd_type == MODBUS_WSR_CMD)

11. при необходимости использованиЯ своих функции внутри modbus_refresh(), следует создать их прототипы в поле PROTOTYPES  
*/

#include "dialtek_modbus.h" 

//==========================  VARIABLES AND PROTOTYPES  ========================

volatile unsigned char rx_buf_ptr = 0; // указатель записи в массив UART
// буфер для сохр. принятных команд
unsigned char rx_buf[32];

unsigned char modbus_cmd = 0; // 0x03 | 0x06 | 0x04

unsigned char rx_byte;       // байт принятый с ПК
 
unsigned char answer = 0;    // тип ответа на команду с ПК
unsigned int modbus_reg_addr = 0;       // адрес регистра для R/W по запросу от modbus мастера
unsigned int addr_buf_1 = 0, addr_buf_2 = 0;
unsigned int regs2read = 0;             // число регистров для чтения по команде modbus rhr
unsigned int CRC16 = 0;			// полученная контрольная сумма
unsigned char  crc_buf[250];            // буфер для хранения байтов для расчета CRC16

unsigned int reg_wr_data = 0;
unsigned int holding_register[125];  // буфер для хранения R/W переменных чтения, макс. число регистров - 124
unsigned int input_register[125];    // буфер для хранения Read-only переменных чтения, макс. число регистров - 124

unsigned char rx_flag = 0, timer_state = 0;

/*############################################################################*/ 
/*                   ПОЛЯ, ИЗМЕНЯЕМЫЕ ПОЛЬЗОВАТЕЛЕМ !!!                       */ 

/* RS485 EN/DIS DEFINE */

#define TX_EN  LATDbits.LATD2=1 
#define TX_DIS LATDbits.LATD2=0

/* HARDWARE INFO */

 // unsigned char com_dev_id    = 247;              // MODBUS ID устройства длЯ широковещательного режима, лучше не трогать 
  unsigned char dev_id        = 3;                  // MODBUS ID устройства   <<<<<<<<<<======== ID
  unsigned char firmware_ver  = 15;                 // версиЯ прошивки текущего устройства
  unsigned char device_family = 5;                  // код семейства устройств

/* PROTOTYPES */
 
 void SPI2_PUT_int (unsigned int buf); 
 void Modbus_SPI_R_WR (unsigned int hold_reg_data, unsigned int hold_reg_addr, unsigned char R_Wr, unsigned char counter); 
 void SPI_TO_CPLD_SEND (unsigned int Data,unsigned int reg_index);
 void Dev_ID_init();
 
 
 //============================================================================
 /* сброс modbus приемника */
  void modbus_reset()
  { 
   for(int i = 0; i < 32; i++) 
        rx_buf[i] = 0;
   
   rx_buf_ptr = 0;
   rx_flag = 0;

  }
  
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
  
  /* чтение 1 байта данных */
//  void modbus_uart_byte (unsigned char rx_byte) {
//  /// прием байта данных в буфер 
//  wr_ptr++;               // инкремент счетчика записанных байт
//  rx_buf[wr_ptr & 0x0f] = rx_byte;
//  }
   
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
    // отправка пакета мастеру
    TX_EN;
    uart_send_byte((unsigned char)dev_id); // ID устройства
    uart_send_byte((unsigned char)MODBUS_WSR_CMD);                     // код команды
    uart_send_byte((unsigned char)(modbus_reg_addr >> 8));             // ст. байт адреса регистра
    uart_send_byte((unsigned char)(modbus_reg_addr & 0x00ff));         // мл. байт адреса регистра
    uart_send_byte((unsigned char)(reg_wr_data >> 8));
    uart_send_byte((unsigned char)(reg_wr_data & 0x00ff));
     // отправка CRC
    uart_send_byte((unsigned char)(CRC16 >> 8));      // msb
    uart_send_byte((unsigned char)(CRC16 & 0x00ff));  // lsb 
    TX_DIS;
    //--------------------------------------------------------------------
  }
  
  /* формирование и отправка ответа на команду чтения RW регистров */
  void modbus_rhr_answer() {
    
    /// ответ на команды чтения регистров
          addr_buf_1 = modbus_reg_addr; 
  	  addr_buf_2 = addr_buf_1;             // сохр. адрес в двух переменных	  
          // расчет CRC
          crc_buf[0] = dev_id;
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
          uart_send_byte((unsigned char)dev_id);   // ID устройства
          uart_send_byte((unsigned char)MODBUS_RHR_CMD);                       // код команды
          uart_send_byte((unsigned char)regs2read*2);                          // кол-во передаваемых байт 

          for(unsigned char i = 0; i < regs2read; i++)
          {   // отправка байт данных с инкрементом адреса
            uart_send_byte((unsigned char)(holding_register[addr_buf_2] >> 8));     // msb
            uart_send_byte((unsigned char)(holding_register[addr_buf_2] & 0x00ff)); // lsb
            ++addr_buf_2;
          }
          // отправка CRC
          uart_send_byte((unsigned char)(CRC16 >> 8));      // msb
          uart_send_byte((unsigned char)(CRC16 & 0x00ff));  // lsb  
	  TX_DIS;
          //--------------------------------------------------------------------
  
  }
 
  /* формирование и отправка ответа на команду чтения Read-only регистров */
  void modbus_rir_answer() {
    
    /// ответ на команды чтения input регистров
    
  	  addr_buf_1 = modbus_reg_addr; 
  	  addr_buf_2 = addr_buf_1;             // сохр. адрес в двух переменных		  
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
          uart_send_byte((unsigned char)dev_id);   // ID устройства
          uart_send_byte((unsigned char)MODBUS_RIR_CMD);                       // код команды
          uart_send_byte((unsigned char)regs2read*2);                          // кол-во передаваемых байт 

          for(unsigned char i = 0; i < regs2read; i++)
          {   // отправка байт данных с инкрементом адреса
            uart_send_byte((unsigned char)(input_register[addr_buf_2] >> 8));     // msb
            uart_send_byte((unsigned char)(input_register[addr_buf_2] & 0x00ff)); // lsb
            ++addr_buf_2;
          }
          // отправка CRC
          uart_send_byte((unsigned char)(CRC16 >> 8));      // msb
          uart_send_byte((unsigned char)(CRC16 & 0x00ff));  // lsb   
	  TX_DIS;
          //--------------------------------------------------------------------
  
  }

  /* анализ контрольной суммы полученной посылки */
  void modbus_rx_CRC_check(unsigned char modbus_cmd) {
  /// заполнение массива CRC для рассчета и сравнения с прочитанным  
   unsigned int CRC16_calc = 0;  // рассчетная контрольная сумма
   
   modbus_reg_addr = (rx_buf[2] << 8) | rx_buf[3]; // get starting reg addr
   
   crc_buf[0] = dev_id;
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
   if(rx_buf_ptr >= 8)		// state 2, rx buf has 8 bytes ?
   {   
    if(rx_buf[0] == dev_id)     // state 3, ID check 
    {// ID OK
	modbus_cmd = rx_buf[1]; // get modbus cmd 

	switch(modbus_cmd)	// state 4, rx buf parsing
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
    } // if(my ID) 
    else modbus_reset();
   }  // if(rx_buf_ptr == 8)
   else modbus_reset();
   }  // if(rx_flag) 
  }//func
  
  /* парсинг команды и работа с регистрами */
  void modbus_poll()  {
    /// update modbus regs and vars, send answer to master
   
    modbus_rx_sm(); // parse rx buffer

    // если команда - чтение R/W регистров
    if(answer == MODBUS_RHR_CMD) 
    {
         modbus_refresh(MODBUS_RHR_CMD);
         modbus_rhr_answer();  
	 answer = 0;     // сброс флага завершения ответа на запрос
	 modbus_reset(); 
    }
//--------------------------------------------------------------------
    // если команда - запись в регистр
    if(answer == MODBUS_WSR_CMD) 
    {
         holding_register[addr_buf_1] = reg_wr_data; 
         modbus_refresh(MODBUS_WSR_CMD);
         modbus_wsr_answer(); 
	 answer = 0;     // сброс флага завершения ответа на запрос
	 modbus_reset();
    }  
//--------------------------------------------------------------------
    // если команда - чтение Read-only регистров
    if(answer == MODBUS_RIR_CMD) 
    {
         modbus_refresh(MODBUS_RIR_CMD);
         modbus_rir_answer();  
	 answer = 0;     // сброс флага завершения ответа на запрос
	 modbus_reset();
    }
//--------------------------------------------------------------------    

  }

 //============================================================================
 /* USER FUNCS */
  
  void modbus_int_mode (unsigned char mode)  {      // управление прерыванием UART RX
  
    if(mode == 1) // разрешение прерываний RX UART MODBUS
    {
      IEC0bits.U1RXIE = 1; // en UART1 RX interrupt   
    }
    else         // запрет прерываний RX UART MODBUS
    {
      IEC0bits.U1RXIE = 0; // dis UART1 RX interrupt   
    }
  }
  
  void modbus_refresh(unsigned char cmd_type){      // работа с регистрами
    
  /// RW регистров, TODO - обновление переменных перед отправкой мастеру       
  if(cmd_type == MODBUS_RHR_CMD)
   {   
      
//      if(is_reg(10))
//      {     
//      }
      
       // holding_register[0] = (unsigned int) delay_chanel_1_LSB;
//        holding_register[1] = (unsigned int) delay_chanel_1_MSB;  
//        holding_register[2] = (unsigned int) width_chanel_1_LSB; 
//        holding_register[3] = (unsigned int) width_chanel_1_MSB;   
//        holding_register[4] = (unsigned int) delay_chanel_2_LSB;   
//        holding_register[5] = (unsigned int) delay_chanel_2_MSB;     
//        holding_register[6] = (unsigned int) width_chanel_2_LSB;    
//        holding_register[7] = (unsigned int) width_chanel_2_MSB;  
//        holding_register[8] = (unsigned int) delay_chanel_3_LSB; 
//        holding_register[9] = (unsigned int) delay_chanel_3_MSB;  
//        holding_register[10] = (unsigned int) width_chanel_3_LSB; 
//        holding_register[11] = (unsigned int) width_chanel_3_MSB;                                       
//        holding_register[12] = (unsigned int) delay_chanel_4_LSB; 
//        holding_register[13] = (unsigned int) delay_chanel_4_MSB; 
//        holding_register[14] = (unsigned int) width_chanel_4_LSB;
//        holding_register[15] = (unsigned int) width_chanel_4_MSB;
//        
//        holding_register[16] = (unsigned int) delay_chanel_5_LSB;
//        holding_register[17] = (unsigned int) delay_chanel_5_MSB;  
//        holding_register[18] = (unsigned int) width_chanel_5_LSB; 
//        holding_register[19] = (unsigned int) width_chanel_5_MSB;   
//        holding_register[20] = (unsigned int) delay_chanel_6_LSB;   
//        holding_register[21] = (unsigned int) delay_chanel_6_MSB;     
//        holding_register[22] = (unsigned int) width_chanel_6_LSB;    
//        holding_register[23] = (unsigned int) width_chanel_6_MSB;  
//        holding_register[24] = (unsigned int) delay_chanel_7_LSB; 
//        holding_register[25] = (unsigned int) delay_chanel_7_MSB;  
//        holding_register[26] = (unsigned int) width_chanel_7_LSB; 
//        holding_register[27] = (unsigned int) width_chanel_7_MSB;                                       
//        holding_register[28] = (unsigned int) delay_chanel_8_LSB; 
//        holding_register[29] = (unsigned int) delay_chanel_8_MSB; 
//        holding_register[30] = (unsigned int) width_chanel_8_LSB;
//        holding_register[31] = (unsigned int) width_chanel_8_MSB;
//        
//        holding_register[32] = (unsigned int) enable_chanel_1;                  // EN 1 chanel
//        holding_register[33] = (unsigned int) invert_chanel_1;                  // INV 1 chanel
//        holding_register[34] = (unsigned int) enable_chanel_2;                  // EN 2 chanel
        holding_register[35] = (unsigned int) invert_chanel_2;                  // INV 2 chanel
        holding_register[36] = (unsigned int) enable_chanel_3;                  // EN 3 chanel
        holding_register[37] = (unsigned int) invert_chanel_3;                  // INV 3 chanel
        holding_register[38] = (unsigned int) enable_chanel_4;                  // EN 4 chanel
        holding_register[39] = (unsigned int) invert_chanel_4;                  // INV 4 chanel
        holding_register[40] = (unsigned int) Control_1;                        // Control CPLD 1
        holding_register[41] = (unsigned int) enable_chanel_5;                  // EN 5 chanel
        holding_register[42] = (unsigned int) invert_chanel_5;                  // INV 5 chanel
        holding_register[43] = (unsigned int) enable_chanel_6;                  // EN 6 chanel
        holding_register[44] = (unsigned int) invert_chanel_6;                  // INV 6 chanel
        holding_register[45] = (unsigned int) enable_chanel_7;                  // EN 7 chanel
        holding_register[46] = (unsigned int) invert_chanel_7;                  // INV 7 chanel
        holding_register[47] = (unsigned int) enable_chanel_8;                  // EN 8 chanel
        holding_register[48] = (unsigned int) invert_chanel_8;                  // INV 8 chanel
        holding_register[49] = (unsigned int) Control_2;                        // Control CPLD 2
        holding_register[50] = (unsigned int) clk_DIR;                          // CLK switch
        holding_register[51] = (unsigned int) start_DIR;                        // START switch
        holding_register[52] = (unsigned int) start_en;                         // local START_EN
        holding_register[53] = (unsigned int) start_inv;                        // local START_INV
        holding_register[54] = (unsigned int) delay_start_LSB;                  // DATA of local start counter 
        holding_register[55] = (unsigned int) delay_start_MSB;                  //
        holding_register[56] = (unsigned int) width_start_LSB;                  //  
        holding_register[57] = (unsigned int) width_start_MSB;   
        holding_register[58] = (unsigned int) SPI_BUF_MISO;
   }         
   //-------------------------------------------------------------------------//
  /// —тение Read-only регистров, TODO - обновление переменных перед отправкой мастеру   
   
   if(cmd_type == MODBUS_RIR_CMD)
   {   
       input_register[0] = (unsigned int)dev_id;       
       input_register[1] = (unsigned int)device_family;
       input_register[2] = (unsigned int)firmware_ver;
   } 
   //-------------------------------------------------------------------------//
   /// TODO - получение новых значений от мастера
   //  addr_buf_1 = адрес регистра, в который идет запись (1000 = 0, 1001 = 1 и тд)
   if(cmd_type == MODBUS_WSR_CMD) 
   {  // анализ регистра записи 
      switch(modbus_reg_addr) 
      {  
        case 0: // reg 4 - set output
                delay_chanel_1_LSB = holding_register[0];
                SPI_TO_CPLD_SEND (delay_chanel_1_LSB, 0);
                break;
        case 1: // reg 4 - set output
                delay_chanel_1_MSB = holding_register[1]; 
                SPI_TO_CPLD_SEND (delay_chanel_1_MSB, 1);
                break;
        //---------
        case 2: // reg 7 - set voltage
                width_chanel_1_LSB = holding_register[2];
                SPI_TO_CPLD_SEND (width_chanel_1_LSB, 2);
                break;     
        case 3: // reg 7 - set voltage
                width_chanel_1_MSB = holding_register[3];
                SPI_TO_CPLD_SEND (width_chanel_1_MSB, 3);
                break;   
        case 4: // reg 7 - set voltage
                delay_chanel_2_LSB = holding_register[4];
                SPI_TO_CPLD_SEND (delay_chanel_2_LSB, 4);
                break;   
        case 5: // reg 7 - set voltage
                delay_chanel_2_MSB = holding_register[5];
                SPI_TO_CPLD_SEND (delay_chanel_2_MSB, 5);
                break;   
        case 6: // reg 7 - set voltage
                width_chanel_2_LSB = holding_register[6];
                SPI_TO_CPLD_SEND (width_chanel_2_LSB, 6);
                break;   
        case 7: // reg 7 - set voltage
                width_chanel_2_MSB = holding_register[7];
                SPI_TO_CPLD_SEND (width_chanel_2_MSB, 7);
                break;   
        case 8: // reg 7 - set voltage
                delay_chanel_3_LSB = holding_register[8];
                SPI_TO_CPLD_SEND (delay_chanel_3_LSB, 8);
                break;   
        case 9: // reg 7 - set voltage
                delay_chanel_3_MSB = holding_register[9];
                SPI_TO_CPLD_SEND (delay_chanel_3_MSB, 9);
                break;   
        case 10: // reg 7 - set voltage
                width_chanel_3_LSB = holding_register[10];
                SPI_TO_CPLD_SEND (width_chanel_3_LSB, 10);
                break;   
        case 11: // reg 7 - set voltage
                width_chanel_3_MSB = holding_register[11];
                SPI_TO_CPLD_SEND (width_chanel_3_MSB, 11);
                break;   
        case 12: // reg 7 - set voltage
                delay_chanel_4_LSB = holding_register[12];
                SPI_TO_CPLD_SEND (delay_chanel_4_LSB, 12);
                break;   
        case 13: // reg 7 - set voltage
                delay_chanel_4_MSB = holding_register[13];
                SPI_TO_CPLD_SEND (delay_chanel_4_MSB, 13);
                break;   
        case 14: // reg 7 - set voltage
                width_chanel_4_LSB = holding_register[14];
                SPI_TO_CPLD_SEND (width_chanel_4_LSB, 14);
                break;   
        case 15: // reg 7 - set voltage
                width_chanel_4_MSB = holding_register[15];
                SPI_TO_CPLD_SEND (width_chanel_4_MSB, 15);
                break;   
        case 16: // reg 7 - set voltage
                delay_chanel_5_LSB = holding_register[16];
                SPI_TO_CPLD_SEND (delay_chanel_5_LSB, 16);
                break;   
        case 17: // reg 7 - set voltage
                delay_chanel_5_MSB = holding_register[17];
                SPI_TO_CPLD_SEND (delay_chanel_5_MSB, 17);
                break;   
        case 18: // reg 7 - set voltage
                width_chanel_5_LSB = holding_register[18];
                SPI_TO_CPLD_SEND (width_chanel_5_LSB, 18);
                break; 
        case 19: // reg 7 - set voltage
                width_chanel_5_MSB = holding_register[19];
                SPI_TO_CPLD_SEND (width_chanel_5_MSB, 19);
                break;   
        case 20: // reg 7 - set voltage
                delay_chanel_6_LSB = holding_register[20];
                SPI_TO_CPLD_SEND (delay_chanel_6_LSB, 20);
                break;   
        case 21: // reg 7 - set voltage
                delay_chanel_6_MSB = holding_register[21];
                SPI_TO_CPLD_SEND (delay_chanel_6_MSB, 21);
                break;   
        case 22: // reg 7 - set voltage
                width_chanel_6_LSB = holding_register[22];
                SPI_TO_CPLD_SEND (width_chanel_6_LSB, 22);
                break;   
        case 23: // reg 7 - set voltage
                width_chanel_6_MSB = holding_register[23];
                SPI_TO_CPLD_SEND (width_chanel_6_MSB, 23);
                break;   
        case 24: // reg 7 - set voltage
                delay_chanel_7_LSB = holding_register[24];
                SPI_TO_CPLD_SEND (delay_chanel_7_LSB, 24);
                break;   
        case 25: // reg 7 - set voltage
                delay_chanel_7_MSB = holding_register[25];
                SPI_TO_CPLD_SEND (delay_chanel_7_MSB, 25);
                break;   
        case 26: // reg 7 - set voltage
                width_chanel_7_LSB = holding_register[26];
                SPI_TO_CPLD_SEND (width_chanel_7_LSB, 26);
                break;   
        case 27: // reg 7 - set voltage
                width_chanel_7_MSB = holding_register[27];
                SPI_TO_CPLD_SEND (width_chanel_7_MSB, 27);
                break;   
        case 28: // reg 7 - set voltage
                delay_chanel_8_LSB = holding_register[28];
                SPI_TO_CPLD_SEND (delay_chanel_8_LSB, 28);
                break;   
        case 29: // reg 7 - set voltage
                delay_chanel_8_MSB = holding_register[29];
                SPI_TO_CPLD_SEND (delay_chanel_8_MSB, 29);
                break;   
        case 30: // reg 7 - set voltage
                width_chanel_8_LSB = holding_register[30];
                SPI_TO_CPLD_SEND (width_chanel_8_LSB, 30);
                break;   
        case 31: // 
                width_chanel_8_MSB = holding_register[31];
                SPI_TO_CPLD_SEND (width_chanel_8_MSB, 31);
                break;
                
        // CHANNELS DIR & INV CONTROL
                
        case 32: // EN 1 chanel
                enable_chanel_1 = holding_register[32];
                break;   
        case 33: // INV 1 chanel
                invert_chanel_1 = holding_register[33];
                break;   
        case 34: // EN 2 chanel
                enable_chanel_2 = holding_register[34];
                break;   
        case 35: // INV 2 chanel
                invert_chanel_2 = holding_register[35];
                break;   
        case 36: // reg 7 - set voltage
                enable_chanel_3 = holding_register[36];
                break;   
        case 37: // reg 7 - set voltage
                invert_chanel_3 = holding_register[37];
                break;   
        case 38: // reg 7 - set voltage
                enable_chanel_4 = holding_register[38];
                break;   
        case 39: // reg 7 - set voltage
                invert_chanel_4 = holding_register[39];
                break; 
        case 41: // reg 7 - set voltage
                enable_chanel_5 = holding_register[41];
                break;   
        case 42: // reg 7 - set voltage
                invert_chanel_5 = holding_register[42];
                break;   
        case 43: // reg 7 - set voltage
                enable_chanel_6 = holding_register[43];
                break;   
        case 44: // reg 7 - set voltage
                invert_chanel_6 = holding_register[44];
                break;   
        case 45: // reg 7 - set voltage
                enable_chanel_7 = holding_register[45];
                break;   
        case 46: // reg 7 - set voltage
                invert_chanel_7 = holding_register[46];
                break;   
        case 47: // reg 7 - set voltage
                enable_chanel_8 = holding_register[47];
                break;   
        case 48: // reg 7 - set voltage
                invert_chanel_8 = holding_register[48];
                break;
                
        // CLK & START CONTROL REG's
        case 50: // reg 7 - set voltage
                clk_DIR = holding_register[50];
                break;   
        case 51: // reg 7 - set voltage
                start_DIR = holding_register[51];
                break; 
        case 52: // reg 7 - set voltage
                start_en = holding_register[52];
                break; 
        case 53: // reg 7 - set voltage
                start_inv = holding_register[53];
                break; 
        
        // INTERNAL START GENERATOR REG's
                
        case 54: // reg 7 - set voltage
                delay_start_LSB = holding_register[54];
                SPI_TO_CPLD_SEND (delay_start_LSB, 54);
                break; 
        case 55: // reg 7 - set voltage
                delay_start_MSB = holding_register[55];
                SPI_TO_CPLD_SEND (delay_start_MSB, 55);
                break; 
        case 56: // reg 7 - set voltage
                width_start_LSB = holding_register[56];
                SPI_TO_CPLD_SEND (width_start_LSB, 56);
                break; 
        case 57: // reg 7 - set voltage
                width_start_MSB = holding_register[57];
                SPI_TO_CPLD_SEND (width_start_MSB, 57);
                break; 
        
        default:
        break; 
       }
        
                Control_1 = (((start_inv << 11)|(start_en << 10)|(start_DIR << 9)|(clk_DIR << 8)|(invert_chanel_4 << 7)|(enable_chanel_4 << 6)|(invert_chanel_3 << 5)|(enable_chanel_3 << 4)|(invert_chanel_2 << 3)|(enable_chanel_2 << 2)|(invert_chanel_1 << 1)|enable_chanel_1)& 0x0fff);
                Control_2 = (((invert_chanel_8 << 7)|(enable_chanel_8 << 6)|(invert_chanel_7 << 5)|(enable_chanel_7 << 4)|(invert_chanel_6 << 3)|(enable_chanel_6 << 2)|(invert_chanel_5 << 1)|enable_chanel_5) & 0x00ff);
                SPI_TO_CPLD_SEND (Control_1, 40);
                SPI_TO_CPLD_SEND (Control_2, 49);
                
       
   } //if(cmd_type == MODBUS_WSR_CMD) 
  }

/*############################################################################*/  
  
/*                         M O D B U S   E N D                                */




