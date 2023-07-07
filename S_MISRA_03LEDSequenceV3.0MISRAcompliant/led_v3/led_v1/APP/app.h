#ifndef APP_H
#define APP_H
#include "../ECUAL/LED/LED.h"
#include "../ECUAL/Push Button/PushButton.h"
#include "../ECUAL/Timing/Timing.h"


#define LED_NO 4 //the number of leds
#define MODES_NO 5 //the number of modes
#define lED_STATE_FORM (LED_NO+1) //this define used in formula to calculate the which LEDs on or off 

/*
*
*
* -modes_t datatype hold the mode on and off duration
*   -Members-
* -1-  (uint16_t time_on) ON time duration
* -2-  (uint16_t time_off) OFF time  duration
*
*/
typedef struct{
	uint16_t time_on;
	uint16_t time_off;
}modes_t;

/**
 *
 * @description initialize all modules
 * @param void
 * @return void
 */
extern void app_init(void);

/**
 *
 * @description start app functionality 
 * @param void
 * @return void
 */
extern void app_start(void);


#endif