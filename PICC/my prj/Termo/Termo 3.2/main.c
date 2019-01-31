#include <main.h>
#use rs232(UART1,xmit=PIN_F3,rcv=PIN_F2,baud=115200,BRGH1OK,ERRORS,parity=N,bits=8)
#include <ADS1256.h> // ADC

  // результаты измерений
  S32 pkt8_ch_1 = 0, pkt8_ch_2 = 0, pkt8_ch_3 = 0, pkt8_ch_4 = 0, 
      pkt8_ch_5 = 0, pkt8_ch_6 = 0, pkt8_ch_7 = 0, pkt8_ch_8 = 0;
  U16 meas_status; // статус бит обновления измерений
  
  void Clr_bufs(void)
{
  Ma_buf_cnt = 0;
  Ma_buf_index = 0;
  Ch_buf_sum = 0;
  
  for (U8 i = 0; i < 8; i++)
  {
  // заполнение буферов скольз. ср. нулями
   for (U8 j = 0; j < 128; j++) 
      {
         Ch_buf[i][j] = 0;
      }
  }
  
  for (U8 a = 0; a < 2; a++)
  {
  // заполнение буферов отсчетов нулями
   for (U8 b = 0; b < 8; b++) 
      {
         ADC_counts[a][b] = 0;
      }
  }
}

