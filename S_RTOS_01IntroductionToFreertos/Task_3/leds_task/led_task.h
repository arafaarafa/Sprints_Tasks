#ifndef LED_TASK_H
#define LED_TASK_H
#include "FreeRTOS.h"
#include "GPIO.h"
#include "task.h"

/* configration struct to config the task with wanted pin to toggle and its duration*/
typedef struct{
    pinX_t pin_num;/*pin number*/
    uint16_t delay;/*delay of configration*/
}led_task_config;

/*task to toggle the led every 1 sec*/
void led_task(void *pvParameters);
#endif


