/*
 * LCD.c
 *
 * Created: 23/09/2019 8:51:31
 *  Author: Daniel
 */ 

void wait41ms(void);

void sendNibble(uint8_t nibble) {
	twiSend(LCD_ADDRESS, (nibble | EN));
	twiSend(LCD_ADDRESS, nibble);
}

void lcdSend(uint8_t cmd) {
	uint8_t to_send = cmd & 0xF0;
	sendNibble(to_send);
	to_send = (cmd << 4) & 0xF0;
	sendNibble(to_send);
}

void initLCD(void) {
	lcdSend(0x00);
	//Set to 4 bit mode
	lcdSend(0x03);
	// Wait > 4.1ms
	lcdSend(0x03);
	// Wait > 100 us
	lcdSend(0x03);
}

void wait41ms(void) {
	__asm("PUSH r16");
	__asm("PUSH r17");
	__asm("LDI r17, 0xC1")
	__asm("loop1: ");
	__asm("DEC r16");
	__asm("CPI r16, 0x0");
	__asm("BRNE loop1");
	__asm("DEC r17");
	__asm("CPI r17, 0x0");
	__asm("BRNE loop1");
}