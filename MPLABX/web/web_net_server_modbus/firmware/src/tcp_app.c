#include "tcp_app.h"

static TCP_APP_DATA tcpAppData;

static bool useAlternativeIP = false;

static bool _isDefaultIPInitialized = false;
static IPV4_ADDR defaultIP;
static IPV4_ADDR defaultIPMask;
static IPV4_ADDR defaultGatewayIP;
static IPV4_ADDR alternativeIP;
static IPV4_ADDR alternativeIPMask;
static IPV4_ADDR alternativeGatewayIP;

void TCP_APP_Initialize ( void )
{
    /* Place the TCP state machine in its initial state. */
    tcpAppData.state = APP_TCPIP_WAIT_INIT;
}

TCP_APP_STATES get_tcp_app_state (void)
{
    return tcpAppData.state;
}

void tcp_app_set_alternative_ip (IPV4_ADDR IP, IPV4_ADDR mask, IPV4_ADDR gateway)
{
    alternativeIP.Val = IP.Val;
    alternativeIPMask.Val = mask.Val;
    alternativeGatewayIP.Val = gateway.Val;
}

IPV4_ADDR tcp_app_get_alternative_ip (void)
{
    return alternativeIP;
}
IPV4_ADDR tcp_app_get_alternative_ip_mask (void)
{
    return alternativeIPMask;
}
IPV4_ADDR tcp_app_get_alternative_ip_gateway (void)
{
    return alternativeGatewayIP;
}

IPV4_ADDR tcp_app_get_default_ip (void)
{
    return defaultIP;
}
IPV4_ADDR tcp_app_get_default_ip_mask (void)
{
    return defaultIPMask;
}
IPV4_ADDR tcp_app_get_default_ip_gateway (void)
{
    return defaultGatewayIP;
}

bool tcp_app_use_alternative_ip (void)
{
    if (_isDefaultIPInitialized == false)
    {
        return false;
    }
    
    useAlternativeIP = true;
    tcpAppData.state = APP_TCPIP_CLOSING_CONNECTION;
    
    return true;
}

bool tcp_app_use_default_ip (void)
{
    if (_isDefaultIPInitialized == false)
    {
        return false;
    }
    
    useAlternativeIP = false;
    tcpAppData.state = APP_TCPIP_CLOSING_CONNECTION;
    
    return true;
}

