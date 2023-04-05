#ifndef MOTOR_DRIVER_H
#define MOTOR_DRIVER_H
/* section : includes*/
#include "GPIO.h"


/* section : Macro Declaration*/


/* section : Macro Functions Declarations*/

/* section : Data Types Declarations*/

typedef enum{
    DC_MOTOR_OFF=0,
    DC_MOTOR_ON
}dc_motor_status_t;
typedef enum{
    DC_MOTOR_RIGHT=0,
    DC_MOTOR_LEFT 
}dc_motor_direction_t;

typedef struct{
    pin_config_t dc_motor_pins[2];
    pin_config_t dc_motor_EN;
    dc_motor_status_t dc_motor_status;
    dc_motor_direction_t dc_motor_direction;
    uint8_t dc_motor_speed ;//to do
}dc_motor_config_t;

/* section : Function Declaration*/

Std_ReturnType motor_initialize(const dc_motor_config_t *dc_motor);
Std_ReturnType motor_turn_on(dc_motor_config_t *dc_motor, dc_motor_direction_t dc_motor_direction );
Std_ReturnType motor_stop(dc_motor_config_t *dc_motor);
Std_ReturnType motor_set_speed(dc_motor_config_t *dc_motor, uint8_t dc_motor_speed); //to do

#endif