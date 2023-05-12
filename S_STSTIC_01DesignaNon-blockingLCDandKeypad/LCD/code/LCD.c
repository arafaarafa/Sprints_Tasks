
#include "LCD.h"

static typedef enum{
    PINS_INITIALIZATION=0,
    CMD_58DM,
    CMD_511DM,
#if (LCD_COM_4_OR_8_BITS == LCD_COM_4_BITS)
    CMD_4bit_58DM,
#endif
    CMD_LCD_SETTING,
    CMD_CLEAR,
    CMD_CURSOR,
    CMD_ENTRYMODE,
    CMD_MAX

}lcd_init_state_t;
LCD_ReturnType lcd_init(lcd_config_t *lcd_config){
	
	LCD_ReturnType ret = E_OK;
	if(lcd_config == NULL ){
		ret =E_NOT_OK;
	}else{
		pin_config_t temp;
		static lcd_init_state_t lcd_init_state = PINS_INITIALIZATION;
        lcd_init_state_t prev_state = CMD_MAX+1;
        while((lcd_init_state != prev_state)&& (lcd_init_state<CMD_MAX)){
            prev_state = lcd_init_state;
            switch (lcd_init_state)
            {
             case PINS_INITIALIZATION:
                temp.direction= GPIO_DIRECTION_OUTPUT;
                temp.logic=	GPIO_LOW;
                
                temp.port = lcd_config->port_RS_index;
                temp.pin = lcd_config->pin_RS_index;
                gpio_pin_initialize(&temp);
                
                temp.port = lcd_config->port_RW_index;
                temp.pin = lcd_config->pin_RW_index;
                gpio_pin_initialize(&temp);
                
                
                temp.port = lcd_config->port_EN_index;
                temp.pin = lcd_config->pin_EN_index;
                gpio_pin_initialize(&temp);
                
                for(uint8_t index =0; index < LCD_COM_4_OR_8_BITS;	index++){
                    temp.port = lcd_config->lcd_pin_port[index].port_index;
                    temp.pin = lcd_config->lcd_pin_port[index].pin_index;
                    gpio_pin_initialize(&temp);
                }
                ret = COMPLETED;
                break;
            case CMD_58DM:
                ret = lcd_send_cmd(lcd_config, LCD_8BITS_2LINES_58DM); 
                break;

            case CMD_511DM:
                ret = lcd_send_cmd(lcd_config, LCD_8BITS_2LINES_511DM);
                break;
#if (LCD_COM_4_OR_8_BITS == LCD_COM_4_BITS)
            case CMD_4bit_58DM:                
                ret = lcd_send_cmd(lcd_config, LCD_4BITS_2LINES_58DM);
                break;
#endif
            case CMD_LCD_SETTING:
                ret = lcd_send_cmd(lcd_config, LCD_DISPLAY_ON_CUR_OFF_BLOCK_OFF);
                break;
            case CMD_CLEAR:
                ret = lcd_send_cmd(lcd_config, LCD_CMD_CLEAR);
                break;
            case CMD_CURSOR:
                ret = lcd_send_cmd(lcd_config, LCD_CMD_CURSOR_HOME);
                break;
            case CMD_ENTRYMODE:
                ret = lcd_send_cmd(lcd_config, LCD_CMD_ENTRY_MODE_INCREMENT_ON_SHIFT_OFF);
                break;
            default:
                break;
            }  
            if(ret == COMPLETED){
                lcd_init_state++;
            }  

        }
        if(lcd_init_state>= MAX_STATES){
            lcd_init_state = PINS_INITIALIZATION;
            return COMPLETED;
        }else{
            return IN_PROGRESS;
        }
		
		
	}
	return ret;
}


static typedef enum{
    PINS_SET_LOGIC=0,
#if (LCD_COM_4_OR_8_BITS == LCD_COM_4_BITS)
    MOST_4BITS,
    EN_4BITS,
#endif
    LAST_4BITS_OR_8BITS,
    EN_4BITS_OR_8BITS,
    SEND_CMD_CHAR_MAX_STATE,
    DELAY

}lcd_cmd_data_prog_state_t;

