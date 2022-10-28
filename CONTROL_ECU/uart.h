 /******************************************************************************
 *
 * Module: UART
 *
 * File Name: uart.h
 *
 * Description: header file for the AVR UART driver
 *
 * Author: Muhammad Hassan
 *
 *******************************************************************************/

#ifndef UART_H_
#define UART_H_

#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define POLLING      0
#define INTERRUPT    1
#define UART_MODE POLLING


 /*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/
    typedef enum
    {
        DISABLED,RESEREVED,EVEN,ODD
    }UART_Parity;

    typedef enum
    {
        ONE_BIT,TWO_BITS
    }UART_stopBit;

    typedef enum
    {
        FIVE_BITS,SIX_BITS,SEVEN_BITS,EIGHT_BITS,NINE_BITS = 7
    }UART_BitData;


    typedef struct
    {
        UART_BitData BitData;
        UART_Parity parity;
        UART_stopBit stopBit;
        uint32 UART_baudRate;
    }UART_ConfigType;

 /*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

 /*
 * Description :
 * Function responsible for initialize the UART driver.
 */
 void UART_init(UART_ConfigType * Config_Ptr);

 /*
 * Description :
 * Function sends a byte through UART.
 */
 void UART_sendByte(uint8 data);

 /*
 * Description :
 * Function receives a byte through UART.
 */
 uint8 UART_receiveByte(void);

 /*
 * Description :
 * Function sends a string through UART.
 */
 void UART_sendString(const uint8 *Str);

 /*
 * Description :
 * Function receives a string through UART.
 */
 void UART_receiveString(uint8 *Str);
#endif /* UART_H_ */
