/*                D I A L T E K    M O D B U S   R T U   v 2.1                */

/* ИНСТРУМЕНТЫ ПОЛЬЗОВАТЕЛЯ */

/* README */
/*
Для работы библиотеки MODBUS RTU необходимо:

1. настроить прерывание UART RX по приему одного байта 

2. вставить в обработчик прерывания UART RX функцию modbus_uart_byte, например:
      modbus_uart_byte(MDR_UART1->DR); или modbus_uart_byte(U1RXREG);

3. создать функцию отправки одного байта UART TX следующего вида:
      void uart_send_hex(unsigned char hex_data){ }

4. поместить функцию modbus_rx_sm() в цикл while(1)

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

#define TX_EN  LATFbits.LATF6=1
#define TX_DIS LATFbits.LATF6=0

/* HARDWARE INFO */

//unsigned char com_dev_id    = 247;                // MODBUS ID устройства для широковещательного режима, лучше не трогать 
unsigned char dev_id        = 100;                // MODBUS ID устройства                                      <<<<<<<<<<======== ID
unsigned char firmware_ver  = 10;                 // версия прошивки текущего устройства
unsigned char device_family = 90;                 // код семейства устройств

/* ПРОТОТИПЫ */
//==============================================================================
/* USER FUNCS */

#define ID_lenght	8 // кол-во байт в ID датчика
#define MAX_sens_qty 10   // макс. число датчиков 

unsigned char ID_buf [8]     = {0,0,0,0,0,0,0,0};     // временный массив ID
unsigned char index_buf [10] = {255,255,255,255,255,255,255,255,255,255}; // массив с занятыми ID
unsigned char add_count;       // счетчик попыток добавления
unsigned char eq_cnt = 0;      // счетчик совпадений массива ID  
unsigned char index_exist = 0; // флаг наличия индекса среди уже записанных


unsigned char Sens_ID[MAX_sens_qty][ID_lenght]; // ID датчиков в двумерном виде  
unsigned char sensors_qty  = 0;			// кол-во датчиков на шине 1-wire
unsigned char sensor_index;       // индекс датчика для сохр. его id

