// ---------------------------------------------------------------------
// Created date: 22.09.2016
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
#include <stdlib.h>
#include <stdio.h>
#include <arm.h>

// ---------------------------------------------------------------------
// Prototype functions
// ---------------------------------------------------------------------
void printArmErr(armError_t err);

// ---------------------------------------------------------------------
// Implemented functions
// ---------------------------------------------------------------------
int main()
{
	arm_t myArm;
	armType_t armType;
	armError_t err = ARM_ERR_NONE;
	uint8_t rev[16] = "";
	uint64_t sn = 0;
	uint16_t rfFreq = 0;
	uint8_t rfPower = 0;
	
	//Init armapi
	err=armInit(&myArm, TTY);
	if(err != ARM_ERR_NONE)
	{
		printf("ARM Init failed!\n");
		printArmErr(err);
		armDeInit(&myArm);
		return 1;
	}
	
	//Get information from device
	err=armInfo(&myArm, &armType, rev, &sn, &rfFreq, &rfPower);
	if(err != ARM_ERR_NONE)
	{
		printf("ARM get info failed!\n");
		printArmErr(err);
		armDeInit(&myArm);
		return 1;
	}
	
	//Print information
	switch(armType)
	{
		case ARM_TYPE_N8_LP:
		printf("ARM_TYPE_N8_LP Detected.\n");
		break;
		
		case ARM_TYPE_N8_LD:
		printf("ARM_TYPE_N8_LD Detected.\n");
		break;
		
		case ARM_TYPE_N8_LW:
		printf("ARM_TYPE_N8_LW Detected.\n");
		break;
		
		default:
		printf("No arm type detected.\n");
		break;
	}
	
	if(armType != ARM_TYPE_NONE)
	{
		printf("Revision name: %s\n", rev);
		printf("Serial number: 0x%x\n", (unsigned int)sn);
		printf("Radio frequency band: %u MHz\n", rfFreq);
		printf("Radio max power: %u dBm\n", rfPower);
	}
	
	//DeInit armapi
	err = armDeInit(&myArm);
	if(err != ARM_ERR_NONE)
	{
		printf("ARM DeInit failed!\n");
		printArmErr(err);
		return 1;
	}
	
	return 0;
}

// Print arm error
void printArmErr(armError_t err)
{
	switch(err)
	{
		case ARM_ERR_NONE:
			printf("ARM_ERR_NONE: 'No error.'\n");
		break;

		case ARM_ERR_NO_SUPPORTED:
			printf("ARM_ERR_NO_SUPPORTED: 'Functionality no supported by theARM.'\n");
		break;

		case ARM_ERR_PORT_OPEN:
			printf("ARM_ERR_PORT_OPEN: 'Port Error, at the port opening.'\n");
		break;

		case ARM_ERR_PORT_CONFIG:
			printf("ARM_ERR_PORT_CONFIG: 'Port Error, at the port configuring.'\n");
		break;

		case ARM_ERR_PORT_READ:
			printf("ARM_ERR_PORT_READ: 'Port Error, at the port reading.'\n");
		break;

		case ARM_ERR_PORT_WRITE:
			printf("ARM_ERR_PORT_WRITE: 'Port Error, at the port writing.'\n");
		break;

		case ARM_ERR_PORT_WRITE_READ:
			printf("ARM_ERR_PORT_WRITE_READ: 'Port Error, at the port reading/writing.'\n");
		break;

		case ARM_ERR_PORT_CLOSE:
			printf("ARM_ERR_PORT_CLOSE: 'Port Error, at the port closing.'\n");
		break;

		case ARM_ERR_PARAM_OUT_OF_RANGE:
			printf("ARM_ERR_PARAM_OUT_OF_RANGE: 'Error, one or more of parameters is out of range.'\n");
		break;

		case ARM_ERR_PARAM_INCOMPATIBLE:
			printf("ARM_ERR_PARAM_INCOMPATIBLE: 'Error, the parameters is incompatible between them.'\n");
		break;

		case ARM_ERR_ADDRESSING_NOT_ENABLE:
			printf("ARM_ERR_ADDRESSING_NOT_ENABLE: 'Error, the addressing is not enable.'\n");
		break;

		case ARM_ERR_WOR_ENABLE:
			printf("ARM_ERR_WOR_ENABLE: 'Error, the WOR mode is enable.'\n");
		break;

		case ARM_ERR_ARM_GO_AT:
			printf("ARM_ERR_ARM_GO_AT: 'ARM commend Error, can't switch to AT commend.'\n");
		break;

		case ARM_ERR_ARM_BACK_AT:
			printf("ARM_ERR_ARM_BACK_AT: 'ARM commend Error, can't quit AT commend.'\n");
		break;

		case ARM_ERR_ARM_CMD:
			printf("ARM_ERR_ARM_CMD: 'ARM commend Error, from AT commend.'\n");
		break;

		case ARM_ERR_ARM_GET_REG:
			printf("ARM_ERR_ARM_GET_REG: 'ARM commend Error, from get register.'\n");
		break;

		case ARM_ERR_ARM_SET_REG:
			printf("ARM_ERR_ARM_SET_REG: 'ARM commend Error, from set register.'\n");
		break;

		default:
			printf("ARM_ERR_UNKNON: 'Error unknown'\n");
		break;
	}
}