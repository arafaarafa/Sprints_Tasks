/*
 * OS.h
 *
 * Created: 5/30/2023 12:12:38 AM
 *  Author: Arafa
 */ 


#ifndef OS_H_
#define OS_H_
#include "../STD_LIBRARIES/STD_TYPES.h"
#include "OS_Config.h"

#define SOS_MAX_TASK_NUMBER_ALLOWED		255		/*max number of tasks can handled by os*/
#define TASK_MARGING_INDEX			1		/* to give margin in database of tasks */
typedef uint8_t sos_task_id_t;				/*task id datatype*/
typedef uint32_t sos_sys_tick_t; 
typedef void(*ptr_function_t)(void);		/*pointer to function */


/***enum task state ***/
typedef enum{
	BLOCKED = 0,	 /* blocked task or waiting for event or period*/                       
	READY,			 /* ready task to run*/              
	SUSPENDED,		 /* task is not waiting and there in not scheduling table*/	
	RUNNING			 /* task is executing */	
}sos_enu_task_state_t;

/***enum secheduler state ***/
typedef enum{
	SOS_SCHEDULER_DISABLED=0,	/*disabled by sos_disable function*/
	SOS_SCHEDULER_ENABLED		/*enabled by sos_enable function*/
}sos_enu_scheduler_state_t;

/***enum task_row_state ***/
/* it help if the row is used or not*/
typedef enum{
	SOS_ROW_NOT_ALLOWED_TO_ASSIGN = 0, /* this row can not to use  because another task assigned to it*/
	SOS_ROW_ALLOWED_TO_ASSIGN		   /* the row is available*/
}sos_enu_task_row_state_t;

/***enum return_state of sos APIs ***/
typedef enum{
	SOS_E_NOT_OK=0,				/*there is something wrong but couldn't defined it */
	SOS_NULL_PTR,				/*null pointer used*/
	SOS_TIME_LIMIT_NOT_OK,		/*periodicity isn't allowed*/
	SOS_TASK_NOT_FOUND,			/*there isn't  task in database by provided task_id */
	SOS_PRIORITY_NOT_ALLOW,		/*priority not allow to use*/
	SOS_SCHEDULER_DISABLED,		/*can't run the scheduler because it is disabled*/
	SOS_EXCEED_NUMBER_OF_TASKS,	/*the max number of tasks exceeded*/
	SOS_E_OK					/*every thing  done*/
}sos_enu_return_state_t;

/***struct task_info ***/
/* it provided by user*/
typedef struct{
	ptr_function_t ptr_task;					/*pointer to task*/
	uint8_t periodicity;						/*periodicity of task*/
	uint8_t priority;							/*periority of task*/
	sos_enu_task_state_t task_state;			/*state of task*/
}sos_str_task_info_t;


/*struct task_database_cols*/
typedef struct{
	sos_task_id_t task_id;						/*id of task provided by sos*/
	sos_enu_task_row_state_t task_row_state;	/*if this row used or no*/
	sos_str_task_info_t  str_task_info;			/*described above*/
	sos_sys_tick_t time_counter;						/*counter to approve the periodicity*/
}sos_str_task_database_cols_t;


/*
*   -Description-
*-This API initialize the SOS
*
*   -Output parameters -
*	void
*
*   -Return-
*   -Return cases-
*-1- SOS_E_NOT_OK: there is something wrong but couldn't defined it
*-2- SOS_EXCEED_NUMBER_OF_TASKS: the max number of tasks exceeded
*/
sos_enu_return_state_t sos_init (void); 

/*
*   -Description-
*-This API deinitialize the SOS
*
*   -Output parameters -
*	void
*
*   -Return-
*   -Return cases-
*-1- SOS_E_NOT_OK: there is something wrong but couldn't defined it 
*/
sos_enu_return_state_t sos_deinit (void);


/*
*   -Description-
*-This API to create task and add it to sos database
*
*   -Input parameters -
*	*ptr_str_task: address of struct has all task info
*
*
*   -Output parameters -
*	* task_id: address of varible to return id of created task
*
*   -Return-
*   -Return cases-
*-1- SOS_E_NOT_OK: there is something wrong but couldn't defined it 
*-2- SOS_NULL_PTR: null pointer used
*-3- SOS_PRIORITY_NOT_ALLOW: priority not allow to use
*-4- SOS_TIME_LIMIT_NOT: periodicity isn't allowed
*-5- SOS_EXCEED_NUMBER_OF_TASKS: the max number of tasks exceeded
 
*/
sos_enu_return_state_t sos_create_task(sos_str_task_info_t *ptr_str_task, sos_task_id_t* task_id);

/*
*   -Description-
*-This API to create task from sos database
*
*   -Input parameters -
*	* task_id: address of varible to return id of created task
*
*
*   -Return-
*   -Return cases-
*-1- SOS_E_NOT_OK: there is something wrong but couldn't defined it 
*-2- SOS_NULL_PTR: null pointer used
*-3- SOS_TASK_NOT_FOUND: there isn't  task in database by provided task_id  
*/
sos_enu_return_state_t sos_delete_task(sos_task_id_t *task_id); 

/*
*   -Description-
*-This API to modify task is sos database
*
*   -Output parameters-
*	*ptr_str_task: address of struct has all task info
*
*
*   -Input parameters-
*	* task_id: address of varible to return id of created task
*
*
*   -Return-
*   -Return cases-
*-1- SOS_E_NOT_OK: there is something wrong but couldn't defined it 
*-2- SOS_NULL_PTR: null pointer used
*-3- SOS_TASK_NOT_FOUND: there isn't  task in database by provided task_id  
*-4- SOS_PRIORITY_NOT_ALLOW: priority not allow to use
*-5- SOS_TIME_LIMIT_NOT: periodicity isn't allowed
*-6- SOS_EXCEED_NUMBER_OF_TASKS: the max number of tasks exceeded
*/
sos_enu_return_state_t sos_modify_task(sos_task_id_t *task_id, sos_str_task_info_t *ptr_str_task);

/*
*   -Description-
*-This API to run sos scheduler and executer
*
*/
sos_enu_return_state_t sos_run(void);

/*
*   -Description-
*-This API to disable scheduler
*
*/
sos_enu_return_state_t sos_disable(void);

/*
*   -Description-
*-This API to enable scheduler
*
*/
sos_enu_return_state_t sos_enable(void);


#endif /* OS_H_ */