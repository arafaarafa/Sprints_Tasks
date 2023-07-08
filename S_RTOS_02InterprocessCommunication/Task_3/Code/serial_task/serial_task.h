#ifndef SERIAL_TASK_H
#define SERIAL_TASK_H
#include "FreeRTOS.h"
#include "GPIO.h"
#include "task.h"
#include "semphr.h"
#include "serial.h"
#include "common.h"



/* configration struct to config the serial task and its duration*/
typedef struct{
	QueueHandle_t *queue; /*pointer to queue*/
}serial_task_config;

/*task to send data*/
void serial_task(void *pvParameters);
#endif


