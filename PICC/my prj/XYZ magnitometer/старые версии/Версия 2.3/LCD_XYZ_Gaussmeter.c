/***************** LCD functions *****************/

static void LCDWriteNibble(unsigned char uc) // RS must be set/reset before calling 
{                                           
   uc=uc << 4; // Align with bits 7-4
//   output_low(LCD_RW);
   LCD_RW=0;
   buf = uc;
    DB4 = buf4;
    DB5 = buf5;
    DB6 = buf6;
    DB7 = buf7;
   delay_us(500);
   LCD_E = 1;
  //delay_us(100);
   delay_us(2);
   LCD_E = 0;
   delay_us(50);
   //LCD_RW=1; !!!! ?????? ??? MT16S2H !!!!!!!   
}

static void LCDWriteData(unsigned char uc)
{    
   LCD_RS = 0;
    //delay_ms(50);
    delay_us(500);
    LCD_RS = 1;
    LCD_RW = 1;// Восстановление байтовой синхронизации
    LCDWriteNibble(uc>>4);//двиг разрядов старших
    LCDWriteNibble(uc);
}

static void LCDCommand(unsigned char uc)
{
    LCD_RS = 0; // Instruction mode
    delay_us(250);
    LCD_RW = 1;// Восстановление байтовой синхронизации
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
   delay_us(200);
}

static void LCDinit(void)
{
  LCD_E=0;
  LCD_RS=0;
   
  Delay_ms(20); //1000
  
  LCDWriteNibble(3);
  Delay_us(40);
  LCDWriteNibble(3);
  Delay_us(40);
  LCDWriteNibble(3);
  Delay_us(40);
  LCDWriteNibble(2);
  Delay_us(40);
 
 // LCDCommand(0x28);//????????? ??????????? ??????????(4 ???) ? ???????? ???????????????
 //  LCDCommand(0b00101000);//???????? 0  
// LCDCommand(0b00101010);//???????? 1 WIN CP1261 ??????? ????? 
  LCDCommand(0x2A);//???????? 1 WIN CP1261 ??????? ????? 
  
  LCDCommand(0x08);// ????????? ???????, ????????? ??????, ????????? ???????? ???????
  //LCDCommand(0x0F);// ???????? ???????, ???????? ??????, ???????? ???????? ???????
  //LCDCommand(0x06);// ?????? ????? ????????? ?????? ??? ?????? ??????
  LCDCommand(0x1);// ??????? ?????? ? ??????????? ??????? ? ?????? ??????? 
//   delay_ms(2);
  LCDCommand(0x06);// ?????? ????? ????????? ?????? ??? ?????? ?????? 
  LCDCommand(0b00001111);

 // LCDCommand(0x00);//????????? ?????? DRAM
//  delay_ms(10);
 }

static void LCDPutCh(char c)
{
  LCDWriteData(c);
}
/*
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
*/
/**/

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
      LCDPutCh((U8)u16a +'0');
      LCDPutCh('.');
    }

    _u16-=u16b;
    u16a=_u16/100;
    u16b=u16a*100;
    
    if (u8NumDigs>=3)
    {
      LCDPutCh((U8)u16a+'0');
      //LCDPutCh('.');
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
      //LCDPutCh((U8)_u16+'0');
    }
  
}



/* // ������� ��� ���������
 static void LCDPutU16(U32 _u16,U8 u8NumDigs)
{ 
   U32 u16a ,u16b;
   u16a=_u16 / 10000;
   u16b=u16a*10000;

    if (u8NumDigs >= 5)
   {
      LCDPutCh((U8)u16a+'0');
    }

    _u16 -= u16b;
    u16a = _u16 / 1000;
    u16b = u16a * 1000;
    if (u8NumDigs >= 4)
    {
      LCDPutCh((U8)u16a+'0');
    }

    _u16 -= u16b;
    u16a = _u16 / 100;
    u16b = u16a * 100;
    if (u8NumDigs >= 3)
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
   LCDPutU16((U16)s16a, u8NumDigs);
}

static void LCDMsg(char c)
{
    LCDPutCh(c);
}

static void LCDWelcome(void){
   unsigned int8 i = 0;
//    LCDClear();
    LCDMsg("���������� ���.");
    LCDSetCursor(0x40);
    LCDMsg("��������.�� v2.3");
    Delay_ms(1000);
    LCDClear();  
}
