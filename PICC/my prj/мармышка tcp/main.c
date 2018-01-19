#include <main.h>
#include <math.h>

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
//volatile U16 Tenth_K, Hundredth_K, Thousandth_K  = 0;
U8 LCD_num_symb, LCD_num_symb_K = 1;                  // �� ��������� ���� ����� ��� ������ � �� ���
U16 flash_wr_U16 [] = {0,0,0,0};                      // ��������� ������� ��� ������ �� ���� float
U16 flash_rd_U16 [4];
U8 Sps_Wr = 0;                                        // �������� ��������� ���
U8 CRC_Wr = 0;                                        // ����������� �����
//S32 Temper_int_K = 0;
//float Final_TK = 0.0;
float Max_Temp = 40.0;                                // ������������ ����������� �����������
U16 T_Pulse = 10000;                                  // ����� ��������� � �������
U16 Number_Pulse = 0;                              // ���-�� ��������� � Duty_Cycle
U16 count = 0;
U16 Freq = 64535;                                     // Account starts with this number and finishes on 65535.
                                                      // Interrupt occur with frequency F = 100kHz.                                                   
U8 menu_item = 0;
volatile S8 menu_sel = 0;
   
U8 menu_fl = 0;
int1 meas_stop_fl = 0;
int1 LCD_clear_fl = 1;
int1 reset_fl = 0;                              // ���� ������ �������
U8 count_CN4 = 0;                               // ������� ��� ������������ ������� ������� ������ 4
U8 count_CN3 = 0;                               // ������� ��� ������������ ������� ������� ������ 3
   
U8 NumAver = 1;                                 // ������ ����������
U8 ADC_sps_var = 1;                             // ���������� ���������� ������ ��� 
U8 CRC1=0xFF,CRC2=0xFF, CRC_buf;                // ��������� EEPROM CRC
U32 temp  = 0;                                  // ������������� ����� ��� ���������� T

float TmpInt = 0;                                   // Integral term
float P = 0;                                    // Proportional term
float TemperatureInCelsius = 0;
float TemperatureInKelvin = 0;
float K1 = 600.0;                               // Arbitrary coefficient
float K2 = 5.0;                                 // Arbitrary coefficient
unsigned int16 Integer_part = 0;
unsigned int8 Tenth = 0;
   
static unsigned int8 buf;                          // lcd buf
#BIT buf4 = buf.4 
#BIT buf5 = buf.5
#BIT buf6 = buf.6
#BIT buf7 = buf.7

#include <MT-16S4A-2FLG.h>
#include <ADS1256.h>

/*############################################################################*/
/* ������� ������ �� flash */
static void Wr_Flash2(){
  U16 K1_int = K1 * 10;
  U8 K2_int = K2 * 10;
  
  flash_wr_U16[0] = K1_int;
  flash_wr_U16[1] = K2_int;
  flash_wr_U16[2] = Sps_Wr;
  flash_wr_U16[3] = CRC_wr;
  
  write_program_memory(CK_USER_PAGE,flash_wr_U16,8);
}

/* ������� ������ �� flash */
static void Rd_Flash2(){
  read_program_memory(CK_USER_PAGE,flash_rd_U16,8);
// delay_ms(1);
  K1 = flash_rd_U16[0] / 10.0;
  K2 = flash_rd_U16[1] / 10.0;
  ADC_sps_var = flash_rd_U16[2];
  CRC_buf = flash_rd_U16[3];
}
               
