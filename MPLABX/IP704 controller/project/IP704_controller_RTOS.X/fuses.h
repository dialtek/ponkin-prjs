
// PIC24HJ128GP506 Configuration Bit Settings

// 'C' source line config statements

#include <p24Hxxxx.h>

 int FBS __attribute__((space(prog), address(0xF80000))) = 0xCF ;
//_FBS(
//    BWRP_WRPROTECT_OFF & // Boot Segment Write Protect (Boot Segment may be written)
//    BSS_NO_FLASH &       // Boot Segment Program Flash Code Protection (No Boot program Flash segment)
//    RBS_NO_RAM           // Boot Segment RAM Protection (No Boot RAM)
//);
 int FSS __attribute__((space(prog), address(0xF80002))) = 0xCF ;
//_FSS(
//    SWRP_WRPROTECT_OFF & // Secure Segment Program Write Protect (Secure segment may be written)
//    SSS_NO_FLASH &       // Secure Segment Program Flash Code Protection (No Secure Segment)
//    RSS_NO_RAM           // Secure Segment Data RAM Protection (No Secure RAM)
//);
 int FGS __attribute__((space(prog), address(0xF80004))) = 0x7 ;
//_FGS(
//    GWRP_OFF &           // General Code Segment Write Protect (User program memory is not write-protected)
//    GSS_OFF              // General Segment Code Protection (User program memory is not code-protected)
//);
 int FOSCSEL __attribute__((space(prog), address(0xF80006))) = 0xA3 ;
//_FOSCSEL(
//    FNOSC_PRIPLL &       // Oscillator Mode (Primary Oscillator (XT, HS, EC) w/ PLL)
//    IESO_ON              // Two-speed Oscillator Start-Up Enable (Start up with FRC, then switch)
//);
 int FOSC __attribute__((space(prog), address(0xF80008))) = 0xC6 ;
//_FOSC(
//    POSCMD_HS &          // Primary Oscillator Source (HS Oscillator Mode)
//    OSCIOFNC_OFF &       // OSC2 Pin Function (OSC2 pin has clock out function)
//    FCKSM_CSDCMD         // Clock Switching and Monitor (Both Clock Switching and Fail-Safe Clock Monitor are disabled)
//);
 int FWDT __attribute__((space(prog), address(0xF8000A))) = 0x5F ;
//_FWDT(
//    WDTPOST_PS32768 &    // Watchdog Timer Postscaler (1:32,768)
//    WDTPRE_PR128 &       // WDT Prescaler (1:128)
//    WINDIS_OFF &         // Watchdog Timer Window (Watchdog Timer in Non-Window mode)
//    FWDTEN_OFF           // Watchdog Timer Enable (Watchdog timer enabled/disabled by user software)
//);
 int FPOR __attribute__((space(prog), address(0xF8000C))) = 0xE7 ;
//_FPOR(
//    FPWRT_PWR128         // POR Timer Value (128ms)
//);
 int FICD __attribute__((space(prog), address(0xF8000E))) = 0xC3 ;
//_FICD(
//    ICS_PGD1 &           // Comm Channel Select (Communicate on PGC1/EMUC1 and PGD1/EMUD1)
//    JTAGEN_OFF           // JTAG Port Enable (JTAG is Disabled)
//);