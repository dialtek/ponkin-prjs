// �������� ��� ������ PoE ��� �������
// 28.05.15

// ���� ������� ��������������..
   U8 Mx_ch_code[9] = {0, 0x76, 0x54, 0x32, 0x10};

   U8 PGA;
   U8 PGA_val = 3; // PGA = 8
   U8 Sps_buf=0;
   
   U8 flash_wr_data [] = {0,0,0,0}; // ��������� ������� ��� ������ �� ����
   U8 Aver_Wr = 0;
   U8 Sps_Wr = 0;
   U8 CRC_Wr = 0;
   U8 ADC_select = 0; // ���� ������ ���: 1�� ��� 2��

   int1 meas_stop_fl = 0;
   int1 reset_fl = 0;    // ���� ������ �������
   int1 stop_fl = 0;
   
   U8 NumAver = 1;       // ������ ����������
   U8 ADC_sps_var = 2;   // ���������� ���������� ������ ��� - 10sps default
   U8 CRC1=0xFF,CRC2=0xFF, EE_CRC_buf;   // ��������� EEPROM CRC
   U8 flash_rd_data[4]; // ��������� ������� ��� ������ �� ����

   //Ma - Moving Average
   S32 Ch_buf[8][128];  // ����� ����������� �������� ��� �1
   S32 Ch_buf_sum;     // ����� ������ ����������� �������� ��� �1

   U8 Ma_buf_index = 0; // ������ �������� ��������. �����.
   U8 Ma_buf_size = 5;  // ������ ������!!!

   U8 state;
   U16 tmp=0;

//-------------------- ������ � ���������� ��� ------------------------------//

static U8 RdReg(U8 RegName)
{
   U8 RegValue = 0; 
   //1st Command Byte: 0001 rrrr where rrrr is the address of the first register to read.
   //2nd Command Byte: 0000 nnnn where nnnn is the number of bytes to read � 1
   ADC_CS = 0;
   delay_us(1);
   Spi_write2(0x10+RegName); // 1st Command Byte,??????? ??????
   Spi_write2(0x00); // 1st Command Byte, ?????? ?????? ???? ????
   delay_us(8); // 50 CLK_IN PEDIODS
   RegValue = Spi_read2(0);
   delay_us(1);
   ADC_CS =1;
   delay_us(1);
   Return RegValue;  
}

static void WrReg(U8 RegName,CommandByte)
{
   ADC_CS = 0;
   ADC2_CS = 0;
   delay_us(5);
   Spi_write2(0x50+RegName); // 1st Command Byte: 0101 (0x50) rrrr where rrrr is the address to the first register to be written.
   delay_us(10);
   Spi_write2(0);         // 2nd Command Byte: 0000 nnnn where nnnn is the number of bytes to be written � 1.
   delay_us(10);
   Spi_write2(CommandByte);
   delay_us(10);
   ADC_CS = 1;
   ADC2_CS = 1;
 
   delay_us(20);
}
//---------------------------------------------------------------------------//

//==================== ��������� � �������������� ��� =======================//

static void ADC_sps_set(U8 SPS){
                                                          
   Sps_buf = SPS;
   WrReg(DRATE,SPS); 
   delay_us(20);  
}

static void ADC_set_PGA(u8 _PGA_val){
  
/* PGA
000 = 1 (default)
001 = 2
010 = 4
011 = 8
100 = 16
101 = 32
110 = 64
111 = 64*/
/**/

// PGA ������������� ��� ������� 

   switch (_PGA_val){
      case 0:
       WrReg(ADCON,0);
       PGA = 1;
      break;
      
      case 1:
       WrReg(ADCON,1);
       PGA = 2;
      break;
      
      case 2:
       WrReg(ADCON,2);
       PGA = 4;
      break;
      
      case 3:
       WrReg(ADCON,3);
       PGA = 8;
      break;
      
      case 4:
       WrReg(ADCON,4);
       PGA = 16;
      break;
      
      case 5:
       WrReg(ADCON,5);
       PGA = 32;
      break;
      
      case 6:
       WrReg(ADCON,6);
       PGA = 64;
      break; 
   }
   delay_us(20);
}

static void ADC_SelfCal(){
                     
   ADC_CS = 0;
   ADC2_CS = 0;
   delay_us(1);
   
   Spi_write2(0xF0);
   delay_us(1);
   
   ADC_CS = 1;
   ADC2_CS = 1;
   
   While(ADC_DRDY | ADC2_DRDY) { }   // ���� ���������� ����� ���
    
   /*
   Switch (Sps_buf) {     
    
      case 0xF0:   
       delay_us(220);        
        break;                      
      
      case 0xE0:
       delay_us(255); 
        break;
        
      case 0xD0:
       delay_us(315); 
        break;
        
      case 0xC0:
       delay_us(445); 
        break;
        
      case 0xB0:
       delay_us(685); 
        break;
        
      case 0xA1:
       delay_ms(1);
       delay_us(185);               
        break;      
        
      case 0x92:
       delay_ms(5);
        break;
        
      case 0x82:
       delay_ms(10);
       delay_us(200);
        break;
                   
      case 0x63:
       delay_ms(21); 
        break;
        
      case 0x43:
       delay_ms(41); 
        break;
        
      case 0x23:
       delay_ms(101); 
        break;         
            
      case 0x13:
       delay_ms(201); 
        break;                          
     }
     */
}

