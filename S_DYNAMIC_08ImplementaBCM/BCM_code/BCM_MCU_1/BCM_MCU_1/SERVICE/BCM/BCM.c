/*
 * BCM.c
 *
 * Created: 5/23/2023 8:12:33 PM
 *  Author: Arafa
 */ 
#include "BCM.h"
static str_data_and_slave_instance_t str_data_slave_refrence[MAX_PROTOCOL_COUNTER];
static str_data_instance_t str_data_receive_refrence[MAX_PROTOCOL_COUNTER];
static enu_data_on_bus_state_t data_over_usart_state = SENT;
/*
static enu_data_on_bus_state_t data_over_spi_state = SENT;
static enu_data_on_bus_state_t data_over_i2c_state = SENT;
*/

 static void uart_send_callback(void){
    static uint32_t data_counter =0;
    uint8_t temp;
    data_counter++;
    if(data_counter == 1){
        temp = (str_data_slave_refrence[USART_PROTOCOL].data_length>>(data_counter*8));
        uart_write(&temp);   
    }
    else if(data_counter<str_data_slave_refrence[USART_PROTOCOL].data_length){
        temp = *(str_data_slave_refrence[USART_PROTOCOL].ptr_data+data_counter-MAX_NUMBER_OF_BYTES_FOR_LENGTH);
        uart_write(&temp);   
    }else{
		uart_disable_UDRIE();
        data_counter = 0;
        data_over_usart_state = SENT;
		
    }
    
}

 static void uart_receive_callback(void){
	 static uint32_t data_counter =0;
	 uint8_t temp;
	 
	 if(data_counter < MAX_NUMBER_OF_BYTES_FOR_LENGTH){
		 uart_read(&temp);
		 *(str_data_receive_refrence[USART_PROTOCOL].data_length) |= (((uint16_t)temp)<<(data_counter*8));
		 data_counter++;
	 }
	 else if((data_counter-MAX_NUMBER_OF_BYTES_FOR_LENGTH) < *(str_data_receive_refrence[USART_PROTOCOL].data_length)){
		 uart_read(&temp);
		 (str_data_receive_refrence[USART_PROTOCOL].ptr_data)[data_counter-MAX_NUMBER_OF_BYTES_FOR_LENGTH] = temp;
		 data_counter++;
		 if(data_counter >= *(str_data_receive_refrence[USART_PROTOCOL].data_length)){
			 uart_disable_RCIE();
			 data_counter =0;
			 data_over_usart_state = RECEIVED;
			 *(str_data_receive_refrence[USART_PROTOCOL].data_length) -= MAX_NUMBER_OF_BYTES_FOR_LENGTH;
		 }
	 }
	 
 }

/*static void spi_send_callback(void){
    static uint32_t data_counter =0;
    data_counter++;
    if(data_counter<str_data_slave_refrence[SPI_PROTOCOL].data_length){
      spi_send(str_data_slave_refrence[SPI_PROTOCOL].slave_id,
                str_data_slave_refrence[SPI_PROTOCOL].ptr_data+data_counter<str_data_slave_refrence[USART_PROTOCOL].data_length);   
    }else{
        data_counter =0;
        data_over_spi_state = SENT;
    }
    
 }*/
/*static void i2c_send_callback(void){
    static uint32_t data_counter =0;
    data_counter++;
    if(data_counter<str_data_slave_refrence[SPI_PROTOCOL].data_length){
      i2c_send(str_data_slave_refrence[I2C_PROTOCOL].slave_id,
                str_data_slave_refrence[I2C_PROTOCOL].ptr_data+data_counter<str_data_slave_refrence[USART_PROTOCOL].data_length);   
    }else{
        data_counter =0;
        data_over_i2c_state = SENT;
    }
    
}*/



