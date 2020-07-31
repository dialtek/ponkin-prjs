#include "modbus_buf.h"

unsigned char modbus_rx_buf[MODBUS_RX_BUF_LENGTH];
unsigned char modbus_tx_buf[MODBUS_TX_BUF_LENGTH];

volatile int modbus_rx_buf_ptr = 0;
volatile int modbus_tx_buf_ptr = 0;

volatile unsigned char modbus_rx_flag;
volatile unsigned char modbus_tx_flag;

void modbus_buf_init()
{
    modbus_rx_buf_ptr = -1;
    modbus_tx_buf_ptr = -1;
    
    modbus_rx_flag = 1;
    modbus_tx_flag = 1;
}

int modbus_rx_buf_add(unsigned char new_byte)
{
    if (modbus_rx_buf_ptr >= MODBUS_RX_BUF_LENGTH)
    {
        return 1;
    } else
    if (modbus_rx_buf_ptr < 0)
    {
        modbus_rx_buf_ptr = 0;
    }
    else
    {
        modbus_rx_buf_ptr++;
    }
    modbus_rx_buf[modbus_rx_buf_ptr] = new_byte;
    return 0;
}

int modbus_tx_buf_add(unsigned char new_byte)
{
    if (modbus_tx_buf_ptr >= MODBUS_TX_BUF_LENGTH)
    {
        return 1;
    } else
    if (modbus_tx_buf_ptr < 0)
    {
        modbus_tx_buf_ptr = 0;
    }
    else
    {
        modbus_tx_buf_ptr++;
    }
    modbus_tx_buf[modbus_tx_buf_ptr] = new_byte;
    return 0;
}

void modbus_rx_buf_clear()
{
    modbus_rx_buf_ptr = -1;
}

void modbus_tx_buf_clear()
{
    modbus_tx_buf_ptr = -1;
}


/* *****************************************************************************
 End of File
 */
