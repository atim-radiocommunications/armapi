// ---------------------------------------------------------------------
// Created date: 17.11.2015
// ---------------------------------------------------------------------

/***********************************************************************

 Copyright (c) 2015 ATIM
 
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.

***********************************************************************/

#include "armn8.h"

// ---------------------------------------------------------------------
// Private define
// ---------------------------------------------------------------------
#ifndef __DOXYGEN__

// Time
#define _ARMN8_TIME_TIMEOUT 			100		//100ms
#define _ARMN8_TIME_SFTIMEOUT			10000	//10s
#define _ARMN8_TIME_BOOTING 			3600	//3.6s

// Other
#define _ARMN8_NUMBER_OF_TRIALS_GO_AT 	3
#define _ARMN8_SIGFOX_PAYLOAD_MAX		12
#define _ARMN8_RF_PAYLOAD_MAX			120
#define _ARMN8_MIN_CHANNEL				1
#define _ARMN8_MAX_CHANNEL				559
#define _ARMN8_MIN_RADIO_POWER			(-18)
#define _ARMN8_MAX_LONG_PREAMBLE_TIME	900
#define _ARMN8_MAX_POST_TIME			2550

// Index S Registers
#define _ARMN8_IREGH_APPLICATION 			0
#define _ARMN8_IREGH_CHANNEL1_LSB 			1
#define _ARMN8_IREGH_CHANNEL1_MSB 			2
#define _ARMN8_IREGH_POWER					3
#define _ARMN8_IREGH_RADIO_BAUDRATE 		4
#define _ARMN8_IREGH_SERIAL_BAUDRATE 		5
#define _ARMN8_IREGH_SERIAL_DATABITS 		6
#define _ARMN8_IREGH_SERIAL_PARITY 			7
#define _ARMN8_IREGH_SERIAL_STOPBIT 		8
#define _ARMN8_IREGH_ON_BOARD				9
#define _ARMN8_IREGH_CHANNEL2_LSB 			10
#define _ARMN8_IREGH_CHANNEL2_MSB 			11
#define _ARMN8_IREGH_RSSI_LEVEL				12
#define _ARMN8_IREGH_NSAMPLE_LSB 			13
#define _ARMN8_IREGH_NSAMPLE_MSB 			14
#define _ARMN8_IREGH_USER_GAIN				15
#define _ARMN8_IREGH_WAKE_UP_PWR			16
#define _ARMN8_IREGH_WAKE_UP_RF				17
#define _ARMN8_IREGH_LONG_PREAMBLE_LSB		18
#define _ARMN8_IREGH_LONG_PREAMBLE_MSB		19
#define _ARMN8_IREGH_POST_TIME				20
#define _ARMN8_IREGH_REMOTE_ADDRESS 		21
#define _ARMN8_IREGH_SETTING1				22
#define _ARMN8_IREGH_SETTING2				23
#define _ARMN8_IREGH_LOCALE_ADDRESS 		24
#define _ARMN8_IREGH_VERSION_CODE_LSB		25
#define _ARMN8_IREGH_VERSION_CODE_MSB		26

// S Registers
#define _ARMN8_REGH_APPLICATION 			0
#define _ARMN8_REGH_CHANNEL1_LSB 			2
#define _ARMN8_REGH_CHANNEL1_MSB 			3
#define _ARMN8_REGH_POWER					4
#define _ARMN8_REGH_RADIO_BAUDRATE 			8
#define _ARMN8_REGH_SERIAL_BAUDRATE 		12
#define _ARMN8_REGH_SERIAL_DATABITS 		13
#define _ARMN8_REGH_SERIAL_PARITY 			14
#define _ARMN8_REGH_SERIAL_STOPBIT 			15
#define _ARMN8_REGH_ON_BOARD				25
#define _ARMN8_REGH_CHANNEL2_LSB 			26
#define _ARMN8_REGH_CHANNEL2_MSB 			27
#define _ARMN8_REGH_RSSI_LEVEL				32
#define _ARMN8_REGH_NSAMPLE_LSB 			43
#define _ARMN8_REGH_NSAMPLE_MSB 			44
#define _ARMN8_REGH_USER_GAIN				61
#define _ARMN8_REGH_WAKE_UP_PWR				62
#define _ARMN8_REGH_WAKE_UP_RF				63
#define _ARMN8_REGH_LONG_PREAMBLE_LSB		64
#define _ARMN8_REGH_LONG_PREAMBLE_MSB		65
#define _ARMN8_REGH_POST_TIME				66
#define _ARMN8_REGH_REMOTE_ADDRESS 			90
#define _ARMN8_REGH_SETTING1				92
#define _ARMN8_REGH_SETTING2				93
#define _ARMN8_REGH_LOCALE_ADDRESS 			97
#define _ARMN8_REGH_VERSION_CODE_LSB		98
#define _ARMN8_REGH_VERSION_CODE_MSB		99

// Helper for manipulate registers
#define _ARMN8_REG8_INIT(type, name)	arm->_regs##type[_ARMN8_IREG##type##_##name].reg=_ARMN8_REG##type##_##name
#define _ARMN8_REG16_INIT(type, name) 	arm->_regs##type[_ARMN8_IREG##type##_##name##_LSB].reg=_ARMN8_REG##type##_##name##_LSB; \
										arm->_regs##type[_ARMN8_IREG##type##_##name##_MSB].reg=_ARMN8_REG##type##_##name##_MSB

#define _ARMN8_REG8(type, name) 		arm->_regs##type[_ARMN8_IREG##type##_##name].newVal

#define _ARMN8_REG16_GET(type, name, var)								\
	(var) = arm->_regs##type[_ARMN8_IREG##type##_##name##_MSB].newVal;	\
	(var)<<=8;															\
	(var) |= arm->_regs##type[_ARMN8_IREG##type##_##name##_LSB].newVal
	
#define _ARMN8_REG16_SET(type, name, val)								\
	arm->_regs##type[_ARMN8_IREG##type##_##name##_LSB].newVal = (val);	\
	arm->_regs##type[_ARMN8_IREG##type##_##name##_MSB].newVal = (val)>>8


// Radio Application values
#define _ARMN8_REGH_APPLICATION_UART_RF					0x10
		
// Radio baudrate values
#define _ARMN8_REGH_RADIO_BAUDRATE_1200					0x01
#define _ARMN8_REGH_RADIO_BAUDRATE_2400					0x02
#define _ARMN8_REGH_RADIO_BAUDRATE_4800					0x03
#define _ARMN8_REGH_RADIO_BAUDRATE_9600					0x04
#define _ARMN8_REGH_RADIO_BAUDRATE_19200				0x05
#define _ARMN8_REGH_RADIO_BAUDRATE_38400				0x06
#define _ARMN8_REGH_RADIO_BAUDRATE_57600				0x07
#define _ARMN8_REGH_RADIO_BAUDRATE_115200				0x08
		
