#ifndef UART_H
#define UART_H
#include "data_types.h"
#include <avr\io.h>

#define F_CPU 8000000UL
#define BAUD_RATE 9600

void UART_Init();
void UART_Sender(unit8);
uint8_t UART_Reciever();
void UART_Sender_String(uint8_t *);

#endif
