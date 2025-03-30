/*
 * DCMotor.h
 *
 *  Created on: Oct 9, 2024
 *      Author: saeed
 */

#ifndef DCMOTOR_H_
#define DCMOTOR_H_
# include "common_macros.h"
# include "gpio.h"
#include "pwm.h"

#define FAN_IN1_PORT_ID					PORTD_ID
#define FAN_IN2_PORT_ID					PORTD_ID
#define FAN_EN1_PORT_ID					PORTB_ID

#define FAN_IN1_PIN_ID					PIN6_ID
#define FAN_IN2_PIN_ID					PIN7_ID
#define FAN_EN1_PIN_ID					PIN3_ID

#define FAN_MAX_DUTY_CYCLE				255
#define FAN_MAX_SPEED					100
typedef enum {
	ClockWise, Anti_ClockWise, stop
} DcMotor_State;
/*******************************************************************************
 *                      Functions Prototypes                                   *
 */
void DcMotor_Init(void);

void DcMotor_Rotate(DcMotor_State state, uint8 speed);

#endif /* DCMOTOR_H_ */
