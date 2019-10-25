#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "main.h"
#include "IP702_uart.h"
#include "IP702_cmds.h"

/*=========================================================================== */
// extern
extern volatile QueueHandle_t IP702RxBytes;

/*=========================================================================== */
// local
static unsigned char SrcAnswer[10] = {0,0,0,0,0,0,0,0,0,0}; 
static UBaseType_t RxQueueCnt = 0;
static unsigned char CRCread;
static unsigned int  CRCcalc; 


/*=========================================================================== */
// IP704 commands

// измерения выходного напряжения (выход АЦП)
unsigned int IP702_GetVoltage(void)
{  
    unsigned int SrcMeasVoltage = ERROR_CODE;
    
    // cmd sending sequence
    vTaskSuspendAll(); // приостановка диспетчера на момент отправки посылки
    IP702_TX_EN;
    Uart2SendByte(begin_CMD);        // #
    Uart2SendByte(cmd_lenght1);      // cmd lenght
    Uart2SendByte(measV_CMD);        // cmd
    Uart2SendByte(SrcAddr);          // source address
    Uart2SendByte(0x07);             // CRC
    IP702_TX_DIS;
    xTaskResumeAll(); // возобновление работы диспетчера
    
    vTaskDelay(5); // readout timeout ~ 2 ms
    
    // get src answer rx bytes count 
    RxQueueCnt = uxQueueMessagesWaiting(IP702RxBytes);
    
    if(RxQueueCnt > 0)
    {
        // saving received bytes from rx queue
        for(UBaseType_t i = 0; i < RxQueueCnt; i++)
            xQueueReceive(IP702RxBytes, &SrcAnswer[i], (TickType_t) 5);
    
        CRCread = SrcAnswer[8];
    
        CRCcalc = SrcAnswer[2] + SrcAnswer[3] + SrcAnswer[4] + 
                  SrcAnswer[5] + SrcAnswer[6] + SrcAnswer[7];
    
        CRCcalc = CRCcalc & 0x00ffU;
    
        if((unsigned char)CRCcalc == CRCread)
        {   // the succeed answer  
            SrcMeasVoltage = (unsigned int)((SrcAnswer[6] << 8) | SrcAnswer[7]);
        }
    }
    else 
        SrcMeasVoltage = ERROR_CODE; // answer error 
    
    return SrcMeasVoltage;
}

// запрос текущего уровня уставки напряжения заряда конденсаторов
unsigned int IP702_GetSets(void)
{  
    unsigned int SrcSetVoltage = ERROR_CODE;
    
    // cmd sending sequence
    vTaskSuspendAll(); // приостановка диспетчера на момент отправки посылки
    IP702_TX_EN;
    Uart2SendByte(begin_CMD);        // #
    Uart2SendByte(cmd_lenght1);      // cmd lenght
    Uart2SendByte(getSets_CMD);      // cmd
    Uart2SendByte(SrcAddr);          // source address
    Uart2SendByte(0x3B);             // CRC
    IP702_TX_DIS;
    xTaskResumeAll(); // возобновление работы диспетчера
    
    vTaskDelay(5); // readout timeout ~ 2 ms
    
    // get src answer rx bytes count 
    RxQueueCnt = uxQueueMessagesWaiting(IP702RxBytes);
    
    if(RxQueueCnt > 0)
    {
        // saving received bytes from rx queue
        for(UBaseType_t i = 0; i < RxQueueCnt; i++)
            xQueueReceive(IP702RxBytes, &SrcAnswer[i], (TickType_t) 5);
    
        CRCread = SrcAnswer[8];
    
        CRCcalc = SrcAnswer[2] + SrcAnswer[3] + SrcAnswer[4] + 
                  SrcAnswer[5] + SrcAnswer[6] + SrcAnswer[7];
    
        CRCcalc = CRCcalc & 0x00ffU;
    
        if((unsigned char)CRCcalc == CRCread)
        {   // the succeed answer  
            SrcSetVoltage = (unsigned int)((SrcAnswer[6] << 8) | SrcAnswer[7]);
        }
    }
    else 
        SrcSetVoltage = ERROR_CODE; // answer error 
    
    return SrcSetVoltage;
}

