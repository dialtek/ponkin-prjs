// Измеритель магнитной индукции 1.3 // последние изменения 29.10.14

#include <18F25K80.h>
#device adc=16
#include <stdio.h>
#FUSES NOWDT                    //No Watch Dog Timer
//#FUSES WDT   //Watch Dog Timer
#FUSES SOSC_DIG   //Digital mode, I/O port functionality of RC0 and RC1
//#FUSES WDT4096   //Watch Dog Timer uses 1:32768 Postscale
#FUSES NOXINST                  //Extended set extension and Indexed Addressing mode disabled (Legacy mode)
#FUSES HSM   //High speed Osc, medium power 4MHz-16MHz                                         
#FUSES NOBROWNOUT               //No brownout reset
//#FUSES WDT_NOSLEEP              //Watch Dog Timer, disabled during SLEEP
#FUSES PLLEN                    //4X HW PLL enabled
//#FUSES NOPLLEN                    //4X HW PLL enabled

#use delay(clock=40M)

#use I2C(master, scl=PIN_C3, sda=PIN_C4, fast = 400000)  //sets the target speed to 400 KBSP
#use rs232(uart1,baud=9600,parity=N,xmit=PIN_C6,rcv=PIN_C7,bits=8)

#BYTE TRISA = 0xF92
#BYTE TRISB = 0xF93
#BYTE TRISC = 0xF94 

#BYTE PORTA = 0xF80
#BYTE PORTB = 0xF81
#BYTE PORTC = 0xF82 
         
#BYTE WDTCON = 0xFD1       //wdt control reg
#BYTE PIR1 = 0xF9E         // mssp int flag status
#BIT SSPIF = PIR1.3

#BYTE ADCON0 = 0xFC2 
#BYTE ADCON1 = 0xFC1 
#BYTE ODCON = 0xF91 

#BIT VNCFG = ADCON1.3
#BIT VCFG0 = ADCON1.4
#BIT VCFG1 = ADCON1.5
 
#BIT RA0 = PORTA.0
#BIT RA1 = PORTA.1
#BIT RA2 = PORTA.2
#BIT RA3 = PORTA.3
#BIT RA4 = PORTA.4
#BIT RA5 = PORTA.5

#BIT RB0 = PORTB.0

#BIT TRB0 = TRISB.0
#BIT TRB1 = TRISB.1 // lcd db5
#BIT TRB2 = TRISB.2 //lcd db4
#BIT TRB3 = TRISB.3  //lcd e
#BIT TRB4 = TRISB.4  // lcd rw
#BIT TRB5 = TRISB.5 // lcd rs

#BIT TRA5 = TRISA.5
#BIT TRA4 = TRISA.4
#BIT TRA3 = TRISA.3
#BIT TRA2 = TRISA.2
#BIT TRA1 = TRISA.1
#BIT TRA0 = TRISA.0

#BIT TRC0 = TRISC.0
#BIT TRC1 = TRISC.1
#BIT TRC2 = TRISC.2 //lcd db7
#BIT TRC3 = TRISC.3 // 
#BIT TRC4 = TRISC.4
#BIT TRC5 = TRISC.5 //lcd db6
#BIT TRC6 = TRISC.6
#BIT TRC7 = TRISC.7

#BIT RC0 = PORTC.0
#BIT RC1 = PORTC.1

#BIT RC3 = PORTC.3
#BIT RC4 = PORTC.4
#BIT RC6 = PORTC.6
#BIT RC7 = PORTC.7

#BIT DB4 = PORTB.2
#BIT DB5 = PORTB.1
#BIT DB6 = PORTC.5
#BIT DB7 = PORTC.2

#BIT LCD_RS = PORTB.5 
#BIT LCD_RW = PORTB.4
#BIT LCD_E = PORTB.3

typedef unsigned int32 U32;
typedef int16 U16;
typedef signed int16 S16;
typedef int8 U8;
typedef signed int32 S32;

static U8 buf;

#BIT buf4=buf.4
#BIT buf5=buf.5
#BIT buf6=buf.6
#BIT buf7=buf.7

#DEFINE DRDY RB0

#define one   0x00
#define two   0x40
#define three 0x10
#define four  0x50

       unsigned int1 int_fl = 0,zero_set1=0;
       static U8 ff1=0;
       unsigned int1 fl2=0, menufl1 =0, menufl2 =0, menufl3 =0, menufl4 =1; //флаги нажатия кнопок
       static U8 TMR0fl=0, MenuItemNum=0;
       static U8 RXd_buf=0;

 
