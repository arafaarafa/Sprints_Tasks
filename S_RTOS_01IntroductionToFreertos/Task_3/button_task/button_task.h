#ifndef button_TASK_H
#define button_TASK_H
#include "FreeRTOS.h"
#include "GPIO.h"
#include "task.h"

/* configration struct to config the task with wanted pin to toggle and its duration*/
typedef struct{
    pinX_t pin_num;/*pin number*/
    uint16_t *led_delay;/*pointer to delay of led*/
}button_task_config;

/*task to toggle the led every 1 sec*/
void button_task(void *pvParameters);
#endif


