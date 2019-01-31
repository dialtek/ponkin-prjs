/*                D I A L T E K    M O D B U S   R T U   v 3.0                */

/* ���������, ���������� � ��������� ������� */

/* ��������� ���������� ������� � ���� dialtek_modbus.� */

//================================ STATE MACHINE ===============================

#define MODBUS_RHR_CMD       0x03     // read holding registers cmd id
#define MODBUS_RIR_CMD       0x04     // read input registers cmd id
#define MODBUS_WSR_CMD       0x06     // write single register cmd id

#define max_regs_cnt         125      // ����. ���-�� ��������� ��� ������ �� 1 ���

//==========================  VARIABLES AND PROTOTYPES  ========================

volatile unsigned char rx_buf_ptr = 0; // ��������� ������ � ������ UART
// ����� ��� ����. ��������� ������
unsigned char rx_buf[32];

unsigned char modbus_cmd = 0; // 0x03 | 0x06 | 0x04

unsigned char rx_byte;       // ���� �������� � ��
 
unsigned char answer = 0;    // ��� ������ �� ������� � ��
unsigned int modbus_reg_addr = 0;       // ����� �������� ��� R/W �� ������� �� modbus �������
unsigned int addr_buf_1 = 0, addr_buf_2 = 0;
unsigned int regs2read = 0;             // ����� ��������� ��� ������ �� ������� modbus rhr
unsigned int CRC16 = 0;			// ���������� ����������� �����
unsigned char  crc_buf[250];            // ����� ��� �������� ������ ��� ������� CRC16

unsigned int reg_wr_data = 0;
unsigned int holding_register[125];  // ����� ��� �������� R/W ���������� ������, ����. ����� ��������� - 124
unsigned int input_register[125];    // ����� ��� �������� Read-only ���������� ������, ����. ����� ��������� - 124

unsigned char rx_flag = 0, timer_state = 0;

void modbus_int_mode (unsigned char mode);     // ���. ������������ MODBUS UART     
void modbus_refresh  (unsigned char cmd_type); // ������ � ����������������� ������������
unsigned char is_reg (unsigned int reg_addr);  // ��� �� �������� �������
void uart_send_byte (unsigned char ch);         // ������� ������ 1 ����� UART
void UART_init();
void Timer9_init(unsigned long);

#include "dialtek_modbus.c"
  
