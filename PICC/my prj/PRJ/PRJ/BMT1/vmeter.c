//#include "C:\PRJ\BMT1\vmeter.h"

#include <18F2320.h>
#device adc=10

#include <math.h>


#FUSES NOWDT                    //No Watch Dog Timer
#FUSES WDT128                   //Watch Dog Timer uses 1:128 Postscale
#FUSES H4                       //High speed osc with HW enabled 4X PLL
#FUSES FCMEN                    //Fail-safe clock monitor enabled
#FUSES BROWNOUT                 //Reset when brownout detected
#FUSES BORV45                   //Brownout reset at 4.5V
#FUSES PUT                      //Power Up Timer
#FUSES NOCPD                    //No EE protection
#FUSES STVREN                   //Stack full/underflow will cause reset
#FUSES NODEBUG                  //No Debug mode for ICD
#FUSES NOLVP                    //No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O
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
#use rs232(UART1,baud=9600,parity=N,xmit=PIN_C6,rcv=PIN_C7,bits=8)

#BYTE TRISA = 0xF92
#BYTE TRISB = 0xF93
#BYTE TRISC = 0xF94 

#BYTE PORTA = 0xF80
#BYTE PORTB = 0xF81


#BIT RA2 = PORTA.2
#BIT TRA2 = TRISA.2
#BIT LCD_RS = PORTB.3
#BIT LCD_RW = PORTB.0
#BIT LCD_E = PORTB.2
#BIT PORTB4 = PORTB.4
#BIT PORTB5 = PORTB.5
#BIT PORTB6 = PORTB.6
#BIT PORTB7 = PORTB.7




typedef unsigned int32 U32;
typedef int16 U16;
typedef signed int16 S16;
typedef int8 U8;

// Incremented by timer 0 interrupt
static U8 buf;
#BIT buf4=buf.4
#BIT buf5=buf.5
#BIT buf6=buf.6
#BIT buf7=buf.7

