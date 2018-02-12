//#include "C:\Program Files\PICC\Projects\PRJ\
#include <18F4320.h>
//#device adc=10

#FUSES NOWDT                    //No Watch Dog Timer
#FUSES WDT128                   //Watch Dog Timer uses 1:128 Postscale
#FUSES H4                       //High speed osc with HW enabled 4X PLL
//#FUSES HS                       //High speed osc 
#FUSES NOFCMEN                  //Fail-safe clock monitor disabled
#FUSES BROWNOUT                 //Reset when brownout detected
#FUSES BORV45                   //Brownout reset at 4.5V
#FUSES NOPUT                    //No Power Up Timer
#FUSES NOCPD                    //No EE protection
#FUSES STVREN                   //Stack full/underflow will cause reset
#FUSES NODEBUG                  //No Debug mode for ICD
#FUSES NOLVP                      //NO Low Voltage Programming on B3(PIC16) or B5(PIC18)
#FUSES NOWRT                    //Program memory not write protected
#FUSES NOWRTD                   //Data EEPROM not write protected
#FUSES IESO                     //Internal External Switch Over mode enabled
#FUSES NOEBTR                   //Memory not protected from table reads
#FUSES NOEBTRB                  //Boot block not protected from table reads
#FUSES MCLR                     //Master Clear pin enabled
#FUSES NOPROTECT                //Code not protected from reading
#FUSES NOCPB                    //No Boot Block code protection
#FUSES NOWRTB                   //Boot block not write protected
#FUSES NOWRTC                   //configuration not registers write protected
#FUSES PBADEN                   //PORTB pins are configured as analog input channels on RESET

#use delay(clock=40000000)
#use rs232(uart1,baud=9600,parity=N,xmit=PIN_C6,rcv=PIN_C7,bits=8)

#BYTE TRISA = 0xF92
#BYTE TRISB = 0xF93
#BYTE TRISC = 0xF94 
#BYTE TRISD = 0xF95
#BYTE TRISE = 0xF96

#BYTE PORTA = 0xF80
#BYTE PORTB = 0xF81
#BYTE PORTC = 0xF82
#BYTE PORTD = 0xF83
#BYTE PORTE = 0xF84

#BYTE SSPSTAT = 0xFC7 // SPI contr. bytes       
#BYTE SSPCON = 0xFC6                           

#BIT SMP = SSPSTAT.7                                    
#BIT CKE = SSPSTAT.6                                  
#BIT CKP = SSPCON.4// SERIAL CLK POL      
      
#BIT RA0 = PORTA.0
#BIT RA1 = PORTA.1
#BIT RA2 = PORTA.2
#BIT RA3 = PORTA.3
#BIT RA4 = PORTA.4
#BIT RA5 = PORTA.5

#BIT RE0 = PORTE.0

#BIT TRA5 = TRISA.5
#BIT TRA4 = TRISA.4
#BIT TRA3 = TRISA.3
#BIT TRA2 = TRISA.2
#BIT TRA1 = TRISA.1
#BIT TRA0 = TRISA.0

#BIT TRE0 = TRISE.0

#BIT TRC5 = TRISC.5
#BIT TRC3 = TRISC.3
#BIT TRC4 = TRISC.4
#BIT TRC6 = TRISC.6
#BIT TRC7 = TRISC.7

#BIT RB5 = PORTB.5
#BIT LCD_RS = PORTD.2 
#BIT LCD_RW = PORTD.3
#BIT LCD_E = PORTD.0

//#BIT PORTD0 = PORTD.0
#BIT PORTD4 = PORTD.4
#BIT PORTD5 = PORTD.5
#BIT PORTD6 = PORTD.6
#BIT PORTD7 = PORTD.7

#BIT PORTB1 = PORTB.1
#BIT PORTB2 = PORTB.2
#BIT PORTB3 = PORTB.3
#BIT PORTB4 = PORTB.4

