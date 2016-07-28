#include "legato.h"
#include <stdint.h>
#include <linux/i2c-dev.h>

#include "lsm6ds3.h"
#include "i2c.h"

int fileDesc;	//  I2c device file handle
char filename[] = "/dev/i2c-0";

int i2c_open(void)
{
	fileDesc = open(filename, O_RDWR);

	LE_INFO("i2c_open() I2C handle = %d", fileDesc);

	return (fileDesc);
}

int i2c_openNonBlock(void)
{
	fileDesc = open(filename, O_RDWR | O_NONBLOCK);

	LE_INFO("i2c_openNonBlock() I2C handle = %d", fileDesc);

	return (fileDesc);
}

int i2c_setAddress(int address)
{
	int retVal;

	retVal = ioctl(fileDesc, I2C_SLAVE, address);
	LE_INFO("i2c_setAddress() = %X", retVal);
	return(retVal);
}

// blocking call - the underlying read is I think blocking - need to find out

int i2c_readByteData(uint8_t regAddr ,  uint8_t *val)
{
	int retVal;

	retVal = write(fileDesc, &regAddr ,1);

	if (retVal == 1)
	{
		retVal = read(fileDesc, val, 1);
		//LE_INFO("read( Val %X) = %d", *val ,retVal);
	}
	else
	{
		LE_INFO("! i2c issue");
	}

	return(retVal);
}


int i2c_readUint16Data(uint8_t regAddr, int16_t *val)
{
	int retVal;


	retVal = write(fileDesc, &regAddr ,1);

	if (retVal == 1)
	{
		retVal = read(fileDesc, val, 2);
		//LE_INFO("i2c_readUint16Data( Val %X %X)", regAddr, *val);
	}
	else
	{
		LE_INFO("! i2c issue");
	}

	return(retVal);
}


int i2c_writeByteData( uint8_t regAddr ,  uint8_t val)
{
	int retVal;
	uint8_t data[2];
	data[0] = regAddr;
	data[1] = val;

	retVal = write(fileDesc, &data ,2);

	if (retVal == 1)
	{
		LE_INFO("write( regAddr %X %X" ,regAddr ,val);
	}
	else
	{
		LE_INFO("! i2c issue");
	}
	return(retVal);
}


int i2c_close(void)
{
	int retVal;

	retVal = close(fileDesc);
	LE_INFO("i2c_close() = %d", retVal);
	return(retVal);
}


void i2c_init(void)
{
    LE_INFO("i2c_init");
}
