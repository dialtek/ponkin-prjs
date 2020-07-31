/*                D I A L T E K    M O D B U S   R T U   v 5.1                */
#include "../h/link.h"
#include "../h/dialtek_modbus.h"

volatile unsigned int rx_buf_ptr = 0; // пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ пїЅ пїЅпїЅпїЅпїЅпїЅпїЅ UART
// пїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅ пїЅпїЅпїЅпїЅ. пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ
volatile unsigned char rx_buf[128];

static unsigned int addr_buf_1 = 0, addr_buf_2 = 0;
static unsigned int regs2read = 0;             // пїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ modbus rhr
static unsigned int CRC16 = 0;			// пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅ
static unsigned char crc_buf[300];      // пїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ CRC16
static unsigned char modbus_id = 0;		// пїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ ID пїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ
static unsigned int reg_wr_data = 0;
static unsigned int modbus_reg_addr;    // пїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅ R/W пїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅ modbus пїЅпїЅпїЅпїЅпїЅпїЅпїЅ

static unsigned char answer = 0;

static unsigned int holding_register[125];  // пїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ R/W пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ, пїЅпїЅпїЅпїЅ. пїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ - 124
       unsigned int input_register[125];    // пїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ Read-only пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ, пїЅпїЅпїЅпїЅ. пїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ - 124
 
/* HARDWARE INFO */

static unsigned char com_dev_id = 247;                // MODBUS ID пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ, пїЅпїЅпїЅпїЅпїЅ пїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ 
static unsigned char dev_id = 1;             // MODBUS ID пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ   <<<<<<<<<<======== ID
const char firmware_ver  = 10;                 // пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ
const char device_family = 0;                  // пїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ
const char modbus_ver    = 51;                 // пїЅпїЅпїЅпїЅпїЅпїЅ MODBUS

