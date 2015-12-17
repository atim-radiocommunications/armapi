// ---------------------------------------------------------------------
// Created date: 09.12.2015
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

#ifndef ARM_CONST_H
#define ARM_CONST_H

// ---------------------------------------------------------------------
// Constants for N8LPLD
// ---------------------------------------------------------------------

// Other values
#define _ARM_N8LPLD_TIME_BOOTING 				3500	//3.5s
#define _ARM_N8LPLD_LP_MAX_POWER				14
#define _ARM_N8LPLD_LD_MAX_POWER				27

// Index S Registers
#define _ARM_N8LPLD_IREGH_APPLICATION 			0
#define _ARM_N8LPLD_IREGH_CHANNEL1_LSB 			1
#define _ARM_N8LPLD_IREGH_CHANNEL1_MSB 			2
#define _ARM_N8LPLD_IREGH_POWER					3
#define _ARM_N8LPLD_IREGH_RADIO_BAUDRATE 		4
#define _ARM_N8LPLD_IREGH_SERIAL_BAUDRATE 		5
#define _ARM_N8LPLD_IREGH_SERIAL_DATABITS 		6
#define _ARM_N8LPLD_IREGH_SERIAL_PARITY 		7
#define _ARM_N8LPLD_IREGH_SERIAL_STOPBIT 		8
#define _ARM_N8LPLD_IREGH_ON_BOARD				9
#define _ARM_N8LPLD_IREGH_CHANNEL2_LSB 			10
#define _ARM_N8LPLD_IREGH_CHANNEL2_MSB 			11
#define _ARM_N8LPLD_IREGH_RSSI_LEVEL			12
#define _ARM_N8LPLD_IREGH_NSAMPLE_LSB 			13
#define _ARM_N8LPLD_IREGH_NSAMPLE_MSB 			14
#define _ARM_N8LPLD_IREGH_USER_GAIN				15
#define _ARM_N8LPLD_IREGH_WAKE_UP_PWR			16
#define _ARM_N8LPLD_IREGH_WAKE_UP_RF			17
#define _ARM_N8LPLD_IREGH_LONG_PREAMBLE_LSB		18
#define _ARM_N8LPLD_IREGH_LONG_PREAMBLE_MSB		19
#define _ARM_N8LPLD_IREGH_POST_TIME				20
#define _ARM_N8LPLD_IREGH_REMOTE_ADDRESS 		21
#define _ARM_N8LPLD_IREGH_SETTING1				22
#define _ARM_N8LPLD_IREGH_SETTING2				23
#define _ARM_N8LPLD_IREGH_LOCAL_ADDRESS 		24

// S Registers
#define _ARM_N8LPLD_REGH_APPLICATION 			0
#define _ARM_N8LPLD_REGH_CHANNEL1_LSB 			2
#define _ARM_N8LPLD_REGH_CHANNEL1_MSB 			3
#define _ARM_N8LPLD_REGH_POWER					4
#define _ARM_N8LPLD_REGH_RADIO_BAUDRATE 		8
#define _ARM_N8LPLD_REGH_SERIAL_BAUDRATE 		12
#define _ARM_N8LPLD_REGH_SERIAL_DATABITS 		13
#define _ARM_N8LPLD_REGH_SERIAL_PARITY 			14
#define _ARM_N8LPLD_REGH_SERIAL_STOPBIT 		15
#define _ARM_N8LPLD_REGH_ON_BOARD				25
#define _ARM_N8LPLD_REGH_CHANNEL2_LSB 			26
#define _ARM_N8LPLD_REGH_CHANNEL2_MSB 			27
#define _ARM_N8LPLD_REGH_RSSI_LEVEL				32
#define _ARM_N8LPLD_REGH_NSAMPLE_LSB 			43
#define _ARM_N8LPLD_REGH_NSAMPLE_MSB 			44
#define _ARM_N8LPLD_REGH_USER_GAIN				61
#define _ARM_N8LPLD_REGH_WAKE_UP_PWR			62
#define _ARM_N8LPLD_REGH_WAKE_UP_RF				63
#define _ARM_N8LPLD_REGH_LONG_PREAMBLE_LSB		64
#define _ARM_N8LPLD_REGH_LONG_PREAMBLE_MSB		65
#define _ARM_N8LPLD_REGH_POST_TIME				66
#define _ARM_N8LPLD_REGH_REMOTE_ADDRESS 		90
#define _ARM_N8LPLD_REGH_SETTING1				92
#define _ARM_N8LPLD_REGH_SETTING2				93
#define _ARM_N8LPLD_REGH_LOCAL_ADDRESS	 		97

// Radio Application values
#define _ARM_N8LPLD_REGH_APPLICATION_UART_RF			0x10
			
