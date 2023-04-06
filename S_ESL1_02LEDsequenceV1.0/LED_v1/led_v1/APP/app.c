#include "app.h"

uint8_t led_counter = 0;
led_t led[4];
button_t btn_1;
button_state_t btn_1_state;

app_init(void){
	
	/*led 1 configuration*/
	led[0].port_name=PORTA_INDEX;
	led[0].pin=PIN0;
	led[0].led_status= LED_OFF;
	
	/*led 2 configuration*/
	led[1].port_name=PORTA_INDEX;
	led[1].pin=PIN1;
	led[1].led_status= LED_OFF;
	
	/*led 3 configuration*/
	led[2].port_name=PORTA_INDEX;
	led[2].pin=PIN2;
	led[2].led_status= LED_OFF;
	
	/*led 4 configuration*/
	led[3].port_name=PORTA_INDEX;
	led[3].pin=PIN3;
	led[3].led_status= LED_OFF;
	
	/*button 1 configuration*/
	btn_1.button_pin.direction = GPIO_DIRECTION_INPUT;
	btn_1.button_pin.pin= PIN4;
	btn_1.button_active =BUTTON_ACTIVE_LOW;
	btn_1.button_state = BUTTON_RELEASED;
	
	/*init all leds and button*/
	led_intialize(&led[0]);
	led_intialize(&led[1]);
	led_intialize(&led[2]);
	led_intialize(&led[3]);
	button_initializa(&btn_1);
	
}



void app_start(void){
	
	button_read_state( &btn_1, &btn_1_state);
	if(btn_1_state == BUTTON_PRESSED){
		led_counter++;
		if(led_counter <= LED_NO){
			led_turn_on(&led[led_counter-1]);
			
			}else{
			led_counter = 0;
			uint8_t i;
			for(i=0;i<LED_NO;i++){
				led_turn_off(&led[i]);
			}
			
		}
		button_read_state( &btn_1, &btn_1_state);
		while(btn_1_state == BUTTON_PRESSED){
			button_read_state( &btn_1, &btn_1_state);
		}
	}
	
}
