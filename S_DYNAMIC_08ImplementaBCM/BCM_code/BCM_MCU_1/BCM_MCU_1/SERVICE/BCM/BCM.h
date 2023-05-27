/*
 * BCM.h
 *
 * Created: 5/23/2023 8:12:48 PM
 *  Author: Arafa
 */ 


#ifndef BCM_H_
#define BCM_H_
#include "../../STD_LIBRARIES/STD_TYPES.h"
#include "../../MCAL/UART/UART.h"

/************the maximum number of protocols that can be used with BCM***********/
#define MAX_PROTOCOL_COUNTER 3
/********the maximum number of bytes to describe the length of data will send*********/
#define MAX_NUMBER_OF_BYTES_FOR_LENGTH 2
/************ the minimum number of bytes of data will send ***********/
#define MIN_NUMBER_OF_BYTES_FOR_data 1
/*
*
*
* -enu_protocol_state_t datatype enum has all initialization state
*   -Members-
*
* -1-INITIALIZED
* -2-NOT_REQUIRED
*
*/
typedef enum{
	INITIALIZED = 0,
	NOT_REQUIRED

}enu_protocol_state_t;
/*
*
*
* -str_data_and_slave_instance_t datatype hold the data to transmit and the wanted slave if wanted for protocol
*   -Members-
* -1-  (uint8_t * ptr_data)  pointer to the data
* -2-  (uint16_t data_length) the length of data
*
*/
typedef struct
{
	uint8_t * ptr_data;
	uint16_t data_length;

}str_data_and_slave_instance_t;

/*
*
*
* -str_data_instance_t datatype hold the address of data queue to receive and the length of data
*   -Members-
* -1-  (uint8_t * ptr_data)  pointer to the data
* -2-  (uint16_t *data_length) pointer to the length of data
* -3-  (void *slave_id) void pointer to hold slave info address
*
*/
typedef struct
{
	uint8_t *ptr_data;
	uint16_t *data_length;
}str_data_instance_t;

/*
*
*
* -enu_system_status_t datatype enum has all system return states
*   -Members-
*
* -1-BCM_NOT_OK
* -2-BCM_OK
* -3-IN_PROGRESS
* -4-COMPLETED
*
*/
typedef enum{
	BCM_NOT_OK =0,
	BCM_OK,
	IN_PROGRESS,
	COMPLETED
}enu_system_status_t;

/*
*
*
* -enu_system_protocols_t datatype enum has all types of protocol that can be used with BCM
*   -Members-
*
* -1-USART_PROTOCOL
* -2-SPI_PROTOCOL
* -3-I2C_PROTOCOL
*
*/
typedef enum{
	USART_PROTOCOL =0,
	SPI_PROTOCOL,
	I2C_PROTOCOL
}enu_system_protocols_t;

/*
*
*
* -enu_data_on_bus_state_t datatype enum has all states of data on the bus
*   -Members-
*
* -1-SENT
* -2-NOT_SENT
* -3-RECEIVED
* -4-NOT_RECEIVED
*
*/
typedef enum{
	SENT =0,
	NOT_SENT,
	RECEIVED,
	NOT_RECEIVED
}enu_data_on_bus_state_t;

/*
*
*
* -str_slave_protocol_selection_t datatype hold the address of data queue to receive and the length of data
*   -Members-
* -1-  (enu_system_protocols_t enu_system_protocols)  protocol that can be used with BCM
* -2-  (void *slave_id) void pointer to hold slave info address
*
*/
typedef struct{
	void *slave_id;
	enu_system_protocols_t enu_system_protocols;

}str_slave_protocol_selection_t;


/*
*
*
* -str_bcm_instance_t datatype hold all configuration for wanted protocols to initialization
*   -Members-
* -1-  (enu_protocol_state_t uart_state)  initialized or not for uart
* -2-  (uart_config_t usart_instance) configuration for usart
*
*/
typedef struct
{
	enu_protocol_state_t uart_state;
	uart_config_t usart_instance;
/*
	enu_protocol_state_t spi_state;
	str_spi_instance_t spi_instance;
	
	enu_protocol_state_t i2c_state;
	str_i2c_instance_t i2c_instance;
*/
}str_bcm_instance_t;


