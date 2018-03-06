/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

#if defined(__XC)
    #include <xc.h>        /* XC8 General Include File */
#elif defined(HI_TECH_C)
    #include <htc.h>       /* HiTech General Include File */
#elif defined(__18CXX)
    #include <p18cxxx.h>   /* C18 General Include File */
#endif

#if defined(__XC) || defined(HI_TECH_C)

#include <stdint.h>         // For other data type definitions
#include <stdbool.h>        // For true/false definition
#include <stdio.h>          // For printf

#endif

#include "system.h"         // System funct/params, like osc/peripheral config
#include "user.h"
#include "hd44780.h"
#include "esp8266.h"

/******************************************************************************/
/* Main Program                                                               */
/******************************************************************************/

void main(void)
{
    unsigned char delay;

    // Configure the oscillator for the device
    ConfigureOscillator();

    // Initialize I/O and Peripherals for application
    InitApp();

    /*LATBbits.LATB4 = 1;
    debug_line("Power-up delay");
    Delay10KTCYx(200);
    LATBbits.LATB4 = 0;*/

    esp_request();

    while (1);

}

