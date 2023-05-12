/*
 * UART.c
 *
 * Created: 4/22/2023 7:42:48 AM
 *  Author: Arafa
 */ 

#include "UART.h"

static volatile uint16 *rx_data= NULL;
static volatile uint16 *tx_data = NULL;
static volatile uint8_t rx_flag_INt_used = 0;
static volatile uint8_t tx_flag_INt_used = 0;


Std_ReturnType uart_init(uart_config_t *uart_config){
	
	Std_ReturnType ret = E_OK;
	if(uart_config == NULL){
		ret =E_NOT_OK;
	}
	else{
		UCSRC_ADD = (1<<UART_URSEL)|(uart_config->uart_stop_mode<<UART_USBS)|(uart_config->uart_mode<<UART_UMSEL)
					|(uart_config->uart_parity_mode<<UART_UPM)| (uart_config->uart_clock_polarity<<UART_UCPOL)
					|(uart_config->uart_cs_mode<<UART_UCSZ);
		UCSRA_ADD = (0xFC&UCSRA_ADD)|(uart_config->uart_speed_mode<< UART_U2X);
		UCSRB_ADD = (uart_config->uart_rx_mode<<UART_RXEN)
					|(uart_config->uart_tx_mode<<UART_TXEN)|((uart_config->uart_cs_mode>>3)<<UART_UCSZ2)
					|(0x03&UCSRB_ADD);
		UBRRL_ADD = (uint8_t)uart_config->usart_buadrate;
		UBRRH_ADD = (uint8_t)(uart_config->usart_buadrate>>8);
		
		if(uart_config->uart_rcie_mode == UART_RCIE_ENABLE || uart_config->uart_tcie_mode == UART_TCIE_ENABLE || uart_config->uart_urie_mode == UART_UDRIE_ENABLE){
			sei();
		}
		
	}
	return ret; 
}

Std_ReturnType uart_write(uint16 *data){
	
	Std_ReturnType ret = E_OK;
	if(data == NULL ){
		ret =E_NOT_OK;
	}
	else{
		while (tx_flag_INt_used == 1);
		while (! (UCSRA_ADD & (1<<UART_UDRE)));
		UDR_ADD = (uint8_t)*data;
		if(READ_BIT(UCSRB_ADD,UART_UCSZ2) == 1){
			UCSRB_ADD = (UCSRB_ADD&0xFE)| ((uint8_t)(*data>>8));
		}
	}
	return ret;
}

Std_ReturnType uart_read(uint16 *data){
	Std_ReturnType ret = E_OK;
	if(data == NULL ){
		ret =E_NOT_OK;
	}
	else{
		while (rx_flag_INt_used == 1);
		while ((UCSRA_ADD & (1 << UART_RC)) == 0);
		*data = UDR_ADD;
		if(READ_BIT(UCSRB_ADD,UART_UCSZ2) == 1){
			*data = ((UCSRB_ADD&0x02)<<7)|*data;
		}
	}
	return ret;
}


Std_ReturnType uart_write_INT(uart_config_t *uart_config, uint16 *data){
	
	Std_ReturnType ret = E_OK;
	if(data == NULL || uart_config->uart_tcie_mode != UART_TCIE_ENABLE ){
		ret =E_NOT_OK;
	}
	else{
		while (tx_flag_INt_used == 1);
		tx_flag_INt_used = 1;
		tx_data = data;
		SET_BIT(UCSRB_ADD,UART_UDRIE);
	}
	return ret;
}

Std_ReturnType uart_read_INT(uart_config_t *uart_config, uint16 *data){
	Std_ReturnType ret = E_OK;
	if(data == NULL || uart_config->uart_rcie_mode != UART_RCIE_ENABLE ){
		ret =E_NOT_OK;
	}
	else{
		while (rx_flag_INt_used == 1);
		rx_flag_INt_used = 1;
		rx_data = data;
		SET_BIT(UCSRB_ADD,UART_RCIE);
	}
	return ret;
}


ISR(USART_TXC_vect){

}
ISR(USART_RXC_vect){
	rx_flag_INt_used = 0;
	CLEAR_BIT(UCSRB_ADD,UART_RCIE);
	if(rx_data != NULL){
		*rx_data = UDR_ADD;
		if(READ_BIT(UCSRB_ADD,UART_UCSZ2) == 1){
			*rx_data = ((UCSRB_ADD&0x02)<<7)|*rx_data;
		}
	}
	 
	
}
ISR(USART_UDRE_vect){
	tx_flag_INt_used = 0;
	CLEAR_BIT(UCSRB_ADD,UART_UDRIE);
	if(rx_data != NULL){
		UDR_ADD = *tx_data ;
		if(READ_BIT(UCSRB_ADD,UART_UCSZ2) == 1){
			UCSRB_ADD = (UCSRB_ADD&0xFE)| ((uint8_t)(*rx_data>>8));
		}
	}
	
}