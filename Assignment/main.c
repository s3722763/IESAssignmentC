/*
 * Assignment.c
 *
 * Created: 15/09/2019 1:42:48
 * Author : Daniel
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

uint8_t volatile loop = 0;
uint8_t volatile up = 0;

void serialSetup() {
	UBRRH = 0x00;
	UBRRL = 0x4D;
	
	// Enable transmit and recieve bits
	UCSRB = (1 << RXEN) | (1 << TXEN);
	// Async operation no parity 8 bits
	UCSRC = (1 << URSEL) | (3 << UCSZ0);
}

void serialSend(uint8_t msg) {
	while ((UCSRA & (1 << UDRE)) == 0);
	UDR = msg;
}

ISR(TIMER1_OVF_vect){}

ISR(INT1_vect) {
	if (up == 1) {
		PORTB = 0xF0;
		//Set timer1 counter to zero
		TCNT1 = 0x0000;
		//Start clock
		TCCR1B |= (1 << CS10);
		//Enable overflow interrupt for timer1
		TIMSK = (1 << TOIE1);
	} else {
		//PORTB = 0x0F;
		//On falling edge
		//TCCR1B &= ~(1 << CS10);
		//loop = 0;
	}
}

typedef struct Ultrasonic_t {
	uint16_t distance;
	uint16_t time;
	struct Ultrasonic* newData;
} Ultrasonic;

uint16_t querySensors(Ultrasonic* leftSensor, Ultrasonic* rightSensor)
{	
	uint8_t i;
	uint16_t time = 0;
	PORTC = 0x01;
	//About 10 us
	while (i++ < 14);
	PORTC = 0x00;
	
	loop = 1;
	up = 1;
	//Enable interrupt
	GICR = 0x80;
	while(loop != 0 );
	
	time = TCNT1 / 12;
	//About 12 clock cycles a us
	//serialSend((uint8_t)(time >> 8));
	//serialSend((uint8_t)(time &0x00FF));
	return time;
}

uint8_t timeToDistance(uint16_t time) {
	uint8_t distance;
	distance = time / 58;
	return distance;
}

int main(void)
{
    Ultrasonic leftSensor;
    Ultrasonic rightSensor;
    /*10000000*/
	DDRB = 0xFF;
	DDRD = 0b11110111;
	PORTB = 0x00;
    DDRC = 0x01;
	
	//Set interupt to any change
	MCUCR = (1 << ISC10) | (1 << ISC11);
	//serialSend((MCUCR));
	serialSetup();
	sei();
	
	uint16_t time_s = querySensors(&leftSensor, &rightSensor);
	uint8_t distance = timeToDistance(time_s);
	PORTB = distance;
	
	//serialSend(distance);
    while (1);
}

