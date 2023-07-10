#include "led_task.h"


void led_task(void *pvParameters){
	

	for( ; ; ){
		
				GPIO_write(PORT_0, PIN1, PIN_IS_HIGH);
				vTaskDelay(LED_DELAY_TASK_1_SEC);
				GPIO_write(PORT_0, PIN1, PIN_IS_LOW);
				vTaskDelay(LED_DELAY_TASK_1_SEC);
	
	}
}