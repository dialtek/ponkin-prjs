// Измеритель магнитной индукции 2.0 //

#include <XYZ Gaussmeter.h>
#include <stdio.h>
#include <LCD_XYZ_Gaussmeter.c>

//signed int16 A = 0, B = 0, C = 0, D = 0;
unsigned int1 int_fl = 0,zero_set1=0;
static U8 ff1=0;
unsigned int1 fl2=0, menufl1 =0, menufl2 =0, menufl3 =0, menufl4 =1; //????? ??????? ??????
static U8 TMR0fl=0, MenuItemNum=0;                  
static U8 RXd_buf=0;

char  ConfigRegA = 0x00, ConfigRegB = 0x01, ModeReg = 0x02, xMSB = 0x03, xLSB = 0x04, // ?????? ????????? ??????? ??
      zMSB = 0x05, zLSB = 0x06,yMSB = 0x07,yLSB = 0x08,StatReg = 0x09, idRegA = 0x10,
      idRegB = 0x11, idRegC = 0x12;
     
   
signed int16 SumX=0; // ?????????? ??? ???????? ?????????
signed int16 SumY=0; // 3 ??. ?? ?????? ????? ?????? ?? ???? ???? ???? ?? ???? ??????
signed int16 SumZ=0;
       
signed int16 SumX0=0; // ??? ???. 0
signed int16 SumY0=0;
signed int16 SumZ0=0;
             
unsigned int16 Xh = 0;   // ?????????? ?????? ? ????????
unsigned int8 Xl = 0;
unsigned int16 Yh = 0;
unsigned int8 Yl = 0;
unsigned int16 Zh = 0;
unsigned int8 Zl = 0;
  /*      
   unsigned int16 Xh0 = 0;
    unsigned int8 Xl0 = 0;
     unsigned int16 Yh0 = 0;
      unsigned int8 Yl0 = 0;
       unsigned int16 Zh0 = 0;
        unsigned int8 Zl0 = 0;
    */
    
        //float32 Xd = 0; // ?? LCD ?????
signed int16 Xd = 0;
signed int16 Yd = 0;
signed int16 Zd = 0;
        
        //unsigned int16 K = 3955;   
       
U8 t_out[4]={0,0,0,0};      // ??????? ??????????
U8 b_hold[4]={0,0,0,0};      // ??? ????????? ??????
U8 b_push[4]={0,0,0,0};

//****************** Sensor func ************************************

//??????
/*
  static U8 PBScan(U8 pb){
// ???????????? ??????
//pb-????? ??????(0-3);
 U8 uc=1;
   uc=uc<<(4+pb);
   buf=uc;
   //????????????? ? 1 ?????. ?????
   
    DB4=buf4;
    DB5=buf5;
    DB6=buf6;
    DB7=buf7;
    
    delay_us(100);
    //RA2=rc1;
   return  RC1;
      
}
*/

#INT_EXT 
Void int0(void){
   int_fl = 1;
   clear_interrupt(INT_EXT);
   }

#INT_TIMER0 
void  TIMER0_isr(void) {
// ?????????? ?????? 0.5 ???.
   tmr0fl = 1;
   set_timer0(60000);   
   clear_interrupt(int_timer0);
   }
/*
#INT_TIMER1 
void  TIMER1_isr(void){
// ?????????? ?????? 0.5 ???.
   set_timer1(62685);
//   LCD_E = 1;
   clear_interrupt(int_timer1);
   }
*/

#INT_TIMER3
void  TIMER3_isr(void){                // ?????? ????? ?????????? DRDY
   if(!DRDY) int_fl = 1;
   set_timer3(64335);  
   clear_interrupt(int_timer3);
}

/*
static void StatusSwitch(){
   if (LCD_E = 1){
      TRC0 = 1;
      TRC1 = 1;
      TRC2 = 1;
      TRC5 = 1;
      if (SW1 = 0) LED = 1;
      else LED = 0;
   }
   LCD_E = 0;
}*/
/**/

