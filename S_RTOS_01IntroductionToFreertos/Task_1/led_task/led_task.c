#include "led_task.h"


void led_task(void *pvParameters){
	

	for( ; ; ){
		
				GPIO_write(PORT_0, PIN1, PIN_IS_HIGH);
				vTaskDelay(1000);
				GPIO_write(PORT_0, PIN1, PIN_IS_LOW);
				vTaskDelay(1000);
	
	}
}