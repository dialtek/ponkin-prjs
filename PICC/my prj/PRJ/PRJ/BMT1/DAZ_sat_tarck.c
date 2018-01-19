#include <16F876.h>
//#device PIC16F876 
//#device *=16
//#device adc=10
#FUSES NOWDT, HS, NOPUT, NOPROTECT, BROWNOUT, NOLVP, NOCPD, NOWRT, NODEBUG
//#use delay(clock=4000000)
//#use rs232(baud=9600,parity=N,xmit=PIN_C6,rcv=PIN_C7,bits=8)

//#pragma  chip PIC16F876
//#pragma config WDTE=off, FOSC=XT, BODEN=off, PWRTE=on
// Todo:
// * Make work without LCD - OK 0.2
// * Test -180 - 0 - +180 rotator. OK 0.2
// * Test 0 - 450 rotator ("FAF" command) OK 0.2 but no with S-N-S rotator
// * Add Easycomm interface - fixed 0.7
// * Add more GS-232 commands - 'M###' added 0.7
// * Fix 16F876A and combined right/up button push problem. OK 0.2
// * Allow calibration from buttons - switch on with one of the front panel buttons pressed OK 0.2
// * Random Az/El target displayed on boot up OK 0.2
// * Random Az/El target displayed after calibration OK 0.3
// * Floating point OK 0.3
// * Include speed control
// * Fix overshoot
// * Fix SatPC32 problem of repeatedly rewriting - fixed 0.5
// * Bug when Elevation not moving in certain scenarios - fixed 0.6
// * Reduce LCD flicker by only updating occasionally - fixed 0.6
// * Smooth ADC readings by taking an averaged number - fixed 0.6
// * Change defualt ADC constants for my rotator ;-) - fixed 0.6
// * Add 'M' GS-232 command to set Az only - fixed 0.7
// * Исправлена ошибка записи в EEPROM
// * Переделаны функции управления ЖКИ для поддержки ЖКИ МЭЛТ МТ16S2H
// * Исправлена ошибка в вызове функции LCDSetCursor с 40 на 0x40

#define DELAY_CONSTANT 13  /* Software delay constant: 16 for 4.9152MHz, 13 for 4MHz */
#BYTE FSR = 0x04 // FSR reg
#BYTE TMR0 = 0x1 // TIMER0 reg
#BYTE TXREG = 0x19 // UART TX reg

#BYTE RCSTA = 0x18 // UART RX Sataus reg

#BIT RX9 = RCSTA.6
#BIT SPEN = RCSTA.7

#BYTE RCREG = 0x1A // UART RX reg

#BYTE INTCON = 0xB // INTERRUPT reg

#BIT T0IF = INTCON.2 // T0 int flag
#BIT T0IE = INTCON.5 // T0 int enable
#BIT PEIE = INTCON.6 // periperial int enable
#BIT GIE = INTCON.7  // global interrupt enable

#BYTE ADCON1 = 0x9F // ADC regs
#BYTE ADCON0 = 0x1F //
#BYTE ADRESH = 0x1E // ADC result h byte
#BYTE ADRESL = 0x9E // ADC result l byte
#BYTE PIR1 = 0xC //
#BYTE PIE1 = 0x8C //

#BYTE EEADR = 0x10D //
#BYTE EECON1 = 0x18C //

#BIT EEPGD = EECON1.7
#BIT EERD = EECON1.0
#BIT EEWR = EECON1.1
#BIT WREN = EECON1.2

#BYTE EECON2 = 0x18D // 

#BYTE EEDATA = 0x10C


#BIT TXIF = PIR1.4  //PIR1 reg 
#BIT TXIE = PIE1.4  //PIE1 reg
#BIT RCIF = PIR1.5  //PIR1 reg 
#BIT RCIE = PIE1.5  // PIE1 reg
#BIT OERR = RCSTA.1
#BIT CREN = RCSTA.4

#BIT ADFM = ADCON1.7
#BIT PCFG0 = ADCON1.0
#BIT PCFG1 = ADCON1.1
#BIT PCFG2 = ADCON1.2
#BIT PCFG3 = ADCON1.3
#BIT CHS0 = ADCON0.3
#BIT CHS1 = ADCON0.4
#BIT CHS2 = ADCON0.5
#BIT ADCS0 = ADCON0.6
#BIT ADCS1 = ADCON0.7
#BIT ADON = ADCON0.0
#BIT GO_DONE = ADCON0.2

#BYTE TRISA = 0x85
#BYTE TRISB = 0x86
#BYTE TRISC = 0x87

#BIT TRISC0 = TRISC.0
#BIT TRISC1 = TRISC.1
#BIT TRISC2 = TRISC.2
#BIT TRISC3 = TRISC.3

#BIT TRISC6 = TRISC.6
#BIT TRISC7= TRISC.7

#BYTE PORTA = 0x5
#BYTE PORTB = 0x6

#BIT LCD_RS = PORTB.0
#BIT LCD_RW = PORTB.1
#BIT LCD_E = PORTB.2
#BIT PORTB3 = PORTB.3

#define nop   {#ASM    nop \
#ENDASM}

#define LCD_TIMERWAIT 200 // Time to wait in ms to update LCD to stop flickering

#BYTE PORTC = 0x07

#BIT ROT_LEFT = PORTC.0
#BIT ROT_RIGHT = PORTC.1
#BIT ROT_DOWN = PORTC.2
#BIT ROT_UP = PORTC.3

#BYTE OPTION_REG = 0x81

#BIT PS0 = OPTION_REG.0
#BIT PS1 = OPTION_REG.1
#BIT PS2 = OPTION_REG.2
#BIT PSA = OPTION_REG.3
#BIT T0CS = OPTION_REG.5

#BYTE SPBRG = 0x99

#BYTE TXSTA = 0x98

#BIT BRGH = TXSTA.2
#BIT SYNC = TXSTA.4
#BIT TX9 = TXSTA.6
#BIT TXEN = TXSTA.5


#define BTN_LEFT 1
#define BTN_RIGHT 2
#define BTN_DOWN 4
#define BTN_UP 8



#define EC_NONE 0 // EasyComm command decode numbers
#define EC_AZ 1
#define EC_EL 2
#define EC_UP 3
#define EC_DN 4

#define RS232_BRG 26 /* Baud rate generator BR=FOSC/(16(SPBRG+1)) 9600 bps 26 for 4MHz, 31 for 4.9152MHz */
#define RS232_RXBUFFERSIZE 60
#define RS232_TXBUFFERSIZE 20
#define RS232_LINESIZE 60

#define ADC_NUMSAMPLES 25 // number of ADC samples to take to try to smooth things

#define EE_AZMUL 0
#define EE_AZOFF 3
#define EE_ELMUL 5
#define EE_ELOFF 8
#define EE_FLAGS 10
#define EE_MAX 11 /* Total number of EE bytes used -1 for checksum purposes */