/*
  Name  : CRC-16
  Poly  : 0x8005    x^16 + x^15 + x^2 + 1
  Init  : 0xFFFF
  Revert: true
  XorOut: 0x0000
  Check : 0x4B37 ("123456789")
  MaxLen: 4095 ���� (32767 ���) - �����������
    ���������, �������, ������� � ���� �������� ������
*/
const unsigned int8 CRC16Table[256] = {
    0x0000, 0xC0C1, 0xC181, 0x0140, 0xC301, 0x03C0, 0x0280, 0xC241,
    0xC601, 0x06C0, 0x0780, 0xC741, 0x0500, 0xC5C1, 0xC481, 0x0440,
    0xCC01, 0x0CC0, 0x0D80, 0xCD41, 0x0F00, 0xCFC1, 0xCE81, 0x0E40,
    0x0A00, 0xCAC1, 0xCB81, 0x0B40, 0xC901, 0x09C0, 0x0880, 0xC841,
    0xD801, 0x18C0, 0x1980, 0xD941, 0x1B00, 0xDBC1, 0xDA81, 0x1A40,
    0x1E00, 0xDEC1, 0xDF81, 0x1F40, 0xDD01, 0x1DC0, 0x1C80, 0xDC41,
    0x1400, 0xD4C1, 0xD581, 0x1540, 0xD701, 0x17C0, 0x1680, 0xD641,
    0xD201, 0x12C0, 0x1380, 0xD341, 0x1100, 0xD1C1, 0xD081, 0x1040,
    0xF001, 0x30C0, 0x3180, 0xF141, 0x3300, 0xF3C1, 0xF281, 0x3240,
    0x3600, 0xF6C1, 0xF781, 0x3740, 0xF501, 0x35C0, 0x3480, 0xF441,
    0x3C00, 0xFCC1, 0xFD81, 0x3D40, 0xFF01, 0x3FC0, 0x3E80, 0xFE41,
    0xFA01, 0x3AC0, 0x3B80, 0xFB41, 0x3900, 0xF9C1, 0xF881, 0x3840,
    0x2800, 0xE8C1, 0xE981, 0x2940, 0xEB01, 0x2BC0, 0x2A80, 0xEA41,
    0xEE01, 0x2EC0, 0x2F80, 0xEF41, 0x2D00, 0xEDC1, 0xEC81, 0x2C40,
    0xE401, 0x24C0, 0x2580, 0xE541, 0x2700, 0xE7C1, 0xE681, 0x2640,
    0x2200, 0xE2C1, 0xE381, 0x2340, 0xE101, 0x21C0, 0x2080, 0xE041,
    0xA001, 0x60C0, 0x6180, 0xA141, 0x6300, 0xA3C1, 0xA281, 0x6240,
    0x6600, 0xA6C1, 0xA781, 0x6740, 0xA501, 0x65C0, 0x6480, 0xA441,
    0x6C00, 0xACC1, 0xAD81, 0x6D40, 0xAF01, 0x6FC0, 0x6E80, 0xAE41,
    0xAA01, 0x6AC0, 0x6B80, 0xAB41, 0x6900, 0xA9C1, 0xA881, 0x6840,
    0x7800, 0xB8C1, 0xB981, 0x7940, 0xBB01, 0x7BC0, 0x7A80, 0xBA41,
    0xBE01, 0x7EC0, 0x7F80, 0xBF41, 0x7D00, 0xBDC1, 0xBC81, 0x7C40,
    0xB401, 0x74C0, 0x7580, 0xB541, 0x7700, 0xB7C1, 0xB681, 0x7640,
    0x7200, 0xB2C1, 0xB381, 0x7340, 0xB101, 0x71C0, 0x7080, 0xB041,
    0x5000, 0x90C1, 0x9181, 0x5140, 0x9301, 0x53C0, 0x5280, 0x9241,
    0x9601, 0x56C0, 0x5780, 0x9741, 0x5500, 0x95C1, 0x9481, 0x5440,
    0x9C01, 0x5CC0, 0x5D80, 0x9D41, 0x5F00, 0x9FC1, 0x9E81, 0x5E40,
    0x5A00, 0x9AC1, 0x9B81, 0x5B40, 0x9901, 0x59C0, 0x5880, 0x9841,
    0x8801, 0x48C0, 0x4980, 0x8941, 0x4B00, 0x8BC1, 0x8A81, 0x4A40,
    0x4E00, 0x8EC1, 0x8F81, 0x4F40, 0x8D01, 0x4DC0, 0x4C80, 0x8C41,
    0x4400, 0x84C1, 0x8581, 0x4540, 0x8701, 0x47C0, 0x4680, 0x8641,
    0x8201, 0x42C0, 0x4380, 0x8341, 0x4100, 0x81C1, 0x8081, 0x4040 
};
 
