/*
 * LCD.c
 *
 * Created: 23/09/2019 8:51:31
 *  Author: Daniel
 */ 

#include "LCD.h"

void display_reset(void);

void sendNibble(uint8_t nibble, uint8_t is_char) {
	uint8_t options = EN;
	if (is_char) {
		options |= RS;
	}
	options |= BACKLIGHT_CMD;
	twiSend(LCD_ADDRESS, (nibble | options));
	PORTB = (nibble | options);
	_delay_us(1);
	options ^= EN;
	twiSend(LCD_ADDRESS, nibble | options);
}

void lcdSend(uint8_t cmd, uint8_t is_char) {
	uint8_t to_send = cmd & 0xF0;
	sendNibble(to_send, is_char);
	to_send = (cmd << 4) & 0xF0;
	sendNibble(to_send, is_char);
}

void initLCD(void) {
	_delay_ms(15);
	lcdSend(0x00, 0);
	//Set to 4 bit mode
	sendNibble(0x3, 0);
	// Wait > 4.1ms
	_delay_ms(5);
	sendNibble(0x3, 0);
	_delay_us(200);
	// Wait > 100 us
	sendNibble(BIT_MODE, 0);
	_delay_us(200);
	lcdSend(FUNCTION_SET, 0);
	display_reset();
}

void display_reset(void) {
	lcdSend(DISPLAY_ON, 0);
	_delay_us(37);
	lcdSend(CLEAR_DISPLAY, 0);
	_delay_ms(1.5);
	lcdSend(ENTRY_MODE, 0);
	_delay_us(37);
}

void go_home(void) {
	lcdSend(HOME_CMD, 0);
	_delay_ms(2);
}

void sendCharacterLCD(uint8_t character) {
	//Address is just the ascii value for the character
	lcdSend(character, 1);
	_delay_us(5);	
}

/*void sendNumberLCD(uint8_t number, uint8_t line) {
	uint8_t address = NUMBER_BASE_ADDRESS + number;
	lcdSend(address, 0);
	_delay_us(5);
}*/