#ifndef _MODBUS_BUF_H    /* Guard against multiple inclusion */
#define _MODBUS_BUF_H

#define MODBUS_RX_BUF_LENGTH 32 // !!!
#define MODBUS_TX_BUF_LENGTH 256 // !!!

extern unsigned char modbus_rx_buf[MODBUS_RX_BUF_LENGTH];
extern unsigned char modbus_tx_buf[MODBUS_TX_BUF_LENGTH];

extern volatile int modbus_rx_buf_ptr;
extern volatile int modbus_tx_buf_ptr;

extern volatile unsigned char modbus_rx_flag;
extern volatile unsigned char modbus_tx_flag;

//TODO: Inline error: multiple deaclaration

void modbus_buf_init();

int modbus_rx_buf_add(unsigned char new_byte);

int modbus_tx_buf_add(unsigned char new_byte);

void modbus_rx_buf_clear();

void modbus_tx_buf_clear();

// ---------------TCP-IP Part--------------
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include "configuration.h"
#include "definitions.h" 
#include "tcpip/tcpip.h"

#define SERVER_PORT 4001

typedef enum
{
    /* In this state, the application waits for the initialization of the TCP/IP stack
     * to complete. */
    MODBUS_BUF_TCPIP_WAIT_INIT,

    /* In this state, the application waits for a IP Address */
    MODBUS_BUF_TCPIP_WAIT_FOR_IP,

    MODBUS_BUF_TCPIP_OPENING_SERVER,

    MODBUS_BUF_TCPIP_WAIT_FOR_CONNECTION,

    MODBUS_BUF_TCPIP_SERVING_CONNECTION,

    MODBUS_BUF_TCPIP_CLOSING_CONNECTION,

    MODBUS_BUF_TCPIP_ERROR,
} MODBUS_BUF_TCPIP_STATES;


typedef struct
{
    /* The application's current state */
    MODBUS_BUF_TCPIP_STATES state;

    TCP_SOCKET              socket;

} MODBUS_BUF_TCP_APP_DATA;



void modbus_buf_tcp_set_alternative_ip (IPV4_ADDR IP, IPV4_ADDR mask, IPV4_ADDR gateway);

bool modbus_buf_tcp_use_alternative_ip (void);

bool modbus_buf_tcp_use_default_ip (void);

IPV4_ADDR modbus_buf_tcp_get_alternative_ip (void);
IPV4_ADDR modbus_buf_tcp_get_alternative_ip_mask (void);
IPV4_ADDR modbus_buf_tcp_get_alternative_ip_gateway (void);

IPV4_ADDR modbus_buf_tcp_get_default_ip (void);
IPV4_ADDR modbus_buf_tcp_get_default_ip_mask (void);
IPV4_ADDR modbus_buf_tcp_get_default_ip_gateway (void);

void MODBUS_BUF_TCP_Initialize ( void );

void MODBUS_BUF_TCP_Tasks (void);

#endif /* _MODBUS_BUF_H */