typedef int32 U32;
typedef int16 U16;
typedef signed int16 S16;
typedef int8 U8;

typedef union
{
  float f;
  struct
  {
    U8 u8Lo;
    U8 u8Mid;
    U8 u8Hi;
  } fs;
} FLOATUNION;

static U8 _u8Buttons;
static U8 _u8ButtonsLast;
static U8 tst1;
// RS232 buffers etc
static char _acRS232RxData[RS232_RXBUFFERSIZE]; /* Rx Buffer */
static char _cRS232RxIn;
static char _cRS232RxOut;
static char _acRS232TxData[RS232_TXBUFFERSIZE]; /* Tx Buffer */
static char _cRS232TxIn;
static char _cRS232TxOut;

static BOOLEAN RS232RxCharReady(void);
static char RS232RxGetChar(void);
static BOOLEAN RS232RxPutChar(char c);
static BOOLEAN RS232TxCharReady(void);
static char RS232TxGetChar(void);
static BOOLEAN RS232TxPutChar(char c);
static BOOLEAN RS232TxMsg( char psz);

/* Line input parser */
static char _acLine[RS232_LINESIZE];
static U8 _u8LinePos;

// Are we moving? 
static BOOLEAN _bAzTrack;
static BOOLEAN _bElTrack;

// Target Az/El
static S16 _s16AzTarget;
static S16 _s16ElTarget;

// EEPROM stored values
static float _fAzMul;
static U16 _u16AzOff; // Raw ADC offset for zero Az
static float _fElMul;
static U16 _u16ElOff; // Raw ADC offset for zero El
static U16 _u16Flags; // Flags

#BIT FLAG_AZ450 = _u16Flags.0 // 450 degree azimuth flag

#BIT FLAG_SNS = _u16Flags.1 // -180 - 0 - +180 flag



// Incremented by timer 0 interrupt
static U16 _u16Timer; 

static BOOLEAN _bLCDActive;
static U16 _u16LCDTimer; // Timer setting last time LCD was updated to stop flicker


 
// handle the timer interrupt
#int_TIMER0
void TMR0int() 
{
 _u16Timer++;
  TMR0=250; // Increments and overflows when rolls over past 255 
  T0IF=0; // Must remember to clear overflow or will continuously interrupt! 
 //set_timer0(250);
 //clear_interrupt(int_timer0);
}

// handle the tx serial interrupt
#int_TBE
void RS232TXint()
{
if (RS232TxCharReady())
    {
    //putc(RS232TxGetChar()); 
    TXREG=RS232TxGetChar();
    }
    else
    {
      TXIE=0;
    }
 
}

 // handle the rx serial interrupt
#int_RDA
void RS232RxInt()
{
     // RS232RxPutChar(getc());
   if (OERR)
    {
      CREN=0; // Must reset Rx logic on overrun
      CREN=1;
    }
    else
    {
      RS232RxPutChar(RCREG);
    }    
}  

// Some glue functions...

static U16 ByteToWord(U8 u8Lo,U8 u8Hi)
{
  U16 u16a;
  u16a=((int16) u8Hi) << 8;
  return u16a+u8Lo;
}

static char toupper(char c)
{
  if (c>='a' && c<='z')
  {
    c-='a'-'A';
  }
  return c;
}

static void Delay(unsigned char uc) /* software delay uc * 100us */
{
  while (uc)
  {
    char uc2;

    uc--;

    for (uc2=0;uc2<DELAY_CONSTANT;uc2++)
    {
    }
  }
}

static U16 TimerGet(void)
{
  U16 u16a;

  GIE=0;
  u16a=_u16Timer;
  GIE=1;

  return u16a;
}

static BOOLEAN ParseWhite(U8 *pu8Pos)
{
  // Ignore white space in _acLine. Return FALSE if no white space...
  BOOLEAN bFinished=FALSE;
  BOOLEAN bWhiteFound=FALSE; // at end of string
  U8 u8Pos;
  char c;
  u8Pos=*pu8Pos;
 

  while (!bFinished)
  {
    if (u8Pos<_u8LinePos)
    {
      c=_acLine[u8Pos];
      if (c!=' ' && c!='\t')
      {
        bFinished=TRUE;
      }
      else
      {
        bWhiteFound=TRUE;
        u8Pos++;
      }
    }
    else
    {
      bFinished=TRUE;
    }
  }
  *pu8Pos=u8Pos;
  return bWhiteFound;  
}

static BOOLEAN ParseU16(U8 *pu8Pos,U16 *pu16)
{
  // Parse _acLine from *pu8Pos for a number. Return FALSE if error...
  BOOLEAN bFinished=FALSE;
  BOOLEAN bNumFound=FALSE; // at end of string
  char c;
  U8 u8Pos;
  U16 u16a=0;
  u8Pos=*pu8Pos;
 
  while (!bFinished)
  {
    if (u8Pos<_u8LinePos)
    {
      c=_acLine[u8Pos];
      if (c<'0' || c>'9')
      {
        bFinished=TRUE;
      }
      else
      {
        bNumFound=TRUE;
        u16a*=10;
        c-='0';
        u16a+=c;
        u8Pos++;
      }
    }
    else
    {
      bFinished=TRUE;
    }
  }
  *pu8Pos=u8Pos;
  if (bNumFound)
  {
    *pu16=u16a;
  }
  return bNumFound;  
}

static BOOLEAN ParseFloat(U8 *pu8Pos,float *pf)
{
  U16 u16Int;
  U16 u16Frac=0;
  float f;
  U8 u8a,u8Pos;
  float fFrac;
  

  if (!ParseU16(pu8Pos,&u16Int))
  {
    return FALSE;
  }
  f=u16Int;
  u8a=*pu8Pos;
  if (_acLine[u8a]=='.')
  {
   
    (*pu8Pos)++;

    u8Pos=*pu8Pos; // So we know how many digits in the fractional part

    if (ParseU16(pu8Pos,&u16Frac))
    {
      fFrac=u16Frac;

      u8Pos=*pu8Pos-u8Pos;
      while (u8Pos)
      {
        fFrac/=10;
        u8Pos--;
      }
      f+=fFrac;
    }
  }
  *pf=f;
  return TRUE;
} 

/*************** ADC functions ****************/

static void Set_adc_ch(U8 adc_ch_no)
{
    U8 buf1,buf2;
    buf1 = (adc_ch_no & 0x7) << 3; // clear bits 3-7 and shift left 
    ADCON0 = ADCON0 & 0x38;  // clear bits 3-5
    ADCON0 = buf1 | ADCON0; // set bits 
}