// Serial baudrate values
#define _ARMN8_REGH_SERIAL_BAUDRATE_1200				0x00
#define _ARMN8_REGH_SERIAL_BAUDRATE_2400				0x01
#define _ARMN8_REGH_SERIAL_BAUDRATE_4800				0x02
#define _ARMN8_REGH_SERIAL_BAUDRATE_9600				0x03
#define _ARMN8_REGH_SERIAL_BAUDRATE_19200				0x04
#define _ARMN8_REGH_SERIAL_BAUDRATE_38400				0x05
#define _ARMN8_REGH_SERIAL_BAUDRATE_57600				0x06
#define _ARMN8_REGH_SERIAL_BAUDRATE_115200				0x07
#define _ARMN8_REGH_SERIAL_BAUDRATE_230400				0x08
		
// Serial parity values
#define _ARMN8_REGH_SERIAL_PARITY_ODD					0x01
#define _ARMN8_REGH_SERIAL_PARITY_EVEN					0x03
#define _ARMN8_REGH_SERIAL_PARITY_NO					0x02
		
// Power values
#define	_ARMN8_REGH_POWER_USER_GAIN						0xff
#define	_ARMN8_REGH_POWER_LIMIT							0x00
		
// Setting 1 values
#define	_ARMN8_REGH_SETTING1_LBT						0x01
#define	_ARMN8_REGH_SETTING1_AFA						0x02
#define	_ARMN8_REGH_SETTING1_LONG_PREAMBLE				0x04
#define	_ARMN8_REGH_SETTING1_WOR_CS						0x08
#define	_ARMN8_REGH_SETTING1_FILTER_LONG_PREAMBLE		0x10
#define	_ARMN8_REGH_SETTING1_PACKET_MODE				0x40
#define	_ARMN8_REGH_SETTING1_INFINITY_MODE				0x80
		
// Setting 2 values
#define	_ARMN8_REGH_SETTING2_WHITENING					0x10
#define	_ARMN8_REGH_SETTING2_CRC						0x20
#define	_ARMN8_REGH_SETTING2_LONG_HEADRE				0x40
		
// On board values
#define	_ARMN8_REGH_ON_BOARD_TXRX_ON					0x01
#define	_ARMN8_REGH_ON_BOARD_TXRX_OFF					0x02
		
// Wake up pwr values
#define _ARMN8_REGH_WAKE_UP_PWR_UART					0x10
#define _ARMN8_REGH_WAKE_UP_PWR_INT0					0x80
		
// Wake up rf values
#define _ARMN8_REGH_WAKE_UP_RF_RF						0x80

#endif //__DOXYGEN__

// ---------------------------------------------------------------------
// Private prototypes functions
// ---------------------------------------------------------------------
#ifndef __DOXYGEN__

void _armN8Uint8ToHexStr(uint8_t val, uint8_t* str);
void _armN8Uint8ToDecStr(uint8_t val, uint8_t* str);
void _armN8HexStrToUint8(const uint8_t* str, uint8_t* val);

ssize_t _armN8Read(armN8_t* arm, uint8_t* buf, size_t nbyte, unsigned int timeout);
ssize_t _armN8WriteRead(armN8_t* arm, const uint8_t* tbuf, size_t tnbyte, uint8_t* rbuf, size_t rnbyte, unsigned int rtimeout);

armN8Error_t _armN8GoAt(armN8_t* arm);
armN8Error_t _armN8BackAt(armN8_t* arm);
armN8Error_t _armN8GetRegH(armN8_t* arm, uint8_t reg, uint8_t* val);
armN8Error_t _armN8SetRegH(armN8_t* arm, uint8_t reg, uint8_t val);

#endif //__DOXYGEN__

// ---------------------------------------------------------------------
// Implementation public functions
// ---------------------------------------------------------------------
armN8Error_t armN8Init(armN8_t* arm, void* port)
{	
	int i = 0;
	//Initialize the arm structure
	bzero(arm, sizeof(armN8_t));
	arm->_port = port;
	
	//Init registers
	_ARMN8_REG8_INIT (H, APPLICATION);
	_ARMN8_REG16_INIT(H, CHANNEL1);
	_ARMN8_REG8_INIT (H, POWER);
	_ARMN8_REG8_INIT (H, RADIO_BAUDRATE);
	_ARMN8_REG8_INIT (H, SERIAL_BAUDRATE);
	_ARMN8_REG8_INIT (H, SERIAL_DATABITS);
	_ARMN8_REG8_INIT (H, SERIAL_PARITY);
	_ARMN8_REG8_INIT (H, SERIAL_STOPBIT);
	_ARMN8_REG8_INIT (H, ON_BOARD);
	_ARMN8_REG16_INIT(H, CHANNEL2);
	_ARMN8_REG8_INIT (H, RSSI_LEVEL);
	_ARMN8_REG16_INIT(H, NSAMPLE);
	_ARMN8_REG8_INIT (H, USER_GAIN);
	_ARMN8_REG8_INIT (H, WAKE_UP_PWR);
	_ARMN8_REG8_INIT (H, WAKE_UP_RF);
	_ARMN8_REG16_INIT(H, LONG_PREAMBLE);
	_ARMN8_REG8_INIT (H, POST_TIME);
	_ARMN8_REG8_INIT (H, REMOTE_ADDRESS);
	_ARMN8_REG8_INIT (H, SETTING1);
	_ARMN8_REG8_INIT (H, SETTING2);
	_ARMN8_REG8_INIT (H, LOCALE_ADDRESS);
	_ARMN8_REG16_INIT(H, VERSION_CODE);
	
	//Open the uart port
	if(armPortOpen(&arm->_port))
		return ARMN8_ERR_PORT_OPEN;

	if(armPortConfig(arm->_port, 	ARMPORT_BAUDRATE_19200,
									ARMPORT_DATA_8BITS,
									ARMPORT_PARITY_NO,
									ARMPORT_STOPBIT_1))
		return ARMN8_ERR_PORT_CONFIG;
	
	//Reboot the arm
	return armN8Reboot(arm);
}

armN8Error_t armN8DeInit(armN8_t* arm)
{
	if(armPortClose(arm->_port) == -1)
		return ARMN8_ERR_PORT_CLOSE;
		
	return ARMN8_ERR_NONE;
}