char  ConfigRegA = 0x00, ConfigRegB = 0x01, ModeReg = 0x02, xMSB = 0x03, xLSB = 0x04,
      zMSB = 0x05, zLSB = 0x06,yMSB = 0x07,yLSB = 0x08,StatReg = 0x09, idRegA = 0x10,
      idRegB = 0x11, idRegC = 0x12;
      
      signed int16 SumX=0; // переменные для осн. измерения
      signed int16 SumY=0;
      signed int16 SumZ=0;
       
      signed int16 SumX0=0; // для уст. 0
      signed int16 SumY0=0;
      signed int16 SumZ0=0;
      
      signed int32 average_Xg=0; 
      signed int32 average_Yg=0;
      signed int32 average_Zg=0;
             
      unsigned int16 Xh = 0;
      unsigned int8 Xl = 0;
      unsigned int16 Yh = 0;
      unsigned int8 Yl = 0;
      unsigned int16 Zh = 0;
      unsigned int8 Zl = 0;

      float Xd = 0;
      float Yd = 0;
      float Zd = 0;
      
      S32 average_X, average_Y, average_Z;

      U8 aver_count = 0;
             
      U8 t_out[4]={0,0,0,0};
      U8 b_hold[4]={0,0,0,0};
      U8 b_push[4]={0,0,0,0};
       
       
/***************** LCD functions *****************/

static void LCDWriteNibble(unsigned char uc) /* RS must be set/reset before calling */
{                                           
  uc=uc << 4; /* Align with bits 7-4*/
  LCD_RW=0;
  buf=uc;
    DB4=buf4;
    DB5=buf5;
    DB6=buf6;
    DB7=buf7;
  delay_us(200);
  LCD_E=1;
  delay_us(10);
  LCD_E=0;
  delay_us(200);
  LCD_RW=1;   
}

static void LCDWriteData(unsigned char uc)
{
  
    LCD_RS=0;
    delay_us(300);
    LCD_RS=1;
    LCD_RW=1;// Восстановление байтовой синхронизации
    LCDWriteNibble(uc>>4);//двиг разрядов старших
    LCDWriteNibble(uc);
  
}

static void LCDCommand(unsigned char uc)
{
    LCD_RS=0; /* Instruction mode */
    delay_us(150);
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
  //delay_ms(2000);
  LCDWriteNibble(3);
  Delay_us(200);
  //Delay_ms(1);
  LCDWriteNibble(3);
  //Delay_ms(1);
  Delay_us(200);
  LCDWriteNibble(3);
  //Delay_ms(1);
  Delay_us(200);
  LCDWriteNibble(2);
  //Delay_ms(1);
  Delay_us(200);
  
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
  delay_ms(10);
  //Delay_ms(20);
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
    LCDClear();
    LCDMsg("  MultiSensor");
    LCDSetCursor(0x40);
    LCDMsg("Magnitometer 1.3");
    LCDSetCursor(0x50);
    LCDMsg(" ___LHEP_JINR___");
    Delay_ms(1000);
    LCDClear();   
}

/***********************************************/

//кнопки
  static U8 PBScan(U8 pb){
// сканирование кнопок
//pb-номер кнопки(0-3);
 U8 uc=1;
   uc=uc<<(4+pb);
   buf=uc;
   //устанавливаем в 1 соотв. линию
   
    DB4=buf4;
    DB5=buf5;
    DB6=buf6;
    DB7=buf7;
    
    delay_us(100);
    //RA2=rc1;
   return  RC1;
      
}

