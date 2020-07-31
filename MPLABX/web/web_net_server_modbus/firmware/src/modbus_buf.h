#ifndef _MODBUS_BUF_H    /* Guard against multiple inclusion */
#define _MODBUS_BUF_H

#define MODBUS_RX_BUF_LENGTH 8
#define MODBUS_TX_BUF_LENGTH 256

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

#endif /* _MODBUS_BUF_H */

/* *****************************************************************************
 End of File
 */
