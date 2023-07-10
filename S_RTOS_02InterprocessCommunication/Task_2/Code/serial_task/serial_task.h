#ifndef SERIAL_TASK_H
#define SERIAL_TASK_H
#include "FreeRTOS.h"
#include "GPIO.h"
#include "task.h"
#include "semphr.h"
#include "serial.h"


#deine SERIAL_TICKS_WAIT_ON_EVENT						100
#deine SERIAL_DELAY_VALUE_FOR_ENABLE_THE_LOAD			100
/* configration struct to config the serial task and its duration*/
typedef struct{
	uint16_t delay;
	char *data;
	SemaphoreHandle_t *mutex; /*pointer to mutex*/
}serial_task_config;

/*task to send data*/
void serial_task(void *pvParameters);
#endif


