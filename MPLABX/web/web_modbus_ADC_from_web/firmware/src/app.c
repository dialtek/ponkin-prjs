#include "app.h"
#include "modbus_app.h"
#include "http_app.h"
#include "d_eeprom.h"
#include "ADS1256.h"

// *****************************************************************************
// global
unsigned char EEPR_buf[Data2saveLen];

unsigned int ADC_SPS = 0; 
unsigned int ADC_PGA = 0;

unsigned int FirmVersion = 10;

signed long ADC1_arr[4] = {0,0,0,0};     // ADC1 measurements buf
signed long ADC2_arr[4] = {0,0,0,0};     // ADC2 measurements buf

float CHx_T[8] = {0,0,0,0,0,0,0,0};      // temperature array

// *****************************************************************************
// config to EEPROM save/restore functions

void SaveCfg(void)                       // save setting to EEPROM 
{
   EEPR_buf[0] = (unsigned char)ADC_SPS;
   EEPR_buf[1] = (unsigned char)ADC_PGA;  
   
   eeprom_src_save(&EEPR_buf,Data2saveLen);
}

unsigned int RestoreCfg(void)            // restore setting from EEPROM 
{
    eeprom_src_restore(&EEPR_buf,Data2saveLen); // !!! читаю наверняка - 2 раза
          
    if(eeprom_src_restore(&EEPR_buf,Data2saveLen))
    {   
      ADC_SPS = (unsigned int)EEPR_buf[0];
      ADC_PGA = (unsigned int)EEPR_buf[1];
      
      ADCs_change_SPS(ADC_SPS);
      ADCs_change_PGA(ADC_PGA);  
      
      holding_reg_write(25,1);
      return 1;
    }
    else return 0;
}

// *****************************************************************************
// ADCs

float PKT_Kx[8][8];

float power(float t, unsigned char k)    //  t to the power of k
{
  float res = 1.0;
  while (k) 
      {
        if (k & 1) 
           res *= t;
        t *= t;
        k >>= 1;
      }
  return res;
}

float ADC_vol_to_T(unsigned char PKT_ch) //  converts ADC voltage to Kelvins
{
 
 float T, R = 0;
 float k[7] = {0,0,0,0,0,0,0};
 float p = 0, t = 0, z1,z2,z3,z4,z5,z6 = 0;
 
 unsigned char i = 0;

 for(i = 0; i < 7; i++)                 // fill coeff. array from the web sets
 {
    if(PKT_Kx[PKT_ch][i] != 0) 
      k[i] = PKT_Kx[PKT_ch][i];
 }
 
 R = PKT_Kx[PKT_ch][7];                 // save the Rx value

 if(PKT_ch < 4)                  
   t = ADC1_arr[PKT_ch]/CURR_SRC_VAL;   // ADC1 meas data
 else 
   t = ADC2_arr[PKT_ch-4]/CURR_SRC_VAL; // ADC2 meas data
 
 p = (float)(R/t);                      // R nominal/R measured
 
 z1 = k[0]+k[1]*p;                      // calc the polynome members
 z2 = k[2]*(power(p,2.0));
 z3 = k[3]*(power(p,3.0));
 z4 = k[4]*(power(p,4.0));
 z5 = k[5]*(power(p,5.0));
 z6 = k[6]*(power(p,6.0));
 T  = z1+z2+z3+z4+z5+z6;               // final result in Kelvins 
 
 return T;
}

void ADC_SPS_Set(int New_ADC_SPS)        // ADC meas freq. set
{
     if(New_ADC_SPS <= ADC_MAX_SPS)
     {
        ADC_SPS = New_ADC_SPS;
        ADCs_change_SPS(ADC_SPS);
        SaveCfg();
     }
     
     // x = adc_get_sps()
     // if(x == New_ADC_SPS)
     
}

int ADC_SPS_Get(void)                    // ADC meas freq. get
{
    return ADC_SPS;
}

void Fill_Temper_regs(void)              // calc T and fill regs
{
   unsigned int n = 0;                   // temperature inerator
   
   // temperature
   for(n = 0; n < 8; n++)         
   {
     CHx_T[n] = ADC_vol_to_T(n);   // calc temperature 
     CHx_T[n] *= CURR_SRC_VAL;     // 1089.12 -> 108912  
     holding_reg_write(30+n,(unsigned int)CHx_T[n]);  // write to regs
   }  
}

