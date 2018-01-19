#include <main.h>
#INCLUDE <stdlib.h>
#use rs232(UART2,xmit=PIN_F5,rcv=PIN_F4,baud=230400,BRGH1OK,ERRORS,parity=N,bits=8)
 
    // ���� ������� ��������������..
    U8 Mx_ch_code[9] = {0, 0x76, 0x54, 0x32, 0x10};
    S32 adc_data[8];
    U8 PGA;
    U8 PGA_val = 3; // PGA = 8
    U8 Sps_buf=0;
    //S16 ADCaddCoef = 1;
    //float ADCmulCoef = 1;
   
   U8 flash_wr_data [] = {0,0,0,0}; // ��������� ������� ��� ������ �� ����
   U8 Aver_Wr = 0;
   U8 Sps_Wr = 0;
   U8 CRC_Wr = 0;
   U8 ADC_select = 0; // ���� ������ ���: 1�� ��� 2��

   int1 meas_stop_fl = 0;
   int1 reset_fl = 0;    // ���� ������ �������
   int1 stop_fl = 0;
   int1 send_t_fl = 0;
   
   U8 NumAver = 1;       // ������ ����������
   U8 ADC_sps_var = 1;   // ���������� ���������� ������ ��� 
   U8 CRC1=0xFF,CRC2=0xFF, CRC_buf;   // ��������� EEPROM CRC
   U8 flash_rd_data[4]; // ��������� ������� ��� ������ �� ����

   //Ma - Moving Average
   S32 Ch_buf[8][128];  // ����� ����������� �������� ��� �1
   S32 Ch_buf_sum;     // ����� ������ ����������� �������� ��� �1

   U8 Ma_buf_index = 0; // ������ �������� ��������. �����.
   U8 Ma_buf_size = 16;  // ������ ������!!!
   
   U8 RXd_buf[64]; // ����� ��� ������ UART ������ 
   U8 state;
   U16 tmp=0;
   
   static U8 wrptr=0,rdptr=0;
   static U8 RxData[16]; 
   
#include <ADS1256.h>

/*############################################################################*/

static void Rd_Flash(){

  read_program_memory(CK_USER_PAGE,flash_rd_data,4);
  delay_ms(5);
  NumAver = flash_rd_data[1]; 
  ADC_sps_var = flash_rd_data[0];
  CRC_buf = flash_rd_data[2];

}

static void Wr_Flash(){

  flash_wr_data[0] = Aver_Wr; 
  flash_wr_data[1] = Sps_Wr;
  flash_wr_data[2] = CRC_Wr;
  //flash_wr_data[4] = 0x00;
  write_program_memory(CK_USER_PAGE,flash_wr_data,4);
  delay_ms(2);

 //if(Rd_Flash(buf_index)==in_wr_data) return 1; else return 0;
}

