// ---------------------------------------------------------------------
// Created date: 17.11.2015
// ---------------------------------------------------------------------

/***********************************************************************

 Copyright (c) 2016 ATIM
 
 
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

// ---------------------------------------------------------------------
// Include
// ---------------------------------------------------------------------
#include "armport.h"
#include <Arduino.h>
#include <HardwareSerial.h>

// ---------------------------------------------------------------------
// Private define
// ---------------------------------------------------------------------
#ifdef ARMPORT_WITH_nSLEEP
#define _ARMPORT_PIN_nSLEEP	4
#endif
#ifdef ARMPORT_WITH_nRESET
#define _ARMPORT_PIN_nRESET 8
#endif

// ---------------------------------------------------------------------
// Implemented method
// ---------------------------------------------------------------------

ArmPort::ArmPort() : _port(0)
{
}

ArmPort::~ArmPort()
{
	Close();
}

int ArmPort::Open(void* port)
{
	if(_port)
		Close();
	
	if(!((HardwareSerial*)port))
		return -1;

	_port = port;
	
	//Init gpio
	#ifdef ARMPORT_WITH_nSLEEP
	pinMode(_ARMPORT_PIN_nSLEEP, OUTPUT);
	#endif
	#ifdef ARMPORT_WITH_nRESET
	pinMode(_ARMPORT_PIN_nRESET, OUTPUT);
	#endif
	
	return 0;
}

int ArmPort::Config(armPortBaudrate_t baudrate,
					armPortDatabits_t databits,
					armPortParity_t parity,
					armPortStopbit_t stopbit)
{
	if(_port==0)
		return -1;
	
	uint8_t config = 0;
	
	//Set data bits
	switch(databits)
	{
		case ARMPORT_DATA_7BITS:
			config += SERIAL_7N1;
		break;
		
		case ARMPORT_DATA_8BITS:
			config += SERIAL_8N1;
		break;
	}
	
	//Set parity
	switch(parity)
	{
		case ARMPORT_PARITY_NO:
			config += SERIAL_5N1;
		break;
		
		case ARMPORT_PARITY_EVEN:
			config += SERIAL_5E1;
		break;
		
		case ARMPORT_PARITY_ODD:
			config += SERIAL_5O1;
		break;
	}
	
	//Set bit stop
	switch(stopbit)
	{
		case ARMPORT_STOPBIT_1:
			config += SERIAL_5N1;
		break;
		
		case ARMPORT_STOPBIT_2:
			config += SERIAL_5N2;
		break;
	}
	
	((HardwareSerial*)_port)->begin((unsigned long)baudrate, config);
	return 0;
}

int ArmPort::Close()
{
	if(_port==0)
		return -1;
		
	((HardwareSerial*)_port)->end();
	_port = 0;
	
	//Deinit gpio
	#ifdef ARMPORT_WITH_nSLEEP
	pinMode(_ARMPORT_PIN_nSLEEP, INPUT);
	#endif
	#ifdef ARMPORT_WITH_nRESET
	pinMode(_ARMPORT_PIN_nRESET, INPUT);
	#endif
	
	return 0;
}

int ArmPort::Write(const void* buf, size_t nbyte)
{
	if(_port==0)
		return -1;
		
	return ((HardwareSerial*)_port)->write((const uint8_t*)buf, nbyte);
}

int ArmPort::Read(void* buf, size_t nbyte, unsigned int timeout)
{
	if(_port==0)
		return -1;
		
	if(nbyte == 0)
		return 0;
		
	((HardwareSerial*)_port)->setTimeout(timeout);
	return ((HardwareSerial*)_port)->readBytes((uint8_t*)buf, 1);
}

void ArmPort::Delay(unsigned int ms)
{
	delay(ms);
}

#if defined ARMPORT_WITH_nSLEEP || defined ARMPORT_WITH_nBOOT || defined ARMPORT_WITH_nRESET
void ArmPort::GpioSet(armPortPin_t pin, bool val)
{
	switch(pin)
	{
		#ifdef ARMPORT_WITH_nSLEEP
		case ARMPORT_PIN_nSLEEP:
			digitalWrite(_ARMPORT_PIN_nSLEEP, val);
		break;
		#endif
		
		#ifdef ARMPORT_WITH_nRESET
		case ARMPORT_PIN_nRESET:
			digitalWrite(_ARMPORT_PIN_nRESET, val);
		break;
		#endif
	}
}
#endif
