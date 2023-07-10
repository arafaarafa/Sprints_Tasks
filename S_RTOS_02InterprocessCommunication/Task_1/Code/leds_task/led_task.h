#ifndef LED_TASK_H
#define LED_TASK_H
#include "FreeRTOS.h"
#include "GPIO.h"
#include "task.h"
#include "semphr.h"

#define LED_TASK_DELAY								25
#define LED_TICKS_WAIT_ON_EVENT						0
typedef enum{
	LED_OFF,
	LED_ON
}led_state;
/* configration struct to config the task with wanted pin to toggle and its duration*/
typedef struct{
    pinX_t pin_num;/*pin number*/
		SemaphoreHandle_t *semaphore; /*pointer to semaphore*/
}led_task_config;

/*task to toggle the led every 1 sec*/
void led_task(void *pvParameters);
#endif


