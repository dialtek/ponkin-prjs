#include <main.h>
#use rs232(UART2,baud=9600,parity=N,bits=8)

   static S32 ADC_RByte1=0;
   static S32 ADC_RByte2=0;
   static S32 ADC_RByte3=0;
   static S32 ADC_RByte_Sum=0;
   static S32 ADCresult=0;
   static float Vin;                          
   static U8 PGA;
   //static float Vref=2.5;
   static U8 Sps_buf,Global_Ch_Number=0;
   static S16 ADCaddCoef;
   static float ADCmulCoef;
   float Final_T_in_K = 0;
   U8 ostatok_int_dec,ostatok_int_sot  = 0;
   U8 LCD_num_symb = 1;             // по умолчанию одна цифра для вывода Т на ЛСД
   U8 flash_wr_data [] = {0,0,0,0}; // заготовка массива для записи во флэш
   U8 Aver_Wr = 0;
   U8 Sps_Wr = 0;
   U8 CRC_Wr = 0;
   
   U8 menu_item = 0;
   volatile S8 menu_sel = 0;
   
   U8 menu_fl = 0;
   int1 meas_stop_fl = 0;
   int1 LCD_clear_fl = 1;
   int1 reset_fl = 0;    // флаг сброса системы
   
   U8 NumAver = 1;       // размер усреднения
   U8 ADC_sps_var = 1;   // переменная усреднения данных АЦП 
   U8 CRC1=0xFF,CRC2=0xFF, CRC_buf;   // константы EEPROM CRC
   U8 flash_rd_data[4]; // заготовка массива для чтения из флэш
   U32 temp  = 0;        // промежуточный буфер для вычислений T
   S32 ADC_data  = 0;    // отсчеты АЦП
     
static unsigned int8 buf; // lcd buf
#BIT buf4=buf.4 
#BIT buf5=buf.5
#BIT buf6=buf.6
#BIT buf7=buf.7
   

#include <LCD_16X4_Termo3.h>
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

static void OscSetup(){
  //Fcy=Fosc/2
  //Fin=10M
  //Fosc=Fin(M/(N1*N2))
  //Fosc=80M
  //U2BRG = 259;// BAUD Rate Setting for 9600
  U2BRG = 129;// BAUD Rate Setting for 19200
  U2MODE = 0b1010101010010000;
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
  ENABLE_INTERRUPTS(INTR_GLOBAL);
  enable_interrupts(INTR_CN_PIN|PIN_B5); 
  enable_interrupts(INTR_CN_PIN|PIN_B5);
  enable_interrupts(INTR_CN_PIN|PIN_B4);
  enable_interrupts(INTR_CN_PIN|PIN_B3);
  enable_interrupts(INTR_CN_PIN|PIN_B2);
  enable_interrupts(INT_TIMER1);
  EXT_INT_EDGE(L_TO_H);
}

static void DisableInt (){
  DISABLE_INTERRUPTS(INTR_GLOBAL);
  disable_interrupts(INTR_CN_PIN|PIN_B5); 
  disable_interrupts(INTR_CN_PIN|PIN_B5);
  disable_interrupts(INTR_CN_PIN|PIN_B4);
  disable_interrupts(INTR_CN_PIN|PIN_B3);
  disable_interrupts(INTR_CN_PIN|PIN_B2);
}

static void MCU_init(){

  setup_timer1(TMR_INTERNAL | TMR_DIV_BY_64); // таймер 1 сбрасывает собачий таймер
  set_timer1(20000); //reset the timer.
  
   SETUP_SPI2(SPI_MASTER|SPI_SCK_IDLE_LOW|SPI_XMIT_H_TO_L|SPI_MODE_8B|SPI_SAMPLE_AT_END|SPI_SS_DISABLED|SPI_CLK_DIV_128);
   //f SCLK SPI = 312,5 kHz
   //setup_timer1(TMR_DISABLED|TMR_DIV_BY_1);
   //enable_interrupts(INT_EXT0);
   //enable_interrupts(INT_TIMER1);
  
 SCK2_TRIS=0; // SPI2 tris
 SDI2_TRIS=1;
 SDO2_TRIS=0;
 
 CN1_TRIS = 1;
 CN2_TRIS = 1;
 CN3_TRIS = 1;
 CN4_TRIS = 1;
 
 TRG0 = 0; // lcd buf tris
 TRG1 = 0;
 TRB1 = 0;
 TRB0 = 0;
 
 LCD_RS_TRIS=0;
 LCD_RW_TRIS=0;
 LCD_E_TRIS=0;
 
 ADC_CS_TRIS=0;
 ADC_RESET_TRIS=0;
 ADC_SYNC_TRIS=0;
 ADC_DRDY_TRIS=1; // опрос готовнсти данных АЦП
 Status_LED_TRIS = 0;
 
 UART2_RX_TRIS=1;
 UART2_TX_TRIS=0;
 XPORT_RST_TRIS=0;
 
 XPORT_RST_n = 0;
 delay_us(500);
 XPORT_RST_n = 1;
 EnableInt();
}

