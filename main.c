#include <avr\io.h>
#include <util/delay.h>
#include "GPIO.h"
#include "LCD.h"
#include "UART.h"

int main()
{
    LCD_Init();
    UART_Init();
    uint8_t receieved_data;
    GPIO_InitPin(GPIO_B, GPIO_PIN_B0, GPIO_OUTPUT);
    while (1)
    {
        receieved_data = UART_Reciever();
        UART_Sender(receieved_data);
        if (receieved_data == '1')
            GPIO_WritePin(GPIO_B, GPIO_PIN_B0, GPIO_HIGH);
        else if (receieved_data == '0')
            GPIO_WritePin(GPIO_B, GPIO_PIN_B0, GPIO_LOW);
    }
    return 0;
}