void TCP_APP_Tasks (void)
{
    SYS_STATUS          tcpipStat;
    const char          *netName, *netBiosName;
    static IPV4_ADDR    dwLastIP[2] = { {-1}, {-1} };
    IPV4_ADDR           ipAddr;
    int                 i, nNets;
    TCPIP_NET_HANDLE    netH;
    
    SYS_CMD_READY_TO_READ();
    switch(tcpAppData.state)
    {
        case APP_TCPIP_WAIT_INIT:
            tcpipStat = TCPIP_STACK_Status(sysObj.tcpip);
            if(tcpipStat < 0)
            {   // some error occurred
                SYS_CONSOLE_MESSAGE(" APP: TCP/IP stack initialization failed!\r\n");
                tcpAppData.state = APP_TCPIP_ERROR;
            }
            else if(tcpipStat == SYS_STATUS_READY)
            {
                // now that the stack is ready we can check the
                // available interfaces
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
#endif  // defined(TCPIP_STACK_USE_NBNS)

                }
                tcpAppData.state = APP_TCPIP_WAIT_FOR_IP;

            }
            break;

        case APP_TCPIP_WAIT_FOR_IP:

            // if the IP address of an interface has changed
            // display the new value on the system console
            nNets = TCPIP_STACK_NumberOfNetworksGet();

            for (i = 0; i < nNets; i++)
            {
                netH = TCPIP_STACK_IndexToNet(i);
                if(!TCPIP_STACK_NetIsReady(netH))
                {
                    return;    // interface not ready yet!
                }
                
                if (_isDefaultIPInitialized == true)  // РІС‹Р±РѕСЂ IP
                {
                    if (useAlternativeIP == true)
                    {
                        TCPIP_STACK_NetAddressSet(netH, &alternativeIP, &alternativeIPMask, true);
                        TCPIP_STACK_NetAddressGatewaySet(netH, &alternativeGatewayIP);
                    } else {
                        TCPIP_STACK_NetAddressSet(netH, &defaultIP, &defaultIPMask, true);
                        TCPIP_STACK_NetAddressGatewaySet(netH, &defaultGatewayIP);
                    }
                } else {
                    defaultIP.Val = TCPIP_STACK_NetAddress(netH);
                    defaultIPMask.Val = TCPIP_STACK_NetMask(netH);
                    defaultGatewayIP.Val = TCPIP_STACK_NetAddressGateway(netH);

                    alternativeIP.Val = defaultIP.Val;
                    alternativeIPMask.Val = defaultIPMask.Val;
                    alternativeGatewayIP.Val = defaultGatewayIP.Val;
                    
                    _isDefaultIPInitialized = true;
                }
                
                ipAddr.Val = TCPIP_STACK_NetAddress(netH);
                if(dwLastIP[i].Val != ipAddr.Val)
                {
                    dwLastIP[i].Val = ipAddr.Val;

                    SYS_CONSOLE_MESSAGE(TCPIP_STACK_NetNameGet(netH));
                    SYS_CONSOLE_MESSAGE(" IP Address: ");
                    SYS_CONSOLE_PRINT("%d.%d.%d.%d \r\n", ipAddr.v[0], ipAddr.v[1], ipAddr.v[2], ipAddr.v[3]);
                }
                tcpAppData.state = APP_TCPIP_OPENING_SERVER;
            }
            break;
        case APP_TCPIP_OPENING_SERVER:
        {
            SYS_CONSOLE_PRINT("Waiting for Client Connection on port: %d\r\n", SERVER_PORT);
            tcpAppData.socket = TCPIP_TCP_ServerOpen(IP_ADDRESS_TYPE_IPV4, SERVER_PORT, 0);
            if (tcpAppData.socket == INVALID_SOCKET)
            {
                SYS_CONSOLE_MESSAGE("Couldn't open server socket\r\n");
                break;
            }
            tcpAppData.state = APP_TCPIP_WAIT_FOR_CONNECTION;
        }
        break;

        case APP_TCPIP_WAIT_FOR_CONNECTION:
        {
            if (!TCPIP_TCP_IsConnected(tcpAppData.socket))
            {
                return;
            }
            else
            {
                // We got a connection
                tcpAppData.state = APP_TCPIP_SERVING_CONNECTION;
                SYS_CONSOLE_MESSAGE("Received a connection\r\n");
            }
        }
        break;

        case APP_TCPIP_SERVING_CONNECTION:
        {
            if (!TCPIP_TCP_IsConnected(tcpAppData.socket))
            {
                tcpAppData.state = APP_TCPIP_CLOSING_CONNECTION;
                SYS_CONSOLE_MESSAGE("Connection was closed\r\n");
                break;
            }
            int16_t wMaxGet, wMaxPut, wCurrentChunk;
            // Figure out how many bytes have been received and how many we can transmit.
            wMaxGet = TCPIP_TCP_GetIsReady(tcpAppData.socket);	// Get TCP RX FIFO byte count
            wMaxPut = TCPIP_TCP_PutIsReady(tcpAppData.socket);	// Get TCP TX FIFO free space

            wCurrentChunk = 100;
            
            if (wCurrentChunk > wMaxGet)
                wCurrentChunk = wMaxGet;
            modbus_rx_buf_ptr = wCurrentChunk - 1;

            //Transfer the data out of the TCP RX FIFO and into our local processing buffer.
            TCPIP_TCP_ArrayGet(tcpAppData.socket, modbus_rx_buf, wCurrentChunk);

            if (modbus_tx_buf_ptr >= 0) {
                int16_t putCount = modbus_tx_buf_ptr + 1;
                if (putCount > wMaxPut) {  //TODO: РїРѕРґРѕР±РЅР°СЏ РїСЂРѕРІРµСЂРєР° РїСЂРѕСЃС‚Рѕ "СЃСЂРµР¶РµС‚" modbus-РѕС‚РІРµС‚, РµСЃР»Рё TX FIFO TCP РїРµСЂРµРїРѕР»РЅРµРЅ 
                    putCount = wMaxPut;
                }

                TCPIP_TCP_ArrayPut(tcpAppData.socket, modbus_tx_buf, putCount);
                modbus_tx_buf_clear();
            }

            TCPIP_TCP_Flush(tcpAppData.socket);
            // No need to perform any flush.  TCP data in TX FIFO will automatically transmit itself after it accumulates for a while.  If you want to decrease latency (at the expense of wasting network bandwidth on TCP overhead), perform and explicit flush via the TCPFlush() API.
         break;   
        }
        
        
        case APP_TCPIP_CLOSING_CONNECTION:
        {
            // Close the socket connection.
            TCPIP_TCP_Close(tcpAppData.socket);
            tcpAppData.socket = INVALID_SOCKET;
            tcpAppData.state = APP_TCPIP_WAIT_FOR_IP;

        }
        
        break;
        default:
            break;
    }
}