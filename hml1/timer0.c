/*
 * timer.c
 *
 *  Created on: Oct 28, 2024
 *      Author: saeed
 */
#include "timer0.h"
#include"Common_Macros.h"
#include"std_types.h"
#include <avr/io.h>
#include <avr/interrupt.h>

static CallbackFunction g_callBackPtr = NULL_PTR;



ISR(TIMER0_COMP_vect) {
	if (g_callBackPtr != NULL_PTR) {
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callBackPtr)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}

ISR(TIMER0_OVF_vect) {
	if (g_callBackPtr != NULL_PTR) {
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callBackPtr)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}

ISR(TIMER2_COMP_vect) {
	if (g_callBackPtr != NULL_PTR) {
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callBackPtr)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}

ISR(TIMER2_OVF_vect) {
	if (g_callBackPtr != NULL_PTR) {
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callBackPtr)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}

ISR(TIMER1_COMPA_vect) {
	if (g_callBackPtr != NULL_PTR) {
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callBackPtr)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}

ISR(TIMER1_OVF_vect) {
	if (g_callBackPtr != NULL_PTR) {
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callBackPtr)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}


void Timer_init(const Timer_ConfigType *Config_Ptr) {
	SET_BIT(SREG, 7);
		if ((Config_Ptr->timer_ID) == TIMER0) {
			if ((Config_Ptr->timer_mode) == PWM_MODE) {
				/*Choose Mode*/
				SET_BIT(TCCR0, WGM00);
				SET_BIT(TCCR0, WGM01);
				/* to (nin-inverting mode) COM01 set to 1 to Compare Output Mode, Fast PWM Mode*/
				SET_BIT(TCCR0, COM01);
				/*Choose Pre_scaller*/
				TCCR0 = (TCCR0 & 0xF8) | (Config_Ptr->timer_clock);
				TCNT0 = Config_Ptr->timer_InitialValue; //initial value to count
				/*Duty Cycle for speed of Motor*/
				OCR0 = Config_Ptr->timer_compare_MatchValue;
			} else if ((Config_Ptr->timer_mode) ==   CTC_MODE) {
				/*Active non PWM Mode*/
				SET_BIT(TCCR0, FOC0);
				/*Choose Mode*/
				/* Normal port operation, OC0 disconnected */
				SET_BIT(TCCR0, WGM01);
				/*Choose Pre_scaller*/
				TCCR0 = (TCCR0 & 0xF8) | (Config_Ptr->timer_clock);
				TCNT0 = Config_Ptr->timer_InitialValue; //initial value to count
				OCR0 = Config_Ptr->timer_compare_MatchValue;
				/*Timer/Counter0 Output Compare Match Interrupt Enable */
				SET_BIT(TIMSK, OCIE0);
			} else if ((Config_Ptr->timer_mode) == NORMAL_MODE) {
				/*Active non PWM Mode*/
				SET_BIT(TCCR0, FOC0);
				/*Choose Pre_scaller*/
				TCCR0 = (TCCR0 & 0xF8) | (Config_Ptr->timer_clock);
				TCNT0 = Config_Ptr->timer_InitialValue; //initial value to count
				/*Timer/Counter0 Overflow Interrupt Enable*/
				SET_BIT(TIMSK, TOIE0);
			}
		} else if ((Config_Ptr->timer_ID) == TIMER1) {
			if ((Config_Ptr->timer_mode) == PWM_MODE) {
				/*Compare Output Mode, Fast PWM(1) AS non-inverting mode*/
				SET_BIT(TCCR1A, COM1A1);
				SET_BIT(TCCR1A, COM1B1);
				/*The FOC1A/FOC1B bits are only active when
				 * the WGM13:0 bits specifies a non-PWM mode*/

				/*Fast PWM, 8-bit   MODE 5*/
				SET_BIT(TCCR1A, WGM10);
				SET_BIT(TCCR1B, WGM12);

				/*
				 * insert the required clock value in the first three bits (CS10, CS11 and CS12)
				 * of TCCR1B Register
				 */
				TCCR1B = (TCCR1B & 0xF8) | (Config_Ptr->timer_clock);

				/*Initial value for timer 1*/
				TCNT1 = Config_Ptr->timer_InitialValue;

				OCR1A = Config_Ptr->timer_compare_MatchValue;
			} else if ((Config_Ptr->timer_mode) ==  CTC_MODE) {
				/*Compare Output Mode, non-PWM Normal port operation
				 *  COM1A1/COM1A0/COM1B1/COM1B0 = 0 */

				/*The FOC1A/FOC1B bits are only active when
				 * the WGM13:0 bits specifies a non-PWM mode*/
				SET_BIT(TCCR1A, FOC1A);
				/*choose MODE 4 =====> Top = OCR1A ====>*/
				SET_BIT(TCCR1B, WGM12);

				/*
				 * insert the required clock value in the first three bits (CS10, CS11 and CS12)
				 * of TCCR1B Register
				 */
				TCCR1B = (TCCR1B & 0xF8) | (Config_Ptr->timer_clock);

				/*Initial value for timer 1*/
				TCNT1 = Config_Ptr->timer_InitialValue;

				OCR1A = Config_Ptr->timer_compare_MatchValue;

				/*enable interrupt of timer 1 FOR compare output capture */
				SET_BIT(TIMSK, OCIE1A);
			} else if ((Config_Ptr->timer_mode) == NORMAL_MODE) {
				/*non-PWM Normal port operation
				 *  COM1A1/COM1A0/COM1B1/COM1B0 = 0 */
				SET_BIT(TCCR1A, FOC1A);
				/*Normal MODE (MODE 0)WGM10/WGM11/WGM12/WGM13 = 0*/

				/*
				 * insert the required clock value in the first three bits (CS10, CS11 and CS12)
				 * of TCCR1B Register
				 */
				TCCR1B = (TCCR1B & 0xF8) | (Config_Ptr->timer_clock);

				/*Initial value for timer 1*/
				TCNT1 = Config_Ptr->timer_InitialValue;

				SET_BIT(TIMSK, TOIE1);
			}
		} else if ((Config_Ptr->timer_ID) == TIMER2) {
			if ((Config_Ptr->timer_mode) == PWM_MODE) {

			} else if ((Config_Ptr->timer_mode) ==     CTC_MODE) {

			} else if ((Config_Ptr->timer_mode) == NORMAL_MODE) {

			}
		}}

