/*
 * Registers.h
 *
 *  Created on: Sep 24, 2021
 *      Author: Mohamed Khaled Alahadmy
 */

#ifndef EMBEDDED_MOHAMED_H_
#define EMBEDDED_MOHAMED_H_

// Data Direction Registers
#define DDRA (*(volatile unsigned char *)0x3A)
#define DDRB (*(volatile unsigned char *)0x37)
#define DDRC (*(volatile unsigned char *)0x34)
#define DDRD (*(volatile unsigned char *)0x31)
// PORTS
#define PORTA (*(volatile unsigned char *)0x3B)
#define PORTB (*(volatile unsigned char *)0x38)
#define PORTC (*(volatile unsigned char *)0x35)
#define PORTD (*(volatile unsigned char *)0x32)
// PINS
#define PINA (*(volatile unsigned char *)0x39)
#define PINB (*(volatile unsigned char *)0X36)
#define PINC (*(volatile unsigned char *)0x33)
#define PIND (*(volatile unsigned char *)0x30)
// defines
#define PIN0 0
#define PIN1 1
#define PIN2 2
#define PIN3 3
#define PIN4 4
#define PIN5 5
#define PIN6 6
#define PIN7 7
#endif /* EMBEDDED_MOHAMED_H_ */
