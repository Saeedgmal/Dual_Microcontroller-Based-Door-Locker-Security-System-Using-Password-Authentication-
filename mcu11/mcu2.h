/*
 * mcu2.h
 *
 *  Created on: Nov 1, 2024
 *      Author: saeed
 */

#ifndef MCU2_H_
#define MCU2_H_

#include "pir.h"
#include"std_types.h"
#include <avr/io.h>
#include"Buzzer.h"
#include "gpio.h"
#include "uart.h"
#include "i2c.h"
#include "timer0.h"
#include "external_eeprom.h"
#include "DCMOTOR.h"
#include<util/delay.h>
#include "pwm.h"
#define MAX_STORED_PASSWORD			4

#define CREATED_PASS 0x10
#define RENTERED_CREATED_PASS 0x11
#define PASSWORD_CHECKING_FINISHED 0x12

#define PASSWORDS_MATCH 0x13
#define PASSWORDS_DONT_MATCH 0x14

#define OPTION_MENU 0x15

#define  OPEN_DOOR 0x16

#define USER_ENTERED_PASS 0x17
#define USER_ACCESS	0x18

#define PASSWORDS_IS_CORRECT 0x19

#define CHANGE_PASS 0x20

#define UNBLOCK_THE_SYSTEM 0x21



/********************************FUNCTIONS PROTOTYPES****************************/

void Pass_in_EEPROM(void);
void Check_Pass(void);
void Close_OR_Open(void);
void call(void);
void call2(void);
void call3(void);

#endif /* MCU2_H_ */
