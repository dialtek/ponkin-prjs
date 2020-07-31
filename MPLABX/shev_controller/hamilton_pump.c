
/* 
 * File:   hamilton_pump.c
 * Author: D_LHEP_DESKTOP
 *
 * Created on 29 но€бр€ 2018 г., 10:20
 */
#include "hamilton_pump.h"
/*=========================================================================== */ 
 extern unsigned char uart2_rx_ptr; 
 extern unsigned char uart2_rx_buf[30];
 extern unsigned char answer_ready; 
 
 extern unsigned char bufx[30];
 
//void PSD4_struct_init(PSD4cmds cmd)
// {
//     cmd.init_protocol   = 10;
//     cmd.init_valve      = 11;
//     cmd.init_syringe    = 12;
//     
//     cmd.get_syr_pos     = 13;
//     cmd.get_syr_vel     = 14;
//     cmd.get_valve_angle = 15;
//
//     cmd.set_syr_pos     = 16;
//     cmd.set_syr_vel     = 17;
//     cmd.set_valve_angle = 18;
// }
 
// start/stop async delay timer
void TmOutTimer_state(unsigned int state)
{
    T4CONbits.TON = state;  // Start 32-bit Timer
}

 // T2/3 - async delay timer set
 void TmOutTimer_set(unsigned int ms)
 {
    unsigned long msCnts = (unsigned long)ms * 1000UL;  // user ms into us
    msCnts = (unsigned long)((float)msCnts / 4.26);      // us to timer ticks
    
    TMR5 = 0x00;            // Clear 32-bit Timer (msw)
    TMR4 = 0x00;            // Clear 32-bit Timer (lsw)
    
    PR5 = (unsigned int)(msCnts >> 16);        // Load 32-bit period value (msw)
    PR4 = (unsigned int)(msCnts & 0x0000ffff);  // Load 32-bit period value (lsw)
 }
 
// T2/3 - async delay timer
void TmOutTimer_init(void)
{
     // 1 timer tick = 60M/256 = 234 375 Hz = 4.26 us
     // 176 056 (2 AFB8) = 750 ms
      
    T5CONbits.TON = 0;      // Stop any 16-bit Timer5 operation
    T4CONbits.TON = 0;      // Stop any 16/32-bit Timer5 operation
    T4CONbits.T32 = 1;      // Enable 32-bit Timer mode
    T4CONbits.TCS = 0;      // Select internal instruction cycle clock
    T4CONbits.TGATE = 0;    // Disable Gated Timer mode
    T4CONbits.TCKPS = 0b11; // Select 1:256 Prescaler

    TMR5 = 0x00;            // Clear 32-bit Timer (msw)
    TMR4 = 0x00;            // Clear 32-bit Timer (lsw)
    
    // defaul - any values
    PR5 = 0x0000;      // Load 32-bit period value (msw)
    PR4 = 0x00ff;      // Load 32-bit period value (lsw)
    
    IPC7bits.T5IP = 4;      // Set Timer5 Interrupt Priority Level
    IFS1bits.T5IF = 0;      // Clear Timer5 Interrupt Flag
    
    IEC1bits.T5IE = 1;      // Enable Timer5 interrupt
}

// T4/5 async delay timer int
void _ISR_PSV _T5Interrupt(void)
{   
    //PSD4rxToutOvfl = 1;

    TMR4 = 0x00; // Clear 32-bit Timer (msw)
    TMR5 = 0x00; // Clear 32-bit Timer (lsw)

    IFS1bits.T5IF = 0;   // Clear Timer interrupt flag  
} 
 
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
              converted_num = char2num(uart2_rx_buf[begin_index]);
          break;
          //----
          case 2:  
              converted_num = char2num(uart2_rx_buf[begin_index])  * 10 +
                         char2num(uart2_rx_buf[begin_index+1]);
          break;
          //----
          case 3:  
              converted_num = char2num(uart2_rx_buf[begin_index])  * 100 +
                         char2num(uart2_rx_buf[begin_index+1])* 10  +
                         char2num(uart2_rx_buf[begin_index+2]);
          break;
          //----
          case 4:  
              converted_num = char2num(uart2_rx_buf[begin_index])  * 1000 +
                         char2num(uart2_rx_buf[begin_index+1])* 100  +
                         char2num(uart2_rx_buf[begin_index+2])* 10   +
                         char2num(uart2_rx_buf[begin_index+3]);
          //----
          default: break;
        }
}

void answer_refresh(void)
{
    // clear RxArray for the new cmd and answer
    
    uart2_rx_ptr = 0;
    for(char i = 0; i < 30; i++)
        uart2_rx_buf[i] = 0;
     //   input_register[10+i] = 0; // 10+ - send + return bytes
}

unsigned int check_cmd_answer(unsigned char index)
{
  // check the answer
   
  //for(int i = 0; i < 30; i++)
    //  bufx[i] = uart2_rx_buf[i];
    
  if(uart2_rx_buf[index] == '/' && uart2_rx_buf[index+2] == '@')
      return (unsigned int)1;
  else 
      return (unsigned int)0; 
}  