unsigned int16 CONST TABLE [901]= {
2394   ,
2371   ,
2348   ,
2325   ,
2303   ,
2282   ,
2261   ,
2240   ,
2220   ,
2200   ,
2181   ,
2162   ,
2143   ,
2125   ,
2107   ,
2089   ,
2072   ,
2055   ,
2039   ,
2022   ,
2006   ,
1991   ,
1975   ,
1960   ,
1945   ,
1931   ,
1916   ,
1902   ,
1888   ,
1874   ,
1861   ,
1847   ,
1834   ,
1821   ,
1809   ,
1796   ,
1784   ,
1772   ,
1759   ,
1748   ,
1736   ,
1724   ,
1713   ,
1702   ,
1690   ,
1679   ,
1668   ,
1658   ,
1647   ,
1636   ,
1626   ,
1616   ,
1605   ,
1595   ,
1585   ,
1575   ,
1565   ,
1556   ,
1546   ,
1536   ,
1527   ,
1518   ,
1508   ,
1499   ,
1490   ,
1481   ,
1472   ,
1463   ,
1454   ,
1445   ,
1436   ,
1427   ,
1419   ,
1410   ,
1402   ,
1393   ,
1385   ,
1376   ,
1368   ,
1360   ,
1352   ,
1343   ,
1335   ,
1327   ,
1319   ,
1311   ,
1303   ,
1295   ,
1288   ,
1280   ,
1272   ,
1264   ,
1257   ,
1249   ,
1242   ,
1234   ,
1227   ,
1219   ,
1212   ,
1204   ,
1197   ,
1190   ,
1182   ,
1175   ,
1168   ,
1161   ,
1154   ,
1147   ,
1140   ,
1133   ,
1126   ,
1119   ,
1112   ,
1106   ,
1099   ,
1092   ,
1085   ,
1079   ,
1072   ,
1066   ,
1059   ,
1053   ,
1046   ,
1040   ,
1033   ,
1027   ,
1021   ,
1014   ,
1008   ,
1002   ,
9960   ,
9899   ,
9839   ,
9779   ,
9719   ,
9660   ,
9601   ,
9542   ,
9484   ,
9427   ,
9369   ,
9313   ,
9256   ,
9200   ,
9145   ,
9089   ,
9035   ,
8980   ,
8926   ,
8872   ,
8819   ,
8766   ,
8714   ,
8662   ,
8610   ,
8559   ,
8508   ,
8458   ,
8408   ,
8358   ,
8309   ,
8260   ,
8212   ,
8164   ,
8116   ,
8069   ,
8022   ,
7976   ,
7930   ,
7884   ,
7839   ,
7794   ,
7749   ,
7705   ,
7662   ,
7618   ,
7575   ,
7532   ,
7490   ,
7448   ,
7407   ,
7366   ,
7325   ,
7284   ,
7244   ,
7205   ,
7165   ,
7126   ,
7088   ,
7049   ,
7011   ,
6974   ,
6936   ,
6900   ,
6863   ,
6827   ,
6791   ,
6755   ,
6720   ,
6685   ,
6650   ,
6616   ,
6582   ,
6548   ,
6515   ,
6481   ,
6449   ,
6416   ,
6384   ,
6352   ,
6320   ,
6289   ,
6258   ,
6227   ,
6197   ,
6166   ,
6136   ,
6107   ,
6077   ,
6048   ,
6019   ,
5990   ,
5962   ,
5934   ,
5906   ,
5878   ,
5850   ,
5823   ,
5796   ,
5769   ,
5743   ,
5716   ,
5690   ,
5664   ,
5638   ,
5613   ,
5588   ,
5562   ,
5538   ,
5513   ,
5488   ,
5464   ,
5440   ,
5416   ,
5392   ,
5368   ,
5345   ,
5321   ,
5298   ,
5275   ,
5252   ,
5230   ,
5207   ,
5185   ,
5163   ,
5141   ,
5119   ,
5097   ,
5075   ,
5054   ,
5032   ,
5011   ,
4990   ,
4969   ,
4948   ,
4927   ,
4907   ,
4886   ,
4866   ,
4845   ,
4825   ,
4805   ,
4785   ,
4765   ,
4745   ,
4726   ,
4706   ,
4687   ,
4667   ,
4648   ,
4629   ,
4610   ,
4591   ,
4572   ,
4553   ,
4534   ,
4515   ,
4496   ,
4478   ,
4459   ,
4441   ,
4423   ,
4404   ,
4386   ,
4368   ,
4350   ,
4332   ,
4314   ,
4296   ,
4278   ,
4260   ,
4243   ,
4225   ,
4207   ,
4190   ,
4173   ,
4155   ,
4138   ,
4120   ,
4103   ,
4086   ,
4069   ,
4052   ,
4035   ,
4018   ,
4001   ,
3984   ,
3967   ,
3951   ,
3934   ,
3917   ,
3901   ,
3884   ,
3868   ,
3851   ,
3835   ,
3819   ,
3802   ,
3786   ,
3770   ,
3754   ,
3738   ,
3722   ,
3706   ,
3690   ,
3674   ,
3658   ,
3643   ,
3627   ,
3611   ,
3596   ,
3580   ,
3565   ,
3550   ,
3534   ,
3519   ,
3504   ,
3489   ,
3474   ,
3459   ,
3444   ,
3429   ,
3414   ,
3399   ,
3384   ,
3370   ,
3355   ,
3341   ,
3326   ,
3312   ,
3298   ,
3283   ,
3269   ,
3255   ,
3241   ,
3227   ,
3213   ,
3200   ,
3186   ,
3172   ,
3159   ,
3145   ,
3132   ,
3119   ,
3105   ,
3092   ,
3079   ,
3066   ,
3053   ,
3040   ,
3028   ,
3015   ,
3002   ,
2990   ,
2977   ,
2965   ,
2953   ,
2941   ,
2929   ,
2917   ,
2905   ,
2893   ,
2881   ,
2870   ,
2858   ,
2847   ,
2835   ,
2824   ,
2813   ,
2802   ,
2791   ,
2780   ,
2770   ,
2759   ,
2748   ,
2738   ,
2727   ,
2717   ,
2707   ,
2697   ,
2687   ,
2677   ,
2667   ,
2658   ,
2648   ,
2638   ,
2629   ,
2620   ,
2611   ,
2602   ,
2593   ,
2584   ,
2575   ,
2566   ,
2557   ,
2549   ,
2541   ,
2532   ,
2524   ,
2516   ,
2508   ,
2500   ,
2492   ,
2484   ,
2477   ,
2469   ,
2462   ,
2454   ,
2447   ,
2440   ,
2433   ,
2426   ,
2419   ,
2412   ,
2405   ,
2398   ,
2392   ,
2385   ,
2379   ,
2373   ,
2366   ,
2360   ,
2354   ,
2348   ,
2342   ,
2336   ,
2331   ,
2325   ,
2319   ,
2314   ,
2308   ,
2303   ,
2298   ,
2292   ,
2287   ,
2282   ,
2277   ,
2272   ,
2267   ,
2262   ,
2257   ,
2252   ,
2248   ,
2243   ,
2239   ,
2234   ,
2229   ,
2225   ,
2221   ,
2216   ,
2212   ,
2208   ,
2203   ,
2199   ,
2195   ,
2191   ,
2187   ,
2183   ,
2179   ,
2175   ,
2171   ,
2167   ,
2163   ,
2159   ,
2155   ,
2152   ,
2148   ,
2144   ,
2140   ,
2137   ,
2133   ,
2129   ,
2125   ,
2122   ,
2118   ,
2114   ,
2110   ,
2107   ,
2103   ,
2099   ,
2096   ,
2092   ,
2088   ,
2084   ,
2081   ,
2077   ,
2073   ,
2069   ,
2066   ,
2062   ,
2058   ,
2054   ,
2050   ,
2046   ,
2042   ,
2038   ,
2034   ,
2030   ,
2026   ,
2022   ,
2018   ,
2014   ,
2010   ,
2006   ,
2001   ,
1997   ,
1993   ,
1988   ,
1984   ,
1980   ,
1975   ,
1971   ,
1966   ,
1961   ,
1957   ,
1952   ,
1947   ,
1942   ,
1937   ,
1932   ,
1927   ,
1922   ,
1917   ,
1912   ,
1907   ,
1902   ,
1896   ,
1891   ,
1885   ,
1880   ,
1874   ,
1869   ,
1863   ,
1857   ,
1852   ,
1846   ,
1840   ,
1834   ,
1828   ,
1822   ,
1816   ,
1809   ,
1803   ,
1797   ,
1791   ,
1784   ,
1778   ,
1771   ,
1764   ,
1758   ,
1751   ,
1744   ,
1738   ,
1731   ,
1724   ,
1717   ,
1710   ,
1703   ,
1695   ,
1688   ,
1681   ,
1674   ,
1666   ,
1659   ,
1652   ,
1644   ,
1637   ,
1629   ,
1622   ,
1614   ,
1606   ,
1599   ,
1591   ,
1583   ,
1575   ,
1568   ,
1560   ,
1552   ,
1544   ,
1536   ,
1528   ,
1520   ,
1512   ,
1504   ,
1496   ,
1488   ,
1480   ,
1472   ,
1464   ,
1456   ,
1448   ,
1440   ,
1432   ,
1423   ,
1415   ,
1407   ,
1399   ,
1391   ,
1383   ,
1375   ,
1367   ,
1359   ,
1351   ,
1343   ,
1335   ,
1327   ,
1319   ,
1311   ,
1304   ,
1296   ,
1288   ,
1280   ,
1273   ,
1265   ,
1257   ,
1250   ,
1242   ,
1235   ,
1227   ,
1220   ,
1213   ,
1206   ,
1198   ,
1191   ,
1184   ,
1177   ,
1170   ,
1163   ,
1156   ,
1150   ,
1143   ,
1136   ,
1130   ,
1123   ,
1117   ,
1111   ,
1104   ,
1098   ,
1092   ,
1086   ,
1080   ,
1074   ,
1069   ,
1063   ,
1057   ,
1052   ,
1047   ,
1041   ,
1036   ,
1031   ,
1026   ,
1021   ,
1016   ,
1011   ,
1007   ,
1002   ,
9974   ,
9930   ,
9887   ,
9844   ,
9803   ,
9762   ,
9722   ,
9684   ,
9646   ,
9608   ,
9572   ,
9537   ,
9502   ,
9468   ,
9435   ,
9241   ,
9183   ,
9124   ,
9066   ,
9008   ,
8950   ,
8892   ,
8834   ,
8777   ,
8719   ,
8662   ,
8605   ,
8548   ,
8491   ,
8434   ,
8378   ,
8322   ,
8265   ,
8209   ,
8153   ,
8097   ,
8042   ,
7986   ,
7931   ,
7875   ,
7820   ,
7765   ,
7710   ,
7655   ,
7601   ,
7546   ,
7492   ,
7437   ,
7383   ,
7329   ,
7275   ,
7221   ,
7168   ,
7114   ,
7060   ,
7007   ,
6954   ,
6900   ,
6847   ,
6794   ,
6741   ,
6688   ,
6636   ,
6583   ,
6530   ,
6478   ,
6426   ,
6373   ,
6321   ,
6269   ,
6217   ,
6165   ,
6113   ,
6061   ,
6010   ,
5958   ,
5906   ,
5855   ,
5804   ,
5752   ,
5701   ,
5650   ,
5599   ,
5548   ,
5497   ,
5446   ,
5395   ,
5344   ,
5294   ,
5243   ,
5193   ,
5142   ,
5092   ,
5041   ,
4991   ,
4941   ,
4891   ,
4841   ,
4791   ,
4741   ,
4691   ,
4641   ,
4591   ,
4542   ,
4492   ,
4443   ,
4393   ,
4344   ,
4295   ,
4245   ,
4196   ,
4147   ,
4098   ,
4049   ,
4000   ,
3952   ,
3903   ,
3854   ,
3806   ,
3757   ,
3709   ,
3661   ,
3612   ,
3564   ,
3516   ,
3468   ,
3421   ,
3373   ,
3325   ,
3278   ,
3230   ,
3183   ,
3136   ,
3089   ,
3042   ,
2995   ,
2948   ,
2901   ,
2855   ,
2809   ,
2762   ,
2716   ,
2670   ,
2625   ,
2579   ,
2533   ,
2488   ,
2443   ,
2398   ,
2353   ,
2308   ,
2264   ,
2219   ,
2175   ,
2131   ,
2087   ,
2044   ,
2001   ,
1957   ,
1914   ,
1872   ,
1829   ,
1787   ,
1745   ,
1703   ,
1662   ,
1620   ,
1579   ,
1539   ,
1498   ,
1458   ,
1418   ,
1379   ,
1339   ,
1300   ,
1262   ,
1224   ,
1186   ,
1148   ,
1111   ,
1074   ,
1037   ,
1001   ,
9652   ,
9298   ,
8948   ,
8603   ,
8261   ,
7924   ,
7591   ,
7262   ,
6939   ,
6619   ,
6305   ,
5996   ,
5691   ,
5392   ,
5098   ,
4809   ,
4525   ,
4247   ,
3975   ,
3709   ,
3448   ,
3194   ,
2945   ,
2703   ,
2467   ,
2238   ,
2015   ,
1799   ,
1590   ,
1388   ,
1193   ,
1005};