static U16 ADCGet(U8 u8Channel)
{
  int n;
  U16 u16Sum=0;

  for (n=0;n<ADC_NUMSAMPLES;n++)
  {
    U16 u16Result=0;

    ADFM=1; // Right Justified

    PCFG0=0; // VDD/VSS ref, three channels
    PCFG1=0;
    PCFG2=1;
    PCFG3=0;
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  //  Set_adc_ch (u8Channel);
     //set_adc_channel(u8Channel);


    CHS0=(BOOLEAN)(u8Channel & 0x1);
    CHS1=(BOOLEAN)(u8Channel & 0x2);
    CHS2=(BOOLEAN)(u8Channel & 0x4);

    ADCS0=0; // FOSC/32
    ADCS1=1;

    ADON=1; // switch on A/D

    Delay(1); // Wait for required acquisition time
     //delay_us(100);



    GO_DONE=1; // Set Go/!Done bit to start conversion

    while (GO_DONE) // Wait for Go/!Done bit to clear
    {
    }
     
    u16Result=((U16)(ADRESH))<<8;
    u16Result|=ADRESL;

    ADON=0; // switch off A/D

    PCFG0=0; // VDD/VSS ref, zero channels
    PCFG1=1;
    PCFG2=1;
    PCFG3=0;

    u16Sum+=u16Result;  
  }
  u16Sum/=ADC_NUMSAMPLES;
  return u16Sum;
}



 
/********* RS232 Functions *************/ 

static BOOLEAN RS232RxCharReady(void)
{
  if (_cRS232RxIn==_cRS232RxOut)
  {
    return FALSE;
  }
  else
  {
    return TRUE;
  }
}

static char RS232RxGetChar(void)
{
   char c;
  if (RS232RxCharReady())
  {
     c=_acRS232RxData[_cRS232RxOut];
    _cRS232RxOut++;
    if (_cRS232RxOut>=RS232_RXBUFFERSIZE)
    {
      _cRS232RxOut=0;
    }
    return c;
  }
  else
  {
    return FALSE;
  }
}

static BOOLEAN RS232RxPutChar(char c)
{
  char cNextIdx;
  cNextIdx=_cRS232RxIn+1;

  if (cNextIdx>=RS232_RXBUFFERSIZE)
  {
    cNextIdx=0;
  }

  if (cNextIdx==_cRS232RxOut)
  {
    return FALSE;
  }
  _acRS232RxData[_cRS232RxIn]=c;
  _cRS232RxIn=cNextIdx;
  return TRUE;
}


static boolean RS232TxCharReady(void)
{
  if (_cRS232TxIn==_cRS232TxOut)
  {
    return FALSE;
  }
  else
  {
    return TRUE;
  }
}


static char RS232TxGetChar(void)
{
  char c;
  if (RS232TxCharReady())
  {
     c=_acRS232TxData[_cRS232TxOut];
    _cRS232TxOut++;
    if (_cRS232TxOut>=RS232_TXBUFFERSIZE)
    {
      _cRS232TxOut=0;
    }
    return c;
  }
  else
  {
    return FALSE;
  }
}

static BOOLEAN RS232TxPutChar(char c)
{
   char cNextIdx;
   cNextIdx=_cRS232TxIn+1;

  if (cNextIdx>=RS232_TXBUFFERSIZE)
  {
    cNextIdx=0;
  }

  if (cNextIdx==_cRS232TxOut)
  {
    return FALSE;
  }
  _acRS232TxData[_cRS232TxIn]=c;
  _cRS232TxIn=cNextIdx;

  if (!TXIE)
  {
    TXIE=1;
  }
  return TRUE;
}

static void RS232TxPutU16(U16 _u16)
{
  U16 u16a, u16b;

  u16a=_u16/1000;
  u16b=u16a*1000;

  RS232TxPutChar((U8)u16a+'0');

  _u16-=u16b;
  u16a=_u16/100;
  u16b=u16a*100;
  RS232TxPutChar((U8)u16a+'0');

  _u16-=u16b;
  u16a=_u16/10;
  u16b=u16a*10;
  RS232TxPutChar((U8)u16a+'0');

  _u16-=u16b;
  RS232TxPutChar((U8)_u16+'0');
}

static void RS232TxPutS16(S16 s16a)
{
  char c='+';

  if (s16a<0)
  {
    s16a=-s16a;
    c='-';
  }
  RS232TxPutChar(c);
  RS232TxPutU16((U16)s16a);
}

static void RS232TxPutFloat(float f)
{
  float f2;

  if (f<0.0)
  {
    f=0.0;
  }

  RS232TxPutU16((U16)f);
  RS232TxPutChar('.');
  f2=(U16)f; // remove integer part
  f-=f2;
  f*=10000.0;
  RS232TxPutU16((U16)f);
}


static BOOLEAN RS232TxMsg(char psz)
{
  BOOLEAN b;
  b=RS232TxPutChar(psz);
  if (!b)
  {
      return FALSE;
  }
  else
  {
    return TRUE;
  }  
}

static void RS232TxPutError(void)
{
  RS232TxPutChar('?');
  RS232TxPutChar('>');
  RS232TxPutChar('\r');
  RS232TxPutChar('\n');
}

static void RS232TxInit(void)
{
  _cRS232TxIn=0;
  _cRS232TxOut=0;
}

static void RS232RxInit(void)
{
  _cRS232RxIn=0;
  _cRS232RxOut=0;
}


/***************** LCD functions *****************/

static void LCDWriteNibble(unsigned char uc) /* RS must be set/reset before calling */
{                                           //Запись половины байта
  uc=uc << 2; /* Align with bits 2-5 */
  LCD_RW=0;
  TRISA=0b11000011; /* Set to output bits 2-5 */
  PORTA=uc;
  LCD_E=1;
  nop;
  nop;
  LCD_E=0;
  //LCD_RW=1; !!!!!!!!!!!!!!
  TRISA=0b11111111; /* Set to input bits 2-5 */  
}

static unsigned char LCDReadByte(void) /* RS must be set/reset before calling */
{
  unsigned char uc,uc2;

  LCD_RW=1;
  LCD_E=1;
  nop;
  nop;
  uc=PORTA;
  LCD_E=0;
  uc<<=2;
  uc&=0xF0;
  LCD_E=1;
  nop;
  nop;
  uc2=PORTA;
  LCD_E=0;
  uc2>>=2;
  LCD_RW=0; // Восстановление байтовой синхронизации
  uc2&=0x0F;
  uc|=uc2;
  return uc;
}

static BOOLEAN LCDWaitReady(void)
{
  if (_bLCDActive)
  {
    U16 _u16;
    _u16=TimerGet();

    while (LCDReadByte() & 0x80)
    {
      U16 u16Diff;
      u16Diff=TimerGet()-_u16;

      if (u16Diff>5) // Timeout
      {
        _bLCDActive=FALSE;
        return FALSE;
      }
    }
  }
  return TRUE;
}

