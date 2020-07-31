#ifndef _APP_H
#define _APP_H

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include "modbus_app.h"
#include "http_app.h"
#include "d_eeprom.h"
#include "PIC32MZ_UART.h"

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility

extern "C" {

#endif

#define RX_LED_POS 14

void APP_Initialize ( void );
void APP_Tasks( void );

void ADC_SPS_Set(int New_ADC_SPS);
int ADC_SPS_Get(void);
#endif /* _APP_H */

//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

/*******************************************************************************
 End of File
 */

