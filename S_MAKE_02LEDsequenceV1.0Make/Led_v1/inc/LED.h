#ifndef LED_H
#define	LED_H


/* section : includes*/
#include "DIO.h"


/* section : Macro Declaration*/


/* section : Macro Functions Declarations*/

/* section : Data Types Declarations*/
typedef enum {
    LED_OFF=0,
    LED_ON
}led_status_t;

typedef struct{
    uint8_t port_name:4;
    uint8_t pin:3;
    uint8_t led_status:1;
}led_t;

/* section : Function Declaration*/
Std_ReturnType led_intialize(led_t *);
Std_ReturnType led_turn_on(led_t *);
Std_ReturnType led_turn_off(led_t *);
Std_ReturnType led_toggle(led_t *);

#endif
