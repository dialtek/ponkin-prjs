#include "C:\PRJ\TK-2\main.h"
//#device  high_ints=true

#BYTE TRISA = 0xF92
#BYTE TRISB = 0xF93
#BYTE TRISC = 0xF94 
#BYTE TRISD = 0xF95

#BYTE PORTA = 0xF80
#BYTE PORTB = 0xF81
#BYTE PORTC = 0xF82
#BYTE PORTD = 0xF83

#BIT RA2 = PORTA.2
#BIT TRA2 = TRISA.2
#BIT TRA4 = TRISA.4
#BIT TRA5 = TRISA.5
#BIT TRC4 = TRISC.4
#BIT TRC5 = TRISC.5
#BIT RB5 = PORTB.5
#BIT LCD_RS = PORTD.3
#BIT LCD_RW = PORTD.0
#BIT LCD_E = PORTD.2
#BIT PORTD4 = PORTD.4
#BIT PORTD5 = PORTD.5
#BIT PORTD6 = PORTD.6
#BIT PORTD7 = PORTD.7
#BIT PORTC4 = PORTC.4
#BIT PORTC5 = PORTC.5

#BIT RB0 = PORTB.0
#BIT RB1 = PORTB.1
#BIT PORTB2 = PORTB.2
#BIT PORTB3 = PORTB.3
#BIT PORTB4 = PORTB.4
#BIT PORTB5 = PORTB.5
#BIT PORTB6 = PORTB.6
#BIT PORTB7 = PORTB.7


typedef unsigned int32 U32;
typedef signed int32 S32;
typedef int16 U16;
typedef signed int16 S16;
typedef unsigned int8 U8;

signed int8 x=0;
int1 fl1=0,fl2=0;
static U8 phase=0,buf=0,buf1=0,buf2=0,buf3=0; 
static U16  angle=0,buf4=0,buf5=0;
signed int16 sum1=0;
static S32 turn_counter1=0,turn_counter2=0; 
static S32 l1=0,l2=0;
static U8 MenuItemNum=0;

static U8 b_hold[4]={0,0,0,0};
static U8 b_push[4]={0,0,0,0};
static U8 t_out[4]={0,0,0,0};

static int1 Pbfl = 0,PbFl1=0;


#BIT bf4=buf.4
#BIT bf5=buf.5
#BIT bf6=buf.6
#BIT bf7=buf.7


/*
  Name  : CRC-8
  Poly  : 0x31    x^8 + x^5 + x^4 + 1
  Init  : 0xFF
  Revert: false
  XorOut: 0x00
  Check : 0xF7 ("123456789")
  MaxLen: 15 байт(127 бит) - обнаружение
    одинарных, двойных, тройных и всех нечетных ошибок
*/
unsigned char Crc8(unsigned char *pcBlock, unsigned int len)
{
    unsigned char crc = 0xFF;
    unsigned int i;
 
    while (len--)
    {
        crc ^= *pcBlock++;
 
        for (i = 0; i < 8; i++)
            crc = crc & 0x80 ? (crc << 1) ^ 0x31 : crc << 1;
    }
 
    return crc;
}

/***************** LCD functions *****************/
static void LCDWriteNibble(unsigned char uc) /* RS must be set/reset before calling */
{                                           
  uc=uc << 4; /* Align with bits 7-4*/
  LCD_RW=0;
  buf=uc;
  PORTD4=bf4;
  PORTD5=bf5;
  PORTD6=bf6;
  PORTD7=bf7;
  delay_ms(1);
  LCD_E=1;
  delay_us(2);
  LCD_E=0;
  delay_us(2);
  LCD_RW=1;   
}

static void LCDWriteData(unsigned char uc)
{
  
    LCD_RS=0;
    delay_ms(1);
    LCD_RS=1;
    LCD_RW=1;// Восстановление байтовой синхронизации
    LCDWriteNibble(uc>>4);//двиг разрядов старших
    LCDWriteNibble(uc);
  
}