#include <dialtek_modbus.h> 
   
  void Rd_Flash(){
  U8 a,b,c;
  read_program_memory(CK_USER_PAGE,flash_rd_data,8);
  delay_ms(10);
  
  
  a = flash_rd_data[0];
  b = flash_rd_data[1]; 
  c = flash_rd_data[4];
  
  if(a > 128) Ma_buf_size = 5;
  else        Ma_buf_size = a;
    
  if(b > 7)   ADC_sps_var = 1;
  else        ADC_sps_var = b;
    
  if(c > 6)   PGA_val = 3;
  else        PGA_val = c;
}

  void Wr_Flash(){

  flash_wr_data[0] = Ma_buf_size; 
  flash_wr_data[1] = ADC_sps_var;
  flash_wr_data[4] = PGA_val;
  flash_wr_data[5] = 0;
  write_program_memory(CK_USER_PAGE,flash_wr_data,8);
  delay_ms(10);

 //if(Rd_Flash(buf_index)==in_wr_data) return 1; else return 0;
}

  char Crc8(unsigned char *pcBlock, unsigned int len)
{

  //Name  : CRC-8
  //Poly  : 0x31    x^8 + x^5 + x^4 + 1
  //Init  : 0xFF
  //Revert: false
  //XorOut: 0x00
  //Check : 0xF7 ("123456789")
  //MaxLen: 15 байт(127 бит) - обнаружение
  // одинарных, двойных, тройных и всех нечетных ошибок

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

  void UART1_init(){

   U1MODE = (1<<15 | // UARTx is enabled
             0<<13 | // continue operation when device enters Idle mode 
             0<<12 | // IrDA encoder and decoder disabled
             1<<11 | // 1 - UxRTS in Simplex mode, 0 - flow control mode
             2<<9  | // UxTX, UxRX, UxCTS and UxRTS pins are enabled and used
             0<<7  | // 0 = Wake-up dis
             0<<6  | // 0 = Loopback mode is disabled
             0<<5  | // Auto-Baud Enable bit, disabled
             0<<4  | // Receive Polarity Inversion bit, 0 = UxRX Idle state is '1'
             0<<3  | // BRGH: High Baud Rate Select bit , 0 = Low speed
             0<<2  | // 00 = 8-bit data, no parity
             0      // 0 = One Stop bit
   );

}

  void uart_send_byte (U8 ch) {
  
      U1TXREG = ch; 
      delay_us(1);
      while(U1_TRMT == 0) { } 
  }

  void OscSetup(){
  //Fcy=Fosc/2
  //Fin=10M
  //Fosc=Fin(M/(N1*N2)) = 40M
  // 
  //U2BRG = 259;// BAUD Rate Setting for 9600
  //U2MODE = 0b1010101010000000; // brgh = 0
  U1BRG = 21;// BAUD Rate Setting for 115200
  //U1BRG = 10;  // BAUD Rate Setting for 230400
  U1MODE = 0b1010101010000000; // brgh = 0
  
  PLLFBD = 30; // ???. ????. ??????? PLL M = 30
  
  PLLPRE4 = 0; // ???. ????. ??????? PLL N1 = 2
  PLLPRE3 = 0;
  PLLPRE2 = 0;
  PLLPRE1 = 0;
  PLLPRE0 = 0;
  
  PLLPOST0=0; // ???. ????. ??????? PLL N2 = 2
  PLLPOST1=0;
    
   }

  void EnableInt (){

  enable_interrupts(INT_RDA); // UART Int

  enable_interrupts(INT_TIMER9);
  
  ENABLE_INTERRUPTS(INTR_GLOBAL);
}

  void MCU_init(){

  FWDTEN = 0; // DIS WDT
  
  T9ON = 0;
  setup_timer9(TMR_INTERNAL | TMR_DIV_BY_1);   //  9 - modbus cmd integrity timer
  set_timer9(8400);  // 3x rx byte periods on 115k
  
  SETUP_SPI2(SPI_MASTER|SPI_SCK_IDLE_LOW|SPI_XMIT_H_TO_L|SPI_MODE_8B|SPI_SAMPLE_AT_END|SPI_SS_DISABLED|SPI_CLK_DIV_128);
   //f SCLK SPI = 312,5 kHz

 SCK2_TRIS=0; // SPI2 tris
 SDI2_TRIS=1;
 SDO2_TRIS=0;
 
 ADC_CS_TRIS=0;      ADC2_CS_TRIS=0;
 ADC_RESET_TRIS=0;   ADC2_RESET_TRIS=0;
 ADC_SYNC_TRIS=0;    ADC2_SYNC_TRIS=0;
 ADC_DRDY_TRIS=1;    ADC2_DRDY_TRIS=1;       // опрос готовнсти данных АЦП
 
 UART1_RX_TRIS=1;
 UART1_TX_TRIS=0;
 
 TRC14 = 0; // RS-485 TX EN
 
 EnableInt();
}

  void Full_dev_reset(){

  OscSetup();
  MCU_init();
  reset_fl = 0;
  //ADC_wakeUp();
  //ADC_wakeUp(); 
  ADC_init(input_buf_state);
  ADC_set_PGA(8);
  ADC_sps_set(0x23); //0x023 - 10 sps, 0x43 - 25 sps, 0x63 - 50 sps
                     //0x82 - 100 sps, 0x91 - 500 sps
                     //0xA1 - 1000 sps, 0xC0 - 3750 sps
  ADC_SelfCal();
  meas_stop_fl = 0; // вкл. режим измерений
  NumAver = 10;      // сброс величины усреднения данных АЦП

}

  // || чтение двух АЦП
  void ADC_par_rd_ch(U8 channel)
{

 switch (channel){
//---------------- каналы 1 и 5 --------------------------------------//     
 case 1: 
 
 ADC_setCh(1,1);
 ADC_setCh(1,2);

 SYNC_ADC(1);  // синхр. измерений АЦП 1
 delay_us(200);  
 SYNC_ADC(2);  // синхр. измерений АЦП 2
 
 While(ADC_DRDY) { } // ждем готовности АЦП 1
 pkt8_ch_1 = ADC_read_aver(1,0);
 pkt8_ch_1 = (S32)((float)pkt8_ch_1 * (float)1.0009208471794050526484365616367);

 While(ADC2_DRDY) { } // ждем готовности АЦП 2
 pkt8_ch_5 = ADC_read_aver(2,1);

 break;

//---------------- каналы 2 и 6 --------------------------------------//  
 case 2: 
 
 ADC_setCh(2,1);
 ADC_setCh(2,2);
 
 SYNC_ADC(1);    // синхр. измерений АЦП 1
 delay_us(200);  
 SYNC_ADC(2);    // синхр. измерений АЦП 2
 
 While(ADC_DRDY) { } // ждем готовности АЦП 1
 pkt8_ch_2 = ADC_read_aver(1,2);

 While(ADC2_DRDY) { } // ждем готовности АЦП 2
 pkt8_ch_6 = ADC_read_aver(2,3);
 
 break;
 
//---------------- каналы 3 и 7 --------------------------------------//   
 case 3: 
 
 ADC_setCh(3,1);
 ADC_setCh(3,2);
 
 SYNC_ADC(1);   // синхр. измерений АЦП 1
 delay_us(200);  
 SYNC_ADC(2);   // синхр. измерений АЦП 2
 
 While(ADC_DRDY) { }  // ждем готовности АЦП 1
 pkt8_ch_3 = ADC_read_aver(1,4);
 
 While(ADC2_DRDY) { } // ждем готовности АЦП 2
 pkt8_ch_7 = ADC_read_aver(2,5);
 
 break;
 
//---------------- каналы 4 и 8 --------------------------------------//   
 case 4: 
 
 ADC_setCh(4,1);
 ADC_setCh(4,2);
 
 SYNC_ADC(1);    // синхр. измерений АЦП 1
 delay_us(200);  
 SYNC_ADC(2);    // синхр. измерений АЦП 2
 
 While(ADC_DRDY) { }  // ждем готовности АЦП 1
 pkt8_ch_4 = ADC_read_aver(1,6);

 While(ADC2_DRDY) { } // ждем готовности АЦП 2
 pkt8_ch_8 = ADC_read_aver(2,7);

 Ma_buf_index++; // инкремент индекса
 
 break;

   } // main case
}

  void save_to_flash() {
      
   Sps_Wr = NumAver;
   Aver_Wr = Ma_buf_size; // сохранение sps значения во флеш
   PGA = PGA_val;
   CRC_Wr = CRC8(flash_wr_data,3);
   Wr_Flash();
   } 

  #int_timer9
  void timer9_irq_handler(void) {
  
  T9ON = 0;
  timer_state = 0;
  rx_flag = 1;
  
  disable_interrupts(INT_TIMER9);
  clear_interrupt(int_timer9);
  
  }
  
  #INT_RDA
  void UART1_RXd_isr(void){

    rx_buf[rx_buf_ptr++] = (U8)U1RXREG;
    clear_interrupt(int_rda);  
    
    if(timer_state == 0)
    {
        TMR9 = 0x0000;
        clear_interrupt(int_timer9);   // Clear Timer interrupt flag
        enable_interrupts(int_timer9);
        timer_state = 1;
        T9ON = 1;
    }
    else TMR9 = 0x0000; // reset if timer is on, 115200
}

/*########################################################################### */

  void main()
{ 
  OscSetup();
  MCU_init(); 

  for(U8 i = 0; i < 125; i++) holding_register[i] = 0; // ??????? ?????? ?????????? ??????
  Clr_bufs();
  
  //ADC_sps_var = 1;   // сброс значений по умолчанию 
  //NumAver = 1;       // тк произошел сбой контр. суммы
     
  ADC_RESET = 1; ADC2_RESET = 1;
  ADC_CS = 1;    ADC2_CS = 1;
  ADC_SYNC = 1;  ADC2_SYNC = 1; 

  While(ADC2_DRDY | ADC2_DRDY) { }   // ждем готовности обоих АЦП перед иниц.  
  Rd_Flash();
  ADC_init(input_buf_state);         // Инициализация обоих АЦП 
  
/*############################################################################*/  

  while(true)
  {

  ADC_par_rd_ch(1); // измрение к 1 и 5
  ADC_par_rd_ch(2); // измрение к 2 и 6
  ADC_par_rd_ch(3); // измрение к 3 и 7
  ADC_par_rd_ch(4); // измрение к 4 и 8 
  
  meas_status = 1;  // уст. флага обновления измерений
   
  modbus_poll();    // анализ запроса modbus и ответ при необходимости
  
 } // while  
}  // main
/*############################################################################*/