#INT_RDA
void UART_RXd_isr(void){

RXd_buf = getc();          // ?????? ??????? ??????....
                           // ??? ??????, ????????? ?? ??????? ?? ???????????
if (RXd_buf == 'z')        // ???????????? ?????????? ???????? ???. 0... FTDI ???? ????? ??? ????. ????????? ??
{
menufl1 = 0;
menufl2 = 0;
menufl3 = 0;
fl2=1;

//b_push[0] = 1;
b_push[1] = 1;
b_push[2] = 1;
b_push[3] = 1;
zero_set1 = 1;
}

clear_interrupt(INT_RDA);  // ????? ????? ??????????
}

/**/

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

static void LcdPutResults(U32 _u16,U8 u8NumDigs){
   S16 u16a ,u16b;
    
   _u16= _u16 - u16b;
   u16a=_u16/1000;
   u16b=u16a*1000;
   if (u8NumDigs>=4){
      LCDPutCh((U8)u16a+'0');
      LCDPutCh('.');
   }

   _u16= _u16 - u16b;
   u16a=_u16/100;
   u16b=u16a*100;
   if (u8NumDigs>=3){
      LCDPutCh((U8)u16a+'0');      
   }

   _u16= _u16 - u16b;
   u16a=_u16/10;
   u16b=u16a*10;
   if (u8NumDigs>=2){
      LCDPutCh((U8)u16a+'0');
   }

   _u16= _u16 - u16b;
   if (u8NumDigs>=1){
      LCDPutCh((U8)_u16+'0');
   }     
     //return 0;
   }

 /*
static void ZeroSet(){  
   SensWrData(ConfigRegA,0x74); // single measurment mode, F = 30 Hz,  average = 8
   delay_us(10);
   SensWrData(ModeReg,0x00);  // continuous measurment
   
   if (int_fl){
   //fl2=1;
      i2c_start();  
      i2c_write(0x3C); // The default (factory) HMC5883 7-bit slave address 
                    // is 0x3C for write operations, or 0x3D for read operations.
      i2c_write(0x03); // pointer 
      i2c_stop();
      delay_us(10);
   
      i2c_start();
      i2c_write(0x3D); //i2c Read

      Xh0 = i2c_read();   // X MSB
      Xl0 = i2c_read();   // X LSB
      SumX0 = (Xh0<<8)|Xl0;   //?????????????? ???????? ????????. ??? ?
   
      Yh0 = i2c_read();  // Y MSB  
      Yl0 = i2c_read();  // Y LSB
      Sset_timer0(60000); set_timer0(60000); umY0 = (Yh0<<8)|Yl0;   //?????????????? ???????? ????????. ??? Y
  
      Zh0 = i2c_read();  // Z MSB
      Zl0 = i2c_read();  // Z LSB
      SumZ0 = (Zh0<<8)|Zl0;  //?????????????? ???????? ????????. ??? Z  
   
   //i2c_read();    //if adress pointer = 08, adress pointer = 03
      i2c_stop();   
   }
}
*/
/**/  

// Выделение первой цифры после запятой
static unsigned int8 Remainder (signed int16 Parameter){
   unsigned int8 Tenth = 0;
   unsigned int8 Temp = 0;
   Temp = (unsigned int8)(abs(Parameter) / 10);
   Tenth = Temp % 100;
   return Tenth;
}

// Округление значения магнитного поля.
// Значение поля разбивается по цифрам, округляется, далее из цифр снова составляется
// значение магнитного поля с учётом округления.
static signed int16 Approximation (signed int16 Parameter){
   signed int16 Field = 0;
   signed int16 A = 0, B = 0, C = 0, D = 0;                        // 1-ая, 2-ая, 3-я, 4-ая цифры в значении магнитного поля

   D = (abs(Parameter)) % 10;
   C = ((abs(Parameter)) % 100) / 10;
   B = ((abs(Parameter)) % 1000) / 100;
   A = (abs(Parameter)) / 1000;
  
   if (D >= 5){C++; D = 0;}
   else D = 0;
//   if (C >= 5){B++; C = 0;}
//   else C = 0;
   
   if(Parameter >= 0){
   Field = (A * 1000) + (B * 100) + (C * 10) + D;
   }
   else Field = -1*(A * 1000 + B * 100 + C * 10 + D);
   
   return Field;
}

