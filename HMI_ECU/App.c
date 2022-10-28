/*
 ============================================================================
 Name        : App.c
 Author      : Muhammad Hassan
 Description : Human Machine Interface (HMI) for door locker security system
 Date        : 24/10/2022
 ============================================================================
 */


#include "lcd.h"
#include "uart.h"
#include "UART_Lcfg.h"
#include "keypad.h"
#include "util/delay.h"
#include <avr/io.h>
#include "App.h"
#include "timer1.h"
#include "timer1_Lcfg.h"

/*******************************************************************************
 *                         Global Variables                                    *
 *******************************************************************************/
uint8 failTrials=0;
uint8 g_sec=0;

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/
int main(){
	uint8 pass[PASSWORD_SIZE];
	uint8 confirmPass[PASSWORD_SIZE];
	CURRENT_MENU currentMenu=MENU_CREATE_PASS;
	SREG |= (1<<7);
UART_init(&UART_Config);
LCD_init();
Timer1_setCallBack(App_TickProcessing);

/*
 * If you want to start with create password menu for 1 time only
 */

//UART_sendByte(UART_READY_COMMAND);
//switch(UART_receiveByte()){
//case NO_PASS_CREATED:
//	break;
//case HAVE_PASS:
//	currentMenu=MENU_MAIN;
//	break;
//}
	while(1){
		if(failTrials>2){
			/*if fail trials reaches 3 times HMI sends it to control to take action*/
			UART_sendByte(EXCEEDED_TRIALS_COMMAND);
			LCD_clearScreen();
			LCD_moveCursor(0,0);
			LCD_displayString("Alert many");
			LCD_moveCursor(1,0);
			LCD_displayString("incorrect trials!");
			Timer1_init(&Timer1_Config);
			while(g_sec!=14);
			Timer1_deInit();
			g_sec=0;
			failTrials=0;
//			currentMenu = MENU_MAIN;
		}
		switch(currentMenu){
		case MENU_CREATE_PASS:
			LCD_clearScreen();
			LCD_moveCursor(0,0);
			LCD_displayString("Hi, Enter Pass :");
			LCD_moveCursor(1,0);

			insertPass(pass);

			LCD_clearScreen();
			LCD_moveCursor(0,0);
			LCD_displayString("Enter Pass");
			LCD_moveCursor(1,0);
			LCD_displayString("again: ");

			insertPass(confirmPass);
			if(checkPass(pass,confirmPass) == NOT_MATCH ){
				failTrials++;
			}
			else{

		UART_sendByte(CREATE_PASS_COMMAND);
		UART_sendString(pass);
		LCD_clearScreen();
		LCD_moveCursor(0,0);
		LCD_displayString("Please wait...");
		while(UART_receiveByte()!= PROCCESS_DONE_COMMAND);
		currentMenu = MENU_MAIN;
			}
		break;

		case MENU_MAIN:
		LCD_clearScreen();
		LCD_moveCursor(0,0);
		LCD_displayString("+ : Open Door");
		LCD_moveCursor(1,0);
		LCD_displayString("- : Change Pass");
			switch(KEYPAD_getPressedKey()){
			case CHOICE_OPEN_DOOR:
				currentMenu = MENU_OPEN_DOOR;
			break;
			case CHOICE_CHANGE_PASS:
				currentMenu = MENU_CHANGE_PASS;
			break;
			}
		break;
		case MENU_OPEN_DOOR:
		LCD_clearScreen();
		LCD_moveCursor(0,0);
		LCD_displayString("Enter Pass :");
		LCD_moveCursor(1,0);
		insertPass(pass);

		UART_sendByte(CHECK_PASS_COMMAND);
		UART_sendString(pass);
			switch(UART_receiveByte()){
			case CORRECT_PASS_COMMAND:
				LCD_clearScreen();
				LCD_moveCursor(0,0);
				LCD_displayString("Door Opening..");
				UART_sendByte(OPEN_DOOR_COMMAND);
				Timer1_init(&Timer1_Config);
				while(g_sec!=14);
				Timer1_deInit();
				g_sec=0;
//				_delay_ms(18000);
				LCD_moveCursor(0,0);
				LCD_displayString("Door Closing..");
				Timer1_init(&Timer1_Config);
				while(g_sec!=10);
				Timer1_deInit();
				g_sec=0;
//				_delay_ms(15000);
				currentMenu = MENU_MAIN;
				break;
			case WRONG_PASS_COMMAND:
				failTrials++;
				break;
			}
		break;
		case MENU_CHANGE_PASS:
			LCD_clearScreen();
			LCD_moveCursor(0,0);
			LCD_displayString("Enter Pass :");
			LCD_moveCursor(1,0);
			insertPass(pass);

			UART_sendByte(CHECK_PASS_COMMAND);
			UART_sendString(pass);
				switch(UART_receiveByte()){
				case CORRECT_PASS_COMMAND:
					failTrials=0;
					currentMenu = MENU_CREATE_PASS;
					break;
				case WRONG_PASS_COMMAND:
					failTrials++;
					break;
				}
		break;

		}

	}
	return 0;
}


uint8 checkPass(const uint8 * pass,const uint8 * confirmPass){
	uint8 i;
	uint8 matchFlag;
	for(i=0;i<PASSWORD_SIZE;i++){
		if(pass[i]!=confirmPass[i]){
			matchFlag = NOT_MATCH;
			break;
		}
		else
			matchFlag = MATCH;
				}
	return matchFlag;
}


void insertPass(uint8 * pass){
	uint8 i=0;
	_delay_ms(400);
	pass[i]= KEYPAD_getPressedKey();
	LCD_displayCharacter('*');
//	LCD_intgerToString(pass[i]);
	while(pass[i] != ENTER_KEY){
		_delay_ms(400);
		i++;
		pass[i]= KEYPAD_getPressedKey();
		LCD_displayCharacter('*');
//		LCD_intgerToString(pass[i]);
	}
	pass[i]='#';
}
void App_TickProcessing(void){
g_sec++;
}

