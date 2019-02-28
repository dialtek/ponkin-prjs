/*                D I A L T E K    M O D B U S   R T U   v 3.1                */

/* README */
/*
��� ������ ���������� MODBUS RTU ����������:

1. ��������� ���������� UART RX �� ������ ������ ����� 

2. �������� � ���������� ���������� UART RX ������� modbus_uart_byte, ��������:
      modbus_uart_byte(MDR_UART1->DR); ��� modbus_uart_byte(U1RXREG);

3. ������� ������� �������� ������ ����� UART TX ���������� ����:
      void uart_send_byte(unsigned char hex_data){ }

4. ��������� ������� modbus_rx_sm() � ���������� ���������� �� ������� (� >= 1 ��) ��� ���� while(1)

5. ��������� ������� modbus_init() � main()

6. ��������� ������� modbus_poll() � ���� while(1) (T >= 1 ��)

7. ��������� ����� ��� ���������� ����������� ������ ��������� (���� ����������) � ����������� � ���� RS485 EN/DIS DEFINE

8. ��������� ��������� ���������� � ���� HARDWARE INFO 

9. ��������� ������� modbus_int_mode() ����� � ����������� � �������� ���������� UART RX

10.��������� ����������� ����� ���������� � ������ modbus_refresh() :
      A) ��� ������ ���������, ����������� ��� if(cmd_type == MODBUS_RHR_CMD)
      B) ��� ������ ���������, ����������� ��� if(cmd_type == MODBUS_WSR_CMD)

11. ��� ������������� ������������� ����� ������� ������ modbus_refresh(), ������� ������� �� ��������� � ���� PROTOTYPES  
*/

/*############################################################################*/ 
/*                   ����, ���������� ������������� !!!                       */ 

/* RS485 EN/DIS DEFINE */

#define TX_EN  LATCbits.LATC14 = 1 
#define TX_DIS LATCbits.LATC14 = 0 

/* HARDWARE INFO */

  unsigned char com_dev_id    = 247;                // MODBUS ID ���������� ��� ������������������ ������, ����� �� ������� 
  unsigned char dev_id        = 100;                // MODBUS ID ����������   <<<<<<<<<<======== ID
  unsigned char firmware_ver  = 21;                 // ������ �������� �������� ����������
  unsigned char device_family = 11;                 // ��� ��������� ���������
  unsigned char modbus_ver    = 31;                 // ������ MODBUS

/* PROTOTYPES */
 
