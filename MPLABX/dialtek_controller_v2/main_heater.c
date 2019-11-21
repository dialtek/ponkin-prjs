#include "xc.h"
#include "main.h"
#include "d_heater.h"
#include "d_one_wire.h"
#include "dialtek_modbus.h"  
#include "d_SPI.h"
#include "d_eeprom.h"

/*================================ EXTERN =================================== */
// extern region

extern ImunoDevice  ImunoFirmware;
extern FirmwareInfo FirmInfo;

extern xHeater heater;           // heater struct instance
extern Tsensor sensor;           // sensor struct instance

unsigned int OutControl = 0xAAAA;
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
           
           OWstateMachine();    // async read all the sensors
             
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
               case 12: // heater settings
                   if(RegisterValue < MAX_T)
                    heater.SetT = RegisterValue;
               break;
               //====
               case 13: //  heater hysteresis
                   if(RegisterValue <= MAX_T/2)
                    heater.hysteresis = RegisterValue;
               break;
               //====
               case 14: // select T regulator sensor
                   if(RegisterValue <= MAX_sens_qty-1)
                    heater.sensorIndex = RegisterValue; 
               break;
               //====
               case 16: // heater ctrl
                   if(RegisterValue == ON || RegisterValue == OFF)
                    heater.enable = RegisterValue;
               break;
               //==== 
               case 30: // add the new sensor INDEX
                   if(RegisterValue <= MAX_sens_qty-1)
                    sensor.index = RegisterValue;
               break;
               //====    
               case 31: // add the new sensor ID     
                    holding_reg_write(32, AddNewSensor(RegisterValue) ); 
                    holding_reg_write(10, GetSensorsQty());
                    UpdateIDregs();
     
                    holding_reg_write(30,0); // clear sensor ID register
                    holding_reg_write(31,0); // clear sensor
               break;
               //====    
               case 35: // clear sensor config  
                   if(RegisterValue == 1)
                    ConfigReset();  
               break;
               case 36: // OUTPUT PINS Channels 0...5
                
                   holding_reg_read(36,&OutControl);
                   CPLD_SPI_WR(36,OutControl); 
               break;
               //====
               case 40: // OUTPUT PINS Channels 0...5
                
                   OneWire_reset();
               break;
               
               OneWire_reset();
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
           
           input_reg_write(0,ImunoFirmware.Heater);
           input_reg_write(1,FirmInfo.ver);
           input_reg_write(2,FirmInfo.developer);
           
           modbus_rir_answer(); // ответ на запрос
           
           MODBUS_LED = OFF;
          break;
     }
}

/*================================ HEATER =================================== */ 
// heatear ctrl logic
static void Heater(void)
{
          
       if(heater.enable == ON)
           {
            // get temperature of selected for heater sensor
            holding_reg_read(heater.sensorIndex,  &heater.CurrT);
            
            // turn off heater, 56.55 >= 50
            if(heater.CurrT/100 >= heater.SetT)
            {
                HEATER = OFF;
                HEATER_LED = OFF;   // heater 0FF
                heater.state = OFF;
            }
            
            // turn on heater if
            if(heater.CurrT/100 < (heater.SetT - heater.hysteresis))
            {
                HEATER = ON;
                HEATER_LED = ON;    // heater 0N   
                heater.state = ON;
            }
           }
       
       if (heater.enable == OFF)
       {     
                HEATER = OFF;
                HEATER_LED = OFF;   // heater 0FF
                heater.state = OFF;
       }

}

void main_heater(void)
{
   FirmInfo.ver = 10;               // device firmware version
   FirmInfo.developer = PONKIN;     // device firmware developer
   
   eeprom_rd_regs_H(); // reading sets from SPI EEPROM
   eeprom_rd_regs_I(); 

   Timer32_init();     // OW timing timer
   OWrestoreCfg();     // restore OW cfg
   
   set_modbus_id(201); // MODBUS ID !!!
   modbus_init();      // init modbus SM

   while(1)
   {
      modbus_poll();
      Heater();
   }
}

// main heater
/*=========================================================================== */ 