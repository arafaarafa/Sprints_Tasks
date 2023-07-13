#ifndef LED_TASK_H
#define LED_TASK_H
#include "FreeRTOS.h"
#include "GPIO.h"
#include "task.h"

#define LED_DELAY_TASK_1_SEC                            1000
/*task to toggle the led every 1 sec*/
void led_task(void *pvParameters);
#endif