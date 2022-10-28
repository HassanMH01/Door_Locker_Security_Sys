/******************************************************************************
 *
 * Module: UART
 *
 * File Name: uart.c
 *
 * Description: Source file for the AVR UART driver
 *
 * Author: Muhammad Hassan
 *
 *******************************************************************************/

 #include "common_macros.h" /* To use the macros like SET_BIT */
 #include "avr/io.h" /* To use the IO Ports Registers */
 #include "uart.h"


 void UART_init(UART_ConfigType * Config_Ptr){
    uint16 ubrr_value = 0;
    /* Calculate the UBRR register value */
	ubrr_value = (uint16)(((F_CPU / ((Config_Ptr->UART_baudRate) * 8UL))) - 1);

    CLEAR_BIT(UCSRC,URSEL);
	/* First 8 bits from the BAUD_PRESCALE inside UBRRL and last 4 bits in UBRRH*/
	UBRRH = (uint8)(ubrr_value>>8);
	UBRRL = (uint8)ubrr_value;

    UCSRA = (1<<U2X); /* U2X = 1 for double transmission speed */
    #if(UART_MODE==INTERRUPT)
        UCSRB = (1<<RXCIE) | (1<<TXCIE) | (1<<RXEN) | (1<<TXEN);
    #else
    UCSRB = (1<<RXEN) | (1<<TXEN);
    #endif




    UCSRC = (1<<URSEL) \
    		|(Config_Ptr->stopBit<<USBS) \
			| (Config_Ptr->parity<<UPM0) \
			| ((Config_Ptr->BitData &0x03)<<UCSZ0);
//    switch(Config_Ptr->UART_sendSize){
//    case FIVE_BITS:
//    	UCSRC |= (1<<URSEL) & ~(1<<UCSZ0) & ~(1<<UCSZ1);
//    	break;
//    case SIX_BITS:
//    	UCSRC = (UCSRC | (1<<URSEL) | (1<<UCSZ1)) & (~(1<<UCSZ0));
//    	break;
//    case SEVEN_BITS:
//    	UCSRC = (UCSRC | (1<<URSEL) |  (1<<UCSZ0)) & (~(1<<UCSZ1));
//    	break;
//    case EIGHT_BITS:
//    	UCSRC |=  (1<<URSEL) | (1<<UCSZ0) | (1<<UCSZ1);
//    	break;
//    case NINE_BITS:
//    	UCSRC |=  (1<<URSEL) |  (1<<UCSZ0) | (1<<UCSZ1);
//    	UCSRB |= (1<<UCSZ2);
//    	break;
//    }
//
//
//    switch(Config_Ptr->UART_stopBit){
//    case ONE_BIT:
//    	UCSRC |= (1<<URSEL) &  ~(1<<USBS);
//    	break;
//    case TWO_BITS:
//    	UCSRC |=  (1<<URSEL) | (1<<USBS);
//    break;
//    }
//
//
//switch(Config_Ptr->UART_parity){
//	case DISABLED:
//			UCSRC = (UCSRC | (1<<URSEL)) & ~(1<<UPM0) & ~(1<<UPM1);
//			break;
//	case EVEN:
//		UCSRC = (UCSRC | (1<<URSEL)| (1<<UPM1)) & ~(1<<UPM0) ;
//		break;
//	case ODD:
//		UCSRC |= (1<<URSEL)| (1<<UPM0) | (1<<UPM1);
//		break;
//	case RESEREVED:
//		break;
//}
 }

    void UART_sendByte(uint8 data){
        while(BIT_IS_CLEAR(UCSRA,UDRE)){

        }
        UDR = data;
    }

    uint8 UART_receiveByte(void){
        while(BIT_IS_CLEAR(UCSRA,RXC)){

        }
        return UDR;
    }

    void UART_sendString(const uint8 *Str){
        uint8 i = 0;
	while(Str[i] != '\0')
	{
		UART_sendByte(Str[i]);
		i++;
	}
    }
    
    void UART_receiveString(uint8 *Str){
         uint8 i = 0;
         /* Receive the first byte */
         	Str[i] = UART_receiveByte();

         	/* Receive the whole string until the '#' */
         	while(Str[i] != '#')
         	{
         		i++;
         		Str[i] = UART_receiveByte();
         	}

         	/* After receiving the whole string plus the '#', replace the '#' with '\0' */
         	Str[i] = '\0';
    }