armN8Error_t armN8Reboot(armN8_t* arm)
{
	int i = 0;
	armN8Error_t err = ARMN8_ERR_NONE;
	#ifndef ARMPORT_WITH_nRESET
	uint8_t buf[24];
	ssize_t nread;
	#endif
	
	#ifdef ARMPORT_WITH_nSLEEP
	//nSLEEP to '1'
	armPortGpioSet(arm->_port, ARMPORT_PIN_nSLEEP, true);
	#endif
	
	#ifdef ARMPORT_WITH_nBOOT
	//nBOOT to '1'
	armPortGpioSet(arm->_port, ARMPORT_PIN_nBOOT, true);
	#endif
	
	#ifdef ARMPORT_WITH_nRESET
	//Reboot by pin
	armPortGpioSet(arm->_port, ARMPORT_PIN_nRESET, false);
	armPortDelay(10);
	armPortGpioSet(arm->_port, ARMPORT_PIN_nRESET, true);
	#else
	//Reboot by "ATR"
	if(err = _armN8GoAt(arm))
		return err;
		
	nread = _armN8WriteRead(arm, "ATR\r", 4, buf, sizeof buf, _ARMN8_TIME_TIMEOUT);
	if(nread < 0)
		return ARMN8_ERR_PORT_WRITE_READ;
	//Check the message
	if(memmem(buf, nread, "RESTARTING", 10) == NULL)
		return ARMN8_ERR_ARM_CMD;
	#endif
	
	#ifdef ARMPORT_WITH_nBOOT
	//nBOOT to '0'
	armPortGpioSet(arm->_port, ARMPORT_PIN_nBOOT, false);
	#else
	//Wait booting
	armPortDelay(_ARMN8_TIME_BOOTING);
	#endif
	
	//Configure the port
	if(armPortConfig(arm->_port, 	ARMPORT_BAUDRATE_19200,
									ARMPORT_DATA_8BITS,
									ARMPORT_PARITY_NO,
									ARMPORT_STOPBIT_1))
		return ARMN8_ERR_PORT_CONFIG;
	
	//Read all S register from arm
	if(err = _armN8GoAt(arm))
		return err;
	for(i=0; i<_ARMN8_REGH_SIZE; i++)
	{
		if(err = _armN8GetRegH(arm, arm->_regsH[i].reg, &arm->_regsH[i].val))
			return err;
		arm->_regsH[i].newVal = arm->_regsH[i].val;
	}
	if(err = _armN8BackAt(arm))
		return err;
		
	//Get max power
	arm->_maxPower = 14;
		
	//Set UART to RF Mode in Application register.
	_ARMN8_REG8(H, APPLICATION) = _ARMN8_REGH_APPLICATION_UART_RF;
	#ifdef ARMPORT_WITH_nSLEEP
	//Set Wake up on the slepp pin
	_ARMN8_REG8(H, WAKE_UP_PWR) |=  _ARMN8_REGH_WAKE_UP_PWR_INT0;
	#endif
	
	//Send the new value of registers to arm
	return armN8UpdateConfig(arm);
}

armN8Error_t armN8DataToSigfox(armN8_t* arm, const uint8_t* bufTx, size_t nbyteTx, uint8_t* bufRx)
{
	armN8Error_t err = ARMN8_ERR_NONE;
	size_t i = 0;
	ssize_t nread;
	uint8_t _buf[32] = "AT$SF=";
	
	//Check size
	if(nbyteTx > _ARMN8_SIGFOX_PAYLOAD_MAX)
		return ARMN8_ERR_SIGFOX_DATA;
	
	//Nothing to send ?
	if(nbyteTx == 0)
		return ARMN8_ERR_NONE;
		
	//Converter bufTx to acii
	for(i=0; i<nbyteTx; i++)
		_armN8Uint8ToHexStr(bufTx[i], _buf+6+i*2);
		
	//Frame in Rx mode ?
	if(bufRx)
	{
		_buf[6+i*2] = ',';
		_buf[7+i*2] = '1';
		i++;
	}
	_buf[6+i*2] = '\r';
		
	//Go to AT
	if(err = _armN8GoAt(arm))
		return err;
	
	//Write AT commend and read reply
	nread = _armN8WriteRead(arm, _buf, 6+i*2+1, _buf, sizeof _buf, _ARMN8_TIME_TIMEOUT);
	if(nread < 0)
		return ARMN8_ERR_PORT_WRITE_READ;
		
	//Read/Wait response
	nread = _armN8Read(arm, _buf, sizeof _buf, _ARMN8_TIME_SFTIMEOUT);
	if(nread < 0)
		return ARMN8_ERR_PORT_READ;
		
	//Check the message
	if(memmem(_buf, nread, "OK", 2) == NULL)
		return ARMN8_ERR_SIGFOX_SEND;
		
	//Back AT
	return _armN8BackAt(arm);
}

int8_t armN8GetMaxRadioPower(uint16_t radioChannel, armN8Baudrate_t radioBaud)
{
	return 27;
}

armN8Error_t armN8SetRadio(armN8_t* arm, uint16_t channel, armN8Baudrate_t baud, int8_t power)
{
	int8_t maxPower;

	//The parameter is out of range?
	if(	(channel < _ARMN8_MIN_CHANNEL) || (channel > _ARMN8_MAX_CHANNEL) ||
		((power != ARMN8_POWER_AUTO) && (power > arm->_maxPower) || (power > _ARMN8_MIN_RADIO_POWER)))
		return ARMN8_ERR_PARAM_OUT_OF_RANGE;
	
	//Check if the new parameters is possible
	maxPower = armN8GetMaxRadioPower(channel, baud);
	if(	(maxPower == -1) ||
		(power > maxPower))
		return ARMN8_ERR_PARAM_INCOMPATIBLE;
	
	//Set baudrate
	switch(baud)
	{
		case 1200:
			_ARMN8_REG8(H, RADIO_BAUDRATE) = _ARMN8_REGH_RADIO_BAUDRATE_1200;
		break;
		
		case 2400:	                  
			_ARMN8_REG8(H, RADIO_BAUDRATE) = _ARMN8_REGH_RADIO_BAUDRATE_2400;
		break;
		
		case 4800:	                  
			_ARMN8_REG8(H, RADIO_BAUDRATE) = _ARMN8_REGH_RADIO_BAUDRATE_4800;
		break;
		
		case 9600:	                  
			_ARMN8_REG8(H, RADIO_BAUDRATE) = _ARMN8_REGH_RADIO_BAUDRATE_9600;
		break;
		
		case 19200:	                  
			_ARMN8_REG8(H, RADIO_BAUDRATE) = _ARMN8_REGH_RADIO_BAUDRATE_19200;
		break;
		
		case 38400:	                  
			_ARMN8_REG8(H, RADIO_BAUDRATE) = _ARMN8_REGH_RADIO_BAUDRATE_38400;
		break;
		
		case 57600:	                  
			_ARMN8_REG8(H, RADIO_BAUDRATE) = _ARMN8_REGH_RADIO_BAUDRATE_57600;
		break;
		
		case 115200:	              
			_ARMN8_REG8(H, RADIO_BAUDRATE) = _ARMN8_REGH_RADIO_BAUDRATE_115200;
		break;
		
		default:
			return ARMN8_ERR_PARAM_OUT_OF_RANGE;
		break;
	}
	
	//Set channel if LBT&AFA mode is disable
	//if(LBT&AFA)
		_ARMN8_REG16_SET(H, CHANNEL1, channel);
	
	//Power is adjusted ?
	if(power = ARMN8_POWER_AUTO)
		_ARMN8_REG8(H, POWER) = _ARMN8_REGH_POWER_LIMIT;
	else
	{
		_ARMN8_REG8(H, POWER) = _ARMN8_REGH_POWER_USER_GAIN;
		_ARMN8_REG8(H, USER_GAIN) = power;
	}
	
	return ARMN8_ERR_NONE;
}

