/*                D I A L T E K    M O D B U S   R T U   v 3.1                */

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

#define TX_EN  LATBbits.LATB14=1
#define TX_DIS LATBbits.LATB14=0

/* HARDWARE INFO */
  volatile unsigned char dev_id = DEFAULT_DEV_ID;     // MODBUS ID устройства <<<<<<<<<<======== ID
  unsigned char firmware_ver  = 27;                 // версия прошивки текущего устройства
  unsigned char device_family = 5;                  // код семейства устройств
  unsigned char com_dev_id    = 247;                // MODBUS ID устройства длЯ широковещательного режима, лучше не трогать 
  unsigned char modbus_ver    = 31;                 // версия MODBUS
  
/* ПРОТОТИПЫ */

  // PSP405
unsigned char char2num (unsigned char ch);
unsigned char num2char (unsigned char ch);
unsigned int PSP405_get_voltage();
unsigned int PSP405_get_current();
unsigned int PSP405_get_status();
unsigned int PSP405_get_voltage_lim();
unsigned int PSP405_get_current_lim();
void PSP405_set_output(unsigned int state);
void PSP405_set_power_lim(unsigned int power_lim);

void TimerX32_setMs(unsigned long ms);
void TimerX32_state(unsigned char state);

void eeprom_wr_regs(void);

/* USER FUNCS */ 
  
  void modbus_refresh(unsigned char cmd_type) // работа с регистрами
  {     
    
   /// Чтение R/W регистров, TODO - обновление переменных перед отправкой мастеру    
    
   if(cmd_type == MODBUS_RHR_CMD)
   {   
       holding_register[0] = rd_voltage;
       holding_register[1] = rd_voltage_lim;
       holding_register[2] = rd_current;
       holding_register[3] = rd_current_lim;      
       holding_register[4] = rd_status; // the relay status 0:OFF 1:ON
       holding_register[5] = rd_power_lim;    
       
   }         
   //-------------------------------------------------------------------------//
   /// Чтение Read-only регистров, TODO - обновление переменных перед отправкой мастеру   
   if(cmd_type == MODBUS_RIR_CMD)
   {   
       input_register[0] = (unsigned int)dev_id;       
       input_register[1] = (unsigned int)device_family;
       input_register[2] = (unsigned int)firmware_ver;
       input_register[3] = (unsigned int)modbus_ver; // версия MODBUS
   }         
   //-------------------------------------------------------------------------//
  
   /// ЗАПИСЬ, TODO - получение новых значений от мастера
   //  addr_buf_1 = адрес регистра, в который идет запись (1000 = 0, 1001 = 1 и тд)
  
   if(cmd_type == MODBUS_WSR_CMD) 
   {  // анализ регистра записи 
     
      switch(modbus_reg_addr) {  
        //---------
        case 7: // reg 7 - set voltage
           if(holding_register[7] > MAX_VOLTAGE) holding_register[7] = MAX_VOLTAGE;
           RS232_TX_LED = 1;
           PSP405_set_voltage(holding_register[7]);
           
           curr_cmd = SRC_CMD;
           TimerX32_setMs(500);  
           TimerX32_state(1);
         
        break;
        //---------
        case 8: // reg 8 - set voltage limit
           if(holding_register[8] > MAX_VOLTAGE/100) holding_register[8] = MAX_VOLTAGE/100;
           RS232_TX_LED = 1;
           PSP405_set_voltage_lim(holding_register[8]);
           
           curr_cmd = SRC_CMD;
           TimerX32_setMs(500);  
           TimerX32_state(1);
        break;
        //---------
        case 9: // reg 9 - set current
           if(holding_register[9] > MAX_CURRENT) holding_register[9] = MAX_CURRENT;
           RS232_TX_LED = 1;
           PSP405_set_current(holding_register[9]);
           
           curr_cmd = SRC_CMD;
           TimerX32_setMs(500);  
           TimerX32_state(1);
        break;
        //---------
        case 10: // reg 10 - K1 relay ctrl
           RS232_TX_LED = 1;
           PSP405_set_output(0);
          
           curr_cmd = POL_CHANGE_1;
           TimerX32_setMs(2000);  
           TimerX32_state(1);
           
        break;
        //---------
        case 11: // reg 1 - power limit
           if(holding_register[11] > MAX_POWER) holding_register[11] = MAX_POWER;
           RS232_TX_LED = 1;
           PSP405_set_power_lim(holding_register[11]);
           
           curr_cmd = SRC_CMD;
           TimerX32_setMs(500);  
           TimerX32_state(1);
           
        break;
        //---------
        case 12: // reg 4 - set output
            RS232_TX_LED = 1;
            PSP405_set_output(holding_register[12]);
            
            
            curr_cmd = SRC_CMD;
            TimerX32_setMs(500);  
            TimerX32_state(1);        
        break;
       //---------
        case 19: // reg 19 - ID
            // modbus id change seq     
            if((dev_id >= 254 ) || (dev_id == 0)) break;
            else
            {  
             dev_id = (unsigned char)holding_register[20];
             holding_register[19] = 0;
            }
            
       break;
      }
         RS232_TX_LED = 0;
         eeprom_wr_regs(); // save registers state 
   } 
  }

/*############################################################################*/  
  
/*                         M O D B U S   E N D                                */




