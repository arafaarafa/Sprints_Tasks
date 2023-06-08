#include "DIO.h"

static void (*callback_0)(void);
static void (*callback_1)(void);

static volatile uint8_t *DDRx_registers[] = {(uint8_t *)0x3A, (uint8_t *)0x37, (uint8_t *)0x34, (uint8_t *)0x31};
static volatile uint8_t *PORTx_registers[] = {(uint8_t *)0x3B, (uint8_t *)0x38, (uint8_t *)0x35, (uint8_t *)0x32};
static volatile uint8_t *PINx_registers[] = {(uint8_t *)0x39, (uint8_t *)0x36, (uint8_t *)0x33, (uint8_t *)0x30};


/**
 *
 * @param pin_config it is pointer to pin configuration @ref pin_config_t
 * @return status of function could be
 *          E_OK : the function done successfully
 *          E_NOT_OK : the function has issue to perform this action
 */
Std_ReturnType gpio_pin_direction_initialize(const pin_config_t *pin_config){
    Std_ReturnType ret = E_OK;
    if((pin_config == NULL) || (pin_config->pin >= PIN_MAX_NUMBER) || (pin_config->port >= PORT_MAX_NUMBER)){
        ret =E_NOT_OK;
    }
    else{
        if(pin_config->direction == GPIO_DIRECTION_OUTPUT){
        
			SET_BIT(HWREG8(DDRx_registers[pin_config->port]), pin_config->pin);
        }
        else if(pin_config->direction == GPIO_DIRECTION_INPUT){
			
            CLEAR_BIT(HWREG8(DDRx_registers[pin_config->port]), pin_config->pin);
        }
        else{
            ret =  E_NOT_OK;
        }
    }

    return ret;
}
/**
 *
 * @param pin_config it is pointer to pin configuration @ref pin_config_t
 * @param direction_status
 * @return status of function could be
 *          E_OK : the function done successfully
 *          E_NOT_OK : the function has issue to perform this action
 */
Std_ReturnType gpio_pin_get_direction_status( pin_config_t *pin_config, direction_t *direction_status){

    Std_ReturnType ret = E_OK;

    if((pin_config == NULL) || (direction_status == NULL)){
        ret =E_NOT_OK;
    }
    else{
        *direction_status = READ_BIT(HWREG8(DDRx_registers[pin_config->port]),pin_config->pin);
        pin_config->direction = *direction_status;
    }


    return ret;

}

/**
 *
 * @param pin_config it is pointer to pin configuration @ref pin_config_t
 * @param logic
 * @return status of function could be
 *          E_OK : the function done successfully
 *          E_NOT_OK : the function has issue to perform this action
 */
Std_ReturnType gpio_pin_write_logic( pin_config_t *pin_config, logic_t logic){

    Std_ReturnType ret = E_OK;

    if(pin_config == NULL){
        ret =E_NOT_OK;
    }
    else{
        switch(logic){
            case GPIO_HIGH:
                SET_BIT(HWREG8(PORTx_registers[pin_config->port]),pin_config->pin);
                pin_config->logic = GPIO_HIGH;
                break;
            case GPIO_LOW:
                CLEAR_BIT(HWREG8(PORTx_registers[pin_config->port]),pin_config->pin);
                pin_config->logic = GPIO_LOW;
                break;
            default:
                ret = E_NOT_OK;
		        break;

        }
    }
    return ret;

}


/**
 *
 * @param pin_config it is pointer to pin configuration @ref pin_config_t
 * @param logic
 * @return status of function could be
 *          E_OK : the function done successfully
 *          E_NOT_OK : the function has issue to perform this action
 */
Std_ReturnType gpio_pin_read_logic( pin_config_t *pin_config, logic_t *logic){

    Std_ReturnType ret = E_OK;

    if((pin_config == NULL) || (logic == NULL)){
        ret =E_NOT_OK;
    }
    else{
        *logic = READ_BIT(HWREG8(PINx_registers[pin_config->port]),pin_config->pin);
        pin_config->logic = *logic;
    }
    return ret;

}



/**
 *
 * @param pin_config it is pointer to pin configuration @ref pin_config_t
 * @return status of function could be
 *          E_OK : the function done successfully
 *          E_NOT_OK : the function has issue to perform this action
 */
