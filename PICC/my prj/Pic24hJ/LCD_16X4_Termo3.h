/***************** LCD functions *****************/
static void LCDWriteNibble(unsigned char uc) 
{                                           
 
  buf=uc;
  LCD_D4=Buf0;
  LCD_D5=Buf1;
  LCD_D6=Buf2;
  LCD_D7=Buf3;
  LCD_RW=0;
  PORTG=BufG;
  delay_us(1);
  LCD_E=1;
  PORTG=BufG;
  delay_us(2);
  LCD_E=0;
  PORTG=BufG;
  delay_us(2);
  LCD_RW=1; 
  PORTG=BufG;

}

static void LCDWriteData(unsigned char uc)
{
  
    LCD_RS=0;
    PORTG=BufG;
    delay_us(50);
    LCD_RS=1;
    PORTG=BufG;
    LCD_RW=1;
    PORTG=BufG;
    LCDWriteNibble(uc>>4);
    LCDWriteNibble(uc);
 
}

static void LCDCommand(unsigned char uc)
{
  
    LCD_RS=0;
    PORTG=BufG;
    delay_us(50);
    LCD_RW=1;
    PORTG=BufG;
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
   //Delay_ms(1);
   delay_ms(5);
}

static void LCDInit(void)

{
   
  LCD_E=0;
  //PORTB=BufB;
  LCD_RS=0;
  PORTG=BufG;
  Delay_ms(1000); //
  LCDWriteNibble(3);
  Delay_us(200);
  LCDWriteNibble(3);
  Delay_us(200);
  LCDWriteNibble(3);
  Delay_us(200);
  LCDWriteNibble(2);
  Delay_us(200);
  
  LCDCommand(0x28); // 4-aeoiue ?a?ei, 2 no?iee, o?eoo 5x8 oi?ae
  LCDCommand(0x08); // Auee??eou aenieae, auee??eou eo?ni?, auee??eou ii?aaiea eo?ni?a
  LCDCommand(0x0F); // Aee??eou aenieae, aee??eou eo?ni?, aee??eou ii?aaiea eo?ni?a
  LCDCommand(0x06); // Eo?ni? aoaao aaeaaouny ai?aai i?e aaiaa oaenoa
  LCDCommand(0x1);  // I?enoea ye?aia e ia?aiauaiea eo?ni?a a ia?ao? iiceoe?
  delay_ms(2);
  LCDCommand(0x06);// eo?ni? aoaao aaeaaouny ai?aai i?e auaiaa oaenoa 
  LCDCommand(0x40);// onoaiiaea aa?ana DRAM
  delay_ms(10);
}
 
static void LCDPutCh(char c)
{
  LCDWriteData(c);
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

/*
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
*/
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
    LCDPutCh(c);
}

 static void LCDWelcome(void)
{
    //U16 u16a;
    LCDClear();
    LCDMsg("    KRION-6T    ");
    //Delay_ms(2000);
    LCDSetCursor(0x40);
    LCDMsg("  THERMOMETRY   ");
    LCDSetCursor(0x50);
    LCDMsg("   LHEP JINR   ");
    Delay_ms(2000);
    LCDClear();   
}
