/*
 * UART.c
 *
 * Created: 4/22/2023 7:42:48 AM
 *  Author: Arafa
 */ 

#include "UART.h"

void(*send_callback)(void) = NULL;
void(*receive_callback)(void) = NULL;
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
Std_ReturnType uart_deinit(){
	Std_ReturnType ret = E_OK;
	UCSRC_ADD = 0x80;
	UCSRA_ADD = 0;
	UCSRB_ADD = 0;
	UBRRL_ADD = 0;
	UBRRH_ADD = 0;
	return ret;
}
Std_ReturnType uart_write(uint16_t *data){
	
	Std_ReturnType ret = E_OK;
	if(data == NULL ){
		ret =E_NOT_OK;
	}
	else{
		while (! (UCSRA_ADD & (1<<UART_UDRE)));
		UDR_ADD = (uint8_t)*data;
		
	}
	return ret;
}

Std_ReturnType uart_read(uint16_t *data){
	Std_ReturnType ret = E_OK;
	if(data == NULL ){
		ret =E_NOT_OK;
	}
	else{
		while ((UCSRA_ADD & (1 << UART_RC)) == 0);
		*data = UDR_ADD;
		
	}
	return ret;
}


Std_ReturnType uart_write_INT(void(*callback)(void)){
	
	Std_ReturnType ret = E_OK;
	if( callback == NULL ){
		ret =E_NOT_OK;
	}
	else{
		send_callback = callback;
		
	}
	return ret;
}

Std_ReturnType uart_read_INT(void(*callback)(void)){
	Std_ReturnType ret = E_OK;
	if( callback == NULL ){
		ret =E_NOT_OK;
	}
	else{
		receive_callback = callback;
		uart_enable_RCIE();
	}
	return ret;
}
Std_ReturnType uart_enable_UDRIE(void){
	Std_ReturnType ret = E_OK;
	SET_BIT(UCSRB_ADD,UART_UDRIE);
	return ret;
}
Std_ReturnType uart_disable_UDRIE(void){
	Std_ReturnType ret = E_OK;
	CLEAR_BIT(UCSRB_ADD,UART_UDRIE);
	return ret;
}
Std_ReturnType uart_enable_RCIE(void){
	Std_ReturnType ret = E_OK;
	SET_BIT(UCSRB_ADD,UART_RCIE);
	return ret;
}
Std_ReturnType uart_disable_RCIE(void){
	Std_ReturnType ret = E_OK;
	CLEAR_BIT(UCSRB_ADD,UART_RCIE);
	return ret;
}
ISR(USART_TXC){

}
ISR(USART_RXC){
	
	 (*receive_callback)();
	
}
ISR(USART_UDRE){
	
	(*send_callback)();
	
}