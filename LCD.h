#ifndef LCD_H
#define LCD_H
#include "data_types.h"
#include "GPIO.h"

// Mode Configration
#define LCD_Select_Mode LCD_4_MODE

// LCD PINS
#define LCD_RS_PIN GPIO_PIN_A0
#define LCD_RW_PIN GPIO_PIN_A1
#define LCD_E_PIN GPIO_PIN_A2

// LCd PORTS
#define LCD_RS_PORT GPIO_A
#define LCD_RW_PORT GPIO_A
#define LCD_E_PORT GPIO_A

// LCD Data PINS
#define LCD_DATA_PORT GPIO_B

// LCD Command Codes
#define LCD_CLEAR 0x01
#define LCD_Return_Home 0x02
#define LCD_4_MODE 0x28
#define LCD_8_MODE 0x38
#define LCD_FIRTE_LINE 0x80
#define LCD_SECOND_LINE 0xC0
#define LCD_DISPLAY_ON_CURSOR_BLINKING 0x0E
#define LCD_DISPLAY_ON_CURSOR_OFF 0x0C


// Functions
void LCD_Init();
void LCD_Command(unit8);
void LCD_Data(unit8);
void LCD_String(unit8 *);
void LCD_GO_TO(uint8_t, uint8_t);
static void LCD_GET_Second_Nipple(uint8_t, uint8_t);
static void LCD_GET_First_Nipple(uint8_t, uint8_t);
static void LCD_Define_Nipple_Output(uint8_t);
void LCD_Number(uint8_t);
#endif