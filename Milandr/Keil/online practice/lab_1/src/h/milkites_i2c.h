
#ifndef __I2C_H__
#define __I2C_H__
#ifdef	__cplusplus
extern "C"
{
#endif

   void I2C_Init(void);
	 void I2C_Start(void);
	 void I2C_Send_Addr(uint8_t Byte);
	 void I2C_Send_Byte(uint8_t Byte);
	 uint8_t I2C_GetData(void);
	 void I2C_NACK(void);
	 void I2C_Stop(void);

#ifdef	__cplusplus
}
#endif
#endif