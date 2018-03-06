/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

#if defined(__XC)
    #include <xc.h>         /* XC8 General Include File */
#elif defined(HI_TECH_C)
    #include <htc.h>        /* HiTech General Include File */
#elif defined(__18CXX)
    #include <p18cxxx.h>    /* C18 General Include File */
#endif

#if defined(__XC) || defined(HI_TECH_C)

#include <stdint.h>         /* For uint8_t definition */
#include <stdbool.h>        /* For true/false definition */

#endif

#include "user.h"
#include "hd44780.h"

/******************************************************************************/
/* User Functions                                                             */
/******************************************************************************/

#define ESSID_NAME "My_Network_Name"
#define ESSID_PASS "My_Network_Password"

void InitApp() {
    /* Setup analog functionality and port direction */
    PORTB = 0x00;
    LATB = 0x00;
    TRISB = 0x00;

    /* Initialize peripherals */

    // Hardware EUSART
    baudUSART(
            BAUD_IDLE_CLK_LOW &
            BAUD_IDLE_RX_PIN_STATE_HIGH &
            BAUD_16_BIT_RATE &
            BAUD_WAKEUP_OFF &
            BAUD_AUTO_OFF);
    OpenUSART(
            USART_TX_INT_OFF &
            USART_RX_INT_ON &
            USART_ASYNCH_MODE &
            USART_EIGHT_BIT &
            USART_CONT_RX &
            USART_ADDEN_OFF &
            USART_BRGH_HIGH,
            //34); // baud rate: 57 600 @ 8 MHz
            207); // baud rate: 9 600 @ 8 MHz

    /* Configure the IPEN bit (1=on) in RCON to turn on/off int priorities */

    /* Enable interrupts */
    RCONbits.IPEN = 1;                  // Enable interrupt priorities
    INTCON = _INTCON_GIEH_MASK;         // Only enable High-priority peripheral interrupts
    INTCON3 = 0x00;                     // Disable INT* interrupts

    IPR1bits.RCIP = 1;                  // EUSART receive interrupt is High-priority

    /* Initialize LCD */
    lcd_initialize();
    lcd_flags_set(DISPLAY_CONTROL, CURSOR_ON | BLINKING_ON, 1);
    lcd_goto(1,1);
    lcd_write("ESP8266 libv0.1 demo");
    lcd_goto(2,1);
    lcd_write("(C) 2015 Camil Staps");

    /* Initialize the ESP8266 */
    initESP();
}

void initESP(void) {
    debug_line("Restarting ESP...");
    esp8266_restart();
    esp8266_echoCmds(true);
    esp8266_mode(ESP8266_STATION);
    debug_line("Connecting to AP...");
    unsigned char connect = esp8266_connect((unsigned char *) ESSID_NAME, (unsigned char *) ESSID_PASS);
    if (connect == ESP8266_FAIL) {
        debug_line("Failed to connect");
    } else {
        debug_line("Getting IP...");
        unsigned char ip[4];
        esp8266_ip(ip);
        unsigned char ip_string[15];
        sprintf(ip_string, "%u.%u.%u.%u", ip[0], ip[1], ip[2], ip[3]);
        debug_line(ip_string);
    }
}

void putch(unsigned char byte) {
    lcd_data(byte);
}

unsigned char getch() {
    while (eusart_rx_buffer_rd == eusart_rx_buffer_wr);
    char received = eusart_rx_buffer[eusart_rx_buffer_rd++];
    if (eusart_rx_buffer_rd >= EUSART_BUFFER_SIZE)
        eusart_rx_buffer_rd = 0;
    return received;
}

void debug_line(unsigned char * string) {
    lcd_goto(3,1);
    lcd_write("                    ");
    lcd_goto(3,1);
    lcd_write(string);
}

void restoreEUSARTBuffer(unsigned char x) {
    eusart_rx_buffer[--eusart_rx_buffer_rd] = x;
    if (eusart_rx_buffer_rd == -1)
        eusart_rx_buffer_rd = EUSART_BUFFER_SIZE - 1;
}

//#define _esp8266_getch getch
//#define _esp8266_putch putch

void _esp8266_putch(unsigned char byte) {
    while (BusyUSART());
    WriteUSART(byte);
}
unsigned char _esp8266_getch(void) {
    return getch();
}

void esp_request() {
    lcd_goto(4,1);
    lcd_write("                    ");
    if (!esp8266_start(ESP8266_TCP, "camilstaps.nl", 80)) {
        debug_line("Couldn't open socket");
    } else {
        debug_line("Connected to server");
        if (!esp8266_send("GET / HTTP/1.0\r\nHost: esp.camilstaps.nl\r\n\r\n")) {
            debug_line("Failed HTTP request");
        } else {
            debug_line("Sent HTTP request");
            unsigned char response[21];
            esp8266_receive(response, 20, true);
            debug_line("Received response:");
            lcd_goto(4,1);
            lcd_write(response);
        }
    }
}
