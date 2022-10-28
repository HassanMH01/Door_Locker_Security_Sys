/******************************************************************************
 *
 * Module: UART
 *
 * File Name: UART_Lcfg.c
 *
 * Description: Source file for the AVR UART linking time configuration driver
 *
 * Author: Muhammad Hassan
 *
 *******************************************************************************/


#include "uart.h"

UART_ConfigType UART_Config = {
		EIGHT_BITS,
		EVEN,
		ONE_BIT,
		9600
};