LCD_ReturnType lcd_send_char(lcd_config_t *lcd_config, uint8_t *data){
	Std_ReturnType ret = E_OK;
	if(lcd_config == NULL || data==NULL){
		ret =E_NOT_OK;
		}else{
		pin_config_t temp;
		static lcd_cmd_data_prog_state_t lcd_char_prog_state = PINS_SET_LOGIC, prog_befor_delay = PINS_SET_LOGIC;
        lcd_cmd_data_prog_state_t prev_state = SEND_CMD_MAX_STATE +2;
        timer_delay_t delay_state = TIMEOUT;
        while(((lcd_char_prog_state != prev_state)&& (lcd_char_prog_state<SEND_CMD_MAX_STATE))||(delay_state == TIMEOUT)){
            prev_state = lcd_char_prog_state;
            switch (lcd_char_prog_state)
            {
            case PINS_SET_LOGIC:
                temp.port = lcd_config->port_RS_index;
                temp.pin = lcd_config->pin_RS_index;
                gpio_pin_write_logic( &temp, LCD_DATA);
                
                temp.port = lcd_config->port_RW_index;
                temp.pin = lcd_config->pin_RW_index;
                gpio_pin_write_logic( &temp, LCD_WRITE);
                lcd_char_prog_state++;
                break;
#if (LCD_COM_4_OR_8_BITS == LCD_COM_4_BITS)
            case MOST_4BITS:
                for(uint8_t index = 0; index < LCD_COM_4_OR_8_BITS;	index++){
                temp.port = lcd_config->lcd_pin_port[index].port_index;
                temp.pin = lcd_config->lcd_pin_port[index].pin_index;
                gpio_pin_write_logic( &temp, (cmd>>(index+4)) & ((uint8_t)0x01) );
                }
                temp.port = lcd_config->port_EN_index;
                temp.pin = lcd_config->pin_EN_index;
                gpio_pin_write_logic( &temp, GPIO_HIGH);
                delay(5);
                prog_befor_delay = lcd_char_prog_state;
                lcd_char_prog_state=DELAY;
                break;
            case EN_4BITS:
                gpio_pin_write_logic( &temp, GPIO_LOW);
                delay(5);
                prog_befor_delay = lcd_char_prog_state;
                lcd_char_prog_state=DELAY;
                break;
#endif
            case LAST_4BITS_OR_8BITS:
                for(uint8_t index = 0; index < LCD_COM_4_OR_8_BITS;	index++){
                temp.port = lcd_config->lcd_pin_port[index].port_index;
                temp.pin = lcd_config->lcd_pin_port[index].pin_index;
                gpio_pin_write_logic( &temp, (cmd>>index) & ((uint8_t)0x01) );
                }
            
                temp.port = lcd_config->port_EN_index;
                temp.pin = lcd_config->pin_EN_index;
                gpio_pin_write_logic( &temp, GPIO_HIGH);
                delay(5);
                prog_befor_delay = lcd_char_prog_state;
                lcd_char_prog_state=DELAY;
                break;
            case EN_4BITS_OR_8BITS:
                gpio_pin_write_logic( &temp, GPIO_LOW);
                lcd_char_prog_state++;
                break;    
            case DELAY:
                delay_state = delay_checker();
                if( delay_state == TIMEOUT){
                    prog_befor_delay++;
                    lcd_char_prog_state = prog_befor_delay;
                }
                break;
            default:
                break;
            }

        }

        if(lcd_char_prog_state>= SEND_CMD_MAX_STATE){
            lcd_char_prog_state = PINS_SET_LOGIC;
            return COMPLETED;
        }else{
            return IN_PROGRESS;
        }	
		
		
	}
	return ret;
	
}



