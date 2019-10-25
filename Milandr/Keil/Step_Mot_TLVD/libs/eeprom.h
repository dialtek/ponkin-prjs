

#include "MDR32Fx.h" 

#define ATML_Addr 0xA0

//void rom_wr_byte (uint16_t addr, uint8_t dataByte){
//	
//    /// записывает байт данных по 16 - бит. адресу
//    
//    uint8_t addr_MSB = 0;
//    uint8_t addr_LSB = 0;
//    
//    addr_MSB = (addr >> 8);
//    addr_LSB = addr;
//    
//    
//    I2C_Write_Address(ATML_Addr|0); // запись
//    // A read operation is initiated if this bit is high
//    // and a write operation is initiated if this bit is low.
//    
//    I2C_Write_Address(addr_MSB);
//    I2C_Write_Address(addr_LSB);
//   for(unsigned char i = 0; i < 64; i++)
//  {
//      I2C_Write_Address(i);
//  }
//    
//    
//    delay_ms (15); // t записи в rom - 10 мс
////    crc_buf_wr[crc_wr_index] = dataByte;
////    crc_wr_index++;
// }

// 
//  uint8_t rom_rd_byte (uint16_t addr)
// {
//    /// чтение байта данных по 16 - бит. адресу
//    
//    uint8_t rd_data_byte = 0;
//    uint8_t addr_MSB = 0; // старший байт адреса
//    uint8_t addr_LSB = 0; // младший байт адреса
//    
//    addr_MSB = (addr >> 8); // заполнение ст. байта из 2 - байт. адреса
//    addr_LSB = addr; // заполнение мл. байта из 2 - байт. адреса
////    

//   I2C_Write_Address(ATML_Addr|0); // команда чтения
//    // A read operation is initiated if this bit is high
//   // and a write operation is initiated if this bit is low.
//	 
//	 I2C_Write_Address(addr_MSB);  // выдача на линию ст. байта адреса
//   I2C_Write_Address(addr_LSB);  // выдача на линию мл. байта адреса

//      I2C_Write_Address(ATML_Addr|1); // чтение
//    for(uint8_t i = 0; i < 64; i++ )
//      rd_data_byte = I2C_Read();
////    //i2c_write (0xff); // без этого не работает 0_0
//  
//   return rd_data_byte;
//        
//    // запись
//    // A read operation is initiated if this bit is high
//    // and a write operation is initiated if this bit is low.
//    
// }