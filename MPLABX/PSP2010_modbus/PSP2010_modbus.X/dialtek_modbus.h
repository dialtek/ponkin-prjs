/*                D I A L T E K    M O D B U S   R T U   v 2.1               */

/* ���������, ���������� � ��������� ������� */

/* ��������� ���������� ������� � ���� dialtek_modbus.� */

//================================ STATE MACHINE ===============================
  
#define DETECT_DEV_ID         10      // 10 - �������� id ���������� 
#define GET_CMD_HEADER        11      // 11 - ��������� ���� ������� 
#define GET_MODBUS_WORD_MSB   12      // 12 - ��������� ��. ����� 
#define GET_MODBUS_WORD_LSB   13      // 13 - ��������� ��. �����  
#define GET_REG_CNT_MSB       14      // 14 - ��������� ��. ����� ���. ���.
#define GET_REG_CNT_LSB       15      // 15 - ��������� ��. ����� ���. ���.
#define CALC_CRC1             16      // 16 - ������ �����. ����� 1
#define CALC_CRC2             17      // 17 - ������ �����. ����� 2
#define GET_MODBUS_WORD       18      // 18 ��������� ���.��������

#define MODBUS_RHR_CMD       0x03     // read holding registers cmd id
#define MODBUS_RIR_CMD       0x04     // read input registers cmd id
#define MODBUS_WSR_CMD       0x06     // write single register cmd id

#define EXC_ILLEG_FUNC       0x01     // ��� ������ ��� ������� ������� �� ���������������� ����������� 
#define EXC_REG_QTY	     0x03     // ��� ������ ��� �� ������ ����� ��������� ��� ������
#define EXC_CRC_ERR	     0x04     // ��� ������ ��� �������� CRC

#define max_regs_cnt         125      // ����. ���-�� ��������� ��� ������ �� 1 ���

//==========================  VARIABLES AND PROTOTYPES  ========================

unsigned char wr_ptr = 0, rd_ptr = 0; // ��������� ������ � ������ � ������ UART
// ����� ��� ����. ��������� ������
unsigned char rx_buf[128]; //= {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}; 

// ����� ������������� ��������� state-machine 
unsigned char reg_addr_flag = 0;  
unsigned char ID_flag = 0;     // 0 - ���. ID, 1 - ����������������� 
unsigned char reg_wr_flag = 0;
unsigned char rir_flag = 0;    // read input regs cmd flag
unsigned char reg_qty_flag = 0;
unsigned char get_crc_flag = 0;

unsigned char rx_byte;       // ���� �������� � ��
 
unsigned char answer = 0;    // ��� ������ �� ������� � ��
unsigned char rd_state = DETECT_DEV_ID; // ������ ��������� �� ��������� ���� ��������� �� id ��������� modbus
unsigned int modbus_reg_addr = 0;       // ����� �������� ��� R/W �� ������� �� modbus �������
unsigned int temp_buf = 0;              // ��������� �����
 
unsigned int regs2read = 0;             // ����� ��������� ��� ������ �� ������� modbus rhr
unsigned char  crc_buf[250];            // ����� ��� �������� ������ ��� ������� CRC16
unsigned int CRC16 = 0;                 // ��� �������� ����������� ����������� �����
unsigned int addr_buf_1, addr_buf_2;

unsigned int reg_wr_data = 0;
unsigned int holding_register[125];  // ����� ��� �������� R/W ���������� ������, ����. ����� ��������� - 124
unsigned int input_register[125];    // ����� ��� �������� Read-only ���������� ������, ����. ����� ��������� - 124

void modbus_int_mode (unsigned char mode);     // ���. ������������ MODBUS UART     
void modbus_refresh  (unsigned char cmd_type); // ������ � ����������������� ������������
unsigned char is_reg (unsigned int reg_addr);  // ��� �� �������� �������
void uart_send_hex (unsigned char ch);         // ������� ������ 1 ����� UART

#define DEFAULT_DEV_ID (unsigned char) 70
#define MODBUS_RX_LED LATBbits.LATB0 // LED_RX_485
#define MODBUS_TX_LED LATBbits.LATB1 // LED_TX_485

