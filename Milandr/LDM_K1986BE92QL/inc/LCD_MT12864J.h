// Библиотека для графического дисплея MT-12864J Российской фирмы МЭЛТ
// Дата изменения: 15/01/14 21:48
// Автор: Понкин Дмитрий

//------------------------------Описание функций библиотеки:

//------------------------------ПОЛЬЗОВАТЕЛЬСКИЕ ФУНКЦИИ-----------------------//
// LCD_set_cursor(uint8_t setPoint)       - утановка курсора, число 0-7.пример: LCD_set_cursor(2);
// LCD_full_clear(void)				      - полная очистка дисплея 					
// LCD_space (uint8_t SpaceMulCoef)       - пробел, указывается количество пробелов. пример: LCD_space(4); 
// LCD_Wr_num(uint32_t number,uint8_t num_lenght) - вывод числа, указывается чсило и количсесво цифр в числе. пример: LCD_Wr_num(255,3);
// LCD_print (char* full_word)            - печать слов и символов на дисплее. пример: LCD_print ("Привет! Hello!")  
//-----------------------------------------------------------------------------//

// -----------------------------СИСТЕМНЫЕ ФУНКЦИИ------------------------------//
// LCD_Wr_CMDL  (uint8_t cmd) - запись байта команды в левую  часть дисплея 
// LCD_Wr_CMDR  (uint8_t cmd) - запись байта команды в правую часть дисплея 
// LCD_Wr_DataL (uint8_t dat) - запись байта данных в левую  часть дисплея
// LCD_Wr_DataR (uint8_t dat) - запись байта данных в правую  часть дисплея
// LCD_init	    (void) 			  - инициализация дисплея
// LCD_set_RAM_pageL (uint8_t RAM_page_num)   - утановка курсора на станицу памяти в левой части экрана
// LCD_set_RAM_pageR (uint8_t RAM_page_num)   - утановка курсора на станицу памяти в правой части экрана
// LCD_set_page_AdrL (uint8_t page_adr)		  - установка курсора на определенный пексиль в выбранной странице памяти левой части экрана
// LCD_set_page_AdrR (uint8_t page_adr)       - установка курсора на определенный пексиль в выбранной странице памяти правой части экрана
// LCD_Wr_small_single_numL  (uint8_t number) - вывод одной цифры высотой 7 пикселей 
// LCD_Wr_small_single_wordL (uint8_t number) - вывод одной буквы высотой 7 пикселей 
// LCD_Wr_small_num  (uint32_t number,uint8_t num_lenght) - вывод числа, указывается чсило и количсесво цифр в числе.
// LCD_draw_ktes     (void) 				  - печать логотипа 
//----------------------------------------------------------------------------//

//---------------------------LCD defines--------------------------------------//
// АССОЦИАЦИЯ ПИНОВ МК И ДИСПЛЕЯ
#define LCD_E1_ON   MDR_PORTB->RXTX |=  (1<<7) 	// PIN PORTB.7 = 1
#define LCD_E1_OFF  MDR_PORTB->RXTX &= ~(1<<7) 	// PIN PORTB.7 = 0
#define LCD_E2_ON   MDR_PORTB->RXTX |=  (1<<8) 	// PIN PORTB.8 = 1 
#define LCD_E2_OFF  MDR_PORTB->RXTX &= ~(1<<8) 	// PIN PORTB.8 = 0
#define LCD_A0_ON   MDR_PORTC->RXTX |=  1	// PIN PORTC.0 = 1
#define LCD_A0_OFF  MDR_PORTC->RXTX &= ~1	// PIN PORTC.0 = 0
#define LCD_RES_ON  MDR_PORTB->RXTX |=  (1<<9)	// PIN PORTB.9 = 1
#define LCD_RES_OFF MDR_PORTB->RXTX &= ~(1<<9)	// PIN PORTB.9 = 0
#define LCD_E_ON    MDR_PORTC->RXTX |=  (1<<1) 	// PIN PORTC.1 = 1
#define LCD_E_OFF   MDR_PORTC->RXTX &= ~(1<<1) 	// PIN PORTC.1 = 0
#define LCD_RW_ON   MDR_PORTB->RXTX |=  (1<<10) 	// PIN PORTB.10 = 1
#define LCD_RW_OFF  MDR_PORTB->RXTX &= ~(1<<10) 	// PIN PORTB.2 = 1
//-----------------------End of LCD defines-----------------------------------//

   uint8_t symbol_cnt = 0; // переменная заполнения экрана

//-----------------------LCD font---------------------------------------------//
  
  const uint8_t num_1_small [3] = 
{       // шрифт lucidaSansUnicode_7pt
	// ###
	//  ##
	//  ##
	//  ##
	//  ##
	//  ##
	//  ##
	0x01, 0x7F, 0x7F,  
};

  const uint8_t num_2_small [5] = 
{
	//  ### 
	// ## ##
	//    ##
	//   ## 
	//  ##  
	// ##   
	// #####
	0x62, 0x73, 0x59, 0x4F, 0x46,
};

  const uint8_t num_3_small [5] = 
{
	//  ### 
	// ## ##
	//    ##
	//  ### 
	//    ##
	// ## ##
	//  ### 
	0x22, 0x6B, 0x49, 0x7F, 0x36, 
};

  const uint8_t num_4_small [6] = 
{
	//    ## 
	//   ### 
	//  #### 
	// ## ## 
	// ######
	//    ## 
	//    ## 
	0x18, 0x1C, 0x16, 0x7F, 0x7F, 0x10,
};

  const uint8_t num_5_small [5] = 
{
	// #####
	// ##   
	// ##   
	// #### 
	//    ##
	//    ##
	// #### 
	0x4F, 0x4F, 0x49, 0x79, 0x31,  
};

  const uint8_t num_6_small [5] = 
{
	//  ###
	// ##   
	// ##   
	// #### 
	// ## ##
	// ## ##
	//  ### 
	0x3E, 0x7F, 0x49, 0x79, 0x30,
};

  const uint8_t num_7_small [5] = 
{
	// #####
	//    ##
	//   ## 
	//  ##  
	//  ##  
	// ##   
	// ##   
	0x61, 0x79, 0x1D, 0x07, 0x03, 
};

  const uint8_t num_8_small [5] = 
{
	//  ### 
	// ## ##
	// ## ##
	//  ### 
	// ## ##
	// ## ##
	//  ### 
	0x36, 0x7F, 0x49, 0x7F, 0x36,
};

  const uint8_t num_9_small [5] = 
{
	//  ### 
	// ## ##
	// ## ##
	//  ####
	//    ##
	//    ##
	//  ### 
	0x06, 0x4F, 0x49, 0x7F, 0x3E,
};

  const uint8_t num_0_small [6] = 
{
	//  #### 
	// ##  ##
	// ##  ##
	// ##  ##
	// ##  ##
	// ##  ##
	//  #### 
	0x3E, 0x7F, 0x41, 0x41, 0x7F, 0x3E, 
};

//----------------------------------------Signs-------------------------------//

  const uint8_t great_sign [6] = 
{
//>
 0x41, 0x63, 0x36, 0x1C, 0x08,0x00   // больше
};

  const uint8_t less_sign [6] = 
{
//<
  0x08, 0x1C, 0x36, 0x63, 0x41,0x00,  // меньше
};
	
  const uint8_t eq_sign [6] = 
{

  0x00, 0x14, 0x14, 0x14, 0x14,0x00,  // =
};

  const uint8_t plus_sign [5] = 
{
	0x08, 0x08, 0x3E, 0x08, 0x08, // +
};

  const uint8_t minus_sign [5] = 
{
  0x08, 0x08, 0x08, 0x08, 0x08 ,  // -
};

  const uint8_t dvoetoch [3] = 
{
	0x36, 0x36, 0x00,  // :
};

  const uint8_t vosklit_zn [3] = 
{
	0x6F, 0x6F, 0x00, // !
};

  const uint8_t vopros_zn [5] = 
{
	0x03, 0x69, 0x69, 0x0F, 0x00,  // ?
};

  const uint8_t sign_dot [3] = 
{
        0x60, 0x60, 0x00,  // .
};

  const uint8_t zap_zn [3] = 
{
     0x60, 0xE0, 0x00,  // ,
};

  const uint8_t sign__ [6] = 
{
    0x00, 0x40, 0x40, 0x40, 0x40,0x00, // _
};

  const uint8_t zvezd_zn [7] = 
{
     0x00, 0x2A, 0x1C, 0x3E, 0x1C, 0x2A,0x00, // *
};

  const uint8_t sign_t2 [5] = 
{
        0x60, 0x30, 0x18, 0x0C, 0x06,  // /
};

