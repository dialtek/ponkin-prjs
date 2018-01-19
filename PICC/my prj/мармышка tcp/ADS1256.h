static U8 RdReg(U8 RegName){
   U8 RegValue = 0; 
   //1st Command Byte: 0001 rrrr where rrrr is the address of the first register to read.
   //2nd Command Byte: 0000 nnnn where nnnn is the number of bytes to read – 1
   ADC_CS = 0;
   delay_us(1);
   Spi_write2(0x10+RegName); // 1st Command Byte,??????? ??????
   Spi_write2(0x00); // 1st Command Byte, ?????? ?????? ???? ????
   delay_us(8); // 50 CLK_IN PEDIODS
   RegValue = Spi_read2(0);
   delay_us(1);
   ADC_CS =1;
   delay_us(1);
   Return RegValue;  
}

static void WrReg(U8 RegName,CommandByte)
{
   ADC_CS = 0;
   delay_us(5);
   Spi_write2(0x50+RegName); // 1st Command Byte: 0101 (0x50) rrrr where rrrr is the address to the first register to be written.
   delay_us(10);
   Spi_write2(0);         // 2nd Command Byte: 0000 nnnn where nnnn is the number of bytes to be written – 1.
   delay_us(10);
   Spi_write2(CommandByte);
   delay_us(10);
   ADC_CS = 1;
   delay_us(50);
}

static S32 ADC_RData(){            

     ADC_CS = 0;
     delay_us(1);
     Spi_write2(0x01);
     delay_us(1);
     ADC_CS = 1;
     delay_us(1);
     m1:
     if(!ADC_DRDY){
     ADC_CS = 0;
     delay_us(1);
     ADC_Rbyte1 = Spi_read2(0);
     ADC_Rbyte2 = Spi_read2(0);
     ADC_Rbyte3 = Spi_read2(0);
     delay_us(1);
     ADC_CS = 1;
     ADC_RByte_Sum = (ADC_Rbyte1<<16) + (ADC_Rbyte2<<8) + ADC_Rbyte3;
     return ADC_RByte_Sum;
     }
     else goto m1;
}

static void ADC_StartRdContin(){

     ADC_CS = 0;       
     delay_us(1);                                         
     Spi_write2(0x03);             
     delay_us(1);
     ADC_CS = 1;
}

static S32 ADC_RdataC(){
     ADC_StartRdContin();   
     While(ADC_DRDY)
     delay_us(1);
     ADC_CS = 0;
     delay_us(1);
     ADC_Rbyte1 = Spi_read2(0);
     ADC_Rbyte2 = Spi_read2(0);
     ADC_Rbyte3 = Spi_read2(0);
     delay_us(1);
     ADC_CS = 1;
     ADC_RByte_Sum = (ADC_Rbyte1<<24) + (ADC_Rbyte2<<16) + (ADC_Rbyte3<<8);
     return ADC_RByte_Sum/256;
     }

static void ADC_StopRd(){
   ADC_CS = 0;
   delay_us(5);
   Spi_write2(0x0F);  
   delay_us(5);
   ADC_CS = 1;
   delay_us(50);

}

static void ADC_sps_set(U8 SPS){
   ADC_StopRd();                                                              
   Sps_buf = SPS;
   WrReg(DRATE,SPS);                          
} 

static void ADC_SelfCal(){                    
   ADC_CS = 0;
   delay_us(1);
   Spi_write2(0xF0);
    delay_us(1);
   ADC_CS = 1;  
   Switch (Sps_buf) {   
      case 0xF0:   
       delay_us(220);        
        break;                      
      
      case 0xE0:
       delay_us(255); 
        break;
        
      case 0xD0:
       delay_us(315); 
        break;
        
      case 0xC0:
       delay_us(445); 
        break;
        
      case 0xB0:
       delay_us(685); 
        break;
        
      case 0xA1:
       delay_ms(1);
       delay_us(185);               
        break;      
        
      case 0x92:
       delay_ms(5);
        break;
        
      case 0x82:
       delay_ms(10);
       delay_us(200);
        break;
                   
      case 0x63:
       delay_ms(21); 
        break;
        
      case 0x43:
       delay_ms(41); 
        break;
        
      case 0x23:
       delay_ms(101); 
        break;         
            
      case 0x13:
       delay_ms(201); 
        break;                          
     }    
}

