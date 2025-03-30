/* Module : I2C
 * File Name : i2c.h
 *
 *  Created on: Oct 21, 2024
 *      Author: Ahmed Mabrouk
 */

#ifndef I2C_H_
#define I2C_H_

#include "std_types.h"

/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/
/* I2C Status Bits in the TWSR Register */
#define TWI_START         0x08 /* start has been sent */
#define TWI_REP_START     0x10 /* repeated start */
#define TWI_MT_SLA_W_ACK  0x18 /* Master transmit ( slave address + Write request ) to slave + ACK received from slave. */
#define TWI_MT_SLA_R_ACK  0x40 /* Master transmit ( slave address + Read request ) to slave + ACK received from slave. */
#define TWI_MT_DATA_ACK   0x28 /* Master transmit data and ACK has been received from Slave. */
#define TWI_MR_DATA_ACK   0x50 /* Master received data and send ACK to slave. */
#define TWI_MR_DATA_NACK  0x58 /* Master received data but doesn't send ACK to slave. */
/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
typedef enum {
	No_PRESCALLER, PRESCALLER_4, PRESCALLER_16, PRESCALLER_64
} I2C_BaudRateType;

typedef struct {
	uint8 address;
	I2C_BaudRateType bit_rate;
} I2C_ConfigType;

void I2C_init(const I2C_ConfigType *Config_Ptr);
void I2C_start(void);
void I2C_stop(void);
void I2C_writeByte(uint8 data);
uint8 I2C_readByteWithACK(void);
uint8 I2C_readByteWithNACK(void);
uint8 I2C_getStatus(void);

#endif /* I2C_H_ */
