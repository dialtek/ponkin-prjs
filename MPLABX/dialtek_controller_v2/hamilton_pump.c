/* 
 * File:   hamilton_pump.c
 * Author: D_LHEP_DESKTOP
 *
 * Created on 29 но€бр€ 2018 г., 10:20
 */
#include "hamilton_pump.h"
/*=========================================================================== */ 
 extern unsigned char uart2_rx_ptr; 
 extern unsigned char answer_ready; 
 extern unsigned int input_register[];
 
// HAMILTON PUMP   
unsigned char char2num (unsigned char ch)
{ // converts char symbol into number
  return ch - 0x30;
}

unsigned char num2char (unsigned char ch)
{ // converts number into char symbol
  return ch + 0x30;
}

void answer_refresh(void)
{
    // clear input registers 10-30 for the new cmd and answer
    
    uart2_rx_ptr = 0;
    for(char i = 0; i < 30; i++)
        input_register[10+i] = 0; // 10+ - send + return bytes
}

void pump_init_protocol(unsigned char pump_id)
{
  // /1h30001R
    
  answer_refresh(); // clear input registers 80-100 for the new cmd and answer
            
  PUMP_TX_EN; 
  uart2_send_text("/");
  uart2_send_text("1");//uart2_send_byte(0x31);//num2char(pump_id));
  uart2_send_text("h30001R"); // init protocol
  uart2_CR_LF_send();
  PUMP_TX_DIS;
  delay_ms(100);
}

void pump_init_valve(unsigned char pump_id)
{
  answer_refresh(); // clear input registers 80-100 for the new cmd and answer
            
  PUMP_TX_EN; 
  uart2_send_text("/1h20000R"); // init valve  (вентиль)
  uart2_CR_LF_send();
  PUMP_TX_DIS;
  delay_ms(950);
}

void pump_init_syringe(unsigned char pump_id)
{ 
  // /1h10000R
  answer_refresh(); // clear input registers 80-100 for the new cmd and answer
    
  PUMP_TX_EN; 
  uart2_send_text("/");
  uart2_send_byte(num2char(pump_id));
  uart2_send_text("h10000R"); // init syringe (шприц)
  uart2_CR_LF_send();
  PUMP_TX_DIS;
  delay_ms(950);
}

unsigned int pump_get_pos (unsigned char pump_id)
{
 // get current syringe position
    
  unsigned int cnt = 0;
  unsigned int position = 65535; 
  
  answer_refresh(); 
  
  PUMP_TX_EN; 
  uart2_send_text("/");
  uart2_send_byte(num2char(pump_id));
  uart2_send_text("?R"); // get syringe position cmd
  uart2_CR_LF_send();
  PUMP_TX_DIS;
  
  while(input_register[18] != 0x0060) // '`' 
  {
      cnt++;
      if(cnt > 50000) break;
  }
  
  //if(input_register[18] == 0x0060) //&& input_register[24] == 0x000D) // '`' and  
  //{
  
    position = input_register[10] ;// * 1000 +   
//               char2num(input_register[20]) * 100 +
//               char2num(input_register[21]) * 10  +
//               char2num(input_register[22]);
 // }
    
  //else position = ERROR_CODE; // no response - error code)
  
  return position;

}

void pump_set_pos(unsigned char pump_id, unsigned int pos)
{
    // set syringe position 0 - 3000 (full)
    // /1A1000R
    if (pos > 3000) return;
    
    answer_refresh(); // clear input registers 80-100 for the new cmd and answer
    
    // get chars from number
    unsigned int first_num  = pos/1000;
    unsigned int sec_num    = (pos - first_num * 1000)/100;
    unsigned int third_num  = (pos - first_num * 1000- sec_num*100)/10;
    unsigned int fourth_num = (pos - first_num * 1000 - sec_num*100 - third_num*10);
    
    PUMP_TX_EN;
    uart2_send_text("/");
    uart2_send_byte(num2char(pump_id));
    uart2_send_text("A");
    uart2_send_byte(num2char(first_num));
    uart2_send_byte(num2char(sec_num));
    uart2_send_byte(num2char(third_num));
    uart2_send_byte(num2char(fourth_num));
    uart2_send_text("R");
    uart2_CR_LF_send();
    PUMP_TX_DIS;
}