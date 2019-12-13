#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

#include "main.h"
#include "fuses.h"
#include "KORAD_controller.h"
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

void ModbusIDreset(void)
{
     vTaskDelay(1000);
     if(ResetBtn == OFF)
        set_modbus_id(default_devID);   
}

void SaveCfg(void)
{
   EEPR_buf[0] = (unsigned char)(KORAD_m.set_v >> 8);
   EEPR_buf[1] = (unsigned char)(KORAD_m.set_v & 0x00ff);  
   EEPR_buf[2] = (unsigned char)(KORAD_m.set_i >> 8);
   EEPR_buf[3] = (unsigned char)(KORAD_m.set_i & 0x00ff);
   EEPR_buf[4] = (unsigned char)(state_m.out_state);
   EEPR_buf[5] = (unsigned char)pol_relay_1;
   EEPR_buf[6] = (unsigned char)pol_relay_2;
   EEPR_buf[7] = get_modbus_id();
   
   eeprom_src_save(&EEPR_buf,Data2saveLen);
}

unsigned int RestoreCfg(void)
{
    //EEPR_buf[1] = (unsigned char)(KORAD_m.set_v & 0x00ff);  
    //EEPR_buf[2] = (unsigned char)(KORAD_m.set_i >> 8);
    //EEPR_buf[3] = (unsigned char)(KORAD_m.set_i & 0x00ff);
    //EEPR_buf[4] = (unsigned char)(state_m.out_state);
    //EEPR_buf[5] = (unsigned char)(state_m.pol_relay_1);
    //EEPR_buf[6] = (unsigned char)(state_m.pol_relay_2);
    //EEPR_buf[7] = (unsigned char)get_modbus_id();
    
    if(eeprom_src_restore(&EEPR_buf,Data2saveLen))
    {
       KORAD_m.set_v = (unsigned int)EEPR_buf[0] << 8 | (unsigned int)EEPR_buf[1];
       KORAD_m.set_i = (unsigned int)EEPR_buf[2] << 8 | (unsigned int)EEPR_buf[3];
       state_m.out_state   = (unsigned int)EEPR_buf[4];
       pol_relay_1 = (unsigned int)EEPR_buf[5];
       pol_relay_2 = (unsigned int)EEPR_buf[6];
       set_modbus_id(EEPR_buf[7]);
       
       xQueueSend(KORAD_SetV_q,(void*)&KORAD_m.set_v,(TickType_t)0);
       xQueueSend(KORAD_SetI_q,(void*)&KORAD_m.set_i,(TickType_t)0);
        
       xQueueSend(KORAD_SetState_q,(void*)&state_m.out_state,(TickType_t)0);
        
       POL_relay_1 = pol_relay_1;
       POL_relay_2 = pol_relay_2;
       Relay_1_LED = pol_relay_1;
       Relay_2_LED = pol_relay_2;
       
       return 1;
    }
    else return 0;
}

void ClearStructs(void)
{
    state_m.cvcc_mode    = 0;
    state_m.out_state    = 0;
    state_m.ovp_ocp_mode = 0;
    state_m.rd_process   = 0;
    
    pol_relay_1 = 0;
    pol_relay_2 = 0;
 
    KORAD_m.meas_i = 0;
    KORAD_m.meas_v = 0;
    KORAD_m.set_i  = 0;
    KORAD_m.set_v  = 0;
}
/*================================ TASKS ==================================== */
// USER TASKS

// Modbus RTU over TCP state machine
void task_ModbusSM(void *pvParameters)
{
    unsigned int wr_reg_addr = 0;       // modbus write reg addr
    unsigned int RegisterValue = 0;     // modbus write reg velue

    NewID = default_devID;

    modbus_init(); // must be before ID resore
    
    // try to restore settings from EEPROM
    holding_reg_write(17,RestoreCfg());
    // if CRC OK, setting variables and writing saved settings into target    

	while(1)
    {   
     // если запрос был в переменной modbus_request сохранен его код 
     switch(modbus_get_poll())
     {
//////////////////////////// ЧТЕНИЕ HOLDING ////////////////////////// 
         case MODBUS_RHR_CMD:
             
           Modbus_LED = ON;
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
           holding_reg_write(8,pol_relay_1);
           holding_reg_write(9,pol_relay_2);
           
           vTaskDelay(10);         // LED delay
           modbus_rhr_answer();    // modbus rhr cmd answer

           state_m.rd_process = 0; // rd status bit toggle 
           Modbus_LED = OFF;       // LED toggle
           
         break;
//////////////////////////// ЗАПИСЬ HOLDING ////////////////////////// 
          case MODBUS_WSR_CMD:  // запись holding регистров
              
           Modbus_LED = ON;     // LED toggle 
              
           modbus_wsr_answer(); // ответ на запрос
          // заполнение переменных пользователя данными из Модбас регистров 
           
           wr_reg_addr = get_wr_reg_addr();    // get address
           RegisterValue = get_wr_reg_val();   // get the new value
           
           switch(wr_reg_addr)
           {
               //=====                     
               case 10: // set voltage
                   if(RegisterValue <= 30000)
                   {
                    xQueueSend(KORAD_SetV_q,(void*) &RegisterValue,(TickType_t)0);
                    KORAD_m.set_v = RegisterValue;
                   }
               break;
               //=====                     
               case 11: // set current
                   if(RegisterValue <= 5000)
                   {
                    xQueueSend(KORAD_SetI_q,(void*) &RegisterValue,(TickType_t)0);
                    KORAD_m.set_i = RegisterValue;
                   }
               break;
               //=====  
               case 12: // set output state
                   if(RegisterValue == ON || RegisterValue == OFF)
                    xQueueSend(KORAD_SetState_q,(void*) &RegisterValue,(TickType_t)0);
               break; 
               //=====  
               case 13: // polarity relay 1
                   if(RegisterValue == ON || RegisterValue == OFF)
                   {
                    POL_relay_1 = RegisterValue;
                    Relay_1_LED = RegisterValue;
                    pol_relay_1 = RegisterValue;
                   }
               break; 
               //=====  
               case 14: // polarity relay 2
                   if(RegisterValue == ON || RegisterValue == OFF)
                   {
                    POL_relay_2 = RegisterValue;
                    Relay_2_LED = RegisterValue;
                    pol_relay_2 = RegisterValue;
                   }
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
                     holding_reg_write(20,0);
                     set_modbus_id(NewID);
                   }
               break;
               //=====
               default: break;
           } 
           
          SaveCfg();
          
          Modbus_LED = OFF;      // LED toggle 
           
          break;
//////////////////////////// ЧТЕНИЕ INPUT ////////////////////////////
          case MODBUS_RIR_CMD:   // чтение input регистров
           
           Modbus_LED = ON;      // LED toggle 
           input_reg_write(0,FirmInfo.ver);
           input_reg_write(1,FirmInfo.developer);
           input_reg_write(2,(unsigned int)get_modbus_id());
           
           modbus_rir_answer();  // ответ на запрос
           
           vTaskDelay(10);       // LED delay
           Modbus_LED = OFF;     // LED toggle 
          break;
          
       } // switch
     
             
        if(ResetBtn == OFF) // active low
        {
         ModbusIDreset();
         SaveCfg();
        }
     
    } // while
} // end of task

void task_KORAD(void *pvParameters)
{
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
    
    ClearStructs();
            
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