static void SensRdAll(){
   //SensWrData(ConfigRegA,0x74); // single measurment mode, F = 30 Hz,  average = 8
   SensWrData(ConfigRegB,0xE0); // range = +/- 8.1 Gs
   SensWrData(ModeReg,0x00);  // continuous measurment
   
   delay_us(10);
   if (int_fl){
      i2c_start();  
      i2c_write(0x3C); // The default (factory) HMC5883 7-bit slave address 
                    // is 0x3C for write operations, or 0x3D for read operations.
      i2c_write(0x03); // pointer 
      i2c_stop();
      delay_ms(67);
   
      i2c_start();
      i2c_write(0x3D); //i2c Read
      
      Xh = i2c_read();   // X MSB
      Xl = i2c_read();   // X LSB
      SumX = (Xh<<8)|Xl;   //?????????????? ???????? ????????. ??? ?   
      delay_us(20);                                   
      Yh = i2c_read();  // Y MSB
      Yl = i2c_read();  // Y LSB
      SumY = (Yh<<8)|Yl;   //?????????????? ???????? ????????. ??? Y
      delay_us(20);
      Zh = i2c_read();  // Z MSB
      Zl = i2c_read();  // Z LSB
      SumZ = (Zh<<8)|Zl;  //?????????????? ???????? ????????. ??? Z  
      delay_us(20);
      
   if (fl2){ // ?????? ???.0 ?? ??????!
               // ????? ????? "???.0"
      Lcdsetcursor(0);
      LcdMsg(" УСТАНОВКА НУЛЯ ");    
      SumX0=SumX;
      SumY0=SumY;
      SumZ0=SumZ;  
      delay_ms(1000);
      fl2=0;
   }     
   SumZ = SumZ-SumZ0;
   SumY = SumY-SumY0;
   SumX = SumX-SumX0;
       
   i2c_read();    //if adress pointer = 08, adress pointer = 03
   i2c_stop();
      
   Xd = SumX<<2;
   Yd = SumY<<2;
   Zd = SumZ<<2;
   
   Printf("x%Ld\n",SumZ);
   Printf("y%Ld\n",SumY);
   Printf("z%Ld\n",SumX);
   //restart_wdt();    
     //y = (Max*x)/2048; - ???????? ?? ???????? ? ??   
     
   LcdSetCursor(0x00);

// Значения поля Bx, By, Bz выводятся согласно пожеланию заказчика //
  
// Output value of the magnetic field along the axis "X"
   LcdMsg("Bx");
   if (Approximation(Zd) >= 0){
      LcdMsg(" "); LcdPutU16(Approximation(Zd) / 1000, 1);
      }
   else{
      LcdMsg("-"); LcdPutU16(abs(Approximation(Zd)) / 1000, 1);
   }
   LcdMsg(".");
   LcdPutU16(Remainder(Approximation(Zd)), 2);
   LcdMsg("  ");
   
// Output value of the magnetic field along the axis "Z"
   LcdMsg("Bz");
   if (Approximation(Xd) >= 0){
      LcdMsg(" "); LcdPutU16(Approximation(Xd) / 1000, 1);
      }
   else{
      LcdMsg("-"); LcdPutU16(abs(Approximation(Xd)) / 1000, 1);
   }
   LcdMsg(".");
   LcdPutU16(Remainder(Approximation(Xd)), 2);
//   LcdMsg(" ");

// Output value of the magnetic field along the axis "Y"
   LcdSetCursor(0x40);
   LcdMsg("By");
if (Approximation(Yd) >= 0){
      LcdMsg(" "); LcdPutU16(Approximation(Yd) / 1000, 1);
      }
   else{
      LcdMsg("-"); LcdPutU16(abs(Approximation(Yd)) / 1000, 1);
   }
   LcdMsg(".");
   LcdPutU16(Remainder(Approximation(Yd)), 2);
//   LcdMsg("  ");
 
   LcdMsg("    Гс.  ");

   int_fl = 0;
      //enable_interrupts(INT_EXT);
      }
} 
 //******************************************************************* 
