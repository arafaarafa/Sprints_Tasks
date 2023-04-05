#ifndef LED_H
#define LED_H
/* section : includes*/
#include "../../MCAL/DIO/GPIO.h"

/* section : Macro Declaration*/


/* section : Macro Functions Declarations*/

/* section : Data Types Declarations*/


/*
*
*
* -led_status_t datatype enum has all led states
*   -Members-
*
* -1-LED_OFF
* -2-LED_ON  
*
*/
typedef enum {
    LED_OFF=0,
    LED_ON
}led_status_t;


/*
*
*
* -timer_configuration_t datatype hold the transaction data
*   -Members-
* -1-  (uint8_t port_name) port name contains the pin that connected to led
* -2-  (uint8_t pin) that pin connected to led
* -3-  (uint8_t led_status) led status
*
*
*/
typedef struct{
    uint8_t port_name:4;
    uint8_t pin:3;
    uint8_t led_status:1;
}led_t;

/* section : Function Declaration*/

/*
*   -Description-
*-this function init led configuration
*
*   -Input Output parameters -
*-1-it holds led configuration  (led_t *led)
*
*   -Return-
*   Std_ReturnType
*
*   -Return cases-
*-1- (E_NOK) if there is something wrong
*-2- (E_OK) otherwise
*/
Std_ReturnType led_intialize(led_t *led);


/*
*   -Description-
*-this function to turn on led
*
*   -Input Output parameters -
*-1-it holds led configuration  (led_t *led)
*
*   -Return-
*   Std_ReturnType
*
*   -Return cases-
*-1- (E_NOK) if there is something wrong
*-2- (E_OK) otherwise
*/
Std_ReturnType led_turn_on(led_t *led);

/*
*   -Description-
*-this function to turn off led
*
*   -Input Output parameters -
*-1-it holds led configuration  (led_t *led)
*
*   -Return-
*   Std_ReturnType
*
*   -Return cases-
*-1- (E_NOK) if there is something wrong
*-2- (E_OK) otherwise
*/
Std_ReturnType led_turn_off(led_t *led);


/*
*   -Description-
*-this function to toggle led
*
*   -Input Output parameters -
*-1-it holds led configuration  (led_t *led)
*
*   -Return-
*   Std_ReturnType
*
*   -Return cases-
*-1- (E_NOK) if there is something wrong
*-2- (E_OK) otherwise
*/
Std_ReturnType led_toggle(led_t *led);
#endif