// ---------------------------------------------------------------------
// Created date: 09.12.2015
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

#ifndef ARM_CONST_H
#define ARM_CONST_H

//Number of H registers for N8LPLD
#define _ARM_N8LPLD_REGH_SIZE 	26
//Number of M registers for N8LW
#define _ARM_N8LW_REGM_SIZE 	3
//Number of O registers for N8LW
#define _ARM_N8LW_REGO_SIZE 	6

// ---------------------------------------------------------------------
// Constants for N8LPLD
// ---------------------------------------------------------------------

// Other values
#define _ARM_N8LPLD_TIME_BOOTING 				3500	//3.5s
#define _ARM_N8LPLD_LP_MAX_POWER				14
#define _ARM_N8LPLD_LD_MAX_POWER				27

// Index S Registers
#define _ARM_N8LPLD_IREGH_APPLICATION1 			0
#define _ARM_N8LPLD_IREGH_CHANNEL1_LSB 			1
#define _ARM_N8LPLD_IREGH_CHANNEL1_MSB 			2
#define _ARM_N8LPLD_IREGH_POWER					3
#define _ARM_N8LPLD_IREGH_RADIO_BAUDRATE 		4
#define _ARM_N8LPLD_IREGH_SERIAL_BAUDRATE 		5
#define _ARM_N8LPLD_IREGH_SERIAL_DATABITS 		6
#define _ARM_N8LPLD_IREGH_SERIAL_PARITY 		7
#define _ARM_N8LPLD_IREGH_SERIAL_STOPBIT 		8
#define _ARM_N8LPLD_IREGH_BRIDGE_SETTING 		9
#define _ARM_N8LPLD_IREGH_ON_BOARD				10
#define _ARM_N8LPLD_IREGH_CHANNEL2_LSB 			11
#define _ARM_N8LPLD_IREGH_CHANNEL2_MSB 			12
#define _ARM_N8LPLD_IREGH_RSSI_LEVEL			13
#define _ARM_N8LPLD_IREGH_NSAMPLE_LSB 			14
#define _ARM_N8LPLD_IREGH_NSAMPLE_MSB 			15
#define _ARM_N8LPLD_IREGH_USER_GAIN				16
#define _ARM_N8LPLD_IREGH_WAKE_UP_PWR			17
#define _ARM_N8LPLD_IREGH_WAKE_UP_RF			18
#define _ARM_N8LPLD_IREGH_LONG_PREAMBLE_LSB		19
#define _ARM_N8LPLD_IREGH_LONG_PREAMBLE_MSB		20
#define _ARM_N8LPLD_IREGH_POST_TIME				21
#define _ARM_N8LPLD_IREGH_REMOTE_ADDRESS 		22
#define _ARM_N8LPLD_IREGH_SETTING1				23
#define _ARM_N8LPLD_IREGH_SETTING2				24
#define _ARM_N8LPLD_IREGH_LOCAL_ADDRESS 		25

// S Registers
#define _ARM_N8LPLD_REGH_APPLICATION1 			0
#define _ARM_N8LPLD_REGH_CHANNEL1_LSB 			2
#define _ARM_N8LPLD_REGH_CHANNEL1_MSB 			3
#define _ARM_N8LPLD_REGH_POWER					4
#define _ARM_N8LPLD_REGH_RADIO_BAUDRATE 		8
#define _ARM_N8LPLD_REGH_SERIAL_BAUDRATE 		12
#define _ARM_N8LPLD_REGH_SERIAL_DATABITS 		13
#define _ARM_N8LPLD_REGH_SERIAL_PARITY 			14
#define _ARM_N8LPLD_REGH_SERIAL_STOPBIT 		15
#define _ARM_N8LPLD_REGH_BRIDGE_SETTING 		20
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
#define _ARM_N8LPLD_REGH_APPLICATION1_UART_RF			0x10
#define _ARM_N8LPLD_REGH_APPLICATION1_UART_SFX			0x50
#define _ARM_N8LPLD_REGH_APPLICATION1_UART_SFXB			0xd0
			
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
		
