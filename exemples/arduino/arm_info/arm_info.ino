// ---------------------------------------------------------------------
// This file is a example for use the library armapi with
// ARM NANO (NANO_LP with sigfox and NANO_LW) with Arduino ZERO & Genuino ZERO.
//
// This software initialise armapi, get information about the ARM module
// and print this information.
//
// Created date: 23.09.2016
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
#include <arm.h>

// ---------------------------------------------------------------------
// Prototype functions
// ---------------------------------------------------------------------
void printArmErr(armError_t err);

// ---------------------------------------------------------------------
// Implemented functions
// ---------------------------------------------------------------------
void setup()
{
	//Open the USB serial port at 19200 bps for debug:
	SerialUSB.begin(19200); 
	while(!SerialUSB);
	
	//Instance of the class Arm
	Arm myArm;
	armType_t armType;
	armError_t err = ARM_ERR_NONE;
	uint8_t rev[16] = "";
	uint64_t sn = 0;
	uint16_t rfFreq = 0;
	uint8_t rfPower = 0;

	//Init armapi
	err = myArm.Init(&Serial1);
	if(err != ARM_ERR_NONE)
	{
		SerialUSB.print("ARM Init failed!\r\n");
		printArmErr(err);
		myArm.DeInit();
		return;
	}
	
	//Get information from device
	err = myArm.Info(&armType, rev, &sn, &rfFreq, &rfPower);
	if(err != ARM_ERR_NONE)
	{
		SerialUSB.print("ARM get info failed!\r\n");
		printArmErr(err);
		myArm.DeInit();
		return;
	}
	
	//Print ARM type
	switch(armType)
	{
		case ARM_TYPE_N8_LP:
		SerialUSB.print("ARM_TYPE_N8_LP Detected.\r\n");
		break;
		
		case ARM_TYPE_N8_LD:
		SerialUSB.print("ARM_TYPE_N8_LD Detected.\r\n");
		break;
		
		case ARM_TYPE_N8_LW:
		SerialUSB.print("ARM_TYPE_N8_LW Detected.\r\n");
		break;
		
		default:
		SerialUSB.print("No arm type detected.\r\n");
		break;
	}
	
	//Print information about ARM
	if(armType != ARM_TYPE_NONE)
	{
		SerialUSB.print("Revision name: ");
		SerialUSB.print((char*)rev);
		SerialUSB.print("\r\n");
		
		SerialUSB.print("Serial number: 0x");
		SerialUSB.print((unsigned int)sn, HEX);
		SerialUSB.print("\r\n");
		
		SerialUSB.print("Radio frequency band: ");
		SerialUSB.print(rfFreq, DEC);
		SerialUSB.print(" MHz\r\n");
		
		SerialUSB.print("Radio max power: ");
		SerialUSB.print(rfPower, DEC);
		SerialUSB.print(" dBm\r\n");
	}
	
	//DeInit armapi
	err = myArm.DeInit();
	if(err != ARM_ERR_NONE)
	{
		SerialUSB.print("ARM DeInit failed!\r\n");
		printArmErr(err);
		return;
	}
	
	return;
}

void loop()
{
	//Nothing to do
	delay(1);
}

// Print arm error
void printArmErr(armError_t err)
{
	switch(err)
	{
		case ARM_ERR_NONE:
			SerialUSB.print("ARM_ERR_NONE: 'No error.'\r\n");
		break;

		case ARM_ERR_NO_SUPPORTED:
			SerialUSB.print("ARM_ERR_NO_SUPPORTED: 'Functionality no supported by theARM.'\r\n");
		break;

		case ARM_ERR_PORT_OPEN:
			SerialUSB.print("ARM_ERR_PORT_OPEN: 'Port Error, at the port opening.'\r\n");
		break;

		case ARM_ERR_PORT_CONFIG:
			SerialUSB.print("ARM_ERR_PORT_CONFIG: 'Port Error, at the port configuring.'\r\n");
		break;

		case ARM_ERR_PORT_READ:
			SerialUSB.print("ARM_ERR_PORT_READ: 'Port Error, at the port reading.'\r\n");
		break;

		case ARM_ERR_PORT_WRITE:
			SerialUSB.print("ARM_ERR_PORT_WRITE: 'Port Error, at the port writing.'\r\n");
		break;

		case ARM_ERR_PORT_WRITE_READ:
			SerialUSB.print("ARM_ERR_PORT_WRITE_READ: 'Port Error, at the port reading/writing.'\r\n");
		break;

		case ARM_ERR_PORT_CLOSE:
			SerialUSB.print("ARM_ERR_PORT_CLOSE: 'Port Error, at the port closing.'\r\n");
		break;

		case ARM_ERR_PARAM_OUT_OF_RANGE:
			SerialUSB.print("ARM_ERR_PARAM_OUT_OF_RANGE: 'Error, one or more of parameters is out of range.'\r\n");
		break;

		case ARM_ERR_PARAM_INCOMPATIBLE:
			SerialUSB.print("ARM_ERR_PARAM_INCOMPATIBLE: 'Error, the parameters is incompatible between them.'\r\n");
		break;

		case ARM_ERR_ADDRESSING_NOT_ENABLE:
			SerialUSB.print("ARM_ERR_ADDRESSING_NOT_ENABLE: 'Error, the addressing is not enable.'\r\n");
		break;

		case ARM_ERR_WOR_ENABLE:
			SerialUSB.print("ARM_ERR_WOR_ENABLE: 'Error, the WOR mode is enable.'\r\n");
		break;

		case ARM_ERR_ARM_GO_AT:
			SerialUSB.print("ARM_ERR_ARM_GO_AT: 'ARM commend Error, can't switch to AT commend.'\r\n");
		break;

		case ARM_ERR_ARM_BACK_AT:
			SerialUSB.print("ARM_ERR_ARM_BACK_AT: 'ARM commend Error, can't quit AT commend.'\r\n");
		break;

		case ARM_ERR_ARM_CMD:
			SerialUSB.print("ARM_ERR_ARM_CMD: 'ARM commend Error, from AT commend.'\r\n");
		break;

		case ARM_ERR_ARM_GET_REG:
			SerialUSB.print("ARM_ERR_ARM_GET_REG: 'ARM commend Error, from get register.'\r\n");
		break;

		case ARM_ERR_ARM_SET_REG:
			SerialUSB.print("ARM_ERR_ARM_SET_REG: 'ARM commend Error, from set register.'\r\n");
		break;

		default:
			SerialUSB.print("ARM_ERR_UNKNON: 'Error unknown'\r\n");
		break;
	}
}
