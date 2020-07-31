#include "modbus_app.h"
#include "modbus/dialtek_modbus.h"

void MODBUS_APP_Initialize ( void )
{
    modbus_init();
}

static void modbus_change_ip()
{
//    IPV4_ADDR new_ip, new_mask, new_gateway;
//    unsigned int ipFragment;
//
//    holding_reg_read(3, &ipFragment);
//    new_ip.v[0] = (uint8_t)ipFragment;
//    holding_reg_read(4, &ipFragment);
//    new_ip.v[1] = (uint8_t)ipFragment;
//    holding_reg_read(5, &ipFragment);
//    new_ip.v[2] = (uint8_t)ipFragment;
//    holding_reg_read(6, &ipFragment);
//    new_ip.v[3] = (uint8_t)ipFragment;
//
//    new_mask.v[0] = 255; new_mask.v[1] = 255; new_mask.v[2] = 255; new_mask.v[3] = 0;
//    new_gateway.v[0] = 192; new_gateway.v[0] = 168; new_gateway.v[0] = 100; new_gateway.v[0] = 1;  // отладочный пример
//
//    modbus_buf_tcp_set_alternative_ip(new_ip, new_mask, new_gateway);
}

void MODBUS_APP_Tasks ( void )
{    
}


/*******************************************************************************
 End of File
 */
