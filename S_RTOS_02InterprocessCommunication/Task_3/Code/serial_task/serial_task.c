#include "serial_task.h"


void serial_task(void *pvParameters){
	message_packet data;
	uint8_t counter=0;
	for( ; ; ){
		
		
			if( xQueueReceive( *(((serial_task_config *)pvParameters)->queue), &(data), ( TickType_t ) 200 ) == pdPASS )
      {
				for (counter=0;data.ucData[counter]!= '\0';counter++);
				vSerialPutString((const signed char*)(&data), ++counter);
			}
				
			
	}
}