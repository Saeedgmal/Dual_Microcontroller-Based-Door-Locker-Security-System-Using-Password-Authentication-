/******************************************************************************
 *
 * Module: UART
 *
 * File Name: uart.h
 *
 * Description: Header file for the UART AVR driver
 *
 * Author: Ahmed Mabrouk
 *
 *******************************************************************************/

#ifndef UART_H_
#define UART_H_

#include "std_types.h"

typedef enum {
	baud_10 = 10,
	baud_300 = 300,
	baud_600 = 600,
	baud_1200 = 1200,
	baud_2400 = 2400,
	baud_4800 = 4800,
	baud_9600 = 9600,
	baud_14400 = 14400,
	baud_19200 = 19200,
	baud_38400 = 38400,
	baud_57600 = 57600,
	baud_115200 = 115200,
	baud_128000 = 128000,
	baud_256000 = 256000
} baud_rate_values;

typedef struct {
	uint8 bit_data;
	uint16 parity;
	uint32 stop_bit;
	baud_rate_values baud_rate;
} UART_ConfigType;

#define UART_1_STOP 				0
#define UART_2_STOP                 1

#define UART_DISABLE_PARITY         0
#define UART_EVEN					2
#define UART_ODD					1

#define UART_8_BIT_DATA_MODE		0

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
/*
 * Description :
 * Functional responsible for Initialize the UART device by:
 * 1. Setup the Frame format like number of data bits, parity bit type and number of stop bits.
 * 2. Enable the UART.
 * 3. Setup the UART baud rate.
 */
void UART_init(const UART_ConfigType *Config_Ptr);

/*
 * Description :
 * Functional responsible for send byte to another UART device.
 */
void UART_sendByte(const uint8 data);

/*
 * Description :
 * Functional responsible for receive byte from another UART device.
 */
uint8 UART_recieveByte(void);

/*
 * Description :
 * Send the required string through UART to the other UART device.
 */
void UART_sendString(const uint8 *Str);

/*
 * Description :
 * Receive the required string until the '#' symbol through UART from the other UART device.
 */
void UART_receiveString(uint8 *Str); // Receive until #

#endif /* UART_H_ */