#BIT PORTC5 = PORTC.5
#BIT PORTC6 = PORTC.6
#BIT PORTC7 = PORTC.7

#define Din RA0  //нога Dout МК
#define Dout RA1 //нога Din МК
#define SCLK RA2
#define DRDY RA3//7-ая
#define DSYNC RA4//6 нога мк
#define RESET RA5//7-ая

#define CS RE0  //нога 8 МК

typedef unsigned int32 U32;
typedef int16 U16;
typedef signed int16 S16;
typedef unsigned int8 U8;

Char PGA = 3;
//0 - PGA=1, 1-PGA=2, 2-PGA=4, 3-PGA=8, 4-PGA=16 
static U8 buf;
const U8 SETUP=0x00,MUX=0x01,ACR=0x02,IDAC1=0x03,
IDAC2=0x04,ODAC=0x05,DIO=0x06,DIR=0x07,DEC0=0x08,
MDEC1=0x09,OCR0=0x0A,OCR1=0x0B,OCR2=0x0C,
FSR0=0x0D,FSR1=0x0E,FSR2=0x0F;

/*
static U8 count=0;
static U8 hp = 33;// мощность нагревателя в % 
static int1 tmaxfl = 0,pwrfl=0,dtfl=1;
static U8 ADCNumSamples = 20;
static int1 henfl=0;
static U16 tmax = 30;
static U8 MenuItemNum = 0;//номер пункта меню


 static u8 i;
 static U8 t_out[4]={0,0,0,0};
 static U8 b_hold[4]={0,0,0,0};
 static U8 b_push[4]={0,0,0,0};
 static int1 Pbfl = 0,PbFl1=0;
 */

#BIT buf4=buf.4
#BIT buf5=buf.5
#BIT buf6=buf.6
#BIT buf7=buf.7

static U16 U16EERead(U8 Adr){
U8 value;
U16 DATA;
DATA = read_eeprom(Adr+1);//ст.байт
DATA=DATA<<8;
DATA = DATA+read_eeprom(Adr);//мл.байт
return DATA;
}

static U8 U16EEWrite(U16 Data, U8 Adr){
U8 value;
value=DATA;
write_eeprom (Adr, value);//ст.байт
value=DATA>>8;
write_eeprom (Adr+1, value);//мл.байт
delay_ms(10);
if(U16EERead(Adr)==DATA) return 1;
 else return 0;
}

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

/*
static int1 PBScan(U8 pb){
// сканирование кнопок
//pb-номер кнопки(0-3);
    
    switch (pb){
      case 0:
         return !portb1;
      break;
      case 1:
         return !PORTB2;
      break;
      case 2:
         return !PORTB3;
      break;
      case 3:
         return !PORTB4;
      break;
      default:
         return 0;
    
    }
}
*/
/***************** LCD functions *****************/
static void LCDWriteNibble(unsigned char uc) /* RS must be set/reset before calling */
{                                           
  uc=uc << 4; /* Align with bits 7-4*/
  LCD_RW=0;
  buf=uc;
  PORTD4=buf4;
  PORTD5=buf5;
  PORTD6=buf6;
  PORTD7=buf7;
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
    delay_ms(1);
    LCD_RS=1;
    LCD_RW=1;// Восстановление байтовой синхронизации
    LCDWriteNibble(uc>>4);//двиг разрядов старших
    LCDWriteNibble(uc);
  
}

