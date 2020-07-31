#include "device.h"
#include "PIC32MZ_SPI.h"
#include "ADS1256.h"

#define ADC1_RESET LATBbits.LATB13
#define ADC2_RESET LATDbits.LATD0

#define ADC1_CS LATDbits.LATD5
#define ADC2_CS LATBbits.LATB4

#define ADC1_SYNC LATBbits.LATB12
#define ADC2_SYNC LATBbits.LATB5

#define ADC1_DRDY PORTBbits.RB11
#define ADC2_DRDY PORTBbits.RB3

// ���� ������� �������������� �� ��������� �� ���� ��� ��������
static unsigned char Mx_ch_code[4] = {0x76, 0x54, 0x32, 0x10};

static unsigned char PGA;
static unsigned char PGA_val = 4;       // PGA = 16, +- 312,5
   
static unsigned char Sps_buf=0; 
static unsigned char input_buf_state=1; // ��. ����� ���

static unsigned char ADC_sps_var = 2;   // ���������� ���������� ������ ��� - 10sps default

static unsigned char channel = 0;

static unsigned int meas_status;        // ������ ��� ���������� ���������
static long pkt8_ch[8] = {0,0,0,0,0,0,0,0};
static unsigned char ADC_state = 0;     // ��������� ��������� ������ ������

 unsigned char RdReg(unsigned char RegName)
{
   unsigned char RegValue = 0; 
   //1st Command Byte: 0001 rrrr where rrrr is the address of the first register to read.
   //2nd Command Byte: 0000 nnnn where nnnn is the number of bytes to read – 1
   ADC1_CS = 0;
   //__delay_us(1);
   SPI1_write_byte(0x10+RegName); // 1st Command Byte,??????? ??????
   SPI1_write_byte(0x00); // 1st Command Byte, ?????? ?????? ???? ????
   //__delay_us(8); // 50 CLK_IN PEDIODS

   RegValue = SPI1_read_byte();
   //__delay_us(1);
   ADC1_CS =1;
  // __delay_us(1);
   return RegValue;  
}
 
 void WrReg(unsigned char RegName, unsigned char CommandByte)
{
   ADC1_CS = 0;
   ADC2_CS = 0;
   SPI1_write_byte(0x50+RegName); // 1st Command Byte: 0101 (0x50) rrrr where rrrr is the address to the first register to be written.
   SPI1_write_byte(0);         // 2nd Command Byte: 0000 nnnn where nnnn is the number of bytes to be written – 1.
   SPI1_write_byte(CommandByte);
   int i;
   for(i = 0; i < 2000;i++) { }
   ADC1_CS = 1;
   ADC2_CS = 1;
   
}

 void ADCs_change_SPS(unsigned int SPS)
 {
   if(SPS > ADC_MAX_SPS) 
     SPS = 11;
   
   ADC_sps_var = (unsigned char)SPS; 
   
   ADCs_init(1);
 } 
  
