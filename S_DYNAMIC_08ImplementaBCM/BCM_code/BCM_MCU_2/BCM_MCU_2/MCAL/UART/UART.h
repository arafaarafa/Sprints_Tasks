/*
 * UART.h
 *
 * Created: 4/22/2023 7:45:47 AM
 *  Author: Arafa
 */ 


#ifndef UART_H_
#define UART_H_

#include "../../STD_LIBRARIES/STD_TYPES.h"
#include "../../STD_LIBRARIES/bit_math.h"
#include "../../STD_LIBRARIES/interrupt.h"

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
*
*
* -uart_rcie_mode_t datatype enum has all RC interrupt mode states
*   -Members-
*
* -1-UART_RCIE_DISABLE
* -2-UART_RCIE_ENABLE
*
*/
typedef enum{
	UART_RCIE_DISABLE = 0,
	UART_RCIE_ENABLE
}uart_rcie_mode_t;
/*
*
*
* -uart_tcie_mode_t datatype enum has all TC interrupt mode states
*   -Members-
*
* -1-UART_TCIE_DISABLE
* -2-UART_TCIE_ENABLE
*
*/
typedef enum{
	UART_TCIE_DISABLE = 0,
	UART_TCIE_ENABLE
}uart_tcie_mode_t;


/*
*
*
* -uart_urie_mode_t datatype enum has all UDR empty interrupt mode states
*   -Members-
*
* -1-UART_UDRIE_DISABLE
* -2-UART_UDRIE_ENABLE
*
*/
typedef enum{
	UART_UDRIE_DISABLE = 0,
	UART_UDRIE_ENABLE
}uart_urie_mode_t;

/*
*
*
* -uart_rx_mode_t datatype enum has all RX mode states
*   -Members-
*
* -1-UART_RX_DISABLE
* -2-UART_RX_ENABLE
*
*/
typedef enum{
	UART_RX_DISABLE = 0,
	UART_RX_ENABLE
}uart_rx_mode_t;

/*
*
*
* -uart_tx_mode_t datatype enum has all TX mode states
*   -Members-
*
* -1-UART_TX_DISABLE
* -2-UART_TX_ENABLE
*
*/
typedef enum{
	UART_TX_DISABLE = 0,
	UART_TX_ENABLE
}uart_tx_mode_t;

/*
*
*
* -uart_speed_mode_t datatype enum has all speed mode states
*   -Members-
*
* -1-UART_SYNC_SPEED_MODE
* -2-UART_NORMAL_MODE
* -3-UART_DOUBLE_MODE
*
*/
typedef enum{
	UART_SYNC_SPEED_MODE = 0,
	UART_NORMAL_MODE = 0,
	UART_DOUBLE_MODE
}uart_speed_mode_t;


/*
*
*
* -uart_clock_polarity_t datatype enum has all clock polarity mode states
*   -Members-
*
* -1-UART_NO_CLOCK
* -2-UART_TXR_RXF
* -3-UART_TXF_RXR
*
*/
typedef enum{
	UART_NO_CLOCK = 0,
	UART_TXR_RXF = 0,
	UART_TXF_RXR
}uart_clock_polarity_t;

/*
*
*
* -uart_stop_mode_t datatype enum has all number of stop bits
*   -Members-
*
* -1-UART_STOP_1_BIT
* -2-UART_STOP_2_BIT
*
*/
typedef enum{
	UART_STOP_1_BIT =0,
	UART_STOP_2_BIT
}uart_stop_mode_t;

/*
*
*
* -uart_parity_mode_t datatype enum has all modes of parity bits
*   -Members-
*
* -1-UART_PARITY_DIABLED
* -2-UART_PARITY_EVEN
* -3-UART_PARITY_ODD
*
*/
typedef enum{
	UART_PARITY_DIABLED =0,
	UART_PARITY_EVEN =2,
	UART_PARITY_ODD
}uart_parity_mode_t;

