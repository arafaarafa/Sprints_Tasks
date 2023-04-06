#ifndef APP_H
#define APP_H
#include "../ECUAL/LED/LED.h"
#include "../ECUAL/Push Button/PushButton.h"
#define LED_NO 4


/**
 *
 * @description initialize all modules
 * @param void
 * @return void
 */
void app_init(void);

/**
 *
 * @description start app functionality 
 * @param void
 * @return void
 */
void app_start(void);


#endif