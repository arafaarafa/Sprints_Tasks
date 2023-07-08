#ifndef button_TASK_H
#define button_TASK_H
#include <string.h>
#include "FreeRTOS.h"
#include "GPIO.h"
#include "task.h"
#include "semphr.h"
#include "common.h"


/* configration struct to config the task with wanted pin to toggle and its duration*/
typedef struct{
    sender_id id;
    pinX_t pin_num;/*pin number*/
		QueueHandle_t *queue; /*pointer to queue*/
}button_task_config;

/*task to toggle the led every 1 sec*/
void button_task(void *pvParameters);
#endif


