

#include <avr/interrupt.h>
#include "APP/app.h"
#include "MCAL/Timer/Timer.h"
#include "ECUAL/Timing/Timing.h"



int main(void)
{
	
	app_init();

	
    while(1){
		app_start();
		
	}

    return 0;
}



