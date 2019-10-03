/*
 * TWI.h
 *
 * Created: 23/09/2019 8:30:32
 *  Author: Daniel
 */ 


#ifndef TWI_H_
#define TWI_H_

#include <avr/io.h>

#define WRITE 0xFE
//For 50 kHz
#define I2C_RATE_REGISTER 0x70
#define I2C_GOOD_START 0x08
#define I2C_ADDRESS_SEND_SUCCESS 0x18
#define I2C_DATA_SEND_SUCCESS 0x28

void setBaudrate(void);
void twiSend(uint8_t address, uint8_t msg);

#endif /* TWI_H_ */