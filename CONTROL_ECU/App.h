/*
 ============================================================================
 Name        : App.h
 Author      : Muhammad Hassan
 Description : Control ECU for door locker security system
 Date        : 24/10/2022
 ============================================================================
 */


#ifndef APP_H_
#define APP_H_
/*******************************************************************************
 *                          Preprocessor Macros                                *
 *******************************************************************************/
#define	CHOICE_OPEN_DOOR			 '+'
#define	CHOICE_CHANGE_PASS			 '-'
#define ENTER_KEY					 '='
#define NO_PASS_CREATED				 0x15
#define HAVE_PASS					 0x16
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
 *                              Functions Prototypes                           *
 *******************************************************************************/
void App_TickProcessing(void);

#endif /* APP_H_ */