static void LCDWriteData(unsigned char uc)
{
  if (_bLCDActive)
  {
    LCD_RS=0;
    LCDWaitReady();
    LCD_RS=1;
    LCD_RW=1;// Восстановление байтовой синхронизации
    LCDWriteNibble(uc>>4);
    LCDWriteNibble(uc);
  }
}

static unsigned char LCDReadData(void)
{
  if (_bLCDActive)
  {
    LCD_RS=0;
    LCDWaitReady();
    LCD_RS=1;
    return LCDReadByte();
  }
  else
  {
    return 0;
  }
}

static void LCDCommand(unsigned char uc)
{
  if (_bLCDActive)
  {
    LCD_RS=0; /* Instruction mode */
    LCDWaitReady();
    LCD_RW=1;// Восстановление байтовой синхронизации
    LCDWriteNibble(uc>>4);
    LCDWriteNibble(uc);
  }
}

static void LCDSetCursor(unsigned char ucPos)
{
  if (_bLCDActive)
  {
    LCDCommand(0x80 | ucPos);
  }
}

static void LCDClear(void)
{
  if (_bLCDActive)
  {
    LCDCommand(0x01);
  }
}

static void LCDInit1(void)
{
  _bLCDActive=TRUE; // Let's be optimistic
  _u16LCDTimer=0; // Initialize timer

  LCD_E=0;
  LCD_RS=0;
  Delay(250);
  LCDWriteNibble(3);
  Delay(50);
  LCDWriteNibble(3);
  Delay(2);
  LCDWriteNibble(3);
  Delay(2);
  LCDWriteNibble(2);
  Delay(2);
  LCDCommand(0b00101000);
  LCDCommand(0b00001000);
  LCDCommand(0b00000001);
  LCDCommand(0b00000110);
  LCDCommand(0b00001111);
}

static void LCDInit(void)
// MT16S2H init function
{
  _bLCDActive=TRUE; // Let's be optimistic
  _u16LCDTimer=0; // Initialize timer
  
  LCD_E=0;
  LCD_RS=0;
  Delay(250); ///* software delay uc * 100us */
  LCDWriteNibble(3);
  Delay(50);
  LCDWriteNibble(3);
  Delay(2);
  LCDWriteNibble(3);
  Delay(2);
  LCDWriteNibble(2);
  Delay(2);
  LCDCommand(0b00101000);//установка разрядности интерфейса(4 бит) и страницы знакогенератора
  //LCDCommand(0x28);
  LCDCommand(0b00001000);
  //LCDCommand(0x08);// включение модуля и выбор типа курсора
  LCDCommand(0b00000001);
  //LCDCommand(0x1);// Очистка экрана и перемещение курсора в первую позицию 
  LCDCommand(0b00000110);
  LCDCommand(0b00001111);

 
  
}
static void LCDPutCh(char c)
{
  LCDWriteData(c);
}

static void LCDPutU16(U16 _u16,U8 u8NumDigs)
{
 
  if (_bLCDActive)
  {
    U16 u16a ,u16b;
    
    u16a=_u16/1000;
    u16b=u16a*1000;

    if (u8NumDigs>=5)
    {
      LCDPutCh((U8)u16a+'0');
    }

    _u16-=u16b;
    u16a=_u16/1000;
    u16b=u16a*1000;
    if (u8NumDigs>=4)
    {
      LCDPutCh((U8)u16a+'0');
    }

    _u16-=u16b;
    u16a=_u16/100;
    u16b=u16a*100;
    if (u8NumDigs>=3)
    {
      LCDPutCh((U8)u16a+'0');
    }

    _u16-=u16b;
    u16a=_u16/10;
    u16b=u16a*10;
    if (u8NumDigs>=2)
    {
      LCDPutCh((U8)u16a+'0');
    }

    _u16-=u16b;
    if (u8NumDigs>=1)
    {
      LCDPutCh((U8)_u16+'0');
    }
  }
}

static void LCDPutS16(S16 s16a,U8 u8NumDigs)
{
  char c='+';

  if (s16a<0)
  {
    s16a=-s16a;
    c='-';
  }
  LCDPutCh(c); 
  LCDPutU16((U16)s16a,u8NumDigs);
}

static void LCDMsg(char c)
{
  if (_bLCDActive)
  {
    LCDPutCh(c);
  }
}

// Display signed Azimuth
static void LCDPutAz(S16 s16a)
{
  if (_bLCDActive)
  {
   
   if (FLAG_SNS)
    {
      if (s16a<180)
      {
        LCDPutS16(s16a+180,3);
      }
      else
      {
        LCDPutS16(s16a-180,3);
      }
    }
    else
    {
      LCDPutS16(s16a,3);
    }
  }
}

 static void LCDWelcome(void)
{
  if (_bLCDActive)
  {
    U16 u16a;
    LCDClear();
    LCDMsg("DAZ Tracker");
    LCDSetCursor(0x40);
    LCDMsg("Firmware v0.7.2");
    for (u16a=0;u16a<200;u16a++) // wait 2s
    {
      Delay(100);
    }
    LCDClear();
    LCDMsg("MELT MT16S2H LCD");
    LCDSetCursor(0x40);
    LCDMsg("supported");
     for (u16a=0;u16a<200;u16a++) // wait 2s
    {
      Delay(100);
    }
  }
}

// Update LCD display
static void LCDUpdate(void)
{
  U16 u16Timer;
  u16Timer=TimerGet();
  u16Timer-=_u16LCDTimer;

  if (_bLCDActive && u16Timer>LCD_TIMERWAIT)
  {
    S16 s16a=0;

    _u16LCDTimer+=u16Timer;

    LCDSetCursor(0x0);

    LCDMsg("Az "); // Измеряем Az
 
    s16a=(S16)ADCGet(0);
    s16a-=(S16)_u16AzOff;
    s16a/=_fAzMul;

    LCDPutAz(s16a); // выводим на LCD
    LCDPutCh(0xDF); // Точка градусов

    LCDMsg(" ("); 
   
    LCDPutAz(_s16AzTarget);
    LCDPutCh(0xDF); // Точка градусов
    LCDPutCh(')');

    LCDSetCursor(0x40);

    LCDMsg("El ");
 
    s16a=(S16)ADCGet(1);
    s16a-=(S16)_u16ElOff;
    s16a/=_fElMul;

    LCDPutS16(s16a,3);
    LCDPutCh(0xDF);  // Точка градусов
//------------------------------------------------
    LCDMsg(" (");

    LCDPutS16((S16)_s16ElTarget,3);
    LCDPutCh(0xDF);
    LCDPutCh(')');
  }
}


/***************** EEPROM functions ******************/

// Read a byte of EEPROM data
static U8 EEReadByte(U8 u8Addr)
{
  EEADR=u8Addr;
  EEPGD=0; // Clear EEPGD
  EERD = 1;// Set control bit RD
  return EEDATA;
}

