/*
#define 'Á' 0xA0
#define 'Ã' 0xA1
#define '¨' 0xA2
#define 'Æ' 0xA3
#define 'Ç' 0xA4
#define 'È' 0xA5
#define 'É' 0xA6
#define 'Ë' 0xA7
#define 'Ï' 0xA8
#define 'Ó' 0xA9
#define 'Ô' 0xAA
#define '×' 0xAB
#define 'Ø' 0xAC
#define 'Ú' 0xAD
#define 'Û' 0xAE
#define 'Ý' 0xAF
*/


#define one   0x00
#define two   0x40
#define three 0x10
#define four  0x50


static void LCDWriteNibble(unsigned char uc)
{                                           
  uc=uc << 4; /* Align with bits 7-4*/
  LCD_RW=0;
  buf=uc;
  RG0=buf4;
  RG1=buf5;
  RB1=buf6;
  RB0=buf7;
  //delay_ms(50);
  delay_ms(1);
  LCD_E=1;
  //delay_us(100);
  delay_us(2);
  LCD_E=0;
  delay_us(100);
  LCD_RW=1;   
}

static void LCDWriteData(unsigned char uc)
{
  
    LCD_RS=0;
    //delay_ms(50);
    delay_us(500);
    LCD_RS=1;
    LCD_RW=1;// ?????????????? ???????? ?????????????
    LCDWriteNibble(uc>>4);//???? ???????? ???????
    LCDWriteNibble(uc);
  
}

static void LCDCommand(unsigned char uc)
{
    LCD_RS=0; /* Instruction mode */
    delay_us(500);
    //delay_ms(5);
    LCD_RW=1;// ?????????????? ???????? ?????????????
    LCDWriteNibble(uc>>4);
    LCDWriteNibble(uc);  
}

static void LCDSetCursor(unsigned char ucPos)
{
  LCDCommand(0x80 | ucPos);
}

static void LCDClear(void)
{
   LCDCommand(0x1);
   Delay_us(200);
   //delay_ms(5);
}

static void LCDInit(void)
{
  LCD_E=0;
  LCD_RS=0;
  //Delay_ms(1000); //
  delay_ms(2000);
  LCDWriteNibble(3);
  //Delay_us(200);
  Delay_ms(1);
  LCDWriteNibble(3);
  Delay_ms(1);
  //Delay_us(200);
  LCDWriteNibble(3);
  Delay_ms(1);
  //Delay_us(200);
  LCDWriteNibble(2);
  Delay_ms(1);
  //Delay_us(200);
  
  LCDCommand(0x28);//4-?????? ?????, 2 ??????, ????? 5x8 ?????
  
  LCDCommand(0x08);// ????????? ???????, ????????? ??????, ????????? ???????? ???????
  
 // LCDCommand(0x0C);// ???????? ???????, ???????? ??????, ???????? ???????? ???????
  LCDCommand(0b00001100);// ???????? ???????, ???????? ??????, ???????? ???????? ???????
  
  LCDCommand(0x06);// ?????? ????? ????????? ?????? ??? ?????? ??????
  LCDCommand(0x1);// ??????? ?????? ? ??????????? ??????? ? ?????? ??????? 
  // delay_ms(2);
  Delay_ms(8);
  LCDCommand(0x06);// ?????? ????? ????????? ?????? ??? ?????? ?????? 
  LCDCommand(0x40);//????????? ?????? DRAM
  //delay_ms(10);
  Delay_ms(20);
 }

static void LCDPutCh(char c)
{
  LCDWriteData(c);
}

static void LCDMsg(char c)
{
    
    LCDPutCh(c);
}

static void LCDWelcome(void)
{
    LCDClear();
    LCDMsg("       KZ       ");
    //Delay_ms(2000);
    LCDSetCursor(0x40);
    LCDMsg("     Vitok"      );
    LCDSetCursor(0x50);
    LCDMsg("___LHEP_JINR____");
    Delay_ms(1000);
    LCDClear();   
}

static void LCDPutU16(U32 _u16,U8 u8NumDigs)
{
   
    U32 u16a ,u16b;
    
   u16a=_u16/10000;
   u16b=u16a*10000;

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

static void LCDPutU32(U32 _u16,U8 u8NumDigs)
{
    U32 u16a ,u16b;
    
   u16a=_u16/10000000;
   u16b=u16a*10000000;

    if (u8NumDigs>=7)
    {
      LCDPutCh((U8)u16a+'0');
    }
      _u16-=u16b;
      
   u16a=_u16/1000000;
   u16b=u16a*1000000;
      
    if (u8NumDigs>=6)
    {
      LCDPutCh((U8)u16a+'0');
    }
      _u16-=u16b;
      
   u16a=_u16/100000;
   u16b=u16a*100000;

    if (u8NumDigs>=5)
    {
      LCDPutCh((U8)u16a+'0');
    }

    _u16-=u16b;
    u16a=_u16/10000;
    u16b=u16a*10000;
    if (u8NumDigs>=4)
    {
      LCDPutCh((U8)u16a+'0');
    }

    _u16-=u16b;
    u16a=_u16/1000;
    u16b=u16a*1000;
    if (u8NumDigs>=3)
    {
      LCDPutCh((U8)u16a+'0');
      
    }

    _u16-=u16b;
    u16a=_u16/100;
    u16b=u16a*100;
   if (u8NumDigs>=2)
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

static void LCDPutS32(S32 s32a,U8 u8NumDigs)
{
  char c='+';

  if (s32a<0)
  {
    s32a=-s32a;
    c='-';
  }
  LCDPutCh(c);
  LCDPutU32((U32)s32a,u8NumDigs);
}
