#include "xc.h"
#include "Fuses.h"
#include <p24HJ128GP506.h>
#define FCY 40000000UL
#include <libpic30.h>
#define _ISR_PSV __attribute__((__interrupt__, __auto_psv__))

#define FP 40000000
#define BAUDRATE 115200
#define U1BRGVAL ((FP/BAUDRATE)/16)-1

// SPI defines
#define CS_1_ON LATCbits.LATC2=0
#define CS_1_OFF LATCbits.LATC2=1
#define CS_2_ON LATBbits.LATB5=0
#define CS_2_OFF LATBbits.LATB5=1
//Program defines

#define ADDR0 PORTGbits.RG13
#define ADDR1 PORTGbits.RG12
#define ADDR2 PORTGbits.RG14
#define ADDR3 PORTGbits.RG0
// MAIN
  unsigned int delay_chanel_1_LSB = 100;   // Значение задержки канала 1 младшие 16 бит
  unsigned int delay_chanel_1_MSB = 100;   // Значение задержки канала 1 старшие 16 бит
  unsigned int width_chanel_1_LSB = 50;    // Значение ширины импульса канала 1 младшие 16 бит
  unsigned int width_chanel_1_MSB = 200;   // Значение ширины импульса канала 1 старшие 16 бит
  unsigned int delay_chanel_2_LSB = 150;   // Значение задержки канала 2 младшие 16 бит
  unsigned int delay_chanel_2_MSB = 150;   // Значение задержки канала 2 старшие 16 бит
  unsigned int width_chanel_2_LSB = 800;   // Значение ширины импульса канала 2 младшие 16 бит
  unsigned int width_chanel_2_MSB = 800;   // Значение ширины импульса канала 2 старшие 16 бит
  unsigned int delay_chanel_3_LSB = 400;   // Значение задержки канала 3 младшие 16 бит
  unsigned int delay_chanel_3_MSB = 400;   // Значение задержки канала 3 старшие 16 бит
  unsigned int width_chanel_3_LSB = 100;   // Значение ширины импульса канала 3 младшие 16 бит
  unsigned int width_chanel_3_MSB = 100;   // Значение ширины импульса канала 3 старшие 16 бит
  unsigned int delay_chanel_4_LSB = 100;   // Значение задержки канала 4 младшие 16 бит
  unsigned int delay_chanel_4_MSB = 100;   // Значение задержки канала 4 старшие 16 бит
  unsigned int width_chanel_4_LSB = 100;   // Значение ширины импульса канала 4 младшие 16 бит
  unsigned int width_chanel_4_MSB = 100;   // Значение ширины импульса канала 4 старшие 16 бит
  unsigned int delay_chanel_5_LSB = 100;   // Значение задержки канала 1 младшие 16 бит
  unsigned int delay_chanel_5_MSB = 100;   // Значение задержки канала 1 старшие 16 бит
  unsigned int width_chanel_5_LSB = 50;    // Значение ширины импульса канала 1 младшие 16 бит
  unsigned int width_chanel_5_MSB = 200;   // Значение ширины импульса канала 1 старшие 16 бит
  unsigned int delay_chanel_6_LSB = 150;   // Значение задержки канала 2 младшие 16 бит
  unsigned int delay_chanel_6_MSB = 150;   // Значение задержки канала 2 старшие 16 бит
  unsigned int width_chanel_6_LSB = 800;   // Значение ширины импульса канала 2 младшие 16 бит
  unsigned int width_chanel_6_MSB = 800;   // Значение ширины импульса канала 2 старшие 16 бит
  unsigned int delay_chanel_7_LSB = 400;   // Значение задержки канала 3 младшие 16 бит
  unsigned int delay_chanel_7_MSB = 400;   // Значение задержки канала 3 старшие 16 бит
  unsigned int width_chanel_7_LSB = 100;   // Значение ширины импульса канала 3 младшие 16 бит
  unsigned int width_chanel_7_MSB = 100;   // Значение ширины импульса канала 3 старшие 16 бит
  unsigned int delay_chanel_8_LSB = 100;   // Значение задержки канала 4 младшие 16 бит
  unsigned int delay_chanel_8_MSB = 100;   // Значение задержки канала 4 старшие 16 бит
  unsigned int width_chanel_8_LSB = 100;   // Значение ширины импульса канала 4 младшие 16 бит
  unsigned int width_chanel_8_MSB = 100;   // Значение ширины импульса канала 4 старшие 16 бит
  //DEFINES CONTROL REGISTER 
  unsigned int enable_chanel_1; // EN 1 chanel
  unsigned int invert_chanel_1; // INV 1 chanel
  unsigned int enable_chanel_2; // EN 2 chanel
  unsigned int invert_chanel_2; // INV 2 chanel
  unsigned int enable_chanel_3; // EN 3 chanel
  unsigned int invert_chanel_3; // INV 3 chanel
  unsigned int enable_chanel_4; // EN 1 chanel
  unsigned int invert_chanel_4; // EN 1 chanel
  unsigned int Control_1;       // Control register CPLD_1
  unsigned int enable_chanel_5; // EN 1 chanel
  unsigned int invert_chanel_5; // INV 1 chanel
  unsigned int enable_chanel_6; // EN 2 chanel
  unsigned int invert_chanel_6; // INV 2 chanel
  unsigned int enable_chanel_7; // EN 3 chanel
  unsigned int invert_chanel_7; // INV 3 chanel
  unsigned int enable_chanel_8; // EN 1 chanel
  unsigned int invert_chanel_8; // EN 1 chanel
  unsigned int Control_2;       // Control register CPLD_1
  unsigned int start_DIR; 
  unsigned int clk_DIR; 
  unsigned int start_en; 
  unsigned int start_inv;
  unsigned int delay_start_LSB;
  unsigned int delay_start_MSB;
  unsigned int width_start_LSB;
  unsigned int width_start_MSB;
  unsigned int fl_start = 0;
  
  unsigned int SPI_BUF_MISO = 0;
  

