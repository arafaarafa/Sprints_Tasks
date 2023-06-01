/*
 * OS.c
 *
 * Created: 5/30/2023 12:12:23 AM
 *  Author: Arafa
 */ 
#include "OS.h"
#include "OS_Private.h"


static sos_str_task_database_cols_t tasks_database[SOS_MAX_NUMBER_TASKS + TASK_MARGING_INDEX]; /*array of task its size max number form user plus task margin defined by developer to ignore to use index zero , give the availability to add idle task*/
static sos_task_id_t tasks_ready[SOS_MAX_NUMBER_TASKS + TASK_MARGING_INDEX]; /*all task that will ready will be sotored in it */
static sos_enu_scheduler_state_t  scheduler_state = SOS_SCHEDULER_ENABLED; /*flag to enable or disbale scheduler */
static sos_sys_tick_t sys_tick = 0; /*that will be the refrence to time in the system*/
static uint8_t tasks_counter = 0; /*the task counter about the created tasks */

/*
*   -Description-
*-This static api will schedule the tasks 
*
*/
static sos_enu_return_state_t sos_scheduler(void); 

/*
*   -Description-
*-This static api will execute all ready tasks
*
*/
static sos_enu_return_state_t sos_executer(void); 