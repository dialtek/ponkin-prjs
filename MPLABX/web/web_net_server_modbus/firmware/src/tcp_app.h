#ifndef _TCP_TASKS_H    /* Guard against multiple inclusion */
#define _TCP_TASKS_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include "configuration.h"
#include "definitions.h" 
#include "tcpip/tcpip.h"
#include "modbus_buf.h"

#define SERVER_PORT 4001
typedef enum
{
    /* In this state, the application waits for the initialization of the TCP/IP stack
     * to complete. */
    APP_TCPIP_WAIT_INIT,

    /* In this state, the application waits for a IP Address */
    APP_TCPIP_WAIT_FOR_IP,

    APP_TCPIP_OPENING_SERVER,

    APP_TCPIP_WAIT_FOR_CONNECTION,

    APP_TCPIP_SERVING_CONNECTION,

    APP_TCPIP_CLOSING_CONNECTION,

    APP_TCPIP_ERROR,
} TCP_APP_STATES;
typedef struct
{
    /* The application's current state */
    TCP_APP_STATES state;

    TCP_SOCKET              socket;

} TCP_APP_DATA;

void tcp_app_set_alternative_ip (IPV4_ADDR IP, IPV4_ADDR mask, IPV4_ADDR gateway);

bool tcp_app_use_alternative_ip (void);

bool tcp_app_use_default_ip (void);

IPV4_ADDR tcp_app_get_alternative_ip (void);
IPV4_ADDR tcp_app_get_alternative_ip_mask (void);
IPV4_ADDR tcp_app_get_alternative_ip_gateway (void);

IPV4_ADDR tcp_app_get_default_ip (void);
IPV4_ADDR tcp_app_get_default_ip_mask (void);
IPV4_ADDR tcp_app_get_default_ip_gateway (void);

void TCP_APP_Initialize ( void );

#endif /* _EXAMPLE_FILE_NAME_H */

