#ifndef COMMON_H
#define COMMON_H

typedef enum{
	BUTTON_TASK_1,
	BUTTON_TASK_2,
	CONSUMER_TASK
}sender_id;

typedef struct{
	   sender_id id;
     char ucData[ 20 ];
}message_packet; 

#endif
