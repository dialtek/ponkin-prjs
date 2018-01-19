
/******************************************************/
/* Software V2.3 for magnetic induction's tester V2.1 */
/******************************************************/
// ��������� ��������� 6.04.15

#include <V2.1.h>
#include <stdio.h>
#include <LCD for V2.1.c>

unsigned int1 int_fl = 0,zero_set1=0, LCDClear_Fl = 0;
unsigned int1 SensErr = 0;
unsigned int1 ReInit_flag = 0;
static U8 ff1=0;
unsigned int1 fl2=0, menufl1 =0, menufl2 =0, menufl3 =0, menufl4 =1; //????? ??????? ??????
static U8 TMR0fl=0, MenuItemNum=0;                  
static U8 RXd_buf=0;

char  ConfigRegA = 0x00, ConfigRegB = 0x01, ModeReg = 0x02, xMSB = 0x03, xLSB = 0x04, // ?????? ????????? ??????? ??
      zMSB = 0x05, zLSB = 0x06, yMSB = 0x07, yLSB = 0x08, StatReg = 0x09, idRegA = 0x10,
      idRegB = 0x11, idRegC = 0x12, EEprom_adr = 0xA0;
      
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
float kx_rd = 1.0;
float ky_rd = 1.0;
float kz_rd = 1.0;

