/*
 * Assignment.c
 *
 * Created: 15/09/2019 1:42:48
 * Author : Daniel
 */ 

#include <avr/io.h>

#define LCD_ADDRESS 0x20

typedef struct Ultrasonic_t {
	uint16_t distance;
	uint16_t time;
	struct Ultrasonic* newData;
} Ultrasonic;

void querySensors(Ultrasonic* leftSensor, Ultrasonic* rightSensor)
{
	register int *lower_time asm("r24");
	register int *upper_time asm("r25");
	
	PORTB = 0x42;
	while(PINB == 0x42);
	
	//TODO: Maybe use hardware interrupts when learned
	__asm("loop:");
	__asm("IN r20, 0x16");
	__asm("CPI r20, 0x42");
	__asm("BRNE FIND_HIGH");
	
	__asm("FIND_HIGH:");
	__asm("CPI r20, 0xC3");
	__asm("BRNE CHECK_LEFT");
	__asm("ADIW r24, 0x4");
	__asm("RJMP loop");
	
	__asm("CHECK_LEFT:");
	__asm("ANDI r20, 0x40");
	__asm("BRNE CHECK_RIGHT")
	
	__asm("END: NOP");
}

int main(void)
{
    Ultrasonic leftSensor;
    Ultrasonic rightSensor;
    /*10111101*/
    DDRB = 0xBD;
	//Enable pull-up resistors
	/*01000010*/
	PINB = 0x42;
	
	querySensors(&leftSensor, &rightSensor);
	
    while (1) 
    {
		
    }
}

