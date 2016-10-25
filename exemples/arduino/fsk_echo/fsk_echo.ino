// ---------------------------------------------------------------------
// This file is a example for use the library armapi with
// ARM NANO (NANO_LD, NANO_LP) on arduino board.
//
// This software make a radio echo on the radio channel 4
// with 9600bps radio speed.
//
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
#include <arm.h>

// ---------------------------------------------------------------------
// Define
// ---------------------------------------------------------------------
#define LED 13

// ---------------------------------------------------------------------
// Global variables
// ---------------------------------------------------------------------
//Instance of the class Arm
Arm myArm;
//Buffer for radio echo
uint8_t buff[32];
//Number of byte in buff
int nBuff = 0;

// ---------------------------------------------------------------------
// Implemented functions
// ---------------------------------------------------------------------

void setup()
{
	//Init Led for show error
	pinMode(LED, OUTPUT);
	digitalWrite(LED, LOW);
	
	//Init Arm and set LED to on if error
	if(myArm.Init(&Serial) != ARM_ERR_NONE)
		digitalWrite(LED, HIGH);
	
	//Set local (Fsk) mode.
	myArm.SetMode(ARM_MODE_FSK);

	//Configure radio for listen and say to all ARM
	//at the radio speed 9600 bps on the channel 4
	myArm.FskSetRadio(4, ARM_BAUDRATE_9600, ARM_FSK_POWER_AUTO);
	myArm.UpdateConfig();
}

void loop()
{
	//Echo of receive data to all ARM
	nBuff = myArm.Receive(buff, sizeof(buff), 100);
	myArm.Send(buff, nBuff);
}
