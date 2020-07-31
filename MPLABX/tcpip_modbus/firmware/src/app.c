#include "app.h"
#include "modbus/dialtek_modbus.h"
#include "tcp_app.h"

void APP_Initialize ( void )
{   
    modbus_init();
}

static unsigned int tmp_var = 71;

static void modbus_change_ip()
{
    IPV4_ADDR new_ip, new_mask, new_gateway;
    unsigned int ipFragment;

    holding_reg_read(3, &ipFragment);
    new_ip.v[0] = (uint8_t)ipFragment;
    holding_reg_read(4, &ipFragment);
    new_ip.v[1] = (uint8_t)ipFragment;
    holding_reg_read(5, &ipFragment);
    new_ip.v[2] = (uint8_t)ipFragment;
    holding_reg_read(6, &ipFragment);
    new_ip.v[3] = (uint8_t)ipFragment;

    new_mask.v[0] = 255; new_mask.v[1] = 255; new_mask.v[2] = 255; new_mask.v[3] = 0;
    new_gateway.v[0] = 192; new_gateway.v[0] = 168; new_gateway.v[0] = 100; new_gateway.v[0] = 1;  // отладочный пример

    tcp_app_set_alternative_ip(new_ip, new_mask, new_gateway);
}

static void modbus_poll(void)
{       
    switch( modbus_get_poll() )
    {
        case MODBUS_RHR_CMD:   // Чтение holding регистра
//////////////////////////// Чтение HOLDING //////////////////////////
           // holding_reg_write(register_address,U16 data)
              holding_reg_write(0, tmp_var++);
              int i;
              for (i=1; i<124; i++)
              {
                  holding_reg_write(i, tmp_var++);
              }
              if (tmp_var > 10000) tmp_var = 0;
              modbus_rhr_answer(); // ????? ?? ??????
        break;
//////////////////////////// Чтение HOLDING //////////////////////////
        case MODBUS_WSR_CMD:  // Запись holding регистра
              modbus_wsr_answer();  // ????? ?? ??????;
              //holding_reg_write(get_wr_reg_addr(), get_wr_reg_val());   // этот функционал добавлен в modbus_wsr_answer()
              holding_reg_read(1, &tmp_var);
              
              if (get_wr_reg_addr() == 2)   //если пришёл сигнал о смене ip
              {
                if (get_wr_reg_val() == 0)
                {
                    tcp_app_use_default_ip();
                } else {
                    modbus_change_ip();
                    tcp_app_use_alternative_ip();
                }
              }
              
        break;
//////////////////////////// чтение INPUT ////////////////////////////
        case MODBUS_RIR_CMD:
              input_reg_write(0, 89);
              modbus_rir_answer(); // ????? ?? ??????
        break;
     }
}

void APP_Tasks ( void )
{
    modbus_poll();
}


/*******************************************************************************
 End of File
 */
