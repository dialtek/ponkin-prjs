
#include "MDR32Fx.h"                    // Device header  
#include "stdint.h"
#include "milkites_I2C.h"

void I2C_Init(void){
	/*---------------Нстройка порта С для работы в режиме I2C--------------*/
    MDR_RST_CLK->PER_CLOCK |= 1 << 23;//разрешение тактирование порта C

    MDR_PORTC->FUNC   |= ((2 << 0*2) | (2 << 1*2)); //режим работы порта 
    MDR_PORTC->ANALOG |= ((1 << 0  ) | (1 << 1  )); //цифровой 
    MDR_PORTC->PWR    |= ((3 << 0*2) | (3 << 1*2)); //максимально быcтрый 

	/*-----------------Настройка тактирования блока I2C--------------------*/
    MDR_RST_CLK->PER_CLOCK |= 1 << 10; //разрешение тактирования I2C 

		MDR_I2C->PRL = 0x2; //младшая часть предделителя частоты 
	  MDR_I2C->PRH = 0x0; //старшая часть предделителя частоты
    MDR_I2C->CTR = ((1 << 7) //разрешение работы контроллера I2C 
                  | (0 << 6) //запрещение прерывания от I2C 
                  | (0 << 5)); //cкорость работы I2C = 400 кбит/с
}//void I2C_Init


void I2C_Start(void){
  
	/* S бит генерируется при записи 1 в бит START регистра CMD 
	    при установленных битах RD или WR*/
	MDR_I2C_TypeDef *I2C;
  I2C = MDR_I2C;
  I2C->CMD = (1<<7)|(1<<4); // START bit set and WR bit is set
} // I2C_Start

 void I2C_Send_Addr(uint8_t Byte){
	/*Необходимо записать адрес ведомого в регистр
	I2C_TXD и установить бит WR в регистре I2C_CMD.
	Контроллер осуществит передачу адреса в линию*/
	
	MDR_I2C_TypeDef *I2C;

  I2C = MDR_I2C;

  I2C->TXD = Byte;
  I2C->CMD = (1<<4); // Запись, WR bit is set
	while (((MDR_I2C->STA)&0x02)!= 0){} //wait for T.PROG 
} // I2C_Send_Addr

void I2C_Send_Byte(uint8_t Byte){
	/*Необходимо записать адрес ведомого в регистр
	I2C_TXD и установить бит WR в регистре I2C_CMD.
	Контроллер осуществит передачу адреса в линию*/
	
	MDR_I2C_TypeDef *I2C;

  I2C = MDR_I2C;

  I2C->TXD = Byte;
  I2C->CMD = (1<<4); // Запись, WR bit is set
	while (((MDR_I2C->STA)&0x02)!= 0){} //wait for T.PROG 
} // I2C_Send_Byte

uint8_t I2C_GetData(void){
  MDR_I2C_TypeDef *I2C;
  I2C = MDR_I2C;
	
	uint8_t data = 0;

	MDR_I2C->CMD = (1<<5);// Чтение, RD bit is set
  while (((MDR_I2C->STA)&0x02)!= 0){}//wait for T.PROG 
  data = MDR_I2C->RXD; 
	 
  return data;
} // I2C_GetData

 void I2C_NACK(void){
	 
	MDR_I2C->CMD = (1<<3); // NACK bit		
 }  // I2C_NACK

void I2C_Stop(void){
	 
	MDR_I2C->CMD = (1<<6); // STOP bit
 } // I2C_Stop