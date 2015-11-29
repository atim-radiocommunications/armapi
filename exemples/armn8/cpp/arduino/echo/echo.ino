// ---------------------------------------------------------------------
// This file is a example for use the library armapi with
// ARM NANO (NANO_LD, NANO_LP) on arduino board.
//
// This software send 'hello world' to Sigfox network and make a radio
// echo on the radio channel 64 with 115200bps radio speed.
//
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

// ---------------------------------------------------------------------
// Include
// ---------------------------------------------------------------------
#include <armn8.h>

// ---------------------------------------------------------------------
// Define
// ---------------------------------------------------------------------
#define LED 13

// ---------------------------------------------------------------------
// Global variables
// ---------------------------------------------------------------------
//Instance of  the class Arm
ArmN8 myArm;
//The message to send everywhere
uint8_t msg[] = "Hello world\n";
//Buffer for radio echo
uint8_t buff[32];
//Number of byte in buff
ssize_t nBuff = 0;


// ---------------------------------------------------------------------
// Implemented functions
// ---------------------------------------------------------------------

void setup()
{
  //Init Led for chow error
  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);

  //Init Arm and set LED to on if error
  if (myArm.Init(&Serial) != ARMN8_ERR_NONE)
    digitalWrite(LED, HIGH);

  //Say 'hello world' to Sigfox
  myArm.DataToSigfox(msg, strlen((const char*)msg));

  //Configure radio for listen and say to all ARM
  //at the radio speed 9600 bps on the channel 4
  myArm.SetRadio(4, ARMN8_BAUDRATE_9600, ARMN8_POWER_AUTO);
  myArm.UpdateConfig();

  //Say 'hello world' to all ARM
  myArm.Send(msg, strlen((const char*)msg));
}

void loop()
{
  //Echo of receive data to all ARM
  nBuff = myArm.Receive(buff, sizeof(buff), 100);
  myArm.Send(buff, nBuff);
}
