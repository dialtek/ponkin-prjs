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

4. ��������� ������� modbus_rx_sm() � ���� while(1)

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

#define TX_EN  LATFbits.LATF6=1
#define TX_DIS LATFbits.LATF6=0

/* HARDWARE INFO */

//unsigned char com_dev_id    = 247;                // MODBUS ID ���������� ��� ������������������ ������, ����� �� ������� 
unsigned char dev_id        = 100;                // MODBUS ID ����������                                      <<<<<<<<<<======== ID
unsigned char firmware_ver  = 10;                 // ������ �������� �������� ����������
unsigned char device_family = 90;                 // ��� ��������� ���������

/* ��������� */
//==============================================================================
/* USER FUNCS */

#define ID_lenght	8 // ���-�� ���� � ID �������
#define MAX_sens_qty 10   // ����. ����� �������� 

unsigned char ID_buf [8]     = {0,0,0,0,0,0,0,0};     // ��������� ������ ID
unsigned char index_buf [10] = {255,255,255,255,255,255,255,255,255,255}; // ������ � �������� ID
unsigned char add_count;       // ������� ������� ����������
unsigned char eq_cnt = 0;      // ������� ���������� ������� ID  
unsigned char index_exist = 0; // ���� ������� ������� ����� ��� ����������


unsigned char Sens_ID[MAX_sens_qty][ID_lenght]; // ID �������� � ��������� ����  
unsigned char sensors_qty  = 0;			// ���-�� �������� �� ���� 1-wire
unsigned char sensor_index;       // ������ ������� ��� ����. ��� id

