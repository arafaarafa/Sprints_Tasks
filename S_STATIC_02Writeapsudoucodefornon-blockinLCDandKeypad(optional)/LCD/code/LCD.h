/*
 * LCD.h
 *
 * Created: 4/16/2023 3:53:11 PM
 *  Author: Arafa
 */ 




#ifndef LCD_H_
#define LCD_H_
#include "../../MCAL/DIO/DIO.h"

#define LCD_CGRAM_START_ADD				0x40
#define LCD_DDRAM_START_ADD_LINE_1		0x80
#define LCD_DDRAM_START_ADD_LINE_2		0xC0
#define LCD_CMD_CLEAR					0x01
#define LCD_CMD_CURSOR_HOME				0x02 

#define LCD_CMD_ENTRY_MODE_INCREMENT_ON_SHIFT_ON 0x07 
#define LCD_CMD_ENTRY_MODE_INCREMENT_OFF_SHIFT_OFF 0x04
#define LCD_CMD_ENTRY_MODE_INCREMENT_ON_SHIFT_OFF	0x06
#define LCD_CMD_ENTRY_MODE_INCREMENT_OFF_SHIFT_ON	0x05


#define LCD_MOVE_CURSOR_SHIFT_LEFT		0x10
#define LCD_MOVE_CURSOR_SHIFT_RIGHT		0x14
#define LCD_DISPLAY_SHIFT_LEFT			0x18
#define LCD_DISPLAY_SHIFT_RIGHT			0x1C

#define LCD_DISPLAY_ON_CUR_ON_BLOCK_ON	0x0F
#define LCD_DISPLAY_OFF_CUR_OFF_BLOCK_OFF	0x08
#define LCD_DISPLAY_ON_CUR_OFF_BLOCK_OFF	0x0C
#define LCD_DISPLAY_ON_CUR_ON_BLOCK_OFF		0x0E
#define LCD_DISPLAY_ON_CUR_OFF_BLOCK_ON		0x0D

#define LCD_4BITS_2LINES_58DM				0x28
#define	LCD_8BITS_2LINES_511DM				0x32
#define LCD_8BITS_2LINES_58DM				0x38

#define LCD_MAX_COL			16
#define LCD_MAX_ROW			2
#define LCD_COM_4_BITS		4
#define LCD_COM_8_BITS		8
#define LCD_COM_4_OR_8_BITS		LCD_COM_4_BITS

/*
*
*
* -LCD_ReturnType datatype enum has all lcd function return states
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
}LCD_ReturnType;


/*
*
*
* -lcd_rs_state_t datatype enum has all lcd register select  modes 
*   
*   -Members-
*
*-1- (LCD_COMMAND) command mode
*-2- (LCD_DATA)    data mode
*
*
*/
typedef enum{
	LCD_COMMAND=0,
	LCD_DATA=1
	}lcd_rs_state_t;

/*
*
*
* -lcd_rs_state_t datatype enum has all lcd operations like read write  
*   -Members-
*
*-1- (LCD_WRITE) lcd write case
*-2- (LCD_READ)  lcd read case
*
*
*/	
typedef enum{
	LCD_WRITE=0,
	LCD_READ
}lcd_rw_state_t;




/*
*
*
* -lcd_pin_port_t datatype struct has all lcd pin info
*   -Members-
*
* -1-port_index     **port number declared in dio.h file**
* -2-pin_index      **pin number declared in dio.h file**
*
*/
typedef struct{
	port_index_t port_index;
	pin_index_t  pin_index;
	}lcd_pin_port_t;


/*
*
*
* -lcd_config_t datatype struct has all lcd pins to control the lcd
*   -Members-
*
* -1-lcd_pin_port      **array of all information about data pins even 4bits mode or 8bits mode**
*
* -2-port_RS_index     **port index that lcd rs_pin connected to its pin**
* -3-pin_RS_index      **pin index of rs_pin**
*
* -4-port_RW_index     **port index that lcd rw_pin connected to its pin**
* -5-pin_RW_index      **pin index of rw_pin**
*
* -6-port_EN_index     **port index that lcd EN_pin connected to its pin**
* -7-pin_EN_index      **pin index of EN_pin**
*
*/
typedef struct{
	lcd_pin_port_t lcd_pin_port[LCD_COM_4_OR_8_BITS];
	
	port_index_t port_RS_index;
	pin_index_t  pin_RS_index;
	
	port_index_t port_RW_index;
	pin_index_t  pin_RW_index;
	
	port_index_t port_EN_index;
	pin_index_t  pin_EN_index;
	
}lcd_config_t;

/*
*   -Description-
*-this function init lcd 
*
*   -Input parameters -
*-1-it holds lcd configuration  (lcd_config_t *lcd_config)
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
LCD_ReturnType lcd_init(lcd_config_t *lcd_config);

/*
*   -Description-
*-this function send char
*
*   -Input parameters -
*-1-it holds lcd configuration  (lcd_config_t *lcd_config)
*-2-it pointer to data variable  (uint8_t *data)
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
LCD_ReturnType lcd_send_char(lcd_config_t *lcd_config, uint8_t *data);

/*
*   -Description-
*-this function send data
*
*   -Input parameters -
*-1-it holds lcd configuration  (lcd_config_t *lcd_config)
*-2-it holds command code (uint8_t cmd)
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
LCD_ReturnType lcd_send_cmd(lcd_config_t *lcd_config, uint8_t cmd);

/*
*   -Description-
*-this function send data
*
*   -Input parameters -
*-1-it holds lcd configuration  (lcd_config_t *lcd_config)
*-2-it holds col number (uint8_t col)
*-2-it holds row number (uint8_t row)
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
LCD_ReturnType lcd_set_curser(lcd_config_t *lcd_config, uint8_t col, uint8_t row);

/*
*   -Description-
*-this function send data
*
*   -Input parameters -
*-1-it holds lcd configuration  (lcd_config_t *lcd_config)
*-2-it is array of custom character pixels (uint8_t *arr)
*-2-it is the position of custom char in the memmory (uint8_t *pos)
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
LCD_ReturnType lcd_send_custom_char(lcd_config_t *lcd_config,uint8_t *arr,uint8_t *pos);
#endif /* LCD_H_ */