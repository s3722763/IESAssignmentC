/*
 * TWI.c
 *
 * Created: 23/09/2019 8:30:24
 *  Author: Daniel
 */ 
#include "TWI.h"

void setBaudrate(void) {
	//Setup baudrate
	TWSR = 0x00;
	
	TWBR = I2C_RATE_REGISTER;
	TWCR = (1 << TWEN);
	TWDR = 0xFF;
}

void error(uint8_t code) {
	PORTB = code;
	while(1);
}

void twiStart(void) {
	//Send START condition
	uint8_t a = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
	TWCR = a;
	//Wait for start condition to be fully transmitted
	while(!(TWCR & (1 << TWINT))) {}
	//Check to see what the status register must be
	if ((TWSR & 0xF8) != I2C_GOOD_START) {
		error(TWSR);
	}
}

void twiSendAddress(uint8_t address) {
	uint8_t toSend = (address << 1) & WRITE; // 7 bit address and write bit as LSB as 0
	TWDR = toSend;
	TWCR = (1 << TWINT) | (1 << TWEN); //Send address
	while(!(TWCR & (1 << TWINT))); // Wait until sent
	if ((TWSR & 0xF8) != I2C_ADDRESS_SEND_SUCCESS) {
		error(TWSR);
	}
}

void twiSentData(uint8_t data) {
	TWDR = data; //Set data to be sent
	TWCR = (1 << TWINT) | (1 << TWEN); //Send data
	while(!(TWCR & (1 << TWINT))); // Wait until sent
	if ((TWSR & 0xF8) != I2C_DATA_SEND_SUCCESS ) {
		error(TWSR);
	}
}

void twiStop(void) {
	TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO);
}

void twiSend(uint8_t address, uint8_t msg) {
	//PORTB = 0x10;
	twiStart();
	//PORTB = 0x20;
	twiSendAddress(address);
	//PORTB = 0x30;
	twiSentData(msg);
	//PORTB = 0x40;
	twiStop();
}