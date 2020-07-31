#include "xc.h"
#include "main.h"
#include "d_delay.h"
#include "d_SPI.h"
#include "dialtek_modbus.h"  
#include "d_eeprom.h"

/*=============================== EXTERN ==================================== */
// extern region
extern ImunoDevice  ImunoFirmware;
extern FirmwareInfo FirmInfo;

/*================================ LOCAL ==================================== */
// local static variables
static unsigned int wr_reg_addr = 0;       // modbus write reg addr
static unsigned int RegisterValue = 0;     // modbus write reg velue

static void SetOuts(unsigned int reg_addr, unsigned int RegValue)
{
    switch(reg_addr)
    {    
        //====  Output 1 set  
        case 15: OUT1 =  (RegValue == ON) ? ON : OFF;  break;
        //====  Output 2 set      
        case 16: OUT2 =  (RegValue == ON) ? ON : OFF;  break;
        //====  Output 3 set                
        case 17: OUT3 =  (RegValue == ON) ? ON : OFF;  break;
        //====  Output 4 set  
        case 18: OUT4 =  (RegValue == ON) ? ON : OFF;  break;
        //====  Output 5 set      
        case 19: OUT5 =  (RegValue == ON) ? ON : OFF;  break;
        //====  Output 6 set                
        case 20: OUT6 =  (RegValue == ON) ? ON : OFF;  break;                
        //====  Output 7 set  
        case 21: OUT7 =  (RegValue == ON) ? ON : OFF;  break;
        //====  Output 8 set      
        case 22: OUT8 =  (RegValue == ON) ? ON : OFF;  break;
        //====  Output 9 set                
        case 23: OUT9 =  (RegValue == ON) ? ON : OFF;  break;
        //====  Output 10 set  
        case 24: OUT10 = (RegValue == ON) ? ON : OFF;  break;
        //====  Output 11 set      
        case 25: OUT11 = (RegValue == ON) ? ON : OFF;  break;
        //====  Output 12 set                
        case 26: OUT12 = (RegValue == ON) ? ON : OFF;  break;
        //====
        default: break;
    }

}

/*================================ MODBUS =================================== */ 
// modbus SM 
static void modbus_poll(void)
{    
     switch( modbus_get_poll() )
     {
//////////////////////////// ЧТЕНИЕ HOLDING ////////////////////////// 
          case MODBUS_RHR_CMD: // чтение holding регистров

           // заполнение Модбас регистров переменными пользователя
           // holding_reg_write(register_address,U16 data)
            
           MODBUS_LED = ON; 
           
           holding_reg_write(0,IN1); 
           holding_reg_write(1,IN2); 
           holding_reg_write(2,IN3); 
           holding_reg_write(3,IN4);            
           holding_reg_write(4,IN5); 
           holding_reg_write(5,IN6); 
           holding_reg_write(6,IN7); 
           holding_reg_write(7,IN8); 
           holding_reg_write(8,IN9); 
           holding_reg_write(9,IN10); 
           holding_reg_write(10,IN11); 
           holding_reg_write(11,IN12); 
           
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
                   
           SetOuts(wr_reg_addr, RegisterValue); // set outputs
           
           eeprom_wr_regs(HOLD_REGS);
           eeprom_wr_regs(INPUT_REGS);
           
           MODBUS_LED = OFF;
          break;
//////////////////////////// ЧТЕНИЕ INPUT ////////////////////////////
          case MODBUS_RIR_CMD:  // чтение input регистров
          // заполнение переменных пользователя данными из Модбас регистров 
          // input_reg_write(register_address,U16 data)
              
           MODBUS_LED = ON; 
           
           input_reg_write(0,ImunoFirmware.IO);
           input_reg_write(1,FirmInfo.ver);
           input_reg_write(2,FirmInfo.developer);
      
           modbus_rir_answer();     // ответ на запрос
           delay_ms(1);
           MODBUS_LED = OFF;
           
          break;
     }
}

/*============================= LINE MOVEMENT =============================== */
static void IOrestoreCfg(void)
{
    unsigned int RegValue[12] = {0,0,0,0,0,0,0,0,0,0,0,0};
    
    for(unsigned int i = 15; i < 27; i++)
        holding_reg_read(i,&RegValue[i-15]);
    
    OUT1  = (RegValue[0]  == ON) ? ON : OFF;
    OUT2  = (RegValue[1]  == ON) ? ON : OFF;
    OUT3  = (RegValue[2]  == ON) ? ON : OFF;
    OUT4  = (RegValue[3]  == ON) ? ON : OFF;
    OUT5  = (RegValue[4]  == ON) ? ON : OFF;
    OUT6  = (RegValue[5]  == ON) ? ON : OFF;
    OUT7  = (RegValue[6]  == ON) ? ON : OFF;
    OUT8  = (RegValue[7]  == ON) ? ON : OFF;
    OUT9  = (RegValue[8]  == ON) ? ON : OFF;
    OUT10 = (RegValue[9]  == ON) ? ON : OFF;
    OUT11 = (RegValue[10] == ON) ? ON : OFF;
    OUT12 = (RegValue[11] == ON) ? ON : OFF;     
}

void main_io(void)
{
   FirmInfo.ver = 10;               // device firmware version
   FirmInfo.developer = PONKIN;     // device firmware developer
           
   eeprom_rd_regs_H();  // reading sets from SPI EEPROM
   eeprom_rd_regs_I();  // restire modbus regs
   
   IOrestoreCfg();      // restore outputs states
      
   modbus_init();       // init modbus SM
   
   while(1) 
   {
     modbus_poll();
   }
}

// main line movement
/*=========================================================================== */ 