unsigned char Crc8(unsigned char *pcBlock, unsigned int len)
{

  //Name  : CRC-8
  //Poly  : 0x31    x^8 + x^5 + x^4 + 1
  //Init  : 0xFF
  //Revert: false
  //XorOut: 0x00
  //Check : 0xF7 ("123456789")
  //MaxLen: 15 ����(127 ���) - �����������
  // ���������, �������, ������� � ���� �������� ������

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

static void UART2_init(){

   U2MODE = (1<<15 | // UARTx is enabled
             1<<13 | // Discontinue operation when device enters Idle mode 
             0<<12 | // IrDA encoder and decoder disabled
             1<<11 | // 1 - UxRTS in Simplex mode, 0 - flow control mode
             2<<9  | // UxTX, UxRX, UxCTS and UxRTS pins are enabled and used
             1<<7  | // 1 = Wake-up enabled
             0<<6  | // 0 = Loopback mode is disabled
             0<<5  | // Auto-Baud Enable bit, disabled
             1<<4  | // Receive Polarity Inversion bit, 1 = UxRX Idle state is '0'
             0<<3  | // BRGH: High Baud Rate Select bit , 0 = Low speed
             0<<2  | // 00 = 8-bit data, no parity
             0      // 0 = One Stop bit
   );

}

static void OscSetup(){
  //Fcy=Fosc/2
  //Fin=10M
  //Fosc=Fin(M/(N1*N2)) = 40M
  // 
  //U2BRG = 259;// BAUD Rate Setting for 9600
  //U2MODE = 0b1010101010000000; // brgh = 0
  //U2BRG = 21;// BAUD Rate Setting for 115200
  U2BRG = 10;  // BAUD Rate Setting for 230400
  U2MODE = 0b1010101010000000; // brgh = 0
  
  PLLFBD = 30; // ???. ????. ??????? PLL M = 30
  
  PLLPRE4 = 0; // ???. ????. ??????? PLL N1 = 2
  PLLPRE3 = 0;
  PLLPRE2 = 0;
  PLLPRE1 = 0;
  PLLPRE0 = 0;
  
  PLLPOST0=0; // ???. ????. ??????? PLL N2 = 2
  PLLPOST1=0;
    
   }

static void EnableInt (){

  enable_interrupts(INT_RDA); // UART Int
  enable_interrupts(INT_RDA2); // UART Int
  
  enable_interrupts(INT_TIMER1);
  EXT_INT_EDGE(L_TO_H);
  ENABLE_INTERRUPTS(INTR_GLOBAL);
}

static void MCU_init(){

  setup_timer1(TMR_INTERNAL | TMR_DIV_BY_64); // ������ 1 ���������� ������� ������
  set_timer1(20000); //reset the timer.
  
   SETUP_SPI2(SPI_MASTER|SPI_SCK_IDLE_LOW|SPI_XMIT_H_TO_L|SPI_MODE_8B|SPI_SAMPLE_AT_END|SPI_SS_DISABLED|SPI_CLK_DIV_128);
   //f SCLK SPI = 312,5 kHz
   //setup_timer1(TMR_DISABLED|TMR_DIV_BY_1);
   //enable_interrupts(INT_EXT0);
   //enable_interrupts(INT_TIMER1);
  
 SCK2_TRIS=0; // SPI2 tris
 SDI2_TRIS=1;
 SDO2_TRIS=0;
 
 ADC_CS_TRIS=0;      ADC2_CS_TRIS=0;
 ADC_RESET_TRIS=0;   ADC2_RESET_TRIS=0;
 ADC_SYNC_TRIS=0;    ADC2_SYNC_TRIS=0;
 ADC_DRDY_TRIS=1;    ADC2_DRDY_TRIS=1;       // ����� ��������� ������ ���
 
 UART2_RX_TRIS=1;
 UART2_TX_TRIS=0;
 //XPORT_RST_TRIS=0;
 
 //XPORT_RST_n = 0;
 //delay_us(500);
 //XPORT_RST_n = 1;
 EnableInt();
}

static void Full_dev_reset(){

  OscSetup();
  MCU_init();
  reset_fl = 0;
  //ADC_wakeUp();
  //ADC_wakeUp(); 
  ADC_init();
  ADC_set_PGA(8);
  ADC_sps_set(0x23); //0x023 - 10 sps, 0x43 - 25 sps, 0x63 - 50 sps
                     //0x82 - 100 sps, 0x91 - 500 sps
                     //0xA1 - 1000 sps, 0xC0 - 3750 sps
  ADC_SelfCal();
  meas_stop_fl = 0; // ���. ����� ���������
  NumAver = 10;      // ����� �������� ���������� ������ ���

}

static void Clr_bufs(void)
{
  for (U8 i = 0; i < 8; i++)
  {
  // ���������� ������� ������. ��. ������
   for (U8 j = 0; j < Ma_buf_size; j++) 
      {
         Ch_buf[i][j] = 0;
      }
  }
}

static U8 ch_to_int(char ch){
U8 dg=-1;
 switch (ch){
      case '0' : dg=0;
      break;
      case '1' : dg=1;
      break;
      case '2' : dg=2;
      break;
      case '3' : dg=3;
      break;
      case '4' : dg=4;
      break;
      case '5' : dg=5;
      break;
      case '6' : dg=6;
      break;
      case '7' : dg=7;
      break;
      case '8' : dg=8;
      break;
      case '9' : dg=9;
      break;
      default: dg=-1;
 }
return dg;
}

static unsigned char getrxch (void){

unsigned char rch;

if(rdptr < wrptr){
 // ���� ������, ���������
   rdptr ++;
   rch=RxData[rdptr& 0x0F];// ��������� ������
} else rch = 'x';//�������� ���
   //��������� ����������
   disable_interrupts(INT_RDA2);
  if((wrptr==rdptr) && (wrptr > 15)) 
  {
  wrptr=0;
  rdptr=0;
  } 
  enable_interrupts(INT_RDA2);
  return rch;
}

// ������. ������ ���� ���
/*
static void ADC_Seq_rd_and_print_ch(U8 chanel){

   switch (chanel){
//---------------- ��� 1 --------------------------------------//     
 case 1: 
 
 ADC_select(1);
 ADC_setCh(1);
 delay_us(20);
 ADC_select(0);
 
 ADC_SYNC = 0;
 delay_us(20);
 ADC_SYNC = 1;
 
 While(ADC_DRDY) { } // ���� ���������� ��� 1
 ADC_select(1);
 Printf("a%08Lu\n",ADC_read());
 ADC_select(0);
 delay_us(20);

 break;

//---------------- 2 ������ --------------------------------------//
 case 2:
 
 ADC_select(1);
 ADC_setCh(2);
 ADC_select(0);
 
 ADC_SYNC = 0;
 delay_us(20);
 ADC_SYNC = 1;
 
 While(ADC_DRDY) { } // ���� ���������� ��� 1
 ADC_select(1);
 Printf("b%08Lu\n",ADC_read());
 ADC_select(0);
 delay_us(20);

 break;
 
//---------------- 3 ������ --------------------------------------//  
 case 3: 

 ADC_select(1);
 ADC_setCh(3);
 delay_us(20);
 ADC_select(0);
 
 ADC_SYNC = 0;
 delay_us(20);
 ADC_SYNC = 1;
 
 While(ADC_DRDY) { } // ���� ���������� ��� 1
 ADC_select(1);
 Printf("c%08Lu\n",ADC_read());
 ADC_select(0);
 delay_us(20);

 break;
//---------------- 4 ������ --------------------------------------//    
   case 4: 
   
 ADC_select(1);
 ADC_setCh(4);
 delay_us(20);
 ADC_select(0);
 
 ADC_SYNC = 0;
 delay_us(20);
 ADC_SYNC = 1;
 
 While(ADC_DRDY) { } // ���� ���������� ��� 1
 ADC_select(1);
 Printf("d%08Lu\n",ADC_read());
 ADC_select(0);
 delay_us(20);
 
   break;
//----------------------------------------------------------------//

//------------------- ��� 2 --------------------------------------//     
 case 5: 
 
 ADC_select(2);
 ADC_setCh(1);
 delay_us(20);
 ADC_select(0);
 
 ADC2_SYNC = 0;
 delay_us(20);
 ADC2_SYNC = 1;
 
 While(ADC2_DRDY) { } // ���� ���������� ��� 1
 ADC_select(2);
 Printf("e%08Lu\n",ADC_read());
 ADC_select(0);
 delay_us(20);
 
 break;
 
//---------------- 2 ������ --------------------------------------//
 case 6: 
 
 ADC_select(2);
 ADC_setCh(2);
 delay_us(20);
 ADC_select(0);
 
 ADC2_SYNC = 0;
 delay_us(20);
 ADC2_SYNC = 1;
 
 While(ADC2_DRDY) { } // ���� ���������� ��� 1
 ADC_select(2);
 Printf("f%08Lu\n",ADC_read());
 ADC_select(0);
 delay_us(20);
  
 break;
//---------------- 3 ������ --------------------------------------//  
 case 7: 

 ADC_select(2);
 ADC_setCh(3);
 delay_us(20);
 ADC_select(0);
 
 ADC2_SYNC = 0;
 delay_us(20);
 ADC2_SYNC = 1;
 
 While(ADC2_DRDY) { } // ���� ���������� ��� 1
 ADC_select(2);
 Printf("g%08Lu\n",ADC_read());
 ADC_select(0);
 delay_us(20);
  
 break;
//---------------- 4 ������ --------------------------------------//    
   case 8: 

 ADC_select(2);
 ADC_setCh(4);
 delay_us(20);
 ADC_select(0);
 
 ADC2_SYNC = 0;
 delay_us(20);
 ADC2_SYNC = 1;
 
 While(ADC2_DRDY) { } // ���� ���������� ��� 1
 ADC_select(2);
 Printf("h%08Lu\n",ADC_read());
 ADC_select(0);
 delay_us(20);
  
  break;
   }
   
}
*/
/**/

// || ������ ���� ���
static void ADC_Par_rd_and_print_ch(U8 channel)
{
  char rchr;             // �������� U2 ������
  
  
   switch (channel){
//---------------- ������ 1 � 5 --------------------------------------//     
 case 1: 
 
 ADC_setCh(1,1);
 ADC_setCh(1,2);

 SYNC_ADC(1);  // �����. ��������� ��� 1
 delay_us(200);  
 SYNC_ADC(2);  // �����. ��������� ��� 2
 
 While(ADC_DRDY) { } // ���� ���������� ��� 1
 //Printf("a%09Ld\n",ADC_read_aver(1,0));
 adc_data[0] = ADC_read_aver(1,0);
 While(ADC2_DRDY) { } // ���� ���������� ��� 2
 //Printf("e%09Ld\n",ADC_read_aver(2,1));
 adc_data[1] = ADC_read_aver(2,1);

 break;

//---------------- ������ 2 � 6 --------------------------------------//  
 case 2: 
 
 ADC_setCh(2,1);
 ADC_setCh(2,2);
 
 SYNC_ADC(1);   // �����. ��������� ��� 1
 delay_us(200);  
 SYNC_ADC(2);    // �����. ��������� ��� 2
 
 While(ADC_DRDY) { } // ���� ���������� ��� 1
 //Printf("b%09Ld\n",ADC_read_aver(1,2));
 adc_data[2] = ADC_read_aver(1,2);
 
 While(ADC2_DRDY) { } // ���� ���������� ��� 2
 //Printf("f%09Ld\n",ADC_read_aver(2,3));
 adc_data[3] = ADC_read_aver(2,3);
 
 break;
 
//---------------- ������ 3 � 7 --------------------------------------//   
 case 3: 
 
 ADC_setCh(3,1);
 ADC_setCh(3,2);
 
 SYNC_ADC(1);   // �����. ��������� ��� 1
 delay_us(200);  
 SYNC_ADC(2);   // �����. ��������� ��� 2
 
 While(ADC_DRDY) { } // ���� ���������� ��� 1
 //Printf("c%09Ld\n",ADC_read_aver(1,4));
  adc_data[4] = ADC_read_aver(1,4);
 While(ADC2_DRDY) { } // ���� ���������� ��� 2
 //Printf("g%09Ld\n",ADC_read_aver(2,5));
  adc_data[5] = ADC_read_aver(2,5);
  
 break;
 
//---------------- ������ 4 � 8 --------------------------------------//   
 case 4: 
 
 ADC_setCh(4,1);
 ADC_setCh(4,2);
 
 SYNC_ADC(1);   // �����. ��������� ��� 1
 delay_us(200);  
 SYNC_ADC(2);    // �����. ��������� ��� 2
 
 While(ADC_DRDY) { } // ���� ���������� ��� 1
 //Printf("d%09Ld\n",ADC_read_aver(1,6));
  adc_data[6] = ADC_read_aver(1,6);

 While(ADC2_DRDY) { } // ���� ���������� ��� 2
 //Printf("h%09Ld\n",ADC_read_aver(2,7));
 adc_data[7] = ADC_read_aver(2,7);
 Ma_buf_index++; // ��������� �������
 if(Ma_buf_index > Ma_buf_size-1) Ma_buf_index = 0;   // ����� ������� ������
 
 break;
 
//---------------- ��������� ������ � �� ------------------------------//   
 case 5:
 
 while(rdptr < wrptr){
   U8 dg=0;
   U16 buf1; 
   //���� ���� �������������� ������� 
   rchr=getrxch();
 
   switch(state){
          case 0:
           switch (rchr){ //�������
               case 's': stop_fl = 0; // ����� ���������
                         Clr_bufs();
                         ADC_init(); // ��������� .��� � ������ �����������
                         state=0;
               break; 
               //----------
               case 'p': stop_fl = 1; // ���� ���������
                         printf("stopped\n\r");  
                         state=0;
               break; 
               //----------
               case 'g': state = 1; // pga_set
               if(!stop_fl) state=0; 
               break;
               //----------
               case 'v': state = 2; // sps_set
               if(!stop_fl) state=0;           
               break;
               //----------
               case 'b': state = 5; // aver_buf_size
               if(!stop_fl) state=0;           
               break;
               
              //----------
               case 't': send_t_fl = 1; // ����� ����� ������� ������ �� ����.
                         state=0;         
               break;

               default : printf("err \r\n");      
         } // �������
          break;
          
         case 1: 
         // ���. PGA
            dg = ch_to_int(rchr);
            if(dg == -1){ 
              state=0;
              printf("PGA err \r\n"); 
              break;
                  }
                  
              tmp = (U16)dg;
              
            //if(stop_fl) {     
               if(tmp>=0 && tmp<=6){
                  PGA_val=tmp;
                  printf("PGA=%u \r\n",PGA_val);
               }  else printf("PGA out of range\r\n");
            //}
                  state=0;     
         break;
         
         case 2: 
         // ���. SPS
            dg = ch_to_int(rchr);
            if(dg == -1){ 
              state=0;
              printf("err p1 \r\n"); 
              break;
                  }
          // 1 �����   
          tmp=0;
          tmp+=(U16)dg*10;
          state=3;
          // ������ ���� ����� 3 �������?
         break;
         
         case 3: 
         // ���. SPS
            dg = ch_to_int(rchr);
            if(dg == -1){ 
              state=0;
              printf("err p2 \r\n"); 
              break;
                  }
          // 2 �����        
          tmp+=(U16)dg; 
          state=4;
         break;
         
         case 4: 
            if(tmp>=0 && tmp<=12){
               ADC_sps_var = tmp;
               printf("SPS=%u \r\n",ADC_sps_var);
               } else printf("SPS out of range\r\n");
                  state=0;     
         break;
         
         case 5: 
         // ���. ������� ������ ����������
            dg = ch_to_int(rchr);
            if(dg == -1){ 
              state=0;
              printf("err p1 \r\n"); 
              break;
                  }
          // 1 �����   
          tmp=0;
          tmp+=(U16)dg*100;
          state=6;
          
         break;
         
         case 6: 
         // ���. ������� ������ ����������
            dg = ch_to_int(rchr);
            if(dg == -1){ 
              state=0;
              printf("err p2 \r\n"); 
              break;
                  }
          // 2 �����        
          tmp+=(U16)dg*10;
          state=7;
          
         break;
         
         case 7: 
         // ���. ������� ������ ����������
            dg = ch_to_int(rchr);
            if(dg == -1){ 
              state=0;
              printf("err p3 \r\n"); 
              break;
                  }
          // 3 ����� 
          tmp+=(U16)dg;
          if(tmp>=0 && tmp<=128){
                       Ma_buf_size=(U8)tmp;// ��������� ��� 3 ����� ��� ������
                       printf("aver buf size=%u \r\n",Ma_buf_size);
          } else printf("aver buf out of range\r\n");
          
          state=0;
          
         break;
         
        default : state=0;   
      } // state   
   } // while
   
     break;
   } // main case
}

static void save_to_flash(){
      
   Sps_Wr = NumAver;
   Aver_Wr = ADC_sps_var; // ���������� sps �������� �� ����
   CRC_Wr = CRC8(flash_wr_data,2);
   Wr_Flash();
   } 

#int_timer1
static void timer1_irq_handler(void) {
restart_wdt();     // ���� �������� �������
set_timer1(20000); //reset the timer.
clear_interrupt(int_timer1);
}

#INT_RDA2
void UART2_RXd_isr(void){

while(U2STA & 0x0001)
{ // Receive buffer has data, at least one more character can be read
   wrptr++;
   RxData[wrptr & 0x0F] = (U8)(U2RXREG);
}
}

/*############################################################################*/

static void main()
{ 
  U8 ch = 1;             // ��������� ��������� ������ ��������� ���

  OscSetup();
  MCU_init(); 
  //Rd_Flash();                        // ������ ������ �� ���� ��� ������� �����. �����
  //crc1 = CRC_buf;                    // ����������� �����. �����    
  //crc2 = CRC8(flash_rd_data,2);      // ������� �����. �����
  
  Clr_bufs();
  
  ADC_sps_var = 0;   // ����� �������� �� ��������� 
  NumAver = 1;       // �� ��������� ���� �����. �����
     
  ADC_RESET = 1; ADC2_RESET = 1;
  ADC_CS = 1;    ADC2_CS = 1;
  ADC_SYNC = 1;  ADC2_SYNC = 1; 
     
  While(ADC_DRDY | ADC2_DRDY) { }   // ���� ���������� ����� ��� ����� ����.  
  
  ADC_init();        // ������������� ����� ��� 
  
/*############################################################################*/  

  while(true){
  
  ADC_Par_rd_and_print_ch(ch); // ������ 8 ������� ���� ���
  
  if(send_t_fl)
  {
      send_t_fl = 0;
      Printf("a%09Ld\n",adc_data[0]);
      Printf("e%09Ld\n",adc_data[1]);
      Printf("b%09Ld\n",adc_data[2]);
      Printf("f%09Ld\n",adc_data[3]);
      Printf("c%09Ld\n",adc_data[4]);
      Printf("g%09Ld\n",adc_data[5]);
      Printf("d%09Ld\n",adc_data[6]);
      Printf("h%09Ld\n",adc_data[7]);

  }// ��������� ������ ������
  ch++;
  if (ch > 5) ch = 1; // �������� �������
  if (stop_fl) ch = 5; // ���������� ���������
 } // while  
}  // main
/*############################################################################*/