Std_ReturnType gpio_pin_toggle_logic( pin_config_t *pin_config){

    Std_ReturnType ret = E_OK;

    if(pin_config == NULL){
        ret =E_NOT_OK;
    }
    else{
        TOGGLE_BIT(HWREG8(PORTx_registers[pin_config->port]), pin_config->pin);
        pin_config->logic = ~pin_config->logic;
    }
    return ret;

}


/**
 *
 * @param pin_config it is pointer to pin configuration @ref pin_config_t
 * @return status of function could be
 *          E_OK : the function done successfully
 *          E_NOT_OK : the function has issue to perform this action
 *
 */
Std_ReturnType gpio_pin_initialize( pin_config_t* pin_config){
    Std_ReturnType ret = E_OK;

    if(pin_config == NULL){
        ret =E_NOT_OK;
    }
    else{
        ret=gpio_pin_direction_initialize(pin_config);
        ret=gpio_pin_write_logic(pin_config,pin_config->logic);
    }
    return ret;
}


/**
 *
 * @param port
 * @param direction
 * @return status of function could be
 *          E_OK : the function done successfully
 *          E_NOT_OK : the function has issue to perform this action
 */
Std_ReturnType gpio_port_direction_initialize(port_index_t port, uint8_t direction){

    Std_ReturnType ret = E_OK;
    if(port >= PORT_MAX_NUMBER){
        ret =E_NOT_OK;
    }
    else{
        HWREG8(DDRx_registers[port]) = direction;
    }
    return ret;



}



/**
 *
 * @param port
 * @param direction_status
 * @return status of function could be
 *          E_OK : the function done successfully
 *          E_NOT_OK : the function has issue to perform this action
 */
Std_ReturnType gpio_port_get_direction_status(port_index_t port, uint8_t *direction_status){

    Std_ReturnType ret = E_OK;

    if((direction_status == NULL) || (port >= PORT_MAX_NUMBER)){
        ret =E_NOT_OK;
    }
    else{
        *direction_status = HWREG8(DDRx_registers[port]) ;
    }
    return ret;

}



/**
 *
 * @param port
 * @param logic
 * @return status of function could be
 *          E_OK : the function done successfully
 *          E_NOT_OK : the function has issue to perform this action
 */
Std_ReturnType gpio_port_write_logic(port_index_t port, uint8_t logic){

    Std_ReturnType ret = E_OK;

    if(port >= PORT_MAX_NUMBER){
        ret = E_NOT_OK;
    }
    else{
        HWREG8(PORTx_registers[port]) = logic;
    }

    return ret;

}



/**
 *
 * @param port
 * @param logic
 * @return status of function could be
 *          E_OK : the function done successfully
 *          E_NOT_OK : the function has issue to perform this action
 */
Std_ReturnType gpio_port_read_logic(port_index_t port, uint8_t *logic){

    Std_ReturnType ret = E_OK;

    if((logic == NULL) || (port >= PORT_MAX_NUMBER)){
        ret =E_NOT_OK;
    }
    else{
        *logic = HWREG8(PORTx_registers[port]) ;
    }
    return ret;

}



/**
 *
 * @param port
 * @return status of function could be
 *          E_OK : the function done successfully
 *          E_NOT_OK : the function has issue to perform this action
 */
Std_ReturnType gpio_port_toggle_logic(port_index_t port){

    Std_ReturnType ret = E_OK;
    if(port >= PORT_MAX_NUMBER){
        ret =E_NOT_OK;
    }
    else{
         HWREG8(PORTx_registers[port]) ^= 0xFF;
    }

    return ret;

}