unsigned int8 CRC16(unsigned int16 * pcBlock, unsigned int16 len){             // * pcBlock - ��������� �� ������, �� ������� ��������� CRC16
                                                                              // len - ���-�� ��������� � ���� �������
    unsigned int8 crc = 0xFFFF;
 
    while (len--)
        crc = (crc >> 8) ^ CRC16Table[(crc & 0xFF) ^ *pcBlock++];
 
    return crc;
}

static void OscSetup(){
  U2BRG = 259;// BAUD Rate Setting for 9600
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
  enable_interrupts(INTR_CN_PIN|PIN_B4);
  enable_interrupts(INTR_CN_PIN|PIN_B3);
  enable_interrupts(INTR_CN_PIN|PIN_B2);
  enable_interrupts(INT_TIMER2);                                  // ��������� ���������� �� ������� 2
  enable_interrupts(INT_TIMER1);
  EXT_INT_EDGE(L_TO_H);
}

static void DisableInt (){
  DISABLE_INTERRUPTS(INTR_GLOBAL);
  disable_interrupts(INTR_CN_PIN|PIN_B5);
  disable_interrupts(INTR_CN_PIN|PIN_B4);
  disable_interrupts(INTR_CN_PIN|PIN_B3);
  disable_interrupts(INTR_CN_PIN|PIN_B2);
}

static void MCU_init(){
   setup_timer1(TMR_INTERNAL | TMR_DIV_BY_64);                     // ������ 1 ���������� ������� ������
   set_timer1(20000);                                              //reset the timer.   
   SETUP_TIMER2(TMR_INTERNAL | TMR_DIV_BY_1);                     // ��������� ������� 2. ������������ = 8.
   SET_TIMER2(Freq);                                              // ������� ��������� �������, �� �������� �� ����� �������
  
   SETUP_SPI2(SPI_MASTER|SPI_SCK_IDLE_LOW|SPI_XMIT_H_TO_L|SPI_MODE_8B|SPI_SAMPLE_AT_END|SPI_SS_DISABLED|SPI_CLK_DIV_128);
 
   SCK2_TRIS=0; // SPI2 tris
   SDI2_TRIS=1;
   SDO2_TRIS=0;

   TRG12 = 0; // lcd buf tris
   TRG13 = 0;
   TRB1 = 0;
   TRB0 = 0;
 
   LCD_RS_TRIS=0;
   LCD_RW_TRIS=0;
   LCD_E_TRIS=0;
 
   ADC_CS_TRIS=0;
   ADC_RESET_TRIS=0;
   ADC_SYNC_TRIS=0;
   ADC_DRDY_TRIS=1; // ����� ��������� ������ ���
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
   while (counter < 2000);   
   }

static void LCD_print_menu(){
   LCDsetCursor(Line_1);
   LCDMsg("ADC sps set  ");
   LCDsetCursor(Line_2);
   LCDMsg("����. K1 set ");
   LCDsetCursor(Line_3);
   LCDMsg("����. K2 set ");
   LCDsetCursor(Line_4);
   LCDMsg("Reset device ");
   }

