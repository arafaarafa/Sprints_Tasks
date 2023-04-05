#ifndef HAL_GPIO_H
#define HAL_GPIO_H
/* section : includes*/
#include "Std_Types.h"
#include "Bit_manipulation.h"


/* section : Macro Declaration*/

/* section : Macro Functions Declarations*/

#define PORT_BITS       3
#define PIN_BITS        3
#define DIRECTION_BITS  1
#define LOGIC_BITS      1


#define PORT_MAX_NUMBER 5
#define PIN_MAX_NUMBER  8



#define GPIO_PIN_CONFIGURATION          CONFIG_ENABLE
#define GPIO_PORT_CONFIGURATION         CONFIG_ENABLE


/* section : Data Types Declarations*/

typedef enum{
    GPIO_LOW=0,
    GPIO_HIGH
}logic_t;

typedef enum{
    GPIO_DIRECTION_OUTPUT,
    GPIO_DIRECTION_INPUT
}direction_t;

typedef enum{
    PIN0=0,
    PIN1,
    PIN2,
    PIN3,
    PIN4,
    PIN5,
    PIN6,
    PIN7
}pin_index_t;

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
    unsigned logic    :LOGIC_BITS;/* @ref logic_t */

}pin_config_t;
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


#endif

