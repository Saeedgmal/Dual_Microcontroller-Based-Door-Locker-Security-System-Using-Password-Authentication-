/*
 * Timer0_pwm.c
 *
 *  Created on: Oct 7, 2024
 *      Author: saeed
 */

/*===============includes files=======================*/
#include "avr/io.h"
#include "common_macros.h"
#include "gpio.h"
#include "pwm.h"

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

void PWM_Timer0_Start(uint8 duty_cycle) {
	/*
	 * FOC0 set with zero because it PWM
	 * to select fast PWM mode can set WGM00 and WGM01
	 * to (nin-inverting mode) COM01 set to 1
	 * use 64 pre_scaler by write 1 to CS00 and CS01
	 * */
	SET_BIT(TCCR0, WGM00);
	SET_BIT(TCCR0, WGM01);
	SET_BIT(TCCR0, COM01);
	SET_BIT(TCCR0, CS00);
	SET_BIT(TCCR0, CS01);

	TCNT0 = 0; //initial value to count
	OCR0 = duty_cycle; //speed of motor

	GPIO_setupPinDirection(TIMER0_PORT_ID, TIMER0_PIN_ID, PIN_OUTPUT);
}
