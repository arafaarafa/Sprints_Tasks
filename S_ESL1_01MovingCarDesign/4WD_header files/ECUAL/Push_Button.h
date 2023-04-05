#ifndef MOTOR_DRIVER_H
#define MOTOR_DRIVER_H
/* section : includes*/
#include "GPIO.h"


/* section : Macro Declaration*/


/* section : Macro Functions Declarations*/

/* section : Data Types Declarations*/
typedef enum {
    BUTTON_RELEASED=0,
    BUTTON_PRESSED 
            
}button_state_t;

typedef enum{
    BUTTON_ACTIVE_LOW=0,
    BUTTON_ACTIVE_HIGH
}button_active_t;

typedef struct{
    pin_config_t button_pin;
    button_state_t button_state;
    button_active_t button_active;
}button_t;
/* section : Function Declaration*/

Std_ReturnType button_initializa(const button_t* btn);
Std_ReturnType button_read_state( button_t *btn, button_state_t *btn_state);

#endif