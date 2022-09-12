#include "UART.h"

void UART_Init()
{
    UCSRB |= 1 << TXEN | 1 << RXEN;                // Enable Transmite bit
    UCSRC |= 1 << UCSZ0 | 1 << UCSZ1 | 1 << URSEL; // 8 bit data
    UBRRL = F_CPU / BAUD_RATE / 16 - 1;            // set baud rate
    // UCSRA |= 1 << U2X;                          // to double Boud Rate at same frequency
}
void UART_Sender(unit8 data)
{
    while (!(UCSRA & 1 << UDRE)) // wait untill transmiited buffer empty
        ;
    UDR = data;
}
uint8_t UART_Reciever()
{
    while (!(UCSRA & 1 << RXC)) // wait untill reviever buffer empty
        ;
    return UDR;
}

void UART_Sender_String(uint8_t *string)
{
    uint8_t index = 0;
    while (string[index])
    {
        UART_Sender(string[index]);
        index++;
    }
}