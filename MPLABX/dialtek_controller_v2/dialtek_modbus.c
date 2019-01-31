/*                D I A L T E K    M O D B U S   R T U   v 2.2                */

/* ����������� ������������ */

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

6. ��������� ������� modbus_poll() � ���� while(1) (� >= 1 ��)

7. ��������� ����� ��� ���������� ����������� ������ ��������� (���� ����������) � ����������� � ���� RS485 EN/DIS DEFINE

8. ��������� ��������� ���������� � ���� HARDWARE INFO 

9. ��������� ������� modbus_int_mode() ����� � ����������� � �������� ���������� UART RX

10.��������� ����������� ����� ���������� � ������ modbus_refresh() :
      �) ��� ������ ���������, ����������� ��� if(cmd_type == MODBUS_RHR_CMD)
      �) ��� ������ ���������, ����������� ��� if(cmd_type == MODBUS_WSR_CMD)

11. ��� ������������� ������������� ����� ������� ������ modbus_refresh(), ������� ������� �� ��������� � ���� ���������  
*/

/*############################################################################*/ 
/*                    ���� ���������� ������������� !!!                       */ 

/* RS485 EN/DIS DEFINE */
#define TX_EN  LATEbits.LATE8=1
#define TX_DIS LATEbits.LATE8=0

/* HARDWARE INFO */
  unsigned char dev_id        = DEFAULT_DEV_ID;     // MODBUS ID ����������                                      <<<<<<<<<<======== ID
  unsigned char firmware_ver  = 10;                 // ������ �������� �������� ����������
  unsigned char device_family = 200;                // ��� ��������� ���������

/* ��������� */
unsigned int get_syr_pos (unsigned char);
unsigned int get_syr_vel (unsigned char);
unsigned int get_valve_angle (unsigned char);
  
/* USER FUNCS */
/*--------------------------------------------------------------------------- */  
  
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

/*############################################################################*/  
  
/*                         M O D B U S   E N D                                */




