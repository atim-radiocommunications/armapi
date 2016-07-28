/*
 * i2c.h
 *
 *  Created on: Feb 24, 2016
 *      Author: john
 */

#ifndef I2C_H_
#define I2C_H_

int i2c_open(void);
int i2c_writeByteData( uint8_t regAddr ,  uint8_t val);
int i2c_readUint16Data(uint8_t regAddr, int16_t *val);
int i2c_openNonBlock(void);
int i2c_readByteData(uint8_t regAddr ,  uint8_t *val);
int i2c_setAddress(int address);
void i2c_init(void);

#endif /* I2C_H_ */
