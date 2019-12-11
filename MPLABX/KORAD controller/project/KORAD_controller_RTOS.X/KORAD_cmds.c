#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "main.h"
#include "KORAD_uart.h"
#include "KORAD_cmds.h"

/*=========================================================================== */
// extern
extern volatile QueueHandle_t KORADrxBytes;

/*=========================================================================== */
// local
static unsigned char SrcAnswer[10] = {0,0,0,0,0,0,0,0,0,0}; 
static UBaseType_t RxQueueCnt = 0;

/*=========================================================================== */
// KORAD commands

// converts char symbol into number
unsigned char char2num(unsigned char ch) 
{ 
    return ch - 0x30;
}

// converts number into char symbol
unsigned char num2char(unsigned char ch) 
{ 
    return ch + 0x30;
}

// измерени€ выходного напр€жени€
unsigned int KORAD_GetVoltage(void)
{  
    unsigned int SrcMeasVoltage = ERROR_CODE;
    
    // cmd sending sequence
    vTaskSuspendAll(); // приостановка диспетчера на момент отправки посылки
    Uart2SendText("VOUT1?"); // отсылка команды
    xTaskResumeAll();  // возобновление работы диспетчера
    
    vTaskDelay(60); // readout timeout ~ 60 ms
    
    // get src answer rx bytes count 
    RxQueueCnt = uxQueueMessagesWaiting(KORADrxBytes);
    
    if(RxQueueCnt > 0)
    {
        // saving received bytes from rx queue
        for(UBaseType_t i = 0; i < RxQueueCnt; i++)
            xQueueReceive(KORADrxBytes, &SrcAnswer[i], (TickType_t) 5);

        SrcMeasVoltage = (unsigned int)(
        char2num(SrcAnswer[0]) * 10000 +
        char2num(SrcAnswer[1]) * 1000 +
        char2num(SrcAnswer[3]) * 100 +
        char2num(SrcAnswer[4]) * 10);
    }
    else 
        SrcMeasVoltage = ERROR_CODE; // answer error 
    
    return SrcMeasVoltage;
}

// запрос текущего уровн€ уставки напр€жени€
unsigned int KORAD_GetVSets(void)
{  
    unsigned int SrcSetVoltage = ERROR_CODE;
    
    // cmd sending sequence
    vTaskSuspendAll(); // приостановка диспетчера на момент отправки посылки
    Uart2SendText("VSET1?"); // отсылка команды
    xTaskResumeAll();  // возобновление работы диспетчера
    
    vTaskDelay(60); // readout timeout ~ 60 ms
    
    // get src answer rx bytes count 
    RxQueueCnt = uxQueueMessagesWaiting(KORADrxBytes);
    
    if(RxQueueCnt > 0)
    {
        // saving received bytes from rx queue
        for(UBaseType_t i = 0; i < RxQueueCnt; i++)
            xQueueReceive(KORADrxBytes, &SrcAnswer[i], (TickType_t) 5);
      
        SrcSetVoltage = (unsigned int)(
        char2num(SrcAnswer[0]) * 10000 +
        char2num(SrcAnswer[1]) * 1000 +
        char2num(SrcAnswer[3]) * 100 +
        char2num(SrcAnswer[4]) * 10);

    }
    else 
        SrcSetVoltage = ERROR_CODE; // answer error 
    
    return SrcSetVoltage;
}

// установка напр€жени€
void KORAD_SetVoltage(unsigned int V2set)
{
    // VSET1:12.34
    
    // get chars from number
    unsigned int first_num  = V2set / 10000;
    unsigned int sec_num    = (V2set - first_num * 10000) / 1000;
    unsigned int thidr_num  = (V2set - first_num * 10000 - sec_num * 1000) / 100;
    unsigned int fourth_num = (V2set - first_num * 10000 - sec_num * 1000 - thidr_num * 100) / 10;
    
    // cmd sending sequence
    vTaskSuspendAll(); // приостановка диспетчера на момент отправки посылки
    Uart2SendText("VSET1:");            // отсылка команды
    Uart2SendByte(num2char(first_num));
    Uart2SendByte(num2char(sec_num));
    Uart2SendText("."); 
    Uart2SendByte(num2char(thidr_num));
    Uart2SendByte(num2char(fourth_num));
    xTaskResumeAll(); // возобновление работы диспетчера
    
    vTaskDelay(60);
}

