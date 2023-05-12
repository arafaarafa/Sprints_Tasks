/*
 * UART.h
 *
 * Created: 4/22/2023 7:45:47 AM
 *  Author: Arafa
 */ 


#ifndef UART_H_
#define UART_H_
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

/**RX completed interrupt enum**/
typedef enum{
	UART_RCIE_DISABLE = 0,  //disable interrupt
	UART_RCIE_ENABLE        //enable interrupt
}uart_rcie_mode_t;

/**TX completed interrupt enum**/
typedef enum{
	UART_TCIE_DISABLE = 0,  //disable interrupt
	UART_TCIE_ENABLE        //enable interrupt
}uart_tcie_mode_t;

/**data register empty interrupt**/
typedef enum{
	UART_UDRIE_DISABLE = 0, //disable interrupt
	UART_UDRIE_ENABLE       //enable interrupt
}uart_urie_mode_t;

/**RX modes**/
typedef enum{
	UART_RX_DISABLE = 0,    //disable RX
	UART_RX_ENABLE          //disable RX
}uart_rx_mode_t;

/**tx modes**/
typedef enum{
	UART_TX_DISABLE = 0,    //disable TX
	UART_TX_ENABLE          //enable TX
}uart_tx_mode_t;

/**speed of transmation**/  
typedef enum{
	UART_SYNC_SPEED_MODE = 0,   //sysnc mode
	UART_NORMAL_MODE = 0,       //normal mode
	UART_DOUBLE_MODE            //double speed
}uart_speed_mode_t;

/** clock polarity modes**/
typedef enum{
	UART_NO_CLOCK = 0,          //noclock in async mode
	UART_TXR_RXF = 0,
	UART_TXF_RXR
}uart_clock_polarity_t;


/**number of stop bits selection**/
typedef enum{
	UART_STOP_1_BIT =0,           //one bit     
	UART_STOP_2_BIT               //two bits
}uart_stop_mode_t;


/**parity bits mode**/
typedef enum{
	UART_PARITY_DIABLED =0,         //no parity mode
	UART_PARITY_EVEN =2,            //even parity mode
	UART_PARITY_ODD                 //odd arity mode
}uart_parity_mode_t;
	
/**async or sync modes**/
typedef enum{
	UART_ASYNC_MODE =0,             //async mode
	UART_SYNC_MODE                  //sync mode
}uart_mode_t;

/**data size settings**/
typedef enum{
	UART_CS_5 =0,                   //5bits length
	UART_CS_6,                      //6bits length
	UART_CS_7,                      //7bits length
	UART_CS_8,                      //8bits length
	UART_CS_9 =7                    //9bits length
}uart_cs_mode_t;



typedef struct{
	uart_mode_t uart_mode;
	uart_cs_mode_t uart_cs_mode;
	uart_parity_mode_t uart_parity_mode;
	uart_stop_mode_t uart_stop_mode;
	uart_clock_polarity_t uart_clock_polarity;
	uart_speed_mode_t uart_speed_mode;
	uart_rcie_mode_t uart_rcie_mode;
	uart_tcie_mode_t uart_tcie_mode; 
	uart_urie_mode_t uart_urie_mode;
	uart_rx_mode_t	uart_rx_mode;
	uart_tx_mode_t	uart_tx_mode;
	uint32 usart_buadrate;	
}uart_config_t;


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
Std_ReturnType uart_init(uart_config_t *uart_config);

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
*-1-it holds uart configuration  (uart_config_t *uart_config)
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
Std_ReturnType uart_write_INT(uart_config_t *uart_config, uint16 *data);

/*
*   -Description-
*-this function to receive data using interrupt
*
*   -output parameters -
*-1-it holds uart configuration  (uart_config_t *uart_config)

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
Std_ReturnType uart_read_INT(uart_config_t *uart_config, uint16 *data);
#endif /* UART_H_ */