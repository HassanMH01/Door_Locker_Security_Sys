/*
 ============================================================================
 Name        : App.c
 Author      : Muhammad Hassan
 Description : Control ECU for door locker security system
 Date        : 24/10/2022
 ============================================================================
 */

#include "DC_Motor.h"
#include "uart.h"
#include "UART_Lcfg.h"
#include "external_eeprom.h"
#include "Buzzer.h"
#include "App.h"
#include "twi.h"
#include "TWI_Lcfg.h"
#include "timer1.h"
#include "timer1_Lcfg.h"
#include <avr/io.h>
#include <util/delay.h>

	uint8 g_sec=0;
int main(){

	uint8 matchFlag;
//	uint8 passFlag=0;
	uint8 pass[PASSWORD_SIZE];
	uint8 receivedPass[PASSWORD_SIZE];
	uint8 i;
	SREG |= (1<<7);
DCMotor_Init();
UART_init(&UART_Config);
Buzzer_init();
TWI_init(&TWI_Config);
Timer1_setCallBack(App_TickProcessing);

/*
 * If you want to clear password from EEPROM memory every time
 */

//for(i=0;i<PASSWORD_SIZE;i++){
//				EEPROM_writeByte((0x0311+i),0xFF);
//				_delay_ms(10);
//			}

/*
 * If you want to start with create password menu for 1 time only
 */

//while(UART_receiveByte()!= UART_READY_COMMAND);
//EEPROM_readByte(0x0311,&passFlag);
//if(passFlag==0xFF)
//	UART_sendByte(NO_PASS_CREATED);
//else
//	UART_sendByte(HAVE_PASS);

	while(1){

		switch(UART_receiveByte()){
		case CREATE_PASS_COMMAND:
			UART_receiveString(pass);
			EEPROM_writeString(0x311,pass,PASSWORD_SIZE);
			UART_sendByte(PROCCESS_DONE_COMMAND);
			break;
		case CHECK_PASS_COMMAND:
			UART_receiveString(receivedPass);
			for(i=0;i<5;i++){
				EEPROM_readByte((0x0311+i),(pass+i));
				if(pass[i]!=receivedPass[i]){
					matchFlag = NOT_MATCH;
					break;
				}
				else
				matchFlag = MATCH;
				}
			switch (matchFlag){
			case MATCH:

				UART_sendByte(CORRECT_PASS_COMMAND);
				break;
			case NOT_MATCH:

				UART_sendByte(WRONG_PASS_COMMAND);
				break;
			}
			break;
		case OPEN_DOOR_COMMAND:

			DcMotor_Rotate(CW,100);
			Timer1_init(&Timer1_Config);
			while(g_sec!=10);
			Timer1_deInit();
			g_sec=0;
//			_delay_ms(15000);
			DcMotor_Rotate(OFF,0);
			Timer1_init(&Timer1_Config);
			while(g_sec!=4);
			Timer1_deInit();
			g_sec=0;
//			_delay_ms(2000);
			DcMotor_Rotate(ACW,100);
			Timer1_init(&Timer1_Config);
			while(g_sec!=10);
			Timer1_deInit();
			g_sec=0;
//			_delay_ms(15000);
			DcMotor_Rotate(OFF,0);

			break;
		case EXCEEDED_TRIALS_COMMAND:
			Buzzer_ON();
			Timer1_init(&Timer1_Config);
			while(g_sec!=14);
			Timer1_deInit();
			g_sec=0;
//			_delay_ms(10000);
			Buzzer_OFF();
			break;
		}

	}

	return 0;
}

void App_TickProcessing(void){
g_sec++;
}
