#ifndef button_TASK_H
#define button_TASK_H
#include "FreeRTOS.h"
#include "GPIO.h"
#include "task.h"

#define DELAY_100                           100
#define DELAY_400                           400
#define DELAY_0                             0
#define BUTTON_DELAY_TASK                   200
#define BUTTON_DELAY_TASK_1_SEC             1000
#define BUTTON_PRESSED_4_SEC                4
#define BUTTON_PRESSED_2_SEC                2

/* configration struct to config the task with wanted pin to toggle and its duration*/
typedef struct{
    pinX_t pin_num;/*pin number*/
    uint16_t *led_delay;/*pointer to delay of led*/
}button_task_config;

/*task to toggle the led every 1 sec*/
void button_task(void *pvParameters);
#endif


