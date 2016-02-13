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

// ---------------------------------------------------------------------
// Include
// ---------------------------------------------------------------------

#include "../armport.h"

#if defined(STM32L0)
	#include "stm32l0xx.h"
#elif defined(STM32L1)
	#include "stm32l1xx.h"
#elif defined(STM32L4)
	#include "stm32l4xx.h"
#elif defined(STM32F0)
	#include "stm32f0xx.h"
#elif defined(STM32F1)
	#include "stm32f1xx.h"
#elif defined(STM32F2)
	#include "stm32f2xx.h"
#elif defined(STM32F3)
	#include "stm32f3xx.h"
#elif defined(STM32F4)
	#include "stm32f4xx.h"
#elif defined(STM32F7)
	#include "stm32f7xx.h"
#else
 #error "Please select first the target STM32xx device used in your application."
#endif

// ---------------------------------------------------------------------
// Global variables
// ---------------------------------------------------------------------

UART_HandleTypeDef huartArm1;

// ---------------------------------------------------------------------
// Implementation public functions
// ---------------------------------------------------------------------

int armPortOpen(void** ptrPort)
{	
	huartArm1.Instance = *ptrPort;
	*ptrPort = &huartArm1;
	return 0;
}

int armPortConfig(void* port, 	armPortBaudrate_t baudrate,
								armPortDatabits_t databits,
								armPortParity_t parity,
								armPortStopbit_t stopbit)
{
	UART_HandleTypeDef* huart = (UART_HandleTypeDef*)port;
	
	huart->Init.BaudRate = (uint32_t)baudrate;
	
	switch(databits)
	{
		case ARMPORT_DATA_7BITS:
			huart->Init.WordLength = UART_WORDLENGTH_7B;
		break;
		
		case ARMPORT_DATA_8BITS:
			huart->Init.WordLength = UART_WORDLENGTH_8B;
		break;
	}
	
	switch(parity)
	{
		case ARMPORT_PARITY_NO:
			huart->Init.Parity = UART_PARITY_NONE;
		break;
		
		case ARMPORT_PARITY_EVEN:
			huart->Init.Parity = UART_PARITY_EVEN;
		break;
		
		case ARMPORT_PARITY_ODD:
			huart->Init.Parity = UART_PARITY_ODD;
		break;
	}
	
	switch(stopbit)
	{
		case ARMPORT_STOPBIT_1:
			huart->Init.StopBits = UART_STOPBITS_1;
		break;
		
		case ARMPORT_STOPBIT_2:
			huart->Init.StopBits = UART_STOPBITS_2;
		break;
	}

	huart->Init.Mode = UART_MODE_TX_RX;
	huart->Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart->Init.OverSampling = UART_OVERSAMPLING_16;
	huart->Init.OneBitSampling = UART_ONEBIT_SAMPLING_DISABLED ;
	huart->AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
	
	HAL_UART_Init(huart);
	return 0;
}

int armPortClose(void* port)
{
	UART_HandleTypeDef* huart = (UART_HandleTypeDef*)port;
	HAL_UART_DeInit(&huart);
	return 0;
}

int armPortWrite(void* port, const void* buf, size_t nbyte)
{	
	UART_HandleTypeDef* huart = (UART_HandleTypeDef*)port;
	
	if(HAL_UART_Transmit(huart, (uint8_t*)buf, nbyte, 100) == HAL_OK)
		return nbyte;
	
	return -1;
}

int armPortRead(void* port, void* buf, size_t nbyte, unsigned int timeout)
{
	UART_HandleTypeDef* huart = (UART_HandleTypeDef*)port;
	
	HAL_StatusTypeDef status = HAL_UART_Receive(huart, buf, 1, timeout);
	
	if(status == HAL_OK)
		return 1;
	else if(status == HAL_TIMEOUT)
		return 0;

	return -1;
}

void armPortDelay(int ms)
{
	HAL_Delay(ms);
}

#if defined ARMPORT_WITH_nSLEEP || defined ARMPORT_WITH_nBOOT || defined ARMPORT_WITH_nRESET
void armPortGpioSet(void* port, armPortPin_t pin, bool val)
{
	switch(pin)
	{
		#ifdef ARMPORT_WITH_nSLEEP
		case ARMPORT_PIN_nSLEEP:
		{
			if(val)
				HAL_GPIO_WritePin(ARMPORT_SLEEP_GPIO_PORT, ARMPORT_SLEEP_PIN, GPIO_PIN_SET);
			else
				HAL_GPIO_WritePin(ARMPORT_SLEEP_GPIO_PORT, ARMPORT_SLEEP_PIN, GPIO_PIN_RESET);
		}
		break;
		#endif
		
		#ifdef ARMPORT_WITH_nRESET
		case ARMPORT_PIN_nRESET:
		{
			if(val)
			HAL_GPIO_WritePin(ARMPORT_RESET_GPIO_PORT, ARMPORT_RESET_PIN, GPIO_PIN_SET);
			else
				HAL_GPIO_WritePin(ARMPORT_RESET_GPIO_PORT, ARMPORT_RESET_PIN, GPIO_PIN_RESET);
		}
		break;
		#endif
		
		#ifdef ARMPORT_WITH_nBOOT
		case ARMPORT_PIN_nBOOT:
		{
			if(val)
			HAL_GPIO_WritePin(ARMPORT_BOOT_GPIO_PORT, ARMPORT_RESET_PIN, GPIO_PIN_SET);
			else
				HAL_GPIO_WritePin(ARMPORT_BOOT_GPIO_PORT, ARMPORT_RESET_PIN, GPIO_PIN_RESET);
		}
		break;
		#endif
	}
}
#endif