//****************** Sensor func ***********************************
 
  static void SensWrData(unsigned int8 Adr, Data){
   
   i2c_start();
   i2c_write(0x3C);
                        // The default (factory) HMC5883 7-bit slave address 
                        // is 0x3C for write operations, or 0x3D for read operations.
   i2c_write(Adr);
   i2c_write(Data);
   i2c_stop();
   }
   
  static char SensRdData(char Adr){
   
   char Data = 0;
   
   i2c_start();  
   i2c_write(0x3C); // The default (factory) HMC5883 7-bit slave address 
                    // is 0x3C for write operations, or 0x3D for read operations.
   i2c_write(Adr); // pointer 
 
   i2c_stop();
   delay_us(10);
    i2c_start();
   i2c_write(0x3D); //i2c Read
   delay_us(10);
   Data = i2c_read();
   delay_us(10);
   Data = i2c_read();
   delay_us(10);
   i2c_stop();
   
   return Data;
   }
    
  static void SensInit (){  
   //SensWrData(ConfigRegA,0x50); //  F = 15 Hz + ??????. ?? 4 ????????
   //SensWrData(ConfigRegA,0x44); //  F = 3 Hz + ??????. ?? 4 ????????
   //SensWrData(ConfigRegA,0x08); //  F = 3 Hz/1
   //SensWrData(ConfigRegA,0x14); //  F = 30 Hz/1
   //SensWrData(ConfigRegA,0x70); //  F = 15 Hz/8
   //SensWrData(ConfigRegA,0x50); //  F = 15 Hz/4
   SensWrData(ConfigRegA,0x18); //  F = 75 Hz/1
   SensWrData(ConfigRegB,0xE0); // range = +/- 8.1 Ga
   SensWrData(ModeReg,0x00); // continuous measurment mode 
   }

  static signed int16 SelfCal(){

   unsigned int16 Xh = 0;
   unsigned int8 Xl = 0;
   unsigned int16 Yh = 0;
   unsigned int8 Yl = 0;
   unsigned int16 Zh = 0;
   unsigned int8 Zl = 0;

     SensInit();
     delay_us(10);
   if (int_fl){        
      i2c_start();  
      i2c_write(0x3C); // The default (factory) HMC5883 7-bit slave address 
                    // is 0x3C for write operations, or 0x3D for read operations.
      i2c_write(0x03); // pointer 
      i2c_stop();
      delay_us(10);
   
      i2c_start();
      i2c_write(0x3D); //i2c Read
 
      Xh = i2c_read();   // X MSB
      Xl = i2c_read();   // X LSB
      SumX = (Xh<<8)|Xl;   //?????????????? ???????? ????????. ??? ?
      Yh = i2c_read();  // Y MSB
      Yl = i2c_read();  // Y LSB
      SumY = (Yh<<8)|Yl;   //?????????????? ???????? ????????. ??? Y
      Zh = i2c_read();  // Z MSB
      Zl = i2c_read();  // Z LSB
      SumZ = (Zh<<8)|Zl;  //?????????????? ???????? ????????. ??? Z
      i2c_read();    //if adress pointer = 08, adress pointer = 03
      i2c_stop();
      }
        
   delay_us(10);
  // SensWrData(ConfigRegA,0x00); // selftest end        
        //Printf("X= %Ld ",SumX);
    //Printf("Y= %Ld ",SumY);
    //Printf("Z= %Ld\n\r",SumZ);
    //restart_wdt();
   return 1;
   }

  static void SensRdAll(){
            
   if (fl2){ // кнопка уст.0 нажата
               // сброс флага "уст.0"
              LCDclear();
              Lcdsetcursor(0);
              LcdMsg("ZERO POINT SETUP");    
              SumX0=SumX;
              SumY0=SumY;
              SumZ0=SumZ;  
              delay_ms(1000);
              fl2=0;
              }
      
   average_Zg = (average_Zg/10)-SumZ0;
   average_Yg = (average_Yg/10)-SumY0;
   average_Xg = (average_Xg/10)-SumX0;
   
   //y = (8.1*x)/2048; 8.1/2048 = 0.0039550781252
   
   Xd = average_Xg * 0.0039550781252;
   Yd = average_Yg * 0.0039550781252;
   Zd = average_Zg * 0.0039550781252;
   
   Printf("x%05Ld\n",average_Zg);
   Printf("y%05Ld\n",average_Yg);
   Printf("z%05Ld\n",average_Xg);

   LcdSetCursor(0x00);
   LcdMsg("MAGNET. FIELD,Gs");
   
   LcdSetCursor(0x40);
   LcdMsg("  Bx = ");
   LcdPutS16(Zd*1000,4);

   LcdSetCursor(0x10);
   LcdMsg("  By = ");
   LcdPutS16(Yd*1000,4);
  
   LcdSetCursor(0x50);
   LcdMsg("  Bz = ");
   LcdPutS16(Xd*1000,4);
         
     int_fl = false;
 } 

//******************************************************************

//================== Interrupts  ===================================