void armN8GetRadio(armN8_t* arm, uint16_t* channel, armN8Baudrate_t* baud, int8_t* power)
{
	//Get channel
	if(channel)
	{
		_ARMN8_REG16_GET(H, CHANNEL1, *channel);
	}
	
	//Get baudrate
	if(baud)
	{
		switch(_ARMN8_REG8(H, RADIO_BAUDRATE))
		{
			case _ARMN8_REGH_RADIO_BAUDRATE_1200:
				*baud = (armN8Baudrate_t)1200;
			break;
			
			case _ARMN8_REGH_RADIO_BAUDRATE_2400:	                  
				*baud = (armN8Baudrate_t)2400;
			break;
			
			case _ARMN8_REGH_RADIO_BAUDRATE_4800:	                  
				*baud = (armN8Baudrate_t)4800;
			break;
			
			case _ARMN8_REGH_RADIO_BAUDRATE_9600:	                  
				*baud = (armN8Baudrate_t)9600;
			break;
			
			case _ARMN8_REGH_RADIO_BAUDRATE_19200:	                  
				*baud = (armN8Baudrate_t)19200;
			break;
			
			case _ARMN8_REGH_RADIO_BAUDRATE_38400:	                  
				*baud = (armN8Baudrate_t)38400;
			break;
			
			case _ARMN8_REGH_RADIO_BAUDRATE_57600:	                  
				*baud = (armN8Baudrate_t)57600;
			break;
			
			case _ARMN8_REGH_RADIO_BAUDRATE_115200:	              
				*baud = (armN8Baudrate_t)115200;
			break;
			
			default:
				*baud = ARMN8_BAUDRATE_NONE;
			break;
		}
	}
	
	//Get power
	if(power)
	{
		//Power is auto adjusted ?
		if(_ARMN8_REG8(H, POWER) == _ARMN8_REGH_POWER_LIMIT)
			*power = ARMN8_POWER_AUTO;
		else
			*power = _ARMN8_REG8(H, USER_GAIN);
	}
}

armN8Error_t armN8SetRadioRemoteAdd(armN8_t *arm, uint8_t add)
{
	//Error if the addressing is not enable.
	if(_ARMN8_REG8(H, SETTING2)&_ARMN8_REGH_SETTING2_LONG_HEADRE)
		return ARMN8_ERR_ADDRESSING_NOT_ENABLE;
		
	_ARMN8_REG8(H, REMOTE_ADDRESS) = add;
	return ARMN8_ERR_NONE;
}

uint8_t armN8GetRadioRemoteAdd(armN8_t *arm)
{
	return _ARMN8_REG8(H, REMOTE_ADDRESS);
}

armN8Error_t armN8SetRadioLocalAdd(armN8_t *arm, uint8_t add)
{
	//Error if the addressing is not enable.
	if(_ARMN8_REG8(H, SETTING2)&_ARMN8_REGH_SETTING2_LONG_HEADRE)
		return ARMN8_ERR_ADDRESSING_NOT_ENABLE;
	
	_ARMN8_REG8(H, LOCALE_ADDRESS) = add;
	return ARMN8_ERR_NONE;
}

uint8_t armN8GetRadioLocalAdd(armN8_t *arm)
{
	return _ARMN8_REG8(H, LOCALE_ADDRESS);
}

void armN8EnableAddressing(armN8_t *arm, bool enable)
{
	if(enable) //Enable long header
		_ARMN8_REG8(H, SETTING2) |= _ARMN8_REGH_SETTING2_LONG_HEADRE;
	else //Disable long header
		_ARMN8_REG8(H, SETTING2) &= ~_ARMN8_REGH_SETTING2_LONG_HEADRE;
}

bool armN8IsEnableAddressing(armN8_t *arm)
{
	return (_ARMN8_REG8(H, SETTING2)&_ARMN8_REGH_SETTING2_LONG_HEADRE)?true:false;
}

void armN8EnableCrc(armN8_t *arm, bool enable)
{
	if(enable)
	{
		//Disable infinity mode.
		_ARMN8_REG8(H, SETTING1) &= ~_ARMN8_REGH_SETTING1_INFINITY_MODE;
		_ARMN8_REG8(H, SETTING1) |= _ARMN8_REGH_SETTING1_PACKET_MODE;

		//Enable crc
		_ARMN8_REG8(H, SETTING2) |= _ARMN8_REGH_SETTING2_CRC;
	}
	else //Disable crc
		_ARMN8_REG8(H, SETTING2) &= ~_ARMN8_REGH_SETTING2_CRC;
}

bool armN8IsEnableCrc(armN8_t *arm)
{
	return (_ARMN8_REG8(H, SETTING2)&_ARMN8_REGH_SETTING2_CRC)?true:false;
}

armN8Error_t armN8EnableInfinityMode(armN8_t *arm, bool enable)
{
	if(enable)
	{
		//WOR is enable? 
		if(_ARMN8_REG8(H, WAKE_UP_RF)&_ARMN8_REGH_WAKE_UP_RF_RF)
			return ARMN8_ERR_WOR_ENABLE;
			
		//Disable crc.
		_ARMN8_REG8(H, SETTING2) &= ~_ARMN8_REGH_SETTING2_CRC;

		//Disable packet mode and enable infinity mode
		_ARMN8_REG8(H, SETTING1) &= ~_ARMN8_REGH_SETTING1_PACKET_MODE;
		_ARMN8_REG8(H, SETTING1) |= _ARMN8_REGH_SETTING1_INFINITY_MODE;
	}
	else //Disable infinity mode and enable packet mode
	{
		_ARMN8_REG8(H, SETTING1) &= ~_ARMN8_REGH_SETTING1_INFINITY_MODE;
		_ARMN8_REG8(H, SETTING1) |= _ARMN8_REGH_SETTING1_PACKET_MODE;
	}
	
	return ARMN8_ERR_NONE;
}

bool armN8IsEnableInfinityMode(armN8_t *arm)
{
	return (_ARMN8_REG8(H, SETTING1)&_ARMN8_REGH_SETTING1_INFINITY_MODE)?true:false;
}

void armN8EnableWhitening(armN8_t *arm, bool enable)
{
	if(enable)//Enable whitening
		_ARMN8_REG8(H, SETTING2) |= _ARMN8_REGH_SETTING2_WHITENING;
	else //Disable whitening
		_ARMN8_REG8(H, SETTING2) &= ~_ARMN8_REGH_SETTING2_WHITENING;
}

