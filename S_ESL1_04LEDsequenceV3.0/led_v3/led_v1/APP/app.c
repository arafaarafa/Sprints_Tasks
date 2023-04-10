#include "app.h"

int8_t led_counter = 0;
uint8_t mode_counter = 0;
led_t led[4];
button_INT_t btn_1,btn_2;
uint8_t flag_led_accure =1;
uint8_t flag_mode_accure =1;
uint16_t sys_tick = 0;
modes_t modes[MODES_NO];


/*section : Global variable*/

/* section : Function Declaration*/
/*
*   -Description-
*-this function is the callback function for led counter
*
*/
void function_LEDs(void){

		led_counter++;
		if(led_counter>7){
			led_counter=0;
		}

	
	
}

/*
*   -Description-
*-this function is the callback function for mode counter
*
*/
void function_Modes(void){
	
		mode_counter++;
		if(mode_counter>4){
			mode_counter=0;
		}

	
	
}
/*
*   -Description-
*-this function is the callback function for sys_tick
*
*/
void function_Systick(void){
	sys_tick ++;
	
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
	
	/*button 2 configuration*/
	btn_2.pin_INT_config.INT_mode = FALLING_EDGE;
	btn_2.pin_INT_config.pin_config.port = PORTD_INDEX;
	btn_2.pin_INT_config.pin_config.pin = PIN_3;
	btn_2.pin_INT_config.pin_config.direction = GPIO_DIRECTION_INPUT;
	
	modes[0].time_on = 100;
	modes[0].time_off = 900;


	modes[1].time_on = 200;
	modes[1].time_off = 800;

	modes[2].time_on = 300;
	modes[2].time_off = 700;

	modes[3].time_on = 500;
	modes[3].time_off = 500;

	modes[4].time_on = 800;
	modes[4].time_off = 200;
	
	/*init all leds and buttons*/
	led_intialize(&led[0]);
	led_intialize(&led[1]);
	led_intialize(&led[2]);
	led_intialize(&led[3]);
	button_with_INT(&btn_1, function_LEDs);
	button_with_INT(&btn_2, function_Modes);
	timing_init(1000, function_Systick);
	button_enable_INT(&btn_1);
	button_enable_INT(&btn_2);
	timing_start();
	
}



void app_start(void){
	static uint8_t prev_state=0;          
	uint8_t mode_counter_tmp = 0,
			led_counter_tmp =0;
	
	button_disable_INT(&btn_2);
	mode_counter_tmp = mode_counter;
	button_enable_INT(&btn_2);	
		
	if(sys_tick<= modes[mode_counter_tmp].time_on){
		if(prev_state == 0){
			button_disable_INT(&btn_1);
			led_counter_tmp = led_counter;
			button_enable_INT(&btn_1);
			for(uint8_t i=0;i<LED_NO;i++){
				if((led_counter_tmp/lED_STATE_FORM)!=1){
					if(i<(led_counter_tmp%lED_STATE_FORM)){
						led_turn_on(&led[i]);
						}else{
						
						led_turn_off(&led[i]);
					}
				}else{
					if(i<=(led_counter_tmp%lED_STATE_FORM)){
						led_turn_off(&led[i]);	
					}else{
						led_turn_on(&led[i]);	
					}
					
				}
			}
			prev_state = 1;
		}
		
		
	}else if(sys_tick<(modes[mode_counter_tmp].time_on+modes[mode_counter_tmp].time_off)){
		if(prev_state == 1){
			for(uint8_t i=0;i<LED_NO;i++){
				led_turn_off(&led[i]);
			}
			prev_state = 0;
		}
		
	}else{
		timing_stop();
		sys_tick=0;
		timing_start();
	}
		
	
	
	
}