enu_system_status_t bcm_init(str_bcm_instance_t* ptr_str_bcm_instance){
	enu_system_status_t ret_state = BCM_OK;
	if(ptr_str_bcm_instance == NULL){
		ret_state = BCM_NOT_OK;
	}else{
		if(ptr_str_bcm_instance->uart_state == INITIALIZED){
			uart_init(&(ptr_str_bcm_instance->usart_instance));
		}
		/*
		if(ptr_str_bcm_instance->spi_state == INITIALIZED){
			
		}
		if(ptr_str_bcm_instance->i2c_state == INITIALIZED){
			
		}
		*/
	}	
	return ret_state;
}
enu_system_status_t bcm_deinit(str_bcm_instance_t* ptr_str_bcm_instance){
	enu_system_status_t ret_state = BCM_OK;
	if(ptr_str_bcm_instance->uart_state == NOT_REQUIRED){
			uart_deinit();
		}
		/*
		if(ptr_str_bcm_instance->spi_state == NOT_REQUIRED){
			
		}
		if(ptr_str_bcm_instance->i2c_state == NOT_REQUIRED){
			
		}
		*/
	return ret_state;
}

enu_system_status_t bcm_send(str_slave_protocol_selection_t *ptr_str_slave_protocol_selection, uint8_t *data){
    enu_system_status_t ret_state = BCM_OK;

    switch (ptr_str_slave_protocol_selection->enu_system_protocols)
    {
    case USART_PROTOCOL:
        if(data_over_usart_state == RECEIVED){
	        data_over_usart_state = SENT;
	        }else{
	        ret_state = IN_PROGRESS;
        }
        if(data_over_usart_state == SENT){
	        data_over_usart_state = NOT_SENT;
	        str_data_slave_refrence[ptr_str_slave_protocol_selection->enu_system_protocols].ptr_data= data;
		
	        str_data_slave_refrence[ptr_str_slave_protocol_selection->enu_system_protocols].data_length = MAX_NUMBER_OF_BYTES_FOR_LENGTH + MIN_NUMBER_OF_BYTES_FOR_data;
	        uint8_t temp = MAX_NUMBER_OF_BYTES_FOR_LENGTH + MIN_NUMBER_OF_BYTES_FOR_data;
	        uart_write_INT(uart_send_callback);
	        uart_write(&temp);
	        uart_enable_UDRIE();

        }
        else{
	        
	        ret_state = IN_PROGRESS;
        }
        
        break;
    /*case SPI_PROTOCOL:
        if(data_over_spi_state == NOT_SENT){
            data_over_spi_state = NOT_SENT;
            str_data_slave_refrence[ptr_str_slave_protocol_selection->enu_system_protocols].ptr_data= data;
            str_data_slave_refrence[ptr_str_slave_protocol_selection->enu_system_protocols].data_length = 1;
            str_data_slave_refrence[ptr_str_slave_protocol_selection->enu_system_protocols].slave_id = ptr_str_slave_protocol_selection->slave_id;
            spi_send(ptr_str_slave_protocol_selection->slave_id, data);

        }
        else{
           
           ret_state = IN_PROGRESS;
        }
        break;*/
    /*case I2C_PROTOCOL:
        if(data_over_i2c_state == NOT_SENT){
            data_over_i2c_state = NOT_SENT;
            str_data_slave_refrence[ptr_str_slave_protocol_selection->enu_system_protocols].ptr_data= data;
            str_data_slave_refrence[ptr_str_slave_protocol_selection->enu_system_protocols].data_length = 1;
            str_data_slave_refrence[ptr_str_slave_protocol_selection->enu_system_protocols].slave_id = ptr_str_slave_protocol_selection->slave_id;
            i2c_send(ptr_str_slave_protocol_selection->slave_id, data);

        }
        else{
           
           ret_state = IN_PROGRESS;
        }
        break;*/
    default:
        ret_state = BCM_NOT_OK;
        break;
    }
    return ret_state;
}

