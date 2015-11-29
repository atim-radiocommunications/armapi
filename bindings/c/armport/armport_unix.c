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

#include "armport.h"

#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <termios.h>
#include <errno.h>

int armPortOpen(void** ptrPort)
{
	int* ptrFd = NULL;
	int fd = 0;
	
	//Open uart file port
	fd = open(*ptrPort, O_RDWR);
	if(fd == -1)
	{
		fprintf(stderr, "ERROR - %s: %s\n", __func__, strerror(errno));
		return -1;
	}
	
	//Create new int for save fd.
	ptrFd = malloc(sizeof(int));
	if(ptrFd == NULL)
	{
		fprintf(stderr, "ERROR - %s: %s\n", __func__, strerror(errno));
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
	int fd = *((int*)port);
	
	//struct to configure the urat port
	struct termios cfg;
	
	//Get current attributes
	if(tcgetattr(fd, &cfg) == -1)
	{
		fprintf(stderr, "ERROR - %s: %s\n", __func__, strerror(errno));
		return -1;
	}
	
	//Setup input/output flag
	cfg.c_iflag = 0;
	cfg.c_oflag = OPOST;
	
	//Setup control flag
	cfg.c_cflag  = 0;
	
	//Set data bits
	switch(databits)
	{
		case ARMPORT_DATA_7BITS:
			cfg.c_cflag |= CS7;
		break;
		
		case ARMPORT_DATA_8BITS:
			cfg.c_cflag |= CS8;
		break;
	}
	
	//Set parity
	switch(parity)
	{
		case ARMPORT_PARITY_NO:
		break;
		
		case ARMPORT_PARITY_ODD:
		cfg.c_cflag |= PARODD;
		
		case ARMPORT_PARITY_EVEN:
		cfg.c_cflag |= PARENB;
		break;
	}
	
	//Set bit stop
	switch(stopbit)
	{
		case ARMPORT_STOPBIT_1:
		break;
		
		case ARMPORT_STOPBIT_2:
			cfg.c_cflag |= CSTOPB;
		break;
	}
	
	//Setup local flag
	cfg.c_lflag = 0;
	
	//Set speed
	switch(baudrate)
	{
		case ARMPORT_BAUDRATE_1200:
			cfsetispeed(&cfg, B1200);
			cfsetospeed(&cfg, B1200);
		break;
		
		case ARMPORT_BAUDRATE_2400:
			cfsetispeed(&cfg, B2400);
			cfsetospeed(&cfg, B2400);
		break;
		
		case ARMPORT_BAUDRATE_4800:
			cfsetispeed(&cfg, B4800);
			cfsetospeed(&cfg, B4800);
		break;
		
		case ARMPORT_BAUDRATE_9600:
			cfsetispeed(&cfg, B9600);
			cfsetospeed(&cfg, B9600);
		break;
		
		case ARMPORT_BAUDRATE_19200:
			cfsetispeed(&cfg, B19200);
			cfsetospeed(&cfg, B19200);
		break;
		
		case ARMPORT_BAUDRATE_38400:
			cfsetispeed(&cfg, B38400);
			cfsetospeed(&cfg, B38400);
		break;
		
		case ARMPORT_BAUDRATE_57600:
			cfsetispeed(&cfg, B57600);
			cfsetospeed(&cfg, B57600);
		break;
		
		case ARMPORT_BAUDRATE_115200:
			cfsetispeed(&cfg, B115200);
			cfsetospeed(&cfg, B115200);
		break;
		
		case ARMPORT_BAUDRATE_230400:
			cfsetispeed(&cfg, B230400);
			cfsetospeed(&cfg, B230400);
		break;
		
		default:
			return -1;
		break;
	}
	
	//Set new attributes.
	tcflush(fd, TCIOFLUSH);
	if(tcsetattr(fd, TCSANOW, &cfg) == -1)
	{
		fprintf(stderr, "ERROR - %s: %s\n", __func__, strerror(errno));
		return -1;
	}

	return 0;
}

int armPortClose(void* port)
{
	int fd = *((int*)port);
	
	//Close file
	if(close(fd) == -1)
	{
		fprintf(stderr, "ERROR - %s: %s\n", __func__, strerror(errno));
		return -1;
	}
	
	//Free int fd file
	free(port);
	
	return 0;
}

ssize_t armPortWrite(void* port, const uint8_t *buf, size_t nbyte)
{
	int fd = *((int*)port);
	int n = 0;
	
	n = write(fd, buf, nbyte);
	if(n == -1)
	{
		fprintf(stderr, "ERROR - %s: %s\n", __func__, strerror(errno));
		return -1;
	}
	
	return n;
}

ssize_t armPortRead(void* port, uint8_t *buf, size_t nbyte, unsigned int timeout)
{
	int fd = *((int*)port);
	struct timeval _timeout;
	size_t nread = 0;
	
	//Init timeout
	_timeout.tv_sec = 0;
	_timeout.tv_usec = 1000*timeout;

	//Init fd for select
	fd_set fd_read;
	FD_ZERO(&fd_read);
	FD_SET(fd, &fd_read);
	
	//Wait for reading.
	if(select(fd+1, &fd_read, NULL, NULL, &_timeout) == -1)
	{
		fprintf(stderr, "ERROR - %s: %s\n", __func__, strerror(errno));
		return -1;
	}
	
	//Read data.
	if(FD_ISSET(fd, &fd_read))
	{
		nread = read(fd, buf+nread, nbyte-nread);
		if((int)nread == -1)
		{
			fprintf(stderr, "ERROR - %s: %s\n", __func__, strerror(errno));
			return -1;
		}
	}
	// Timeout ?
	else
		return 0;
	
	return nread;
}

void armPortDelay(int ms)
{
	if(usleep(ms*1000) == -1)
		fprintf(stderr, "ERROR - %s: %s\n", __func__, strerror(errno));
}
