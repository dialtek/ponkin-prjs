// TODO
// 1. асинхр. движение до 4 моторами
// 2. плавный пуск
// 3. логика обработки концевиков
// 4. сохр. параметров в ПЗУ
// 5. алгоритм смены ID
// 6. нормальная регистровая карта
// 7. обработка сигналов Fault контроллера сервоприводов ?  
// 8. определение минимальных значений сигналов управления

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

#define motor_EN  LATBbits.LATB13 = 0   // en the motor
#define motor_DIS LATBbits.LATB13 = 1   // dis the motor

#define motor_DIR LATBbits.LATB14       // the motor rotation direction
#define motor_PUL LATBbits.LATB15

unsigned int motor_step_qty   = 10;     // необх.число шагов
unsigned int motor_step_period  = 100;  // период шагов
unsigned int motor_busy  = 0;           // статус-бит передвижения привода
unsigned int motor_start = 0;           // бит запуска привода
unsigned int motor_dir   = 0;           // направление движения

unsigned int motor_step_cnt = 0;
unsigned int motor_step_temp = 0;
unsigned long ramp_val= 0;
unsigned int k = 10;

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

void Timer2_init()
{
   T2CONbits.TON = 0;           // Timer on/off bit; 0 - Disable Timer
   T2CONbits.TCS = 0;           // Timer Clock Source Select bit; 0 - Internal clock (FOSC/2)
   T2CONbits.TGATE = 0;         // Disable Gated Timer mode
   T2CONbits.TCKPS = 0b01;      //  // Prescaler = (00=1, 01=8, 10=64, 11=256) 
   TMR2 = 0x00;                 // Clear timer register
   PR2 = 31;                    // default setup      
   
   //interrupt timer settings
   //IPC1bits.T2IP = 6; // Set Timer1 interrupt priority to 3 
   IFS0bits.T2IF = 0; // Reset Timer1 interrupt flag      
   IEC0bits.T2IE = 1; // Enable Timer1 interrupt
}

void Timer2_set(unsigned int us_mult)
{
  PR2 = us_mult;       
}
  
void T8_delay_tmr_init()
{
    T8CONbits.TON = 0;      // Disable Timer
    T8CONbits.TCS = 0;      // Select internal instruction cycle clock 
    T8CONbits.TGATE = 0;    // Disable Gated Timer mode
    T8CONbits.TCKPS = 0b00; // Select 1:1 Prescaler
    TMR8 = 0x00;            // Clear timer register
    PR8 = 300;              // Load the period value
    
    IEC3bits.T8IE = 0;      // Disable T8 interrupt
}

void xdelay_us(unsigned int delay)
{
   for(unsigned int i = 0; i < delay; i++)
   {
         T8CONbits.TON = 1; // Start Timer  
         while(!IFS3bits.T8IF) {   }
         T8CONbits.TON = 0; // Stop Timer  
         IFS3bits.T8IF = 0; // claer int flag
   }

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
 
    motor_PUL = ~motor_PUL;
    unsigned int kx = (motor_step_qty/motor_step_period) * k;
    
    motor_step_cnt++;
//    ramp_val = (20*(unsigned long)motor_step_qty)/100;
//    
//    if(motor_step_cnt < ramp_val)
//         PR2 = motor_step_period*20 -motor_step_cnt*kx;
   
//    else if(motor_step_cnt >= (motor_step_qty-(unsigned int)ramp_val))
//         PR2 = motor_step_period + (motor_step_qty - *kx;
    
    //else PR2 = motor_step_period;
    
    if(motor_step_cnt >= motor_step_qty)
    {
        motor_DIS;
        T2CONbits.TON = 0; // stop the Timer 
        motor_PUL = 0;      
        motor_busy = 0;
    }
    
    if(PR2 < 100) PR2 = 100;
    
    IFS0bits.T2IF = 0;     // Clear Timer interrupt flag
 } 

/*=========================================================================== */

void GPIO_init()
{
    // PORT B
    TRISBbits.TRISB12 = 0;  // IO 1 - 
    TRISBbits.TRISB13 = 0;  // IO 2 - EN
    TRISBbits.TRISB14 = 0;  // IO 3 - DIR
    TRISBbits.TRISB15 = 0;  // IO 4 - PUL
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
    //uart2
    TRISFbits.TRISF4 = 0;
    LATFbits.LATF4 = 0;
    TRISFbits.TRISF5 = 1;

    TRISFbits.TRISF6 = 0;
    //PORT F

} 


int main(void) {
    
 OSC_init();
 GPIO_init();
 UART1_init();
 T8_delay_tmr_init();
 Timer2_init();         // motor step
 
 modbus_init();
 motor_PUL = 0;
 motor_DIS;
 
 while(1)
 {
  modbus_rx_sm();
  modbus_poll();
  __delay_ms(1);  

  if(motor_start)
  {    
    motor_busy = 1;
    Timer2_set(motor_step_period);
    motor_step_cnt = 0;
    motor_EN;
    motor_DIR = motor_dir;
    T2CONbits.TON = 1;           // start Timer 
    motor_start = 0;   
  } 
  
  holding_register[8] = (unsigned int)ramp_val;
 }
    
}