#INT_EXT
   void int0(){


   i2c_start();  
   i2c_write(0x3C); // The default (factory) HMC5883 7-bit slave address 
                       // is 0x3C for write operations, or 0x3D for read operations.
   i2c_write(0x03); // pointer 
   i2c_stop();
      
   i2c_start();
   i2c_write(0x3D); //i2c Read
      
   Xh = i2c_read();   // X MSB
   Xl = i2c_read();   // X LSB
   SumX = (Xh<<8)|Xl;   //?????????????? ???????? ????????. ??? ?                                   
   Yh = i2c_read();  // Y MSB
   Yl = i2c_read();  // Y LSB
   SumY = (Yh<<8)|Yl;   //?????????????? ???????? ????????. ??? Y
   Zh = i2c_read();  // Z MSB
   Zl = i2c_read();  // Z LSB
   SumZ = (Zh<<8)|Zl;  //?????????????? ???????? ????????. ??? Z  
   i2c_stop();

   average_X += SumX;
   average_Y += SumY;
   average_Z += SumZ;
   
   aver_count ++;
   
   if (aver_count >= 10) 
      {
        int_fl = true;
        aver_count = 0;
        
        average_Xg = average_X;
        average_Yg = average_Y;
        average_Zg = average_Z;
        
        average_X = 0;
        average_Y = 0;
        average_Z = 0;
        
      }
      
   SensWrData(ConfigRegB,0xE0); // range = +/- 8.1 Gs
   SensWrData(ModeReg,0x00);  // continuous measurment
   clear_interrupt(INT_EXT);
  }

#INT_TIMER0 
   void  TIMER0_isr(void) 
{
// прерывание каждые 0.5 сек.
tmr0fl=1;
set_timer0(60000);   

clear_interrupt(int_timer0);
}

#INT_TIMER3
   void  TIMER3_isr(void) 
{
//****************обработка нажатия кнопок*****************
char i;
for(i=0; i<4; ++i){
//нажата ли кнопка?

 if (PBScan(i)){
  //кнопка нажата
   //порог подавления дребезга достигнут?
   if(t_out[i]>=10) {
          //да
          //флаг "удерживается" установлен?
          if(!b_hold[i]){
            //нет
            b_hold[i]=1;//установить флаг "удерживается"
            b_push[i]=1;//установить флаг "нажато"
           }
          //да
       }
      else
      //порог подавления дребезга не достигнут
      {
      ++t_out[i];//инкремент переменной подавления дребезга
      }
   }
   else
   // кнопка не нажата
   {
   t_out[i]=0; //обнуление переменной подавления дребезга
   b_hold[i]=0; //сброс флага "удерживается"
   }
} //for   

//b_push[0]=1;
 //***********кнопки обработаны****************************

// прерывание каждые 100  мксек.
set_timer3(64535);  



clear_interrupt(int_timer3);
}

#INT_RDA
   void UART_RXd_isr(void){

RXd_buf = getc();          // Чтение входных данных....
                           // без чтения, программа не выходит из обработчика
if (RXd_buf == 'z')        // ОБЯЗАТЕЛЬНОЕ совпадение символов уст. 0... FTDI шлет мусор при откл. программы ПК
{
menufl1 = 0;
menufl2 = 0;
menufl3 = 0;
fl2=0;

//b_push[0] = 1;
b_push[1] = 1;
b_push[2] = 1;
b_push[3] = 1;
zero_set1 = 1;
}

clear_interrupt(INT_RDA);  // сброс флага прерывания
}

//==================================================================

 //встроенноый АЦП
  static void Set_ADC_Ch(U8 Ch){
// Установка канала АЦП
//Встроенная функция не раб.
ADCON0=ADCON0 & 0x3;
ADCON0=ADCON0 | (Ch << 2);
}

//===================================================================
  void main()
  
