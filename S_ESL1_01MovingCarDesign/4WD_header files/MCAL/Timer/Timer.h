#ifndef TIMER_H
#define TIMER_H

/* section : includes*/
#include "../../Std_Types.h"

/* section : Macro Declaration*/


/*
 *
 *  Macros to enable or disable compare match interrupt
 * 
 * 
*/
#define TIMER_OUTPUT_COMPARE_MATCH_INTERRUPT_ENABLE      1
#define TIMER_OUTPUT_COMPARE_MATCH_INTERRUPT_DISABLE     0


/*
 *
 *  Macros to enable or disable overflow interrupt
 * 
 * 
*/
#define TIMER_OVERFLOW_INTERRUPT_ENABLE                  1
#define TIMER_OVERFLOW_INTERRUPT_DISABLE                 0



/* section : Data Types Declarations*/


/*
*
*
* -timer_mode_t datatype enum has all timer modes
*   -Members-
*
* -1-TIMER_MODE_NORMAL
* -2-TIMER_MODE_PWM  Pulse Width Modulation
* -3-TIMER_MODE_CTC  Clear Timer on Compare Match
*
*/
typedef enum{
    TIMER_MODE_NORMAL,
    TIMER_MODE_PWM,
    TIMER_MODE_CTC,
}timer_mode_t;

/*
*
*
* -PWM_mode_t datatype enum has all PWM modes
*   -Members-
*
* -1-PWM_NORMAL_DISCONNECTED
* -2-PWM_MODE_0  Clear OC0 on compare match when up-counting. Set OC0 on compare match when downcounting
* -3-PWM_MODE_1  Set OC0 on compare match when up-counting. Clear OC0 on compare match when downcounting.
*
*/
typedef enum{
    PWM_NORMAL_DISCONNECTED,
    PWM_MODE_0=2,
    PWM_MODE_1=3,
}PWM_mode_t;


/*
*
*
* -timer_prescaller_t datatype enum has all prescaller modes
*   -Members-
*
* -1-TIMER_STOP
* -2-TIMER_PRESCALLER_0
* -3-TIMER_PRESCALLER_8
* -4-TIMER_PRESCALLER_64
* -5-TIMER_PRESCALLER_256
* -6-TIMER_PRESCALLER_1024
* -7-TIMER_EXT_CLK_FALLING_EDGE
* -8-TIMER_EXT_CLK_RISING_EDGE
*
*/
typedef enum{
    TIMER_STOP,
    TIMER_PRESCALLER_0,
    TIMER_PRESCALLER_8,
    TIMER_PRESCALLER_64,
    TIMER_PRESCALLER_256,
    TIMER_PRESCALLER_1024,
    TIMER_EXT_CLK_FALLING_EDGE,
    TIMER_EXT_CLK_RISING_EDGE
}timer_prescaller_t;

/*
*
*
* -timer_configuration_t datatype hold the transaction data
*   -Members-
* -1-  (timer_mode_t timer_mode) timer mode 
* -2-  (timer_prescaller_t timer_prescaller) timer prescaller
* -3-  (uint8_t OCR) the initial value of OCR
* -4-  (uint8_t timer_oc_interrupt) Enable or Disable interrupt compare match
* -5-  (uint8_t timer_of_interrupt) Enable or Disable interrupt overflow
*
*/
typedef struct 
{   timer_mode_t timer_mode;
    timer_prescaller_t timer_prescaller;
    uint8_t OCR;
    uint8_t timer_oc_interrupt :1;
    uint8_t timer_of_interrupt :1;

}timer_configuration_t;


/*section : Global variable*/
static void (*timer_callback_OVF)(void);
static void (*timer_callback_COMP)(void);

/* section : Function Declaration*/
/*
*   -Description-
*-this function init the timer configuration
*
*   -Input Output parameters -
*-1-it holds timer configuration  (timer_configuration_t *timer_configuration)
*
*   -Return-
*   Std_ReturnType
*
*   -Return cases-
*-1- (E_NOK) if there is something wrong
*-2- (E_OK) otherwise
*/
Std_ReturnType timer_initialization(timer_configuration_t *timer_configuration);

/*
*   -Description-
*-this function init timer_callback_OVF with address of callback address
*
*   -Input Output parameters -
*-1-it is pointer to callback funtion  (void (*callback)(void))
*
*   -Return-
*   Std_ReturnType
*
*   -Return cases-
*-1- (E_NOK) if there is something wrong
*-2- (E_OK) otherwise
*/
Std_ReturnType timer_initializ_callback_OVF(void (*callback)(void));

/*
*   -Description-
*-this function init timer_callback_COMP with address of callback address
*
*   -Input Output parameters -
*-1-it is pointer to callback funtion  (void (*callback)(void))
*
*   -Return-
*   Std_ReturnType
*
*   -Return cases-
*-1- (E_NOK) if there is something wrong
*-2- (E_OK) otherwise
*/
Std_ReturnType timer_initializ_callback_COMP(void (*callback)(void));


ISR (TIMER_OVF_vect)        //Timer overflow interrupt
{
	timer_callback_OVF();
}
ISR (TIMER_COMP_vect)       //Timer compare match interrupt
{
	timer_callback_OVF();
}




#endif