#include "xc.h"
#include "fuses.h"
#include "main.h"
#include "d_delay.h"
#include "dialtek_modbus.h"  
#include "d_SPI.h"

//////////////////////////////////////////////////////////////////////////////// 

// device firmvare selector

#define DEV_MODE_HEATER     0            // ImunoFirmware.ImunoHeater
#define DEV_MODE_LINE_MV    0            // ImunoFirmware.ImunoLineMv
#define DEV_MODE_DOSING_SYS 1            // ImunoFirmware.DosingSys
#define DEV_MODE_IO         0            // ImunoFirmware.IO

//////////////////////////////////////////////////////////////////////////////// 
   
ImunoDevice  ImunoFirmware;              // imuno firmvare struct instance
FirmwareInfo FirmInfo;                   // device info struct instance

extern void main_stepper( void );        // imuno line movement firmvare
extern void main_heater( void );         // imuno OW + heater firmvare
extern void main_dosing_sys( void );     // imuno hamilton pump, dosing sys
extern void main_io( void );             // imuno IO

/*================================ SYSTEM =================================== */
// MCU init
static void OSC_init(void)               // oscillator init
{
    // FRCDIV FRC/1; PLLPRE 2; DOZE 1:8; PLLPOST 1:2; DOZEN disabled; ROI disabled; 
    CLKDIV = 0x3000;
    // TUN Center frequency; 
    OSCTUN = 0x0;
    // ROON disabled; ROSEL disabled; RODIV Base clock value; ROSSLP disabled; 
    REFOCON = 0x0;
    // PLLDIV 46; 
    PLLFBD = 0x2E;
    // RND disabled; SATB disabled; SATA disabled; ACCSAT disabled; 
	CORCONbits.RND = 0;
	CORCONbits.SATB = 0;
	CORCONbits.SATA = 0;
	CORCONbits.ACCSAT = 0;
    // CF no clock failure; NOSC PRIPLL; LPOSCEN disabled; CLKLOCK unlocked; OSWEN Switch is Complete; IOLOCK not-active; 
    __builtin_write_OSCCONH((unsigned char) ((0x300 >> _OSCCON_NOSC_POSITION) & 0x00FF));
    __builtin_write_OSCCONL((unsigned char) ((0x300 | _OSCCON_OSWEN_MASK) & 0xFF));
    // Wait for Clock switch to occur
    while (OSCCONbits.OSWEN != 0);
    
    // Fosc = 120M, Fcy = 60M
}