/*--------------------------------------------------------------------------- */
#include "one_wire.h"

  // запись ID нового датчика во временный массив
  void get_sensor_ID()
  {
     if (OneWire_reset())
     {
        OneWire_send(Read_ROM);
        for (unsigned char i = 0; i < ID_lenght; i++)
            ID_buf[i] = OneWire_read(); // сохранение ID датчика во временный буфер 
     }
  }
  
  // поиск ID нового датчика среди уже сохраненных
  unsigned char match_sensor_ID()
  {
     unsigned char sensor_exist = 0;
      
     // сравнение ID нового датчика с теми, что были добавлены ранее
     for(unsigned char i = 0; i < sensors_qty; i++)
     {
        for(unsigned char j = 0; j < ID_lenght; j++)
        {
            if(Sens_ID[i][j] == ID_buf[j])
                eq_cnt++;          
        }
        
        if(eq_cnt < ID_lenght) eq_cnt = 0; // сброс счетчика перед новым поиском
     }
      
     if(eq_cnt >= ID_lenght) 
         sensor_exist = 1;
      
      return sensor_exist;
  }

  // сброс конфигурации датчиков
  void reset_cfg()
  {
      // очитска массива с ID датчиков       
      for(unsigned char i = 0; i < MAX_sens_qty; i++)
      {
         index_buf[i] = 255;  // массив с занятыми ID
                 
         for(unsigned char j = 0; j < ID_lenght; j++) 
             Sens_ID[i][j] = 0;
      }
         
      // очитска регистров, содержащих ID датчиков  
      for(unsigned char i = 10; i < 110; i++)
      {
          input_register[i] = 0;
          holding_register[i-10] = 0;
      }
      
      sensors_qty = 0;                     // сброс числа датчиков    
      add_count = 0;
      index_exist = 0;
  }
  
  
  /* USER FUNCS */
  //==============================================================================
  
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
    
   /// Чтение R/W регистров, TODO - обновление переменных перед отправкой мастеру    
    
   if(cmd_type == MODBUS_RHR_CMD)
   {   
       
    long t = 0;
    unsigned char cnt = 0;
    if(sensors_qty > 0)
    {
        OneWire_all_rd_t(); // Команда измерения Т для всех датчиков
                        // задержка измер. Т 760 мс внутри функции

        for(unsigned char i = 0; i < sensors_qty; i++)// Опрос Тemper с датчиков поочередно
        {
          t = ds18b20_i_rd_t(Sens_ID[i]);  //присвоение Temper значения температуры
       
          holding_register[cnt]   = (unsigned int)  (t >> 16);
          cnt++;
          holding_register[cnt] = (unsigned int)  (t & 0x0000ffff);
          cnt++;
        }
          holding_register[30] = sensor_index;
    }
       
   }         
   //-------------------------------------------------------------------------//
   /// Чтение Read-only регистров, TODO - обновление переменных перед отправкой мастеру   
   if(cmd_type == MODBUS_RIR_CMD)
   {   
       input_register[0] = (unsigned int)dev_id;       
       input_register[1] = (unsigned int)device_family;
       input_register[2] = (unsigned int)firmware_ver;
       
       input_register[9] = (unsigned int)sensors_qty;
                 
       // 1st sensor ID: 10 - 17 input regs
       // 2nd sensor ID: 20 - 27 input regs
       // etc.
   }         
   //-------------------------------------------------------------------------//
  
   /// ЗАПИСЬ, TODO - получение новых значений от мастера
   //  addr_buf_1 = адрес регистра, в который идет запись (1000 = 0, 1001 = 1 и тд)
  
   if(cmd_type == MODBUS_WSR_CMD) 
   {  // анализ регистра записи 
      switch(addr_buf_1) {  
        case 0: // reg 0 - steps

        break;
        //---
        case 1: // 
   
        break;
        //---
        case 2: // 

        break;
        //---
        case 30: // set sensor number
          
          // добавляем новый датчик, если его индекс в диапазоне 0 - MAX_sens_qty-1
          if(holding_register[30] <= MAX_sens_qty -1)
          {
            // смотрим, бы ли ранее записан этот индекс датчика
            for(unsigned char i = 0; i < MAX_sens_qty; i++)
            {
                if(index_buf[i] == holding_register[30])
                    index_exist = 1; // да, взводим флаг
            }
            
            // если это новый датчик..
            if(!index_exist)
            {
               index_buf[add_count] = sensor_index; // сохр. его индекс в буфер
               add_count++; // инкремент числа операций добавления
            }
          }
          
          else holding_register[30] = MAX_sens_qty - 1;
          sensor_index = holding_register[30];
          
          if(add_count > 10) add_count = 0;
            
        break;
        //---
        case 31: // добавление нового датчика
        
        eq_cnt = 0;  // сброс счетчика совпадений байт ID
        
        //get 8 ROM bytes - считывание ID датчка во временный буфер
        get_sensor_ID();  
        
        // сброс операции добавления датчика, если он добавлен ранее
        if(match_sensor_ID() == 1) break;            
        // если это новый датчик - добавляем его
        else
        {
            for (unsigned char i = 0; i < ID_lenght; i++) 
            {
              input_register[(10+10*sensor_index) + i] = ID_buf[i];  
              Sens_ID[sensor_index][i] = input_register[(10+10*sensor_index) + i];
            } 
            
            if(index_exist)
              index_exist = 0; // сброс флага наличия индекса среди уже записанных
            else 
            {
                sensors_qty++; // инкремент числа датчиков, если это новый
                index_exist = 0;
            }
            sensor_index = 255;
           
          // 1st sensor ID: 10 - 17 input regs
          // 2nd sensor ID: 20 - 27 input regs
          // etc.
        }
          
        break;
        //---
        case 32:  
        /* очистка массива с ID и возвражение прибора к исходному состоянию
          без датчиков */
            
            reset_cfg();

        break;
        //---

        //---
          default: break;
    } // switch
   } // if 
  }

/*############################################################################*/  
  
/*                         M O D B U S   E N D                                */




