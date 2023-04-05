#ifndef MOTOR_DRIVER_H
#define MOTOR_DRIVER_H
/* section : includes*/

#include "../MCAL/DIO/GPIO.h"


/* section : Macro Declaration*/


/* section : Macro Functions Declarations*/

/* section : Data Types Declarations*/


/*
*
*
* -button_state_t datatype enum has all button state
*   -Members-
*
* -1-BUTTON_RELEASED
* -2-BUTTON_PRESSED
*
*
*/
typedef enum {
    BUTTON_RELEASED=0,
    BUTTON_PRESSED 
            
}button_state_t;


/*
*
*
* -button_state_t datatype enum has all activaton state of button
*   -Members-
*
* -1-BUTTON_ACTIVE_LOW
* -2-BUTTON_ACTIVE_HIGH
*
*
*/

typedef enum{
    BUTTON_ACTIVE_LOW=0,
    BUTTON_ACTIVE_HIGH
}button_active_t;



/*
*
*
* -button_t datatype hold motor driver configuration
*   -Members-
* -1-  (pin_config_t button_pin) pin configration connected to that button
* -2-  (button_state_t button_state) released or pressed
* -3-  (button_active_t button_active) activation state
*
*/
typedef struct{
    pin_config_t button_pin;
    button_state_t button_state;
    button_active_t button_active;
}button_t;



/* section : Function Declaration*/

/*
*   -Description-
*-this function init button
*
*   -Input Output parameters -
*-1-it holds button configuration  (button_t* btn)
*
*   -Return-
*   Std_ReturnType
*
*   -Return cases-
*-1- (E_NOK) if there is something wrong
*-2- (E_OK) otherwise
*/
Std_ReturnType button_initializa(const button_t* btn);



/*
*   -Description-
*-this function init button
*
*   -Output parameters -
*-1-it holds the state of button (button_state_t *btn_state)

*   -Input Output parameters -
*-1-it holds button configuration  (button_t* btn)
*
*   -Return-
*   Std_ReturnType
*
*   -Return cases-
*-1- (E_NOK) if there is something wrong
*-2- (E_OK) otherwise
*/
Std_ReturnType button_read_state( button_t *btn, button_state_t *btn_state);

#endif