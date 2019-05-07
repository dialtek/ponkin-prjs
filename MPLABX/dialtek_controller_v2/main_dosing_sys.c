#include "xc.h"
#include "main.h"
#include "dialtek_modbus.h" 
#include "dialtek_uart.h"
#include "d_SPI.h"
#include "d_eeprom.h"
#include "hamilton_pump.h"

/*================================ EXTERN =================================== */
// extern region

extern ImunoDevice  ImunoFirmware;
extern FirmwareInfo FirmInfo;

/*================================ LOCAL ==================================== */
// local static variables
 
static unsigned int wr_reg_addr = 0;       // modbus write reg addr
static unsigned int RegisterValue = 0;     // modbus write reg velue

/*================================ MODBUS =================================== */ 
// modbus SM
static void modbus_poll(void)
{    
     // проверка, был ли Модбас запрос 

     switch( modbus_get_poll() )
     {
         case MODBUS_RHR_CMD:   // чтение holding регистров
//////////////////////////// ЧТЕНИЕ HOLDING //////////////////////////             
           // заполнение Модбас регистров переменными пользователя
           // holding_reg_write(register_address,U16 data)
            
           MODBUS_LED = ON; 
           modbus_rhr_answer(); // ответ на запрос 
           delay_ms(1);
           MODBUS_LED = OFF;
           
          break;
//////////////////////////// ЗАПИСЬ HOLDING ////////////////////////// 
          case MODBUS_WSR_CMD:  // запись holding регистров
          modbus_wsr_answer();  // ответ на запрос
          
          // заполнение переменных пользователя данными из Модбас регистров 
          // holding_reg_read(register_address,U16 data pointer)
                      
           MODBUS_LED = ON;  
           wr_reg_addr = get_wr_reg_addr();
           // get the new value
           holding_reg_read(wr_reg_addr,&RegisterValue);    
    
           switch(wr_reg_addr)
           {
               case 12:


               break;
               //==== 
               default: break;
           }
           
            eeprom_wr_regs(HOLD_REGS);
            eeprom_wr_regs(INPUT_REGS);
           
           MODBUS_LED = OFF;
          break;
//////////////////////////// ЧТЕНИЕ INPUT ////////////////////////////
          case MODBUS_RIR_CMD:  // чтение input регистров
          // заполнение переменных пользователя данными из Модбас регистров 
          // input_reg_write(register_address,U16 data)
           MODBUS_LED = ON;  
           
           input_reg_write(0,ImunoFirmware.DosingSys);
           input_reg_write(1,FirmInfo.ver);
           input_reg_write(2,FirmInfo.developer);
           
           modbus_rir_answer(); // ответ на запрос
           
           MODBUS_LED = OFF;
          break;
     }
}

/*============================ DOSING SYSTEM ================================ */ 
// dosing system logic

void main_dosing_sys(void)
{
   FirmInfo.ver = 10;               // device firmware version
   FirmInfo.developer = PONKIN;     // device firmware developer
   
   eeprom_rd_regs_H(); // reading sets from SPI EEPROM
   eeprom_rd_regs_I(); 
   
   modbus_init();      // init modbus SM
   Uart2Init();        // hamilton pump init

   while(1)
   {
      modbus_poll();
      
      init_protocol(0);
      delay_ms(100);
   }
}

// main dosing system 
/*=========================================================================== */ 