static void ADC_init(){
   
  WrReg(STATUS,2);   // ���. ������� �����
  delay_us(20);

   if(ADC_sps_var>8)  ADC_sps_var = 8;
   // ��������� sps
   switch (ADC_sps_var){                // �������� �������� �������� ��������� ��� 
    
      case 0: ADC_sps_set(0x03);  break; // 2,5   sps
      case 1: ADC_sps_set(0x13);  break; // 5   sps
      case 2: ADC_sps_set(0x23);  break; // 10   sps
      case 3: ADC_sps_set(0x43);  break; // 25   sps
      case 4: ADC_sps_set(0x63);  break; // 50   sps
      case 5: ADC_sps_set(0x82);  break; // 100  sps
      case 6: ADC_sps_set(0x91);  break; // 500  sps
      case 7: ADC_sps_set(0xA1);  break; // 1000 sps
      case 8: ADC_sps_set(0xC0);  break; // 3750 sps
      case 9: ADC_sps_set(0xd0);  break; // 7500  sps
      case 10: ADC_sps_set(0xe0);  break; // 15000 sps
      case 11: ADC_sps_set(0xf0);  break; // 30000 sps
      }
      
   ADC_set_PGA(PGA_val);    // ���. PGA
   ADC_SelfCal();      // �������������� ����� ��� 
   delay_us(100);
}
//===========================================================================//

//---------------------- ���. ������� � ������ ��� --------------------------//

static void SYNC_ADC(U8 command)
  { /// ������������� ���
  
   //command 0 - �� ������ �� ���� ���
   //command 1 - ������ ��� 1
   //command 2 - ������ ��� 2
   
   switch(command)
   {
         case 0:     
            ADC_SYNC = 1; 
            ADC2_SYNC = 1;
         break;
         
         case 1: 
            ADC_SYNC = 0; 
            delay_us(20);
            ADC_SYNC = 1;
         break;
         
         case 2: 
            ADC2_SYNC = 0; 
            delay_us(20);
            ADC2_SYNC = 1; 
         break;
   }
  }

static void ADC_select(U8 command)
  { /// ����� ���
  
   //command 0 - �� ������ �� ���� ���
   //command 1 - ������ ��� 1
   //command 2 - ������ ��� 2
   
   switch(command)
   {
         case 0: ADC_CS = 1; ADC2_CS = 1; break;
         case 1: ADC_CS = 0; ADC2_CS = 1; break;
         case 2: ADC_CS = 1; ADC2_CS = 0; break;
   }
  }

static void ADC_setCh(U8 Ch_Number, U8 ADC_number){

 // ���. ������� ���
 // 1 ����� ������������ - 4 ����� ��� �� ����� (13(+) � 12(-) �����) � ��.
 
  ADC_select(ADC_number); // ����� ���
  delay_us(2);
 
  Spi_write2(0x50+MUX);  // ���. ����� ���   
  delay_us(10);
  Spi_write2(0);         
  delay_us(10);
  Spi_write2(Mx_ch_code[Ch_Number]);
  
  ADC_select(0);
  delay_us(20);  
}

static S32 ADC_read(U8 ADC_number)
  {
  
  ADC_select(ADC_number); // ����� ���
  
  S32 ADC_RByte1=0;  // ��. ���� ������ ���
  S32 ADC_RByte2=0;  // ��. ���� ������ ���
  S32 ADC_RByte3=0;  // ��. ���� ������ ���
  
  S32 ADC_RByte_Sum; // ��������� ������� ��� - 24 ����
  
  float Vin;         // ���������� ���������� 

  Spi_write2(0x01);        // ������� ������ Rdata
  delay_us(20);
  ADC_Rbyte1 = Spi_read2(0);   // ������
  ADC_Rbyte2 = Spi_read2(0);
  ADC_Rbyte3 = Spi_read2(0);
  
  ADC_select(0); // ����� ������ ���
  
  // ���������� ���� ���� �������� ���
  ADC_RByte_Sum = ((S32)ADC_Rbyte1<<24) | ((S32)ADC_Rbyte2<<16) | ((S32)ADC_Rbyte3<<8);
  ADC_RByte_Sum = ADC_RByte_Sum/256; // ���������� 24 ��� � 32-������ ����������
  
  Vin = ((ADC_RByte_Sum*5)/(8388608.0*PGA)); // ������ U
  
  return Vin*uV; // ������� ����������������� U 
  
  }

static S32 ADC_read_aver(U8 ADC_number,U8 ADC_ch)
{
 S32 _Ch_buf_sum; // ��������. ��� �������� �����. ������. ��������
 
 Ch_buf[ADC_ch][Ma_buf_index] = ADC_read(ADC_number); // ��������� ������ ���. � �����
 
 for(U8 i = 0; i < Ma_buf_size; i++)                  // ��������� ���� �����
 {
   Ch_buf_sum += Ch_buf[ADC_ch][i];   // ������ ������� ������ �� �����
 } 
 
 if(Ma_buf_index == Ma_buf_size)
 {
   Ch_buf_sum = Ch_buf_sum/Ma_buf_size; // ��������� �������
 }
 else 
 {
   Ch_buf_sum = Ch_buf[ADC_ch][Ma_buf_index];
 }
 
 
  _Ch_buf_sum = Ch_buf_sum; // ������������� ��� ��������
 Ch_buf_sum = 0;           // ����� ���� ����������
 
 return _Ch_buf_sum;

}

//---------------------------------------------------------------------------//
