#include "led_task.h"


void led_task(void *pvParameters){
	uint16_t delay_value = 1000;
	pinX_t pin_num = PIN1;
	if(pvParameters != NULL){
		delay_value = ((led_task_config *)pvParameters)->delay;
		pin_num = ((led_task_config *)pvParameters)->pin_num;
	
	}

	for( ; ; ){
		
				GPIO_write(PORT_0, pin_num, PIN_IS_HIGH);
				vTaskDelay(delay_value);
				GPIO_write(PORT_0, pin_num, PIN_IS_LOW);
				vTaskDelay(delay_value);
	
	}
}