static void LCDCommand(unsigned char uc)
{
  
    LCD_RS=0; /* Instruction mode */
    delay_ms(1);
    LCD_RW=1;// Восстановление байтовой синхронизации
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
   Delay_ms(1);
  
}

static void LCDInit(void)

{
   
  LCD_E=0;
  LCD_RS=0;
  Delay_ms(1000); //
  LCDWriteNibble(3);
  Delay_us(200);
  LCDWriteNibble(3);
  Delay_us(200);
  LCDWriteNibble(3);
  Delay_us(200);
  LCDWriteNibble(2);
  Delay_us(200);
  
  
  LCDCommand(0x28);//4-битный режим, 2 строки, шрифт 5x8 точек
  
  LCDCommand(0x08);// Выключить дисплей, выключить курсор, выключить моргание курсора
  
  

 // LCDCommand(0x0C);// Включить дисплей, включить курсор, включить моргание курсора
   LCDCommand(0b00001100);// Включить дисплей, включить курсор, включить моргание курсора
  
  
  LCDCommand(0x06);// ?????? ????? ????????? ?????? ??? ?????? ??????
  LCDCommand(0x1);// ??????? ?????? ? ??????????? ??????? ? ?????? ??????? 
   delay_ms(2);
  LCDCommand(0x06);// ?????? ????? ????????? ?????? ??? ?????? ?????? 
  LCDCommand(0x40);//????????? ?????? DRAM
  delay_ms(10);
 }

