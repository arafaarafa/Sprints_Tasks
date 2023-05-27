

#include "APP.h"

led_t led_0_sending;
led_t led_1_receiving;

str_bcm_instance_t bcm_instance;

str_slave_protocol_selection_t slave_protocol_selection;
char data[BUFFER_MAX_SIZE]= "Confirm BCM Operating";
uint16_t data_length=22;

char packet_1[BUFFER_MAX_SIZE]=  "BCM Operating";
uint16_t packet_1_length=14;

char packet_2[BUFFER_MAX_SIZE];
uint16_t packet_2_length=0;



void app_init(void){
	/**************init LEDs**************/
	led_0_sending.led_status = LOW_LEVEL;
	led_0_sending.port_name = PORTA_INDEX;
	led_0_sending.pin = PIN_0;
	
	led_1_receiving.led_status = LOW_LEVEL;
	led_1_receiving.port_name = PORTA_INDEX;
	led_1_receiving.pin = PIN_1;
	/**************init LEDs**************/
	
	/**************protocol selection to transmit the data**************/
	slave_protocol_selection.enu_system_protocols = USART_PROTOCOL;
	/**************protocol selection to transmit the data**************/
	
	
	/**************init USART for BCM**************/
	bcm_instance.uart_state = INITIALIZED;
	bcm_instance.usart_instance.uart_clock_polarity = UART_NO_CLOCK;
	bcm_instance.usart_instance.uart_cs_mode = UART_CS_8;
	bcm_instance.usart_instance.uart_mode = UART_ASYNC_MODE;
	bcm_instance.usart_instance.uart_parity_mode = UART_PARITY_EVEN;
	bcm_instance.usart_instance.uart_rcie_mode = UART_RCIE_ENABLE;
	bcm_instance.usart_instance.uart_rx_mode = UART_RX_ENABLE;
	bcm_instance.usart_instance.uart_speed_mode = UART_NORMAL_MODE;
	bcm_instance.usart_instance.uart_stop_mode = UART_STOP_1_BIT;
	bcm_instance.usart_instance.uart_tcie_mode = UART_TCIE_ENABLE;
	bcm_instance.usart_instance.uart_tx_mode = UART_TX_ENABLE;
	bcm_instance.usart_instance.uart_urie_mode = UART_UDRIE_ENABLE;
	bcm_instance.usart_instance.usart_buadrate = 103;
	/**************init USART for BCM**************/
	
	
	
	led_intialize(&led_0_sending);
	led_intialize(&led_1_receiving);
	bcm_init(&bcm_instance);
	
}
void app_run(void){
	
	enu_transmit_or_receive_t transmit_or_receive = TRANSMIT;
	uint8_t compare_flag = 1;
	
	bcm_send_n(&slave_protocol_selection, packet_1, packet_1_length);
	
	while (1)
	{
		if(bcm_dispatcher(USART_PROTOCOL) == COMPLETED){
			
			if(transmit_or_receive == TRANSMIT){
				led_toggle(&led_0_sending);
				bcm_receive_n(&slave_protocol_selection, packet_2, &packet_2_length);
				transmit_or_receive = RECEIVE;
			}
			else{
				
				for(int i=0; i< data_length; i++){
					if(packet_2[i] != data[i]){
						compare_flag = 0;
						break;
					}
				}
				
				for(int i=0; i < BUFFER_MAX_SIZE; i++){
					packet_2[i] = '\0';
				}
				
				if(compare_flag == 1){
					led_toggle(&led_1_receiving);
				}
				bcm_send_n(&slave_protocol_selection, packet_1, packet_1_length);
				compare_flag=1;
				transmit_or_receive = TRANSMIT;
				
			}
			
		}
		
		
	}
	
}