static void Bpush_delay(){
   
   U16 counter = 0;
   
   do {counter++;} 
   while (counter<2000);   
   EnableInt(); 
}

static void LCD_print_menu(){
LCDsetCursor(one);
LCDMsg("ADC sps set  ");
LCDsetCursor(two);
LCDMsg("Average set  ");
LCDsetCursor(three);
LCDMsg("Reset device ");
LCDsetCursor(four);
LCDMsg("Return back  ");
}

static void LCD_main_menu (void) {
//DisableInt();
LCD_print_menu();

   //if(CN4){Bpush_delay(); if(CN4) menu_sel++;}
   //if(CN3){Bpush_delay(); if(CN3) menu_sel--;}
   switch (menu_sel){
    case 0: 
       LCDsetCursor(0x0D); LCDMsg("<--");
       LCDsetCursor(0x4D); LCDMsg("   "); // стирание стрелки от предыдущего
       LCDsetCursor(0x1D); LCDMsg("   "); // элемента меню
       LCDsetCursor(0x5D); LCDMsg("   ");
    break;
    
    case 1: 
       LCDsetCursor(0x0D); LCDMsg("   ");
       LCDsetCursor(0x4D); LCDMsg("<--"); // стирание стрелки от предыдущего
       LCDsetCursor(0x1D); LCDMsg("   "); // элемента меню
       LCDsetCursor(0x5D); LCDMsg("   ");
    break;
    
    case 2: 
       LCDsetCursor(0x0D); LCDMsg("   ");
       LCDsetCursor(0x4D); LCDMsg("   "); // стирание стрелки от предыдущего
       LCDsetCursor(0x1D); LCDMsg("<--"); // элемента меню
       LCDsetCursor(0x5D); LCDMsg("   ");
    break;
    
    case 3: 
       LCDsetCursor(0x0D); LCDMsg("   ");
       LCDsetCursor(0x4D); LCDMsg("   "); // стирание стрелки от предыдущего
       LCDsetCursor(0x1D); LCDMsg("   "); // элемента меню
       LCDsetCursor(0x5D); LCDMsg("<--");
    break;
   }  
}

static void Full_dev_reset(){
  LCDClear();
  LCDsetCursor(one);
  LCDMsg("   Reset done");
  LCDsetCursor(three);
  LCDMsg("Starting device!");
  delay_ms(1000);
  OscSetup();
  MCU_init();
  LCDInit();
  reset_fl = 0;
  ADC_wakeUp();
  ADC_wakeUp(); 
  ADC_init();
  ADC_set_PGA(8);
  ADC_sps_set(0x23); //0x023 - 10 sps, 0x43 - 25 sps, 0x63 - 50 sps
                     //0x82 - 100 sps, 0x91 - 500 sps
                     //0xA1 - 1000 sps, 0xC0 - 3750 sps
  ADC_SelfCal();
  meas_stop_fl = 0; // вкл. режим измерений
  menu_fl = 0;      // отключение меню
  menu_item = 0;    // сброс элемента меню
  NumAver = 1;      // сброс величины усреднения данных АЦП
  LCDClear();       // очистка дисплея

}

