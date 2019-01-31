/*                D I A L T E K    M O D B U S   R T U   v 3.0                */

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

#define TX_EN  RC14=1 
#define TX_DIS RC14=0

/* HARDWARE INFO */

 // unsigned char com_dev_id    = 247;              // MODBUS ID ���������� ��� ������������������ ������, ����� �� ������� 
  unsigned char dev_id        = 100;                  // MODBUS ID ����������   <<<<<<<<<<======== ID
  unsigned char firmware_ver  = 15;                 // ������ �������� �������� ����������
  unsigned char device_family = 5;                  // ��� ��������� ���������

/* PROTOTYPES */


 /* USER FUNCS */
  
  
  void modbus_refresh(unsigned char cmd_type){      // ������ � ����������
    
  /// RW ���������, TODO - ���������� ���������� ����� ��������� �������       
  if(cmd_type == MODBUS_RHR_CMD)
   {   
      //U8 read_complete = is_reading_reg(meas_status_reg);
      if(meas_status)  
      {  // ���� ��������� ��������, ���������� ���������
         // 0. 000 000  0 V - ������, ��������� ����� - ����� ��
         holding_register[0] = (U16) (pkt8_ch_1 & 0x0000ffff);          // LSB ������ 1
         holding_register[1] = (U16)((pkt8_ch_1 & 0xffff0000) >> 16);   // MSB ������ 1
         
         
         holding_register[2] = (U16) (pkt8_ch_2 & 0x0000ffff);          // LSB ������ 2
         holding_register[3] = (U16)((pkt8_ch_2 & 0xffff0000) >> 16);   // LSB ������ 2
         
         holding_register[4] = (U16) (pkt8_ch_3 & 0x0000ffff);          // LSB ������ 3
         holding_register[5] = (U16)((pkt8_ch_3 & 0xffff0000) >> 16);   // MSB ������ 3
         
         holding_register[6] = (U16) (pkt8_ch_4 & 0x0000ffff);          // LSB ������ 4
         holding_register[7] = (U16)((pkt8_ch_4 & 0xffff0000) >> 16);   // LSB ������ 4
         
         holding_register[8] = (U16) (pkt8_ch_5 & 0x0000ffff);          // LSB ������ 5
         holding_register[9] = (U16)((pkt8_ch_5 & 0xffff0000) >> 16);   // MSB ������ 5
         
         holding_register[10] = (U16) (pkt8_ch_6 & 0x0000ffff);         // LSB ������ 6
         holding_register[11] = (U16)((pkt8_ch_6 & 0xffff0000) >> 16);  // LSB ������ 6
         
         holding_register[12] = (U16) (pkt8_ch_7 & 0x0000ffff);         // LSB ������ 7
         holding_register[13] = (U16)((pkt8_ch_7 & 0xffff0000) >> 16);  // MSB ������ 7
         
         holding_register[14] = (U16) (pkt8_ch_8 & 0x0000ffff);         // LSB ������ 8
         holding_register[15] = (U16)((pkt8_ch_8 & 0xffff0000) >> 16);  // LSB ������ 8
         // ===================================================================
         // ���������� ��������
         holding_register[24] = (U16) (ADC_counts[0][0] & 0x0000ffff);         // LSB ������ 1
         holding_register[25] = (U16)((ADC_counts[0][0] & 0xffff0000) >> 16);  // MSB ������ 1
         
         holding_register[26] = (U16) (ADC_counts[0][1] & 0x0000ffff);         // LSB ������ 2
         holding_register[27] = (U16)((ADC_counts[0][1] & 0xffff0000) >> 16);  // LSB ������ 2
         
         holding_register[28] = (U16) (ADC_counts[0][2] & 0x0000ffff);         // LSB ������ 3
         holding_register[29] = (U16)((ADC_counts[0][2] & 0xffff0000) >> 16);  // MSB ������ 3
         
         holding_register[30] = (U16) (ADC_counts[0][3] & 0x0000ffff);         // LSB ������ 4
         holding_register[31] = (U16)((ADC_counts[0][3] & 0xffff0000) >> 16);  // LSB ������ 4
         
         holding_register[32] = (U16) (ADC_counts[1][0] & 0x0000ffff);         // LSB ������ 5
         holding_register[33] = (U16)((ADC_counts[1][0] & 0xffff0000) >> 16);  // MSB ������ 5
         
         holding_register[34] = (U16) (ADC_counts[1][1] & 0x0000ffff);         // LSB ������ 6
         holding_register[35] = (U16)((ADC_counts[1][1] & 0xffff0000) >> 16);  // LSB ������ 6
         
         holding_register[36] = (U16) (ADC_counts[1][2] & 0x0000ffff);         // LSB ������ 7
         holding_register[37] = (U16)((ADC_counts[1][2] & 0xffff0000) >> 16);  // MSB ������ 7
         
         holding_register[38] = (U16) (ADC_counts[1][3] & 0x0000ffff);         // LSB ������ 8
         holding_register[39] = (U16)((ADC_counts[1][3] & 0xffff0000) >> 16);  // LSB ������ 8
         
         // ����� ������ ����� ����� ���������
         meas_status = 0;
      }
      holding_register[16] = (U16)input_buf_state; // ����. ��. ������ ���
      holding_register[18] = PGA_val;
      holding_register[19] = ADC_sps_var;
      holding_register[20] = Ma_buf_size;
      holding_register[21] = dev_id;
      holding_register[22] = firmware_ver;
      holding_register[23] = device_family;
   }         
   //-------------------------------------------------------------------------//
  /// ������ Read-only ���������, TODO - ���������� ���������� ����� ��������� �������   
   
   if(cmd_type == MODBUS_RIR_CMD)
   {   
       input_register[0] = (unsigned int)dev_id;       
       input_register[1] = (unsigned int)device_family;
       input_register[2] = (unsigned int)firmware_ver;
   } 
   //-------------------------------------------------------------------------//
   /// TODO - ��������� ����� �������� �� �������
   //  addr_buf_1 = ����� ��������, � ������� ���� ������ (1000 = 0, 1001 = 1 � ��)
   if(cmd_type == MODBUS_WSR_CMD) 
   {  // ������ �������� ������ 
 
        // range
         if(holding_register[18] >= 0 && holding_register[19] <= 6) 
             PGA_val = holding_register[18];
         // SPS
         if(holding_register[19] >= 0 && holding_register[19] <= 8) 
             ADC_sps_var = holding_register[19];
         // averfge buf size
         if(holding_register[20] >= 1 && holding_register[20] <= 128) 
         {
             Clr_bufs(); // ������� ������ ��������. ��������
             Ma_buf_size = holding_register[20];
         }
         input_buf_state = (U8)holding_register[16]; // ����. ��. ������
                
   } //if(cmd_type == MODBUS_WSR_CMD) 
  }
  

/*############################################################################*/  
  
/*                         M O D B U S   E N D                                */




