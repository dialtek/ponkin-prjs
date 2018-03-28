/*                D I A L T E K    M O D B U S   R T U   v 2.0                */

/* README */
/*
ƒля работы библиотеки MODBUS RTU необходимо:

1. настроить прерывание UART RX по приему одного байта 

2. вставить в обработчик прерывания UART RX функцию modbus_uart_byte, например:
      modbus_uart_byte(MDR_UART1->DR); или modbus_uart_byte(U1RXREG);

3. создать функцию отправки одного байта UART TX следующего вида:
      void uart_send_hex(unsigned char hex_data){ }

4. поместить функцию modbus_rx_sm() в обработчик прерывания по таймеру (“ >= 1 мс) или цикл while(1)

5. поместить функцию modbus_init() в main()

6. поместить функцию modbus_poll() в цикл while(1) (T >= 1 мс)

7. настроить порты для управления разрешением работы приемника (если необходимо) и передатчика в поле RS485 EN/DIS DEFINE

8. настроить аттрибуты устройства в поле HARDWARE INFO 

9. заполнить функцию modbus_int_mode() кодом с разрешением и запретом прерываний UART RX

10.составить регистровую карту устройства в фукции modbus_refresh() :
      A) при чтении регистров, выполняется код if(cmd_type == MODBUS_RHR_CMD)
      B) при записи регистров, выполняется код if(cmd_type == MODBUS_WSR_CMD)

11. при необходимости использования своих функции внутри modbus_refresh(), следует создать их прототипы в поле PROTOTYPES  
*/

/*############################################################################*/ 
/*                   ѕќЋя, »«ћ≈Ќя≈ћџ≈ ѕќЋ№«ќ¬ј“≈Ћ≈ћ !!!                       */ 

/* RS485 EN/DIS DEFINE */

#define TX_EN  LATCbits.LATC3=1
#define TX_DIS LATCbits.LATC3=0

/* HARDWARE INFO */

  unsigned char com_dev_id   = 247;                // MODBUS ID устройства для широковещательного режима, лучше не трогать 
  unsigned char dev_id       = 11;                 // MODBUS ID устройства                                      <<<<<<<<<<======== ID
  unsigned int firmware_ver  = 20;                 // версия прошивки текущего устройства
  unsigned int device_family = 10;                  // код семейства устройств

/* PROTOTYPES */
  
/* USER FUNCS */
  
  void modbus_int_mode (unsigned char mode)  {      // управление прерыванием UART RX
  
    if(mode == 1) // разрешение прерываний RX UART MODBUS
    {
        PIE1bits.RC1IE = 0;    // запрет UART recive
    }
    else         // запрет прерываний RX UART MODBUS
    {
        PIE1bits.RC1IE = 1;    // разрешение UART recive
    }
  }
  
  void modbus_refresh(unsigned char cmd_type){      // работа с регистрами
    
  /// „“≈Ќ»≈ RW регистров, TODO - обновление переменных перед отправкой мастеру       
  if(cmd_type == MODBUS_RHR_CMD)
   {   
        holding_register[0] = set_zero;
        holding_register[1] = offset;
        holding_register[2] = num_of_turns;
        holding_register[3] = grad;
        holding_register[4] = turns_percent;
        holding_register[5] = V_detect;   
        holding_register[6] = current_max;
        holding_register[7] = ADC_current_rms;
        holding_register[8] = overcurrent;
        
        holding_register[10] = ADC_current_dif;
        holding_register[11] = read_turns;
        holding_register[12] = adc_current_result;
        holding_register[13] = ADC_current_max;
        holding_register[14] = ADC_current_min;
   }         
   //-------------------------------------------------------------------------//
  /// „“≈Ќ»≈ Read-only регистров, TODO - обновление переменных перед отправкой мастеру   
   if(cmd_type == MODBUS_RIR_CMD)
   {   
       input_register[0] = (unsigned int)dev_id;       
       input_register[1] = (unsigned int)device_family;
       input_register[2] = firmware_ver;
   } 
   //-------------------------------------------------------------------------//
   /// «јѕ»—№, TODO - получение новых значений от мастера
   //  addr_buf_1 = адрес регистра, в который идет запись (1000 = 0, 1001 = 1 и тд)
   if(cmd_type == MODBUS_WSR_CMD) 
   {  // анализ регистра записи 
      switch(addr_buf_1) {  
        case 4: // reg 4
           
        break;
        //---------
        case 7: // reg 7

        break;     
         //---------
       default: break;  }

   } 
  }

/*############################################################################*/  
  
/*                         M O D B U S   E N D                                */




