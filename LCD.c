#include "LCD.h"

void LCD_Init()
{
    // Inital output pins
    GPIO_InitPin(LCD_RS_PORT, LCD_RS_PIN, GPIO_OUTPUT);
    GPIO_InitPin(LCD_RW_PORT, LCD_RW_PIN, GPIO_OUTPUT);
    GPIO_InitPin(LCD_E_PORT, LCD_E_PIN, GPIO_OUTPUT);

    // Inital Commands
    if (LCD_Select_Mode == LCD_8_MODE)
    {
        GPIO_ALL_PORT_OUTPUT(LCD_DATA_PORT);
        // commands to tell LCD that we will use 8 bit mode
        LCD_Command(LCD_8_MODE);
        LCD_Command(LCD_DISPLAY_ON_CURSOR_BLINKING);
        LCD_Command(LCD_CLEAR);
    }
    else if (LCD_Select_Mode == LCD_4_MODE)
    {
        LCD_Define_Nipple_Output(LCD_DATA_PORT);
        // commands to tell LCD that we will use 4 bit mode
        LCD_Command(0x33);
        LCD_Command(0x32);
        LCD_Command(LCD_4_MODE);
        LCD_Command(LCD_DISPLAY_ON_CURSOR_BLINKING);
        LCD_Command(LCD_CLEAR);
    }
    _delay_ms(2);
}

void LCD_Command(unit8 command)
{
    // Configration to send command
    GPIO_WritePin(LCD_RS_PORT, LCD_RS_PIN, GPIO_LOW);
    GPIO_WritePin(LCD_RW_PORT, LCD_RW_PIN, GPIO_LOW);

    if (LCD_Select_Mode == LCD_8_MODE)
    {
        // Send Command
        GPIO_WritePin_ALL(LCD_DATA_PORT, command);

        // Enable latch pulse
        GPIO_WritePin(LCD_E_PORT, LCD_E_PIN, GPIO_HIGH);
        _delay_us(1);
        GPIO_WritePin(LCD_E_PORT, LCD_E_PIN, GPIO_LOW);
        _delay_us(1);

        // 100 us to let LCD module run the command
        _delay_us(100);
    }
    else if (LCD_Select_Mode == LCD_4_MODE)
    {
        // send first nipple (MS)
        LCD_GET_Second_Nipple(LCD_DATA_PORT, command);

        // Enable latch pulse
        GPIO_WritePin(LCD_E_PORT, LCD_E_PIN, GPIO_HIGH);
        _delay_us(1);
        GPIO_WritePin(LCD_E_PORT, LCD_E_PIN, GPIO_LOW);
        _delay_us(1);

        // send second nipple (LS)
        LCD_GET_First_Nipple(LCD_DATA_PORT, command);

        // Enable latch pulse
        GPIO_WritePin(LCD_E_PORT, LCD_E_PIN, GPIO_HIGH);
        _delay_us(1);
        GPIO_WritePin(LCD_E_PORT, LCD_E_PIN, GPIO_LOW);
        _delay_us(1);

        // 100 us to let LCD module run the command
        _delay_us(100);
    }
}

void LCD_Data(unit8 data)
{
    // Configration to send command
    GPIO_WritePin(LCD_RS_PORT, LCD_RS_PIN, GPIO_HIGH);
    GPIO_WritePin(LCD_RW_PORT, LCD_RW_PIN, GPIO_LOW);

    if (LCD_Select_Mode == LCD_8_MODE)
    {
        // Send Command
        GPIO_WritePin_ALL(LCD_DATA_PORT, data);

        // Enable latch pulse
        GPIO_WritePin(LCD_E_PORT, LCD_E_PIN, GPIO_HIGH);
        _delay_us(1);
        GPIO_WritePin(LCD_E_PORT, LCD_E_PIN, GPIO_LOW);
        _delay_us(1);

        // 100 us to let LCD module run the command
        _delay_us(100);
    }
    else if (LCD_Select_Mode == LCD_4_MODE)
    {
        // send first nipple (MS)
        LCD_GET_Second_Nipple(LCD_DATA_PORT, data);

        // Enable latch pulse
        GPIO_WritePin(LCD_E_PORT, LCD_E_PIN, GPIO_HIGH);
        _delay_us(1);
        GPIO_WritePin(LCD_E_PORT, LCD_E_PIN, GPIO_LOW);
        _delay_us(1);

        // send second nipple (LS)
        LCD_GET_First_Nipple(LCD_DATA_PORT, data);

        // Enable latch pulse
        GPIO_WritePin(LCD_E_PORT, LCD_E_PIN, GPIO_HIGH);
        _delay_us(1);
        GPIO_WritePin(LCD_E_PORT, LCD_E_PIN, GPIO_LOW);
        _delay_us(1);

        // 100 us to let LCD module run the command
        _delay_us(100);
    }
}

void LCD_String(unit8 *string)
{
    uint8_t index = 0;
    while (string[index])
    {
        LCD_Data(string[index]);
        _delay_ms(1);
        index++;
    }
}

void LCD_GO_TO(uint8_t x, uint8_t y)
{
    uint8_t cell = y == 0 ? 0x80 + x : 0xC0 + x;
    LCD_Command(cell);
}

