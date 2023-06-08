#include "PushButton.h"

/**
 *
 * @param btn it's pointer has the configuration of button @ref button_t
 * @return status of function could be
 *          E_OK : the function done successfully
 *          E_NOT_OK : the function has issue to perform this action
 */
Std_ReturnType button_initializa(const button_t* btn){
    Std_ReturnType ret = E_OK;
    if(btn == NULL ){
        ret =E_NOT_OK;
    }
    else{
        ret = gpio_pin_direction_initialize(&(btn->button_pin));
    }

    return ret;
}



/**
 *
 * @param btn it's pointer has the configuration of button @ref button_t
 * @param btn_state it's pointer store the returned state of button @ref button_state_t
 * @return status of function could be
 *          E_OK : the function done successfully
 *          E_NOT_OK : the function has issue to perform this action
 */
Std_ReturnType button_read_state( button_t *btn, button_state_t *btn_state){
    Std_ReturnType ret = E_OK;
	logic_t temp_logic;
    if(btn == NULL  || btn_state == NULL){
        ret =E_NOT_OK;
    }
    else{
        
        gpio_pin_read_logic( &(btn->button_pin), &temp_logic);
		
        if(((btn->button_active == BUTTON_ACTIVE_LOW) && (temp_logic == GPIO_LOW)) || ((btn->button_active == BUTTON_ACTIVE_HIGH) && (temp_logic == GPIO_HIGH))){
            *btn_state = BUTTON_PRESSED ;
            btn->button_state = BUTTON_PRESSED ;
            btn->button_pin.logic = temp_logic;
        }else{
             *btn_state = BUTTON_RELEASED ;
             btn->button_state = BUTTON_RELEASED ;
             btn->button_pin.logic = temp_logic;
        }
    }

    return ret;

}

/*
*   -Description-
*-this function initiate button the connected to external interrupt pin
*
*   -Input Output parameters -
*-1-it is pointer to call back function  (void (*func)(void))
*-2-it is pointer to button configuration  (button_INT_t *btn_INT)
*
*   -Return-
*   Std_ReturnType
*
*   -Return cases-
*-1- (E_NOK) if there is something wrong
*-2- (E_OK) otherwise
*/
Std_ReturnType button_with_INT( button_INT_t *btn_INT , void (*func)(void)){
	Std_ReturnType ret = E_OK;
	if((btn_INT == NULL)  || (func == NULL)){
		ret =E_NOT_OK;
	}
	else{
		
		if(btn_INT->pin_INT_config.pin_config.port == PORTD_INDEX){
			if(btn_INT->pin_INT_config.pin_config.pin == PIN_2){
				gpio_pin_direction_initialize(&(btn_INT->pin_INT_config.pin_config));
				gpio_set_callback_INT0_function(func);
				gpio_init_INT0(&btn_INT->pin_INT_config);
			}else if(btn_INT->pin_INT_config.pin_config.pin == PIN_3){
				gpio_pin_direction_initialize(&(btn_INT->pin_INT_config.pin_config));
				gpio_set_callback_INT1_function(func);
				gpio_init_INT1(&btn_INT->pin_INT_config);
			}else{
				ret =E_NOT_OK;
			}
			
		}else{
			ret =E_NOT_OK;
		}
		
		
	}

	return ret;

}

/*
*   -Description-
*-this function enable button interrupt functionality
*
*   -Input Output parameters -
*-1-it is pointer to button configuration  (button_INT_t *btn_INT)
*
*   -Return-
*   Std_ReturnType
*
*   -Return cases-
*-1- (E_NOK) if there is something wrong
*-2- (E_OK) otherwise
*/
Std_ReturnType button_enable_INT( button_INT_t *btn_INT){
	Std_ReturnType ret = E_OK;
	if(btn_INT == NULL){
		ret =E_NOT_OK;
	}
	else{
		if(btn_INT->pin_INT_config.pin_config.port == PORTD_INDEX){
			if(btn_INT->pin_INT_config.pin_config.pin == PIN_2){
				gpio_enable_INT0(&btn_INT->pin_INT_config);
				
			}
			else if(btn_INT->pin_INT_config.pin_config.pin == PIN_3){
				gpio_enable_INT1(&btn_INT->pin_INT_config);
				
			}
			else{
				ret =E_NOT_OK;
			}
			
			}else{
			ret =E_NOT_OK;
		}
		
	}
	return ret;
	
}


/*
*   -Description-
*-this function disable button interrupt functionality
*
*   -Input Output parameters -
*-1-it is pointer to button configuration  (button_INT_t *btn_INT)
*
*   -Return-
*   Std_ReturnType
*
*   -Return cases-
*-1- (E_NOK) if there is something wrong
*-2- (E_OK) otherwise
*/
Std_ReturnType button_disable_INT( button_INT_t *btn_INT){
	Std_ReturnType ret = E_OK;
	if(btn_INT == NULL){
		ret =E_NOT_OK;
	}
	else{
		if(btn_INT->pin_INT_config.pin_config.port == PORTD_INDEX){
			if(btn_INT->pin_INT_config.pin_config.pin == PIN_2){
					gpio_disable_INT0(&btn_INT->pin_INT_config);
				
				}
				else if(btn_INT->pin_INT_config.pin_config.pin == PIN_3){
					gpio_disable_INT1(&btn_INT->pin_INT_config);
				
				}
				else{
				ret =E_NOT_OK;
				}
			
			}else{
			ret =E_NOT_OK;
		}
		
	}
	return ret;
	
}

