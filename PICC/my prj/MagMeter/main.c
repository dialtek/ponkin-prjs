#include <main.h>
#include <stdio.h>

#BYTE PORTA = 0xF80
#BYTE PORTB = 0xF81
#BYTE PORTC = 0xF82 

#BYTE ADCON0 = 0xFC2 
#BYTE ADCON1 = 0xFC1 
#BYTE ODCON = 0xF91 
#BYTE TRISA = 0xF92
#BYTE TRISB = 0xF93
#BYTE TRISC = 0xF94 

#BIT VNCFG = ADCON1.3
#BIT VCFG0 = ADCON1.4
#BIT VCFG1 = ADCON1.5

#BIT RA2 = PORTA.2
//#BIT TRA2 = TRISA.2
#BIT TRC2 = TRISC.2

#BIT RC3 = PORTC.3
#BIT TRA2 = TRISA.2

#BIT LCD_RS = PORTB.5
#BIT LCD_RW = PORTB.4
#BIT LCD_E = PORTB.3

//#BIT RB4 = PORTB.4
//#BIT RB5 = PORTB.5
//#BIT PORTB6 = PORTB.6
//#BIT PORTB7 = PORTB.7

#BIT DB4 = PORTB.2
#BIT DB5 = PORTB.1
#BIT DB6 = PORTC.5
#BIT DB7 = PORTC.4

typedef unsigned int32 U32;
typedef signed int32 S32;
typedef int16 U16;
typedef signed int16 S16;
typedef int8 U8;

// Incremented by timer 0 interrupt
static U8 TMR0fl=0;

static U8 buf;
#BIT buf4=buf.4
#BIT buf5=buf.5
#BIT buf6=buf.6
#BIT buf7=buf.7

/***************** LCD functions *****************/

static void LCDWriteNibble(unsigned char uc) /* RS must be set/reset before calling */
{ 
 //Запись половины байта
  uc=uc << 4; // Align with bits 7-4
  LCD_RW=0;
  
  buf=uc;
  DB4=buf4;
  DB5=buf5;
  DB6=buf6;
  DB7=buf7;
  delay_us(1);
  LCD_E=1;
  delay_us(2);
  LCD_E=0;
  delay_us(2);
  //LCD_RW=1; !!!! Убрать для MT16S2H !!!!!!!
  
  
}

static void LCDWriteData(unsigned char uc)
{
  
    LCD_RS=0;
     delay_us(50);
    LCD_RS=1;
    LCD_RW=1;// Восстановление байтовой синхронизации
    LCDWriteNibble(uc>>4);
    LCDWriteNibble(uc);
  
}


static void LCDCommand(unsigned char uc)
{
  
    LCD_RS=0; /* Instruction mode */
    delay_us(50);
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
    Delay_ms(2);
  
}

static void LCDInit(void)
// MT16S2H init function
{
  LCD_E=0;
  LCD_RS=0;
   
  Delay_ms(200); //1000
  
  LCDWriteNibble(3);
  Delay_us(200);
  LCDWriteNibble(3);
  Delay_us(200);
  LCDWriteNibble(3);
  Delay_us(200);
  LCDWriteNibble(2);
  Delay_us(200);
 
 // LCDCommand(0x28);//установка разрядности интерфейса(4 бит) и страницы знакогенератора
 //  LCDCommand(0b00101000);//страница 0  
// LCDCommand(0b00101010);//страница 1 WIN CP1261 русские буквы 
  LCDCommand(0x2A);//страница 1 WIN CP1261 русские буквы 
  
  LCDCommand(0x08);// Выключить дисплей, выключить курсор, выключить моргание курсора
  //LCDCommand(0x0F);// Включить дисплей, включить курсор, включить моргание курсора
  //LCDCommand(0x06);// Курсор будет двигаться вправо при выводе текста
  LCDCommand(0x1);// Очистка экрана и перемещение курсора в первую позицию 
   delay_ms(2);
  LCDCommand(0x06);// Курсор будет двигаться вправо при выводе текста 
  LCDCommand(0b00001111);

 // LCDCommand(0x00);//Установка адреса DRAM
  delay_ms(10);
  
 }
 
 
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
      LCDPutCh('.');//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
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
 
  
    U16 u16a;
    LCDClear();
    LCDMsg("Цифровой  ");
    LCDSetCursor(0x40);
    LCDMsg("гауссметр V1.00");
    Delay_ms(2000);
    LCDClear();
  
}

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
   return RC3;
      
}


static void Set_ADC_Ch(U8 Ch){
// Установка канала АЦП
//Встроенная функция не раб.
ADCON0=ADCON0 & 0x3;
ADCON0=ADCON0 | (Ch << 2);
}

