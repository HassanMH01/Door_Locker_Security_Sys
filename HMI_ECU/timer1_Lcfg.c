/******************************************************************************
 *
 * Module: Timer 1
 *
 * File Name: timer1_Lcfg.c
 *
 * Description: Source file for the AVR Timer 1 linking time configuration driver
 *
 * Author: Muhammad Hassan
 *
 *******************************************************************************/

#include "timer1.h"

Timer1_ConfigType Timer1_Config = {
0,
31248,
F_CPU_64,
COMPARE
};


