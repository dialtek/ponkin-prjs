// Измеритель магнитной индукции 2.2 //

#include <XYZ Gaussmeter.h>
#include <stdio.h>
#include <LCD_XYZ_Gaussmeter.c>

unsigned int1 int_fl = 0,zero_set1=0;
static U8 ff1=0;
unsigned int1 fl2=0, menufl1 =0, menufl2 =0, menufl3 =0, menufl4 =1; //????? ??????? ??????
static U8 TMR0fl=0, MenuItemNum=0;                  
static U8 RXd_buf=0;

char  ConfigRegA = 0x00, ConfigRegB = 0x01, ModeReg = 0x02, xMSB = 0x03, xLSB = 0x04, // ?????? ????????? ??????? ??
      zMSB = 0x05, zLSB = 0x06,yMSB = 0x07,yLSB = 0x08,StatReg = 0x09, idRegA = 0x10,
      idRegB = 0x11, idRegC = 0x12;
     
   
signed int16 SumX=0; 
signed int16 SumY=0; 
signed int16 SumZ=0;
       
signed int16 SumX0=0; 
signed int16 SumY0=0;
signed int16 SumZ0=0;

signed int32 average_Xg=0; 
signed int32 average_Yg=0;
signed int32 average_Zg=0;
             
unsigned int16 Xh =0;   
unsigned int8 Xl = 0;
unsigned int16 Yh =0;
unsigned int8 Yl = 0;
unsigned int16 Zh =0;
unsigned int8 Zl = 0;

float Xd = 0;
float Yd = 0;
float Zd = 0;

U8 aver_count = 0;

S32 average_X, average_Y, average_Z;


//****************** Sensor func ************************************
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
   SensWrData(ConfigRegA,0x18); //  F = 30 Hz/1
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
   
   /*
   
   if (int_fl){
      DISABLE_INTERRUPTS(INT_EXT);
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
      //delay_us(20);                                   
      Yh = i2c_read();  // Y MSB
      Yl = i2c_read();  // Y LSB
      SumY = (Yh<<8)|Yl;   //?????????????? ???????? ????????. ??? Y
      //delay_us(20);
      Zh = i2c_read();  // Z MSB
      Zl = i2c_read();  // Z LSB
      SumZ = (Zh<<8)|Zl;  //?????????????? ???????? ????????. ??? Z  
      //delay_us(20);
      i2c_stop();
   */   

   if (fl2){ // ?????? ???.0 ?? ??????!
               // ????? ????? "???.0"
      LCDClear();
      Lcdsetcursor(0);
      LcdMsg(" УСТАНОВКА НУЛЯ ");    
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

/*
  // Output value of the magnetic field along the axis "X"
   LcdMsg("Bx");
   if (Approximation(Zd) >= 0){
      LcdMsg(" "); LcdPutU16(Approximation(Zd*1000) / 1000, 1);
      }
   else{
      LcdMsg("-"); LcdPutU16(abs(Approximation(Zd*1000)) / 1000, 1);
   }
   LcdMsg(".");
   LcdPutU16(Remainder(Approximation(Zd*1000)), 2);
   LcdMsg("  ");
   
// Output value of the magnetic field along the axis "Z"
   LcdMsg("Bz");
   if (Approximation(Xd) >= 0){
      LcdMsg(" "); LcdPutU16(Approximation(Xd*1000) / 1000, 1);
      }
   else{
      LcdMsg("-"); LcdPutU16(abs(Approximation(Xd*1000)) / 1000, 1);
   }
   LcdMsg(".");
   LcdPutU16(Remainder(Approximation(Xd*1000)), 2);
//   LcdMsg(" ");

// Output value of the magnetic field along the axis "Y"
   LcdSetCursor(0x40);
   LcdMsg("By");
if (Approximation(Yd) >= 0){
      LcdMsg(" "); LcdPutU16(Approximation(Yd*1000) / 1000, 1);
      }
   else{
      LcdMsg("-"); LcdPutU16(abs(Approximation(Yd*1000)) / 1000, 1);
   }
   LcdMsg(".");
   LcdPutU16(Remainder(Approximation(Yd*1000)), 2);
   LcdMsg("    Гс.  ");

*/

     // Значения поля Bx, By, Bz выводятся согласно пожеланию заказчика //

   LcdSetCursor(0x00);
   LcdMsg("Bx");
   LcdPutS16(Zd*1000,4);
   LcdMsg("  By");
   LcdPutS16(Yd*1000,4);
   LcdSetCursor(0x40);
   LcdMsg("    Bz");
   LcdPutS16(Xd*1000,4);
   LcdMsg("  Гс.");

   int_fl = false;
      
}

//****************** Sensor func ************************************


//================== Interrupts  ====================================
#INT_EXT 
Void int0(void){

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
   
   if (aver_count == 10) 
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

//b_push[1] = 1;
//b_push[2] = 1;
//b_push[3] = 1;
zero_set1 = 1;
}

clear_interrupt(INT_RDA);  // ????? ????? ??????????
}

//================== Interrupts  ====================================
 
 
void main() {
   TRB0 = 1;   // DRDY
   
   TRB3 = 0; 
   TRB4 = 0;
   TRB5 = 0;
   TRC0 = 0;
   TRC1 = 0;
   TRC2 = 0;
   TRC5 = 0;
 
   TRC3 = 1;
   TRC4 = 1;
   TRC6 = 0;                  // UART1 - TX
   TRC7 = 1;                  // UART1 - RX
   
   EXT_INT_EDGE(L_TO_H);
   enable_interrupts(INT_RDA);
   enable_interrupts(INT_EXT);
   enable_interrupts(GLOBAL);

   LCDInit();
   LcdWelcome();
   SensInit();

   while(true){
   
      if (int_fl) SensRdAll();
      if (!SW1) fl2 = 1;
      
   }
}