static void LCDCommand(unsigned char uc)
{
    LCD_RS=0; /* Instruction mode */
    //delay_ms(1);
    delay_ms(5);
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
   //Delay_ms(1);
   delay_ms(5);
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
  
  LCDCommand(0x28);//4-битный режим, 2 строки, шрифт 5x8 точек
  
  LCDCommand(0x08);// Выключить дисплей, выключить курсор, выключить моргание курсора
  
 // LCDCommand(0x0C);// Включить дисплей, включить курсор, включить моргание курсора
  LCDCommand(0b00001100);// Включить дисплей, включить курсор, включить моргание курсора
  
  LCDCommand(0x06);// ?????? ????? ????????? ?????? ??? ?????? ??????
  LCDCommand(0x1);// ??????? ?????? ? ??????????? ??????? ? ?????? ??????? 
  // delay_ms(2);
  Delay_ms(8);
  LCDCommand(0x06);// ?????? ????? ????????? ?????? ??? ?????? ?????? 
  LCDCommand(0x40);//????????? ?????? DRAM
  //delay_ms(10);
  Delay_ms(20);
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
    U16 u16a;
    LCDClear();
    LCDMsg("CRYO TERM. test");
    //Delay_ms(2000);
    LCDSetCursor(0x40);
    LCDMsg("Firmware test"); 
    Delay_ms(500);
    LCDClear();   
}
/*
#int_TIMER
void  TIMER1_isr(void){
// прерывание каждую мс
set_timer1(64910); 
for(i=0; i<4; ++i){
//нажата ли кнопка?
 if (PBScan(i)){
  //кнопка зажата
   //порог подавления дребезга достигнут
   if(t_out[i]==30) {
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
  
  if(b_push[2]){
     b_push[2]=0;
     Pbfl = 1;
       ++MenuItemNum;
     //   Pbfl = 1;
       
   } if(MenuItemNum>6) MenuItemNum=0;
  
      
clear_interrupt(int_timer1);//сброс прерываения..обяз
}

#int_TIMER3
void  TIMER3_isr(void) 
{
// прерывание каждые 100 мс
// управление нагревателем
set_timer3(59300);
   
   if(count>hp) pwrfl=0;
            else pwrfl=1;
            
    if(tmaxfl&&pwrfl&&dtfl&&henfl){
    PORTC5 = 1;
    }else PORTC5 = 0;
    
    if(count>99){
        count = 0;
        }
 count ++;

clear_interrupt(int_timer3);
}

u16 ADC_read(u8 ch){
  U32 ADC_value;
  u8 i;
  ADC_value=0;
  set_adc_channel(ch); // установка порта АЦП
   delay_us(20);
   for(i=0;i<ADCNumSamples;i++){
   ADC_value = read_adc()+ADC_value;// получение значений с АЦП
   delay_ms(2);
   }
   return ADC_value/ADCNumSamples;
}
*/

//----------------ADS1216 functions-----------------------------
/*
static void WrByte(char b){
   //cs = 0;
   //delay_us(10);
   spi_write(b);
   
}
*/
static void WrByte(char b)
{
spi_write(b);
}

static void WrByte1(char b){
int i;
for (i = 0; i<8; i++){
   SCLK = 1;
   buf = b;
   Dout=buf7;
   //delay_us(2);
   delay_us(10);
   //Dout=buf7;
   SCLK = 0;
   //delay_us(10);
   b=b<<1;
   }
   SCLK = 1;
}

static char RdByte(void){

int i;
char b=0;
for (i = 0; i<8; i++){
   SCLK = 0;
   //delay_us(2);
   delay_us(10);
   b=b<<1;
   
   SCLK = 1;
   delay_us(10);
   b=b+Din;
   }
SCLK = 0;
return b;
}

static char RdByte1(void){
char b = 0;
b = SPI_read(Din);
return b;
}

static void WrReg1(char RegAdr,Wbyte){
//CS = 0;
WrByte(0x50+RegAdr); 
delay_us(40);
WrByte(0x0);
delay_us(40);
WrByte(Wbyte);
//delay_us(20);
//delay_us(10);
//CS = 1;
}

static void WrReg(char RegAdr,Wbyte)
{
Spi_write(0x50+RegAdr);
delay_us(10);
Spi_write(0x0);
delay_us(10);
Spi_write(Wbyte);
}

static char RdReg1(char RegAdr){
char b;
//CS = 0;
WrByte(0x10+RegAdr);
//WrByte(0xF0+RegAdr);
delay_us(40);
WrByte(0);// число читаемых байт - 1
delay_us(40);
Rdbyte(); // мусор
delay_us(40);
b=RdByte();

delay_us(20);
//CS = 1;
return (b);

}