/*
static void LCDInit(void)

{
   // ЧТО ЗА (3)
  LCD_E=0;
  LCD_RS=0;
  Delay_ms(1); //
  LCDWriteNibble(3);
  Delay_ms(1);
  LCDWriteNibble(3);
  Delay_ms(1);
  LCDWriteNibble(3);
  Delay_ms(1);
  LCDWriteNibble(3);
  Delay_ms(1);
 
  // ИНФОРМАЦИЯ ИЗ ДАТАШИТА
  
  LCDCommand(0x28);//4-битный режим, 2 строки, шрифт 5x8 точек
   
  LCDCommand(0x08);// Выключить дисплей, выключить курсор, выключить моргание курсора
 
  LCDCommand(0x0F);// Включить дисплей, включить курсор, включить моргание курсора
  Delay_ms(5000);
  LCDCommand(0x06);// Курсор будет двигаться вправо при выводе текста
 
  LCDCommand(0x1);// Очистка экрана и перемещение курсора в первую позицию 
    
  LCDCommand(0x06);// Курсор будет двигаться вправо при выводе текста 
  
  LCDCommand(0x40);//Установка адреса DRAM
  
  
 }
 */
 
 static void LCDPutCh(char c)
{
  LCDWriteData(c);
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


 static void LCDPutU32(U32 _u32,U8 u8NumDigs)
{
   
    U32 u32a ,u32b;
    
    u32a=_u32/10000000;
    u32b=u32a*10000000;

    if (u8NumDigs>=8)
    {
      LCDPutCh((U8)u32a+'0');
    }   
    
    u32a=_u32/1000000;
    u32b=u32a*1000000;

    if (u8NumDigs>=7)
    {
      LCDPutCh((U8)u32a+'0');
    }   
    
    
    u32a=_u32/100000;
    u32b=u32a*100000;

    if (u8NumDigs>=6)
    {
      LCDPutCh((U8)u32a+'0');
    }   
    
      
    u32a=_u32/10000;
    u32b=u32a*10000;

    if (u8NumDigs>=5)
    {
      LCDPutCh((U8)u32a+'0');
    }

    _u32-=u32b;
    u32a=_u32/1000;
    u32b=u32a*1000;
    if (u8NumDigs>=4)
    {
      LCDPutCh((U8)u32a+'0');
    }

    _u32-=u32b;
    u32a=_u32/100;
    u32b=u32a*100;
    if (u8NumDigs>=3)
    {
      LCDPutCh((U8)u32a+'0');
    }

    _u32-=u32b;
    u32a=_u32/10;
    u32b=u32a*10;
   if (u8NumDigs>=2)
    {
      LCDPutCh((U8)u32a+'0');
    }

    _u32-=u32b;
    if (u8NumDigs>=1)
    {
      LCDPutCh((U8)_u32+'0');
    }
  
}


static void LCDPutS16(S16 s16a,U8 u8NumDigs)
{
  //char c='+';
  char c=' ';

  if (s16a<0)
  {
    s16a=-s16a;
    c='-';
  }
  LCDPutCh(c);
  LCDPutU16((U16)s16a,u8NumDigs);
}

static void LCDPutS32(S32 s32a,U8 u8NumDigs)
{
  //char c='+';
  char c=' ';

  if (s32a<0)
  {
    s32a=-s32a;
    c='-';
  }
  LCDPutCh(c);
  LCDPutU32((U32)s32a,u8NumDigs);
}

static void LCDMsg(char c)
{
  
    LCDPutCh(c);
  
}

 static void LCDWelcome(void)
{
    U16 u16a;
    LCDClear();
    LCDMsg("TK-2 v1.0");
    Delay_ms(20);
    LCDSetCursor(0x40);
    LCDMsg("Firmware 08.09.1"); 
    Delay_ms(3000);
    LCDClear();   
}

static int1 PBScan(U8 pb){
// сканирование кнопок
//pb-номер кнопки(0-3);
    
    switch (pb){
      case 0:
         return !PORTB4;
      break;
      case 1:
         return !PORTB5;
      break;
      case 2:
         return !PORTB6;
      break;
      case 3:
         return !PORTB7;
      break;
      default:
         return 0;
    
    }
}

static int1 ButOk(void){
  if (b_push[3]){
             b_push[3]=0;
             LCDSetCursor(0x10);
             LCDMsg("   OK ");
             return true;
             }else return false;

}

#int_TIMER2 HIGH
void  TIMER2_isr(void) 
{
switch(phase){
case(0):
//сброс ТМР1
set_timer1(0);
PORTC4=0;
PORTC5=0;
phase=1;
break;

case(1):
PORTC4=1;
PORTC5=0;
phase=2;
break;

case(2):
PORTC4=1;
PORTC5=1;
phase=3;
break;

case(3):
PORTC4=0;
PORTC5=1;
phase=0;
break;

default:
phase=0;
}
clear_interrupt(int_timer2);
}

#int_CCP1
void CAPTURE1_isr(void)
{
  buf4=CCP_1>>3;// 360 градусов buf4 - текущее
  
  //счетчик витков
  sum1=buf4-buf5;
  if(sum1 < (-300))x=1;//+1 виток
   else 
   if(sum1 > 300) x=-1;// -1 виток
     else x=0;
  turn_counter1=turn_counter1+x;
  turn_counter2=turn_counter2+x;
  buf5=buf4;//buf5-предыдущее значение
  
  if(!fl1){
     fl1=1;
     angle=buf4;// 360 градусов 
  }
 // angle=buf4;// 360 градусов 
clear_interrupt(int_CCP1);
}

#int_RB
void cpb_isr(void)
{
buf1=portb;
fl2=true;
clear_interrupt(int_RB);
}

#int_EXT 
void ext0_isr(void)
{
   if(!rb0){
      if(rb1)  ++l1;
       else --l1;
   }
clear_interrupt(int_EXT);
}

void main()
{
U8 i=0,j=0,crc1,crc2;
int1 pb_yes_fl=0,crcOkfl=0;
char eebuf[15];
U32 tcbuf,l1buf;


   setup_adc_ports(NO_ANALOGS|VSS_VDD);
   setup_adc(ADC_OFF|ADC_TAD_MUL_0);
   setup_psp(PSP_DISABLED);
   setup_spi(SPI_SS_DISABLED);
   setup_wdt(WDT_OFF);
   setup_timer_0(RTCC_INTERNAL);
  // setup_timer_1(T1_DISABLED);
 
   
   
  setup_vref(VREF_LOW|12|VREF_A2);//0.5Ucc на RA2
  setup_comparator(A0_A3_A1_A2_OUT_ON_A4_A5);



   // TODO: USER CODE!!


   TRA2 = 1;//обозначили как вход
   
   TRC4=0;//sin
   TRC5 = 0;//cos обозначили как выход
   TRA4=1;
   TRA5=0;
   TRISD=0b00000010;
   TRISB=0b11111111;   //rb1-rb4 как входы
   
   //PORTC5=0;
   
   LCDInit();
   
   LCDWelcome();
   
   LCDClear();
     LCDSetCursor(0x0);
    LCDMsg("Reading data ");
    LCDSetCursor(0x40);
    LCDMsg("from EEPROM...");
    
    for (j=0;j<12;j++)
          eebuf[j]=read_eeprom (j);
       crc1=CRC8(eebuf,8);
       crc2=eebuf[8];
       if(crc1==crc2){ 
            //CRC ok 
            crcokfl=true;
            //переписываем из EEPROM в переменные
             LCDMsg("OK");
             tcbuf=eebuf[3];// ст. байт
             tcbuf=(tcbuf<<8) + eebuf[2];
             tcbuf=(tcbuf<<8) + eebuf[1];
             tcbuf=(tcbuf<<8) + eebuf[0];//мл. байт
             
             l1buf=eebuf[7];// ст. байт
             l1buf=(l1buf<<8) + eebuf[6];
             l1buf=(l1buf<<8) + eebuf[5];
             l1buf=(l1buf<<8) + eebuf[4];//мл. байт
             
              }else {
             crcokfl=false; 
             LCDSetCursor(0x10);
             LCDMsg("CRC error !");
             }
    
    /*
    LCDSetCursor(0x50);
    LCDMsg("CRC1=");
    LCDPutU16(CRC1,3);
    LCDMsg("CRC2=");
    LCDPutU16(crc2,3);        
    delay_ms(1000);
    */
     Delay_ms(1000);
     LCDClear();
 
    setup_timer_1(T1_INTERNAL|T1_DIV_BY_2);

  // setup_timer_2(T2_DISABLED,0,1);
   setup_timer_2(T2_DIV_BY_16,89,1);
   setup_ccp1 (CCP_CAPTURE_FE); 

  // setup_comparator(NC_NC_NC_NC);
   

  // setup_vref(FALSE);
 
   ext_int_edge( 0,H_TO_L );   // Sets up EXT
   
     delay_ms(200);
    
    clear_interrupt(int_EXT);
    clear_interrupt(int_CCP1);
    clear_interrupt(int_RB);
   
    enable_interrupts(INT_TIMER2);
    enable_interrupts(INT_CCP1); 
    enable_interrupts(INT_EXT); 
    enable_interrupts(INT_RB); 
    enable_interrupts(GLOBAL);
    delay_ms(100);
    if(crcokfl){
        turn_counter1=tcbuf;
        l1=l1buf;
        }
    
   fl1=0;
   while(true){
   //обработка кнопок
    if(fl2){
    // есть прерывание от кнопок
    delay_ms(50);// для подавления дребезга
    for(i=0; i<4; ++i){
//нажата ли кнопка?
 if (PBScan(i)){
  //кнопка зажата
   //порог подавления дребезга достигнут
   if(t_out[i]==0) {// 0- потому что работаем по прерывнию от нажатия кн.
          //да
          //флаг "Удерживается" установлен
          if(!b_hold[i]){
            //нет
            b_hold[i]=1;//утановить флаг "Удерживается"
            b_push[i]=1;//установить флаг "нажато"
           }
          //да
       }
      else
      //порог подавления дребезга не достигнут
      {
      ++t_out[i];//инкримент переменной подавления дребезга
      }
   }
   else
   // кнопка не нажата
   {
   t_out[i]=0; //обнуление переменной подавления дребезга
   b_hold[i]=0; //сброс флага "удерживается"
   }
}
 //***********кнопки обработаны***********************
  
  if(b_push[1]){
     b_push[1]=0;
     Pbfl = 1;
       ++MenuItemNum;
      } 
        if(MenuItemNum>6) MenuItemNum=0;
        
    fl2=0;
    }
    
      PbFl1=Pbfl; // для синхронности изменения MenuItem и PbFl

      switch (MenuItemNum){
      case 0:
       if(Pbfl1){
         Pbfl=0;
         delay_ms(1);
         LCDClear();
       }
        //нулевой пункт меню
        pb_yes_fl=0;
        if(fl1){
        LCDSetCursor(0x0); 
        LCDMsg("Az=");
        LCDPutU32(angle,3);//знака
        LCDPutCh(0xDF);  // Точка градусов
  
        LCDSetCursor(0x40);
        LCDMsg("W=");
        LCDPutS32(turn_counter1,5);//знака
        LCDPutCh(0xb3);
   
        LCDSetCursor(0x10);
        LCDMsg("L=");
        LCDPutS32((l1*39661)/10000,7);//знака
        LCDPutCh('c');
        LCDPutCh(0xbc);
   
        fl1=0;
        }
      break;
      
      case 1:
      if(Pbfl1){
         Pbfl=0;
          b_push[3]=0;//сброс запомненнных нажатий кн ок
         delay_ms(1);
         LCDClear();
         }
         LCDSetCursor(0x00);
         LCDMsg("  W=");
         LCDPutS32(turn_counter1,5);//знака
         LCDPutCh(0xb3);
        
         LCDSetCursor(0x40);
         LCDMsg("  Set to zero?");
         if(ButOk()) turn_counter1=0;
        break;
       
       case 2:
       if(Pbfl1){
         Pbfl=0;
         b_push[3]=0;//сброс запомненнных нажатий кн ок
         delay_ms(1);
         LCDClear();
        }
        LCDSetCursor(0x00);
        LCDMsg("L=");
        LCDPutS32(l1,5);//знака
         LCDMsg(" pulses");
        
        LCDSetCursor(0x40);
        LCDMsg("  Set to zero?");
        if(ButOk()) l1=0;
         
       break;
       
       case 3:
       if(Pbfl1){
         Pbfl=0;
         b_push[3]=0;//сброс запомненнных нажатий кн ок
         delay_ms(1);
         LCDClear();
       }
        LCDSetCursor(0x00);
        LCDMsg(" Write W and L ");
        LCDSetCursor(0x40);
        LCDMsg(" to EEPROM?");
        if(ButOk()){
         // запись в EEPROM
         // подготовка буфера данных для записи
         //сохранили переменные перед записью
         tcbuf=turn_counter1;
         l1buf=l1;
           eebuf[0]=tcbuf;    //мл.байт
           eebuf[1]=tcbuf>>8; //2-й байт
           eebuf[2]=tcbuf>>16;//3-й байт
           eebuf[3]=tcbuf>>24;//ст. байт
           
           eebuf[4]=l1buf;    //мл.байт
           eebuf[5]=l1buf>>8; //2-й байт
           eebuf[6]=l1buf>>16;//3-й байт
           eebuf[7]=l1buf>>24;//ст. байт
           
           eebuf[8]=CRC8(eebuf,8);//Вычисление контрольной суммы
          // disable_interrupts(GLOBAL);
           //устанавливать адрес последней ячейки EEPROM на неиспользуемую область!!!
            // запись в EEPROM
            for (j=0;j<12;++j) 
                              write_eeprom (j, eebuf[j]);
             // enable_interrupts(GLOBAL);
              LCDSetCursor(0x50);
              LCDMsg(" CRC=" );
              LCDPutU16(eebuf[8],3);
              Delay_ms(1000);
              LCDClear();
              //восстановили переменные после записи
              turn_counter1=tcbuf;
              l1=l1buf;

              MenuItemNum=0;
          }
       break;
       
       case 4:
       if(Pbfl1){
         Pbfl=0;
         b_push[3]=0;//сброс запомненнных нажатий кн ок 
         delay_ms(1);
         LCDClear();
       }
       // LCDSetCursor(0x00);
       // LCDMsg("menu num4");
        
         MenuItemNum=0;
       break;
       
       default:
       MenuItemNum=0;
      }
   }

}
