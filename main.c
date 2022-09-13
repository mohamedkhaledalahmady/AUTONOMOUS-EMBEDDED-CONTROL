#include <avr\io.h>
#include <util/delay.h>
#include "GPIO.h"
#include "LCD.h"
#include "UART.h"
#include "math.h"
#include <string.h>
#include <avr/interrupt.h>

#define delay 600
#define Success 1
#define Fail 0
#define Data_Frame_Length 8
#define BACKSPACE 8
#define NEWLINE 13

uint8_t seconds, minuts, hours;

typedef struct DC_Motor
{
    float32 speed;     // 0 : 100
    uint8_t direction; // F , B
} DC_Motor;

typedef struct Stepper_Motor
{
    uint8_t angle;     // 0 : 45
    uint8_t direction; // R , L
} Stepper_Motor;

uint8_t str_len(uint8_t *string)
{
    uint8_t count = 0;
    while (string[count])
        count++;
    return count;
}

uint8_t Filter_Data_Frame(uint8_t size, uint8_t receieved_array[], DC_Motor *dc_motor, Stepper_Motor *stepper_motor)
{
    uint8_t receieved_speed;
    DC_Motor dc_temp;
    Stepper_Motor stepper_temp;

    if (size == Data_Frame_Length && receieved_array[Data_Frame_Length - 1] == 'E')
    {
        uint8_t index;
        dc_temp.speed = 0;
        for (index = 0; index <= 2; index++)
        {
            if (receieved_array[index] >= '0' && receieved_array[index] <= '9' && receieved_array[0] <= '1') // must first 3 elements in data fram be numbers
                dc_temp.speed += (receieved_array[index] - '0') * pow(10, 2 - index);
            else
                return Fail;
        }
        if (receieved_array[index] != 'F' && receieved_array[index] != 'B')
            return Fail;
        dc_temp.direction = receieved_array[index];

        stepper_temp.angle = 0;
        if (receieved_array[4] > '4')
        {
            UART_Sender_String("AAAAAAAAAAA");
            return Fail;
        }
        else if (receieved_array[4] == '4' && receieved_array[5] > '5')
        {
            UART_Sender_String("BBBBBBBBBBBBBBB");
            return Fail;
        }
        else
        {
            stepper_temp.angle = (receieved_array[4] - '0') * pow(10, 1);
            stepper_temp.angle += (receieved_array[5] - '0');
        }

        // for (index = 4; index < Data_Frame_Length - 2; index++)
        // {
        //     if (receieved_array[index] >= '0' && receieved_array[index] <= '9')
        //         stepper_temp.angle += (receieved_array[index] - '0') * pow(10, 5 - index);
        //     else
        //         return Fail;
        // }

        if (receieved_array[6] != 'L' && receieved_array[6] != 'R')
            return Fail;
        stepper_temp.direction = receieved_array[6];

        // if everything is ok now change original structs
        dc_motor->speed = dc_temp.speed;         // 0 : 100
        dc_motor->direction = dc_temp.direction; // F or B

        stepper_motor->angle = stepper_temp.angle;         // 0 : 45
        stepper_motor->direction = stepper_temp.direction; // L or R

        return Success;
    }
    return Fail;
}

void Rotate_Right(uint8_t no_of_steps)
{
    // CW C 6 3 9
    uint8_t step;
    uint8_t sequence[] = {0xC0, 0x60, 0x30, 0x90};
    static uint8_t order1 = 0;

    for (step = 0; step < no_of_steps; step++)
    {
        PORTC = sequence[order1];
        order1 = order1 >= 3 ? 0 : order1 + 1;
        _delay_ms(delay);
    }
    Diplay_Time();
}

void Rotate_Left(uint8_t no_of_steps)
{
    // C.C.W 3 6 C 9
    uint8_t step;
    uint8_t sequence[] = {0x30, 0x60, 0xC0, 0x90};
    static uint8_t order2 = 0;
    for (step = 0; step < no_of_steps; step++)
    {
        PORTC = sequence[order2];
        order2 = order2 >= 3 ? 0 : order2 + 1;
        _delay_ms(delay);
    }
    Diplay_Time();
}

ISR(TIMER1_OVF_vect)
{
    seconds++;
    if (seconds > 59)
    {
        minuts++;
        seconds = 0;
    }
    if (minuts > 59)
    {
        hours++;
        minuts = 0;
    }
    Diplay_Time();
}

// ISR(USART_RXC_vect)
// {
//     LCD_GO_TO(0, 0);
//     LCD_Data('1');
//     receieved_data = UDR;
//     UART_Sender(receieved_data);
// }

void Diplay_Time()
{
    LCD_GO_TO(0, 1);
    LCD_String("Time ");
    LCD_Number(hours);
    LCD_Data(':');
    LCD_Number(minuts);
    LCD_Data(':');
    LCD_Number(seconds);
    LCD_String(" AM");
}

