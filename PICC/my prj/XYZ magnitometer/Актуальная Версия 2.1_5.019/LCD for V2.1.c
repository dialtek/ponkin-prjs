/***************** LCD functions *****************/

void LCDWriteNibble(unsigned char uc) // RS must be set/reset before calling 
{                                           
   uc=uc << 4; // Align with bits 7-4
   LCD_RW=0;
   buf = uc;
    DB4 = buf4;
    DB5 = buf5;
    DB6 = buf6;
    DB7 = buf7;
   delay_us(500);
   LCD_E = 1;
   delay_us(2);
   LCD_E = 0;
   delay_us(50);
}

void LCDWriteData(unsigned char uc)
{    
   LCD_RS = 0;
    delay_us(500);
    LCD_RS = 1;
    LCD_RW = 1;// Восстановление байтовой синхронизации
    LCDWriteNibble(uc>>4);//двиг разрядов старших
    LCDWriteNibble(uc);
}

void LCDCommand(unsigned char uc)
{
    LCD_RS = 0; // Instruction mode
    delay_us(250);
    LCD_RW = 1;// Восстановление байтовой синхронизации
    LCDWriteNibble(uc>>4);
    LCDWriteNibble(uc);  
}

void LCDSetCursor(unsigned char ucPos)
{
  LCDCommand(0x80 | ucPos);
}

void LCDClear(void)
{
   LCDCommand(0x1);
   delay_us(200);
}

void LCDinit(void)
{
  LCD_E=0;
  LCD_RS=0;
   
  Delay_ms(20);
  
  LCDWriteNibble(3);
  Delay_us(40);
  LCDWriteNibble(3);
  Delay_us(40);
  LCDWriteNibble(3);
  Delay_us(40);
  LCDWriteNibble(2);
  Delay_us(40);
 
  LCDCommand(0x2A);//???????? 1 WIN CP1261 ??????? ?????  
  LCDCommand(0x08);// ????????? ???????, ????????? ??????, ????????? ???????? ???????
  LCDCommand(0x1);// ??????? ?????? ? ??????????? ??????? ? ?????? ??????? 
  LCDCommand(0x06);// ?????? ????? ????????? ?????? ??? ?????? ?????? 
  LCDCommand(0b00001111);

 }

void LCDPutCh(char c)
{
  LCDWriteData(c);
}

void LCDPutU16(U32 _u16,U8 u8NumDigs)
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
      LCDPutCh((U8)u16a +'0');
      LCDPutCh('.');
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

void LCDPutU16n(U32 _u16,U8 u8NumDigs)
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
      LCDPutCh((U8)u16a +'0');
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

void LCDPutS16(S16 s16a,U8 u8NumDigs)
{
   char c='+';

   if (s16a<0)
   {
      s16a=-s16a;
      c='-';
   }
   LCDPutCh(c);
   LCDPutU16((U16)s16a, u8NumDigs);
}

void LCDPutS16n(S16 s16a,U8 u8NumDigs)
{
   char c='+';

   if (s16a<0)
   {
      s16a=-s16a;
      c='-';
   }
   LCDPutCh(c);
   LCDPutU16n((U16)s16a, u8NumDigs);
}

void LCDMsg(char c)
{
    LCDPutCh(c);
}

void LCDWelcome(void){
   LCDMsg("   ����������");
   LCDSetCursor(two);
   LCDMsg("   ���������");
   LCDSetCursor(three);
   LCDMsg(" ��������. v2.4 ");
   LCDSetCursor(four);
   LCDMsg("                ");
   Delay_ms(1000);
   LCDClear();  
}

void NC_LCDMsg()
{

    LCDSetCursor (one);
    LCDMsg ("    ������     ");
    LCDSetCursor (two);
    LCDMsg ("      ��       ");
    LCDSetCursor (three);
    LCDMsg ("   ���������!  ");
    LCDSetCursor (four);
    LCDMsg ("                ");
}