// *****************************************************************************
// MODBUS RTU over TCP

 unsigned int RegisterAddr  = 0;         // modbus write reg addr
 unsigned int RegisterValue = 0;         // modbus write reg velue
 
 void modbus_poll(void)                  // modbus logic
{       
  switch( modbus_get_poll() )            // check if received modbus cmd
  {
    case 0x03:   
////////////////////////////  HOLDING //////////////////////////
      if(ADCs_meas_ready())              // ADCs read complete, new data
      {  
         // 0. 000 000  
         holding_reg_write(0, (unsigned int) (ADC1_arr[0] & 0x0000ffff));          // LSB ������ 1
         holding_reg_write(1, (unsigned int)((ADC1_arr[0] & 0xffff0000) >> 16));   // MSB ������ 1


         holding_reg_write(2, (unsigned int) (ADC1_arr[1] & 0x0000ffff));          // LSB ������ 2
         holding_reg_write(3, (unsigned int)((ADC1_arr[1] & 0xffff0000) >> 16));   // LSB ������ 2

         holding_reg_write(4, (unsigned int) (ADC1_arr[2] & 0x0000ffff));          // LSB ������ 3
         holding_reg_write(5, (unsigned int)((ADC1_arr[2] & 0xffff0000) >> 16));   // MSB ������ 3

         holding_reg_write(6, (unsigned int) (ADC1_arr[3] & 0x0000ffff));          // LSB ������ 4
         holding_reg_write(7, (unsigned int)((ADC1_arr[3] & 0xffff0000) >> 16));   // LSB ������ 4

         holding_reg_write(8, (unsigned int) (ADC2_arr[0] & 0x0000ffff));          // LSB ������ 5
         holding_reg_write(9, (unsigned int)((ADC2_arr[0] & 0xffff0000) >> 16));   // MSB ������ 5

         holding_reg_write(10, (unsigned int) (ADC2_arr[1] & 0x0000ffff));         // LSB ������ 6
         holding_reg_write(11, (unsigned int)((ADC2_arr[1] & 0xffff0000) >> 16));  // LSB ������ 6

         holding_reg_write(12, (unsigned int) (ADC2_arr[2] & 0x0000ffff));         // LSB ������ 7
         holding_reg_write(13, (unsigned int)((ADC2_arr[2] & 0xffff0000) >> 16));  // MSB ������ 7

         holding_reg_write(14, (unsigned int) (ADC2_arr[3] & 0x0000ffff));         // LSB ������ 8
         holding_reg_write(15, (unsigned int)((ADC2_arr[3] & 0xffff0000) >> 16));  // LSB ������ 8 

         Fill_Temper_regs();              // update T value, 30-37 regs
      }
         // get ADCs parameters 
         holding_reg_write(17, ADCs_get_CurrMeasCh());
         holding_reg_write(18, ADCs_get_PGA());
         holding_reg_write(19, ADCs_get_SPS());
         holding_reg_write(20, FirmVersion);

      modbus_rhr_answer();          
    break;
//////////////////////////// HOLDING //////////////////////////
    case 0x06:
        modbus_wsr_answer();  

        RegisterAddr  = get_wr_reg_addr();    // get address
        RegisterValue = get_wr_reg_val();     // get the new value

       switch(RegisterAddr)
       {
          case 18: // reg 18 - range
            if(RegisterValue <= ADC_MAX_RANGE)
            {
              ADC_PGA = RegisterValue;
              ADCs_change_PGA(ADC_PGA);  
              SaveCfg();
            }
          break;
          //----
          case 19: // reg 19 - SPS
            ADC_SPS_Set(RegisterValue);
          break;
          //----    
          default: break;
       }


    break;
//////////////////////////// INPUT ////////////////////////////
    case 0x04:
      input_reg_write(0, 89);
      modbus_rir_answer(); //
    break;
 }
}
 
void APP_Initialize ( void )            // init system
{
    HTTP_APP_Initialize();              // http   web server init  
    MODBUS_APP_Initialize();            // modbus tcp server init
    ADCs_init(1);                       // ADCs init
    ADCs_init(1);                       // 2 times required
    
    RestoreCfg();                       // restore last device params
    
    // TODO - function, get coef from web page 
    PKT_Kx[6][0]=3.06244888759101741;
    PKT_Kx[6][1]=-30.3586341044865549;
    PKT_Kx[6][2]=241,908977336715907;
    PKT_Kx[6][3]=-649.7562889382243166;
    PKT_Kx[6][4]=955.307573420926928;
    PKT_Kx[6][5]=-485.428257496096194;
    PKT_Kx[6][6]=136.248866791371256;
    PKT_Kx[6][7]=1000.0;

}

void APP_Tasks ( void )                 // tasks
{
    modbus_poll();                      // tcp-server - MODBUS
    HTTP_APP_Tasks();                   // web server
    ADC_par_rd_ch(&ADC1_arr,&ADC2_arr); // ADC read
}

// *****************************************************************************
