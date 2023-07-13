#include "led_task.h"


void led_task(void *pvParameters){
	led_state prev_state = LED_OFF;
	GPIO_write(PORT_0, ((led_task_config *)pvParameters)->pin_num, PIN_IS_LOW);
	for( ; ; ){
				if( xSemaphoreTake( *(((led_task_config *)pvParameters)->semaphore), ( TickType_t ) LED_TICKS_WAIT_ON_EVENT) == pdTRUE ){
					 if(prev_state == LED_OFF){
						 GPIO_write(PORT_0, ((led_task_config *)pvParameters)->pin_num, PIN_IS_HIGH);
						 prev_state = LED_ON;
					 }else{
						 GPIO_write(PORT_0, ((led_task_config *)pvParameters)->pin_num, PIN_IS_LOW);
						 prev_state = LED_OFF;
					 }
				}
					vTaskDelay(LED_TASK_DELAY);
	}
}