//----------------------------------------ABC_RUS-----------------------------//
  const uint8_t word_A [7] = 
{       // Gadugi 6pts / Bold

	//   ###  
	//   ###  
	//  ## ## 
	//  ## ## 
	// #######
	// ##   ##
	// ##   ##
	0x70, 0x7C, 0x1F, 0x13, 0x1F, 0x7C, 0x70, 
};

  const uint8_t word_6e [5] = 
{
	// #### 
	// ##   
	// ##   
	// #### 
	// ## ##
	// ## ##
	// #### 
	//      
	0x7F, 0x7F, 0x49, 0x79, 0x30,  
};

  const uint8_t word_B [5] = 
{
	// #### 
	// ## ##
	// ## ##
	// #### 
	// ## ##
	// ## ##
	// #### 
	//      
	0x7F, 0x7F, 0x49, 0x7F, 0x36,  
};

  const uint8_t word_Ge [5] = 
{
	// #####
	// ##   
	// ##   
	// ##   
	// ##   
	// ##   
	// ##   
	//      
	0x7F, 0x7F, 0x01, 0x01, 0x01, 
  
};

  const uint8_t word_D [8] = 
{
	//   ##### 
	//   ## ## 
	//   ## ## 
	//   ## ## 
	//   ## ## 
	//  ##  ## 
	// ########
	//     
	0x40, 0x60, 0x7F, 0x5F, 0x41, 0x7F, 0x7F, 0x40, 
  
};

  const uint8_t word_E [5] = 
{
	// #####
	// ##   
	// ##   
	// #####
	// ##   
	// ##   
	// #####
	//      
	0x7F, 0x7F, 0x49, 0x49, 0x49, 
  
};

  const uint8_t word_Je [10] = 
{
	// ##  ##  ##
	//  ## ## ## 
	//   ######  
	//    ####   
	//   ######  
	//  ## ## ## 
	// ##  ##  ##
	//           
	0x41, 0x63, 0x36, 0x1C, 0x7F, 0x7F, 0x1C, 0x36, 0x63, 0x41, 
  
};

  const uint8_t word_Z [5] = 
{
	//  ### 
	// ## ##
	//    ##
	//  ### 
	//    ##
	// ## ##
	//  ### 
	//      
	0x22, 0x6B, 0x49, 0x7F, 0x36, 

  
};

  const uint8_t word_I [6] = 
{
	// ##  ##
	// ## ###
	// ## ###
	// ######
	// ### ##
	// ### ##
	// ##  ##
	//       
	0x7F, 0x7F, 0x38, 0x0E, 0x7F, 0x7F, 
};

  const uint8_t word_K [6] = 
{
	// ##  ##
	// ## ## 
	// ####  
	// ###   
	// ####  
	// ## ## 
	// ##  ##
	//       
	0x7F, 0x7F, 0x1C, 0x36, 0x63, 0x41, 
  
};

  const uint8_t word_L [6] = 
{
	//  #####
	//  ## ##
	//  ## ##
	//  ## ##
	//  ## ##
	//  ## ##
	// ##  ##
	//       
	0x40, 0x7F, 0x3F, 0x01, 0x7F, 0x7F, 
};

  const uint8_t word_M [8] = 
{

	// ##    ##
	// ##    ##
	// ###  ###
	// ########
	// ########
	// ## ## ##
	// ##    ##
	0x7F, 0x7F, 0x1C, 0x38, 0x38, 0x1C, 0x7F, 0x7F, 
};

  const uint8_t word_H [6] = 
{
	// ##  ##
	// ##  ##
	// ##  ##
	// ######
	// ##  ##
	// ##  ##
	// ##  ##
	//       
	0x7F, 0x7F, 0x08, 0x08, 0x7F, 0x7F, 
};

  const uint8_t word_O [6] = 
{
	//  #### 
	// ##  ##
	// ##  ##
	// ##  ##
	// ##  ##
	// ##  ##
	//  #### 
	//       
	0x3E, 0x7F, 0x41, 0x41, 0x7F, 0x3E,  
};
  
  const uint8_t word_Pe [6] = 
{
	// #######
	// ##   ##
	// ##   ##
	// ##   ##
	// ##   ##
	// ##   ##
	// ##   ##
	0x7F, 0x7F, 0x01, 0x01, 0x7F, 0x7F, 
};

  const uint8_t word_R [6] = 
{
	// ##### 
	// ##  ##
	// ##  ##
	// ##### 
	// ##    
	// ##    
	// ##    
	//       
	0x7F, 0x7F, 0x09, 0x09, 0x0F, 0x06, 
};
  
  const uint8_t word_C [6] = 
{
	//  #### 
	// ##  ##
	// ##    
	// ##    
	// ##    
	// ##  ##
	//  #### 
	//       
	0x3E, 0x7F, 0x41, 0x41, 0x63, 0x22, 
};
  
  const uint8_t word_T [6] = 
{
	// ######
	//   ##  
	//   ##  
	//   ##  
	//   ##  
	//   ##  
	//   ##  
	0x01, 0x01, 0x7F, 0x7F, 0x01, 0x01, 
};
  
  const uint8_t word_Y [7] = 
{
	// ##   ##
	//  ## ## 
	//  ## ## 
	//   ###  
	//   ###  
	//   ##   
	// ###    
	//        
	0x41, 0x47, 0x7E, 0x38, 0x1E, 0x07, 0x01,  
};

  const uint8_t word_F [8] = 
{
	//    ##   
	//  ###### 
	// ## ## ##
	// ## ## ##
	// ## ## ##
	//  ###### 
	//    ##   
	//         
	0x1C, 0x3E, 0x22, 0x7F, 0x7F, 0x22, 0x3E, 0x1C, 
};

  const uint8_t word_X [7] = 
{
	// ##   ##
	//  ## ## 
	//   ###  
	//   ###  
	//   ###  
	//  ## ## 
	// ##   ##
	//        
	0x41, 0x63, 0x3E, 0x1C, 0x3E, 0x63, 0x41,
};

  const uint8_t word_TCe [7] = 
{
	// ##  ## 
	// ##  ## 
	// ##  ## 
	// ##  ## 
	// ##  ## 
	// ##  ## 
	// #######
	//      ##
	0x7F, 0x7F, 0x40, 0x40, 0x7F, 0xFF, 0xC0, 
};

  const uint8_t word_4e [5] = 
{
	// ## ##
	// ## ##
	// ## ##
	// ## ##
	//  ####
	//    ##
	//    ##
	//      
	0x0F, 0x1F, 0x10, 0x7F, 0x7F, 
};

  const uint8_t word_She [8] = 
{
	// ## ## ##
	// ## ## ##
	// ## ## ##
	// ## ## ##
	// ## ## ##
	// ## ## ##
	// ########
	//         
	0x7F, 0x7F, 0x40, 0x7F, 0x7F, 0x40, 0x7F, 0x7F, 
};

  const uint8_t word_Sha [9] = 
{
	// ## ## ## 
	// ## ## ## 
	// ## ## ## 
	// ## ## ## 
	// ## ## ## 
	// ## ## ## 
	// #########
	//        ##
	0x7F, 0x7F, 0x40, 0x7F, 0x7F, 0x40, 0x7F, 0xFF, 0xC0, 
};

  const uint8_t word_Tz [7] = 
{
	// ####   
	//   ##   
	//   ##   
	//   #### 
	//   ## ##
	//   ## ##
	//   #### 
	//        
	0x01, 0x01, 0x7F, 0x7F, 0x48, 0x78, 0x30, 
};

  const uint8_t word_Ii [8] = 
{

	// ##    ##
	// ##    ##
	// ##    ##
	// ##### ##
	// ##  ####
	// ##  ####
	// ##### ##
	0x7F, 0x7F, 0x48, 0x48, 0x78, 0x30, 0x7F, 0x7F, 
};

  const uint8_t word_Mz [5] = 
{
	// ##   
	// ##   
	// ##   
	// #### 
	// ## ##
	// ## ##
	// #### 
	//      
	0x7F, 0x7F, 0x48, 0x78, 0x30, 
};

  const uint8_t word_Ee [5] = 
{
	//  ### 
	// ## ##
	//    ##
	//   ###
	//    ##
	// ## ##
	//  ### 
	//      
	0x22, 0x63, 0x49, 0x7F, 0x3E, 
};

  const uint8_t word_Uy [8] = 
{
	// ## #### 
	// ## #  ##
	// ####  ##
	// ####  ##
	// ####  ##
	// ## #  ##
	// ## #### 
	//         
	0x7F, 0x7F, 0x1C, 0x7F, 0x41, 0x41, 0x7F, 0x3E, 
};

  const uint8_t word_Ya [6] = 
{
	//  #####
	// ##  ##
	// ##  ##
	//  #####
	//  ## ##
	//  ## ##
	// ##  ##
	0x46, 0x7F, 0x39, 0x09, 0x7F, 0x7F, 
};

