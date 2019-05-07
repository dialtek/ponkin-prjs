#include "xc.h"
#include "fuses.h"
#include "main.h"
#include <libpic30.h>
#include "dialtek_modbus.h" 
/*=========================================================================== */    
FirmwareInfo FirmInfo;

unsigned int wr_reg_addr = 0;       // modbus write reg addr
unsigned int RegisterValue = 0;     // modbus write reg velue

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
  
AD1PCFGH = 0xffff; 
AD1PCFGL = 0xffff; 
//настраиваем порт б на вход/выход 
TRISBbits.TRISB0 = 1;//par5 
TRISBbits.TRISB1 = 1;//par4 
TRISBbits.TRISB2 = 1;//par3 
TRISBbits.TRISB3 = 1;//par2 
TRISBbits.TRISB4 = 1;//par1 
TRISBbits.TRISB5 = 1;//par0 

TRISCbits.TRISC2 = 0;// spi_cs 

TRISDbits.TRISD8 = 1;// int1 
TRISDbits.TRISD9 = 1;// int2 

TRISFbits.TRISF2 = 1; // uatr_rx 
TRISFbits.TRISF3 = 0; // uatr_tx 
TRISFbits.TRISF6 = 0; // uatr_tx_en 

TRISGbits.TRISG6 = 0; //spi_clk 
TRISGbits.TRISG7 = 1;//spi_miso 
TRISGbits.TRISG8 = 0;//spi_mosi
  
}

/*================================ MODBUS =================================== */ 
// modbus SM 
void modbus_poll(void)
{    
     switch( modbus_get_poll() )
     {
//////////////////////////// ЧТЕНИЕ HOLDING ////////////////////////// 
          case MODBUS_RHR_CMD:

           // заполнение Модбас регистров переменными пользователя
           // holding_reg_write(register_address,U16 data)
            
           //MODBUS_LED = ON; 
           
           holding_reg_write(0,12345); 
           
           modbus_rhr_answer(); // ответ на запрос
           //__delay_ms(1);
           //MODBUS_LED = OFF;
          break;
//////////////////////////// ЗАПИСЬ HOLDING ////////////////////////// 
          case MODBUS_WSR_CMD:
           modbus_wsr_answer();  // ответ на запрос 
           
          // заполнение переменных пользователя данными из Модбас регистров 
          // holding_reg_read(register_address,U16 data pointer)
           
           //MODBUS_LED = ON;  
           wr_reg_addr = get_wr_reg_addr();
           // get the new value
           holding_reg_read(wr_reg_addr,&RegisterValue);   
                   
           switch(wr_reg_addr)
           {
               case 0: // X axis motor speed 
                   //holding_reg_read(0,&axis_motor[X].speed);
               break;
               //====              
               default: break;
           }
           
           //eeprom_wr_regs(HOLD_REGS);
           //eeprom_wr_regs(INPUT_REGS);
           
           //MODBUS_LED = OFF;
          break;
//////////////////////////// ЧТЕНИЕ INPUT ////////////////////////////
          case MODBUS_RIR_CMD:  // чтение input регистров
          // заполнение переменных пользователя данными из Модбас регистров 
          // input_reg_write(register_address,U16 data)
              
           //MODBUS_LED = ON; 
           
           input_reg_write(0,0);
           input_reg_write(1,FirmInfo.ver);
           input_reg_write(2,FirmInfo.developer);
      
           modbus_rir_answer();     // ответ на запрос
           //delay_ms(1);
           //MODBUS_LED = OFF;
           
          break;
     }
}

/*================================= MAIN ==================================== */ 
int main()
{    
    FirmInfo.ver = 10;               // device firmware version
    FirmInfo.developer = LETKIN;     // device firmware developer
   
    OSC_init();
    GPIO_init ();
    TX_DIS;         // release RS485 line !!!
    
    //eeprom_rd_regs_H();  // reading sets from SPI EEPROM
    //eeprom_rd_regs_I();  // restire modbus regs
    
    //RestoreDevCfg();      // restore outputs states
   
    modbus_init();
        
 while(1)
 {
    modbus_poll();    
 } 
}