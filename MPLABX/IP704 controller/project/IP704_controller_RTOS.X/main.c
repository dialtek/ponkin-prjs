#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

#include "main.h"
#include "d_eeprom.h"
#include "fuses.h"
#include "dialtek_modbus.h"
#include "IP702_controller.h"
#include "IP702_cmds.h"
#include "dialtek_uart.h"

#define ResetBtn PORTBbits.RB3 

FirmwareInfo FirmInfo;          // device info struct instance

/*============================ RTOS OBJECTS ================================= */

volatile QueueHandle_t IP704_RdVoltage_q; 
volatile QueueHandle_t IP704_RdStatus_q; 

volatile QueueHandle_t IP704_SetV_q; 
volatile QueueHandle_t IP704_SetState_q;

volatile QueueHandle_t IP704_Ans_q; 
volatile QueueHandle_t Modbus_Status_q; 

TaskHandle_t ModbusTaskHandle;

/*============================= USER FUNCS ================================== */
// USER FUNCS

void ModbusIDset(unsigned char ID2set)
{
    set_modbus_id(ID2set);
    input_reg_write(2,(unsigned int)get_modbus_id());
    eeprom_wr_regs(INPUT_REGS);
}

void ModbusIDreset(void)
{
     vTaskDelay(1000);
     if(ResetBtn == OFF)
        ModbusIDset(default_devID);   
}

/*================================ TASKS ==================================== */
// USER TASKS

// Modbus RTU over TCP state machine
void task_ModbusSM(void *pvParameters)
{
    #define Master_485_LED LATBbits.LATB0 

    unsigned int wr_reg_addr = 0;       // modbus write reg addr
    unsigned int RegisterValue = 0;     // modbus write reg velue
       
    unsigned int IP704wrStatus = 0;
    unsigned char NewID = default_devID;
    
    IP704_state state_m;
    IP704_voltage IP704_m;
    
    modbus_init();
    RestoreCfg();

    // write saved settings
    holding_reg_read(15, &RegisterValue);     
    xQueueSend(IP704_SetV_q,(void*)&RegisterValue,(TickType_t)0);

	while(1)
    {   
     // если запрос был в переменной modbus_request сохранен его код 
     switch(modbus_get_poll())
     {
//////////////////////////// ЧТЕНИЕ HOLDING ////////////////////////// 
         case MODBUS_RHR_CMD:
             
           Master_485_LED = ON;
           // get measured voltage if queue is not empty 
           if(uxQueueMessagesWaiting(IP704_RdVoltage_q) > 0)
              xQueueReceive(IP704_RdVoltage_q, &IP704_m, (TickType_t)0);
         
           // get IP704 status if queue is not empty 
           if(uxQueueMessagesWaiting(IP704_RdStatus_q) > 0)
              xQueueReceive(IP704_RdStatus_q, &state_m, (TickType_t)0);
           
           // get command write operation status
           if(uxQueueMessagesWaiting(IP704_Ans_q) > 0)
              xQueueReceive(IP704_Ans_q, &IP704wrStatus, (TickType_t)0);
            
           // measured and set voltage
           holding_reg_write(0,IP704_m.read_v);
           holding_reg_write(1,IP704_m.set_v);
           
           // status & errors
           holding_reg_write(2,state_m.ext_control_en);
           holding_reg_write(3,state_m.charge_en);
           holding_reg_write(4,state_m.ready);
           holding_reg_write(5,state_m.remote_ctrl);      
           holding_reg_write(6,state_m.overheat);
           holding_reg_write(7,state_m.low_supply);
           holding_reg_write(8,state_m.short_circuit);
           holding_reg_write(9,state_m.load_break);  
           holding_reg_write(10,state_m.fault);  
           holding_reg_write(11,state_m.interlock);  
           
           // cmd write status -> cleared after readout
           holding_reg_write(12,IP704wrStatus);
           IP704wrStatus = 0;
           
           modbus_rhr_answer(); // modbus rhr cmd answer
           
           vTaskDelay(5);       // LED delay
           Master_485_LED = OFF; // LED toggle
           
         break;
//////////////////////////// ЗАПИСЬ HOLDING ////////////////////////// 
          case MODBUS_WSR_CMD:  // запись holding регистров
           modbus_wsr_answer(); // ответ на запрос
          // заполнение переменных пользователя данными из Модбас регистров 
           
           wr_reg_addr = get_wr_reg_addr();    // get address
           RegisterValue = get_wr_reg_val();   // get the new value
           
           switch(wr_reg_addr)
           {
               //=====                     
               case 15: // set voltage
                   if(RegisterValue <= 1000)
                   { 
                    xQueueSend(IP704_SetV_q,(void*) &RegisterValue,(TickType_t)0);
                    holding_reg_write(15, RegisterValue);
                   }
               break;
               //=====  
               case 16: // set output state
                   if(RegisterValue == ON || RegisterValue == OFF)
                    xQueueSend(IP704_SetState_q,(void*) &RegisterValue,(TickType_t)0);
               break; 
               //=====
               case 19: // reg 19 - ID set
                   if((RegisterValue > 254) && (RegisterValue == 0)) break;
                   NewID = (unsigned char)RegisterValue;
               break;
               //=====
               case 20: // reg 20 - ID confirm
                   if(RegisterValue == ON) 
                   {
                     holding_reg_write(19,0);
                     ModbusIDset(NewID);
                   }
               break;
               //=====
               default: break;
           } 
          eeprom_wr_regs(HOLD_REGS);
           
          break;
//////////////////////////// ЧТЕНИЕ INPUT ////////////////////////////
          case MODBUS_RIR_CMD:  // чтение input регистров
           
           input_reg_write(0,FirmInfo.ver);
           input_reg_write(1,FirmInfo.developer);
           input_reg_write(2,(unsigned int)get_modbus_id());
           
           modbus_rir_answer(); // ответ на запрос
          break;
          
       } // switch
     
     if(ResetBtn == OFF) // active low
        ModbusIDreset();
     
    } // while
} // end of task