static void ADC_setCh(U8 Ch_Number){
   ADC_StopRd();
   Global_Ch_Number = Ch_Number;
   Switch (Ch_Number) {

    //case 4:   WrReg(MUX,0x76); //7 & 6             
           //break;
//--------------------------------
    //case 3: WrReg(MUX,0x54);    
           //break;
//--------------------------------           
    case 2: WrReg(MUX,0x01);        
           break;
//--------------------------------    
    case 1: WrReg(MUX,0x23);    
           break;
    //default:printf("bad cmd");  
            }

   ADC_SelfCal();
   ADC_StartRdContin();
   ADC_RdataC();
   ADC_RdataC();
   ADC_RdataC();
   ADC_RdataC();
}

static S32 Read_ADC_vol_in(S32 k){
    S32 VinInt;
    ADCresult = ADC_RDataC();
    ADCresult=ADCresult+ADCaddCoef; // Аддитивная ошибка, ошибка смещения 
    Vin = ((ADCresult*5)/(8388608.0*PGA))*ADCmulCoef;
    VinInt = Vin*k;
    return VinInt;
}               

static S32 ADC_vol_average(U8 NumSamples){  
   S32 A,Sum = 0;               
   U8 i;
   
   for (i = 0; i < NumSamples; i++){      
      A = Read_ADC_vol_in(uV);
      Sum = Sum + A;    
   }                                  
   return Sum/NumSamples;
}

static void ADC_set_PGA(u8 PGA_val){
  
  PGA = PGA_val;

   switch (PGA_val){
      case 1:
       WrReg(ADCON,0);
      break;
      
      case 2:
       WrReg(ADCON,1);
      break;
      
      case 4:
       WrReg(ADCON,2);
      break;
      
      case 8:
       WrReg(ADCON,3);
      break;
      
      case 16:
       WrReg(ADCON,4);
      break;
      
      case 32:
       WrReg(ADCON,5);
      break;
      
      case 64:
       WrReg(ADCON,6);
      break; 
   }
}

static void ADC_wakeUp(){
   ADC_CS = 1;                         
   ADC_RESET = 0; //When using the RESET pin, take it low to force a reset.
   delay_us(100);
   ADC_RESET = 1;
   ADC_SYNC =0;
   delay_us(100);
   ADC_SYNC = 1; //To use the SYNC/PDWN pin, take it low and then high
   delay_ms(1);
} 

static void ADC_init(){  
   WrReg(STATUS,2);
   ADC_set_PGA(8);    //
   if(ADC_sps_var>7)  ADC_sps_var = 7;
   if(ADC_sps_var==0) ADC_sps_var = 1;
   switch (ADC_sps_var){                // передача величины скорости измерений АЦП 
      case 1: ADC_sps_set(0x23);  break; // 10   sps
      case 2: ADC_sps_set(0x43);  break; // 25   sps
      case 3: ADC_sps_set(0x63);  break; // 50   sps
      case 4: ADC_sps_set(0x82);  break; // 100  sps
      case 5: ADC_sps_set(0x91);  break; // 500  sps
      case 6: ADC_sps_set(0xA1);  break; // 1000 sps
      case 7: ADC_sps_set(0xC0);  break; // 3750 sps
   }
}

static float ADC_vol_to_T(){                 // Rt = R[1 + A * t + B * t^2]
   float Final_T = 0.0;
   float R = 1000;                           // Данные из DataSheet R=1000 Ом
   float Rt = 0;
   float D = 0;
   float X = 0;
   float A = 0.0039083;                      // Некий коэффициент. Данные из Resistance Temperature Detectors (RTDs)
   float B = -0.0000005775;                  // Некий коэффициент. Данные из Resistance Temperature Detectors (RTDs)
   temp = ADC_vol_average(NumAver);         
    
   Rt = temp/10.0;                           // Приводим к Омам
   D = 1 - (Rt/R);                          
   X = A*A - (4 * B * D);
   Final_T = (-A + sqrt(X))/(2*B);           // Температура в градусах Цельсия    
   return Final_T;
  }