static void GPIO_init(void)              // MCU IO init
{
    /*
    The ANSELx register has a default value of 0xFFFF;
    therefore, all pins that share analog functions are
    analog (not digital) by default.
     */       
   	
   ANSELA = 0x0000;
   ANSELB = 0x0000;
   ANSELC = 0x0000;
   ANSELD = 0x0000;
   ANSELE = 0x0000;
   ANSELG = 0x0000;
   
   // IO inputs 
   TRISA = 0x0000ffff;      // PORTA - IO 8 inputs
   CNPDA = 0x0000ffff;      // waek pull down on inputs
   
   TRISBbits.TRISB4 = 1;    // input
   TRISBbits.TRISB5 = 1;    // input
   CNPDBbits.CNPDB4 = 1;    // waek pull down 
   CNPDBbits.CNPDB5 = 1;    // waek pull down
      
   TRISBbits.TRISB8 = 1;    // input
   TRISBbits.TRISB8 = 1;    // input
   CNPDBbits.CNPDB8 = 1;    // waek pull down 
   CNPDBbits.CNPDB9 = 1;    // waek pull down 
   
   // IO outputs 
   TRISEbits.TRISE0 = 0;    // IO_O1
   TRISEbits.TRISE1 = 0;    // IO_O2
   TRISEbits.TRISE2 = 0;    // IO_O3
   TRISEbits.TRISE3 = 0;    // IO_O4
   TRISEbits.TRISE4 = 0;    // IO_O5
   TRISEbits.TRISE5 = 0;    // IO_O6
   TRISEbits.TRISE6 = 0;    // IO_O7
   TRISEbits.TRISE7 = 0;    // IO_O8
   TRISFbits.TRISF1 = 0;    // IO_O9
   TRISFbits.TRISF2 = 0;    // IO_O10
   TRISFbits.TRISF3 = 0;    // IO_O11
   TRISFbits.TRISF4 = 0;    // IO_O12
   
   //MOXA ctrl
   TRISBbits.TRISB0 = 0;    // MOXA RESET pin
   TRISEbits.TRISE8 = 0;    // Modbus TX EN
   
   //ICSP
   TRISBbits.TRISB6 = 0;    // PGC
   TRISBbits.TRISB7 = 0;    // PGD
   
   //LEDS
   TRISCbits.TRISC1 = 0;    // LED 1, MODBUS
   TRISCbits.TRISC2 = 0;    // LED 2, MODBUS
   TRISCbits.TRISC3 = 0;    // LED 3
   TRISCbits.TRISC4 = 0;    // LED 4, power led
   
   //OW
   TRISGbits.TRISG0 = 1;    // one wire RX
   TRISGbits.TRISG1 = 0;    // one wire TX
   TRISGbits.TRISG6 = 0;    // heater ctrl
   
   //SCK1
   TRISGbits.TRISG14 = 0;   // SPI1 SCK, R126
   TRISGbits.TRISG13 = 0;   // SPI1 SDO, RP125
   TRISGbits.TRISG12 = 1;   // SPI1 SDI, RPI124
   TRISGbits.TRISG15 = 0;   // SPI1 nCS, digital IO
   
   //SCK3
   TRISDbits.TRISD6 = 0;    // SPI3 SCK, RP70
   TRISDbits.TRISD7 = 0;    // SPI3 SDO, RP71
   TRISDbits.TRISD8 = 0;    // SPI3 nCS, RD8
   TRISDbits.TRISD9 = 1;    // SPI3 SDI, RPI73
   
   //U1
   TRISEbits.TRISE9 = 1;    // U1RX - RPI89
   TRISFbits.TRISF0 = 0;    // U1TX - RP96
   
   //U2
   TRISBbits.TRISB12 = 1;   // U2RX,  Hamilton Pump
   TRISFbits.TRISF12 = 0;   // U2TX, RP108, Hamilton Pumpp
   TRISFbits.TRISF13 = 0;   // U2/RS-485 TX EN

   // RPn RPi setup
   __builtin_write_OSCCONL(OSCCON & ~(1<<6)); // Разблокировать настройку выводов RPX
   // UART1 peripheral pin select
   RPOR7bits.RP96R = 1;     // RF0 as U1TX
   RPINR18bits.U1RXR = 89;  // 001 1100 I RPI96, table 11-2 in big datasheet
   
   // Hamilton PUMP, UART2 peripheral pin select
   RPOR11bits.RP108R = 3;   // RF12 - U2TX, RP108
   RPINR19bits.U2RXR = 44;  // RB12 - U2RX, RPI44
   
   // SPI1 peripheral pin select
   RPINR20bits.SDI1R = 124;       // RPI124
   
   RPOR15bits.RP126R = 0b000110;  // SCK1 - 0b000110 RPn tied to SPI1 Clock Output
   RPINR20bits.SCK1R = 126;       // SCK1 - IN setup
   
   RPOR14bits.RP125R = 0b000101;  // SDO1 - 000101 RPn tied to SPI1 SDO 
   
   // SPI3 peripheral pin select
   RPINR29bits.SDI3R = 73;   // RPI73
   RPOR3bits.RP70R   = 0x20; // SCK3 - 100000 RPn tied to SPI3 Clock Output
   RPINR29bits.SCK3R = 70;   // SCK3 - in setup
   RPOR3bits.RP71R = 0x1F;   // SDO3 - 011111 RPn tied to SPI3 Slave Output 

   __builtin_write_OSCCONL(OSCCON | (1<<6));  // Заблокировать настройку выводов RPX
}

static void System_Init(void)            // MCU systems init
{
   OSC_init();          // oscillator is common for all dev modes
   GPIO_init();         // MCU port init
   TIMER8_delay_init(); // delay timer 
               
   POWER_LED = ON;      // turn on LEDs
   MOXA_active = ON;
   
   TX_DIS;              // release RS485 bus
   CS3_HIGH;            // release SPI bus
   CS2_HIGH;

   SPI1_init();         // Analog board CPLD communication
   SPI3_init();         // serial EEPROM 

   // define imuno firmware codes
   ImunoFirmware.Heater = 10;
   ImunoFirmware.LineMv = 11;
   ImunoFirmware.DosingSys = 12;
   ImunoFirmware.IO  = 13;
   ImunoFirmware.Vibro  = 14;
}

/*=========================================================================== */ 
// main MAIN
int main(void) 
{
   System_Init();                   // device init 

   #if DEV_MODE_HEATER  == 1
	main_heater();                  // ImunoFirmware.ImunoLineMv    = 10
   #endif
   //======================
   #if DEV_MODE_LINE_MV == 1
	main_stepper();                 // ImunoFirmware.ImunoHeater    = 11
   #endif
   //======================
   #if DEV_MODE_DOSING_SYS == 1
	main_dosing_sys();              // ImunoFirmware.ImunoDosingSys = 12
   #endif
   //======================
   #if DEV_MODE_IO == 1
	main_io();                      // ImunoFirmware.IO  = 14
   #endif
}
/*=========================================================================== */ 