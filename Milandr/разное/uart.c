/*=========================================================================== */
// UART
	void Uart_init (void){
//UART	  
MDR_PORTB->FUNC |= ((2 << 5*2) | (2 << 6*2)); 	//режим работы порта
MDR_PORTB->ANALOG |= ((1 << 5) | (1 << 6)); 	//цифровой
MDR_PORTB->PWR |= ((3 << 5*2) | (3 << 6*2)); 	//максимально быcтрый

MDR_RST_CLK->PER_CLOCK |= (1UL << 6); 			//тактирование UART1
MDR_RST_CLK->UART_CLOCK = (4 					// установка делителя для UART1
  |(0 << 8) 									// установка делителя для UART2
  |(1 << 24) 						// разрешение тактовой частоты UART1
  |(0 << 25));						// разрешение тактовой частоты UART2*/ 

  //Параметры делителя при частоте = 5000000Гц и скорости = 115200
MDR_UART1->IBRD = 0x2; 						// целая часть делителя скорости
MDR_UART1->FBRD = 0x2e; 					// дробная часть делителя скорости
MDR_UART1->LCR_H = ((0 << 1) 				// разрешение проверки четности
  |(0 << 2) 								// четность/нечетность
  |(0 << 3) 								// стоп-бит
  |(1 << 4) 						// вкл. буфера FIFO приемника и передатчика 12 бит, глубину 16 слов
  |(3 << 5) 								// длина слова = 8 бит
  |(0 << 7)); 							    // передача бита четности

//MDR_UART1->IMSC = 1 << 4;                // RXIM разрешение прерывания от приемника UARTRXINTR. 1 – установлена;   
MDR_UART1->IMSC = (1 << 10) | (1<<4 );   // Маскированное  состояние  прерывания  по  переполнению  буфера UARTOEINTR 
MDR_UART1->IFLS = 1<<4;                  // разрешение прерывание по залолн. 1/2 буфера фифо

MDR_UART1->CR = ((1 << 8)|(1 << 9)|1);   // передачик и приемник разрешен, 

}
	
	void Uart_send_hex(U8 hex_data){
	  
      // пока Буфер   FIFO   передатчика   заполнен...  
	while(MDR_UART1->FR & (1<<5)) { }; // ждем готовности UART1;

    MDR_UART1->DR = hex_data;
  
	}
	  
	void Uart_CR_LF_send (void){
	  
        Uart_send_hex(0x0A);
	Uart_send_hex(0x0D);
	
	}

	void Uart_num_send(int32_t data){
	  
  unsigned char temp[10],count=0;
  if (data<0) 
  {
    data=-data;
    Uart_send_hex('-');
  }     
  if (data)
  {
    while (data)
    {
      temp[count++]=data%10+'0';
      data/=10;                 
    }                           
    while (count)           
      Uart_send_hex(temp[--count]);          
  }
  else Uart_send_hex('0');           
}

	void Uart_send_text(unsigned char *s){
  while (*s != 0)
    Uart_send_hex(*s++);
}

/*=========================================================================== */
main -> Uart_init();

while           Uart_send_text("T=");
                Uart_num_send(10);
                Uart_CR_LF_send();
				delay_ms(1000);
				