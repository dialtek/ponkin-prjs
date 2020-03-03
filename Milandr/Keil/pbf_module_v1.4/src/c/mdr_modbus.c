#include "FreeRTOS.h"
#include "queue.h"
#include "semphr.h"
#include "mdr_modbus.h"
#include <MDR32F9Qx_port.h>
#include "main.h"
#include "mdr_uart.h"

#define USE_JTAG_A
#define TX_EN     MDR_PORTB->RXTX |=  (1<<9) & (~JTAG_PINS(MDR_PORTB))   // вкл.  передатчик RS485 _/
#define TX_DIS    MDR_PORTB->RXTX &= ~(1<<9) & (~JTAG_PINS(MDR_PORTB))   // выкл. передатчик RS485 \_

uint16_t rx_buf_ptr = 0; // указатель записи в массив UART
// буфер для сохр. принятных команд
uint8_t  rx_buf[128];

uint8_t modbus_cmd = 0;   // 0x03 | 0x06 | 0x04

uint16_t addr_buf_1 = 0, addr_buf_2 = 0;
uint16_t regs2read = 0;     // число регистров для чтения по команде modbus rhr
uint16_t CRC16 = 0;			// полученная контрольная сумма
uint8_t  crc_buf[300];      // буфер для хранения байтов для расчета CRC16
uint8_t modbus_id = 0;		// буфер для хранения ID из запроса мастера
uint16_t reg_wr_data = 0;
uint16_t modbus_reg_addr;       // адрес регистра для R/W по запросу от modbus мастера

uint16_t holding_register[125];  // буфер для хранения R/W переменных чтения, макс. число регистров - 124
uint16_t input_register[125];    // буфер для хранения Read-only переменных чтения, макс. число регистров - 124
 
/* HARDWARE INFO */

