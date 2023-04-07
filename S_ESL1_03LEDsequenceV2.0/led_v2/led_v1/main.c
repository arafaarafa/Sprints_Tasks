

#include <avr/interrupt.h>
#include "APP/app.h"






button_INT_t btn_trail,btn_trail_2;

int main(void)
{
	
	
	app_init();
    while(1){
		app_start();
	}

    return 0;
}