unsigned int search_answer(unsigned char reg_index, unsigned char begin_index, unsigned char end_index)
{
    unsigned int sorted_anser = ERROR_CODE; // 19? 17 26
    
    unsigned char data_size;

    if(uart2_rx_buf[reg_index] == 0x60) // '`'  
    {
      // get begin and and sychro bytes indexes: '`' and {0D}{0A}  
      // => /0`1400{03}{0D}{0A}
      for(unsigned char i = begin_index; i <= end_index; i++) // answer is input_register 17 - 26
      {
          if(uart2_rx_buf[i] == '`') 
              begin_index = i;
          if(uart2_rx_buf[i] == 0x0D && uart2_rx_buf[i+1] == 0x0A ) 
              end_index = i;
      }
      begin_index++; // moving ptr to next byte => '`',  0`1200{03}{0D}{0A}
      end_index--;   // moving ptr to next byte => end of data, 0`1200{03}{0D}{0A}
      
      data_size = end_index - begin_index; // get data char count
      // convert ans chars to number 
      sorted_anser = chars2number(data_size, begin_index);        
    }  
    else sorted_anser = ERROR_CODE; // no response - error code
    
    return sorted_anser;
}

unsigned int init_protocol(unsigned char pump_id)
{
  // /1h30001R
    
  answer_refresh(); // clear input registers 80-100 for the new cmd and answer
            
  PUMP_TX_EN; 
  uart2_send_text("/");
  uart2_send_byte(num2char(pump_id));
  uart2_send_text("h30001R"); // init protocol
  uart2_CR_LF_send();
  PUMP_TX_DIS;
  delay_ms(100);
  // check the PSD4 answer to curr cmd
  return check_cmd_answer(11);
}

unsigned int init_valve(unsigned char pump_id)
{
  answer_refresh(); // clear input registers 80-100 for the new cmd and answer
            
  PUMP_TX_EN; 
  uart2_send_text("/");
  uart2_send_byte(num2char(pump_id));
  uart2_send_text("h20000R"); // init valve  (вентиль)
  uart2_CR_LF_send();
  PUMP_TX_DIS;
  delay_ms(950);
  // check the PSD4 answer to curr cmd
  return check_cmd_answer(11);
}

unsigned int init_syringe(unsigned char pump_id)
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
  // check the PSD4 answer to curr cmd
  return check_cmd_answer(11);
}

unsigned int get_syr_pos (unsigned char pump_id)
{
  // get current syringe position 
  //unsigned int position = 0;
  
  answer_refresh(); 
  
  PUMP_TX_EN; 
  uart2_send_text("/");
  uart2_send_byte(num2char(pump_id));
  uart2_send_text("?R"); // get syringe position cmd
  uart2_CR_LF_send();
  PUMP_TX_DIS;
  //delay_ms(20); // delay to read all answer bytes
  
  //position = search_answer(8, 8, 16); 
  
  //return position;
}

unsigned int rd_syr_pos(void)
{ 
  unsigned int position = search_answer(8, 8, 16); 
  // answer: uart2_rx_buf[8] = '`', numeric value of answer - uart2_rx_buf[8 - 16] 

  return position;
}

unsigned int set_syr_pos(unsigned char pump_id, unsigned int pos)
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
                                 // cmd                answer  
    return check_cmd_answer(10); // 1A0200R{0D}{0A} -> /0@{03}{0D}{0A}
}

void get_syr_vel(unsigned char pump_id)            // get syringe velocity
{
    // get syringe velocity => /1?2R
  
    answer_refresh(); 
    
    PUMP_TX_EN; 
    uart2_send_text("/");
    uart2_send_byte(num2char(pump_id));
    uart2_send_text("?2R"); // get current velocity cmd
    uart2_CR_LF_send();
    PUMP_TX_DIS;
    //delay_ms(20); // delay to read all answer bytes !!!!
}

unsigned int rd_syr_vel(void)
{
    unsigned int velocity;
        
    velocity = search_answer(9, 7, 16); 
    // answer: reg - 9 = '`', numeric value of answer - 7 - 16 regs

    return velocity;
}

unsigned int set_syr_vel(unsigned char pump_id, unsigned int vel)  // set syringe velocity
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
    delay_ms(20); // delay to read all answer bytes
    
                                 // cmd           answer  
    return check_cmd_answer(8);  //1S10R{0D}{0A}  /0@{03}{0D}{0A}
}

void get_valve_angle (unsigned char pump_id)       // get current valve angle
{
    //  get current valve angl => /1?25000R
    
    answer_refresh(); 
    
    PUMP_TX_EN; 
    uart2_send_text("/");
    uart2_send_byte(num2char(pump_id));
    uart2_send_text("?25000R"); // get current velocity cmd
    uart2_CR_LF_send();
    PUMP_TX_DIS;
    //delay_ms(20); // delay to read all answer bytes

}

unsigned int rd_valve_angle(void)
{
    unsigned int angle; 
        
    angle = search_answer(13, 13, 18); 
  
    return angle;
    
}

unsigned int set_valve_angle(unsigned char pump_id, unsigned int angle, unsigned int dir)  // set valve angle
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
    delay_ms(20); // delay to read all answer bytes
    
                                 //  cmd               answer  
    return check_cmd_answer(10); // /1h28180R{0D}{0A}  /0@{03}{0D}{0A}
}