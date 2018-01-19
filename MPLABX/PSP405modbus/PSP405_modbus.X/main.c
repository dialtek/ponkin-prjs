#include <stdio.h>
#include <stdlib.h>
#include "fuses.h"
#include "p24Hxxxx.h"
#include <timer.h>

#include "c30_delay.h"
#include<uart.h>
#include <p24HJ128GP506A.h>

#define _ISR_PSV __attribute__((__interrupt__, __auto_psv__))
  
#define FCY 40000000UL
#define FP 40000000
#define U1_BAUDRATE 115200
#define U2_BAUDRATE 2400
#define U1BRGVAL ((FP/U1_BAUDRATE)/16)-1
#define U2BRGVAL ((FP/U2_BAUDRATE)/16)-1 

#define MAX_VOLTAGE 40000 // PSP405 max voltage
#define MAX_CURRENT 5000  // PSP405 max current
#define ERROR_CODE 65535  // value on reading error
#define READ_TIMEOUT 1000 // reading timeout in ms 
#define RX_BUF_SIZE 38    // rx buf size 


#define K1_ON LATGbits.LATG12 = 1   // K1 relay ON 
#define K1_OFF LATGbits.LATG12 = 0   // K1 relay OFF 

unsigned char uart2_rx_buf[40] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};   
unsigned char rx_msg[40] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};  
unsigned char uart2_rx_ptr = 0;
unsigned char data_ready = 0;
unsigned int rd_status, rd_voltage = 0, rd_current = 0, 
             rd_voltage_lim = 0, rd_current_lim = 0;


// funcs prototypes
void uart2_text_send(char *s);
void uart_num_send(long data);
// PSP405
unsigned char char2num (unsigned char ch);
unsigned char num2char (unsigned char ch);
unsigned int PSP405_get_voltage();
unsigned int PSP405_get_current();
unsigned int PSP405_get_status();
unsigned int PSP405_get_voltage_lim();
unsigned int PSP405_get_current_lim();
void PSP405_set_output(unsigned int state);

//****************************************************************************//
//                                  M O D B U S
//================================ state-machine =============================//
#define detect_dev_id      10      // ??? 0 ????????? ???.????????
#define get_cmd_header     11      // ??? 1 ????????? ???.????????
#define get_modbus_word_msb   12   // ??? 2 ????????? ???.????????
#define get_modbus_word_lsb   13   // ??? 3 ????????? ???.????????
#define get_reg_cnt_msb    14      // ??? 4 ????????? ???.????????
#define get_reg_cnt_lsb    15      // ??? 5 ????????? ???.????????
#define calc_crc1          16      // ??? 6 ????????? ???.????????
#define calc_crc2          17      // ??? 7 ????????? ???.????????
#define get_modbus_word    18      // ??? 8 ????????? ???.????????
//================================== defines ===================================
#define TX_EN_ON  LATBbits.LATB14=1
#define TX_EN_OFF LATBbits.LATB14=0

#define modbus_rhr_cmd  0x03       // read holding registers cmd id
#define modbus_wsr_cmd  0x06       // write single register cmd id
#define com_dev_id      0          // ? ????????????????? ?????? ???????????? ????? 0
#define dev_id          61         // modbus id ???????? ??????????
#define max_regs_cnt    125        // ????. ???-?? ????????? ??? ?????? ?? 1 ???
//================================= variables ==================================
unsigned char reg_addr_flag = 0;
unsigned char reg_wr_flag = 0;
unsigned char reg_qty_flag = 0;
unsigned char get_crc_flag = 0;

unsigned char rx_byte;                    // ???? ???????? ? ??
unsigned char wr_ptr = 0, rd_ptr = 0;     // ???????? ?????? ? ?????? ? ?????? UART
                                          // ????? ??? ????. ????????? ??????
unsigned char rx_buf[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}; 

unsigned char answer = 0;                 // ??? ?????? ?? ??????? ? ??
unsigned char rd_state = detect_dev_id;   // ?????? ????????? ?? ????????? ???? ????????? ?? id ????????? modbus
unsigned int modbus_reg_addr = 0;         // ????? ???????? ??? R/W ?? ??????? ?? modbus ???????
unsigned int temp_buf = 0;                // ????????? ?????

