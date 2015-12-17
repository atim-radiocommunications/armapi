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

#include "arm.h"
#include "armconst.h"

// ---------------------------------------------------------------------
// Private define
// ---------------------------------------------------------------------
#ifndef __DOXYGEN__

// Time
#define _ARM_TIME_RESET 				10		//10ms
#define _ARM_TIME_TIMEOUT 				100		//100ms
#define _ARM_TIME_BACK_AT				100		//100ms
#define _ARM_TIME_SF_UPLINK_TIMEOUT		10000	//10s
#define _ARM_TIME_SF_DOWNLINK_TIMEOUT	45000	//45s
#define _ARM_TIME_BOOTING				100		//100ms

// Other values
#define _ARM_NUMBER_OF_TRIALS_GO_AT 	3
#define _ARM_SIGFOX_PAYLOAD_MAX			12
#define _ARM_SIGFOX_PAYLOAD_DOWNLINK	8
#define _ARM_RF_PAYLOAD_MAX				120
#define _ARM_MIN_CHANNEL				1
#define _ARM_MAX_CHANNEL				559
#define _ARM_MIN_RADIO_POWER			(-18)
#define _ARM_MAX_LONG_PREAMBLE_TIME		900
#define _ARM_MAX_POST_TIME				2550
#define _ARM_BASE_DEC					10
#define _ARM_BASE_HEX					16


#define _ARM_IMP1(t1) if(arm->type & (ARM_TYPE_##t1))
#define _ARM_IMP2(t1, t2) if(arm->type & (ARM_TYPE_##t1|ARM_TYPE_##t2))

// Helper for manipulate registers
#define _ARM_REG8_INIT(armType, regType, regName) \
	arm->_N8LPLD.regs##regType[_ARM_##armType##_IREG##regType##_##regName].reg=_ARM_##armType##_REG##regType##_##regName
	
#define _ARM_REG16_INIT(armType, regType, regName) \
	arm->_N8LPLD.regs##regType[_ARM_##armType##_IREG##regType##_##regName##_LSB].reg=_ARM_##armType##_REG##regType##_##regName##_LSB; \
	arm->_N8LPLD.regs##regType[_ARM_##armType##_IREG##regType##_##regName##_MSB].reg=_ARM_##armType##_REG##regType##_##regName##_MSB

#define _ARM_REG8(armType, regType, regName) \
	arm->_N8LPLD.regs##regType[_ARM_##armType##_IREG##regType##_##regName].newVal

#define _ARM_REG16_GET(armType, regType, regName, var)												\
	(var) = arm->_N8LPLD.regs##regType[_ARM_##armType##_IREG##regType##_##regName##_MSB].newVal;	\
	(var)<<=8;																						\
	(var) |= arm->_N8LPLD.regs##regType[_ARM_##armType##_IREG##regType##_##regName##_LSB].newVal
	
#define _ARM_REG16_SET(armType, regType, regName, val)												\
	arm->_N8LPLD.regs##regType[_ARM_##armType##_IREG##regType##_##regName##_LSB].newVal = (val);	\
	arm->_N8LPLD.regs##regType[_ARM_##armType##_IREG##regType##_##regName##_MSB].newVal = (val)>>8

#endif //__DOXYGEN__

// ---------------------------------------------------------------------
// Private prototypes functions
// ---------------------------------------------------------------------
#ifndef __DOXYGEN__

uint8_t* _armUintToStr(uint64_t val, uint8_t* str, uint8_t base, int n);
uint64_t _armStrToUint(uint8_t* str, uint8_t base);

ssize_t _armRead(arm_t* arm, void* buf, size_t nbyte, unsigned int timeout);
ssize_t _armWriteRead(arm_t* arm, const void* tbuf, size_t tnbyte, void* rbuf, size_t rnbyte, unsigned int rtimeout);

armError_t _armGoAt(arm_t* arm);
armError_t _armBackAt(arm_t* arm);
armError_t _armGetReg(arm_t* arm, uint8_t type, uint8_t num, uint8_t* val);
armError_t _armSetReg(arm_t* arm, uint8_t type, uint8_t num, uint8_t val);

#endif //__DOXYGEN__

// ---------------------------------------------------------------------
// Implementation public functions
// ---------------------------------------------------------------------
armError_t armInit(arm_t* arm, void* port)
{	
	//Initialize the arm structure
	bzero(arm, sizeof(arm_t));
	arm->_port = port;
	arm->type = ARM_TYPE_NONE;
	
	//Open the uart port
	if(armPortOpen(&arm->_port))
		return ARM_ERR_PORT_OPEN;

	if(armPortConfig(arm->_port, 	ARMPORT_BAUDRATE_19200,
									ARMPORT_DATA_8BITS,
									ARMPORT_PARITY_NO,
									ARMPORT_STOPBIT_1))
		return ARM_ERR_PORT_CONFIG;
	
	//Reboot the arm
	return armReboot(arm);
}

armError_t armDeInit(arm_t* arm)
{
	if(armPortClose(arm->_port) == -1)
		return ARM_ERR_PORT_CLOSE;
		
	arm->type = ARM_TYPE_NONE;
	return ARM_ERR_NONE;
}

