#include "xc.h"
#include "fuses.h"
#include <p24HJ128GP506.h>
#define FCY 40000000UL
#include <libpic30.h>
#include <stdio.h>
#include <stdint.h>
#define _ISR_PSV __attribute__((__interrupt__, __auto_psv__))

#define FP 40000000
#define U1_BAUDRATE 115200
#define U1BRGVAL ((FP/U1_BAUDRATE)/16)-1

#include "dialtek_modbus.h"

 
void OSC_init()
{
    // FCY=FOSC/2, FOSC= FIN*M/(N1*N2) 
    CLKDIVbits.PLLPRE = 0;      // 0 - divider N1 = 2
    PLLFBD = 30;                // multiplier M = PLLFBD + 2
    CLKDIVbits.PLLPOST = 0;     // 0 - divider N2 = 2

    OSCTUN=0;                   // 000000 = Center frequency (7.37 MHz nominal)
    RCONbits.SWDTEN=0;          // Disable Watch Dog Timer

    while(OSCCONbits.LOCK !=1) {};   // 1 = Indicates that PLL is in lock, or PLL start-up timer is satisfied
                                    // 0 = Indicates that PLL is out of lock, start-up timer is in progress or PLL is disabled
    //note: FOSC= 10 MHz * 32/(2*2) = 80 MHz, FCY = 80/2
}   

void GPIO_init()
{
    // PORT B
    TRISBbits.TRISB12 = 0; // IO 1
    TRISBbits.TRISB2 = 0;  // OW TX
    TRISBbits.TRISB3 = 1;  // OW RX
    //PORT C
    TRISCbits.TRISC1 = 0; // OUT2
    TRISCbits.TRISC2 = 0; // OUT3
    //PORT D
    TRISDbits.TRISD1 = 0; 
    //PORT F
    TRISFbits.TRISF0 = 0;
    LATFbits.LATF0 = 0;
    TRISFbits.TRISF1 = 0;
    LATFbits.LATF1 = 0;
    
    TRISFbits.TRISF2 = 1;
    TRISFbits.TRISF3 = 1;
    // I2C 2
//    TRISFbits.TRISF4 = 0;
//    TRISFbits.TRISF5 = 0;
//    
//    LATFbits.LATF4 = 1;   //Start with bus in idle mode - both lines high 
//    LATFbits.LATF5 = 1;
//    
    //ODCFbits.ODCF4 = 1;   //Open drain mode 
    //ODCFbits.ODCF5 = 1; 

    TRISFbits.TRISF6 = 0;
    //PORT F
    
    // обязательно отключить режим АЦП при работе с digital io
    AD1PCFGL = 0xffff;
    AD1PCFGH = 0xffff;
    


} 

void Timer2_init()
{
   T2CONbits.TON = 0;           // Timer on/off bit; 0 - Disable Timer
   T2CONbits.TCS = 0;           // Timer Clock Source Select bit; 0 - Internal clock (FOSC/2)
   T2CONbits.TGATE = 0;         // Disable Gated Timer mode
   T2CONbits.TCKPS = 0b11;      //  // Prescaler = (00=1, 01=8, 10=64, 11=256) 
   TMR2 = 0x00;                 // Clear timer register
   PR2 = 50000;                    // default setup      
   
   //interrupt timer settings
   //IPC1bits.T2IP = 6; // Set Timer1 interrupt priority to 3 
   IFS0bits.T2IF = 0; // Reset Timer1 interrupt flag      
   IEC0bits.T2IE = 1; // Enable Timer1 interrupt
}

void Timer2_set(unsigned int us_mult)
{
  PR2 = us_mult;       
}
/*=========================================================================== */
// UART 
void UART1_init()
{   /// modbus 
    // RX interrupt UART1 settings 
    IPC2bits.U1RXIP = 7; // Set UART1 RX interrupt priority to 1 
    IFS0bits.U1RXIF = 0; // Reset UART1 RX interrupt flag
    IEC0bits.U1RXIE = 1; // Enable UART1 RX interrupt
    
    U1BRG = U1BRGVAL;      // Baud Rate setting for 115200 uart
    U1MODEbits.UARTEN = 1;  // 1 = UARTx is enabled; all UARTx pins are controlled by UARTx as defined by UEN <1:0>
    U1MODEbits.UEN = 0;     // 0 = UxTX and UxRX pins are enabled and used; UxCTS and UxRTS/BCLK pins controlled by port latches
    U1MODEbits.PDSEL = 0;   // 0 = No Parity, 8-Data bits
    U1MODEbits.ABAUD = 0;   // 0 = Baud rate measurement disabled or completed
    U1MODEbits.BRGH = 0;    // 1 = BRG generates 4 clocks per bit period (4x baud clock, High-Speed mode)
    U1MODEbits.STSEL = 0;   // 0 = 1-Stop bit

    U1STAbits.UTXISEL0 = 0; // Interrupt when a unsigned character is transferred to the Transmit Shift Register (this implies there isat least one unsigned character open in the transmit buffer
    U1STAbits.UTXISEL1 = 0;
    U1STAbits.UTXINV = 0;
    U1STAbits.UTXEN = 1;    // 1 = Transmit enabled, UxTX pin controlled by UARTx
    U1STAbits.URXISEL = 0;  // 0x = Interrupt is set when any unsigned character is received and transferred from the UxRSR to the receive buffer. Receive buffer has one or more unsigned characters.
                         // The URXISEL<1:0> (UxSTA<7:6>) control bits determine when the UART receiver generates an interrupt.
  
 //Once enabled, the UxTX and UxRX pins are configured as an output and an
 //input, respectively, overriding the TRIS and PORT register bit settings for the corresponding I/O port pins. 
}

void uart_send_hex (unsigned char Ch)
{ 
    U1TXREG = Ch;
    while(U1STAbits.TRMT == 0){ }
    __delay_us(50);
    // waiting for trancsaction to be complete  
}

/*=========================================================================== */
// interrupts
void _ISR_PSV _U1RXInterrupt(void)      //interupt UART 1 RX
{ /// получение 1 байта по UART1
        
    modbus_uart_byte(U1RXREG);
    IFS0bits.U1RXIF = 0;   //Clear  UART1_Rx interrupt   
}

void _ISR_PSV _T2Interrupt(void)        //interupt Timer 2
{    
     

    
//        //get 8 ROM bytes
//     if (OneWire_reset())
//     {
//       OneWire_send(Read_ROM);
//       for (uint8_t p = 0; p < 8; p++) {
//        input_register[p] = (unsigned int) OneWire_read(); /// сохранение ID датчика в переменную
//        }
//     }
  

    
    
   IFS0bits.T2IF = 0;     // Clear Timer interrupt flag
 } 

/*=========================================================================== */

int main(void) {
 
 OSC_init();
 GPIO_init();
 UART1_init();
 
 modbus_init();
 Timer2_init();
 
 
 TRISBbits.TRISB13 = 0;  // IO 2 - EN
 
 //T2CONbits.TON = 1;  
 
 while(1)
 {
   modbus_rx_sm();
   modbus_poll();
   __delay_ms(1);
     
 }  
}