bool armN8IsEnableWhitening(armN8_t *arm)
{
	return (_ARMN8_REG8(H, SETTING2)&_ARMN8_REGH_SETTING2_WHITENING)?true:false;
}

armN8Error_t armN8SetSerial(armN8_t* arm, armPortBaudrate_t baud, armPortDatabits_t databits, armPortParity_t parity, armPortStopbit_t stopbit)
{	
	//Check if baud is compatible with wake up on uart if enable.
	if(_ARMN8_REG8(H, WAKE_UP_PWR)&_ARMN8_REGH_WAKE_UP_PWR_UART &&
		baud > ARMPORT_BAUDRATE_38400)
		return ARMN8_ERR_PARAM_OUT_OF_RANGE;
	
	//Set baudrate
	switch(baud)
	{
		case 1200:
			_ARMN8_REG8(H, SERIAL_BAUDRATE) = _ARMN8_REGH_RADIO_BAUDRATE_1200;
		break;
		
		case 2400:	                  
			_ARMN8_REG8(H, SERIAL_BAUDRATE) = _ARMN8_REGH_RADIO_BAUDRATE_2400;
		break;
		
		case 4800:	                  
			_ARMN8_REG8(H, SERIAL_BAUDRATE) = _ARMN8_REGH_RADIO_BAUDRATE_4800;
		break;
		
		case 9600:	                  
			_ARMN8_REG8(H, SERIAL_BAUDRATE) = _ARMN8_REGH_RADIO_BAUDRATE_9600;
		break;
		
		case 19200:	                  
			_ARMN8_REG8(H, SERIAL_BAUDRATE) = _ARMN8_REGH_RADIO_BAUDRATE_19200;
		break;
		
		case 38400:	                  
			_ARMN8_REG8(H, SERIAL_BAUDRATE) = _ARMN8_REGH_RADIO_BAUDRATE_38400;
		break;
		
		case 57600:	                  
			_ARMN8_REG8(H, SERIAL_BAUDRATE) = _ARMN8_REGH_RADIO_BAUDRATE_57600;
		break;
		
		case 115200:	              
			_ARMN8_REG8(H, SERIAL_BAUDRATE) = _ARMN8_REGH_RADIO_BAUDRATE_115200;
		break;
		
		case 230400:	              
			_ARMN8_REG8(H, SERIAL_BAUDRATE) = _ARMN8_REGH_SERIAL_BAUDRATE_230400;
		break;
		
		default:
			return ARMN8_ERR_PARAM_OUT_OF_RANGE;
		break;
	}
	
	//Set databits
	_ARMN8_REG8(H, SERIAL_DATABITS) = databits;
	
	//Set databits
	switch(parity)
	{
		case ARMPORT_PARITY_ODD:
			_ARMN8_REG8(H, SERIAL_PARITY) = _ARMN8_REGH_SERIAL_PARITY_ODD;
		break;
		
		case ARMPORT_PARITY_EVEN:
			_ARMN8_REG8(H, SERIAL_PARITY) = _ARMN8_REGH_SERIAL_PARITY_EVEN;
		break;
		
		case ARMPORT_PARITY_NO:
		default:
			_ARMN8_REG8(H, SERIAL_PARITY) = _ARMN8_REGH_SERIAL_PARITY_NO;
		break;
	}
	
	//Set databits
	_ARMN8_REG8(H, SERIAL_STOPBIT) = stopbit;

	return ARMN8_ERR_NONE;
}

void armN8GetSerial(armN8_t* arm, armPortBaudrate_t* baud, armPortDatabits_t* databits, armPortParity_t* parity, armPortStopbit_t* stopbit)
{
	//Get baudrate
	if(baud)
	{
		switch(_ARMN8_REG8(H, SERIAL_BAUDRATE))
		{
			case _ARMN8_REGH_SERIAL_BAUDRATE_1200:
				*baud = (armPortBaudrate_t)1200;
			break;
			
			case _ARMN8_REGH_SERIAL_BAUDRATE_2400:	                  
				*baud = (armPortBaudrate_t)2400;
			break;
			
			case _ARMN8_REGH_SERIAL_BAUDRATE_4800:	                  
				*baud = (armPortBaudrate_t)4800;
			break;
			
			case _ARMN8_REGH_SERIAL_BAUDRATE_9600:	                  
				*baud = (armPortBaudrate_t)9600;
			break;
			
			case _ARMN8_REGH_SERIAL_BAUDRATE_19200:	                  
				*baud = (armPortBaudrate_t)19200;
			break;
			
			case _ARMN8_REGH_SERIAL_BAUDRATE_38400:	                  
				*baud = (armPortBaudrate_t)38400;
			break;
			
			case _ARMN8_REGH_SERIAL_BAUDRATE_57600:	                  
				*baud = (armPortBaudrate_t)57600;
			break;
			
			case _ARMN8_REGH_SERIAL_BAUDRATE_115200:	              
				*baud = (armPortBaudrate_t)115200;
			break;
			
			case _ARMN8_REGH_SERIAL_BAUDRATE_230400:	              
				*baud = (armPortBaudrate_t)230400;
			break;
			
			default:
				*baud = ARMPORT_BAUDRATE_NONE;
			break;
		}
	}
	
	//Get databits
	if(databits)
		*databits = (armPortDatabits_t)_ARMN8_REG8(H, SERIAL_DATABITS);
	
	
	//Get parity
	if(parity)
	{
		switch(_ARMN8_REG8(H, SERIAL_PARITY))
		{
			case _ARMN8_REGH_SERIAL_PARITY_ODD:	              
				*parity = ARMPORT_PARITY_ODD;
			break;
			
			case _ARMN8_REGH_SERIAL_PARITY_EVEN:	              
				*parity = ARMPORT_PARITY_EVEN;
			break;
			
			case _ARMN8_REGH_SERIAL_PARITY_NO:
			default:
				*parity = ARMPORT_PARITY_NO;
			break;
		}
	}
	
	//Get stopbit
	if(stopbit)
		*stopbit = (armPortStopbit_t)_ARMN8_REG8(H, SERIAL_STOPBIT);
}