// ������������ �� ����
static void LCD_main_menu (void) {
   LCD_print_menu();
   switch (menu_sel){
      case 0: 
         LCDsetCursor(0x0D); LCDMsg(0x91); LCDMsg("- ");
         LCDsetCursor(0x4D); LCDMsg("   "); // �������� ������� �� �����������
         LCDsetCursor(0x1D); LCDMsg("   "); // �������� ����
         LCDsetCursor(0x5D); LCDMsg("   ");
         break;
    
      case 1: 
         LCDsetCursor(0x0D); LCDMsg("   ");
         LCDsetCursor(0x4D); LCDMsg(0x91); LCDMsg("- "); // �������� ������� �� �����������
         LCDsetCursor(0x1D); LCDMsg("   "); // �������� ����
         LCDsetCursor(0x5D); LCDMsg("   ");
         break;
    
      case 2: 
         LCDsetCursor(0x0D); LCDMsg("   ");
         LCDsetCursor(0x4D); LCDMsg("   "); // �������� ������� �� �����������
         LCDsetCursor(0x1D); LCDMsg(0x91); LCDMsg("- "); // �������� ����
         LCDsetCursor(0x5D); LCDMsg("   ");
         break;
    
      case 3: 
         LCDsetCursor(0x0D); LCDMsg("   ");
         LCDsetCursor(0x4D); LCDMsg("   "); // �������� ������� �� �����������
         LCDsetCursor(0x1D); LCDMsg("   "); // �������� ����
         LCDsetCursor(0x5D); LCDMsg(0x91); LCDMsg("- ");
         break;
      }  
   }

// ������ ������������ �������
static void Full_dev_reset(){
   LCDClear();
   LCDsetCursor(Line_1);
   LCDMsg("   Reset done");
   LCDsetCursor(Line_3);
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
   meas_stop_fl = 0; // ���. ����� ���������
   menu_fl = 0;      // ���������� ����
   menu_item = 0;    // ����� �������� ����
   NumAver = 1;      // ����� �������� ���������� ������ ���
   LCDClear();       // ������� �������
   }

/* ������� ��� ���������� ���������� � float, ����� ����� �
   ����� ���� ������� �� �������.*/
static void Destroy_float (float Variable_float){             
   Integer_part = Variable_float;                                                               // ��������� ����� �����
   Tenth = (Variable_float - Integer_part) * 10;                                                // ��������� ������� �����  
}

/* �������, ������� ������� �������� �����-���� ����� ����� �������*/
/* This function ... */

static unsigned int8 Remainder (float Parameter, unsigned int8 Digit){           // Digit - ���������� ����� ����� ����� �������, ������� ����� �������
                                                                                 // Parameter - �����, ������� ����� �������� ����� �������
   unsigned int32 Temporary = 0;                                                 // ��������� ����������
//   unsigned int8 N = 0;                                                        // ��������� ����������
   unsigned int8 ValueDigit = 0;                                                 // �������� �����
   unsigned int8 i = 0;
   unsigned int8 Degree = 1;
//   N = Digit + 1;
   for(i = 1; i <= Digit; i++){
      Degree = Degree * 10;
   }  
   Temporary = (abs(Parameter)) * Degree;
   ValueDigit = Temporary % 10;      
   return ValueDigit;
}

/* ������� �������� ����� ����� �, � ������ ������������� ����������� ������� ���� ����� */
/* This function delet fractional part and delet minus if temperature is negative */

static unsigned int16 PositiveTemperature(){
   unsigned int16 IntegerPartPosTemp = 0;
   if (TemperatureInCelsius >= 0){
      IntegerPartPosTemp = TemperatureInCelsius;                                 // ����������� ���������� int16 ������������� �������� ���������� float32. �
                                                                                 // ���������� ������� ������������� ����� ��������. ������� ����� �������������.
   }
   else
      IntegerPartPosTemp = abs(TemperatureInCelsius);                            // ����������� ���������� int16 ������������� �������� ���������� float32 ���������� ��
                                                                                 // ����� 1. � ���������� ������� ������������� ����� ��������. ������� ����� �������������.
   return IntegerPartPosTemp;
}