/*--------------------------------------------------------------------------- */
#include "one_wire.h"

  // ������ ID ������ ������� �� ��������� ������
  void get_sensor_ID()
  {
     if (OneWire_reset())
     {
        OneWire_send(Read_ROM);
        for (unsigned char i = 0; i < ID_lenght; i++)
            ID_buf[i] = OneWire_read(); // ���������� ID ������� �� ��������� ����� 
     }
  }
  
  // ����� ID ������ ������� ����� ��� �����������
  unsigned char match_sensor_ID()
  {
     unsigned char sensor_exist = 0;
      
     // ��������� ID ������ ������� � ����, ��� ���� ��������� �����
     for(unsigned char i = 0; i < sensors_qty; i++)
     {
        for(unsigned char j = 0; j < ID_lenght; j++)
        {
            if(Sens_ID[i][j] == ID_buf[j])
                eq_cnt++;          
        }
        
        if(eq_cnt < ID_lenght) eq_cnt = 0; // ����� �������� ����� ����� �������
     }
      
     if(eq_cnt >= ID_lenght) 
         sensor_exist = 1;
      
      return sensor_exist;
  }

  // ����� ������������ ��������
  void reset_cfg()
  {
      // ������� ������� � ID ��������       
      for(unsigned char i = 0; i < MAX_sens_qty; i++)
      {
         index_buf[i] = 255;  // ������ � �������� ID
                 
         for(unsigned char j = 0; j < ID_lenght; j++) 
             Sens_ID[i][j] = 0;
      }
         
      // ������� ���������, ���������� ID ��������  
      for(unsigned char i = 10; i < 110; i++)
      {
          input_register[i] = 0;
          holding_register[i-10] = 0;
      }
      
      sensors_qty = 0;                     // ����� ����� ��������    
      add_count = 0;
      index_exist = 0;
  }
  
  
  /* USER FUNCS */
  //==============================================================================
  
  void modbus_int_mode (unsigned char mode)  {      // ���������� ����������� UART RX
  
    if(mode == 1) // ���������� ���������� RX UART MODBUS
    {
      IEC0bits.U1RXIE = 1; // en UART1 RX interrupt   
    }
    else         // ������ ���������� RX UART MODBUS
    {
      IEC0bits.U1RXIE = 0; // dis UART1 RX interrupt   
    }
  }
  
  void modbus_refresh(unsigned char cmd_type){      // ������ � ����������
    
   /// ������ R/W ���������, TODO - ���������� ���������� ����� ��������� �������    
    
   if(cmd_type == MODBUS_RHR_CMD)
   {   
       
    long t = 0;
    unsigned char cnt = 0;
    if(sensors_qty > 0)
    {
        OneWire_all_rd_t(); // ������� ��������� � ��� ���� ��������
                        // �������� �����. � 760 �� ������ �������

        for(unsigned char i = 0; i < sensors_qty; i++)// ����� �emper � �������� ����������
        {
          t = ds18b20_i_rd_t(Sens_ID[i]);  //���������� Temper �������� �����������
       
          holding_register[cnt]   = (unsigned int)  (t >> 16);
          cnt++;
          holding_register[cnt] = (unsigned int)  (t & 0x0000ffff);
          cnt++;
        }
          holding_register[30] = sensor_index;
    }
       
   }         
   //-------------------------------------------------------------------------//
   /// ������ Read-only ���������, TODO - ���������� ���������� ����� ��������� �������   
   if(cmd_type == MODBUS_RIR_CMD)
   {   
       input_register[0] = (unsigned int)dev_id;       
       input_register[1] = (unsigned int)device_family;
       input_register[2] = (unsigned int)firmware_ver;
       
       input_register[9] = (unsigned int)sensors_qty;
                 
       // 1st sensor ID: 10 - 17 input regs
       // 2nd sensor ID: 20 - 27 input regs
       // etc.
   }         
   //-------------------------------------------------------------------------//
  
   /// ������, TODO - ��������� ����� �������� �� �������
   //  addr_buf_1 = ����� ��������, � ������� ���� ������ (1000 = 0, 1001 = 1 � ��)
  
   if(cmd_type == MODBUS_WSR_CMD) 
   {  // ������ �������� ������ 
      switch(addr_buf_1) {  
        case 0: // reg 0 - steps

        break;
        //---
        case 1: // 
   
        break;
        //---
        case 2: // 

        break;
        //---
        case 30: // set sensor number
          
          // ��������� ����� ������, ���� ��� ������ � ��������� 0 - MAX_sens_qty-1
          if(holding_register[30] <= MAX_sens_qty -1)
          {
            // �������, �� �� ����� ������� ���� ������ �������
            for(unsigned char i = 0; i < MAX_sens_qty; i++)
            {
                if(index_buf[i] == holding_register[30])
                    index_exist = 1; // ��, ������� ����
            }
            
            // ���� ��� ����� ������..
            if(!index_exist)
            {
               index_buf[add_count] = sensor_index; // ����. ��� ������ � �����
               add_count++; // ��������� ����� �������� ����������
            }
          }
          
          else holding_register[30] = MAX_sens_qty - 1;
          sensor_index = holding_register[30];
          
          if(add_count > 10) add_count = 0;
            
        break;
        //---
        case 31: // ���������� ������ �������
        
        eq_cnt = 0;  // ����� �������� ���������� ���� ID
        
        //get 8 ROM bytes - ���������� ID ������ �� ��������� �����
        get_sensor_ID();  
        
        // ����� �������� ���������� �������, ���� �� �������� �����
        if(match_sensor_ID() == 1) break;            
        // ���� ��� ����� ������ - ��������� ���
        else
        {
            for (unsigned char i = 0; i < ID_lenght; i++) 
            {
              input_register[(10+10*sensor_index) + i] = ID_buf[i];  
              Sens_ID[sensor_index][i] = input_register[(10+10*sensor_index) + i];
            } 
            
            if(index_exist)
              index_exist = 0; // ����� ����� ������� ������� ����� ��� ����������
            else 
            {
                sensors_qty++; // ��������� ����� ��������, ���� ��� �����
                index_exist = 0;
            }
            sensor_index = 255;
           
          // 1st sensor ID: 10 - 17 input regs
          // 2nd sensor ID: 20 - 27 input regs
          // etc.
        }
          
        break;
        //---
        case 32:  
        /* ������� ������� � ID � ����������� ������� � ��������� ���������
          ��� �������� */
            
            reset_cfg();

        break;
        //---

        //---
          default: break;
    } // switch
   } // if 
  }

/*############################################################################*/  
  
/*                         M O D B U S   E N D                                */




