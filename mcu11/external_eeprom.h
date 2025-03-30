/* Module : 24C16 EEPROM Chip
 * File Name : external_eeprom.h
 *
 *  Created on: Oct 21, 2024
 *      Author: Ahmed Mabrouk
 */

#ifndef EXTERNAL_EEPROM_H_
#define EXTERNAL_EEPROM_H_

#include "std_types.h"

/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/
#define ERROR 0
#define SUCCESS 1

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

uint8 EEPROM_writeByte(uint16 adress, uint8 data);
uint8 EEPROM_readByte(uint16 adress, uint8 *data);

#endif /* EXTERNAL_EEPROM_H_ */
