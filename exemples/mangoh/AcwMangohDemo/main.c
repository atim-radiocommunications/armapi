// ---------------------------------------------------------------------
// Created date: 26.05.2016
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
#include <legato.h>
#include <interfaces.h>
#include <arm.h>

#include "lsm6ds3.h"

// ---------------------------------------------------------------------
// Global variables
// ---------------------------------------------------------------------
le_timer_Ref_t timerRef;
arm_t myAcw;
armType_t armType;

// ---------------------------------------------------------------------
// Extern prototypes functions
// ---------------------------------------------------------------------
extern uint8_t* _armUintToStr(uint64_t val, uint8_t* str, uint8_t base, int n);

// ---------------------------------------------------------------------
// Prototypes functions
// ---------------------------------------------------------------------
void timerPeriodicEvent_init(int period);
void timerPeriodicEvent_cbh(le_timer_Ref_t timerRef);
void ConfigureGpios();
void CardDetectEventHandler(bool gpioState, void* contextPtr);
void printArmErr(armError_t err);

// ---------------------------------------------------------------------
// Implementation public functions
// ---------------------------------------------------------------------
COMPONENT_INIT
{
	LE_INFO("AcwMangohDemo: Initialising...\n");
	
	mangoh_muxCtrl_Iot0Uart1On();
	
	mangoh_iot0_gpio1_Activate();//nBoot
	mangoh_iot0_gpio2_Activate();//nReset
	mangoh_iot0_gpio3_Activate();//nSleep
	
	//Reset arm by pin
	mangoh_iot0_gpio2_Deactivate();//nReset
	usleep(10000);
	mangoh_iot0_gpio2_Activate();//nReset
	
	armError_t err = ARM_ERR_NONE;
	
	//Init armapi
	if((err=armInit(&myAcw, "/dev/ttyHSL0")) != ARM_ERR_NONE)
	{
		LE_ERROR("ARM Init failed!");
		printArmErr(err);
		exit(1);
	}
	
	//Get information from device
	armType = ARM_TYPE_NONE;
	if((err=armInfo(&myAcw, &armType, NULL, NULL, NULL, NULL)) != ARM_ERR_NONE)
	{
		LE_ERROR("ARM get info failed!");
		printArmErr(err);
		exit(1);
	}
	
	switch(armType)
	{
		case ARM_TYPE_N8_LP:
		LE_INFO("ARM_TYPE_N8_LP Detected.\n");
		break;
		
		case ARM_TYPE_N8_SFU:
		LE_INFO("ARM_TYPE_N8_SFU Detected.\n");
		break;
		
		case ARM_TYPE_N8_SFD:
		LE_INFO("ARM_TYPE_N8_SFD Detected.\n");
		break;
		
		case ARM_TYPE_N8_LD:
		LE_INFO("ARM_TYPE_N8_LD  Detected.\n");
		break;
		
		case ARM_TYPE_N8_LW:
		LE_INFO("ARM_TYPE_N8_LW Detected.\n");
		break;
		
		default:
		LE_INFO("No arm type detected.\n");
		break;
	}
	
	//If Sigfox supported print id
	if(armType == ARM_TYPE_N8_SFU)
	{
		uint8_t str[64];
		uint64_t idSfx = 0;
		idSfx = armSfxGetId(&myAcw);
		LE_INFO("idSfx:0x%s.\n", _armUintToStr(idSfx, str, 16, 8));
		
		armSetMode(&myAcw, ARM_MODE_SFX);
	}
	//If LoraWan supported print devEui
	else if(armType == ARM_TYPE_N8_LW)
	{
		//uint8_t str[64];
		//uint64_t devEui = 0;
		//armLwIds(&myAcw, NULL, &devEui, NULL, NULL, NULL, NULL);
		//LE_INFO("devEui:0x%s.\n", _armUintToStr(devEui, str, 16, 8));
		
		//Set Lora config
		armSetMode(&myAcw, ARM_MODE_LORAWAN);
		armLwSetConfirmedFrame(&myAcw, 5);
		armLwEnableOtaa(&myAcw, true);
		armLwEnableRxWindows(&myAcw, true);
		armLwEnableTxAdaptiveSpeed(&myAcw, true);
		armLwEnableDutyCycle(&myAcw, false);
		armLwEnableTxAdaptiveChannel(&myAcw, true);
		armLwEnableRx2Adaptive(&myAcw, true);
	}
	
	//Update configuration into ARM.
	if((err=armUpdateConfig(&myAcw)) != ARM_ERR_NONE)
	{
		LE_ERROR("ARM update configuration failed!");
		printArmErr(err);
		exit(1);
	}
	
	// setup the accelerometer and i2c bus
    LSM6DS3_i2cInit(LSM6DS3_DEFAULT_I2C_ADDRESS);
	LSM6DS3__init();
	LSM6DS3__begin();

	timerPeriodicEvent_init(1);
}

