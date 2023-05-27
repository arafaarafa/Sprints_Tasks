/*
 * BCM_MCU_2.c
 *
 * Created: 5/24/2023 8:02:40 PM
 * Author : Arafa
 */ 

#include "../SERVICE/BCM/BCM.h"
#include "../ECUAL/LED/LED.h"
/* to define the maximum size of array*/
#define  BUFFER_MAX_SIZE 50
/*
*
*
* -enu_transmit_or_receive_t datatype enum to know the app in which state
*   -Members-
*
* -1-TRANSMIT
* -2-RECEIVE
*
*/
typedef enum{
	TRANSMIT,
	RECEIVE
}enu_transmit_or_receive_t;

/*
*   -Description-
*-used to init all global variables
*

*
*   -Return- : void
*
*/
void app_init(void);
/*
*   -Description-
*-used to run the app and included the super loop
*

*
*   -Return- : void
*
*/
void app_run(void);