armN8Error_t armN8SetWorMode(armN8_t* arm, armN8Wor_t mode, uint16_t periodTime, uint16_t postTime, int8_t rssiLevel, bool filterLongPreamble)
{	
	//Disable WOR mode
	_ARMN8_REG8(H, WAKE_UP_RF) &= ~_ARMN8_REGH_WAKE_UP_RF_RF;
	#ifndef ARMPORT_WITH_nSLEEP
		_ARMN8_REG8(H, WAKE_UP_PWR) &= ~_ARMN8_REGH_WAKE_UP_PWR_UART;
	#endif
	_ARMN8_REG8(H, SETTING1) &= ~_ARMN8_REGH_SETTING1_LONG_PREAMBLE;
	
	//Return if disable mode.
	if(mode == ARMN8_WOR_DISABLE)
		return ARMN8_ERR_NONE;

	//periodTime out of rang?
	if(periodTime>_ARMN8_MAX_LONG_PREAMBLE_TIME)
		return ARMN8_ERR_PARAM_OUT_OF_RANGE;
	
	//postTime out of rang?
	if(postTime>_ARMN8_MAX_POST_TIME)
		return ARMN8_ERR_PARAM_OUT_OF_RANGE;
		
	//Set period time (same registers than long preamble)
	_ARMN8_REG16_SET(H, LONG_PREAMBLE, periodTime);
	
	//Set post time
	_ARMN8_REG8(H, POST_TIME) = postTime/10;
	
	//Enable long preamble?
	if(mode == ARMN8_WOR_LP)
	{
		_ARMN8_REG8(H, SETTING1) |= _ARMN8_REGH_SETTING1_LONG_PREAMBLE;
		return ARMN8_ERR_NONE;
	}

	//Enable wake up on radio
	_ARMN8_REG8(H, WAKE_UP_RF) |= _ARMN8_REGH_WAKE_UP_RF_RF;
	
	#ifndef ARMPORT_WITH_nSLEEP
	//Change uart baudrate if necessary
	if(_ARMN8_REG8(H, SERIAL_BAUDRATE) > _ARMN8_REGH_RADIO_BAUDRATE_38400)
		_ARMN8_REG8(H, SERIAL_BAUDRATE) = _ARMN8_REGH_RADIO_BAUDRATE_38400;
	//Enable wake up on uart
	_ARMN8_REG8(H, WAKE_UP_PWR) |=  _ARMN8_REGH_WAKE_UP_PWR_UART;
	#endif
	
	//Set WOR in CS 'Carrier Sense'?
	if(mode == ARMN8_WOR_CS)
	{
		_ARMN8_REG8(H, SETTING1) |= _ARMN8_REGH_SETTING1_WOR_CS;
		
		//Set rssi level if WOR in CS
		_ARMN8_REG8(H, RSSI_LEVEL) = rssiLevel;
	}
	//Set WOR in PQT 'Preamble Quality Threshold'?
	else
	{
		_ARMN8_REG8(H, SETTING1) &= ~_ARMN8_REGH_SETTING1_WOR_CS;
	}
	
	//Enable/disable filter in long preamble
	if(filterLongPreamble)
		_ARMN8_REG8(H, SETTING1) |= _ARMN8_REGH_SETTING1_FILTER_LONG_PREAMBLE;
	else
		_ARMN8_REG8(H, SETTING1) &= ~_ARMN8_REGH_SETTING1_FILTER_LONG_PREAMBLE;
	
	return ARMN8_ERR_NONE;
}

void armN8GetWorMode(armN8_t* arm, armN8Wor_t* mode, uint16_t* periodTime, uint16_t* postTime, int8_t* rssiLevel, bool* filterLongPreamble)
{
	//Get WOR mode
	if(mode)
	{
		//WOR is enable? 
		if(_ARMN8_REG8(H, WAKE_UP_RF)&_ARMN8_REGH_WAKE_UP_RF_RF)
		{
			//WOR in CS 'Carrier Sense'?
			if(_ARMN8_REG8(H, SETTING1)&_ARMN8_REGH_SETTING1_WOR_CS)
				*mode = ARMN8_WOR_CS;
			else//WOR in PQT 'Preamble Quality Threshold'?
				*mode = ARMN8_WOR_PQT;
		}
		//long preamble is enable? 
		else if(_ARMN8_REG8(H, SETTING1)&_ARMN8_REGH_SETTING1_LONG_PREAMBLE)
			*mode = ARMN8_WOR_LP;
		else //WOR is disable?
			*mode = ARMN8_WOR_DISABLE;
	}
	
	//Get post time
	if(postTime)
		*postTime = _ARMN8_REG8(H, POST_TIME)*10;
	
	//Get period time
	if(periodTime)
	{
		_ARMN8_REG16_GET(H, LONG_PREAMBLE, *periodTime);
	}
	
	//Get rssi level
	if(rssiLevel)
		*rssiLevel = _ARMN8_REG8(H, RSSI_LEVEL);
	
	//Get filter
	if(filterLongPreamble)
		*filterLongPreamble = (_ARMN8_REG8(H, SETTING1)&_ARMN8_REGH_SETTING1_FILTER_LONG_PREAMBLE)?true:false;
}

armN8Error_t armN8EnableWakeUpUart(armN8_t *arm, bool enable)
{
	//Disable?
	if(enable == false)
	{
		#ifndef ARMPORT_WITH_nSLEEP
		//WOR is enable? 
		if(_ARMN8_REG8(H, WAKE_UP_RF)&_ARMN8_REGH_WAKE_UP_RF_RF)
			return ARMN8_ERR_WOR_ENABLE;
		#endif
		
		_ARMN8_REG8(H, WAKE_UP_PWR) &=  ~_ARMN8_REGH_WAKE_UP_PWR_UART;
	}
	else //Enable?
	{
		//Change uart baudrate if necessary
		if(_ARMN8_REG8(H, SERIAL_BAUDRATE) > _ARMN8_REGH_RADIO_BAUDRATE_38400)
			_ARMN8_REG8(H, SERIAL_BAUDRATE) = _ARMN8_REGH_RADIO_BAUDRATE_38400;
		
		_ARMN8_REG8(H, WAKE_UP_PWR) |=  _ARMN8_REGH_WAKE_UP_PWR_UART;
	}
	
	return ARMN8_ERR_NONE;
}

bool armN8IsEnableWakeUpUart(armN8_t *arm)
{
	return (_ARMN8_REG8(H, WAKE_UP_PWR)&_ARMN8_REGH_WAKE_UP_PWR_UART)?true:false;
}

#ifdef ARMPORT_WITH_nSLEEP
void armN8Sleep(armN8_t* arm, bool sleep)
{
	armPortGpioSet(arm->_port, !sleep);
}
#endif