//Timer call back
void timerPeriodicEvent_cbh(le_timer_Ref_t timerRef)
{
	static unsigned int cmpSend = 0;
	static int liAX = 0;
	static int liAY = 0;
	static int liAZ = 0;
	
	float AX, AY, AZ;
	//float temperature;
	int iAX, iAY, iAZ;

	//Read the sensor values
	//temperature =  LSM6DS3__readTempC();
	//LE_INFO("temperature=%f", temperature);
	
	AX = LSM6DS3__readFloatAccelX();
	AY = LSM6DS3__readFloatAccelY();
	AZ = LSM6DS3__readFloatAccelZ();

	iAX = (int)(AX*10);
	iAY = (int)(AY*10);
	iAZ = (int)(AZ*10);
	
	//Print sensor values
	LE_INFO("AX=%f AY=%f AZ=%f", AX , AY , AZ);
	
	
	cmpSend++;
	//All 10s
	if(cmpSend >= 10)
	{
		//Sensor values changed ?
		if( (iAX!=liAX) ||
			(iAY!=liAY)	||
			(iAZ!=liAZ))
		{
			//Send to network
			char string[64];
			if(armGetMode(&myAcw) == ARM_MODE_SFX)
			{
				sprintf(string, "%i %i %i", iAX, iAY, iAZ);
				
			}
			else if(armGetMode(&myAcw) == ARM_MODE_LORAWAN)
			{
				sprintf(string, "AX=%f AY=%f AZ=%f", AX , AY , AZ);
				
			}
			
			armSend(&myAcw, string, strlen(string));
			printf("Send network: <%s>\n", string);
		}
			
		cmpSend = 0;
		
		//Save laser sensor values
		liAX = iAX;
		liAY = iAY;
		liAZ = iAZ;
	}
}

// This sets up the timerPeriodicEvent_cbh
void timerPeriodicEvent_init(int period)
{
	le_clk_Time_t repeatInterval;
	repeatInterval.sec = period;
	repeatInterval.usec = 0;

    timerRef = le_timer_Create ("mainLoopTimer");
	le_timer_SetHandler ( timerRef, timerPeriodicEvent_cbh);
	le_timer_SetInterval( timerRef, repeatInterval);
	le_timer_SetRepeat( timerRef, 0 )	;	// 0 is forever
	le_timer_Start( timerRef);
}

// Print arm error
void printArmErr(armError_t err)
{
	switch(err)
	{
		case ARM_ERR_NONE:
			LE_INFO("ARM_ERR_NONE: 'No error.'\n");
		break;

		case ARM_ERR_NO_SUPPORTED:
			LE_INFO("ARM_ERR_NO_SUPPORTED: 'Functionality no supported by theARM.'\n");
		break;

		case ARM_ERR_PORT_OPEN:
			LE_INFO("ARM_ERR_PORT_OPEN: 'Port Error, at the port opening.'\n");
		break;

		case ARM_ERR_PORT_CONFIG:
			LE_INFO("ARM_ERR_PORT_CONFIG: 'Port Error, at the port configuring.'\n");
		break;

		case ARM_ERR_PORT_READ:
			LE_INFO("ARM_ERR_PORT_READ: 'Port Error, at the port reading.'\n");
		break;

		case ARM_ERR_PORT_WRITE:
			LE_INFO("ARM_ERR_PORT_WRITE: 'Port Error, at the port writing.'\n");
		break;

		case ARM_ERR_PORT_WRITE_READ:
			LE_INFO("ARM_ERR_PORT_WRITE_READ: 'Port Error, at the port reading/writing.'\n");
		break;

		case ARM_ERR_PORT_CLOSE:
			LE_INFO("ARM_ERR_PORT_CLOSE: 'Port Error, at the port closing.'\n");
		break;

		case ARM_ERR_PARAM_OUT_OF_RANGE:
			LE_INFO("ARM_ERR_PARAM_OUT_OF_RANGE: 'Error, one or more of parameters is out of range.'\n");
		break;

		case ARM_ERR_PARAM_INCOMPATIBLE:
			LE_INFO("ARM_ERR_PARAM_INCOMPATIBLE: 'Error, the parameters is incompatible between them.'\n");
		break;

		case ARM_ERR_ADDRESSING_NOT_ENABLE:
			LE_INFO("ARM_ERR_ADDRESSING_NOT_ENABLE: 'Error, the addressing is not enable.'\n");
		break;

		case ARM_ERR_WOR_ENABLE:
			LE_INFO("ARM_ERR_WOR_ENABLE: 'Error, the WOR mode is enable.'\n");
		break;

		case ARM_ERR_ARM_GO_AT:
			LE_INFO("ARM_ERR_ARM_GO_AT: 'ARM command Error, can't switch to AT command.'\n");
		break;

		case ARM_ERR_ARM_BACK_AT:
			LE_INFO("ARM_ERR_ARM_BACK_AT: 'ARM command Error, can't quit AT command.'\n");
		break;

		case ARM_ERR_ARM_CMD:
			LE_INFO("ARM_ERR_ARM_CMD: 'ARM command Error, from AT command.'\n");
		break;

		case ARM_ERR_ARM_GET_REG:
			LE_INFO("ARM_ERR_ARM_GET_REG: 'ARM command Error, from get register.'\n");
		break;

		case ARM_ERR_ARM_SET_REG:
			LE_INFO("ARM_ERR_ARM_SET_REG: 'ARM command Error, from set register.'\n");
		break;

		default:
			LE_INFO("ARM_ERR_UNKNON: 'Error unknown'\n");
		break;
	}
}


