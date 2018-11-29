// 1-wire
#define One_wire_TX_pin   LATBbits.LATB2  // RB2	  
#define One_wire_RX_pin   PORTBbits.RB3   // RB3	

/*--------------------------------------------------------------------------- */
#define CRC8INIT   0x00
#define CRC8POLY   0x18  
#define Skip_ROM   0xCC         // ������� ��������� �� ���� �������� �� ����
#define Convert_T  0x44         // ������� ������ ��������� �����������
#define Match_ROM  0x55         // ������� ��������� � ���������� �������
#define Read_scr   0xBE         // ������� ������ ��������� ����������� �������      
#define Read_ROM   0x33         // ������� ������ ID ������ ������������� � ���� ����������
unsigned char buf[8];
/*--------------------------------------------------------------------------- */

/*=========================================================================== */
// 1-wire 

 void OneWire_tx_state(unsigned char state) {
	  
   // ������������ ���. ������� �� ����� 1-wire
   
  One_wire_TX_pin = state;
  //TRISBbits.TRISB2 = 0;  // OW TX off
 
 }
 
 unsigned int OneWire_rx_state() {
	  
  // ������ �������� ������ �� ���� 1-wire
  unsigned int state = 0;
  state = One_wire_RX_pin;
  return state;
 
}

 unsigned char OneWire_reset() {
	  
  // ����� ������� ������ (reset), ������� �������� ������� �����������.
  // ���� ������� ����������� �������, ���������� ��� ���������� � ���������� 1, ����� ���������� 0 
 unsigned char retVal = 0;	
 
  OneWire_tx_state(0);
  __delay_us(640); // ����� 480..960 ���
  OneWire_tx_state(1);
  
  __delay_us(50); // ����� ����������� �������������� ���������, ����� ������� ������� ������� �� ����
  // ��� �� ����� 60 �� �� ��������� �������� �����������;
  
  for (unsigned char c = 100; c; c--) {
    if (!OneWire_rx_state()) {
      while(!OneWire_rx_state())
      retVal = 1;
    }
  }
      
    // ���� ��������� ������� �����������, ��� ��� ���������
    //while (!OneWirePin_level()) { } // ��� ����� ������� �����������

  return retVal;
}
 
 void OneWire_send_bit(unsigned char bit) {
  
  // ���������� ���� ���
  // bit ������������ ��������, 0 - ����, ����� ������ �������� - �������
	  
  OneWire_tx_state(0);
  if (bit) {
    __delay_us(8); // ������ �������, �� 1 �� 15 ��� (� ������ ������� �������������� ������)
    OneWire_tx_state(1);
    __delay_us(65); // �������� �� ���������� ��������� (�� ����� 60 ���)
  } 
  else {
    __delay_us(70); // ������ ������� �� ���� �������� (�� ����� 60 ���, �� ����� 120 ���)
    OneWire_tx_state(1);
    __delay_ms(1); // ����� �������������� �������� ������� �� ���� + 1 �� (�������)
  }
}

 unsigned char OneWire_read_bit() {
  
  // ������ �������� ����, ������������ ������������.
  // ���������� 0 - ���� ������� 0, �������� �� ���� �������� - ���� �������� �������
	  
  unsigned char retVal = 0;
  
  OneWire_tx_state(0);
  __delay_us(5); // ������������ ������� ������, ������� 1 ���
  OneWire_tx_state(1);
  __delay_us(3); // ����� �� ������� �������������, ����� �� ����� 15 ���
  
  if(OneWire_rx_state()) retVal = 1;
  __delay_us(65); // �������� �� ���������� ����-�����, ������� 60 ��� � ������ ������� ������
  
  return retVal;
}

 unsigned char OneWire_read() {
  
  // ������ ���� ����, ���������� �����������, 
  // ������� ��� �����, ���������� ����������� ��������
  
  unsigned char r = 0;
  
  for (unsigned char p = 8; p; p--) {
    r >>= 1;
    if (OneWire_read_bit())
      r |= 0x80;
  }
  return r;
}

 void OneWire_send(unsigned char b) {
  
  // ���������� ���� ����, ������ ������ ���, ������� ��� �����
  // b - ������������ ��������
	  
  for (unsigned char p = 8; p; p--) {
    OneWire_send_bit(b & 1);
    b >>= 1;
  }
}

 unsigned char crc8 (unsigned char data, unsigned char crc) {
	// ������ ����������� �����
	  
	unsigned char i;

	crc = crc ^ data;
	for (i = 0; i < 8; i++)
	{
	    if (crc & 0x01)
	        crc = (crc >> 1) ^ 0x8C;
	    else
	        crc >>= 1;
	}

	return crc;
 }

 unsigned char OneWire_skip() {
	  
	// ��������� ������������������ ������������� (reset + ������� ������� �����������)
	// ���� ������� ����������� �������, ��������� ������� SKIP ROM
	// ���������� 1, ���� ������� ����������� �������, 0 - ���� ���
	  
  if (!OneWire_reset())
    return 0;
  OneWire_send(0xCC);
  	return 1;
}

 unsigned char OneWire_all_rd_t() {
 
	// ��������� ������������������ ������������� (reset + ������� ������� �����������)
	// ���� ������� ����������� �������, ��������� ������� SKIP ROM
	// ���� ������� ��������� �����������
        // ���� 760�� ���� ������ ������� �����������   
  if (OneWire_reset())
  {
      OneWire_send(Skip_ROM);             // ��������� �� ���� �������� �� ����
      OneWire_send(Convert_T); 		  //  ������ ��������� � 
      __delay_ms(750);
     
      return 1;
  }
  else return 0;
}  

 unsigned char onewire_read_rom(unsigned char *s_ID) {
  // ��������� ������������������ ������������� (reset + ������� ������� �����������)
  // ���� ������� ����������� �������, ��������� ������� READ ROM, ����� ������ 8-�������� ��� ����������
  // ��������� ��� � ����� �� ��������� buf, ������� � �������� �����
  // ���������� 1, ���� ��� ��������, 0 - ���� ������� ����������� �� �������
  if (!OneWire_reset())
    return 0; 
  OneWire_send(Read_ROM);
  for (unsigned char p = 0; p < 8; p++) {
    s_ID[p] = OneWire_read(); /// ���������� ID ������� � ����������
  }
  return 1;
  /*����� ������ ������ ������� 8 ���� � 2 ������
  LCD_set_cursor(1); 
for (unsigned char i = 0; i < 4; i++)  //����� ������ ������ ������� 8 ���� � 2 ������
	{
          LCD_Wr_num(sens_ID[i],3);
          LCD_print(" ");
        }
LCD_set_cursor(2);
for (unsigned char i = 4; i < 8; i++)  
	{
          LCD_Wr_num(sens_ID[i],3);
          LCD_print(" ");
        }
  */
}

 unsigned char OneWire_match_ID(unsigned char *s_ID) {
  
  if (!OneWire_reset()) return 0;
  
  OneWire_send(Match_ROM);
  for (unsigned char p = 0; p < 8; p++) 
    OneWire_send(s_ID[p]);
  return 1;
}
		
 long ds18b20_i_rd_t (unsigned char *s_ID) {
	  // ������ ��������� ����������� �������
	 	 
	 unsigned char scratchpad[8];		// ����� ������ �������
	 unsigned char CRC_read = 0;
         unsigned char CRC_calc = 0;
	 unsigned char OneWireRdByte = 0;	
 	 long Temper = 0; 

//       OneWire_reset();
//       OneWire_send(Skip_ROM);             // ��������� �� ���� �������� �� ����
//       OneWire_send(Convert_T); 		  //  ������ ��������� � 
//       __delay_ms(760);
       OneWire_reset();
      // OneWire_send(Skip_ROM);  
       OneWire_match_ID(s_ID);
       OneWire_send(Read_scr);			// ������ �� ������ ������ 

     for (unsigned char i = 0; i < 9; i++) 
     {		// ���������� ������ �������
        OneWireRdByte = OneWire_read();
        scratchpad[i] = OneWireRdByte;
	
	if(i == 8) CRC_read = scratchpad[8];// ���� ���
     }
	  
     for (unsigned char i = 0; i < 8; i++) 
     {		// ���������� ����� �������
        CRC_calc = crc8(scratchpad[i], CRC_calc); // ������ CRC
     }
     if(CRC_calc == CRC_read) // CRC �����...
	{
	 		Temper = (scratchpad[1] << 8) | scratchpad[0]; // ��������� ��. � �� ����� ������
			if(Temper < 2000)
	 			Temper = (625 * Temper)/10; 				   // �������� ������� � �����������
			 											   	   // +125 �������� - 2000 ��������
			else {
				Temper = Temper - 65535;					   // �������� ������� � �����������
				Temper = (55 * Temper*1000)/879;			   // ������������� �
			}
	}

 return Temper;	
}

// 1-wire
/*=========================================================================== */