armError_t armReboot(arm_t* arm)
{
	int i = 0;
	armError_t err = ARM_ERR_NONE;
	
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
		armPortDelay(_ARM_TIME_RESET);
		armPortGpioSet(arm->_port, ARMPORT_PIN_nRESET, true);
	#else
		//No need rebooting because initialization (type == ARM_TYPE_NONE)
		if(arm->type != ARM_TYPE_NONE)
		{
			//Go to AT commend to reboot.
			if((err = _armGoAt(arm)))
				return err;
			
			//Reboot by "ATR" if ARM is already initialized/used/...
			if(armPortWrite(arm->_port, "ATR\n", 4) != 4)
				return ARM_ERR_PORT_WRITE;
		}
	#endif
	
	//Wait booting
	armPortDelay(_ARM_TIME_BOOTING);
	
	#ifndef ARM_WITHOUT_N8_LPLD
		_ARM_IMP2(N8_LP, N8_LD)
		{
			#ifdef ARMPORT_WITH_nBOOT
				//nBOOT to '0'
				armPortGpioSet(arm->_port, ARMPORT_PIN_nBOOT, false);
			#else
				//Wait booting
				if(arm->type != ARM_TYPE_NONE)
					armPortDelay(_ARM_N8LPLD_TIME_BOOTING);
			#endif
		}
	#endif
	
	//Configure the port
	if(armPortConfig(arm->_port, 	ARMPORT_BAUDRATE_19200,
									ARMPORT_DATA_8BITS,
									ARMPORT_PARITY_NO,
									ARMPORT_STOPBIT_1))
		return ARM_ERR_PORT_CONFIG;
		
	//Get info to get ARM type
	err = armInfo(arm, &arm->type, NULL, NULL, NULL, NULL);
	if(err != ARM_ERR_NONE)
		return err;
		
	//Init registers	
	#ifndef ARM_WITHOUT_N8_LPLD
	_ARM_IMP2(N8_LP, N8_LD)
	{
		_ARM_REG8_INIT (N8LPLD, H, APPLICATION);
		_ARM_REG16_INIT(N8LPLD, H, CHANNEL1);
		_ARM_REG8_INIT (N8LPLD, H, POWER);
		_ARM_REG8_INIT (N8LPLD, H, RADIO_BAUDRATE);
		_ARM_REG8_INIT (N8LPLD, H, SERIAL_BAUDRATE);
		_ARM_REG8_INIT (N8LPLD, H, SERIAL_DATABITS);
		_ARM_REG8_INIT (N8LPLD, H, SERIAL_PARITY);
		_ARM_REG8_INIT (N8LPLD, H, SERIAL_STOPBIT);
		_ARM_REG8_INIT (N8LPLD, H, ON_BOARD);
		_ARM_REG16_INIT(N8LPLD, H, CHANNEL2);
		_ARM_REG8_INIT (N8LPLD, H, RSSI_LEVEL);
		_ARM_REG16_INIT(N8LPLD, H, NSAMPLE);
		_ARM_REG8_INIT (N8LPLD, H, USER_GAIN);
		_ARM_REG8_INIT (N8LPLD, H, WAKE_UP_PWR);
		_ARM_REG8_INIT (N8LPLD, H, WAKE_UP_RF);
		_ARM_REG16_INIT(N8LPLD, H, LONG_PREAMBLE);
		_ARM_REG8_INIT (N8LPLD, H, POST_TIME);
		_ARM_REG8_INIT (N8LPLD, H, REMOTE_ADDRESS);
		_ARM_REG8_INIT (N8LPLD, H, SETTING1);
		_ARM_REG8_INIT (N8LPLD, H, SETTING2);
		_ARM_REG8_INIT (N8LPLD, H, LOCAL_ADDRESS);
	}
	#endif
	
	#ifndef ARM_WITHOUT_N8_LW
	_ARM_IMP1(N8_LW)
	{
		//_ARM_REG8_INIT (N8LPLD, M, APPLICATION);
	}
	#endif
	
	//Go to AT commend for get register
	if((err = _armGoAt(arm)))
		return err;
	
	#ifndef ARM_WITHOUT_N8_LPLD
	_ARM_IMP2(N8_LP, N8_LD)
	{
		//Read all S register from arm
		for(i=0; i<_ARM_N8LPLD_REGH_SIZE; i++)
		{
			if((err = _armGetReg(arm, 'H', arm->_N8LPLD.regsH[i].reg, &arm->_N8LPLD.regsH[i].val)))
				return err;
			arm->_N8LPLD.regsH[i].newVal = arm->_N8LPLD.regsH[i].val;
		}
		
		//Set UART to RF Mode in Application register.
		_ARM_REG8(N8LPLD, H, APPLICATION) = _ARM_N8LPLD_REGH_APPLICATION_UART_RF;
		#ifdef ARMPORT_WITH_nSLEEP
		//Set Wake up on the sleep pin
		_ARM_REG8(N8LPLD, H, WAKE_UP_PWR) |=  _ARM_N8LPLD_REGH_WAKE_UP_PWR_INT0;
		#endif
	}
	#endif
	
	#ifndef ARM_WITHOUT_N8_LW
	_ARM_IMP1(N8_LW)
	{
	}
	#endif
	
	//back AT
	if((err = _armBackAt(arm)))
		return err;
	
	//Send the new value of registers to arm
	return armUpdateConfig(arm);
}

armError_t armInfo(arm_t* arm, armType_t* armType, uint8_t* rev, uint64_t* sn, uint16_t* rfFreq, uint8_t* rfPower)
{	
	armError_t err = ARM_ERR_NONE;
	armType_t _armType = ARM_TYPE_NONE;
	
	uint16_t _rfFreq = -1;
	uint8_t _rfPower = -1;
		
	//Get arm type, rev and sn from 'ATV' commend
	if((arm->type==ARM_TYPE_NONE) || rev || sn)
	{
		uint8_t buf[64];
		ssize_t nread;
	
		//Go to AT commend
		err = _armGoAt(arm);
		if(err != ARM_ERR_NONE)
			return err;
			
		//Send 'ATV'
		nread = _armWriteRead(arm, "ATV\r", 4, buf, sizeof buf, _ARM_TIME_TIMEOUT);
		if(nread < 0)
			return ARM_ERR_PORT_WRITE_READ;
		
		//Quit AT commend
		err = _armBackAt(arm);
		if(err != ARM_ERR_NONE)
			return err;

		//If Lora ?
		if(memmem(buf, nread, "LoRa", 4))
		{
			_armType = ARM_TYPE_N8_LW;
			_rfFreq = 868;
			_rfPower = _ARM_N8LW_MAX_POWER;
		}
		else
		{
			//Is 868Mhz ?
			if(memmem(buf, nread, "868MHZ", 6))
				_rfFreq = 868;
				
			//Is LP?
			if(memmem(buf, nread, "14DBM", 5))
			{
				_rfPower = _ARM_N8LPLD_LP_MAX_POWER;
				_armType = ARM_TYPE_N8_LP;
			}
			else // or LD ?
			{
				_rfPower = _ARM_N8LPLD_LD_MAX_POWER;
				_armType = ARM_TYPE_N8_LD;
			}
		}
		
		//Get ARM firmware revision
		if(rev)
		{
			size_t i=0;
			uint8_t* ptrstr = NULL;
				
			#ifndef ARM_WITHOUT_N8_LPLD
			if(_armType&(ARM_TYPE_N8_LP|ARM_TYPE_N8_LD))
			{
				ptrstr = memmem(buf, nread, "REV. ", 5);
				ptrstr += 5;
			}
			#endif
			
			#ifndef ARM_WITHOUT_N8_LW
			if(_armType&(ARM_TYPE_N8_LW))
			{
				ptrstr = memmem(buf, nread, "Rev:", 4);
				ptrstr += 4;
			}
			#endif
			
			//Copy string rev
			if(ptrstr)
			{
				while(!(ptrstr[i] == ' ' ||
						ptrstr[i] == '\n'||
						ptrstr[i] == '\0'))
				{
					rev[i] = ptrstr[i];
					i++;
				}
				rev[i] = '\0';
			}
		}
		
		//Get ARM serial number
		if(sn)
		{
			uint8_t* ptrstr = NULL;
				
			#ifndef ARM_WITHOUT_N8_LPLD
			if(_armType&(ARM_TYPE_N8_LP|ARM_TYPE_N8_LD))
			{
				ptrstr = memmem(buf, nread, "S/N: ", 5);
				ptrstr += 5;
			}
			#endif
			
			#ifndef ARM_WITHOUT_N8_LW
			if(_armType&(ARM_TYPE_N8_LW))
			{
				ptrstr = memmem(buf, nread, "S/N:", 4);
				ptrstr += 4;
			}
			#endif
			
			//Convert serial number string to uint
			*sn = _armStrToUint(ptrstr, _ARM_BASE_HEX);
		}
	}
	else
	{
		//Get type from ARM type
		_armType = arm->type;
		
		//Get frequency from ARM type
		if(_armType&(ARM_TYPE_N8_LP|ARM_TYPE_N8_LD|ARM_TYPE_N8_LW))
			_rfFreq = 868;
			
		//Get power from ARM type
		if(_armType&(ARM_TYPE_N8_LP|ARM_TYPE_N8_LW))
			_rfPower = _ARM_N8LPLD_LP_MAX_POWER;
		else if(_armType&(ARM_TYPE_N8_LD))
			_rfPower = _ARM_N8LPLD_LD_MAX_POWER;
	}
	
	//Get arm type
	if(armType)
		*armType = _armType;
	
	//Get frequency
	if(rfFreq)
		*rfFreq = _rfFreq;
	
	//Get power
	if(rfPower)
		*rfPower = _rfPower;

	return err;
}

