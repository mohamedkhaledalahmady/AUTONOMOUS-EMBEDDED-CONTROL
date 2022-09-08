#include <avr\io.h>
#include <util/delay.h>
#include "Operations.h"
#include "GPIO.h"
#include "LCD.h"

int main()
{
    LCD_Init();
    LCD_GO_TO(0, 0);
    LCD_String("Cairo University");
    LCD_GO_TO(4, 1);
    LCD_String("Eco Racing");
    while (1)
    {
    }
    return 0;
}