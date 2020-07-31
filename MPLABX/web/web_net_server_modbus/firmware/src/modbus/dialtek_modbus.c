/*                D I A L T E K    M O D B U S   R T U   v 5.1                */
#include "xc.h"
#include "dialtek_modbus.h"
#include "tcp_app.h"

static unsigned int addr_buf_1 = 0, addr_buf_2 = 0;
static unsigned int regs2read = 0; 
static unsigned int CRC16 = 0;	
static unsigned char crc_buf[300];  
static unsigned char modbus_id = 0;	
static unsigned int reg_wr_data = 0;
static unsigned int modbus_reg_addr;   

//static unsigned char answer = 0;

static unsigned int holding_register[125]; 
       unsigned int input_register[125];    
 
/* HARDWARE INFO */

static unsigned char com_dev_id = 247;      
static unsigned char dev_id = 202;     
const char firmware_ver  = 10;          
const char device_family = 0;                
const char modbus_ver    = 41;     

  
  static unsigned int modbus_CRC16(unsigned char buf[], unsigned int len)
  {

    
  unsigned int crc = 0xFFFF;
  //U8 crc_lsb, crc_msb;
  unsigned int pos; 
  for (pos = 0; pos < len; pos++)
  {
    crc ^= (unsigned int)buf[pos];          // XOR byte into least sig. byte of crc
    int i;
    for (i = 8; i != 0; i--)
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
  
  void modbus_wsr_answer() 
  { 
    crc_buf[0] = (modbus_id == dev_id) ? dev_id : com_dev_id;
    crc_buf[1] = (unsigned char) MODBUS_WSR_CMD;
    crc_buf[2] = (unsigned char)(modbus_reg_addr >> 8);
    crc_buf[3] = (unsigned char)(modbus_reg_addr & 0x00ff);
    crc_buf[4] = (unsigned char)(reg_wr_data >> 8);
    crc_buf[5] = (unsigned char)(reg_wr_data & 0x00ff);
    CRC16 = modbus_CRC16(crc_buf, 6);

    if (modbus_reg_addr < 125)
    {
      holding_register[modbus_reg_addr] = reg_wr_data;
    }
    
    //--------------------------------------------------------------------
    //// �������� ������ �������
    //TX_EN;
    //UartSendByte((modbus_id == dev_id) ? dev_id : com_dev_id); // ID ����������
    //UartSendByte((unsigned char)MODBUS_WSR_CMD);                     // ��� �������
    //UartSendByte((unsigned char)(modbus_reg_addr >> 8));             // ��. ���� ������ ��������
    //UartSendByte((unsigned char)(modbus_reg_addr & 0x00ff));         // ��. ���� ������ ��������
    //UartSendByte((unsigned char)(reg_wr_data >> 8));
    //UartSendByte((unsigned char)(reg_wr_data & 0x00ff));
    // // �������� CRC
    //UartSendByte((unsigned char)(CRC16 >> 8));      // msb
    //UartSendByte((unsigned char)(CRC16 & 0x00ff));  // lsb 
    //TX_DIS;
    
    modbus_tx_buf_add((modbus_id == dev_id) ? dev_id : com_dev_id);
    modbus_tx_buf_add((unsigned char)MODBUS_WSR_CMD);
    modbus_tx_buf_add((unsigned char)(modbus_reg_addr >> 8));
    modbus_tx_buf_add((unsigned char)(modbus_reg_addr & 0x00ff));
    modbus_tx_buf_add((unsigned char)(reg_wr_data >> 8));
    modbus_tx_buf_add((unsigned char)(reg_wr_data & 0x00ff));
    
    modbus_tx_buf_add((unsigned char)(CRC16 >> 8));      // msb
    modbus_tx_buf_add((unsigned char)(CRC16 & 0x00ff));  // lsb 
    //--------------------------------------------------------------------
  }
  
  /* ������������ � �������� ������ �� ������� ������ RW ��������� */
  void modbus_rhr_answer()
  {
    
    /// ����� �� ������� ������ ���������
          addr_buf_1 = modbus_reg_addr; 
  	      addr_buf_2 = addr_buf_1;             // ����. ����� � ���� ����������	  
          // ������ CRC
          crc_buf[0] = (modbus_id == dev_id) ? dev_id : com_dev_id;
          crc_buf[1] = MODBUS_RHR_CMD;
          crc_buf[2] = regs2read*2;
          
          unsigned char cnt = 3;      // �������� �������� ������ ��� ������� CRC

          unsigned char j;
          for(j = 0; j < regs2read;j++)
          { // ���������� ������ CRC ��� �������
            crc_buf[cnt++] = (unsigned char)(holding_register[addr_buf_1] >> 8);
            crc_buf[cnt++] = (unsigned char)(holding_register[addr_buf_1] & 0x00ff);
            ++addr_buf_1;  
          }
            // ������ CRC  
          CRC16 = modbus_CRC16(crc_buf,(regs2read*2)+3);
          //--------------------------------------------------------------------
          // �������� ������ ������� 
	      //TX_EN;
          modbus_tx_buf_add((modbus_id == dev_id) ? dev_id : com_dev_id);   // ID ����������
          modbus_tx_buf_add((unsigned char)MODBUS_RHR_CMD);                       // ��� �������
          modbus_tx_buf_add((unsigned char)regs2read*2);                          // ���-�� ������������ ���� 

          unsigned char i;
          for(i = 0; i < regs2read; i++)
          {   // �������� ���� ������ � ����������� ������
            modbus_tx_buf_add((unsigned char)(holding_register[addr_buf_2] >> 8));     // msb
            modbus_tx_buf_add((unsigned char)(holding_register[addr_buf_2] & 0x00ff)); // lsb
            ++addr_buf_2;
          }
          // �������� CRC
          modbus_tx_buf_add((unsigned char)(CRC16 >> 8));      // msb
          modbus_tx_buf_add((unsigned char)(CRC16 & 0x00ff));  // lsb  
	      //TX_DIS;
          //--------------------------------------------------------------------
  
  }
 
  /* ������������ � �������� ������ �� ������� ������ Read-only ��������� */
  void modbus_rir_answer()
  {
    
    /// ����� �� ������� ������ input ���������
    
          addr_buf_1 = modbus_reg_addr; 
          addr_buf_2 = addr_buf_1;             // ����. ����� � ���� ����������		  
          // ������ CRC
          crc_buf[0] = (modbus_id == dev_id) ? dev_id : com_dev_id;
          crc_buf[1] = MODBUS_RIR_CMD;
          crc_buf[2] = regs2read*2;
          
          unsigned char cnt = 3;      // �������� �������� ������ ��� ������� CRC

          unsigned char i;
          for(i = 0; i < regs2read; i++)
          { // ���������� ������ CRC ��� �������
            crc_buf[cnt++] = (unsigned char)(input_register[addr_buf_1] >> 8);
            crc_buf[cnt++] = (unsigned char)(input_register[addr_buf_1] & 0x00ff);
            ++addr_buf_1;  
          }
            // ������ CRC  
          CRC16 = modbus_CRC16(crc_buf,(regs2read*2)+3);
          //--------------------------------------------------------------------
          // �������� ������ ������� 
          //TX_EN;
          modbus_tx_buf_add((modbus_id == dev_id) ? dev_id : com_dev_id);   // ID ����������
          modbus_tx_buf_add((unsigned char)MODBUS_RIR_CMD);                       // ��� �������
          modbus_tx_buf_add((unsigned char)regs2read*2);                          // ���-�� ������������ ���� 
          
          for(i = 0; i < regs2read; i++)
          {   // �������� ���� ������ � ����������� ������
            modbus_tx_buf_add((unsigned char)(input_register[addr_buf_2] >> 8));     // msb
            modbus_tx_buf_add((unsigned char)(input_register[addr_buf_2] & 0x00ff)); // lsb
            ++addr_buf_2;
          }
          // �������� CRC
          modbus_tx_buf_add((unsigned char)(CRC16 >> 8));      // msb
          modbus_tx_buf_add((unsigned char)(CRC16 & 0x00ff));  // lsb   
          //TX_DIS;
          //--------------------------------------------------------------------
  
  }

  /* ������ ����������� ����� ���������� ������� */
  unsigned char modbus_rx_CRC_check(unsigned char modbus_cmd)
  {
  /// ���������� ������� CRC ��� �������� � ��������� � �����������  
   unsigned int CRC16_calc = 0;  // ���������� ����������� �����
   unsigned char ans = 0;
   
   modbus_reg_addr = (unsigned int)((modbus_rx_buf[2] << 8) | modbus_rx_buf[3]); // get starting reg addr
   
   crc_buf[0] = (modbus_id == dev_id) ? dev_id : com_dev_id;
   crc_buf[2] = (unsigned char)(modbus_reg_addr >> 8);
   crc_buf[3] = (unsigned char)(modbus_reg_addr & 0x00ff);  
   
   switch(modbus_cmd)
   {
    case MODBUS_WSR_CMD:
	reg_wr_data	= (modbus_rx_buf[4] << 8) | modbus_rx_buf[5]; // get data to write into reg
	
	crc_buf[1] = (unsigned char) MODBUS_WSR_CMD;
	crc_buf[4] = (unsigned char)(reg_wr_data >> 8);
	crc_buf[5] = (unsigned char)(reg_wr_data & 0x00ff);
     break;
     //----
     case MODBUS_RHR_CMD:
	regs2read	= (modbus_rx_buf[4] << 8) | modbus_rx_buf[5]; // get number of regs to read
    
	crc_buf[1] = (unsigned char) MODBUS_RHR_CMD;
	crc_buf[4] = (unsigned char)(regs2read >> 8);
	crc_buf[5] = (unsigned char)(regs2read & 0x00ff);
     break;
     //----
     case MODBUS_RIR_CMD:
	regs2read	= (modbus_rx_buf[4] << 8) | modbus_rx_buf[5]; // get number of regs to read
    
	crc_buf[1] = (unsigned char) MODBUS_RIR_CMD;
	crc_buf[4] = (unsigned char)(regs2read >> 8);
	crc_buf[5] = (unsigned char)(regs2read & 0x00ff);
     break;
     //----
     default: break;
   }
   
   CRC16 = (modbus_rx_buf[6] << 8) | modbus_rx_buf[7]; // get CRC16 from rx msg
   CRC16_calc = modbus_CRC16(crc_buf,6); // calc CRC16  

   if(CRC16_calc == CRC16) 
     ans = modbus_cmd;

   return ans;
  }
    
  /* ��� �� �������� ������� */
  unsigned char is_reg (unsigned int reg_addr)
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
    TCP_APP_Tasks();
    
    /// update modbus regs and vars, send answer to master
    unsigned char rx_cmd_code = 0;        // ��� ����������� �������rx_cmd_code = 0;
    // state 1 and 2, transmit end, rx buf has > 7 bytes ?
    if((modbus_rx_buf_ptr >= 7))
    { 
        modbus_id = modbus_rx_buf[0];      // get device ID from master msg
		   
     if((modbus_id == dev_id) || (modbus_id == com_dev_id))
     {
      switch(modbus_rx_buf[1])
      {   
        case MODBUS_RHR_CMD:                // ���� ������� - ������ R/W ���������
            if(modbus_rx_CRC_check(MODBUS_RHR_CMD) == MODBUS_RHR_CMD)
            {
                rx_cmd_code = MODBUS_RHR_CMD;
            }
        break;
////-------------------------------------------------------------------
        case MODBUS_WSR_CMD:                // ���� ������� - ������ Read-only ���������
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
     } // switch(rx_buf[1])
      
      modbus_reset();
      
    }  // if dev_id
    else 
    {
        modbus_reset();
    }
   }   //  if(rx_buf_ptr >= 7)
   
   return rx_cmd_code;
    
  }
 
  /* ����� modbus ��������� */
  void modbus_reset(void)
  {
     //for(int i = 0; i < 128; i++) 
     // rx_buf[i] = 0;
   
     //rx_buf_ptr = 0;
     //rx_flag = 0;
     
     modbus_rx_buf_clear();
  }
  
  /* ������������� */
  void modbus_init (void) 
  {
   /// ��������� ���������
   //Uart1Init();
   TCP_APP_Initialize();
   modbus_buf_init();
   
   unsigned char i;
   for(i = 0; i < 125; i++) 
   {
      holding_register[i] = 0;   // clearing RW resgisters 
      input_register[i] = 0;     // clearing read-only resgisters 
   }
   
   modbus_reset();
   }

  void holding_reg_write(unsigned int red_addr, unsigned int value)
  {
      holding_register[red_addr] = value;
  }
  
  void holding_reg_read(unsigned int red_addr, unsigned int *usr_var_ptr)
  {
     *usr_var_ptr = holding_register[red_addr];
  }
  
  void input_reg_read(unsigned int red_addr, unsigned int *usr_var_ptr)
  {
     *usr_var_ptr = input_register[red_addr];
  }
  
  void input_reg_write(unsigned int reg_addr, unsigned int value)
  {
      input_register[reg_addr] = value;
  }
 
  /* ��������� ������ ������������� �������� */
  unsigned int get_wr_reg_addr(void)
  {
      return modbus_reg_addr;
  }
/* 

  unsigned char com_dev_id    = 247;                // MODBUS ID ���������� ��� ������������������ ������, ����� �� ������� 
  unsigned char dev_id        = DEFAULT_DEV_ID;     // MODBUS ID ����������   <<<<<<<<<<======== ID
  unsigned char firmware_ver  = 21;                 // ������ �������� �������� ����������
  unsigned char device_family = 200;                // ��� ��������� ���������
  unsigned char modbus_ver    = 31;                 // ������ MODBUS
  

unsigned int get_syr_pos (unsigned char);
unsigned int get_syr_vel (unsigned char);
unsigned int get_valve_angle (unsigned char);
  


  void modbus_int_mode (unsigned char mode)  
  {      // ���������� ����������� UART RX
  
    if(mode == 1) // ���������� ���������� RX UART MODBUS
    {
      IEC0bits.U1RXIE = 1; // en UART1 RX interrupt   
    }
    else         // ������ ���������� RX UART MODBUS
    {
      IEC0bits.U1RXIE = 0; // dis UART1 RX interrupt   
    }
  }
  
  void modbus_refresh(unsigned char cmd_type) // ������ � ����������
  {     
    
   /// ������ R/W ���������, TODO - ���������� ���������� ����� ��������� �������    
    
   if(cmd_type == MODBUS_RHR_CMD)
   {
     MODBUS_RX_LED = ~MODBUS_RX_LED;  
    //if(is_reg(0)) holding_register[0] = get_syr_pos(1);
    //if(is_reg(1)) holding_register[1] = get_syr_vel(1);
    //if(is_reg(2)) holding_register[2] = get_valve_angle(1);       


    
    //MODBUS_RX_LED = 0;   
   }         
   //-------------------------------------------------------------------------//
   /// ������ Read-only ���������, TODO - ���������� ���������� ����� ��������� �������   
   if(cmd_type == MODBUS_RIR_CMD)
   {   
       MODBUS_RX_LED = ~MODBUS_RX_LED;  
        
       input_register[0] = (unsigned int)dev_id;       
       input_register[1] = (unsigned int)device_family;
       input_register[2] = (unsigned int)firmware_ver;
       
   }         
   //-------------------------------------------------------------------------//
  
   /// ������, TODO - ��������� ����� �������� �� �������
   //  starting_address = ����� ��������, � ������� ���� ������ (1000 = 0, 1001 = 1 � ��)
      
   if(cmd_type == MODBUS_WSR_CMD) 
   {  // ������ �������� ������ 
       
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
*/  
    
  unsigned int get_wr_reg_val(void)
  {
      return reg_wr_data;
  }
  
  unsigned char get_modbus_id(void)
  {
      unsigned char current_ID = dev_id;
      return current_ID;
  }

  void set_modbus_id(unsigned char newID)
  {
      dev_id = newID;
      modbus_reset();
  }
  
 // Modbus
/*=========================================================================== */