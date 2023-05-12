

#ifndef UART_CONFIG_H_
#define UART_CONFIG_H_

/**RX completed interrupt**/
#define UART_RCIE_DISABLE                       0   //disable interrupt
#define UART_RCIE_ENABLE                        1   //enable interrupt
#define UART_RCIE_MODE                          UART_RCIE_DISABLE

/**TX completed interrupt**/
#define UART_TCIE_DISABLE                       0   //disable interrupt
#define UART_TCIE_ENABLE                        1   //enable interrupt
#define UART_TCIE_MODE                          UART_TCIE_DISABLE

/**data register empty interrupt**/
#define UART_UDRIE_DISABLE                      0   //disable interrupt
#define UART_UDRIE_ENABLE                       1   //enable interrupt
#define UART_URIE_MODE                          UART_UDRIE_DISABLE

/**RX modes**/
#define UART_RX_DISABLE                         0   //disable RX
#define UART_RX_ENABLE                          1   //disable RX
#define UART_RX_MODE                            UART_RX_ENABLE


/**tx modes**/
#define UART_TX_DISABLE                         0   //disable TX
#define UART_TX_ENABLE                          1   //enable TX
#define UART_TX_MODE                            UART_TX_ENABLE

/**speed of transmation**/
#define UART_SYNC_SPEED_MODE                    0   //sysnc mode
#define UART_NORMAL_MODE                        0   //normal mode
#define UART_DOUBLE_MODE                        1   //double speed
#define UART_SPEED_MODE                         UART_NORMAL_MODE

/** clock polarity modes**/
#define UART_NO_CLOCK                           0 // noclock in async mode
#define UART_TXR_RXF                            0
#define UART_TXF_RXR                            1
#define UART_CLOCK_POLARITY                     UART_NO_CLOCK

/**number of stop bits selection**/
#define UART_STOP_1_BIT                         0   //one bit
#define UART_STOP_2_BIT                         1   //two bits
#define UART_STOP_MODE                          UART_STOP_2_BIT

/**parity bits mode**/
#define UART_PARITY_DIABLED                     0   //no parity mode
#define UART_PARITY_EVEN                        2   //even parity mode
#define UART_PARITY_ODD                         3   //odd arity mode
#define UART_PARITY_MODE	                    UART_PARITY_DIABLED

/**async or sync modes**/
#define UART_ASYNC_MODE                         0   //async mode
#define UART_SYNC_MODE                          1   //sync mode
#define UART_MODE                               UART_SYNC_MODE

/**data size settings**/
#define UART_CS_5                               0   //5bits length
#define UART_CS_6                               1   //6bits length
#define UART_CS_7                               2   //7bits length
#define UART_CS_8                               3   //8bits length
#define UART_CS_9                               7   //9bits length
#define UART_CS_MODE                            UART_CS_8 /*data size*/


/**should be defined by user**/
  
#define USART_BAUDRATE                          9600


#endif