{
  U16 i=0,zero=8384;

  S32 buf=0,buf1=0,sum=0;
  U8 ADCh=0;
     
   TRC0 = 0;
   
   TRA2 = 0;    
   TRC3 = 1;
   TRC4 = 1;  //The user must configure these pins as inputs by setting
              //the associated TRIS bits. 
   TRC6=0;
   TRC7=1;  //xmit=PIN_C6,rcv=PIN_C7
   
   TRB0 = 1; // DRDY pin
   
   TRB2 = 0; //кнопки
   TRB1 = 0;   
   TRC2 = 0;
   TRC5 = 0;
   
   TRB5 = 0; //LCD_RS = PORTB.5 
   TRB4 = 0; //LCD_RW = PORTB.4
   TRB3 = 0; //LCD_E = PORTB.3
   
   TRC1 = 1;// сканер кнопок
   
   //конфигурация VREF ADC
   //Vref+
   //VCFG0=1;//10 - ext.ref на RA3; 00-Avdd
   //VCFG1=0;
   //Vref-
   //VNCFG=0;// 0-gnd 1-Ext.ref
   //ODCON=0;
   
   EXT_INT_EDGE(L_TO_H);

   //setup_timer_0(RTCC_INTERNAL|RTCC_DIV_256);
   
   enable_interrupts(GLOBAL);
   //enable_interrupts(INT_TIMER0);
   enable_interrupts(INT_TIMER3);
   enable_interrupts(INT_EXT);
   enable_interrupts(INT_RDA);
   
   //set_timer0(60000); 

  LCDInit();
  LcdWelcome();
  
  /*
  lcdsetcursor(one);
  lcdMsg("     SELECT");
  lcdsetcursor(two);
  lcdMsg("    MAGNETIC");
  lcdsetcursor(three);
  lcdMsg("   SENSOR TYPE");
  */
 
  SensInit();
  //SelfCal();

   while(TRUE)
   {
     for(i=0; i<4; ++i){
//нажата ли кнопка?

 if (PBScan(i)){
  //кнопка нажата
   //порог подавления дребезга достигнут?
   if(t_out[i]>=10) {
          //да
          //флаг "удерживается" установлен?
          if(!b_hold[i]){
            //нет
            b_hold[i]=1;//установить флаг "удерживается"
            b_push[i]=1;//установить флаг "нажато"
           }
          //да
       }
      else
      //порог подавления дребезга не достигнут
      {
      ++t_out[i];//инкремент переменной подавления дребезга
      }
   }
   else
   // кнопка не нажата
   {
   t_out[i]=0; //обнуление переменной подавления дребезга
   b_hold[i]=0; //сброс флага "удерживается"
   }
} //for   

 //***********кнопки обработаны****************************

  if (int_fl) SensRdAll();               // чтение и отсылка на пк
  
  //Кнопка 3 - уст. 0
  if (b_push[3]){ b_push[3]=0; fl2=1; }  // флаг установки нуля

/*
   //Кнопка 0
  if (b_push[0]){
   zero_set1 = 1;
   b_push[0]=0;
   menufl2 = 1;
   menufl1 = 0;
   lcdclear();
  }
  
*/  
  
/*
   //Кнопка 1
  if (b_push[1]&zero_set1){
  
       b_push[1]=0;

       menufl3=1;
       lcdsetcursor(0);
       LcdMsg("ZERO POINT SETUP"); 
       zero=buf1;
       Delay_ms(1000);
       menufl2=1;

  } 
*/ 

/*
   //кнопка 2    
  if (b_push[2]){
  zero_set1=0;
  if(menufl2){
  menufl2=0;
  lcdclear();
  }
       b_push[2]=0;
       menufl1=1;
       lcdClear();
  } 

*/

/*
  if(menufl1){
  if (menuFl2){
  }
   menufl3=1;
   if (int_fl) SensRdAll();   
  }
*/ 

/*
  if(tmr0fl&&menuFl2){
   menufl1=0;
   tmr0fl=0;// флаг TMR0,появляется каждые 0.3 сек.
   sum=0;
       Set_ADC_Ch(8);
       delay_us(50);
         for(i=0;i<100;i++){
    buf=read_ADC();
   if(buf < 0)buf=0;
     if (buf > 4095) buf=4095;
     
      sum=sum+buf;
}
//если сигнал на входе АЦП отрицательный, то выходной код - 4095!
buf=sum/100;
//Vref=4.096V
// 25 mV / Gauss
// 1mV - 0.04Gs

buf=buf*4;
buf1=buf;
LCDSetCursor(0x00);
LCDMsg(" MAGN.FIELD-1AX ");
//LCDSetCursor(0x40);
//LCDMsg("     1-AX.");
buf=buf-zero;//установка нуля
LCDSetCursor(0x10);
LCDMsg("    ");
LCDPutS16(buf,4);// Функция изменена !!!!
//LCDPutU16(buf,4);
LCDMsg(" Gs");  
     
  }
*/         
  
     }

  }

