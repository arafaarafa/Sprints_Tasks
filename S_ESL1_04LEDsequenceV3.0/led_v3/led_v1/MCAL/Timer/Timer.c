#include "Timer.h"

static void (*timer_callback_OVF)(void) = NULL;
static void (*timer_callback_COMP)(void) = NULL;

Std_ReturnType timer0_initialization(timer_configuration_t *timer_configuration){
	Std_ReturnType ret = E_OK;
	if(timer_configuration == NULL ){
		ret =E_NOT_OK;
	}
	else{
		TCCR0_ADD |= ((1&timer_configuration->timer_mode)<<WGM00_bit);
		TCCR0_ADD |= ((timer_configuration->timer_mode>>1)<<WGM01_bit);
		if(timer_configuration->timer_mode == TIMER_MODE_NORMAL){
			
			TIMSK_ADD |= ((timer_configuration->timer_oc_interrupt<<1)|timer_configuration->timer_of_interrupt);
			if(timer_configuration->timer_of_interrupt == 1 || timer_configuration->timer_oc_interrupt == 1){
				sei();
			}
		}
	}

	return ret;
	
	
}

Std_ReturnType timer_start(timer_configuration_t *timer_configuration){
	Std_ReturnType ret = E_OK;
	if(timer_configuration == NULL ){
		ret =E_NOT_OK;
	}
	else{
		
		
		if(timer_configuration->timer_mode == TIMER_MODE_NORMAL){
			TCNT0_ADD = timer_configuration->OCR;
			TCCR0_ADD |= timer_configuration->timer_prescaller;
		}
	}

	return ret;
	
}


Std_ReturnType timer_stop(timer_configuration_t *timer_configuration){
	Std_ReturnType ret = E_OK;
	if(timer_configuration == NULL ){
		ret =E_NOT_OK;
	}
	else{
		
		
		if(timer_configuration->timer_mode == TIMER_MODE_NORMAL){
			TCCR0_ADD &= ~0b00000111;
		}
	}

	return ret;
	
}
Std_ReturnType timer_initialize_callback_OVF(void (*callback)(void)){
	Std_ReturnType ret = E_OK;
	timer_callback_OVF = callback;
	return ret;
}
Std_ReturnType timer_initialize_callback_COMP(void (*callback)(void)){
	Std_ReturnType ret = E_OK;
	timer_callback_COMP = callback;
	return ret;
}

ISR (TIMER0_OVF_vect)        //Timer overflow interrupt
{
	(*timer_callback_OVF)();
	
}
ISR (TIMER0_COMP_vect)       //Timer compare match interrupt
{
	(*timer_callback_COMP)();
}