unsigned char rx_flag = 0;


  void modbus_get_byte(unsigned char byte)
  {
	rx_buf[rx_buf_ptr++] = byte;
  }
  
  /* пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅ */
  static unsigned int modbus_CRC16(unsigned char buf[], unsigned int len)
  {
  /// пїЅпїЅпїЅпїЅпїЅпїЅ crc16
    
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
  
  /* пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ */
  void modbus_wsr_answer() 
  { 
    /// пїЅпїЅпїЅпїЅпїЅ пїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ пїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ
    
    // пїЅпїЅпїЅпїЅпїЅпїЅ CRC
    crc_buf[0] = (modbus_id == dev_id) ? dev_id : com_dev_id;
    crc_buf[1] = (unsigned char) MODBUS_WSR_CMD;
    crc_buf[2] = (unsigned char)(modbus_reg_addr >> 8);
    crc_buf[3] = (unsigned char)(modbus_reg_addr & 0x00ff);
    crc_buf[4] = (unsigned char)(reg_wr_data >> 8);
    crc_buf[5] = (unsigned char)(reg_wr_data & 0x00ff);
    CRC16 = modbus_CRC16(crc_buf, 6);

    //--------------------------------------------------------------------
    // пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ
    //TX_EN;
    UART_send_byte((modbus_id == dev_id) ? dev_id : com_dev_id); // ID пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ
    UART_send_byte((unsigned char)MODBUS_WSR_CMD);                     // пїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ
    UART_send_byte((unsigned char)(modbus_reg_addr >> 8));             // пїЅпїЅ. пїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ
    UART_send_byte((unsigned char)(modbus_reg_addr & 0x00ff));         // пїЅпїЅ. пїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ
    UART_send_byte((unsigned char)(reg_wr_data >> 8));
    UART_send_byte((unsigned char)(reg_wr_data & 0x00ff));
     // пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ CRC
    UART_send_byte((unsigned char)(CRC16 >> 8));      // msb
    UART_send_byte((unsigned char)(CRC16 & 0x00ff));  // lsb 
    //TX_DIS;
    //--------------------------------------------------------------------
  }
  
  /* пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ RW пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ */
  void modbus_rhr_answer()
  {
    
    /// пїЅпїЅпїЅпїЅпїЅ пїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ
          addr_buf_1 = modbus_reg_addr; 
  	      addr_buf_2 = addr_buf_1;             // пїЅпїЅпїЅпїЅ. пїЅпїЅпїЅпїЅпїЅ пїЅ пїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ	  
          // пїЅпїЅпїЅпїЅпїЅпїЅ CRC
          crc_buf[0] = (modbus_id == dev_id) ? dev_id : com_dev_id;
          crc_buf[1] = MODBUS_RHR_CMD;
          crc_buf[2] = regs2read*2;
          
          unsigned char cnt = 3;      // пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ CRC

          for(unsigned char j = 0; j < regs2read;j++)
          { // пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ CRC пїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ
            crc_buf[cnt++] = (unsigned char)(holding_register[addr_buf_1] >> 8);
            crc_buf[cnt++] = (unsigned char)(holding_register[addr_buf_1] & 0x00ff);
            ++addr_buf_1;  
          }
            // пїЅпїЅпїЅпїЅпїЅпїЅ CRC  
          CRC16 = modbus_CRC16(crc_buf,(regs2read*2)+3);
          //--------------------------------------------------------------------
          // пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ 
	      //TX_EN;
          UART_send_byte((modbus_id == dev_id) ? dev_id : com_dev_id);   // ID пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ
          UART_send_byte((unsigned char)MODBUS_RHR_CMD);                       // пїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ
          UART_send_byte((unsigned char)regs2read*2);                          // пїЅпїЅпїЅ-пїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅ 

          for(unsigned char i = 0; i < regs2read; i++)
          {   // пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ пїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ
            UART_send_byte((unsigned char)(holding_register[addr_buf_2] >> 8));     // msb
            UART_send_byte((unsigned char)(holding_register[addr_buf_2] & 0x00ff)); // lsb
            ++addr_buf_2;
          }
          // пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ CRC
          UART_send_byte((unsigned char)(CRC16 >> 8));      // msb
          UART_send_byte((unsigned char)(CRC16 & 0x00ff));  // lsb  
	      //TX_DIS;
          //--------------------------------------------------------------------
  
  }
 
  /* пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ Read-only пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ */
  void modbus_rir_answer()
  {
    
    /// пїЅпїЅпїЅпїЅпїЅ пїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ input пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ
    
          addr_buf_1 = modbus_reg_addr; 
          addr_buf_2 = addr_buf_1;             // пїЅпїЅпїЅпїЅ. пїЅпїЅпїЅпїЅпїЅ пїЅ пїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ		  
          // пїЅпїЅпїЅпїЅпїЅпїЅ CRC
          crc_buf[0] = (modbus_id == dev_id) ? dev_id : com_dev_id;
          crc_buf[1] = MODBUS_RIR_CMD;
          crc_buf[2] = regs2read*2;
          
          unsigned char cnt = 3;      // пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ CRC

          for(unsigned char i = 0; i < regs2read; i++)
          { // пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ CRC пїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ
            crc_buf[cnt++] = (unsigned char)(input_register[addr_buf_1] >> 8);
            crc_buf[cnt++] = (unsigned char)(input_register[addr_buf_1] & 0x00ff);
            ++addr_buf_1;  
          }
            // пїЅпїЅпїЅпїЅпїЅпїЅ CRC  
          CRC16 = modbus_CRC16(crc_buf,(regs2read*2)+3);
          //--------------------------------------------------------------------
          // пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ 
          //TX_EN;
          UART_send_byte((modbus_id == dev_id) ? dev_id : com_dev_id);   // ID пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ
          UART_send_byte((unsigned char)MODBUS_RIR_CMD);                       // пїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ
          UART_send_byte((unsigned char)regs2read*2);                          // пїЅпїЅпїЅ-пїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅ 

          for(unsigned char i = 0; i < regs2read; i++)
          {   // пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ пїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ
            UART_send_byte((unsigned char)(input_register[addr_buf_2] >> 8));     // msb
            UART_send_byte((unsigned char)(input_register[addr_buf_2] & 0x00ff)); // lsb
            ++addr_buf_2;
          }
          // пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ CRC
          UART_send_byte((unsigned char)(CRC16 >> 8));      // msb
          UART_send_byte((unsigned char)(CRC16 & 0x00ff));  // lsb   
          //TX_DIS;
          //--------------------------------------------------------------------
  
  }

  /* пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ */
  unsigned char modbus_rx_CRC_check(unsigned char modbus_cmd)
  {
  /// пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ CRC пїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ  
   unsigned int CRC16_calc = 0;  // пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅ
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
    
  /* пїЅпїЅпїЅ пїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ */
  unsigned char is_reg (unsigned int reg_addr)
  {  
   /// пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ
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
  
  /* пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅ пїЅпїЅпїЅпїЅпїЅпїЅ пїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ */
  unsigned char modbus_get_poll(void)  
  {
    /// update modbus regs and vars, send answer to master
    unsigned char rx_cmd_code = 0;        // код поступившей командыrx_cmd_code = 0;
    // state 1 and 2, transmit end, rx buf has > 7 bytes ?
    if(rx_buf_ptr > 7) // (rx_flag == 1 && rx_buf_ptr > 7) 
    { 
        modbus_id = rx_buf[0];      // get device ID from master msg
		   
     if((modbus_id == dev_id) || (modbus_id == com_dev_id))
     {
    
      switch(rx_buf[1])
      {   
        case MODBUS_RHR_CMD:                // пїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ - пїЅпїЅпїЅпїЅпїЅпїЅ R/W пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ
            if(modbus_rx_CRC_check(MODBUS_RHR_CMD) == MODBUS_RHR_CMD)
            {
                rx_cmd_code = MODBUS_RHR_CMD;
            }
        break;
////-------------------------------------------------------------------
        case MODBUS_WSR_CMD:                // пїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ - пїЅпїЅпїЅпїЅпїЅпїЅ Read-only пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ
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
   }   //  if(rx_buf_ptr > 7)
   
   return rx_cmd_code;
    
  }
 
  /* пїЅпїЅпїЅпїЅпїЅ modbus пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ */
  void modbus_reset(void)
  {

     for(int i = 0; i < 128; i++) 
      rx_buf[i] = 0;
   
     rx_buf_ptr = 0;
     rx_flag = 0;
  }
  
  /* пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ */
  void modbus_init (void) 
  {
   /// пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ
   UART_init(4);
   
//   for(unsigned char i = 0; i < 125; i++) 
//   {
//      holding_register[i] = 0;   // clearing RW resgisters 
//      input_register[i] = 0;     // clearing read-only resgisters 
//   }
   
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
 
  /* пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ */
  unsigned int get_wr_reg_addr(void)
  {
      return modbus_reg_addr;
  }
/* 

  unsigned char com_dev_id    = 247;                // MODBUS ID пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ, пїЅпїЅпїЅпїЅпїЅ пїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ 
  unsigned char dev_id        = DEFAULT_DEV_ID;     // MODBUS ID пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ   <<<<<<<<<<======== ID
  unsigned char firmware_ver  = 21;                 // пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ
  unsigned char device_family = 200;                // пїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ
  unsigned char modbus_ver    = 31;                 // пїЅпїЅпїЅпїЅпїЅпїЅ MODBUS
  

unsigned int get_syr_pos (unsigned char);
unsigned int get_syr_vel (unsigned char);
unsigned int get_valve_angle (unsigned char);
  


  void modbus_int_mode (unsigned char mode)  
  {      // пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ UART RX
  
    if(mode == 1) // пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ RX UART MODBUS
    {
      IEC0bits.U1RXIE = 1; // en UART1 RX interrupt   
    }
    else         // пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ RX UART MODBUS
    {
      IEC0bits.U1RXIE = 0; // dis UART1 RX interrupt   
    }
  }
  
  void modbus_refresh(unsigned char cmd_type) // пїЅпїЅпїЅпїЅпїЅпїЅ пїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ
  {     
    
   /// пїЅпїЅпїЅпїЅпїЅпїЅ R/W пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ, TODO - пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ    
    
   if(cmd_type == MODBUS_RHR_CMD)
   {
     MODBUS_RX_LED = ~MODBUS_RX_LED;  
    //if(is_reg(0)) holding_register[0] = get_syr_pos(1);
    //if(is_reg(1)) holding_register[1] = get_syr_vel(1);
    //if(is_reg(2)) holding_register[2] = get_valve_angle(1);       


    
    //MODBUS_RX_LED = 0;   
   }         
   //-------------------------------------------------------------------------//
   /// пїЅпїЅпїЅпїЅпїЅпїЅ Read-only пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ, TODO - пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ   
   if(cmd_type == MODBUS_RIR_CMD)
   {   
       MODBUS_RX_LED = ~MODBUS_RX_LED;  
        
       input_register[0] = (unsigned int)dev_id;       
       input_register[1] = (unsigned int)device_family;
       input_register[2] = (unsigned int)firmware_ver;
       
   }         
   //-------------------------------------------------------------------------//
  
   /// пїЅпїЅпїЅпїЅпїЅпїЅ, TODO - пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ
   //  starting_address = пїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ, пїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ (1000 = 0, 1001 = 1 пїЅ пїЅпїЅ)
      
   if(cmd_type == MODBUS_WSR_CMD) 
   {  // пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ 
       
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