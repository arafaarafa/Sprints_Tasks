ifndef LED_H
#define	LED_H


/* section : includes*/
#include "../../MCAL_layer/GPIO/GPIO.h"


/* section : Macro Declaration*/


/* section : Macro Functions Declarations*/

/* section : Data Types Declarations*/
typedef enum {
    LED_OFF=0,
    LED_ON
}led_status_t;

typedef struct{
    uint8 port_name:4;
    uint8 pin:3;
    uint8 led_status:1;
}led_t;

/* section : Function Declaration*/
Std_ReturnType led_intialize(led_t *);
Std_ReturnType led_turn_on(led_t *);
Std_ReturnType led_turn_off(led_t *);
Std_ReturnType led_toggle(led_t *);

#endif
