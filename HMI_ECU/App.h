/*
 * App.h
 *
 *  Created on: Oct 25, 2022
 *      Author: Hassa
 */

#ifndef APP_H_
#define APP_H_
#include "std_types.h"
/*******************************************************************************
 *                          Preprocessor Macros                                *
 *******************************************************************************/
#define	CHOICE_OPEN_DOOR			'+'
#define	CHOICE_CHANGE_PASS			'-'
#define ENTER_KEY					'='
#define NO_PASS_CREATED			 0x15
#define HAVE_PASS			 0x16
#define PASSWORD_SIZE				 6
#define NOT_MATCH					 0
#define MATCH						 1u
#define EXCEEDED_TRIALS_COMMAND		 0xFF
#define UART_READY_COMMAND			 0xAA
#define CREATE_PASS_COMMAND			 0xDD
#define CHECK_PASS_COMMAND			 0x17
#define CORRECT_PASS_COMMAND		 0x18
#define	WRONG_PASS_COMMAND			 0x19
#define OPEN_DOOR_COMMAND			 0xBB
#define	PROCCESS_DONE_COMMAND		 0xCC


/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/

typedef enum{
	MENU_CREATE_PASS,MENU_MAIN,MENU_OPEN_DOOR,MENU_CHANGE_PASS
}CURRENT_MENU;

typedef enum{
	DOOR_CLOSED,DOOR_OPENED
}DOOR_STATE;


/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/


/*
 * Description :
 * Checks if the 2 entered passwords are matching.
 */
uint8 checkPass(const uint8 * pass,const uint8 * confirmPass);


/*
 * Description :
 * takes the password insertion in a buffer process and displays it as '*'.
 */
void insertPass(uint8 * pass);


/*
 * Description :
 * increments seconds counter g_sec.
 */
void App_TickProcessing(void);


#endif /* APP_H_ */
