#include "Timing.h"

static timer_configuration_t timer_configuration;


static void (*tmp_callBack)(void);




static void function_callback(void)
{	(*tmp_callBack)();
	TCNT0_ADD = timer_configuration.OCR;
}
	
	
Std_ReturnType timing_init(uint16_t time_us , void (*callback)(void)){
	volatile uint16_t timer_init_value =0;
	volatile uint32_t max_delay =0;
	volatile uint32_t cycle_time=0;	
	volatile uint32_t prescaller = 256;
	volatile uint64_t prscaller_max_regiter = 65536;
	Std_ReturnType ret = E_OK;
	max_delay = (((double)prscaller_max_regiter/MCU_CLOCK)*1000000);
	cycle_time = ((double)prescaller/MCU_CLOCK)*1000000;
	timer_init_value = (double)(max_delay- time_us)/cycle_time;
	
	if(time_us < 1000 ){
		ret =E_NOT_OK;
	}else{
		if(MCU_CLOCK ==0)
			return E_NOT_OK;
		timer_configuration.OCR=timer_init_value;
		timer_configuration.timer_mode = TIMER_MODE_NORMAL;
		timer_configuration.timer_prescaller=TIMER_PRESCALLER_256;
		timer_configuration.timer_of_interrupt =TIMER_OVERFLOW_INTERRUPT_ENABLE;
		tmp_callBack = callback;
		timer_initialize_callback_OVF(function_callback);
		timer0_initialization(&timer_configuration);			
	}

	return ret;
}



void timing_start(void){
	timer_start(&timer_configuration);
	
}


void timing_stop(){
	
	timer_stop(&timer_configuration);
}