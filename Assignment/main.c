/*
 * Assignment.c
 *
 * Created: 15/09/2019 1:42:48
 * Author : Daniel
 */ 

#define F_CPU 12000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

uint8_t volatile got_distance = 0;
uint8_t volatile is_high = 0;

ISR(INT1_vect) {
	if (was_high == 1) {
		//Stop timer
		TCCR1B = 0;
		got_distance = 1;
		is_high = 0;
	} else {
		//Start timer
		TCCR1B |= (1 << CS10);
		is_high = 1;
	}
}

uint16_t querySensors()
{	
	uint8_t i;
	PORTC = 0x01;
	//About 10 us
	_delay_us(10);
	PORTC = 0x00;
	
	got_distance = 0;
	while(got_distance == 0);
	
	uint16_t clock_cycles = TCNT1;
	TCNT1 = 0;
	//About 12 clock cycles a us
	return clock_cycles;
}

uint8_t timeToDistance(uint16_t time) {
	uint8_t distance;
	distance = time / 696;
	return distance;
}

int main(void)
{
	DDRB = 0xFF;
	DDRD = 0b11110111;
    DDRC = 0x01;
	
	PORTB = 0x00;
	PORTC = 0x00;
	
	//Enable interrupt
	GICR |= (1 << INT1);
	//Changes on any logical change
	MCUCR |= (1 << ISC10);
	sei();
	
	while (1) {
		uint16_t time_s = querySensors();
		uint8_t distance = timeToDistance(time_s);
		PORTB = distance;
		_delay_ms(50);
	}
	
	//serialSend(distance);
    while (1);
}

