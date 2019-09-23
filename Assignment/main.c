/*
 * Assignment.c
 *
 * Created: 15/09/2019 1:42:48
 * Author : Daniel
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "TWI.h"

typedef struct Ultrasonic_t {
	uint16_t distance;
	uint16_t time;
	struct Ultrasonic* newData;
} Ultrasonic;

void initLCD(void);

int main(void)
{
    Ultrasonic leftSensor;
    Ultrasonic rightSensor;	
	DDRB = 0xFF;
	setBaudrate();
	twiSend(LCD_ADDRESS, 'a');
	
    while (1) 
    {
		
    }
}

void initLCD(void) {
	
}
