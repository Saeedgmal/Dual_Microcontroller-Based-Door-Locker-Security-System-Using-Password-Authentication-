/*
 * pir.h
 *
 *  Created on: Oct 28, 2024
 *      Author: saeed
 */

#ifndef PIR_H_
#define PIR_H_

#include <avr/io.h>
#include <stdint.h>
#include"std_types.h"

// Define the pin where the PIR sensor is connected
#define PIR_PIN PC2 // Change this according to your setup

// Function prototypes
void PIR_init(void);
uint8 PIR_getState(void);


#endif /* PIR_H_ */
