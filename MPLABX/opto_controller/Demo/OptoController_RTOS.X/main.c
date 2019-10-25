#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "main.h"
#include "d_eeprom.h"
#include "fuses.h"
#include "dialtek_modbus.h"
#include "dialtek_one_wire.h"
#include "opto_controller.h"

FirmwareInfo FirmInfo;          // device info struct instance

/*============================ RTOS OBJECTS ================================= */

volatile QueueHandle_t modbus_el_q; 
volatile QueueHandle_t sensor_qty_q; 
volatile QueueHandle_t sensor[MaxSensQty]; 

SemaphoreHandle_t NewSensSemph; // new sensor adding semph

/*================================ TASKS ==================================== */
// USER TASKS

// Modbus RTU over TCP state machine
void task_ModbusSM(void *pvParameters)
{
    static unsigned int wr_reg_addr = 0;       // modbus write reg addr
    static unsigned int RegisterValue = 0;     // modbus write reg velue
    
    static modbus_reg_element temper;
    static Tsensor Tsens;                      // struct
    static unsigned int SensorsQty = 0;
   
    modbus_init();
    RestoreCfg();
            
	while(1)
    {
     // если запрос был в переменной modbus_request сохранен его код 
     switch(modbus_get_poll())
     {
//////////////////////////// ЧТЕНИЕ HOLDING ////////////////////////// 
         case MODBUS_RHR_CMD: // чтение holding регистров
           
           if(uxQueueMessagesWaiting(modbus_el_q) > 0)
            xQueueReceive(modbus_el_q, &temper, (TickType_t)0);
           
           if(uxQueueMessagesWaiting(sensor_qty_q) > 0)
            xQueuePeek(sensor_qty_q, &SensorsQty, (TickType_t)0);
           
           holding_reg_write(temper.reg_address, (unsigned int)temper.data); 
           holding_reg_write(20, SensorsQty); 
           
           modbus_rhr_answer(); // ответ на запрос
           
           if(UpdateIDregs(0))  // update regs if new sensor added
           {
             eeprom_wr_regs(HOLD_REGS);
             eeprom_wr_regs(INPUT_REGS);
           }
           
         break;
//////////////////////////// ЗАПИСЬ HOLDING ////////////////////////// 
          case MODBUS_WSR_CMD:  // запись holding регистров
           modbus_wsr_answer(); // ответ на запрос
          // заполнение переменных пользователя данными из Модбас регистров 
           
           wr_reg_addr = get_wr_reg_addr();    // get address
           RegisterValue = get_wr_reg_val();   // get the new value
           
           switch(wr_reg_addr)
           {
               case 30: // add the new sensor INDEX
                  if(RegisterValue <= MaxSensQty-1)
                    Tsens.index = RegisterValue;
               break;
               //=====
               case 31: // add the new sensor ID 
                   if(RegisterValue == 1)
                    xTaskCreate(task_GetSensorID,"GetSensorID",
                            configMINIMAL_STACK_SIZE, (void*)&Tsens,2,NULL);                        // start the scheduler
                    
                   holding_reg_write(30,0); // clear sensor ID register
                   holding_reg_write(31,0); // clear sensor
               break;
               //=====
               case 35: // clear sensor config  
                   if(RegisterValue == 1)
                    ConfigReset(); 
               break;
               //=====
               default: break;
           } 
          break;
//////////////////////////// ЧТЕНИЕ INPUT ////////////////////////////
          case MODBUS_RIR_CMD:  // чтение input регистров
           
           UpdateIDregs(1); // update regs by EN
           
           input_reg_write(1,FirmInfo.ver);
           input_reg_write(2,FirmInfo.developer);
           
           modbus_rir_answer(); // ответ на запрос
           eeprom_wr_regs(INPUT_REGS);
          break;
          
       } // switch
    } // while
} // end of task

// Save new sensors ID 
void task_GetSensorID(void *pvParameters)
{
    static Tsensor *NewSensor;// struct 
    static unsigned int NewIndex = 0;
    
    static unsigned char Search_Ok = 0;
    static unsigned int SensorsQty = 0;
    
    // Преобразование типа void* к типу Tsensor*
    NewSensor = (Tsensor*) pvParameters;
    
    NewIndex = NewSensor->index;
    
    vTaskSuspendAll();                          // stop the scheduler
    Search_Ok = get_sensor_ID(&NewSensor->ID);  // save the new sensor ID   
    xTaskResumeAll();                           // start the scheduler
    
    if(Search_Ok) // if sensor is found
    {    
        xQueueReceive(sensor_qty_q, &SensorsQty, (TickType_t)0);
        SensorsQty++;       // set sensor index
        xQueueSend(sensor_qty_q,(void*) &SensorsQty, (TickType_t)0);
        
        // send NOT by ptr! its already ptrs
        xQueueSend(sensor[NewIndex],NewSensor, (TickType_t)0);
        
        if( NewSensSemph != NULL )
            xSemaphoreGive(NewSensSemph);
    } 
    vTaskSuspend(NULL);     // Suspend this task till new sensor search
}

// OW temperature measurement task
void task_GetTemp(void *pvParameters)
{
    static modbus_reg_element temper;
    static Tsensor Tsens;   // struct 
    static unsigned int SensorsQty = 0;

    // 1 sensor redout time ~ 15 ms + 7 ms period 
    
    while(1)
    {
        // get sensor qty if were added
        if(uxQueueMessagesWaiting(sensor_qty_q) > 0)
            xQueuePeek(sensor_qty_q, &SensorsQty, (TickType_t)0);
        else
           taskYIELD(); 

        SendTmeasCmd(); // send measure cmd to existing sensors
  
        // read T from existig sensors
        for(unsigned char i = 0; i < SensorsQty; i++)
        {
            // check sensor exist by index
            if(uxQueueMessagesWaiting(sensor[i]) > 0)
            {
                // receive sensor entity
                xQueuePeek(sensor[i], &Tsens, (TickType_t)0);

                vTaskSuspendAll();                 // stop RTOS scheduler
                OneWire_match_ID(&Tsens.ID);       // send MATCH ID OW cmd
                temper.data = ds18b20_i_rd_t()/10; // get T from sensor
                xTaskResumeAll();                  // resume RTOS scheduler

                temper.reg_address = Tsens.index;  // save sensor reg addr and T
                xQueueSend(modbus_el_q,(void*) &temper, (TickType_t)0);   
            }
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
    sensor_qty_q = xQueueCreate(MaxSensQty, sizeof(unsigned char));
    modbus_el_q  = xQueueCreate(32, sizeof(modbus_reg_element));
    for(unsigned char i = 0; i < MaxSensQty; i++)
        sensor[i] = xQueueCreate(1, sizeof(Tsensor));

    // create USER tasks 
    xTaskCreate(task_ModbusSM,"ModbusSM", configMINIMAL_STACK_SIZE*2,NULL,1,NULL);
    xTaskCreate(task_GetTemp,"GetTemp", configMINIMAL_STACK_SIZE,NULL,0,NULL);
    
    NewSensSemph = xSemaphoreCreateBinary();
    
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

