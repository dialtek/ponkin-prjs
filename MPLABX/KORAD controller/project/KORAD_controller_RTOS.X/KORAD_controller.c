#include <p24HJ256GP206.h>

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "main.h"
#include "d_eeprom.h"
#include "dialtek_modbus.h"

/*=========================================================================== */
// extern

//extern volatile QueueHandle_t modbus_el_q; 

//extern SemaphoreHandle_t NewSensSemph; // new sensor adding semph

/*=========================================================================== */
// IP704 controller USER functions 
void GPIO_init(void)
{
    // PORT B
    TRISBbits.TRISB14 = 0; // 4w to MOXA TX_EN
    TRISBbits.TRISB0 = 0;  // Master_485_LED
    TRISBbits.TRISB1 = 0;  // Slave_485_LED
    TRISBbits.TRISB3 = 1;  // BTN_RESET
    TRISBbits.TRISB4 = 0;  // LED_RS485_RX
    
    //PORT C
    TRISCbits.TRISC2 = 0;  // SPI1_CS1    EEPROM CS
    
    //PORT F
    TRISFbits.TRISF2 = 1;   // uart1_RxD
    LATFbits.LATF2   = 0;   // uart1_RxD
    TRISFbits.TRISF3 = 0;   // uart1_TxD
    LATFbits.LATF3   = 0;   // uart1_TxD
    TRISFbits.TRISF4 = 1;   // uart2_RX
    LATFbits.LATF4   = 0;   // uart2_RX          
    TRISFbits.TRISF5 = 0;   // uart2_Tx
    LATFbits.LATF5   = 0;   // uart2_Tx

    //PORT G
    TRISGbits.TRISG6 = 0;   // SPI2_SCLK 
    TRISGbits.TRISG7 = 1;   // SPI2_SDI
    TRISGbits.TRISG8 = 0;   // SPI2_SDO
    TRISGbits.TRISG9 = 0;   // IP702 TX EN
    
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
    Uart2Init();
}

void RestoreCfg(void)
{
    unsigned int buf = 0;

    input_reg_read(2, &buf); 
    
    if((buf < 254) && (buf != 0))
        set_modbus_id((unsigned char)buf);
}

// IP704 controller
/*=========================================================================== */