/* ����� modbus ��������� */
  void modbus_reset()
  { 
   for(int i = 0; i < 32; i++) 
        rx_buf[i] = 0;
   
   rx_buf_ptr = 0;
   rx_flag = 0;

  }
  
  /* ������� �������� ��������� */
  void modbus_init (void) {
   /// ��������� ���������
    
   for(unsigned char i = 0; i < 125; i++) 
   {
      holding_register[i] = 0;   // clearing RW resgisters 
      input_register[i] = 0;     // clearing read-only resgisters 
   }
   
   modbus_reset();
   }

  /* ��� �� �������� ������� */
  unsigned char is_reg (unsigned int reg_addr){  
   /// �������� ������ ����������� ��������
    
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
  
  /* ������ 1 ����� ������ */
//  void modbus_uart_byte (unsigned char rx_byte) {
//  /// ����� ����� ������ � ����� 
//  wr_ptr++;               // ��������� �������� ���������� ����
//  rx_buf[wr_ptr & 0x0f] = rx_byte;
//  }
   
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
    // �������� ������ �������
    TX_EN;
    uart_send_byte((unsigned char)dev_id); // ID ����������
    uart_send_byte((unsigned char)MODBUS_WSR_CMD);                     // ��� �������
    uart_send_byte((unsigned char)(modbus_reg_addr >> 8));             // ��. ���� ������ ��������
    uart_send_byte((unsigned char)(modbus_reg_addr & 0x00ff));         // ��. ���� ������ ��������
    uart_send_byte((unsigned char)(reg_wr_data >> 8));
    uart_send_byte((unsigned char)(reg_wr_data & 0x00ff));
     // �������� CRC
    uart_send_byte((unsigned char)(CRC16 >> 8));      // msb
    uart_send_byte((unsigned char)(CRC16 & 0x00ff));  // lsb 
    TX_DIS;
    //--------------------------------------------------------------------
  }
  
  /* ������������ � �������� ������ �� ������� ������ RW ��������� */
  void modbus_rhr_answer() {
    
    /// ����� �� ������� ������ ���������
          addr_buf_1 = modbus_reg_addr; 
  	  addr_buf_2 = addr_buf_1;             // ����. ����� � ���� ����������	  
          // ������ CRC
          crc_buf[0] = dev_id;
          crc_buf[1] = MODBUS_RHR_CMD;
          crc_buf[2] = regs2read*2;
          
          unsigned char cnt = 3;      // �������� �������� ������ ��� ������� CRC

          for(unsigned char j = 0; j < regs2read;j++)
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
          uart_send_byte((unsigned char)dev_id);   // ID ����������
          uart_send_byte((unsigned char)MODBUS_RHR_CMD);                       // ��� �������
          uart_send_byte((unsigned char)regs2read*2);                          // ���-�� ������������ ���� 

          for(unsigned char i = 0; i < regs2read; i++)
          {   // �������� ���� ������ � ����������� ������
            uart_send_byte((unsigned char)(holding_register[addr_buf_2] >> 8));     // msb
            uart_send_byte((unsigned char)(holding_register[addr_buf_2] & 0x00ff)); // lsb
            ++addr_buf_2;
          }
          // �������� CRC
          uart_send_byte((unsigned char)(CRC16 >> 8));      // msb
          uart_send_byte((unsigned char)(CRC16 & 0x00ff));  // lsb  
	  TX_DIS;
          //--------------------------------------------------------------------
  
  }
 
  /* ������������ � �������� ������ �� ������� ������ Read-only ��������� */
  void modbus_rir_answer() {
    
    /// ����� �� ������� ������ input ���������
    
  	  addr_buf_1 = modbus_reg_addr; 
  	  addr_buf_2 = addr_buf_1;             // ����. ����� � ���� ����������		  
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
          uart_send_byte((unsigned char)dev_id);   // ID ����������
          uart_send_byte((unsigned char)MODBUS_RIR_CMD);                       // ��� �������
          uart_send_byte((unsigned char)regs2read*2);                          // ���-�� ������������ ���� 

          for(unsigned char i = 0; i < regs2read; i++)
          {   // �������� ���� ������ � ����������� ������
            uart_send_byte((unsigned char)(input_register[addr_buf_2] >> 8));     // msb
            uart_send_byte((unsigned char)(input_register[addr_buf_2] & 0x00ff)); // lsb
            ++addr_buf_2;
          }
          // �������� CRC
          uart_send_byte((unsigned char)(CRC16 >> 8));      // msb
          uart_send_byte((unsigned char)(CRC16 & 0x00ff));  // lsb   
	  TX_DIS;
          //--------------------------------------------------------------------
  
  }

  /* ������ ����������� ����� ���������� ������� */
  void modbus_rx_CRC_check(unsigned char modbus_cmd) {
  /// ���������� ������� CRC ��� �������� � ��������� � �����������  
   unsigned int CRC16_calc = 0;  // ���������� ����������� �����
   
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
  
  /* ������� ������ */
  void modbus_rx_sm (void) {
  /// ��������� ������
	  
  if(rx_flag)			// state 1, rx timer overflows
  {
   if(rx_buf_ptr == 8)		// state 2, rx buf has 8 bytes ?
   {   
    if(rx_buf[0] == dev_id)     // state 3, ID check 
    {// ID OK

	switch(rx_buf[1])	// state 4, rx buf parsing
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
  
  /* ������� ������� � ������ � ���������� */
  void modbus_poll()  {
    /// update modbus regs and vars, send answer to master
   
    modbus_rx_sm(); // parse rx buffer

    // ���� ������� - ������ R/W ���������
    if(answer == MODBUS_RHR_CMD) 
    {
         modbus_refresh(MODBUS_RHR_CMD);
         modbus_rhr_answer();  
	 answer = 0;     // ����� ����� ���������� ������ �� ������
	 modbus_reset(); 
    }
//--------------------------------------------------------------------
    // ���� ������� - ������ � �������
    if(answer == MODBUS_WSR_CMD) 
    {
         holding_register[modbus_reg_addr] = reg_wr_data; 
         modbus_refresh(MODBUS_WSR_CMD);
         modbus_wsr_answer(); 
	 answer = 0;     // ����� ����� ���������� ������ �� ������
	 modbus_reset();
    }  
//--------------------------------------------------------------------
    // ���� ������� - ������ Read-only ���������
    if(answer == MODBUS_RIR_CMD) 
    {
         modbus_refresh(MODBUS_RIR_CMD);
         modbus_rir_answer();  
	 answer = 0;     // ����� ����� ���������� ������ �� ������
	 modbus_reset();
    }
//--------------------------------------------------------------------    

  }
 

