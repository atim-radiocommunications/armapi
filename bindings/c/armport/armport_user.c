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

#include "../armport.h"

int armPortOpen(void** ptrPort)
{
	return 0;
}

int armPortConfig(void* port, 	armPortBaudrate_t baudrate,
								armPortDatabits_t databits,
								armPortParity_t parity,
								armPortStopbit_t stopbit)
{
	return 0;
}

int armPortClose(void* port)
{
	return 0;
}

int armPortWrite(void* port, const void* buf, size_t nbyte)
{	
	return 0;
}

int armPortRead(void* port, void* buf, size_t nbyte, unsigned int timeout)
{
	return 0;
}

void armPortDelay(int ms)
{
}

#if defined ARMPORT_WITH_nSLEEP || defined ARMPORT_WITH_nBOOT || defined ARMPORT_WITH_nRESET
void armPortGpioSet(void* port, armPortPin_t pin, bool val)
{
}
#endif

