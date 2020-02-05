#include "xc.h"
#include "fuses.h"
#include <p24HJ128GP506.h>
#define FCY 40000000UL
#include <libpic30.h>
#include <stdio.h>
#include <stdint.h>
#define _ISR_PSV __attribute__((__interrupt__, __auto_psv__))

// !!!!! 07.11.19 использовать только p24HJ128GP506, с p24HJ128GP506A возникают проблемы с SPI EEPROM


#define FP 40000000
#define BAUDRATE 115200
#define U1BRGVAL ((FP/BAUDRATE)/16)-1

#define STATUS_LED LATFbits.LATF5

#define ADC1_RESET LATDbits.LATD3
#define ADC2_RESET LATDbits.LATD0
#define ADC1_SYNC  LATDbits.LATD2
#define ADC2_SYNC  LATDbits.LATD11
#define ADC1_CS    LATGbits.LATG9
#define ADC2_CS    LATDbits.LATD10
#define ADC1_DRDY  PORTDbits.RD1
#define ADC2_DRDY  PORTDbits.RD9 

// ADC1256 Register map
#define STATUS 0x00     
#define MUX 0x01 
#define ADCON 0x02
#define DRATE 0x03
#define IO 0x04
#define OFCO 0x05
#define OFC1 0x06
#define OFC2 0x07
#define FSCO 0x08
#define FSC1 0x09
#define FSC2 0x0A
#define uV 10000000  // для калибровки 
//#define uV 100000 // по умолчанию
#define mV 1000

#define SET_CH      10
#define GET_CH_DATA 20

//enum ADC_MUX_ch {
//    
//    ch1 = 0,
//    ch2 = 0x76,
//    ch3 = 0x54,
//    ch4 = 0x10
//};

// коды каналов мультиплексора со смещением на один для удобства
unsigned char Mx_ch_code[5] = {0, 0x76, 0x54, 0x32, 0x10};

unsigned char PGA;
unsigned char PGA_val = 4; // PGA = 16, +- 312,5 мВ
   
unsigned char Sps_buf=0; 
unsigned char input_buf_state=1; // вх. буфер АЦП

unsigned char meas_stop_fl = 0;
unsigned char reset_fl = 0;      // флаг сброса системы

unsigned char NumAver = 1;       // размер усреднения
unsigned char ADC_sps_var = 2;   // переменная усреднения данных АЦП - 10sps default

//Ma - Moving Average
signed long Ch_buf[8][128];      // буфер скользящего среднего  unsigned signed long ADC_counts[2][8];    // буфер отсчетов АЦП
signed long ADC_counts[2][8];    // буфер отсчетов АЦП
signed long Ch_buf_sum;          // сумма буфера скользящего среднего

unsigned char Ma_buf_index = 0; // индекс элемента скользящ. средн.
unsigned char Ma_buf_size = 5;  // РАЗМЕР БУФЕРА
unsigned char Ma_buf_cnt = 0;   // счетчик эл. буфера

unsigned char state;
unsigned int tmp=0;

// результаты измерений
signed long pkt8_ch_1 = 0, pkt8_ch_2 = 0, pkt8_ch_3 = 0, pkt8_ch_4 = 0, 
            pkt8_ch_5 = 0, pkt8_ch_6 = 0, pkt8_ch_7 = 0, pkt8_ch_8 = 0;

signed long pkt8_ch[8] = {0,0,0,0,0,0,0,0};

unsigned char channel = 1;

unsigned int meas_status; // статус бит обновления измерений

unsigned char ADC_state = 0; // начальное состояние машины чтения

#include "dialtek_modbus.h" 
/*=========================================================================== */    
void OSC_init()
{
        // FCY=FOSC/2, FOSC= FIN*M/(N1*N2) 
        CLKDIVbits.PLLPRE = 0;      // 0 - divider N1 = 2
        PLLFBD = 30;                // multiplier M = PLLFBD + 2
        CLKDIVbits.PLLPOST = 0;     // 0 - divider N2 = 2
        
        OSCTUN=0;                   // 000000 = Center frequency (7.37 MHz nominal)
        RCONbits.SWDTEN=0;          // Disable Watch Dog Timer
        
        while(OSCCONbits.LOCK !=1); // 1 = Indicates that PLL is in lock, or PLL start-up timer is satisfied
                                    // 0 = Indicates that PLL is out of lock, start-up timer is in progress or PLL is disabled
        //note: FOSC= 10 MHz * 32/(2*2) = 80 MHz, FCY = 80/2
 } 

