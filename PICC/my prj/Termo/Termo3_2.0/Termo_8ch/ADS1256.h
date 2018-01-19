
static void ADC_wakeUp(){

   ADC_CS = 1;
   ADC2_CS = 1;
   
   ADC_RESET = 0; //When using the RESET pin, take it low to force a reset.
   ADC2_RESET = 0; //When using the RESET pin, take it low to force a reset.
   delay_us(200);
   
   ADC_RESET = 1;
   ADC2_RESET = 1;
   
   ADC_SYNC =0;
   ADC2_SYNC =0;   
   delay_us(200);
   
   ADC_SYNC = 1; //To use the SYNC/PDWN pin, take it low and then high
   ADC2_SYNC = 1; //To use the SYNC/PDWN pin, take it low and then high
   
   delay_ms(2);

}

static U8 RdReg(U8 RegName)
{
   U8 RegValue = 0; 
   //1st Command Byte: 0001 rrrr where rrrr is the address of the first register to read.
   //2nd Command Byte: 0000 nnnn where nnnn is the number of bytes to read � 1
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
   ADC2_CS = 0;
   delay_us(5);
   Spi_write2(0x50+RegName); // 1st Command Byte: 0101 (0x50) rrrr where rrrr is the address to the first register to be written.
   delay_us(10);
   Spi_write2(0);         // 2nd Command Byte: 0000 nnnn where nnnn is the number of bytes to be written � 1.
   delay_us(10);
   Spi_write2(CommandByte);
   delay_us(10);
   ADC_CS = 1;
   ADC2_CS = 1;
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

     if    (ADC_select) {ADC_CS = 1; ADC2_CS = 0;}
     else  {ADC_CS = 0; ADC2_CS = 1;}
     delay_us(1);                                         
     Spi_write2(0x03);             
     delay_us(1);
     ADC_CS = 1;
     ADC2_CS = 1;
}

static S32 ADC_RdataC(){                                              
                                                                  
     if (ADC_select) {ADC_CS = 1; ADC2_CS = 0;}
     else            {ADC_CS = 0; ADC2_CS = 1;}
     delay_us(1);                                         
     Spi_write2(0x03);             
     delay_us(1);
     ADC_CS = 1;
     ADC2_CS = 1;
     
     if (ADC_select == 0){
      While(ADC_DRDY)
      delay_us(1);
      ADC_CS = 0;
      delay_us(1);
      ADC_Rbyte1 = Spi_read2(0);
      ADC_Rbyte2 = Spi_read2(0);
      ADC_Rbyte3 = Spi_read2(0);
      delay_us(1);
      ADC_CS = 1;
          }
     
     else {
      While(ADC2_DRDY)
      delay_us(1);
      ADC2_CS = 0;
      delay_us(1);
      ADC_Rbyte1 = Spi_read2(0);
      ADC_Rbyte2 = Spi_read2(0);
      ADC_Rbyte3 = Spi_read2(0);
      delay_us(1);
      ADC2_CS = 1;  
          }
     
     ADC_RByte_Sum = (ADC_Rbyte1<<24) + (ADC_Rbyte2<<16) + (ADC_Rbyte3<<8);
     return ADC_RByte_Sum/256;
     
     }

static void ADC_StopRd(){
   
     if    (ADC_select) {ADC_CS = 1; ADC2_CS = 0;}
     else  {ADC_CS = 0; ADC2_CS = 1;}
   delay_us(5);
   Spi_write2(0x0F);  
   delay_us(5);
   ADC2_CS = 1;
   ADC_CS = 1;
   delay_us(50);

}

static void ADC_sps_set(U8 SPS){

   ADC_StopRd();                                                              
   Sps_buf = SPS;
   WrReg(DRATE,SPS); 
                 
   // ???????? ???_????? ? ??????????          
} 

static void ADC_SelfCal(){
                     
   ADC_CS = 0;
   ADC2_CS = 0;
   delay_us(1);
   Spi_write2(0xF0);
    delay_us(1);
   ADC_CS = 1;
   ADC2_CS = 1;
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
   if (Ch_Number > 4) ADC_select = 1;
   else ADC_select = 0;
     
   Switch (Ch_Number) {

    case 4: WrReg(MUX,0x10); break;
    case 3: WrReg(MUX,0x32); break;
    case 2: WrReg(MUX,0x54); break;
    case 1: WrReg(MUX,0x76); break;
    
    case 8: WrReg(MUX,0x10); break;
    case 7: WrReg(MUX,0x32); break;
    case 6: WrReg(MUX,0x54); break;
    case 5: WrReg(MUX,0x76); break; 
    
           }
   ADC_SelfCal();
   ADC_StartRdContin();
   ADC_RdataC();
   ADC_RdataC();
   ADC_RdataC();
   ADC_RdataC();
   

}

