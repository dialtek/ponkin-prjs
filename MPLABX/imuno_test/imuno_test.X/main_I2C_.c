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

#define EEprom_addr 0xA0 // AT24C128 I2C addres
unsigned char crc_buf_wr[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
unsigned char crc_buf_rd[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
unsigned char crc_wr_index = 0;
unsigned char crc_rd_index = 0;
/*--------------------------------------------------------------------------- */
// 1-wire
#include "one_wire.h"   // подключение библиотеки 1-wire 

/*--------------------------------------------------------------------------- */
 
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
    TRISFbits.TRISF4 = 0;
    TRISFbits.TRISF5 = 0;
    
    LATFbits.LATF4 = 1;   //Start with bus in idle mode - both lines high 
    LATFbits.LATF5 = 1;
    
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
// I2C master 
void I2C_init(unsigned int FCLOCK)
{
    I2C2BRG = ((FCY / FCLOCK / 1000)-(FCY  / 10000000 + (FCY % 2 >= 5 ? 1 : 0))) - 1;
    if (I2C2BRG <= 2) I2C2BRG = 3; // значение в регистре не может быть меньше 2       

    I2C2CONbits.I2CSIDL = 1;    // Continues the module operation in the Idle mode
    I2C2CONbits.SCLREL = 1;     // Releases the SCLx clock
    I2C2CONbits.A10M = 0;       // 0 - 7-bit slave address, 1 - 10 bit
    I2C2CONbits.RCEN = 0;       // Enables Receive mode for I2C          
    I2C2CONbits.I2CEN = 1;      // Enables the I2Cx module and configures the 
                                // SDAx and SCLx pins as serial port pins  
}

void I2C_stop()
{   
    unsigned char cnt = 0;

    while (I2C2STATbits.TRSTAT)        // ожидание окончания активности
    {
        __delay_us(1); 
        cnt++;
        if(cnt > 9) break;
    }
    
    cnt = 0;
    
    I2C2CONbits.PEN = 1;                // формировать бит стоп
    while (I2C2CONbits.PEN)            // ожидание окончания формирования бита стоп
    {
        __delay_us(1); 
        cnt++;
        if(cnt > 9) break;
    }
}

// формирования начала START для записи
void I2C_start()
{
    unsigned char cnt = 0;
    // загрузка адреса устройства с формированием битов управления
    while (I2C2STATbits.TRSTAT) // ожидание окончания активности
    {
        __delay_us(1); 
        cnt++;
        if(cnt > 9) break;
    }
    
    cnt = 0;
    
    I2C2CONbits.SEN = 1;
    while (I2C2CONbits.SEN)
    {
        __delay_us(1); 
        cnt++;
        if(cnt > 9) break;
    }
    
//    cnt = 0;
//    I2C2TRN = addr;
//    while (I2C2STATbits.TBF)       // ожидание окончания передачи
//    {
//        __delay_us(1); 
//        cnt++;
//        if(cnt > 9) break;
//    }
//    
//    while (I2C2STATbits.TRSTAT)        // ожидание окончания активности
//    {
//        __delay_us(1); 
//        cnt++;
//        if(cnt > 9) break;
//    }
//
//    if (I2C2STATbits.ACKSTAT == 0) return 1; // адрес принят
//    else return 0;                           // ошибка
}


void I2C_Rstart()
{
        // загрузка адреса устройства с формирование битов управления
    while (I2C2STATbits.TRSTAT); // ожидание окончания активности

    I2C2CONbits.SEN = 1;
    while (I2C2CONbits.SEN);
    
    if (I2C2STATbits.ACKSTAT == 0) return 0; // адрес принят
    else {
        return 1;                   // формирование стоп, ошибка
    }


}

// формирования записи байта в устройство
unsigned char I2C_write(unsigned char data) 
{
    while (I2C2STATbits.TRSTAT);    // ожидание окончания активности
    I2C2TRN = data;
    while (I2C2STATbits.TBF);       // ожидание окончания передачи
    
    if (I2C2STATbits.ACKSTAT == 0) 
    {
        return 0; // байта принят
    
    }
    else {
        //i2c_stop();                 //формировать бит стоп
        return 1;                   // формирование стоп, ошибка
    }
    
    
//    unsigned char cnt = 0;
//    
//    while (I2C2STATbits.TRSTAT)    // ожидание окончания активности
//    {
//        __delay_us(1); 
//        cnt++;
//        if(cnt > 9) break;
//    }
//    
//    cnt = 0;
//    
//    I2C2TRN = data;
//    while (I2C2STATbits.TBF)       // ожидание окончания передачи
//    {
//        __delay_us(1); 
//        cnt++;
//        if(cnt > 9) break;
//    }
//    
//    if (I2C2STATbits.ACKSTAT == 0) return 1; // байт принят
//    else  return 0;
}

unsigned char I2C_read_ack(void)
{
    unsigned char cnt = 0;
    unsigned char rd_byte = 0;
    
    while (I2C2STATbits.TRSTAT);    // ожидание окончания активности

    I2C2CONbits.RCEN = 1;           //начать прием данных
    Nop();
    //	while (I2C2CONbits.RCEN);
    //	while (I2C2STATbits.TRSTAT);// ожидание окончания активности
    while (!I2C2STATbits.RBF);      // ожидание загрузки буфера приема

    I2C2CONbits.ACKDT = 0;          //установить бит подтвеждения приема
    I2C2CONbits.ACKEN = 1;          //начать формировать бит
    while (I2C2CONbits.ACKEN);      //ожидать окончания формирования

    return I2C2RCV;                 //чтение буфера
    
    
    
    
//    I2C2CONbits.ACKDT = 0;          //установить бит не-подтвеждения приема;
//    
////    while (I2C2STATbits.TRSTAT)    // ожидание окончания активности
////    {
////        __delay_us(1); 
////        cnt++;
////        if(cnt > 9) break;
////    }
//    //I2C2CONbits.ACKDT = 0;          //установить бит не-подтвеждения приема;
//   // I2C2CONbits.ACKEN = 0;          //начать формировать бит
//    while (I2C2CON & 0x1F);         //wait for idle condition
//    
//    I2C2CONbits.RCEN = 1;           //начать прием данных
//    //rd_byte = I2C2RCV;
//
//    cnt = 0;
//    while (!I2C2STATbits.RBF)      // ожидание загрузки буфера приема
//    {
//        __delay_us(1); 
//        cnt++;
//        if(cnt > 30) break;
//    }
//    cnt = 0;
//    
//    I2C2CONbits.ACKEN = 1;	
//    while(I2C2CONbits.ACKEN)
//    {
//        __delay_us(1); 
//        cnt++;
//        if(cnt > 30) break;
//    }
//    
//
//   
//    rd_byte = I2C2RCV;
//    
//
//    
//    cnt = 0;
//    
////    while (I2C2CONbits.ACKEN)      //ожидать окончания формирования
////    {
////        __delay_us(1); 
////        cnt++;
////        if(cnt > 9) break;
////    }

    //return rd_byte;                 //чтение буфера
}

unsigned char I2C_read_noack(void)  // формирования чтения байта из устройства с не_подтверждением приема
{

    while (I2C2STATbits.TRSTAT);    // ожидание окончания активности

    I2C2CONbits.RCEN = 1;           //начать прием данных
    Nop();
    //	while (I2C2CONbits.RCEN);
    //	while (I2C2STATbits.TRSTAT);
    while (!I2C2STATbits.RBF);      // ожидание загрузки буфера приема

    I2C2CONbits.ACKDT = 1;          //установить бит не-подтвеждения приема
    I2C2CONbits.ACKEN = 1;          //начать формировать бит
    while (I2C2CONbits.ACKEN);      //ожидать окончания формирования
    I2C2CONbits.ACKDT = 0;          //Set for NotACk

    return I2C2RCV;                 //чтение буфера

}//

/*=========================================================================== */
// I2C EEprom 
 unsigned short ROM_CRC16 (unsigned char * data_p, unsigned char length)
 {
    // расчет контрольной суммы
    // взят из интернета
    
    unsigned char x;
    unsigned short crc = 0xFFFF;

    while (length--)
    {
       x = crc >> 8 ^ * data_p++;
       x ^= x>>4;
       crc = (crc << 8) ^ ((unsigned short) (x << 12)) ^ 
              ((unsigned short) (x <<5)) ^  ( (unsigned short) x) ;
    }

    return crc;
 }

 void ROM_wr_byte (unsigned short addr, unsigned char dataByte)
 {
    /// записывает байт данных по 16 - бит. адресу
    
    unsigned char addr_MSB = 0;
    unsigned char addr_LSB = 0;
    
    addr_MSB = (addr >> 8);
    addr_LSB = addr;
    
    I2C_start();
    I2C_write (EEprom_addr|0);
    // A read operation is initiated if this bit is high
    // and a write operation is initiated if this bit is low.
    
    
    __delay_us(20);
    I2C_write (addr_MSB);
    __delay_us(20);
    I2C_write (addr_LSB);
    __delay_us(20);
    I2C_write (dataByte);
    __delay_us(20);
    I2C_stop ();
    __delay_ms (12); // t записи в rom - 10 мс
//    crc_buf_wr[crc_wr_index] = dataByte;
//    crc_wr_index++;
 }

  unsigned char ROM_rd_byte (unsigned short addr)
 {
    /// чтение байта данных по 16 - бит. адресу
    
    unsigned char rd_data_byte = 0;
    unsigned char addr_MSB = 0; // старший байт адреса
    unsigned char addr_LSB = 0; // младший байт адреса
    
    addr_MSB = (addr >> 8); // заполнение ст. байта из 2 - байт. адреса
    addr_LSB = addr; // заполнение мл. байта из 2 - байт. адреса
    
    I2C_start();
    I2C_write (EEprom_addr|0);
    __delay_us(20);
    // A read operation is initiated if this bit is high
    // and a write operation is initiated if this bit is low.
    
    I2C_write (addr_MSB); // выдача на линию ст. байта адреса
    __delay_us(20);
    I2C_write (addr_LSB); // выдача на линию мл. байта адреса
    __delay_us(20);
    I2C_Rstart();
    I2C_write (EEprom_addr|1);
    __delay_us(20);
     for(unsigned char i =0; i < 64; i++)
     {
        rd_data_byte = I2C_read_ack();
     }

    I2C_stop ();
    
//    crc_buf_rd[crc_rd_index] = rd_data_byte;
//    crc_rd_index++;
    
    return rd_data_byte;
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

// for(unsigned char i = 0; i < ID_lenght; i++)// заполнение двумерного массива ID датчиков
//{
// Sens_N_ID[0][i] = Sens1_ID[i];
// Sens_N_ID[1][i] = Sens2_ID[i];
//}
 
 OSC_init();
 GPIO_init();
 UART1_init();
 
 modbus_init();
 Timer2_init();
 
 
 TRISBbits.TRISB13 = 0;  // IO 2 - EN
 
 I2C_init(100);
 
 //T2CONbits.TON = 1;  
  //ROM_wr_byte(0x0000,0x82);  

//   for(unsigned char i =0; i < 64; i++)
//  {
//      ROM_wr_byte(i,i); 
//  }
 
 while(1)
 {
  // if()
  // {
     //  LATBbits.LATB12 = 1;
  // }
     
//  for(unsigned char i =0; i < 64; i++)
//  {
//      ROM_wr_byte(i,i); 
//  }
  
  __delay_ms(100);
  ROM_rd_byte(0);
//  __delay_ms(50);

//   modbus_rx_sm();
//   modbus_poll();
  
     

     
 }  
}
