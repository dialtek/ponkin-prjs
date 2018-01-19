#ifndef __mdr_1_wire_H__
#define __mdr_1_wire_H__

/*--------------------------------------------------------------------------- */
#define CRC8INIT   0x00
#define CRC8POLY   0x18  
/*--------------------------------------------------------------------------- */

/*=========================================================================== */
// 1-wire 

	void OneWirePin_SetDir(U8 direction) {
	  
   // ������������� ���� 1-wire
  
  if(!direction) MDR_PORTF->FUNC &= ~(1 << 1); 			// ��� PD2 �� ����
  else           MDR_PORTF->FUNC |=  (1 << 1); 			// ��� PD2 �� �����
  
  //MDR_PORTF->FUNC    = 0x0000;          // ������� - ���� 
  MDR_PORTF->ANALOG  = 0xffff;          // ����� ����� - ��������
  MDR_PORTF->PWR     = 0xffffffff;      // ����������� ������� ����� ( ������� 10 ��)

 }
 
 	void OneWirePin_Low() {
	  
   // ������������� ���� �� ���� 1-wire
   
  MDR_PORTF->RXTX &= ~ (1 << 1);
 
 }
 
  	void OneWirePin_High() {
	  
   // ������������� 1 �� ���� 1-wire
   
  MDR_PORTF->RXTX |= (1 << 1);
 
 }
 
 	U8 OneWirePin_level() {
	  
  // ������ �������� ������ �� ���� 1-wire
	  
  return MDR_PORTF->RXTX & (1 << 1);
}

	U8 OneWire_reset() {
	  
  // ����� ������� ������ (reset), ������� �������� ������� �����������.
  // ���� ������� ����������� �������, ���������� ��� ���������� � ���������� 1, ����� ���������� 0 
	  
  OneWirePin_SetDir(1); // ���� �� �����	  
  OneWirePin_Low();
  delay_us(640); // ����� 480..960 ���
  OneWirePin_High();
  delay_us(5); // ����� ����������� �������������� ���������, ����� ������� ������� ������� �� ����
  // ��� �� ����� 60 �� �� ��������� �������� �����������;
  OneWirePin_SetDir(0); // ���� �� ����	
  for (U8 c = 100; c; c--) {
    if (!OneWirePin_level()) {
      // ���� ��������� ������� �����������, ��� ��� ���������
      while (!OneWirePin_level()) { } // ��� ����� ������� �����������
      return 1;
    }
    delay_us(10);
  }
  return 0;
}
 
	void OneWire_send_bit(U8 bit) {
  
  // ���������� ���� ���
  // bit ������������ ��������, 0 - ����, ����� ������ �������� - �������
	  
  OneWirePin_SetDir(1); // ���� �� �����
  OneWirePin_Low();
  if (bit) {
    delay_us(10); // ������ �������, �� 1 �� 15 ��� (� ������ ������� �������������� ������)
    OneWirePin_High();
    delay_us(80); // �������� �� ���������� ��������� (�� ����� 60 ���)
  } 
  else {
    delay_us(80); // ������ ������� �� ���� �������� (�� ����� 60 ���, �� ����� 120 ���)
    OneWirePin_High();
    delay_us(5); // ����� �������������� �������� ������� �� ���� + 1 �� (�������)
  }
}

	U8 OneWire_read_bit() {
  
  // ������ �������� ����, ������������ ������������.
  // ���������� 0 - ���� ������� 0, �������� �� ���� �������� - ���� �������� �������
	  
  U8 r = 0;
  
  OneWirePin_SetDir(1); // ��� �� �����
  OneWirePin_Low();
  delay_us(10); // ������������ ������� ������, ������� 1 ���
  OneWirePin_High();
  delay_us(10); // ����� �� ������� �������������, ����� �� ����� 15 ���
  OneWirePin_SetDir(0); // ��� �� ����
  r = OneWirePin_level();
  delay_us(70); // �������� �� ���������� ����-�����, ������� 60 ��� � ������ ������� ������
  
  return r;
}

        U8 OneWire_read() {
  
  // ������ ���� ����, ���������� �����������, 
  // ������� ��� �����, ���������� ����������� ��������
  
  U8 r = 0;
  
  for (U8 p = 8; p; p--) {
    r >>= 1;
    if (OneWire_read_bit())
      r |= 0x80;
  }
  return r;
}

	void OneWire_send(U8 b) {
  
  // ���������� ���� ����, ������ ������ ���, ������� ��� �����
  // b - ������������ ��������
	  
  for (U8 p = 8; p; p--) {
    OneWire_send_bit(b & 1);
    b >>= 1;
  }
}

	U8 crc8 (U8 data, U8 crc) {
	// ������ ����������� �����
	  
	U8 bit_counter;
	U8 feedback_bit;
	
	bit_counter = 8;
	
	do
	{
    	feedback_bit = (crc ^ data) & 0x01;
    	if ( feedback_bit == 0x01 ) crc = crc ^ CRC8POLY;
    	crc = (crc >> 1) & 0x7F;
    	if ( feedback_bit == 0x01 ) crc = crc | 0x80;
    	data = data >> 1;
    	bit_counter--;
	}  while (bit_counter > 0);
	
	return crc;
 }

	U8 OneWire_skip() {
	  
	// ��������� ������������������ ������������� (reset + ������� ������� �����������)
	// ���� ������� ����������� �������, ��������� ������� SKIP ROM
	// ���������� 1, ���� ������� ����������� �������, 0 - ���� ���
	  
  if (!OneWire_reset())
    return 0;
  OneWire_send(0xCC);
  	return 1;
}
	
	S32 ds18b20_rd_t () {
	  // ������ ��������� �������
	  	 
	 U8 scratchpad[8];		// ����� ������ �������
	 U8 CRC = 0;
	 U8 OneWireRdByte = 0;	
 	 S32 Temper = 0; 
	  
 if (OneWire_skip()) { 				// �������� ������� ������� �� ����
	   
      OneWire_send(0x44); 						// ������ ������, ������ ��������� � 
	  do OneWireRdByte = OneWire_read();		// �������� �� ������� ������ �������� �� ���� 
	  while (OneWireRdByte == 0);
 }
 
 if (OneWire_skip()) {				// ���������� ������ - ������� RESET �����������! 
	  OneWire_send(0xBE);			// ������ �� ������ ������  
	  delay_us(2);

     for (U8 i = 0; i < 9; i++) {		// ���������� ����� �������
        OneWireRdByte = OneWire_read();
        scratchpad[i] = OneWireRdByte;
        CRC = crc8(scratchpad[i], CRC); // ������ CRC
     }	     
	 if(CRC == 0) // CRC �����...
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
 	 }
 return Temper;	
}

// 1-wire
/*=========================================================================== */

#endif