static void LCD_GET_Second_Nipple(uint8_t port, uint8_t value)
{
    switch (port)
    {
    case GPIO_A:
        GPIO_WritePin(GPIO_A, GPIO_PIN_A4, GET_Pin(value, 4));
        GPIO_WritePin(GPIO_A, GPIO_PIN_A5, GET_Pin(value, 5));
        GPIO_WritePin(GPIO_A, GPIO_PIN_A6, GET_Pin(value, 6));
        GPIO_WritePin(GPIO_A, GPIO_PIN_A7, GET_Pin(value, 7));
        break;
    case GPIO_B:
        GPIO_WritePin(GPIO_B, GPIO_PIN_B4, GET_Pin(value, 4));
        GPIO_WritePin(GPIO_B, GPIO_PIN_B5, GET_Pin(value, 5));
        GPIO_WritePin(GPIO_B, GPIO_PIN_B6, GET_Pin(value, 6));
        GPIO_WritePin(GPIO_B, GPIO_PIN_B7, GET_Pin(value, 7));
        break;
    case GPIO_C:
        GPIO_WritePin(GPIO_C, GPIO_PIN_C4, GET_Pin(value, 4));
        GPIO_WritePin(GPIO_C, GPIO_PIN_C5, GET_Pin(value, 5));
        GPIO_WritePin(GPIO_C, GPIO_PIN_C6, GET_Pin(value, 6));
        GPIO_WritePin(GPIO_C, GPIO_PIN_C7, GET_Pin(value, 7));
        break;
    case GPIO_D:
        GPIO_WritePin(GPIO_D, GPIO_PIN_D4, GET_Pin(value, 4));
        GPIO_WritePin(GPIO_D, GPIO_PIN_D5, GET_Pin(value, 5));
        GPIO_WritePin(GPIO_D, GPIO_PIN_D6, GET_Pin(value, 6));
        GPIO_WritePin(GPIO_D, GPIO_PIN_D7, GET_Pin(value, 7));
        break;
    default:
        break;
    }
}

static void LCD_GET_First_Nipple(uint8_t port, uint8_t value)
{
    value = value << 4;
    switch (port)
    {
    case GPIO_A:
        GPIO_WritePin(GPIO_A, GPIO_PIN_A4, GET_Pin(value, 4));
        GPIO_WritePin(GPIO_A, GPIO_PIN_A5, GET_Pin(value, 5));
        GPIO_WritePin(GPIO_A, GPIO_PIN_A6, GET_Pin(value, 6));
        GPIO_WritePin(GPIO_A, GPIO_PIN_A7, GET_Pin(value, 7));
        break;
    case GPIO_B:
        GPIO_WritePin(GPIO_B, GPIO_PIN_B4, GET_Pin(value, 4));
        GPIO_WritePin(GPIO_B, GPIO_PIN_B5, GET_Pin(value, 5));
        GPIO_WritePin(GPIO_B, GPIO_PIN_B6, GET_Pin(value, 6));
        GPIO_WritePin(GPIO_B, GPIO_PIN_B7, GET_Pin(value, 7));
        break;
    case GPIO_C:
        GPIO_WritePin(GPIO_C, GPIO_PIN_C4, GET_Pin(value, 4));
        GPIO_WritePin(GPIO_C, GPIO_PIN_C5, GET_Pin(value, 5));
        GPIO_WritePin(GPIO_C, GPIO_PIN_C6, GET_Pin(value, 6));
        GPIO_WritePin(GPIO_C, GPIO_PIN_C7, GET_Pin(value, 7));
        break;
    case GPIO_D:
        GPIO_WritePin(GPIO_D, GPIO_PIN_D4, GET_Pin(value, 4));
        GPIO_WritePin(GPIO_D, GPIO_PIN_D5, GET_Pin(value, 5));
        GPIO_WritePin(GPIO_D, GPIO_PIN_D6, GET_Pin(value, 6));
        GPIO_WritePin(GPIO_D, GPIO_PIN_D7, GET_Pin(value, 7));
        break;
    default:
        break;
    }
}

static void LCD_Define_Nipple_Output(uint8_t port)
{
    switch (port)
    {
    case GPIO_A:
        DDRA |= 1 << PIN4;
        DDRA |= 1 << PIN5;
        DDRA |= 1 << PIN6;
        DDRA |= 1 << PIN7;

        break;
    case GPIO_B:
        DDRB |= 1 << PIN4;
        DDRB |= 1 << PIN5;
        DDRB |= 1 << PIN6;
        DDRB |= 1 << PIN7;

        break;
    case GPIO_C:
        DDRC |= 1 << PIN4;
        DDRC |= 1 << PIN5;
        DDRC |= 1 << PIN6;
        DDRC |= 1 << PIN7;

        break;
    case GPIO_D:
        DDRD |= 1 << PIN4;
        DDRD |= 1 << PIN5;
        DDRD |= 1 << PIN6;
        DDRD |= 1 << PIN7;

        break;
    default:
        break;
    }
}

void LCD_Number(uint8_t num)
{
    uint8_t array[4];
    uint8_t i = 0;
    while (num)
    {
        array[i] = num % 10;
        i++;
        num /= 10;
    }
    int8_t j;
    if (i == 1)
        LCD_Data('0');
    if (i == 0)
        LCD_String("00");
    for (j = i - 1; j >= 0; j--)
        LCD_Data(array[j] + '0');
}