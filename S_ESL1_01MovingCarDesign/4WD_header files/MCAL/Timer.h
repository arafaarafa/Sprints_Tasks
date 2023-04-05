#ifndef TIMER_H
#define TIMER_H
#include "Std_Types.h"


typedef enum {
    prescaler_2,
    prescaler_4,
    prescaler_8,
    prescaler_16,
    prescaler_32,
    prescaler_64,
    prescaler_128,
    prescaler_256,
}timer_prescaler_t;

typedef struct  
{
    timer_prescaler_t timer_prescaler;
    uint8_t timer_mode;
    
}timer_t;

#endif