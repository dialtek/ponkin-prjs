/******************************************************************************/
/*Files to Include                                                            */
/******************************************************************************/

#if defined(__XC)
    #include <xc.h>         /* XC8 General Include File */
#elif defined(HI_TECH_C)
    #include <htc.h>        /* HiTech General Include File */
#elif defined(__18CXX)
    #include <p18cxxx.h>    /* C18 General Include File */
#endif

#include "system.h"

/* Refer to the device datasheet for information about available
oscillator configurations. */
void ConfigureOscillator(void)
{
    // INTSRC = from INTOSC; PLL enabled; center frequency
    OSCTUNE = 0b11000000;
    // IDLEN = enter sleep; 8MHz INTOSC; use INTOSC
    OSCCON = 0b01111111;
}