armError_t armDataToSigfox(arm_t* arm, const uint8_t* bufTx, size_t nbyteTx, uint8_t* bufRx)
{
	#ifndef ARM_WITHOUT_N8_LPLD
	_ARM_IMP1(N8_LP)
	{
		armError_t err1 = ARM_ERR_NONE;
		armError_t err2 = ARM_ERR_NONE;
		size_t i = 0;
		ssize_t nread;
		uint8_t _buf[32] = "AT$SF=";
		
		//Check size
		if(nbyteTx > _ARM_SIGFOX_PAYLOAD_MAX)
			return ARM_ERR_SIGFOX_DATA;
			
		//Converter bufTx to acii
		for(i=0; i<nbyteTx; i++)
			_armUintToStr(bufTx[i], _buf+6+i*2, _ARM_BASE_HEX, 2);
			
		//Frame in Rx mode ?
		if(bufRx)
		{
			_buf[6+i*2] = ',';
			_buf[7+i*2] = '1';
			i++;
		}
		_buf[6+i*2] = '\r';
			
		//Go to AT
		err1 = _armGoAt(arm);
		if(err1 != ARM_ERR_NONE)
			return err1;
		
		//Write AT commend and read reply
		nread = _armWriteRead(arm, _buf, 6+i*2+1, _buf, sizeof _buf, _ARM_TIME_TIMEOUT);
		if(nread < 0)
			return ARM_ERR_PORT_WRITE_READ;
			
		//Read/Wait response
		nread = _armRead(arm, _buf, sizeof _buf, bufRx?_ARM_TIME_SF_DOWNLINK_TIMEOUT:_ARM_TIME_SF_UPLINK_TIMEOUT);
		if(nread < 0)
			return ARM_ERR_PORT_READ;
			
		//Check the message if downlink
		if(bufRx)
		{
			uint8_t* pbuf = memmem(_buf, nread, "+RX=", 2);
			if(pbuf == NULL)
				err1 = ARM_ERR_SIGFOX_SEND_RECEIVE;
			else //Convert data from ASCII value
				*((uint64_t*)bufRx) = _armStrToUint(pbuf+4, _ARM_BASE_HEX);
		}
		else //Check the message if uplink
		{
			if(memmem(_buf, nread, "OK", 2) == NULL)
				err1 = ARM_ERR_SIGFOX_SEND_RECEIVE;
		}

		//Back AT
		err2 = _armBackAt(arm);
		
		if(err2 != ARM_ERR_NONE)
			return err2;
		
		return err1;
	}
	#endif
	
	return ARM_ERR_BAD_TYPE;
}

int8_t armGetMaxRadioPower(uint16_t radioChannel, armBaudrate_t radioBaud)
{
	if(radioBaud == ARM_BAUDRATE_NONE)
		return -1;
		
	if(	(radioChannel < _ARM_MIN_CHANNEL) || (radioChannel > _ARM_MAX_CHANNEL))
		return -1;
	
	return 27;
}

armError_t armSetRadio(arm_t* arm, uint16_t channel, armBaudrate_t baud, int8_t power)
{
	#ifndef ARM_WITHOUT_N8_LPLD
	_ARM_IMP2(N8_LP, N8_LD)
	{
		int8_t maxPower;
		int8_t armMaxPower = arm->type&ARM_TYPE_N8_LP?_ARM_N8LPLD_LP_MAX_POWER:_ARM_N8LPLD_LD_MAX_POWER;

		//The parameter is out of range?
		if(	(channel < _ARM_MIN_CHANNEL) || (channel > _ARM_MAX_CHANNEL) ||
			((power != ARM_POWER_AUTO) && ((power > armMaxPower) || (power < _ARM_MIN_RADIO_POWER))))
			return ARM_ERR_PARAM_OUT_OF_RANGE;
		
		//Check if the new parameters is possible
		maxPower = armGetMaxRadioPower(channel, baud);
		if(	(maxPower == -1) ||
			(power > maxPower))
			return ARM_ERR_PARAM_INCOMPATIBLE;
		
		//Set baudrate
		switch(baud)
		{
			case 1200:
				_ARM_REG8(N8LPLD, H, RADIO_BAUDRATE) = _ARM_N8LPLD_REGH_RADIO_BAUDRATE_1200;
			break;
			
			case 2400:	                  
				_ARM_REG8(N8LPLD, H, RADIO_BAUDRATE) = _ARM_N8LPLD_REGH_RADIO_BAUDRATE_2400;
			break;
			
			case 4800:	                  
				_ARM_REG8(N8LPLD, H, RADIO_BAUDRATE) = _ARM_N8LPLD_REGH_RADIO_BAUDRATE_4800;
			break;
			
			case 9600:	                  
				_ARM_REG8(N8LPLD, H, RADIO_BAUDRATE) = _ARM_N8LPLD_REGH_RADIO_BAUDRATE_9600;
			break;
			
			case 19200:	                  
				_ARM_REG8(N8LPLD, H, RADIO_BAUDRATE) = _ARM_N8LPLD_REGH_RADIO_BAUDRATE_19200;
			break;
			
			case 38400:	                  
				_ARM_REG8(N8LPLD, H, RADIO_BAUDRATE) = _ARM_N8LPLD_REGH_RADIO_BAUDRATE_38400;
			break;
			
			case 57600:	                  
				_ARM_REG8(N8LPLD, H, RADIO_BAUDRATE) = _ARM_N8LPLD_REGH_RADIO_BAUDRATE_57600;
			break;
			
			case 115200:	              
				_ARM_REG8(N8LPLD, H, RADIO_BAUDRATE) = _ARM_N8LPLD_REGH_RADIO_BAUDRATE_115200;
			break;
			
			default:
				return ARM_ERR_PARAM_OUT_OF_RANGE;
			break;
		}
		
		//Set channel if LBT&AFA mode is disable
		//if(LBT&AFA)
			_ARM_REG16_SET(N8LPLD, H, CHANNEL1, channel);
		
		//Power is adjusted ?
		if((power = ARM_POWER_AUTO))
			_ARM_REG8(N8LPLD, H, POWER) = _ARM_N8LPLD_REGH_POWER_LIMIT;
		else
		{
			_ARM_REG8(N8LPLD, H, POWER) = _ARM_N8LPLD_REGH_POWER_USER_GAIN;
			_ARM_REG8(N8LPLD, H, USER_GAIN) = power;
		}
		
		return ARM_ERR_NONE;
	}
	#endif
	
	return ARM_ERR_BAD_TYPE;
}

void armGetRadio(arm_t* arm, uint16_t* channel, armBaudrate_t* baud, int8_t* power)
{
	#ifndef ARM_WITHOUT_N8_LPLD
	_ARM_IMP2(N8_LP, N8_LD)
	{
		//Get channel
		if(channel)
		{
			_ARM_REG16_GET(N8LPLD, H, CHANNEL1, *channel);
		}
		
		//Get baudrate
		if(baud)
		{
			switch(_ARM_REG8(N8LPLD, H, RADIO_BAUDRATE))
			{
				case _ARM_N8LPLD_REGH_RADIO_BAUDRATE_1200:
					*baud = (armBaudrate_t)1200;
				break;
				
				case _ARM_N8LPLD_REGH_RADIO_BAUDRATE_2400:	                  
					*baud = (armBaudrate_t)2400;
				break;
				
				case _ARM_N8LPLD_REGH_RADIO_BAUDRATE_4800:	                  
					*baud = (armBaudrate_t)4800;
				break;
				
				case _ARM_N8LPLD_REGH_RADIO_BAUDRATE_9600:	                  
					*baud = (armBaudrate_t)9600;
				break;
				
				case _ARM_N8LPLD_REGH_RADIO_BAUDRATE_19200:	                  
					*baud = (armBaudrate_t)19200;
				break;
				
				case _ARM_N8LPLD_REGH_RADIO_BAUDRATE_38400:	                  
					*baud = (armBaudrate_t)38400;
				break;
				
				case _ARM_N8LPLD_REGH_RADIO_BAUDRATE_57600:	                  
					*baud = (armBaudrate_t)57600;
				break;
				
				case _ARM_N8LPLD_REGH_RADIO_BAUDRATE_115200:	              
					*baud = (armBaudrate_t)115200;
				break;
				
				default:
					*baud = ARM_BAUDRATE_NONE;
				break;
			}
		}
		
		//Get power
		if(power)
		{
			//Power is auto adjusted ?
			if(_ARM_REG8(N8LPLD, H, POWER) == _ARM_N8LPLD_REGH_POWER_LIMIT)
				*power = ARM_POWER_AUTO;
			else
				*power = _ARM_REG8(N8LPLD, H, USER_GAIN);
		}
	}
	#endif
}