//----------------------------------------ABC_ENG-----------------------------//
  const uint8_t word_D_EN [7] = 
{
	// #####  
	// ##  ## 
	// ##   ##
	// ##   ##
	// ##   ##
	// ##  ## 
	// #####  
	//        
	//        
	0x7F, 0x7F, 0x41, 0x41, 0x63, 0x3E, 0x1C, 
};

  const uint8_t word_F_EN [6] = 
{
	// ######
	// ##    
	// ##    
	// ##### 
	// ##    
	// ##    
	// ##    
	//       
	//       
	0x7F, 0x7F, 0x09, 0x09, 0x09, 0x01,
};

  const uint8_t word_G_EN [7] = 
{
	//   #### 
	//  ##  ##
	// ##     
	// ## ####
	// ##   ##
	//  ##  ##
	//   #### 
	//        
	//        
	0x1C, 0x3E, 0x63, 0x49, 0x49, 0x7B, 0x3A,  
};

  const uint8_t word_I_EN [4] = 
{
	// ####
	//  ## 
	//  ## 
	//  ## 
	//  ## 
	//  ## 
	// ####
	//     
	//     
	0x41, 0x7F, 0x7F, 0x41, 
};

  const uint8_t word_J_EN [5] = 
{
	//   ###
	//    ##
	//    ##
	//    ##
	//    ##
	//    ##
	// #### 
	//      
	//      
	0x40, 0x40, 0x41, 0x7F, 0x3F, 
};

  const uint8_t word_L_EN [6] = 
{
	// ##    
	// ##    
	// ##    
	// ##    
	// ##    
	// ##    
	// ######
	//       
	//       
	0x7F, 0x7F, 0x40, 0x40, 0x40, 0x40, 
};

  const uint8_t word_N_EN [7] = 
{
	// ##   ##
	// ###  ##
	// #### ##
	// ## ####
	// ##  ###
	// ##   ##
	// ##   ##
	//        
	//        
	0x7F, 0x7F, 0x06, 0x0C, 0x18, 0x7F, 0x7F,
};

  const uint8_t word_Q_EN [8] = 
{
	//   ####  
	//  ##  ## 
	// ##    ##
	// ##    ##
	// ##    ##
	//  ##  ## 
	//   ####  
	//     ##  
	//      ###
	0x1C, 0x3E, 0x63, 0x41, 0xC1, 0xE3, 0x3E, 0x1C, 
};

  const uint8_t word_R_EN [6] = 
{
	// ##### 
	// ##  ##
	// ##  ##
	// ##### 
	// ####  
	// ## ## 
	// ##  ##
	//       
	//       
	0x7F, 0x7F, 0x19, 0x39, 0x6F, 0x46,
};

  const uint8_t word_S_EN [6] = 
{
	//  #### 
	// ##  ##
	// ##    
	//  #### 
	//     ##
	// ##  ##
	//  #### 
	//       
	//       
	0x26, 0x6F, 0x49, 0x49, 0x7B, 0x32, 
};

  const uint8_t word_V_EN [7] = 
{
	// ##   ##
	// ##   ##
	// ##   ##
	//  ## ## 
	//  ## ## 
	//   ###  
	//   ###  
	//        
	//        
	0x07, 0x1F, 0x78, 0x60, 0x78, 0x1F, 0x07,  
};
 
  const uint8_t word_U_EN [7] = 
{
	// ##   ##
	// ##   ##
	// ##   ##
	// ##   ##
	// ##   ##
	// ##   ##
	//  ##### 
	0x3F, 0x7F, 0x40, 0x40, 0x40, 0x7F, 0x3F, 
};

  const uint8_t word_W_EN [8] = 
{
	// ##    ##
	// ## ## ##
	// ## ## ##
	// ########
	// ########
	//  ##  ## 
	//  ##  ## 
	//         
	//         
	0x1F, 0x7F, 0x78, 0x1E, 0x1E, 0x78, 0x7F, 0x1F,
};

  const uint8_t word_Y_EN [6] = 
{
	// ##  ##
	// ##  ##
	//  #### 
	//  #### 
	//   ##  
	//   ##  
	//   ##  
	//       
	//       
	0x03, 0x0F, 0x7C, 0x7C, 0x0F, 0x03,
};

  const uint8_t word_Z_EN [6] = 
{
	// ######
	//     ##
	//    ## 
	//   ##  
	//  ##   
	// ##    
	// ######
	//       
	//       
	0x61, 0x71, 0x59, 0x4D, 0x47, 0x43,
};

