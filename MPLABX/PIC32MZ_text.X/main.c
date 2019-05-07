//===================================================================================================================================//
#include <xc.h>
#include "fuses.h"

#define LED_TRIS      TRISHbits.TRISH2    // macro for direction register bit of the LED pin
#define LED_LAT       LATHbits.LATH2      // macro for output register bit of the LED pin
#define LED_TRIS15    TRISHbits.TRISH15   // macro for direction register bit of the LED pin
#define LED_LAT15     LATHbits.LATH15     // macro for output register bit of the LED pin
#define _ISR_PSV __attribute__((__interrupt__, __auto_psv__))
#define FPB 100000000
#define Desired_Baud_Rate 115200
#define U1BRG1 ((FPB/Desired_Baud_Rate)/4) - 1 // = 650.042
int var = 0;
//==================================================================================================================================//
T8_delay_tmr_init()
{
    T8CONbits.ON = 0;                                  // ?????? ????????
    T8CONbits.TCS = 0;                                 // ????? ????????? ???????????? ??????? - ?????????? ????????
    T8CONbits.T32 = 0;                                 // ????? 32-??????? ??????? - ????????
    IPC9bits.T8IP = 1;                                 // 
    IPC9bits.T8IS = 1;   
    T8CONbits.TGATE = 0;
    T8CONbits.TCKPS = 0;                               // ???????? ??????? ??????? - 1:4
    TMR8 = 0x0000;                                     // ??????? ???????? ???????
    PR8 = 87;                                          // ?????? ???????, ?????????? ????? - 16 ??? TCKPS = 2 - 1 us
    IFS1bits.T8IF = 0;                                 // 
    IEC1bits.T8IE = 0;                                 // Disabled T8 interrupt
   // T8CONbits.ON = 1;
}
//===================================================================================================================================//
static void PIC32MZ_CPU_Init(void)
{
    /* Unlock */
    SYSKEY = 0x00000000;
    SYSKEY = 0xAA996655;
    SYSKEY = 0x556699AA;

    /* PBCLK8: EBI */
    while (PB8DIVbits.PBDIVRDY == 0); //
    PB8DIVbits.PBDIV = 1;
    PB8DIVbits.ON = 1;

    /* PBCLK7: CPU, Deadman Timer */
    while (PB7DIVbits.PBDIVRDY == 0);
    PB7DIVbits.PBDIV = 0;
    PB7DIVbits.ON = 1;

    /* PBCLK5: Flash, Crypto, RNG, USB, CAN, Ethernet, SQI */
    while (PB5DIVbits.PBDIVRDY == 0);
    PB5DIVbits.PBDIV = 1;
    PB5DIVbits.ON = 1;

    /* PBCLK4: Ports */
    while (PB4DIVbits.PBDIVRDY == 0);
    PB4DIVbits.PBDIV = 9;
    PB4DIVbits.ON = 1;

    /* PBCLK3: ADC, Comparator, Timers, Output Compare, Input Capture */
    while (PB3DIVbits.PBDIVRDY == 0);
    PB3DIVbits.PBDIV = 1;
    PB3DIVbits.ON = 1;

    /* PBCLK2: PMP, I2C, UART, SPI */
    while (PB2DIVbits.PBDIVRDY == 0);
    PB2DIVbits.PBDIV = 1;
    PB2DIVbits.ON = 1;

    /* PBCLK1: Always ON */
    while (PB1DIVbits.PBDIVRDY == 0);
    PB1DIVbits.PBDIV = 9;

    /* Configue Reference Clock Outputs */
    REFO1CON = 0;
    REFO2CON = 0;
    REFO3CON = 0;
    REFO4CON = 0;

    RPA14Rbits.RPA14R = 0x5;    /* RPA14 is used by SDO1 */
    SDI1Rbits.SDI1R = 0x2;      /* SDI1 is set to RPF4 */

    /* Lock */
    SYSKEY = 0x33333333;

    /* Configure SRS Priority Selection */
    PRISSbits.SS0 = 0;
    PRISSbits.PRI1SS = 1;
    PRISSbits.PRI2SS = 2;
    PRISSbits.PRI3SS = 3;
    PRISSbits.PRI4SS = 4;
    PRISSbits.PRI5SS = 5;
    PRISSbits.PRI6SS = 6;
    PRISSbits.PRI7SS = 7;

    /* Enable multi vector mode */
    INTCONbits.MVEC = 1;
}
//==================================================================================================================================//

void delay_us(unsigned long delay)
{
   for(unsigned long i = 0; i < delay; i++)
   {
        T8CONbits.ON = 1; // Start Timer  
        while(!IFS1bits.T8IF) {   }
        IFS1bits.T8IF = 0;                     // claer int flag
        T8CONbits.ON = 0;                      // Stop Timer  
   }
}
//===================================================================================================================================//
void delay_ms(unsigned long ms)
{
    delay_us(ms * 1000UL);
}
//==================================================================================================================================//
void UART1_init()
{
    IPC28bits.U1RXIP = 7;
    IFS3bits.U1RXIF = 0;                // Reset UART RX interrupt flag
    IFS3bits.U1TXIF = 0;
    IEC3bits.U1RXIE = 1;                // Enable UART1 RX interrupt
    
    CFGCONbits.IOLOCK = 0; 
    U1RXRbits.U1RXR = 0b0010; 
    RPF5Rbits.RPF5R = 0b0001; 
    CFGCONbits.IOLOCK = 1;
    
    U1BRG = U1BRG1;
    U1MODEbits.UARTEN = 1;                                      
    U1MODEbits.UEN = 0;                                         // U1TX and U1RX are enabled and used
    U1MODEbits.PDSEL = 0;                                       // No parity, 8 bit data;
    U1MODEbits.ABAUD = 0;                                       // Baud rate measurment disabled or completed;
    U1MODEbits.BRGH = 1;                                        // High-speed mode - 4x baud clock enabled;
    U1MODEbits.STSEL = 0;                                       // 1 stop bit
    U1MODEbits.ON = 1;
    
    U1STAbits.URXISEL0 = 0;
    U1STAbits.URXISEL1 = 0;
    U1STAbits.UTXINV  = 0;
    U1STAbits.UTXEN = 1;
    U1STAbits.URXEN = 1;
    U1STAbits.URXISEL = 0;
}
//===================================================================================================================================//
void __attribute__((vector(_UART1_RX_VECTOR), interrupt(IPL7SRS), nomips16)) UART1RxISR(void)
{
    //U1RXREG
    IFS3bits.U1RXIF = 0;                            //Clear UART1 RX interrupt
}
//===================================================================================================================================//
void uart_send_hex(unsigned char byte)
{
    U1TXREG = byte;
    while(U1STAbits.TRMT == 0) { }
}
//==================================================================================================================================//
int main()
{
    PIC32MZ_CPU_Init();
    UART1_init();
    LED_TRIS = 0;   // LED set as output
    LED_TRIS15 = 0;
    T8_delay_tmr_init();

    asm volatile("ei");
   
    while (1)
    {
       LATHbits.LATH2 = 1;
       delay_ms(100);
       LATHbits.LATH2 = 0;
       delay_ms(100);
    }
}
//=================================================================================================================================//