armError_t armSetRadioRemoteAdd(arm_t *arm, uint8_t add)
{
	#ifndef ARM_WITHOUT_N8_LPLD
	_ARM_IMP2(N8_LP, N8_LD)
	{
		//Error if the addressing is not enable.
		if(_ARM_REG8(N8LPLD, H, SETTING2)&_ARM_N8LPLD_REGH_SETTING2_LONG_HEADRE)
			return ARM_ERR_ADDRESSING_NOT_ENABLE;
			
		_ARM_REG8(N8LPLD, H, REMOTE_ADDRESS) = add;
		return ARM_ERR_NONE;
	}
	#endif
	
	return ARM_ERR_BAD_TYPE;
}

uint8_t armGetRadioRemoteAdd(arm_t *arm)
{
	#ifndef ARM_WITHOUT_N8_LPLD
	_ARM_IMP2(N8_LP, N8_LD)
	{
		return _ARM_REG8(N8LPLD, H, REMOTE_ADDRESS);
	}
	#endif
	
	return 255;
}

armError_t armSetRadioLocalAdd(arm_t *arm, uint8_t add)
{
	#ifndef ARM_WITHOUT_N8_LPLD
	_ARM_IMP2(N8_LP, N8_LD)
	{
		//Error if the addressing is not enable.
		if(_ARM_REG8(N8LPLD, H, SETTING2)&_ARM_N8LPLD_REGH_SETTING2_LONG_HEADRE)
			return ARM_ERR_ADDRESSING_NOT_ENABLE;
		
		_ARM_REG8(N8LPLD, H, LOCAL_ADDRESS) = add;
		return ARM_ERR_NONE;
	}
	#endif
	
	return ARM_ERR_BAD_TYPE;
}

uint8_t armGetRadioLocalAdd(arm_t *arm)
{
	#ifndef ARM_WITHOUT_N8_LPLD
	_ARM_IMP2(N8_LP, N8_LD)
	{
		return _ARM_REG8(N8LPLD, H, LOCAL_ADDRESS);
	}
	#endif
	
	return 0;
}

void armEnableAddressing(arm_t *arm, bool enable)
{
	#ifndef ARM_WITHOUT_N8_LPLD
	_ARM_IMP2(N8_LP, N8_LD)
	{
		if(enable) //Enable long header
			_ARM_REG8(N8LPLD, H, SETTING2) |= _ARM_N8LPLD_REGH_SETTING2_LONG_HEADRE;
		else //Disable long header
			_ARM_REG8(N8LPLD, H, SETTING2) &= ~_ARM_N8LPLD_REGH_SETTING2_LONG_HEADRE;
	}
	#endif
}

bool armIsEnableAddressing(arm_t *arm)
{
	#ifndef ARM_WITHOUT_N8_LPLD
	_ARM_IMP2(N8_LP, N8_LD)
	{
		return (_ARM_REG8(N8LPLD, H, SETTING2)&_ARM_N8LPLD_REGH_SETTING2_LONG_HEADRE)?true:false;
	}
	#endif
	
	return false;
}

void armEnableCrc(arm_t *arm, bool enable)
{
	#ifndef ARM_WITHOUT_N8_LPLD
	_ARM_IMP2(N8_LP, N8_LD)
	{
		if(enable)
		{
			//Disable infinity mode.
			_ARM_REG8(N8LPLD, H, SETTING1) &= ~_ARM_N8LPLD_REGH_SETTING1_INFINITY_MODE;
			_ARM_REG8(N8LPLD, H, SETTING1) |= _ARM_N8LPLD_REGH_SETTING1_PACKET_MODE;

			//Enable crc
			_ARM_REG8(N8LPLD, H, SETTING2) |= _ARM_N8LPLD_REGH_SETTING2_CRC;
		}
		else //Disable crc
			_ARM_REG8(N8LPLD, H, SETTING2) &= ~_ARM_N8LPLD_REGH_SETTING2_CRC;
	}
	#endif
}

bool armIsEnableCrc(arm_t *arm)
{
	#ifndef ARM_WITHOUT_N8_LPLD
	_ARM_IMP2(N8_LP, N8_LD)
	{
		return (_ARM_REG8(N8LPLD, H, SETTING2)&_ARM_N8LPLD_REGH_SETTING2_CRC)?true:false;
	}
	#endif
	
	return false;
}

armError_t armEnableInfinityMode(arm_t *arm, bool enable)
{
	#ifndef ARM_WITHOUT_N8_LPLD
	_ARM_IMP2(N8_LP, N8_LD)
	{
		if(enable)
		{
			//WOR is enable? 
			if(_ARM_REG8(N8LPLD, H, WAKE_UP_RF)&_ARM_N8LPLD_REGH_WAKE_UP_RF_RF)
				return ARM_ERR_WOR_ENABLE;
				
			//Disable crc.
			_ARM_REG8(N8LPLD, H, SETTING2) &= ~_ARM_N8LPLD_REGH_SETTING2_CRC;

			//Disable packet mode and enable infinity mode
			_ARM_REG8(N8LPLD, H, SETTING1) &= ~_ARM_N8LPLD_REGH_SETTING1_PACKET_MODE;
			_ARM_REG8(N8LPLD, H, SETTING1) |= _ARM_N8LPLD_REGH_SETTING1_INFINITY_MODE;
		}
		else //Disable infinity mode and enable packet mode
		{
			_ARM_REG8(N8LPLD, H, SETTING1) &= ~_ARM_N8LPLD_REGH_SETTING1_INFINITY_MODE;
			_ARM_REG8(N8LPLD, H, SETTING1) |= _ARM_N8LPLD_REGH_SETTING1_PACKET_MODE;
		}
		
		return ARM_ERR_NONE;
	}
	#endif
	
	return ARM_ERR_BAD_TYPE;
}

bool armIsEnableInfinityMode(arm_t *arm)
{
	#ifndef ARM_WITHOUT_N8_LPLD
	_ARM_IMP2(N8_LP, N8_LD)
	{
		return (_ARM_REG8(N8LPLD, H, SETTING1)&_ARM_N8LPLD_REGH_SETTING1_INFINITY_MODE)?true:false;
	}
	#endif
	
	return false;
}

void armEnableWhitening(arm_t *arm, bool enable)
{
	#ifndef ARM_WITHOUT_N8_LPLD
	_ARM_IMP2(N8_LP, N8_LD)
	{
		if(enable)//Enable whitening
			_ARM_REG8(N8LPLD, H, SETTING2) |= _ARM_N8LPLD_REGH_SETTING2_WHITENING;
		else //Disable whitening
			_ARM_REG8(N8LPLD, H, SETTING2) &= ~_ARM_N8LPLD_REGH_SETTING2_WHITENING;
	}
	#endif
}

bool armIsEnableWhitening(arm_t *arm)
{
	#ifndef ARM_WITHOUT_N8_LPLD
	_ARM_IMP2(N8_LP, N8_LD)
	{
		return (_ARM_REG8(N8LPLD, H, SETTING2)&_ARM_N8LPLD_REGH_SETTING2_WHITENING)?true:false;
	}
	#endif
	
	return false;
}

