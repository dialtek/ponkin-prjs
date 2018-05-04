#include <xc.h>
#include "Fuse.h"
#define _XTAL_FREQ 40000000

#define BAUDRATE 
#define UART1BRG (((_XTAL_FREQ / BAUDRATE)/64) - 1) 
#define ANOD_1_ON LATAbits.LATA3=0
#define ANOD_1_OFF LATAbits.LATA3=1
#define ANOD_2_ON LATAbits.LATA2=0
#define ANOD_2_OFF LATAbits.LATA2=1
#define STRB_ON LATCbits.LATC1=1
#define STRB_OFF LATCbits.LATC1=0
#define TX_EN LATCbits.LATC3=1
#define TX_DIS LATCbits.LATC3=0
#define RES_BUT PORTBbits.RB3

#define _ISR_PSV __attribute__((__interrupt__, __auto_psv__))
#define detect_dev_id 10 

#define TX_LED_ON  LATCbits.LATC5 = 1
#define TX_LED_OFF LATCbits.LATC5 = 0

#define RX_LED_ON  LATCbits.LATC4 = 1
#define RX_LED_OFF LATCbits.LATC4 = 0

#define DEFAULT_DEV_ID (unsigned char)10

unsigned int flag = 0; // Переменная для возведения флага прерывания
unsigned int flag_2 = 0; // Переменная для флага прерывания по заднему фронту посыки 
unsigned int Buf = 0; // Переменная для хранения принятой посылки
unsigned char count = 0;
unsigned int V_detect = 0;

unsigned int turns_percent = 0;

volatile unsigned int ADC_cutoff_null;
volatile unsigned int sort_tmp;
volatile unsigned int ADC_current_rms = 0;

volatile unsigned int ADC_current_dif = 0;

volatile unsigned int ADC_current_result = 0;
volatile unsigned int ADC_current_max = 0;
volatile unsigned int ADC_current_min = 4096;

unsigned char bd_rate_code = 4;  // default - 115200
unsigned char bd_rate_fl = 0;    // флаг смены bdrate

unsigned int current_max;
unsigned int overcurrent;
unsigned int read_turns;
unsigned int GRAD_cutoff_null;

unsigned int offset;            // Значение сопротивления потенциометра, принятое за "0"
unsigned int num_of_turns;      // Количество оборотов, принятое за 100%, величина от 1 до 9 
unsigned int grad;              // положение привода в градусах
unsigned int set_zero;          // Бит нажатие которого устанавливает "0"
unsigned int set_zero_error;    // Бит ошибки установки "0"
unsigned int refresh_offset;    // Обновление значения "0"

unsigned int led_cnt = 65000;       // счетчик вкл. светодиодов

void EEPROM_WrByte(unsigned char bAdd, unsigned char bData)
{
//    unsigned char gie_Status;
//    
//    while(WR) { };        // check the WR bit to see if a previous Write operation is in progress
//    EEADR=eepromAddr;     // Write the address to EEADR.
//    EEDATA=eepromData;    // load the 8-bit data value to be written in the EEDATA register.
//    WREN=1;               // Set the WREN bit to enable eeprom operation.
//    gie_Status = GIE;     // Copy the current Interrupt state
//    GIE = 0;              // Disable the interrupts
//    EECON2=0x55;          // Execute the special instruction sequence
//    EECON2=0xaa;          // Refer the datasheet for more info
//    WR=1;                 // Set the WR bit to trigger the eeprom write operation.
//    GIE = gie_Status;     // Restore the interrupts
//    WREN=0;               // Disable the EepromWrite
//    uint8_t a = 0;
//  char GIE_BIT_VAL = 0;
// EEADR = eepromAddr;
//  EEDATA = eepromData;
//  EECON1bits.EEPGD = 0;
// EECON1bits.CFGS = 0;
// EECON1bits.WREN = 1;
// GIE_BIT_VAL = INTCONbits.GIE;
// INTCONbits.GIE = 0;
// EECON2 = 0x55;
// EECON2 = 0xAA;
// EECON1bits.WR = 1;
// while(EECON1bits.WR); //Wait till the write completion
// INTCONbits.GIE = GIE_BIT_VAL;
// EECON1bits.WREN = 0;
    
    
    unsigned char GIEBitsVal = 0;
    
    EEADR = bAdd & 0xff;      // data mem
    EEDATA = bData;
    EECON1bits.EEPGD = 0;
    EECON1bits.CFGS = 0;
    EECON1bits.WREN = 1;
    
    GIEBitsVal = INTCONbits.GIE;
    INTCONbits.GIE = 0;
    EECON2 = 0x55;
    EECON2 = 0xAA;
    EECON1bits.WR = 1;
    while(EECON1bits.WR) {} 
    EECON1bits.WREN = 0;
    INTCONbits.GIE = GIEBitsVal;   
}
    
