/*
 * GPIO.c
 *
 *  Created on: Apr 17, 2022
 *      Author: MG
 */
#include "GPIO.h"
// define input or output pin
unit8 GPIO_InitPin(unit8 port, unit8 pin, unit8 direction)
{
	unit8 state = GPIO_SUCCESS;
	if (port > 3 || pin > 7 || direction > 1)
		state = GPIO_FAILED;
	else
	{
		switch (port)
		{
		case GPIO_A:
			if (direction == GPIO_LOW)
				CLEAR_Pin(DDRA, pin);
			else
				SET_PIN(DDRA, pin);
			break;
		case GPIO_B:
			if (direction == GPIO_LOW)
				CLEAR_Pin(DDRB, pin);
			else
				SET_PIN(DDRB, pin);
			break;
		case GPIO_C:
			if (direction == GPIO_LOW)
				CLEAR_Pin(DDRC, pin);
			else
				SET_PIN(DDRC, pin);
			break;
		case GPIO_D:
			if (direction == GPIO_LOW)
				CLEAR_Pin(DDRD, pin);
			else
				SET_PIN(DDRD, pin);
			break;
		}
	}
	return state;
}
unit8 GPIO_WritePin(unit8 port, unit8 pin, unit8 value)
{
	unit8 state = GPIO_SUCCESS;
	if (port > 3 || pin > 7 || value > 1)
		state = GPIO_FAILED;
	switch (port)
	{
	case GPIO_A:
		if (value == GPIO_LOW)
			CLEAR_Pin(PORTA, pin);
		else
			SET_PIN(PORTA, pin);
		break;
	case GPIO_B:
		if (value == GPIO_LOW)
			CLEAR_Pin(PORTB, pin);
		else
			SET_PIN(PORTB, pin);
		break;
	case GPIO_C:
		if (value == GPIO_LOW)
			CLEAR_Pin(PORTC, pin);
		else
			SET_PIN(PORTC, pin);
		break;
	case GPIO_D:
		if (value == GPIO_LOW)
			CLEAR_Pin(PORTD, pin);
		else
			SET_PIN(PORTD, pin);
		break;
	}
	return state;
}
unit8 GPIO_GetPin(unit8 port, unit8 pin)
{
	unit8 state = GPIO_SUCCESS;
	if (port > 3 || pin > 7)
		state = GPIO_FAILED;
	switch (port)
	{
	case GPIO_A:
		return GET_Pin(PINA, pin);
		break;
	case GPIO_B:
		return GET_Pin(PINB, pin);
		break;
	case GPIO_C:
		return GET_Pin(PINC, pin);
		break;
	case GPIO_D:
		return GET_Pin(PIND, pin);
		break;
	}
	return state;
}
unit8 GPIO_ALL_PORT_OUTPUT(unit8 port)
{
	unit8 state = GPIO_SUCCESS;
	if (port > 3)
		state = GPIO_FAILED;
	switch (port)
	{
	case GPIO_A:
		DDRA = 0xff;
		break;
	case GPIO_B:
		DDRB = 0xff;
		break;
	case GPIO_C:
		DDRC = 0xff;
		break;
	case GPIO_D:
		DDRD = 0xff;
		break;
	}
	return state;
}
unit8 GPIO_WritePin_ALL(unit8 port, unit8 value)
{
	unit8 state = GPIO_SUCCESS;
	if (port > 3)
		state = GPIO_FAILED;
	switch (port)
	{
	case GPIO_A:
		PORTA = value;
		break;
	case GPIO_B:
		PORTB = value;
		break;
	case GPIO_C:
		PORTC = value;
		break;
	case GPIO_D:
		PORTD = value;
		break;
	}
	return state;
}
void GPIO_WritePin_4_last_nipple(unit8 port, unit8 value, unit8 Pin_D4, unit8 Pin_D5, unit8 Pin_D6, unit8 Pin_D7)
{
	// 1234 5678
	switch (port)
	{
	case GPIO_A:
		GPIO_WritePin(GPIO_A, Pin_D7, (value >> 7) & 1);
		GPIO_WritePin(GPIO_A, Pin_D6, (value >> 6) & 1);
		GPIO_WritePin(GPIO_A, Pin_D5, (value >> 5) & 1);
		GPIO_WritePin(GPIO_A, Pin_D4, (value >> 4) & 1);
		// PORTA = value & 0xf0;	//1234 0000
		break;
	case GPIO_B:
		GPIO_WritePin(GPIO_B, Pin_D7, (value >> 7) & 1);
		GPIO_WritePin(GPIO_B, Pin_D6, (value >> 6) & 1);
		GPIO_WritePin(GPIO_B, Pin_D5, (value >> 5) & 1);
		GPIO_WritePin(GPIO_B, Pin_D4, (value >> 4) & 1);
		// PORTB = value & 0xf0;
		break;
	case GPIO_C:
		GPIO_WritePin(GPIO_C, Pin_D7, (value >> 7) & 1);
		GPIO_WritePin(GPIO_C, Pin_D6, (value >> 6) & 1);
		GPIO_WritePin(GPIO_C, Pin_D5, (value >> 5) & 1);
		GPIO_WritePin(GPIO_C, Pin_D4, (value >> 4) & 1);
		// PORTC = value & 0xf0;
		break;
	case GPIO_D:
		GPIO_WritePin(GPIO_D, Pin_D7, (value >> 7) & 1);
		GPIO_WritePin(GPIO_D, Pin_D6, (value >> 6) & 1);
		GPIO_WritePin(GPIO_D, Pin_D5, (value >> 5) & 1);
		GPIO_WritePin(GPIO_D, Pin_D4, (value >> 4) & 1);
		// PORTD = value & 0xf0;
		break;
	}
}
void GPIO_WritePin_4_first_nipple(unit8 port, unit8 value, unit8 Pin_D4, unit8 Pin_D5, unit8 Pin_D6, unit8 Pin_D7)
{
	// xxxx xxxx
	//  1234 5678
	switch (port)
	{
	case GPIO_A:
		GPIO_WritePin(GPIO_A, Pin_D7, (value >> 3) & 1);
		GPIO_WritePin(GPIO_A, Pin_D6, (value >> 2) & 1);
		GPIO_WritePin(GPIO_A, Pin_D5, (value >> 1) & 1);
		GPIO_WritePin(GPIO_A, Pin_D4, (value >> 0) & 1);
		// PORTA = value << 4;	// 5678 0000
		break;
	case GPIO_B:
		GPIO_WritePin(GPIO_B, Pin_D7, (value >> 3) & 1);
		GPIO_WritePin(GPIO_B, Pin_D6, (value >> 2) & 1);
		GPIO_WritePin(GPIO_B, Pin_D5, (value >> 1) & 1);
		GPIO_WritePin(GPIO_B, Pin_D4, (value >> 0) & 1);
		// PORTB = value << 4;
		break;
	case GPIO_C:
		GPIO_WritePin(GPIO_C, Pin_D7, (value >> 3) & 1);
		GPIO_WritePin(GPIO_C, Pin_D6, (value >> 2) & 1);
		GPIO_WritePin(GPIO_C, Pin_D5, (value >> 1) & 1);
		GPIO_WritePin(GPIO_C, Pin_D4, (value >> 0) & 1);
		// PORTC = value << 4;
		break;
	case GPIO_D:
		GPIO_WritePin(GPIO_D, Pin_D7, (value >> 3) & 1);
		GPIO_WritePin(GPIO_D, Pin_D6, (value >> 2) & 1);
		GPIO_WritePin(GPIO_D, Pin_D5, (value >> 1) & 1);
		GPIO_WritePin(GPIO_D, Pin_D4, (value >> 0) & 1);
		// PORTD = value << 4;
		break;
	}
}
