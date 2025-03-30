/*
 * pir.c
 *
 *  Created on: Oct 28, 2024
 *      Author: saeed
 */


#include "pir.h"
#include"std_types.h"
#include <avr/io.h>



void PIR_init(void) {
    // Set PIR_PIN as input
    DDRD &= ~(1 << PIR_PIN); // Clear the bit to set as input
}

uint8 PIR_getState(void) {
    // Read the state of the PIR sensor
    return (PIND & (1 << PIR_PIN)) ? 1 : 0; // Return 1 if motion detected, otherwise 0
}
