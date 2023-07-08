#include "button_task.h"


void button_task(void *pvParameters){

	
	pinState_t button_state;
	pinState_t prev_state;
	message_packet data;

	
	data.id = ((button_task_config *)pvParameters)->id;
  prev_state = PIN_IS_HIGH;
	
	
	for(;;){
		button_state = GPIO_read(PORT_0, ((button_task_config *)pvParameters)->pin_num);
		
		if((prev_state == PIN_IS_LOW) && (button_state == PIN_IS_HIGH)){
			if(data.id == BUTTON_TASK_1){
				strcpy( data.ucData, "raising_t1" );
			}else if(data.id == BUTTON_TASK_2){
				strcpy( data.ucData, "raising_t2" );
			}	
			xQueueSend( *(((button_task_config *)pvParameters)->queue), ( void * ) &data, ( TickType_t ) 25 );
			prev_state = PIN_IS_HIGH;
		}else if((prev_state == PIN_IS_HIGH) && (button_state == PIN_IS_LOW)){
			if(data.id == BUTTON_TASK_1){
				strcpy( data.ucData, "falling_t1" );
			}else if(data.id == BUTTON_TASK_2){
				strcpy( data.ucData, "falling_t2" );
			}	
			xQueueSend( *(((button_task_config *)pvParameters)->queue), ( void * ) &data, ( TickType_t ) 25 );
			prev_state = PIN_IS_LOW;
		}else{
			
		}
		vTaskDelay(25);
	}
		
	
}