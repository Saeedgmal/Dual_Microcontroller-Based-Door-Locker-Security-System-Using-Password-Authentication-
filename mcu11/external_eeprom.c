/* Module : 24C16 EEPROM Chip
 * File Name : external_eeprom.h
 *
 *  Created on: Oct 21, 2024
 *      Author: Ahmed Mabrouk
 */

#include "external_eeprom.h"
#include "i2c.h"

uint8 EEPROM_writeByte(uint16 adress, uint8 data) {
	I2C_start();

	if (I2C_getStatus() != TWI_START) {
		return ERROR;
	}

	/* Send the device address, we need to get A8 A9 A10 address bits from the
	 * memory location address and R/W=0 (write) */
	I2C_writeByte((uint8) (0xA0 | ((adress & 0x0700) >> 7)));
	if (I2C_getStatus() != TWI_MT_SLA_W_ACK) {
		return ERROR;
	}

	/* Send the required memory location address */
	I2C_writeByte((uint8) (adress));

	if (I2C_getStatus() != TWI_MT_DATA_ACK) {
		return ERROR;
	}

	/* write byte to eeprom */
	I2C_writeByte(data);
	if (I2C_getStatus() != TWI_MT_DATA_ACK)
		return ERROR;

	/* Send the Stop Bit */
	I2C_stop();

	return SUCCESS;
}

uint8 EEPROM_readByte(uint16 adress, uint8 *data)
{
	I2C_start();

	if (I2C_getStatus() != TWI_START) {
		return ERROR;
	}
	/* Send the device address, we need to get A8 A9 A10 address bits from the
	 * memory location address and R/W=0 (write) */
	I2C_writeByte((uint8) (0xA0 | ((adress & 0x0700) >> 7)));

	if (I2C_getStatus() != TWI_MT_SLA_W_ACK) {
		return ERROR;
	}

	/* Send the required memory location address */
	I2C_writeByte((uint8)(adress));
    /* Send the Repeated Start Bit */
    I2C_start();
    if (I2C_getStatus() != TWI_REP_START)
    {
    	return ERROR;
    }

    /* Send the device address, we need to get A8 A9 A10 address bits from the
     * memory location address and R/W=1 (Read) */
    I2C_writeByte((uint8)((0xA0) | ((adress & 0x0700)>>7) | 1));
    if (I2C_getStatus() != TWI_MT_SLA_R_ACK)
        return ERROR;

    /* Read Byte from Memory without send ACK */
    *data = I2C_readByteWithNACK();
    if (I2C_getStatus() != TWI_MR_DATA_NACK)
        return ERROR;

    /* Send the Stop Bit */
    I2C_stop();

    return SUCCESS;
}
