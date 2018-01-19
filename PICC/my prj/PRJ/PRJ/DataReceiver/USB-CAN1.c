#include "C:\PRJ\DataReceiver\USB-CAN1.h"

#BYTE TRISC =0x0F94
#BYTE TRISB =0x0F93
#BYTE TRISA =0x0F92


#BYTE LATC =0x0F8B
#BYTE LATB =0x0F8A
#BYTE LATA =0x0F89

#BYTE PORTC =0x0F82
#BYTE PORTB =0x0F81
#BYTE PORTA =0x0F80

#BYTE RCSTA =0x0FAB
#BYTE RCREG =0x0FAE

#BYTE TXREG =0x0FAD
#BYTE TXSTA =0x0FAC


#bit OERR=RCSTA.1
#bit FERR=RCSTA.2
#bit CREN=RCSTA.4

#bit TXEN=TXSTA.5
#bit TRMT=TXSTA.1

#bit B5 = PORTB.5
#bit B4 = PORTB.4
#bit B3 = PORTB.3
#bit B2 = PORTB.2
#bit B1 = PORTB.1


#bit TRB5 = TRISB.5
#bit TRB3 = TRISB.3
#bit TRB2 = TRISB.2
#bit TRB1 = TRISB.1

#bit A0 = PORTA.0 
#bit A1 = PORTA.1 
#bit A2 = PORTA.2 
#bit A3 = PORTA.3 
#bit A4 = PORTA.4 
#bit A5 = PORTA.5 
#bit A6 = PORTA.6 
#bit A7 = PORTA.7 

#bit TRA0=TRISA.0
#bit TRA1=TRISA.1
#bit TRA2=TRISA.2
#bit TRA3=TRISA.3
#bit TRA4=TRISA.4
#bit TRA5=TRISA.5
#bit TRA6=TRISA.6
#bit TRA7=TRISA.7

#bit C0=PORTC.0
#bit C1=PORTC.1
#bit C2=PORTC.2
#bit C3=PORTC.3
#bit C4=PORTC.4
#bit C5=PORTC.5
#bit C6=PORTC.6
#bit C7=PORTC.7

#bit TRC0=TRISC.0
#bit TRC1=TRISC.1
#bit TRC2=TRISC.2
#bit TRC3=TRISC.3
#bit TRC4=TRISC.4
#bit TRC5=TRISC.5
#bit TRC6=TRISC.6
#bit TRC7=TRISC.7

unsigned char c,rxbuf[20];
int1 fl=0,errfl=0,fl1=0;
unsigned int16  count1=0,count2=0; 
unsigned int8 i=0;

#int_RDA
void RDA_int(void){
//буфер приемника полон
 c=RCREG;
 errfl=FERR;
   if(fl){
    rxbuf[i]=c;
     ++i;
     if(i>15){
       i=0;
       CREN=0;
       fl=0;
       fl1=1;
     }
  }else if(c==0xaa) {
                     fl=1;
                    }
 
clear_interrupt(int_rda);
}

#int_TBE
void tbe_int(void){
//буфер передатчика пуст

// TXREG=c;
 
 
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
   unsigned int8 j=0,k=0,rxcrc,calcrc,fgrad1,pgrad1,fgrad2,pgrad2,vdd;
   unsigned int16 t1,t2,vcc,vpoint;
   setup_adc_ports(NO_ANALOGS|VSS_VDD);
   setup_adc(ADC_OFF|ADC_TAD_MUL_0);
   setup_spi(SPI_SS_DISABLED);
   setup_wdt(WDT_OFF);
   setup_timer_0(RTCC_INTERNAL);
   setup_timer_1(T1_DISABLED);
   setup_timer_2(T2_DISABLED,0,1);
   setup_vref(FALSE);
//Setup_Oscillator parameter not selected from Intr Oscillator Config tab

   // TODO: USER CODE!!
   CREN=0;// прием запрещен
   //TXEN=0;
   enable_interrupts(int_rda);
  // enable_interrupts(int_tbe);
   enable_interrupts(global);
   
   CREN=1;
   //TXEN=1;
  k=0; 
  while(true){
   
   // Delay_MS(1000);
  if(fl1 ){
    // принят пакет сообщения
     if(rxbuf[0]==0xaa && rxbuf[8]==0x55){
     // если формат правильный
     ++k;
      rxcrc=rxbuf[7];
       for(j=0;j<=9;++j){
         rxbuf[j]=rxbuf[j+1];
       }
       /*
        for(j=0;j<=7;++j){
          printf("%X ",rxbuf[j]);
        } */
       
        calcrc=crc8(rxbuf,6);//вычисляем crc принятого пакета 
         if(rxcrc == calcrc) printf(" CRC ok");
         
         else printf(" CRC err");
               
       t1=rxbuf[0];
       t1= t1 << 8;
       t1=t1+rxbuf[1];
       
      fgrad1= t1/10;
      pgrad1= t1-fgrad1*10;

       
       t2=rxbuf[2];
       t2=t2 << 8;
       t2=t2+rxbuf[3];
       
       fgrad2= t2/10;
       pgrad2= t2-fgrad2*10;

       
       
       vcc=rxbuf[4];
       vcc=vcc << 8;
       vcc=vcc+rxbuf[5];
       
       Vdd=Vcc/1000;
       Vpoint=Vcc-Vdd*1000;

       
       
       printf(" t1=%u .%uC t2=%u.%uC Vcc=%u.%LuV n=%u \n\r",fgrad1,pgrad1,fgrad2,pgrad2,vdd,vpoint,k);
     //  printf("\n\r");
       
     } //else printf("frame error \n\r");
    
       fl1=0;
   // fl=0;
   // CREN=0;
    CREN=1;
     
  } 
 }
}