enu_system_status_t bcm_send_n(str_slave_protocol_selection_t *ptr_str_slave_protocol_selection, uint8_t *data, uint16_t length){
    enu_system_status_t ret_state = BCM_OK;

    switch (ptr_str_slave_protocol_selection->enu_system_protocols)
    {
    case USART_PROTOCOL:
		if(data_over_usart_state == RECEIVED){
			data_over_usart_state = SENT;
			}else{
			ret_state = IN_PROGRESS;
		}
        if(data_over_usart_state == SENT){
            data_over_usart_state = NOT_SENT;
            str_data_slave_refrence[ptr_str_slave_protocol_selection->enu_system_protocols].ptr_data= data;
            str_data_slave_refrence[ptr_str_slave_protocol_selection->enu_system_protocols].data_length = length+MAX_NUMBER_OF_BYTES_FOR_LENGTH;
            uint8_t temp = length+MAX_NUMBER_OF_BYTES_FOR_LENGTH;
			uart_write_INT(uart_send_callback);
            uart_write(&temp);
			uart_enable_UDRIE();

        }
        else{
           
           ret_state = IN_PROGRESS;
        }
        
        break;
    /*case SPI_PROTOCOL:
        if(data_over_spi_state == NOT_SENT){
            data_over_spi_state = NOT_SENT;
            str_data_slave_refrence[ptr_str_slave_protocol_selection->enu_system_protocols].ptr_data= data;
            str_data_slave_refrence[ptr_str_slave_protocol_selection->enu_system_protocols].data_length = length;
            str_data_slave_refrence[ptr_str_slave_protocol_selection->enu_system_protocols].slave_id = ptr_str_slave_protocol_selection->slave_id;
            spi_send(ptr_str_slave_protocol_selection->slave_id, length);

        }
        else{
           
           ret_state = IN_PROGRESS;
        }
        break;
    */
    /*case I2C_PROTOCOL:
        if(data_over_i2c_state == NOT_SENT){
            data_over_i2c_state = NOT_SENT;
            str_data_slave_refrence[ptr_str_slave_protocol_selection->enu_system_protocols].ptr_data= data;
            str_data_slave_refrence[ptr_str_slave_protocol_selection->enu_system_protocols].data_length = length;
            str_data_slave_refrence[ptr_str_slave_protocol_selection->enu_system_protocols].slave_id = ptr_str_slave_protocol_selection->slave_id;
            i2c_send(ptr_str_slave_protocol_selection->slave_id, length);

        }
        else{
           
           ret_state = IN_PROGRESS;
        }
        break;
    */
    default:
        ret_state = BCM_NOT_OK;
        break;
    }
    return ret_state;

}




enu_system_status_t bcm_dispatcher(enu_system_protocols_t enu_com_protocol){

    enu_system_status_t ret_state = IN_PROGRESS;
    switch (enu_com_protocol)
    {
    case USART_PROTOCOL:
        if(data_over_usart_state == SENT || data_over_usart_state == NOT_SENT){
            ret_state = (data_over_usart_state == SENT)? COMPLETED : IN_PROGRESS;
        }else{
            ret_state = (data_over_usart_state == RECEIVED)? COMPLETED : IN_PROGRESS;
        }
        

        break;
    /*case SPI_PROTOCOL:
        ret_state = (data_over_spi_state == SENT)? COMPLETED : IN_PROGRESS;
        break;*/
    /*case I2C_PROTOCOL:
        ret_state = (data_over_i2c_state == SENT)? COMPLETED : IN_PROGRESS;
        break;*/
    default:
        ret_state = BCM_NOT_OK;
        break;
    }
    return ret_state;
}

enu_system_status_t bcm_receive_n(str_slave_protocol_selection_t *ptr_str_slave_protocol_selection, uint8_t *data , uint16_t *length){
    enu_system_status_t ret_state = BCM_OK;

    switch (ptr_str_slave_protocol_selection->enu_system_protocols)
    {
    case USART_PROTOCOL:
		if(data_over_usart_state == SENT){
			data_over_usart_state = RECEIVED;
		}else{
			ret_state = IN_PROGRESS;
		}
        if(data_over_usart_state == RECEIVED){
            data_over_usart_state = NOT_RECEIVED;
            str_data_receive_refrence[ptr_str_slave_protocol_selection->enu_system_protocols].ptr_data= data;
            *length = 0;
            str_data_receive_refrence[ptr_str_slave_protocol_selection->enu_system_protocols].data_length = length;
            uart_read_INT(uart_receive_callback);

        }
        else{
           
           ret_state = IN_PROGRESS;
        }
        
        break;
    /*case SPI_PROTOCOL:
        
        break;
    */
    /*case I2C_PROTOCOL:
        
        break;
    */
    default:
        ret_state = BCM_NOT_OK;
        break;
    }
    return ret_state;
}
