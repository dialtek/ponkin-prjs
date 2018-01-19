//#include "C:\PRJ\RemTermo\Remtermo.h"
#include <16F88.h>
#device *=16
#device adc=10

#FUSES NOWDT                    //No Watch Dog Timer
#FUSES HS                       //High speed Osc (> 4mhz)
#FUSES NOPUT                    //No Power Up Timer
#FUSES MCLR                     //Master Clear pin enabled
#FUSES BROWNOUT                 //Reset when brownout detected
#FUSES NOLVP                    //No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O
#FUSES NOCPD                    //No EE protection
#FUSES NOWRT                    //Program memory not write protected
#FUSES NODEBUG                  //No Debug mode for ICD
#FUSES NOPROTECT                //Code not protected from reading
#FUSES NOFCMEN                  //Fail-safe clock monitor disabled
#FUSES IESO                      //Internal External Switch Over mode enabled

#BYTE portA = 0x05
#BYTE portB = 0x06

#BYTE TRISA = 0x85               
#BYTE TRISB = 0x86 
#BYTE PIR1 = 0x0C 

#bit TRB5=TRISB.5
#bit TRB4=TRISB.4

#bit PORTB4=PORTB.4

#byte TXREG=0x19
#byte TXSTA=0x98
#bit TXEN=TXSTA.5
#bit TRMT=TXSTA.1
#bit TXIF=PIR1.4                 

#use delay(clock=10000000)
#use rs232(UART1,baud=9600,parity=N,xmit=PIN_B5,rcv=PIN_B2,bits=8)

unsigned char txbuf[30],msgbuf[20];
unsigned int8 j,k=0;

#int_TBE
void tbe_int(void){
//буфер передатчика пуст
 if(k<=j){
 TXREG=txbuf[k];
  ++k;
  }else TXEN=0;
clear_interrupt(int_tbe);
}


/*
  Name  : CRC-8
  Poly  : 0x31    x^8 + x^5 + x^4 + 1
  Init  : 0xFF
  Revert: false
  XorOut: 0x00
  Check : 0xF7 ("123456789")
  MaxLen: 15 байт(127 бит) - обнаружение
    одинарных, двойных, тройных и всех нечетных ошибок
*/
unsigned char Crc8(unsigned char *pcBlock, unsigned int len)
{
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

void main()
{
unsigned int16 temp1,temp2,Vdd,V,Vpoint;
unsigned int8 fgrad1,pgrad1,fgrad2,pgrad2,i,pl=8;


   setup_adc_ports(sAN0|sAN1|sAN2|VSS_VREF);
   setup_adc(ADC_CLOCK_DIV_16);
   setup_timer_0(RTCC_INTERNAL|RTCC_DIV_1);
   setup_comparator(NC_NC_NC_NC);
   setup_vref(FALSE);
//Setup_Oscillator parameter not selected from Intr Oscillator Config tab

   // TODO: USER CODE!!
  TRB4=0;
  PORTB4=0;
  TXEN=0;
  enable_interrupts(int_TBE);
  enable_interrupts(GLOBAL);
  
 while(true){
 
 //формирование начала сообщени€
  //символы 0x0 в начале собщени€ дл€ включени€ передатчика в количестве pl
  for(j=0;j<pl;++j){
     txbuf[j]=0x0;
  }
    txbuf[j]=0xAA;// начало блока данных
    ++j;
    txbuf[j]=0xAA;
 
   set_ADC_channel(0);
      delay_us(30);
     temp1=read_ADC()*2;// градусы ÷ельси€,умноженные на 10,с разрешением 2(0.2)градуса
          
      fgrad1= temp1/10;
      pgrad1= temp1-fgrad1*10;
 
   set_ADC_channel(1);
     delay_us(30);
    temp2=read_ADC()*2;// градусы ÷ельси€,умноженные на 10,с разрешением 2(0.2)градуса
    
     fgrad2= temp2/10;
     pgrad2= temp2-fgrad2*10;
 
    set_ADC_channel(2);
      delay_us(30);
       V=read_ADC()*4*2;// напр€жение батареи в милливольтах
       
       Vdd=V/1000;
       Vpoint=V-Vdd*1000;
 
 
   msgbuf[0]=temp1>>8;//ст. байт
   msgbuf[1]=temp1;// мл. байт
   
   msgbuf[2]=temp2>>8;
   msgbuf[3]=temp2;
   
   msgbuf[4]=V>>8;
   msgbuf[5]=V;
   
   msgbuf[6]=crc8(msgbuf,6);//вычисл€ем crc8
   msgbuf[7]=0x55;// конец блока
   //
   for(i=0;i<8;++i){
   j=j+1;
    txbuf[j]=msgbuf[i];
   }
   j=18;
   k=0;
   TXEN=1;// начало передачи  

 //printf("      T1=%u.%u C   T2=%u.%u C   Vdd=%Lu.%Lu V    \n\r",fgrad1,pgrad1,fgrad2,pgrad2,Vdd,Vpoint);
 
    
 
  delay_ms(10000);
 }
}
