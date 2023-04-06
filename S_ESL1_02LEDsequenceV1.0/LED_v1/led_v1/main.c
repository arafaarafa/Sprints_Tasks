/*
 */

#include <avr/io.h>
pin_config_t pin_config ={.port= PORTA_INDEX, .pin = PIN0, .direction = GPIO_DIRECTION_OUTPUT, .logic= GPIO_HIGH};
int main(void)
{
    // Insert code
    gpio_pin_initialize(&pin_config);

    while(1)
    ;

    return 0;
}
