#include "consumer_task.h"


void consumer_task(void *pvParameters){


	message_packet data;
	for(;;){
		data.id = ((consumer_task_config *)pvParameters)->id;
		strcpy( data.ucData, "consumer_task" );
		xQueueSend( *(((consumer_task_config *)pvParameters)->queue), ( void * ) &data, ( TickType_t ) 50 );
		vTaskDelay(((consumer_task_config *)pvParameters)->delay);
	}
		
	
}