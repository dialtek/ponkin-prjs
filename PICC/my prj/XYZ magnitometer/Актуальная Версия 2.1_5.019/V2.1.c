
/******************************************************/
/* Software V2.3 for magnetic induction's tester V2.1 */
/******************************************************/
// ��������� ��������� 15.03.17

#include <V2.1.h>
#include <stdio.h>
#include <LCD for V2.1.c>

#define TLV493D_rd_addr 0xbd     // i2c ����� ������� ��� ������ 
#define TLV493D_wr_addr 0xbc     // i2c ����� ������� ��� ������

#define TLV493D        37        // ID ������� Bmax = 1,3 kGs
#define HMC5883l       30        // ID ������� Bmax = 8,1 Gs

unsigned int1 int_fl = 0;
unsigned int1 SensErr = 0;
unsigned int1 set_zero_fl = 0;


char  ConfigRegA = 0x00, ConfigRegB = 0x01, ModeReg = 0x02, EEprom_adr = 0xA0;
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
float kx = 1.0;   // ������������� ������������
float ky = 1.0;
float kz = 1.0;

U8 crc_buf_wr[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
U8 crc_buf_rd[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
U8 crc_wr_index = 0;
U8 crc_rd_index = 0;

U16 coord_sys = 0;      // ���������� ������ ������� ��������� ���������
U16 sens_type;          // ��� ������� => 37 - TLV493D, 30 - HMC5883l        
U16 sens_num;           // � ������� � ���� �������
U16 ROM_Adr = 0x0000;
int1 rom_rd_status = 0; // ���� ������� ��������� ���

U16 CRC_Wr;
U16 CRC1 = 0;
U16 CRC2 = 0; 

U8 TLV493D_frm_cnt = 0; // ���������� ����� �������� ��������� ������� TLV493D
U8 wr_ptr = 0, rd_ptr = 0;                         // �������� ������ � ������ � ������ UART
U8 rx_buf[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}; // ����� ��� ����. ��������� ������

//****************** Sensor 1 funcs ************************************
void SensWrData(unsigned int8 Adr, Data)
{
   
   i2c_start ();
   i2c_write (0x3C);

   // The default (factory) HMC5883 7 - bit slave address
   // is 0x3C for write operations, or 0x3D for read operations.
   i2c_write (Adr);
   i2c_write (Data);
   i2c_stop ();
}
 
char SensRdData(char Adr)
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
    
void HMC5883l_Init ()
{
   
   //SensWrData (ConfigRegA, 0x14); // F = 30 Hz / 1
   SensWrData (ConfigRegA, 0x18); // F = 75 Hz / 1
   SensWrData (ConfigRegB, 0xE0); // range = + / - 8.1 Ga
   SensWrData (ModeReg, 0x00); // continuous measurment mode
   //SensWrData (ModeReg, 0x01); // single measurment mode
}

signed int16 SelfCal()
{
   
   unsigned int16 Xh = 0;
   unsigned int8 Xl = 0;
   unsigned int16 Yh = 0;
   unsigned int8 Yl = 0;
   unsigned int16 Zh = 0;
   unsigned int8 Zl = 0;
   
   HMC5883l_Init();
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
   return 1;
}

void SensRdAll()
{
   
   if (set_zero_fl)
   {
      // ���. 0
      
      LCDClear ();
      Lcdsetcursor (0);
      LcdMsg (" ��������� ���� ");
      SumX0 = SumX;
      SumY0 = SumY;
      SumZ0 = SumZ;
      delay_ms (1000);
      set_zero_fl = 0;
   }

   
   average_Zg = SumZ - SumZ0; //(average_Zg / 10) - SumZ0;
   average_Yg = SumY - SumY0;
   average_Xg = SumX - SumX0;
   
   //y = (8.1 * x) / 2048; 8.1 / 2048 = 0.0039550781252
   
   Xd = average_Xg * 0.0039550781252;
   Xd *= kx; // ��������� �� ����������� ����������� �� ���
   Yd = average_Yg * 0.0039550781252;
   Yd *= ky; // ��������� �� ����������� ����������� �� ���
   Zd = average_Zg * 0.0039550781252;
   Zd *= -kz; // ��������� �� ����������� ����������� �� ���
   // ������� �������� ����������� ��� Z ��� ���������� ������ ���������
   // ����� �������� � ������

   
   // �������� ���� Bx, By, Bz ��������� �������� ��������� ��������� //

   Printf ("x%05Ldh\n", ( (S32) (Xd * 1000))); // Zd �������� �� �� �������� ���� � ��
   Printf ("y%05Ldh\n", ( (S32) (Yd * 1000))); // 
   Printf ("z%05Ldh\n", ( (S32) (Zd * 1000))); // Zd
   LcdSetCursor (one);
   LcdMsg ("Bx = ");
   LcdPutS16 (Xd * 1000, 4); // zd
   LcdMsg (" ��. ");
   LcdSetCursor (two);
   LcdMsg ("By = ");
   LcdPutS16 (Yd * 1000, 4);
   LcdMsg (" ��. ");
   LcdSetCursor (three);
   LcdMsg ("Bz = ");
   LcdPutS16 (Zd * 1000, 4); // Xd
   LcdMsg (" ��. ");
   int_fl = false;
}

//****************** Sensor 1 funcs ************************************

//////////////////// Sensor 2 funcs ////////////////////////////////////  
 void TLV493D_reset()
{
    i2c_start();
    i2c_write (0x00); 
    i2c_stop();
}
 
 U8 TLV493D_init()
{
//!      // ����� ���. ������� ��������� ������� �������� ��������� 7, 8, 9 �������
//!      // ��� ���������� ������ ���� �������� � ���������������� ��������.
//!
       S16 reg7data = 0;    // ���������� ��� ����. ��������� �������� �������
       S16 reg8data = 0;
       S16 reg9data = 0;

//!      //------- 1 ���� - ������ ��������� ������������ ������� -------// 
      
       i2c_start ();
       i2c_write (TLV493D_rd_addr); // ������ ���������
       i2c_read();           // Bx (0H)
       i2c_read();           // By (1H)
       i2c_read();           // Bz (2H)
       
       i2c_read();           // Temp (3H) Temp. (11�8) FRM CH
       i2c_read();           // Bx2 (4H)  Bx (3�0) By (3�0)
       i2c_read();           // Bz2 (5H)
       
       i2c_read();                      // Temp2 (6H)
       reg7data = i2c_read();           // FactSet1 (7H)
       reg8data = i2c_read();           // FactSet2 (8H)
       reg9data = i2c_read();           // FactSet3 (9H)
       i2c_stop ();

//!      // ������������� ������� 
//!      // ������ ���������� ���� ����������� ����� ����� �� ������ �����������������, 
//!      // ����� master-controlled
//!      // ���, ������� ��������� ������� �� ������� ������ ��������� �������, �� ����� 3.3 ���
//!    
       i2c_start ();
       i2c_write (TLV493D_wr_addr); //  ������ ������������
       i2c_write (0x00);            //  Reg 0, Reserved register, must write 0's
       
       i2c_write( 0 << 7 |          //  Reg 1, parity disabled in Reg3
                  0 << 5 |          //  define the slave address, dont use, ADDR = 1, pulled high on PCB  
 ((reg7data & 0x18) << 3)|          //  Bits must correspond to bits 4:3 from read register 7H
                  0 << 2 |          //  If "0" INT (interrupt pulse) disabled
                  1 << 1 |          //  If "1" fast mode enabled
                        1);         //  If "1" - Low power mode, f = 100 Hz
                  
                  
       i2c_write(reg8data);         //  Reg 2, Bits must correspond to bits 7:0 from read register 8H
       
       i2c_write( 1 << 7 |          //  Reg 3, temperature measurement disabled
                  1 << 6 |          //  If '1' period is 12ms, if '0' period is 100ms     
                  0 << 5 |          //  If "0" parity test disabled
          (reg9data & 0x1f));       //  Bits must correspond to bits 4:0 from read register 9H.        
       i2c_stop ();
       
       if (reg8data < 0xff) return 1;
       else return 0;
}

 float TLV493D_calc_field (S16 nibble_h, S16 nibble_l)
 {
      // ������ �������� ���������� ���� �� ��� X �������
      // nibble_h - MSB, nibble_l �������� ������� �������� ������ ��� �
         
      S16 fi = 0;          // ��� �������� �������� ���������� ����
      float fl = 0;        // ��� �������� ���������� ���� � ��
      
      fi = (nibble_h << 4) | nibble_l;
      if ( fi >= 2048)   fi = fi - 4096;  // Interpret bit 12 as +/- 
      
      // LSB = 0.098 mT -> 0.98 Gs
      fl = fi * 0.098;    // ������� �� �������� ��� � mT
      fl *= 10;           // ������� �� mT � ������
      
      return fl;

  }
 
 U8 TLV493D_rd_all(U8 coord_sys)
 {
        
       S16 xh, yh, zh = 0;  // ��. ����� ������
       S16 xl, yl, zl = 0;  // ��. ���������
       S16 bz2, bx2by2, frame_ctr = 0; // �������� �������
       S16 x, y, z = 0;
       S16 coodr_buf = 0;

       U8 status; // 1 - ������ ��, 0 - ������ ������, 2 - ��������� �������������
 
        // ������ ������
       i2c_start ();
     
       i2c_write (TLV493D_rd_addr);     // ������ ���������
       xh = i2c_read();                 // Bx (0H)
       yh = i2c_read();                 // By (1H)
       zh = i2c_read();                 // Bz (2H)
       
       frame_ctr = i2c_read();          // Temp (3H) Temp. (11�8) FRM CH
       bx2by2 = i2c_read();             // Bx2 (4H)  Bx (3�0) By (3�0)
       bz2 = i2c_read();                // Bz2 (5H)
     
       i2c_read();                      // ���������� ���������� ��� 10 ���������
       i2c_read(); 
       i2c_read(); 
       i2c_read(); 
     
       i2c_stop ();
       
       if(frame_ctr == 0xff) status = 0; // ������ �� �����
       
       // ��������� ������� �������� �������� ��������� � �����
       else if(TLV493D_frm_cnt == (U8)frame_ctr) 
       {// ������ ���������
         TLV493D_reset(); // ����� ��������� �������
         TLV493D_init();  // �������������
       }
       
       else                                  // ���������, ��� ��
       {
         TLV493D_frm_cnt = frame_ctr;   // ����. ������ �������� �������� ���������
         
         xl = bx2by2 >> 4;      // ��������� ��. ��������� �������� �� ��� � 
         yl = bx2by2 & 0x0f;    // ��������� ��. ��������� �������� �� ��� Y 
         zl = bz2 & 0x0f;       // ��������� ��. ��������� �������� �� ��� Z  
       
         x = (S16)(kx * TLV493D_calc_field(xh, xl));    // �������� � ������� ��. � ��. ���� ��� ������� ���� �� X
         y = (S16)(ky * TLV493D_calc_field(yh, yl));    // �������� � ������� ��. � ��. ���� ��� ������� ���� �� Y
         z = (S16)(kz * TLV493D_calc_field(zh, zl));    // �������� � ������� ��. � ��. ���� ��� ������� ���� �� Z
         
         switch(coord_sys)       // ������ �������� ������� ���������
         {
            case 0: break;       // �� ���������, ������ �� ������
            //=====
            case 1:              // 1 ������� ��������� ������� ���������
               coodr_buf = x;    // ������� ������ ������ ����
               x = z;
               z = coodr_buf;
               break;       
            //=====
            case 2:              // 2 ������� ��������� ������� ���������
               coodr_buf = y;    // ������� ������ ������ �����
               y = z;
               z = coodr_buf;
               break;       
            //=====
            default: break;
         
         }
         
         if (set_zero_fl)
         {
           // ���. 0
      
          LCDClear ();
          Lcdsetcursor (0);
          LcdMsg (" ��������� ���� ");
          SUMX0 = x;  // ����. �������� �������� ���������� ����
          SUMY0 = y;
          SUMZ0 = z;
          delay_ms (1000);
          set_zero_fl = 0;
         }
         
         x = x - SUMX0; // ����� �������� ����
         y = y - SUMY0;
         z = z - SUMZ0;
         
        // �������� �� �� �������� ���� � ��
         Printf ("x%05Ldt\n", x); 
         Printf ("y%05Ldt\n", y);
         Printf ("z%05Ldt\n", z);

         LcdSetCursor (one);
         LcdMsg (" Bx = "); LCDPutS16n (x, 4); LcdMsg (" ��. ");
         LcdSetCursor (two); 
         LcdMsg (" By = "); LCDPutS16n (y, 4); LcdMsg (" ��. ");
         LcdSetCursor (three);
         LcdMsg (" Bz = "); LCDPutS16n (z, 4); LcdMsg (" ��. ");
         
         status = 1;
       }

       return status;
 
 }

//////////////////// Sensor 2 funcs ////////////////////////////////////


//------------------ EEPROM funcs --------------------------------------
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

 void rom_wr_byte (U16 addr, U8 dataByte)
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

 U8 rom_rd_byte (U16 addr)
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
    
    while (k < i)
    {
       buf = rom_rd_byte (ee_addr); // ������ ����� �� ������
       * dataByte_ptr = buf; // ���. ����� ����� �� ������ ���������� ����������
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

 U16 rom_wr_CRC16 (ee_addr, U8 crc_buf)
 {
    U16 CRC_Wr;
    
    CRC_Wr = CRC16 (crc_buf, 14); // ������ CRC16
    
    rom_wr_byte (ee_addr, (CRC_Wr >> 8)); // ������ ��. ����� CRC � rom
    ee_addr++;  // ��������� ������
    rom_wr_byte (ee_addr, (U8) CRC_Wr); // ������ ��. ����� CRC � rom
    
    return CRC_Wr;
 }

 U16 rom_rd_CRC16 (ee_addr)
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

 int1 rom_rd_sens_data (void)
 {
    int1 _rom_rd_status = 0;

    sens_type = rom_rd_byte (ROM_Adr); // ��� ������� 0
    ROM_Adr++;
    sens_num = rom_rd_byte (ROM_Adr);  // � ������� 1
    ROM_Adr++;
    coord_sys = rom_rd_byte (ROM_Adr); // ������� ��������� 2
    ROM_Adr++;
    rom_rd_float (ROM_Adr,&kx); // Kx 3 - 6
    ROM_adr += 4;
    rom_rd_float (ROM_Adr,&ky); // Ky 7 - 10
    ROM_adr += 4;
    rom_rd_float (ROM_Adr,&kz); // Kz 11 - 14
    
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

void update_rom_data(void)
{
   U16 ROM_Adr = 0x0000;
  // U16 CRC_Wr;
   U16 CRC1 = 0;
  // U16 CRC2 = 0; 

   rom_wr_byte(ROM_Adr,sens_type);     // ��� �������   0
   rom_wr_byte (++ROM_Adr, sens_num);  // � �������     1
   rom_wr_byte (++ROM_Adr, coord_sys); // ���.��������� 2
   rom_wr_float(++ROM_Adr,&kx);        // Kx            3-6 
   ROM_adr += 4;
   rom_wr_float(ROM_Adr,&ky);          // Ky            7-10
   ROM_adr += 4;
   rom_wr_float(ROM_Adr,&kz);          // Kz            11-14
   
   ROM_Adr += 4;
   CRC1 = rom_wr_CRC16(ROM_Adr,crc_buf_wr);
   crc_wr_index = 0;   
}

//------------------ EEPROM funcs --------------------------------------
 
//= == == = == == == == = == = Interrupts = == = == == == == == == ==
 #int_EXT
 void int0 (void)
 {
    signed int16 coodr_buf = 0;
    
    if (SensErr)
    {

       sens_type = 0;
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
       
      // average_X += SumX;
       //average_Y += SumY;
       //average_Z += SumZ;
       //aver_count ++;
       
       //if (aver_count == 5)
       //{
          int_fl = true;
       //   aver_count = 0;
          
       //   average_Xg = average_X;
      //    average_Yg = average_Y;
       //   average_Zg = average_Z;
   
          switch(coord_sys)       // ������ �������� ������� ���������
         {
            case 0: break;       // �� ���������, ������ �� ������
            //=====
            case 1:              // 1 ������� ��������� ������� ���������
               coodr_buf = SumX;    // ������� ������ ������ ����
               SumX = SumZ;
               SumZ = coodr_buf;
               break;       
                           //=====
            case 2:              // 2 ������� ��������� ������� ���������
               coodr_buf = SumY;    // ������� ������ ������ �����
               SumY = SumZ;
               SumZ = coodr_buf;
               break;       
            //=====
            default: break;
         
         }
          
          //average_X = 0;
          //average_Y = 0;
          //average_Z = 0;
       //}

       HMC5883l_Init();
       //SensWrData (ConfigRegB, 0xE0); // range = + / - 8.1 Gs
       //SensWrData (ModeReg, 0x00);    // continuous measurment
    }

    SET_TIMER0 (55770);
    clear_interrupt (int_EXT);
 }

 #int_RDA
 void UART_RXd_isr (void)
 {
    
    
    wr_ptr++;                    // ��������� �������� �����. ����
    rx_buf[wr_ptr & 0x0f]  = RCREG;     // ����. ����� �� ��
  
    clear_interrupt (int_RDA);         // ����� ����� ����������
 }

//= == == = == == == == = == = Interrupts = == = == == == == == == ==

void LCDsensInfoMsg()
{
       LCDclear ();
       LCDSetCursor (one);
       LCDMsg ("��������� ������");
       LCDSetCursor (two);
       LCDMsg ("      ���:      ");
       LCDSetCursor (three);
       
       if (sens_type == TLV493D)  
       {
         LCDMsg ("  Bmax = 1.3 kGS   ");
       }
        else if (sens_type == HMC5883l) 
       {
         LCDMsg (" Bmax = 8.1 GS    ");
       }
       
       else LCDMsg ("   ������ ID    ");
       
       LCDSetCursor (four);
         LCDMsg ("������ N:  ");
       LCDPutU16n ( (U16) sens_num, 3) ;
       delay_ms(2000);
       
       LCDClear();
       Lcdsetcursor (one);
       LCDMsg ("������������:");
       Lcdsetcursor (0x40);
       LCDMsg ("Kx = ");
       LcdPutS16 ( (S32) (kx * 1000), 5);
       Lcdsetcursor (0x10);
       LCDMsg ("Ky = ");
       LcdPutS16 ( (S32) (ky * 1000), 5);
       Lcdsetcursor (0x50);
       LCDMsg ("Kz = ");
       LcdPutS16 ( (S32) (kz * 1000), 5);
       
       delay_ms (2000);
       LCDclear ();

} 

U8 detect_sensors()
{
       U8 status = 0;
       
       rom_rd_status = rom_rd_sens_data (); 
       delay_ms (500);
       
       if      (sens_type == HMC5883l) 
       {
         EXT_int_EDGE (L_TO_H);
         enable_interrupts (int_EXT);
         //SETUP_TIMER_0 (T0_INTERNAL|T0_DIV_128);
         //SET_TIMER0 (55770);
         //enable_interrupts (int_TIMER0);
         status = 30;                   // return sensor id if sucess
         HMC5883l_Init();
       }
       
       else if (sens_type == TLV493D) status = TLV493D_init();
  
       else
      {
         kx = 1.0;
         ky = 1.0;
         kz = 1.0;
      }
    
    return status;
}

U8 ch_to_int(char ch)
{
// �������������� ������� � �����
U8 dg=-1;                                                                        
 
 switch (ch)
   {
      case '0' : dg=0; break;
      case '1' : dg=1; break;
      case '2' : dg=2; break;
      case '3' : dg=3; break;
      case '4' : dg=4; break;
      case '5' : dg=5; break;
      case '6' : dg=6; break;
      case '7' : dg=7; break;
      case '8' : dg=8; break;
      case '9' : dg=9; break;
      default: dg = -1;
   }

   return dg;
}

char get_rx_ch (void)
{                                                     
// Get RX char
char rch;

   if (rd_ptr < wr_ptr) // ����� �� ����
   {
      rd_ptr++;                    // ��������� �������� �������� ����
      rch = rx_buf[rd_ptr & 0x0F]; // ����. �������� �� �������
   }
   else rch = 'x';   
   
   // ������ ���������� �� UART �� ����� ��������� ����������  
   // �� ����. � �����. �������� �������
   disable_interrupts(INT_RDA);    
           
   if ((wr_ptr==rd_ptr) && (wr_ptr > 15)) // ���� ����� ��������                                            
   {  
      wr_ptr=0;                                                                   
      rd_ptr=0;                                                       
   } 

enable_interrupts(INT_RDA);         // ���������� ����������

return rch;
}

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
     
   float kx = 1;   // ��� �������������
   float ky = 1;
   float kz = 1;
      
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
   
     
   U16 sens_type = HMC5883l; //TLV493D;
   U16 sens_num = 18;

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
   LCDSetCursor(two);
   LCDMsg(" ������ � ���...");
//-----------------------------------------------------------------------------       
   rom_wr_byte(ROM_Adr,sens_type);     // ��� �������   0
   rom_wr_byte (++ROM_Adr, sens_num);  // � �������     1
   rom_wr_byte (++ROM_Adr, coord_sys); // ���.��������� 2
   rom_wr_float(++ROM_Adr,&kx);        // Kx            3-6 
   ROM_adr += 4;
   rom_wr_float(ROM_Adr,&ky);          // Ky            7-10
   ROM_adr += 4;
   rom_wr_float(ROM_Adr,&kz);          // Kz            11-14
   
   ROM_Adr += 4;
   CRC1 = rom_wr_CRC16(ROM_Adr,crc_buf_wr);
   crc_wr_index = 0;   
 //-----------------------------------------------------------------------------     
   sens_type = 0;
   sens_num  = 0;
   
   LCDclear();
   
   while(true){
   
   ROM_Adr = 0x0000;
   
   kx = 0;
   ky = 0;
   kz = 0;
   
    sens_type = rom_rd_byte (ROM_Adr); // ��� ������� 0
    ROM_Adr++;
    sens_num = rom_rd_byte (ROM_Adr);  // � ������� 1
    ROM_Adr++;
    coord_sys = rom_rd_byte (ROM_Adr); // ������� ��������� 2
    ROM_Adr++;
    rom_rd_float (ROM_Adr,&kx); // Kx 3 - 6
    ROM_adr += 4;
    rom_rd_float (ROM_Adr,&ky); // Ky 7 - 10
    ROM_adr += 4;
    rom_rd_float (ROM_Adr,&kz); // Kz 11 - 14
    
    ROM_adr += 4;
    CRC1 = rom_rd_CRC16 (ROM_adr); // ������ ����������� CRC
    CRC2 = CRC16 (crc_buf_rd, 14); // ������ CRC �� ��������� ������
   
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

//=============================================================================

   /// ����� ���������
   
    U8 TLV493D_status = 0;
    char rx_byte;       // ���� �������� � ��
    U8 rd_state = 0;    // ������ ���������
    char coef_id = 0;   // ������������� ������ ���������� ��������� � ��
    U16 num_param = 0;  // ��������� �������� ��������� � ��
    
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

    LED = 1;
    
    LCDInit ();
    LCDWelcome ();
    if(detect_sensors() != 0) LCDsensInfoMsg();

    enable_interrupts (int_RDA);
    enable_interrupts (GLOBAL);
//-----------------------------------------------------------------------------   
    while (true)
    { 
       restart_wdt(); 
//-----------------------------------------------------------------------------   
       switch(sens_type) // ������ ���� �������� �������
       {
        case TLV493D:    // ��� - 1.3 kGs
             TLV493D_status = TLV493D_rd_all(coord_sys); // ����� �������� ������
            
             if (TLV493D_status == 1)                    // ������ ���������, ������ �������              
             {
               LCDSetCursor(four);
               LCDMsg(" r"); LCDPutU16(coord_sys, 1);    // ����� �� ������� ������� ���������
               LCDMsg("  1,3 kGs  ");                    // � ���� �������
             }
             else sens_type = 0;      // ����� ������ �������, ��������� ����� �������������
             
        break;
        //===========   
        case HMC5883l:  // ��� - 8 Gs
        
            if (int_fl) // ���� ��� ������� ���� � ���������� �� �������
             {    
               SensRdAll(); // ����� �������� ������
               LCDSetCursor(four);
               LCDMsg(" r"); LCDPutU16(coord_sys, 1); // ����� �� ������� ������� ���������
               LCDMsg("   8,1 Gs ");                  // � ���� �������
             }
             else sens_type = 0;                      // ����� ������ �������, ��������� ����� �������������
        //===========   
        break;
        //===========              
        default: 
               if(detect_sensors() == 0) 
               { 
                  NC_LCDMsg();
                  delay_ms(1000);
               }
               else LCDsensInfoMsg();
               break; 
       }
//-----------------------------------------------------------------------------   
       if (!SB2) set_zero_fl = 1; // �������� ������� ���. 0
//----------------------------------------------------------------------------- 
// ��������� ������

       while(rd_ptr < wr_ptr) // ����� �� ����, ������� ���� 
        {
              U8 temp_buf;                                         
              rx_byte = get_rx_ch();  
              
              // ����� ������� ��������� ������� � ��
              LCDSetCursor(four);
              LCDMsg("             *");

               switch(rd_state)  // �������� ������� ��������� ������ ������
               {
               //-----
                  case 0:        // ��������� ����������� ������
                     switch(rx_byte)
                     {
                        case 'z':            // �������� ������� ���. 0
                           set_zero_fl = 1;  // ���������� ���� ���. 0
                           printf("ok\n\r"); // ������� ������ �� ��
                           rd_state = 0;     // ������� � ��������� ������� ��������� �������
                           break;
                           //=====
                        case 's':            // �������� ������� ������� id � ������� ���������
                           printf("r=");  printf("%01lu,",coord_sys);   // ������� ������� ���������
                           printf("id="); printf("%02lu\n\r",sens_type); // ������� id
                           rd_state = 0;     // ������� � ��������� ������� ��������� �������
                           break;
                           //=====
                        case 'r':            // �������� ������� ���. ������� ���������
                           rd_state = 5;     // ������� � ��������� ������� ������� 
                           break;
                           //=====                           
                        case 'k':            // �������� ������� ������� �������������
                           printf("a"); printf("%04lu",(U16)(kx*1000));  // ������� �����.
                           printf("b"); printf("%04lu",(U16)(ky*1000));
                           printf("c"); printf("%04lu\n\r",(U16)(kz*1000));
                           rd_state = 0;     // ������� � ��������� ������� ��������� �������
                           break;
                           //=====
                        case 'a':            // �������� ������� ���. �����. �
                           rd_state = 1;     // ������� � ��������� ������ ������� ����� �������
                           coef_id = 'a';    // ���������� �������������� ���������
                           break;
                           //=====
                        case 'b':            // �������� ������� ���. �����. b
                           rd_state = 1;     // ������� � ��������� ������ ������� ����� �������
                           coef_id = 'b';    // ���������� �������������� ���������
                           break;
                           //=====
                        case 'c':            // �������� ������� ���. �����. c
                           rd_state = 1;     // ������� � ��������� ������ ������� ����� �������
                           coef_id = 'c';    // ���������� �������������� ���������
                           break;
                           //=====                           
                           
                        default: 
                           printf("cmd error\n\r"); 
                           break;
                     }
                  break;
               //-----
               // ������ ���� ���������� � ����������
               case 1: 
                  temp_buf = ch_to_int(rx_byte);
                  if(temp_buf == -1)   // �������� ������������ ���������                                                           
                  {        
                   rd_state = 0;                                                
                   printf("err p1\n\r");                                            
                   break;
                  }
                                                                        
                  num_param = 0;                                                                 
                  num_param += (U16) temp_buf*1000;                                                      
                  rd_state = 2;                                                             
               break;
               //-----
               case 2: 
                  temp_buf = ch_to_int(rx_byte);
                  if(temp_buf == -1)   // �������� ������������ ���������                                                              
                  {        
                   rd_state = 0;                                                
                   printf("err p2\n\r");                                            
                   break;
                  }                                                                                              
                  num_param += (U16) temp_buf*100;                                                      
                  rd_state = 3;                                                             
               break;
               //-----
               case 3: 
                  temp_buf = ch_to_int(rx_byte);
                  if(temp_buf == -1)   // �������� ������������ ���������                                                      
                  {        
                   rd_state = 0;                                                
                   printf("err p3\n\r");                                            
                   break;
                  }
                  num_param += (U16) temp_buf*10;                                                      
                  rd_state = 4;                                                             
               break;
               //-----
                case 4: 
                  temp_buf = ch_to_int(rx_byte);
                  if(temp_buf == -1)   // �������� ������������ ���������                                                           
                  {        
                   rd_state = 0;                                                
                   printf("err p4\n\r");                                            
                   break;
                  }
                  num_param += (U16) temp_buf;    
                  
                  // ��� 4 ����� ��������� �������� �������
                  switch(coef_id) // ��������� ���������� ����. � ����������
                  {
                     case 'a': 
                        kx = (float) num_param / 1000.0; 
                        if(kx == 0)  { kx = 1.0; num_param += 1000; } // ������ �� ���. ����. = 0
                        break;
                     case 'b': 
                        ky = (float) num_param / 1000.0; 
                        if(ky == 0) { ky = 1.0; num_param += 1000; }  // ������ �� ���. ����. = 0
                        break;
                     case 'c': 
                        kz = (float) num_param / 1000.0; 
                        if(kz == 0) { kz = 1.0; num_param += 1000; }// ������ �� ���. ����. = 0
                        break;
                     default: break;
                  }
                  Printf("%c", coef_id);           // �������� id ������������
                  printf("%04lu\n\r",num_param);   // �������� ������������
                  
                  // ����� ��������� � ������ � ���
                  LCDclear();
                  LCDSetCursor(two);
                  LCDMsg(" ������ � ���...");
                  update_rom_data();         // ������ � ���
                  rd_state = 0;              // ������� � ��������� ������� ��������� �������                                                            
               break; 
               //-----
               case 5: 
                  temp_buf = ch_to_int(rx_byte);
                  if((temp_buf == -1) | (temp_buf > 2))  // �������� ������������ ���������                                                         
                  {        
                   rd_state = 0;             // ������� � ��������� ������� ��������� �������                                               
                   printf("err p\n\r");                              
                   break;
                  }
                  SUMX0 = 0; // ����� �����. ���. 0
                  SUMY0 = 0;
                  SUMZ0 = 0; 
                  coord_sys = (U16)temp_buf;      // ���������� ������� ���������  
                  printf("r=");
                  printf("%01ld\n\r",coord_sys);   // �������� ������ �������� ������� ���������
                  // ����� ��������� � ������ � ���
                  LCDclear();
                  LCDSetCursor(two);
                  LCDMsg(" ������ � ���...");
                  update_rom_data();              // ������ � ���
                  rd_state = 0;                   // ������� � ��������� ������� ��������� �������
                  break;
               //-----
               default: break;
               
               } // switch
               
               // ������� ������� ��������� ������� � ��
              LCDSetCursor(four);
              delay_ms(75);
              LCDMsg("              ");
            }  // while
            
    } // while
 }  // main
//=============================================================================