// чтение статуса и ошибок
IP704_state* IP702_GetStatus(void)
{  
    unsigned char SrcStatus;
    unsigned char SrcErrors;

    static IP704_state SrcState;
    
    SrcState.ext_control_en = ERROR_CODE; 
    SrcState.charge_en      = ERROR_CODE; 
    SrcState.ready          = ERROR_CODE; 
    SrcState.remote_ctrl    = ERROR_CODE; 

    SrcState.overheat       = ERROR_CODE; 
    SrcState.low_supply     = ERROR_CODE; 
    SrcState.short_circuit  = ERROR_CODE; 
    SrcState.load_break     = ERROR_CODE; 
    SrcState.fault          = ERROR_CODE; 
    SrcState.interlock      = ERROR_CODE; 

    // cmd sending sequence
    vTaskSuspendAll(); // приостановка диспетчера на момент отправки посылки
    IP702_TX_EN;
    Uart2SendByte(begin_CMD);        // #
    Uart2SendByte(cmd_lenght1);      // cmd lenght
    Uart2SendByte(getStatus_CMD);    // cmd
    Uart2SendByte(SrcAddr);          // source address
    Uart2SendByte(0x0B);             // CRC - 10B
    IP702_TX_DIS;
    xTaskResumeAll(); // возобновление работы диспетчера
    
    vTaskDelay(5); // readout timeout ~ 2 ms
    
    // get src answer rx bytes count 
    RxQueueCnt = uxQueueMessagesWaiting(IP702RxBytes);
    
    if(RxQueueCnt > 0)
    {
        // saving received bytes from rx queue
        for(UBaseType_t i = 0; i < RxQueueCnt; i++)
            xQueueReceive(IP702RxBytes, &SrcAnswer[i], (TickType_t) 5);
    
        CRCread = SrcAnswer[8];
    
        CRCcalc = SrcAnswer[2] + SrcAnswer[3] + SrcAnswer[4] + 
                  SrcAnswer[5] + SrcAnswer[6] + SrcAnswer[7];
    
        CRCcalc = CRCcalc & 0x00ffU;
    
        if((unsigned char)CRCcalc == CRCread)
        {   // the succeed answer  
            SrcStatus = SrcAnswer[6];
            SrcErrors = SrcAnswer[7];
            
            SrcState.ext_control_en = (unsigned int)(SrcStatus & 1); 
            SrcState.charge_en     = SrcStatus & (1 << 1) ? 1 : 0; 
            SrcState.ready         = SrcStatus & (1 << 3) ? 1 : 0; 
            SrcState.remote_ctrl   = SrcStatus & (1 << 6) ? 1 : 0; 
            
            SrcState.overheat = (unsigned int)(SrcErrors & 1); 
            SrcState.low_supply    = SrcErrors & (1 << 1) ? 1 : 0; 
            SrcState.short_circuit = SrcErrors & (1 << 2) ? 1 : 0; 
            SrcState.load_break    = SrcErrors & (1 << 3) ? 1 : 0; 
            SrcState.fault         = SrcErrors & (1 << 4) ? 1 : 0; 
            SrcState.interlock     = SrcErrors & (1 << 6) ? 1 : 0;            
        }
    }
    else { }
        
    return &SrcState;
}

// установка напряжения
unsigned int IP702_SetVoltage(unsigned int V2set)
{
    unsigned char V_lsb, V_msb;
    
    V_msb = (unsigned char)(V2set >> 8);
    V_lsb = (unsigned char)(V2set & 0x00ff);
    CRCcalc = begin_CMD + cmd_lenght2 + setU_CMD + SrcAddr + V_msb + V_lsb;
    
    // cmd sending sequence
    vTaskSuspendAll(); // приостановка диспетчера на момент отправки посылки
    IP702_TX_EN;
    Uart2SendByte(begin_CMD);        // #
    Uart2SendByte(cmd_lenght2);      // cmd lenght
    Uart2SendByte(setU_CMD);
    Uart2SendByte(SrcAddr);          // source address
    Uart2SendByte(V_msb);            // msb
    Uart2SendByte(V_lsb);            // lsb
    Uart2SendByte((unsigned char)(CRCcalc & 0x00ff));
    IP702_TX_DIS;
    xTaskResumeAll(); // возобновление работы диспетчера
    
    vTaskDelay(5);    // readout timeout ~ 2 ms
    
    // get src answer rx bytes count 
    RxQueueCnt = uxQueueMessagesWaiting(IP702RxBytes);
    
    if(RxQueueCnt > 0)
    {
        // saving received bytes from rx queue
        for(UBaseType_t i = 0; i < RxQueueCnt; i++)
            xQueueReceive(IP702RxBytes, &SrcAnswer[i], (TickType_t) 5);
    
        // 'OK'- the succeed answer          
        if(SrcAnswer[0] == 'O' && SrcAnswer[1] == 'K' ) 
         return 1;
    }
    
    else return 0;  

}

// заряд/разряд накопительных конденсаторов
unsigned int IP702_SetState(unsigned int state)
{ 
    // cmd sending sequence
    vTaskSuspendAll(); // приостановка диспетчера на момент отправки посылки
    IP702_TX_EN;
    Uart2SendByte(begin_CMD);        // #
    Uart2SendByte(cmd_lenght1);      // cmd lenght
    Uart2SendByte((state == 1) ? chargeON_CMD : chargeOFF_CMD);
    Uart2SendByte(SrcAddr);          // source address
    Uart2SendByte((state == 1) ? 0x09 : 0x0A); // CRC
    IP702_TX_DIS;
    xTaskResumeAll(); // возобновление работы диспетчера
    
    //CRC 0x09 MSB of => begin_CMD + cmd_lenght1 + chargeON_CMD + SrcAddr
    
    vTaskDelay(5); // readout timeout ~ 2 ms
    
    // get src answer rx bytes count 
    RxQueueCnt = uxQueueMessagesWaiting(IP702RxBytes);
    
    if(RxQueueCnt > 0)
    {
         // saving received bytes from rx queue
        for(UBaseType_t i = 0; i < RxQueueCnt; i++)
            xQueueReceive(IP702RxBytes, &SrcAnswer[i], (TickType_t) 5);
    
        // 'OK'- the succeed answer          
        if(SrcAnswer[0] == 'O' && SrcAnswer[1] == 'K' ) 
         return 1;
    }
    
    else return 0; 
}

// IP704 commands
/*=========================================================================== */

