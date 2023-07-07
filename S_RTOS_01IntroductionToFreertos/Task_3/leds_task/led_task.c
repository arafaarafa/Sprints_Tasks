#include "led_task.h"


void led_task(void *pvParameters){
	
	for( ; ; ){
		
				if(((led_task_config *)pvParameters)->delay == 0){
					GPIO_write(PORT_0, ((led_task_config *)pvParameters)->pin_num, PIN_IS_LOW);
				}else{
					GPIO_write(PORT_0, ((led_task_config *)pvParameters)->pin_num, PIN_IS_HIGH);
					vTaskDelay(((led_task_config *)pvParameters)->delay);
					GPIO_write(PORT_0, ((led_task_config *)pvParameters)->pin_num, PIN_IS_LOW);
					vTaskDelay(((led_task_config *)pvParameters)->delay);
				}
				
	
	}
}