armN8Error_t armN8SetLbtAfaMode(armN8_t *arm, armN8LbtAfa_t mode, int8_t rssiLevel, uint16_t nSamples, uint16_t channel2)
{
	armN8Baudrate_t baud;
	int8_t power;
	int8_t maxPower;
	
	//Disable LBT&AFA mode?
	if(mode == ARMN8_LBTAFA_DISABLE)
	{
		_ARMN8_REG8(H, SETTING1) &= (_ARMN8_REGH_SETTING1_LBT|_ARMN8_REGH_SETTING1_AFA);
		return ARMN8_ERR_NONE;
	}
	
	//The parameter is out of range?
	if(	(channel2 < _ARMN8_MIN_CHANNEL) || (channel2 > _ARMN8_MAX_CHANNEL))
		return ARMN8_ERR_PARAM_OUT_OF_RANGE;
	
	//Check if the new parameters is possible
	armN8GetRadio(arm, NULL, &baud, &power);
	maxPower = armN8GetMaxRadioPower(channel2, baud);
	if(	(maxPower == -1) ||
		(power > maxPower))
		return ARMN8_ERR_PARAM_INCOMPATIBLE;
	
	//Enable LBT mode
	_ARMN8_REG8(H, SETTING1) |= _ARMN8_REGH_SETTING1_LBT;
	
	//Set rssi level
	_ARMN8_REG8(H, RSSI_LEVEL) = rssiLevel;
	
	//Set nSamples
	_ARMN8_REG16_SET(H, NSAMPLE, nSamples);
	
	//Enable AFA mode?
	if(mode = ARMN8_LBTAFA_LBTAFA)
	{
		//Set AFA mode
		_ARMN8_REG8(H, SETTING1) |= _ARMN8_REGH_SETTING1_AFA;
		
		//Set channel2
		_ARMN8_REG16_SET(H, CHANNEL2, channel2);
	}
	
	return ARMN8_ERR_NONE;
}

void armN8GetLbtAfaMode(armN8_t *arm, armN8LbtAfa_t* mode, int8_t* rssiLevel, uint16_t* nSamples, uint16_t* channel2)
{
	//Get LBT&AFA mode
	if(mode)
	{
		//LBT is enable?
		if(_ARMN8_REG8(H, SETTING1)&_ARMN8_REGH_SETTING1_LBT)
		{
			//AFA is enable?
			if(_ARMN8_REG8(H, SETTING1)&_ARMN8_REGH_SETTING1_AFA)
				*mode = ARMN8_LBTAFA_LBTAFA;
			else
				*mode = ARMN8_LBTAFA_LBT;
		}
		else
			*mode = ARMN8_LBTAFA_DISABLE;
	}
	
	//Get rssi level
	if(rssiLevel)
		*rssiLevel = _ARMN8_REG8(H, RSSI_LEVEL);
	
	//Get nSamples
	if(nSamples)
	{
		_ARMN8_REG16_GET(H, NSAMPLE, *nSamples);
	}
	
	//Get channel 2
	if(channel2)
	{
		_ARMN8_REG16_GET(H, CHANNEL2, *channel2);
	}
}

void armN8SetLed(armN8_t* arm, armN8Led_t led)
{
	_ARMN8_REG8(H, ON_BOARD) &= ~(_ARMN8_REGH_ON_BOARD_TXRX_ON|_ARMN8_REGH_ON_BOARD_TXRX_OFF);
	
	switch(led)
	{
		case ARMN8_LED_OFF:
		break;
		
		case ARMN8_LED_OFF_RF:
			_ARMN8_REG8(H, ON_BOARD) |= _ARMN8_REGH_ON_BOARD_TXRX_OFF;
		break;
		
		case ARMN8_LED_ON_RF:
			_ARMN8_REG8(H, ON_BOARD) |= _ARMN8_REGH_ON_BOARD_TXRX_ON;
		break;
	}
}

armN8Led_t armN8GetLed(armN8_t* arm)
{
	if(_ARMN8_REG8(H, ON_BOARD)&_ARMN8_REGH_ON_BOARD_TXRX_ON)
		return ARMN8_LED_ON_RF;
		
	if(_ARMN8_REG8(H, ON_BOARD)&_ARMN8_REGH_ON_BOARD_TXRX_OFF)
		return ARMN8_LED_OFF_RF;
		
	return ARMN8_LED_OFF;
}

armN8Error_t armN8UpdateConfig(armN8_t* arm)
{
	armN8Error_t err = ARMN8_ERR_NONE;
	bool reConfigPort = false;
	int i = 0;
	
	//Find index of first registers changed.
	for(i=0; i<_ARMN8_REGH_SIZE; i++)
	{
		if(arm->_regsH[i].newVal != arm->_regsH[i].val)
			break;
	}
	
	//Registers changed found?
	if(i<_ARMN8_REGH_SIZE)
	{
		//Write S register changed to arm
		if(err = _armN8GoAt(arm))
			return err;
		for(; i<_ARMN8_REGH_SIZE; i++)
		{
			//Set the new value if the value was changed. 
			if(arm->_regsH[i].newVal != arm->_regsH[i].val)
			{
				if(err = _armN8SetRegH(arm, arm->_regsH[i].reg, arm->_regsH[i].newVal))
					return err;
					
				arm->_regsH[i].val = arm->_regsH[i].newVal;
				
				if(	(i >= _ARMN8_IREGH_SERIAL_BAUDRATE) &&
					(i <= _ARMN8_IREGH_SERIAL_STOPBIT))
					reConfigPort = true;
			}
		}
		if(err = _armN8BackAt(arm))
			return err;
	}
	
	//Need to reconfigure the port?
	if(reConfigPort)
	{
		armPortBaudrate_t baudrate;
		armPortDatabits_t databits;
		armPortParity_t parity;
		armPortStopbit_t stopbit;
		
		armN8GetSerial(arm, &baudrate, &databits, &parity, &stopbit);
		if(armPortConfig(arm->_port, baudrate, databits, parity, stopbit))
			err = ARMN8_ERR_PORT_CONFIG;
	}
	
	return err;
}

ssize_t armN8Send(armN8_t *arm, const uint8_t *buf, size_t nbyte)
{
	ssize_t nwrite = 0;
	ssize_t n = 0;
	int baud = 0;
	
	armN8GetRadio(arm, NULL, (armN8Baudrate_t*)&baud, NULL);
	if(baud <= 0)
		return -1;
	
	//if(infini mode disabel)
	if(1)
	{
		//Send _ARMN8_RF_PAYLOAD_MAX by _ARMN8_RF_PAYLOAD_MAX
		while((nbyte-nwrite) > _ARMN8_RF_PAYLOAD_MAX)
		{
			n = armPortWrite(arm->_port, buf+nwrite, _ARMN8_RF_PAYLOAD_MAX);
			if(n == -1)
				return -1;
			nwrite += n;
			
			armPortDelay(((n*8000)/baud)+100);
		}
		
		//Send last data
		n = armPortWrite(arm->_port, buf+nwrite, (nbyte-nwrite));
		if(n == -1)
			return -1;
			
		nwrite += n;
		
		//TODO temporaier aven de trouver mieu ce qui serai bine ce cerai de lancer un timer
		//et de verifier si le timer a finie aven char ehnvoi de nouvelle données ou
		// aven de rentrer en commende AT
		//armPortDelay((n*8000)/baud+100);
		
		//Wait Te+Ta+Tb+Tc+Tpreamble+Tsync+Tdata+Tcrc
		//Te: 3 byte time
		//Ta: 5ms if "listen before talk" is enable else 0ms
		//Tb: Pseudorandom if "listen before talk" is enable
		//Tc: Time before radio Tx 0 by default
		//Tpreamble:
		//Tsync:
		//Tdata: nbyte * byte time
		//Tcrc: 2 byte time if crc is enable
		armPortDelay(((n*8000)/baud)+100);
	}
	else 
	{
		//Send all buf
		nwrite = armPortWrite(arm->_port, buf, nbyte);
		
		//Wait end send
		//armPortDelay();
	}
	
	return nwrite;
}