// измерени€ выходного тока
unsigned int KORAD_GetCurrent(void)
{  
    unsigned int SrcMeasCurrent = ERROR_CODE;
    
    // cmd sending sequence
    vTaskSuspendAll(); // приостановка диспетчера на момент отправки посылки
    Uart2SendText("IOUT1?"); // отсылка команды
    xTaskResumeAll();  // возобновление работы диспетчера
    
    vTaskDelay(60); // readout timeout ~ 60 ms
    
    // get src answer rx bytes count 
    RxQueueCnt = uxQueueMessagesWaiting(KORADrxBytes);
    
    if(RxQueueCnt > 0)
    {
        // saving received bytes from rx queue
        for(UBaseType_t i = 0; i < RxQueueCnt; i++)
            xQueueReceive(KORADrxBytes, &SrcAnswer[i], (TickType_t) 5);

        SrcMeasCurrent = (unsigned int)(
        char2num(SrcAnswer[0]) * 1000 +
        char2num(SrcAnswer[2]) * 100 +
        char2num(SrcAnswer[3]) * 10 +
        char2num(SrcAnswer[4]));
    }
    else 
        SrcMeasCurrent = ERROR_CODE; // answer error 
    
    return SrcMeasCurrent;
}

// запрос текущей уставки тока
unsigned int KORAD_GetISets(void)
{  
    unsigned int SrcSetCurrent = ERROR_CODE;
    
    // cmd sending sequence
    vTaskSuspendAll(); // приостановка диспетчера на момент отправки посылки
    Uart2SendText("ISET1?"); // отсылка команды
    xTaskResumeAll();  // возобновление работы диспетчера
    
    vTaskDelay(60); // readout timeout ~ 60 ms
    
    // get src answer rx bytes count 
    RxQueueCnt = uxQueueMessagesWaiting(KORADrxBytes);
    
    if(RxQueueCnt > 0)
    {
        // saving received bytes from rx queue
        for(UBaseType_t i = 0; i < RxQueueCnt; i++)
            xQueueReceive(KORADrxBytes, &SrcAnswer[i], (TickType_t) 5);
      
        SrcSetCurrent = (unsigned int)(
        char2num(SrcAnswer[0]) * 1000 +
        char2num(SrcAnswer[2]) * 100 +
        char2num(SrcAnswer[3]) * 10 +
        char2num(SrcAnswer[4]));

    }
    else 
        SrcSetCurrent = ERROR_CODE; // answer error 
    
    return SrcSetCurrent;
}

// установка тока
void KORAD_SetCurrent(unsigned int I2set)
{
    // ISET1:0.125
    
    // get chars from number
    unsigned int first_num  =  I2set / 1000;
    unsigned int sec_num    = (I2set - first_num * 1000) / 100;
    unsigned int thidr_num  = (I2set - first_num * 1000 - sec_num * 100) / 10;
    unsigned int fourth_num = (I2set - first_num * 1000 - sec_num * 100 - thidr_num * 10);
    
    // cmd sending sequence
    vTaskSuspendAll(); // приостановка диспетчера на момент отправки посылки
    Uart2SendText("ISET1:");            // отсылка команды
    Uart2SendByte(num2char(first_num));
    Uart2SendText("."); 
    Uart2SendByte(num2char(sec_num));
    Uart2SendByte(num2char(thidr_num));
    Uart2SendByte(num2char(fourth_num));
    xTaskResumeAll(); // возобновление работы диспетчера
    
    vTaskDelay(60);
}

// установка состо€ни€ выхода
void KORAD_SetState(unsigned int state)
{
  char *s = (state) ? "OUT1" : "OUT0";

  // cmd sending sequence
  vTaskSuspendAll(); // приостановка диспетчера на момент отправки посылки
  Uart2SendText(s); // отсылка команды
  xTaskResumeAll();  // возобновление работы диспетчера

  vTaskDelay(60); // readout timeout ~ 60 ms  

}

// чтение статуса
KORAD_state* KORAD_GetStatus(void)
{  
    unsigned char SrcStatus;   
    static KORAD_state SrcState;
    
    SrcState.cvcc_mode    = ERROR_CODE; 
    SrcState.out_state    = ERROR_CODE; 
    SrcState.ovp_ocp_mode = ERROR_CODE; 
    SrcState.rd_process   = 0; // reset rd status bit
    
    vTaskSuspendAll(); // приостановка диспетчера на момент отправки посылки
    Uart2SendText("STATUS?"); // отсылка команды
    xTaskResumeAll();  // возобновление работы диспетчера
    
    vTaskDelay(60); // readout timeout ~ 60 ms

    // get src answer rx bytes count 
    RxQueueCnt = uxQueueMessagesWaiting(KORADrxBytes);
    
    if(RxQueueCnt > 0)
    {
        // saving received bytes from rx queue
        for(UBaseType_t i = 0; i < RxQueueCnt; i++)
            xQueueReceive(KORADrxBytes, &SrcAnswer[i], (TickType_t) 5);
    
        SrcStatus = SrcAnswer[0];

        SrcState.cvcc_mode     = (unsigned int)(SrcStatus & 1); 
        SrcState.out_state     = (unsigned int)(SrcStatus & (1 << 6) ? 1 : 0); 
        SrcState.ovp_ocp_mode  = (unsigned int)(SrcStatus & (1 << 5) ? 1 : 0);    
       
        if(SrcAnswer[0] != 0)
         SrcState.rd_process = 1; // toggle rd status bit
    }
    else { }
        
    return &SrcState;
}

// KORAD commands
/*=========================================================================== */

