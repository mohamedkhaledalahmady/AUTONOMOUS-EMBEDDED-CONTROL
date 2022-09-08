/*
 * Operations.h
 *
 *  Created on: Apr 5, 2022
 *      Author: Mohamed Khaled Alahamdy
 */

#ifndef OPERATIONS_H_
#define OPERATIONS_H_

#define SET_PIN(Reg, index) Reg |= (1 << index)
#define CLEAR_Pin(Reg, index) Reg &= (~(1 << index))
#define GET_Pin(Reg, index) Reg >> index & 1
#define TOGELL_Pin(Reg, index) Reg = Reg ^ (1 << index)

#endif /* OPERATIONS_H_ */