static char RdReg(char RegAdr){
char b;
//CS = 0;
Spi_write(0x10+RegAdr);
//WrByte(0xF0+RegAdr);
delay_us(10);
Spi_write(0);// число читаемых байт - 1
//delay_us(10);
//Spi_read(0); // мусор
delay_us(10);
b=Spi_read(0);

delay_us(20);
//CS = 1;
return (b);

}

static char RdRam(char RamAdr){
char b = 0;
//CS = 0;
WrByte(0x20+RamAdr);
//delay_us(40);
WrByte(0x0);
//delay_us(40);
b=RdByte();
//delay_us(40);
//CS = 1;
return (b);

}

static char Rdata(void){
char b =0;
WrByte(0x01);
delay_us(50);
SPI_read(0);
b = SPI_read(0)*SPI_read(0)*SPI_read(0);
return b;
}

static void AdsInit (void){
   cs=0;
delay_us(20);
WrReg(SETUP,0b00011110); //SETUP  --> buf en, ref en = 2.5 В
WrReg(MUX,0x01);         //MUX    --> Ain0 & Ain1
WrReg(ACR,PGA);          //ACR    --> PGA = 0 (Vin = +-2.5 B +- 1.5 мкВ, 
WrReg(IDAC1,0x00);   
WrReg(IDAC2,0x00);   
WrReg(ODAC,0);        //ODAC   --> ЦАП смещения диапазона вх. напряжений
WrReg(DIO,0x00);      //DIO    --> 0 или 1 на Din0 -Din7 
WrReg(DIR,0x00);         //DIR    --> конфигурация вх/вых Din0 - Din7
WrReg(DEC0,0b11111000);  // f выборок = 36 Гц. DEC0
WrReg(MDEC1,0b01110111); //M/DEC1 --> полярность вх.напряжений
delay_us(20); 
   cs=1;
}

static void SelfCal (void)
{
cs=0;
  delay_us(20);
  Wrbyte(0xF0);
  delay_us(20);
cs=1;
}

static unsigned int32 Adc_Rdata(void){
unsigned int32 r1,r2,r3;
unsigned int32 Sum;
//While (!DRDY)
l1:
if (!DRDY){
set_timer2(0);
   cs = 0;
   WrByte(0x01);
   delay_us(20);        
    r1 = spi_read(0);   
    r2 = spi_read(0);
    r3 = spi_read(0);
   cs=1;
Sum = (r1<<16)+(r2<<8)+r3;
return Sum;
}else goto l1;}

static unsigned int32 Middle_Sum (char n){
unsigned int32 a1 = 0;
unsigned int32 a2 = 0;
int i;
   for(i=0;i<n;i++){
   a1 = Adc_Rdata();
   a2 = a1+a2;}
   a2=a2/n;
return a2;}

static unsigned int32 AdcChData (char Ch){
unsigned int32 r1,r2,r3;
unsigned int32 Sum;
cs =0;
   delay_us(20);
   Wrreg(MUX, Ch);
   delay_us(20);
cs=1;
    Adc_Rdata();
    Adc_Rdata();
    Adc_Rdata();
    Adc_Rdata();
   Sum = Middle_Sum(5);
return Sum;}


static u16 powr (char n){
char a = 1;
Return (a<<n);
}


//---------------------------------------------------------------

