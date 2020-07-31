#include "../h/25k80_uart.h"

void UART_init(unsigned char bd_rate_code)
{   
    switch(bd_rate_code)
    {
        case 0: SPBRG1 = 64;   TXSTA1bits.BRGH = 0; break; // 9600
        case 1: SPBRG1 = 129;  TXSTA1bits.BRGH = 1; break; // 19200
        case 2: SPBRG1 = 64;   TXSTA1bits.BRGH = 1; break; // 38400
        case 3: SPBRG1 = 42;   TXSTA1bits.BRGH = 1; break; // 57600
        case 4: SPBRG1 = 21;   TXSTA1bits.BRGH = 1; break; // 115200
        case 5: SPBRG1 = 10;   TXSTA1bits.BRGH = 1; break; // 230400

        default: SPBRG1 = 64;   TXSTA1bits.BRGH = 0; // 9600
    }

    TXSTA1bits.SYNC = 0; // ����������� ����� ��������
    TXSTA1bits.TX9 = 0; // ������� 8 ���
    TXSTA1bits.TXEN = 1; // ��� � ���������� ��������
    //TXSTA1bits.BRGH = 0; // �������� �� ������� ��������


    RCSTA1bits.CREN1 = 1; // �������� ��������
    RCSTA1bits.RX9 = 0; // ����� 8 ���
    RCSTA1bits.SPEN = 1; // ������ ���� ���
    RCSTA1bits.CREN1 = 1; // �������� �������� 
    RCSTA1bits.FERR = 0; // ��� ������ ����������� ��������
    RCSTA1bits.OERR =0;  // ��� ������ ������������ ��������
   

    BAUDCON1bits.RXDTP1 = 0; // ��� ���������� �������� ������ �������������/ �� �������������
    BAUDCON1bits.TXCKP1 = 0; // ��������� ����������� ��� �������� (TXx) �������� ������ �������
    BAUDCON1bits.BRG16 = 0; // 8 ������ Boud Rate ���������

    BAUDCON1bits.ABDEN1 = 0; // ��������� �������� �������� ������ ���������
    //BAUDCON1bits.WUE1 = 1; // ���������� ��������� �� ������� ������ ��������� �������
    PIR1bits.RC1IF = 0;
}

void UART_send_byte(unsigned char byte)
{
    while (TXSTA1bits.TRMT1 == 0);

    // wait to load TXREGx until TRMT is set
   // while(!TXSTA1bits.TRMT1);

    TXREG1bits.TXREG1 = byte;
    __delay_us(100);
}

