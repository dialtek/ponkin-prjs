#include "xc.h"
#include "main.h"
#include "d_delay.h"
#include "d_SPI.h"
#include "dialtek_modbus.h"  
#include "d_eeprom.h"

// line movement axis
#define X 0
#define Y 1
#define Z 2

// line movement steppers parameters
typedef struct axis_param_t
{ 
    unsigned int speed; // 0 - 100 %
    unsigned int steps;
    unsigned int dir;
    unsigned int state;
    
} axis_param; 

// motor array
axis_param axis_motor[3] = { {0,0,0,0}, {0,0,0,0}, {0,0,0,0} };

/*=============================== EXTERN ==================================== */
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
     switch( modbus_get_poll() )
     {
//////////////////////////// ЧТЕНИЕ HOLDING ////////////////////////// 
          case MODBUS_RHR_CMD: // чтение holding регистров

           // заполнение Модбас регистров переменными пользователя
           // holding_reg_write(register_address,U16 data)
            
           MODBUS_LED = ON; 
           
           holding_reg_write(0,axis_motor[X].speed); 
           holding_reg_write(1,axis_motor[X].steps);  
           holding_reg_write(2,axis_motor[X].dir);
           holding_reg_write(3,axis_motor[X].state);
           
           holding_reg_write(4,axis_motor[Y].speed); 
           holding_reg_write(5,axis_motor[Y].steps);  
           holding_reg_write(6,axis_motor[Y].dir);
           holding_reg_write(7,axis_motor[Y].state);
           
           holding_reg_write(8,axis_motor[Z].speed); 
           holding_reg_write(9,axis_motor[Z].steps);  
           holding_reg_write(10,axis_motor[Z].dir);
           holding_reg_write(11,axis_motor[Z].state);
           
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
               case 0: // X axis motor speed 
                   holding_reg_read(0,&axis_motor[X].speed);
                   CPLD_SPI_WR(0,axis_motor[X].speed);
               break;
               //====
               case 1: // X axis steps to move
                   holding_reg_read(1,&axis_motor[X].steps);
                   CPLD_SPI_WR(1,axis_motor[X].steps);
               break;
               //====
               case 2: // X axis move direction 
                   holding_reg_read(2,&axis_motor[X].dir);
                   CPLD_SPI_WR(2,axis_motor[X].dir);
               break;
               //====
               case 3: // X axis cmd to move
                   holding_reg_read(3,&axis_motor[X].state);
                   CPLD_SPI_WR(3,axis_motor[X].state);
               break;
               ////////////////////////////////////////////
               case 4: // Y axis motor speed 
                   holding_reg_read(4,&axis_motor[Y].speed);
                   CPLD_SPI_WR(4,axis_motor[Y].speed);
               break;
               //====
               case 5: // Y axis steps to move
                   holding_reg_read(5,&axis_motor[Y].steps);
                   CPLD_SPI_WR(5,axis_motor[Y].steps);
               break;
               //====
               case 6: // Y axis move direction 
                   holding_reg_read(6,&axis_motor[Y].dir);
                   CPLD_SPI_WR(6,axis_motor[Y].dir);
               break;
               //====
               case 7: // Y axis cmd to move
                   holding_reg_read(7,&axis_motor[Y].state);
                   CPLD_SPI_WR(7,axis_motor[Y].state);
               break;
                ////////////////////////////////////////////
               case 8: // Z axis motor speed 
                   holding_reg_read(8,&axis_motor[Z].speed);
                   CPLD_SPI_WR(8,axis_motor[Z].speed);
               break;
               //====
               case 9: // Z axis steps to move
                   holding_reg_read(7,&axis_motor[Z].steps);
                   CPLD_SPI_WR(7,axis_motor[Z].steps);
               break;
               //====
               case 10: // Z axis move direction 
                   holding_reg_read(7,&axis_motor[Z].dir);
                   CPLD_SPI_WR(7,axis_motor[Z].dir);
               break;
               //====
               case 11: // Z axis cmd to move
                   holding_reg_read(8,&axis_motor[Z].state);
                   CPLD_SPI_WR(8,axis_motor[Z].state);
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
           
           input_reg_write(0,ImunoFirmware.LineMv);
           input_reg_write(1,FirmInfo.ver);
           input_reg_write(2,FirmInfo.developer);
      
           modbus_rir_answer();     // ответ на запрос
           delay_ms(1);
           MODBUS_LED = OFF;
           
          break;
     }
}

/*============================= LINE MOVEMENT =============================== */
static void LineMVrestoreCfg(void)
{
    holding_reg_read(0,&axis_motor[X].speed); 
    holding_reg_read(1,&axis_motor[X].steps);  
    holding_reg_read(2,&axis_motor[X].dir);
    holding_reg_read(3,&axis_motor[X].state);
    
    holding_reg_read(4,&axis_motor[Y].speed); 
    holding_reg_read(5,&axis_motor[Y].steps);  
    holding_reg_read(6,&axis_motor[Y].dir);
    holding_reg_read(7,&axis_motor[Y].state);
           
    holding_reg_read(8,&axis_motor[Z].speed); 
    holding_reg_read(9,&axis_motor[Z].steps);  
    holding_reg_read(10,&axis_motor[Z].dir);
    holding_reg_read(11,&axis_motor[Z].state);
}

void main_stepper(void)
{
   FirmInfo.ver = 10;               // device firmware version
   FirmInfo.developer = PONKIN;     // device firmware developer
           
   eeprom_rd_regs_H();  // reading sets from SPI EEPROM
   eeprom_rd_regs_I();  // restire modbus regs
   
   LineMVrestoreCfg();  // restore line movement system cfg
      
   modbus_init();       // init modbus SM
   
   while(1) 
   {
       SPI1_PUT_int(0x0001);
       modbus_poll();
   }
}

// main line movement
/*=========================================================================== */ 