armError_t armSetSerial(arm_t* arm, armPortBaudrate_t baud, armPortDatabits_t databits, armPortParity_t parity, armPortStopbit_t stopbit)
{	
	#ifndef ARM_WITHOUT_N8_LPLD
	_ARM_IMP2(N8_LP, N8_LD)
	{
		//Check if baud is compatible with wake up on uart if enable.
		if(_ARM_REG8(N8LPLD, H, WAKE_UP_PWR)&_ARM_N8LPLD_REGH_WAKE_UP_PWR_UART &&
			baud > ARMPORT_BAUDRATE_38400)
			return ARM_ERR_PARAM_OUT_OF_RANGE;
		
		//Set baudrate
		switch(baud)
		{
			case 1200:
				_ARM_REG8(N8LPLD, H, SERIAL_BAUDRATE) = _ARM_N8LPLD_REGH_SERIAL_BAUDRATE_1200;
			break;
			
			case 2400:	                  
				_ARM_REG8(N8LPLD, H, SERIAL_BAUDRATE) = _ARM_N8LPLD_REGH_SERIAL_BAUDRATE_2400;
			break;
			
			case 4800:	                  
				_ARM_REG8(N8LPLD, H, SERIAL_BAUDRATE) = _ARM_N8LPLD_REGH_SERIAL_BAUDRATE_4800;
			break;
			
			case 9600:	                  
				_ARM_REG8(N8LPLD, H, SERIAL_BAUDRATE) = _ARM_N8LPLD_REGH_SERIAL_BAUDRATE_9600;
			break;
			
			case 19200:	                  
				_ARM_REG8(N8LPLD, H, SERIAL_BAUDRATE) = _ARM_N8LPLD_REGH_SERIAL_BAUDRATE_19200;
			break;
			
			case 38400:	                  
				_ARM_REG8(N8LPLD, H, SERIAL_BAUDRATE) = _ARM_N8LPLD_REGH_SERIAL_BAUDRATE_38400;
			break;
			
			case 57600:	                  
				_ARM_REG8(N8LPLD, H, SERIAL_BAUDRATE) = _ARM_N8LPLD_REGH_SERIAL_BAUDRATE_57600;
			break;
			
			case 115200:	              
				_ARM_REG8(N8LPLD, H, SERIAL_BAUDRATE) = _ARM_N8LPLD_REGH_SERIAL_BAUDRATE_115200;
			break;
			
			case 230400:	              
				_ARM_REG8(N8LPLD, H, SERIAL_BAUDRATE) = _ARM_N8LPLD_REGH_SERIAL_BAUDRATE_230400;
			break;
			
			default:
				return ARM_ERR_PARAM_OUT_OF_RANGE;
			break;
		}
		
		//Set databits
		_ARM_REG8(N8LPLD, H, SERIAL_DATABITS) = databits;
		
		//Set databits
		switch(parity)
		{
			case ARMPORT_PARITY_ODD:
				_ARM_REG8(N8LPLD, H, SERIAL_PARITY) = _ARM_N8LPLD_REGH_SERIAL_PARITY_ODD;
			break;
			
			case ARMPORT_PARITY_EVEN:
				_ARM_REG8(N8LPLD, H, SERIAL_PARITY) = _ARM_N8LPLD_REGH_SERIAL_PARITY_EVEN;
			break;
			
			case ARMPORT_PARITY_NO:
			default:
				_ARM_REG8(N8LPLD, H, SERIAL_PARITY) = _ARM_N8LPLD_REGH_SERIAL_PARITY_NO;
			break;
		}
		
		//Set databits
		_ARM_REG8(N8LPLD, H, SERIAL_STOPBIT) = stopbit;

		return ARM_ERR_NONE;
	}
	#endif
	
	return ARM_ERR_BAD_TYPE;
}

void armGetSerial(arm_t* arm, armPortBaudrate_t* baud, armPortDatabits_t* databits, armPortParity_t* parity, armPortStopbit_t* stopbit)
{
	#ifndef ARM_WITHOUT_N8_LPLD
	_ARM_IMP2(N8_LP, N8_LD)
	{
		//Get baudrate
		if(baud)
		{
			switch(_ARM_REG8(N8LPLD, H, SERIAL_BAUDRATE))
			{
				case _ARM_N8LPLD_REGH_SERIAL_BAUDRATE_1200:
					*baud = (armPortBaudrate_t)1200;
				break;
				
				case _ARM_N8LPLD_REGH_SERIAL_BAUDRATE_2400:	                  
					*baud = (armPortBaudrate_t)2400;
				break;
				
				case _ARM_N8LPLD_REGH_SERIAL_BAUDRATE_4800:	                  
					*baud = (armPortBaudrate_t)4800;
				break;
				
				case _ARM_N8LPLD_REGH_SERIAL_BAUDRATE_9600:	                  
					*baud = (armPortBaudrate_t)9600;
				break;
				
				case _ARM_N8LPLD_REGH_SERIAL_BAUDRATE_19200:	                  
					*baud = (armPortBaudrate_t)19200;
				break;
				
				case _ARM_N8LPLD_REGH_SERIAL_BAUDRATE_38400:	                  
					*baud = (armPortBaudrate_t)38400;
				break;
				
				case _ARM_N8LPLD_REGH_SERIAL_BAUDRATE_57600:	                  
					*baud = (armPortBaudrate_t)57600;
				break;
				
				case _ARM_N8LPLD_REGH_SERIAL_BAUDRATE_115200:	              
					*baud = (armPortBaudrate_t)115200;
				break;
				
				case _ARM_N8LPLD_REGH_SERIAL_BAUDRATE_230400:	              
					*baud = (armPortBaudrate_t)230400;
				break;
				
				default:
					*baud = ARMPORT_BAUDRATE_NONE;
				break;
			}
		}
		
		//Get databits
		if(databits)
			*databits = (armPortDatabits_t)_ARM_REG8(N8LPLD, H, SERIAL_DATABITS);
		
		
		//Get parity
		if(parity)
		{
			switch(_ARM_REG8(N8LPLD, H, SERIAL_PARITY))
			{
				case _ARM_N8LPLD_REGH_SERIAL_PARITY_ODD:	              
					*parity = ARMPORT_PARITY_ODD;
				break;
				
				case _ARM_N8LPLD_REGH_SERIAL_PARITY_EVEN:	              
					*parity = ARMPORT_PARITY_EVEN;
				break;
				
				case _ARM_N8LPLD_REGH_SERIAL_PARITY_NO:
				default:
					*parity = ARMPORT_PARITY_NO;
				break;
			}
		}
		
		//Get stopbit
		if(stopbit)
			*stopbit = (armPortStopbit_t)_ARM_REG8(N8LPLD, H, SERIAL_STOPBIT);
	}
	#endif
}

