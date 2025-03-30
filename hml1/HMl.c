/*
 * HMI_ECU.c
 *
 *  Created on: Oct 28, 2024
 *      Author: saeed
 */
#include "mcu1.h"

uint16 key1 = 0, first_pass[MAX_NUM_PASSWORD] = { 0 }, ///array key
		second_pass[MAX_NUM_PASSWORD] = { 0 }, flag = 0;
uint8 check_pass[MAX_NUM_PASSWORD] = { 0 };
uint8 wrong_correct = 0, dis_flag = 0,G_timer = 0;

/*UART Configration */

UART_ConfigType UART_ConfigType_1 = {
	UART_8_BIT_DATA_MODE,
	UART_DISABLE_PARITY,
	UART_1_STOP, baud_9600 };
Timer_ConfigType Timer_ConfigType_1 = { 0, 31249, TIMER1,F_CPU_256 ,CTC_MODE};
/*equation time counter =(req_time(1s)( /(clock time period))) - 1
 * clock time period = frequency of system = frequency of CPU / N(prescaler)*/

int main() {

	UART_init(&UART_ConfigType_1);
	LCD_init();
	LCD_displayString("Door Lock system");
	Timer_init(&Timer_ConfigType_1);
	Timer_setCallBack(Message_Wrong_Pass,TIMER1);

	while (1) {
		wrong_correct = UART_recieveByte();
		if (wrong_correct == 'Z') {
			Display();
		} else if (wrong_correct == 'R') {
			LCD_clearScreen();
			LCD_displayString("  Wrong in ");
			LCD_moveCursor(1, 0);
			LCD_displayString("  Password");
			Timer_init(&Timer_ConfigType_1);
			Timer_setCallBack(Message_Wrong_Pass,TIMER1);
		} else if (wrong_correct == 'A') {
			LCD_clearScreen();
			LCD_displayString("Door Unlocking");
			LCD_moveCursor(1, 3);
			LCD_displayString("Please wait");
		} else if (wrong_correct == 'B') {
			if (dis_flag == 0) {
				dis_flag = 1;
				LCD_clearScreen();
				LCD_displayString("Wait for people");
				LCD_moveCursor(1, 3);
				LCD_displayString("to Enter");
				UART_sendByte('N');
			} else {
				UART_sendByte('N');
			}
		} else if (wrong_correct == 'K') {
			LCD_clearScreen();
			LCD_displayString("   Door is");
			LCD_moveCursor(1, 3);
			LCD_displayString("locking");


			Timer_init(&Timer_ConfigType_1);
			Timer_setCallBack(Message_Wrong_Pass_15,TIMER1);



/*
			_delay_ms(15000);
			Open_OR_Check();
*/
		} else if (wrong_correct == 'T') {
			LCD_clearScreen();
			LCD_displayString(" System Locked");
			LCD_moveCursor(1, 0);
			LCD_displayString("Wait for 1 Min");



			Timer_init(&Timer_ConfigType_1);
			Timer_setCallBack(Message_Wrong_Pass_60,TIMER1);
/*
			_delay_ms(60000);
			Open_OR_Check();
			*/
		}
	}
}

void Display(void) {
	LCD_clearScreen();
	LCD_displayString("Plz enter pass:");
	LCD_moveCursor(1, 0);
	for (uint8 i = 0; i <= MAX_NUM_PASSWORD; i++) {
		key1 = KEYPAD_getPressedKey();
		first_pass[i] = key1;
		if (i == MAX_NUM_PASSWORD) {

		} else {
			LCD_displayCharacter('*');
		}
		_delay_ms(500);
	}
	if (first_pass[5] == 'C') {
		LCD_clearScreen();
		LCD_displayString("Plz re-enter the");
		LCD_moveCursor(1, 0);
		LCD_displayString("same pass:");
		LCD_moveCursor(1, 10);
		for (uint8 i = 0; i <= MAX_NUM_PASSWORD; i++) {///////////////////
			key1 = KEYPAD_getPressedKey();
			second_pass[i] = key1;
			if (i == MAX_NUM_PASSWORD) {
			} else {
				LCD_displayCharacter('*');
			}
			_delay_ms(500);
		}
		if (second_pass[5] == 67) {
			for (uint8 i = 0; i < MAX_NUM_PASSWORD; i++) {
				if (first_pass[i] == second_pass[i]) {

				} else {
					flag = 1;
					break;
				}
			}
			if (flag == 1) {
				LCD_clearScreen();
				LCD_displayString("Two Passwords");
				LCD_moveCursor(1,0);
				LCD_displayString("Not Identical");
				Timer_init(&Timer_ConfigType_1);
				Timer_setCallBack(Message_Wrong_Pass,TIMER1);
			} else {
				UART_sendByte('X');
				for (uint8 j = 0; j < MAX_NUM_PASSWORD; j++) {
					UART_sendByte(first_pass[j]);
					_delay_ms(10);
				}
				Open_OR_Check();
			}
		} else {
			return Display();
		}
	} else {
		return Display();
	}
}

void Open_OR_Check(void) {
	LCD_clearScreen();
	LCD_displayString("+ : Open Door");
	LCD_moveCursor(1, 0);
	LCD_displayString("- : Change Pass");
	key1 = KEYPAD_getPressedKey();
	if ((key1 == '+') || (key1 == '-')) {
		UART_sendByte(key1);
		_delay_ms(500);
		LCD_clearScreen();
		LCD_displayString("Plz enter old");
		LCD_moveCursor(1, 0);
		LCD_displayString("pass:");
		LCD_moveCursor(1, 5);
		key1 = 0;
		for (uint8 i = 0; i <= MAX_NUM_PASSWORD; i++) {
			first_pass[i] = KEYPAD_getPressedKey();
			if (i == MAX_NUM_PASSWORD) {
			} else {

				// LCD_intgerToString(first_pass[i]);

				LCD_displayCharacter('*');
					}
			_delay_ms(500);
					}
		if (first_pass[MAX_NUM_PASSWORD] != 'C') {
	LCD_clearScreen();
	LCD_displayString("  Wrong in ");
    LCD_moveCursor(1, 0);
	LCD_displayString("Enter button");
	Timer_init(&Timer_ConfigType_1);
	Timer_setCallBack(Message_Wrong_Button,TIMER1);

		} else {
		for (uint8 i = 0; i <= MAX_NUM_PASSWORD; i++) {
			UART_sendByte(first_pass[i]);
			_delay_ms(10);
				}
					}
			} else {
			return Open_OR_Check();
			}
		}

void Message_Wrong_Pass(void)
{
	G_timer++;
	Timer_deInit(TIMER1);
	if((G_timer == 1)  )
	{
		G_timer = 0;
		if((wrong_correct == 'R'))
		{
			Open_OR_Check();
		}else
		{
			Display();
		}
	}
}

void Message_Wrong_Button(void)
{
	G_timer++;
	if((G_timer == 1) && ((first_pass[MAX_NUM_PASSWORD] != 'C')))
	{
		G_timer = 0;
		Timer_deInit(TIMER1);
		Open_OR_Check();
	}
}
void Message_Wrong_Pass_15(void)
{
	G_timer++;
	if(G_timer == 15)
	{
		G_timer = 0;
		Timer_deInit(TIMER1);
		Open_OR_Check();
	}
}

void Message_Wrong_Pass_60(void)
{
	G_timer++;
	if(G_timer == 60)
	{
		G_timer = 0;
		Timer_deInit(TIMER1);
		Open_OR_Check();
	}
}
