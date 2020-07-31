#include "app.h"
#include "modbus/dialtek_modbus.h"
#include "tcp_app.h"

// *****************************************************************************
// Section: Global Data Definitions
// *****************************************************************************
unsigned int modbus_var = 0;

extern unsigned int web_var_1;
extern unsigned int web_var_2;


// *****************************************************************************
// Section: Application Callback Functions
// *****************************************************************************

/* TODO:  Add any necessary callback functions.
*/

// *****************************************************************************
// Section: Application Local Functions
// *****************************************************************************

static TCP_APP_DATA tcpAppData;
APP_DATA appData;
APP_LED_STATE LEDstate = APP_LED_STATE_OFF;

void HTTP_server_SM(void)
{
    SYS_STATUS          tcpipStat;
    TCPIP_NET_HANDLE    netH;
    int                 nNets;
    static IPV4_ADDR    dwLastIP[2] = { {-1}, {-1} };
    IPV4_ADDR           ipAddr;
    int                 i;
    const char          *netName, *netBiosName;
    static uint32_t     startTick = 0;


    switch(appData.state)
    {
        case AP_MOUNT_DISK:
            if(SYS_FS_Mount(APP_SYS_FS_NVM_VOL, APP_SYS_FS_MOUNT_POINT, APP_SYS_FS_TYPE, 0, NULL) == 0)
            {
                SYS_CONSOLE_PRINT("SYS_Initialize: The %s File System is mounted\r\n", APP_SYS_FS_TYPE_STRING);
                appData.state = AP_TCPIP_WAIT_INIT;
            }
            break;

        case AP_TCPIP_WAIT_INIT:
            tcpipStat = TCPIP_STACK_Status(sysObj.tcpip);
            if(tcpipStat < 0)
            {   // some error occurred
                SYS_CONSOLE_MESSAGE("APP: TCP/IP stack initialization failed!\r\n");
                appData.state = AP_TCPIP_ERROR;
            }
            else if(tcpipStat == SYS_STATUS_READY)
            {
                // now that the stack is ready we can check the
                // available interfaces and register
                // a Bonjour service

                nNets = TCPIP_STACK_NumberOfNetworksGet();

                for(i = 0; i < nNets; i++)
                {
                    netH = TCPIP_STACK_IndexToNet(i);
                    netName = TCPIP_STACK_NetNameGet(netH);
                    netBiosName = TCPIP_STACK_NetBIOSName(netH);

#if defined(TCPIP_STACK_USE_NBNS)
                    SYS_CONSOLE_PRINT("    Interface %s on host %s - NBNS enabled\r\n", netName, netBiosName);
#else
                    SYS_CONSOLE_PRINT("    Interface %s on host %s - NBNS disabled\r\n", netName, netBiosName);
#endif // defined(TCPIP_STACK_USE_NBNS)
                    (void)netName;          // avoid compiler warning 
                    (void)netBiosName;      // if SYS_CONSOLE_PRINT is null macro

#if defined(TCPIP_STACK_USE_ZEROCONF_MDNS_SD)
                    // base name of the service Must not exceed 16 bytes long
                    // the last digit will be incremented by interface
                    char mDNSServiceName[] = "MyWebServiceNameX ";

                    mDNSServiceName[sizeof(mDNSServiceName) - 2] = '1' + i;
                    TCPIP_MDNS_ServiceRegister(netH
                            , mDNSServiceName                     // name of the service
                            ,"_http._tcp.local"                   // type of the service
                            ,80                                   // TCP or UDP port, at which this service is available
                            ,((const uint8_t *)"path=/index.htm") // TXT info
                            ,1                                    // auto rename the service when if needed
                            ,NULL                                 // no callback function
                            ,NULL);                               // no application context
#endif // defined(TCPIP_STACK_USE_ZEROCONF_MDNS_SD)
                }

#if defined(TCPIP_STACK_USE_HTTP_NET_SERVER)
                // register the application HTTP processing
                HTTP_APP_Initialize();
#endif // defined(TCPIP_STACK_USE_HTTP_NET_SERVER)

                appData.state = AP_TCPIP_TRANSACT;
            }

            break;

        case AP_TCPIP_TRANSACT:
            if(SYS_TMR_TickCountGet() - startTick >= SYS_TMR_TickCounterFrequencyGet()/2ul)
            {
                startTick = SYS_TMR_TickCountGet();
                LEDstate ^= APP_LED_STATE_ON;
                if(LEDstate == 1)
                {
                    APP_LED_3StateSet();
                }
                else if(LEDstate == 0)
                {
                    APP_LED_3StateClear();
                }
            }

            // if the IP address of an interface has changed
            // display the new value on the system console
            nNets = TCPIP_STACK_NumberOfNetworksGet();

            for(i = 0; i < nNets; i++)
            {
                netH = TCPIP_STACK_IndexToNet(i);
                ipAddr.Val = TCPIP_STACK_NetAddress(netH);
                if(dwLastIP[i].Val != ipAddr.Val)
                {
                    dwLastIP[i].Val = ipAddr.Val;
                    SYS_CONSOLE_PRINT("%s IP Address: %d.%d.%d.%d \r\n",
                            TCPIP_STACK_NetNameGet(netH),
                            ipAddr.v[0], ipAddr.v[1], ipAddr.v[2], ipAddr.v[3]);
                }
            }

            break;

        default:
            break;
    }

}

static void modbus_poll(void)
{       
    switch( modbus_get_poll() )
    {
        case MODBUS_RHR_CMD:   // ?????? holding ????????
//////////////////////////// ?????? HOLDING //////////////////////////
           // holding_reg_write(register_address,U16 data)
              holding_reg_write(0, modbus_var++);
              unsigned int i;
              for (i=0; i<123; i++)
              {
                  holding_reg_write(0, modbus_var++);
              }
              holding_reg_write(1,web_var_1);
              holding_reg_write(2,web_var_2);
              
              if (modbus_var > 65000) modbus_var = 0;
              modbus_rhr_answer(); // ????? ?? ??????
        break;
//////////////////////////// ?????? HOLDING //////////////////////////
        case MODBUS_WSR_CMD:  // ?????? holding ????????
              modbus_wsr_answer();  // ????? ?? ??????;
              //holding_reg_write(get_wr_reg_addr(), get_wr_reg_val());   // ???? ?????????? ???????? ? modbus_wsr_answer()
              holding_reg_read(1, &modbus_var);
              
        break;
//////////////////////////// ?????? INPUT ////////////////////////////
        case MODBUS_RIR_CMD:
              input_reg_write(0, 89);
              modbus_rir_answer(); // ????? ?? ??????
        break;
     }
}
// *****************************************************************************
// Section: Application Initialization and State Machine Functions
// *****************************************************************************

void APP_Initialize ( void )
{
    /* Place the application state machine in its initial state. */
    appData.state = AP_MOUNT_DISK;
    
    modbus_init();
}

void APP_Tasks ( void )
{
    HTTP_server_SM();
    modbus_poll();
}

/******************************************************************************/