void GPIO_init()
{
  
    TRISCbits.TRISC14 = 0;  // RX-485 TX EN
    TRISFbits.TRISF5 = 0;   // LED
    TRISCbits.TRISC1 = 0;   // EEPROM CS
    
    TRISFbits.TRISF2 = 1;   // U1 RX
    TRISFbits.TRISF3 = 0;   // U1 TX
  
    TRISGbits.TRISG6 = 0;   // SPI2 SCK
    TRISGbits.TRISG7 = 1;   // SPI2 SDI
    TRISGbits.TRISG8 = 0;   // SPI2 SDO
  
    TRISDbits.TRISD3 = 0;   // ADC1 reset 
    TRISDbits.TRISD0 = 0;   // ADC2 reset 
    TRISDbits.TRISD2 = 0;   // ADC1 SYNC
    TRISDbits.TRISD11 = 0;  // ADC2 SYNC
    TRISGbits.TRISG9  = 0;  // ADC1 CS
    TRISDbits.TRISD10 = 0;  // ADC2 CS
    TRISDbits.TRISD1 = 1;   // ADC1 DRDY
    TRISDbits.TRISD9 = 1;   // ADC2 DRDY 
    
    AD1PCFGL = 0xffff; // Port pin in Digital mode, port read input enabled, 
    AD1PCFGH = 0xffff; 
  
}
/*=========================================================================== */
// UART 1 - Modbus + Modbus state machine timer 
void UART1_init()
{
    // RX interrupt UART1 settings 
    //IPC2bits.U1RXIP = 4; // Set UART1 RX interrupt priority to 1 
    IFS0bits.U1RXIF = 0;   // Reset UART1 RX interrupt flag
    
    U1BRG = U1BRGVAL;      // Baud Rate setting for 115200 uart
    U1MODEbits.UARTEN = 1;  // 1 = UARTx is enabled; all UARTx pins are controlled by UARTx as defined by UEN <1:0>
    U1MODEbits.UEN = 0;     // 0 = UxTX and UxRX pins are enabled and used; UxCTS and UxRTS/BCLK pins controlled by port latches
    U1MODEbits.PDSEL = 0;   // 0 = No Parity, 8-Data bits
    U1MODEbits.ABAUD = 0;   // 0 = Baud rate measurement disabled or completed
    U1MODEbits.BRGH = 0;    // 1 = BRG generates 4 clocks per bit period (4x baud clock, High-Speed mode)
    U1MODEbits.STSEL = 0;   // 0 = 1-Stop bit

//    U1STAbits.UTXISEL0 = 0; // Interrupt when a unsigned character is transferred to the Transmit Shift Register (this implies there isat least one unsigned character open in the transmit buffer
//    U1STAbits.UTXISEL1 = 0;
    U1STAbits.UTXINV = 0;
    U1STAbits.UTXEN = 1;    // 1 = Transmit enabled, UxTX pin controlled by UARTx
    U1STAbits.URXISEL = 0;  // 0x = Interrupt is set when any unsigned character is received and transferred from the UxRSR to the receive buffer. Receive buffer has one or more unsigned characters.
                            // The URXISEL<1:0> (UxSTA<7:6>) control bits determine when the UART receiver generates an interrupt.
 
    IEC0bits.U1RXIE = 1; // Enable UART1 RX interrupt  
 }

void U1_send_byte(unsigned char Ch)
{ // отправка 1 байта данных
       
        U1TXREG = Ch;
        //  should wait at least one instruction cycle between 
        //  writing UxTXREG and reading the TRMT bit
        __delay_us(1);
        while(U1STAbits.TRMT == 0); //waiting for trancsaction to be complete   

 }
 
void _ISR_PSV _U1RXInterrupt(void)      //interupt UART 1 RX MODBUS
    {
      // rx buffer has data, at least one more character can be read
      while(U1STAbits.URXDA == 0){ }
      
      rx_buf[rx_buf_ptr++] = U1RXREG;

      IFS0bits.U1RXIF = 0;    // Clear  UART1_Tx interrupt  

      if(timer_state == 0)
      {
            TMR9 = 0x0000;
            IFS3bits.T9IF = 0;    // Clear Timer interrupt flag
            timer_state = 1;
            T9CONbits.TON = 1;
      }
      else TMR9 = 0x0000;         // reset if timer is on, 115200       
     }

