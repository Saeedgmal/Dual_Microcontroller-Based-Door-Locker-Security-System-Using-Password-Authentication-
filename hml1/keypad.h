/*
 * Module : Keypad
 * File Name : keypad.h
 *
 *  Created on: Oct 4, 2024
 *      Author: Ahmed Mabrouk
 */

#ifndef KEYPAD_H_
#define KEYPAD_H_

/*===============Includes Files================*/
#include "std_types.h"

/*===============Macros================*/
#define KEYPAD_NUM_COLS 4
#define KEYPAD_NUM_ROWS 4


/* Keypad Port configurations */
#define KEYPAD_ROW_PORT_ID         PORTB_ID
#define KEYPAD_FIRST_ROW_PIN_ID    PIN0_ID

#define KEYPAD_COL_PORT_ID                PORTB_ID
#define KEYPAD_FIRST_COL_PIN_ID           PIN4_ID

/*Keypad external pull up resistor (pressed = 0)*/
#define KEYPAD_BUTTON_PRESSED    LOGIC_LOW
#define KEYPAD_BUTTON_RELEASED   LOGIC_HIGH

/*===============Functions Prototypes================*/

/*function to return the number pressed in keypad*/
uint8 KEYPAD_getPressedKey(void);
#endif /* KEYPAD_H_ */
