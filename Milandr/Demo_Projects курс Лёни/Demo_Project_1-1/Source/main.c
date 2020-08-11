#include "main.h"

int main(void)
{
  LED_init();
  BTN_init();

  // MDR_PORTA->RXTX = 0x0000000f; 

  while(1)
  {
    MDR_PORTE->RXTX
  }
}

void LED_init(void)
{
  // вкл. тактирования PORTA 
  *(unsigned int*)(0x40020000 + 0x1C) = 1 << 21; // 0x200000
  // MDR_RST_CLK->PER_CLOCK |= 1 << RST_CLK_PCLK_PORTA_Pos;
    MDR_RST_CLK->PER_CLOCK |= RST_CLK_PCLK_PORTA_Msk;


  // конфигурация линий PA0...PA7 
  MDR_PORTA->OE     |= 0x000000ff;    // навправление порта - выход
  MDR_PORTA->FUNC   &= 0xffff0000;    // функция - порт
  MDR_PORTA->ANALOG |= 0x000000ff;    // порты - цифровые, АЦП отключен
  MDR_PORTA->PULL   &= 0xff00ff00;    // внутренние подтягивающие - резисторы выключены 
  MDR_PORTA->PD     &= 0xff00ff00;    // управление - драйвер
  MDR_PORTA->PWR    =  0xffff0000;    // сброс битов регистра
  MDR_PORTA->PWR    |= 0x00005555;    // крутизна фронта импульса - низкая
  MDR_PORTA->GFEN   &= 0xffffff00;    // фильтр коротких импульсов - откл.
}

void BTN_init(void)
{
  // вкл. тактирования PORTE 
  MDR_RST_CLK->PER_CLOCK |= RST_CLK_PCLK_PORTE_Msk;

  // конфигурация линий PE7
  MDR_PORTA->ANALOG |= 1 << 7;    // порт E - цифровой вход

}