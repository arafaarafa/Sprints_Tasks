#include "button_task.h"


void button_task(void *pvParameters){

	
	pinState_t button_state;
	uint8_t sec_counter =0;
	
	
	for(;;){
		button_state = GPIO_read(PORT_0, ((button_task_config *)pvParameters)->pin_num);
		if(button_state == PIN_IS_HIGH){
			while(button_state == PIN_IS_HIGH){
				vTaskDelay(BUTTON_TASK_DELAY);
				button_state = GPIO_read(PORT_0, ((button_task_config *)pvParameters)->pin_num);
			}
			
			xSemaphoreGive( *(((button_task_config *)pvParameters)->semaphore));
			vTaskDelay(BUTTON_TASK_DELAY);
		
		}
		
	}
	vTaskDelay(BUTTON_TASK_DELAY);
}