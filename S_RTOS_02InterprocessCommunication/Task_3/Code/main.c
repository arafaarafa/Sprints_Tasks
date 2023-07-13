/*
 * FreeRTOS Kernel V10.2.0
 * Copyright (C) 2019 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * http://www.FreeRTOS.org
 * http://aws.amazon.com/freertos
 *
 * 1 tab == 4 spaces!
 */

/* 
	NOTE : Tasks run in system mode and the scheduler runs in Supervisor mode.
	The processor MUST be in supervisor mode when vTaskStartScheduler is 
	called.  The demo applications included in the FreeRTOS.org download switch
	to supervisor mode prior to main being called.  If you are not using one of
	these demo application projects then ensure Supervisor mode is used.
*/


/*
 * Creates all the demo application tasks, then starts the scheduler.  The WEB
 * documentation provides more details of the demo application tasks.
 * 
 * Main.c also creates a task called "Check".  This only executes every three 
 * seconds but has the highest priority so is guaranteed to get processor time.  
 * Its main function is to check that all the other tasks are still operational.
 * Each task (other than the "flash" tasks) maintains a unique count that is 
 * incremented each time the task successfully completes its function.  Should 
 * any error occur within such a task the count is permanently halted.  The 
 * check task inspects the count of each task to ensure it has changed since
 * the last time the check task executed.  If all the count variables have 
 * changed all the tasks are still executing error free, and the check task
 * toggles the onboard LED.  Should any task contain an error at any time 
 * the LED toggle rate will change from 3 seconds to 500ms.
 *
 */

/* Standard includes. */
#include <stdlib.h>
#include <stdio.h>

/* Scheduler includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "lpc21xx.h"
#include "task.h"
#include "semphr.h"
#include "queue.h"
/* Peripheral includes. */
#include "serial.h"
#include "GPIO.h"
/* Tasks includes*/
#include "common.h"
#include "serial_task.h"
#include "button_task.h"
#include "consumer_task.h"
/*-----------------------------------------------------------*/

/* Constants to setup I/O and processor. */
#define mainBUS_CLK_FULL	( ( unsigned char ) 0x01 )

/* Constants for the ComTest demo application tasks. */
#define mainCOM_TEST_BAUD_RATE	( ( unsigned long ) 115200 )




/*
 * Configure the processor for use with the Keil demo board.  This is very
 * minimal as most of the setup is managed by the settings in the project
 * file.
 */
static void prvSetupHardware( void );
/*-----------------------------------------------------------*/
#define CONSUMER_TASK_DELAY						100

/*-------------------------------------------------*/

TaskHandle_t Serial_Task_Handler = NULL;
TaskHandle_t Button_Task_1_Handler = NULL;
TaskHandle_t Button_Task_2_Handler = NULL;
TaskHandle_t Consumer_Task_Handler = NULL;

QueueHandle_t xStructQueue = NULL;

serial_task_config serial_task_cfg;
button_task_config button_task_1_cfg;
button_task_config button_task_2_cfg;
consumer_task_config consumer_task_cfg;


/*
 * Application entry point:
 * Starts all the other tasks, then starts the scheduler. 
 */
int main( void )
{
	/*global vars*/
	xStructQueue = xQueueCreate(10, sizeof( message_packet ) );
	
	
	
	/*****************button cfg 1**********************/
	serial_task_cfg.queue = &xStructQueue;
	
	
	/*****************button cfg 2**********************/
	button_task_1_cfg.id = BUTTON_TASK_1;
	button_task_1_cfg.pin_num = PIN0;
	button_task_1_cfg.queue = &xStructQueue;
	
	
	/*****************button cfg 1**********************/
	button_task_2_cfg.id = BUTTON_TASK_2;
	button_task_2_cfg.pin_num = PIN7;
	button_task_2_cfg.queue = &xStructQueue;
	
	/*************consumer cfg**************/
	consumer_task_cfg.id = CONSUMER_TASK;
	consumer_task_cfg.delay = CONSUMER_TASK_DELAY;
	consumer_task_cfg.queue = &xStructQueue;
	
	
	
	
	/* Setup the hardware for use with the Keil demo board. */
	prvSetupHardware();
	
										
									
    /* Create Tasks here */
	/***************************serial_task**************************************/	
	xTaskCreate(
                    serial_task,       							/* Function that implements the task. */
                    "serial_task",          						/* Text name for the task. */
                    configMINIMAL_STACK_SIZE,     /* Stack size in words, not bytes. */
                    &serial_task_cfg,    					/* Parameter passed into the task. */
                    1,							/* Priority at which the task is created. */
                    &Serial_Task_Handler );
										
										
										
	/***************************button task 1**************************************/	
	xTaskCreate(
                    button_task,       							/* Function that implements the task. */
                    "button_task_1",          						/* Text name for the task. */
                    configMINIMAL_STACK_SIZE,     /* Stack size in words, not bytes. */
                    &button_task_1_cfg,    					/* Parameter passed into the task. */
                    1,							/* Priority at which the task is created. */
                    &Button_Task_1_Handler );
										
		/***************************button task 2**************************************/	
	xTaskCreate(
                    button_task,       							/* Function that implements the task. */
                    "button_task_2",          						/* Text name for the task. */
                    configMINIMAL_STACK_SIZE,     /* Stack size in words, not bytes. */
                    &button_task_2_cfg,    					/* Parameter passed into the task. */
                    1,							/* Priority at which the task is created. */
                    &Button_Task_2_Handler );
										
		/***************************consumer task**************************************/	
	xTaskCreate(
                    consumer_task,       							/* Function that implements the task. */
                    "consumer_task",          						/* Text name for the task. */
                    configMINIMAL_STACK_SIZE,     /* Stack size in words, not bytes. */
                    &consumer_task_cfg,    					/* Parameter passed into the task. */
                    1,							/* Priority at which the task is created. */
                    &Consumer_Task_Handler );


	/* Now all the tasks have been started - start the scheduler.

	NOTE : Tasks run in system mode and the scheduler runs in Supervisor mode.
	The processor MUST be in supervisor mode when vTaskStartScheduler is 
	called.  The demo applications included in the FreeRTOS.org download switch
	to supervisor mode prior to main being called.  If you are not using one of
	these demo application projects then ensure Supervisor mode is used here. */
	vTaskStartScheduler();

	/* Should never reach here!  If you do then there was not enough heap
	available for the idle task to be created. */
	for( ;; );
}
/*-----------------------------------------------------------*/

/* Function to reset timer 1 */
void timer1Reset(void)
{
	T1TCR |= 0x2;
	T1TCR &= ~0x2;
}

/* Function to initialize and start timer 1 */
static void configTimer1(void)
{
	T1PR = 1000;
	T1TCR |= 0x1;
}

static void prvSetupHardware( void )
{
	/* Perform the hardware setup required.  This is minimal as most of the
	setup is managed by the settings in the project file. */

	/* Configure UART */
	xSerialPortInitMinimal(mainCOM_TEST_BAUD_RATE);
	
	
	
	/* Configure GPIO */
	GPIO_init();
	
	/* Config trace timer 1 and read T1TC to get current tick */
	configTimer1();

	/* Setup the peripheral bus to be the same as the PLL output. */
	VPBDIV = mainBUS_CLK_FULL;
}
/*-----------------------------------------------------------*/



/* Task to be created. */



