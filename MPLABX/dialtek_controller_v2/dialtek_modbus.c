/*                D I A L T E K    M O D B U S   R T U   v 2.2                */

/* ИНСТРУМЕНТЫ ПОЛЬЗОВАТЕЛЯ */

/* README */
/*
Для работы библиотеки MODBUS RTU необходимо:

1. настроить прерывание UART RX по приему одного байта 

2. вставить в обработчик прерывания UART RX функцию modbus_uart_byte, например:
      modbus_uart_byte(MDR_UART1->DR); или modbus_uart_byte(U1RXREG);

3. создать функцию отправки одного байта UART TX следующего вида:
      void uart_send_hex(unsigned char hex_data){ }

4. поместить функцию modbus_rx_sm() в обработчик прерывания по таймеру (Т >= 1 мс) или цикл while(1)

5. поместить функцию modbus_init() в main()

6. поместить функцию modbus_poll() в цикл while(1) (Т >= 1 мс)

7. настроить порты для управления разрешением работы приемника (если необходимо) и передатчика в поле RS485 EN/DIS DEFINE

8. настроить аттрибуты устройства в поле HARDWARE INFO 

9. заполнить функцию modbus_int_mode() кодом с разрешением и запретом прерываний UART RX

10.составить регистровую карту устройства в фукции modbus_refresh() :
      А) при чтении регистров, выполняется код if(cmd_type == MODBUS_RHR_CMD)
      Б) при записи регистров, выполняется код if(cmd_type == MODBUS_WSR_CMD)

11. при необходимости использования своих функции внутри modbus_refresh(), следует создать их прототипы в поле ПРОТОТИПЫ  
*/

/*############################################################################*/ 
/*                    ПОЛЯ ИЗМЕНЯЕМЫЕ ПОЛЬЗОВАТЕЛЕМ !!!                       */ 

/* RS485 EN/DIS DEFINE */
#define TX_EN  LATEbits.LATE8=1
#define TX_DIS LATEbits.LATE8=0

/* HARDWARE INFO */
  unsigned char dev_id        = DEFAULT_DEV_ID;     // MODBUS ID устройства                                      <<<<<<<<<<======== ID
  unsigned char firmware_ver  = 10;                 // версия прошивки текущего устройства
  unsigned char device_family = 200;                // код семейства устройств

/* ПРОТОТИПЫ */
unsigned int get_syr_pos (unsigned char);
unsigned int get_syr_vel (unsigned char);
unsigned int get_valve_angle (unsigned char);
  
/* USER FUNCS */
/*--------------------------------------------------------------------------- */  
  
  void modbus_int_mode (unsigned char mode)  
  {      // управление прерыванием UART RX
  
    if(mode == 1) // разрешение прерываний RX UART MODBUS
    {
      IEC0bits.U1RXIE = 1; // en UART1 RX interrupt   
    }
    else         // запрет прерываний RX UART MODBUS
    {
      IEC0bits.U1RXIE = 0; // dis UART1 RX interrupt   
    }
  }
  
  void modbus_refresh(unsigned char cmd_type) // работа с регистрами
  {     
    
   /// Чтение R/W регистров, TODO - обновление переменных перед отправкой мастеру    
    
   if(cmd_type == MODBUS_RHR_CMD)
   {
     MODBUS_RX_LED = ~MODBUS_RX_LED;  
    //if(is_reg(0)) holding_register[0] = get_syr_pos(1);
    //if(is_reg(1)) holding_register[1] = get_syr_vel(1);
    //if(is_reg(2)) holding_register[2] = get_valve_angle(1);       


    
    //MODBUS_RX_LED = 0;   
   }         
   //-------------------------------------------------------------------------//
   /// Чтение Read-only регистров, TODO - обновление переменных перед отправкой мастеру   
   if(cmd_type == MODBUS_RIR_CMD)
   {   
       MODBUS_RX_LED = ~MODBUS_RX_LED;  
        
       input_register[0] = (unsigned int)dev_id;       
       input_register[1] = (unsigned int)device_family;
       input_register[2] = (unsigned int)firmware_ver;
       
   }         
   //-------------------------------------------------------------------------//
  
   /// ЗАПИСЬ, TODO - получение новых значений от мастера
   //  starting_address = адрес регистра, в который идет запись (1000 = 0, 1001 = 1 и тд)
      
   if(cmd_type == MODBUS_WSR_CMD) 
   {  // анализ регистра записи 
       
      MODBUS_RX_LED = ~MODBUS_RX_LED;  
       
      switch(starting_address) 
      {  
        case 1: // reg 1

        break;
        //---------
        case 6: // set syringe position   
            if(holding_register[6] <= 3000) 
               set_syr_pos(1, holding_register[6]);
        break;
        //---------
        case 7: // set syringe velocity   
            if(holding_register[7] <= 40) 
               set_syr_vel(1, holding_register[7]);
        break;
        //---------
        case 8: // set valve angle   
            if(holding_register[8] <= 345) 
               set_valve_angle(1, holding_register[8], 0);
        break;
        //---------
        case 10:  init_protocol(1);  break;    
        //---------    
        case 11:  init_valve(1);     break;    
        //---------
        case 12:  init_syringe(1);   break;    
        //---------              
        default: break;  
      }
      
      //eeprom_wr_regs(); // save registers state
   }
   
      
   
  }

/*############################################################################*/  
  
/*                         M O D B U S   E N D                                */




