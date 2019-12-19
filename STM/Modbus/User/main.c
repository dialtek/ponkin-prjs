#include "Config.h"
#include "Modbus.h"
#include "LVDB_ADC.h"

unsigned int wr_reg_addr = 0;
unsigned int RegisterValue = 0;

unsigned int LVDBxCHxV[LVDBxChNum];

void LVDBxReadOut(void)
{
		 // LVDB1 readout
	 LVDBxChxMeasV(1,&LVDBxCHxV);
	 for(uint16_t i = 0; i < LVDBxChNum; i++)
		input_reg_write(i, LVDBxCHxV[i]);
 
	 input_reg_write(56,0xffff); // delimeter
 
	 // LVDB2 readout
	 LVDBxChxMeasV(2,&LVDBxCHxV);
	 for(uint16_t i = 0; i < LVDBxChNum; i++)
		input_reg_write(i+57, LVDBxCHxV[i]);

}

unsigned char ReadModbusID (void)
{
	// pins pulled UP
	
	unsigned char ID = (unsigned char) ((GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11) << 3) |				
																			(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_10) << 2) |
																			(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_9)  << 1) |
																			(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_8)));

	ID = ~ID;			// invert number		
	ID &= 0x000f; // clear msb nibble 
	
	return ID;
}
	


void modbus_poll(void)
{
// если запрос был в переменной modbus_request сохранен его код 
     switch(modbus_get_poll())
     {
//////////////////////////// ЧТЕНИЕ HOLDING ////////////////////////// 
         case MODBUS_RHR_CMD:
             
           MODBUS_LED_ON;

           modbus_rhr_answer(); // modbus rhr cmd answer

           MODBUS_LED_OFF; // LED toggle
           
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
											nTurnOn_1_1_LOW;
										else 
											nTurnOn_1_1_HIGH;
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
          
					MODBUS_LED_ON;					
					
					LVDBxReadOut();
					
					MODBUS_LED_OFF; // LED toggle
         
           modbus_rir_answer(); // ответ на запрос
          break;
          
       } // switch
}

int main()
{ 
  unsigned char ModbusID = 0;
	
  InitClock();
	GPIO_Config();
	
	ModbusID = ReadModbusID();
	if(DEV_ID_MODE)
		set_modbus_id(ModbusID);
	else
		set_modbus_id(++ModbusID);
	
	modbus_init();

	LVDB_init();
	//TIM_Config();
	__enable_irq();
	
	
while(1)
{	
  modbus_poll();
	
 } // while		
} // main