Static U16 Ih,Ut;
static U8 TMR0fl=0;
static U8 ff1=0;
static U16 pwm_val=535;// начальное значение тока нагревателя

//Запись и чтение EEPROM

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
write_eeprom (Adr, value);//мл.байт
value=DATA>>8;
write_eeprom (Adr+1, value);//ст.байт
delay_ms(10);
if(U16EERead(Adr)==DATA) return 1;
 else return 0;
}
 



/***************** LCD functions *****************/

static void LCDWriteNibble(unsigned char uc) /* RS must be set/reset before calling */
{                                           //Запись половины байта
  uc=uc << 4; /* Align with bits 7-4*/
  LCD_RW=0;
  //TRISB=0b00000010; /* Set to output bits 7-4 */
  //PORTB=uc;
  buf=uc;
  PORTB4=buf4;
  PORTB5=buf5;
  PORTB6=buf6;
  PORTB7=buf7;
  delay_us(1);
  LCD_E=1;
  delay_us(2);
  LCD_E=0;
  delay_us(2);
  LCD_RW=1; 
  //TRISB=0b11110010; /* Set to input bits 7-4 */  
}

static U8 PBScan(U8 pb){
// сканирование кнопок
//pb-номер кнопки(0-3);
 U8 uc=1;
   uc=uc<<(4+pb);
   buf=uc;
   //устанавливаем в 1 соотв. линию
    PORTB4=buf4;
    PORTB5=buf5;
    PORTB6=buf6;
    PORTB7=buf7;
    delay_us(10);
   return RA2;
      
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
  LCDCommand(0x0F);// Включить дисплей, включить курсор, включить моргание курсора
  LCDCommand(0x06);// Курсор будет двигаться вправо при выводе текста
  LCDCommand(0x1);// Очистка экрана и перемещение курсора в первую позицию 
   delay_ms(2);
  LCDCommand(0x06);// Курсор будет двигаться вправо при выводе текста 
  LCDCommand(0x40);//Установка адреса DRAM
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
    LCDMsg("VM PMT-2,PMT-4M");
    LCDSetCursor(0x40);
    LCDMsg("Firmware v0.2");
    Delay_ms(2000);
    LCDClear();
  
}

