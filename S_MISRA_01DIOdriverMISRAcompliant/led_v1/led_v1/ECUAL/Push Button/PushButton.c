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
    if(btn == NULL  || btn_state == NULL){
        ret =E_NOT_OK;
    }
    else{
        logic_t temp_logic;
        gpio_pin_read_logic( &(btn->button_pin), &temp_logic);
        if(btn->button_active == temp_logic){
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