static void ADC_rd_and_print_ch(U8 chanel){
   unsigned int16 IntegerPartTempInKelvin = 0;
   S32 Temporary_K = 0;
   unsigned int16 Temporary = 0;
   unsigned int8 Tenth_C, Hundredth_C, Thousandth_C = 0;
   ADC_setCh(chanel);
   ADCaddCoef =0;                                                                // �������� ���� ��� ������ 
   ADCmulCoef =1;                                                                // ������������. ������ ��� ������ 

   TemperatureInCelsius = ADC_vol_to_T();                                        // ����������� �������� ����������� � ����������� � ���������� TemperatureInCelsius
   DisableInt();
   printf("%f \n\r",TemperatureInCelsius);
   EnableInt();

   if (PositiveTemperature() >= 0 & PositiveTemperature() < 10) LCD_num_symb = 1;// 
   if (PositiveTemperature() >= 10) LCD_num_symb = 2;                            // ����������� ���-�� ���� � ����� �����
   if (PositiveTemperature() >= 100) LCD_num_symb = 3;                           //
   
// ����� � ������ ������ �������/////////////////////////////////////
   LCDsetCursor(Line_1);
   LCDMsg("T=");
   if (TemperatureInCelsius < 0){
      LCDMsg("-");
      LCDPutU16(PositiveTemperature(),LCD_num_symb);
      }
   else LCDPutU16(PositiveTemperature(),LCD_num_symb);                           // ����� �� ������� ����� ����� ����������� � �������� �������
   LCDMsg(".");
   LCDPutU16(Remainder(TemperatureInCelsius,1),1);                               // ����� �� ������� ���������� ���� ����������� � �������� �������
   LCDPutU16(Remainder(TemperatureInCelsius,2),1);                               // ����� �� ������� ����� ���� ����������� � �������� �������
   LCDPutch(0xb0);LCDMsg("C ");
   LCDPutU16(Number_Pulse,5);

// ����� �� ������ ������ ������� ////////////////////////////
   LCDsetCursor(Line_2);
   LCDMsg("T=");
   TemperatureInKelvin = TemperatureInCelsius + 273.15;
   IntegerPartTempInKelvin = TemperatureInKelvin;
   
   if (TemperatureInKelvin < 10) {LCD_num_symb_K = 1;}                           //
   if (TemperatureInKelvin >= 10){LCD_num_symb_K = 2;}                           // ����������� ���-�� ���� � ����� �����
   if (TemperatureInKelvin >= 100){LCD_num_symb_K = 3;}                          //
  
   LCDPutU16(IntegerPartTempInKelvin,LCD_num_symb_K);                            // ����� �� ������� ����� ����� ����������� � �������� ��������
   LCDMsg(".");
   LCDPutU16(Remainder(TemperatureInKelvin,1),1);                                // ����� �� ������� ���������� ���� ����������� � �������� �������
   LCDPutU16(Remainder(TemperatureInKelvin,2),1);                                // ����� �� ������� ����� ���� ����������� � �������� �������
   LCDPutch(0xb0);LCDMsg("K");
   
//   if(LCD_num_symb_K==1){LCDPutch(0xb0);LCDMsg("K        ");}  // ������� ������ 
//   if(LCD_num_symb_K==2){LCDPutch(0xb0);LCDMsg("K       "); }
//   if(LCD_num_symb_K==3){LCDPutch(0xb0);LCDMsg("K      "); }

// ����� � ������ ������ ������� ////////////////////////////
   LCDsetCursor(Line_3);
//   LCDMsg("Tmin=-196");LCDPutch(0xb0);LCDMsg("C");
   LCDMsg("������. "); LCDPutU32(TmpInt,7);

// ����� � �������� ������ ������� ////////////////////////////
   LCDsetCursor(Line_4); 
//   LCDMsg("Tmax=150");LCDPutch(0xb0);LCDMsg("C");
   LCDMsg("�������. "); LCDPutU32(P,7);
}

/* ������� ��� ���������� ������ �� flash*/
static void save_to_flash(){
   CRC_Wr = CRC16(flash_wr_U16,2);
   Sps_Wr = ADC_sps_var;
   Wr_Flash2();
   } 

// �������������� �������� ���������
#int_cni
static void cn_irq_handler(void) {
   meas_stop_fl = 1;                                              // ����� ����� ��������� ���������
   menu_fl = 1;                                                   // ����� ����� �������� � ����
      
   if (menu_item == 1){
      if (menu_sel > 3) menu_sel = 0;
      if (menu_sel < 0) menu_sel = 3;
      }
   if (CN1 == 1) {
      menu_item = 0;
      LCD_clear_fl = 1;
      }
   if (CN2==1) menu_item = 1;
   if (CN3==1) menu_sel--;
   if (CN4==1) menu_sel++;
   clear_interrupt(INTR_CN_PIN);
}