/*  
  static void SensRdAll(){
            
   SensWrData(ConfigRegA,0x74); // single measurment mode, F = 30 Hz,  average = 8
   SensWrData(ConfigRegB,0xE0); // range = +/- 8.1 Gs
   SensWrData(ModeReg,0x00);  // continuous measurment
   delay_us(10);
  
  if (int_fl){
   i2c_start();  
   i2c_write(0x3C); // The default (factory) HMC5883 7-bit slave address 
                    // is 0x3C for write operations, or 0x3D for read operations.
   i2c_write(0x03); // pointer 
   i2c_stop();
   delay_us(20);
  
  
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
   
    if (fl2){ // ?????? ???.0 ?? ??????!
               // ????? ????? "???.0"
              Lcdsetcursor(0);
              LcdMsg("ZERO POINT SETUP");    
              SumX0=SumX;
              SumY0=SumY;
              SumZ0=SumZ;  
              delay_ms(1000);
              fl2=0;
              }
      
   SumZ = SumZ-SumZ0;
   SumY = SumY-SumY0;
   SumX = SumX-SumX0;
       
   i2c_read();    //if adress pointer = 08, adress pointer = 03
   i2c_stop();
     
    Printf("x%Ld\n",SumX);
    Printf("y%Ld\n",SumY);
    Printf("z%Ld\n",SumZ);

    
     //y = (Max*x)/2048; - ???????? ?? ???????? ? ??   
     
     LcdSetCursor(0x00);
     LcdMsg("MAGNET. FIELD,Gs");
     
     Xd = SumX*4;       
     LcdSetCursor(0x40);
     LcdMsg("  X = ");
     LcdPutS16(Xd,4);
     //LcdPutResults(Xd,5);     
     
     Yd = SumY*4;  
     LcdSetCursor(0x10);
     LcdMsg("  Y = ");
     LcdPutS16(Yd,4);
     
     Zd = SumZ*4;  
     LcdSetCursor(0x50);
     LcdMsg("  Z = ");
     LcdPutS16(Zd,4);
         
     int_fl = 0;
   }
 } 
 //******************************************************************* 
 */
 /**/
 
void main() {
   TRB0 = 1;   // DRDY
   TRB3 = 0;
   TRB4 = 0;
   TRB5 = 0;
   TRC0 = 0;
   TRC1 = 0;
   TRC2 = 0;
   TRC5 = 0;
/*   TRC0 = 1;
   TRC1 = 1;
   TRC2 = 1;
   TRC5 = 1;*/
   
   TRC3 = 1;
   TRC4 = 1;
   TRC6 = 0;                  // UART1 - TX
   TRC7 = 1;                  // UART1 - RX

   //setup_timer_0(RTCC_INTERNAL|RTCC_DIV_8|RTCC_8_bit);      //256 us overflow
   //setup_timer_1(T1_INTERNAL|T1_DIV_BY_1);                //125 us = 1000 tick
   //setup_timer_3(T3_INTERNAL | T3_DIV_BY_1);   
   
   enable_interrupts(GLOBAL);
   enable_interrupts(INT_EXT);
   EXT_INT_EDGE(H_TO_L);
   enable_interrupts(INT_RDA);
   //enable_interrupts(INT_TIMER0);
   //enable_interrupts(INT_TIMER1);
   //enable_interrupts(INT_TIMER3);
   
   
   //set_timer0(60000); 
   //set_timer1(62685); 
   //set_timer3(64335);                              //150 us = 1200 tick

   LCDInit();
   LcdWelcome();
   SensInit();
   SelfCal();
   
   while(true){
      SensRdAll();
      if (!SW1) fl2 = 1;
   }
}

