 /******************************************************************************
 *
 * Module: DC Motor
 *
 * File Name: DC_Motor.h
 *
 * Description: header file for the DC Motor driver
 *
 * Author: Muhammad Hassan
 *
 *******************************************************************************/

#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_

#include "gpio.h"

#define MOTOR_PORT_ID       PORTB_ID
#define MOTOR_PWM_PIN_ID    PIN3_ID
#define MOTOR_IN1_ID        PIN1_ID
#define MOTOR_IN2_ID        PIN2_ID



typedef enum
{
	OFF,CW,ACW
}DcMotor_State;


/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

/*
 * Description :
 * initialize PWM on Timer0 :
 * Set Timer Initial value
 * Set Compare Value
 * Configure timer control register
* 1. Fast PWM mode FOC0=0
* 2. Fast PWM Mode WGM01=1 & WGM00=1
* 3. Clear OC0 when match occurs (non inverted mode) COM00=0 & COM01=1
* 4. clock = F_CPU/8 CS00=0 CS01=1 CS02=0
 */
void PWM_Timer0_Init(uint8 set_duty_cycle);


/*
*Description :
*The Function responsible for setup the direction for the two motor pins through the GPIO driver.
*Stop the DC-Motor at the beginning through the GPIO driver.
*/
void DCMotor_Init(void);


/*
* Description :
*The function responsible for rotate the DC Motor CW/ or A-CW or stop the motor based on the state input state value.
* Send the required duty cycle to the PWM driver based on the required speed value.
*/
void DcMotor_Rotate(DcMotor_State state,uint8 speed);

#endif /* DC_MOTOR_H_ */