ssize_t armN8Receive(armN8_t *arm, uint8_t *buf, size_t nbyte, int timeout)
{
	size_t nread = 0;
	int n = 0;
	
	while(1)
	{
		//Read from the port
		n = armPortRead(arm->_port, buf+nread, nbyte-nread, timeout);
		if(n == -1)
			return -1;
		else if(n == 0)
			return nread;
		
		nread += n;
	}
	
	return nread;
}

// ---------------------------------------------------------------------
// Implementation of private functions
// ---------------------------------------------------------------------
#ifndef __DOXYGEN__

void _armN8Uint8ToHexStr(uint8_t val, uint8_t* str)
{
	uint8_t digit = ((val>>4)&0xf);
	if(digit <= 9)
		str[0] = digit+'0';
	else
		str[0] = digit+('A'-10);
		
	digit = (val&0xf);
	if(digit <= 9)
		str[1] = digit+'0';
	else
		str[1] = digit+('A'-10);
}

void _armN8Uint8ToDecStr(uint8_t val, uint8_t* str)
{	
	uint8_t digit = val%10;
	str[1] = '0'+digit;
	digit = val/10;
	str[0] = '0'+digit;
}

void _armN8HexStrToUint8(const uint8_t* str, uint8_t* val)
{
	if(str[0] <= '9')
		*val = (str[0]-'0')<<4;
	else
		*val = (str[0]-('A'-10))<<4;
	
	if(str[1] <= '9')
		*val |= (str[1]-'0');
	else
		*val |= (str[1]-('A'-10));
}

ssize_t _armN8Read(armN8_t* arm, uint8_t* buf, size_t nbyte, unsigned int timeout)
{
	size_t nread = 0;
	size_t i = 0;
	int n = 0;
	int lfcount = 0;
	
	while(1)
	{
		//Read from the port
		n = armPortRead(arm->_port, buf+nread, nbyte-nread, timeout);
		if(n == -1)
			return -1;
		else if(n == 0)
			return nread;
		
		//Check if stop read condition
		for(i=nread; i<nread+n; i++)
		{
			if(buf[i] == '\n')
			{
				lfcount++;
				if(lfcount >= 2)
				{
					nread += n;
					return nread;
				}
			}
		}
		
		nread += n;
	}
	
	return nread;
}

ssize_t _armN8WriteRead(armN8_t* arm, const uint8_t* tbuf, size_t tnbyte, uint8_t* rbuf, size_t rnbyte, unsigned int rtimeout)
{
	//Write
	if(armPortWrite(arm->_port, tbuf, tnbyte) != (ssize_t)tnbyte)
		return -1;
		
	//Read
	return _armN8Read(arm, rbuf, rnbyte, rtimeout);
}

armN8Error_t _armN8GoAt(armN8_t* arm)
{
	uint8_t ntry = 0;
	uint8_t buf[40];
	ssize_t nread;
	
	while(ntry < _ARMN8_NUMBER_OF_TRIALS_GO_AT)
	{
		ntry++;
		
		//Write '+++' for go to AT commend and read reply
		nread = _armN8WriteRead(arm, "+++", 3, buf, sizeof buf, _ARMN8_TIME_TIMEOUT);
		if(nread < 0)
			return ARMN8_ERR_PORT_WRITE_READ;
			
		//Check the message
		if(	memmem(buf, nread, "WELCOME IN SETUP MODE", 21) != NULL ||
			memmem(buf, nread, "+++", 3) != NULL)
			return ARMN8_ERR_NONE;
	}
	
	return ARMN8_ERR_ARM_GO_AT;
}

armN8Error_t _armN8BackAt(armN8_t* arm)
{
	uint8_t buf[32];
	ssize_t nread;
	
	//Write 'ATI' for back AT commend and read reply
	nread = _armN8WriteRead(arm, "ATI\r", 4, buf, sizeof buf, _ARMN8_TIME_TIMEOUT);
	if(nread < 0)
		return ARMN8_ERR_PORT_WRITE_READ;
		
	//Check the message
	if(memmem(buf, nread, "QUIT SETUP", 10) == NULL)
		return ARMN8_ERR_ARM_BACK_AT;
		
	//Wait arm ready
	armPortDelay(_ARMN8_TIME_TIMEOUT+_ARMN8_REG8(H, POST_TIME)*10);
	
	return ARMN8_ERR_NONE;
}

armN8Error_t _armN8GetRegH(armN8_t* arm, uint8_t reg, uint8_t* val)
{
	uint8_t rbuf[16];
	ssize_t nread;
	uint8_t* ptrrbuf = NULL;
	uint8_t tbuf[8] = "ATH0";
	
	//Create AT commend
	_armN8Uint8ToDecStr(reg, tbuf+4);
	tbuf[6] = '\r';
	
	//Write AT commend and read reply
	nread = _armN8WriteRead(arm, tbuf, 7, rbuf, sizeof rbuf, _ARMN8_TIME_TIMEOUT);
	if(nread < 0)
		return ARMN8_ERR_PORT_WRITE_READ;
		
	//Check the message
	tbuf[6] = '=';
	ptrrbuf = (uint8_t*)memmem(rbuf, nread, tbuf+2, 5);
	if(ptrrbuf == NULL)
		return ARMN8_ERR_ARM_GET_REG;
		
	//Convert the value
	ptrrbuf += 5;
	if(ptrrbuf[0] == '\0' && ptrrbuf[1] == '\0')
		return ARMN8_ERR_ARM_GET_REG;
	_armN8HexStrToUint8(ptrrbuf, val);
	
	return ARMN8_ERR_NONE;
}

armN8Error_t _armN8SetRegH(armN8_t* arm, uint8_t reg, uint8_t val)
{
	uint8_t rbuf[16];
	ssize_t nread;
	uint8_t tbuf[10] = "ATH0";
	
	//Create AT commend
	_armN8Uint8ToDecStr(reg, tbuf+4);
	tbuf[6] = '=';
	_armN8Uint8ToHexStr(val, tbuf+7);
	tbuf[9] = '\r';
		
	//Write AT commend and read reply
	nread = _armN8WriteRead(arm, tbuf, 10, rbuf, sizeof rbuf, _ARMN8_TIME_TIMEOUT);
	if(nread < 0)
		return ARMN8_ERR_PORT_WRITE_READ;
		
	//Check the message
	if(memmem(rbuf, nread, tbuf+2, 7) == NULL)
		return ARMN8_ERR_ARM_SET_REG;
	
	return ARMN8_ERR_NONE;
}

#endif //__DOXYGEN__

