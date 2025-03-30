/*
 * DCMotor.c
 *
 *  Created on: Oct 9, 2024
 *      Author: saeed
 */

#include "DCMotor.h"

#include <avr/io.h>
 /*Description:Initializes the DC motor by setting the direction for the motor pins
 * and stopping the motor at the beginning.
 * */
void DcMotor_Init(void) {
	GPIO_setupPinDirection(FAN_IN1_PORT_ID, FAN_IN1_PIN_ID, PIN_OUTPUT);
	GPIO_setupPinDirection(FAN_IN1_PORT_ID, FAN_IN2_PIN_ID, PIN_OUTPUT);
	GPIO_setupPinDirection(FAN_EN1_PORT_ID, FAN_EN1_PIN_ID, PIN_OUTPUT);

	GPIO_writePin(FAN_IN1_PORT_ID, FAN_IN1_PIN_ID, LOGIC_LOW);
	GPIO_writePin(FAN_IN1_PORT_ID, FAN_IN2_PIN_ID, LOGIC_LOW);
	GPIO_writePin(FAN_EN1_PORT_ID, FAN_EN1_PIN_ID, LOGIC_LOW);
}
/*
 * Description: Controls the motor's state (Clockwise/Anti-Clockwise/Stop)
 * and adjusts the speed based on the input duty cycle.
 * */
void DcMotor_Rotate(DcMotor_State state, uint8 speed) {
	if (state == ClockWise) {
		GPIO_writePin(FAN_IN1_PORT_ID, FAN_IN1_PIN_ID, LOGIC_LOW);
		GPIO_writePin(FAN_IN2_PORT_ID, FAN_IN2_PIN_ID, LOGIC_HIGH);
		speed = (uint8) ((uint32) (FAN_MAX_DUTY_CYCLE * speed) / FAN_MAX_SPEED);
		PWM_Timer0_Start(speed);
	} else if (state == Anti_ClockWise) {
		GPIO_writePin(FAN_IN1_PORT_ID, FAN_IN1_PIN_ID, LOGIC_HIGH);
		GPIO_writePin(FAN_IN2_PORT_ID, FAN_IN2_PIN_ID, LOGIC_LOW);
		speed = (uint8) ((uint32) (FAN_MAX_DUTY_CYCLE * speed) / FAN_MAX_SPEED);
		PWM_Timer0_Start(speed);
	} else if (state == stop) {
		GPIO_writePin(FAN_IN1_PORT_ID, FAN_IN1_PIN_ID, LOGIC_LOW);
		GPIO_writePin(FAN_IN2_PORT_ID, FAN_IN2_PIN_ID, LOGIC_LOW);
		PWM_Timer0_Start(0);
	}
}