// ��������� � ������������� ���
 void ADC_set_SPS(unsigned char SPS){
                                                          
   Sps_buf = SPS;
   WrReg(DRATE,SPS);
   while(ADC1_DRDY || ADC2_DRDY) { }   // ���� ���������� ����� ���

}

 unsigned int ADCs_get_SPS(void)
 {
   return (unsigned int)ADC_sps_var;
 }
 
 void ADCs_change_PGA(unsigned int PGA)
 {
   if(PGA <= ADC_MAX_RANGE)
     PGA_val = (unsigned char)PGA;
   
   ADCs_init(1);
 }
 
 unsigned int ADCs_get_PGA(void)
 {
   return (unsigned int)PGA_val; 
 }
 
 void ADC_set_PGA(unsigned char _PGA_val){
  
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
   
   while(ADC1_DRDY | ADC2_DRDY) { }   // ���� ���������� ����� ���
}

 void ADC_SelfCal(){
                     
   ADC1_CS = 0;
   ADC2_CS = 0;
   SPI1_write_byte(0xF0);
   SPI1_write_byte(0xF0);
   
   ADC1_CS = 1;
   ADC2_CS = 1;
   
   while(ADC1_DRDY || ADC2_DRDY) { }   // ���� ���������� ����� ���
   
   /*
   Switch (Sps_buf) {     
    
      case 0xF0:   
       __delay_us(220);        
        break;                      
      
      case 0xE0:
       __delay_us(255); 
        break;
        
      case 0xD0:
       __delay_us(315); 
        break;
        
      case 0xC0:
       __delay_us(445); 
        break;
        
      case 0xB0:
       __delay_us(685); 
        break;
        
      case 0xA1:
       ______delay_ms(1);
       __delay_us(185);               
        break;      
        
      case 0x92:
       ______delay_ms(5);
        break;
        
      case 0x82:
       ______delay_ms(10);
       __delay_us(200);
        break;
                   
      case 0x63:
       ______delay_ms(21); 
        break;
        
      case 0x43:
       ______delay_ms(41); 
        break;
        
      case 0x23:
       ______delay_ms(101); 
        break;         
            
      case 0x13:
       ______delay_ms(201); 
        break;                          
     }
     */
}

 void ADCs_init(unsigned char buf_state){
     
   ADC1_RESET = 1; ADC2_RESET = 1;      
   ADC1_CS = 1;    ADC2_CS = 1;
   ADC1_SYNC = 1;  ADC2_SYNC = 1;
    
   SPI1_init();
   SPI2_init();
   
  unsigned char buf_st = buf_state << 1; // ���������� ������� ��. ������
  
  //PGA_val = holding_register[18];
  //if(PGA_val > 6) PGA_val = 4; // PGA = 16, +- 312,5 ��
    
  //ADC_sps_var = holding_register[19];  // SPS    
  //if(ADC_sps_var > 8) ADC_sps_var = 2; // 10 SPS
  
   WrReg(STATUS,buf_st);   // ���. ������� �������

   //if(ADC_sps_var>8)  ADC_sps_var = 8;
   // ��������� sps
   switch (ADC_sps_var){                // �������� �������� �������� ��������� ��� 
    
      case 0: ADC_set_SPS(0x03);  break; // 2,5   sps
      case 1: ADC_set_SPS(0x13);  break; // 5   sps
      case 2: ADC_set_SPS(0x23);  break; // 10   sps
      case 3: ADC_set_SPS(0x43);  break; // 25   sps
      case 4: ADC_set_SPS(0x63);  break; // 50   sps
      case 5: ADC_set_SPS(0x82);  break; // 100  sps
      case 6: ADC_set_SPS(0x91);  break; // 500  sps
      case 7: ADC_set_SPS(0xA1);  break; // 1000 sps
      case 8: ADC_set_SPS(0xC0);  break; // 3750 sps
      case 9: ADC_set_SPS(0xd0);  break; // 7500  sps
      case 10: ADC_set_SPS(0xe0); break; // 15000 sps
      case 11: ADC_set_SPS(0xf0); break; // 30000 sps
      
       default: ADC_set_SPS(0x23);
      }
   
      
   ADC_set_PGA(PGA_val);    // ���. PGA
   ADC_SelfCal();           // �������������� ����� ��� 
   
   ADC_state = SET_CH; 
   ADC_sync(1);
}
//---------------------- ���. ������� � ������ ��� --------------------------//

 void ADC_sync(unsigned char state) { /// ������������� ���

       ADC1_SYNC = state; 
       ADC2_SYNC = state;
  }

 void ADC_select(unsigned char command) { /// ����� ���
  
   //command 0 - �� ������ �� ���� ���
   //command 1 - ������ ��� 1
   //command 2 - ������ ��� 2
   
   switch(command)
   {
         case 0: ADC1_CS = 1; ADC2_CS = 1; break;
         case 1: ADC1_CS = 0; ADC2_CS = 1; break;
         case 2: ADC1_CS = 1; ADC2_CS = 0; break;
   }
   int i;
   for(i = 0; i < 1000;i++) { }
  }

 void ADCx_setCh(unsigned char ADCx, unsigned char CHx)
 {

 // ���. ������� ���
 // 1 ����� ������������ - 4 ����� ��� �� ����� (13(+) � 12(-) �����) � ��.
 
  ADC_select(ADCx); // ����� ���
 
  SPI1_write_byte(0x50+MUX);  // ���. ����� ���   
  SPI1_write_byte(0);         
  SPI1_write_byte(Mx_ch_code[CHx]);
  ADC_select(0); 
}

 signed long ADC_read(unsigned char ADC_number)
  {
  signed long ADC_RByte_Sum; // ��������� ������� ��� - 24 ����
  ADC_select(ADC_number); // ����� ���
  
  SPI1_write_byte(0x01);        // ������� ������ Rdata
  int i;
  for(i = 0; i < 500;i++) { }  // !!!! ����������� 50 clkIn = 7 us
  signed long ADC_Rbyte1 = SPI1_read_byte();   // ������
  signed long ADC_Rbyte2 = SPI1_read_byte();
  signed long ADC_Rbyte3 = SPI1_read_byte();
  
  ADC_select(0); // ����� ������ ���
  
  // ���������� ���� ���� �������� ���, ��� ������ ���� ��� ������������� �����
  ADC_RByte_Sum = (ADC_Rbyte1<<24) | (ADC_Rbyte2<<16) | ADC_Rbyte3<<8;
  ADC_RByte_Sum /=256;

  return ADC_RByte_Sum;
  
  }

 signed long ADCx_read_aver(unsigned char ADCx, unsigned char CHx)
{
  float Vin = 0;          // ���������� ���������� 
  signed long curr_ADCx_val = 0; // ��������. ��� �������� �����. ������. ��������
  
  curr_ADCx_val = ADC_read(ADCx);               // ����. ����� ���.

  Vin = (float)((curr_ADCx_val*5.0)/(8388608.0*PGA)); // ������ U
  return (signed long) (Vin*uV); // ������� ����������������� U
 
}

 void ADC_par_rd_ch(signed long *ADC1_ArrPtr, signed long *ADC2_ArrPtr)
{
   int i,j,k;
   
   // || ������ ���� ���
    switch (ADC_state)
    {
        case SET_CH:      // ���. ������ � ����� ������ ���. 
            meas_status = 0;
            ADCx_setCh(1,channel);
            ADCx_setCh(2,channel);
            ADC_sync(0);  // �����. ��������� ���
            //__delay_us(20);
            for(i = 0; i < 2000;i++) { }
            ADC_sync(1);
            
            ADC_state = GET_CH_DATA;    // ������� � ����. ������ 
        break;
        //----
        case GET_CH_DATA:
            if(ADC1_DRDY == 0 && ADC2_DRDY == 0)  // ���� ���������� ���
            {  
                // ��������� �� ����������
                pkt8_ch[channel]   = ADCx_read_aver(1,0); 
                pkt8_ch[channel+4] = ADCx_read_aver(2,0);    
                
                channel++;               // ��������� ������ ���. 
                
                if(channel > 3) 
                {
                  for(k = 0; k < 4; k++) // ���������� �������� ������� ������ �����������
                  {  
                    *ADC1_ArrPtr++ = pkt8_ch[k];
                    *ADC2_ArrPtr++ = pkt8_ch[k+4];
                  }
                    channel = 0;      // ����� �������� �������
                    meas_status = 1;  // ���. ����� ���������� 
                    
                    SPI2_write_byte(0x01);  
                    
                }   
                
                ADC_state = SET_CH;   // ���. ��������� ����� ������ ��� � ����. ������ �����. ���.
            }
        break;
        //----
        default:  ADC_state = SET_CH; // ���. ��������� ����� ������ ��� � ����. ������ �����. ���.
    } 
}

 unsigned int ADCs_meas_ready(void)
 {
   return meas_status; 
 }
 
 unsigned int ADCs_get_CurrMeasCh(void)
 {
  return (unsigned int)channel;
 }