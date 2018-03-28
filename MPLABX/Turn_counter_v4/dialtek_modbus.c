/*                D I A L T E K    M O D B U S   R T U   v 2.0                */

/* README */
/*
��� ������ ���������� MODBUS RTU ����������:

1. ��������� ���������� UART RX �� ������ ������ ����� 

2. �������� � ���������� ���������� UART RX ������� modbus_uart_byte, ��������:
      modbus_uart_byte(MDR_UART1->DR); ��� modbus_uart_byte(U1RXREG);

3. ������� ������� �������� ������ ����� UART TX ���������� ����:
      void uart_send_hex(unsigned char hex_data){ }

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

#define TX_EN  LATCbits.LATC3=1
#define TX_DIS LATCbits.LATC3=0

/* HARDWARE INFO */

  unsigned char com_dev_id   = 247;                // MODBUS ID ���������� ��� ������������������ ������, ����� �� ������� 
  unsigned char dev_id       = 11;                 // MODBUS ID ����������                                      <<<<<<<<<<======== ID
  unsigned int firmware_ver  = 20;                 // ������ �������� �������� ����������
  unsigned int device_family = 10;                  // ��� ��������� ���������

/* PROTOTYPES */
  
/* USER FUNCS */
  
  void modbus_int_mode (unsigned char mode)  {      // ���������� ����������� UART RX
  
    if(mode == 1) // ���������� ���������� RX UART MODBUS
    {
        PIE1bits.RC1IE = 0;    // ������ UART recive
    }
    else         // ������ ���������� RX UART MODBUS
    {
        PIE1bits.RC1IE = 1;    // ���������� UART recive
    }
  }
  
  void modbus_refresh(unsigned char cmd_type){      // ������ � ����������
    
  /// ������ RW ���������, TODO - ���������� ���������� ����� ��������� �������       
  if(cmd_type == MODBUS_RHR_CMD)
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
        
        holding_register[10] = ADC_current_dif;
        holding_register[11] = read_turns;
        holding_register[12] = adc_current_result;
        holding_register[13] = ADC_current_max;
        holding_register[14] = ADC_current_min;
   }         
   //-------------------------------------------------------------------------//
  /// ������ Read-only ���������, TODO - ���������� ���������� ����� ��������� �������   
   if(cmd_type == MODBUS_RIR_CMD)
   {   
       input_register[0] = (unsigned int)dev_id;       
       input_register[1] = (unsigned int)device_family;
       input_register[2] = firmware_ver;
   } 
   //-------------------------------------------------------------------------//
   /// ������, TODO - ��������� ����� �������� �� �������
   //  addr_buf_1 = ����� ��������, � ������� ���� ������ (1000 = 0, 1001 = 1 � ��)
   if(cmd_type == MODBUS_WSR_CMD) 
   {  // ������ �������� ������ 
      switch(addr_buf_1) {  
        case 4: // reg 4
           
        break;
        //---------
        case 7: // reg 7

        break;     
         //---------
       default: break;  }

   } 
  }

/*############################################################################*/  
  
/*                         M O D B U S   E N D                                */