// Read a Word of EEPROM data
static U16 EEReadWord(U8 u8Addr)
{
  U16 u16a;

  u16a=EEReadByte(u8Addr+1);
  u16a<<=8;
  u16a+=EEReadByte(u8Addr);

  return u16a;
}

static float EEReadFloat(U8 u8Addr)
{
  FLOATUNION fu;

  fu.fs.u8Lo=EEReadByte(u8Addr);
  fu.fs.u8Mid=EEReadByte(u8Addr+1);
  fu.fs.u8Hi=EEReadByte(u8Addr+2);

  return fu.f;
}

// Write a byte of EEPROM data
static void EEWriteByte(U8 u8Addr,U8 u8Data)
{
  EEADR=u8Addr;
  EEDATA=u8Data;
  EEPGD=0; // Clear EEPGD
  WREN=1;  
  GIE=0;
  EECON2=0x55;
  EECON2=0xAA;
  EEWR=1;
  GIE=1;
  WREN=0;  
  while (EEWR)
  {
  }  
}

// Write a Word of EEPROM data
static void EEWriteWord(U8 u8Addr,U16 u16Data)
{
  EEWriteByte(u8Addr,(U8)u16Data);
  u16Data>>=8;
  EEWriteByte(u8Addr+1,u16Data);
}

// Write a Float of EEPROM data
static void EEWriteFloat(U8 u8Addr,float f)
{
  FLOATUNION *pfu=&f;
  EEWriteByte(u8Addr,pfu->fs.u8Lo);
  EEWriteByte(u8Addr+1,pfu->fs.u8Mid);
  EEWriteByte(u8Addr+2,pfu->fs.u8Hi);
}

// Calculate the EEPROM checksum
static U16 EECalcSum(void)
{
  U8 u8a;
  U16 u16Sum=0;

  for (u8a=0; u8a<EE_MAX; u8a++)
  {
    u16Sum+=(U8)(EEReadByte(u8a)+u8a);
  }
  return u16Sum;
}

// Write the EEPROM checksum
static void EEWriteSum(void)
{
  U16 u16a;
  u16a=EECalcSum();
  EEWriteWord(254,u16a);
}

// Check the EEPROM checksum is OK
static BOOLEAN EECheck(void)
{
  BOOLEAN b;

  U16 u16SumRead,u16SumCalc;
  
  u16SumRead=EEReadWord(254);
  u16SumCalc=EECalcSum();

  if (u16SumRead==u16SumCalc)
  {
    return TRUE;
  }
  return FALSE;
}

// If EEPROM values are OK, load them up, otherwise choose some default values.
// Warns on LCD if EEPROM values are wrong.
static void EEInit()
{
  if (!EECheck())
  {
    U16 u16a;

    LCDClear();
    LCDMsg("Warning: bad");
    LCDSetCursor(0x40);
    LCDMsg("EEPROM data.");
    _fAzMul=1.8583;
    _u16AzOff=8;
    _fElMul=4.5555;
    _u16ElOff=13;
    _u16Flags=0;
    for (u16a=0;u16a<200;u16a++) // wait 2s
    {
      Delay(100);
    }
    LCDClear();
  }
  else
  {
    _fAzMul=EEReadFloat(EE_AZMUL);
    _u16AzOff=EEReadWord(EE_AZOFF);
    _fElMul=EEReadFloat(EE_ELMUL);    
    _u16ElOff=EEReadWord(EE_ELOFF);
    _u16Flags=EEReadWord(EE_FLAGS);
  }
}

// Write current RAM values to EEPROM
static BOOLEAN EEWriteAll(void)
{
  EEWriteFloat(EE_AZMUL,_fAzMul);
  EEWriteWord(EE_AZOFF,_u16AzOff);
  EEWriteFloat(EE_ELMUL,_fElMul);
  EEWriteWord(EE_ELOFF,_u16ElOff);
  EEWriteWord(EE_FLAGS,_u16Flags);
  EEWriteSum();
  return EECheck();
}


/**************** Button functions *******************/

static U8 ButtonGetRaw(void)
{
  // Not debounced.
  U8 u8a;

  PORTB3=0; // Enable buttons
  nop; // Need this delay!!! 16F876A does not settle in time otherwise.
  u8a=PORTA; // Read buttons
  PORTB3=1; // Disable buttons
  u8a>>=2;
  u8a&=0x0F;
  u8a^=0x0F;
  return u8a;
}

static U8 ButtonGet(void)
{
  // Wait for 5ms of completely stable buttons to debounce
 
  U8 u8Org,u8New;
  U16 u16Org,u16New,u16Diff;
    
  u8Org=ButtonGetRaw();
  u16Org=TimerGet();
  u8New=u8Org;
  u16New=u16Org;
  
  do
  {
 
    u8New=ButtonGetRaw();
    u16New=TimerGet();

    if (u8New!=u8Org)
    {
      u8Org=u8New;
      u16Org=u16New; // reset timer
    }
    u16Diff=u16New-u16Org;
  } while (u16Diff<5);

  return u8New;
}

// Deal with any button pushes and return immediately
// Only moves rotator according to mask
// Mask bit 0 Left
// Mask bit 1 Right
// Mask bit 2 Down
// Mask bit 3 Up
// Returns button state

// при нажатии кнопок 
// не проверяются никакие ограничения
// сразу запись в порт управления приводом антенны
static U8 ButtonCheck(U8 u8Mask) 
{
  U8 u8a;

  // Any change in button status?
  _u8Buttons=ButtonGet();

  u8a=_u8Buttons^_u8ButtonsLast;

  if (u8a!=0)
  {
    if (u8a & 0x03 & u8Mask) // нажаты обе кнопки
    {
      ROT_LEFT=0;
      ROT_RIGHT=0;
      _bAzTrack=FALSE;
      if (_u8Buttons & BTN_LEFT)
      {
        ROT_LEFT=1;
      }
      else
      {
        if (_u8Buttons & BTN_RIGHT)
        {
          ROT_RIGHT=1;
        }
      }
    }
    if (u8a & 0x0C & u8Mask) // нажаты обе кнопки
    {
      ROT_DOWN=0;
      ROT_UP=0;
      _bElTrack=FALSE;
      if (_u8Buttons & BTN_DOWN)
      {
        ROT_DOWN=1;
      }
      else
      {
        if (_u8Buttons & BTN_UP)
        {
          ROT_UP=1;
        }
      }
    }
    _u8ButtonsLast=_u8Buttons;
  }
  return _u8Buttons;
}