static void ADC_rd_and_print_ch(U8 chanel){

   switch (chanel){
//---------------- 1 датчик --------------------------------------//     
 case 1: 
  LCDsetCursor(one);
  LCDMsg("CTP");
  LCDMsg(":");
  ADCaddCoef = 22;      // смещение нуля для канала 1
  ADCmulCoef = 0.99978; // мультипликат. ошибка для канала 1
  ADC_setCh(4);
  Final_T_in_K = ADC_vol_to_T();
  LCDPutU32(temp,4);
  LCDsetCursor(0x0A);
  LCDPutU16(Final_T_in_K,LCD_num_symb);
  LCDMsg(".");
  LCDPutU16(ostatok_int_dec,1);
  if(LCD_num_symb==1){LCDMsg("K  ");} //очистка строки 
  if(LCD_num_symb==2){LCDMsg("K "); }
  if(LCD_num_symb==3){LCDMsg("K");  }
  Printf("a%05Lu\n",temp);
  LCDsetCursor(0x03);
  LCDMsg(" "); 
  
 break;
//---------------- 2 датчик --------------------------------------//
 case 2: 
  LCDsetCursor(two);
  LCDMsg("C");
  LCDputCH(0xA8);// П
  LCDMsg(" :");
  ADCaddCoef =7;         // смещение нуля для канала 2
  ADCmulCoef =0.999769;  // мультипликат. ошибка для канала 2
  ADC_setCh(3);
  Final_T_in_K = ADC_vol_to_T();
  LCDPutU32(temp,4);
  LCDsetCursor(0x4A);
  LCDPutU16(Final_T_in_K,LCD_num_symb);
  LCDMsg(".");
  LCDPutU16(ostatok_int_dec,1);
  if(LCD_num_symb==1){LCDMsg("K  ");} //очистка строки 
  if(LCD_num_symb==2){LCDMsg("K "); }
  if(LCD_num_symb==3){LCDMsg("K");  }
  Printf("b%05Lu\n",temp);
  LCDsetCursor(0x43);
  LCDMsg(" ");
 break;
//---------------- 3 датчик --------------------------------------//  
 case 3: 
  LCDsetCursor(three);
  LCDputCH(0xA8);// П
  LCDMsg('E');
  LCDMsg('P');
  LCDMsg(':');
  ADCaddCoef =30;        // смещение нуля для канала 3
  ADCmulCoef =0.999795;  // мультипликат. ошибка для канала 3
  ADC_setCh(2);
  Final_T_in_K = ADC_vol_to_T();
  LCDPutU32(temp,4);
  LCDMsg(" ");
  LCDPutU16(Final_T_in_K,LCD_num_symb);
  LCDMsg(".");
  LCDPutU16(ostatok_int_dec,1);
  if(LCD_num_symb==1){LCDMsg("K  ");} //очистка строки 
  if(LCD_num_symb==2){LCDMsg("K "); }
  if(LCD_num_symb==3){LCDMsg("K");  }
  Printf("c%05Lu\n",temp);
  LCDsetCursor(0x13);
  LCDMsg(" ");
 break;
//---------------- 4 датчик --------------------------------------//    
   case 4: 
  LCDsetCursor(four);
  LCDMsg("CO");
  LCDputCH(0xA7); // Л
  LCDMsg(":");
  ADCaddCoef = 83;         // смещение нуля для канала 4
  ADCmulCoef = 0.99985;         // мультипликат. ошибка для канала 4
  ADC_setCh(1);
  Final_T_in_K = ADC_vol_to_T();
  LCDPutU32(temp,4);
  LCDMsg(" ");
  LCDPutU16(Final_T_in_K,LCD_num_symb);
  LCDMsg(".");
  LCDPutU16(ostatok_int_dec,1);
  if(LCD_num_symb==1){LCDMsg("K  ");} //очистка строки 
  if(LCD_num_symb==2){LCDMsg("K "); }
  if(LCD_num_symb==3){LCDMsg("K");  }
  Printf("d%05Lu\n",temp);
  LCDsetCursor(0x53);
  LCDMsg(" "); 
   break;
//----------------------------------------------------------------//   
   }

}

static void save_to_flash(){
      
   Sps_Wr = NumAver;
   Aver_Wr = ADC_sps_var; // сохранение sps значения во флеш
   CRC_Wr = CRC8(flash_wr_data,2);
   Wr_Flash();
   
   } 

#int_cni
static void cn_irq_handler(void) {

   DisableInt();                    // отключение прерываний для обработки дребезка 
   meas_stop_fl = 1;                // взвод флага остановки измерений
   menu_fl = 1;                     // взвод флага перехода в меню
    if (menu_item == 1)
  {
    if (menu_sel>3) {menu_sel=0;}
    if (menu_sel<0) {menu_sel=3;}
  }
   if (CN2==1) {menu_item = 1;}
   if (CN3==1) {menu_sel--;}
   if (CN4==1) {menu_sel++;}
   clear_interrupt(INTR_CN_PIN);

}

#int_timer1
static void timer1_irq_handler(void) {
restart_wdt();     // сбос собачего таймера
set_timer1(20000); //reset the timer.
clear_interrupt(int_timer1);
}


/*############################################################################*/

