
/**
  TMR8 Generated Driver API Source File 

  @Company
    Microchip Technology Inc.

  @File Name
    tmr8.c

  @Summary
    This is the generated source file for the TMR8 driver using PIC24 / dsPIC33 / PIC32MM MCUs

  @Description
    This source file provides APIs for driver for TMR8. 
    Generation Information : 
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - 1.75
        Device            :  dsPIC33EP512GM710
    The generated drivers are tested against the following:
        Compiler          :  XC16 v1.35
        MPLAB             :  MPLAB X v5.05
*/

/*
    (c) 2016 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
*/

/**
  Section: Included Files
*/

#include <xc.h>
#include "tmr8.h"

/**
  Section: Data Type Definitions
*/

/** TMR Driver Hardware Instance Object

  @Summary
    Defines the object required for the maintainence of the hardware instance.

  @Description
    This defines the object required for the maintainence of the hardware
    instance. This object exists once per hardware instance of the peripheral.

  Remarks:
    None.
*/

typedef struct _TMR_OBJ_STRUCT
{
    /* Timer Elapsed */
    bool                                                    timerElapsed;
    /*Software Counter value*/
    uint8_t                                                 count;

} TMR_OBJ;

static TMR_OBJ tmr8_obj;

/**
  Section: Driver Interface
*/

void TMR8_Initialize (void)
{
    //TMR8 0; 
    TMR8 = 0x00;
    //Period = 0.000001 s; Frequency = 60000000 Hz; PR8 60; 
    PR8 = 0x3C;
    //TCKPS 1:1; T32 16 Bit; TON enabled; TSIDL disabled; TCS FOSC/2; TGATE disabled; 
    T8CON = 0x8000;

    
    IFS3bits.T8IF = false;
    IEC3bits.T8IE = true;
	
    tmr8_obj.timerElapsed = false;

}



void __attribute__ ( ( interrupt, no_auto_psv ) ) _T8Interrupt (  )
{
    /* Check if the Timer Interrupt/Status is set */

    //***User Area Begin

    // ticker function call;
    // ticker is 1 -> Callback function gets called everytime this ISR executes
    TMR8_CallBack();

    //***User Area End

    tmr8_obj.count++;
    tmr8_obj.timerElapsed = true;
    IFS3bits.T8IF = false;
}


void TMR8_Period16BitSet( uint16_t value )
{
    /* Update the counter values */
    PR8 = value;
    /* Reset the status information */
    tmr8_obj.timerElapsed = false;
}

uint16_t TMR8_Period16BitGet( void )
{
    return( PR8 );
}

void TMR8_Counter16BitSet ( uint16_t value )
{
    /* Update the counter values */
    TMR8 = value;
    /* Reset the status information */
    tmr8_obj.timerElapsed = false;
}

uint16_t TMR8_Counter16BitGet( void )
{
    return( TMR8 );
}


void __attribute__ ((weak)) TMR8_CallBack(void)
{
    // Add your custom callback code here
}

void TMR8_Start( void )
{
    /* Reset the status information */
    tmr8_obj.timerElapsed = false;
    

    /*Enable the interrupt*/
    IEC3bits.T8IE = true;

    /* Start the Timer */
    T8CONbits.TON = 1;
}

void TMR8_Stop( void )
{
    /* Stop the Timer */
    T8CONbits.TON = false;

    /*Disable the interrupt*/
    IEC3bits.T8IE = false;
}

bool TMR8_GetElapsedThenClear(void)
{
    bool status;
    
    status = tmr8_obj.timerElapsed;

    if(status == true)
    {
        tmr8_obj.timerElapsed = false;
    }
    return status;
}

int TMR8_SoftwareCounterGet(void)
{
    return tmr8_obj.count;
}

void TMR8_SoftwareCounterClear(void)
{
    tmr8_obj.count = 0; 
}

/**
 End of File
*/