unsigned int regs2read = 0;               // ????? ????????? ??? ?????? ?? ??????? modbus rhr
unsigned int  crc_buf[250];               // ????? ??? ???????? ?????? ??? ??????? CRC16
unsigned int CRC16 = 0;                   // ??? ???????? ??????????? ??????????? ?????
unsigned int addr_buf_1 = 0, addr_buf_2 = 0;

unsigned int reg_wr_data = 0;
unsigned int holding_register[125];       // ????? ??? ???????? ?????????? ??????, ????. ????? ????????? - 124 
//============================== MODBUS FUNCTIONS ============================//
  // ???????? ??????? ???????? ????? ?? UART
  void uart_send_hex (unsigned char ch);
  
  unsigned char is_reg (unsigned int reg_addr)
  {  
   // ????????, ???? ?? ????????? ? ????????
   unsigned char rd_status = 0;
      for(unsigned int t = addr_buf_1; t <= regs2read; t++)
      { // ??? ?? ???????? ???? ???. ? ??????? ??????
        if (t == reg_addr) 
		{
			rd_status = 1;  
			break;
		}
      }
      // ???? ??? ???????? ?????? ???? ???????
      if ( reg_addr == (1000 + reg_addr) ) rd_status = 1;
      
      return rd_status;
  }
 
  ///////////////////////////////////
  void modbus_refresh(unsigned char cmd_type) 
  {
   // READING, TODO update registers    
  if(cmd_type == modbus_rhr_cmd)
   {   
       holding_register[0] = rd_voltage;
       holding_register[1] = rd_voltage_lim;
       holding_register[2] = rd_current;
       holding_register[3] = rd_current_lim;      
       holding_register[4] = rd_status; // the relay status 0:OFF 1:ON
  }         
   //-------------------------------------------------------------------------//
   /// WRITING, TODO get from registers, addr_buf_1 contauns writing reg addr - 1000(etc. 0,1,2...))
   if(cmd_type == modbus_wsr_cmd)
   {
      switch(addr_buf_1)
      { // ???? ???????? ?????? ?????? ? ?????? ??????!!!!!! 
        case 4: // reg 4 - set output
           PSP405_set_output(holding_register[4]);
        break;
        //---------
        case 7: // reg 7 - set voltage
           if(holding_register[7] > MAX_VOLTAGE) holding_register[7] = MAX_VOLTAGE;
           PSP405_set_voltage(holding_register[7]);
        break;
        //---------
        case 8: // reg 8 - set voltage limit
           if(holding_register[8] > MAX_VOLTAGE/100) holding_register[8] = MAX_VOLTAGE/100;
           PSP405_set_voltage_lim(holding_register[8]);
        break;
        //---------
        case 9: // reg 9 - set current
           if(holding_register[9] > MAX_CURRENT) holding_register[9] = MAX_CURRENT;
           PSP405_set_current(holding_register[9]);
        break;
        //---------
        case 10: // reg 10 - K1 relay ctrl
           PSP405_set_output(0);
           for(unsigned int i = 0; i < 2000; i++) 
             delay_ms(1);
           if     (holding_register[10] == 1) K1_ON;
           else if(holding_register[10] == 0) K1_OFF; 
           for(unsigned int i = 0; i < 100; i++) 
             delay_ms(1);
           PSP405_set_output(1);
        break;
         //---------
       default: break;     
       } 
       for(unsigned int i = 0; i < 400; i++) 
          delay_ms(1);      // ??????????? ????????
   } 
  }
  
  unsigned char get_rx_ch (void)
  {                                                     
// Get RX unsigned char
    unsigned char rch;

   if (rd_ptr < wr_ptr) // ????? ?? ????
   {
      rd_ptr++;                    // ????????? ???????? ???????? ????
      rch = rx_buf[rd_ptr & 0x0f]; // ????. ???????? ?? ???????
   }
   else rch = 'x';   
   
   // ?????? ?????????? ?? UART ?? ????? ????????? ??????????  
   // ?? ????. ? ?????. ???????? ???????
   //IEC0bits.U1RXIE = 0; // dis UART1 RX interrupt   
           
   if ((wr_ptr==rd_ptr) && (wr_ptr > 15)) // ???? ????? ????????                                            
   {  
      wr_ptr=0;                                                                   
      rd_ptr=0;                                                       
   } 

    IEC0bits.U1RXIE = 1; // Enable UART1 RX interrupt
return rch;
}

  unsigned int modbus_CRC16(unsigned int buf[], unsigned char len)
  {//-------crc16
  unsigned int  crc = 0xFFFF;
  //unsigned char crc_lsb, crc_msb;
  unsigned int pos;
  
  for (pos = 0; pos < len; pos++)
  {
    crc ^= (unsigned int )buf[pos];          // XOR byte into least sig. byte of crc
    unsigned int i;
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
  { // ????? ?? ??????? ?????? ? ???????
    
    crc_buf[0] = dev_id;
    crc_buf[1] = modbus_wsr_cmd;
    crc_buf[2] = (unsigned char)(modbus_reg_addr >> 8);
    crc_buf[3] = (unsigned char)(modbus_reg_addr & 0x00ff);
    crc_buf[4] = (unsigned char)(reg_wr_data >> 8);
    crc_buf[5] = (unsigned char)(reg_wr_data & 0x00ff);
    CRC16 = modbus_CRC16(crc_buf, 6); // ?????? CRC

    //--------------------------------------------------------------------
    TX_EN_ON;
    // ???????? ?????? ???????
    uart_send_hex(dev_id);                // ID ??????????
    uart_send_hex(modbus_wsr_cmd);        // ??? ???????
    uart_send_hex((unsigned char)(modbus_reg_addr >> 8));           // ??. ???? ?????? ????????
    uart_send_hex((unsigned char)(modbus_reg_addr & 0x00ff));       // ??. ???? ?????? ????????
    uart_send_hex((unsigned char)(reg_wr_data >> 8));
    uart_send_hex((unsigned char)(reg_wr_data & 0x00ff));
     // ???????? CRC
    uart_send_hex((unsigned char)(CRC16 >> 8));      // msb
    uart_send_hex((unsigned char)(CRC16 & 0x00ff));  // lsb  
    __delay_ms(1);    
    TX_EN_OFF;
          //--------------------------------------------------------------------
  }

  void modbus_rhr_answer()
  {
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
          TX_EN_ON;
          uart_send_hex(dev_id);                // ID ??????????
          uart_send_hex(modbus_rhr_cmd);        // ??? ???????
          uart_send_hex(regs2read*2);           // ???-?? ???????????? ???? 

          for(unsigned char i = 0; i < regs2read; i++)
          {   // ???????? ???? ?????? ? ??????????? ??????
            uart_send_hex((unsigned char)(holding_register[addr_buf_2] >> 8));     // msb
            uart_send_hex((unsigned char)(holding_register[addr_buf_2] & 0x00ff)); // lsb
            ++addr_buf_2;
          }
          // ???????? CRC
          uart_send_hex((unsigned char)(CRC16 >> 8));      // msb
          uart_send_hex((unsigned char)(CRC16 & 0x00ff));  // lsb    
          __delay_ms(1);
          TX_EN_OFF;
          //--------------------------------------------------------------------
  }

  void modbus_poll() 
  {
    // update modbus regs and vars, send answer to master
  
    addr_buf_1 = modbus_reg_addr - 1000; // ??????? ???????? ? ??????
    
    // ???? ???? ??????? ?????? ?????????
    if(answer == modbus_rhr_cmd) 
    {
         modbus_refresh(modbus_rhr_cmd);// ?????????? ???????? ?????????
         modbus_rhr_answer();           // ????? ??? ??????? ?????? ?????????
    }
//--------------------------------------------------------------------
    // ???? ???? ??????? ?????? ?????????
    if(answer == modbus_wsr_cmd) 
    {
         holding_register[addr_buf_1] = reg_wr_data; // ????. ?????? ????????
         modbus_refresh(modbus_wsr_cmd);
         modbus_wsr_answer();             // ??????? ?????? ?? ??????? ?????? ? ???????
    }  
     answer = 0;                         // ????? ??? ??????? ?????? ?????????
  }

  /// MODBUS IRQ
  void _ISR_PSV _T1Interrupt() 
  { 
    // ????????? ??????? modbus, ?????? 5 ??
    if(rd_ptr < wr_ptr) // ????? ?? ????, ??????? ???? 
    {                                     
       rx_byte = get_rx_ch();  
      
       switch(rd_state)  // ???????? ??????? ????????? ?????? ??????
       {
       //====
         case detect_dev_id:              // ???? ????????? ? ??????????
           switch(rx_byte)
           {
             case dev_id:                 // ???????? ??????? ????????? ?? ???????? id ??????????
               rd_state = get_cmd_header; // ??????? ? ????????? ???????? ????????? ???????
             break;
             //----  
             case com_dev_id:             // ???????? ??????? ?????????????????? ?????????
               rd_state = get_cmd_header; // ??????? ? ????????? ???????? ????????? ???????
             break;
             //----    
             default:                     // ???????? ??? ?????? ??????? 
               rd_state = detect_dev_id;  // ??????? ? ?????? id ??????? modbus
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
                { 
                  answer = modbus_rhr_cmd;
                  rd_state = detect_dev_id;
                }
                else rd_state = detect_dev_id; 
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
                {
                  answer = modbus_wsr_cmd;
                  rd_state = detect_dev_id;
                }
                else rd_state = detect_dev_id; 
                get_crc_flag = 0;
               }
              
         break; 
         //=====
          default: rd_state = detect_dev_id;    
        } // switch
    }  // while 
//--------------------------------------------- 
PR1 = 3125;          // Load the period value = 5 ms
IFS0bits.T1IF = 0;   // Clear Timer interrupt flag
}

//                                M O D B U S   E N D 
//****************************************************************************//
  
void OSC_init()
{
    // FCY=FOSC/2, FOSC= FIN*M/(N1*N2) 
    CLKDIVbits.PLLPRE = 0;      // 0 - divider N1 = 2
    PLLFBD = 30;                // multiplier M = PLLFBD + 2
    CLKDIVbits.PLLPOST = 0;     // 0 - divider N2 = 2

    OSCTUN=0;                   // 000000 = Center frequency (7.37 MHz nominal)
    RCONbits.SWDTEN=0;          // Disable Watch Dog Timer

    while(OSCCONbits.LOCK !=1) {};   // 1 = Indicates that PLL is in lock, or PLL start-up timer is satisfied
                                    // 0 = Indicates that PLL is out of lock, start-up timer is in progress or PLL is disabled
    //note: FOSC= 10 MHz * 32/(2*2) = 80 MHz, FCY = 80/2
}   
/*=========================================================================== */
// UART 
void UART1_init()
{   /// modbus 
    // RX interrupt UART1 settings 
    IPC2bits.U1RXIP = 7; // Set UART1 RX interrupt priority to 1 
    IFS0bits.U1RXIF = 0; // Reset UART1 RX interrupt flag
    IEC0bits.U1RXIE = 1; // Enable UART1 RX interrupt
    
    U1BRG = U1BRGVAL;      // Baud Rate setting for 115200 uart
    U1MODEbits.UARTEN = 1;  // 1 = UARTx is enabled; all UARTx pins are controlled by UARTx as defined by UEN <1:0>
    U1MODEbits.UEN = 0;     // 0 = UxTX and UxRX pins are enabled and used; UxCTS and UxRTS/BCLK pins controlled by port latches
    U1MODEbits.PDSEL = 0;   // 0 = No Parity, 8-Data bits
    U1MODEbits.ABAUD = 0;   // 0 = Baud rate measurement disabled or completed
    U1MODEbits.BRGH = 0;    // 1 = BRG generates 4 clocks per bit period (4x baud clock, High-Speed mode)
    U1MODEbits.STSEL = 0;   // 0 = 1-Stop bit

    U1STAbits.UTXISEL0 = 0; // Interrupt when a unsigned character is transferred to the Transmit Shift Register (this implies there isat least one unsigned character open in the transmit buffer
    U1STAbits.UTXISEL1 = 0;
    U1STAbits.UTXINV = 0;
    U1STAbits.UTXEN = 1;    // 1 = Transmit enabled, UxTX pin controlled by UARTx
    U1STAbits.URXISEL = 0;  // 0x = Interrupt is set when any unsigned character is received and transferred from the UxRSR to the receive buffer. Receive buffer has one or more unsigned characters.
                         // The URXISEL<1:0> (UxSTA<7:6>) control bits determine when the UART receiver generates an interrupt.
  
 //Once enabled, the UxTX and UxRX pins are configured as an output and an
 //input, respectively, overriding the TRIS and PORT register bit settings for the corresponding I/O port pins. 
}

void UART2_init()
{   /// RS-232 
    // RX interrupt UART2 settings 
    IPC7bits.U2RXIP = 7;   // Set UART2 RX interrupt priority to 4
    IFS1bits.U2RXIF = 0;   // Reset UART2 RX interrupt flag
    IEC1bits.U2RXIE = 1;   // dis UART2 RX interrupt
    
    U2BRG = U2BRGVAL;       // Baud Rate setting for 2400 
    U2MODEbits.UARTEN = 1;  // 1 = UARTx is enabled; all UARTx pins are controlled by UARTx as defined by UEN <1:0>
    U2MODEbits.UEN = 0;     // 0 = UxTX and UxRX pins are enabled and used; UxCTS and UxRTS/BCLK pins controlled by port latches
    U2MODEbits.PDSEL = 0;   // 0 = No Parity, 8-Data bits
    U2MODEbits.ABAUD = 0;   // 0 = Baud rate measurement disabled or completed
    U2MODEbits.BRGH = 0;    // 1 = BRG generates 4 clocks per bit period (4x baud clock, High-Speed mode)
    U2MODEbits.STSEL = 0;   // 0 = 1-Stop bit

    U2STAbits.URXISEL0 = 0; // Interrupt flag bit is set when a character is received
    U2STAbits.URXISEL1 = 0;
    U2STAbits.UTXINV = 0;
    U2STAbits.UTXEN = 1;    // 1 = Transmit enabled, UxTX pin controlled by UARTx
                            // The URXISEL<1:0> (UxSTA<7:6>) control bits determine when the UART receiver generates an interrupt.
  
 //Once enabled, the UxTX and UxRX pins are configured as an output and an
 //input, respectively, overriding the TRIS and PORT register bit settings for the corresponding I/O port pins. 
}

unsigned char UART1GetChar ()
{
    unsigned char buf;
    while(IFS0bits.U1RXIF == 0) { }
    buf = U1RXREG;
    //IFS0bits.U1RXIF = 0;
    return buf; 
}
  
void uart_send_hex (unsigned char Ch)
{ // ??? ??????? ?????? ????????? ? ?????? ? ????. ??????
    
    U1TXREG = Ch;
    while(U1STAbits.TRMT == 0){ }
    // waiting for trancsaction to be complete
   
}

void uart2_send_hex (unsigned char Ch)
{ // RS-232 send byte
    
    U2TXREG = Ch;
    while(U2STAbits.TRMT == 0){ }
    // waiting for trancsaction to be complete
}

void uart_CR_LF_send (void){
	  
    uart_send_hex(0x0A);
	uart_send_hex(0x0D);
	
	}

void uart_num_send(long data){
	  
  unsigned char temp[10],count=0;
  if (data<0) 
  {
    data=-data;
    uart_send_hex('-');
  }     
  if (data)
  {
    while (data)
    {
      temp[count++]=data%10+'0';
      data/=10;                 
    }                           
    while (count)           
      uart_send_hex(temp[--count]);          
  }
  else uart_send_hex('0');           
}

void uart_text_send(char *s){
  while (*s != 0)
    uart_send_hex(*s++);
}

void uart2_text_send(char *s){
  while (*s != 0)
    uart2_send_hex(*s++);
}

/*=========================================================================== */
void _ISR_PSV _U1RXInterrupt(void)      //interupt UART 1 RX
{ /// ?????????? ????????? ??? ??????????? 1 ????? ?? UART1
        
    wr_ptr++;               // ????????? ???????? ?????????? ????       
    rx_buf[wr_ptr & 0x0f] = U1RXREG;
    IFS0bits.U1RXIF = 0;   //Clear  UART1_Rx interrupt   
}

void _ISR_PSV _U2RXInterrupt(void)      //interupt UART 2 RX
{   /// RS2-232 RX int   
    uart2_rx_buf[uart2_rx_ptr] = U2RXREG; 
   
    if(uart2_rx_buf[uart2_rx_ptr] == 0x0A)
    {
      uart2_rx_ptr = 0;
      data_ready = 1;      
    }
    else
     uart2_rx_ptr++;              // ????????? ???????? ?????????? ???? 

    IFS1bits.U2RXIF = 0;   //Clear  UART2_Rx interrupt  
  
}
  
void GPIO_init()
{
    // PORT B
    TRISBbits.TRISB14 = 0;
    //PORT C
    TRISCbits.TRISC1 = 0; // OUT2
    TRISCbits.TRISC2 = 0; // OUT3
    //PORT D
    TRISDbits.TRISD1 = 0; 
    //PORT F
    TRISFbits.TRISF0 = 0;
    LATFbits.LATF0 = 0;
    TRISFbits.TRISF1 = 0;
    LATFbits.LATF1 = 0;
    //uart2
    TRISFbits.TRISF4 = 0;
    LATFbits.LATF4 = 0;
    TRISFbits.TRISF5 = 1;

    TRISFbits.TRISF6 = 0;
    //PORT G
    TRISGbits.TRISG0=0;
    TRISGbits.TRISG6=0;   // OUT4
    TRISGbits.TRISG9=0;
    TRISGbits.TRISG12=0;  // coil 1
    TRISGbits.TRISG13=0;
    TRISGbits.TRISG14=0;
    TRISGbits.TRISG15=0;  // OUT1
} 

void Timer1_init()
{
    // 5 ms int
    
    //interrupt timer settings
  
    IPC0bits.T1IP = 5; // Set Timer1 interrupt priority to 3 
    IFS0bits.T1IF = 0; // Reset Timer1 interrupt flag      
    IEC0bits.T1IE = 1; // Enable Timer1 interrupt 
            
    T1CONbits.TON = 0;           // Timer on/off bit; 0 - Disable Timer
    T1CONbits.TCS = 0;           // Timer Clock Source Select bit; 0 - Internal clock (FOSC/2)
    T1CONbits.TGATE = 0;         // Disable Gated Timer mode
    T1CONbits.TCKPS = 0b10;      // Prescaler = (00=1, 01=8, 10=64, 11=256) 
    TMR1 = 0x00;                 // Clear timer register
    PR1 = 3125;                 // Load the period value
    T1CONbits.TON = 1;           // Start Timer 
    
}
/*=========================================================================== */
/// PSP405 functions
unsigned char char2num (unsigned char ch)
{ // converts char symbol into number
  return ch - 0x30;
}

unsigned char num2char (unsigned char ch)
{ // converts number into char symbol
  return ch + 0x30;
}

void PSP405_set_voltage(unsigned int voltage)
{
  // get chars from number
  unsigned int first_num  = voltage/10000;
  unsigned int sec_num    = (voltage - first_num * 10000)/1000;
  unsigned int thidr_num  = (voltage - first_num * 10000- sec_num*1000)/100;
  unsigned int fourth_num = (voltage - first_num * 10000 - sec_num*1000 - thidr_num*100)/10;
  // send SV xx.xx<cr> cmd
  uart2_text_send("SV ");
  uart2_send_hex(num2char(first_num));
  uart2_send_hex(num2char(sec_num));
  uart2_text_send(".");
  uart2_send_hex(num2char(thidr_num));
  uart2_send_hex(num2char(fourth_num));
  uart2_send_hex(0x0D); 
}
  
void PSP405_set_voltage_lim(unsigned int voltage_lim)
{
  // get chars from number
  unsigned int first_num  = voltage_lim/10;
  unsigned int sec_num    = (voltage_lim - first_num * 10);
  // send SU xx<cr> cmd
  uart2_text_send("SU ");
  uart2_send_hex(num2char(first_num));
  uart2_send_hex(num2char(sec_num));
  uart2_send_hex(0x0D);    
}

void PSP405_set_current(unsigned int current)
{ // current in mA
  // get chars from number
  unsigned int first_num  = current/1000;
  unsigned int sec_num    = (current - first_num * 1000)/100;
  unsigned int thidr_num  = (current - first_num * 1000 - sec_num*100)/10;
  // send SI x.xx<cr> cmd
  uart2_text_send("SI ");
  uart2_send_hex(num2char(first_num));
  uart2_text_send(".");
  uart2_send_hex(num2char(sec_num));
  uart2_send_hex(num2char(thidr_num));
  uart2_send_hex(0x0D);    
}

void PSP405_set_output(unsigned int state)
{   
    char *s = (state) ? "KOE" : "KOD"; 
    uart2_text_send(s);       // send get voltage cmd
    uart2_send_hex(0x0D);  
}

void PSP405_get_all()
{
  uart2_send_hex('L');
  uart2_send_hex(0x0D);
}

void PSP405_rx_parse(unsigned char parse_state)
{   
  switch(parse_state)
  {
  case 0:
    rd_voltage     = ERROR_CODE;
    rd_current     = ERROR_CODE;
    rd_voltage_lim = ERROR_CODE;
    rd_current_lim = ERROR_CODE;
    rd_status      = ERROR_CODE;
  break;
  //====================================================
  case 1:
    //------- checking answer to be Vvv.vv<cr>
    if(uart2_rx_buf[0] == 'V' && uart2_rx_buf[38] == 0x0D)
    {  // ok, got nice answer
       rd_voltage = char2num(uart2_rx_buf[1]) * 10000 + 
                    char2num(uart2_rx_buf[2]) * 1000  +
                    char2num(uart2_rx_buf[4]) * 100   +
                    char2num(uart2_rx_buf[5]) * 10;
    }
    //------- checking answer to be Av.vvv<cr>
    if(uart2_rx_buf[6] == 'A' && uart2_rx_buf[38] == 0x0D) 
    {  // ok, got nice answer
       rd_current = char2num(uart2_rx_buf[7]) * 1000 + 
                    char2num(uart2_rx_buf[9]) * 100  +
                    char2num(uart2_rx_buf[10])* 10   +
                    char2num(uart2_rx_buf[11]);
    }
    //------- checking src answer to be Uuu<cr>
    if(uart2_rx_buf[18] == 'U' && uart2_rx_buf[38] == 0x0D)
    {  // ok, got nice answer
       rd_voltage_lim =  char2num(uart2_rx_buf[19]) * 10 + char2num(uart2_rx_buf[20]);
    }
    //------- checking src answer to be Ii.ii<cr>
    if(uart2_rx_buf[21] == 'I' && uart2_rx_buf[38] == 0x0D)
    {  // ok, got nice answer
       rd_current_lim = char2num((unsigned char)uart2_rx_buf[22]) * 1000 + 
                        char2num((unsigned char)uart2_rx_buf[24]) * 100  +
                        char2num((unsigned char)uart2_rx_buf[25]) * 10;
    }
    //------- checking src answer to be Fffffff<cr> 
    if(uart2_rx_buf[30] == 'F' && uart2_rx_buf[38] == 0x0D)
    {  // ok, got nice answer
        rd_status = char2num(uart2_rx_buf[31]);
    }
    break;
    //====================================================
    default: break;
  }
  
}

/*=========================================================================== */

int main(void) 
{
    OSC_init();
    GPIO_init();
    UART1_init();
    UART2_init();
    Timer1_init();

    unsigned int count = 0;

while(1)
{        
  modbus_poll();
  __delay_ms(1); 

   if(data_ready)
   { 
    PSP405_rx_parse(1);
    PSP405_get_all();
    data_ready = 0;
    count = 0;
   }
   else
   {   
    count++;
    if(count > 3000) 
    { 
      PSP405_rx_parse(0);
      PSP405_get_all();
      count = 0;
      data_ready=0;
    }
   }
      
//      LATGbits.LATG6 = 1;
//      LATGbits.LATG15 = 1;
//      LATCbits.LATC1 = 1;
//      LATCbits.LATC2 = 1;
  }
}