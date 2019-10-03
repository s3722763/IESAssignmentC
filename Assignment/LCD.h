/*
 * LCD.h
 *
 * Created: 23/09/2019 8:51:25
 *  Author: Daniel
 */ 


#ifndef LCD_H_
#define LCD_H_

#define F_CPU 12000000

#include "TWI.h"
#include <util/delay.h>

//Look at hd44780 datasheet for details
#define LCD_ADDRESS 0x27
#define BACKLIGHT 0x08

#define BACKLIGHT_CMD 0x08
#define EN 0x04
#define RW 0x02
#define RS 0x01
//4 Bit mode 
#define BIT_MODE 0x02
//2 for function set, C for  number of lines and size (5 * 8)
#define FUNCTION_SET 0x2C
#define DISPLAY_ON 0x08 
#define CLEAR_DISPLAY 0x01
#define ENTRY_MODE 0x06
#define NUMBER_BASE_ADDRESS 0x30
#define HOME_CMD 0x02

void initLCD(void);
void sendCharacterLCD(uint8_t character);

#endif /* LCD_H_ */