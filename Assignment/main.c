/*
 * Assignment.c
 *
 * Created: 15/09/2019 1:42:48
 * Author : Daniel
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "LCD.h"

typedef struct Ultrasonic_t {
	uint16_t distance;
	uint16_t time;
	struct Ultrasonic* newData;
} Ultrasonic;

uint8_t single_num_to_char(uint8_t num);
void three_digit_to_str(uint8_t num, uint8_t* result);

int main(void)
{
    Ultrasonic leftSensor;
    Ultrasonic rightSensor;	
	DDRB = 0xFF;
	
	//setBaudrate();
	//initLCD();
	uint8_t num = 123;
	uint8_t res[3];
	three_digit_to_str(num, res);
	
    while (1) 
    {
		__asm("NOP");
    }
}

void three_digit_to_str(uint8_t number, uint8_t* result) {
	uint8_t h = number / 100;
	uint8_t t = (number / 10) - (h * 10);
	uint8_t o = number - (t * 10) - (h * 100);
	result[0] = single_num_to_char(o);
	result[1] = single_num_to_char(t);
	result[2] = single_num_to_char(h);
}

uint8_t single_num_to_char(uint8_t num) {
	return num | 0x30;
}