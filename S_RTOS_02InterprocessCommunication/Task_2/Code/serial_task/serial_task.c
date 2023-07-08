#include "serial_task.h"


void serial_task(void *pvParameters){
	uint32_t load_counter;
	uint8_t msg_cnt;
	for( ; ; ){
			if(xSemaphoreTake( *(((serial_task_config *)pvParameters)->mutex),  ( TickType_t ) 100) == pdTRUE){
				for(msg_cnt=0; msg_cnt<10; msg_cnt++){
					vSerialPutString((const signed char*)(((serial_task_config *)pvParameters)->data), 20);
					if(((serial_task_config *)pvParameters)->delay>100){
						for(load_counter=0; load_counter< 100000; load_counter++);
					}
				}
				
				xSemaphoreGive( *(((serial_task_config *)pvParameters)->mutex));
			}
			vTaskDelay(((serial_task_config *)pvParameters)->delay);
			
			
	}
}