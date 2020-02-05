#include "Modbus.h"

volatile unsigned char rx_buf_ptr = 0; // ��������� ������ � ������ UART
// ����� ��� ����. ��������� ������
volatile unsigned char rx_buf[128];

static unsigned int addr_buf_1 = 0, addr_buf_2 = 0;
static unsigned int regs2read = 0;             	// ����� ��������� ��� ������ �� ������� modbus rhr
static unsigned int CRC16 = 0;									// ���������� ����������� �����
static unsigned char crc_buf[300];     					// ����� ��� �������� ������ ��� ������� CRC16
static unsigned char modbus_id = 0;							// ����� ��� �������� ID �� ������� �������
static unsigned int reg_wr_data = 0;
static unsigned int modbus_reg_addr;    				// ����� �������� ��� R/W �� ������� �� modbus �������

static unsigned char answer = 0;

static unsigned int holding_register[125];  // ����� ��� �������� R/W ���������� ������, ����. ����� ��������� - 124
static unsigned int input_register[125];    // ����� ��� �������� Read-only ���������� ������, ����. ����� ��������� - 124
 
/* HARDWARE INFO */

const char com_dev_id    = 247;                // MODBUS ID ���������� ��� ������������������ ������, ����� �� ������� 
static unsigned char dev_id = 100;             // MODBUS ID ����������   <<<<<<<<<<======== ID
const char firmware_ver  = 10;                 // ������ �������� �������� ����������
const char device_family = 0;                  // ��� ��������� ���������
const char modbus_ver    = 41;                 // ������ MODBUS

