#include "UART.h"

static volatile uint16_t *rx_data= NULL;
static volatile uint16_t *tx_data = NULL;
static volatile uint8_t rx_flag_INt_used = 0;
static volatile uint8_t tx_flag_INt_used = 0;

Std_ReturnType uart_init(){
	
	Std_ReturnType ret = E_OK;

    UCSRC_ADD = (1<<UART_URSEL)|(UART_STOP_MODE<<UART_USBS)|(UART_MODE<<UART_UMSEL)
                |(UART_PARITY_MODE<<UART_UPM)| (UART_CLOCK_POLARITY<<UART_UCPOL)
                |((UART_CS_MODE&0x03)<<UART_UCSZ);

    UCSRA_ADD = (0xFC&UCSRA_ADD)|(UART_SPEED_MODE<< UART_U2X);
    UCSRB_ADD = (UART_RX_MODE<<UART_RXEN)
                |(UART_TX_MODE<<UART_TXEN)|((UART_CS_MODE>>3)<<UART_UCSZ2)
                |(0x03&UCSRB_ADD);
    UBRRL_ADD = (((F_CPU / (USART_BAUDRATE * 16UL))) - 1);
    UBRRH_ADD = (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)>>8;
    
    if(UART_RCIE_MODE == UART_RCIE_ENABLE ||    UART_TCIE_MODE == UART_TCIE_ENABLE || UART_URIE_MODE == UART_UDRIE_ENABLE){
        sei();
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

Std_ReturnType uart_write_INT(uint16 *data){
	
	Std_ReturnType ret = E_OK;
	if(data == NULL || UART_TCIE_MODE != UART_TCIE_ENABLE ){
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

Std_ReturnType uart_read_INT(uint16 *data){
	Std_ReturnType ret = E_OK;
	if(data == NULL || UART_RCIE_MODE != UART_RCIE_ENABLE ){
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