/*                D I A L T E K    M O D B U S   R T U   v 2.1                */

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

#define TX_EN  LATBbits.LATB14=1
#define TX_DIS LATBbits.LATB14=0

/* HARDWARE INFO */
  unsigned char dev_id        = DEFAULT_DEV_ID;     // MODBUS ID ���������� <<<<<<<<<<======== ID
  unsigned char firmware_ver  = 21;                 // ������ �������� �������� ����������
  unsigned char device_family = 5;                  // ��� ��������� ���������
  unsigned char com_dev_id    = 247;                // MODBUS ID ���������� ��� ������������������ ������, ����� �� ������� 

/* ��������� */

  // PSP405
unsigned char char2num (unsigned char ch);
unsigned char num2char (unsigned char ch);
unsigned int PSP405_get_voltage();
unsigned int PSP405_get_current();
unsigned int PSP405_get_status();
unsigned int PSP405_get_voltage_lim();
unsigned int PSP405_get_current_lim();
void PSP405_set_output(unsigned int state);
void PSP405_set_power_lim(unsigned int power_lim);

//void eeprom_wr_page(unsigned int address);
void eeprom_wr_regs(void);
//unsigned int eeprom_rd_regs(unsigned int address);
  
/* USER FUNCS */ 
  
  void modbus_refresh(unsigned char cmd_type) // ������ � ����������
  {     
    
   /// ������ R/W ���������, TODO - ���������� ���������� ����� ��������� �������    
    
   if(cmd_type == MODBUS_RHR_CMD)
   {   
       holding_register[0] = rd_voltage;
       holding_register[1] = rd_voltage_lim;
       holding_register[2] = rd_current;
       holding_register[3] = rd_current_lim;      
       holding_register[4] = rd_status; // the relay status 0:OFF 1:ON
       holding_register[5] = rd_power_lim;     
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
  
   /// ������, TODO - ��������� ����� �������� �� �������
   //  addr_buf_1 = ����� ��������, � ������� ���� ������ (1000 = 0, 1001 = 1 � ��)
  
   if(cmd_type == MODBUS_WSR_CMD) 
   {  // ������ �������� ������ 
      switch(addr_buf_1) {  
          case 4: // reg 4 - set output
            RS232_TX_LED = 1;
           PSP405_set_output(holding_register[4]);
        break;
        //---------
        case 7: // reg 7 - set voltage
           if(holding_register[7] > MAX_VOLTAGE) holding_register[7] = MAX_VOLTAGE;
           RS232_TX_LED = 1;
           PSP405_set_voltage(holding_register[7]);
        break;
        //---------
        case 8: // reg 8 - set voltage limit
           if(holding_register[8] > MAX_VOLTAGE/100) holding_register[8] = MAX_VOLTAGE/100;
           RS232_TX_LED = 1;
           PSP405_set_voltage_lim(holding_register[8]);
        break;
        //---------
        case 9: // reg 9 - set current
           if(holding_register[9] > MAX_CURRENT) holding_register[9] = MAX_CURRENT;
           RS232_TX_LED = 1;
           PSP405_set_current(holding_register[9]);
        break;
        //---------
        case 10: // reg 10 - K1 relay ctrl
           RS232_TX_LED = 1;
           PSP405_set_output(0);
           for(unsigned int i = 0; i < 2000; i++) 
             __delay_ms(1);
           if     (holding_register[10] == 1) 
           {
               K1_ON;
               POL_RELAY_LED = 1;
           }
           else if(holding_register[10] == 0) 
           {
               K1_OFF;
               POL_RELAY_LED = 0;
           }
           for(unsigned int i = 0; i < 100; i++) 
             __delay_ms(1);
           PSP405_set_output(1);
        break;
        //---------
        //---------
        case 11: // reg 1 - power limit
           if(holding_register[11] > MAX_POWER) holding_register[11] = MAX_POWER;
           RS232_TX_LED = 1;
           PSP405_set_power_lim(holding_register[11]);
        break;
       //---------
        case 19: // reg 19 - ID
            // modbus id change seq     
            if((dev_id >= 254 ) || (dev_id == 0)) break;
            else
            {  
             dev_id = (unsigned char)holding_register[20];
             holding_register[19] = 0;
            }
            
       break;
       default: break;  
      }
      
       for(unsigned int i = 0; i < 400; i++) 
         __delay_ms(1); 
         eeprom_wr_regs(); // save registers state       
         RS232_TX_LED = 0;
   }
   
      
   
  }

/*############################################################################*/  
  
/*                         M O D B U S   E N D                                */