#include "dialtek_modbus.h" 

//=============================================================================    
    void Oscillator_init ()
    {
        // FCY=FOSC/2, FOSC= FIN*M/(N1*N2) 
        CLKDIVbits.PLLPRE = 0;      // 0 - divider N1 = 2
        PLLFBD = 30;                // multiplier M = PLLFBD + 2
        CLKDIVbits.PLLPOST = 0;     // 0 - divider N2 = 2
        
        OSCTUN=0;                   // 000000 = Center frequency (7.37 MHz nominal)
        RCONbits.SWDTEN=0;          // Disable Watch Dog Timer
        
        while(OSCCONbits.LOCK !=1) {};   // 1 = Indicates that PLL is in lock, or PLL start-up timer is satisfied
                                        // 0 = Indicates that PLL is out of lock, start-up timer is in progress or PLL is disabled
        //note: FOSC= 10 MHz * 32/(2*2) = 80 MHz, FCY = 80/2
    }   
    //SPI
    void SPI2_init ()
    {
        // A series of 8/16 clock pulses shift out 8/16 bits of transmit data from Shift Register SPIxSR
        // to the SDOx pin and simultaneously shift the data at the SDIx pin into SPIxSR.
        // SPI interrupt
        // When the ongoing transmit and receive operations are completed, the content of the
        // SPIx Shift register (SPIxSR) is moved to the SPIx Receive Buffer (SPIxRXB).
        // c) The SPIx Receive Buffer Full Status (SPIRBF) bit in the SPIx Status and Control
        // (SPIxSTAT<0>) register is set by the module, indicating that the receive buffer is full.
        // Once the SPIxBUF register is read by the user code, the hardware clears the SPIRBF
        // bit.
        SPI2STATbits.SPIEN = 0;         // Turn off spi module before initialization 
        // SPI2CON1 Register Settings:
        SPI2CON1bits.DISSCK = 0;        //Internal Serial Clock is Enabled
        SPI2CON1bits.DISSDO = 0;        //SDOx pin is controlled by the module
        SPI2CON1bits.MODE16 = 1;        //Communication is word-wide (16 bits)
        SPI2CON1bits.SMP = 0;           //Input Data is sampled at the middle of data output time
        SPI2CON1bits.CKE = 0;           //Serial output data changes on transition from
        SPI2CON1bits.CKP = 0;           //Serial output data changes on transition from
        SPI2CON1bits.PPRE = 2;          //Primary prescale 1:1
        SPI2CON1bits.SPRE = 4;          //Secondary prescale 1:1
        // SPI2CON2 Register Settings:
        SPI2CON1bits.MSTEN = 1;         //Master Mode Enabled
        SPI2CON2bits.FRMEN = 0;         // CS(SS) Support bit; 0 = Framed SPIx support disable 
        SPI2CON2bits.SPIFSD = 0;        // CS(SS) Pulse Direction; 0 = Frame sync pulse output (master)
        SPI2CON2bits.FRMPOL = 1;        // CS(SS) Sync Pulse Polarity bit; 0 = Frame sync pulse is active-low
        SPI2CON2bits.FRMDLY = 0;       // 1 = Frame sync pulse coincides with first bit clock
                                          
        
        SPI2STATbits.SPIEN = 1;         //Enable SPI Module
        SPI2BUF = 0x0000;               //Write data to be transmitted
                                        //Interrupt Controller Settings
    }
    void SPI2_PUT_int (unsigned int buf)               
    {
         __delay_us(10);
         // LATCbits.LATC2 = 0;
         SPI2STATbits.SPIEN = 1;
         SPI2BUF = buf;        
         __delay_us(10);
        }
    unsigned int SPI2_GET_int ()
    {
        unsigned int buf = 0;
        
   // Clear BF
   // Clear interrupt flag
   //SSPBUF = 0x00; // initiate bus cycle
   // wait until cycle complete
        
   SPI2BUF = 0x0000;
      
      if(SPI2STATbits.SPIRBF)  
      {
         
          SPI2STATbits.SPIROV = 0;
          buf = SPI2BUF;
      }
        return buf; 
        __delay_us(10);
        
    }
    void Modbus_SPI_R_WR (unsigned int hold_reg_data, unsigned int  hold_reg_addr, unsigned char R_Wr, unsigned char counter) 		// функция отправки по SPI МК >>> ПЛИС  
	{ // прогоняется 2 раза в цикле по counter

			unsigned int Data_buff = 0;
            unsigned int SPI_frame = 0x0000;                      // создали переменную кадра SPI
			unsigned int MSByte_data = 0x0000;
            unsigned int LSByte_data = 0x0000;                          
			unsigned int SPI_addr = 0x0000;
            unsigned int SPI_addr_buf = 0x0000;
			Data_buff = 0x0000;  
            Data_buff = hold_reg_data;
            MSByte_data = Data_buff >> 8;                 // выделили старший байт слова
            Data_buff = hold_reg_data;
            LSByte_data = Data_buff & 0x00ff;             // выделили младший байт слова
            
            switch(counter)	
				{
				case 1 : // MSByte_data = 0;
                         // LSByte_data = 0;
                         
                          SPI_frame = LSByte_data;                          // заполняем младшие 8 бит данными
                
				break;
				case 2 : SPI_frame = MSByte_data;			// младший байт на 1 итерации, старший на 2-ой
				break;
				}            
            
                 switch(hold_reg_addr)	
                        {
                            case 0 : SPI_addr = (hold_reg_addr * 2) + counter ;
                            break;
                            case 1 : SPI_addr = (hold_reg_addr * 2) + counter ;			
                            break;
                            case 2 : SPI_addr = (hold_reg_addr * 2) + counter ;
                            break;
                            case 3 : SPI_addr = (hold_reg_addr * 2) + counter ;			
                            break;
                            case 4 : SPI_addr = (hold_reg_addr * 2) + counter ;
                            break;
                            case 5 : SPI_addr = (hold_reg_addr * 2) + counter ;			
                            break;
                            case 6 : SPI_addr = (hold_reg_addr * 2) + counter ;
                            break;
                            case 7 : SPI_addr = (hold_reg_addr * 2) + counter ;			
                            break;
                            case 8 : SPI_addr = (hold_reg_addr * 2) + counter ;
                            break;
                            case 9 : SPI_addr = (hold_reg_addr * 2) + counter ;			
                            break;
                            case 10 : SPI_addr = (hold_reg_addr * 2) + counter ;
                            break;
                            case 11 : SPI_addr = (hold_reg_addr * 2) + counter ;			
                            break;
                            case 12 : SPI_addr = (hold_reg_addr * 2) + counter ;
                            break;
                            case 13 : SPI_addr = (hold_reg_addr * 2) + counter ;			
                            break;
                            case 14 : SPI_addr = (hold_reg_addr * 2) + counter ;
                            break;
                            case 15 : SPI_addr = (hold_reg_addr * 2) + counter ;			
                            break;
                            case 16 : SPI_addr = ((hold_reg_addr - 16) * 2) + counter;
                            break;
                            case 17 : SPI_addr = ((hold_reg_addr - 16) * 2) + counter;			
                            break;
                            case 18 : SPI_addr = ((hold_reg_addr - 16) * 2) + counter;
                            break;
                            case 19 : SPI_addr = ((hold_reg_addr - 16) * 2) + counter;			
                            break;
                            case 20 : SPI_addr = ((hold_reg_addr - 16) * 2) + counter;			
                            break;
                            case 21 : SPI_addr = ((hold_reg_addr - 16) * 2) + counter;			
                            break;
                            case 22 : SPI_addr = ((hold_reg_addr - 16) * 2) + counter;			
                            break;
                            case 23 : SPI_addr = ((hold_reg_addr - 16) * 2) + counter;			
                            break;
                            case 24 : SPI_addr = ((hold_reg_addr - 16) * 2) + counter;			
                            break;
                            case 25 : SPI_addr = ((hold_reg_addr - 16) * 2) + counter;			
                            break;
                            case 26 : SPI_addr = ((hold_reg_addr - 16) * 2) + counter;			
                            break;
                            case 27 : SPI_addr = ((hold_reg_addr - 16) * 2) + counter;			
                            break;
                            case 28 : SPI_addr = ((hold_reg_addr - 16) * 2) + counter;			
                            break;
                            case 29 : SPI_addr = ((hold_reg_addr - 16) * 2) + counter;			
                            break;
                            case 30 : SPI_addr = ((hold_reg_addr - 16) * 2) + counter;			
                            break;
                            case 31 : SPI_addr = ((hold_reg_addr - 16) * 2) + counter;			
                            break;
                            case 40 : SPI_addr = (hold_reg_addr - 8) + counter;			
                            break;
                            case 49 : SPI_addr = (hold_reg_addr - 17) + counter;			
                            break;
                            case 54 : SPI_addr = (hold_reg_addr - 20) + counter;		
                            break;
                            case 55 : SPI_addr = (hold_reg_addr - 19) + counter;			
                            break;
                            case 56 : SPI_addr = (hold_reg_addr - 18) + counter;			
                            break;
                            case 57 : SPI_addr = (hold_reg_addr - 17) + counter;			
                            break;
                            default: break;
                        }                                     
            
             
            SPI_addr_buf = SPI_addr;    
            SPI_addr_buf = SPI_addr_buf << 8;                                         // установка переменной адреса в нужную позицию											
			
		  
		  
		  SPI_frame = SPI_addr_buf + SPI_frame;				// склеиваем адрес и данные
		  
			if (R_Wr == 0)
				SPI_frame &= (~(1<<15));					// утанавливаем бит 15 в 0 - режим "запись"
			else
				SPI_frame |= (1<<15);						// утанавливаем бит 15 в 1 - режим "чтение"
	 
            if ((hold_reg_addr < 16)||(hold_reg_addr == 40)||(hold_reg_addr == 54)||(hold_reg_addr == 55)||(hold_reg_addr == 56)||(hold_reg_addr == 57))							// Установка нужного CS
                CS_1_ON;
			else	
                CS_1_OFF;
           
          
            if (((15 < hold_reg_addr)&&(hold_reg_addr < 32))||(hold_reg_addr == 49))
                CS_2_ON;
			else	
				CS_2_OFF;
           									
						//задержка
                            
          SPI2_PUT_int(SPI_frame);						// Передача по SPI
						
                        //задержка
		  				
			CS_1_OFF;
			CS_2_OFF;		
           __delay_us(5); 
           
            
		}  	
    void SPI_TO_CPLD_SEND (unsigned int Data,unsigned int reg_index)
    {
       unsigned int i;                       // width_modul
       i = 1;
       for(i = 1; i < 3; i++)
            {
                Modbus_SPI_R_WR (Data, reg_index, 0, i);
            }
    }
    // UART  
    void UART_init ()
    {
     // RX interrupt UART1 settings 
    //IPC2bits.U1RXIP = 4; // Set UART1 RX interrupt priority to 1 
    IFS0bits.U1RXIF = 0; // Reset UART1 RX interrupt flag
    
    U1BRG = U1BRGVAL;      // Baud Rate setting for 115200 uart
    U1MODEbits.UARTEN = 1;  // 1 = UARTx is enabled; all UARTx pins are controlled by UARTx as defined by UEN <1:0>
    U1MODEbits.UEN = 0;     // 0 = UxTX and UxRX pins are enabled and used; UxCTS and UxRTS/BCLK pins controlled by port latches
    U1MODEbits.PDSEL = 0;   // 0 = No Parity, 8-Data bits
    U1MODEbits.ABAUD = 0;   // 0 = Baud rate measurement disabled or completed
    U1MODEbits.BRGH = 0;    // 1 = BRG generates 4 clocks per bit period (4x baud clock, High-Speed mode)
    U1MODEbits.STSEL = 0;   // 0 = 1-Stop bit

    U1STAbits.UTXISEL0 = 0; // Interrupt when a unsigned character is transferred to the Transmit Shift Register (this implies there isat least one unsigned character open in the transmit buffer
    U1STAbits.UTXISEL1 = 0;
    U1STAbits.UTXINV = 0;
    U1STAbits.UTXEN = 1;    // 1 = Transmit enabled, UxTX pin controlled by UARTx
    U1STAbits.URXISEL = 0;  // 0x = Interrupt is set when any unsigned character is received and transferred from the UxRSR to the receive buffer. Receive buffer has one or more unsigned characters.
                         // The URXISEL<1:0> (UxSTA<7:6>) control bits determine when the UART receiver generates an interrupt.
  
 //Once enabled, the UxTX and UxRX pins are configured as an output and an
 //input, respectively, overriding the TRIS and PORT register bit settings for the corresponding I/O port pins. 
    IEC0bits.U1RXIE = 1; // Enable UART1 RX interrupt  
    }

    void uart_send_byte (unsigned char Ch)
    { // отправка 1 байта данных
       
        U1TXREG = Ch;
        //  should wait at least one instruction cycle between 
        //  writing UxTXREG and reading the TRMT bit
        __delay_us(1);
        while(U1STAbits.TRMT == 0); //waiting for trancsaction to be complete   

    }
    
    void Timer9_init(unsigned long baudrate)
    {
       T9CONbits.TON = 0;           // Timer on/off bit; 0 - Disable Timer
       IFS3bits.T9IF = 0;           // Clear Timer interrupt flag
       TMR9 = 0x0000;               // reset if timer is on, 115200
       T9CONbits.TCS = 0;           // Timer Clock Source Select bit; 0 - Internal clock (FOSC/2)
       T9CONbits.TGATE = 0;         // Disable Gated Timer mode
       T9CONbits.TCKPS = 0b11;      // Prescaler = (00=1, 01=8, 10=64, 11=256) 
       T8CONbits.T32 = 0;
       
       switch(baudrate)
       {
           case 9600:   break; // 1 byte - 840 us
           case 57600:  break; // 1 byte - 140 us
           case 115200: PR9 = 3000; break; // 1 byte - 70 us, 3000 ~ 80 us, 2800 * 3 = 210 us
           case 230400: break; // 1 byte - 35 us
               
           default: PR9 = 3000; // Load the period value
       }
       
       IEC3bits.T9IE = 1;           // Enable T9 interrupt 
    
    }

    //------------------------------------------------------------------------//
    // interrupts
    
    void en_interrupts_global(void)
    {
    /* Set CPU IPL to 0, enable level 1-7 interrupts */
    /* No restoring of previous CPU IPL state performed here */
        SRbits.IPL = 0;
    }
    
    void dis_interrupts_global(void)
    {
    /* Set CPU IPL to 7, disable level 1-7 interrupts */
    /* No saving of current CPU IPL setting performed here */
        SRbits.IPL = 7;
    }
    
    void interrupts_init(void)
    {
        /* Interrupt nesting enabled here */
        //INTCON1bits.NSTDIS = 1;
        
        /// priorities
        
//        /* Set UART1 RX interrupt priority to 6 (level 7 is highest) */
//        IPC2bits.U1RXIP = 6;    
//        /* Set Timer9 interrupt priority to 5 (level 7 is highest) */
//        IPC13bits.T9IP = 5;
//        /* Set SPI2 interrupt priority to 4 (level 7 is highest) */
//        IPC8bits.SPI2IP = 4;
        
        /// flags
        
        IFS0bits.U1RXIF = 0; // Reset UART1 RX interrupt flag
        IFS3bits.T9IF = 0;   // Reset Timer9 interrupt flag 
        IFS2bits.SPI2IF = 0; // Reset SPI2 interrupt flag
        
        /// enable 
        
        IEC0bits.U1RXIE = 1; // Enable UART1 RX interrupt  
        IEC3bits.T9IE   = 1; // Enable Timer9 interrupt
        IEC2bits.SPI2IE = 0; // Disable SPI2 interrupts 
        
    }
    
    void _ISR_PSV _T9Interrupt(void)        //interupt Timer 9
    {      
        T9CONbits.TON = 0;   // stop the timer
        timer_state = 0;
        TMR9 = 0x0000;       // reset if timer is on
        rx_flag = 1;
        
        IFS3bits.T9IF = 0;   // Clear Timer interrupt flag
    } 
    
    void _ISR_PSV _U1RXInterrupt(void)      //interupt UART 1 RX MODBUS
    {
      rx_buf[rx_buf_ptr++] = (unsigned char)U1RXREG; // save rx byte into modbus rx buf
      IFS0bits.U1RXIF = 0;      // clear UART1_rx interrupt  
      
      if(timer_state == 0)
      {
            TMR9 = 0x0000;
            IFS3bits.T9IF = 0;    // Clear Timer interrupt flag
            T9CONbits.TON = 1;
            timer_state = 1;
      }
      TMR9 = 0x0000;         // reset if timer is on, 115200
      
      
    }
   
    void _ISR_PSV _SPI2Interrupt(void)      // Конец посылки по SPI2
    {
            
            // LATCbits.LATC2 = 1;   
            //SPI2STATbits.SPIEN = 0;   
            IFS2bits.SPI2IF = 0; //
            //LATCbits.LATC2 = 1; 
              
        }
    //------------------------------------------------------------------------// 
    
    void GPIO_init ()
    {
       //PORT B
        AD1PCFGH = 0xffff;
        AD1PCFGL = 0xffff;
        
        TRISBbits.TRISB0 = 1;
        TRISBbits.TRISB5 = 0;  // CS_2
        TRISBbits.TRISB9 = 0;  // STATUS_LED_2
        LATBbits.LATB9 = 0;    // must be grounded
        TRISBbits.TRISB10 = 0; // RF_OUT 
        TRISBbits.TRISB11 = 0; // START_LED
        TRISBbits.TRISB12 = 0; // I/O_1 
        LATBbits.LATB12 = 0;   
        TRISBbits.TRISB13 = 0;
        TRISBbits.TRISB14 = 0;
        TRISBbits.TRISB15 = 0; 
        //PORT C
        TRISCbits.TRISC2 = 0; 
        //PORT D
        TRISDbits.TRISD0 = 0;
        TRISDbits.TRISD1 = 0; // RX_EN // must be grounded
        TRISDbits.TRISD2 = 0; // TX_EN 
        TRISDbits.TRISD11 = 1;                  //External interrupt
        //PORT F
        TRISFbits.TRISF0 = 0;
        LATFbits.LATF0 = 0;
        TRISFbits.TRISF1 = 0;
        LATFbits.LATF1 = 0;
        TRISFbits.TRISF6 = 0; 
        //PORT G
        TRISGbits.TRISG0=1; //Modbus_ADDR3
        TRISGbits.TRISG9=0;
        TRISGbits.TRISG12=1; //Modbus_ADDR1
        TRISGbits.TRISG13=1; //Modbus_ADDR0
        TRISGbits.TRISG14=1; //Modbus_ADDR2
    }
    void Init_CPLD()
    {
        delay_chanel_1_LSB = 0xAAAA;   // Значение задержки канала 1 младшие 16 бит
        SPI_TO_CPLD_SEND (delay_chanel_1_LSB, 0);
        delay_chanel_1_MSB =  0xAAAA;   // Значение задержки канала 1 старшие 16 бит
        SPI_TO_CPLD_SEND (delay_chanel_1_MSB, 1);
        width_chanel_1_LSB = 2000;    // Значение ширины импульса канала 1 младшие 16 бит
        SPI_TO_CPLD_SEND (width_chanel_1_LSB, 2);
        width_chanel_1_MSB = 0;   // Значение ширины импульса канала 1 старшие 16 бит
        SPI_TO_CPLD_SEND (width_chanel_1_MSB, 3); 
        delay_chanel_2_LSB = 1000;   // Значение задержки канала 2 младшие 16 бит
        SPI_TO_CPLD_SEND (delay_chanel_2_LSB, 4);
        delay_chanel_2_MSB = 0;   // Значение задержки канала 2 старшие 16 бит
        SPI_TO_CPLD_SEND (delay_chanel_2_MSB, 5);
        width_chanel_2_LSB = 2000;   // Значение ширины импульса канала 2 младшие 16 бит
        SPI_TO_CPLD_SEND (width_chanel_2_LSB, 6);
        width_chanel_2_MSB = 0;   // Значение ширины импульса канала 2 старшие 16 бит
        SPI_TO_CPLD_SEND ( width_chanel_2_MSB, 7);
        delay_chanel_3_LSB = 1000;   // Значение задержки канала 3 младшие 16 бит
        SPI_TO_CPLD_SEND (delay_chanel_3_LSB, 8);
        delay_chanel_3_MSB = 0;   // Значение задержки канала 3 старшие 16 бит
        SPI_TO_CPLD_SEND (delay_chanel_3_MSB, 9);
        width_chanel_3_LSB = 2000;   // Значение ширины импульса канала 3 младшие 16 бит
        SPI_TO_CPLD_SEND (width_chanel_3_LSB, 10);
        width_chanel_3_MSB = 0;   // Значение ширины импульса канала 3 старшие 16 бит
        SPI_TO_CPLD_SEND ( width_chanel_3_MSB, 11);
        delay_chanel_4_LSB = 1000;   // Значение задержки канала 4 младшие 16 бит
        SPI_TO_CPLD_SEND (delay_chanel_4_LSB, 12);
        delay_chanel_4_MSB = 0;   // Значение задержки канала 4 старшие 16 бит
        SPI_TO_CPLD_SEND (delay_chanel_4_MSB, 13);
        width_chanel_4_LSB = 2000;   // Значение ширины импульса канала 4 младшие 16 бит
        SPI_TO_CPLD_SEND (width_chanel_4_LSB, 14);
        width_chanel_4_MSB = 0;   // Значение ширины импульса канала 4 старшие 16 бит
        SPI_TO_CPLD_SEND (width_chanel_4_MSB, 15);                 
    }
    void Dev_ID_init()
    {
            dev_id = 0;
            dev_id = ~(ADDR0 + ADDR1*2 + ADDR2*4 + ADDR3*8); 
            dev_id &= 0x0f;
    }
   
int main()
{     
    Oscillator_init ();
    GPIO_init();
    Timer9_init(115200);
    UART_init ();
    //SPI2_init ();
    //Init_ADC();
    Init_CPLD();
    modbus_init();
    
    //interrupts_init();
    //en_interrupts_global();

 while(1)
 {
     
   modbus_poll();
 
 }//WHILE(1)
}//MAIN