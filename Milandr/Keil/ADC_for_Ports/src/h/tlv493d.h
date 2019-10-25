#ifndef __TLV493D_H__
#define __TLV493D_H__

#ifdef	__cplusplus
extern "C"
{
#endif
#define TLV493D_rd_addr 0xbd // i2c адрес датчика при чтении 
#define TLV493D_wr_addr 0xbc // i2c адрес датчика при записи


/* =================================================================================================== */
  void TLV493D_reset();
	void TLV493D_init(void);
	float TLV493D_calc_field (uint8_t nibble_h, uint8_t nibble_l);
	void read_all_TLV493D(char X, char Y,char Z);

/* =================================================================================================== */
	#ifdef	__cplusplus
}
#endif
#endif
