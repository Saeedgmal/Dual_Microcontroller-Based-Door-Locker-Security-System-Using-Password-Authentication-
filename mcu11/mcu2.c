/*
 * mcu2.c
 *
 *  Created on: Oct 28, 2024
 *      Author: saeed
 */

#include "mcu2.h"
#define MAX_STORED_PASSWORD			4

/************************************GLOBAL VARBS*****************************************/
uint8 stored_pass[MAX_STORED_PASSWORD] = { 0 }, *open_check = 0, check_byte = 0,
		count = 0;

uint8 glopal_timer = 0;
Timer_ConfigType Timer_ConfigType_1 = { 0, 31249, TIMER1,F_CPU_256 ,CTC_MODE};
/*equation time counter =(req_time(1s)( /(clock time period))) - 1
 * clock time period = frequency of system = frequency of CPU / N(prescaler)*/

/******************************Functions**************************************/


void Pass_in_EEPROM(void);
void Check_Pass(void);
void Close_OR_Open(void);
void call(void);
void call2(void);
void call3(void);


int main() {
	UART_ConfigType UART_ConfigType_2 = {
	UART_8_BIT_DATA_MODE,
	UART_DISABLE_PARITY,
	UART_1_STOP, baud_9600 };

	I2C_ConfigType I2C_ConfigType_1 = { 0x01, No_PRESCALLER };

	UART_init(&UART_ConfigType_2);

	I2C_init(&I2C_ConfigType_1);
	DcMotor_Init();
	Buzzer_init();
	while (1) {

		check_byte = UART_recieveByte();
		if (check_byte == 'X') {
			Pass_in_EEPROM();
		} else if (check_byte == '+' || (check_byte == '-')) {
			Check_Pass();
		} else if (check_byte == 'N') {
			Close_OR_Open();
		}
	}
}

void Pass_in_EEPROM(void) {
	for (uint8 i = 0; i <= MAX_STORED_PASSWORD; i++) {
		stored_pass[i] = UART_recieveByte();
	}
	for (uint8 i = 0; i <= MAX_STORED_PASSWORD; i++) {
		EEPROM_writeByte((750 + i), (stored_pass[i]));
		_delay_ms(10);
		stored_pass[i] = 0;
	}
}

void Check_Pass(void) {
	uint8 read_pass[MAX_STORED_PASSWORD] = { 0 }, flag = 0;
	for (uint8 i = 0; i <= MAX_STORED_PASSWORD; i++) {
		stored_pass[i] = UART_recieveByte();
		_delay_ms(10);
	}
	for (uint8 i = 0; i <= MAX_STORED_PASSWORD; i++) {
		EEPROM_readByte((750 + i), &(read_pass[i]));
		_delay_ms(10);
		if (read_pass[i] == stored_pass[i]) {
		} else {
			flag = 1;
			break;
		}
	}
	if ((flag == 0) && (check_byte == '+')) {
		/*Motor on*/
		UART_sendByte('A');
		DcMotor_Rotate(ClockWise, 100);

		Timer_init(&Timer_ConfigType_1);
		Timer_setCallBack(call,TIMER1);

	/*
		_delay_ms(15000);
		DcMotor_Rotate(Stop, 0);
		Close_OR_Open();
*/
	} else if ((flag == 0) && (check_byte == '-')) {
		UART_sendByte('Z');
	} else if (flag == 1) {
		count++;
		if (count == 3) {

			UART_sendByte('T');
			Buzzer_on();




			Timer_init(&Timer_ConfigType_1);
			Timer_setCallBack(call2,TIMER1);
	/*
			_delay_ms(60000);
			Buzzer_off();
			*/
		} else {
			UART_sendByte('R');
		}
	}
}

void Close_OR_Open(void) {
	if (PIR_getState() == LOGIC_HIGH) {
		UART_sendByte('B');
	} else if (PIR_getState() == LOGIC_LOW) {
		UART_sendByte('K');
		DcMotor_Rotate(Anti_ClockWise, 100);


		Timer_init(&Timer_ConfigType_1);
		Timer_setCallBack(call3,TIMER1);

		/*
		_delay_ms(15000);
		DcMotor_Rotate(Stop, 0);
		*/
	}
}

void call(void)
{
	glopal_timer++;
	if(glopal_timer == 15)
	{
		glopal_timer = 0;
		Timer_deInit(TIMER1);
		DcMotor_Rotate(stop, 0);
		Close_OR_Open();
	}
}

void call2(void)
{
	glopal_timer++;
	if(glopal_timer == 60)
	{
		glopal_timer = 0;
		Timer_deInit(TIMER1);
		Buzzer_off();
	}
}

void call3(void)
{
	glopal_timer++;
	if(glopal_timer == 15)
	{
		glopal_timer = 0;
		Timer_deInit(TIMER1);
		DcMotor_Rotate(stop, 0);
	}
}
/********************************************************************************/
