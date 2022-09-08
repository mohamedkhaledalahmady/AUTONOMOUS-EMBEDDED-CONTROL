/*
 * GPIO.h
 *
 *  Created on: Apr 17, 2022
 *      Author: Mohamed Alahamdy
 */

#ifndef GPIO_H_
#define GPIO_H_

#include "Registers.h"
#include "Operations.h"
#include "data_types.h"
#include <util/delay.h>

#define GPIO_A 0
#define GPIO_B 1
#define GPIO_C 2
#define GPIO_D 3

#define GPIO_PIN_A0 0
#define GPIO_PIN_A1 1
#define GPIO_PIN_A2 2
#define GPIO_PIN_A3 3
#define GPIO_PIN_A4 4
#define GPIO_PIN_A5 5
#define GPIO_PIN_A6 6
#define GPIO_PIN_A7 7

#define GPIO_PIN_B0 0
#define GPIO_PIN_B1 1
#define GPIO_PIN_B2 2
#define GPIO_PIN_B3 3
#define GPIO_PIN_B4 4
#define GPIO_PIN_B5 5
#define GPIO_PIN_B6 6
#define GPIO_PIN_B7 7

#define GPIO_PIN_C0 0
#define GPIO_PIN_C1 1
#define GPIO_PIN_C2 2
#define GPIO_PIN_C3 3
#define GPIO_PIN_C4 4
#define GPIO_PIN_C5 5
#define GPIO_PIN_C6 6
#define GPIO_PIN_C7 7

#define GPIO_PIN_D0 0
#define GPIO_PIN_D1 1
#define GPIO_PIN_D2 2
#define GPIO_PIN_D3 3
#define GPIO_PIN_D4 4
#define GPIO_PIN_D5 5
#define GPIO_PIN_D6 6
#define GPIO_PIN_D7 7

#define GPIO_INPUT 0
#define GPIO_OUTPUT 1

#define GPIO_HIGH 1
#define GPIO_LOW 0

#define GPIO_SUCCESS 1
#define GPIO_FAILED 0

unit8 GPIO_InitPin(unit8,unit8,unit8);
unit8 GPIO_WritePin(unit8,unit8,unit8);
unit8 GPIO_GetPin(unit8,unit8);
unit8 GPIO_ALL_PORT_OUTPUT(unit8);
unit8 GPIO_WritePin_ALL(unit8,unit8);
void GPIO_WritePin_4_last_nipple(unit8,unit8,unit8,unit8,unit8,unit8);
void GPIO_WritePin_4_first_nipple(unit8,unit8,unit8,unit8,unit8,unit8);

#endif /* GPIO_H_ */
