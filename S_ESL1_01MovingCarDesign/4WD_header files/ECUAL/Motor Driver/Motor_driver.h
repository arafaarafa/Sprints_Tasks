#ifndef MOTOR_DRIVER_H
#define MOTOR_DRIVER_H
/* section : includes*/
#include "../../MCAL/DIO/GPIO.h"
#include "../../MCAL/Timer/Timer.h"


/* section : Macro Declaration*/


/* section : Macro Functions Declarations*/

/* section : Data Types Declarations*/

/*
*
*
* -dc_motor_status_t datatype enum has all motor status
*   -Members-
*
* -1-DC_MOTOR_OFF
* -2-DC_MOTOR_ON
*
*
*/
typedef enum{
    DC_MOTOR_OFF=0,
    DC_MOTOR_ON
}dc_motor_status_t;


/*
*
*
* -dc_motor_direction_t datatype enum has all motor direction
*   -Members-
*
* -1-DC_MOTOR_RIGHT
* -2-DC_MOTOR_LEFT
*
*
*/
typedef enum{
    DC_MOTOR_RIGHT=0,
    DC_MOTOR_LEFT 
}dc_motor_direction_t;


/*
*
*
* -dc_motor_config_t datatype hold motor driver configuration
*   -Members-
* -1-  (pin_config_t dc_motor_pins[2]) array contains the info about two pins connected motor driver 
* -2-  (pin_config_t dc_motor_EN) enable pin in motor driver
* -3-  (dc_motor_status_t dc_motor_status) motor status off or on
* -4-  (dc_motor_direction_t dc_motor_direction) motor direction forwared or backwared
* -5-  (uint8_t dc_motor_speed ) motor speed
*
*/
typedef struct{
    pin_config_t dc_motor_pins[2];
    pin_config_t dc_motor_EN;
    dc_motor_status_t dc_motor_status;
    dc_motor_direction_t dc_motor_direction;
    uint8_t dc_motor_speed ;
}dc_motor_config_t;

/* section : Function Declaration*/


/*
*   -Description-
*-this function init motor driver
*
*   -Input Output parameters -
*-1-it holds motor driver configuration  (tdc_motor_config_t *dc_motor)
*
*   -Return-
*   Std_ReturnType
*
*   -Return cases-
*-1- (E_NOK) if there is something wrong
*-2- (E_OK) otherwise
*/
Std_ReturnType motor_initialize(const dc_motor_config_t *dc_motor);



/*
*   -Description-
*-this function turn on motor driver
*
*   -Input Output parameters -
*-1-it holds motor driver configuration  (tdc_motor_config_t *dc_motor)
*-2-it holds motor direction  (dc_motor_direction_t dc_motor_direction)
*
*   -Return-
*   Std_ReturnType
*
*   -Return cases-
*-1- (E_NOK) if there is something wrong
*-2- (E_OK) otherwise
*/
Std_ReturnType motor_turn_on(dc_motor_config_t *dc_motor, dc_motor_direction_t dc_motor_direction );

/*
*   -Description-
*-this function turn off motor 
*
*   -Input Output parameters -
*-1-it holds motor driver configuration  (dc_motor_config_t *dc_motor)
*
*   -Return-
*   Std_ReturnType
*
*   -Return cases-
*-1- (E_NOK) if there is something wrong
*-2- (E_OK) otherwise
*/
Std_ReturnType motor_stop(dc_motor_config_t *dc_motor);

/*
*   -Description-
*-this function set motor speed
*
*   -Input Output parameters -
*-1-it holds motor driver configuration  (dc_motor_config_t *dc_motor)
*-1-it holds motor speed  (uint8_t dc_motor_speed)
*
*   -Return-
*   Std_ReturnType
*
*   -Return cases-
*-1- (E_NOK) if there is something wrong
*-2- (E_OK) otherwise
*/
Std_ReturnType motor_set_speed(dc_motor_config_t *dc_motor, uint8_t dc_motor_speed); 

#endif