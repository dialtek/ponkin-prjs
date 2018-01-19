#define Line_1    0x00
#define Line_2    0x40
#define Line_3    0x10
#define Line_4    0x50


static void LCDWriteNibble(unsigned char uc)       // Запись половины байта
{                                           
  uc = uc << 4;                                    // Align with bits 7-4
  LCD_RW = 0;
  buf = uc;
  RG12 = buf4;
  RG13 = buf5;
  RB1 = buf6;
  RB0 = buf7;
  delay_ms(1);
  LCD_E = 1;
  delay_us(2);
  LCD_E = 0; 
}

static void LCDWriteData(unsigned char uc)
{
    LCD_RS=0;
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
}

static void LCDInit(void)
{
  LCD_E=0;
  LCD_RS=0;
  delay_ms(20);
  LCDWriteNibble(3);
  Delay_ms(40);
  LCDWriteNibble(3);
  Delay_ms(40);
  LCDWriteNibble(3);
  Delay_ms(40);
  LCDWriteNibble(2);
  Delay_ms(40);

// --- Function Set --- //
   LCDCommand(0x2A);      //Настройка 4-ёхбитного режима работы ЖКИ, страница 1 встроенного знакогенератора
   
// --- Display ON/OFF control --- //
   LCDCommand(0x0C);      //Включение индикатора, курсор выключен
   
// --- Clear Display --- //
   LCDCommand(0x01);      //Очистка индикатора
   
// --- Entry Mode Set --- //
   LCDCommand(0x06);      //Установка режима ввода данных: сдвигать курсор вправо
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
    LCDMsg(" ");
    //Delay_ms(2000);
    LCDSetCursor(0x40);
    LCDMsg("АнтикриостатV1.0");
    LCDSetCursor(0x50);
    LCDMsg("___JINR_LHEP____");
    Delay_ms(2000);
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

    if (u8NumDigs>=8)
    {
      LCDPutCh((U8)u16a+'0');
    }
      _u16-=u16b;
      
   u16a=_u16/1000000;
   u16b=u16a*1000000;
      
    if (u8NumDigs>=7)
    {
      LCDPutCh((U8)u16a+'0');
    }
      _u16-=u16b;
      
   u16a=_u16/100000;
   u16b=u16a*100000;

    if (u8NumDigs>=6)
    {
      LCDPutCh((U8)u16a+'0');
    }

    _u16-=u16b;
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

/*
static float sqrt_cpu_newton(float L)
   {
      float temp, div = L; 
      float rslt = (float)L; 
      if (L <= 0) return 0; 
      while (l)
      {
          temp = L/div + div; 
         div = temp >> 1; 
         div += temp & 1; 
         if (rslt > div) rslt = (U16)div; 
         else 
         {
          if (l/rslt == rslt-1 && l%rslt==0) rslt--; 
          return rslt; 
          }
      }
   }
   */
