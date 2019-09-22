/*
 * Assignment.c
 *
 * Created: 15/09/2019 1:42:48
 * Author : Daniel
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

#define LCD_ADDRESS 0x27
#define WRITE 0xFE
//For 50 kHz
#define I2C_RATE_REGISTER 0x70

typedef struct Ultrasonic_t {
	uint16_t distance;
	uint16_t time;
	struct Ultrasonic* newData;
} Ultrasonic;

void setBaudRate(void) {
	//Setup baudrate
	TWSR = 0x00;
	TWBR = I2C_RATE_REGISTER;
	TWCR = (1 << TWEN);
}

void error(uint8_t code) {
	PORTB = code;
	while(1);
}

void twiStart(void) {
	//Send START condition
	uint8_t current_status = TWSR;
	TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
	//Wait for start condition to be fully transmitted
	while(!(TWCR & ((1 << TWINT) | (1 << TWEN))));
	if ((TWSR & 0xF8) != current_status) {
		error(0x1);
	}
}

void twiSendAddress(void) {
	uint8_t current_status = TWSR;
	uint8_t toSend = (LCD_ADDRESS << 1) & WRITE; // 7 bit address and write bit as LSB as 0
	TWDR = toSend;
	TWCR = (1 << TWINT) | (1 << TWEN); //Send address
	while(!(TWCR & ((1 << TWINT) | (1 << TWEN )))); // Wait until sent
	if ((TWSR & 0xF8) != current_status) {
		error(0x2);
	}
}

void twiSentData(uint8_t data) {
	uint8_t current_status = TWSR;
	TWDR = data; //Set data to be sent
	TWCR = (1 << TWINT) | (1 << TWEN); //Send data
	while(!(TWCR & ((1 << TWINT) | (1 << TWEN )))); // Wait until sent
	if ((TWSR & 0xF8) != current_status) {
		error(0x1);
	}
}

void twiStop(void) {
	TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO);
}

void sendTWI(uint8_t msg) {
	//PORTB = 0x10;
	twiStart();
	//PORTB = 0x20;
	twiSendAddress();
	//PORTB = 0x30;
	twiSentData(msg);
	//PORTB = 0x40;
	twiStop();
}

int main(void)
{
    Ultrasonic leftSensor;
    Ultrasonic rightSensor;
	DDRB = 0xFF;
	sei();
	setBaudRate();
	sendTWI(0xF0);
	
	
    while (1) 
    {
		
    }
}

