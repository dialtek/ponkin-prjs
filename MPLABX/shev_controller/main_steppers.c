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

static void SPI1_PUT_int (unsigned int buf);

// line movement steppers parameters
typedef struct axis_param_t
{ 
    unsigned int contrl; 
    unsigned int status;
    unsigned int stp_num_lsb;
    unsigned int stp_num_msb;
    unsigned int stp_width;
    unsigned int acc_min;
    unsigned int acc_max;
    unsigned int stp_ldwn_lsb;
    unsigned int stp_ldwn_msb;
    unsigned int acc_period;
    unsigned int stp_counter_lsb;
    unsigned int stp_counter_msb;
    unsigned int abs_counter_lsb;
    unsigned int abs_counter_msb;
    
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

             axis_motor[X].contrl = CPLD_SPI_RD(1);  
             holding_reg_write(1,axis_motor[X].contrl);
             
             axis_motor[X].status = CPLD_SPI_RD(2); 
             holding_reg_write(2,axis_motor[X].status);
             
             
             axis_motor[X].stp_num_lsb = CPLD_SPI_RD(3) ;
             holding_reg_write(3,axis_motor[X].stp_num_lsb);
             
             axis_motor[X].stp_num_msb = CPLD_SPI_RD(4);
             holding_reg_write(4,axis_motor[X].stp_num_msb);
             
             
             axis_motor[X].stp_width = CPLD_SPI_RD(5);
             holding_reg_write(5,axis_motor[X].stp_width);
             
             axis_motor[X].acc_min = CPLD_SPI_RD(6);
             holding_reg_write(6,axis_motor[X].acc_min);
             
             axis_motor[X].acc_max = CPLD_SPI_RD(7);
             holding_reg_write(7,axis_motor[X].acc_max);
             
             axis_motor[X].stp_ldwn_lsb = CPLD_SPI_RD(8);
             holding_reg_write(8,axis_motor[X].stp_ldwn_lsb);
             
             axis_motor[X].stp_ldwn_msb = CPLD_SPI_RD(9);
             holding_reg_write(9,axis_motor[X].stp_ldwn_msb);
            
             axis_motor[X].acc_period = CPLD_SPI_RD(10);
             holding_reg_write(10,axis_motor[X].acc_period);
             
             axis_motor[X].stp_counter_lsb = CPLD_SPI_RD(11);
             holding_reg_write(11,axis_motor[X].stp_counter_lsb);
             axis_motor[X].stp_counter_msb = CPLD_SPI_RD(12);
             holding_reg_write(12,axis_motor[X].stp_counter_msb);
             
             axis_motor[X].abs_counter_lsb = CPLD_SPI_RD(13);
             holding_reg_write(13,axis_motor[X].abs_counter_lsb);
             axis_motor[X].abs_counter_msb = CPLD_SPI_RD(14);
             holding_reg_write(14,axis_motor[X].abs_counter_msb);
           
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
//               case 0: // X axis motor speed 
//                   holding_reg_read(0,&axis_motor[X].speed);
//                   CPLD_SPI_WR(0,axis_motor[X].speed);
//               break;
               //====
               case 1: // X axis steps to move
                   holding_reg_read(1,&axis_motor[X].contrl);
                   CPLD_SPI_WR(1,axis_motor[X].contrl);
               break;
               //====
               case 2: // X axis move direction 
                   holding_reg_read(2,&axis_motor[X].status);
                   CPLD_SPI_WR(2,axis_motor[X].status);
               break;
               //====
               case 3: // X axis cmd to move
                   holding_reg_read(3,&axis_motor[X].stp_num_lsb);
                   CPLD_SPI_WR(3,axis_motor[X].stp_num_lsb);
               break;
               ////////////////////////////////////////////
               case 4: // Y axis motor speed 
                   holding_reg_read(4,&axis_motor[X].stp_num_msb);
                   CPLD_SPI_WR(4,axis_motor[X].stp_num_msb);
               break;
               //====
               case 5: // Y axis steps to move
                   holding_reg_read(5,&axis_motor[X].stp_width);
                   CPLD_SPI_WR(5,axis_motor[X].stp_width);
               break;
               //====
               case 6: // Y axis move direction 
                   holding_reg_read(6,&axis_motor[X].acc_min);
                   CPLD_SPI_WR(6,axis_motor[X].acc_min);
               break;
               //====
               case 7: // Y axis cmd to move
                   holding_reg_read(7,&axis_motor[X].acc_max);
                   CPLD_SPI_WR(7,axis_motor[X].acc_max);
               break;
                ////////////////////////////////////////////
               case 8: // Z axis motor speed 
                   holding_reg_read(8,&axis_motor[X].stp_ldwn_lsb);
                   CPLD_SPI_WR(8,axis_motor[X].stp_ldwn_lsb);
               break;
               //====
               case 9: // Z axis steps to move
                   holding_reg_read(9,&axis_motor[X].stp_ldwn_msb);
                   CPLD_SPI_WR(9,axis_motor[X].stp_ldwn_msb);
               break;
               //====
               case 10: // Z axis move direction 
                   holding_reg_read(10,&axis_motor[X].acc_period);
                   CPLD_SPI_WR(10,axis_motor[X].acc_period);
               break;
//               //====
               case 11: // Z axis cmd to move
                   holding_reg_read(11,&axis_motor[X].stp_counter_lsb);
                   CPLD_SPI_WR(11,axis_motor[X].stp_counter_lsb);
               break;              
               case 12: // Z axis cmd to move
                   holding_reg_read(12,&axis_motor[X].stp_counter_msb);
                   CPLD_SPI_WR(12,axis_motor[X].stp_counter_msb);
               break;       
               case 13: // Z axis cmd to move
                   holding_reg_read(13,&axis_motor[X].abs_counter_lsb);
                   CPLD_SPI_WR(13,axis_motor[X].abs_counter_lsb);
               break;       
               case 14: // Z axis cmd to move
                   holding_reg_read(14,&axis_motor[X].abs_counter_msb);
                   CPLD_SPI_WR(14,axis_motor[X].abs_counter_msb);
               break;       
               
               

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
  //holding_reg_read(0,&axis_motor[X].speed); 
//    holding_reg_read(1,&axis_motor[X].contrl);  
//    holding_reg_read(2,&axis_motor[X].status);
//    holding_reg_read(3,&axis_motor[X].);
//    holding_reg_read(3,&axis_motor[X].stp_num);
    
//    holding_reg_read(4,&axis_motor[Y].speed); 
//    holding_reg_read(5,&axis_motor[Y].steps);  
//    holding_reg_read(6,&axis_motor[Y].dir);
//    holding_reg_read(7,&axis_motor[Y].state);
//           
//    holding_reg_read(8,&axis_motor[Z].speed); 
//    holding_reg_read(9,&axis_motor[Z].steps);  
//    holding_reg_read(10,&axis_motor[Z].dir);
//    holding_reg_read(11,&axis_motor[Z].state);
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
       modbus_poll();
       //delay_us(1000);
       //CPLD_SPI_WR(1,0x0001);
      // SPI1_PUT_int (0x1);
   }
}

// main line movement
/*=========================================================================== */ 
