/*
 * timer1.h
 *
 *  Created on: Oct 26, 2022
 *      Author: Hassa
 */

#ifndef TIMER1_H_
#define TIMER1_H_
#include "std_types.h"
typedef enum{
	NO_CLOCK,F_CPU_NO_SCALE,F_CPU_8,F_CPU_64,F_CPU_256,F_CPU_1024
}Timer1_Prescaler;

typedef enum{
NORMAL,COMPARE
}Timer1_Mode;

typedef struct{
	uint16 initial_value;
	uint16 compare_value; // it will be used in compare mode only.
	Timer1_Prescaler prescaler;
	Timer1_Mode mode;
}Timer1_ConfigType;


void Timer1_init(const Timer1_ConfigType * Config_Ptr);
void Timer1_deInit(void);
void Timer1_setCallBack(void(*a_ptr)(void));

#endif /* TIMER1_H_ */