#int_timer1
static void timer1_irq_handler(void) {
   restart_wdt();                                  // ���� �������� �������
   set_timer1(20000);                              //reset the timer.
   clear_interrupt(int_timer1);
   }

/* �� ����� ����������, ������ 2 ������������� ������ � ���������� � ���������� "count" 1.
���� ���������� "count" ���������� � ���-��� ��������� � "Number_Pulse", ��
����������� ����������. ����� ���������� "count" ������ ������ ���-�� ���������
�� ��� �������, �� ����������� ��������� � ���������� "count" ���������.
*/
/* When variable "count" will equal number unit impuls, pin RD11 will fall.
When variable "count" will equal number impuls in period, pin RD11 will rise.
*/
#int_timer2                                                        // ���������� ���������� �� ������� 2
static void timer2_isr_handler(void) {
   set_timer2(Freq);                                               // reset the timer.
   count++;
   
   if(count >= Number_Pulse) RD11 = 0;
   if(count >= T_Pulse) {
      RD11 = 1;
      count = 0;
      }  
   clear_interrupt(int_timer2);
}

/*��� ���������� ���-���������? ���� ������� ����� ������� ������������ � ������,
�������� �� ������������� �����������, �������� ��������, ������� ���� ������ �
������ ������. ��� ���������������� ������������, ��� �������� � ������ ���������
��������������� � �� ���� ����������� ����������� ��� �� ��������� �������, ���
� �� ��������� �������.
����� �������������� �������� �����������, � ���� ��������� ������������ ������������.
�� ���������������, ������� ���� � �������, ��� �� ���������� (��������������,
��� ������ �� ��������� � ����� �����������, ���� ��������� � ����� �������������).
� ����������� ��������, �� ����� �������������, ��� ���� ��������-������ � ��������.
� ���������� ������ �������, ��� ������������ ��������, ����� ��������� ����� ��������
��������� ����� ����� � ����� � ���������, ������� ������������ ������ ����������
�����, � ��������� �������� � �������� ���������� ����������, ������� ��������
���������� �������� ���������� ����������. ������, ��� ��� ��� ���� �������� ������
�����������, ��������������� �����������, ���������������� ������������ �� ��������
������.
*/

static void PI_regulator(){
   float Tmp = 0;  
//   float P = 0;                                                                  // Proportional term
   if (TemperatureInCelsius >= 60) RD11 = 0;                                     // �������� ������ �� �������������� �������� �����������
// ����������� ������ ����������� ������ � ������, ����� �����
// ��������� � Duty Cycle ������ ����� ��������� � �������.
//   if (Number_Pulse <= T_Pulse){

// �� ��� ���, ���� ������� �����  ���������� ������������ � �����������
// �� �������� 5 ��������, ������������ ���� �� ���������.
      if (TemperatureInCelsius >= (Max_Temp - 5.0)){
         Tmp = Max_Temp - TemperatureInCelsius;
         TmpInt = TmpInt + Tmp * K2;                                                   // Integral term
         if (TmpInt < 0) TmpInt = 0;
         if (Tmp <= 0) Tmp = 0;

         P = K1 * Tmp;                                                                 // Proportional term
         Number_Pulse = (unsigned int16)(P + TmpInt);
      }
      else{
         Tmp = Max_Temp - TemperatureInCelsius;
         P = K1 * Tmp;
         Number_Pulse = (unsigned int16)(P);
      }
//   }
//   else Number_Pulse = Number_Pulse / 2;
//   if (Number_Pulse >= T_Pulse) Number_Pulse = T_Pulse;
}

/*############################################################################*/

