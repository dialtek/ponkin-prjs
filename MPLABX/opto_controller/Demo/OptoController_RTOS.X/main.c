#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "main.h"
#include "d_eeprom.h"
#include "fuses.h"
#include "dialtek_modbus.h"
#include "dialtek_one_wire.h"


/*=============================== QUEUES ==================================== */

volatile QueueHandle_t modbus_el_q; 
volatile QueueHandle_t sensor_qty_q; 
volatile QueueHandle_t sensor[MaxSensQty]; 

/*============================== USER FUNCS ================================= */
// USER functions

void GPIO_init(void)
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

void OSC_init(void)
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
    SPI2_init();
    OneWire_init();
}

void SendTmeasCmd(void)
{
    vTaskSuspendAll();      // stop the scheduler to complete sensor reading 
    OneWire_all_rd_t();
    xTaskResumeAll();       // resume scheduler work
    vTaskDelay(750);        // t meas 
}

void ConfigReset(void)
{
    if(sensor_qty_q != NULL)
        xQueueReset(sensor_qty_q);  // clear total sensor qty
    
    if(modbus_el_q != NULL)
        xQueueReset(modbus_el_q);   // clear modbus rx queue 
    
    for(unsigned char i = 0; i < MaxSensQty; i++)
    {
       if(sensor[i] != NULL)        // clear sensor indexex and ID
        xQueueReset(sensor[i]);
    }
     
    for(char i = 10; i < 120; i++)  // clear Modbus registers
    {
        input_reg_write(i,0);
        holding_reg_write(i-10,0);
    }
    
    // clear eeprom
    eeprom_wr_regs(HOLD_REGS);
    eeprom_wr_regs(INPUT_REGS);
}

unsigned int UpdateIDregs(unsigned char EN)
{
     if( (xSemaphoreTake(NewSensSemph, (TickType_t)0)) || EN)
     {   
         Tsensor Tsens;  
         unsigned int SenQty = 0;
         
        // save current sensor qty
        xQueuePeek(sensor_qty_q, &SenQty, (TickType_t)0);

        if(SenQty > 0) // if any sensors added
        {
          for(unsigned char i = 0; i < SenQty; i++)
          { 
                // save sensors ID into local var
                xQueuePeek(sensor[i], &Tsens, (TickType_t)0);

                // fill input regs - sensors ID
                for(unsigned char j = 0; j < 8; j++)
                   input_reg_write((10+10*i)+j,Tsens.ID[j]);
          }
        }
        return 1;
     }
     else 
         return 0;
}

void RestoreCfg(void)
{
    unsigned int SensQtySaved = 0;                // current sensors qty
    Tsensor RestoredSensor;  
    unsigned int buf[ID_lenght];
    unsigned char IDptr = 0;
    
    // saved sensors qty
    holding_reg_read(20, &SensQtySaved); 
    
    // check if restored sensors        
    if(SensQtySaved > 0 && SensQtySaved <= MaxSensQty) 
    {
        for(char i = 0; i < SensQtySaved; i++)
        {
            RestoredSensor.index = i;
            
            for(char j = 0; j < ID_lenght; j++)
            {
                input_reg_read(IDptr+10, &buf[j]);       // get ID from input regs
                IDptr++;
                
                RestoredSensor.ID[j] = (unsigned char)buf[j];
            }
            
            // fill sensor queue
            xQueueSend(sensor[i],&RestoredSensor, (TickType_t)0);
                     
            // ID - 8 regs
            IDptr += 2; // shift ptr to next ID point - 10,20,30...
        }

        // restore sensors qty
        if(SensQtySaved <= MaxSensQty);
            xQueueSend(sensor_qty_q,(void*) &SensQtySaved, (TickType_t)0);
    }

}

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

