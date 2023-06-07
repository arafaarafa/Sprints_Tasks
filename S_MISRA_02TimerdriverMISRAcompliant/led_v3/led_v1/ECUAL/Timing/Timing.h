#ifndef TIMING_H
#define TIMING_H
#include "Timing_config.h"
#include "Timing.h"
#include "../../MCAL/Timer/Timer.h"

#ifndef MCU_CLOCK
#error MCU_CLOCK ("didn\'t define") //error to force user to define CPU Frequency
#endif 

/*
*   -Description-
*-this function init the timing system
*
*   -Input parameters -
*-1-it is time of one cycle in timer system the wanted in us   (uint16_t time_us)
*-1-it is the callback function set for timer ISR  (void (*callback)(void))
*
*   -Return-
*   Std_ReturnType
*
*   -Return cases-
*-1- (E_NOK) if there is something wrong
*-2- (E_OK) otherwise
*/
Std_ReturnType timing_init(uint16_t time_us , void (*callback)(void));

/*
*   -Description-
*-this function start the timing system
*
*   -Return-
*	VOID
*/
void timing_start(void);

/*
*   -Description-
*-this function stop the timing system
*
*   -Return-
*	VOID
*/
void timing_stop(void);
#endif