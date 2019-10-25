#include "MDR32Fx.h"                                       	//Device Header

#define F_CPU 8000000 																			// указание тактовой частоты МК
//#include "milkites_delay.h"  																// подключение библиотеки задержек

// Нужно определить эту константу, чтобы не отваливался JTAG на PORTB
#define USE_JTAG_A

// Нужно определить эту константу, чтобы не отваливался JTAG на PORTD
//#define USE_JTAG_B


// Подключение SPL
#include <MDR32F9Qx_port.h>
#include <MDR32F9Qx_rst_clk.h>


int main()
{
	//Настройка
	MDR_RST_CLK->PER_CLOCK = 0xffffffff;  // вкл. тактирование всей периферии
	
	// ---------PORTA (для демонстрации) ---
	
	// Инициализация структуры для настройки порта
	PORT_InitTypeDef PORTA_config_struct;
	PORT_StructInit(&PORTA_config_struct);
	
	// Настройка порта
	PORTA_config_struct.PORT_OE = PORT_OE_OUT;
	PORTA_config_struct.PORT_MODE = PORT_MODE_DIGITAL;
	PORTA_config_struct.PORT_SPEED = PORT_SPEED_MAXFAST;
	PORT_Init(MDR_PORTA, &PORTA_config_struct);
	
	PORT_SetBits(MDR_PORTA, PORT_Pin_All);
	
	
	
	
	// ---------PORTB-------------
	
	// Инициализация структуры для настройки порта
	PORT_InitTypeDef PORTB_config_struct;
	PORT_StructInit(&PORTB_config_struct);
	
	// Настройка порта
	PORTB_config_struct.PORT_Pin = PORT_Pin_All & (~JTAG_PINS(MDR_PORTB));  // Чтобы не отваливался JTAG,
	                             //исключаем из инициализации JTAG-овские пины
	PORTB_config_struct.PORT_OE = PORT_OE_OUT;
	PORTB_config_struct.PORT_MODE = PORT_MODE_DIGITAL;
	PORTB_config_struct.PORT_SPEED = PORT_SPEED_MAXFAST;
	PORT_Init(MDR_PORTB, &PORTB_config_struct);
	
	// Работоспособность разных способов записи в порт B:
	
	// Здесь поведение JTAG-а соответствует ожидаемому:
	//MDR_PORTB->RXTX = 0xff & (~JTAG_PINS(MDR_PORTB));  // JTAG будет работать дальше
	  MDR_PORTB->RXTX = 0 << 10 & (~JTAG_PINS(MDR_PORTB));  // JTAG будет работать дальше
	//MDR_PORTB->RXTX = 1 << 7;                          // JTAG будет работать дальше
	//MDR_PORTB->RXTX = 0xff;                            // JTAG отвалится
	
	
	// А ВОТ ДАЛЬШЕ САМОЕ ИНТЕРЕСНОЕ:
	
	//PORT_Write(MDR_PORTB, 0xff & (~JTAG_PINS(MDR_PORTB)));  // JTAG будет работать дальше
	//PORT_Write(MDR_PORTB, 0xff);                            // JTAG отвалится !!! Хотя в функции PORT_Write есть защита от записи в пины JTAG
	
	//PORT_WriteBit(MDR_PORTB, PORT_Pin_All, 1);                           // JTAG отвалится !!! Хотя в самой функции защита есть от записи в пины JTAG
	//PORT_WriteBit(MDR_PORTB, PORT_Pin_All & (~JTAG_PINS(MDR_PORTB)), 1);   // JTAG отвалится !!! И даже маска в аргументе не поможет !!!!!!!!!!!
	//PORT_WriteBit(MDR_PORTB, PORT_Pin_7, 1);                             // JTAG отвалится !!!
	
	//PORT_SetBits(MDR_PORTB, PORT_Pin_All);                                 // JTAG отвалится !!! Хотя в самой функции защита есть от записи в пины JTAG
	//PORT_SetBits(MDR_PORTB, PORT_Pin_All & (~JTAG_PINS(MDR_PORTB)) );      // JTAG отвалится !!! И тут тоже маска в аргументе не помогает !!!!!!!!!!!
	//PORT_SetBits(MDR_PORTB, PORT_Pin_7 );                                // JTAG отвалится !!!
}
