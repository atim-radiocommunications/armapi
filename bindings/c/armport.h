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

#ifndef ARMPORT_H
#define ARMPORT_H

#ifndef __DOXYGEN__
	#ifndef __BEOS__
	#define __BEOS__
	#endif
#endif

// ---------------------------------------------------------------------
// Include
// ---------------------------------------------------------------------

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C"
{
#endif

#ifndef __DOXYGEN__
//Memories functions at to define by port
extern void bzero(void *s, size_t n);
extern void *memmem(const void *haystack, size_t haystacklen, const void *needle, size_t needlelen);
#endif

/*! \defgroup armport The port for armapi
 * 
 * All function in this group except \ref armPortGpioSet() must be 
 * implemented on you platform for use \b armapi.
 * 
 * @{
 */
 
// ---------------------------------------------------------------------
// Enum
// ---------------------------------------------------------------------

/*!	\brief Constant to define the baudrate value.
 * 
 */
typedef enum
{
	ARMPORT_BAUDRATE_NONE	= 0,		//!< That is probably a error.
	ARMPORT_BAUDRATE_1200	= 1200,		//!< 1200 bps.
	ARMPORT_BAUDRATE_2400	= 2400,		//!< 2400 bps.
	ARMPORT_BAUDRATE_4800	= 4800,		//!< 4800 bps.
	ARMPORT_BAUDRATE_9600	= 9600,		//!< 9600 bps.
	ARMPORT_BAUDRATE_19200	= 19200,	//!< 19200 bps.
	ARMPORT_BAUDRATE_38400	= 38400,	//!< 38400 bps.
	ARMPORT_BAUDRATE_57600	= 57600,	//!< 57600 bps.
	ARMPORT_BAUDRATE_115200	= 115200,	//!< 115200 bps.
	ARMPORT_BAUDRATE_230400	= 230400	//!< 230400 bps.
}armPortBaudrate_t;

/*!	\brief Constant to define the data bits value.
 * 
 */
typedef enum
{
	ARMPORT_DATA_7BITS		= 7,	//!< data of 7 bits.
	ARMPORT_DATA_8BITS		= 8		//!< data of 8 bits.
}armPortDatabits_t;

/*!	\brief Constant to define the parity type.
 * 
 */
typedef enum
{
	ARMPORT_PARITY_NO,		//!< No parity.
	ARMPORT_PARITY_ODD,		//!< ODD parity.
	ARMPORT_PARITY_EVEN		//!< Even parity.
}armPortParity_t;

/*!	\brief Constant to define the number stop bits.
 * 
 */
typedef enum
{
	ARMPORT_STOPBIT_1		= 1,	//!< 1 stop bit.
	ARMPORT_STOPBIT_2		= 2		//!< 2 stop bit.
}armPortStopbit_t;

// ---------------------------------------------------------------------
// struct
// ---------------------------------------------------------------------

#if defined ARMPORT_WITH_nSLEEP || defined ARMPORT_WITH_nBOOT || defined ARMPORT_WITH_nRESET || __DOXYGEN__
/*!	\brief Constant to define the pins.
 * 
 */
typedef enum
{
	#if defined ARMPORT_WITH_nSLEEP || __DOXYGEN__
	ARMPORT_PIN_nSLEEP,		//!< nSLEEP pin.
	#endif
	#if defined ARMPORT_WITH_nBOOT || __DOXYGEN__
	ARMPORT_PIN_nBOOT,		//!< nBOOT pin
	#endif
	#if defined ARMPORT_WITH_nRESET || __DOXYGEN__
	ARMPORT_PIN_nRESET,		//!< nRESET pin.
	#endif
}armPortPin_t;
#endif

// ---------------------------------------------------------------------
// Prototypes functions
// ---------------------------------------------------------------------

int armPortOpen(void** port);
int armPortConfig(void* port,	armPortBaudrate_t baudrate,
								armPortDatabits_t databits,
								armPortParity_t parity,
								armPortStopbit_t stopbit);
int armPortClose(void* port);

ssize_t armPortWrite(void* port, const uint8_t* buf, size_t nbyte);

ssize_t armPortRead(void* port, uint8_t* buf, size_t nbyte, unsigned int timeout);

void armPortDelay(int ms);

#if defined ARMPORT_WITH_nSLEEP || defined ARMPORT_WITH_nBOOT || defined ARMPORT_WITH_nRESET || __DOXYGEN__
void armPortGpioSet(void* port, armPortPin_t pin, bool val);
#endif

/** @}*/ //armport

#ifdef __cplusplus
}
#endif

#endif //ARMPORT_H
