#include "app.h"

// *****************************************************************************
// global
unsigned char EEPR_buf[Data2saveLen];
unsigned int i = 0;

unsigned char *TX_ptr = 0, *RX_ptr = 0;

// *****************************************************************************
// config to EEPROM save/restore functions

void SaveCfg(void)                       // save setting to EEPROM 
{
   //EEPR_buf[0] = (unsigned char)ADC_SPS;
   //EEPR_buf[1] = (unsigned char)ADC_PGA;  
   
   eeprom_src_save(&EEPR_buf,Data2saveLen);
}

unsigned int RestoreCfg(void)            // restore setting from EEPROM 
{
    eeprom_src_restore(&EEPR_buf,Data2saveLen); // !!! читаю наверняка - 2 раза
          
    if(eeprom_src_restore(&EEPR_buf,Data2saveLen))
    {   
      //ADC_SPS = (unsigned int)EEPR_buf[0];
      //ADC_PGA = (unsigned int)EEPR_buf[1];
      
      holding_reg_write(25,1);
      return 1;
    }
    else return 0;
}

// *****************************************************************************
// TCP to/from UART
    
void TCPreceive_UARTsend(void)
{
    TX_ptr = (void*)modbus_clean_rx();

    //if(*TX_ptr != 0)
    //{
      for(i = 0; i < TCP_RxCnt(); i++)
        Uart1SendByte(*TX_ptr++);
    //}  
}

uint32_t UARTreceive_TCPsend(void)
{
    if( Uart1_rx_complete() )
    { 
      RX_ptr = (void*)Uart1_RxBuf_ptr();
      
      for(i = 0; i < Uart1_bytes_get() ; i++)
        modbus_tx_buf_add(*RX_ptr++);
      
      Uart1_rx_reset();
      
      return 1U;
    }  
    else
      return 0U;
}

// *****************************************************************************
// MODBUS RTU over TCP

/*

 unsigned int RegisterAddr  = 0;        // modbus write reg addr
 unsigned int RegisterValue = 0;        // modbus write reg velue
 
 void modbus_poll(void)                 // modbus logic
{       
  switch( modbus_get_poll() )            // check if received modbus cmd
  {
    case 0x03:   
////////////////////////////  HOLDING //////////////////////////

      holding_reg_write(0,1);     
      holding_reg_write(1,16);   
      modbus_rhr_answer();          
    break;
//////////////////////////// HOLDING //////////////////////////
    case 0x06:
        modbus_wsr_answer();  

        RegisterAddr  = get_wr_reg_addr();    // get address
        RegisterValue = get_wr_reg_val();     // get the new value

       switch(RegisterAddr)
       {
          case 1:   
            LATHbits.LATH14 = RegisterValue;
            modbus_tx_buf_add((unsigned char)RegisterValue);
          break;
          
          //----    
          default: break;
       }


    break;
//////////////////////////// INPUT ////////////////////////////
    case 0x04:
      input_reg_write(0, 89);
      modbus_rir_answer(); //
    break;
 }
}
 
 */
 
void APP_Initialize ( void )            // init system
{
    HTTP_APP_Initialize();              // http   web server init  
    MODBUS_APP_Initialize();            // modbus tcp server init
    Uart1Init();
    //RestoreCfg();                       // restore last device params 
}

void APP_Tasks ( void )                 // tasks
{
    HTTP_APP_Tasks();                   // web server
    
    TCPreceive_UARTsend();              // receive TCP bytes and send it to UART
    
    LATHINV = UARTreceive_TCPsend() << RX_LED_POS;

}

// *****************************************************************************
