#ifndef CONSUMER_TASK_H
#define CONSUMER_TASK_H
#include <string.h>
#include "FreeRTOS.h"
#include "GPIO.h"
#include "task.h"
#include "semphr.h"
#include "common.h"


/* configration struct to config the consumert task */
typedef struct{
    sender_id id; /*id used for message*/
    uint16_t delay; /*delay value*/
		QueueHandle_t *queue; /*pointer to queue*/
}consumer_task_config;

/*task run every spacific delay*/
void consumer_task(void *pvParameters);

#endif