armError_t armSetWorMode(arm_t* arm, armWor_t mode, uint16_t periodTime, uint16_t postTime, int8_t rssiLevel, bool filterLongPreamble)
{	
	#ifndef ARM_WITHOUT_N8_LPLD
	_ARM_IMP2(N8_LP, N8_LD)
	{
		//Disable WOR mode
		_ARM_REG8(N8LPLD, H, WAKE_UP_RF) &= ~_ARM_N8LPLD_REGH_WAKE_UP_RF_RF;
		#ifndef ARMPORT_WITH_nSLEEP
			_ARM_REG8(N8LPLD, H, WAKE_UP_PWR) &= ~_ARM_N8LPLD_REGH_WAKE_UP_PWR_UART;
		#endif
		_ARM_REG8(N8LPLD, H, SETTING1) &= ~_ARM_N8LPLD_REGH_SETTING1_LONG_PREAMBLE;
		
		//Return if disable mode.
		if(mode == ARM_WOR_DISABLE)
			return ARM_ERR_NONE;

		//periodTime out of rang?
		if(periodTime>_ARM_MAX_LONG_PREAMBLE_TIME)
			return ARM_ERR_PARAM_OUT_OF_RANGE;
		
		//postTime out of rang?
		if(postTime>_ARM_MAX_POST_TIME)
			return ARM_ERR_PARAM_OUT_OF_RANGE;
			
		//Set period time (same registers than long preamble)
		_ARM_REG16_SET(N8LPLD, H, LONG_PREAMBLE, periodTime);
		
		//Set post time
		_ARM_REG8(N8LPLD, H, POST_TIME) = postTime/10;
		
		//Enable long preamble?
		if(mode == ARM_WOR_LP)
		{
			_ARM_REG8(N8LPLD, H, SETTING1) |= _ARM_N8LPLD_REGH_SETTING1_LONG_PREAMBLE;
			return ARM_ERR_NONE;
		}

		//Enable wake up on radio
		_ARM_REG8(N8LPLD, H, WAKE_UP_RF) |= _ARM_N8LPLD_REGH_WAKE_UP_RF_RF;
		
		#ifndef ARMPORT_WITH_nSLEEP
		//Change uart baudrate if necessary
		if(_ARM_REG8(N8LPLD, H, SERIAL_BAUDRATE) > _ARM_N8LPLD_REGH_SERIAL_BAUDRATE_38400)
			_ARM_REG8(N8LPLD, H, SERIAL_BAUDRATE) = _ARM_N8LPLD_REGH_SERIAL_BAUDRATE_38400;
		//Enable wake up on uart
		_ARM_REG8(N8LPLD, H, WAKE_UP_PWR) |=  _ARM_N8LPLD_REGH_WAKE_UP_PWR_UART;
		#endif
		
		//Set WOR in CS 'Carrier Sense'?
		if(mode == ARM_WOR_CS)
		{
			_ARM_REG8(N8LPLD, H, SETTING1) |= _ARM_N8LPLD_REGH_SETTING1_WOR_CS;
			
			//Set rssi level if WOR in CS
			_ARM_REG8(N8LPLD, H, RSSI_LEVEL) = rssiLevel;
		}
		//Set WOR in PQT 'Preamble Quality Threshold'?
		else
		{
			_ARM_REG8(N8LPLD, H, SETTING1) &= ~_ARM_N8LPLD_REGH_SETTING1_WOR_CS;
		}
		
		//Enable/disable filter in long preamble
		if(filterLongPreamble)
			_ARM_REG8(N8LPLD, H, SETTING1) |= _ARM_N8LPLD_REGH_SETTING1_FILTER_LONG_PREAMBLE;
		else
			_ARM_REG8(N8LPLD, H, SETTING1) &= ~_ARM_N8LPLD_REGH_SETTING1_FILTER_LONG_PREAMBLE;
		
		return ARM_ERR_NONE;
	}
	#endif
	
	return ARM_ERR_BAD_TYPE;
}

void armGetWorMode(arm_t* arm, armWor_t* mode, uint16_t* periodTime, uint16_t* postTime, int8_t* rssiLevel, bool* filterLongPreamble)
{
	#ifndef ARM_WITHOUT_N8_LPLD
	_ARM_IMP2(N8_LP, N8_LD)
	{
		//Get WOR mode
		if(mode)
		{
			//WOR is enable? 
			if(_ARM_REG8(N8LPLD, H, WAKE_UP_RF)&_ARM_N8LPLD_REGH_WAKE_UP_RF_RF)
			{
				//WOR in CS 'Carrier Sense'?
				if(_ARM_REG8(N8LPLD, H, SETTING1)&_ARM_N8LPLD_REGH_SETTING1_WOR_CS)
					*mode = ARM_WOR_CS;
				else//WOR in PQT 'Preamble Quality Threshold'?
					*mode = ARM_WOR_PQT;
			}
			//long preamble is enable? 
			else if(_ARM_REG8(N8LPLD, H, SETTING1)&_ARM_N8LPLD_REGH_SETTING1_LONG_PREAMBLE)
				*mode = ARM_WOR_LP;
			else //WOR is disable?
				*mode = ARM_WOR_DISABLE;
		}
		
		//Get post time
		if(postTime)
			*postTime = _ARM_REG8(N8LPLD, H, POST_TIME)*10;
		
		//Get period time
		if(periodTime)
		{
			_ARM_REG16_GET(N8LPLD, H, LONG_PREAMBLE, *periodTime);
		}
		
		//Get rssi level
		if(rssiLevel)
			*rssiLevel = _ARM_REG8(N8LPLD, H, RSSI_LEVEL);
		
		//Get filter
		if(filterLongPreamble)
			*filterLongPreamble = (_ARM_REG8(N8LPLD, H, SETTING1)&_ARM_N8LPLD_REGH_SETTING1_FILTER_LONG_PREAMBLE)?true:false;
	}
	#endif
}

armError_t armEnableWakeUpUart(arm_t *arm, bool enable)
{
	#ifndef ARM_WITHOUT_N8_LPLD
	_ARM_IMP2(N8_LP, N8_LD)
	{
		//Disable?
		if(enable == false)
		{
			#ifndef ARMPORT_WITH_nSLEEP
			//WOR is enable? 
			if(_ARM_REG8(N8LPLD, H, WAKE_UP_RF)&_ARM_N8LPLD_REGH_WAKE_UP_RF_RF)
				return ARM_ERR_WOR_ENABLE;
			#endif
			
			_ARM_REG8(N8LPLD, H, WAKE_UP_PWR) &=  ~_ARM_N8LPLD_REGH_WAKE_UP_PWR_UART;
		}
		else //Enable?
		{
			//Change uart baudrate if necessary
			if(_ARM_REG8(N8LPLD, H, SERIAL_BAUDRATE) > _ARM_N8LPLD_REGH_SERIAL_BAUDRATE_38400)
				_ARM_REG8(N8LPLD, H, SERIAL_BAUDRATE) = _ARM_N8LPLD_REGH_SERIAL_BAUDRATE_38400;
			
			_ARM_REG8(N8LPLD, H, WAKE_UP_PWR) |=  _ARM_N8LPLD_REGH_WAKE_UP_PWR_UART;
		}
		
		return ARM_ERR_NONE;
	}
	#endif
	
	return ARM_ERR_BAD_TYPE;
}

bool armIsEnableWakeUpUart(arm_t *arm)
{
	#ifndef ARM_WITHOUT_N8_LPLD
	_ARM_IMP2(N8_LP, N8_LD)
	{
		return (_ARM_REG8(N8LPLD, H, WAKE_UP_PWR)&_ARM_N8LPLD_REGH_WAKE_UP_PWR_UART)?true:false;
	}
	#endif
	
	return false;
}

#ifdef ARMPORT_WITH_nSLEEP
void armSleep(arm_t* arm, bool sleep)
{
	armPortGpioSet(arm->_port, ARMPORT_PIN_nSLEEP, !sleep);
}
#endif