// Bridge setting
#define _ARM_N8LPLD_REGH_BRIDGE_SETTING_TXRF			0x02
#define _ARM_N8LPLD_REGH_BRIDGE_SETTING_RXRF			0x04
		
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
#define _ARM_N8LW_MAX_POWER			14

// O Registers no saved in arm_t structure
#define _ARM_N8LW_REGO_DEVADDR		0
#define _ARM_N8LW_SIZE_DEVADDR		4
#define _ARM_N8LW_REGO_DEVEUI		4
#define _ARM_N8LW_SIZE_DEVEUI		8
#define _ARM_N8LW_REGO_APPEUI		12
#define _ARM_N8LW_SIZE_APPEUI		8
#define _ARM_N8LW_REGO_APPKEY		20
#define _ARM_N8LW_SIZE_APPKEY		16
#define _ARM_N8LW_REGO_NWKSKEY		36
#define _ARM_N8LW_SIZE_NWKSKEY		16
#define _ARM_N8LW_REGO_APPSKEY		52
#define _ARM_N8LW_SIZE_APPSKEY		16

// O Registers
#define _ARM_N8LW_REGO_TXRX2_SF					75
#define _ARM_N8LW_REGO_POWER 					76
#define _ARM_N8LW_REGO_TXRX2_CHANNEL 			77
#define _ARM_N8LW_REGO_CONFIRMED_FRAME 			80
#define _ARM_N8LW_REGO_PORT_FIELD	 			82
#define _ARM_N8LW_REGO_CONFIG		 			83

//TxRx2 Spreading factor (O075)
#define	_ARM_N8LW_REGO_TXRX2_SF_12		0x00
#define	_ARM_N8LW_REGO_TXRX2_SF_11		0x01
#define	_ARM_N8LW_REGO_TXRX2_SF_10		0x02
#define	_ARM_N8LW_REGO_TXRX2_SF_9		0x03
#define	_ARM_N8LW_REGO_TXRX2_SF_8		0x04
#define	_ARM_N8LW_REGO_TXRX2_SF_7		0x05

//Power (O076)
#define	_ARM_N8LW_REGO_POWER_UNUSED		0x00
#define	_ARM_N8LW_REGO_POWER_14			0x01
#define	_ARM_N8LW_REGO_POWER_11			0x02
#define	_ARM_N8LW_REGO_POWER_8			0x03
#define	_ARM_N8LW_REGO_POWER_5			0x04
#define	_ARM_N8LW_REGO_POWER_2			0x05

//Config (O083)
#define	_ARM_N8LW_REGO_CONFIG_OTAA				0x01
#define	_ARM_N8LW_REGO_CONFIG_RX_ON				0x02
#define	_ARM_N8LW_REGO_CONFIG_ADAPTIVE_SPEED	0x04
#define	_ARM_N8LW_REGO_CONFIG_DUTY_CYCLE		0x08
#define	_ARM_N8LW_REGO_CONFIG_ADAPTIVE_CHANNEL	0x10
#define	_ARM_N8LW_REGO_CONFIG_ADAPTIVE_RX2		0x20

// Index O Registers
#define _ARM_N8LW_IREGO_TXRX2_SF				0
#define _ARM_N8LW_IREGO_POWER 					1
#define _ARM_N8LW_IREGO_TXRX2_CHANNEL 			2
#define _ARM_N8LW_IREGO_CONFIRMED_FRAME 		3
#define _ARM_N8LW_IREGO_PORT_FIELD	 			4
#define _ARM_N8LW_IREGO_CONFIG		 			5

// Index M Registers
#define _ARM_N8LW_IREGM_CONFIGURATION 			0
#define _ARM_N8LW_IREGM_LOW_POWER 				1
#define _ARM_N8LW_IREGM_LED			 			2

// M Registers
#define _ARM_N8LW_REGM_CONFIGURATION 			0
#define _ARM_N8LW_REGM_LOW_POWER 				1
#define _ARM_N8LW_REGM_LED			 			2

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
