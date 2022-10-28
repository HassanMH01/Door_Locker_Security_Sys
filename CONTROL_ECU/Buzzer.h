 /******************************************************************************
 *
 * Module: Buzzer
 *
 * File Name: Buzzer.h
 *
 * Description: header file for the Buzzer driver
 *
 * Author: Muhammad Hassan
 *
 *******************************************************************************/

#ifndef BUZZER_H_
#define BUZZER_H_

#include "gpio.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define BUZZER_PORT    PORTB_ID
#define BUZZER_PIN     PIN0_ID

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
void Buzzer_init(void);

void Buzzer_ON(void);

void Buzzer_OFF(void);

#endif /* BUZZER_H_ */