static void main(){ 
   TRD11 = 0;                                    // �� �����
   RD11 = 0;                                     // ����������� ��������
  
   Status_LED_TRIS = 0;
   Status_LED = 0;
  
   TRC14 = 0;                                    // ��� RC14 ������������� �� �����
   RC14 = 0;                                     // �������� ���
  
   TRD0 = 0;                                     // ��� RC14 ������������� �� �����
   RD0 = 0;                                      // �������� ���
  
   OscSetup();
   MCU_init();        

   LCDInit();
   LCDwelcome();
  //Rd_Flash2();
  

   LCDSetCursor(Line_1);
   LCDMsg("  Reading data");
   LCDSetCursor(Line_2);
   LCDMsg("   from ROM...");
  
   Rd_Flash2();                                   // ������ ������ �� ���� ��� ������� �����. �����
   crc1 = CRC_buf;                               // ����������� �����. �����    
   crc2 = CRC16(flash_rd_U16,2);                 // ������� �����. �����.
  
   LCDSetCursor(Line_3);
  
   if (crc1==crc2){LCDMsg("       OK!");}
   else {
      LCDMsg("   CRC error!");
      ADC_sps_var = 3;                              // ����� �������� �� ���������, 
      NumAver = 1;                                  // �.�. ��������� ���� �����. �����
      }

   ADC_wakeUp();                             // ����� ��� 
   ADC_wakeUp();                             // ����� ��������������
   ADC_init();                               // ������������� ���
   ADC_SelfCal();                            // �������������� ���
   delay_ms(1000);
  
   LCDclear();
//   T_Pulse = 10000;
//   Number_Pulse = 1000;
//   TmpInt = 0;
   K1 = 600.0;
   K2 = 5.0;
  
/*############################################################################*/  

   while(true){
//      Status_LED = RD11;
/*      delay_ms(200);
      Status_LED = 0;
      delay_ms(200);
      */
//      PI_regulator();                                                                     // ���������� ���������
   
      if (reset_fl)     {Full_dev_reset();}                                               // ������ ����� �������
      if (!meas_stop_fl){ADC_rd_and_print_ch(2);}                                         // ������ ������� ������� ���,                                                                                    
                                                                                          // ����� �� ������� � UART
      PI_regulator();                                                                     // ���������� ���������
      if (menu_fl){                                                                       // ����� � ��������� ���� 
         if (LCD_clear_fl){LCD_clear_fl = 0; LCDClear();}                                 // ������� ������ 
         Bpush_delay();                                                                   // ���������� �������� ������        
         switch (menu_item){                                                              // ����� ����                                                   
            case 0:
               meas_stop_fl = 0; break;                                                   // ������� � ��������� 
            case 1: 
               LCD_main_menu();                                                           // ADC average set
               if  (CN2 == 1){
                  Bpush_delay();
                  if ((CN2 == 1) & (menu_sel==0)){                                        // ADC sps set menu
                     LCD_clear_fl = 1; menu_item = 2; }                       
                  if ((CN2 == 1) & (menu_sel==1)){                                        // �1
                     LCD_clear_fl = 1; menu_item = 3; }                    
                  if ((CN2 == 1) & (menu_sel==2)){                                        // �2
                     LCD_clear_fl = 1; menu_item = 4; }                      
                  if ((CN2 == 1) & (menu_sel==3)){                                        // Reset device
                     LCD_clear_fl = 1; menu_item = 5; }}
               break;
            case 2:                                                                       // ADC sps set menu  
               LCDsetCursor(Line_1);
               LCDMsg("Samples per sec.");
               LCDsetCursor(Line_3);
               if(CN4){Bpush_delay(); if(CN4) ADC_sps_var=ADC_sps_var-1; delay_ms(200);}
               if(CN3){Bpush_delay(); if(CN3) ADC_sps_var=ADC_sps_var+1; delay_ms(200);}
               if(ADC_sps_var>7)  ADC_sps_var = 7;
               if(ADC_sps_var==0) ADC_sps_var = 1;
               switch (ADC_sps_var){                                                      // �������� �������� �������� ��������� ��� 
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
            case 3:                                                                       // K1  
               LCDsetCursor(Line_1);
               LCDMsg(" ����������� �1 ");
               LCDsetCursor(Line_3);               
               if(CN4 == 1){
                  Bpush_delay();
                  if(CN4 == 1){
                     count_CN4++;                                                         // ��� ��������� ����������, ���� ����� ���� ������
                     if (count_CN4 <= 20) K1 = K1 - 0.1;
                     if (count_CN4 >= 21) {K1 = K1 - 1.0; K1 = K1 - 0.1;}
                     if (count_CN4 >= 40) K1 = K1 - 10.0;
                     if (count_CN4 >= 60) K1 = K1 - 100.0;
                     delay_ms(80);
                     }                                                                    // ��������� ������������ �1                 
                  }
                  else if(CN4 == 0) count_CN4 = 0;  
               if(CN3 == 1){
                  Bpush_delay();
                  if(CN3 == 1){
                     count_CN3++;                                                         // ��� ��������� ����������, ���� ����� ������� ������
                     if (count_CN3 <= 20) K1 = K1 + 0.1;
                     if (count_CN3 >= 21) {K1 = K1 + 1.0; K1 = K1 + 0.1;}
                     if (count_CN3 >= 40) K1 = K1 + 10.0;
                     if (count_CN4 >= 60) K1 = K1 + 100.0;
                     delay_ms(80);
                     }                 
                  }
                  else if(CN3 == 0) count_CN3 = 0;
               if (K1 <= 1) K1 = 1;
               Destroy_float(K1);                                                         // �������� ������������ �1 �� ����� ����� � �������
               LCDsetCursor(0x16);
               LCDputU16(Integer_part,4); LCDMsg(","); LCDputU16(Tenth,1);                // ����� �� ������� ������������ �1          
               save_to_flash();
               break;              
            case 4:                                                                       // K2  
               LCDsetCursor(Line_1);
               LCDMsg(" ����������� �2 ");
               LCDsetCursor(Line_3);
               if(CN4 == 1){
                  Bpush_delay();
                  if(CN4 == 1){
                     count_CN4++;                                                         // ��� ��������� ����������, ���� ����� ������� ������
                     if (count_CN4 <= 20) K2 = K2 - 0.1;
                     if (count_CN4 >= 21) {K2 = K2 - 1.0; K2 = K2 - 0.1;}
                     if (count_CN4 >= 40) K2 = K2 - 10.0;
                     delay_ms(80);
                     }                                                                    // ��������� ������������ �2                 
                  }
                  else if(CN4 == 0) count_CN4 = 0;  
               if(CN3 == 1){
                  Bpush_delay();
                  if(CN3 == 1){
                     count_CN3++;                                                         // ��� ��������� ����������, ���� ����� ������� ������
                     if (count_CN3 <= 20) K2 = K2 + 0.1;
                     if (count_CN3 >= 21) {K2 = K2 + 1.0; K2 = K2 + 0.1;}
                     if (count_CN3 >= 40) K2 = K2 + 10.0;
                     delay_ms(80);
                     }                 
                  }
                  else if(CN3 == 0) count_CN3 = 0;
               LCDsetCursor(0x16);
               Destroy_float(K2);                                                         // �������� ������������ �2 �� ����� ����� � �������
               LCDputU16(Integer_part,2); LCDMsg(","); LCDputU16(Tenth,1);                // ����� �� ������� ������������ �2
               save_to_flash();
               break;               
            case 5:                                                                       // Reset menu
               LCDsetCursor(Line_1);
               LCDMsg(" Reset device?");
               LCDsetCursor(Line_3);
               LCDMsg("    Yes -> +");
               LCDsetCursor(Line_4);
               LCDMsg("    No  -> -");
               if(CN3){Bpush_delay(); if(CN3) {reset_fl = 1;}}                            // �������� ����� RESET ��� ������ ���� �������
               if(CN4){Bpush_delay(); if(CN4) {menu_item= 1;}}                            // ������ � ����� � ����        
               break;
            }  
         }  
      }
}
/*############################################################################*/