#int_TIMER0
void  TIMER0_isr(void) 
{
// прерывание каждые 0.5 сек.
tmr0fl=1;
set_timer0(60000);   

clear_interrupt(int_timer0);
}


void main()
{
U8 t_out[4]={0,0,0,0};
U8 b_hold[4]={0,0,0,0};
U8 b_push[4]={0,0,0,0};
U8 ADCh=0;
U16 i=0,zero=8384;

S16 b,c;
S32 buf=0,buf1=0,sum=0;

   setup_adc(ADC_CLOCK_DIV_32|ADC_TAD_MUL_16|VREF_4V096);// не раб.
   setup_adc_ports(sAN1);// не раб.
   setup_timer_4(T4_DISABLED,0,1);
   setup_comparator(NC_NC_NC_NC);// This device COMP currently not supported by the PICWizard

  
   //конфигурирование PWM
   setup_timer_2(T2_DIV_BY_1 ,255,1);// PWM freq 39.06 kHz
   setup_ccp2(CCP_PWM);
  
  set_pwm2_duty(800);
  
   setup_timer_0(RTCC_INTERNAL|RTCC_DIV_256);
   set_timer0(60000);   

  
  

//конфигурация VREF ADC
//Vref+
VCFG0=1;//10 - ext.ref на RA3; 00-Avdd
VCFG1=0;
//Vref-
VNCFG=0;// 0-gnd 1-Ext.ref
   




   TRA2=0;
   TRC2=0;
ODCON=0;   
TRISB=0b00000001;
TRISC=0b10001001;
LCDInit();

LCDWelcome();

LCDClear();
LCDSetCursor(0x0);

enable_interrupts(INT_TIMER0);
enable_interrupts(GLOBAL);


while(true){
 restart_wdt();
 if(tmr0fl){
 tmr0fl=0;// флаг TMR0,появляется каждые 0.3 сек.
  //Измерение B
  Set_ADC_Ch(1);
  LCDSetCursor(0x0);
  LCDMsg("B=");
 
  //усреднение результатов АЦП
   sum=0;
  for(i=0;i<100;i++){
    buf=read_ADC();
   if(buf < 0)buf=0;
     if (buf > 4095) buf=4095;
      sum=sum+buf;;
}
//если сигнал на входе АЦП отрицательный, то выходной код - 4095!!!!!!!!!!!!!
buf=sum/100;
//Vref=4.096V
// 25 mV / Gauss
// 1mV - 0.04Gs

buf=buf*4;
buf1=buf;

buf=buf-zero;//установка нуля
LCDPutS16(buf,4);// Функция изменена !!!!
LCDMsg(" Гаусс");

LCDSetCursor(0x40);
LCDMsg("Измер.");
/*
 //Измерение T
 //Датчик - LM35 
 // +10мВ/Градус
  Set_ADC_Ch(0);
  //усреднение результатов АЦП
   sum=0;
  for(i=0;i<100;i++){
    buf=read_ADC();
   if(buf < 0)buf=0;
     if (buf > 4095) buf=4095;
      sum=sum+buf;;
}
//если сигнал на входе АЦП отрицательный, то выходной код - 4095!!!!!!!!!!!!!
buf=sum/100;
 LCDSetCursor(0x40);
 LCDMsg("T=");
 LCDPutS16(buf,4);// Функция изменена !!!!
 LCDMsg(" C");
 */
 
 
}
//****************обработка нажатия кнопок*****************

for(i=0; i<4; ++i){
//нажата ли кнопка?
 if (PBScan(i)){
  //кнопка нажата
   //порог подавления дребезга достигнут?
   if(t_out[i]==20) {
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
 //***********кнопки обработаны***********************
  //Кнопка 0
  if (b_push[0]){
       b_push[0]=0;
       LCDSetCursor(0x40);
       LCDMsg("Уст. 0");
       zero=buf1;
       Delay_ms(700);
       LCDSetCursor(0x40);
       LCDMsg("      ");
  }
      
   //Кнопка 1
  if (b_push[1]){
       b_push[1]=0;
       LCDSetCursor(0x40);
       LCDMsg("Стоп  ");
       Disable_interrupts(INT_TIMER0);
  } 
  
   //Кнопка 2
  if (b_push[2]){
       b_push[2]=0;
       LCDSetCursor(0x40);
       LCDMsg("Измер.");
       Enable_interrupts(INT_TIMER0);
  } 
  
   //Кнопка 3
  if (b_push[3]){
       b_push[3]=0;
       LCDSetCursor(0x40);
      // LCDMsg("Кн. 3");
  } 

}


}