void Timer9_init(unsigned long baudrate)
{
       T9CONbits.TON = 0;           // Timer on/off bit; 0 - Disable Timer
       IFS3bits.T9IF = 0;           // Clear Timer interrupt flag
       TMR9 = 0x0000;               // reset if timer is on, 115200
       T9CONbits.TCS = 0;           // Timer Clock Source Select bit; 0 - Internal clock (FOSC/2)
       T9CONbits.TGATE = 0;         // Disable Gated Timer mode
       T9CONbits.TCKPS = 0;      // Prescaler = (00=1, 01=8, 10=64, 11=256) 
       T8CONbits.T32 = 0;
       
       switch(baudrate)
       {
           case 9600:   break; // 1 byte - 840 us
           case 57600:  break; // 1 byte - 140 us
           case 115200: PR9 = 8400; break; // 1 byte - 70 us, 2800 * 3 = 210 us
           case 230400: break; // 1 byte - 35 us
               
           default: PR9 = 8400; // Load the period value
       }
       
       IEC3bits.T9IE = 1;           // Enable T9 interrupt 
    }

/*=========================================================================== */
// SPI2 - 2 x ADC ADS1256, SPI EEPROM

void SPI2_init(unsigned char latch_edge)
{
                
        SPI2STATbits.SPIEN = 0;         // Turn off spi module before initialization 
        IFS2bits.SPI2EIF   = 0;         // Clear the Interrupt Flag
        IFS2bits.SPI2IF = 0;            // Disable the Interrupt
        // SPI2CON1 Register Settings:
        SPI2CON1bits.DISSCK = 0;        //Internal Serial Clock is Enabled
        SPI2CON1bits.DISSDO = 0;        //SDOx pin is controlled by the module
        SPI2CON1bits.MODE16 = 0;        //Communication is byte-wide (8 bits)
        SPI2CON1bits.SMP = 1;           //Input Data is sampled at the end of data output time
        SPI2CON1bits.CKE = latch_edge;  // Serial output data changes on transition from active clock state to Idle clock state
        SPI2CON1bits.CKP = 0;           // Idle state for clock is a low level; active state is a high level
        
        // SPI2STAT Register Settings
        SPI2STATbits.SPISIDL = 0; // Continue module operation in Idle mode
        SPI2STATbits.SPIROV = 0;  // No Receive Overflow has occurred

        // SPI2 SCK f = 1M @ 80M Fosc, Fcy 40M  
        // Fsck = 833.3 kHz
        SPI2CON1bits.SPRE = 5;          //Secondary prescale 3:1
        SPI2CON1bits.PPRE = 1;          //Primary prescale 16:1
        
        SPI2CON2bits.FRMEN = 0;         //Framed SPIx support is disabled
        SPI2CON1bits.MSTEN = 1;         //Master Mode Enabled
                                          
        SPI2STATbits.SPIEN = 1;         //Enable SPI Module
                                        //Interrupt Controller Settings
        
    }

void SPI2_write_byte (unsigned char buf)               
{
     unsigned char temp;

     SPI2BUF = buf;
     
     while(!SPI2STATbits.SPIRBF);
     
     // после записи необходимы вычитать содержание буфера SPI для сброса флага
     temp = SPI2BUF; 
     
     SPI2STATbits.SPIROV = 0;
 }