static void Ih_LCDUpdate(U8 ns){
//Вывод значения тока нагревателя 
U16 num1,num2;
U16 mod;
 if(ns == 1) LCDSetCursor(0x0);//Уст. курсор на первую строку
    else LCDSetCursor(0x40);//Уст. курсор на вторую строку

LCDMsg("Ih= ");
num1=Ih/10;
num2=num1*10;
mod=Ih-num2;
LCDPutU16(num1,3);
LCDMsg(".");
LCDPutU16(mod,1);
LCDMsg(' ');
LCDMsg(0xBC);//м
LCDMsg(0x41);//А
 if(ff1){
    LCDMsg(' ');
    LCDMsg(0xD9);
    LCDMsg(0xDA);
    LCDMsg(" ");
     } else LCDMsg("    ");
}



static void Ut_LCDUpdate(U8 ns){
//Вывод значения ЭДС термопары
U16 num1,num2;
U16 mod;
 if(ns == 1) LCDSetCursor(0x0);//Уст. курсор на первую строку
    else LCDSetCursor(0x40);//Уст. курсор на вторую строку
    
LCDMsg("Ut= ");
num1=Ut/100;
num2=num1*100;
mod=Ut-num2;
LCDPutU16(num1,2);
LCDMsg(".");
LCDPutU16(mod,2);
LCDMsg(' ');
LCDMsg(0xBC);//м
LCDMsg(0x42);//В
LCDMsg("    ");
}

