#include "app.h"

uint8_t led_counter = 0;
led_t led[4];
button_INT_t btn_1;
uint8_t flag_accure =1;




void function_trial(void){
	if(flag_accure != 0){
		led_counter++;
		flag_accure =0;
	}
	
	
}

void app_init(void){
	
	/*led 1 configuration*/
	led[0].port_name=PORTA_INDEX;
	led[0].pin=PIN_0;
	led[0].led_status= LED_OFF;
	
	/*led 2 configuration*/
	led[1].port_name=PORTA_INDEX;
	led[1].pin=PIN_1;
	led[1].led_status= LED_OFF;
	
	/*led 3 configuration*/
	led[2].port_name=PORTA_INDEX;
	led[2].pin=PIN_2;
	led[2].led_status= LED_OFF;
	
	/*led 4 configuration*/
	led[3].port_name=PORTA_INDEX;
	led[3].pin=PIN_3;
	led[3].led_status= LED_OFF;
	
	/*button 1 configuration*/
	btn_1.pin_INT_config.INT_mode = FALLING_EDGE;
	btn_1.pin_INT_config.pin_config.port = PORTD_INDEX;
	btn_1.pin_INT_config.pin_config.pin = PIN_2;
	btn_1.pin_INT_config.pin_config.direction = GPIO_DIRECTION_INPUT;
	
	
	/*init all leds and button*/
	led_intialize(&led[0]);
	led_intialize(&led[1]);
	led_intialize(&led[2]);
	led_intialize(&led[3]);
	button_with_INT(&btn_1, function_trial);
	
}



void app_start(void){
	static uint8_t prev_state=0;
	button_disable_INT(&btn_1);
	if(prev_state != led_counter){
		led_toggle(&led[led_counter-1]);
		
		if(led_counter>=4){
			led_counter =0;
			
		}
		prev_state = led_counter;
		flag_accure = 1;
	}
	button_enable_INT(&btn_1);
	for(int x = 0;x<5000; x++);
	
	
	
	
}