#include "dialtek_modbus.c"

  /* ������� �������� ��������� */
  void modbus_init (void) {
   /// ��������� ���������
    
   for(unsigned char i = 0; i < 124; i++) 
   {
      holding_register[i] = 0;    // clearing RW resgisters 
      input_register[i]   = 0;    // clearing read-only resgisters 
   }
   }
  
  void modbus_reset(void)
  { 
   for(int i = 0; i < 126; i++) 
        rx_buf[i] = 0;
   
      //PIE1bits.RC1IE = 0;    // ������ UART recive // UART Int
      wr_ptr=0;                                                                   
      rd_ptr=0;       
      //PIE1bits.RC1IE = 1;    // ���������� UART recive   
  }
  
  /* ��� �� �������� ������� */
  unsigned char is_reg (unsigned int reg_addr){  
   /// �������� ������ ����������� ��������
    
   unsigned char rd_status = 0;
   
      for(unsigned int t = addr_buf_1; t <= regs2read; t++)
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
  
  /* ������ 1 ����� ������ */
  void modbus_uart_byte (unsigned char rx_byte) {
  /// ����� ����� ������ � ����� 
  wr_ptr++;               // ��������� �������� ���������� ����
  rx_buf[wr_ptr] = rx_byte;
  }
  
  /* ���������� ������ ��������� */
  char get_rx_ch (void){   
  /// ��������� ����� � ������ ������
    
   char rch;

   if (rd_ptr < wr_ptr) // ����� �� ����
   {
      rd_ptr++;                    // ��������� �������� �������� ����
      rch = rx_buf[rd_ptr]; // ����. �������� �� �������
   }
   else rch = 'x';   
   
   // ������ ���������� �� UART �� ����� ��������� ����������  
   // �� ����. � �����. �������� �������
   //modbus_int_mode(0);
           
   if ((wr_ptr==rd_ptr) && (wr_ptr > 126)) // ���� ����� ��������                                            
   {  
      wr_ptr=0;                                                                   
      rd_ptr=0;                                                       
   } 

   //modbus_int_mode(1);        // ���������� ����������

return rch;
}
  
  /* ������ ����������� ����� */
  unsigned int modbus_CRC16(unsigned char buf[], unsigned int len) {
  /// ������ crc16
    
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
  
  /* ������������ � �������� ������ �� ������� ������ ������ �������� */
  void modbus_wsr_answer() { 
    /// ����� �� ������� ������ � �������
    
    // ������ CRC
    crc_buf[0] = (unsigned char) dev_id;
    crc_buf[1] = (unsigned char) MODBUS_WSR_CMD;
    crc_buf[2] = (unsigned char)(modbus_reg_addr >> 8);
    crc_buf[3] = (unsigned char)(modbus_reg_addr & 0x00ff);
    crc_buf[4] = (unsigned char)(reg_wr_data >> 8);
    crc_buf[5] = (unsigned char)(reg_wr_data & 0x00ff);
    CRC16 = modbus_CRC16(crc_buf, 6);

    //--------------------------------------------------------------------
    IEC1bits.U2RXIE = 0;      // DIS RS232 interrupt
    // �������� ������ �������
    TX_EN;
    uart_send_hex((unsigned char)dev_id); // ID ����������
    uart_send_hex((unsigned char)MODBUS_WSR_CMD);                     // ��� �������
    uart_send_hex((unsigned char)(modbus_reg_addr >> 8));             // ��. ���� ������ ��������
    uart_send_hex((unsigned char)(modbus_reg_addr & 0x00ff));         // ��. ���� ������ ��������
    uart_send_hex((unsigned char)(reg_wr_data >> 8));
    uart_send_hex((unsigned char)(reg_wr_data & 0x00ff));
     // �������� CRC
    uart_send_hex((unsigned char)(CRC16 >> 8));      // msb
    uart_send_hex((unsigned char)(CRC16 & 0x00ff));  // lsb   
    TX_DIS;
    IEC1bits.U2RXIE = 1;      // EN RS232 interrupt
    //--------------------------------------------------------------------
  }
  
  /* ������������ � �������� ������ �� ������� ������ RW ��������� */
  void modbus_rhr_answer() {
    
    /// ����� �� ������� ������ ���������
  	  addr_buf_2 = addr_buf_1;             // ����. ����� ��� �������� � ���� ����������	  
          // ������ CRC
          crc_buf[0] = dev_id;
          crc_buf[1] = MODBUS_RHR_CMD;
          crc_buf[2] = regs2read*2;
          
          unsigned char cnt = 3;      // �������� �������� ������ ��� ������� CRC

          for(unsigned char i = 0; i < regs2read; i++)
          { // ���������� ������ CRC ��� �������
            crc_buf[cnt++] = (unsigned char)(holding_register[addr_buf_1] >> 8);
            crc_buf[cnt++] = (unsigned char)(holding_register[addr_buf_1] & 0x00ff);
            ++addr_buf_1;  
          }
            // ������ CRC  
          CRC16 = modbus_CRC16(crc_buf,(regs2read*2)+3);
          //--------------------------------------------------------------------
          // �������� ������ ������� 
	  TX_EN;
          uart_send_hex((unsigned char)dev_id);   // ID ����������
          uart_send_hex((unsigned char)MODBUS_RHR_CMD);                       // ��� �������
          uart_send_hex((unsigned char)regs2read*2);                          // ���-�� ������������ ���� 

          for(unsigned char i = 0; i < regs2read; i++)
          {   // �������� ���� ������ � ����������� ������
            uart_send_hex((unsigned char)(holding_register[addr_buf_2] >> 8));     // msb
            uart_send_hex((unsigned char)(holding_register[addr_buf_2] & 0x00ff)); // lsb
            ++addr_buf_2;
          }
          // �������� CRC
          uart_send_hex((unsigned char)(CRC16 >> 8));      // msb
          uart_send_hex((unsigned char)(CRC16 & 0x00ff));  // lsb  
	  TX_DIS;
          //--------------------------------------------------------------------
  
  }
 
  /* ������������ � �������� ������ �� ������� ������ Read-only ��������� */
  void modbus_rir_answer() {
    
    /// ����� �� ������� ������ input ���������
    
  	  addr_buf_2 = addr_buf_1;             // ����. ����� ��� �������� � ���� ����������	  
          // ������ CRC
          crc_buf[0] = dev_id;
          crc_buf[1] = MODBUS_RIR_CMD;
          crc_buf[2] = regs2read*2;
          
          unsigned char cnt = 3;      // �������� �������� ������ ��� ������� CRC

          for(unsigned char i = 0; i < regs2read; i++)
          { // ���������� ������ CRC ��� �������
            crc_buf[cnt++] = (unsigned char)(input_register[addr_buf_1] >> 8);
            crc_buf[cnt++] = (unsigned char)(input_register[addr_buf_1] & 0x00ff);
            ++addr_buf_1;  
          }
            // ������ CRC  
          CRC16 = modbus_CRC16(crc_buf,(regs2read*2)+3);
          //--------------------------------------------------------------------
          // �������� ������ ������� 
	  TX_EN;
          uart_send_hex((unsigned char)dev_id);   // ID ����������
          uart_send_hex((unsigned char)MODBUS_RIR_CMD);                       // ��� �������
          uart_send_hex((unsigned char)regs2read*2);                          // ���-�� ������������ ���� 

          for(unsigned char i = 0; i < regs2read; i++)
          {   // �������� ���� ������ � ����������� ������
            uart_send_hex((unsigned char)(input_register[addr_buf_2] >> 8));     // msb
            uart_send_hex((unsigned char)(input_register[addr_buf_2] & 0x00ff)); // lsb
            ++addr_buf_2;
          }
          // �������� CRC
          uart_send_hex((unsigned char)(CRC16 >> 8));      // msb
          uart_send_hex((unsigned char)(CRC16 & 0x00ff));  // lsb   
	  __delay_ms(1);
	  TX_DIS;
          //--------------------------------------------------------------------
  
  }

  /* ������������ � �������� ������ � ������ ������ ������� */
  void modbus_exc_rsp(unsigned char exc_code) {
   /// ����� �������, � ������ ������������� ������ �������
	  
   crc_buf[0] = (unsigned char)(dev_id);     
   crc_buf[1] = (unsigned char)(0x80 | rx_byte); 
   crc_buf[2] = (unsigned char)(0x01); 
   CRC16 = modbus_CRC16(crc_buf,3); 
   TX_EN;		     
   uart_send_hex(dev_id);
   uart_send_hex(0x80 | rx_byte);
   uart_send_hex(exc_code);
   // �������� CRC
   uart_send_hex((unsigned char)(CRC16 >> 8));      // msb
   uart_send_hex((unsigned char)(CRC16 & 0x00ff));  // lsb 
   TX_DIS;
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
     //modbus_exc_rsp(EXC_CRC_ERR);
   }
   
   get_crc_flag = 0;              // ����� ����� ������� CRC16 
  }
  
  /* ������ ��������� ������� ������ */
  void modbus_rx_sm (void) {
    /// ��������� ������
    
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
		  rir_flag = 0;
                  rd_state = GET_MODBUS_WORD_MSB; // ������� � ����. ��������� ���� ���� � ��
	     break;      
             //---- 
             case MODBUS_WSR_CMD:                 // ������ � �������
                  reg_addr_flag = 1;              // ���. ����� ������ ������ ��������
                  reg_wr_flag   = 1;              // ���. ����� ������ � ������� 
                  regs2read = 0;
                  reg_wr_data = 0;
		  rir_flag = 0;
                  rd_state = GET_MODBUS_WORD_MSB; // ������� � ����. ��������� ���� ���� � �� 
             break; 
	     //---- 
             case MODBUS_RIR_CMD:                 // Read Input Registers 
                  reg_addr_flag = 1;              // ���. ����� ������ ������ �������
                  regs2read = 0;
                  reg_wr_data = 0;
		  rir_flag = 1;
                  rd_state = GET_MODBUS_WORD_MSB; // ������� � ����. ��������� ���� ���� � �� 
             break; 
             //---- 
             // ������� � ����. ������ id ���������� � ������ ������  
             default: 
		  //modbus_exc_rsp(EXC_ILLEG_FUNC);    
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
		get_crc_flag = (rir_flag == 0 ? MODBUS_RHR_CMD : MODBUS_RIR_CMD); // ���. ���� ������� CRC ��� ������� ������
                rd_state = GET_MODBUS_WORD_MSB; // ������� � ����. ������ 2 ���� CRC
               }
                 // ������, ������� � ����. ������ id ����������
               else 
	       {
		 rd_state = DETECT_DEV_ID; 
		 //modbus_exc_rsp(EXC_REG_QTY);        
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
		case MODBUS_RIR_CMD:
		  crc_buf[1] = (unsigned char) MODBUS_RIR_CMD;	
                  crc_buf[4] = (unsigned char)(regs2read >> 8);
                  crc_buf[5] = (unsigned char)(regs2read & 0x00ff);
		  modbus_rx_CRC_check(MODBUS_RIR_CMD);
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
  
  /* ������ � ���������� */
  void modbus_poll()  {
    /// update modbus regs and vars, send answer to master
    addr_buf_1 = modbus_reg_addr - 1000; // ����������� �� ��������� � ������
    
    //  ������ R/W ���������
    if(answer == MODBUS_RHR_CMD) 
    {    
	 MODBUS_RX_LED = 1;
	 MODBUS_TX_LED = 1;
         modbus_refresh(MODBUS_RHR_CMD);
         modbus_rhr_answer();  
	 answer = 0;   // ����� ����� ���������� ������ �� ������   
	 modbus_reset(); 
	 
	 __delay_ms(10);
         MODBUS_RX_LED = 0;
	 MODBUS_TX_LED = 0;
    }
//--------------------------------------------------------------------
    // ������ � �������
    if(answer == MODBUS_WSR_CMD) 
    {
	 MODBUS_RX_LED = 1;
	 MODBUS_TX_LED = 1;
	 
         holding_register[addr_buf_1] = reg_wr_data; 
         modbus_refresh(MODBUS_WSR_CMD);
         modbus_wsr_answer();     
	 answer = 0;   // ����� ����� ���������� ������ �� ������   
	 modbus_reset();

         MODBUS_RX_LED = 0;
	 MODBUS_TX_LED = 0;
    }  
//--------------------------------------------------------------------
    // ������ Read-only ���������
    if(answer == MODBUS_RIR_CMD) 
    {    
	 MODBUS_RX_LED = 1;
	 MODBUS_TX_LED = 1;
	 
         modbus_refresh(MODBUS_RIR_CMD);
         modbus_rir_answer();   
	 answer = 0;   // ����� ����� ���������� ������ �� ������   
	 modbus_reset();
	 
	 __delay_ms(10);
         MODBUS_RX_LED = 0;
	 MODBUS_TX_LED = 0;
    }
 //--------------------------------------------------------------------
  }
 