U8 crc_buf_wr[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
U8 crc_buf_rd[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
U8 crc_wr_index = 0;
U8 crc_rd_index = 0;
U8 my_arr[4];  
U8 aver_count = 0;

U16 sens_type;
U16 sens_num;
U16 ROM_Adr = 0x0000;
   
U16 CRC_Wr;
U16 CRC1 = 0;
U16 CRC2 = 0; 

S32 average_X, average_Y, average_Z;

//****************** Sensor func ************************************
static void SensWrData(unsigned int8 Adr, Data)
{
   
   i2c_start ();
   i2c_write (0x3C);

   // The default (factory) HMC5883 7 - bit slave address
   // is 0x3C for write operations, or 0x3D for read operations.
   i2c_write (Adr);
   i2c_write (Data);
   i2c_stop ();
}
 
static char SensRdData(char Adr)
{
   
   char Data = 0;
   
   i2c_start ();
   i2c_write (0x3C); // The default (factory) HMC5883 7 - bit slave address
   // is 0x3C for write operations, or 0x3D for read operations.
   i2c_write (Adr); // pointer
   i2c_stop ();
   delay_us (10);
   i2c_start ();
   i2c_write (0x3D); //i2c Read
   delay_us (10);
   Data = i2c_read ();
   delay_us (10);
   Data = i2c_read ();
   delay_us (10);
   i2c_stop ();
   
   return Data;
}
    
static void SensInit ()
{
   
   //SensWrData (ConfigRegA, 0x14); // F = 30 Hz / 1
   SensWrData (ConfigRegA, 0x18); // F = 75 Hz / 1
   SensWrData (ConfigRegB, 0xE0); // range = + / - 8.1 Ga
   SensWrData (ModeReg, 0x00); // continuous measurment mode
   //SensWrData (ModeReg, 0x01); // single measurment mode
}

static signed int16 SelfCal()
{
   
   unsigned int16 Xh = 0;
   unsigned int8 Xl = 0;
   unsigned int16 Yh = 0;
   unsigned int8 Yl = 0;
   unsigned int16 Zh = 0;
   unsigned int8 Zl = 0;
   SensInit ();
   delay_us (10);

   if (int_fl)
   {
      i2c_start ();
      i2c_write (0x3C); // The default (factory) HMC5883 7 - bit slave address
      // is 0x3C for write operations, or 0x3D for read operations.
      i2c_write (0x03); // pointer
      i2c_stop ();
      delay_us (10);
      
      i2c_start ();
      i2c_write (0x3D); //i2c Read
      Xh = i2c_read (); // X MSB
      Xl = i2c_read (); // X LSB
      SumX = (Xh<<8)|Xl; //?????????????? ???????? ????????. ??? ?
      Yh = i2c_read (); // Y MSB
      Yl = i2c_read (); // Y LSB
      SumY = (Yh<<8)|Yl; //?????????????? ???????? ????????. ??? Y
      Zh = i2c_read (); // Z MSB
      Zl = i2c_read (); // Z LSB
      SumZ = (Zh<<8)|Zl; //?????????????? ???????? ????????. ??? Z
      i2c_read (); //if adress pointer = 08, adress pointer = 03
      i2c_stop ();
   }

   
   delay_us (10);
   // SensWrData (ConfigRegA, 0x00); // selftest end
   //Printf ("X = %Ld ", SumX);
   //Printf ("Y = %Ld ", SumY);
   //Printf ("Z = %Ld\n\r", SumZ);
   //restart_wdt ();
   return 1;
}

static void SensRdAll()
{
   if (fl2)
   {
      // ���. 0
      
      LCDClear ();
      Lcdsetcursor (0);
      LcdMsg (" ��������� ���� ");
      SumX0 = SumX;
      SumY0 = SumY;
      SumZ0 = SumZ;
      delay_ms (1000);
      fl2 = 0;
   }

   
   average_Zg = (average_Zg / 10) - SumZ0;
   average_Yg = (average_Yg / 10) - SumY0;
   average_Xg = (average_Xg / 10) - SumX0;
   
   //y = (8.1 * x) / 2048; 8.1 / 2048 = 0.0039550781252
   
   Xd = average_Xg * 0.0039550781252;
   Xd *= kx_rd; // ��������� �� ����������� ����������� �� ���
   Yd = average_Yg * 0.0039550781252;
   Yd *= ky_rd; // ��������� �� ����������� ����������� �� ���
   Zd = average_Zg * 0.0039550781252;
   Zd *= kz_rd; // ��������� �� ����������� ����������� �� ���
   
   // �������� ���� Bx, By, Bz ��������� �������� ��������� ��������� //
   
   //Printf ("x % 05Ld\n", average_Zg); // �������� �� �� "�����" �������� �������
   //Printf ("y % 05Ld\n", average_Yg) ;
   //Printf ("z % 05Ld\n", average_Xg) ;
   
   Printf ("x%05Ld\n", ( (S32) (Zd * 1000))); // �������� �� �� �������� ���� � ��
   Printf ("y%05Ld\n", ( (S32) (Yd * 1000)));
   Printf ("z%05Ld\n", ( (S32) (Xd * 1000)));
   LcdSetCursor (one);
   LcdMsg ("Bx = ");
   LcdPutS16 (Zd * 1000, 4);
   LcdMsg (" ��. ");
   LcdSetCursor (two);
   LcdMsg ("By = ");
   LcdPutS16 (Yd * 1000, 4);
   LcdMsg (" ��. ");
   LcdSetCursor (three);
   LcdMsg ("Bz = ");
   LcdPutS16 (Xd * 1000, 4);
   LcdMsg (" ��. ");
   int_fl = false;
}

//****************** Sensor func ************************************
//------------------ EEPROM func ------------------------------------
 U16 CRC16 (U8 * data_p, U8 length)
 {
    // ������ ����������� �����
    // ���� �� ���������
    
    U8 x;
    U16 crc = 0xFFFF;

    while (length--)
    {
       x = crc >> 8 ^ * data_p++;
       x ^= x>>4;
       crc = (crc << 8) ^ ((U16) (x << 12)) ^ ((U16) (x <<5)) ^ ( (U16) x) ;
    }

    return crc;
 }

 static void rom_wr_byte (U16 addr, U8 dataByte)
 {
    /// ���������� ���� ������ �� 16 - ���. ������
    
    U8 addr_MSB = 0;
    U8 addr_LSB = 0;
    
    addr_MSB = (addr >> 8);
    addr_LSB = addr;
    
    i2c_start ();
    i2c_write (EEprom_adr|0); // ������
    // A read operation is initiated if this bit is high
    // and a write operation is initiated if this bit is low.
    
    i2c_write (addr_MSB);
    i2c_write (addr_LSB);
    i2c_write (dataByte);
    i2c_stop ();
    delay_ms (15); // t ������ � rom - 10 ��
    crc_buf_wr[crc_wr_index] = dataByte;
    crc_wr_index++;
 }

 static U8 rom_rd_byte (U16 addr)
 {
    /// ������ ����� ������ �� 16 - ���. ������
    
    U8 rd_data_byte = 0;
    U8 addr_MSB = 0; // ������� ���� ������
    U8 addr_LSB = 0; // ������� ���� ������
    
    addr_MSB = (addr >> 8); // ���������� ��. ����� �� 2 - ����. ������
    addr_LSB = addr; // ���������� ��. ����� �� 2 - ����. ������
    
    i2c_start ();
    i2c_write (EEprom_adr|0); // ������� ������
    // A read operation is initiated if this bit is high
    // and a write operation is initiated if this bit is low.
    
    i2c_write (addr_MSB); // ������ �� ����� ��. ����� ������
    i2c_write (addr_LSB); // ������ �� ����� ��. ����� ������
    i2c_start ();
    i2c_write (EEprom_adr|1); // ������
    rd_data_byte = i2c_read ();
    i2c_write (0xff); // ��� ����� �� �������� 0_0
    i2c_stop ();
    crc_buf_rd[crc_rd_index] = rd_data_byte;
    crc_rd_index++;
    
    return rd_data_byte;
 }

 void rom_rd_float (U16 ee_addr, void * float_data_ptr)
 {
    /// ������ 4 - ����. ���������� ���� float �� rom
    
    // ���������� ��������� �� ������� �����������. �������.
    // ���� float, ���������� ��������� ���������� �� rom � ����������
    // ��� ������ ����������� ����� ���������
    
    U8 buf;
    U8 * dataByte_ptr = float_data_ptr; // ��������� ��������� (�����)
    // ���������� ��� ������
    U8 k = 0;
    U8 i = sizeof (float);
    
    //Lcdsetcursor (0x50);
    //lcdPutCh ('b');
    
    while (k < i)
    {
       //* dataByte_ptr = my_arr[k];
       buf = rom_rd_byte (ee_addr); // ������ ����� �� ������
       * dataByte_ptr = buf; // ���. ����� ����� �� ������ ���������� ����������
       //LcdPutU16 (buf, 3) ;
       //lcdPutCh ('_');
       dataByte_ptr++; // ��������� ������ ����� ����������
       ee_addr++; // ��������� ������ rom
       k++; // ��������� ��������� ����� ������
    }

    //LCDMsg ("adr = ");
    //LcdPutU16 ( (U32) ee_addr * 1000, 4) ;
    //delay_ms (1000);
    //Lcdsetcursor (0x40);
    
    
    //LCDMsg ("CRC_rd = ");
    //LcdPutU16 ( (U32) CRC_rd, 5) ;
    //Lcdsetcursor (0x50);
    //LCDMsg ("CRC_LSB = ");
    //LcdPutU16 ( (U32) CRC_rd_LSB * 100, 5) ;
 }

 void rom_wr_float (U16 ee_addr, void * float_data_ptr)
 {
    /// ������ 4 - ����. ���������� ���� float � rom
    
    // ���������� ��������� �� �������. ���� float ��� �� ����������.
    // ���������� ��������� ������ ���� ���������� � rom
    
    U8 * dataByte_ptr = float_data_ptr; // ��������� ��������� (�����)
    // ���������� ��� ������
    U8 k = 0;
    U8 i = sizeof (float); // ���������� ������� float � ������ - 4
    //Lcdsetcursor (0);
    //lcdPutCh ('a');
    
    while (k < i)
    {
       //my_arr[k] = *dataByte_ptr;
       //LcdPutU16 (my_arr[k], 3) ;
       //lcdPutCh ('_');
       rom_wr_byte (ee_addr, * dataByte_ptr); // ������ ����� � ��������. ������ � rom
       dataByte_ptr++; // ��������� ������ ����� ����������
       ee_addr++; // ��������� ������ rom
       k++;  // ��������� ��������� ����� ������
    }

    //Lcdsetcursor (0x00);
    //LCDMsg ("CRC_wr = ");
    //LcdPutU16 ( (U32) CRC_Wr, 5);
 }

 static U16 rom_wr_CRC16 (ee_addr, U8 crc_buf)
 {
    U16 CRC_Wr;
    
    CRC_Wr = CRC16 (crc_buf, 14); // ������ CRC16
    
    rom_wr_byte (ee_addr, (CRC_Wr >> 8)); // ������ ��. ����� CRC � rom
    ee_addr++;  // ��������� ������
    rom_wr_byte (ee_addr, (U8) CRC_Wr); // ������ ��. ����� CRC � rom
    
    return CRC_Wr;
 }

 static U16 rom_rd_CRC16 (ee_addr)
 {
    U8 CRC_rd_MSB; // ��. ���� CRC ��� ������
    U8 CRC_rd_LSB; // ��. ���� CRC ��� ������
    U16 CRC_rd; // 16 - ���. CRC
    
    CRC_rd_MSB = rom_rd_byte (ee_addr); // ������ ��. ����� CRC �� rom
    ee_addr++;
    CRC_rd_LSB = rom_rd_byte (ee_addr); // ������ ��. ����� CRC �� rom
    CRC_rd = CRC_rd_MSB << 8; // �������������� CRC
    CRC_rd |= CRC_rd_LSB; // �� ����������� ����
    
    return CRC_rd;
 }

 static int1 rom_rd_sens_data (void)
 {
    int1 _rom_rd_status = 0;
    
    LCDclear ();
    LCDSetCursor (two);
    LCDMsg (" ������ ���...");
    
    sens_type = rom_rd_byte (ROM_Adr); // ��� ������� 0
    ROM_Adr++;
    sens_num = rom_rd_byte (ROM_Adr); // � ������� 1
    ROM_Adr++;
    rom_rd_float (ROM_Adr,&kx_rd); // Kx 2 - 5
    ROM_adr += 4;
    rom_rd_float (ROM_Adr,&ky_rd); // Ky 6 - 9
    ROM_adr += 4;
    rom_rd_float (ROM_Adr,&kz_rd); // Kz 10 - 13
    
    ROM_adr += 4;
    CRC1 = rom_rd_CRC16 (ROM_adr); // ������ ����������� CRC
    CRC2 = CRC16 (crc_buf_rd, 14); // ������ CRC �� ��������� ������
    crc_rd_index = 0;
    ROM_adr = 0x0000;

    if (CRC1 == CRC2)
    {
       _rom_rd_status = 1;
    }

    return _rom_rd_status;
 }

 //------------------ EEPROM func ------------------------------------
 
 //= == == = == == == == = == = Interrupts = == = == == == == == == ==
 #int_EXT
 void int0 (void)
 {
    if (SensErr)
    {
       SensErr = 0;
       ReInit_flag = 1;
    }

    
    else
    {
       
       i2c_start ();
       i2c_write (0x3C); // The default (factory) HMC5883 7 - bit slave address
       // is 0x3C for write operations, or 0x3D for read operations.
       i2c_write (0x03); // pointer
       i2c_stop ();
       
       i2c_start ();
       i2c_write (0x3D); //i2c Read
       
       Xh = i2c_read (); // X MSB
       Xl = i2c_read (); // X LSB
       SumX = (Xh<<8)|Xl; //?????????????? ???????? ????????. ??? ?
       Yh = i2c_read (); // Y MSB
       Yl = i2c_read (); // Y LSB
       SumY = (Yh<<8)|Yl; //?????????????? ???????? ????????. ??? Y
       Zh = i2c_read (); // Z MSB
       Zl = i2c_read (); // Z LSB
       SumZ = (Zh<<8)|Zl; //?????????????? ???????? ????????. ??? Z
       i2c_stop ();
       
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

       
       SensWrData (ConfigRegB, 0xE0); // range = + / - 8.1 Gs
       SensWrData (ModeReg, 0x00); // continuous measurment
    }

    SET_TIMER0 (55770);
    clear_interrupt (int_EXT);
 }

 #int_RDA
 void UART_RXd_isr (void)
 {
    RXd_buf = getc ();  // ?????? ??????? ??????....
    // ??? ??????, ????????? ?? ??????? ?? ???????????
    if (RXd_buf == 'z')  // ???????????? ?????????? ???????? ???. 0... FTDI ???? ????? ??? ????. ????????? ??
    {
       menufl1 = 0;
       menufl2 = 0;
       menufl3 = 0;
       fl2 = 1;
       zero_set1 = 1;
    }

    clear_interrupt (int_RDA); // ????? ????? ??????????
 }

 #int_TIMER0
 void INT_TIMER0_isr (void)
 {
    SET_TIMER0 (55770);
    clear_interrupt (int_TIMER0);
    SensErr = 1;
 }

 //= == == = == == == == = == = Interrupts = == = == == == == == == ==
 
 void main  ()
 {
// ����� ������������� ���������������

 
/*  
///////////////////////////////////////////////////////////////////////////////  
   /// ������������ ���

   //float kx = 1.058935361; // ������ ������������ ������� � 2 
   //float ky = 1.20824295;
   //float kz = 1.031481481;
   
   //float kx = 1.041121495;   // ������ ������������ ������� � 1
   //float ky = 1.141393443;
   //float kz = 1.023897059;
   
   //float kx = 1.092291928;   // ������������ ������� � 1 21.04
   //float ky = 1.170930426;
   //float kz = 1.042684161;
     
   //float kx = 1;   // ��� �������������
   //float ky = 1;
   //float kz = 1;
      
   //float kx = 1.0778792;   // ������������ ������� � 2 ���. ����� 21.04
   //float ky = 1.19226638;
   //float kz = 1.06812933;
   
   //float kx = 1.07537299;   // ������������ ������� � 1 ���. ����� 21.04
   //float ky = 1.173361522;
   //float kz = 1.061591431;
   
   //float kx = 1.0517;     // ������������ ������� � 2 ���. 28.12.16
   //float ky = 1.2266;
   //float kz = 1.0406;
   
   //float kx = 1.0747;     // ������������ ������� � 1 ���. 28.12.16
   //float ky = 1.1824;
   //float kz = 1.0650;
   
     
   U16 sens_type = 30;
   U16 sens_num = 4;

   U16 ROM_Adr = 0x0000;
   U16 CRC_Wr;
   U16 CRC1 = 0;
   U16 CRC2 = 0; 

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
   //enable_interrupts(GLOBAL);

   LCDInit();
   LcdWelcome();
   //SensInit();
   LCDSetCursor(two);
   LCDMsg(" ������ � ���...");
    
   rom_wr_byte(ROM_Adr,sens_type);     // ��� �������   0
   rom_wr_byte (++ROM_Adr, sens_num);      // � �������     1
   rom_wr_float(++ROM_Adr,&kx);          // Kx            2-5 
   ROM_adr += 4;
   rom_wr_float(ROM_Adr,&ky);          // Ky            6-9
   ROM_adr += 4;
   rom_wr_float(ROM_Adr,&kz);          // Kz            10-13
   
   ROM_Adr += 4;
   CRC1 = rom_wr_CRC16(ROM_Adr,crc_buf_wr);
   crc_wr_index = 0;
   
   sens_type = 0;
   sens_num  = 0;
   
   LCDclear();
   
   while(true){
   
   ROM_Adr = 0x0000;
   
   kx = 0;
   ky = 0;
   kz = 0;
   
   sens_type = rom_rd_byte(ROM_Adr);               // ��� �������   0
   ROM_Adr++;
   sens_num  = rom_rd_byte(ROM_Adr);               // � �������     1
   ROM_Adr++;
   rom_rd_float(ROM_Adr,&kx);                      // Kx            2-5 
   ROM_adr += 4;
   rom_rd_float(ROM_Adr,&ky);                      // Ky            6-9
   ROM_adr += 4;
   rom_rd_float(ROM_Adr,&kz);                      // Kz            10-13
   ROM_adr += 4;
   CRC2 = rom_rd_CRC16(ROM_adr);                  // ������ CRC �� ��������� ������
   
   Lcdsetcursor(0x00);
   LCDMsg("kx=");
   LcdPutS16((S32)(kx*1000),5);
   Lcdsetcursor(0x40);
   LCDMsg("ky=");
   LcdPutS16((S32)(ky*1000),5);
   Lcdsetcursor(0x10);
   LCDMsg("kz=");
   LcdPutS16((S32)(kz*1000),5);
   
   //Printf("CRC1=%LX\n",CRC1);
   //Printf("CRC2=%LX\n",CRC2);
   
   for(U8 i =0; i < sizeof(crc_buf_wr); i++)
   {
      //Printf("CRC_buf_wr =%LX CRC_buf_rd=%LX\n",crc_buf_wr[i], crc_buf_rd[i]);
      Printf("__");
      Printf("CRC_buf_wr =%LX\n",crc_buf_wr[i]);
      
      delay_ms(500);
   }
   Printf("\n\r");
   Printf("\n\r");
   //Printf("CRC1=%LX\n",CRC1);
   crc_rd_index = 0;
   
   delay_ms(500);
   
   } // while
 } // main
///////////////////////////////////////////////////////////////////////////////  
*/



 /**/
//=============================================================================
   /// ����� ���������


   
    int1 rom_rd_status = 0;
    
    TRB0 = 1; // DRDY
    TRB1 = 0;
    
    TRB3 = 0;
    TRB4 = 0;
    TRB5 = 0;
    TRC0 = 0;
    TRC1 = 0;
    TRC2 = 0;
    TRC5 = 0;
    TRC3 = 1;
    TRC4 = 1;
    TRC6 = 0; // UART1 - TX
    TRC7 = 1; // UART1 - RX
    
    EXT_int_EDGE (L_TO_H);
    enable_interrupts (int_RDA);
    enable_interrupts (int_EXT);
    SETUP_TIMER_0 (T0_INTERNAL|T0_DIV_128);
    SET_TIMER0 (55770);
    enable_interrupts (GLOBAL);
    
    LED = 1;
    LCDInit ();
    LcdWelcome ();
    
    for (U8 i = 0; i < 10; i++)
    {
       rom_rd_status = rom_rd_sens_data (); // ������ ��� �������
       
       if (rom_rd_status)
       {
          break;
       }

       delay_ms (100);
    }
   
    LCDSetCursor (0x10);
    
    if (rom_rd_status)
    {
       LCDMsg ("       OK!      ");
       delay_ms (1000);
       LCDclear ();
       
       LCDSetCursor (0x00);
       LCDMsg ("  ��� �������:  ");
       LCDSetCursor (0x40);

       if (sens_type == 30)
       {
          LCDMsg ("   3 - ������   ");
       }

       else
       {
          LCDMsg ("   1 - ������   ");
       }
       
       LCDSetCursor (0x50);
       LCDMsg ("������ N: ");
       LCDPutU16n ( (U16) sens_num, 3) ;
       
       delay_ms (2000);
       LCDclear ();
       
       Lcdsetcursor (0x00);
       LCDMsg ("������������:");
       Lcdsetcursor (0x40);
       LCDMsg ("Kx = ");
       LcdPutS16 ( (S32) (kx_rd * 1000), 5);
       Lcdsetcursor (0x10);
       LCDMsg ("Ky = ");
       LcdPutS16 ( (S32) (ky_rd * 1000), 5);
       Lcdsetcursor (0x50);
       LCDMsg ("Kz = ");
       LcdPutS16 ( (S32) (kz_rd * 1000), 5);
       
       delay_ms (2000);
       LCDclear ();
    }
    else
    {
       LCDMsg ("    ������..    ");
       delay_ms (1000);
       kx_rd = 1.0;
       ky_rd = 1.0;
       kz_rd = 1.0;
       LCDSetCursor (four);
       LCDMsg ("�� ����������");
    }

    SensInit ();
    delay_ms (100);
    enable_interrupts (int_TIMER0);
    
    while (true)
    { 
       if (int_fl)
       {  // ������� ����� ������
          SensRdAll ();
       }
     
       if (SensErr)
       {  // ������ �� ���������
          LCDSetCursor (one);
          LCDMsg ("    ������     ");
          LCDSetCursor (two);
          LCDMsg ("      ��       ");
          LCDSetCursor (three);
          LCDMsg ("   ���������!  ");
          LCDSetCursor (four);
          LCDMsg ("               ");
          Printf ("x - 10000\n") ;
       }

       if (ReInit_flag)
       {  // ������� ��������������� �������
          // ��� �����. ������� ��������� �������������
          // ��� �������������� �������� ���������
          SensErr = 0;
          disable_interrupts (int_TIMER0);
          delay_ms (300);
          
          for (U8 i = 0; i < 10; i++)
          {
             rom_rd_status = rom_rd_sens_data (); // ������ ��� �������
             if (rom_rd_status)
             {
                break;
             }

             delay_ms (100);
          }
         
          //rom_rd_status = 0;          //// ����� �������������, �� ������� ��
          
          LCDSetCursor (0x10);
          
          if (rom_rd_status)
          {
             LCDMsg ("       OK!      ");
             delay_ms (1000);
             LCDclear ();
       
             LCDSetCursor (0x00);
             LCDMsg ("  ��� �������:  ");
             LCDSetCursor (0x40);

             if (sens_type == 30)
             {
                LCDMsg ("   3 - ������   ");
             }

             else
             {
                LCDMsg ("   1 - ������   ");
             }
             
             LCDSetCursor (0x50);
             LCDMsg ("������ N: ");
             LCDPutU16n ( (U16) sens_num, 3) ;
             
             delay_ms (2000);
             LCDclear ();
             
             Lcdsetcursor (0x00);
             LCDMsg ("������������:");
             Lcdsetcursor (0x40);
             LCDMsg ("Kx = ");
             LcdPutS16 ( (S32) (kx_rd * 1000), 5);
             Lcdsetcursor (0x10);
             LCDMsg ("Ky = ");
             LcdPutS16 ( (S32) (ky_rd * 1000), 5);
             Lcdsetcursor (0x50);
             LCDMsg ("Kz = ");
             LcdPutS16 ( (S32) (kz_rd * 1000), 5);
             
             delay_ms (2000);
             LCDclear ();
          }

          else
          {
             LCDMsg ("    ������..    ");
             delay_ms (1000);
             kx_rd = 1.0;
             ky_rd = 1.0;
             kz_rd = 1.0;
             LCDSetCursor (four);
             LCDMsg ("�� ����������");
          }

          ReInit_flag = 0;
          SensInit ();
          SensInit ();
          delay_ms (100);
          enable_interrupts (int_TIMER0);
       }

       if (!SB2) fl2 = 1; // �������� ������� ���. 0
       
    } // while
 }  // main
 
//=============================================================================
/**/