/*
*   -Description-
*-this function to init BCM system
*
*   -Input parameters -
*-1-it holds all configuration of all wanted protocols   (str_bcm_instance_t* ptr_str_bcm_instance)
*
*   -Return-
*   -Return cases-
*-1- BCM_NOT_OK       something wrong
*-2- BCM_OK	          every thing done
*-3- IN_PROGRESS      the data is still in progress transmit or receive
*-4- COMPLETED        the data transmitted or received
*/
enu_system_status_t bcm_init(str_bcm_instance_t* ptr_str_bcm_instance);

/*
*   -Description-
*-this function to deinit BCM system
*
*   -Input parameters -
*-1-it holds all configuration of all wanted protocols   (str_bcm_instance_t* ptr_str_bcm_instance)
*
*   -Return-
*   -Return cases-
*-1- BCM_NOT_OK       something wrong
*-2- BCM_OK	          every thing done
*-3- IN_PROGRESS      the data is still in progress transmit or receive
*-4- COMPLETED        the data transmitted or received
*/
enu_system_status_t bcm_deinit(str_bcm_instance_t* ptr_str_bcm_instance);

/*
*   -Description-
*-this function to send one byte of data
*
*   -Input parameters -
*-1-it holds the wanted will use to send to data   (str_slave_protocol_selection_t *ptr_str_slave_protocol_selection)
*-2-it pointer to data to send   (uint8_t *data)
*
*   -Return-
*   -Return cases-
*-1- BCM_NOT_OK       something wrong
*-2- BCM_OK	          every thing done
*-3- IN_PROGRESS      the data is still in progress transmit or receive
*-4- COMPLETED        the data transmitted or received
*/
enu_system_status_t bcm_send(str_slave_protocol_selection_t *ptr_str_slave_protocol_selection, uint8_t *data);

/*
*   -Description-
*-this function to send N byte of data
*
*   -Input parameters -
*-1-it holds the wanted will use to send to data   (str_slave_protocol_selection_t *ptr_str_slave_protocol_selection)
*-2-it pointer to data to send   (uint8_t *data)
*-3-it is the length of data   (uint16_t length)
*
*   -Return-
*   -Return cases-
*-1- BCM_NOT_OK       something wrong
*-2- BCM_OK	          every thing done
*-3- IN_PROGRESS      the data is still in progress transmit or receive
*-4- COMPLETED        the data transmitted or received
*/
enu_system_status_t bcm_send_n(str_slave_protocol_selection_t *ptr_str_slave_protocol_selection, uint8_t *data, uint16_t length);

/*
*   -Description-
*-this function to receive N byte of data
*
*   -Input parameters -
*-1-it holds the wanted will use to send to data   (str_slave_protocol_selection_t *ptr_str_slave_protocol_selection)
*   -Output parameters -
*-1-it pointer to data to receive   (uint8_t *data)
*-2-it pointer the length of data   (uint16_t *length)
*
*   -Return-
*   -Return cases-
*-1- BCM_NOT_OK       something wrong
*-2- BCM_OK	          every thing done
*-3- IN_PROGRESS      the data is still in progress transmit or receive
*-4- COMPLETED        the data transmitted or received
*/
enu_system_status_t bcm_receive_n(str_slave_protocol_selection_t *ptr_str_slave_protocol_selection, uint8_t *data , uint16_t *length);


/*
*   -Description-
*-used to view the state of bus
*
*   -Input parameters -
*-1-it holds the wanted will use to send to data   (str_slave_protocol_selection_t *ptr_str_slave_protocol_selection)
*
*   -Return-
*   -Return cases-
*-1- BCM_NOT_OK       something wrong
*-2- BCM_OK	          every thing done
*-3- IN_PROGRESS      the data is still in progress transmit or receive
*-4- COMPLETED        the data transmitted or received
*/
enu_system_status_t bcm_dispatcher(enu_system_protocols_t enu_com_protocol);




#endif /* BCM_H_ */