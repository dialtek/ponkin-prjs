#include "Config.h"
#include "Modbus.h"
#include "LVDB_ADC.h"

unsigned int wr_reg_addr = 0;
unsigned int RegisterValue = 0;

/* 
UART пины: 
PA2 - TX
PA3 - RX

SPI pins
PA4 - CS
PA5 - SCK
PA6 - MISO
PA7 - MOSI

PE7		CS2
PE8 	CS3
PE9 	CS4
PE10 	CS5
PE11	CS6
PE12	CS7

PE13 	Modbus TX EN
PE14 	Modbus RX EN

PE15		n_Turn_ON_2
*/

	

void modbus_poll(void)
{
// если запрос был в переменной modbus_request сохранен его код 
     switch(modbus_get_poll())
     {
//////////////////////////// ЧТЕНИЕ HOLDING ////////////////////////// 
         case MODBUS_RHR_CMD:
             
           //Master_485_LED = ON;
          
           holding_reg_write(0,ADCxChxMeasV(ADC_1,Ch1));
				   holding_reg_write(1,ADCxChxMeasV(ADC_1,Ch2));
				   holding_reg_write(2,ADCxChxMeasV(ADC_2,Ch3));
				   holding_reg_write(3,ADCxChxMeasV(ADC_2,Ch4));
				   holding_reg_write(4,ADCxChxMeasV(ADC_3,Ch5));
				   holding_reg_write(5,ADCxChxMeasV(ADC_3,Ch6));
				   holding_reg_write(6,ADCxChxMeasV(ADC_1,Ch7));
				   holding_reg_write(7,ADCxChxMeasV(ADC_1,Ch8));
						 
           modbus_rhr_answer(); // modbus rhr cmd answer
				   //modbus_reset();

           //Master_485_LED = OFF; // LED toggle
           
         break;
//////////////////////////// ЗАПИСЬ HOLDING ////////////////////////// 
          case MODBUS_WSR_CMD:  // запись holding регистров
           modbus_wsr_answer(); // ответ на запрос
          // заполнение переменных пользователя данными из Модбас регистров 
           
           wr_reg_addr = get_wr_reg_addr();    // get address
           RegisterValue = get_wr_reg_val();   // get the new value
           
           switch(wr_reg_addr)
           {
               //=====                     
               case 10: 

                    if(RegisterValue == 1)
											nTurnOn2_HIGH;
										else 
											nTurnOn2_LOW;
               break;
							 //=====                     
               case 15: 
									ADCxSetRdFreq(RegisterValue);
               break;
               
               //=====
               default: break;
           } 
 
          break;
//////////////////////////// ЧТЕНИЕ INPUT ////////////////////////////
          case MODBUS_RIR_CMD:  // чтение input регистров
           
           input_reg_write(0,1234);
         
           modbus_rir_answer(); // ответ на запрос
          break;
          
       } // switch
}

int main(){ 

  InitClock();
	GPIO_Config();

	modbus_init();
	RX_EN;
	
	LVDB_init();
	//TIM_Config();
	__enable_irq();
	
while(1)
{	
  modbus_poll();
	
 } // while		
} // main
