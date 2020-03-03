#include "Config.h"
#include "Modbus.h"
#include "LVDB_ADC.h"

unsigned int RegisterAddr  = 0;
unsigned int RegisterValue = 0;
unsigned int FirmVer = 0;
unsigned int SPIsclk_Fp = 4;

unsigned int LVDBxCHxV[LVDBxChNum];

void LVDBxGetState(void)
{
	// LVDB1 TurnOn states
	holding_reg_write(0,TurnOn_1_1_state);
	holding_reg_write(1,TurnOn_1_2_state);
	holding_reg_write(2,TurnOn_1_3_state);
	holding_reg_write(3,TurnOn_1_4_state);
	holding_reg_write(4,TurnOn_1_5_state);
	holding_reg_write(5,TurnOn_1_6_state);
	holding_reg_write(6,TurnOn_1_7_state);
	holding_reg_write(7,TurnOn_1_8_state);
	holding_reg_write(8,TurnOn_1_9_state);
	// LVDB2 TurnOn states
	holding_reg_write(9, TurnOn_2_1_state);
	holding_reg_write(10,TurnOn_2_2_state);
	holding_reg_write(11,TurnOn_2_3_state);
	holding_reg_write(12,TurnOn_2_4_state);
	holding_reg_write(13,TurnOn_2_5_state);
	holding_reg_write(14,TurnOn_2_6_state);
	holding_reg_write(15,TurnOn_2_7_state);
	holding_reg_write(16,TurnOn_2_8_state);
	holding_reg_write(17,TurnOn_2_9_state);
}
void LVDBxSupplyLogic(unsigned int RegAddr, unsigned int RegVal)
{
	switch(RegAddr)
	 {     
			 // LVDB1 TurnOn control
			 case 20:	(RegVal == 1) ? nTurnOn_1_1_LOW : nTurnOn_1_1_HIGH;	break;                  
			 case 21:	(RegVal == 1) ? nTurnOn_1_2_LOW : nTurnOn_1_2_HIGH;	break;
			 case 22:	(RegVal == 1) ? nTurnOn_1_3_LOW : nTurnOn_1_3_HIGH;	break;
			 case 23:	(RegVal == 1) ? nTurnOn_1_4_LOW : nTurnOn_1_4_HIGH;	break;
			 case 24:	(RegVal == 1) ? nTurnOn_1_5_LOW : nTurnOn_1_5_HIGH;	break;
			 case 25:	(RegVal == 1) ? nTurnOn_1_6_LOW : nTurnOn_1_6_HIGH;	break;
			 case 26:	(RegVal == 1) ? nTurnOn_1_7_LOW : nTurnOn_1_7_HIGH;	break;
			 case 27:	(RegVal == 1) ? nTurnOn_1_8_LOW : nTurnOn_1_8_HIGH;	break;
			 case 28:	(RegVal == 1) ? nTurnOn_1_9_LOW : nTurnOn_1_9_HIGH;	break;
			 // LVDB2 TurnOn control 
			 case 29:	(RegVal == 1) ? nTurnOn_2_1_LOW : nTurnOn_2_1_HIGH;	break;                  
			 case 30:	(RegVal == 1) ? nTurnOn_2_2_LOW : nTurnOn_2_2_HIGH;	break;
			 case 31:	(RegVal == 1) ? nTurnOn_2_3_LOW : nTurnOn_2_3_HIGH;	break;
			 case 32:	(RegVal == 1) ? nTurnOn_2_4_LOW : nTurnOn_2_4_HIGH;	break;
			 case 33:	(RegVal == 1) ? nTurnOn_2_5_LOW : nTurnOn_2_5_HIGH;	break;
			 case 34:	(RegVal == 1) ? nTurnOn_2_6_LOW : nTurnOn_2_6_HIGH;	break;
			 case 35:	(RegVal == 1) ? nTurnOn_2_7_LOW : nTurnOn_2_7_HIGH;	break;
			 case 36:	(RegVal == 1) ? nTurnOn_2_8_LOW : nTurnOn_2_8_HIGH;	break;
			 case 37:	(RegVal == 1) ? nTurnOn_2_9_LOW : nTurnOn_2_9_HIGH;	break;
			 //=====
			 default: break;
	 } 
}
	

void LVDBxReadOut(void)
{
	 // LVDB1 readout
	 LVDBxChxMeasV(LVDB_1, &LVDBxCHxV);
	
	 for(uint16_t i = 0; i < LVDBxChNum; i++)
		input_reg_write(i, LVDBxCHxV[i]);

	 input_reg_write(56,0xffff);	// LVDBx delimeter
	
	 // LVDB2 readout
	 LVDBxChxMeasV(LVDB_2, &LVDBxCHxV);
	
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
     switch(modbus_get_poll())
     {
//////////////////////////// ЧТЕНИЕ HOLDING ////////////////////////// 
         case MODBUS_RHR_CMD:
             
            MODBUS_LED_ON;										// LED toggle
				 
						LVDBxGetState();									// LVDBx read
					  holding_reg_write(38,SPIsclk_Fp); // SPI sclk parameter
					  holding_reg_write(39,FirmVer); 		// dev firm version
				 
            modbus_rhr_answer(); 							// modbus rhr cmd answer
            MODBUS_LED_OFF; 	  						  // LED toggle
           
         break;
//////////////////////////// ЗАПИСЬ HOLDING ////////////////////////// 
         case MODBUS_WSR_CMD:  	 // запись holding регистров
					  MODBUS_LED_ON;			 // LED toggle
						modbus_wsr_answer(); // ответ на запрос
					
						// заполнение переменных пользователя данными из Модбас регистров 
           
						RegisterAddr  = get_wr_reg_addr();  // get address
						RegisterValue = get_wr_reg_val();   // get the new value
           
						LVDBxSupplyLogic(RegisterAddr, RegisterValue);
				 
				 		switch(RegisterAddr)
						{ 
							case 38: 
								SPIsclk_Fp = RegisterValue;
								ADCxSetRdFreq(SPIsclk_Fp);
							break;
							//=====
							default: break;
					  }
						MODBUS_LED_OFF;			// LED toggle
	
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
	FirmVer = 11;								// dev firmvare version
	
  InitClock();
	GPIO_Config();
	
	ModbusID = ReadModbusID();
	if(DEV_ID_MODE)
		set_modbus_id(ModbusID);
	else
		set_modbus_id(ModbusID+100);
	
	modbus_init();

	LVDB_init();
	__enable_irq();

while(1)
{	
  modbus_poll();
	
 } // while		
} // main