unsigned char EEPROM_RdByte(unsigned char bAdd)
{
//    while(RD || WR) { };           // check the WR&RD bit to see if a RD/WR is in progress
//    EEADR=eepromAddr;       // Write the address to EEADR.
//    RD = 1;                    // Set the RD bit to trigger the eeprom read operation.
//    return(EEDATA);            // Return the data read form eeprom.
    
 EEADR = bAdd & 0x0ff;
 EECON1bits.CFGS = 0;
 EECON1bits.EEPGD = 0;
 EECON1bits.RD = 1;
 Nop(); //Nop may be required for latency at high frequencies
 Nop(); //Nop may be required for latency at high frequencies
 return EEDATA; // return with read byte
}
    

//****************************************************************************//
//                                  M O D B U S

//================================ state-machine =============================//
     // ??? 0 ????????? ???.????????
#define get_cmd_header     11      // ??? 1 ????????? ???.????????
#define get_modbus_word_msb   12   // ??? 2 ????????? ???.????????
#define get_modbus_word_lsb   13   // ??? 3 ????????? ???.????????
#define get_reg_cnt_msb    14      // ??? 4 ????????? ???.????????
#define get_reg_cnt_lsb    15      // ??? 5 ????????? ???.????????
#define calc_crc1          16      // ??? 6 ????????? ???.????????
#define calc_crc2          17      // ??? 7 ????????? ???.????????
#define get_modbus_word    18      // ??? 8 ????????? ???.????????

  unsigned char wr_ptr = 0, rd_ptr = 0;   // ???????? ?????? ? ?????? ? ?????? UART
  // ????? ??? ????. ????????? ??????
  static unsigned char rx_buf[64];
//============================== RS-485 defines ==============================//

#define modbus_rhr_cmd  0x03   // read holding registers cmd id
#define modbus_wsr_cmd  0x06   // write single register cmd id

#define com_dev_id 0           // ? ????????????????? ?????? ???????????? ????? 0
unsigned char dev_id  = DEFAULT_DEV_ID;          // modbus id <<<<<<<<<<========================================= ID
#define firmware_ver    12     // ?????? ???????? ???????? ??????????
#define device_family   10     // ??? ????????? ?????????: 10 - PKT-8
#define max_regs_cnt    125    // ????. ???-?? ????????? ??? ?????? ?? 1 ???
#define meas_status_reg 16     // № статус регистра обновления измерений

  volatile unsigned char reg_addr_flag = 0, reg_wr_flag = 0, reg_qty_flag = 0, get_crc_flag = 0;
  volatile unsigned char rx_byte;                  // ???? ???????? ? ??
  volatile unsigned char answer = 0;               // ??? ?????? ?? ??????? ? ??
  volatile unsigned char rd_state = detect_dev_id; // ?????? ????????? ?? ????????? ???? ????????? ?? id ????????? modbus
  volatile unsigned int modbus_reg_addr = 0;     // ????? ???????? ??? R/W ?? ??????? ?? modbus ???????
  volatile unsigned int temp_buf = 0;            // ????????? ?????
  volatile unsigned char id_change = 0;
  
  volatile unsigned int regs2read = 0;           // ????? ????????? ??? ?????? ?? ??????? modbus rhr
  static volatile unsigned char  crc_buf[250];            // ????? ??? ???????? ?????? ??? ??????? CRC16
  volatile unsigned int CRC16 = 0;               // ??? ???????? ??????????? ??????????? ?????
  volatile unsigned int addr_buf_1, addr_buf_2;

  volatile unsigned int reg_wr_data = 0;
  static volatile unsigned int holding_register[125];   // ????? ??? ???????? ?????????? ??????, ????. ????? ????????? - 124
  