unsigned char SPI2_read_byte(void)
{
 unsigned char ret_value = 0;
  
 unsigned int buf = 0; 

 if(SPI2STATbits.SPIROV) 
 { 
    buf = SPI2BUF; 
    SPI2STATbits.SPIROV = 0; 
 } 

  SPI2BUF = 0x00;                  // initiate bus cycle 
  
  while(!SPI2STATbits.SPIRBF);

  SPI2STATbits.SPIROV = 0;
  ret_value = SPI2BUF;    /* return byte read */

  return ret_value;                  		  /* RBF bit is not set return error*/
}
/*=========================================================================== */
//работа с регистрами АЦП

  void clr_bufs()
{
  Ma_buf_cnt = 0;
  Ma_buf_index = 0;
  Ch_buf_sum = 0;
  
  for (unsigned char i = 0; i < 8; i++)
  {
  // заполнение буферов скольз. ср. нулями
   for (unsigned char j = 0; j < 128; j++) 
      {
         Ch_buf[i][j] = 0;
      }
  }
  
  for (unsigned char a = 0; a < 8; a++)
  {
  // заполнение буферов отсчетов нулями
   for (unsigned char b = 0; b < 128; b++) 
      {
         ADC_counts[a][b] = 0;
      }
  }
}

 unsigned char RdReg(unsigned char RegName)
{
   unsigned char RegValue = 0; 
   //1st Command Byte: 0001 rrrr where rrrr is the address of the first register to read.
   //2nd Command Byte: 0000 nnnn where nnnn is the number of bytes to read – 1
   ADC1_CS = 0;
   __delay_us(1);
   SPI2_write_byte(0x10+RegName); // 1st Command Byte,??????? ??????
   SPI2_write_byte(0x00); // 1st Command Byte, ?????? ?????? ???? ????
   __delay_us(8); // 50 CLK_IN PEDIODS
   RegValue = SPI2_read_byte();
   __delay_us(1);
   ADC1_CS =1;
   __delay_us(1);
   return RegValue;  
}

 void WrReg(unsigned char RegName, unsigned char CommandByte)
{
   ADC1_CS = 0;
   ADC2_CS = 0;
   __delay_us(5);
   SPI2_write_byte(0x50+RegName); // 1st Command Byte: 0101 (0x50) rrrr where rrrr is the address to the first register to be written.
   __delay_us(10);
   SPI2_write_byte(0);         // 2nd Command Byte: 0000 nnnn where nnnn is the number of bytes to be written – 1.
   __delay_us(10);
   SPI2_write_byte(CommandByte);
   __delay_us(10);
   ADC1_CS = 1;
   ADC2_CS = 1;
 
   __delay_us(20);
}