static void Pa_LCDUpdate(U8 ns){
U16 num1,num2,pres;
U16 mod;
//Вывод значения давления в Па
if(ns == 1) LCDSetCursor(0x0);//Уст. курсор на первую строку
    else LCDSetCursor(0x40);//Уст. курсор на вторую строку
   

if (Ut<100){
         LCDMsg("P> ");
          pres=2394;
           Ut=100;
  } else if(Ut>1000){
           LCDMsg("P< ");
          pres=1005;
           Ut=1000;
  } else{
  pres = table[ut-100];
  LCDMsg("P= ");
  }

num1=Pres/1000;
num2=num1*1000;
mod=Pres-num2;

LCDPutU16(num1,1);
LCDMsg(".");
LCDPutU16(mod,3);
LCDMsg("E");

if ((99<Ut)&&(Ut<230))
{LCDPutS16(1,2);
}
else if ((229<Ut)&&(Ut<785))
{LCDPutS16(0,2);
}
else if ((784<Ut)&&(Ut<969))
{LCDPutS16(-1,2);
}
else
{LCDPutS16(-2,2);
}

//LCDMsg(" Pa");
//Па
LCDMsg(' ');
LCDMsg(0xA8);
LCDMsg(0x61);
LCDMsg(" ");

}

#int_TIMER0
void  TIMER0_isr(void) 
{
// прерывание каждые 0.5 сек.
tmr0fl=1;
set_timer0(46000);   

clear_interrupt(int_timer0);
}


