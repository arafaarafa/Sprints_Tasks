#include "button_task.h"


void button_task(void *pvParameters){

	
	pinState_t button_state;
	uint8_t sec_counter =0;
	
	for(;;){
		button_state = GPIO_read(PORT_0, ((button_task_config *)pvParameters)->pin_num);
		if(button_state == PIN_IS_HIGH){
			
			while(button_state == PIN_IS_HIGH){
				vTaskDelay(BUTTON_DELAY_TASK_1_SEC);
				sec_counter++;
				button_state = GPIO_read(PORT_0, ((button_task_config *)pvParameters)->pin_num);
			}
			if(sec_counter > BUTTON_PRESSED_4_SEC){
				*(((button_task_config *)pvParameters)->led_delay)= DELAY_100;
			}else if((sec_counter > BUTTON_PRESSED_2_SEC) && (sec_counter < BUTTON_PRESSED_4_SEC)){
				*(((button_task_config *)pvParameters)->led_delay)= DELAY_400;
			}else if(sec_counter < BUTTON_PRESSED_2_SEC){
				*(((button_task_config *)pvParameters)->led_delay)= DELAY_0;
			}else{
			
			}
			
			sec_counter = 0;
			
		}
		vTaskDelay(BUTTON_DELAY_TASK);
	}
	
}