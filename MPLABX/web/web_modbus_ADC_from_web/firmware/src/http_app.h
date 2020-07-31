/* 
 * File:   http_app.h
 * Author: ADM
 *
 * Created on 16 апреля 2020 г., 12:20
 */

#ifndef HTTP_APP_H
#define	HTTP_APP_H

#ifdef	__cplusplus
extern "C"
{
#endif
	
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "system_config.h"
#include "system_definitions.h"


	// *****************************************************************************
// *****************************************************************************
// Section: Type Definitions
// *****************************************************************************
// *****************************************************************************
#if defined (__PIC32C__) || defined(__SAMA5D2__)        
/* This section is highly customizable based on application's specific needs. */
#define APP_SWITCH_1StateGet()      SWITCH_Get()
#define APP_SWITCH_2StateGet()      SWITCH_Get()
#define APP_SWITCH_3StateGet()      SWITCH_Get()
#elif defined (__PIC32MZ__)    
/* This section is highly customizable based on application's specific needs. */
#define APP_SWITCH_1StateGet()      SWITCH1_Get()
#define APP_SWITCH_2StateGet()      SWITCH2_Get()
#define APP_SWITCH_3StateGet()      SWITCH2_Get()
#endif

#define APP_LED_1StateSet()         LED1_Set()
#define APP_LED_1StateGet()         LED1_Get()
#define APP_LED_1StateClear()       LED1_Clear()
#define APP_LED_1StateToggle()      LED1_Toggle()

#if defined(__PIC32MZ__)
#define APP_LED_2StateSet()         LED2_Set()
#define APP_LED_2StateGet()         LED2_Get()
#define APP_LED_2StateClear()       LED2_Clear()
#define APP_LED_2StateToggle()      LED2_Toggle()

#define APP_LED_3StateSet()         LED3_Set()
#define APP_LED_3StateGet()         LED3_Get()
#define APP_LED_3StateClear()       LED3_Clear()
#define APP_LED_3StateToggle()      LED3_Toggle()
#endif

// Application SYS_FS mount points
// Adjust as needed
#define APP_SYS_FS_NVM_VOL          "/dev/nvma1"
#define APP_SYS_FS_MOUNT_POINT      "/mnt/mchpSite1"
#define APP_SYS_FS_TYPE             MPFS2
#define APP_SYS_FS_TYPE_STRING      "MPFS2"

// *****************************************************************************
/* Application states

  Summary:
    Application states enumeration

  Description:
    This enumeration defines the valid application states.  These states
    determine the behavior of the application at various times.
*/

typedef enum
{
    /* Application's state machine's initial state. */
    APP_STATE_INIT=0,
    APP_STATE_SERVICE_TASKS,
    /* TODO: Define states used by the application state machine. */
            /* The app mounts the disk */
    APP_MOUNT_DISK = 0,

    /* In this state, the application waits for the initialization of the TCP/IP stack
     * to complete. */
    APP_TCPIP_WAIT_INIT,

    /* In this state, the application can do TCP/IP transactions.. */
    APP_TCPIP_TRANSACT,

    /* The application waits in this state for the driver to be ready
       before sending the "hello world" message. */
    //APP_STATE_WAIT_FOR_READY,

    /* The application waits in this state for the driver to finish
       sending the message. */
    //APP_STATE_WAIT_FOR_DONE,

    /* The application does nothing in the idle state. */
    //APP_STATE_IDLE
    //
    APP_USERIO_LED_DEASSERTED,

    APP_USERIO_LED_ASSERTED,

    APP_TCPIP_ERROR,

} APP_STATES;

typedef enum
{
    APP_TCPIP_WAIT_FOR_COMMAND,

    APP_TCPIP_GET_COMMAND,

    APP_TCPIP_PROCESS_COMMAND,
}APP_COMMAND_STATES;
// *****************************************************************************
/* LED State

  Summary:
    Enumerates the supported LED states.

  Description:
    This enumeration defines the supported LED states.

  Remarks:
    None.
*/
typedef enum
{
    /* LED State is on */
    APP_LED_STATE_OFF = 0,
   /* LED State is off */
    APP_LED_STATE_ON = 1,
} APP_LED_STATE;

// *****************************************************************************
/* Application Data

  Summary:
    Holds application data

  Description:
    This structure holds the application's data.

  Remarks:
    Application strings and buffers are be defined outside this structure.
 */

typedef struct
{
    /* The application's current state */
    APP_STATES state;
    APP_COMMAND_STATES appCmdState;
/* TODO: Define any additional data used by the application. */
    /* SYS_FS File handle */
    SYS_FS_HANDLE           fileHandle;
} APP_DATA;

// *****************************************************************************
// *****************************************************************************
// Section: extern declarations
// *****************************************************************************
// *****************************************************************************
extern const uint8_t NVM_MEDIA_DATA[];

void HTTP_APP_Initialize( void );
void HTTP_APP_Tasks ( void );


#ifdef	__cplusplus
}
#endif

#endif	/* HTTP_APP_H */