// настройка и инициализация АЦП
 void ADC_sps_set(unsigned char SPS){
                                                          
   Sps_buf = SPS;
   WrReg(DRATE,SPS); 
   __delay_us(20);  
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

// PGA присваевается для расчета 

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
   __delay_us(20);
}

 void ADC_SelfCal(){
                     
   ADC1_CS = 0;
   ADC2_CS = 0;
   __delay_us(5);
   SPI2_write_byte(0xF0);
   SPI2_write_byte(0xF0);
   __delay_us(5);
   
   ADC1_CS = 1;
   ADC2_CS = 1;
   
   while(ADC1_DRDY | ADC2_DRDY) { }   // ждем готовности обоих АЦП
   
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

 void ADC_init(unsigned char buf_state){
   
  unsigned char buf_st = buf_state << 1; // подготовка команды вх. буфера
  
  PGA_val = holding_register[18];
  if(PGA_val > 6) PGA_val = 4; // PGA = 16, +- 312,5 мВ
    
  ADC_sps_var = holding_register[19];  // SPS    
  if(ADC_sps_var > 8) ADC_sps_var = 2; // 10 SPS
    
  clr_bufs(); // очистка буфера скользящ. среднего
  Ma_buf_size = holding_register[20];
  // averfge buf size
  if((Ma_buf_size < 1) && (Ma_buf_size > 128))  Ma_buf_size = 5;
  
  WrReg(STATUS,buf_st);   // упр. входным буфером
  __delay_us(20);

   if(ADC_sps_var>8)  ADC_sps_var = 8;
   // установка sps
   switch (ADC_sps_var){                // передача величины скорости измерений АЦП 
    
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
      case 10: ADC_sps_set(0xe0); break; // 15000 sps
      case 11: ADC_sps_set(0xf0); break; // 30000 sps
      
       default: ADC_sps_set(0x23);
      }
      
   ADC_set_PGA(PGA_val);    // Уст. PGA
   ADC_SelfCal();           // Автокалибровка обоих АЦП 
   __delay_us(100);
}
//---------------------- уст. каналов и чтение АЦП --------------------------//

 void ADC_sync(unsigned char state) { /// синхронизация АЦП
  
     
       ADC1_SYNC = state; 
       ADC2_SYNC = state;

  }

 void ADC_select(unsigned char command) { /// выбор АЦП
  
   //command 0 - не выбран ни один АЦП
   //command 1 - выбран АЦП 1
   //command 2 - выбран АЦП 2
   
   switch(command)
   {
         case 0: ADC1_CS = 1; ADC2_CS = 1; break;
         case 1: ADC1_CS = 0; ADC2_CS = 1; break;
         case 2: ADC1_CS = 1; ADC2_CS = 0; break;
   }
  }

 void ADCx_setCh(unsigned char ADCx, unsigned char CHx)
 {

 // уст. каналоа АЦП
 // 1 канал пользователя - 4 канал АЦП по факту (13(+) и 12(-) ножки) и тд.
 
  ADC_select(ADCx); // выбор АЦП
 
  SPI2_write_byte(0x50+MUX);  // уст. канал АЦП   
  SPI2_write_byte(0);         
  SPI2_write_byte(Mx_ch_code[CHx]);
  
  ADC_select(0);
}

 signed long ADC_read(unsigned char ADC_number)
  {
  signed long ADC_RByte_Sum; // суммарные отсчеты АЦП - 24 бита
  ADC_select(ADC_number); // выбор АЦП
  
  SPI2_write_byte(0x01);        // команда чтения Rdata
  __delay_us(20);
  signed long ADC_Rbyte1 = SPI2_read_byte();   // чтение
  signed long ADC_Rbyte2 = SPI2_read_byte();
  signed long ADC_Rbyte3 = SPI2_read_byte();
  
  ADC_select(0); // сброс выбора АЦП
  
  // склеивание трех байт отсчетов АЦП, тут должно быть уже отрицательное число
  ADC_RByte_Sum = (ADC_Rbyte1<<24) | (ADC_Rbyte2<<16) | ADC_Rbyte3<<8;
  ADC_RByte_Sum /=256;

  return ADC_RByte_Sum;
  
  }

 signed long ADCx_read_aver(unsigned char ADCx, unsigned char CHx)
{
  float Vin = 0;          // измеренное напряжение 
  signed long curr_ADCx_val = 0; // переменн. для хранения текущ. усредн. значения
  
  curr_ADCx_val = ADC_read(ADCx);               // сохр. новое изм.

  Vin = (float)((curr_ADCx_val*5.0)/(8388608.0*PGA)); // расчет U
  return (signed long) (Vin*uV); // возврат масштабированного U
 
}

 void ADC_par_rd_ch()
{
// || чтение двух АЦП
    switch (ADC_state)
    {
        case SET_CH:      // уст. канала и строб начала изм.
            ADCx_setCh(1,channel);
            ADCx_setCh(2,channel);
            ADC_sync(0);  // синхр. измерений АЦП
            __delay_us(20);
            ADC_sync(1);
            
            ADC_state = GET_CH_DATA;    // переход в сост. чтения 
        break;
        //----
        case GET_CH_DATA:
            if(ADC1_DRDY == 0 && ADC2_DRDY == 0)  // ждем готовности АЦП
            {   // считываем по готовности
                pkt8_ch[channel-1] = ADCx_read_aver(1,channel-1); // смещяем индекс назад
                pkt8_ch[channel+3] = ADCx_read_aver(2,channel+3); // смещаем индекс вперед
                
                //Ma_buf_index++;       // инкремент индекса   
                //if(Ma_buf_index > Ma_buf_size - 1) Ma_buf_index = 0;     // сброс индекса буфера
                
                channel++;            // инеремент канала изм. 
                if(channel > 4) 
                {
                    channel = 1;
                    meas_status = 1;  // уст. флага обновления измерений
                }        
                meas_status = 1;      // уст. флага обновления измерений
                ADC_state = SET_CH;   // уст. состояния смены канала АЦП и форм. строба синхр. изм.
            }
        break;
        //----
        default:  ADC_state = SET_CH; // уст. состояния смены канала АЦП и форм. строба синхр. изм.
    } 
}
/*=========================================================================== */
// 25LC128 SPI EEPROM
#define EEPROM_READ  0x03  // Read data from memory array beginning at selected address
#define EEPROM_WRITE 0x02  // Write data to memory array beginning at selected address  
#define EEPROM_WREN  0x06  // Set the write enable latch (enable write operations)
#define EEPROM_RDSR  0x05  // Read STATUS register
#define EEPROM_CS LATCbits.LATC1   // SPI EEPROM CS

void eeprom_wr_page(unsigned int address)
{
  // EEPROM write enable sequence
  EEPROM_CS = 0;
  SPI2_write_byte(EEPROM_WREN);
  EEPROM_CS = 1;
  __delay_us(20);
  
  // EEPROM address and data write sequence
  EEPROM_CS = 0;
  SPI2_write_byte(EEPROM_WRITE);
  
  SPI2_write_byte((unsigned char)(address >> 8));      // set address ptr msb
  SPI2_write_byte((unsigned char)(address & 0x00ff));  // set address ptr lsb
  
  for(unsigned char i = 0; i < 32; i++) // max bytes to write - 64
  {
    SPI2_write_byte((unsigned char)(holding_register[i + address/2] >> 8));            // data msb    
    SPI2_write_byte((unsigned char)(holding_register[i + address/2] & 0x00ff));        // data lsb 
  }
  
  __delay_us(5);
  EEPROM_CS = 1;
  
  __delay_ms(8);  // internal Write Cycle Time = 5 ms
}

void eeprom_wr_regs(void)
{
  /// 124 modbus register saving sequence
    
  // 25LC128 SPI EEPROM addres pointer, 248 bytes beginning from 0x00 address
  unsigned int EEPROM_addr = 0; 

  eeprom_wr_page(EEPROM_addr);  // EEPROM memory page 1 - 0...31 regs
  EEPROM_addr += 64;
  eeprom_wr_page(EEPROM_addr);  // EEPROM memory page 2 - 32...63 regs
  EEPROM_addr += 64;
  eeprom_wr_page(EEPROM_addr);  // EEPROM memory page 3 - 64...95 regs
  EEPROM_addr += 64;
  eeprom_wr_page(EEPROM_addr);  // EEPROM memory page 4 - 96...124 regs
}

void eeprom_rd_regs(void)
{
  unsigned char lsb = 0, msb = 0;
  unsigned int address = 0;
  // EEPROM read sequence
  EEPROM_CS = 0;
  SPI2_write_byte(EEPROM_READ);
  
  SPI2_write_byte((unsigned char)(address >> 8));      // set address ptr msb
  SPI2_write_byte((unsigned char)(address & 0x00ff));  // set address ptr lsb

  for(unsigned char i = 0; i < max_regs_cnt-1; i++)
  { 
    msb = SPI2_read_byte();
    lsb = SPI2_read_byte();
    
    holding_register[i] = (msb << 8) | lsb;   
  }
  EEPROM_CS = 1;
}

/*=========================================================================== */ 

void _ISR_PSV _T9Interrupt(void)        //interupt Timer 9
    {      
        T9CONbits.TON = 0;   // stop the timer
        timer_state = 0;
        TMR9 = 0x0000;       // reset if timer is on
        rx_flag = 1;
        
        IFS3bits.T9IF = 0;   // Clear Timer interrupt flag
    } 

int main()
{    
    OSC_init();
    GPIO_init ();
    TX_DIS;       // release RS485 line !!!
    
    Timer9_init(115200);
    UART1_init();
    SPI2_init(0); // ADC SPI mode

    modbus_init();
    
    ADC1_RESET = 1; ADC2_RESET = 1;
    ADC1_CS = 1;    ADC2_CS = 1;
    ADC1_SYNC = 1;  ADC2_SYNC = 1; 
    
    EEPROM_CS = 1;
    __delay_ms(1);
    
    
    holding_register[51] = 0; // сброс регистра уст. ID
    eeprom_rd_regs();         // восстановление значений регистров из SPI EEPROM
    
    // восстановление ID устройства из памяти   
    dev_id = (unsigned char)holding_register[50];
    if(dev_id == 0 || dev_id > 254) dev_id = 100;
    
    // буфер усреднения
    Ma_buf_size = (unsigned char)holding_register[20];
    if(holding_register[20] < 1 || holding_register[20] > 128) 
       Ma_buf_size = 5;
    clr_bufs(); // очистка буфера скользящ. среднего
    
    ADC_sync(1);  
    ADC_init(input_buf_state);         // Инициализация обоих АЦП 
    ADC_init(input_buf_state);         // Инициализация обоих АЦП 
    __delay_ms(100);
    STATUS_LED = 1;
    ADC_state = SET_CH;
    
 while(1)
 {
    ADC_par_rd_ch(); // измерения
    modbus_poll();   
 } 
}