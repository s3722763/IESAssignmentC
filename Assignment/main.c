/*
 * Assignment.c
 *
 * Created: 15/09/2019 1:42:48
 * Author : Daniel
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

#define LCD_ADDRESS 0x20

typedef struct Ultrasonic_t {
	uint16_t distance;
	uint16_t time;
	struct Ultrasonic* newData;
} Ultrasonic;

uint16_t querySensors(Ultrasonic* leftSensor, Ultrasonic* rightSensor)
{	
	PORTC = 0xFF;
	PORTB = 0xF0;
	uint16_t time = 0;
	uint8_t inc = 0;
	while(inc++ != 0xF);
	PORTB = 0x0F;
	PORTC = 0x7F;
	while(PINC != 0x00) {
		//PORTB = PINC;
		//time += 8;
	}
	
	return time;
}

uint8_t timeToDistance(uint16_t time) {
	uint16_t distance;
	time = time * 100;
	distance = time * 2;
	return distance;
}

int main(void)
{
    Ultrasonic leftSensor;
    Ultrasonic rightSensor;
    /*10111101*/
    DDRC = 0x80;
	//Enable pull-up resistors
	/*01000010*/
	PORTC = 0x7F;
	DDRB = 0xFF;
	uint16_t time = querySensors(&leftSensor, &rightSensor);
	uint8_t distance = timeToDistance(time);
	PORTB = distance;
    while (1) 
    {
		
    }
}