void task_IP704(void *pvParameters)
{
    #define Slave_485_LED  LATBbits.LATB1 

    IP704_voltage IP704p;
    IP704_state *src_state;
    unsigned int V2set = 0;
    unsigned int State2set = 0;
    unsigned int IP704answer = 0;  

    while(1)
    {   
        // set voltage level if queue not empty
        if(uxQueueMessagesWaiting(IP704_SetV_q) > 0)
        {
           xQueueReceive(IP704_SetV_q,(void*)&V2set, (TickType_t)0);
           IP704answer = IP702_SetVoltage(V2set);
           xQueueSend(IP704_Ans_q, (void*) &IP704answer, (TickType_t)0);
           vTaskDelay(10);
        }
        
        // set output state if queue not empty
        if(uxQueueMessagesWaiting(IP704_SetState_q) > 0)
        {
           xQueueReceive(IP704_SetState_q, &State2set, (TickType_t)0);
           IP704answer = IP702_SetState(State2set);
           xQueueSend(IP704_Ans_q, (void*) &IP704answer, (TickType_t)0);
           vTaskDelay(10);
        }
        
        // read measured voltage and sets from master
        IP704p.read_v = IP702_GetVoltage();
        IP704p.set_v  = IP702_GetSets();
        xQueueSend(IP704_RdVoltage_q,(void*) &IP704p, (TickType_t)0);   
        
        // read IP704 status and errors
        src_state = IP702_GetStatus();
        xQueueSend(IP704_RdStatus_q, src_state, (TickType_t)0);  
        
        // toggle LED if IP704 answer is valid
        if(IP704p.read_v != ERROR_CODE)
        {
            Slave_485_LED = ON;
            vTaskDelay(5);
            Slave_485_LED = OFF;
            vTaskDelay(5);
        }     
    }
}

/*=============================== RTOS MAIN ================================= */
int main( void )
{
    SystemInit();

    FirmInfo.ver = 10;                // device firmware version
    FirmInfo.developer = PONKIN;      // device firmware developer
    
    // init Queues  
    IP704_RdStatus_q  = xQueueCreate(4, sizeof(IP704_state));
    IP704_RdVoltage_q = xQueueCreate(4, sizeof(IP704_voltage));
    IP704_SetV_q      = xQueueCreate(4, sizeof(unsigned int));
    IP704_SetState_q  = xQueueCreate(4, sizeof(unsigned int));
    IP704_Ans_q       = xQueueCreate(4, sizeof(unsigned int));

    // create USER tasks 
    ModbusTaskHandle = NULL;
    
    xTaskCreate(task_ModbusSM,"ModbusSM", configMINIMAL_STACK_SIZE*2,NULL,1,ModbusTaskHandle);
    xTaskCreate(task_IP704,"IP704SM", configMINIMAL_STACK_SIZE,NULL,1,NULL);
    
	vTaskStartScheduler(); // start the RTOS scheduler 
}

/*============================== RTOS HOOKS ================================= */
void vApplicationIdleHook( void )
{ // бездействие

}

void vApplicationStackOverflowHook( TaskHandle_t pxTask, char *pcTaskName )
{
	( void ) pcTaskName;
	( void ) pxTask;

	/* Run time stack overflow checking is performed if
	configCHECK_FOR_STACK_OVERFLOW is defined to 1 or 2.  This hook
	function is called if a stack overflow is detected. */
	taskDISABLE_INTERRUPTS();
	for( ;; );
}

/*=========================================================================== */

