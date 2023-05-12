#ifndef UART_H_
#define UART_H_

#include "UART_CONFIG.h"
#include <avr/interrupt.h>
#include "../../Std_Types.h"
#include "../../Bit_manipulation.h"

#define UCSRC_ADD (*((volatile uint8_t *)0x40))
#define	UART_URSEL		7
#define	UART_UMSEL		6
#define UART_UPM		4
#define UART_USBS		3
#define UART_UCSZ		1
#define UART_UCPOL		0

#define UDR_ADD (*((volatile uint8_t *)0x2C))

#define UCSRA_ADD (*((volatile uint8_t *)0x2B))
#define	UART_RC		7
#define	UART_TC		6 
#define UART_UDRE	5
#define UART_FE		4
#define UART_DOR	3
#define UART_PE		2
#define UART_U2X	1




#define UCSRB_ADD (*((volatile uint8_t *)0x2A))
#define	UART_RCIE		7
#define	UART_TCIE		6
#define UART_UDRIE		5
#define UART_RXEN		4
#define UART_TXEN		3
#define UART_UCSZ2		2
#define UART_RXB8		1
#define UART_TXB8		0

#define UBRRH_ADD (*((volatile uint8_t *)0x40))
#define UBRRL_ADD (*((volatile uint8_t *)0x29))

/*
*   -Description-
*-this function to init uart
*
*   -Input parameters -
*-1-it holds uart configuration  (uart_config_t *uart_config)
*
*   -Return-
*   Std_ReturnType
*
*   -Return cases-
*
*-1- (E_NOT_OK) there some thing wrong 
*-2- (E_OK) very thing ok
*/
Std_ReturnType uart_init(void);

/*
*   -Description-
*-this function to transfer data
*
*   -Input parameters -
*-1-it holds data to send  (uint16 *data)
*
*   -Return-
*   Std_ReturnType
*
*   -Return cases-
*
*-1- (E_NOT_OK) there some thing wrong 
*-2- (E_OK) very thing ok
*/
Std_ReturnType uart_write(uint16 *data);

/*
*   -Description-
*-this function to receive data
*
*   -output parameters -
*-1-it holds received  data  (uint16 *data)
*
*   -Return-
*   Std_ReturnType
*
*   -Return cases-
*
*-1- (E_NOT_OK) there some thing wrong 
*-2- (E_OK) very thing ok
*/
Std_ReturnType uart_read(uint16 *data);

/*
*   -Description-
*-this function to transfer data using interrupt
*
*   -input parameters -
*-2-it holds data to send  (uint16 *data)
*
*   -Return-
*   Std_ReturnType
*
*   -Return cases-
*
*-1- (E_NOT_OK) there some thing wrong 
*-2- (E_OK) very thing ok
*/
Std_ReturnType uart_write_INT(uint16 *data);

/*
*   -Description-
*-this function to receive data using interrupt
*
*
*   -output parameters -
*-1-it holds data to send  (uint16 *data)
*
*   -Return-
*   Std_ReturnType
*
*   -Return cases-
*
*-1- (E_NOT_OK) there some thing wrong 
*-2- (E_OK) very thing ok
*/
Std_ReturnType uart_read_INT(uint16 *data);
#endif