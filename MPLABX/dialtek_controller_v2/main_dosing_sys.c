#include "xc.h"
#include "main.h"
#include "dialtek_modbus.h" 
#include "dialtek_uart.h"
#include "d_SPI.h"
#include "d_eeprom.h"
#include "hamilton_pump.h"

#define SEND_CMD     (unsigned char)100
#define CHECK        (unsigned char)101
#define IDLE         (unsigned char)102

/*================================ EXTERN =================================== */
// extern region

extern ImunoDevice  ImunoFirmware;
extern FirmwareInfo FirmInfo;

/*================================ LOCAL ==================================== */
// local static variables
 
static unsigned int wr_reg_addr = 0;            // modbus write reg addr
static unsigned int RegisterValue = 0;          // modbus write reg velue

static unsigned int CPLDcontrol = 0;
static unsigned int CPLDstatus = 0;

unsigned int PSD4cmdWrStatus = 0;        // PSD4 write cmd answer status 
static unsigned int PSD4angleDir = 0;           // PSD4 valve_angle change direction
//static PSD4cmds PSD4cmd;                        // cmd list struct
static unsigned char PSD4_rd_state = SEND_CMD;  // read state machine var

static unsigned char PSD4rxTimeOut  = 20;
unsigned char PSD4rxToutOvfl = 0;
static unsigned int PSD4answer = 0;
unsigned int PSD4cmd2send = 0;
unsigned int PSD4cmd2read = CMD_get_syr_pos;
unsigned int PSD4cmdVal = 0;

unsigned char bufx[30];

static void PSD4_state_machine(void)
{
    switch(PSD4_rd_state)
    {
        case SEND_CMD:
            
            if(PSD4cmd2read == CMD_get_syr_pos)
                get_syr_pos(default_id);
            
            if(PSD4cmd2read == CMD_get_syr_vel)
                get_syr_vel(default_id);
            
            if(PSD4cmd2read == CMD_get_valve_angle)
                get_valve_angle(default_id);
            
            TmOutTimer_set(PSD4rxTimeOut);
            TmOutTimer_state(ON);
            PSD4_rd_state = IDLE;
        break;
        //====
        case IDLE:
            if(PSD4rxToutOvfl)
            {
                PSD4rxToutOvfl = 0;
                TmOutTimer_state(OFF);
                
                switch(PSD4cmd2read)
                {
                    case CMD_get_syr_pos:
                        PSD4answer = rd_syr_pos();
                        holding_reg_write(3,PSD4answer);
                        PSD4cmd2read = CMD_get_syr_vel;
                    break;
                    //===
                    case CMD_get_syr_vel:
                        PSD4answer = rd_syr_vel();
                        holding_reg_write(4,PSD4answer);
                        PSD4cmd2read = CMD_get_valve_angle;
                    break;
                    //===
                    case CMD_get_valve_angle:
                        PSD4answer = rd_valve_angle();
                        holding_reg_write(5,PSD4answer);
                        PSD4cmd2read = CMD_get_syr_pos;
                    break;
                }

                if(PSD4answer != ERROR_CODE)
                    PSD4cmdWrStatus = 1;
            }
            
            PSD4_rd_state = CHECK;
            
        break;
        //====
        case CHECK:
            
            switch(PSD4cmd2send)
            {
                 case CMD_set_syr_pos:
                  PSD4cmdWrStatus = set_syr_pos(default_id,PSD4cmdVal);
                  PSD4cmd2send = 0;
                 break;
                 //===
                 case CMD_set_syr_vel:
                  PSD4cmdWrStatus = set_syr_vel(default_id,PSD4cmdVal);
                  PSD4cmd2send = 0;
                 break;
                 //===
                 case CMD_set_valve_angle:
                  PSD4cmdWrStatus = set_valve_angle(default_id, PSD4cmdVal, PSD4angleDir);
                  PSD4cmd2send = 0;
                 break;
            }
  
            PSD4_rd_state = SEND_CMD;   
            
        break;
        //====
        default: PSD4_rd_state = SEND_CMD;   
    }
}

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
          
          CPLDstatus = CPLD_SPI_RD(2);
          
          //====================================  
          // REGISTER MAP
          
          PSD4_state_machine();
          
          holding_reg_write(0,PSD4cmdWrStatus);
          
          holding_reg_write(2,CPLDstatus);

