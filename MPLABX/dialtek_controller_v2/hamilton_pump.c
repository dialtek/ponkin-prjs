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

unsigned int chars2number(unsigned char data_size, unsigned char begin_index)
{
      unsigned int converted_num = 0;
      
      switch(data_size) // 1-9, 10-99, 100 -- 999, 1000+ cases
      {
          case 1:  
              converted_num = char2num(input_register[begin_index]);
          break;
          //----
          case 2:  
              converted_num = char2num(input_register[begin_index])  * 10 +
                         char2num(input_register[begin_index+1]);
          break;
          //----
          case 3:  
              converted_num = char2num(input_register[begin_index])  * 100 +
                         char2num(input_register[begin_index+1])* 10  +
                         char2num(input_register[begin_index+2]);
          break;
          //----
          case 4:  
              converted_num = char2num(input_register[begin_index])  * 1000 +
                         char2num(input_register[begin_index+1])* 100  +
                         char2num(input_register[begin_index+2])* 10   +
                         char2num(input_register[begin_index+3]);
          //----
          default: break;
        }
}

void answer_refresh(void)
{
    // clear input registers 10-30 for the new cmd and answer
    
    uart2_rx_ptr = 0;
    for(char i = 0; i < 30; i++)
        input_register[10+i] = 0; // 10+ - send + return bytes
}

unsigned int search_answer(unsigned char reg_index, unsigned char begin_index, unsigned char end_index)
{
    unsigned int sorted_anser = ERROR_CODE; // 19? 17 26
    
    unsigned char data_size;
    
    if(input_register[reg_index] == 0x0060) // '`'  
    {
      // get begin and and sychro bytes indexes: '`' and {0D}{0A}  
      // => /0`1400{03}{0D}{0A}
      for(unsigned char i = begin_index; i <= end_index; i++) // answer is input_register 17 - 26
      {
          if(input_register[i] == '`') 
              begin_index = i;
          if(input_register[i] == 0x000D && input_register[i+1] == 0x000A ) 
              end_index = i;
      }
      begin_index++; // moving ptr to next byte => '`',  0`1200{03}{0D}{0A}
      end_index--;   // moving ptr to next byte => end of data, 0`1200{03}{0D}{0A}
      
      data_size = end_index - begin_index; // get data char count
      // convert ans chars to number 
      sorted_anser = chars2number(data_size, begin_index);        
    }  
    else sorted_anser = ERROR_CODE; // no response - error code)
    
    return sorted_anser;
}

void init_protocol(unsigned char pump_id)
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

void init_valve(unsigned char pump_id)
{
  answer_refresh(); // clear input registers 80-100 for the new cmd and answer
            
  PUMP_TX_EN; 
  uart2_send_text("/1h20000R"); // init valve  (вентиль)
  uart2_CR_LF_send();
  PUMP_TX_DIS;
  delay_ms(950);
}

void init_syringe(unsigned char pump_id)
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

unsigned int get_syr_pos (unsigned char pump_id)
{
  // get current syringe position 
    
  unsigned int position; 

  answer_refresh(); 
  
  PUMP_TX_EN; 
  uart2_send_text("/");
  uart2_send_byte(num2char(pump_id));
  uart2_send_text("?R"); // get syringe position cmd
  uart2_CR_LF_send();
  PUMP_TX_DIS;
  delay_ms(20); // delay to read all answer bytes
  
  position = search_answer(18, 16, 26); 
  // answer: reg - 18 = '`', numeric value of answer - 16 - 26 regs

  return position;

}

void set_syr_pos(unsigned char pump_id, unsigned int pos)
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

unsigned int get_syr_vel(unsigned char pump_id)            // get syringe velocity
{
    // get syringe velocity => /1?2R
    
    unsigned int velocity;
    
    answer_refresh(); 
    
    PUMP_TX_EN; 
    uart2_send_text("/");
    uart2_send_byte(num2char(pump_id));
    uart2_send_text("?2R"); // get current velocity cmd
    uart2_CR_LF_send();
    PUMP_TX_DIS;
    delay_ms(20); // delay to read all answer bytes
    
    velocity = search_answer(19, 17, 26); 
    // answer: reg - 19 = '`', numeric value of answer - 17 - 26 regs

    return velocity;
}

void set_syr_vel(unsigned char pump_id, unsigned int vel)  // set syringe velocity
{
    // set syringe velociry, 0 - 40
    // /1S1000R
    if (vel > 40) return;
    
    answer_refresh(); // clear input registers 80-100 for the new cmd and answer
    
    // get chars from number
    unsigned int first_num  =  vel/10;
    unsigned int sec_num    = (vel - first_num * 10);

    PUMP_TX_EN;
    uart2_send_text("/");
    uart2_send_byte(num2char(pump_id));
    uart2_send_text("S");
    uart2_send_byte(num2char(first_num));
    uart2_send_byte(num2char(sec_num));
    uart2_send_text("R");
    uart2_CR_LF_send();
    PUMP_TX_DIS;
}

unsigned int get_valve_angle (unsigned char pump_id)       // get current valve angle
{
    //  get current valve angl => /1?25000R
    
    unsigned int angle; 

    answer_refresh(); 
    
    PUMP_TX_EN; 
    uart2_send_text("/");
    uart2_send_byte(num2char(pump_id));
    uart2_send_text("?25000R"); // get current velocity cmd
    uart2_CR_LF_send();
    PUMP_TX_DIS;
    delay_ms(20); // delay to read all answer bytes
    
    angle = search_answer(23, 23, 28); 
  
    return angle;
}

void set_valve_angle(unsigned char pump_id, unsigned int angle, unsigned int dir)  // set valve angle
{
    // set valve angle
    // /1h27{...}R clockwise, /1h28{...}R couner clockwise
    if (angle > 345) return;
    
    answer_refresh(); // clear input registers 80-100 for the new cmd and answer
    
    // get chars from number
    unsigned int first_num  =  angle/100;
    unsigned int sec_num    = (angle - first_num * 100)/10;
    unsigned int third_num  = (angle - first_num * 100 - sec_num*10);
    // min = (a < b) ? a : b;
    
    PUMP_TX_EN;
    uart2_send_text("/");
    uart2_send_byte(num2char(pump_id));
    uart2_send_text("h");
    uart2_send_text((dir == 1) ? "28" : "27"); // 0 - clockwise, 1 - counter clockwise
    uart2_send_byte(num2char(first_num));
    uart2_send_byte(num2char(sec_num));
     uart2_send_byte(num2char(third_num));
    uart2_send_text("R");
    uart2_CR_LF_send();
    PUMP_TX_DIS;
}