armError_t armSetLbtAfaMode(arm_t *arm, armLbtAfa_t mode, int8_t rssiLevel, uint16_t nSamples, uint16_t channel2)
{
	#ifndef ARM_WITHOUT_N8_LPLD
	_ARM_IMP2(N8_LP, N8_LD)
	{
		armBaudrate_t baud;
		int8_t power;
		int8_t maxPower;
		
		//Disable LBT&AFA mode?
		if(mode == ARM_LBTAFA_DISABLE)
		{
			_ARM_REG8(N8LPLD, H, SETTING1) &= (_ARM_N8LPLD_REGH_SETTING1_LBT|_ARM_N8LPLD_REGH_SETTING1_AFA);
			return ARM_ERR_NONE;
		}
		
		//The parameter is out of range?
		if(	(channel2 < _ARM_MIN_CHANNEL) || (channel2 > _ARM_MAX_CHANNEL))
			return ARM_ERR_PARAM_OUT_OF_RANGE;
		
		//Check if the new parameters is possible
		armGetRadio(arm, NULL, &baud, &power);
		maxPower = armGetMaxRadioPower(channel2, baud);
		if(	(maxPower == -1) ||
			(power > maxPower))
			return ARM_ERR_PARAM_INCOMPATIBLE;
		
		//Enable LBT mode
		_ARM_REG8(N8LPLD, H, SETTING1) |= _ARM_N8LPLD_REGH_SETTING1_LBT;
		
		//Set rssi level
		_ARM_REG8(N8LPLD, H, RSSI_LEVEL) = rssiLevel;
		
		//Set nSamples
		_ARM_REG16_SET(N8LPLD, H, NSAMPLE, nSamples);
		
		//Enable AFA mode?
		if(mode == ARM_LBTAFA_LBTAFA)
		{
			//Set AFA mode
			_ARM_REG8(N8LPLD, H, SETTING1) |= _ARM_N8LPLD_REGH_SETTING1_AFA;
			
			//Set channel2
			_ARM_REG16_SET(N8LPLD, H, CHANNEL2, channel2);
		}
		
		return ARM_ERR_NONE;
	}
	#endif
	
	return ARM_ERR_BAD_TYPE;
}

void armGetLbtAfaMode(arm_t *arm, armLbtAfa_t* mode, int8_t* rssiLevel, uint16_t* nSamples, uint16_t* channel2)
{
	#ifndef ARM_WITHOUT_N8_LPLD
	_ARM_IMP2(N8_LP, N8_LD)
	{
		//Get LBT&AFA mode
		if(mode)
		{
			//LBT is enable?
			if(_ARM_REG8(N8LPLD, H, SETTING1)&_ARM_N8LPLD_REGH_SETTING1_LBT)
			{
				//AFA is enable?
				if(_ARM_REG8(N8LPLD, H, SETTING1)&_ARM_N8LPLD_REGH_SETTING1_AFA)
					*mode = ARM_LBTAFA_LBTAFA;
				else
					*mode = ARM_LBTAFA_LBT;
			}
			else
				*mode = ARM_LBTAFA_DISABLE;
		}
		
		//Get rssi level
		if(rssiLevel)
			*rssiLevel = _ARM_REG8(N8LPLD, H, RSSI_LEVEL);
		
		//Get nSamples
		if(nSamples)
		{
			_ARM_REG16_GET(N8LPLD, H, NSAMPLE, *nSamples);
		}
		
		//Get channel 2
		if(channel2)
		{
			_ARM_REG16_GET(N8LPLD, H, CHANNEL2, *channel2);
		}
	}
	#endif
}

void armSetLed(arm_t* arm, armLed_t led)
{
	#ifndef ARM_WITHOUT_N8_LPLD
	_ARM_IMP2(N8_LP, N8_LD)
	{
		_ARM_REG8(N8LPLD, H, ON_BOARD) &= ~(_ARM_N8LPLD_REGH_ON_BOARD_TXRX_ON|_ARM_N8LPLD_REGH_ON_BOARD_TXRX_OFF);
		
		switch(led)
		{
			case ARM_LED_OFF:
			break;
			
			case ARM_LED_OFF_RF:
				_ARM_REG8(N8LPLD, H, ON_BOARD) |= _ARM_N8LPLD_REGH_ON_BOARD_TXRX_OFF;
			break;
			
			case ARM_LED_ON_RF:
				_ARM_REG8(N8LPLD, H, ON_BOARD) |= _ARM_N8LPLD_REGH_ON_BOARD_TXRX_ON;
			break;
		}
	}
	#endif
}

armLed_t armGetLed(arm_t* arm)
{
	#ifndef ARM_WITHOUT_N8_LPLD
	_ARM_IMP2(N8_LP, N8_LD)
	{
		if(_ARM_REG8(N8LPLD, H, ON_BOARD)&_ARM_N8LPLD_REGH_ON_BOARD_TXRX_ON)
			return ARM_LED_ON_RF;
			
		if(_ARM_REG8(N8LPLD, H, ON_BOARD)&_ARM_N8LPLD_REGH_ON_BOARD_TXRX_OFF)
			return ARM_LED_OFF_RF;
			
		return ARM_LED_OFF;
	}
	#endif
	
	return ARM_LED_OFF;
}

armError_t armUpdateConfig(arm_t* arm)
{
	#ifndef ARM_WITHOUT_N8_LPLD
	_ARM_IMP2(N8_LP, N8_LD)
	{
		armError_t err = ARM_ERR_NONE;
		bool reConfigPort = false;
		int i = 0;
		
		//Find index of first registers changed.
		for(i=0; i<_ARM_N8LPLD_REGH_SIZE; i++)
		{
			if(arm->_N8LPLD.regsH[i].newVal != arm->_N8LPLD.regsH[i].val)
				break;
		}
		
		//Registers changed found?
		if(i<_ARM_N8LPLD_REGH_SIZE)
		{
			//Write S register changed to arm
			if((err = _armGoAt(arm)))
				return err;
			for(; i<_ARM_N8LPLD_REGH_SIZE; i++)
			{
				//Set the new value if the value was changed. 
				if(arm->_N8LPLD.regsH[i].newVal != arm->_N8LPLD.regsH[i].val)
				{
					if((err = _armSetReg(arm, 'H', arm->_N8LPLD.regsH[i].reg, arm->_N8LPLD.regsH[i].newVal)))
						return err;
						
					arm->_N8LPLD.regsH[i].val = arm->_N8LPLD.regsH[i].newVal;
					
					if(	(i >= _ARM_N8LPLD_IREGH_SERIAL_BAUDRATE) &&
						(i <= _ARM_N8LPLD_IREGH_SERIAL_STOPBIT))
						reConfigPort = true;
				}
			}
			if((err = _armBackAt(arm)))
				return err;
		}
		
		//Need to reconfigure the port?
		if(reConfigPort)
		{
			armPortBaudrate_t baudrate;
			armPortDatabits_t databits;
			armPortParity_t parity;
			armPortStopbit_t stopbit;
			
			armGetSerial(arm, &baudrate, &databits, &parity, &stopbit);
			if(armPortConfig(arm->_port, baudrate, databits, parity, stopbit))
				err = ARM_ERR_PORT_CONFIG;
		}
		
		return err;
	}
	#endif
	
	return ARM_ERR_BAD_TYPE;
}