const uint8_t com_dev_id    = 247;       // MODBUS ID устройства длЯ широковещательного режима, лучше не трогать 
uint8_t dev_id     = default_devID;      // MODBUS ID устройства   <<<<<<<<<<======== ID
const char firmware_ver  = 10;           // версиЯ прошивки текущего устройства
const char device_family = 0;            // код семейства устройств
const char modbus_ver    = 41;           // версия MODBUS

 /* Create a counting semaphore that has a maximum count of 10 and an
    initial count of 0. */
 SemaphoreHandle_t RxSemaphore;
 
  /* расчет контрольной суммы */
  static uint16_t modbus_CRC16(uint8_t buf[], uint16_t len) {
  /// расчет crc16
    
  uint16_t crc = 0xFFFF;
  //U8 crc_lsb, crc_msb;
  for (uint16_t pos = 0; pos < len; pos++)
  {
    crc ^= (uint16_t)buf[pos];          // XOR byte into least sig. byte of crc
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
  volatile void modbus_wsr_answer() { 
    /// ответ на команды записи в регистр
    
    // расчет CRC
    crc_buf[0] = (modbus_id == dev_id) ? dev_id : com_dev_id;
    crc_buf[1] = (uint8_t) MODBUS_WSR_CMD;
    crc_buf[2] = (uint8_t)(modbus_reg_addr >> 8);
    crc_buf[3] = (uint8_t)(modbus_reg_addr & 0x00ff);
    crc_buf[4] = (uint8_t)(reg_wr_data >> 8);
    crc_buf[5] = (uint8_t)(reg_wr_data & 0x00ff);
    CRC16 = modbus_CRC16(crc_buf, 6);

    //--------------------------------------------------------------------
    // отправка пакета мастеру
    TX_EN;
    vTaskSuspendAll(); // приостановка диспетчера на момент отправки посылки
    UartSendByte((modbus_id == dev_id) ? dev_id : com_dev_id); // ID устройства
    UartSendByte((uint8_t)MODBUS_WSR_CMD);                     // код команды
    UartSendByte((uint8_t)(modbus_reg_addr >> 8));             // ст. байт адреса регистра
    UartSendByte((uint8_t)(modbus_reg_addr & 0x00ff));         // мл. байт адреса регистра
    UartSendByte((uint8_t)(reg_wr_data >> 8));
    UartSendByte((uint8_t)(reg_wr_data & 0x00ff));
     // отправка CRC
    UartSendByte((uint8_t)(CRC16 >> 8));      // msb
    UartSendByte((uint8_t)(CRC16 & 0x00ff));  // lsb 
    xTaskResumeAll(); // возобновление работы диспетчера
		vTaskDelay(5);
    TX_DIS;
    //--------------------------------------------------------------------
  }
  
  
	/* формирование и отправка ответа на команду чтения RW регистров */
  volatile void modbus_rhr_answer() {
    
    /// ответ на команды чтения регистров
          addr_buf_1 = modbus_reg_addr; 
  	      addr_buf_2 = addr_buf_1;             // сохр. адрес в двух переменных	  
          // расчет CRC
          crc_buf[0] = (modbus_id == dev_id) ? dev_id : com_dev_id;
          crc_buf[1] = MODBUS_RHR_CMD;
          crc_buf[2] = regs2read*2;
          
          uint8_t cnt = 3;      // величина смещения данных при расчете CRC

          for(uint8_t j = 0; j < regs2read;j++)
          { // заполнение буфера CRC для расчета
            crc_buf[cnt++] = (uint8_t)(holding_register[addr_buf_1] >> 8);
            crc_buf[cnt++] = (uint8_t)(holding_register[addr_buf_1] & 0x00ff);
            ++addr_buf_1;  
          }
            // расчет CRC  
          CRC16 = modbus_CRC16(crc_buf,(regs2read*2)+3);
          //--------------------------------------------------------------------
          // отправка пакета мастеру 
	        TX_EN;
          vTaskSuspendAll(); // приостановка диспетчера на момент отправки посылки
          
          UartSendByte((modbus_id == dev_id) ? dev_id : com_dev_id);   // ID устройства
          UartSendByte((uint8_t)MODBUS_RHR_CMD);                       // код команды
          UartSendByte((uint8_t)regs2read*2);                          // кол-во передаваемых байт 

          for(uint8_t i = 0; i < regs2read; i++)
          {   // отправка байт данных с инкрементом адреса
            UartSendByte((uint8_t)(holding_register[addr_buf_2] >> 8));     // msb
            UartSendByte((uint8_t)(holding_register[addr_buf_2] & 0x00ff)); // lsb
            ++addr_buf_2;
          }
          // отправка CRC
          UartSendByte((uint8_t)(CRC16 >> 8));      // msb
          UartSendByte((uint8_t)(CRC16 & 0x00ff));  // lsb  
          
          xTaskResumeAll(); // возобновление работы диспетчера
					vTaskDelay(5);
					TX_DIS;
          //--------------------------------------------------------------------
  
  }
 
  
	/* формирование и отправка ответа на команду чтения Read-only регистров */
  volatile void modbus_rir_answer() {
    
    /// ответ на команды чтения input регистров
    
          addr_buf_1 = modbus_reg_addr; 
          addr_buf_2 = addr_buf_1;             // сохр. адрес в двух переменных		  
          // расчет CRC
          crc_buf[0] = (modbus_id == dev_id) ? dev_id : com_dev_id;
          crc_buf[1] = MODBUS_RIR_CMD;
          crc_buf[2] = regs2read*2;
          
          uint8_t cnt = 3;      // величина смещения данных при расчете CRC

          for(uint8_t i = 0; i < regs2read; i++)
          { // заполнение буфера CRC для расчета
            crc_buf[cnt++] = (uint8_t)(input_register[addr_buf_1] >> 8);
            crc_buf[cnt++] = (uint8_t)(input_register[addr_buf_1] & 0x00ff);
            ++addr_buf_1;  
          }
            // расчет CRC  
          CRC16 = modbus_CRC16(crc_buf,(regs2read*2)+3);
          //--------------------------------------------------------------------
          // отправка пакета мастеру 
          TX_EN;
          vTaskSuspendAll(); // приостановка диспетчера на момент отправки посылки
          UartSendByte((modbus_id == dev_id) ? dev_id : com_dev_id);         // ID устройства
          UartSendByte((uint8_t)MODBUS_RIR_CMD);                       // код команды
          UartSendByte((uint8_t)regs2read*2);                          // кол-во передаваемых байт 

          for(uint8_t i = 0; i < regs2read; i++)
          {   // отправка байт данных с инкрементом адреса
            UartSendByte((uint8_t)(input_register[addr_buf_2] >> 8));     // msb
            UartSendByte((uint8_t)(input_register[addr_buf_2] & 0x00ff)); // lsb
            ++addr_buf_2;
          }
          // отправка CRC
          UartSendByte((uint8_t)(CRC16 >> 8));      // msb
          UartSendByte((uint8_t)(CRC16 & 0x00ff));  // lsb   
          xTaskResumeAll(); // возобновление работы диспетчера
					vTaskDelay(5);
          TX_DIS;
          //--------------------------------------------------------------------
  
  }

  
	/* анализ контрольной суммы полученной посылки */
  uint8_t modbus_rx_CRC_check(uint8_t modbus_cmd) {
  /// заполнение массива CRC для рассчета и сравнения с прочитанным  
   uint16_t CRC16_calc = 0;  // рассчетная контрольная сумма
   uint8_t ans = 0;
   
   modbus_reg_addr = (uint16_t)((rx_buf[2] << 8) | rx_buf[3]); // get starting reg addr
   
   crc_buf[0] = (modbus_id == dev_id) ? dev_id : com_dev_id;
   crc_buf[2] = (uint8_t)(modbus_reg_addr >> 8);
   crc_buf[3] = (uint8_t)(modbus_reg_addr & 0x00ff);  
   
   switch(modbus_cmd)
   {
    case MODBUS_WSR_CMD:
	reg_wr_data	= (rx_buf[4] << 8) | rx_buf[5]; // get data to write into reg
	
	crc_buf[1] = (uint8_t) MODBUS_WSR_CMD;
	crc_buf[4] = (uint8_t)(reg_wr_data >> 8);
	crc_buf[5] = (uint8_t)(reg_wr_data & 0x00ff);
     break;
     //----
     case MODBUS_RHR_CMD:
	regs2read	= (rx_buf[4] << 8) | rx_buf[5]; // get number of regs to read
    
	crc_buf[1] = (uint8_t) MODBUS_RHR_CMD;
	crc_buf[4] = (uint8_t)(regs2read >> 8);
	crc_buf[5] = (uint8_t)(regs2read & 0x00ff);
     break;
     //----
     case MODBUS_RIR_CMD:
	regs2read	= (rx_buf[4] << 8) | rx_buf[5]; // get number of regs to read
    
	crc_buf[1] = (uint8_t) MODBUS_RIR_CMD;
	crc_buf[4] = (uint8_t)(regs2read >> 8);
	crc_buf[5] = (uint8_t)(regs2read & 0x00ff);
     break;
     //----
     default: break;
   }
   
   CRC16 = (rx_buf[6] << 8) | rx_buf[7]; // get CRC16 from rx msg
   CRC16_calc = modbus_CRC16(crc_buf,6); // calc CRC16  

   if(CRC16_calc == CRC16) 
     ans = modbus_cmd;

   return ans;
  }
    
  
	/* был ли прочитан регистр */
  volatile uint8_t is_reg (uint16_t reg_addr){  
   /// проверка чтения конкретного регистра
   uint16_t t; 
   uint8_t rd_status = 0;

      for(t = modbus_reg_addr; t <= regs2read; t++)
      { 
        if (t == reg_addr) 
	{
	 rd_status = 1;  
	 break;
	}
      }

      //if (reg_addr == (1000 + reg_addr) ) rd_status = 1;
      
      return rd_status;
  }
  
  
	/* парсинг команды и работа с регистрами */
  volatile uint8_t modbus_get_poll(void)  
  {
     /// update modbus regs and vars, send answer to master
     
     // state 1, rx timer overflows
     xSemaphoreTake(RxSemaphore,portMAX_DELAY);
     
     uint8_t rx_cmd_code = 0;        // код поступившей команды

     // ok, Rx timeout - read queue till empty
     while(UartGetQcnt() != 0)
     {
        UartGetByte(&rx_buf[rx_buf_ptr],portMAX_DELAY);
        rx_buf_ptr++;
     }
     
    if(rx_buf_ptr > 7)              // state 2, rx buf has 8 bytes ?
    {
        modbus_id = rx_buf[0];      // get device ID from master msg
		   
    if((modbus_id == dev_id) || (modbus_id == com_dev_id))
    {
    
    switch(rx_buf[1])
    {   
        case MODBUS_RHR_CMD:        // если команда - чтение R/W регистров
            if(modbus_rx_CRC_check(MODBUS_RHR_CMD) == MODBUS_RHR_CMD)
            {
                rx_cmd_code = MODBUS_RHR_CMD;
            }
        break;
////-------------------------------------------------------------------
        case MODBUS_WSR_CMD:       // если команда - чтение Read-only регистров
            if(modbus_rx_CRC_check(MODBUS_WSR_CMD) == MODBUS_WSR_CMD)
            {
                rx_cmd_code = MODBUS_WSR_CMD;
            }
        break;
////-------------------------------------------------------------------
        case MODBUS_RIR_CMD: 
            if(modbus_rx_CRC_check(MODBUS_RIR_CMD) == MODBUS_RIR_CMD)
            {
                rx_cmd_code = MODBUS_RIR_CMD;
            }
        break;
        
        default: break; // rx cmd error 
     } // switch
    }  // if dev_id
//--------------------------------------------------------------------    
  } // if(rx_buf_ptr > 7)
     
  modbus_reset(); // reset modbus sm
  
  return rx_cmd_code;
 }

  
	/* сброс modbus приемника */
  void modbus_reset()
  { 
   
   rx_buf_ptr = 0;
   UartResetQueue();
   
  }
  
  
	/* инициализация */
  void modbus_init (void) 
  {
   /// обнуление регистров
   UartInit();
   modbus_reset();
   RxSemaphore = xSemaphoreCreateCounting(10, 0);
   
   //eeprom_rd_regs_H();
   //eeprom_rd_regs_H(); // !? костыль, если читать 1 раз - всегда все рег.= 0xffff
   //eeprom_rd_regs_I();
  }
  
  
	volatile void holding_reg_write(uint16_t red_addr, uint16_t value)
  {
      holding_register[red_addr] = value;
  }
  
  
	volatile void holding_reg_read(uint16_t red_addr, uint16_t *usr_var_ptr)
  {
     *usr_var_ptr = holding_register[red_addr];
  }
  
  
	volatile void input_reg_read(uint16_t red_addr, uint16_t *usr_var_ptr)
  {
     *usr_var_ptr = input_register[red_addr];
  }
  
  
	volatile void input_reg_write(uint16_t reg_addr, uint16_t value)
  {
      input_register[reg_addr] = value;
  }
 
  
	volatile uint16_t get_wr_reg_addr(void)
  {
      return modbus_reg_addr;
  }
  
  
	volatile uint16_t get_wr_reg_val(void)
  {
      return reg_wr_data;
  }
  
  
	volatile uint8_t get_modbus_id(void)
  {
      uint8_t current_ID = dev_id;
      return current_ID;
  }

  
	volatile void set_modbus_id(uint8_t newID)
  {
      dev_id = newID;
      modbus_reset();
  }
  