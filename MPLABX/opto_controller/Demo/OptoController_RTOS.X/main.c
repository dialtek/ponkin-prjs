#include <stdio.h>
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "main.h"
#include "fuses.h"
#include "dialtek_modbus.h"
#include "dialtek_one_wire.h"

FirmwareInfo FirmInfo;                   // device info struct instance

/*=============================== QUEUES ==================================== */

volatile QueueHandle_t sensors_q; 
volatile QueueHandle_t modbus_el_q; 
volatile QueueHandle_t sensor_qty_q; 

volatile QueueHandle_t sensor[MaxSensQty]; 

/*============================== USER FUNCS ================================= */
// USER functions

void GPIO_init()
{
    // PORT B
    TRISBbits.TRISB0 = 0;  // LED_1WIRE
    TRISBbits.TRISB1 = 0;  // LED_UART_TX
    TRISBbits.TRISB2 = 0;  // LED_RS485_TX
    TRISBbits.TRISB3 = 0;  // LED_UART_RX
    TRISBbits.TRISB4 = 0;  // LED_RS485_RX
    TRISBbits.TRISB5 = 1;  // BTN_RESET
    
    //PORT C
    TRISCbits.TRISC2 = 0;  // SPI1_CS1    EEPROM CS
   
    //PORT D
    TRISDbits.TRISD7 = 0;    //TX_EN
    TRISDbits.TRISD8 = 1;   //IN_1_MK
    LATDbits.LATD8   = 0; 
    TRISDbits.TRISD9 = 1;   //IN_2_MK
    LATDbits.LATD9   = 0; 
    TRISDbits.TRISD10 = 1;  //IN_3_MK
    LATDbits.LATD10   = 0; 
    TRISDbits.TRISD11 = 1;  //IN_4_MK
    LATDbits.LATD11   = 0; 
    
    //PORT F
    TRISFbits.TRISF0 = 0;   //Relay_1
    LATFbits.LATF0   = 0;       
    TRISFbits.TRISF1 = 0;   //Relay_2
    LATFbits.LATF1   = 0;   //
    TRISFbits.TRISF2 = 1;   // uart1_RxD
    LATFbits.LATF2   = 0;   // uart1_RxD
    TRISFbits.TRISF3 = 0;   // uart1_TxD
    LATFbits.LATF3   = 0;   // uart1_TxD
    TRISFbits.TRISF4 = 1;   //opto_RX
    LATFbits.LATF4   = 0;   //opto_RX          
    TRISFbits.TRISF5 = 0;   //opto_Tx
    LATFbits.LATF5   = 1;   //opto_Tx

    //PORT G
    TRISGbits.TRISG0 = 0;   //Relay_4
    LATGbits.LATG0   = 0; 
    TRISGbits.TRISG1 = 0;   //Relay_3
    LATGbits.LATG1   = 0;
    TRISGbits.TRISG6 = 0;   // SPI2_SCLK 
    TRISGbits.TRISG7 = 1;   // SPI2_SDI
    TRISGbits.TRISG8 = 0;   // SPI2_SDO
    
    TRISGbits.TRISG12= 0;   //1WIRE_MK_OUT
    TRISGbits.TRISG14= 1;   //1WIRE_MK_IN
    
    AD1PCFGL = 0xffff; // Port pin in Digital mode, port read input enabled, 
    AD1PCFGH = 0xffff; 
    
} 

void OSC_init()
{
        // FCY=FOSC/2, FOSC= FIN*M/(N1*N2) 
        CLKDIVbits.PLLPRE = 0;      // 0 - divider N1 = 2
        PLLFBD = 30;                // multiplier M = PLLFBD + 2
        CLKDIVbits.PLLPOST = 0;     // 0 - divider N2 = 2
        
        OSCTUN=0;                   // 000000 = Center frequency (7.37 MHz nominal)
        RCONbits.SWDTEN=0;          // Disable Watch Dog Timer
        
        while(OSCCONbits.LOCK !=1); // 1 = Indicates that PLL is in lock, or PLL start-up timer is satisfied
                                    // 0 = Indicates that PLL is out of lock, start-up timer is in progress or PLL is disabled
        //note: FOSC= 10 MHz * 32/(2*2) = 80 MHz, FCY = 80/2
 } 

void SystemInit(void)
{
    OSC_init();
    GPIO_init();
    OneWire_init();
}

void SendTmeasCmd(void)
{
    vTaskSuspendAll();      // stop the scheduler to complete sensor reading 
    OneWire_all_rd_t();
    xTaskResumeAll();       // resume scheduler work
    vTaskDelay(750);        // t meas 
}