static S32 Read_ADC_vol_in(S32 k){
    S32 VinInt = 0;
    ADCresult = ADC_RDataC();
    ADCresult=ADCresult+ADCaddCoef; // ���������� ������, ������ �������� 
    Vin = ((ADCresult*5)/(8388608.0*PGA))*ADCmulCoef;
    VinInt = Vin*k;
    return VinInt;
}               

static S32 ADC_vol_average(U8 NumSamples){
   
   S32 A,Sum = 0;               
   U8 i;
   
   for (i=0;i<NumSamples;i++){
       
       A = Read_ADC_vol_in(uV);
       Sum = Sum + A;    
   }                                  
   return Sum/NumSamples;
}

static void ADC_set_PGA(u8 PGA_val){
  
  PGA = PGA_val;

/* PGA
000 = 1 (default)
001 = 2
010 = 4
011 = 8
100 = 16
101 = 32
110 = 64
111 = 64*/

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

static void ADC_init(){
   
  WrReg(STATUS,2);
      //
   if(ADC_sps_var>7)  ADC_sps_var = 7;
   if(ADC_sps_var==0) ADC_sps_var = 1;
    switch (ADC_sps_var){                // �������� �������� �������� ��������� ��� 
      case 1: ADC_sps_set(0x23);  break; // 10   sps
      case 2: ADC_sps_set(0x43);  break; // 25   sps
      case 3: ADC_sps_set(0x63);  break; // 50   sps
      case 4: ADC_sps_set(0x82);  break; // 100  sps
      case 5: ADC_sps_set(0x91);  break; // 500  sps
      case 6: ADC_sps_set(0xA1);  break; // 1000 sps
      case 7: ADC_sps_set(0xC0);  break; // 3750 sps
      }

}

static float power(float t, U8 k) // ���������� t � ������� k
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

static float ADC_vol_to_T(){
    float R = 1000;
    float Temper,k1,k2,k3,k4,k5,k6,k7 = 0;
    float p,z1,z2,z3,z4,z5,z6 = 0;
    U8 Temper_int = 0;
   temp = ADC_vol_average(NumAver);
   p=R/(temp/10); // �������� � ���
   switch (Global_Ch_Number){
//-------------------------------------------
      case 4: // ���������
k1=12.1972840491798706;
k2=-103.27107382635586;
k3=397.925821471959352;
k4=-567.703864333219826;
k5=208.592693047598004;
k6=315.492219684645534;
k7=-92.5740048021543771;
      break;
//-------------------------------------------
      case 3: // ����
k1=3.06244888759101741;
k2=-30.3586341044865549;
k3=241.908977336715907;
k4=-649.756288938224316;
k5=955.307573420926928;
k6=-485.428257496096194;
k7=136.248866791371256;
      break;
      //-------------------------------------------
      case 2: // ���
k1=17.2566714868880808;
k2=-215.322746395599097;
k3=1219.40785944648087;
k4=-3277.70955596119165;
k5=4778.55193661898375;
k6=-3251.6292140185833;
k7=954.333331361413002;
      break; 
//-------------------------------------------
      case 1: // ��������
k1 = 4.005067403952125460;
k2 = -55.2455571058671922;
k3 = 448.087557092308998;
k4 = -1390.99036489240825; 
k5 = 2271.71780132129788; 
k6 = -1387.04864621348679; 
k7 = 500.36806705314666;
      break;         
//-------------------------------------------
   }
   z1 = k1+k2*p;
   z2 = k3*(power(p,2));
   z3 = k4*(power(p,3));
   z4 = k5*(power(p,4));
   z5 = k6*(power(p,5));
   z6 = k7*(power(p,6));
   Temper = (z1+z2+z3+z4+z5+z6);
   Temper_int = Temper;
   ostatok_int_dec = (Temper-Temper_int)*10;
   ostatok_int_sot = (Temper-Temper_int)*100;
   if (ostatok_int_sot > 4) ostatok_int_dec++;
   if (Temper<10) { LCD_num_symb = 1;}
   if (Temper>=10){ LCD_num_symb = 2;}
   if (Temper>=100){LCD_num_symb = 3;}
   return Temper;
   }

/*

static U8 RdReg(U8 RegName)
{
   U8 RegValue = 0; 
   //1st Command Byte: 0001 rrrr where rrrr is the address of the first register to read.
   //2nd Command Byte: 0000 nnnn where nnnn is the number of bytes to read � 1
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
   //if   (ADC_select) {ADC_CS = 0; ADC2_CS = 1;}
   //else              {ADC_CS = 1; ADC2_CS = 0;}
   ADC_CS = 0;
   //ADC2_CS = 0;
   delay_us(5);
   Spi_write2(0x50+RegName); // 1st Command Byte: 0101 (0x50) rrrr where rrrr is the address to the first register to be written.
   delay_us(10);
   Spi_write2(0);            // 2nd Command Byte: 0000 nnnn where nnnn is the number of bytes to be written � 1.
   delay_us(10);
   Spi_write2(CommandByte);
   delay_us(10);
   ADC_CS = 1;
   //ADC2_CS = 1;
   delay_us(50);
}

static S32 ADC_RData(){            

     //if   (ADC_select) {ADC_CS = 0; ADC2_CS = 1;}
     //else              {ADC_CS = 1; ADC2_CS = 0;}
     ADC_CS = 0;
     delay_us(1);
     Spi_write2(0x01);
     delay_us(1);
     ADC_CS = 1;
     //ADC2_CS = 1;
     delay_us(1);
     m1:
     if(!ADC_DRDY | !ADC2_DRDY){
     if   (ADC_select) {ADC_CS = 0; ADC2_CS = 1;}
     else              {ADC_CS = 1; ADC2_CS = 0;}
     delay_us(1);
     ADC_Rbyte1 = Spi_read2(0);
     ADC_Rbyte2 = Spi_read2(0);
     ADC_Rbyte3 = Spi_read2(0);
     delay_us(1);
     ADC_CS = 1;
     //ADC2_CS = 1;
     ADC_RByte_Sum = (ADC_Rbyte1<<16) + (ADC_Rbyte2<<8) + ADC_Rbyte3;
     return ADC_RByte_Sum;
     }
     else goto m1;
}

static void ADC_StartRdContin(){

     //if   (ADC_select) {ADC_CS = 0; ADC2_CS = 1;}
     //else              {ADC_CS = 1; ADC2_CS = 0;} 
     ADC_CS = 0;
     delay_us(1);                                         
     Spi_write2(0x03);             
     delay_us(1);
     ADC_CS = 1;
     //ADC2_CS = 1;
    
}

static S32 ADC_RdataC(){                                              
                                                              
     //ADC_StartRdContin();
     //if   (ADC_select) {ADC_CS = 0; ADC2_CS = 1;}
     //else              {ADC_CS = 1; ADC2_CS = 0;}
     ADC_CS = 0;
     delay_us(1);                                         
     Spi_write2(0x03); //ADC_StartRdContin            
     delay_us(1);
     ADC_CS = 1;
     //ADC2_CS = 1;
     //While(ADC_DRDY | ADC2_DRDY)
     While(ADC_DRDY)
     delay_us(1);
     //if   (ADC_select) {ADC_CS = 0; ADC2_CS = 1;}
     //else              {ADC_CS = 1; ADC2_CS = 0;}
     //ADC2_CS = 0
     ADC_CS = 0;
     delay_us(1);
     ADC_Rbyte1 = Spi_read2(0);
     ADC_Rbyte2 = Spi_read2(0);
     ADC_Rbyte3 = Spi_read2(0);
     delay_us(1);
     ADC_CS = 1;
     //ADC2_CS = 1;
     ADC_RByte_Sum = (ADC_Rbyte1<<24) + (ADC_Rbyte2<<16) + (ADC_Rbyte3<<8);
     return ADC_RByte_Sum/256;
     }

static void ADC_StopRd(){
   
   ADC_CS = 0;
   //ADC2_CS = 0;
   delay_us(5);
   Spi_write2(0x0F);  
   delay_us(5);
   ADC_CS = 1;
   //ADC2_CS = 1;
   delay_us(50);

}

static void ADC_sps_set(U8 SPS){

   ADC_StopRd();                                                              
   Sps_buf = SPS;
   WrReg(DRATE,SPS); 
                 
   // ???????? ???_????? ? ??????????          
} 

static void ADC_SelfCal(){
                     
   ADC_CS = 0;
   //ADC2_CS = 0;
   delay_us(1);
   Spi_write2(0xF0);
    delay_us(1);
   ADC_CS = 1;
   //ADC2_CS = 1;  
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
   
   //if (Ch_number>4) {ADC_select = 0;}
   //else ADC_select = 1; 
   
   Switch (Ch_Number) {

    case 4: WrReg(MUX,0x10); break;
    case 3: WrReg(MUX,0x32); break;
    case 2: WrReg(MUX,0x54); break;
    case 1: WrReg(MUX,0x76); break;
    
    case 8: WrReg(MUX,0x10); break;
    case 7: WrReg(MUX,0x32); break;
    case 6: WrReg(MUX,0x54); break;
    case 5: WrReg(MUX,0x76); break; 
   ADC_SelfCal();
   ADC_StartRdContin();
   ADC_RdataC();
   ADC_RdataC();
   ADC_RdataC();
   ADC_RdataC();
   
}
}

static S32 Read_ADC_vol_in(S32 k){
    S32 VinInt;
    ADCresult = ADC_RDataC();
    //ADCresult=ADCresult+ADCaddCoef; // ���������� ������, ������ �������� 
    Vin = ((ADCresult*5)/(8388608.0*PGA));//*ADCmulCoef;
    VinInt = Vin*k;
    return VinInt;
}               

static S32 ADC_vol_average(U8 NumSamples){
   
   S32 A,Sum = 0;               
   U8 i;
   
   for (i=0; i<NumSamples; i++) {
       
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
   //ADC2_CS = 1;
   ADC_RESET = 0; //When using the RESET pin, take it low to force a reset.
   //ADC2_RESET = 0; //When using the RESET pin, take it low to force a reset.
   delay_us(100);
   ADC_RESET = 1;
   //ADC2_RESET = 1;
   ADC_SYNC =0;
   //ADC2_SYNC =0;
   delay_us(100);
   ADC_SYNC = 1; //To use the SYNC/PDWN pin, take it low and then high
   //ADC2_SYNC = 1; //To use the SYNC/PDWN pin, take it low and then high
   delay_ms(1);

} 

static void ADC_init(){
   
  WrReg(STATUS,2);
  ADC_set_PGA(8);    //
   if(ADC_sps_var>7)  ADC_sps_var = 7;
   if(ADC_sps_var==0) ADC_sps_var = 1;
    switch (ADC_sps_var){                // �������� �������� �������� ��������� ��� 
      case 1: ADC_sps_set(0x23);  break; // 10   sps
      case 2: ADC_sps_set(0x43);  break; // 25   sps
      case 3: ADC_sps_set(0x63);  break; // 50   sps
      case 4: ADC_sps_set(0x82);  break; // 100  sps
      case 5: ADC_sps_set(0x91);  break; // 500  sps
      case 6: ADC_sps_set(0xA1);  break; // 1000 sps
      case 7: ADC_sps_set(0xC0);  break; // 3750 sps
      }

}

static float power(float t, U8 k) // ���������� t � ������� k
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

static float ADC_vol_to_T(){
    float R = 1000;
    float Temper,k1,k2,k3,k4,k5,k6,k7 = 0;
    float p,z1,z2,z3,z4,z5,z6 = 0;
    U8 Temper_int = 0;
   temp = ADC_vol_average(NumAver);
   p=R/(temp/10); // �������� � ���
   switch (Global_Ch_Number){
//-------------------------------------------
      case 4: // ���������
k1=12.1972840491798706;
k2=-103.27107382635586;
k3=397.925821471959352;
k4=-567.703864333219826;
k5=208.592693047598004;
k6=315.492219684645534;
k7=-92.5740048021543771;
      break;
//-------------------------------------------
      case 3: // ����
k1=3.06244888759101741;
k2=-30.3586341044865549;
k3=241.908977336715907;
k4=-649.756288938224316;
k5=955.307573420926928;
k6=-485.428257496096194;
k7=136.248866791371256;
      break;
      //-------------------------------------------
      case 2: // ���
k1=17.2566714868880808;
k2=-215.322746395599097;
k3=1219.40785944648087;
k4=-3277.70955596119165;
k5=4778.55193661898375;
k6=-3251.6292140185833;
k7=954.333331361413002;
      break; 
//-------------------------------------------
      case 1: // ��������
k1 = 4.005067403952125460;
k2 = -55.2455571058671922;
k3 = 448.087557092308998;
k4 = -1390.99036489240825; 
k5 = 2271.71780132129788; 
k6 = -1387.04864621348679; 
k7 = 500.36806705314666;
      break;         
//-------------------------------------------
   }
   z1 = k1+k2*p;
   z2 = k3*(power(p,2));
   z3 = k4*(power(p,3));
   z4 = k5*(power(p,4));
   z5 = k6*(power(p,5));
   z6 = k7*(power(p,6));
   Temper = (z1+z2+z3+z4+z5+z6);
   Temper_int = Temper;
   ostatok_int_dec = (Temper-Temper_int)*10;
   ostatok_int_sot = (Temper-Temper_int)*100;
   if (ostatok_int_sot > 4) ostatok_int_dec++;
   if (Temper<10) { LCD_num_symb = 1;}
   if (Temper>=10){ LCD_num_symb = 2;}
   if (Temper>=100){LCD_num_symb = 3;}
   return Temper;
   }
   */