// Radio baudrate values	
#define _ARM_N8LPLD_REGH_RADIO_BAUDRATE_1200			0x01
#define _ARM_N8LPLD_REGH_RADIO_BAUDRATE_2400			0x02
#define _ARM_N8LPLD_REGH_RADIO_BAUDRATE_4800			0x03
#define _ARM_N8LPLD_REGH_RADIO_BAUDRATE_9600			0x04
#define _ARM_N8LPLD_REGH_RADIO_BAUDRATE_19200			0x05
#define _ARM_N8LPLD_REGH_RADIO_BAUDRATE_38400			0x06
#define _ARM_N8LPLD_REGH_RADIO_BAUDRATE_57600			0x07
#define _ARM_N8LPLD_REGH_RADIO_BAUDRATE_115200			0x08
			
// Serial baudrate values	
#define _ARM_N8LPLD_REGH_SERIAL_BAUDRATE_1200			0x00
#define _ARM_N8LPLD_REGH_SERIAL_BAUDRATE_2400			0x01
#define _ARM_N8LPLD_REGH_SERIAL_BAUDRATE_4800			0x02
#define _ARM_N8LPLD_REGH_SERIAL_BAUDRATE_9600			0x03
#define _ARM_N8LPLD_REGH_SERIAL_BAUDRATE_19200			0x04
#define _ARM_N8LPLD_REGH_SERIAL_BAUDRATE_38400			0x05
#define _ARM_N8LPLD_REGH_SERIAL_BAUDRATE_57600			0x06
#define _ARM_N8LPLD_REGH_SERIAL_BAUDRATE_115200			0x07
#define _ARM_N8LPLD_REGH_SERIAL_BAUDRATE_230400			0x08
		
// Serial parity values
#define _ARM_N8LPLD_REGH_SERIAL_PARITY_ODD				0x01
#define _ARM_N8LPLD_REGH_SERIAL_PARITY_EVEN				0x03
#define _ARM_N8LPLD_REGH_SERIAL_PARITY_NO				0x02
		
// Power values
#define	_ARM_N8LPLD_REGH_POWER_USER_GAIN				0xff
#define	_ARM_N8LPLD_REGH_POWER_LIMIT					0x00
		
// Setting 1 values
#define	_ARM_N8LPLD_REGH_SETTING1_LBT					0x01
#define	_ARM_N8LPLD_REGH_SETTING1_AFA					0x02
#define	_ARM_N8LPLD_REGH_SETTING1_LONG_PREAMBLE			0x04
#define	_ARM_N8LPLD_REGH_SETTING1_WOR_CS				0x08
#define	_ARM_N8LPLD_REGH_SETTING1_FILTER_LONG_PREAMBLE	0x10
#define	_ARM_N8LPLD_REGH_SETTING1_PACKET_MODE			0x40
#define	_ARM_N8LPLD_REGH_SETTING1_INFINITY_MODE			0x80
		
// Setting 2 values
#define	_ARM_N8LPLD_REGH_SETTING2_WHITENING				0x10
#define	_ARM_N8LPLD_REGH_SETTING2_CRC					0x20
#define	_ARM_N8LPLD_REGH_SETTING2_LONG_HEADRE			0x40
		
// On board values
#define	_ARM_N8LPLD_REGH_ON_BOARD_TXRX_ON				0x01
#define	_ARM_N8LPLD_REGH_ON_BOARD_TXRX_OFF				0x02
		
// Wake up pwr values
#define _ARM_N8LPLD_REGH_WAKE_UP_PWR_UART				0x10
#define _ARM_N8LPLD_REGH_WAKE_UP_PWR_INT0				0x80
		
// Wake up rf values
#define _ARM_N8LPLD_REGH_WAKE_UP_RF_RF					0x80

// ---------------------------------------------------------------------
// Constants for N8LW
// ---------------------------------------------------------------------

// Other values
#define _ARM_N8LW_MAX_POWER		14

// Index M Registers
#define _ARM_N8LW_IREGM_CONFIGURATION 			0
#define _ARM_N8LW_IREGM_LOW_POWER 				1
#define _ARM_N8LW_IREGM_CHANNEL1_LED 			2

// M Registers
#define _ARM_N8LW_REGM_CONFIGURATION 			0
#define _ARM_N8LW_REGM_LOW_POWER 				1
#define _ARM_N8LW_REGM_CHANNEL1_LED 			2

// Configuration (M000)
#define	_ARM_N8LW_REGM_CONFIGURATION_TYPE_NETWORK		0x01
#define	_ARM_N8LW_REGM_CONFIGURATION_MODULATION_LORA	0x02
#define	_ARM_N8LW_REGM_CONFIGURATION_CLASS_B			0x04
#define	_ARM_N8LW_REGM_CONFIGURATION_CLASS_C			0x08
#define	_ARM_N8LW_REGM_CONFIGURATION_CLASS_MASK			0x0c

// Low power (M001)
#define	_ARM_N8LW_REGM_LOW_POWER_ENABLE					0x01

// LED (M002)
#define	_ARM_N8LW_REGM_LED_BOOT							0x01
#define	_ARM_N8LW_REGM_LED_WAKEUP						0x02
#define	_ARM_N8LW_REGM_LED_RADIO_TX						0x04
#define	_ARM_N8LW_REGM_LED_RADIO_RX						0x08
#define	_ARM_N8LW_REGM_LED_DEFAULT_STATE				0x10


#endif //ARM_CONST_H
