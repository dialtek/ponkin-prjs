/******************************************************************************/
/* User Level #define Macros                                                  */
/******************************************************************************/

#include <stdint.h>
#include <stdio.h>
#include <usart.h>
#include "esp8266.h"

/******************************************************************************/
/* Global variables                                                           */
/******************************************************************************/

#define EUSART_BUFFER_SIZE 2048
char eusart_rx_buffer[EUSART_BUFFER_SIZE];
uint16_t eusart_rx_buffer_rd = 0;
uint16_t eusart_rx_buffer_wr = 0;

/******************************************************************************/
/* User Function Prototypes                                                   */
/******************************************************************************/

void InitApp(void);                         // I/O and Peripheral Initialization
void initESP(void);
void putch(unsigned char);                  // stdout
unsigned char getch(void);                  // stdin
void restoreEUSARTBuffer(unsigned char);    // put a char back in the buffer
void debug_line(unsigned char *);           // Output a line for debugging
void esp_request(void);