// Stop the rotator when it's reached its destination
static void RotatorUpdate(void)
{
  if (_bAzTrack)
  {
    S16 s16Az;
    s16Az=(S16)ADCGet(0);
    s16Az-=_u16AzOff;
    s16Az/=_fAzMul;

    if ((_s16AzTarget>=s16Az && ROT_LEFT) ||
      (_s16AzTarget<=s16Az && ROT_RIGHT))
    {
      ROT_LEFT=0;
      ROT_RIGHT=0;
      _bAzTrack=FALSE;
    }
  }

  if (_bElTrack)
  {
    S16 s16El;
    s16El=(S16)ADCGet(1);
    s16El-=_u16ElOff;
    s16El/=_fElMul;

    if ((_s16ElTarget>=s16El && ROT_DOWN) ||
      (_s16ElTarget<=s16El && ROT_UP))
    {
      ROT_DOWN=0;
      ROT_UP=0;
      _bElTrack=FALSE;
    }
  }
}

// Wait for buttons to be pressed not in mask. Allow Rotator to move according to those in mask.
// Return buttons pressed.
static U8 ButtonGetPress(U8 u8Mask)
{
  U8 u8Button;

  do
  {
    u8Button=ButtonCheck(u8Mask);
  } while ((u8Button & ~u8Mask)!=0); // wait for buttons to be released first

  do
  {
    u8Button=ButtonCheck(u8Mask);
  } while ((u8Button & ~u8Mask)==0);

  return u8Button;
}

static void ButtonConfig(void) //Калибровка с кнопок
{
  if (_bLCDActive && ButtonGet()) // Если присутствует ЖКИ и нажата кнопка,то входим в режим калибровки
  {
    U8 u8Button;
    BOOLEAN bFinished;
    U16 u16AzMin;
    U16 u16AzMax;
    U16 u16ElMin;
    U16 u16ElMax;
    BOOLEAN bAz450=FALSE;
    BOOLEAN bEl90=FALSE;
    BOOLEAN bSNS=FALSE;

    LCDClear();
    LCDMsg("Set Az=min &");
    LCDSetCursor(0x40);
    LCDMsg("press D (U=esc)");

    u8Button=ButtonGetPress(BTN_LEFT | BTN_RIGHT);
    if (u8Button & BTN_UP)
    {
      return;
    }
    u16AzMin=ADCGet(0);

    LCDClear();
    LCDMsg("Set El=min &");
    LCDSetCursor(0x40);
    LCDMsg("press L (R=esc)");

    u8Button=ButtonGetPress(BTN_UP | BTN_DOWN);
    if (u8Button & BTN_RIGHT)
    {
      return;
    }
    u16ElMin=ADCGet(1);

    LCDClear();
    LCDMsg("Set Az=max &");
    LCDSetCursor(0x40);
    LCDMsg("press D (U=esc)");

    u8Button=ButtonGetPress(BTN_LEFT | BTN_RIGHT);
    if (u8Button & BTN_UP)
    {
      return;
    }
    u16AzMax=ADCGet(0);

    LCDClear();
    LCDMsg("Set El=max &");
    LCDSetCursor(0x40);
    LCDMsg("press L (R=esc)");

    u8Button=ButtonGetPress(BTN_UP | BTN_DOWN);
    if (u8Button & BTN_RIGHT)
    {
      return;
    }
    u16ElMax=ADCGet(1);

    LCDClear();
    LCDMsg("Az range: 450 U");
    LCDSetCursor(0x40);
    LCDMsg("360 D (R=esc)");

    u8Button=ButtonGetPress(0);
    if (u8Button & BTN_RIGHT)
    {
      return;
    }
    if (u8Button & BTN_UP)
    {
      bAz450=TRUE;
    }

    LCDClear();
    LCDMsg("El range: 0-90 U");
    LCDSetCursor(0x40);
    LCDMsg("0-180 D (R=esc)");

    u8Button=ButtonGetPress(0);
    if (u8Button & BTN_RIGHT)
    {
      return;
    }
    if (u8Button & BTN_UP)
    {
      bEl90=TRUE;
    }

    LCDClear();
    LCDMsg("CCW stop North=U");
    LCDSetCursor(0x40);
    LCDMsg("South=D (R=esc)");

    u8Button=ButtonGetPress(0);
    if (u8Button & BTN_RIGHT)
    {
      return;
    }
    if (u8Button & BTN_DOWN)
    {
      bSNS=TRUE;
    }

    LCDClear();
    LCDMsg("EE Write: U");
    LCDSetCursor(0x40);
    LCDMsg("(R=esc)");

    u8Button=ButtonGetPress(0);
    if (u8Button & BTN_RIGHT)
    {
      return;
    }
    if (u8Button & BTN_UP)
    {
      FLAG_SNS=bSNS;
      FLAG_AZ450=bAz450;
      _u16AzOff=u16AzMin;
      _u16ElOff=u16ElMin;
      _fAzMul=(float)(u16AzMax-u16AzMin);
      if (bAz450)
      {
        _fAzMul/=450.0;
      }
      else
      {
        _fAzMul/=360.0;//размерность В/град.
      }
      _fElMul=(float)(u16ElMax-u16ElMin);
      if (bEl90)
      {
       _fElMul/=90;//размерность В/град.
      }
      else
      {
        _fElMul/=180;
      }
      LCDClear();
      if (EEWriteAll())
      {
        LCDMsg("EEPROM write OK");
      }
      else
      {
        LCDMsg("EEPROM failed!");
      }
      LCDSetCursor(0x40);
      LCDMsg("Push btn to exit");
      ButtonGetPress(0);
    }
  }
}

// Zeroise target and stop tracking
static void TargetInit(void)
{
  _s16AzTarget=0;
  _s16ElTarget=0;
  _bAzTrack=FALSE;
  _bElTrack=FALSE;
}

static U8 EasyCommCommand(U8 *pu8Pos)
{
  // Look for a two character Easycomm command...
  char c1='\0';
  char c2='\0';
  U8 u8Pos;
  U8 u8Command;
  u8Pos=*pu8Pos;
  u8Command=EC_NONE;
  ParseWhite(&u8Pos); // ignore white space

  if (u8Pos<=_u8LinePos+1) // make sure there's at least two more characters
  {
    c1=toupper(_acLine[u8Pos++]);
    c2=toupper(_acLine[u8Pos++]);

    if (c1=='A' && c2=='Z')
    {
      u8Command=EC_AZ; 
    }
    else if (c1=='E' && c2=='L')
    {
      u8Command=EC_EL;
    }
    else if (c1=='U' && c2=='P')
    {
      u8Command=EC_UP;
    }
    else if (c1=='D' && c2=='N')
    {
      u8Command=EC_DN;
    }
    if (u8Command!=EC_NONE)
    {
      *pu8Pos=u8Pos;
    }
  }
  return u8Command;
}