//          for(int i = 16; i < 40; i++)
//          {
//              holding_reg_write(i,(unsigned int)bufx[i-16]);
//          }

          //====================================

          modbus_rhr_answer(); // ответ на запрос 
          
          delay_ms(1);
          MODBUS_LED = OFF;
          
          // cmd write status -> cleared after readout
          PSD4cmdWrStatus = 0;  
        
          break;
//////////////////////////// ЗАПИСЬ HOLDING ////////////////////////// 
          case MODBUS_WSR_CMD:  // запись holding регистров
          modbus_wsr_answer();  // ответ на запрос
          
          // заполнение переменных пользователя данными из Модбас регистров 
          // holding_reg_read(register_address,U16 data pointer)
                      
           MODBUS_LED = ON;  
           
           wr_reg_addr = get_wr_reg_addr();  // get the addr
           RegisterValue = get_wr_reg_val(); // get the new value
    
           switch(wr_reg_addr)
           {
               case 1: // CPLD
                   holding_reg_read(1,&CPLDcontrol);
                   CPLD_SPI_WR(1,CPLDcontrol);
               break;
               //====  
               case 8: // synigne position set
                   PSD4cmd2send = CMD_set_syr_pos;
                   PSD4cmdVal = RegisterValue; 
               break;
               //====  
               case 9: // syringe velocity set
                   PSD4cmd2send = CMD_set_syr_vel;
                   PSD4cmdVal = RegisterValue; 
               break;
               //====  
               case 10: // valve angle move dir
                    if(RegisterValue == 1 || RegisterValue == 0)
                     PSD4angleDir = RegisterValue;
               break;   
               //====  
               case 11: // valve angle move en 
                   PSD4cmd2send = CMD_set_valve_angle;
                   PSD4cmdVal = RegisterValue; 
                   //set_valve_angle(default_id, PSD4cmdVal, PSD4angleDir);
               break;
               //==== 
               case 13: // PSD4 init_protocol
                   if(RegisterValue == 1)
                   {
                    PSD4cmdWrStatus = init_protocol(1); 
                    //holding_reg_write(13,0); // clear the reg
                   }
               break;
                //==== 
               case 14: // PSD4 init_valve
                   if(RegisterValue == 1)
                   {
                    PSD4cmdWrStatus = init_valve(1); 
                    //holding_reg_write(14,0); // clear the reg
                   }
               break;
               //==== 
               case 15: // PSD4 init_syringe
                   if(RegisterValue == 1)
                   {
                    PSD4cmdWrStatus = init_syringe(1); 
                    //holding_reg_write(15,0); // clear the reg
                   }
               break;
               
               //==== 
               default: break;
           }
           
            //eeprom_wr_regs(HOLD_REGS);
            //eeprom_wr_regs(INPUT_REGS);
           
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
   FirmInfo.ver = 12;             // device firmware version
   FirmInfo.developer = PONKIN;   // device firmware developer
   //PSD4_struct_init(PSD4cmd);

   //eeprom_rd_regs_H(); // reading sets from SPI EEPROM
   //eeprom_rd_regs_I(); 
    
   set_modbus_id(202); // MODBUS ID !!!
   modbus_init();      // init modbus SM
   Uart2Init();        // hamilton pump init
   
   TmOutTimer_init();  // async timeout timer init

   // PSD4 powerON init procedure ~ 2 sec
   if(init_protocol(1))
       PSD4cmdWrStatus++; // inc if sucess
   
   if(init_valve(1))
       PSD4cmdWrStatus++; // inc if sucess
   
   if(init_syringe(1))   
       PSD4cmdWrStatus++; // inc if sucess
   
   holding_reg_write(6,PSD4cmdWrStatus);
   
   while(1)
   {
      modbus_poll();
   }
}

// main dosing system 
/*=========================================================================== */ 