#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

#include "main.h"
#include "d_eeprom.h"
#include "fuses.h"
#include "dialtek_modbus.h"
#include "KORAD_controller.h"
#include "KORAD_cmds.h"
#include "dialtek_uart.h"

#define ResetBtn PORTBbits.RB3 

FirmwareInfo FirmInfo;          // device info struct instance

/*============================ RTOS OBJECTS ================================= */

volatile QueueHandle_t KORAD_RdParams_q; 
volatile QueueHandle_t KORAD_RdStatus_q; 

volatile QueueHandle_t KORAD_SetV_q; 
volatile QueueHandle_t KORAD_SetI_q; 
volatile QueueHandle_t KORAD_SetState_q;

volatile QueueHandle_t KORAD_Ans_q; 
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
       
    unsigned int KORADwrStatus = 0;
    unsigned char NewID = default_devID;
    
    KORAD_state state_m;
    KORAD_params KORAD_m;
    
    modbus_init();
    //RestoreCfg();
    
    // write saved settings
    holding_reg_read(15, &RegisterValue);     
    xQueueSend(KORAD_SetV_q,(void*)&RegisterValue,(TickType_t)0);

	while(1)
    {   
     // если запрос был в переменной modbus_request сохранен его код 
     switch(modbus_get_poll())
     {
//////////////////////////// ЧТЕНИЕ HOLDING ////////////////////////// 
         case MODBUS_RHR_CMD:
             
           Master_485_LED = ON;
           // get measured voltage if queue is not empty 
           if(uxQueueMessagesWaiting(KORAD_RdParams_q) > 0)
              xQueueReceive(KORAD_RdParams_q, &KORAD_m, (TickType_t)0);
         
           // get KORAD status if queue is not empty 
           if(uxQueueMessagesWaiting(KORAD_RdStatus_q) > 0)
              xQueueReceive(KORAD_RdStatus_q, &state_m, (TickType_t)0);
            
           
           // cmd write status -> cleared after readout
           holding_reg_write(0,state_m.rd_process);
           
           // measured and set voltage
           holding_reg_write(1,KORAD_m.meas_v);
           holding_reg_write(2,KORAD_m.meas_i);
           holding_reg_write(3,KORAD_m.set_v);
           holding_reg_write(4,KORAD_m.set_i);
           
           // status 
           holding_reg_write(5,state_m.out_state); 
           holding_reg_write(6,state_m.cvcc_mode);      // 1 - CV 0 - CC
           holding_reg_write(7,state_m.ovp_ocp_mode); 
           
           vTaskDelay(5);          // LED delay
           
           modbus_rhr_answer();    // modbus rhr cmd answer
           
           state_m.rd_process = 0; // rd status bit toggle 
           Master_485_LED = OFF;   // LED toggle
           
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
                   if(RegisterValue <= 30000)
                   { 
                    xQueueSend(KORAD_SetV_q,(void*) &RegisterValue,(TickType_t)0);
                    holding_reg_write(15, RegisterValue);
                   }
               break;
               //=====                     
               case 16: // set current
                   if(RegisterValue <= 5000)
                   { 
                    xQueueSend(KORAD_SetI_q,(void*) &RegisterValue,(TickType_t)0);
                    holding_reg_write(16, RegisterValue);
                   }
               break;
               //=====  
               case 17: // set output state
                   if(RegisterValue == ON || RegisterValue == OFF)
                    xQueueSend(KORAD_SetState_q,(void*) &RegisterValue,(TickType_t)0);
                   holding_reg_write(17, RegisterValue);
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

void task_KORAD(void *pvParameters)
{
    #define RS232_LED  LATBbits.LATB1 

    KORAD_params KORADp;
    KORAD_state *src_state;
    unsigned int V2set = 0, I2set = 0;
    unsigned int State2set = 0;

    while(1)
    {   
        // set voltage level if queue not empty
        if(uxQueueMessagesWaiting(KORAD_SetV_q) > 0)
        {
           xQueueReceive(KORAD_SetV_q,(void*)&V2set, (TickType_t)0);
           KORAD_SetVoltage(V2set);
        }
        
        // set current value if queue not empty
        if(uxQueueMessagesWaiting(KORAD_SetI_q) > 0)
        {
           xQueueReceive(KORAD_SetI_q,(void*)&I2set, (TickType_t)0);
           KORAD_SetCurrent(I2set);
        }
        
        // set output state if queue not empty
        if(uxQueueMessagesWaiting(KORAD_SetState_q) > 0)
        {
           xQueueReceive(KORAD_SetState_q, &State2set, (TickType_t)0);
           KORAD_SetState(State2set);
        }
        
        // read measured V I, and V I sets
        KORADp.meas_v = KORAD_GetVoltage();
        KORADp.set_v  = KORAD_GetVSets();
        KORADp.meas_i = KORAD_GetCurrent();
        KORADp.set_i  = KORAD_GetISets();
        xQueueSend(KORAD_RdParams_q,(void*) &KORADp, (TickType_t)0);   
        
        // read KORAD status
        src_state = KORAD_GetStatus();
        xQueueSend(KORAD_RdStatus_q, src_state, (TickType_t)0); 
        
        // toggle LED if KORAD answer is valid
        if(KORADp.meas_v != ERROR_CODE)
        {
            RS232_LED = ON;
            vTaskDelay(5);
            RS232_LED = OFF;
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
    KORAD_RdStatus_q  = xQueueCreate(4, sizeof(KORAD_state));
    KORAD_RdParams_q  = xQueueCreate(4, sizeof(KORAD_params));
    KORAD_SetV_q      = xQueueCreate(4, sizeof(unsigned int));
    KORAD_SetI_q      = xQueueCreate(4, sizeof(unsigned int));
    KORAD_SetState_q  = xQueueCreate(4, sizeof(unsigned int));
    KORAD_Ans_q       = xQueueCreate(4, sizeof(unsigned int));

    // create USER tasks 
    ModbusTaskHandle = NULL;
    
    xTaskCreate(task_ModbusSM,"ModbusSM", configMINIMAL_STACK_SIZE*2,NULL,1,ModbusTaskHandle);
    xTaskCreate(task_KORAD,"task_KORAD_SM", configMINIMAL_STACK_SIZE,NULL,1,NULL);
    
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

