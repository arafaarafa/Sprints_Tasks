#include "keypad.h"


/*global variables*/

char values[KEYPAD_MAX_ROWS_NO][KEYPAD_MAX_COLS_NO];

/*global variables*/


KEYPAD_ReturnType keypad_initialize(const keypad_config_t *keypad_config){
    KEYPAD_ReturnType ret = COMPLETED;
    
    if(keypad_config == NULL){
        ret =E_NOT_OK;
    }
    else{
        pin_config_t temp;
        temp.direction = GPIO_DIRECTION_OUTPUT;
        for(uint8 counter =0; counter < KEYPAD_MAX_ROWS_NO ; counter++){
            temp.port = keypad_config->keypad_rows[counter].keypad_pin_port;
            temp.pin = keypad_config->keypad_rows[counter].keypad_pin;
            gpio_pin_direction_initialize(&temp);
        }
        temp.direction = GPIO_DIRECTION_INPUT;
        for(uint8 counter =0; counter < KEYPAD_MAX_COLS_NO ; counter++){
            temp.port = keypad_config->keypad_cols[counter].keypad_pin_port;
            temp.pin = keypad_config->keypad_cols[counter].keypad_pin;
            gpio_pin_direction_initialize(&temp);
        }
    
        
    
    }
    return ret 
}
KEYPAD_ReturnType keypad_get_value(const keypad_config_t *keypad_config, char *value){
    KEYPAD_ReturnType ret = E_OK;
    
    if(keypad_config == NULL || value == NULL){
        ret =E_NOT_OK;
    }
    else{
        pin_config_t temp_row,temp_col;
        logic_t btn_state;
        for(uint8 counter_row =0; counter_row < KEYPAD_MAX_ROWS_NO ; counter_row++){
            temp_row.port = keypad_config->keypad_rows[counter_row].keypad_pin_port;
            temp_row.pin = keypad_config->keypad_rows[counter_row].keypad_pin;
            gpio_pin_write_logic( &temp_row, GPIO_HIGH);
            
            for(uint8 counter_col =0; counter_col < KEYPAD_MAX_COLS_NO ; counter_col++){
            temp_col.port = keypad_config->keypad_cols[counter_col].keypad_pin_port;
            temp_col.pin = keypad_config->keypad_cols[counter_col].keypad_pin;
            gpio_pin_read_logic(&temp_col, &btn_state);
            if(btn_state == GPIO_HIGH){
                *value = values[counter_row][counter_col];
                gpio_pin_write_logic( &temp_row, GPIO_LOW);
                return COMPLETED;
                }
            }
            
            gpio_pin_write_logic( &temp_row, GPIO_LOW);
        } 
        ret = COMPLETED;
    }
    return ret;
}