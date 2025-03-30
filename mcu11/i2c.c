/* Module : I2C
 * File Name : i2c.c
 *
 *  Created on: Oct 21, 2024
 *      Author: Ahmed Mabrouk
 */

#include "i2c.h"
#include <avr/io.h>
#include "common_macros.h"

/*=================Functions implementation=============== */

void I2C_init(const I2C_ConfigType *Config_Ptr) {

	TWBR = 0x02;
	TWSR = Config_Ptr->bit_rate;

	/* Two Wire Bus address my address if any master device want to call me: 0x1 (used in case this MC is a slave device)
	 General Call Recognition: Off */
	TWAR = Config_Ptr->address;

	TWCR = (1 << TWEN); /* enable TWI */
}

void I2C_start(void) {
	/*
	 * Clear the TWINT flag before sending the start bit TWINT=1
	 * send the start bit by TWSTA=1
	 * Enable TWI Module TWEN=1
	 */

	TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);

	/* Wait for TWINT flag set in TWCR Register (start bit is send successfully) */
	while (BIT_IS_CLEAR(TWCR, TWINT)) {
	}
}
void I2C_stop(void) {
	/*
	 * Clear the TWINT flag before sending the stop bit TWINT=1
	 * send the stop bit by TWSTO=1
	 * Enable TWI Module TWEN=1
	 */
	TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);

}
void I2C_writeByte(uint8 data) {
	/* Put data On TWI data Register */
	TWDR = data;

	/*
	 * Clear the TWINT flag before sending the data TWINT=1
	 * Enable TWI Module TWEN=1
	 */
	TWCR = (1 << TWINT) | (1 << TWEN);

	/* Wait for TWINT flag set in TWCR Register(data is send successfully) */
	while (BIT_IS_CLEAR(TWCR, TWINT)) {
	}
}
uint8 I2C_readByteWithACK(void) {
	/*
	 * Clear the TWINT flag before reading the data TWINT=1
	 * Enable sending ACK after reading or receiving data TWEA=1
	 * Enable TWI Module TWEN=1
	 */
	TWCR = (1 << TWINT) | (1 << TWEA) | (1 << TWEN);

	/* Wait for TWINT flag set in TWCR Register (data received successfully) */
	while (BIT_IS_CLEAR(TWCR, TWINT)) {
	}

	/* Read Data */
	return TWDR;
}
uint8 I2C_readByteWithNACK(void) {
	/*
	 * Clear the TWINT flag before reading the data TWINT=1
	 * Enable TWI Module TWEN=1
	 */
	TWCR = (1 << TWINT) | (1 << TWEN);

	/* Wait for TWINT flag set in TWCR Register (data received successfully) */
	while (BIT_IS_CLEAR(TWCR, TWINT)) {
	}

	/* Read Data */
	return TWDR;
}
uint8 I2C_getStatus(void) {
	uint8 status;
	/* masking to eliminate first 3 bits and get the last 5 bits (status bits) */
	status = (TWSR & 0xF8);
	return status;
}
