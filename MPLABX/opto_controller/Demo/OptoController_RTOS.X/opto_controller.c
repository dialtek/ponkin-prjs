#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "main.h"
#include "d_eeprom.h"
#include "dialtek_modbus.h"
#include "dialtek_one_wire.h"

/*=========================================================================== */
// extern

extern volatile QueueHandle_t modbus_el_q; 
extern volatile QueueHandle_t sensor_qty_q; 
extern volatile QueueHandle_t sensor[MaxSensQty]; 

extern SemaphoreHandle_t NewSensSemph; // new sensor adding semph

/*=========================================================================== */
// opto controller USER functions 
void GPIO_init(void)
{
        // PORT B
    TRISBbits.TRISB0 = 1;  // IN_4_MK
    TRISBbits.TRISB1 = 1;  // IN_3_MK
    TRISBbits.TRISB2 = 1;  // IN_2_MK
    TRISBbits.TRISB3 = 1;  // IN_1_MK
    TRISBbits.TRISB4 = 1;  // BTN_RESET
    TRISBbits.TRISB5 = 0;  // LED_OUT_1
    TRISBbits.TRISB8 = 1;  //IN_5_MK
    TRISBbits.TRISB9 = 1;  //IN_6_MK
    TRISBbits.TRISB10 = 1;  //IN_7_MK
    TRISBbits.TRISB11 = 1;  //IN_8_MK
    TRISBbits.TRISB14 = 1;  //IN_9_MK
    TRISBbits.TRISB15 = 1;  //IN_10_MK
    
    //PORT C
    TRISCbits.TRISC1 = 0;  // LED_OUT_2
    TRISCbits.TRISC2 = 0;  // SPI1_CS1    EEPROM CS
   
    //PORT D
    TRISDbits.TRISD1 = 0;  //MK_OUT_1
    TRISDbits.TRISD2 = 0;  //MK_OUT_2
    TRISDbits.TRISD3 = 0;  //MK_OUT_3
    TRISDbits.TRISD4 = 0;  //MK_OUT_4
    TRISDbits.TRISD5 = 1;  //1Wire_MK_In
    TRISDbits.TRISD6 = 0;  //1Wire_MK_Out
    TRISDbits.TRISD7 = 0;  //TX_EN
    
    //PORT F
    TRISFbits.TRISF4 = 1;   // IN_11_MK
    TRISFbits.TRISF5 = 1;   // IN_12_MK

    //PORT G
    TRISGbits.TRISG0 = 0;   // LED_TX_485
    TRISGbits.TRISG6 = 0;   // SPI2_SCLK 
    TRISGbits.TRISG7 = 1;   // SPI2_SDI
    TRISGbits.TRISG8 = 0;   // SPI2_SDO
    TRISGbits.TRISG12= 0;   // LED_1Wire
    TRISGbits.TRISG13= 0;   // LED_OUT_4
    TRISGbits.TRISG14= 0;   // LED_RX_485
    TRISGbits.TRISG15= 0;   // LED_OUT_3
    
    AD1PCFGL = 0xffff; // Port pin in Digital mode, port read input enabled, 
    AD1PCFGH = 0xffff; 
    
// basic ver    
//    // PORT B
//    TRISBbits.TRISB0 = 0;  // LED_1WIRE
//    TRISBbits.TRISB1 = 0;  // LED_UART_TX
//    TRISBbits.TRISB2 = 0;  // LED_RS485_TX
//    TRISBbits.TRISB3 = 0;  // LED_UART_RX
//    TRISBbits.TRISB4 = 0;  // LED_RS485_RX
//    TRISBbits.TRISB5 = 1;  // BTN_RESET
//    
//    //PORT C
//    TRISCbits.TRISC2 = 0;  // SPI1_CS1    EEPROM CS
//   
//    //PORT D
//    TRISDbits.TRISD7 = 0;    //TX_EN
//    TRISDbits.TRISD8 = 1;   //IN_1_MK
//    LATDbits.LATD8   = 0; 
//    TRISDbits.TRISD9 = 1;   //IN_2_MK
//    LATDbits.LATD9   = 0; 
//    TRISDbits.TRISD10 = 1;  //IN_3_MK
//    LATDbits.LATD10   = 0; 
//    TRISDbits.TRISD11 = 1;  //IN_4_MK
//    LATDbits.LATD11   = 0; 
//    
//    //PORT F
//    TRISFbits.TRISF0 = 0;   //Relay_1
//    LATFbits.LATF0   = 0;       
//    TRISFbits.TRISF1 = 0;   //Relay_2
//    LATFbits.LATF1   = 0;   //
//    TRISFbits.TRISF2 = 1;   // uart1_RxD
//    LATFbits.LATF2   = 0;   // uart1_RxD
//    TRISFbits.TRISF3 = 0;   // uart1_TxD
//    LATFbits.LATF3   = 0;   // uart1_TxD
//    TRISFbits.TRISF4 = 1;   //opto_RX
//    LATFbits.LATF4   = 0;   //opto_RX          
//    TRISFbits.TRISF5 = 0;   //opto_Tx
//    LATFbits.LATF5   = 1;   //opto_Tx
//
//    //PORT G
//    TRISGbits.TRISG0 = 0;   //Relay_4
//    LATGbits.LATG0   = 0; 
//    TRISGbits.TRISG1 = 0;   //Relay_3
//    LATGbits.LATG1   = 0;
//    TRISGbits.TRISG6 = 0;   // SPI2_SCLK 
//    TRISGbits.TRISG7 = 1;   // SPI2_SDI
//    TRISGbits.TRISG8 = 0;   // SPI2_SDO
//    
//    TRISGbits.TRISG12= 0;   //1WIRE_MK_OUT
//    TRISGbits.TRISG14= 1;   //1WIRE_MK_IN
//    
//    AD1PCFGL = 0xffff; // Port pin in Digital mode, port read input enabled, 
//    AD1PCFGH = 0xffff; 
    
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
        holding_reg_write(i,0);
    }
    
    // clear eeprom
    eeprom_wr_regs(HOLD_REGS);
    eeprom_wr_regs(HOLD_REGS);
    eeprom_wr_regs(INPUT_REGS);
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

// opto controller
/*=========================================================================== */

