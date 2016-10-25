// ---------------------------------------------------------------------
// Created date: 28.07.2016
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

#include <windows.h>
#include <stdio.h>

#define _ARM_PORT_SIZE_BUF_NAME_PORT	256
 
int armPortOpen(void** ptrPort)
{
	HANDLE* ptrFd = NULL;
	HANDLE fd = INVALID_HANDLE_VALUE;

	
	//Make name file
	#ifdef UNICODE
	char nameDriverNotUnicode[_ARM_PORT_SIZE_BUF_NAME_PORT];
	LPWSTR nameDriver[_ARM_PORT_SIZE_BUF_NAME_PORT];
	sprintf(nameDriverNotUnicode, "//./%s", (char*)(*ptrPort));
	MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, nameDriverNotUnicode, strlen(nameDriverNotUnicode)+1, nameDriver, _ARM_PORT_SIZE_BUF_NAME_PORT);
	#else
	LPWSTR nameDriver[_ARM_PORT_SIZE_BUF_NAME_PORT];
	sprintf((char*)nameDriver, "//./%s", (char*)(*ptrPort));
	#endif
	
	//Open serial file port
	fd = CreateFile(nameDriver, GENERIC_READ|GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	
	if (fd == INVALID_HANDLE_VALUE)
	{
		fprintf(stderr, "ERROR:%d - %s\n", GetLastError(), __func__);
		return -1;
	}
	
	//Create new HANDLE for save fd.
	ptrFd = malloc(sizeof(HANDLE));
	if(ptrFd == NULL)
	{
		fprintf(stderr, "ERROR:%d - %s\n", GetLastError(), __func__);
		return -1;
	}
	
	*ptrFd = fd;
	*ptrPort = ptrFd;
	return 0;
}

int armPortConfig(void* port, 	armPortBaudrate_t baudrate,
								armPortDatabits_t databits,
								armPortParity_t parity,
								armPortStopbit_t stopbit)
{
	//No valid pointer?
	if(port == NULL)
		return -1;
	
	HANDLE fd = *((int*)port);
	
	//struct to configure the urat port
	DCB dcbComm = {0};
	dcbComm.DCBlength = sizeof(DCB);
	
	//Get current attributes
	if(GetCommState(fd, &dcbComm) == 0)
	{
        fprintf(stderr, "ERROR:%d - %s\n", GetLastError(), __func__);
		return -1;
	}
	
    //Setup input/output/control flag
	dcbComm.fBinary = TRUE;
	dcbComm.fOutxCtsFlow = FALSE;
	dcbComm.fOutxDsrFlow = FALSE;
	dcbComm.fDtrControl = DTR_CONTROL_ENABLE;
	dcbComm.fDsrSensitivity = FALSE;
	dcbComm.fTXContinueOnXoff = FALSE;
	dcbComm.fOutX = TRUE;
	dcbComm.fInX = TRUE;
	dcbComm.fErrorChar = FALSE;
	dcbComm.fNull = FALSE;
	dcbComm.fRtsControl = RTS_CONTROL_ENABLE;
	dcbComm.fAbortOnError = FALSE;
	dcbComm.XonLim = 256;
	dcbComm.XoffLim = 256;
	dcbComm.XonChar = 17;
	dcbComm.XoffChar = 19;
	dcbComm.ErrorChar = -1;
	dcbComm.EofChar = 0;
	dcbComm.EvtChar = 0;
	
	//Set data bits
	switch(databits)
	{
		case ARMPORT_DATA_7BITS:
			dcbComm.ByteSize = 7;
		break;
		
		case ARMPORT_DATA_8BITS:
			dcbComm.ByteSize = 8;
		break;
	}
	
	//Set parity
	switch(parity)
	{
		case ARMPORT_PARITY_NO:
			dcbComm.fParity = FALSE;
			dcbComm.Parity = NOPARITY;
		break;
		
		case ARMPORT_PARITY_ODD:
			dcbComm.fParity = TRUE;
			dcbComm.Parity = ODDPARITY;
		break;
		
		case ARMPORT_PARITY_EVEN:
			dcbComm.fParity = TRUE;
			dcbComm.Parity = EVENPARITY;
		break;
	}
	
	//Set bit stop
	switch(stopbit)
	{
		case ARMPORT_STOPBIT_1:
			dcbComm.StopBits = ONESTOPBIT;
		break;
		
		case ARMPORT_STOPBIT_2:
			dcbComm.StopBits = TWOSTOPBITS;
		break;
	}
	
	//Set speed
	dcbComm.BaudRate = (DWORD)baudrate;
	
	//Set new attributes.
	if(SetCommState(fd, &dcbComm) == 0)
	{
		fprintf(stderr, "ERROR:%d - %s('%s')\n", (int)GetLastError(), __func__, name);
		return -1;
	}

	return 0;
}

int armPortClose(void* port)
{
	//No valid pointer?
	if(port == NULL)
		return -1;
		
	HANDLE fd = *((int*)port);
	
	//Close file
	if(CloseHandle(fd) == 0)
	{
		fprintf(stderr, "ERROR:%d - %s\n", (int)GetLastError(), __func__);
		return -1;
	}
	
	//Free HANDLE fd file
	fd = INVALID_HANDLE_VALUE;
	free(port);
	
	return 0;
}

int armPortWrite(void* port, const void* buf, size_t nbyte)
{
	//No valid pointer?
	if(port == NULL)
		return -1;
		
	HANDLE fd = *((int*)port);
	int n = 0;
	
	if(WriteFile(fd, (LPVOID)buf, (DWORD)nbyte, (LPDWORD)&n, NULL) == 0)
	{
		fprintf(stderr, "ERROR:%d - %s\n", (int)GetLastError(), __func__);
		return -1;
	}
	
	return n;
}

int armPortRead(void* port, void* buf, size_t nbyte, unsigned int timeout)
{
	//No valid pointer?
	if(port == NULL)
		return -1;
		
	HANDLE fd = *((int*)port);
	int nread = 0;
	
	//Set timeout.
	COMMTIMEOUTS commTimeouts;
    commTimeouts.ReadIntervalTimeout = 0;
	commTimeouts.ReadTotalTimeoutMultiplier = 0;
    commTimeouts.ReadTotalTimeoutConstant = timeout;
	commTimeouts.WriteTotalTimeoutMultiplier = 0;
	commTimeouts.WriteTotalTimeoutConstant = 0;
	
	if(SetCommTimeouts(fd, &commTimeouts) == 0)
	{
		fprintf(stderr, "ERROR:%d - %s\n", (int)GetLastError(), __func__);
		return -1;
	}

    if(ReadFile(fd, (LPVOID)buf, 1, (LPDWORD)&n, NULL) == 0)
	{
		fprintf(stderr, "ERROR:%d - %s\n", (int)GetLastError(), __func__);
		return -1;
	}
	
	return nread;
}

void armPortDelay(unsigned int ms)
{
	Sleep(ms);
}
