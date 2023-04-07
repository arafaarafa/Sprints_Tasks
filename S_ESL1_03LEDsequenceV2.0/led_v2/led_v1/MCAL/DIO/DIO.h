
#ifndef DIO_H
#define DIO_H
/* section : includes*/


#include <avr/interrupt.h>
#include "../../Std_Types.h"
#include "../../Bit_manipulation.h"



/* section : Macro Declaration*/

/* section : Macro Functions Declarations*/

/*
 *
 *  Macros to control external interrupts
 * 
 * 
*/

#define GICR_ADD			 (*((volatile uint8_t *) 0x5B)) 
#define INT0_Globle		6
#define INT1_Globle		7

#define MCUCR_ADD			(*((volatile uint8_t *) 0x55))
#define INT1_MODE_INDEX	2
#define SREG_ADD			(*((volatile uint8_t *) 0x5F))
#define Globle_INT		7

/*
 *
 *  Macros to control ports and pins
 * 
 * 
*/
#define PORT_BITS       3
#define PIN_BITS        3
#define DIRECTION_BITS  1
#define LOGIC_BITS      1


#define PORT_MAX_NUMBER 4
#define PIN_MAX_NUMBER  8






/* section : Data Types Declarations*/

/*
*
*
* -logic_t datatype enum has all pin levels
*   -Members-
*
* -1-GPIO_LOW
* -2-GPIO_HIGH 
*
*/
typedef enum{
    GPIO_LOW=0,
    GPIO_HIGH
}logic_t;

/*
*
*
* -direction_t datatype enum has all pin direction
*   -Members-
*
* -1-GPIO_DIRECTION_INPUT
* -2-GPIO_DIRECTION_OUTPUT
*
*/

typedef enum{
    
    GPIO_DIRECTION_INPUT=0,
	GPIO_DIRECTION_OUTPUT=1
}direction_t;


/*
*
*
* -pin_index_t datatype enum has all pin indexes 
*
*/
typedef enum{
    PIN_0,
    PIN_1,
    PIN_2,
    PIN_3,
    PIN_4,
    PIN_5,
    PIN_6,
    PIN_7
}pin_index_t;

/*
*
*
* -port_index_t datatype enum has all port indexes
*
*/
typedef enum{
    PORTA_INDEX=0,
    PORTB_INDEX,
    PORTC_INDEX,
    PORTD_INDEX,
    PORTE_INDEX
}port_index_t;

typedef struct{
    unsigned port    :PORT_BITS;/* @ref port_index_t */
    unsigned pin    :PIN_BITS;/* @ref pin_index_t */
    unsigned direction    :DIRECTION_BITS; /* @ref direction_t */
    unsigned logic    :LOGIC_BITS; /* @ref logic_t */

}pin_config_t;

/*
*
*
* -INT_mode_t datatype enum has all external interrupt modes
*
*/
typedef enum{
	LOW_LEVEL,
	LOGICAL_CHANGE,
	FALLING_EDGE,
	RISING_EDGE
} INT_mode_t;

/*
*
*
* -pin_INT_config_t datatype has all configurations of pin that has external interrupt functionality 
*
*/
typedef struct{
	pin_config_t pin_config;/* @ref pin_config_t */
	INT_mode_t INT_mode;/* @ref INT_mode_t */	
} pin_INT_config_t;

/* section : Function Declaration*/

Std_ReturnType gpio_pin_direction_initialize(const pin_config_t*);
Std_ReturnType gpio_pin_get_direction_status( pin_config_t*, direction_t *);
Std_ReturnType gpio_pin_write_logic( pin_config_t*, logic_t);
Std_ReturnType gpio_pin_read_logic( pin_config_t*, logic_t *);
Std_ReturnType gpio_pin_toggle_logic( pin_config_t*);
Std_ReturnType gpio_pin_initialize( pin_config_t*);


Std_ReturnType gpio_port_direction_initialize(port_index_t, uint8_t );
Std_ReturnType gpio_port_get_direction_status(port_index_t, uint8_t *);
Std_ReturnType gpio_port_write_logic(port_index_t, uint8_t );
Std_ReturnType gpio_port_read_logic(port_index_t, uint8_t *);
Std_ReturnType gpio_port_toggle_logic(port_index_t);


Std_ReturnType gpio_port_low_nibble_direction_initialize(pin_config_t *, uint8_t );
Std_ReturnType gpio_port_low_nibble_write_logic(pin_config_t *, uint8_t);
Std_ReturnType gpio_port_high_nibble_direction_initialize(pin_config_t *, uint8_t );
Std_ReturnType gpio_port_high_nibble_write_logic(pin_config_t *, uint8_t);

Std_ReturnType gpio_init_INT0(const pin_INT_config_t *pin_INT_config);
Std_ReturnType gpio_init_INT1(const pin_INT_config_t *pin_INT_config);

Std_ReturnType gpio_enable_INT0(const pin_INT_config_t *pin_INT_config);
Std_ReturnType gpio_enable_INT1(const pin_INT_config_t *pin_INT_config);

Std_ReturnType gpio_disable_INT0(const pin_INT_config_t *pin_INT_config);
Std_ReturnType gpio_disable_INT1(const pin_INT_config_t *pin_INT_config);

Std_ReturnType gpio_set_callback_INT0_function(void (*func)(void));
Std_ReturnType gpio_set_callback_INT1_function(void (*func)(void));

#endif


