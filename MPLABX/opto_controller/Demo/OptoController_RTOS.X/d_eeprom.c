#include "FreeRTOS.h"
#include "d_SPI.h"
#include "d_eeprom.h"
#include "dialtek_modbus.h"

/*================================ EEPROM =================================== */
// 25LC128 SPI EEPROM

// 125 holding/input register write

void eeprom_wr_page(unsigned char reg_type, unsigned int address)
{
  unsigned int RegVal = 0;  
    
  // EEPROM write enable sequence
  CS2_LOW;
  SPI2_write_byte(EEPROM_WREN);
  CS2_HIGH;
  
  // EEPROM address and data write sequence
  CS2_LOW;
  SPI2_write_byte(EEPROM_WRITE);
  
  SPI2_write_byte((unsigned char)(address >> 8));      // set address ptr msb
  SPI2_write_byte((unsigned char)(address & 0x00ff));  // set address ptr lsb
  
  for(unsigned int i = 0; i < 32; i++) // max bytes to write - 64
  {
      
    if(reg_type == HOLD_REGS)  
        holding_reg_read((i + address/2),&RegVal); 
        
    if(reg_type == INPUT_REGS)
        input_reg_read((i + (address-INPUT_REGS_ADDR)/2),&RegVal);
    
    SPI2_write_byte((unsigned char)(RegVal >> 8));     // data msb    
    SPI2_write_byte((unsigned char)(RegVal & 0x00ff)); // data lsb 
 }
  
  CS2_HIGH;
  
  vTaskDelay(10);  // Internal Write Cycle Time × 5 ms
}

void eeprom_wr_regs(unsigned char reg_type)
{
  /// 124 modbus register saving sequence
    
  // 25LC128 SPI EEPROM addres pointer, 248 bytes beginning from 0x00 address
  unsigned int EEPROM_addr = 0;
  
  if(reg_type == INPUT_REGS)
      EEPROM_addr = INPUT_REGS_ADDR;
  
  // save holding registers into memory
  eeprom_wr_page(reg_type,EEPROM_addr);  // EEPROM memory page 1 - 0...31 regs
  EEPROM_addr += 64;
  eeprom_wr_page(reg_type,EEPROM_addr);  // EEPROM memory page 2 - 32...63 regs
  EEPROM_addr += 64;
  eeprom_wr_page(reg_type,EEPROM_addr);  // EEPROM memory page 3 - 64...95 regs
  EEPROM_addr += 64;
  eeprom_wr_page(reg_type,EEPROM_addr);  // EEPROM memory page 4 - 96...124 regs     
  
}

void eeprom_clear_page(unsigned int address)
{
  // EEPROM write enable sequence
  CS2_LOW;
  SPI2_write_byte(EEPROM_WREN);
  CS2_HIGH;
  //delay_us(20);
  
  // EEPROM address and data write sequence
  CS2_LOW;
  SPI2_write_byte(EEPROM_WRITE);
  
  SPI2_write_byte((unsigned char)(address >> 8));      // set address ptr msb
  SPI2_write_byte((unsigned char)(address & 0x00ff));  // set address ptr lsb
  
  for(unsigned char i = 0; i < 64; i++) // max bytes to write - 64
  { 
    SPI2_write_byte(0); // data msb    
 }
  
  //delay_us(5);
  CS2_HIGH;
  
  vTaskDelay(10);  // Internal Write Cycle Time × 5 ms
}

void eeprom_clear(void)
{
  unsigned int EEPROM_addr = 0; // input regs location
    
  for(unsigned long i = 0; i < 2000; i++) // max bytes to write - 64, 128000/64 = 2000
  { 
    eeprom_clear_page(EEPROM_addr);   
    EEPROM_addr += 64;
  }
  
}

void eeprom_rd_regs_H(void)
{
  unsigned char lsb = 0, msb = 0;
  unsigned int address = 0;
  // EEPROM read sequence
  CS2_LOW;
  SPI2_write_byte(EEPROM_READ);
  
  SPI2_write_byte((unsigned char)(address >> 8));      // set address ptr msb
  SPI2_write_byte((unsigned char)(address & 0x00ff));  // set address ptr lsb

  // holding regs restore
  for(unsigned int i = 0; i < 125; i++)
  { 
    msb = SPI2_read_byte();
    lsb = SPI2_read_byte();
    
    holding_reg_write(i,(unsigned int)((msb << 8) | lsb));   
  }
  CS2_HIGH;
}

void eeprom_rd_regs_I(void)
{
  unsigned char lsb = 0, msb = 0;
  unsigned int address = 256;
  // EEPROM read sequence
  CS2_LOW;
  SPI2_write_byte(EEPROM_READ);
  
  SPI2_write_byte((unsigned char)(address >> 8));      // set address ptr msb
  SPI2_write_byte((unsigned char)(address & 0x00ff));  // set address ptr lsb

  // holding regs restore
  for(unsigned int i = 0; i < 125; i++)
  { 
    msb = SPI2_read_byte();
    lsb = SPI2_read_byte();
    
    input_reg_write(i,(unsigned int)((msb << 8) | lsb));   
  }
  
  CS2_HIGH;
}

/*================================ EEPROM =================================== */
