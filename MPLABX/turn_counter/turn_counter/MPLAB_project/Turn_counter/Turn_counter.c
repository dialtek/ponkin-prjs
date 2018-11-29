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

#define DEFAULT_DEV_ID (unsigned char) 10

unsigned int flag = 0; // ���������� ��� ���������� ����� ����������
unsigned int Buf = 0;  // ���������� ��� �������� �������� �������
unsigned char count = 0;
unsigned int V_detect = 0;

unsigned int turns_percent = 0;
unsigned int turns_percent_press = 0;

unsigned int ADC_cutoff_null;
unsigned int ADC_current_rms = 0;
unsigned int ADC_current_dif = 0;
unsigned int ADC_current_result = 0;
unsigned int ADC_current_max = 0;
unsigned int ADC_current_min = 4096;
unsigned int ADC_RES_BUF;

unsigned int CHANGE_MOTOR = 1;
unsigned int POT_MIN = 400;
unsigned int SET_MIN = 0;
unsigned int POT_MAX = 1600;
unsigned int SET_MAX = 0;
unsigned int GRAD_MAX = 0;
unsigned int TURN_PERCENT_2 = 0;
unsigned int grad_step;  //unsigned int 
unsigned int percent_step;            //unsigned int

unsigned char bd_rate_code = 4;  // default - 115200
unsigned char bd_rate_fl = 0;    // ���� ����� bdrate

unsigned int current_max;
unsigned int overcurrent;
unsigned int read_turns;
unsigned int GRAD_cutoff_null;

unsigned int offset = 0 ;            // �������� ������������� �������������, �������� �� "0"
unsigned int num_of_turns;      // ���������� ��������, �������� �� 100%, �������� �� 1 �� 9 
unsigned int grad;              // ��������� ������� � ��������
unsigned int set_zero;          // ��� ������� �������� ������������� "0"
unsigned int set_zero_error;    // ��� ������ ��������� "0"
unsigned int refresh_offset;    // ���������� �������� "0"

unsigned int eeprom_buf = 0;

unsigned int led_cnt = 65000;       // ������� ���. �����������

void EEPROM_WrByte(unsigned char bAdd, unsigned char bData)
{    
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
    INTCONbits.GIE = 1;
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
#define DETECT_DEV_ID         10      // 10 - �������� id ���������� 
#define GET_CMD_HEADER        11      // 11 - ��������� ���� ������� 
#define GET_MODBUS_WORD_MSB   12      // 12 - ��������� ��. ����� 
#define GET_MODBUS_WORD_LSB   13      // 13 - ��������� ��. �����  
#define GET_REG_CNT_MSB       14      // 14 - ��������� ��. ����� ���. ���.
#define GET_REG_CNT_LSB       15      // 15 - ��������� ��. ����� ���. ���.
#define CALC_CRC1             16      // 16 - ������ �����. ����� 1
#define CALC_CRC2             17      // 17 - ������ �����. ����� 2
#define GET_MODBUS_WORD       18      // 18 ��������� ���.��������

  unsigned char wr_ptr = 0, rd_ptr = 0;   // ???????? ?????? ? ?????? ? ?????? UART
  // ????? ??? ????. ????????? ??????
  static unsigned char rx_buf[32]; //= {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}; 
//============================== RS-485 defines ==============================//

#define MODBUS_RHR_CMD       0x03     // read holding registers cmd id
#define MODBUS_WSR_CMD       0x06     // write single register cmd id

unsigned char dev_id  = DEFAULT_DEV_ID;          // modbus id <<<<<<<<<<========================================= ID
#define firmware_ver    20     // ?????? ???????? ???????? ??????????
#define device_family   10     // ??? ????????? ?????????: 10 - PKT-8
#define max_regs_cnt    125    // ????. ???-?? ????????? ??? ?????? ?? 1 ???
#define meas_status_reg 16     // � ������ �������� ���������� ���������

  unsigned char reg_addr_flag = 0, reg_wr_flag = 0, reg_qty_flag = 0, get_crc_flag = 0;
  unsigned char rx_byte;                  // ???? ???????? ? ??
  unsigned char answer = 0;               // ??? ?????? ?? ??????? ? ??
  unsigned char rd_state = detect_dev_id; // ?????? ????????? ?? ????????? ???? ????????? ?? id ????????? modbus
  unsigned int modbus_reg_addr = 0;     // ????? ???????? ??? R/W ?? ??????? ?? modbus ???????
  unsigned int temp_buf = 0;            // ????????? ?????
  unsigned char id_change = 0;
  
  unsigned int regs2read = 0;           // ????? ????????? ??? ?????? ?? ??????? modbus rhr
  unsigned char  crc_buf[250];            // ????? ??? ???????? ?????? ??? ??????? CRC16
  unsigned int CRC16 = 0;               // ??? ???????? ??????????? ??????????? ?????
  unsigned int addr_buf_1, addr_buf_2;

  unsigned int reg_wr_data = 0;
  unsigned int holding_register[125];  // ����� ��� �������� R/W ���������� ������, ����. ����� ��������� - 124
 
//============================== MODBUS FUNCTIONS ============================//
  // �������� ������� �������� ����� �� UART
  void uart_send_hex(unsigned char temp)
    {
        while (TXSTA1bits.TRMT1 == 0);
      
        // wait to load TXREGx until TRMT is set
       // while(!TXSTA1bits.TRMT1);
         
        TXREG1bits.TXREG1 = temp;
        __delay_us(100);

    }
  
  unsigned char is_reg (unsigned int reg_addr)
  {  
  /// �������� �� ������/������ ������������� ��������
   unsigned char rd_status = 0;
      for(unsigned char t = addr_buf_1; t <= regs2read; t++)
      { // ��� �� �������� ���� ���. � ������� ������
        if (t == reg_addr) rd_status = 1;  
      }
      // ���� ��� �������� ������ ���� �������
      if ( reg_addr == (1000 + reg_addr) ) rd_status = 1;
      
      return rd_status;
  }
 
  ///////////////////////////////////
  
  void modbus_reset()
  { 
   for(int i = 0; i < 32; i++) 
        rx_buf[i] = 0;
   
      //PIE1bits.RC1IE = 0;    // ������ UART recive // UART Int
      wr_ptr=0;                                                                   
      rd_ptr=0;       
      //PIE1bits.RC1IE = 1;    // ���������� UART recive   
  }
  void modbus_refresh(unsigned char cmd_type) {

   // ���������� �������� ��������� ���� ������ ��� !     
  if(cmd_type == MODBUS_RHR_CMD)         // <<<=======================================================
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
        holding_register[10] = turns_percent_press;
        
        // holding_register[10] = ADC_current_dif;
        holding_register[11] = read_turns;
        holding_register[12] = ADC_current_result;
        holding_register[13] = ADC_current_max;
        holding_register[14] = ADC_current_min;
        holding_register[15] = GRAD_cutoff_null;
        holding_register[16] = (unsigned int)bd_rate_code;
        
        holding_register[21] = (unsigned int)dev_id;
        holding_register[25] = (unsigned int)firmware_ver;
        
        holding_register[30] = (unsigned int)CHANGE_MOTOR;
        holding_register[31] = (unsigned int)POT_MIN;
        holding_register[32] = (unsigned int)SET_MIN;
        holding_register[33] = (unsigned int)POT_MAX;
        holding_register[34] = (unsigned int)SET_MAX;
        holding_register[35] = (unsigned int)GRAD_MAX;            // ������������ ���������� ��������, �� ������� ����� �������������� �����
        holding_register[36] = (unsigned int)TURN_PERCENT_2;
                
   }
   //-------------------------------------------------------------------------//
   /// ���������� ���������� �� ���������  <<<=========================================================
   if(cmd_type == MODBUS_WSR_CMD)
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
        case 30: // reg 19 - ID
              CHANGE_MOTOR = (unsigned char)holding_register[30];
              EEPROM_WrByte(13,CHANGE_MOTOR & 0x00ff); // lsb
              EEPROM_WrByte(14,CHANGE_MOTOR >> 8); 
        break;  
        
        case 32: // reg 19 - ID
               SET_MIN = (unsigned char)holding_register[32];
        break;
        
        case 34: // reg 19 - ID
               SET_MAX = (unsigned char)holding_register[34];
        break;
        
        case 35: // reg 19 - ID
               GRAD_MAX = (unsigned int)holding_register[35];
               EEPROM_WrByte(15,GRAD_MAX & 0x00ff); // lsb
               EEPROM_WrByte(16,GRAD_MAX >> 8); 
        break;
        
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
   
           
   if (wr_ptr==rd_ptr && wr_ptr > 15) // ???? ????? ????????                                            
   { 
      //PIE1bits.RC1IE = 0;    // ������ UART recive // UART Int
      wr_ptr=0;                                                                   
      rd_ptr=0;       
      //PIE1bits.RC1IE = 1;    // ���������� UART recive                                                
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
    crc_buf[1] = MODBUS_WSR_CMD;
    crc_buf[2] = (unsigned char)(modbus_reg_addr >> 8);
    crc_buf[3] = (unsigned char)(modbus_reg_addr & 0x00ff);
    crc_buf[4] = (unsigned char)(reg_wr_data >> 8);
    crc_buf[5] = (unsigned char)(reg_wr_data & 0x00ff);
    CRC16 = modbus_CRC16(crc_buf, 6);

    //--------------------------------------------------------------------
    TX_EN;  
    // ???????? ?????? ???????
    uart_send_hex((unsigned char)dev_id);                // ID ??????????
    uart_send_hex(MODBUS_WSR_CMD);        // ??? ???????
    uart_send_hex((unsigned char)(modbus_reg_addr >> 8));           // ??. ???? ?????? ????????
    uart_send_hex((unsigned char)(modbus_reg_addr & 0x00ff));       // ??. ???? ?????? ????????
    uart_send_hex((unsigned char)(reg_wr_data >> 8));
    uart_send_hex((unsigned char)(reg_wr_data & 0x00ff));
     // ???????? CRC
    uart_send_hex((unsigned char)(CRC16 >> 8));      // msb
    uart_send_hex((unsigned char)(CRC16 & 0x00ff));  // lsb  
    __delay_ms(2);       
    TX_DIS;
          //--------------------------------------------------------------------
  }

  void modbus_rhr_answer() {
    // ????? ?? ??????? ?????? ?????????
       addr_buf_2 = addr_buf_1;             // ????. ????? ??? ???????? ? ???? ??????????     
          // ?????? CRC
          crc_buf[0] = dev_id;
          crc_buf[1] = MODBUS_RHR_CMD;
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
          uart_send_hex((unsigned char)dev_id);                // ID ??????????
          uart_send_hex(MODBUS_RHR_CMD);        // ??? ???????
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
          __delay_ms(2);   
          TX_DIS;
          //--------------------------------------------------------------------
  }

   /* ������ ����������� ����� ���������� ������� */
  void modbus_rx_CRC_check(unsigned char modbus_cmd) {
  /// ���������� ������� CRC ��� �������� � ��������� � �����������  
   // ��. 1,4,5 ��������� � rx_sm	
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
   }
   
   get_crc_flag = 0;              // ����� ����� ������� CRC16 
  }
  
  void modbus_rx_sm(){
                  /// ��������� ������� modbus
        //reg_addr_flag = 0, reg_wr_flag = 0, reg_qty_flag = 0, get_crc_flag = 0;
        
       while(rd_ptr < wr_ptr) // ����� �� ����, ������� ���� 
       {                                     
       rx_byte = get_rx_ch();  
              
       switch(rd_state)  // �������� ������� ��������� ������ ������
       {
       //====
         case DETECT_DEV_ID:              // ���� ��������� � ���������� �� ���. ID
           if(rx_byte == dev_id) 
           {
                                          // �������� ������� ��������� �� �������� id ����������
               rd_state = GET_CMD_HEADER; // ������� � ��������� �������� ��������� �������
           }
          break;
       //=====                          
         case GET_CMD_HEADER:             // ������ ������� modbus
           switch (rx_byte)
           { 
             case MODBUS_RHR_CMD:                 // Read Holding Registers 
                  reg_addr_flag = 1;              // ���. ����� ������ ������ ��������
                  regs2read = 0;
                  reg_wr_data = 0;
                  rd_state = GET_MODBUS_WORD_MSB; // ������� � ����. ��������� ���� ���� � ��
	     break;      
             //---- 
             case MODBUS_WSR_CMD:                 // ������ � �������
                  reg_addr_flag = 1;              // ���. ����� ������ ������ ��������
                  reg_wr_flag   = 1;              // ���. ����� ������ � ������� 
                  regs2read = 0;
                  reg_wr_data = 0;
                  rd_state = GET_MODBUS_WORD_MSB; // ������� � ����. ��������� ���� ���� � �� 
             break; 
	     //---- 
         // ������� � ����. ������ id ���������� � ������ ������  
             default: 
		  rd_state = DETECT_DEV_ID;	     
           }
         break;
        //=====
         case GET_MODBUS_WORD_MSB:              // ��������� ��. �����
             temp_buf = (unsigned int)rx_byte;           // ����. ��. ����
             temp_buf = temp_buf << 8;
             rd_state = GET_MODBUS_WORD_LSB;    // ������� � ����. ������ ��. �����
         break;
         //=====
         case GET_MODBUS_WORD_LSB:              // ��������� ��. ����� 
             temp_buf |= (unsigned int)rx_byte;          // ����. ��. ����
             /// ������ ������ ��� ���������� ��������
             if(reg_addr_flag)                 // ���� �������� ���� ������?
             {
               modbus_reg_addr = temp_buf;     // ����. ������ ���������� �������� ��� ������
               reg_addr_flag = 0;              // ����� ����� ������ ������
               if(reg_wr_flag) reg_qty_flag = 0; // ����� ����� ������ ����� ��������� ��� ������ ���� ���� ������� ������             
               else reg_qty_flag = 1;            // ���. ����� ������ ����� ��������� ��� ������ ���� ��� ������
               rd_state = GET_MODBUS_WORD_MSB;   // ������� � ����. ������ 2 ���� ���-�� ��������� ��� ������
               temp_buf = 0;                     // ��������� ���������� ������
               break;
             }
             //---
             if(reg_wr_flag)                   // ���� ������ � �������?
             { 
                reg_wr_data = temp_buf;        // ����. �������� ��� ������
                reg_wr_flag = 0;               // ����� ����� ������ � �������
                get_crc_flag = MODBUS_WSR_CMD; // ���. ���� ������� CRC ��� ������� ������
                rd_state = GET_MODBUS_WORD_MSB;// ������� � ����. ������ 2 ���� CRC
                break;
             }
             //---
             if(reg_qty_flag)                  // ���� ������ ��-�� ��������� ��� ������?
             { 
               if(temp_buf < max_regs_cnt)     // �������� �� ������ ����� ��������� ��� ������
               {  // ��
                regs2read = temp_buf;           // ���������� ����� ��������� ��� ������
                get_crc_flag = MODBUS_RHR_CMD ; // ���. ���� ������� CRC ��� ������� ������
                rd_state = GET_MODBUS_WORD_MSB; // ������� � ����. ������ 2 ���� CRC
               }
                 // ������, ������� � ����. ������ id ����������
               else 
	       {
               rd_state = DETECT_DEV_ID;         
	       }
               reg_qty_flag = 0;                // ����� ����� ������ ���-�� ���������       
               break;
             }
	     //---
	     switch(get_crc_flag)
	     {  // ������������ ������� ��� �������� CRC16
		case MODBUS_WSR_CMD:
		  crc_buf[1] = (unsigned char) MODBUS_WSR_CMD;	
		  crc_buf[4] = (unsigned char)(reg_wr_data >> 8);
          crc_buf[5] = (unsigned char)(reg_wr_data & 0x00ff);
		  modbus_rx_CRC_check(MODBUS_WSR_CMD);
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
  
  void modbus_poll() {
    // update modbus regs and vars, send answer to master
        
        /// on reading cmd
    if(answer == MODBUS_RHR_CMD) // ????? ??? ??????? ?????? ?????????
    {
         addr_buf_1 = modbus_reg_addr - 1000; // ??????????? ?? ???????? ? ??????
         modbus_refresh(MODBUS_RHR_CMD);
         modbus_rhr_answer();    // ??????? ???????? ????????????? ?????????
         answer = 0;   
         modbus_reset();
    }
//--------------------------------------------------------------------
    /// on writing cmd
    if(answer == MODBUS_WSR_CMD) // ????? ??? ??????? ?????? ? ???????
    {   
        addr_buf_1 = modbus_reg_addr - 1000; // ??????????? ?? ???????? ? ??????
         holding_register[addr_buf_1] = reg_wr_data; // ?????? ?????????? ?????? ? ??????? ?? ??????
         modbus_refresh(MODBUS_WSR_CMD);
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
        modbus_reset();
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
  
        ANCON0bits.ANSEL0 = 1;  // ����� 0 ������ ��� ��������������� ��� ���������� ����
        ANCON0bits.ANSEL1 = 1;  // ����� 1 ������ ��� ��������������� ��� ���������� ����
        ANCON1bits.ANSEL8 = 0;  // ����� 8 ������ ��� ��������������� ��� ���������� ����
        ANCON1bits.ANSEL10 = 0; //        
    }   
    void Hold_reg_Inint()
    {
        num_of_turns = 5;
        current_max = 700;
        
    }
    void ADC_Init()
    {
        
        ADCON0bits.GO_nDONE = 0; // �������������� �� ����������� ���� 0
        ADCON0bits.CHS = 0;   // ��������� ������ ���
        ADCON1bits.CHSN = 0;  // ���������������� ���� ���, CHSN = 0 - ������������� ���� ��������� � "0"      
        ADCON1bits.VCFG = 0;  // ����� �������� ���������� 4,096 �
        ADCON1bits.VNCFG = 0; // ������� ������� ����������
        ADCON2bits.ACQT = 2;  //  101 = 12 TAD
        ADCON2bits.ADCS = 1;  // Fosc/32;  // ������� ��������������
        ADCON2bits.ADFM = 1;  // ���������� � 12-������ ������ ���������� � �������� ���������
        //ADRESHbits.ADRESH = 0;// ������������� �������� ��������������  
        ADCON0bits.ADON = 1; // ��� ���
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
       
        TXSTA1bits.SYNC = 0; // ����������� ����� ��������
        TXSTA1bits.TX9 = 0; // ������� 8 ���
        TXSTA1bits.TXEN = 1; // ��� � ���������� ��������
        //TXSTA1bits.BRGH = 0; // �������� �� ������� ��������
        
        
        RCSTA1bits.CREN1 = 1; // �������� ��������
        RCSTA1bits.RX9 = 0; // ����� 8 ���
        RCSTA1bits.SPEN = 1; // ������ ���� ���
        RCSTA1bits.CREN1 = 1; // �������� �������� 
        RCSTA1bits.FERR = 0; // ��� ������ ����������� ��������
        RCSTA1bits.OERR =0;  // ��� ������ ������������ ��������
        

        BAUDCON1bits.RXDTP1 = 0; // ��� ���������� �������� ������ �������������/ �� �������������
        BAUDCON1bits.TXCKP1 = 0; // ��������� ����������� ��� �������� (TXx) �������� ������ �������
        BAUDCON1bits.BRG16 = 0; // 8 ������ Boud Rate ���������
        
        BAUDCON1bits.ABDEN1 = 0; // ��������� �������� �������� ������ ���������
        //BAUDCON1bits.WUE1 = 1; // ���������� ��������� �� ������� ������ ��������� �������
        //PIR1bits.RC1IF = 0;
    }
    void Interrupt_Init()
    {
        RCONbits.IPEN = 0;          // 1 = Enable priority levels on interrupts;  Interrupt Priority Enable bit
        INTCONbits.GIEH = 1;        // ���������� ���������� �������� ������
        INTCONbits.GIEL = 1;        // ���������� ���������� ������� ������ (���������)
        INTCONbits.TMR0IE = 0;      // ���������� �� ������������ (���������)
        
        PIR1bits.ADIF = 0;
        PIE1bits.ADIE = 0;
        
        INTCONbits.RBIE = 0;        // ��������� ���������� ����� RB (���������)
        INTCONbits.RBIF = 0;
    
        INTCONbits.INT0IF = 0;      // ���� �������� ���������� (��������� ���������)
        IOCB = 0;
        INTCON2bits.nRBPU = 1;      // ��� �������� ����� B ���������
        
        INTCON2bits.INTEDG1 = 1;    // ���������� �� ����������� ������ - 1, ���������� - 0
        
        INTCON3bits.INT1IE = 1;     // �������� ������� ���������� INT1
        PIE1bits.RC1IE = 1;         // ���������� UART recive
        //INTCONbits.TMR0IE = 1;      // ���������� �� ������������ ������� 0 
        PIE1bits.TMR1IE = 1;        // ���������� �� ������������ ������� 1
    }
    unsigned int ADC_read()
    {  
       unsigned int ADC_result = 0;
       GO_nDONE = 1;          // ������ ��������������, ����� �������������� �� ������ ������� � 0
       __delay_us(20);
//       unsigned int cn = 0;
//       while (GO_nDONE == 1)
//       {
//           cn++;
//           __nop();
//           if(cn > 500) break;
//
//       }// ���������� ���������� ��������������

       ADC_result = (ADRESH<<8) | ADRESL; // ���������� "�����" �������� � �������� ���������
       PIR1bits.ADIF = 0;
       
       ADC_result &= 0x0fff;
       
       return ADC_result;
    }
    unsigned int ADC_read_turns()
    {
       
        unsigned int adc_turn_result = 0; 
        ADCON0bits.CHS = 0;
        __delay_us(10);
        
        adc_turn_result = ADC_read(); 
        
        return adc_turn_result;
    }  
    void interrupt ISR()
    {
        if(INTCON3bits.INT1IF)
        {     
           
              TMR1L = 0x00;
              TMR1H = 0x0f; //0xC0; - default 
              T1CONbits.TMR1ON = 1;   // �������� ������ 
             // INTCON3bits.INT1IE = 0; //disable interrupt while timer TEST MODE
              V_detect = 1;
              INTCON3bits.INT1IF = 0; // ����� ����� ����������
             
        }
        // ------------------- 
        if (PIR1bits.RC1IF) // uart rx int
            {            
                wr_ptr++;
                rx_buf[wr_ptr & 0x0F] = RCREG1;
            }
        
        if (PIR1bits.TMR1IF)
            {
                T1CONbits.TMR1ON = 0; 
                V_detect = 0;   
                PIR1bits.TMR1IF = 0;
            }
//        
//         if (INTCONbits.TMR0IF) // ���������� �� ������� 6 ms
//         {
//             //modbus_rx_sm();
//             //modbus_poll();
//             holding_register[27]++;
//             TMR0L = 0x0f;
//             TMR0H = 0xff;            
//             // ����� �������
//             INTCONbits.TMR0IF = 0;
//         }

    }      
    void Timer0_init ()
    { 
        T0CONbits.TMR0ON = 0;  // ������
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
        T1CONbits.SOSCEN = 1;  // 1-������������ �� �������� �����������, 0-������������ �� ���� T1CKI 
        T1CONbits.TMR1CS = 0;  // 0 - Fosc/4, 1 - Fosc
        T1CONbits.T1CKPS = 3;  // prescaler 11=1:8, 10=1:4, 01=1:2, 00=1:1
        T1CONbits.nT1SYNC = 0; // 1 - �� ������������������ ����
        
//      TMR1L = 0x01;
//      TMR1H = 0x00;
//      T1CONbits.TMR1ON = 0;  // ������ �������                
    }
    
    void EEprom_restore()
    {
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
        eeprom_buf =  (unsigned int)(0x00ff & EEPROM_RdByte(7));
        eeprom_buf |= (unsigned int)(EEPROM_RdByte(8) << 8);
        if(eeprom_buf >= 4095)
            eeprom_buf = 0;
        offset = eeprom_buf;
        // 
        eeprom_buf = 0x00ff & EEPROM_RdByte(9);
        eeprom_buf |= EEPROM_RdByte(10) << 8;
        if(eeprom_buf > 4095) eeprom_buf = 0;
        POT_MIN = eeprom_buf;
        //
        eeprom_buf = 0x00ff & EEPROM_RdByte(11);
        eeprom_buf |= EEPROM_RdByte(12) << 8;
        if(eeprom_buf > 4095) eeprom_buf = 4095;
        POT_MAX = eeprom_buf;
        //
        eeprom_buf = 0x00ff & EEPROM_RdByte(13);
        eeprom_buf |= EEPROM_RdByte(14) << 8;
        if(eeprom_buf > 2) eeprom_buf = 1;
        CHANGE_MOTOR = eeprom_buf; 
        //
        eeprom_buf = 0x00ff & EEPROM_RdByte(15);
        eeprom_buf |= EEPROM_RdByte(16) << 8;
        if(eeprom_buf > 360) eeprom_buf = 360;
        GRAD_MAX = eeprom_buf; 
        
        
        

    }
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////Main////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

 void main() 
 {
        unsigned int curr_arr[100];
        
        Hold_reg_Inint();
        //Timer0_init();
        Timer1_init();
        GPIO_init();
        TX_DIS;             // ������������ ���� �����������
        ADC_Init();
        EEprom_restore();
        Interrupt_Init();
        
        modbus_reset();    
        for(int i = 0; i < 125; i++) 
            holding_register[i] = 0;
       
        T1CONbits.TMR1ON = 1;  
        
    while(1)
    {      
        modbus_rx_sm();
        modbus_poll();
        
        if(RES_BUT)
        {
            
        }
        else    // ����� �������� �� ���������
        {  
                // �������� 3 ��� - �������� �� ���������� �������
          for(int i = 0; i < 60; i++)  
          {
              __delay_ms(5);
          }
          
          if(RES_BUT) { }
          else 
          {
            dev_id = DEFAULT_DEV_ID;
            bd_rate_code = 4;
            
            UART_Init(bd_rate_code);
            EEPROM_WrByte(1,bd_rate_code);
            EEPROM_WrByte(2,dev_id);
          }
          
        }
        
        ADC_current_max = 0;
        ADC_current_min = 4096;
//------------------------------- ��������� ����---------------------------//
        ADCON0bits.CHS = 9;         // ����� ��������� ����
        __delay_us(10);
        for(int i=0;i<100;i++)
        {
         GO_nDONE = 1;          // ������ ��������������, ����� �������������� �� ������ ������� � 0
         __delay_us (20);       // acquisition delay of 4.6 us

          curr_arr[i] = (ADRESH<<8) | ADRESL; // ���������� "�����" �������� � �������� ���������//ADC_read(); // i
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
        ADC_current_rms = (unsigned int)((ADC_current_dif/2) * 4.27);//122*0.005*7;
       
        ADCON0bits.CHS = 0;
        __delay_us(10);
        GO_nDONE = 1;          // ������ ��������������, ����� �������������� �� ������ ������� � 0
        __delay_us(20);
       
        read_turns = (ADRESH<<8) | ADRESL; // ���������� "�����" �������� � �������� ���������
        PIR1bits.ADIF = 0;
//------------------------------- ��������� ����� ��������---------------------------//
//-------------------------------- �������������� ������ GZ-OF-25/5,5K-----------------------------//     
if(CHANGE_MOTOR == 1)
{
         
        ADCON0bits.CHS = 0;    // ������ ���, ������ ��������� �������.
        __delay_us(10);
        GO_nDONE = 1;          // ������ ��������������, ����� �������������� �� ������ ������� � 0
        __delay_us(20);
       
        GRAD_cutoff_null = (ADRESH<<8) | ADRESL; // ���������� "�����" �������� � �������� ���������
        PIR1bits.ADIF = 0;
        
                
        GRAD_cutoff_null = (GRAD_cutoff_null - offset)*0.879;   //�������� ��������� ������������� � ������� � ������ ��������� "0"
        if((GRAD_cutoff_null < 0)||(GRAD_cutoff_null > 4096))   //
          {
            grad = 0;
          }   
        else    
          {
            grad = GRAD_cutoff_null;
          }
           turns_percent = (grad*10)/((num_of_turns * 3600)/100);      //�������� �������� � �������� ������������ ���������� ���������� ��������
           turns_percent_press = (unsigned int)((grad*10)/(((float)num_of_turns*360.0)/100.0)); ////�������� �������� � �������� � ��������� �� ����������� ����� 100.0%
           
        if(ADC_current_rms > current_max)
         overcurrent = 1;
        else
         overcurrent = 0;
}         
if(CHANGE_MOTOR == 2)
{  
////-------------------------------- ����������������� ������ GZ-OF-9/6K -----------------------------// 
        
          if(SET_MIN)
          {
              
           ADCON0bits.CHS = 0;
           __delay_us(10);
           GO_nDONE = 1;          // ������ ��������������, ����� �������������� �� ������ ������� � 0
           __delay_us(20);
       
           POT_MIN = (ADRESH<<8) | ADRESL; // ���������� "�����" �������� � �������� ���������
           PIR1bits.ADIF = 0;

           EEPROM_WrByte(9,POT_MIN & 0x00ff); // lsb
           __delay_ms(5);
           EEPROM_WrByte(10,POT_MIN >> 8); 
           __delay_ms(5);
           SET_MIN = 0;
          }
        
          if (SET_MAX)
          {
           ADCON0bits.CHS = 0;
           __delay_us(10);
           GO_nDONE = 1;          // ������ ��������������, ����� �������������� �� ������ ������� � 0
           __delay_us(20);
       
           POT_MAX = (ADRESH<<8) | ADRESL; // ���������� "�����" �������� � �������� ���������
           PIR1bits.ADIF = 0;
           
           EEPROM_WrByte(11,POT_MAX & 0x00ff); // lsb
           __delay_ms(5);
           EEPROM_WrByte(12,POT_MAX >> 8); 
           __delay_ms(5);
           SET_MAX = 0;
          }
        
        unsigned long y = 100;  
        grad_step = ((POT_MAX-POT_MIN)*y)/GRAD_MAX;
        percent_step = ((POT_MAX-POT_MIN)*y)/100;     
        
        
           ADCON0bits.CHS = 0;
           __delay_us(10);
           GO_nDONE = 1;          // ������ ��������������, ����� �������������� �� ������ ������� � 0
           __delay_us(20);
       
           ADC_RES_BUF = (ADRESH<<8) | ADRESL; // ���������� "�����" �������� � �������� ���������
           PIR1bits.ADIF = 0;

        if(ADC_RES_BUF < POT_MIN)
        {
            ADC_RES_BUF = POT_MIN;
        }
        
        
        grad = ((ADC_RES_BUF-POT_MIN)*y)/grad_step;
        
        turns_percent = ((ADC_RES_BUF-POT_MIN)*y)/percent_step; 
       
        turns_percent_press = ((ADC_RES_BUF-POT_MIN)*y*10)/percent_step; 
}         
        
        modbus_rx_sm();
        modbus_poll();
        
        led_cnt++;
        if(led_cnt > 5) 
        {
             led_cnt = 0;
             RX_LED_OFF;
             TX_LED_OFF;    
        }  
    
        
         if (set_zero)
        {
            set_zero = 0;
           ADCON0bits.CHS = 0;
           __delay_us(10);
           GO_nDONE = 1;          // ������ ��������������, ����� �������������� �� ������ ������� � 0
           __delay_us(20);
       
           offset = (ADRESH<<8) | ADRESL; // ���������� "�����" �������� � �������� ���������
           PIR1bits.ADIF = 0;
        
           EEPROM_WrByte(7,offset & 0x00ff); // lsb
           __delay_ms(5);
           EEPROM_WrByte(8,offset >> 8); 
           __delay_ms(5);
        }
        
       
    } // while
}//main