/*
*
*
* -uart_mode_t datatype enum has all modes of usart
*   -Members-
*
* -1-UART_ASYNC_MODE
* -2-UART_SYNC_MODE
*
*/	
typedef enum{
	UART_ASYNC_MODE =0,
	UART_SYNC_MODE
}uart_mode_t;

/*
*
*
* -uart_mode_t datatype enum has all modes of character sizes
*   -Members-
*
* -1-UART_CS_5
* -2-UART_CS_6
* -3-UART_CS_7
* -4-UART_CS_8
* -5-UART_CS_9
*
*/
typedef enum{
	UART_CS_5 =0,
	UART_CS_6,
	UART_CS_7,
	UART_CS_8,
	UART_CS_9 =7
}uart_cs_mode_t;


/*
*
*
* -uart_config_t datatype hold all configuration of usart
*
*
*/
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
	uint32_t usart_buadrate;
	/*void (*RXC_func)(void);
	void (*TXC_func)(void);
	void (*UDRE_func)(void);*/
	
}uart_config_t;


/*
*   -Description-
*-used to init the usart
*
*   -Input parameters -
*-1-it holds all configuration of usart   (uart_config_t *uart_config)
*
*   -Return-
*   -Return cases-
*-1- E_NOT_OK       something wrong
*-2- E_OK	          every thing done
*/
Std_ReturnType uart_init(uart_config_t *uart_config);

/*
*   -Description-
*-used to deinit the usart
*
*
*   -Return-
*   -Return cases-
*-1- E_NOT_OK       something wrong
*-2- E_OK	          every thing done
*/
Std_ReturnType uart_deinit(void);

/*
*   -Description-
*-used to transmit data 
*
*   -Input parameters -
*-1-it is pointer to data  (uint16_t *data)
*
*   -Return-
*   -Return cases-
*-1- E_NOT_OK       something wrong
*-2- E_OK	          every thing done
*/
Std_ReturnType uart_write(uint16_t *data);

/*
*   -Description-
*-used to receive data
*
*   -Output parameters -
*-1-it is pointer to data  (uint16_t *data)
*
*   -Return-
*   -Return cases-
*-1- E_NOT_OK       something wrong
*-2- E_OK	          every thing done
*/
Std_ReturnType uart_read(uint16_t *data);

/*
*   -Description-
*-used to set callback function for URD empty interrupt 
*
*   -Input parameters -
*-1-it is pointer to function  (void(*callback)(void))
*
*   -Return-
*   -Return cases-
*-1- E_NOT_OK       something wrong
*-2- E_OK	          every thing done
*/
Std_ReturnType uart_write_INT(void(*callback)(void));

/*
*   -Description-
*-used to set callback function for RX complete 
*
*   -Input parameters -
*-1-it is pointer to function  (void(*callback)(void))
*
*   -Return-
*   -Return cases-
*-1- E_NOT_OK       something wrong
*-2- E_OK	          every thing done
*/
Std_ReturnType uart_read_INT(void(*callback)(void));

/*
*   -Description-
*-used to enable UDR empty  interrupt
*
*
*   -Return-
*   -Return cases-
*-1- E_NOT_OK       something wrong
*-2- E_OK	          every thing done
*/
Std_ReturnType uart_enable_UDRIE(void);

/*
*   -Description-
*-used to disable UDR empty interrupt
*
*
*   -Return-
*   -Return cases-
*-1- E_NOT_OK       something wrong
*-2- E_OK	          every thing done
*/
Std_ReturnType uart_disable_UDRIE(void);

/*
*   -Description-
*-used to enable RX complete interrupt
*
*
*   -Return-
*   -Return cases-
*-1- E_NOT_OK       something wrong
*-2- E_OK	          every thing done
*/
Std_ReturnType uart_enable_RCIE(void);
/*
*   -Description-
*-used to disable RX complete interrupt
*
*
*   -Return-
*   -Return cases-
*-1- E_NOT_OK       something wrong
*-2- E_OK	          every thing done
*/
Std_ReturnType uart_disable_RCIE(void);
#endif /* UART_H_ */