Std_ReturnType gpio_port_low_nibble_direction_initialize(pin_config_t *pin_config, uint8_t data){
    Std_ReturnType ret = E_OK;
    if(pin_config == NULL){
        ret =E_NOT_OK;
    }
    else{
        SET_LOW_NIBBLE_BITS(HWREG8(DDRx_registers[pin_config->port]), data);
    }
    return ret;

}
Std_ReturnType gpio_port_low_nibble_write_logic(pin_config_t *pin_config, uint8_t data){
    Std_ReturnType ret = E_OK;
    if(pin_config == NULL){
        ret =E_NOT_OK;
    }
    else{
        SET_LOW_NIBBLE_BITS(HWREG8(PORTx_registers[pin_config->port]), data);
    }
    return ret;
}
Std_ReturnType gpio_port_high_nibble_direction_initialize(pin_config_t *pin_config, uint8_t data){
    Std_ReturnType ret = E_OK;
    if(pin_config == NULL){
        ret =E_NOT_OK;
    }
    else{
        SET_HIGH_NIBBLE_BITS(HWREG8(DDRx_registers[pin_config->port]), data);
    }
    return ret;

}
Std_ReturnType gpio_port_high_nibble_write_logic(pin_config_t *pin_config, uint8_t data){
    Std_ReturnType ret = E_OK;
    if(pin_config == NULL){
        ret =E_NOT_OK;
    }
    else{
        SET_HIGH_NIBBLE_BITS(HWREG8(PORTx_registers[pin_config->port]), data);
    }
    return ret;

}


/*
*   -Description-
*-this function init external interrupt 0
*
*   -Input Output parameters -
*-1-it is pointer to pin configuration that has external interrupt functionality   (pin_INT_config_t *pin_INT_config)
*
*   -Return-
*   Std_ReturnType
*
*   -Return cases-
*-1- (E_NOK) if there is something wrong
*-2- (E_OK) otherwise
*/

Std_ReturnType gpio_init_INT0(const pin_INT_config_t *pin_INT_config){
	Std_ReturnType ret = E_OK;
	if(pin_INT_config == NULL){
		ret =E_NOT_OK;
	}
	else{
		
		if((pin_INT_config->pin_config.port == PORTD_INDEX) && (pin_INT_config->pin_config.pin == PIN_2)){
			//GICR_ADD |= (1<<INT0_Globle);						MCUCR_ADD |= pin_INT_config->INT_mode;						SREG_ADD |= (1<<Globle_INT);
			
		}else{
			ret =E_NOT_OK;
			
		}
								

	}
	return ret;
	
}


/*
*   -Description-
*-this function init external interrupt 1
*
*   -Input Output parameters -
*-1-it is pointer to pin configuration that has external interrupt functionality   (pin_INT_config_t *pin_INT_config)
*
*   -Return-
*   Std_ReturnType
*
*   -Return cases-
*-1- (E_NOK) if there is something wrong
*-2- (E_OK) otherwise
*/
Std_ReturnType gpio_init_INT1(const pin_INT_config_t *pin_INT_config){
	Std_ReturnType ret = E_OK;
	if(pin_INT_config == NULL){
		ret =E_NOT_OK;
	}
	else{
		
		if((pin_INT_config->pin_config.port == PORTD_INDEX) && (pin_INT_config->pin_config.pin == PIN_3)){
			GICR_ADD |= (1<<INT1_Globle);						MCUCR_ADD |= (pin_INT_config->INT_mode<<2);						SREG_ADD |= (1<<Globle_INT);
			
		}else{
			ret =E_NOT_OK;
		}
						

	}
	return ret;
	
}

/*
*   -Description-
*-this function enable external interrupt 0
*
*   -Input Output parameters -
*-1-it is pointer to pin configuration that has external interrupt functionality   (pin_INT_config_t *pin_INT_config)
*
*   -Return-
*   Std_ReturnType
*
*   -Return cases-
*-1- (E_NOK) if there is something wrong
*-2- (E_OK) otherwise
*/
Std_ReturnType gpio_enable_INT0(const pin_INT_config_t *pin_INT_config){
	Std_ReturnType ret = E_OK;
	if(pin_INT_config == NULL){
		ret =E_NOT_OK;
	}
	else{
		
		if((pin_INT_config->pin_config.port == PORTD_INDEX) && (pin_INT_config->pin_config.pin == PIN_2)){
			GICR_ADD |= (1<<INT0_Globle);
			MCUCR_ADD |= pin_INT_config->INT_mode;
			
			}else{
			ret =E_NOT_OK;
			
		}
						

	}
	return ret;
}
/*
*   -Description-
*-this function enable external interrupt 1
*
*   -Input Output parameters -
*-1-it is pointer to pin configuration that has external interrupt functionality   (pin_INT_config_t *pin_INT_config)
*
*   -Return-
*   Std_ReturnType
*
*   -Return cases-
*-1- (E_NOK) if there is something wrong
*-2- (E_OK) otherwise
*/
Std_ReturnType gpio_enable_INT1(const pin_INT_config_t *pin_INT_config){
	Std_ReturnType ret = E_OK;
	if(pin_INT_config == NULL){
		ret =E_NOT_OK;
	}
	else{
		
		if((pin_INT_config->pin_config.port == PORTD_INDEX) && (pin_INT_config->pin_config.pin == PIN_3)){
			GICR_ADD |= (1<<INT1_Globle);						MCUCR_ADD |= (pin_INT_config->INT_mode<<INT1_MODE_INDEX);
			
			}else{
			ret =E_NOT_OK;
		}
						

	}
	return ret;
	
}