static void main()
{ 
  S32 ADC_voltage = 0;
  OscSetup();
  MCU_init();        

  LCDInit();
  lCDwelcome();

  LCDSetCursor(one);
  LCDMsg("  Reading data");
  LCDSetCursor(two);
  LCDMsg("   from ROM...");
  
  Rd_Flash();                        // чтение денных из флеш для расчета контр. суммы
  crc1 = CRC_buf;                    // сохраненная контр. сумма    
  crc2 = CRC8(flash_rd_data,2);      // текущая контр. сумма
  
  LCDSetCursor(three);
  
  if (crc1==crc2){LCDMsg("       OK!");}
  else {
  LCDMsg("   CRC error!");
  ADC_sps_var = 2;   // сброс значений по умолчанию 
  NumAver = 1;       // тк произошел сбой контр. суммы
   }
   
      ADC_wakeUp();      // Сброс АЦП 
      ADC_wakeUp();      // перед инициализацией
      ADC_init();        // Инициализация АЦП
      ADC_SelfCal();     // Автокалибровка АЦП

  delay_ms(2000);
        
  LCDclear();
  
  ADCaddCoef = 22;      // смещение нуля для канала 1
  ADCmulCoef = 0.99978; // мультипликат. ошибка для канала 1
  ADC_setCh(4);
  
/*############################################################################*/  

  while(true){

  if (reset_fl)     {Full_dev_reset();}        // полный сброс системы
  
  if (!meas_stop_fl){// чтение АЦП
  
  ADC_voltage = Read_ADC_vol_in(uV);
  Printf("V%Ld\n\r",ADC_voltage);
  delay_ms(10);
  
  } 
                                               // вывод на дисплей и UART
  if (menu_fl){                                // вызов и обработка меню
  
  if (LCD_clear_fl){LCD_clear_fl = 0; LCDClear();} // очистка экрана
  
  Bpush_delay();                   // подавление дребезга кнопок
 
  switch (menu_item){                   // древо меню
/*----------------------------------------------------------------------------*/                                                           
  case 0: meas_stop_fl = 0; break;     // возврат в измерения
/*----------------------------------------------------------------------------*/   
  case 1: 
          LCD_main_menu();             // ADC average set
           if  (CN2 == 1){
            Bpush_delay();
            if ((CN2 == 1) & (menu_sel==0)){ // ADC sps set menu
                  LCD_clear_fl = 1; menu_item = 2; }   
                  
            if ((CN2 == 1) & (menu_sel==1)){ // ADC average set
                  LCD_clear_fl = 1; menu_item = 3; }
                  
            if ((CN2 == 1) & (menu_sel==2)){ // Reset device
                  LCD_clear_fl = 1; menu_item = 4; }                   
  
            if ((CN2 == 1) & (menu_sel==3)){ // Return back
                  LCD_clear_fl = 1; menu_item--; }}
            break;
/*----------------------------------------------------------------------------*/  
   case 2:                               // ADC sps set menu
   
   LCDsetCursor(one);
   LCDMsg("Samples per sec.");
   LCDsetCursor(three);
   if(CN4){Bpush_delay(); if(CN4) ADC_sps_var=ADC_sps_var-1; delay_ms(200);}
   if(CN3){Bpush_delay(); if(CN3) ADC_sps_var=ADC_sps_var+1; delay_ms(200);}
   if(ADC_sps_var>7)  ADC_sps_var = 7;
   if(ADC_sps_var==0) ADC_sps_var = 1;
    switch (ADC_sps_var){                // передача величины скорости измерений АЦП 
      case 1: ADC_sps_set(0x23); LCDsetCursor(0x16); LCDputU16(10,4);  break; // 10   sps
      case 2: ADC_sps_set(0x43); LCDsetCursor(0x16); LCDputU16(25,4);  break; // 25   sps
      case 3: ADC_sps_set(0x63); LCDsetCursor(0x16); LCDputU16(50,4);  break; // 50   sps
      case 4: ADC_sps_set(0x82); LCDsetCursor(0x16); LCDputU16(100,4); break; // 100  sps
      case 5: ADC_sps_set(0x91); LCDsetCursor(0x16); LCDputU16(500,4); break; // 500  sps
      case 6: ADC_sps_set(0xA1); LCDsetCursor(0x16); LCDputU16(1000,4);break; // 1000 sps
      case 7: ADC_sps_set(0xC0); LCDsetCursor(0x16); LCDputU16(3750,4);break; // 3750 sps
      }     
   save_to_flash();
   break;  
/*----------------------------------------------------------------------------*/
   case 3:                               // ADC average size menu
   
   LCDsetCursor(one);
   LCDMsg("    Average");
   LCDsetCursor(three);
   if(CN4){Bpush_delay(); if(CN4) --NumAver; delay_ms(100);} // декремент величины усреднения
   if(CN3){Bpush_delay(); if(CN3) ++NumAver; delay_ms(100);} // инкремент величины усреднения
   LCDsetCursor(0x16);
   LCDputU16(NumAver,3);
   
   save_to_flash();
   break;
/*----------------------------------------------------------------------------*/  
   case 4:                               // Reset menu
   
   LCDsetCursor(one);
   LCDMsg(" Reset device?");
   LCDsetCursor(three);
   LCDMsg("    Yes -> +");
   LCDsetCursor(four);
   LCDMsg("    No  -> -");
   if(CN3){Bpush_delay(); if(CN3) {reset_fl = 1;}}    // поднятие флага RESET для сброса всей системы
   if(CN4){Bpush_delay(); if(CN4) {menu_item= 1;}}    // отмена и выход в меню
   
   save_to_flash();
   break;
   }  
  }  
  
 }
}
/*############################################################################*/