void main()
{
 u8 j=0;
 char buf1[8],b;
 int1 EEWrFl=0;
 unsigned int32 Vin;
 unsigned int32 Mid;
 U16 t, t1, t2,tr;
 unsigned int32 LSB_weight = 149;// нВ
 
 //LSB_weight = 0,298023223876953125 мкВ = 298 нВ
 
//Sum = (r1<<16)+(r2<<8)+r3;
 
 U8 dt = 2,CRC1=0xFF,CRC2=0xFF;
 
   SMP = 1; // стробирование входных данных по cпадающему фронту
   CKE = 0;//необходимая полярность SCK
   CKP = 0; // необходимая полярность SCK
   
   setup_wdt(WDT_OFF);
   setup_timer_0(RTCC_INTERNAL);
   setup_timer_1(T1_INTERNAL|T2_DIV_BY_4);
   setup_timer_2 ( T2_DIV_BY_4, 1, 1);
   //setup_timer_3(T3_INTERNAL|T3_DIV_BY_4);
   setup_comparator(NC_NC_NC_NC);
   setup_vref(FALSE);

 setup_spi(spi_master | spi_l_to_h | SPI_CLK_T2);

   TRA0 = 1;//на вход
   TRA1 = 1;
   TRA2 = 1;
   TRA3 = 1;
   TRA4 = 0;
   TRA5 = 0;//вых
   TRC3= 0;
   TRC4=1;
   TRC6=0;
   TRC7=1;
     //xmit=PIN_C6,rcv=PIN_C7
 
  DSYNC = 1;
  
   
   //TRISC=0b11101111;
   TRC5=0;
   TRISD=0b00000000;
   TRISB=0b11110110;   //rb7-rb4 как входы
   TRISE=0b00000000;   //E.0 - вых
   CS = 1;

   LCDInit(); 
   
  /*  
     LCDClear();
     LCDSetCursor(0x0);
    LCDMsg("Reading data ");
    LCDSetCursor(0x40);
    LCDMsg("from EEPROM...");
    
    for (j=0;j<5;j++)
          buf1[j]=read_eeprom (j);
       crc1=CRC8(buf1,3);
       crc2=buf1[3];
       if(crc1==crc2){    
    
      //delay_ms(500);
      LCDMsg("OK");
      tmax=buf1[0];
      dt=buf1[1];
      hp=buf1[2]; 
       }else {
             LCDSetCursor(0x10);
             LCDMsg("CRC error !");
             }
    
    LCDSetCursor(0x50);
    LCDMsg("CRC1=");
    LCDPutU16(CRC1,3);
    LCDMsg("CRC2=");
    LCDPutU16(crc2,3);        
    delay_ms(1000);
    
     Delay_ms(1000);
     LCDClear();
    
    set_timer3(59285); 
    set_timer1(64910); 
    enable_interrupts(INT_TIMER1);
    enable_interrupts(INT_TIMER3);
    enable_interrupts(GLOBAL);
  */
  // LCDMsg("CRC2="); 
  
  LCDWelcome();
 // LCDMsg("Ready!");

  reset=0;
   delay_us(15);
   reset=1;
   Cs=1;
   delay_ms(1);
   
// LCDClear();
 
   AdsInit();
 
   SelfCal();

/*
    delay_us(100);
    cs=0;
    delay_us(20);
   WrReg(SETUP,0b00011110);  
    delay_us(20);
    cs=1;
    
    
   delay_us(100);
    cs=0;
    delay_us(20);
    WrReg(MUX,0x01);
    delay_us(20);
    cs=1;
    
    delay_us(100);
    cs=0;
    delay_us(20);
    WrReg(ACR,0x03);  
    delay_us(20);
    cs=1;
    
  */
    
   LCDclear();
   
   
   while(true){
   
//--------------------- 1 датчик-------------------
  LCDSetCursor(0x0C);
  LCDputCH('*');
  Mid = AdcChData(0x10);
  Vin = (Mid*LSB_weight)/(1000*powr(PGA));
  LCDSetCursor(0x00);
  LCDMsg("CTP:");
  LCDSetCursor(4);
  lcdPutU32(Vin,4);
  LCDMsg(" uV  ");
  Printf("%Lu\n",Vin);
//------------------------------------------------
  //Printf("%u\n",1);
  //Printf("B\n\r");
//--------------------- 2 датчик-------------------
   LCDSetCursor(0x4C);
   LCDputCH('*');
   Mid = AdcChData(0x32);
   Vin = (Mid*LSB_weight)/(1000*powr(PGA)); 
   LCDSetCursor(0x40);
   LCDMsg("C");
   LCDputCH(0xA8);
   LCDMsg(" :");
   lcdPutU32(Vin,4);
   LCDMsg(" uV  ");
   Printf("%Lu\n",Vin);
//------------------------------------------------  
  
//--------------------- 3 датчик-------------------
  LCDSetCursor(0x1C);
  LCDputCH('*');
  Mid = AdcChData(0x54);
  Vin = (Mid*LSB_weight)/(1000*powr(PGA));  
  LCDSetCursor(0x10);
   LCDputCH(0xA8);
  LCDMsg('E');
  LCDMsg("P:");
  lcdPutU32(Vin,4);
  LCDMsg(" uV  ");
  Printf("%Lu\n",Vin);
//------------------------------------------------ 
  
  
//--------------------- 4 датчик------------------- 
  LCDSetCursor(0x5C);
  LCDputCH('*');
  Mid = AdcChData(0x76);
  Vin = (Mid*LSB_weight)/(1000*powr(PGA));
  LCDSetCursor(0x50);
  LCDMsg("CO");
  LCDputCH(0xA7);
  LCDMsg(":");
  lcdPutU32(Vin,4);
  LCDMsg(" uV  ");
  //LCDSetCursor(7);
  Printf("%Lu\n",Vin);
//------------------------------------------------ 


  /*
  PbFl1=Pbfl; // для синхронности изменения MenuItem и PbFl
   switch (MenuItemNum){
      case 0:
      if(Pbfl1){
         Pbfl=0;
         delay_ms(1);
         LCDClear();
      }
   //нулевой пункт меню
  //****************Первый датчик******************
   ADC_value=ADC_read(0);
   LCDSetCursor(0x0); 
   t = ADC_value*2;
   t1 = t/10;
   t2 = t - t1*10;
   LCDMsg("t1=");
   LCDPutU16(t1,3);//знака
   LCDMsg('.');
   LCDPutU16(t2,1);
   LCDPutCh(0xEF);
   LCDMsg("C   HP"); 
//****************второй датчик******************
   ADC_value=ADC_read(1); // установка порта АЦП
   LCDSetCursor(0x40); 
   t = ADC_value*2;
   tr=t;
   t1 = t/10;
   t2 = t - t1*10;
   LCDMsg("t2=");
   LCDPutU16(t1,3);
   LCDMsg('.');
   LCDPutU16(t2,1);
   LCDPutCh(0xEF);
   LCDMsg("C  ");
   LCDPutU16(hp,3);
   LCDMsg('%');
   
   //****************третий датчик******************
   ADC_value=ADC_read(2);
   LCDSetCursor(0x10); 
   t = ADC_value*2;
   t1 = t/10;
   t2 = t - t1*10;
   LCDMsg("t3=");
   LCDPutU16(t1,3);
   LCDMsg('.');
   LCDPutU16(t2,1);
   LCDPutCh(0xEF);
   LCDMsg("C  ");
   LCDMsg(" dt");
   
   //**********************************
   LCDSetCursor(0x50); 
   LCDMsg("tmax=");
   LCDPutU16(tmax,3);//знака.разряда
   LCDPutCh(0xEF);
   LCDMsg("C  ");
 //  LCDMsg("dt=");
   LCDPutU16(dt,2);//знака.разряда
   LCDPutCh(0xEF);
   LCDMsg('C');
   
  //**************флаг максимальн.температуры
   if (tr>=tmax*10){
      tmaxfl = 0;
      dtfl=0;
      }else  tmaxfl=1;     
         if(tr<=(tmax*10-dt*10)) dtfl = 1;
         
      break;
      case 1:
      if(Pbfl1){
         Pbfl=0;
         LCDClear();
      }
         LCDSetCursor(0x0);
         LCDMsg("tmax=");
         LCDPutU16(tmax,3);
         LCDPutCh(0xEF);
         LCDMsg('C');
         
          //увеличение tmax
  if (b_push[1]){
       b_push[1]=0;
        tmax++; 
  }
  //уменьшение tmax
  if (b_push[3]){
       b_push[3]=0;
        tmax--; 
  }
  if(tmax<1)tmax = 1;
  if(tmax>150)tmax = 150;
  
      break;
      case 2:
       if(Pbfl1){
         Pbfl=0;
         LCDClear();
      }
         LCDSetCursor(0x0);
         LCDMsg("dt=");
         LCDPutU16(dt,2);
         LCDPutCh(0xEF);
         LCDMsg('C');
         
           //увеличение dt
  if (b_push[1]){
       b_push[1]=0;
        dt++; 
  }
  //уменьшение dt
  if (b_push[3]){
       b_push[3]=0;
        dt--;
  }
  if(dt<1)dt = 1;
  if(dt>50)dt = 50;
         
      break;
      case 3:
      if(Pbfl1){
         Pbfl=0;
         LCDClear();
      }
         LCDSetCursor(0x0);
         LCDMsg("HP=");
         LCDPutU16(hp,3);
         LCDMsg('%');
         
       //увеличение Hp
  if (b_push[1]){
       b_push[1]=0;
        hp++; 
  }
  //уменьшение Hp
  if (b_push[3]){
       b_push[3]=0;
        hp--;
       
  }
   if(hp<1)hp = 1;
  if(hp>100)hp = 100;
         
       break;
       case 4:
      if(Pbfl1){
         Pbfl=0;
         LCDClear();
      }
     if (b_push[1]){
       b_push[1]=0;
        henfl=1;//Heater en ;
       
  }
  //уменьшение Hp
  if (b_push[3]){
       b_push[3]=0;
       henfl=0;//Heater Dis ;
          
  }  
      LCDSetCursor(0x0);
     if(henfl)  LCDMsg("Heater ON "); else LCDMsg("Heater OFF");
         
      break;
      case 5:
        if(Pbfl1){
           Pbfl=0;
           LCDClear(); 
         LCDSetCursor(0x0);
         LCDMsg("Write current "); 
         LCDSetCursor(0x40);
         LCDMsg("parameters to   ");
         LCDSetCursor(0x10);
         LCDMsg("EEPROM ?");  
         LCDSetCursor(0x50);
         LCDMsg(" NO  ");
       }
             
     if (b_push[1]){
       b_push[1]=0;
       EEWrFl=1;
       LCDSetCursor(0x50);
       LCDMsg(" YES ");
      }
    if (b_push[3]){
       b_push[3]=0;
       EEWrFl=0;
       LCDSetCursor(0x50);
       LCDMsg(" NO  ");
    }       
      break;
      case 6:
      if(Pbfl1){
           Pbfl=0;
        // LCDClear();
      }
         if(EEWrFl){
           LCDClear();
           LCDSetCursor(0x0);
           LCDMsg("Writing data  ");
           LCDSetCursor(0x40);
           LCDMsg("to EEPROM... ");
           buf1[0]=tmax;
           buf1[1]=dt;
           buf1[2]=hp;
           buf1[3]=CRC8(buf1,3);//Вычисление контрольной суммы
           disable_interrupts(GLOBAL);
           //устанавливать адрес последней ячейки EEPROM на неиспользуемую область!!!
            for (j=0;j<5;++j)
              write_eeprom (j, buf1[j]);
              enable_interrupts(GLOBAL);
           EEWrFl=0;
           
           //delay_ms(500);
           //LCDClear();
           LCDMsg("OK" );
           LCDSetCursor(0x10);
           LCDMsg(" CRC=" );
           LCDPutU16(buf1[3],3);
           delay_ms(500);
         }
          MenuItemNum=0;
          PbFl=1;
         
         break;
     
      default:
      MenuItemNum=0;   
         
    }
*/
  }

}