LCD_ReturnType lcd_send_cmd(lcd_config_t *lcd_config, uint8_t cmd){
	Std_ReturnType ret = E_OK;
	if(lcd_config == NULL || cmd==NULL){
		ret =E_NOT_OK;
		}else{
		pin_config_t temp;
		static lcd_cmd_data_prog_state_t lcd_cmd_prog_state = PINS_SET_LOGIC, prog_befor_delay = PINS_SET_LOGIC;
        lcd_cmd_data_prog_state_t prev_state = SEND_CMD_MAX_STATE +2;
        timer_delay_t delay_state = TIMEOUT;
        while(((lcd_cmd_prog_state != prev_state)&& (lcd_cmd_prog_state<SEND_CMD_MAX_STATE))|| (delay_state == TIMEOUT)){
            prev_state = lcd_cmd_prog_state;
            switch (lcd_cmd_prog_state)
            {
            case PINS_SET_LOGIC:
                temp.port = lcd_config->port_RS_index;
                temp.pin = lcd_config->pin_RS_index;
                gpio_pin_write_logic( &temp, LCD_COMMAND);
                
                temp.port = lcd_config->port_RW_index;
                temp.pin = lcd_config->pin_RW_index;
                gpio_pin_write_logic( &temp, LCD_WRITE);
                lcd_cmd_prog_state++;
                break;
#if (LCD_COM_4_OR_8_BITS == LCD_COM_4_BITS)
            case MOST_4BITS:
                for(uint8_t index = 0; index < LCD_COM_4_OR_8_BITS;	index++){
                temp.port = lcd_config->lcd_pin_port[index].port_index;
                temp.pin = lcd_config->lcd_pin_port[index].pin_index;
                gpio_pin_write_logic( &temp, (cmd>>(index+4)) & ((uint8_t)0x01) );
                }
                temp.port = lcd_config->port_EN_index;
                temp.pin = lcd_config->pin_EN_index;
                gpio_pin_write_logic( &temp, GPIO_HIGH);
                delay(5);
                prog_befor_delay = lcd_cmd_prog_state;
                lcd_cmd_prog_state=DELAY;
                break;
            case EN_4BITS:
                gpio_pin_write_logic( &temp, GPIO_LOW);
                delay(5);
                prog_befor_delay = lcd_cmd_prog_state;
                lcd_cmd_prog_state=DELAY;
                break;
#endif
            case LAST_4BITS_OR_8BITS:
                for(uint8_t index = 0; index < LCD_COM_4_OR_8_BITS;	index++){
                temp.port = lcd_config->lcd_pin_port[index].port_index;
                temp.pin = lcd_config->lcd_pin_port[index].pin_index;
                gpio_pin_write_logic( &temp, (cmd>>index) & ((uint8_t)0x01) );
                }
            
                temp.port = lcd_config->port_EN_index;
                temp.pin = lcd_config->pin_EN_index;
                gpio_pin_write_logic( &temp, GPIO_HIGH);
                delay(5);
                prog_befor_delay = lcd_cmd_prog_state;
                lcd_cmd_prog_state=DELAY;
                break;
            case EN_4BITS_OR_8BITS:
                temp.port = lcd_config->port_EN_index;
                temp.pin = lcd_config->pin_EN_index;
                gpio_pin_write_logic( &temp, GPIO_LOW);
                lcd_cmd_prog_state++;
                break;    
            case DELAY:
                delay_state = delay_checker();
                if( delay_state == TIMEOUT){
                    prog_befor_delay++;
                    lcd_cmd_prog_state = prog_befor_delay;
                }
                break;
            default:
                break;
            }

        }

        if(lcd_cmd_prog_state>= SEND_CMD_MAX_STATE){
            lcd_cmd_prog_state = PINS_SET_LOGIC;
            return COMPLETED;
        }else{
            return IN_PROGRESS;
        }	

	}
	return ret;
	
}

LCD_ReturnType lcd_set_curser(lcd_config_t *lcd_config, uint8_t col, uint8_t row){
	LCD_ReturnType ret = E_OK;
	if(lcd_config == NULL || col>LCD_MAX_COL|| row>LCD_MAX_ROW){
		ret =E_NOT_OK;
		}else{

			col--;
			switch(row){
				case 1:
					ret = lcd_send_cmd(lcd_config, LCD_DDRAM_START_ADD_LINE_1+col);
				break;
				case 2:
					ret = lcd_send_cmd(lcd_config, LCD_DDRAM_START_ADD_LINE_2+col);
				break;
				default:
					ret =E_NOT_OK;
				break;
			}
			
		}

	return ret;
}


static typedef enum{
    SET_POS=0,
    SEND_CUSTOM_CHAR,
}lcd_send_custom_char_state_t;

LCD_ReturnType lcd_send_custom_char(lcd_config_t *lcd_config,uint8_t *arr ,uint8_t *pos){
	LCD_ReturnType ret = E_OK;
	if(lcd_config == NULL || NULL == arr){
		ret =E_NOT_OK;
		}else{
            static uint8_t index=0;
            static lcd_send_custom_char_state_t lcd_send_custom_char_state = IN_PROGRESS;
            switch (lcd_send_custom_char_state)
            {
                
            case SET_POS:
                ret = lcd_send_cmd(lcd_config, LCD_CGRAM_START_ADD + (*pos)*8);
                if(ret == COMPLETED){
                  lcd_send_custom_char_state = SEND_CUSTOM_CHAR;  
                  
                }
                return IN_PROGRESS;
                break;
            case SEND_CUSTOM_CHAR:
                ret = lcd_send_char(lcd_config, index+arr);
                if((ret == COMPLETED)&&(index>=8)){
                    lcd_send_custom_char_state = SET_POS;
                    index=0;
                    return COMPLETED;
                }else if((ret == COMPLETED)&&(index<8)){
                    index++;
                    return IN_PROGRESS;
                }else{
                    return IN_PROGRESS;
                }
                break;
            default:
                break;
            }
		}
	return ret;	
}
