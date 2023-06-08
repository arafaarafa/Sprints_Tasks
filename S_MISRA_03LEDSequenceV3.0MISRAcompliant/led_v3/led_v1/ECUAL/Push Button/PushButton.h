#ifndef PUSH_BUTTON_H
#define	PUSH_BUTTON_H

/* section : includes*/
#include "../../MCAL/DIO/DIO.h"


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

typedef struct{
	pin_INT_config_t pin_INT_config;
}button_INT_t;

/* section : Function Declaration*/

Std_ReturnType button_initializa(const button_t* btn);
Std_ReturnType button_read_state( button_t *btn, button_state_t *btn_state);
Std_ReturnType button_with_INT( button_INT_t *btn_INT , void (*func)(void));
Std_ReturnType button_enable_INT( button_INT_t *btn_INT);
Std_ReturnType button_disable_INT( button_INT_t *btn_INT);
#endif	/* PUSH_BUTTON_H */