/* USER FUNCS */
  
  void modbus_refresh(unsigned char cmd_type) {     // ������ � ����������
    
  /// RW ���������, TODO - ���������� ���������� ����� ��������� �������       
  if(cmd_type == MODBUS_RHR_CMD)
   {   
      if(meas_status)  
      {  // ���� ��������� ��������, ���������� ���������
         // 0. 000 000  0 V - ������, ��������� ����� - ����� ��
         holding_register[0] = (unsigned int) (pkt8_ch[0] & 0x0000ffff);          // LSB ������ 1
         holding_register[1] = (unsigned int)((pkt8_ch[0] & 0xffff0000) >> 16);   // MSB ������ 1
         
         
         holding_register[2] = (unsigned int) (pkt8_ch[1] & 0x0000ffff);          // LSB ������ 2
         holding_register[3] = (unsigned int)((pkt8_ch[1] & 0xffff0000) >> 16);   // LSB ������ 2
         
         holding_register[4] = (unsigned int) (pkt8_ch[2] & 0x0000ffff);          // LSB ������ 3
         holding_register[5] = (unsigned int)((pkt8_ch[2] & 0xffff0000) >> 16);   // MSB ������ 3
         
         holding_register[6] = (unsigned int) (pkt8_ch[3] & 0x0000ffff);          // LSB ������ 4
         holding_register[7] = (unsigned int)((pkt8_ch[3] & 0xffff0000) >> 16);   // LSB ������ 4
         
         holding_register[8] = (unsigned int) (pkt8_ch[4] & 0x0000ffff);          // LSB ������ 5
         holding_register[9] = (unsigned int)((pkt8_ch[4] & 0xffff0000) >> 16);   // MSB ������ 5
         
         holding_register[10] = (unsigned int) (pkt8_ch[5] & 0x0000ffff);         // LSB ������ 6
         holding_register[11] = (unsigned int)((pkt8_ch[5] & 0xffff0000) >> 16);  // LSB ������ 6
         
         holding_register[12] = (unsigned int) (pkt8_ch[6] & 0x0000ffff);         // LSB ������ 7
         holding_register[13] = (unsigned int)((pkt8_ch[6] & 0xffff0000) >> 16);  // MSB ������ 7
         
         holding_register[14] = (unsigned int) (pkt8_ch[7] & 0x0000ffff);         // LSB ������ 8
         holding_register[15] = (unsigned int)((pkt8_ch[7] & 0xffff0000) >> 16);  // LSB ������ 8
         // ===================================================================
//         // ���������� ��������
//         holding_register[24] = (unsigned int) (ADC_counts[0][0] & 0x0000ffff);         // LSB ������ 1
//         holding_register[25] = (unsigned int)((ADC_counts[0][0] & 0xffff0000) >> 16);  // MSB ������ 1
//         
//         holding_register[26] = (unsigned int) (ADC_counts[0][1] & 0x0000ffff);         // LSB ������ 2
//         holding_register[27] = (unsigned int)((ADC_counts[0][1] & 0xffff0000) >> 16);  // LSB ������ 2
//         
//         holding_register[28] = (unsigned int) (ADC_counts[0][2] & 0x0000ffff);         // LSB ������ 3
//         holding_register[29] = (unsigned int)((ADC_counts[0][2] & 0xffff0000) >> 16);  // MSB ������ 3
//         
//         holding_register[30] = (unsigned int) (ADC_counts[0][3] & 0x0000ffff);         // LSB ������ 4
//         holding_register[31] = (unsigned int)((ADC_counts[0][3] & 0xffff0000) >> 16);  // LSB ������ 4
//         
//         holding_register[32] = (unsigned int) (ADC_counts[1][0] & 0x0000ffff);         // LSB ������ 5
//         holding_register[33] = (unsigned int)((ADC_counts[1][0] & 0xffff0000) >> 16);  // MSB ������ 5
//         
//         holding_register[34] = (unsigned int) (ADC_counts[1][1] & 0x0000ffff);         // LSB ������ 6
//         holding_register[35] = (unsigned int)((ADC_counts[1][1] & 0xffff0000) >> 16);  // LSB ������ 6
//         
//         holding_register[36] = (unsigned int) (ADC_counts[1][2] & 0x0000ffff);         // LSB ������ 7
//         holding_register[37] = (unsigned int)((ADC_counts[1][2] & 0xffff0000) >> 16);  // MSB ������ 7
//         
//         holding_register[38] = (unsigned int) (ADC_counts[1][3] & 0x0000ffff);         // LSB ������ 8
//         holding_register[39] = (unsigned int)((ADC_counts[1][3] & 0xffff0000) >> 16);  // LSB ������ 8
         // ����� ������ ����� ����� ���������
         meas_status = 0;
      }
      
      holding_register[17] = channel;
      holding_register[18] = PGA_val;
      holding_register[19] = ADC_sps_var;
      holding_register[20] = Ma_buf_size;
      holding_register[21] = Ma_buf_index;
   }         
   //-------------------------------------------------------------------------//
  /// ������ Read-only ���������, TODO - ���������� ���������� ����� ��������� �������   
   
   if(cmd_type == MODBUS_RIR_CMD)
   {   
       input_register[0] = (unsigned int)dev_id;       
       input_register[1] = (unsigned int)device_family;
       input_register[2] = (unsigned int)firmware_ver;
       input_register[3] = (unsigned int)modbus_ver;
   } 
   //-------------------------------------------------------------------------//
   /// TODO - ��������� ����� �������� �� �������
   if(cmd_type == MODBUS_WSR_CMD) 
   {  
       
       switch(modbus_reg_addr) // ������ �������� ������ 
       {
           case 18: // reg 18 - range
            if(holding_register[18] >= 0 && holding_register[18] <= 6) 
                PGA_val = holding_register[18];
           break;
           //----
           case 19: // reg 19 - SPS
             if(holding_register[19] >= 0 && holding_register[19] <= 8) 
                ADC_sps_var = holding_register[19];
           break;
           //----
           case 20: // reg 20 - averfge buf size
             if(holding_register[20] >= 1 && holding_register[20] <= 128) 
                Ma_buf_size = holding_register[20];
           break;
           //----    
           case 51: // reg 51 - ����� ID
             // modbus id change seq     
             if((dev_id > 254 ) || (dev_id == 0)) break;
             else
             {  
                if(holding_register[51] == 1)
                    dev_id = (unsigned char)holding_register[50];
                holding_register[51] = 0;
             }
           break;
           
           default: break;
       }
         ADC_init(input_buf_state); // ������������� ����� ���
         eeprom_wr_regs();   
   } //if(cmd_type == MODBUS_WSR_CMD) 
  }

/*############################################################################*/  
  
/*                         M O D B U S   E N D                                */