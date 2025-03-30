/*
 * mcu1..h
 *
 *  Created on: Oct 28, 2024
 *      Author: saeed
 */

#ifndef MCU1__C_
#define MCU1__C_

#include"lcd.h"
#include"keypad.h"
#include <util/delay.h> /* For the delay functions */
#include <avr/io.h>
#include"uart.h"
#include "gpio.h"
#include "timer0.h"
#include <avr/interrupt.h>
#define MAX_NUM_PASSWORD	5

/*****************Functions prototypes******************************/
void Display(void);
void Open_OR_Check(void);
void Message_Wrong_Pass(void);
void Message_Wrong_Pass_60(void);
void Message_Wrong_Pass_15(void);
void Message_Wrong_Button(void);
/*******************************************************************/
#endif /* MC1_H_ */

