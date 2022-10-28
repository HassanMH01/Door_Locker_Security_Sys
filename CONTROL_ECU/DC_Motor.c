 /******************************************************************************
 *
 * Module: DC Motor
 *
 * File Name: DC_Motor.c
 *
 * Description: Source file for the DC Motor driver
 *
 * Author: Muhammad Hassan
 *
 *******************************************************************************/
#include "DC_Motor.h"
#include <avr/io.h>
/*
 * Description :
 * initialize PWM on Timer0 :
 * Set Timer Initial value
 * Set Compare Value
 * Configure timer control register
 */

void PWM_Timer0_Init(uint8 set_duty_cycle){

	TCNT0 = 0; //Set Timer Initial value

	OCR0  = set_duty_cycle; // Set Compare Value

	/* Configure timer control register
	 * 1. Fast PWM mode FOC0=0
	 * 2. Fast PWM Mode WGM01=1 & WGM00=1
	 * 3. Clear OC0 when match occurs (non inverted mode) COM00=0 & COM01=1
	 * 4. clock = F_CPU/8 CS00=0 CS01=1 CS02=0
	 */
	TCCR0 = (1<<WGM00) | (1<<WGM01) | (1<<COM01) | (1<<CS01);
}

/*
*Description :
*The Function responsible for setup the direction for the two motor pins through the GPIO driver.
*Stop the DC-Motor at the beginning through the GPIO driver.
*/
void DCMotor_Init(void){
/*set PB3/OC0 as output pin --> pin where the PWM signal is generated from MC & other two pins for */
			GPIO_setupPinDirection(MOTOR_PORT_ID,MOTOR_PWM_PIN_ID,PIN_OUTPUT);
			GPIO_setupPinDirection(MOTOR_PORT_ID,MOTOR_IN1_ID,PIN_OUTPUT);
			GPIO_setupPinDirection(MOTOR_PORT_ID,MOTOR_IN2_ID,PIN_OUTPUT);
			
/*Stop the DC-Motor at the beginning through the GPIO driver.*/
			GPIO_writePin(MOTOR_PORT_ID,MOTOR_IN1_ID,LOGIC_LOW);
			GPIO_writePin(MOTOR_PORT_ID,MOTOR_IN2_ID,LOGIC_LOW);
}

/*
* Description :
*The function responsible for rotate the DC Motor CW/ or A-CW or stop the motor based on the state input state value.
* Send the required duty cycle to the PWM driver based on the required speed value.
*/
void DcMotor_Rotate(DcMotor_State state,uint8 speed){

	/*Stop Motor*/
	if(state == OFF){
			PWM_Timer0_Init(0);
			GPIO_writePin(MOTOR_PORT_ID,MOTOR_IN1_ID,LOGIC_LOW);
			GPIO_writePin(MOTOR_PORT_ID,MOTOR_IN2_ID,LOGIC_LOW);
					}
	else{ /*Rotate the motor*/
			PWM_Timer0_Init(((uint16)speed*255/100)); /*Calculate duty cycle sent to PWM using explicit casting to avoid overflow*/
				if(state == CW){ /*Rotate the motor --> Clock Wise*/
					GPIO_writePin(MOTOR_PORT_ID,MOTOR_IN1_ID,LOGIC_LOW);
					GPIO_writePin(MOTOR_PORT_ID,MOTOR_IN2_ID,LOGIC_HIGH);
								}
			else if(state == ACW){ /*Rotate the motor --> Anti-Clock Wise*/
					GPIO_writePin(MOTOR_PORT_ID,MOTOR_IN1_ID,LOGIC_HIGH);
					GPIO_writePin(MOTOR_PORT_ID,MOTOR_IN2_ID,LOGIC_LOW);
								 }
		}
	}