static void RotatorSet(S16 s16Az,S16 s16El)
{
  // Set the rotator position. 
  // If El or Az are 32767, then no attempt is made to move that axis
  if (s16Az!=32767)
  {
    if (FLAG_SNS)
    {
      if (s16Az<180)
      {
        s16Az+=180;
      }
      else
      {
        s16Az-=180;
      }
    }
    _s16AzTarget=s16Az;

    s16Az=(S16)ADCGet(0);

    s16Az-=_u16AzOff;
    s16Az/=_fAzMul;

    if (_s16AzTarget>s16Az)
    {
      ROT_RIGHT=1;
      ROT_LEFT=0;
      _bAzTrack=TRUE;
    }
    else
    {
      if (_s16AzTarget<s16Az)
      {
        ROT_LEFT=1;
        ROT_RIGHT=0;
        _bAzTrack=TRUE;
      }
      else
      {
        ROT_LEFT=0;
        ROT_RIGHT=0;
        _bAzTrack=FALSE;
      }
    }
  }
  if (s16El!=32767)
  {
    _bElTrack=TRUE;
    _s16ElTarget=s16El;

    s16El=(S16)ADCGet(1);

    s16El-=_u16ElOff;
    s16El/=_fElMul;

    if (_s16ElTarget>s16El)
    {
      ROT_UP=1;
      ROT_DOWN=0;
      _bElTrack=TRUE;
    }
    else
    {
      if (_s16ElTarget<s16El)
      {
        ROT_DOWN=1;
        ROT_UP=0;
        _bElTrack=TRUE;
      }
      else
      {
        ROT_DOWN=0;
        ROT_UP=0;
        _bElTrack=FALSE;
      }
    }
  }
}