int main()
{
    TCNT1 = 0xC2F7;      // 0x85EE;      // for delay 1 second
    TIMSK |= 1 << TOIE1; // enable timer 1 overflow interrupt
    TCCR1B = 0x04;       // for prescaler 256

    DDRB |= 1 << PIN3;
    TCCR0 = 0x62; // configuration for timer 0 in PWM phase control mode, non inverting, clk/8

    LCD_Init();
    UART_Init();

    uint8_t receieved_data;
    uint8_t receieved_array[Data_Frame_Length + 1];
    DC_Motor dc_Motor = {0, 'F'};
    Stepper_Motor stepper_Motor = {0, 'R'};
    uint8_t i = 0;

    GPIO_InitPin(GPIO_D, GPIO_PIN_D6, GPIO_OUTPUT); // led for correct indecation
    GPIO_InitPin(GPIO_D, GPIO_PIN_D7, GPIO_OUTPUT); // led for error indecation

    GPIO_InitPin(GPIO_B, GPIO_PIN_B1, GPIO_OUTPUT); // Input 1 for dc motor
    GPIO_InitPin(GPIO_B, GPIO_PIN_B2, GPIO_OUTPUT); // Input 2 for dc motor

    GPIO_InitPin(GPIO_C, GPIO_PIN_C4, GPIO_OUTPUT); // A for stepper motor
    GPIO_InitPin(GPIO_C, GPIO_PIN_C5, GPIO_OUTPUT); // B for LCD
    GPIO_InitPin(GPIO_C, GPIO_PIN_C6, GPIO_OUTPUT); // C for LCD
    GPIO_InitPin(GPIO_C, GPIO_PIN_C7, GPIO_OUTPUT); // D for LCD

    GPIO_InitPin(GPIO_A, GPIO_PIN_A4, GPIO_OUTPUT); // D4 for LCD
    GPIO_InitPin(GPIO_A, GPIO_PIN_A5, GPIO_OUTPUT); // D5 for LCD
    GPIO_InitPin(GPIO_A, GPIO_PIN_A6, GPIO_OUTPUT); // D6 for LCD
    GPIO_InitPin(GPIO_A, GPIO_PIN_A7, GPIO_OUTPUT); // D7 for LCD

    // inital run dc motor forward (CCW) with speed 50%
    GPIO_WritePin(GPIO_B, GPIO_PIN_B1, GPIO_LOW);
    GPIO_WritePin(GPIO_B, GPIO_PIN_B2, GPIO_HIGH);
    OCR0 = ceil(dc_Motor.speed * 2.55f);

    // Display default data on LCD
    LCD_String("sp:00%F dir: +00");
    LCD_GO_TO(0, 1);
    LCD_String("Time 00:00:00 AM");

    sei();
    while (1)
    {
        receieved_data = UART_Reciever();
        UART_Sender(receieved_data);

        if (receieved_data == NEWLINE)
        {
            if (Filter_Data_Frame(i, receieved_array, &dc_Motor, &stepper_Motor) == Success)
            {
                UART_Sender_String("1. DC Motor {");
                uint8_t j = 0;
                for (j = 0; j < 3; j++)
                    UART_Sender(receieved_array[j]);
                UART_Sender('%');
                UART_Sender_String(" , ");
                UART_Sender(receieved_array[3]);
                UART_Sender_String("}");
                UART_Sender(NEWLINE);
                UART_Sender_String("2. Stepper Motor {");
                for (j = 4; j < 6; j++)
                    UART_Sender(receieved_array[j]);
                UART_Sender_String(" , ");
                UART_Sender(receieved_array[6]);
                UART_Sender_String("}");
                UART_Sender(NEWLINE);

                // Dispaly Data On LCD
                LCD_Command(LCD_CLEAR);
                LCD_String("S:");
                uint8_t index;
                if (receieved_array[0] != '0')
                    LCD_Data(receieved_array[0]);
                for (index = 1; index <= 2; index++)
                    LCD_Data(receieved_array[index]);
                LCD_Data('%');
                LCD_Data(dc_Motor.direction);
                LCD_String(" dir: ");
                stepper_Motor.direction == 'L' ? LCD_Data('-') : LCD_Data('+');
                for (index = 4; index <= 5; index++)
                    LCD_Data(receieved_array[index]);

                // indecation leds
                GPIO_WritePin(GPIO_D, GPIO_PIN_D6, GPIO_HIGH);
                GPIO_WritePin(GPIO_D, GPIO_PIN_D7, GPIO_LOW);

                // Control DC Motor
                if (dc_Motor.direction == 'B')
                {
                    GPIO_WritePin(GPIO_B, GPIO_PIN_B1, GPIO_HIGH);
                    GPIO_WritePin(GPIO_B, GPIO_PIN_B2, GPIO_LOW);
                }
                else if (dc_Motor.direction == 'F')
                {
                    GPIO_WritePin(GPIO_B, GPIO_PIN_B1, GPIO_LOW);
                    GPIO_WritePin(GPIO_B, GPIO_PIN_B2, GPIO_HIGH);
                }
                OCR0 = ceil(dc_Motor.speed * 2.55f);

                // Control Stepper Motor
                if (stepper_Motor.direction == 'L')
                    Rotate_Left(stepper_Motor.angle);
                else if (stepper_Motor.direction == 'R')
                    Rotate_Right(stepper_Motor.angle);
            }
            else
            {
                // indecation leds
                GPIO_WritePin(GPIO_D, GPIO_PIN_D6, GPIO_LOW);
                GPIO_WritePin(GPIO_D, GPIO_PIN_D7, GPIO_HIGH);
                // Error Message
                UART_Sender_String("Invalid Data Format use this format (XXXAYYBE)");
                UART_Sender(NEWLINE);
            }

            i = 0;
            receieved_array[Data_Frame_Length - 1] = 'N';
        }
        else
        {
            receieved_array[i] = receieved_data;
            i = i > 10 ? 0 : i + 1;
        }
    }

    return 0;
}