void Timer_deInit(Timer_ID_Type timer_type) {
	switch (timer_type) {
	    case TIMER0:
	            // Stop Timer0 by clearing the control register
         TCCR0 = 0x00; // Clear Timer/Counter Control Register
         TCNT0 = 0x00; // Clear Timer/Counter Register
         TIFR |= (1 << TOV0); // Clear overflow flag
        break;

        case TIMER1:
	      // Stop Timer1 by clearing the control register
	       TCCR1A = 0x00; // Clear Timer/Counter Control Register A
	       TCCR1B = 0x00; // Clear Timer/Counter Control Register B
	       TCNT1 = 0x00; // Clear Timer/Counter Register
	       TIFR |= (1 << TOV1); // Clear overflow flag
	    break;

	    case TIMER2:
	            // Stop Timer2 by clearing the control register
	    	TCCR2 = 0x00; // Clear Timer/Counter Control Register
	        TCNT2 = 0x00; // Clear Timer/Counter Register
	        TIFR |= (1 << TOV2); // Clear overflow flag
	    break;

	        default:
	            // Handle invalid timer ID if necessary
	            break;
	    }
}

void Timer_setCallBack(CallbackFunction a_ptr, Timer_ID_Type a_timer_ID) {
    switch (a_timer_ID) {
        case TIMER0:
        	g_callBackPtr = a_ptr;
            break;
        case TIMER1:
        	g_callBackPtr = a_ptr;
            break;
        case TIMER2:
        	g_callBackPtr = a_ptr;
            break;
    }
}