// Parse the input line if one's available
static void RS232Check(void)
{
  while (RS232RxCharReady())
  {
    char c;
    c=RS232RxGetChar();


    if (c=='\n' || c=='\r')
    {
      U8 u8Pos=0;
      U8 u8EasyCommCommand;
      u8EasyCommCommand=EasyCommCommand(&u8Pos);

      if (u8EasyCommCommand!=EC_NONE)
      {
        while (u8EasyCommCommand!=EC_NONE)
        {
          BOOLEAN bError=FALSE;

          switch (u8EasyCommCommand)
          {
            case EC_AZ:
            case EC_EL:
              {
                float f;
                S16 s16a;

                ParseWhite(&u8Pos);
                if (!ParseFloat(&u8Pos,&f))
                {
                  bError=TRUE;
                  break;
                }
                s16a=(S16)f;
                if (u8EasyCommCommand==EC_AZ)
                {
                  RotatorSet(s16a,32767);
                }
                else
                {
                  RotatorSet(32767,s16a);
                }
              }
              break;
            case EC_UP:
            case EC_DN:
              // Parsed but ignored...
              {
                float f;
                char acMode[3];
                U8 u8a=0;

                ParseWhite(&u8Pos);
                if (!ParseFloat(&u8Pos,&f))
                {
                  bError=TRUE;
                  break;
                }
                ParseWhite(&u8Pos);
                while (u8Pos<_u8LinePos && u8a<3)
                {
                  char c;
                  c=_acLine[u8Pos++];

                  acMode[u8a++]=c;
                }
                while (u8a<3)
                {
                  acMode[u8a++]=' ';
                }
              }
              break;
            default:
              bError=TRUE;
              break;
          }
          if (bError)
          {
            RS232TxPutError();
            u8EasyCommCommand=EC_NONE;
          }
          else
          {
            u8EasyCommCommand=EasyCommCommand(&u8Pos);
          }
        }
      }
      else
      { // This is a GS232 command
        // Ignore leading spaces...
        while (u8Pos<_u8LinePos)
        {
          c=toupper(_acLine[u8Pos]);
          u8Pos++;
          if (c!=' ' && c!='\t')
          {
            break;
          }
        };
        if (u8Pos<=_u8LinePos)
        {
          // Get command char
          switch (c)
          {
            /* case 'F':  // Калибровка через COM-порт 
              if (u8Pos<_u8LinePos)
              {
                char cAzEl;
                cAzEl=toupper(_acLine[u8Pos++]);
  
                if (cAzEl=='W')
                {
                  if (EEWriteAll())
                  {
                    RS232TxMsg(&"EEPROM write OK\r\n");
                  }
                  else
                  {
                    RS232TxMsg(&"EEPROM failed\r\n");
                  }
                  break;
                }
  
                if (cAzEl=='S') // Set South stop rotator
                {
                  FLAG_SNS=TRUE;
                  RS232TxMsg(&"South stop\r\n");
                  break;
                }
  
                if (cAzEl=='N') // Set 0 - 360/450 rotator
                {
                  FLAG_SNS=FALSE;
                  RS232TxMsg(&"North stop\r\n");
                  break;
                }
  
                if (u8Pos<_u8LinePos)
                {
                  char cEndStart;
                  cEndStart=toupper(_acLine[u8Pos++]);
  
                  if (cAzEl=='A' && cEndStart=='O') // Set Az Offset directly
                  {
                    U16 u16a;
  
                    ParseWhite(&u8Pos);
                    if (ParseU16(&u8Pos,&u16a))
                    {
                      _u16AzOff=u16a;
                           TargetInit();
                      RS232TxMsg(&"Az off=");
                      RS232TxPutU16(_u16AzOff);
                      RS232TxMsg(&"\r\n");
                      break;
                    }
                  }
                  if (cAzEl=='A' && cEndStart=='M') // Set Az Mul directly
                  {
                    float f;
  
                    ParseWhite(&u8Pos);
                    if (ParseFloat(&u8Pos,&f))
                    {
                      _fAzMul=f;
                           TargetInit();
                      RS232TxMsg(&"Az mul=");
                      RS232TxPutFloat(_fAzMul);
                      RS232TxMsg(&"\r\n");
                      break;
                    }
                  }
                  if (cAzEl=='A' && cEndStart=='S')
                  {
                    _u16AzOff=ADCGet(0);
                    TargetInit();
                    RS232TxMsg(&"Az Offset=");
                    RS232TxPutU16(_u16AzOff);
                    RS232TxMsg(&"\r\n");
                    break;
                  }
                  if (cAzEl=='A' && cEndStart=='E')
                  {
                    U16 u16a;
                    u16a=ADCGet(0);
                    
                    _fAzMul=((float)(u16a-_u16AzOff))/360.0;
                    FLAG_AZ450=FALSE;
                    TargetInit();
                    RS232TxMsg(&"Az mul=");
                    RS232TxPutFloat(_fAzMul);
                    RS232TxMsg(&"\r\n");
                    break;
                  }
                  if (cAzEl=='A' && cEndStart=='F')
                  {
                    U16 u16a;
                    u16a=ADCGet(0);
                    
                    _fAzMul=((float)(u16a-_u16AzOff))/450.0;
                    FLAG_AZ450=TRUE;
                    TargetInit();
                    RS232TxMsg(&"Az mul=");
                    RS232TxPutFloat(_fAzMul);
                    RS232TxMsg(&"\r\n");
                    break;
                  }
                  if (cAzEl=='E' && cEndStart=='O') // Set El Offset directly
                  {
                    U16 u16a;
  
                    ParseWhite(&u8Pos);
                    if (ParseU16(&u8Pos,&u16a))
                    {
                      _u16ElOff=u16a;
                      TargetInit();
                      RS232TxMsg(&"El off=");
                      RS232TxPutU16(_u16ElOff);
                      RS232TxMsg(&"\r\n");
                      break;
                    }
                  }
                  if (cAzEl=='E' && cEndStart=='M') // Set El Mul directly
                  {
                    float f;
  
                    ParseWhite(&u8Pos);
                    if (ParseFloat(&u8Pos,&f))
                    {
                      _fElMul=f;
                      TargetInit();
                      RS232TxMsg(&"El mul=");
                      RS232TxPutFloat(_fElMul);
                      RS232TxMsg(&"\r\n");
                      break;
                    }
                  }
                  if (cAzEl=='E' && cEndStart=='S')
                  {
                    _u16ElOff=ADCGet(1);
                    TargetInit();
                    RS232TxMsg(&"El Offset=");
                    RS232TxPutU16(_u16ElOff);
                    RS232TxMsg(&"\r\n");
                    break;
                  }
                  if (cAzEl=='E' && cEndStart=='E')
                  {
                    U16 u16a;
                    u16a=ADCGet(1);
                    
                    _fElMul=((float)(u16a-_u16ElOff))/180.0;
                    TargetInit();
                    RS232TxMsg(&"El mul=");
                    RS232TxPutFloat(_fElMul);
                    RS232TxMsg(&"\r\n");
                    break;
                  }
                  if (cAzEl=='E' && cEndStart=='N')
                  {
                    U16 u16a;
                    u16a=ADCGet(1);
  
                    _fElMul=((float)(u16a-_u16ElOff))/90.0;
                    TargetInit();
                    RS232TxMsg(&"El mul=");
                    RS232TxPutFloat(_fElMul);
                    RS232TxMsg(&"\r\n");
                  }
                }
              }
              RS232TxPutError();
              break; */ // !!!!!!!!!!!!!!!!!!!!!!!!!!!!
            case 'S':
              _bAzTrack=FALSE;
              _bElTrack=FALSE;
              ROT_LEFT=0;
              ROT_RIGHT=0;
              ROT_UP=0;
              ROT_DOWN=0;
              break;
            case 'C':
              if (u8Pos<_u8LinePos)
              {
                c=_acLine[u8Pos];
              }
              // Send out AZ
              {
                S16 s16a;
                s16a=(S16)ADCGet(0);
                s16a-=(S16)_u16AzOff;
                s16a/=_fAzMul;
                if (FLAG_SNS)
                {
                  if (s16a<180)
                  {
                    RS232TxPutS16(s16a+180);
                  }
                  else
                  {
                    RS232TxPutS16(s16a-180);
                  }
                }
                else
                {
                  RS232TxPutS16(s16a);
                }
  
                if (c=='2')
                {
                  //Send out EL
                  S16 _s16;
                  _s16=(S16)ADCGet(1);
  
                  _s16-=(S16)_u16ElOff;
                  _s16/=_fElMul;
                  RS232TxPutS16(_s16);
                }
                RS232TxPutChar('\r');
                RS232TxPutChar('\n');
              }
              break;
            case 'W':
            case 'M': // 'M' command added - supposed to set Az only
              {
                S16 s16Az=32767; // wild numbers signify ignore setting
                S16 s16El=32767;
  
                ParseWhite(&u8Pos);
                if (!ParseU16(&u8Pos,(U16 *)&s16Az))
                {
                  RS232TxPutError();
                }
                else
                {
                       if (c=='W') // only for W command do we need El
                       {
                          // If no El, we ignore.
                      ParseWhite(&u8Pos);
                      ParseU16(&u8Pos,(U16 *)&s16El);
                       }
                  RotatorSet(s16Az,s16El);
                }
              }
              break;
            default:
              RS232TxPutError();
              break;
          }
        }
      }
      _u8LinePos=0;
    }
    else
    {
      if (_u8LinePos<RS232_LINESIZE)
      {
        _acLine[_u8LinePos]=c;
        _u8LinePos++;
      }
    }
  }
}

 void main(void)
{
  // TRISB Init to disable LCD E line (PORTB.2) and
  // enable portb.3 as output and set to 1 (disable buttons)
  // Bit 7 is CTS back to PC - needs to be set on or else TXD
  // connects thru to CTS via 4.7k resistor and makes some 
  // host progs loopy (eg SatPC32).
  TRISB=0b01000000;
  PORTB=0b10001000; // Set CTS on!
  _u8Buttons=0;

  // ADC Init
  TRISA = 0b11111111;  // 1=input 

  PCFG0=0; // VDD/VSS ref, zero channels Must do this or PORTA disabled for output
  PCFG1=1;
  PCFG2=1;
  PCFG3=0;

  // TMR0 Init
  _u16Timer=0;
 // setup_timer_0 (RTCC_INTERNAL|RTCC_DIV_256);

  PSA=0; // Prescaler assigned to TMR0 
  PS0=1; // 256 prescale on FOSC/4 
  PS1=1;
  PS2=1; 
  T0CS=0; // select crystal osc (FOSC/4) 
  T0IE=1; // Enable timer interrupt 
   
 
 
  // USART init
  RS232TxInit();
  RS232RxInit();
  SPBRG=RS232_BRG;
  BRGH=1; // High speed Baud rate 
  SYNC=0; // Async USART mode 
  TX9=0; // 8 bit 
  RX9=0;
  SPEN=1; // Enable serial port 
  TXEN=1; // Enable TX 
  CREN=1; // Enable Rx 
  TRISC7=1; // RX bit input 
  TRISC6=0; // TX bit output 
  TXIE=0; // Disable Tx interrupt (for now) 
  RCIE=1; // Enable Rx interrupt 
  PEIE=1; // Peripheral enable interrupts 
  

  // Enable Rotator bits as output
  TRISC0=0;
  TRISC1=0;
  TRISC2=0;
  TRISC3=0;
  

  // No movement required
  ROT_LEFT=0;
  ROT_RIGHT=0;
  ROT_DOWN=0;
  ROT_UP=0;

  // LCD Init
  
 
  LCDInit();
  
  
            
  // Welcome message on LCD
  LCDWelcome(); 
 
 
  // Initialise variables from EEPROM
  EEInit();

  // 'zeroise' target Az/El and stop tracking
   TargetInit();

  // Initialise line input parser
  _u8LinePos=0;

//  EEInit();

 GIE=1; // Enable interrupts

   
  // If a button's pressed during boot, then we need to go into config mode
  ButtonConfig();

  // Here we go...
  while (1)
  {
    ButtonCheck(0x0F); // Deal with any button presses
    RS232Check(); // Deal with any incoming RS232 stuff
    LCDUpdate(); // Update the LCD display
    RotatorUpdate(); // Update rotator settings - stop tracking if reached destination
  }
  
}  