// reset config to default
void ConfigReset(void)
{
    xQueueReset(sensor_qty_q);  // clear total sensor qty
    xQueueReset(sensors_q);
    xQueueReset(modbus_el_q); 
    xQueueReset(sensor);
    
     // clear Modbus registers
     for(char i = 0; i < 20; i++) 
         holding_reg_write(i,0);
}

/*================================ TASKS ==================================== */
// USER TASKS

/* Modbus RTU over TCP state machine */
void task_ModbusSM(void *pvParameters)
{
    static unsigned int wr_reg_addr = 0;       // modbus write reg addr
    static unsigned int RegisterValue = 0;     // modbus write reg velue
    
    static modbus_reg_element temper;
    static Tsensor Tsens;        // struct
    static unsigned int SensorsQty = 0;
    modbus_init();
    
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
         break;
//////////////////////////// ЗАПИСЬ HOLDING ////////////////////////// 
          case MODBUS_WSR_CMD:  // запись holding регистров
           modbus_wsr_answer(); // ответ на запрос
          // заполнение переменных пользователя данными из Модбас регистров 
          // holding_reg_read(register_address,U16 data pointer) !!!! <<<===
                      
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
               //=====
               default: break;
           }
          break;
//////////////////////////// ЧТЕНИЕ INPUT ////////////////////////////
          case MODBUS_RIR_CMD:  // чтение input регистров
           
            // ID датчиков не выводятся изза отсутсвия памаяти()
            /*
            xQueuePeek(sensor_qty_q, &SensorsQty, (TickType_t)0);
                      
            if(SensorsQty > 0)
            {
              for(unsigned char i = 0; i < SensorsQty; i++)
              {
                    xQueueReceive(sensor[i], &Tsens, (TickType_t)0);
                    
                    for(unsigned char j = 0; j < 8; j++)
                    {
                     input_reg_write(j+10,Tsens.ID[j]);
                    }
              }
              
             // restore sensor queue, receive cmd deleted all entities
             for(unsigned char i = 0; i < SensorsQty; i++)
                xQueueSend(sensor[i],(void*) &RxSensors[i], (TickType_t)0);
            }  
            */
              
           input_reg_write(1,FirmInfo.ver);
           input_reg_write(2,FirmInfo.developer);
           
           modbus_rir_answer(); // ответ на запрос
          break;
     }
    }
}

/* Save new sensor ID */
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
        xQueueSend(sensor_qty_q,(void*) &SensorsQty, (TickType_t)0);;
        
        // send NOT by ptr! its already ptrs
        xQueueSend(sensor[NewIndex],NewSensor, (TickType_t)0);
    } 
    vTaskSuspend(NULL);     // Suspend this task till new sensor search
}

void task_GetTemp(void *pvParameters)
{
    static modbus_reg_element temper;
    static Tsensor Tsens;   // struct 
    static Tsensor RxSensors[MaxSensQty];
    static unsigned int SensorsQty = 0;

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
                xQueueReceive(sensor[i], &Tsens, (TickType_t)0);

                vTaskSuspendAll();                 // stop RTOS scheduler
                OneWire_match_ID(&Tsens.ID);       // send MATCH ID OW cmd
                temper.data = ds18b20_i_rd_t()/10; // get T from sensor
                xTaskResumeAll();                  // resume RTOS scheduler

                temper.reg_address = Tsens.index;  // save sensor reg addr and T
                xQueueSend(modbus_el_q,(void*) &temper, (TickType_t)0);

                RxSensors[i] = Tsens; // save current sensor entity to buf 
         }
        }
         // restore sensor queue, receive cmd deleted all entities
         for(unsigned char i = 0; i < SensorsQty; i++)
            xQueueSend(sensor[i],(void*) &RxSensors[i], (TickType_t)0);
     } 
}

/*=============================== RTOS MAIN ================================= */
int main( void )
{
    SystemInit();
    
    FirmInfo.ver = 10;                // device firmware version
    FirmInfo.developer = LEUSHIN;     // device firmware developer
    
    // init Queues  
    sensors_q    = xQueueCreate(MaxSensQty, sizeof(Tsensor));
    sensor_qty_q = xQueueCreate(MaxSensQty, sizeof(unsigned char));
    modbus_el_q  = xQueueCreate(32, sizeof(modbus_reg_element));
    for(unsigned char i = 0; i < MaxSensQty; i++)
        sensor[i] = xQueueCreate(1, sizeof(Tsensor));

    // create USER tasks 
    xTaskCreate(task_ModbusSM,"ModbusSM", configMINIMAL_STACK_SIZE,NULL,1,NULL);
    xTaskCreate(task_GetTemp,"GetTemp", configMINIMAL_STACK_SIZE,NULL,0,NULL);
    
	vTaskStartScheduler(); // start the RTOS scheduler 
}

/*============================== RTOS UTILS ================================= */
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