ssize_t armSend(arm_t *arm, const void* buf, size_t nbyte)
{
	ssize_t nwrite = 0;
	ssize_t n = 0;
		
	#ifndef ARM_WITHOUT_N8_LPLD
	_ARM_IMP2(N8_LP, N8_LD)
	{
		int baud = 0;
		
		armGetRadio(arm, NULL, (armBaudrate_t*)&baud, NULL);
		if(baud <= 0)
			return -1;
		
		//if(infini mode disabel)
		if(1)
		{
			//Send _ARM_RF_PAYLOAD_MAX by _ARM_RF_PAYLOAD_MAX
			while((nbyte-nwrite) > _ARM_RF_PAYLOAD_MAX)
			{
				n = armPortWrite(arm->_port, buf+nwrite, _ARM_RF_PAYLOAD_MAX);
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
	}
	#endif
	
	#ifndef ARM_WITHOUT_N8_LW
	_ARM_IMP1(N8_LW)
	{
		//Send all buf
		nwrite = armPortWrite(arm->_port, buf, nbyte);
	}
	#endif
	
	return nwrite;
}

ssize_t armReceive(arm_t *arm, void* buf, size_t nbyte, int timeout)
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

uint8_t* _armUintToStr(uint64_t val, uint8_t* str, uint8_t base, int n)
{	
	int i = 0;
	int nDigit = 0;
	uint8_t tmpDigit = 0;
	
	//Convert digits
	while(val)
	{
		tmpDigit = val%base;
		
		if(tmpDigit < 10)
			str[nDigit] = '0'+tmpDigit;
		else
			str[nDigit] = 'a'+tmpDigit-10;
		
		val /= base;
		nDigit++;
	}
	
	//Switch str 
	for(i=0; i<nDigit/2; i++)
	{
		tmpDigit = str[i];
		str[i] = str[nDigit-i-1];
		str[nDigit-i-1] = tmpDigit;
	}
	
	//Add '0' if necessary
	if(nDigit < n)
	{
		int nd = n-nDigit;
		for(i=nDigit-1; i>=0; i--)
			str[i+nd] = str[i];
		for(i=0; i<nd; i++)
			str[i] = '0';
			
		nDigit = n;
	}
	
	str[nDigit] = '\0';
	return str;
}

uint64_t _armStrToUint(uint8_t* str, uint8_t base)
{	
	uint64_t val = 0;

	//Convert digits
	while(1)
	{
		
		
		if((*str >= '0') && (*str <= '9'))
		{
			val *= base;
			val += *str-'0';
		}
		else if((*str >= 'a') && (*str <= 'z'))
		{
			val *= base;
			val += (*str-'a')+10;
		}
		else if((*str >= 'A') && (*str <= 'Z'))
		{
			val *= base;
			val += (*str-'A')+10;
		}
		else
			break;
			
		str++;
	}
	
	return val;
}

ssize_t _armRead(arm_t* arm, void* buf, size_t nbyte, unsigned int timeout)
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
		
		#ifndef ARM_WITHOUT_N8_LPLD
		_ARM_IMP2(N8_LP, N8_LD)
		{
			//Check if stop read condition
			for(i=nread; i<nread+n; i++)
			{
				if(((char*)buf)[i] == '\n')
				{
					lfcount++;
					if(lfcount >= 2)
					{
						nread += n;
						return nread;
					}
				}
			}
		}
		#endif
		
		nread += n;
	}
	
	return nread;
}

ssize_t _armWriteRead(arm_t* arm, const void* tbuf, size_t tnbyte, void* rbuf, size_t rnbyte, unsigned int rtimeout)
{
	//Write
	if(armPortWrite(arm->_port, tbuf, tnbyte) != (ssize_t)tnbyte)
		return -1;
		
	//Read
	return _armRead(arm, rbuf, rnbyte, rtimeout);
}

armError_t _armGoAt(arm_t* arm)
{
	uint8_t ntry = 0;
	uint8_t buf[40];
	ssize_t nread;
	
	while(ntry < _ARM_NUMBER_OF_TRIALS_GO_AT)
	{
		ntry++;
		
		//Write '+++' for go to AT commend and read reply
		#if !defined ARM_WITHOUT_N8_LPLD && !defined ARMPORT_WITH_nBOOT
		if(arm->type&(ARM_TYPE_NONE))
		{
			nread = _armWriteRead(arm, "+++", 3, buf, sizeof buf, _ARM_N8LPLD_TIME_BOOTING/_ARM_NUMBER_OF_TRIALS_GO_AT);
			//Soit on est dans le boot du N8_LPLD ou deja en commend AT
			if(nread == 0)
			{
				_armWriteRead(arm, "ATQ\r", 4, buf, sizeof buf, _ARM_TIME_TIMEOUT);
				continue;
			}
		}
		else
		#endif
			nread = _armWriteRead(arm, "+++", 3, buf, sizeof buf, _ARM_TIME_TIMEOUT);
		
		if(nread < 0)
			return ARM_ERR_PORT_WRITE_READ;
			
		//In AT commend if timeout or receive 3 char (3*'+')
		//or if "ARM" is read.
		if(	(nread == 0) ||	(nread == 3) ||
			(memmem(buf, nread, "ARM", 3) != NULL)) 
			return ARM_ERR_NONE;
	}
	
	return ARM_ERR_ARM_GO_AT;
}

armError_t _armBackAt(arm_t* arm)
{
	uint8_t buf[32];
	ssize_t nread = 0;
	
	//Write 'ATI' or 'ATQ' for back AT commend and read reply
	#ifndef ARM_WITHOUT_N8_LPLD
	_ARM_IMP2(N8_LP, N8_LD)
	{
		nread = _armWriteRead(arm, "ATI\r", 4, buf, sizeof buf, _ARM_TIME_TIMEOUT);
	}
	#endif
	
	#ifndef ARM_WITHOUT_N8_LW
	_ARM_IMP2(NONE, N8_LW)
	{
		nread = _armWriteRead(arm, "ATQ\r", 4, buf, sizeof buf, _ARM_TIME_TIMEOUT);
	}
	#endif
	
	if(nread < 0)
		return ARM_ERR_PORT_WRITE_READ;
		
	//Check reply
	if(	(memmem(buf, nread, "QUIT SETUP", 10) == NULL) &&
		(memmem(buf, nread, "Quit setup", 10) == NULL))
	{
		return ARM_ERR_ARM_BACK_AT;
	}
		
	//Wait arm ready
	if(arm->type&(ARM_TYPE_N8_LP|ARM_TYPE_N8_LD))
		armPortDelay(_ARM_TIME_BACK_AT+_ARM_REG8(N8LPLD, H, POST_TIME)*10);
	else
		armPortDelay(_ARM_TIME_BACK_AT);
	
	return ARM_ERR_NONE;
}

armError_t _armGetReg(arm_t* arm, uint8_t type, uint8_t num, uint8_t* val)
{
	uint8_t rbuf[16];
	ssize_t nread;
	uint8_t* ptrrbuf = NULL;
	uint8_t tbuf[8] = "AT";
	
	//Create AT commend
	tbuf[2] = type;
	_armUintToStr(num, tbuf+3, _ARM_BASE_DEC, 3);
	tbuf[6] = '\r';
	
	//Write AT commend and read reply
	nread = _armWriteRead(arm, tbuf, 7, rbuf, sizeof rbuf, _ARM_TIME_TIMEOUT);
	if(nread < 0)
		return ARM_ERR_PORT_WRITE_READ;
		
	//Check the message
	tbuf[6] = '=';
	rbuf[nread] = '\0';
	ptrrbuf = (uint8_t*)memmem(rbuf, nread, tbuf+2, 5);
	if(ptrrbuf == NULL)
		return ARM_ERR_ARM_GET_REG;
		
	//Convert the value
	ptrrbuf += 5;
	if(ptrrbuf[0] == '\0' && ptrrbuf[1] == '\0')
		return ARM_ERR_ARM_GET_REG;
	*val = _armStrToUint(ptrrbuf, _ARM_BASE_HEX);
	
	return ARM_ERR_NONE;
}

armError_t _armSetReg(arm_t* arm, uint8_t type, uint8_t num, uint8_t val)
{
	uint8_t rbuf[16];
	ssize_t nread;
	uint8_t tbuf[10] = "AT";
	
	//Create AT commend
	tbuf[2] = type;
	_armUintToStr(num, tbuf+3, _ARM_BASE_DEC, 3);
	tbuf[6] = '=';
	_armUintToStr(val, tbuf+7, _ARM_BASE_HEX, 2);
	tbuf[9] = '\r';
		
	//Write AT commend and read reply
	nread = _armWriteRead(arm, tbuf, 10, rbuf, sizeof rbuf, _ARM_TIME_TIMEOUT);
	if(nread < 0)
		return ARM_ERR_PORT_WRITE_READ;
		
	//Check the message
	if(memmem(rbuf, nread, tbuf+2, 7) == NULL)
		return ARM_ERR_ARM_SET_REG;
	
	return ARM_ERR_NONE;
}

#endif //__DOXYGEN__

