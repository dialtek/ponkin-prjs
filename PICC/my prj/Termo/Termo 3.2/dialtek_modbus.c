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

/*############################################################################*/ 
/*                   ПОЛЯ, ИЗМЕНЯЕМЫЕ ПОЛЬЗОВАТЕЛЕМ !!!                       */ 

/* RS485 EN/DIS DEFINE */

#define TX_EN  RC14=1 
#define TX_DIS RC14=0

/* HARDWARE INFO */

 // unsigned char com_dev_id    = 247;              // MODBUS ID устройства длЯ широковещательного режима, лучше не трогать 
  unsigned char dev_id        = 100;                  // MODBUS ID устройства   <<<<<<<<<<======== ID
  unsigned char firmware_ver  = 15;                 // версиЯ прошивки текущего устройства
  unsigned char device_family = 5;                  // код семейства устройств

/* PROTOTYPES */


 /* USER FUNCS */
  
  
  void modbus_refresh(unsigned char cmd_type){      // работа с регистрами
    
  /// RW регистров, TODO - обновление переменных перед отправкой мастеру       
  if(cmd_type == MODBUS_RHR_CMD)
   {   
      //U8 read_complete = is_reading_reg(meas_status_reg);
      if(meas_status)  
      {  // цикл измерений завершен, обновление регистров
         // 0. 000 000  0 V - формат, последнее число - сотни нВ
         holding_register[0] = (U16) (pkt8_ch_1 & 0x0000ffff);          // LSB канала 1
         holding_register[1] = (U16)((pkt8_ch_1 & 0xffff0000) >> 16);   // MSB канала 1
         
         
         holding_register[2] = (U16) (pkt8_ch_2 & 0x0000ffff);          // LSB канала 2
         holding_register[3] = (U16)((pkt8_ch_2 & 0xffff0000) >> 16);   // LSB канала 2
         
         holding_register[4] = (U16) (pkt8_ch_3 & 0x0000ffff);          // LSB канала 3
         holding_register[5] = (U16)((pkt8_ch_3 & 0xffff0000) >> 16);   // MSB канала 3
         
         holding_register[6] = (U16) (pkt8_ch_4 & 0x0000ffff);          // LSB канала 4
         holding_register[7] = (U16)((pkt8_ch_4 & 0xffff0000) >> 16);   // LSB канала 4
         
         holding_register[8] = (U16) (pkt8_ch_5 & 0x0000ffff);          // LSB канала 5
         holding_register[9] = (U16)((pkt8_ch_5 & 0xffff0000) >> 16);   // MSB канала 5
         
         holding_register[10] = (U16) (pkt8_ch_6 & 0x0000ffff);         // LSB канала 6
         holding_register[11] = (U16)((pkt8_ch_6 & 0xffff0000) >> 16);  // LSB канала 6
         
         holding_register[12] = (U16) (pkt8_ch_7 & 0x0000ffff);         // LSB канала 7
         holding_register[13] = (U16)((pkt8_ch_7 & 0xffff0000) >> 16);  // MSB канала 7
         
         holding_register[14] = (U16) (pkt8_ch_8 & 0x0000ffff);         // LSB канала 8
         holding_register[15] = (U16)((pkt8_ch_8 & 0xffff0000) >> 16);  // LSB канала 8
         // ===================================================================
         // обновление отсчетов
         holding_register[24] = (U16) (ADC_counts[0][0] & 0x0000ffff);         // LSB канала 1
         holding_register[25] = (U16)((ADC_counts[0][0] & 0xffff0000) >> 16);  // MSB канала 1
         
         holding_register[26] = (U16) (ADC_counts[0][1] & 0x0000ffff);         // LSB канала 2
         holding_register[27] = (U16)((ADC_counts[0][1] & 0xffff0000) >> 16);  // LSB канала 2
         
         holding_register[28] = (U16) (ADC_counts[0][2] & 0x0000ffff);         // LSB канала 3
         holding_register[29] = (U16)((ADC_counts[0][2] & 0xffff0000) >> 16);  // MSB канала 3
         
         holding_register[30] = (U16) (ADC_counts[0][3] & 0x0000ffff);         // LSB канала 4
         holding_register[31] = (U16)((ADC_counts[0][3] & 0xffff0000) >> 16);  // LSB канала 4
         
         holding_register[32] = (U16) (ADC_counts[1][0] & 0x0000ffff);         // LSB канала 5
         holding_register[33] = (U16)((ADC_counts[1][0] & 0xffff0000) >> 16);  // MSB канала 5
         
         holding_register[34] = (U16) (ADC_counts[1][1] & 0x0000ffff);         // LSB канала 6
         holding_register[35] = (U16)((ADC_counts[1][1] & 0xffff0000) >> 16);  // LSB канала 6
         
         holding_register[36] = (U16) (ADC_counts[1][2] & 0x0000ffff);         // LSB канала 7
         holding_register[37] = (U16)((ADC_counts[1][2] & 0xffff0000) >> 16);  // MSB канала 7
         
         holding_register[38] = (U16) (ADC_counts[1][3] & 0x0000ffff);         // LSB канала 8
         holding_register[39] = (U16)((ADC_counts[1][3] & 0xffff0000) >> 16);  // LSB канала 8
         
         // сброс статус флага новых измерений
         meas_status = 0;
      }
      holding_register[16] = (U16)input_buf_state; // сост. вх. буфера АЦП
      holding_register[18] = PGA_val;
      holding_register[19] = ADC_sps_var;
      holding_register[20] = Ma_buf_size;
      holding_register[21] = dev_id;
      holding_register[22] = firmware_ver;
      holding_register[23] = device_family;
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
 
        // range
         if(holding_register[18] >= 0 && holding_register[19] <= 6) 
             PGA_val = holding_register[18];
         // SPS
         if(holding_register[19] >= 0 && holding_register[19] <= 8) 
             ADC_sps_var = holding_register[19];
         // averfge buf size
         if(holding_register[20] >= 1 && holding_register[20] <= 128) 
         {
             Clr_bufs(); // очистка буфера скользящ. среднего
             Ma_buf_size = holding_register[20];
         }
         input_buf_state = (U8)holding_register[16]; // сост. вх. буфера
                
   } //if(cmd_type == MODBUS_WSR_CMD) 
  }
  

/*############################################################################*/  
  
/*                         M O D B U S   E N D                                */