//-----------------------LCD functions----------------------------------------//

  void WRITE_DATA(uint32_t data)
  {
    
  MDR_PORTA->RXTX |= (data & 0x003F);
  MDR_PORTA->RXTX &= ~(~data & 0x003F);
  MDR_PORTF->RXTX |= ((data>>4) & 0x000C);
  MDR_PORTF->RXTX &= ~(~(data>>4) & 0x000C);
    
  }

 /*
    void vport (uint8_t dataByte)
     {
          union
             {
                   uint8_t ss;
                   struct
                      {
                          unsigned a0 :1;
                          unsigned a1 :1;
                          unsigned a2 :1;
                          unsigned a3 :1;
                          unsigned a4 :1;
                          unsigned a5 :1;
                          unsigned a6 :1;
                          unsigned a7 :1;
                       
                      } byte;         
             } cod;
              
             cod.ss=dataByte;
              
        PORTD.5= cod.byte.a7; PORTD.6= cod.byte.a6; PORTD.7= cod.byte.a5; 
        A4_ADG732 = cod.byte.a4; A3_ADG732 = cod.byte.a3; A2_ADG732 = cod.byte.a2;
        A1_ADG732 = cod.byte.a1; A0_ADG732= cod.byte.a0;
      
     }
 
*/  
  
  
   void LCD_Wr_CMDL (uint8_t cmd){
 
  /*
  uint8_t cmd_sum1 = 0x00, cmd_sum2=0x00; 
  
  uint8_t cmd_bit0, cmd_bit1, cmd_bit2, cmd_bit3, 
          cmd_bit4, cmd_bit5, cmd_bit6, cmd_bit7;
  
  cmd_bit0 = cmd & 1;
  cmd_bit1 = cmd & (1<<1);
  cmd_bit2 = cmd & (1<<2);
  cmd_bit3 = cmd & (1<<3);
  cmd_bit4 = cmd & (1<<4);
  cmd_bit5 = cmd & (1<<5);
  cmd_bit6 = cmd & (1<<6);
  cmd_bit7 = cmd & (1<<7);
  
  cmd_sum1 = cmd_sum1 | (cmd_bit0 & cmd_bit1 & cmd_bit2 & cmd_bit3 & cmd_bit4);
  */
  
  LCD_RW_OFF;     
  LCD_A0_OFF;           //Выдача байта в индикатор как команды
  LCD_E2_OFF;
  LCD_E1_ON;            //Выбрать нужные нужные кристаллы в индикаторе
  WRITE_DATA(cmd);    //Выдать байт на шину данных индикатора
  //MDR_PORTB->RXTX = cmd;    //Выдать байт на шину данных индикатора
  //MDR_PORTA->RXTX = cmd;    //Выдать байт на шину данных индикатора
  //MDR_PORTF->RXTX = ;    //Выдать байт на шину данных индикатора
  delay_3us();		//Это время предустановки адреса (tAW)
  LCD_E_ON;		//Сформировать строб записи в индикатор E=1
  delay_3us();		//Длительность сигнала E=1 (время предустановки данных попало сюда (tDS))
  LCD_E_OFF;		//Сбросить сигнал E
  delay_5us();  	//Минимально допустимый интервал между сигналами E=1
  delay_5us();
}

   void LCD_Wr_CMDR (uint8_t cmd){
  
  LCD_RW_OFF;     
  LCD_A0_OFF;           //Выдача байта в индикатор как команды
  LCD_E1_OFF;
  LCD_E2_ON;            //Выбрать нужные нужные кристаллы в индикаторе
  WRITE_DATA(cmd);    //Выдать байт на шину данных индикатора
  //MDR_PORTA->RXTX = cmd;    //Выдать байт на шину данных индикатора
  //MDR_PORTF->RXTX = cmd>>4;    //Выдать байт на шину данных индикатора
  delay_3us();		//Это время предустановки адреса (tAW)
  LCD_E_ON;		//Сформировать строб записи в индикатор E=1
  delay_3us();		//Длительность сигнала E=1 (время предустановки данных попало сюда (tDS))
  LCD_E_OFF;		//Сбросить сигнал E
  delay_5us();  	//Минимально допустимый интервал между сигналами E=1
  delay_5us();
   }

   void LCD_Wr_DataL (uint8_t dat){
  
  LCD_RW_OFF;     
  LCD_A0_ON;           //Выдача байта в индикатор как команды
  if  (symbol_cnt<10) {LCD_E2_OFF; LCD_E1_ON;}
  else {LCD_E2_ON;LCD_E1_OFF;}
  WRITE_DATA(dat);    //Выдать байт на шину данных индикатора
  //MDR_PORTB->RXTX = dat;    //Выдать байт на шину данных индикатора
  //MDR_PORTA->RXTX = dat;    //Выдать байт на шину данных индикатора
 //MDR_PORTF->RXTX = dat>>4;    //Выдать байт на шину данных индикатора
  delay_3us();		//Это время предустановки адреса (tAW)
  LCD_E_ON;		//Сформировать строб записи в индикатор E=1
  delay_3us();		//Длительность сигнала E=1 (время предустановки данных попало сюда (tDS))
  LCD_E_OFF;		//Сбросить сигнал E
  delay_5us();  	//Минимально допустимый интервал между сигналами E=1
  delay_5us();
}

   void LCD_Wr_DataR (uint8_t dat){
  
  LCD_RW_OFF;     
  LCD_A0_ON;           //Выдача байта в индикатор как команды
  LCD_E1_OFF;
  LCD_E2_ON;            //Выбрать нужные нужные кристаллы в индикаторе
  WRITE_DATA(dat);    //Выдать байт на шину данных индикатора
  //MDR_PORTA->RXTX = dat;    //Выдать байт на шину данных индикатора
  delay_3us();		//Это время предустановки адреса (tAW)
  LCD_E_ON;		//Сформировать строб записи в индикатор E=1
  delay_3us();		//Длительность сигнала E=1 (время предустановки данных попало сюда (tDS))
  LCD_E_OFF;		//Сбросить сигнал E
  delay_5us();  	//Минимально допустимый интервал между сигналами E=1
  delay_5us();
   }

   void LCD_init (void){

    LCD_E_OFF;
    LCD_RES_OFF;
    delay_20us();
    LCD_RES_ON;
    delay_100us();
    LCD_Wr_CMDL(0xC0);
    LCD_Wr_CMDR(0xC0);
    LCD_Wr_CMDL(0x3F);
    LCD_Wr_CMDR(0x3F);
 
}

   void LCD_set_RAM_pageL (uint8_t RAM_page_num){

    LCD_Wr_CMDL(RAM_page_num|0xB8);

}

   void LCD_set_page_AdrL (uint8_t page_adr){

    LCD_Wr_CMDL(0x40|page_adr);
    //Установка текущего адреса для записи 
    //данных в 0 для левого кристалла индикатора
}

   void LCD_set_RAM_pageR (uint8_t RAM_page_num){

    if (RAM_page_num>7){return;} // всего 7 стр в памяти
    LCD_Wr_CMDR(RAM_page_num|0xB8);

}

   void LCD_set_page_AdrR (uint8_t page_adr){

    if (page_adr>63){return;} // всего 63 ячейки памяти
    LCD_Wr_CMDR(0x40|page_adr);
    //Установка текущего адреса для записи 
    //данных в 0 для левого кристалла индикатора
}
   
   void LCD_set_cursor (uint8_t setPoint){
        //LCD_cursor_pos = setPoint;    // сохраняем значение перемнной положения курсора 
     
        //LCD_Wr_DataL(0x00);           // сдвиг курсора -> - центровка
        //LCD_Wr_DataL(0x00);           // сдвиг курсора -> - центровка
        //LCD_Wr_DataL(0x00);           // сдвиг курсора -> - центровка
        symbol_cnt = 0;               // сброс счетчика символов в строке, переход на новую строку
        LCD_set_RAM_pageL(setPoint);  // установка страницы для заполнения левой части экрана
        LCD_set_page_AdrL(0);         // установка адреса пикселя в странице на "2" - смещение для центровки
        
        LCD_set_RAM_pageR(setPoint);  // установка страницы для заполнения правой части экрана
        LCD_set_page_AdrR(0);         // установка адреса пикселя в странице на "2" - смещение для центровки
        
}

   void LCD_full_clear (void){
  
              	for(uint8_t p=0; p<8; p++) {    //Цикл по всем 8-ми страницам индикатора
		LCD_set_RAM_pageL(p);           //Установка текущей страницы для левого кристалла индикатора
		LCD_set_page_AdrL(p);           //Установка текущего адреса для записи данных в 0 для левого кристалла индикатора
		for(uint8_t c=0; c<64; c++) {   //Цикл вывода данных в левую половину индикатора
			LCD_Wr_DataL(0x00);     //Вывод очередного байта в индикатор
		}
		LCD_set_RAM_pageR(p);           //Установка текущей страницы для правого кристалла индикатора
		LCD_set_page_AdrR(p);           //Установка текущего адреса для записи данных в 0 для правого кристалла индикатора
		for(uint8_t c=64; c<128; c++) { //Цикл вывода данных в правую половину индикатора
			LCD_Wr_DataR(0x00);     //Вывод очередного байта в индикатор
		}
               }



}

   void LCD_space (uint8_t SpaceMulCoef){
     for(uint8_t i=1; i<SpaceMulCoef;  i++) {symbol_cnt++;}        //инкремент переменной заполнения экрана 
     if (SpaceMulCoef>19) {SpaceMulCoef = 19;}                      //предотвращеие выхода символа за пределы строки   
     for(uint8_t c=0; c<6*SpaceMulCoef; c++) {LCD_Wr_DataL(0x00);}  //цикл с отрисовкой трех пустых линий по вертикали 
                                                                              
   }
   
   void LCD_Wr_small_single_numL (uint8_t number){
     
     uint8_t t;
     symbol_cnt++; // инкремент переменной заполнения экрана
     
     switch (number) {
                                                         // печать пустой точки - мини пробел
       case 0: for(t=0; t<6; t++) {LCD_Wr_DataL(num_0_small[t]);} LCD_Wr_DataL(0); break;
       case 1: LCD_Wr_DataL(0);LCD_Wr_DataL(0);          // сдвиг единицы чтобы полностью затереть предыдущ. цифру
               for(t=0; t<3; t++) {LCD_Wr_DataL(num_1_small[t]);} LCD_Wr_DataL(0); break; // рисование цифр 0 - 9
       case 2: for(t=0; t<5; t++) {LCD_Wr_DataL(num_2_small[t]);} LCD_Wr_DataL(0); break; 
       case 3: for(t=0; t<5; t++) {LCD_Wr_DataL(num_3_small[t]);} LCD_Wr_DataL(0); break;
       case 4: for(t=0; t<6; t++) {LCD_Wr_DataL(num_4_small[t]);} LCD_Wr_DataL(0); break;
       case 5: for(t=0; t<5; t++) {LCD_Wr_DataL(num_5_small[t]);} LCD_Wr_DataL(0); break;
       case 6: for(t=0; t<5; t++) {LCD_Wr_DataL(num_6_small[t]);} LCD_Wr_DataL(0); break;
       case 7: for(t=0; t<5; t++) {LCD_Wr_DataL(num_7_small[t]);} LCD_Wr_DataL(0); break;
       case 8: for(t=0; t<5; t++) {LCD_Wr_DataL(num_8_small[t]);} LCD_Wr_DataL(0); break;
       case 9: for(t=0; t<5; t++) {LCD_Wr_DataL(num_9_small[t]);} LCD_Wr_DataL(0); break; 
     }
    }
   
   void LCD_Wr_small_num (uint32_t number,uint8_t num_lenght){
   
     
    uint16_t first_num;
    uint32_t third_num, fourth_num, fifth_num, second_num;
    
    switch (num_lenght) {
     
    case 1: LCD_Wr_small_single_numL(number); break;
  
    case 2: first_num = number/10;               LCD_Wr_small_single_numL(first_num);
            number = number-(first_num*10);      LCD_Wr_small_single_numL(number);
      break;
      
    case 3: first_num = number/100;              
              LCD_Wr_small_single_numL(first_num);
            second_num = number-(first_num*100); 
            second_num = second_num/10; 
              LCD_Wr_small_single_numL(second_num);
            number = number-(first_num*100+second_num*10); LCD_Wr_small_single_numL(number);
      break;
      
    case 4: first_num = number/1000;              
              LCD_Wr_small_single_numL(first_num);
            second_num = number-(first_num*1000); 
            second_num = second_num/100; 
              LCD_Wr_small_single_numL(second_num);
            third_num = number-(first_num*1000+second_num*100); 
            third_num = third_num/10; 
              LCD_Wr_small_single_numL(third_num);
            number = number-(first_num*1000+second_num*100+third_num*10); 
              LCD_Wr_small_single_numL(number);
      break;
      
     case 5: first_num = number/10000;              
              LCD_Wr_small_single_numL(first_num);
            second_num = number-(first_num*10000); 
            second_num = second_num/1000; 
              LCD_Wr_small_single_numL(second_num);
            third_num = number-(first_num*10000+second_num*1000); 
            third_num = third_num/100; 
              LCD_Wr_small_single_numL(third_num);
            fourth_num = number-(first_num*10000+second_num*1000+third_num*100);
            fourth_num = fourth_num/10;
              LCD_Wr_small_single_numL(fourth_num);
            number = number-(first_num*10000+second_num*1000+third_num*100+fourth_num*10);
              LCD_Wr_small_single_numL(number);
      break;
      
      case 6: first_num = number/100000;              
              LCD_Wr_small_single_numL(first_num);
            second_num = number-(first_num*100000); 
            second_num = second_num/10000; 
              LCD_Wr_small_single_numL(second_num);
            third_num = number-(first_num*100000+second_num*10000); 
            third_num = third_num/1000; 
              LCD_Wr_small_single_numL(third_num);
            fourth_num = number-(first_num*100000+second_num*10000+third_num*1000);
            fourth_num = fourth_num/100;
              LCD_Wr_small_single_numL(fourth_num);
            fifth_num = number-(first_num*100000+second_num*10000+third_num*1000+fourth_num*100);
            fifth_num = fifth_num/10;
              LCD_Wr_small_single_numL(fifth_num);
            number = number-(first_num*100000+second_num*10000+third_num*1000+fourth_num*100+fifth_num*10);
              LCD_Wr_small_single_numL(number);
      break;
      
    }
   }

   void LCD_wr_num(uint32_t number,uint8_t num_lenght){
     
        LCD_Wr_small_num (number,num_lenght);
        
   }
   
   void LCD_Wr_small_single_wordL (char word){
     
    
    symbol_cnt++;       // инкремент переменной заполнения экрана
     
    switch (word) {
    uint8_t t;                                           // печать пустой точки - мини пробел
      
    case 'А': for(t=0; t<7; t++) {LCD_Wr_DataL(word_A[t]);}  LCD_Wr_DataL(0); break;
    case 'а': for(t=0; t<7; t++) {LCD_Wr_DataL(word_A[t]);}  LCD_Wr_DataL(0); break; 
    case 'Б': for(t=0; t<5; t++) {LCD_Wr_DataL(word_6e[t]);} LCD_Wr_DataL(0); break;
    case 'б': for(t=0; t<5; t++) {LCD_Wr_DataL(word_6e[t]);} LCD_Wr_DataL(0); break;
    case 'В': for(t=0; t<5; t++) {LCD_Wr_DataL(word_B[t]);}  LCD_Wr_DataL(0); break;
    case 'в': for(t=0; t<5; t++) {LCD_Wr_DataL(word_B[t]);}  LCD_Wr_DataL(0); break;
    case 'Г': for(t=0; t<5; t++) {LCD_Wr_DataL(word_Ge[t]);}                 break; // Тут печать пустой точки не нужна
    case 'г': for(t=0; t<5; t++) {LCD_Wr_DataL(word_Ge[t]);}                 break; // Тут печать пустой точки не нужна
    case 'Д': for(t=0; t<8; t++) {LCD_Wr_DataL(word_D[t]);}  LCD_Wr_DataL(0); break;
    case 'д': for(t=0; t<8; t++) {LCD_Wr_DataL(word_D[t]);}  LCD_Wr_DataL(0); break;
    case 'Е': for(t=0; t<5; t++) {LCD_Wr_DataL(word_E[t]);}  LCD_Wr_DataL(0); break;
    case 'е': for(t=0; t<5; t++) {LCD_Wr_DataL(word_E[t]);}  LCD_Wr_DataL(0); break;
    case 'Ё': for(t=0; t<5; t++) {LCD_Wr_DataL(word_E[t]);}  LCD_Wr_DataL(0); break;
    case 'ё': for(t=0; t<5; t++) {LCD_Wr_DataL(word_E[t]);}  LCD_Wr_DataL(0); break;
    case 'Ж': for(t=0; t<10;t++) {LCD_Wr_DataL(word_Je[t]);} LCD_Wr_DataL(0); break;
    case 'ж': for(t=0; t<10;t++) {LCD_Wr_DataL(word_Je[t]);} LCD_Wr_DataL(0); break;
    case 'З': for(t=0; t<5; t++) {LCD_Wr_DataL(word_Z[t]);}  LCD_Wr_DataL(0); break;
    case 'з': for(t=0; t<5; t++) {LCD_Wr_DataL(word_Z[t]);}  LCD_Wr_DataL(0); break;
    case 'И': for(t=0; t<6; t++) {LCD_Wr_DataL(word_I[t]);}  LCD_Wr_DataL(0); break;
    case 'и': for(t=0; t<6; t++) {LCD_Wr_DataL(word_I[t]);}  LCD_Wr_DataL(0); break;
    case 'Й': for(t=0; t<6; t++) {LCD_Wr_DataL(word_I[t]);} LCD_Wr_DataL(0); break;
    case 'й': for(t=0; t<6; t++) {LCD_Wr_DataL(word_I[t]);} LCD_Wr_DataL(0); break;
    case 'К': for(t=0; t<6; t++) {LCD_Wr_DataL(word_K[t]);}  LCD_Wr_DataL(0); break;
    case 'к': for(t=0; t<6; t++) {LCD_Wr_DataL(word_K[t]);}  LCD_Wr_DataL(0); break;
    case 'Л': for(t=0; t<6; t++) {LCD_Wr_DataL(word_L[t]);}  LCD_Wr_DataL(0); break;
    case 'л': for(t=0; t<6; t++) {LCD_Wr_DataL(word_L[t]);}  LCD_Wr_DataL(0); break;
    case 'М': for(t=0; t<8; t++) {LCD_Wr_DataL(word_M[t]);}  LCD_Wr_DataL(0); break;
    case 'м': for(t=0; t<8; t++) {LCD_Wr_DataL(word_M[t]);}  LCD_Wr_DataL(0); break;
    case 'Н': for(t=0; t<6; t++) {LCD_Wr_DataL(word_H[t]);}  LCD_Wr_DataL(0); break;
    case 'н': for(t=0; t<6; t++) {LCD_Wr_DataL(word_H[t]);}  LCD_Wr_DataL(0); break;
    case 'О': for(t=0; t<6; t++) {LCD_Wr_DataL(word_O[t]);}  LCD_Wr_DataL(0); break;
    case 'о': for(t=0; t<6; t++) {LCD_Wr_DataL(word_O[t]);}  LCD_Wr_DataL(0); break;
    case 'П': for(t=0; t<6; t++) {LCD_Wr_DataL(word_Pe[t]);} LCD_Wr_DataL(0); break;
    case 'п': for(t=0; t<6; t++) {LCD_Wr_DataL(word_Pe[t]);} LCD_Wr_DataL(0); break;
    case 'Р': for(t=0; t<6; t++) {LCD_Wr_DataL(word_R[t]);}  LCD_Wr_DataL(0); break;
    case 'р': for(t=0; t<6; t++) {LCD_Wr_DataL(word_R[t]);}  LCD_Wr_DataL(0); break;
    case 'С': for(t=0; t<6; t++) {LCD_Wr_DataL(word_C[t]);}  LCD_Wr_DataL(0); break;
    case 'с': for(t=0; t<6; t++) {LCD_Wr_DataL(word_C[t]);}  LCD_Wr_DataL(0); break;
    case 'Т': for(t=0; t<6; t++) {LCD_Wr_DataL(word_T[t]);}  LCD_Wr_DataL(0); break;
    case 'т': for(t=0; t<6; t++) {LCD_Wr_DataL(word_T[t]);}  LCD_Wr_DataL(0); break;
    case 'У': for(t=0; t<7; t++) {LCD_Wr_DataL(word_Y[t]);}  LCD_Wr_DataL(0); break;
    case 'у': for(t=0; t<7; t++) {LCD_Wr_DataL(word_Y[t]);}  LCD_Wr_DataL(0); break;
    case 'Ф': for(t=0; t<8; t++) {LCD_Wr_DataL(word_F[t]);}  LCD_Wr_DataL(0); break;
    case 'ф': for(t=0; t<8; t++) {LCD_Wr_DataL(word_F[t]);}  LCD_Wr_DataL(0); break;
    case 'Х': for(t=0; t<7; t++) {LCD_Wr_DataL(word_X[t]);}  LCD_Wr_DataL(0); break;
    case 'х': for(t=0; t<7; t++) {LCD_Wr_DataL(word_X[t]);}  LCD_Wr_DataL(0); break;
    case 'Ц': for(t=0; t<7; t++) {LCD_Wr_DataL(word_TCe[t]);}LCD_Wr_DataL(0); break;
    case 'ц': for(t=0; t<7; t++) {LCD_Wr_DataL(word_TCe[t]);}LCD_Wr_DataL(0); break;
    case 'Ч': for(t=0; t<5; t++) {LCD_Wr_DataL(word_4e[t]);} LCD_Wr_DataL(0); break;
    case 'ч': for(t=0; t<5; t++) {LCD_Wr_DataL(word_4e[t]);} LCD_Wr_DataL(0); break;
    case 'Ш': for(t=0; t<8; t++) {LCD_Wr_DataL(word_She[t]);}LCD_Wr_DataL(0); break;
    case 'ш': for(t=0; t<8; t++) {LCD_Wr_DataL(word_She[t]);}LCD_Wr_DataL(0); break;
    case 'Щ': for(t=0; t<9; t++) {LCD_Wr_DataL(word_Sha[t]);}LCD_Wr_DataL(0); break;
    case 'щ': for(t=0; t<9; t++) {LCD_Wr_DataL(word_Sha[t]);}LCD_Wr_DataL(0); break;
    case 'Ь': for(t=0; t<5; t++) {LCD_Wr_DataL(word_Mz[t]);} LCD_Wr_DataL(0); break;
    case 'ь': for(t=0; t<5; t++) {LCD_Wr_DataL(word_Mz[t]);} LCD_Wr_DataL(0); break;
    case 'Ъ': for(t=0; t<7; t++) {LCD_Wr_DataL(word_Tz[t]);} LCD_Wr_DataL(0); break;
    case 'ъ': for(t=0; t<7; t++) {LCD_Wr_DataL(word_Tz[t]);} LCD_Wr_DataL(0); break;
    case 'Ы': for(t=0; t<8; t++) {LCD_Wr_DataL(word_Ii[t]);} LCD_Wr_DataL(0); break;
    case 'ы': for(t=0; t<8; t++) {LCD_Wr_DataL(word_Ii[t]);} LCD_Wr_DataL(0); break;
    case 'Э': for(t=0; t<5; t++) {LCD_Wr_DataL(word_Ee[t]);} LCD_Wr_DataL(0); break;
    case 'э': for(t=0; t<5; t++) {LCD_Wr_DataL(word_Ee[t]);} LCD_Wr_DataL(0); break;
    case 'Ю': for(t=0; t<8;t++) {LCD_Wr_DataL(word_Uy[t]);}  LCD_Wr_DataL(0); break;
    case 'ю': for(t=0; t<8;t++) {LCD_Wr_DataL(word_Uy[t]);}  LCD_Wr_DataL(0); break;
    case 'Я': for(t=0; t<6; t++) {LCD_Wr_DataL(word_Ya[t]);} LCD_Wr_DataL(0); break;
    case 'я': for(t=0; t<6; t++) {LCD_Wr_DataL(word_Ya[t]);} LCD_Wr_DataL(0); break;
  
   
    case '>': for(t=0; t<6; t++) {LCD_Wr_DataL(great_sign[t]);}               break; 
    case '<': for(t=0; t<6; t++) {LCD_Wr_DataL(less_sign[t]);}                break;
      
    case '=': for(t=0; t<6; t++) {LCD_Wr_DataL(eq_sign[t]);} LCD_Wr_DataL(0); break;
    case '+': for(t=0; t<5; t++) {LCD_Wr_DataL(plus_sign[t]);}LCD_Wr_DataL(0);break; 
    case '-': for(t=0; t<5; t++) {LCD_Wr_DataL(minus_sign[t]);}LCD_Wr_DataL(0);break;
    case ':': for(t=0; t<3; t++) {LCD_Wr_DataL(dvoetoch[t]);}                  break;
    case '!': for(t=0; t<3; t++) {LCD_Wr_DataL(vosklit_zn[t]);}                break;
    case '?': for(t=0; t<5; t++) {LCD_Wr_DataL(vopros_zn[t]);}                 break;
    case '_': for(t=0; t<7; t++) {LCD_Wr_DataL(sign__[t]);}                    break; 
    case '*': for(t=0; t<7; t++) {LCD_Wr_DataL(zvezd_zn[t]);} break;
    case '/': for(t=0; t<5; t++) {LCD_Wr_DataL(sign_t2[t]);} LCD_Wr_DataL(0); break; 
    //case '°': for(t=0; t<6; t++) {LCD_Wr_DataL(sign_degree[t]);}              break; 
    case '.': for(t=0; t<3; t++) {LCD_Wr_DataL(sign_dot[t]);}                 break; 
    case ',': for(t=0; t<3; t++) {LCD_Wr_DataL(zap_zn[t]);}                   break; 

    case 'A': for(t=0; t<7; t++) {LCD_Wr_DataL(word_A[t]);}  LCD_Wr_DataL(0); break; //eng
    case 'a': for(t=0; t<7; t++) {LCD_Wr_DataL(word_A[t]);}  LCD_Wr_DataL(0); break; //eng
    case 'B': for(t=0; t<5; t++) {LCD_Wr_DataL(word_B[t]);}  LCD_Wr_DataL(0); break;
    case 'b': for(t=0; t<5; t++) {LCD_Wr_DataL(word_B[t]);}  LCD_Wr_DataL(0); break;
    case 'C': for(t=0; t<6; t++) {LCD_Wr_DataL(word_C[t]);}  LCD_Wr_DataL(0); break;
    case 'c': for(t=0; t<6; t++) {LCD_Wr_DataL(word_C[t]);}  LCD_Wr_DataL(0); break;
    case 'D': for(t=0; t<7; t++) {LCD_Wr_DataL(word_D_EN[t]);}  LCD_Wr_DataL(0); break;
    case 'd': for(t=0; t<7; t++) {LCD_Wr_DataL(word_D_EN[t]);}  LCD_Wr_DataL(0); break;
    case 'E': for(t=0; t<5; t++) {LCD_Wr_DataL(word_E[t]);}  LCD_Wr_DataL(0); break;
    case 'e': for(t=0; t<5; t++) {LCD_Wr_DataL(word_E[t]);}  LCD_Wr_DataL(0); break;
    case 'F': for(t=0; t<6; t++) {LCD_Wr_DataL(word_F_EN[t]);}  LCD_Wr_DataL(0); break;
    case 'f': for(t=0; t<6; t++) {LCD_Wr_DataL(word_F_EN[t]);}  LCD_Wr_DataL(0); break;
    case 'G': for(t=0; t<7; t++) {LCD_Wr_DataL(word_G_EN[t]);}  LCD_Wr_DataL(0); break;
    case 'g': for(t=0; t<7; t++) {LCD_Wr_DataL(word_G_EN[t]);}  LCD_Wr_DataL(0); break;    
    case 'H': for(t=0; t<6; t++) {LCD_Wr_DataL(word_H[t]);}  LCD_Wr_DataL(0); break;
    case 'h': for(t=0; t<6; t++) {LCD_Wr_DataL(word_H[t]);}  LCD_Wr_DataL(0); break;
    case 'I': for(t=0; t<4; t++) {LCD_Wr_DataL(word_I_EN[t]);}  LCD_Wr_DataL(0); break;
    case 'i': for(t=0; t<4; t++) {LCD_Wr_DataL(word_I_EN[t]);}  LCD_Wr_DataL(0); break;   
    case 'J': for(t=0; t<5; t++) {LCD_Wr_DataL(word_J_EN[t]);}  LCD_Wr_DataL(0); break;
    case 'j': for(t=0; t<5; t++) {LCD_Wr_DataL(word_J_EN[t]);}  LCD_Wr_DataL(0); break;
    case 'K': for(t=0; t<6; t++) {LCD_Wr_DataL(word_K[t]);}  LCD_Wr_DataL(0); break;
    case 'k': for(t=0; t<6; t++) {LCD_Wr_DataL(word_K[t]);}  LCD_Wr_DataL(0); break;
    case 'L': for(t=0; t<6; t++) {LCD_Wr_DataL(word_L_EN[t]);}  LCD_Wr_DataL(0); break;
    case 'l': for(t=0; t<6; t++) {LCD_Wr_DataL(word_L_EN[t]);}  LCD_Wr_DataL(0); break;
    case 'M': for(t=0; t<8; t++) {LCD_Wr_DataL(word_M[t]);}  LCD_Wr_DataL(0); break;   
    case 'm': for(t=0; t<8; t++) {LCD_Wr_DataL(word_M[t]);}  LCD_Wr_DataL(0); break;
    case 'N': for(t=0; t<7; t++) {LCD_Wr_DataL(word_N_EN[t]);}  LCD_Wr_DataL(0); break;
    case 'n': for(t=0; t<7; t++) {LCD_Wr_DataL(word_N_EN[t]);}  LCD_Wr_DataL(0); break;    
    case 'O': for(t=0; t<6; t++) {LCD_Wr_DataL(word_O[t]);}  LCD_Wr_DataL(0); break;
    case 'o': for(t=0; t<6; t++) {LCD_Wr_DataL(word_O[t]);}  LCD_Wr_DataL(0); break;
    case 'P': for(t=0; t<6; t++) {LCD_Wr_DataL(word_R[t]);}  LCD_Wr_DataL(0); break;
    case 'p': for(t=0; t<6; t++) {LCD_Wr_DataL(word_R[t]);}  LCD_Wr_DataL(0); break;
    case 'Q': for(t=0; t<8; t++) {LCD_Wr_DataL(word_Q_EN[t]);}  LCD_Wr_DataL(0); break;
    case 'q': for(t=0; t<8; t++) {LCD_Wr_DataL(word_Q_EN[t]);}  LCD_Wr_DataL(0); break;   
    case 'R': for(t=0; t<6; t++) {LCD_Wr_DataL(word_R_EN[t]);}  LCD_Wr_DataL(0); break;
    case 'r': for(t=0; t<6; t++) {LCD_Wr_DataL(word_R_EN[t]);}  LCD_Wr_DataL(0); break; 
    case 'S': for(t=0; t<6; t++) {LCD_Wr_DataL(word_S_EN[t]);}  LCD_Wr_DataL(0); break;
    case 's': for(t=0; t<6; t++) {LCD_Wr_DataL(word_S_EN[t]);}  LCD_Wr_DataL(0); break;
    case 'T': for(t=0; t<6; t++) {LCD_Wr_DataL(word_T[t]);}  LCD_Wr_DataL(0); break;
    case 't': for(t=0; t<6; t++) {LCD_Wr_DataL(word_T[t]);}  LCD_Wr_DataL(0); break;
    case 'U': for(t=0; t<7; t++) {LCD_Wr_DataL(word_U_EN[t]);}  LCD_Wr_DataL(0); break;
    case 'u': for(t=0; t<7; t++) {LCD_Wr_DataL(word_U_EN[t]);}  LCD_Wr_DataL(0); break;    
    case 'V': for(t=0; t<7; t++) {LCD_Wr_DataL(word_V_EN[t]);}  LCD_Wr_DataL(0); break;
    case 'v': for(t=0; t<7; t++) {LCD_Wr_DataL(word_V_EN[t]);}  LCD_Wr_DataL(0); break;
    case 'W': for(t=0; t<8; t++) {LCD_Wr_DataL(word_W_EN[t]);}  LCD_Wr_DataL(0); break;
    case 'w': for(t=0; t<8; t++) {LCD_Wr_DataL(word_W_EN[t]);}  LCD_Wr_DataL(0); break;
    case 'X': for(t=0; t<7; t++) {LCD_Wr_DataL(word_X[t]);}  LCD_Wr_DataL(0); break;
    case 'x': for(t=0; t<7; t++) {LCD_Wr_DataL(word_X[t]);}  LCD_Wr_DataL(0); break;   
    case 'Y': for(t=0; t<6; t++) {LCD_Wr_DataL(word_Y_EN[t]);}  LCD_Wr_DataL(0); break;
    case 'y': for(t=0; t<6; t++) {LCD_Wr_DataL(word_Y_EN[t]);}  LCD_Wr_DataL(0); break; 
    case 'Z': for(t=0; t<6; t++) {LCD_Wr_DataL(word_Z_EN[t]);}  LCD_Wr_DataL(0); break;
    case 'z': for(t=0; t<6; t++) {LCD_Wr_DataL(word_Z_EN[t]);}  LCD_Wr_DataL(0); break;       
    }
   }
 
   void LCD_print(char* full_word){
   
   uint8_t word_lenght = 0;                     //инициализация переменной размера слова
   //uint8_t temp = 0;                           //инициализация переменной проверки переполн. строки
   
   for(uint8_t i = 0; i<25; i++){               //цикл определения длины слова
     if(full_word[i]==0) {break;}               //выход из цикла конце слова 
     word_lenght++;                             //инкремент перемнной размера слова
   }

   for(uint8_t j = 0; j<word_lenght; j++){      //цикл отрисовки всего слова по буквам
     if (full_word[j]== ' '){LCD_space(1);};    //если текущий симлол это пробел, рисуем пробел  
     LCD_Wr_small_single_wordL(full_word[j]); 
   }
   }
     
   void LCD_draw_ktes (void){
     
  const uint8_t ktes [8][128] =
{
	// ###################################################################################################### ###  ####################
	// #####################################################################################################  ###   ###################
	// ##                   ####                              ####                                           #####                   ##
	// ##                    ##                                ##                                            #####                   ##
	// ##                    ##     ######################     ##                                            #####                   ##
	// ##                    ##     ######################     ##                                            ## ###                  ##
	// ##                    ##     ##                  ##     ##                                           ### ###                  ##
	// ##                    #########                  #########                                           ###  ##                  ##
	// ##                    #########                  #########                                           ###  ###                 ##
	// ##                           ##                  ##                                                  ##   ###                 ##
	// ##                           ######################                                                 ###    ##                 ##
	// ##                           ######################                                                 ###    ##                 ##
	// ##                                                                                                  ##     ###                ##
	// ##                                                                                                 ###      ##                ##
	// ##                                                                                                 ###      ###########       ##
	// ##                                              ##                                        #############################       ##
	// ##       ###                         ########################                             #####################   #####       ##
	// ##       ###       ##                ########################                              ###    ###            ####         ##
	// ##      ####      ###                #########################                             ###                  ####          ##
	// ##      ####    #####                ######   ######    ######                              ####               ####           ##
	// ##      ####   ######                         ####      ###                                  ####              ###            ##
	// ##      ####   ######                         ####             #######        ######          ####     ##      ##             ##
	// ##      #### ######                           ####             ########       #######          ###     ##        ##           ##
	// ##      ##########       ##                   ####                 #####      #######                  ###      ###           ##
	// ##      #########        ##       ##          ####                   ###     ####  ##                   ####   ###            ##
	// ##      ########         ##     ####          ####               #######     ###                         #### ####            ##
	// ##      #######          ###   #####         #####            ###########    ###                          #######             ##
	// ##      ######           ###  ######         #####           ############   ###                            #####              ##
	// ##      ########         ###  ######         #####           #####   ####   ###                             ####              ##
	// ##      #########        ### #######         #####                   ####   ###                            ####               ##
	// ##      ##########       ###########        ######                  ####    ##                            ####  #######       ##
	// ##      ##########       ###########        ######                 #####    ##     ####                  ####   #######       ##
	// ##     ############      ####### ###       #######           ##########     ###   #####                 ####    ##            ##
	// ##     ###### ######     ######  ###       #######           #########      #########                   ###    ###            ##
	// ##      #####  ######    #####   ###       #######            #######       ########                    ##     ######         ##
	// ##      #####    ####    #####   ###       ######                            ######                            #######        ##
	// ##      #####    ####    ###     ###       ######                                                             ###   ###       ##
	// ##      #####     ###    ###     ###       ######                                                             ###   ###       ##
	// ##        ##      ###                      ## ##                                                              ##     ##       ##
	// ##                                                                                                            ##  #####       ##
	// ###                                                                                                           ########        ##
	// ############                                                                                                  ######          ##
	// ############                                                                                                                  ##
	// ###       ##                 ##############                                                                                   ##
	// ##        ##                 #       ##   #                                                                    ##   ##        ##
	// ##        ##                 # ##    ##   #                                    ##       ##                     ##   ##        ##
	// ##  ##############           # ##   ###   #                                    ####     ##                    ###   ##        ##
	// ##  ##############           # ##  ###    #                                    #####    ##                    ###   ##        ##
	// ##                           # ##  ##     #                                    ## ####  ##                   #########        ##
	// ##                           # ## ##      #                                    ##  #### ##                   ########         ##
	// ##                           # #####      #                                    ##   ######                   ##   ###         ##
	// ##  ##############           ######       #                         ##################################       ##   ##   ###    ##
	// ##  ##############           ######       #                         ##################################       ##  ###   ####   ##
	// ##        ##                 # #####   ## #                         ##         ##   ######          ##           ###  #####   ##
	// ##        ##                 # ## ###  ## #                         ##         ##  #### ##          ##           ##   #####   ##
	// ###       ##                 # ##  ### ## #                         ##         ## ###   ##          ##               ### ##   ##
	// ############                 # ##    #### #                         ##         #####    ##          ##               ##  ##   ##
	// ############                 # ##  ###### #                         ##         ####     ##          ##              #######   ##
	// ###                          #     ###### #                         ##         ##       ##          ##              #######   ##
	// ##                           #            #                         ##                              ##              ##   ##   ##
	// ##                           ##############                         ##                             ####             ##   ##   ##
	// ##                                                                 ####                            ####                       ##
	// ################################################################################################################################
	// ################################################################################################################################
	0xFF, 0xFF, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x07, 0xFF, 0xFF, 0x87, 0x83, 0x83, 0x83, 0x83, 0xF3, 0xF3, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0xF3, 0xF3, 0x83, 0x83, 0x83, 0x83, 0x87, 0xFF, 0xFF, 0x07, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0xC1, 0xFC, 0xFF, 0x1F, 0x7F, 0xFC, 0xE0, 0x01, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0xFF, 0xFF, 
	0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x0F, 0x0F, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x8C, 0x8F, 0x0F, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0xE0, 0xFC, 0xFF, 0x8F, 0x81, 0x80, 0x80, 0x83, 0x9F, 0xFF, 0xF0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 
	0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFC, 0xFF, 0xFF, 0xFF, 0x80, 0xC0, 0xC0, 0xF0, 0xF8, 0xF8, 0x7C, 0x3E, 0x3E, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x07, 0x07, 0x07, 0xFF, 0xFF, 0xFF, 0xFF, 0x0F, 0x0F, 0x07, 0x07, 0x07, 0x07, 0x1F, 0x1F, 0x1F, 0x0F, 0x0F, 0x0C, 0x00, 0x60, 0x60, 0x60, 0x60, 0xE0, 0xE0, 0xE0, 0xC0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x07, 0x0F, 0x1F, 0x39, 0x79, 0x71, 0x61, 0x03, 0x03, 0x03, 0x01, 0x01, 0xE1, 0xE1, 0x81, 0x01, 0x01, 0x01, 0x01, 0x01, 0x38, 0xBC, 0xDE, 0xCF, 0x07, 0x03, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 
	0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF7, 0xF3, 0xE1, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFC, 0xC0, 0xE0, 0xF8, 0xFC, 0xFE, 0xFE, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0xFC, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x1C, 0x1C, 0x1C, 0x1E, 0x0E, 0x8E, 0xCE, 0xFF, 0xFF, 0xFF, 0x3C, 0x00, 0x00, 0x00, 0xF8, 0xFF, 0x3F, 0x07, 0x01, 0x00, 0x00, 0x81, 0x81, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x83, 0xC7, 0xEF, 0xFE, 0x7C, 0x3E, 0x1F, 0xC7, 0xC3, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 
	0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x3F, 0x3F, 0x7F, 0x7F, 0x3F, 0x01, 0x03, 0x07, 0x07, 0x1F, 0x7F, 0x7E, 0x7C, 0x00, 0x00, 0x00, 0x00, 0x3F, 0x3F, 0x3F, 0x0F, 0x0F, 0x03, 0x01, 0x00, 0x3F, 0x3F, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7F, 0x7F, 0x3F, 0x7F, 0x7F, 0x3F, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x0F, 0x0F, 0x0E, 0x0E, 0x0E, 0x0F, 0x07, 0x03, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x07, 0x03, 0x01, 0x00, 0x00, 0xF0, 0xFE, 0x3F, 0x0F, 0x8C, 0x8C, 0xBC, 0xF8, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 
	0xFF, 0xFF, 0x0F, 0x06, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6, 0xFE, 0xFE, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF8, 0x08, 0xE8, 0xE8, 0x08, 0x08, 0x88, 0xC8, 0xF8, 0x78, 0x08, 0x08, 0x08, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0xE0, 0xC0, 0xC0, 0x80, 0x00, 0x00, 0x00, 0x00, 0xE0, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC3, 0xF3, 0xF3, 0x03, 0x03, 0x03, 0xF1, 0xF1, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 
	0xFF, 0xFF, 0x80, 0x00, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0xF8, 0xF8, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x18, 0xFF, 0xFF, 0x3C, 0x7E, 0xE7, 0xC1, 0x80, 0x00, 0xE0, 0xE0, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF8, 0xF8, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0xFF, 0xFF, 0x18, 0x99, 0xDB, 0xFF, 0x7F, 0x7E, 0x3C, 0xFF, 0xFF, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0xF8, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0x1F, 0x03, 0x03, 0x73, 0x7F, 0x3F, 0x07, 0x81, 0xE0, 0xF8, 0x78, 0xF8, 0xF0, 0x00, 0x00, 0x00, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xC7, 0xC3, 0xC3, 0xC3, 0xC3, 0xC3, 0xC3, 0xC3, 0xC3, 0xC3, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xDF, 0xD0, 0xD3, 0xD3, 0xD0, 0xD0, 0xD6, 0xD6, 0xD7, 0xD7, 0xD7, 0xD7, 0xD0, 0xDF, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xE0, 0xFF, 0xFF, 0xE0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC7, 0xC7, 0xC3, 0xC3, 0xC1, 0xC0, 0xC0, 0xC0, 0xC0, 0xC7, 0xC7, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xF0, 0xFF, 0xFF, 0xF0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xDE, 0xDF, 0xC7, 0xC6, 0xC6, 0xDF, 0xDF, 0xC0, 0xC0, 0xC0, 0xFF, 0xFF, 
}; 
                for(uint8_t p=0; p<8; p++) {//Цикл по всем 8-ми страницам индикатора
		LCD_set_RAM_pageL(p);//Установка текущей страницы для левого кристалла индикатора
		LCD_set_page_AdrL(0);//Установка текущего адреса для записи данных в 0 для левого кристалла индикатора
		for(uint8_t c=0; c<64; c++) {//Цикл вывода данных в левую половину индикатора
			LCD_Wr_DataL(ktes[p][c]);//Вывод очередного байта в индикатор
		}
                }
                
                for(uint8_t p=0; p<8; p++) {//Цикл по всем 8-ми страницам индикатора
		LCD_set_RAM_pageR(p);//Установка текущей страницы для левого кристалла индикатора
		LCD_set_page_AdrR(0);//Установка текущего адреса для записи данных в 0 для левого кристалла индикатора
		for(uint8_t c=64; c<128; c++) {//Цикл вывода данных в левую половину индикатора
		LCD_Wr_DataR(ktes[p][c]);//Вывод очередного байта в индикатор
		}
                }
                               
    }
   
//-----------------------End of LCD functions----------------------------------//

//-----------------------END OF LIBRARY----------------------------------------------//