//============================== MODBUS FUNCTIONS ============================//
  // прототип функции отправки байта по UART
  void uart_send_hex(unsigned char temp)
    {
//      int c = 0;

        while (TXSTA1bits.TRMT1 == 0);
//        {
//            c++;
//            if (c> 499) break;
//            __delay_us(1);
//        }
         
        TXREG1bits.TXREG1 = temp;
        __delay_us(50);
    }
  
  void UART_Init(char bd_rate_code);
   
  unsigned char is_reg (unsigned int reg_addr)
  {  
  /// проверка на чтение/запись определенного регистра
   unsigned char rd_status = 0;
      for(unsigned char t = addr_buf_1; t <= regs2read; t++)
      { // был ли прочитан этот рег. в составе группы
        if (t == reg_addr) rd_status = 1;  
      }
      // если был прочитан только этот регистр
      if ( reg_addr == (1000 + reg_addr) ) rd_status = 1;
      
      return rd_status;
  }
 
  ///////////////////////////////////
  void modbus_refresh(unsigned char cmd_type) {

   // обновление значений регистров надо делать ТУТ !     
  if(cmd_type == modbus_rhr_cmd)         // <<<=======================================================
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
        
       // holding_register[10] = ADC_current_dif;
        holding_register[11] = read_turns;
        holding_register[12] = ADC_current_result;
        holding_register[13] = ADC_current_max;
        holding_register[14] = ADC_current_min;
        holding_register[16] = (unsigned int)bd_rate_code;
        
        holding_register[21] = (unsigned int)dev_id;
        holding_register[25] = (unsigned int)firmware_ver;
                
   }
   //-------------------------------------------------------------------------//
   /// обновление переменных из регистров  <<<=========================================================
   if(cmd_type == modbus_wsr_cmd)
   {    
        switch(addr_buf_1) {  
        case 0: // reg 0 - zero lvl
           set_zero = holding_register[0];
        break;
        //---------
        case 2: // reg 2 - num of turns
           num_of_turns = holding_register[2];
           EEPROM_WrByte(3,num_of_turns & 0x00ff); // lsb

           EEPROM_WrByte(4,num_of_turns >> 8); 
        break;  
        //---------
        case 6: // reg 6 - current_max
           current_max = holding_register[6];  
           EEPROM_WrByte(5,current_max & 0x00ff); // lsb
           EEPROM_WrByte(6,current_max >> 8); 
        break; 
        //---------
        case 16: // reg 16 - baud rate settings
            bd_rate_code = (unsigned char)holding_register[16];
            bd_rate_fl = 1;
        break; 
        //---------
        case 19: // reg 19 - ID
               id_change = 1;
        break;  
         //---------
       default: break;  }
   }
     RX_LED_ON;
     TX_LED_ON;
     led_cnt = 0;
  }

  unsigned char get_rx_ch (void) {                                                     
// Get RX char
  unsigned char rch;

   if (rd_ptr < wr_ptr) // ????? ?? ????
   { 
      rd_ptr++;                    // ????????? ???????? ???????? ????
      rch = rx_buf[rd_ptr & 0x0f]; // ????. ???????? ?? ???????
   }
   else rch = 'x';   
   
   // ?????? ?????????? ?? UART ?? ????? ????????? ??????????  
   // ?? ????. ? ?????. ???????? ???????
   
           
   if (wr_ptr==rd_ptr && wr_ptr > 200) // ???? ????? ????????                                            
   {  //PIE1bits.RC1IE = 0;    // запрет UART recive // UART Int
      wr_ptr=0;                                                                   
      rd_ptr=0;       
      //PIE1bits.RC1IE = 1;    // разрешение UART recive                                                
   } 

    
return rch;
}

  unsigned int modbus_CRC16(unsigned char buf[], unsigned char len)  {//-------crc16
  unsigned int crc = 0xFFFF;
  //unsigned char crc_lsb, crc_msb;
  for (unsigned char pos = 0; pos < len; pos++)
  {
    crc ^= (unsigned int)buf[pos];          // XOR byte into least sig. byte of crc
    for (unsigned char i = 8; i != 0; i--)
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

  void modbus_wsr_answer() { // ????? ?? ??????? ?????? ? ???????
    // ?????? CRC
    crc_buf[0] = dev_id;
    crc_buf[1] = modbus_wsr_cmd;
    crc_buf[2] = (unsigned char)(modbus_reg_addr >> 8);
    crc_buf[3] = (unsigned char)(modbus_reg_addr & 0x00ff);
    crc_buf[4] = (unsigned char)(reg_wr_data >> 8);
    crc_buf[5] = (unsigned char)(reg_wr_data & 0x00ff);
    CRC16 = modbus_CRC16(crc_buf, 6);

    //--------------------------------------------------------------------
    TX_EN;  
    // ???????? ?????? ???????
    __delay_us(20); 
    uart_send_hex((unsigned char)dev_id);                // ID ??????????
    uart_send_hex(modbus_wsr_cmd);        // ??? ???????
    uart_send_hex((unsigned char)(modbus_reg_addr >> 8));           // ??. ???? ?????? ????????
    uart_send_hex((unsigned char)(modbus_reg_addr & 0x00ff));       // ??. ???? ?????? ????????
    uart_send_hex((unsigned char)(reg_wr_data >> 8));
    uart_send_hex((unsigned char)(reg_wr_data & 0x00ff));
     // ???????? CRC
    uart_send_hex((unsigned char)(CRC16 >> 8));      // msb
    uart_send_hex((unsigned char)(CRC16 & 0x00ff));  // lsb  
    __delay_ms(1);       
    TX_DIS;
          //--------------------------------------------------------------------
  }

  void modbus_rhr_answer() {
    // ????? ?? ??????? ?????? ?????????
       addr_buf_2 = addr_buf_1;             // ????. ????? ??? ???????? ? ???? ??????????     
          // ?????? CRC
          crc_buf[0] = dev_id;
          crc_buf[1] = modbus_rhr_cmd;
          crc_buf[2] = regs2read*2;
          
          unsigned char cnt = 3;      // ???????? ???????? ?????? ??? ??????? CRC

          for(unsigned char i = 0; i < regs2read; i++)
          { // ?????????? ?????? CRC ??? ???????
            crc_buf[cnt++] = (unsigned char)(holding_register[addr_buf_1] >> 8);
            crc_buf[cnt++] = (unsigned char)(holding_register[addr_buf_1] & 0x00ff);
            ++addr_buf_1;
          }
            // ?????? CRC  
          CRC16 = modbus_CRC16(crc_buf,(regs2read*2)+3);
          //--------------------------------------------------------------------
          // ???????? ?????? ???????
          TX_EN;
          __delay_us(20); 
          uart_send_hex((unsigned char)dev_id);                // ID ??????????
          uart_send_hex(modbus_rhr_cmd);        // ??? ???????
          uart_send_hex(regs2read*2);           // ???-?? ???????????? ???? 
          for(unsigned char j = 0; j < regs2read; j++)
          {   // ???????? ???? ?????? ? ??????????? ??????
            uart_send_hex((unsigned char)(holding_register[addr_buf_2] >> 8));     // msb
            uart_send_hex((unsigned char)(holding_register[addr_buf_2] & 0x00ff)); // lsb
            ++addr_buf_2;
          }
          // ???????? CRC
          uart_send_hex((unsigned char)(CRC16 >> 8));      // msb
          uart_send_hex((unsigned char)(CRC16 & 0x00ff));  // lsb    
          __delay_ms(1);   
          TX_DIS;
          //--------------------------------------------------------------------
  }

  void modbus_rx_sm(){
                  /// обработка команды modbus
        //reg_addr_flag = 0, reg_wr_flag = 0, reg_qty_flag = 0, get_crc_flag = 0;
        
       while(rd_ptr < wr_ptr) // ????? ?? ????, ??????? ???? 
       {              
       rx_byte = get_rx_ch();
       switch(rd_state)  // ???????? ??????? ????????? ?????? ??????
       {
       //====
         case detect_dev_id:              // ???? ????????? ? ??????????
           if(rx_byte == dev_id) 
           {
                                          // получена команда обращения по текущему id устройтсва
               rd_state = get_cmd_header; // переход в состояние ожидания заголовка команды
               //id_flag = 0;               // уст. режима осн. ID
           }
           if(rx_byte == com_dev_id)      // или широковещательному ID
           {
                                          // получена команда обращения по текущему id устройтсва
               rd_state = get_cmd_header; // переход в состояние ожидания заголовка команды
               //ID_flag = 1;               // уст. режима широковещательного ID
           }
          break;
       //=====                          
         case get_cmd_header:             // ?????? ??????? modbus
           switch (rx_byte)
           { 
             case modbus_rhr_cmd:                 // ?????? ?????????
                  reg_addr_flag = 1;              // ???. ????? ?????? ?????? ????????
                  regs2read = 0;
                  reg_wr_data = 0;
                  rd_state = get_modbus_word_msb; // ??????? ? ????. ????????? ???? ???? ? ??
             break;      
             //---- 
             case modbus_wsr_cmd:                 // ?????? ? ???????
                  reg_addr_flag = 1;              // ???. ????? ?????? ?????? ????????
                  reg_wr_flag   = 1;              // ???. ????? ?????? ? ??????? 
                  regs2read = 0;
                  reg_wr_data = 0;
                  rd_state = get_modbus_word_msb; // ??????? ? ????. ????????? ???? ???? ? ?? 
             break; 
             //---- 
             // ??????? ? ????. ?????? id ?????????? ? ?????? ??????  
             default: rd_state = detect_dev_id;
           }
         break;
        //=====
         case get_modbus_word_msb:              // ????????? ??. ?????
             temp_buf = (unsigned int)rx_byte;           // ????. ??. ????
             temp_buf = temp_buf << 8;
             rd_state = get_modbus_word_lsb;    // ??????? ? ????. ?????? ??. ?????
         break;
         //=====
         case get_modbus_word_lsb:              // ????????? ??. ????? 
             temp_buf |= (unsigned int)rx_byte;          // ????. ??. ????
             /// ?????? ?????? ??? ?????????? ????????
             if(reg_addr_flag)                 // ???? ???????? ???? ???????
             {
               modbus_reg_addr = temp_buf;     // ????. ?????? ?????????? ???????? ??? ??????
               reg_addr_flag = 0;              // ????? ????? ?????? ??????
               if(reg_wr_flag) reg_qty_flag = 0; // ????? ????? ?????? ????? ????????? ??? ?????? ???? ???? ??????? ??????             
               else reg_qty_flag = 1;            // ???. ????? ?????? ????? ????????? ??? ?????? ???? ??? ??????
               rd_state = get_modbus_word_msb;   // ??????? ? ????. ?????? 2 ???? ???-?? ????????? ??? ??????
               temp_buf = 0;                     // ????????? ?????????? ??????
               break;
             }
             
             if(reg_wr_flag)                   // ???? ?????? ? ????????
             { 
                reg_wr_data = temp_buf;        // ????. ???????? ??? ??????
                reg_wr_flag = 0;               // ????? ????? ?????? ? ???????
                get_crc_flag = modbus_wsr_cmd; // ???. ???? ??????? CRC ??? ??????? ??????
                rd_state = get_modbus_word_msb;// ??????? ? ????. ?????? 2 ???? CRC
                break;
             }
             
             if(reg_qty_flag)                  // ???? ?????? ??-?? ????????? ??? ???????
             { 
               if(temp_buf < max_regs_cnt)     // ???????? ?? ?????? ????? ????????? ??? ??????
               {  // ??
                regs2read = temp_buf;           // ?????????? ????? ????????? ??? ??????
                get_crc_flag = modbus_rhr_cmd;  // ???. ???? ??????? CRC ??? ??????? ??????
                rd_state = get_modbus_word_msb; // ??????? ? ????. ?????? 2 ???? CRC
               }
                 // ??????, ??????? ? ????. ?????? id ??????????
               else rd_state = detect_dev_id; 
               reg_qty_flag = 0;                // ????? ????? ?????? ???-?? ?????????       
               break;
             }
             
             if(get_crc_flag == modbus_rhr_cmd)// ?????? CRC16 ??? ??????? ?????? ?????????
             {
                crc_buf[0] = dev_id;
                crc_buf[1] = modbus_rhr_cmd;
                crc_buf[2] = (unsigned char)(modbus_reg_addr >> 8);
                crc_buf[3] = (unsigned char)(modbus_reg_addr & 0x00ff);
                crc_buf[4] = (unsigned char)(regs2read >> 8);
                crc_buf[5] = (unsigned char)(regs2read & 0x00ff);
                CRC16 = modbus_CRC16(crc_buf,6); 
                if(CRC16 == temp_buf) 
                  answer = modbus_rhr_cmd;
                //else rd_state = detect_dev_id; 
                rd_state = detect_dev_id;
                get_crc_flag = 0;              // ????? ????? ??????? CRC16 
             } 
               
             if(get_crc_flag == modbus_wsr_cmd)// ?????? ??? ??????? ?????? ? ???????
             { 
                crc_buf[0] = dev_id;
                crc_buf[1] = modbus_wsr_cmd;
                crc_buf[2] = (unsigned char)(modbus_reg_addr >> 8);
                crc_buf[3] = (unsigned char)(modbus_reg_addr & 0x00ff);
                crc_buf[4] = (unsigned char)(reg_wr_data >> 8);
                crc_buf[5] = (unsigned char)(reg_wr_data & 0x00ff);
             
                CRC16 = modbus_CRC16(crc_buf,6);
                if(CRC16 == temp_buf) 
                  answer = modbus_wsr_cmd;

                get_crc_flag = 0;
                rd_state = detect_dev_id; 
               }
              
         break; 
         //=====
          default: rd_state = detect_dev_id;    
         
        } // switch
      
    }  // if    
        
        
    }
 
  void modbus_reset()
  { 
   for(int i = 0; i < 64; i++) 
        rx_buf[i] = 0;
   
   wr_ptr = 0;
   rd_ptr = 0;
  }
    
  void modbus_poll() {
    // update modbus regs and vars, send answer to master
        
        /// on reading cmd
    if(answer == modbus_rhr_cmd) // ????? ??? ??????? ?????? ?????????
    {
        addr_buf_1 = modbus_reg_addr - 1000; // ??????????? ?? ???????? ? ??????
         modbus_refresh(modbus_rhr_cmd);
         modbus_rhr_answer();    // ??????? ???????? ????????????? ?????????
         answer = 0;   
         modbus_reset();
    }
//--------------------------------------------------------------------
    /// on writing cmd
    if(answer == modbus_wsr_cmd) // ????? ??? ??????? ?????? ? ???????
    {   
        addr_buf_1 = modbus_reg_addr - 1000; // ??????????? ?? ???????? ? ??????
         holding_register[addr_buf_1] = reg_wr_data; // ?????? ?????????? ?????? ? ??????? ?? ??????
         modbus_refresh(modbus_wsr_cmd);
         modbus_wsr_answer();             // ??????? ?????? ?? ??????? ?????? ? ???????
         answer = 0; 
         modbus_reset();

    }  
    
    if(bd_rate_fl) // bdrate change and eeprom wr
    {
        PIE1bits.RC1IE = 0; 
        EEPROM_WrByte(1,bd_rate_code);
        bd_rate_fl = 0;
        modbus_reset();
        PIE1bits.RC1IE = 1; 
        
    }
        
     if(id_change == 1)
     {
        if((dev_id >= 255 )|| (dev_id == 0)) return;
                 
        dev_id = (unsigned char)holding_register[20];
        EEPROM_WrByte(2,dev_id);
        holding_register[19] = 0;
        //dev_id =  EEPROM_RdByte(2);
        id_change = 0;
     }  

  }
 
//                                M O D B U S   E N D 
//****************************************************************************//
    void GPIO_init()
    {
        // Port A
        TRISAbits.TRISA0 = 1; // Pin 2 /ADC_Potentiometr
        TRISAbits.TRISA1 = 0; // NC
        TRISAbits.TRISA2 = 0; // NC
        TRISAbits.TRISA3 = 0; // NC
        // Port B
        TRISBbits.TRISB0 = 0; // NC
        TRISBbits.TRISB1 = 1; // INTERRUPT_1
        TRISBbits.TRISB2 = 1; // NC  
        TRISBbits.TRISB3 = 1; // BUTTON_RESET
        TRISBbits.TRISB4 = 1; // AN9/ ADC_CURRENT
        TRISBbits.TRISB5 = 0; // NC
        // Port C
        TRISCbits.TRISC1 = 0; // NC
        TRISCbits.TRISC2 = 0; // NC
        TRISCbits.TRISC3 = 0; // Pin_14 /TX_EN
        TRISCbits.TRISC4 = 0; // Pin_15 /IO_1
        TRISCbits.TRISC5 = 0; // Pin_16 /IO_2
        TRISCbits.TRISC6 = 0; // Pin_17 /TX_UART
        TRISCbits.TRISC7 = 1; // Pin_18 /RX_UART
  
        ANCON0bits.ANSEL0 = 1;  // Вывод 0 канала АЦП сконфигурирован как аналоговый вход
        ANCON0bits.ANSEL1 = 1;  // Вывод 1 канала АЦП сконфигурирован как аналоговый вход
        ANCON1bits.ANSEL8 = 0;  // Вывод 8 канала АЦП сконфигурирован как аналоговый вход
        ANCON1bits.ANSEL10 = 0; //        
    }   
    void Hold_reg_Inint()
    {
        num_of_turns = 5;
        current_max = 700;
        
    }
    void ADC_Init()
    {
        ADCON0bits.ADON = 1; // Вкл АЦП
        ADCON0bits.GO_nDONE = 0; // Преобразования не выполняются пока 0
        ADCON0bits.CHS = 0;   // Установка канала АЦП
        ADCON1bits.CHSN = 0;  // Дифференциальный вход АЦП, CHSN = 0 - отрицательный вход подключен к "0"      
        ADCON1bits.VCFG = 0;  // Выбор опорного напряжения 4,096 В
        ADCON1bits.VNCFG = 0; // Внешнее опорное напряжение
        ADCON2bits.ACQT = 2;//7;  //  101 = 12 TAD
        ADCON2bits.ADCS = 2; // Fosc/32;  // Частота преобразований
        ADCON2bits.ADFM = 1;  // заполнение в 12-битный ргистр начинается с младшего полубайта
        //ADRESHbits.ADRESH = 0;// Положительные значения преобразования  
    }
    void UART_Init(char bd_rate_code)
    {   
        
        
        switch(bd_rate_code)
        {
            case 0: SPBRG1 = 64;   TXSTA1bits.BRGH = 0; break; // 9600
            case 1: SPBRG1 = 129;  TXSTA1bits.BRGH = 1; break; // 19200
            case 2: SPBRG1 = 64;   TXSTA1bits.BRGH = 1; break; // 38400
            case 3: SPBRG1 = 42;   TXSTA1bits.BRGH = 1; break; // 57600
            case 4: SPBRG1 = 21;   TXSTA1bits.BRGH = 1; break; // 115200
            case 5: SPBRG1 = 10;   TXSTA1bits.BRGH = 1; break; // 230400
            
            default: SPBRG1 = 64;   TXSTA1bits.BRGH = 0; // 9600
        }
       
        //SPBRG1 = 64;//UART1BRG; 57600        // Установка скорости передачи данных
        //SPBRG1 = 10;//10;// 9600

        TXSTA1bits.SYNC = 0; // Асинхронный режим передечи
        TXSTA1bits.TX9 = 0; // Посылка 8 бит
        TXSTA1bits.TXEN = 1; // Бит о готовности передачи
        //TXSTA1bits.BRGH = 0; // Передача на высокой скорости
        
        
        RCSTA1bits.CREN1 = 1; // Включить приемник
        RCSTA1bits.RX9 = 0; // Прием 8 бит
        RCSTA1bits.SPEN = 1; // Сериал порт вкл
        RCSTA1bits.CREN1 = 1; // Включить приемник 
        RCSTA1bits.FERR = 0; // Бит ошибки кодирования отключен
        RCSTA1bits.OERR =0; // Бит ошибки переполнения отключен
        

        BAUDCON1bits.RXDTP1 = 0; // Бит полярности принятых данных инвертируются/ не инвертируются
        BAUDCON1bits.TXCKP1 = 0; // Состояние бездействия для передачи (TXx) является низким уровнем
        BAUDCON1bits.BRG16 = 0; // 8 битный Boud Rate генератор
        
        BAUDCON1bits.ABDEN1 = 0; // Измерение скорости передачи данных отключено
        //BAUDCON1bits.WUE1 = 1; // Генерирует прерыване по заднему фронту пришедшей посылки
        //PIR1bits.RC1IF = 0;
    }
    void Interrupt_Init()
    {
        RCONbits.IPEN = 0;          // 1 = Enable priority levels on interrupts;  Interrupt Priority Enable bit
        INTCONbits.GIEH = 1;        // Разрешение прерываний высокого уровня
        INTCONbits.GIEL = 1;        // Разрешение прерываний низкого уровня (отключено)
        INTCONbits.TMR0IE = 0;      // Прерывания по переполнению (отключено)
        
        INTCONbits.RBIE = 0;        // Разрешить прерывания порта RB (отключено)
        INTCONbits.RBIF = 0;
    
        INTCONbits.INT0IF = 0;      // флаг внешнего прерывания (очищается програмно)
        IOCB = 0;
        INTCON2bits.nRBPU = 1;      // Все подтяжки порта B отключены
        //INTCON2bits.INTEDG0 = 1;  //INT0 Прерывание по нарастающему фронту
        //INT1:
        PIE1bits.ADIE = 0;
        INTCON2bits.INTEDG1 = 1;    // Прерывание по восходящему фронту - 1, спадающему - 0
        
        INTCON3bits.INT1IE = 1;     // Включить внешнее прерывание INT1
        PIE1bits.RC1IE = 1;         // разрешение UART recive
        INTCONbits.TMR0IE = 1;      // разрешение по переполнению таймера 0 
        PIE1bits.TMR1IE = 1;        // разрешение по переполнению таймера 1
    }
    unsigned int ADC_read()
    {  
       unsigned int ADC_result = 0;
       GO_nDONE = 1; // Начало преобразования, после преобразований он скинет регистр в 0
       __delay_us (10);       // acquisition delay of 4.6 us
       while (GO_nDONE == 1){}// Дожидаемся завершения преобразования
       
       ADC_result = (ADRESH<<8) | ADRESL; // Возвращаем "сумму" старшего и младшего полубайта
       
       ADC_result &= 0x0fff;
       
       return ADC_result;
    }
    unsigned int ADC_read_turns()
    {
       
        unsigned int adc_turn_result = 0; 
        ADCON0bits.CHS = 0;
        __delay_us(50);
        
        adc_turn_result = ADC_read(); 
        
        return adc_turn_result;
    }  
    void interrupt ISR()
    {
        if(INTCON3bits.INT1IF)
        {       
              TMR1L = 0x00;
              TMR1H = 0xC0; 
              T1CONbits.TMR1ON = 1;
              
              INTCON3bits.INT1IF = 0;           
        }
        // ------------------- 
        if (PIR1bits.RC1IF) // uart rx int
            {
                if (RCSTA1bits.OERR == 1)
                {
                RCSTA1bits.OERR = 0; // clear overrun if it occurs
                RCSTA1bits.CREN = 0;
                RCSTA1bits.CREN = 1;
                }                
                
                wr_ptr++;
                rx_buf[wr_ptr & 0x0F] = RCREG1;
            }
        
        if (PIR1bits.TMR1IF)
            {
                T1CONbits.TMR1ON = 0; 
                
                if(!PORTBbits.RB1)
                V_detect = 1;
                else
                V_detect = 0;
                PIR1bits.TMR1IF = 0;
            }
//        if (INTCONbits.TMR0IF) // прерывание от таймера 6 ms
//          {
////            led_cnt++;
////            if(led_cnt > 30) 
////            {
////                led_cnt = 0;
////                RX_LED_OFF;
////                TX_LED_OFF;    
////            }  
//            modbus_rx_sm();
//
//
////            // сброс таймера
//             INTCONbits.TMR0IF = 0;
//             TMR0L = 0x0f;
//             TMR0H = 0xff;
////              
//         } 
    }      
    void Timer0_init ()
    { 
        T0CONbits.TMR0ON = 0;  // запуск
        T0CONbits.T08BIT = 0;  //16 bit mode
        T0CONbits.T0CS = 0;    // internal clock 
        T0CONbits.PSA = 0;
        T0CONbits.T0PS = 7;    // prescaler = 256
        TMR0L = 0xff;
        TMR0H = 0x00;
                
    }
    void Timer1_init()
    { 
        T1GCONbits.TMR1GE = 0;
        T1CONbits.SOSCEN = 1;  // 1-тактирование от внешнего осциллятора, 0-тактирование от пина T1CKI 
        T1CONbits.TMR1CS = 0;  // 0 - Fosc/4, 1 - Fosc
        T1CONbits.T1CKPS = 3;  // prescaler 11=1:8, 10=1:4, 01=1:2, 00=1:1
        T1CONbits.nT1SYNC = 0; // 1 - не синхронизированный клок
        
//      TMR1L = 0x01;
//      TMR1H = 0x00;
//      T1CONbits.TMR1ON = 0;  // запуск таймера                
    }
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////Main////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

 void main() 
 {
        unsigned int eeprom_buf = 0;
     
        Hold_reg_Inint();
        //Timer0_init ();
        Timer1_init();
        GPIO_init();
        ADC_Init();
        
        bd_rate_code = EEPROM_RdByte(1);
        if(bd_rate_code > 5)
            bd_rate_code = 4;
        UART_Init(bd_rate_code);
        // offce
        dev_id = EEPROM_RdByte(2);
        if((dev_id >= 255 )|| (dev_id == 0))
            dev_id = DEFAULT_DEV_ID;
        
        // num_of_turns
        eeprom_buf = 0x00ff & EEPROM_RdByte(3);
        eeprom_buf |= EEPROM_RdByte(4) << 8;
        if(eeprom_buf > 9)
            eeprom_buf = 5;
        num_of_turns = eeprom_buf;
        
        // current_max
        eeprom_buf = 0x00ff & EEPROM_RdByte(5);
        eeprom_buf |= EEPROM_RdByte(6) << 8;
        if(eeprom_buf > 1200)
            eeprom_buf = 1000;
        current_max = eeprom_buf;
        
        // offset
        eeprom_buf = 0x00ff & EEPROM_RdByte(7);
        eeprom_buf |= EEPROM_RdByte(8) << 8;
        if(eeprom_buf >= 4095)
            eeprom_buf = 0;
        offset = eeprom_buf;
        
        Interrupt_Init();
        
        modbus_reset();    
        for(int i = 0; i < 125; i++) 
         holding_register[i] = 0;
       
        //T0CONbits.TMR0ON = 1; //Необходим для работы Modbus
        T1CONbits.TMR1ON = 1;  

        static unsigned int curr_arr[100];
        
    while(1)
    {      
        if(RES_BUT)
        {
            
        }
        else    // сброс настроек на заводские
        {   
            dev_id = DEFAULT_DEV_ID;
            bd_rate_code = 4;
            
            UART_Init(bd_rate_code);
            EEPROM_WrByte(1,bd_rate_code);
            EEPROM_WrByte(2,dev_id);
        }
        
        ADC_current_max = 0;
        ADC_current_min = 4096;
        
        ADCON0bits.CHS = 9;         // канал измерения тока
        __delay_us(50);
        for(int i=0;i<100;i++)
        {
          curr_arr[i] = ADC_read();
          __delay_us(200);
        }
             
        
        for(int i=0;i<100;i++)
        {
          if(curr_arr[i] > ADC_current_max)
				ADC_current_max = curr_arr[i];
          
		  if(curr_arr[i] < ADC_current_min)
				ADC_current_min = curr_arr[i];
        }
        
		ADC_current_dif = ADC_current_max - ADC_current_min;       
        ADC_current_rms = (ADC_current_dif/2) * 4.27;//122*0.005*7;
       
        read_turns = ADC_read_turns();


        if (set_zero)
        {
           offset = ADC_read_turns();
           //reg 1 - offset
           EEPROM_WrByte(7,offset & 0x00ff); // lsb
           EEPROM_WrByte(8,offset >> 8); 
        break; 
           set_zero = 0;
        }
                 
        GRAD_cutoff_null = (ADC_read_turns() - offset)*0.879;
        if((GRAD_cutoff_null < 0)||(GRAD_cutoff_null > 4096))
          {
            grad = 0;
          }   
        else    
          {
            grad = GRAD_cutoff_null;
          }
           turns_percent = grad/((num_of_turns * 360)/100);
          
        if(ADC_current_rms > current_max)
        overcurrent = 1;
        else
        overcurrent = 0;
             
       modbus_rx_sm();
       modbus_poll();
        
        led_cnt++;
        if(led_cnt > 5) 
        {
             led_cnt = 0;
             RX_LED_OFF;
             TX_LED_OFF;    
        }  
       
    } // while
}//main
