// ---------------------------------------------------------------------
// This file is a example for use the library armapi with
// ARM NANO (NANO_LP with sigfox) on arduino board.
//
// This software send periodically 'Hello Sigfox' to Sigfox network.
//
// Created date: 13.02.2016
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
//Instance of  the class Arm
Arm myArm;
//The message to send at sigfox
uint8_t msg[] = "Hello Sigfox";

// ---------------------------------------------------------------------
// Implemented functions
// ---------------------------------------------------------------------

void setup()
{
	//Init Led for show error
	pinMode(LED, OUTPUT);
	digitalWrite(LED, LOW);
	
	//Init Arm and set LED to on if error
	if (myArm.Init(&Serial) != ARM_ERR_NONE)
		digitalWrite(LED, HIGH);
	
	//Set Sigfox mode in uplink.
	myArm.SetMode(ARM_MODE_SFX);
	myArm.SfxEnableDownlink(false);
	myArm.UpdateConfig();
}

void loop()
{
	unsigned int i;
	
	//Send the message to sigfox
	myArm.Send(msg, sizeof(msg)-1);
	
	//Wait 10min
	for(i=0; i<10; i++)
		delay(60000);
}
