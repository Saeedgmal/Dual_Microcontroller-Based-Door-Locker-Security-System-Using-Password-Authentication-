/*
 * Timer0_pwm.h
 *
 *  Created on: Oct 7, 2024
 *      Author: HP
 */

#ifndef PWM_H_
#define PWM_H_

/*===============includes files=======================*/
#include "std_types.h"
#include "gpio.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define TIMER0_PORT_ID					PORTB_ID
#define TIMER0_PIN_ID					PIN3_ID

/*******************************************************************************
 *                      Functions Prototypes                                   *
 */
void PWM_Timer0_Start(uint8 duty_cycle);

#endif /* PWM_H_ */