void main()
{
char ch;
U8 i,ff=0xff;
U16 val=0;
U32 ADC_value;
U8 t_out[4]={0,0,0,0};
U8 b_hold[4]={0,0,0,0};
U8 b_push[4]={0,0,0,0};

   setup_adc_ports(AN0_TO_AN1|VSS_VREF);
   setup_adc(ADC_OFF|ADC_TAD_MUL_20);
   
   setup_spi(SPI_SS_DISABLED);
   setup_wdt(WDT_OFF);
   setup_timer_0(RTCC_INTERNAL|RTCC_DIV_256);
   set_timer0(46000);   
   setup_timer_1(T1_DISABLED);
  
  //конфигурирование PWM
   setup_timer_2(T2_DIV_BY_4 ,255,1);
   setup_ccp1(CCP_PWM);
   
   
   setup_comparator(NC_NC_NC_NC);
   setup_vref(FALSE);
//Setup_Oscillator parameter not selected from Intr Oscillator Config tab

   // TODO: USER CODE!!
   //установка режима АЦП
   setup_adc(ADC_CLOCK_DIV_64|ADC_TAD_MUL_20);
   



 
TRA2=1;//   RA2 - вход опроса кнопок 
TRISB=0b00000010;

LCDInit();
 // Welcome message on LCD
 LCDWelcome();
 //Установка значения PWM (0-1023)
//746 - 140 mA
//535 - 100 mA
//0.189mA на единицу кода PWM
val=U16EERead(0);
 if(val<535||val>746){
   pwm_val=536;
   ch=0;
 }
   else {
   pwm_val=val;
   ch=1;
   }
   set_pwm1_duty(pwm_val);
   LCDClear();
   LCDSetCursor(0);
   if(ch) LCDMsg("EE READ OK");
     else  LCDMsg("EE READ ERR");
   
   delay_ms(1000);
   
   enable_interrupts(INT_TIMER0);
enable_interrupts(GLOBAL);

  
 
while(true) {

//*******Измерение,вывод на COM и LCD**************************
   if(tmr0fl){
    tmr0fl=0;// флаг TMR0,появляется каждые 0.5 сек.
   //Измеряем ток нагревателя
   set_adc_channel(1);//Уст. канал 1 АЦП (An1)
   delay_us(20);
     ADC_value = read_adc();//получаем результат преобразования
    // f=(ADC_Value*4)/25.7; мA
     Ih=(ADC_Value*400)/257;
    
    //Измеряем ЭДС термопары
    set_adc_channel(0);//Уст. канал 0 АЦП (An0)
    delay_us(20);
    
    ADC_value = read_adc();//получаем результат преобразования
   
   //f=(ADC_value*4)/381.0;//мB
    ut=(ADC_value*400)/381;
    //Вывод на com-порт
       printf("Ut = %Lu mV Ih = %Lu mA \n\r", ut, Ih);
     //Вывод на LCD  
     Ih_LCDUpdate(1);
      if(ff) Ut_LCDUpdate(2);
         else Pa_LCDUpdate(2);
       
     //Ut_LCDUpdate(2);
     //Pa_LCDUpdate(2);
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
  //Увеличение тока нагревателя
  if (b_push[0]&& ff1){
       b_push[0]=0;
       pwm_val=pwm_val+1;
       set_pwm1_duty(pwm_val);
  }
  //Уменьшение тока нагревателя
  if (b_push[1] && ff1){
       b_push[1]=0;
       pwm_val=pwm_val-1;
       set_pwm1_duty(pwm_val);
  }
  
  //Режим отображения давления 
  if (b_push[3]){
       b_push[3]=0;
       ff=~ff;
    }
    
   //Режим установки тока нагревателя
  if (b_push[2]){
       b_push[2]=0;
       ff1=~ff1;
       if(ff1==0) U16EEWrite(pwm_val,0);//запись в EEPROM
    }
    
    
  delay_ms(1);
}   
}  
  


