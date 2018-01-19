#include <main.h>
#include <usb_cdc.h>
//#include <pic_18usb.h>
#use delay(clock=48000000)
#define USB_CON_SENSE_PIN PIN_RA3

static void UsbWrRd(void){
char ch;
/*
int16 ADC_value;
set_adc_channel(11);
delay_us(10);
ADC_value = read_adc();
usb_cdc_putc(ADC_value);
*/

   //if(usb_cdc_kbhit())//есть ли что то в буфере?
   //{
   //ch = usb_cdc_getc(); 
   usb_cdc_putc("1\n");           //sends a character
   
    usb_cdc_putc("2\n");
   ;
   usb_cdc_putc("3\n");
   
   usb_cdc_putc("4\n");
   
   //usb_cdc_putc("\n\r");
  // }
   
}

Void Main (void){

      setup_adc( ADC_CLOCK_INTERNAL);
      setup_adc(ADC_CLOCK_DIV_64);
      setup_adc_ports(sAN11|VSS_VREF);
       
   

   //OSCCON = 0x66;
   //TRISB = 0b00100000;
   TRISB = 0b00000000;
   //TRISA = 0b0000000;

   usb_init_cs();
   usb_attach();
   
   //enable_interrupts(INT_EXT);
   
   delay_ms(1000);
   //usb_cdc_putc("USB by PIC18F14K50 working!!!\n\r"); 
   ///setup_timer_3(T3_DISABLED|T3_DIV_BY_1);
   setup_comparator(NC_NC_NC_NC);// This device COMP currently not supported by the PICWizard
   
   /*
   enable_interrupts(GLOBAL);
   enable_interrupts(INT_TIMER0);
   setup_timer_0 (RTCC_INTERNAL|RTCC_EXT_L_TO_H);
   set_timer0(35000);
   #int_timer0
   
   
void timer0interrupt(){

   enable_interrupts(TIMER0);

   Rb4=0;
   delay_us(10);
   Rb4=1;
   delay_us(10);
   clear_interrupt(TIMER0);

}
     */ 
 
while(true){ 
  
   usb_task();    //периодическое подключение устр. к шине USB
 
  if(usb_enumerated())     // ПК обнаружил железо?
  {
   delay_ms(300);
   UsbWrRd();
   
  }
 
  /*
   Rb6=0;
   delay_us(10);
   Rb6=1;
   delay_us(10);
   */
}
}

