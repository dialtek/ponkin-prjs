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

    TXSTA1bits.SYNC = 0; // Асинхронный режим передечи
    TXSTA1bits.TX9 = 0; // Посылка 8 бит
    TXSTA1bits.TXEN = 1; // Бит о готовности передачи
    //TXSTA1bits.BRGH = 0; // Передача на высокой скорости


    RCSTA1bits.CREN1 = 1; // Включить приемник
    RCSTA1bits.RX9 = 0; // Прием 8 бит
    RCSTA1bits.SPEN = 1; // Сериал порт вкл
    RCSTA1bits.CREN1 = 1; // Включить приемник 
    RCSTA1bits.FERR = 0; // Бит ошибки кодирования отключен
    RCSTA1bits.OERR =0;  // Бит ошибки переполнения отключен
   

    BAUDCON1bits.RXDTP1 = 0; // Бит полярности принятых данных инвертируются/ не инвертируются
    BAUDCON1bits.TXCKP1 = 0; // Состояние бездействия для передачи (TXx) является низким уровнем
    BAUDCON1bits.BRG16 = 0; // 8 битный Boud Rate генератор

    BAUDCON1bits.ABDEN1 = 0; // Измерение скорости передачи данных отключено
    //BAUDCON1bits.WUE1 = 1; // Генерирует прерыване по заднему фронту пришедшей посылки
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