unsigned char rx_flag = 0;

  /* ������ ����������� ����� */
  static unsigned int modbus_CRC16(unsigned char buf[], unsigned int len)
  {
  /// ������ crc16
    
  unsigned int crc = 0xFFFF;
  //U8 crc_lsb, crc_msb;
  for (unsigned int pos = 0; pos < len; pos++)
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
  volatile void modbus_wsr_answer() 
  { 
    /// ����� �� ������� ������ � �������
    
    // ������ CRC
    crc_buf[0] = (modbus_id == dev_id) ? dev_id : com_dev_id;
    crc_buf[1] = (unsigned char) MODBUS_WSR_CMD;
    crc_buf[2] = (unsigned char)(modbus_reg_addr >> 8);
    crc_buf[3] = (unsigned char)(modbus_reg_addr & 0x00ff);
    crc_buf[4] = (unsigned char)(reg_wr_data >> 8);
    crc_buf[5] = (unsigned char)(reg_wr_data & 0x00ff);
    CRC16 = modbus_CRC16(crc_buf, 6);

    //--------------------------------------------------------------------
    // �������� ������ �������
	  TX_EN;
    UartSendByte((modbus_id == dev_id) ? dev_id : com_dev_id); // ID ����������
    UartSendByte((unsigned char)MODBUS_WSR_CMD);                     // ��� �������
    UartSendByte((unsigned char)(modbus_reg_addr >> 8));             // ��. ���� ������ ��������
    UartSendByte((unsigned char)(modbus_reg_addr & 0x00ff));         // ��. ���� ������ ��������
    UartSendByte((unsigned char)(reg_wr_data >> 8));
    UartSendByte((unsigned char)(reg_wr_data & 0x00ff));
     // �������� CRC
    UartSendByte((unsigned char)(CRC16 >> 8));      // msb
    UartSendByte((unsigned char)(CRC16 & 0x00ff));  // lsb 
    TX_DIS;
    //--------------------------------------------------------------------
  }
  
  /* ������������ � �������� ������ �� ������� ������ RW ��������� */
  volatile void modbus_rhr_answer()
  {
    
    /// ����� �� ������� ������ ���������
          addr_buf_1 = modbus_reg_addr; 
  	      addr_buf_2 = addr_buf_1;             // ����. ����� � ���� ����������	  
          // ������ CRC
          crc_buf[0] = (modbus_id == dev_id) ? dev_id : com_dev_id;
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
          UartSendByte((modbus_id == dev_id) ? dev_id : com_dev_id);   // ID ����������
          UartSendByte((unsigned char)MODBUS_RHR_CMD);                       // ��� �������
          UartSendByte((unsigned char)regs2read*2);                          // ���-�� ������������ ���� 

          for(unsigned char i = 0; i < regs2read; i++)
          {   // �������� ���� ������ � ����������� ������
            UartSendByte((unsigned char)(holding_register[addr_buf_2] >> 8));     // msb
            UartSendByte((unsigned char)(holding_register[addr_buf_2] & 0x00ff)); // lsb
            ++addr_buf_2;
          }
          // �������� CRC
          UartSendByte((unsigned char)(CRC16 >> 8));      // msb
          UartSendByte((unsigned char)(CRC16 & 0x00ff));  // lsb  
					TX_DIS;
          //--------------------------------------------------------------------
  
  }
 
  /* ������������ � �������� ������ �� ������� ������ Read-only ��������� */
  volatile void modbus_rir_answer()
  {
    
    /// ����� �� ������� ������ input ���������
    
          addr_buf_1 = modbus_reg_addr; 
          addr_buf_2 = addr_buf_1;             // ����. ����� � ���� ����������		  
          // ������ CRC
          crc_buf[0] = (modbus_id == dev_id) ? dev_id : com_dev_id;
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
          UartSendByte((modbus_id == dev_id) ? dev_id : com_dev_id);   // ID ����������
          UartSendByte((unsigned char)MODBUS_RIR_CMD);                       // ��� �������
          UartSendByte((unsigned char)regs2read*2);                          // ���-�� ������������ ���� 

          for(unsigned char i = 0; i < regs2read; i++)
          {   // �������� ���� ������ � ����������� ������
            UartSendByte((unsigned char)(input_register[addr_buf_2] >> 8));     // msb
            UartSendByte((unsigned char)(input_register[addr_buf_2] & 0x00ff)); // lsb
            ++addr_buf_2;
          }
          // �������� CRC
          UartSendByte((unsigned char)(CRC16 >> 8));      // msb
          UartSendByte((unsigned char)(CRC16 & 0x00ff));  // lsb   
          TX_DIS;
          //--------------------------------------------------------------------
  
  }

  /* ������ ����������� ����� ���������� ������� */
  static unsigned char modbus_rx_CRC_check(unsigned char modbus_cmd)
  {
  /// ���������� ������� CRC ��� �������� � ��������� � �����������  
   unsigned int CRC16_calc = 0;  // ���������� ����������� �����
   unsigned char ans = 0;
   
   modbus_reg_addr = (unsigned int)((rx_buf[2] << 8) | rx_buf[3]); // get starting reg addr
   
   crc_buf[0] = (modbus_id == dev_id) ? dev_id : com_dev_id;
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
     default: break;
   }
   
   CRC16 = (rx_buf[6] << 8) | rx_buf[7]; // get CRC16 from rx msg
   CRC16_calc = modbus_CRC16(crc_buf,6); // calc CRC16  

   if(CRC16_calc == CRC16) 
     ans = modbus_cmd;

   return ans;
  }
    
  /* ��� �� �������� ������� */
  volatile unsigned char is_reg (unsigned int reg_addr)
  {  
   /// �������� ������ ����������� ��������
   unsigned int t; 
   unsigned char rd_status = 0;

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
  
  /* ������� ������� � ������ � ���������� */
  unsigned char modbus_get_poll(void)  
  {
    /// update modbus regs and vars, send answer to master
   
    // state 1 and 2, transmit end, rx buf has > 7 bytes ?
    if((rx_flag == 1 && rx_buf_ptr > 7)) 
			//if(rx_buf_ptr > 7)
			{ 
					modbus_id = rx_buf[0];      // get device ID from master msg
				 
			 if((modbus_id == dev_id) || (modbus_id == com_dev_id))
			 {
				
				switch(rx_buf[1])
				{   
					case MODBUS_RHR_CMD:                // ���� ������� - ������ R/W ���������
							if(modbus_rx_CRC_check(MODBUS_RHR_CMD) == MODBUS_RHR_CMD);
							{
									modbus_reset();
									return MODBUS_RHR_CMD;
							}
					break;
	////-------------------------------------------------------------------
					case MODBUS_WSR_CMD:                // ���� ������� - ������ Read-only ���������
							if(modbus_rx_CRC_check(MODBUS_WSR_CMD) == MODBUS_WSR_CMD);
							{
									holding_register[modbus_reg_addr] = reg_wr_data;
									modbus_reset();
									return MODBUS_WSR_CMD;
							}
					break;
	////-------------------------------------------------------------------
					case MODBUS_RIR_CMD: 
							if(modbus_rx_CRC_check(MODBUS_RIR_CMD) == MODBUS_RIR_CMD);
							{
									modbus_reset();
									return MODBUS_RIR_CMD;
							}
					break;
					
					default: break;  
			 } // switch(rx_buf[1])
			}  // if dev_id
			else 
			{
					 modbus_reset();
					 return 0;
			}
   }   //  if(rx_buf_ptr > 7)
    else return 0;
    
  }
 
  /* ����� modbus ��������� */
  void modbus_reset(void)
  { 
     for(int i = 0; i < 128; i++) 
      rx_buf[i] = 0;
   
     rx_buf_ptr = 0;
     rx_flag = 0;
  }
  
  /* ������������� */
  void modbus_init (void) 
  {
   /// ��������� ���������
   Uart2Init();
   
//   for(unsigned char i = 0; i < 125; i++) 
//   {
//      holding_register[i] = 0;   // clearing RW resgisters 
//      input_register[i] = 0;     // clearing read-only resgisters 
//   }
   
   modbus_reset();
   }

  volatile void holding_reg_write(unsigned int red_addr, unsigned int value)
  {
      holding_register[red_addr] = value;
  }
  
  volatile void holding_reg_read(unsigned int red_addr, unsigned int *usr_var_ptr)
  {
     *usr_var_ptr = holding_register[red_addr];
  }
  
  volatile void input_reg_read(unsigned int red_addr, unsigned int *usr_var_ptr)
  {
     *usr_var_ptr = input_register[red_addr];
  }
  
  volatile void input_reg_write(unsigned int reg_addr, unsigned int value)
  {
      input_register[reg_addr] = value;
  }
 
  /* ��������� ������ ������������� �������� */
  volatile unsigned int get_wr_reg_addr(void)
  {
      return modbus_reg_addr;
  }


 
	volatile unsigned int get_wr_reg_val(void)
  {
      return reg_wr_data;
  }
  
  volatile unsigned char get_modbus_id(void)
  {
      unsigned char current_ID = dev_id;
      return current_ID;
  }

  volatile void set_modbus_id(unsigned char newID)
  {
      dev_id = newID;
      modbus_reset();
  }
	
	// Modbus
/*=========================================================================== */