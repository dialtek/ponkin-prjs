#include "h/link.h"
#include "h/Fuse.h"

/*=============================== VARIABLES ================================= */
// GLOBAL variables

unsigned int wr_reg_addr = 0;            // modbus write reg addr
unsigned int RegisterValue = 0;          // modbus write reg velue

unsigned int V_Mx_Ch[5] = {0};
unsigned int I_Mx_Ch[5] = {0};
unsigned int I_total = 0, zero_lvl = 0;

#define MEAS_CH_CNT 5
#define V_to_I_coef 5 // 1 mV = 5 nA
/*============================== FUNCTIONS ================================== */

void GPIO_init()
{
        // Port A
        TRISAbits.TRISA0 = 1; // ADC CH+
        TRISAbits.TRISA1 = 1; // ADC CH-
        // Port B
        TRISBbits.TRISB4 = 0; // LED
        // Port C
        TRISCbits.TRISC0 = 0; // MX SEL0
        TRISCbits.TRISC1 = 0; // MX SEL1
        TRISCbits.TRISC2 = 0; // MX SEL2
        TRISCbits.TRISC3 = 0; // MX EN
        
        TRISCbits.TRISC6 = 0; // Pin_17 TX_UART
        TRISCbits.TRISC7 = 1; // Pin_18 RX_UART
  
        ANCON0bits.ANSEL0 = 1; // Вывод 0 канала АЦП сконфигурирован как аналоговый вход
        ANCON0bits.ANSEL1 = 1; // Вывод 1 канала АЦП сконфигурирован как аналоговый вход      
    }   

void delay_ms(unsigned int ms)
{
    while(--ms)
        __delay_ms(1);
}

void Interrupt_init()
{
    RCONbits.IPEN = 0;          // 1 = Enable priority levels on interrupts;  Interrupt Priority Enable bit
    INTCONbits.GIEH = 1;        // Разрешение прерываний высокого уровня
    INTCONbits.GIEL = 1;        // Разрешение прерываний низкого уровня (отключено)

    PIR1bits.ADIF = 0;
    PIE1bits.ADIE = 0;
    PIE1bits.RC1IE = 1;         // разрешение UART recive

    //PIE1bits.TMR1IE = 1;        // разрешение по переполнению таймера 1
}

void interrupt ISR()
{

    // ------------------- 
    if (PIR1bits.RC1IF) // uart rx int
    {  
        modbus_get_byte(RCREG1);
    }
}

void MX_set_ch(unsigned char ch)
{
    MX_DIS;
    __delay_us(1);
    switch(ch)
    {
        case 0:
            LATCbits.LATC0 = 0;
            LATCbits.LATC1 = 0;
            LATCbits.LATC2 = 0;
        break;
        //=====================
        case 1:
            LATCbits.LATC0 = 1;
            LATCbits.LATC1 = 0;
            LATCbits.LATC2 = 0;
        break;
        //=====================
        case 2:
            LATCbits.LATC0 = 0;
            LATCbits.LATC1 = 1;
            LATCbits.LATC2 = 0;
        break;
        //=====================
        case 3:
            LATCbits.LATC0 = 1;
            LATCbits.LATC1 = 1;
            LATCbits.LATC2 = 0;
        break;
        //=====================
        case 4:
            LATCbits.LATC0 = 0;
            LATCbits.LATC1 = 0;
            LATCbits.LATC2 = 1;
        break;
        //=====================
        
        default:
            LATCbits.LATC0 = 0;
            LATCbits.LATC1 = 0;
            LATCbits.LATC2 = 0;
        //=====================
        
    }
    __delay_us(1);
    MX_EN;
}

/*================================ MODBUS =================================== */ 

void Meas_perform(void)
{
    I_total = 0;
    MX_DIS;
    __delay_us(50);
    
    zero_lvl = ADC_read_aver(10);
            
    for(unsigned char i = 0; i < MEAS_CH_CNT; i++)
    {
        MX_set_ch(i);

        V_Mx_Ch[i] = ADC_read_aver(10) - zero_lvl; 
          
        if( V_Mx_Ch[i] & (1<<15) )
          I_Mx_Ch[i] = (~V_Mx_Ch[i]) / V_to_I_coef;  // -V to I convertion
        else 
          I_Mx_Ch[i] =  V_Mx_Ch[i]   / V_to_I_coef;  // +V to I convertion 
        
        I_total += I_Mx_Ch[i];
    }
}

void modbus_poll(void)
{    
     // проверка, был ли Модбас запрос

     switch( modbus_get_poll() )
     {
         case MODBUS_RHR_CMD:   // чтение holding регистров
//////////////////////////// ЧТЕНИЕ HOLDING //////////////////////////             
          // заполнение Модбас регистров переменными пользователя
          // holding_reg_write(register_address,U16 data)
          LED_ON;

          //====================================  
          // REGISTER MAP
//          ADC_V = ADC_read_aver(100) - ADC_ZERO_LVL;
//          
//          if( ADC_V & (1<<15) )
//            I_meas = (~ADC_V)/5;
//          else 
//            I_meas = ADC_V/5;  
          
          holding_reg_write(0, V_Mx_Ch[0]);   
          holding_reg_write(1, V_Mx_Ch[1]);  
          holding_reg_write(2, V_Mx_Ch[2]);  
          holding_reg_write(3, V_Mx_Ch[3]);  
          holding_reg_write(4, V_Mx_Ch[4]);  
          
          holding_reg_write(5, I_Mx_Ch[0]);   
          holding_reg_write(6, I_Mx_Ch[1]);   
          holding_reg_write(7, I_Mx_Ch[2]);   
          holding_reg_write(8, I_Mx_Ch[3]);   
          holding_reg_write(9, I_Mx_Ch[4]);   
          holding_reg_write(10, I_total);   
          holding_reg_write(11, zero_lvl);

                  
          //====================================

          modbus_rhr_answer(); // ответ на запрос 
          
          delay_ms(10);
          LED_OFF;
        
          break;
//////////////////////////// ЗАПИСЬ HOLDING ////////////////////////// 
          case MODBUS_WSR_CMD:  // запись holding регистров
          modbus_wsr_answer();  // ответ на запрос
          
          // заполнение переменных пользователя данными из Модбас регистров 
          // holding_reg_read(register_address,U16 data pointer)
                      
           LED_ON;  
           
           wr_reg_addr = get_wr_reg_addr();  // get the addr
           RegisterValue = get_wr_reg_val(); // get the new value
    
           switch(wr_reg_addr)
           {
               case 3: 
                   MX_set_ch((unsigned char)RegisterValue);
               break;
               //==== 
               default: break;
           }
           
            //eeprom_wr_regs(HOLD_REGS);
            //eeprom_wr_regs(INPUT_REGS);
           
           LED_OFF;
          break;
//////////////////////////// ЧТЕНИЕ INPUT ////////////////////////////
          case MODBUS_RIR_CMD:  // чтение input регистров
          // заполнение переменных пользователя данными из Модбас регистров 
          // input_reg_write(register_address,U16 data)
             
           
           //input_reg_write(0,ImunoFirmware.DosingSys);
           //input_reg_write(1,FirmInfo.ver);
           //input_reg_write(2,FirmInfo.developer);
           
           modbus_rir_answer(); // ответ на запрос
           
          break;
     }
}

/*================================= MAIN ==================================== */ 

void main() 
{
   GPIO_init();
   ADC_Init();
   
   modbus_init();
   set_modbus_id(10);
   
   Interrupt_init();

   LED_ON;        
   
   while(1)
   {
    Meas_perform();
    modbus_poll();
    
   } // while
}    //main
