 /******************************************************************************
 *
 * Module: ICU
 *
 * File Name: icu.h
 *
 * Description: Source file for the AVR ICU driver
 *
 * Author: Muhammad Hassan
 *
 *******************************************************************************/

#include "timer1.h"
#include "common_macros.h" /* To use the macros like SET_BIT */
#include <avr/io.h> /* To use ICU/Timer1 Registers */
#include "gpio.h"
#include <avr/interrupt.h> /* For ICU ISR */


/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/

/* Global variables to hold the address of the call back function in the application */
static volatile void (*g_callBackPtr)(void) = NULL_PTR;

/*******************************************************************************
 *                       Interrupt Service Routines                            *
 *******************************************************************************/

ISR(TIMER1_COMPA_vect){
	if(g_callBackPtr != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callBackPtr)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}

ISR(TIMER1_OVF_vect){
	if(g_callBackPtr != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callBackPtr)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/
/*
 * Description : Function to initialize the ICU driver
 * 	1. Set the required clock.
 * 	2. Set the required edge detection.
 * 	3. Enable the Input Capture Interrupt.
 * 	4. Initialize Timer1 Registers
 */
void Timer1_init(const Timer1_ConfigType * Config_Ptr){
switch(Config_Ptr->mode){
case NORMAL:
	TCNT1= Config_Ptr->initial_value;
	TCCR1A = (1<<FOC1A) | (1<<FOC1B);
	SET_BIT(TIMSK,TOIE1);
	TCCR1B = (Config_Ptr->prescaler);
	break;
case COMPARE:
	TCNT1= Config_Ptr->initial_value;
	OCR1A= Config_Ptr->compare_value;
	TCCR1A = (1<<FOC1A) | (1<<FOC1B);
	SET_BIT(TIMSK,OCIE1A);
	TCCR1B = (Config_Ptr->prescaler);
	break;
}

}

/*
 * Description: Function to set the Call Back function address.
 */
void Timer1_setCallBack(void(*a_ptr)(void)){
	/* Save the address of the Call back function in a global variable */
	g_callBackPtr = a_ptr;
}



/*
 * Description: Function to disable the Timer1 to stop the ICU Driver
 */
void Timer1_deInit(void){
	/* Clear All Timer1 Registers */
	TCCR1A = 0; // Stop Timer1 by clear the Clock bits
	TCCR1B = 0; // Stop Timer1 by clear the Clock bits
	OCR1A = 0;
	/* Disable the Input Capture interrupt */
	CLEAR_BIT(TIMSK,TICIE1);
	CLEAR_BIT(TIMSK,OCIE1A);
	CLEAR_BIT(TIMSK,OCIE1B);
	CLEAR_BIT(TIMSK,TOIE1);
}
