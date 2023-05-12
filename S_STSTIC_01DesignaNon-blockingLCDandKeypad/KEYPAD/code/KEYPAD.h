

#ifndef KEYPAD_H
#define	KEYPAD_H

/* section : includes*/
#include "keypad_config.h"
#include "../../MCAL_layer/GPIO/GPIO.h"

/* section : Macro Declaration*/


/* section : Macro Functions Declarations*/

/* section : Data Types Declarations*/

/*
*
*
* -KEYPAD_ReturnType datatype enum has all keypad's function return states
*
*   -Members-
*
*-1- (IN_PROGRESS) the fucntion didn't fininsh its role
*-2- (E_NOT_OK) there some thing wrong 
*-3- (COMPLETED) the function done
*-4- (E_OK) very thing ok
*
*/
typedef enum{
    IN_PROGRESS,
    E_NOT_OK,
    COMPLETED,
    E_OK
}KEYPAD_ReturnType;


/*
*
*
* -keypad_pin_t datatype struct has all keypad pin info
*   -Members-
*
* -1-port_index     **port number declared in dio.h file**
* -2-pin_index      **pin number declared in dio.h file**
*
*/
typedef struct {
    port_index_t keypad_pin_port;
    pin_index_t  keypad_pin;   
}keypad_pin_t;

/*
*
*
* -keypad_pin_t datatype struct has all keypad pin info
*   -Members-
*
* -1-port_index     **port number declared in dio.h file**
* -2-pin_index      **pin number declared in dio.h file**
*
*/
typedef struct{
    keypad_pin_t keypad_rows[KEYPAD_MAX_ROWS_NO];
    keypad_pin_t keypad_cols[KEYPAD_MAX_COLS_NO];
}keypad_config_t;



/* section : Function Declaration*/

/*
*   -Description-
*-this function init the keypad pins
*
*   -Input parameters -
*-1-it holds keypad configuration  (keypad_config_t *keypad_config)
*
*   -Return-
*   LCD_ReturnType
*
*   -Return cases-
*-1- (IN_PROGRESS) the fucntion didn't fininsh its role
*-2- (E_NOT_OK) there some thing wrong 
*-3- (COMPLETED) the function done
*-4- (E_OK) very thing ok
*/
Std_ReturnType keypad_initialize(const keypad_config_t *keypad_config);

/*
*   -Description-
*-this function init the keypad pins
*
*   -Input parameters -
*-1-it holds keypad configuration  (keypad_config_t *keypad_config)

*   -output parameters -
*-1-it pointer to variable that has value has been pressed on keypad  (char *value)
*
*   -Return-
*   LCD_ReturnType
*
*   -Return cases-
*-1- (IN_PROGRESS) the fucntion didn't fininsh its role
*-2- (E_NOT_OK) there some thing wrong 
*-3- (COMPLETED) the function done
*-4- (E_OK) very thing ok
*/
Std_ReturnType keypad_get_value(const keypad_config_t *keypad_config, char *value);

#endif	/* KEYPAD_H */
