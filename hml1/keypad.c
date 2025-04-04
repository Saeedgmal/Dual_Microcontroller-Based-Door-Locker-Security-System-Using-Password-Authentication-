/* Module : Keypad
 * File Name : keypad.c
 *
 *  Created on: Oct 4, 2024
 *      Author: Ahmed Mabrouk
 */

/*===============Includes Files================*/
#include "keypad.h"
#include "gpio.h"
#include <util/delay.h>
#ifndef STANDARD_KEYPAD

#if (KEYPAD_NUM_COLS == 3)
/*
 * Function responsible for mapping the switch number in the keypad to
 * its corresponding functional number in the proteus for 4x3 keypad
 */
static uint8 KEYPAD_4x3_adjustKeyNumber(uint8 button_number);
#elif (KEYPAD_NUM_COLS == 4)
/*
 * Function responsible for mapping the switch number in the keypad to
 * its corresponding functional number in the proteus for 4x4 keypad
 */
static uint8 KEYPAD_4x4_adjustKeyNumber(uint8 button_number);
#endif

#endif /* STANDARD_KEYPAD */

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/
uint8 KEYPAD_getPressedKey(void) {
	uint8 colmuns, rows;
	/*Setup direction of pins of rows */
	GPIO_setupPinDirection(KEYPAD_ROW_PORT_ID, KEYPAD_FIRST_ROW_PIN_ID + 0,
			PIN_INPUT);
	GPIO_setupPinDirection(KEYPAD_ROW_PORT_ID, KEYPAD_FIRST_ROW_PIN_ID + 1,
			PIN_INPUT);
	GPIO_setupPinDirection(KEYPAD_ROW_PORT_ID, KEYPAD_FIRST_ROW_PIN_ID + 2,
			PIN_INPUT);
	GPIO_setupPinDirection(KEYPAD_ROW_PORT_ID, KEYPAD_FIRST_ROW_PIN_ID + 3,
			PIN_INPUT);

	/*Setup direction of pins of rows */
	GPIO_setupPinDirection(KEYPAD_COL_PORT_ID, KEYPAD_FIRST_COL_PIN_ID + 0,
			PIN_INPUT);
	GPIO_setupPinDirection(KEYPAD_COL_PORT_ID, KEYPAD_FIRST_COL_PIN_ID + 1,
			PIN_INPUT);
	GPIO_setupPinDirection(KEYPAD_COL_PORT_ID, KEYPAD_FIRST_COL_PIN_ID + 2,
			PIN_INPUT);

#if (KEYPAD_NUM_COLS == 4)
	GPIO_setupPinDirection(KEYPAD_COL_PORT_ID,KEYPAD_FIRST_COL_PIN_ID + 3,PIN_INPUT);
	#endif

	while (1)/*pooling Technic to waiting to the button pressed */
	{
		for (rows = 0; rows < KEYPAD_NUM_ROWS; rows++) {
			/*
			 * Each time setup the direction for all keypad port as input pins,
			 * except this row will be output pin
			 */
			GPIO_setupPinDirection(KEYPAD_ROW_PORT_ID,
					(KEYPAD_FIRST_ROW_PIN_ID + rows), PIN_OUTPUT);

			/*Write  pressed on all columns of this row */
			GPIO_writePin(KEYPAD_ROW_PORT_ID, (KEYPAD_FIRST_ROW_PIN_ID + rows),
			KEYPAD_BUTTON_PRESSED);

			/*looping about all columns in this row*/
			for (colmuns = 0; colmuns < KEYPAD_NUM_COLS; colmuns++) {
				/* Check if the switch is pressed in this column */
				if (KEYPAD_BUTTON_PRESSED
						== (GPIO_readPin(KEYPAD_COL_PORT_ID,
								(KEYPAD_FIRST_COL_PIN_ID + colmuns)))) {
#if (KEYPAD_NUM_COLS == 3)
#ifdef STANDARD_KEYPAD
							return ((rows*KEYPAD_NUM_COLS)+colmuns+1);
						#else
					return (KEYPAD_4x3_adjustKeyNumber(
							(rows * KEYPAD_NUM_COLS) + colmuns + 1));
#endif

#elif (KEYPAD_NUM_COLS == 4)
						#ifdef STANDARD_KEYPAD
							return ((rows*KEYPAD_NUM_COLS)+colmuns+1);
						#else
							return (KEYPAD_4x4_adjustKeyNumber((rows * KEYPAD_NUM_COLS) + colmuns + 1));
						#endif
					#endif
				}
			}
			GPIO_setupPinDirection(KEYPAD_ROW_PORT_ID,KEYPAD_FIRST_ROW_PIN_ID+rows,PIN_INPUT);
			_delay_ms(5); /* Add small delay to fix CPU load issue in proteus */
		}
	}
}

#ifndef STANDARD_KEYPAD

#if (KEYPAD_NUM_COLS == 3)
/*
 * Description :
 * Update the keypad pressed button value with the correct one in keypad 4x3 shape
 */
static uint8 KEYPAD_4x3_adjustKeyNumber(uint8 button_number) {
	uint8 keypad_button = 0;
	switch (button_number) {
	case 10:
		keypad_button = '*'; // ASCII Code of *
		break;
	case 11:
		keypad_button = 0;
		break;
	case 12:
		keypad_button = '#'; // ASCII Code of #
		break;
	default:
		keypad_button = button_number;
		break;
	}
	return keypad_button;
}
#elif (KEYPAD_NUM_COLS == 4)
/*
 * Description :
 * Update the keypad pressed button value with the correct one in keypad 4x4 shape
 */
static uint8 KEYPAD_4x4_adjustKeyNumber(uint8 button_number)
{
	uint8 keypad_button = 0;

	switch (button_number) {
	case 1: keypad_button = 7;
			break;
	case 2: keypad_button = 8;
			break;
	case 3: keypad_button = 9;
			break;
	case 4: keypad_button = '%'; // ASCII Code of %
			break;
	case 5: keypad_button = 4;
			break;
	case 6: keypad_button = 5;
			break;
	case 7: keypad_button = 6;
			break;
	case 8: keypad_button = '*'; /* ASCII Code of '*' */
			break;
	case 9: keypad_button = 1;
			break;
	case 10: keypad_button = 2;
			break;
	case 11: keypad_button = 3;
			break;
	case 12: keypad_button = '-'; /* ASCII Code of '-' */
			break;
	case 13: keypad_button = 'C';  /* ASCII of Enter */
			break;
	case 14: keypad_button = 0;
			break;
	case 15: keypad_button = '='; /* ASCII Code of '=' */
			break;
	case 16: keypad_button = '+'; /* ASCII Code of '+' */
			break;
	default: keypad_button = button_number;
			break;
	}
	return keypad_button;
}
#endif

#endif /* STANDARD_KEYPAD */
