include "LED.h"



/**
 *
 * @param led @ref led_t
 * @return Std_ReturnType the status of function
 *          (E_OK): the function done successfully
 *          (E_NOT_OK): the function didn't work correctely
 */
Std_ReturnType led_intialize(led_t * led){
    Std_ReturnType res = E_OK;

    if(led == NULL){
        res = E_NOT_OK;

    }else{
        pin_config_t temp = {.port = led->port_name, .pin = led->pin, .direction = GPIO_DIRECTION_OUTPUT , .logic = led->led_status };
        gpio_pin_direction_initialize(&temp);
        gpio_pin_write_logic( &temp, temp.logic);
    }
    return res;
}

/**
 *
 * @param led @ref led_t
 * @return Std_ReturnTypethe status of function
 *          (E_OK): the function done successfully
 *          (E_NOT_OK): the function didn't work correctely
 */
Std_ReturnType led_turn_on(led_t *led){
    Std_ReturnType res = E_OK;
    if(led == NULL){
        res = E_NOT_OK;

    }else{
        pin_config_t temp = {.port = led->port_name, .pin = led->pin, .direction = GPIO_DIRECTION_OUTPUT , .logic = LED_ON };
        led->led_status = LED_ON;
        gpio_pin_write_logic( &temp, temp.logic);
    }
    return res;
}


/**
 *
 * @param led @ref led_t
 * @return Std_ReturnType the status of function
 *          (E_OK): the function done successfully
 *          (E_NOT_OK): the function didn't work correctly
 */
Std_ReturnType led_turn_off(led_t *led){
    Std_ReturnType res = E_OK;
    if(led == NULL){
        res = E_NOT_OK;

    }else{
        pin_config_t temp = {.port = led->port_name, .pin = led->pin, .direction = GPIO_DIRECTION_OUTPUT , .logic = LED_OFF };
        led->led_status = LED_OFF;
        gpio_pin_write_logic( &temp, temp.logic);
    }
    return res;
}

/**
/**
 *
 * @param led @ref led_t
 * @return Std_ReturnType the status of function
 *          (E_OK): the function done successfully
 *          (E_NOT_OK): the function didn't work correctely
 */
Std_ReturnType led_toggle(led_t *led){
Std_ReturnType res = E_OK;
    if(led == NULL){
        res = E_NOT_OK;

    }else{
        pin_config_t temp = {.port = led->port_name, .pin = led->pin, .direction = GPIO_DIRECTION_OUTPUT , .logic = led->led_status };
        gpio_pin_toggle_logic( &temp);
        led->led_status = temp.logic;
    }
    return res;

}
