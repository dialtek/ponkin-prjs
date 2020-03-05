//===================================================================================================================================//
#include <xc.h>
#include "fuses.h"
                                          // PIC32MZ2048EFH144-I/PH
#define LED_TRIS      TRISKbits.TRISK4    // macro for direction register bit of the LED pin
#define LED           LATKbits.LATK4      // macro for output register bit of the LED pin

#define _ISR_PSV __attribute__((__interrupt__, __auto_psv__))
#define FPB 100000000 // 100 M
#define Desired_Baud_Rate 115200
#define U2BRG1 ((FPB/Desired_Baud_Rate)/4) - 1 // = 650.042
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
void PIC32MZ_CPU_Init(void)
{
    /* Unlock */
    SYSKEY = 0x00000000;
    SYSKEY = 0xAA996655;
    SYSKEY = 0x556699AA;

    /* PBCLK8: EBI */
    while (PB8DIVbits.PBDIVRDY == 0); // 0000001 = PBCLKx is SYSCLK divided by 2 !!!
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
    PB4DIVbits.PBDIV = 1;
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
    PB1DIVbits.PBDIV = 1;

    /* Configue Reference Clock Outputs */
    REFO1CON = 0;
    REFO2CON = 0;
    REFO3CON = 0;
    REFO4CON = 0;
 
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
void UART2_init()
{
    //IPC36bits.U2RXIP = 7;
    IFS4bits.U2RXIF = 0;                // Reset UART RX interrupt flag
    
    IFS4bits.U2TXIF = 0;
    IEC4bits.U2RXIE = 0;                // Enable UART2 RX interrupt
    
    CFGCONbits.IOLOCK = 0;   
    // rpd4 rpd5 - diagnostic uart
    TRISDbits.TRISD4 = 1;
    RPD5Rbits.RPD5R = 0x2;      /* U2 TX is set to RPD5 */
    
    TRISDbits.TRISD5 = 0;
    U2RXRbits.U2RXR = 0x4;      /* U2 RX is set to RPD4 */
    CFGCONbits.IOLOCK = 1;
    
    U2BRG = U2BRG1;
    U2MODEbits.UARTEN = 1;                                      
    U2MODEbits.UEN = 0;                                         // U2TX and U2RX are enabled and used
    U2MODEbits.PDSEL = 0;                                       // No parity, 8 bit data;
    U2MODEbits.ABAUD = 0;                                       // Baud rate measurment disabled or completed;
    U2MODEbits.BRGH = 1;                                        // High-speed mode - 4x baud clock enabled;
    U2MODEbits.STSEL = 0;                                       // 1 stop bit
    U2MODEbits.ON = 1;
    
    U2STAbits.URXISEL0 = 0;
    U2STAbits.URXISEL1 = 0;
    U2STAbits.UTXINV  = 0;
    U2STAbits.UTXEN = 1;
    U2STAbits.URXEN = 1;
    U2STAbits.URXISEL = 0;
}
//===================================================================================================================================//
void __attribute__((vector(_UART1_RX_VECTOR), interrupt(IPL7SRS), nomips16)) UART1RxISR(void)
{
    //U1RXREG
    IFS3bits.U1RXIF = 0;                            //Clear UART1 RX interrupt
}
//===================================================================================================================================//
void uart2_send_byte(unsigned char byte)
{
    U2TXREG = byte;
    while(U2STAbits.TRMT == 0) { }
}
//==================================================================================================================================//
int main()
{
    PIC32MZ_CPU_Init();
    UART2_init();
    LED_TRIS = 0;   // LED set as output
    T8_delay_tmr_init();

    //asm volatile("ei"); // enable int global
   
    LED = 1;
    
    while (1)
    {
       LED = 1;
       delay_ms(50);
       LED = 0;
       delay_ms(50);
       uart2_send_byte(0x42);
    }
}
//=================================================================================================================================//