/*
*   -Description-
*-this function disable external interrupt 0
*
*   -Input Output parameters -
*-1-it is pointer to pin configuration that has external interrupt functionality   (pin_INT_config_t *pin_INT_config)
*
*   -Return-
*   Std_ReturnType
*
*   -Return cases-
*-1- (E_NOK) if there is something wrong
*-2- (E_OK) otherwise
*/

Std_ReturnType gpio_disable_INT0(const pin_INT_config_t *pin_INT_config){
	Std_ReturnType ret = E_OK;
	if(pin_INT_config == NULL){
		ret =E_NOT_OK;
	}
	else{
		
		if((pin_INT_config->pin_config.port == PORTD_INDEX) && (pin_INT_config->pin_config.pin == PIN_2)){
			GICR_ADD &= ~(1<<INT0_Globle);
			}else{
			ret =E_NOT_OK;
			
		}
						

	}
	return ret;
	
}
/*
*   -Description-
*-this function disable external interrupt 1
*
*   -Input Output parameters -
*-1-it is pointer to pin configuration that has external interrupt functionality   (pin_INT_config_t *pin_INT_config)
*
*   -Return-
*   Std_ReturnType
*
*   -Return cases-
*-1- (E_NOK) if there is something wrong
*-2- (E_OK) otherwise
*/
Std_ReturnType gpio_disable_INT1(const pin_INT_config_t *pin_INT_config){
	Std_ReturnType ret = E_OK;
	if(pin_INT_config == NULL){
		ret =E_NOT_OK;
	}
	else{
		
		if((pin_INT_config->pin_config.port == PORTD_INDEX) && (pin_INT_config->pin_config.pin == PIN_3)){
			GICR_ADD &= ~(1<<INT1_Globle);
			}else{
			ret =E_NOT_OK;
			
		}
						

	}
	return ret;
	
}

/*
*   -Description-
*-this function set callback function to external interrupt 0
*
*   -Input Output parameters -
*-1-it is pointer to call back function  (void (*func)(void))
*
*   -Return-
*   Std_ReturnType
*
*   -Return cases-
*-1- (E_NOK) if there is something wrong
*-2- (E_OK) otherwise
*/
Std_ReturnType gpio_set_callback_INT0_function(void (*func)(void)){
	Std_ReturnType ret = E_OK;
	if(func == NULL){
		ret = E_NOT_OK;
	}
	else{
		callback_0 = func;
	}
	
	return ret;
}

/*
*   -Description-
*-this function set callback function to external interrupt 1
*
*   -Input Output parameters -
*-1-it is pointer to call back function  (void (*func)(void))
*
*   -Return-
*   Std_ReturnType
*
*   -Return cases-
*-1- (E_NOK) if there is something wrong
*-2- (E_OK) otherwise
*/
Std_ReturnType gpio_set_callback_INT1_function(void (*func)(void)){
	Std_ReturnType ret = E_OK;
	if(func == NULL){
		ret = E_NOT_OK;
	}
	else{
		callback_1 = func;
	}
	
	return ret;
}

/*
*   -Description-
*-interrupt service routine for  external interrupt 0
*
*/
ISR(INT0_vect){
	
	(*callback_0)();
	
	
}

/*
*   -Description-
*-interrupt service routine for  external interrupt 1
*
*/

ISR(INT1_vect){
	
	(*callback_1)();
	
	
}