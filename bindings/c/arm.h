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

#ifndef ARM_H
#define ARM_H

// ---------------------------------------------------------------------
// Include
// ---------------------------------------------------------------------
#include <stdbool.h>

#include "armconfig.h"
#include "armport.h"

// ---------------------------------------------------------------------
// Define
// ---------------------------------------------------------------------

/*!	\brief Constant to define the broadcast value.
 * 
 * 	Value for parameter \ref armFskSetRadioRemoteAdd() function.
 */
#define ARM_FSK_BROADCAST 			255

/*!	\brief Constant to define the auto power value.
 * 
 * 	Value for parameter \p power of \ref armFskSetRadioRemoteAdd() function.
 */
#define ARM_FSK_POWER_AUTO			(-127)

/*!	\brief 
 * 
 * 	
 */
#define ARM_LW_UNCONFIRMED(val)		((-1)*(val))

/*!	\brief 
 * 
 * 	
 */
#define ARM_LW_IS_UNCONFIRMED(val)	((val)<=0)

#ifndef __DOXYGEN__
	//Number of H registers for N8LPLD
	#define _ARM_N8LPLD_REGH_SIZE 	26
	//Number of M registers for N8LW
	#define _ARM_N8LW_REGM_SIZE 	3
	//Number of O registers for N8LW
	#define _ARM_N8LW_REGO_SIZE 	6
#endif //__DOXYGEN__

// ---------------------------------------------------------------------
// Enum
// ---------------------------------------------------------------------

/*!	\brief Constant to define the errors.
 * 
 */
typedef enum
{
	ARM_ERR_NONE,					//!< No error.
	ARM_ERR_NO_SUPPORTED,			//!< Functionality no supported by the\b ARM.

	ARM_ERR_PORT_OPEN,				//!< Port Error, at the port opening.
	ARM_ERR_PORT_CONFIG,			//!< Port Error, at the port configuring.
	ARM_ERR_PORT_READ,				//!< Port Error, at the port reading.
	ARM_ERR_PORT_WRITE,				//!< Port Error, at the port writing.
	ARM_ERR_PORT_WRITE_READ,		//!< Port Error, at the port reading/writing.
	ARM_ERR_PORT_CLOSE,				//!< Port Error, at the port closing.

	ARM_ERR_PARAM_OUT_OF_RANGE,		//!< Error, one or more of parameters is out of range.
	ARM_ERR_PARAM_INCOMPATIBLE,		//!< Error, the parameters is incompatible between them.
	ARM_ERR_ADDRESSING_NOT_ENABLE,	//!< Error, the addressing is not enable.
									//!< \note To fix this error, you can enable the addressing with \ref armFskEnableAddressing() function.
	ARM_ERR_WOR_ENABLE,				//!< Error, the WOR mode is enable.
									//!< \note To fix this error, you can disable the WOR mode with \ref armFskSetWorMode() function.

	ARM_ERR_ARM_GO_AT,				//!< \b ARM commend Error, can't switch to AT commend.
	ARM_ERR_ARM_BACK_AT,			//!< \b ARM commend Error, can't quit AT commend.
	ARM_ERR_ARM_CMD,				//!< \b ARM commend Error, from AT commend.
	ARM_ERR_ARM_GET_REG,			//!< \b ARM commend Error, from get register.
	ARM_ERR_ARM_SET_REG,			//!< \b ARM commend Error, from set register.
}armError_t;

/*!	\brief Constant to define the baudrate value.
 * 
 */
typedef enum
{
	ARM_BAUDRATE_NONE		= 0,		//!< That is probably a error.
	ARM_BAUDRATE_1200		= 1200,		//!< 1200 bps.
	ARM_BAUDRATE_2400		= 2400,		//!< 2400 bps.
	ARM_BAUDRATE_4800		= 4800,		//!< 4800 bps.
	ARM_BAUDRATE_9600		= 9600,		//!< 9600 bps.
	ARM_BAUDRATE_19200		= 19200,	//!< 19200 bps.
	ARM_BAUDRATE_38400		= 38400,	//!< 38400 bps.
	ARM_BAUDRATE_57600		= 57600,	//!< 57600 bps.
	ARM_BAUDRATE_115200		= 115200,	//!< 115200 bps.
}armBaudrate_t;

/*!	\brief Constant to define the WOR mode 'Wake On Radio'.
 * 
 * \see armFskSetWorMode()
 */
typedef enum
{
	ARM_FSK_WOR_DISABLE,	//!< Disable WOR mode.
	ARM_FSK_WOR_LP,			//!< Enable long preamble for the transmitter, then wake up the receptor.
	ARM_FSK_WOR_CS,			//!< Enable WOR mode in 'Carrier Sense'.
							//!< \note The \b ARM is wake up on level rssi (choose this mode for speed).
	ARM_FSK_WOR_PQT			//!< Enable WOR mode in 'Preamble Quality Threshold'.
							//!< \note The \b ARM is wake up on the preamble (choose this mode for quality reception).
}armFskWor_t;

/*!	\brief Constant to define the comportment of the LED.
 * 
 * \see armSetLed()
 */
typedef enum
{
	ARM_LED_OFF,		//!< The LED is 'off' all the time.
	ARM_LED_OFF_RF,		//!< The LED is 'off' on RF activity and 'on' other time.
	ARM_LED_ON_RF		//!< The LED is 'on' on RF activity and 'off' other time.
}armLed_t;

/*!	\brief Constant to define the LBT&AFA mode 'Listen before talk' and 'Adaptive Frequency Agility'.
 * 
 * \see armFskSetLbtAfaMode()
 */
typedef enum
{
	ARM_FSK_LBTAFA_DISABLE,	//!< Disable all LBT&AFA mode.
	ARM_FSK_LBTAFA_LBT,		//!< Enable Listen Before Talk .
	ARM_FSK_LBTAFA_AFA,		//!< Enable Adaptive Frequency Agility, is used to receive data on one channel of the two.
	ARM_FSK_LBTAFA_LBTAFA,	//!< Enable Listen Before Talk and adaptive Frequency Agility, listen on the tow channels and talk on the free channels.
}armFskLbtAfa_t;

/*!	\brief Constant to define the working mode.
 * 
 * \see armSetMode()
 */
typedef enum
{
	ARM_MODE_LOCAL,				//!< Mode for local radio.
	ARM_MODE_SFX_NETWORK,		//!< Mode for Sigfox network.
	ARM_MODE_LORA_NETWORK,		//!< Mode for Lora network (LoRaWan).
}armMode_t;

/*!	\brief Type of \b ARM
 * 
 * \see armInfo()
 */
typedef enum
{
	ARM_TYPE_NONE	= 0x01,	//!< No \b Arm type.
	ARM_TYPE_N8_LP	= 0x02, //!< \b ARM Nano in 868MHz low power version (and Sigfox). 
	ARM_TYPE_N8_LD	= 0x04, //!< \b ARM Nano in 868MHz long distance version. 
	ARM_TYPE_N8_LW	= 0x08, //!< \b ARM Nano in 868MHz LoraWan version. 
}armType_t;

// ---------------------------------------------------------------------
// struct
// ---------------------------------------------------------------------

#ifndef __DOXYGEN__
/*!	\brief Register struct, this struct a representation one register.
 * 
 */
typedef struct
{	
	uint8_t reg;	//!< A index of register.
	uint8_t val;	//!< A value of register.
	uint8_t newVal;	//!< A new value of register.
}armReg_t;

/*!	\brief H registers for ARM_N8_LP and ARM_N8_LD
 * 
 */
typedef struct
{
	armReg_t	regsH[_ARM_N8LPLD_REGH_SIZE];
}armN8LpLd_t;

/*!	\brief H registers for ARM_N8_LP and ARM_N8_LD
 * 
 */
typedef struct
{
	armReg_t	regsM[_ARM_N8LW_REGM_SIZE];
	armReg_t	regsO[_ARM_N8LW_REGO_SIZE];
}armN8Lw_t;

/*!	\brief Arm struct.
 * 
 */
typedef struct
{
	armType_t	type;
	void* 		_port;
	union
	{
		armN8LpLd_t _N8LPLD;
		armN8Lw_t 	_N8LW;
	};
}arm_t;

/*!	\brief 128 bits variable type.
 * 
 */
typedef struct
{
	uint64_t lsb;
	uint64_t msb;
}uint128_t;
#endif

// ---------------------------------------------------------------------
// Prototypes functions
// ---------------------------------------------------------------------

/*! 
 * \brief Initialize the structure, port and \b ARM.
 * 
 * This function must be call before call other function depend of the \b arm_t structure.
 * 
 * \param arm Pointer to your \b ARM structure.
 * \param port Pointer to something which mean you serial port.
 * 
 * \return Error available:
 * 		- \ref ARM_ERR_NONE If the initialization is success.
 * 		- \ref ARM_ERR_PORT_OPEN If the port can't open.
 * 		- \ref ARM_ERR_PORT_CONFIG If the port can't is configured.
 * 		- \ref ARM_ERR_PORT_WRITE If can't write through the port.
 * 		- \ref ARM_ERR_PORT_READ If can't read through the port.
 * 		- \ref ARM_ERR_PORT_WRITE_READ If can't write or read through the port.
 * 		- \ref ARM_ERR_ARM_GO_AT If can't go to AT commend.
 * 		- \ref ARM_ERR_ARM_BACK_AT If can't back AT commend.
 * 		- \ref ARM_ERR_ARM_GET_REG If can't get register from \b ARM.
 * 		- \ref ARM_ERR_ARM_SET_REG If can't set register from \b ARM.
 */
armError_t armInit(arm_t* arm, void* port);

/*! 
 * \brief De-initialize the port.
 * 
 * \param arm Pointer to your \b ARM structure.
 * 
 * \return Error available:
 * 		- \ref ARM_ERR_NONE If the de-initialization is success.
 * 		- \ref ARM_ERR_PORT_CLOSE If the port can't close.
 */
armError_t armDeInit(arm_t* arm);

/*! 
 * \brief Reboot the \b ARM.
 * 
 * \param arm Pointer to your \b ARM structure.
 * 
 * \return Error available:
 * 		- \ref ARM_ERR_NONE If the reboot is success.
 * 		- \ref ARM_ERR_NO_SUPPORTED If there is bad \b ARM type.
 * 			Probably the \b ARM structure is not initialized.
 * 			In this case you can call \ref armInit() and check the returned error.
 * 		- \ref ARM_ERR_PORT_CONFIG If the port can't is configured.
 * 		- \ref ARM_ERR_PORT_WRITE If can't write through the port.
 * 		- \ref ARM_ERR_PORT_READ If can't read through the port.
 * 		- \ref ARM_ERR_PORT_WRITE_READ If can't write or read through the port.
 * 		- \ref ARM_ERR_ARM_GO_AT If can't go to AT commend.
 * 		- \ref ARM_ERR_ARM_BACK_AT If can't back AT commend.
 * 		- \ref ARM_ERR_ARM_GET_REG If can't get register from \b ARM.
 * 		- \ref ARM_ERR_ARM_SET_REG If can't set register from \b ARM.
 */
armError_t armReboot(arm_t* arm);

/*! 
 * \brief Get information about the \b ARM.
 * 
 * \note If you don't went get a parameter you can give the \b NULL value.
 * 
 * \param arm Pointer to your \b ARM structure.
 * \param armType If the pointer is valid, The \b ARM type is set. The possible values is:
 * 	- \ref ARM_TYPE_N8_LP For \b ARM Nano in 868MHz low power version (and Sigfox). 
 * 	- \ref ARM_TYPE_N8_LD For \b ARM Nano in 868MHz long distance version. 
 * 	- \ref ARM_TYPE_N8_LW For \b ARM Nano in 868MHz LoraWan version.
 * \param rev If the pointer is valid, the firmware version is copied.
 * This parameter must be a string buffer capacity equal or more of 16 bytes.
 * \param sn If the pointer is valid, the serial number is set.
 * This parameter is the ID Sigfox in the case where the \b ARM support the Sigfox Network.
 * \param rfFreq If the pointer is valid, the work frequency of your \b ARM is set.
 * \param rfPower If the pointer is valid, the max power supported by your \b ARM is set.
 * 
 * \return Error available:
 * 		- \ref ARM_ERR_NONE If success.
 * 		- \ref ARM_ERR_PORT_WRITE_READ If can't write or read through the port.
 * 		- \ref ARM_ERR_ARM_GO_AT If can't go to AT commend.
 * 		- \ref ARM_ERR_ARM_BACK_AT If can't back AT commend.
 */
armError_t armInfo(arm_t* arm, armType_t* armType, uint8_t* rev, uint64_t* sn, uint16_t* rfFreq, uint8_t* rfPower);

/*! 
 * \brief Set the mode.
 * 
 * \param arm Pointer to your \b ARM structure.
 * \param mode The mode, the possible value:
 * 	- \ref ARM_MODE_LOCAL To set the \b ARM in local radio mode.
 * 	- \ref ARM_MODE_SFX_NETWORK To set the \b ARM in Sigfox network mode.
 * 	- \ref ARM_MODE_LORA_NETWORK To set the \b ARM in Lora network (LoRaWan) mode.
 * 
 * \return Error available:
 * - \ref ARM_ERR_NONE If successful.
 * - \ref ARM_ERR_NO_SUPPORTED If you \b ARM don't support the mode.
 * 
 * \note You need to call \ref armUpdateConfig() to update the parameters in you \b ARM.
 * 
 * \see armGetMode()
 */
armError_t armSetMode(arm_t* arm, armMode_t mode);

/*! 
 * \brief Get the mode.
 * 
 * \param arm Pointer to your \b ARM structure.
 * \return The Mode:
 * 		- \ref ARM_MODE_LOCAL, Mode for local radio.
 * 		- \ref ARM_MODE_SFX_NETWORK, Mode for Sigfox network.
 * 		- \ref ARM_MODE_LORA_NETWORK, Mode for Lora network (LoRaWan).
 * 
 * \see armSetMode()
 */
armMode_t armGetMode(arm_t* arm);

/*! 
 * \brief Enable/Disable the Sigfox downlink.
 * 
 * This function is supported by:
 * 	- \b ARM_N8_LP, \b ARM Nano in 868Mhz Low Power (and Sigfox).
 * 
 * \param arm Pointer to your \b ARM structure.
 * \param enable \e true to enable Sigfox downlink, false to disable.
 * 
 * \return Error available:
 *	- \ref ARM_ERR_NONE If successful.
 *	- \ref ARM_ERR_NO_SUPPORTED If your \b ARM don't support this function.
 * 
 * \note You need to call \ref armUpdateConfig() to update the parameters in you \b ARM.
 * \warning In the case here Sigfox network is supporter by your \b ARM only on uplink, this
 * function don't return error.
 * 
 * \see armSfxIsEnableDownlink()
 */
armError_t armSfxEnableDownlink(arm_t* arm, bool enable);

/*! 
 * \brief Get if the Sigfox downlink is enable.
 * 
 * \note In the case where this function in not supported by your \b ARM the returned value is unfeasible.
 * 
 * This function is supported by:
 * 	- \b ARM_N8_LP, \b ARM Nano in 868Mhz Low Power (and Sigfox).
 * 
 * \param arm Pointer to your \b ARM structure.
 * \return \e true if the Sigfox downlink is enable or \e false if disable.
 * 
 * \see armSfxEnableDownlink()
 */
bool armSfxIsEnableDownlink(arm_t* arm);

/*! 
 * \brief Get The maximal possible power.
 * 
 * Get the maximal possible power of function channel and baudrate.
 * 
 * For more information, please consulate the main radio parameter page.
 * \todo Create the main parameter page.
 * 
 * \param radioChannel The radio channel.
 * \param radioBaud The radio baudrate.
 * 
 * \return The maximal power possible in dBm. -1 if no power possible.
 * 
 * \todo to implement.
 */
int8_t armFskMaxRadioPower(uint16_t radioChannel, armBaudrate_t radioBaud);

/*! 
 * \brief Setup the local radio configuration.
 * 
 * For more information, please consulate the local radio parameters page.
 * \todo Create the local parameter page.
 * 
 * This function is supported by:
 * 	- \b ARM_N8_LP, \b ARM Nano in 868Mhz Low Power (and Sigfox).
 * 	- \b ARM_N8_LD, \b ARM Nano in 868MHz Long Distance.
 * 
 * \param arm Pointer to your \b ARM structure.
 * \param channel The main radio channel.
 * - The range possible is of 1 to 559.
 * - The function, return the error \ref ARM_ERR_PARAM_OUT_OF_RANGE if this value is out of rang.
 * \param baud The radio baudrate.
 * - The function, return the error \ref ARM_ERR_PARAM_OUT_OF_RANGE if you give a another value defined below.
 * - Is possible to give a integer value. For example for \ref ARM_BAUDRATE_19200 you can directly give \b 19200.
 * - The possible value is:
 * 		- \ref ARM_BAUDRATE_1200 to 1200bps.
 * 		- \ref ARM_BAUDRATE_2400 to 2400bps.
 * 		- \ref ARM_BAUDRATE_4800 to 4800bps.
 * 		- \ref ARM_BAUDRATE_9600 to 9600bps.
 * 		- \ref ARM_BAUDRATE_19200 to 19200bps.
 * 		- \ref ARM_BAUDRATE_38400 to 38400bps.
 * 		- \ref ARM_BAUDRATE_57600 to 57600bps.
 * 		- \ref ARM_BAUDRATE_115200 to 115200bps.
 * 
 * \param power The radio output power.
 * - If you have a \b ARM in LD 'Long Distence' version the max value is 27 for 27dBm.
 * - If you have a \b ARM in LP 'Low Power' version the max value is 14 for 14dBm.
 * - The min value is -18 for -18dBm.
 * - You can passe the \ref ARM_FSK_POWER_AUTO value to set the max power according from the \p channel and \p baud parameter.
 * In this case, you can choose the \p channel and \p baud value without worry the \p power value.
 * 
 * \return Error available:
 * - \ref ARM_ERR_NONE If successful.
 * - \ref ARM_ERR_NO_SUPPORTED If your \b ARM don't support this function.
 * - \ref ARM_ERR_PARAM_OUT_OF_RANGE If one of the parameters is out of rang.
 * - \ref ARM_ERR_PARAM_INCOMPATIBLE The parameters of this function is link between them.
 * Is very important to chose the correct value. For more information, please consulate the local radio parameter page.
 * 
 * \note You need to call \ref armUpdateConfig() to update the parameters in you \b ARM.
 * 
 * \see armFskGetRadio()
 * \see armFskMaxRadioPower()
 */
armError_t armFskSetRadio(arm_t* arm, uint16_t channel, armBaudrate_t baud, int8_t power);

/*! 
 * \brief Get the local radio configuration.
 * 
 * Please, for more information about parameter consult the documentation of the \ref armFskSetRadio() function.
 * \note If you don't went get a parameter you can give the \b NULL value.
 * \note In the case where this function in not supported by your \b ARM the value of parameters is no modified.
 * 
 * This function is supported by:
 * 	- \b ARM_N8_LP, \b ARM Nano in 868Mhz Low Power (and Sigfox).
 * 	- \b ARM_N8_LD, \b ARM Nano in 868MHz Long Distance.
 * 
 * \param arm Pointer to your \b ARM structure.
 * \param channel If the pointer is valid, the \p channel is set.
 * \param baud If the pointer is valid, the \p baud is set. If \ref ARM_BAUDRATE_NONE is set, there is probably a error.
 * \param power If the pointer is valid, the \p power is set. If the power is no particularity specified, the \ref ARM_FSK_POWER_AUTO value is set.
 * 
 * \see armFskSetRadio()
 */
void armFskGetRadio(arm_t* arm, uint16_t* channel, armBaudrate_t* baud, int8_t* power);

/*! 
 * \brief Set the radio remote address.
 * 
 * This function is supported by:
 * 	- \b ARM_N8_LP, \b ARM Nano in 868Mhz Low Power (and Sigfox).
 * 	- \b ARM_N8_LD, \b ARM Nano in 868MHz Long Distance.
 * 
 * \param arm Pointer to your \b ARM structure.
 * \param add Remote address of 0 to 255. The 255 value is used for \e broadcast, the
 * macro \ref ARM_FSK_BROADCAST (255) can be used in this case.
 * 
 * \return Error available:
 * - \ref ARM_ERR_NONE If successful.
 * - \ref ARM_ERR_NO_SUPPORTED If your \b ARM don't support this function.
 * - \ref ARM_ERR_ADDRESSING_NOT_ENABLE If the addressing is not enable.
 * 
 * \note You need to call \ref armUpdateConfig() to update the parameters in you \b ARM.
 * 
 * \see armFskGetRadioRemoteAdd()
 * \see armFskSetRadioLocalAdd()
 * \see armFskEnableAddressing()
 */
armError_t armFskSetRadioRemoteAdd(arm_t* arm, uint8_t add);

/*! 
 * \brief Get the remote address.
 * 
 * \note In the case where this function in not supported by your \b ARM the returned value is unfeasible.
 * 
 * This function is supported by:
 * 	- \b ARM_N8_LP, \b ARM Nano in 868Mhz Low Power (and Sigfox).
 * 	- \b ARM_N8_LD, \b ARM Nano in 868MHz Long Distance.
 * 
 * \param arm Pointer to your \b ARM structure.
 * \return The remote address.
 * 
 * \see armFskSetRadioRemoteAdd()
 */
uint8_t armFskGetRadioRemoteAdd(arm_t* arm);

/*! 
 * \brief Set the radio local address.
 * 
 * This function is supported by:
 * 	- \b ARM_N8_LP, \b ARM Nano in 868Mhz Low Power (and Sigfox).
 * 	- \b ARM_N8_LD, \b ARM Nano in 868MHz Long Distance.
 * 
 * \param arm Pointer to your \b ARM structure.
 * \param add Local address of 0 to 255.
 * 
 * \return Error available:
 * - \ref ARM_ERR_NONE If successful.
 * - \ref ARM_ERR_NO_SUPPORTED If your \b ARM don't support this function.
 * - \ref ARM_ERR_ADDRESSING_NOT_ENABLE If the addressing is not enable.
 * 
 * \note You need to call \ref armUpdateConfig() to update the parameters in you \b ARM.
 * 
 * \see armFskGetRadioLocalAdd()
 * \see armFskSetRadioRemoteAdd()
 * \see armFskEnableAddressing()
 */
armError_t armFskSetRadioLocalAdd(arm_t* arm, uint8_t add);

/*! 
 * \brief Get the local address.
 * 
 * \note In the case where this function in not supported by your \b ARM the returned value is unfeasible.
 * 
 * This function is supported by:
 * 	- \b ARM_N8_LP, \b ARM Nano in 868Mhz Low Power (and Sigfox).
 * 	- \b ARM_N8_LD, \b ARM Nano in 868MHz Long Distance.
 * 
 * \param arm Pointer to your \b ARM structure.
 * \return The local address.
 * 
 * \see armFskSetRadioLocalAdd()
 */
uint8_t armFskGetRadioLocalAdd(arm_t* arm);

/*! 
 * \brief Enable/Disable \b Addressing.
 * 
 * \note In the case where this function in not supported by your \b ARM this functions is ignored.
 * 
 * This function is supported by:
 * 	- \b ARM_N8_LP, \b ARM Nano in 868Mhz Low Power (and Sigfox).
 * 	- \b ARM_N8_LD, \b ARM Nano in 868MHz Long Distance.
 * 
 * \param arm Pointer to your \b ARM structure.
 * \param enable \e true to enable \b Addressing or \e false to disable.
 * 
 * \note You need to call \ref armUpdateConfig() to update the parameters in you \b ARM.
 * 
 * \see armFskIsEnableAddressing()
 */
void armFskEnableAddressing(arm_t* arm, bool enable);

/*! 
 * \brief Get enable \b Addressing.
 * 
 * \note In the case where this function in not supported by your \b ARM the returned value is unfeasible.
 * 
 * This function is supported by:
 * 	- \b ARM_N8_LP, \b ARM Nano in 868Mhz Low Power (and Sigfox).
 * 	- \b ARM_N8_LD, \b ARM Nano in 868MHz Long Distance.
 * 
 * \param arm Pointer to your \b ARM structure.
 * \return \e true if the \b Addressing is enable or \e false if disable.
 * 
 * \see armFskEnableAddressing()
 */
bool armFskIsEnableAddressing(arm_t* arm);

/*! 
 * \brief Enable/Disable \b CRC.
 * 
 * \warning This functions disable automatically the \b infinity \b mode.
 * \note In the case where this function in not supported by your \b ARM this functions is ignored.
 * 
 * This function is supported by:
 * 	- \b ARM_N8_LP, \b ARM Nano in 868Mhz Low Power (and Sigfox).
 * 	- \b ARM_N8_LD, \b ARM Nano in 868MHz Long Distance.
 * 
 * \param arm Pointer to your \b ARM structure.
 * \param enable \e true to enable \b CRC or \e false to disable.
 * 
 * \note You need to call \ref armUpdateConfig() to update the parameters in you \b ARM.
 * 
 * \see armFskIsEnableCrc()
 * \see armFskEnableInfinityMode()
 */
void armFskEnableCrc(arm_t* arm, bool enable);

/*! 
 * \brief Get enable \b CRC.
 * 
 * \note In the case where this function in not supported by your \b ARM the returned value is unfeasible.
 * 
 * This function is supported by:
 * 	- \b ARM_N8_LP, \b ARM Nano in 868Mhz Low Power (and Sigfox).
 * 	- \b ARM_N8_LD, \b ARM Nano in 868MHz Long Distance.
 * 
 * \param arm Pointer to your \b ARM structure.
 * \return \e true if the \b CRC is enable or \e false if disable.
 * 
 * \see armFskEnableCrc()
 */
bool armFskIsEnableCrc(arm_t* arm);
 
/*! 
 * \brief Enable/Disable \b Infinity \b mode.
 * 
 * \warning This functions disable automatically the \b CRC.
 * 
 * This function is supported by:
 * 	- \b ARM_N8_LP, \b ARM Nano in 868Mhz Low Power (and Sigfox).
 * 	- \b ARM_N8_LD, \b ARM Nano in 868MHz Long Distance.
 * 
 * \param arm Pointer to your \b ARM structure.
 * \param enable \e true to enable \b Infinity \b mode or \e false to disable.
 * 
 * \return Error available:
 * - \ref ARM_ERR_NONE If successful.
 * - \ref ARM_ERR_NO_SUPPORTED If your \b ARM don't support this function.
 * - \ref ARM_ERR_WOR_ENABLE If the WOR mode is enable.
 * 
 * \note You need to call \ref armUpdateConfig() to update the parameters in you \b ARM.
 * 
 * \see armFskIsEnableInfinityMode()
 * \see armFskEnableCrc()
 */
armError_t armFskEnableInfinityMode(arm_t* arm, bool enable);

/*! 
 * \brief Get enable \b Infinity \b mode.
 * 
 * \note In the case where this function in not supported by your \b ARM the returned value is unfeasible.
 * 
 * This function is supported by:
 * 	- \b ARM_N8_LP, \b ARM Nano in 868Mhz Low Power (and Sigfox).
 * 	- \b ARM_N8_LD, \b ARM Nano in 868MHz Long Distance.
 * 
 * \param arm Pointer to your \b ARM structure.
 * \return \e true if the \b Infinity \b mode is enable or \e false if disable.
 * 
 * \see armFskEnableInfinityMode()
 */
bool armFskIsEnableInfinityMode(arm_t* arm);

/*! 
 * \brief Enable/Disable \b Whitening.
 * 
 * \note In the case where this function in not supported by your \b ARM this functions is ignored.
 * 
 * This function is supported by:
 * 	- \b ARM_N8_LP, \b ARM Nano in 868Mhz Low Power (and Sigfox).
 * 	- \b ARM_N8_LD, \b ARM Nano in 868MHz Long Distance.
 * 
 * \param arm Pointer to your \b ARM structure.
 * \param enable \e true to enable \b Whitening false to disable.
 * 
 * \note You need to call \ref armUpdateConfig() to update the parameters in you \b ARM.
 * 
 * \see armFskIsEnableWhitening()
 */
void armFskEnableWhitening(arm_t *arm, bool enable);

/*! 
 * \brief Get enable \b Whitening.
 * 
 * \note In the case where this function in not supported by your \b ARM the returned value is unfeasible.
 * 
 * This function is supported by:
 * 	- \b ARM_N8_LP, \b ARM Nano in 868Mhz Low Power (and Sigfox).
 * 	- \b ARM_N8_LD, \b ARM Nano in 868MHz Long Distance.
 * 
 * \param arm Pointer to your \b ARM structure.
 * \return \e true if the \b Whitening is enable or \e false if disable.
 * 
 * \see armFskEnableWhitening()
 */
bool armFskIsEnableWhitening(arm_t *arm);

/*! 
 * \brief Setup serial port configuration.
 * 
 * \warning In the case or the port don't support one of below parameters,
 * this function don't return error. But, the error
 * \ref ARM_ERR_PORT_CONFIG will return to next call \ref armUpdateConfig().
 * 
 * This function is supported by:
 * 	- \b ARM_N8_LP, \b ARM Nano in 868Mhz Low Power (and Sigfox).
 * 	- \b ARM_N8_LD, \b ARM Nano in 868MHz Long Distance.
 * 
 * \param arm Pointer to your \b ARM structure.
 * \param baud The serial baudrate.
 * - The function, return the error \ref ARM_ERR_PARAM_OUT_OF_RANGE if
 * you give a another value defined below.
 * - If the wake up on uart is enable and the \p baud parameter is bigger
 * of 38400 the \ref ARM_ERR_PARAM_OUT_OF_RANGE error is returned.
 * - Is possible to give a integer value. For example for \ref ARMPORT_BAUDRATE_19200 you can directly give \b 19200.
 * - The possible value is:
 * 		- \ref ARMPORT_BAUDRATE_1200 to 1200bps.
 * 		- \ref ARMPORT_BAUDRATE_2400 to 2400bps.
 * 		- \ref ARMPORT_BAUDRATE_4800 to 4800bps.
 * 		- \ref ARMPORT_BAUDRATE_9600 to 9600bps.
 * 		- \ref ARMPORT_BAUDRATE_19200 to 19200bps.
 * 		- \ref ARMPORT_BAUDRATE_38400 to 38400bps.
 * 		- \ref ARMPORT_BAUDRATE_57600 to 57600bps.
 * 		- \ref ARMPORT_BAUDRATE_115200 to 115200bps.
 * 		- \ref ARMPORT_BAUDRATE_230400 to 230400bps.
 * 
 * \param databits The number of data bits:
 * 		- \ref ARMPORT_DATA_7BITS 7 data bits.
 * 		- \ref ARMPORT_DATA_8BITS 8 data bits.
 * 
 * \param parity The type of parity:
 * 		- \ref ARMPORT_PARITY_NO Disable parity.
 * 		- \ref ARMPORT_PARITY_ODD Enabled, odd parity 
 * 		- \ref ARMPORT_PARITY_EVEN Enabled, even parity.
 * 
 * \param stopbit The number of stop bits:
 * 		- \ref ARMPORT_STOPBIT_1 Enable 1 stop bit.
 * 		- \ref ARMPORT_STOPBIT_2 Enable 2 stop bit.
 * 
 * \return Error available:
 * - \ref ARM_ERR_NONE If successful.
 * - \ref ARM_ERR_NO_SUPPORTED If your \b ARM don't support this function.
 * - \ref ARM_ERR_PARAM_OUT_OF_RANGE If one of the parameters is out of rang.
 * 
 * \note You need to call \ref armUpdateConfig() to update the parameters in you \b ARM.
 * 
 * \see armGetSerial()
 * \see armEnableWakeUpUart()
 */
armError_t armSetSerial(arm_t* arm, armPortBaudrate_t baud, armPortDatabits_t databits, armPortParity_t parity, armPortStopbit_t stopbit);

/*! 
 * \brief Get the serial port configuration.
 * 
 * \note If you don't went get a parameter you can give the \b NULL value.
 * \note In the case where this function in not supported by your \b ARM the value of parameters is no modified.
 * 
 * This function is supported by:
 * 	- \b ARM_N8_LP, \b ARM Nano in 868Mhz Low Power (and Sigfox).
 * 	- \b ARM_N8_LD, \b ARM Nano in 868MHz Long Distance.
 * 
 * \param arm Pointer to your \b ARM structure.
 * \param baud If the pointer is valid, the \p baud is set. If \ref ARMPORT_BAUDRATE_NONE is set, there is probably a error.
 * \param databits If the pointer is valid, the \p databits is set.
 * \param parity If the pointer is valid, the \p parity is set.
 * \param stopbit If the pointer is valid, the \p stopbit is set.
 * 
 * \see armSetSerial()
 */
void armGetSerial(arm_t* arm, armPortBaudrate_t* baud, armPortDatabits_t* databits, armPortParity_t* parity, armPortStopbit_t* stopbit);

/*!  
 * \brief Enable/Disable and configure the \b wake \b on \b radio mode.
 * 
 * \warning If \b ARMPORT_WITH_nSLEEP is not defined and the \p mode 
 * is \ref ARM_FSK_WOR_CS or \ref ARM_FSK_WOR_PQT
 * this function enable the wake up on uart (see \ref armEnableWakeUpUart())
 * and change the serial baudrate if necessary. In other mode
 * (and if \b ARMPORT_WITH_nSLEEP is not defined) this function 
 * disable the wake up on uart.
 * \warning If you have the \b LBT mode enable (in \ref ARM_FSK_LBTAFA_LBT or
 * \ref ARM_FSK_LBTAFA_LBTAFA see \ref armFskSetLbtAfaMode()) and the
 * \p mode is \ref ARM_FSK_WOR_CS the \p rssiLevel
 * is the same register in \b ARM, so if change this value with this function,
 * the \p rssiLevel value of the \b LBT is also modified.
 * 
 * This function is supported by:
 * 	- \b ARM_N8_LP, \b ARM Nano in 868Mhz Low Power (and Sigfox).
 * 	- \b ARM_N8_LD, \b ARM Nano in 868MHz Long Distance.
 * 
 * \param arm Pointer to your \b ARM structure.
 * 
 * \param mode The value available:
 * - \ref ARM_FSK_WOR_DISABLE To disable the wake on radio mode. The other parameters is ignored.
 * - \ref ARM_FSK_WOR_LP To enable the long preamble, necessary for the
 * transmitter to wake up the receptor. The parameters \p rssiLevel and \p filterLongPreamble is ignored.
 * - \ref ARM_FSK_WOR_CS To enable the wake on radio in 'Carrier Sense'
 * (choose this mode for speed).
 * - \ref ARM_FSK_WOR_PQT To enable the wake on radio in 'Preamble Quality Threshold'
 * (choose this mode for quality reception). The parameter \p rssiLevel is ignored.
 * 
 * \param periodTime The period time in milliseconds.
 * - The maximal value possible is 900.
 * - The function, return the error \ref ARM_ERR_PARAM_OUT_OF_RANGE if this value is out of rang.
 * - If the \p mode is \ref ARM_FSK_WOR_CS or \ref ARM_FSK_WOR_PQT the \p periodTime
 * is the time between two wake up. If the condition of mode is check, the \b ARM keep awaken to receive the frame.
 * This value must be same of emitter (mode in \ref ARM_FSK_WOR_LP).
 * - If the \p mode is \ref ARM_FSK_WOR_LP the \p periodTime is the time of
 * emission long preamble. It is necessary to emit the loge preamble for considerate the wake-up period of the receiver.
 *  This value must be same of receptor (mode in \ref ARM_FSK_WOR_CS or \ref ARM_FSK_WOR_PQT).
 * 
 * \param postTime The time in milliseconds where the WOR is disable.
 * - The maximal value possible is 2550.
 * - The function, return the error \ref ARM_ERR_PARAM_OUT_OF_RANGE if this value is out of rang.
 * - In the case or \p mode is:
 * 		- \ref ARM_FSK_WOR_CS or \ref ARM_FSK_WOR_PQT, the \p postTime is the time
 * here the \b ARM keep awaken after the receive the last frame.
 * 		- \ref ARM_FSK_WOR_LP after send the first frame with long preamble,
 * the next frames are send without long preamble. After the last frame send
 * and after the \p postTime the \b ARM send the next frame with long preamble.
 * 
 * \param rssiLevel This parameter in dBm is used by \ref ARM_FSK_WOR_CS (the default value is -95).
 * In \ref ARM_FSK_WOR_CS mode the wake up is generate by the rssi level. This Level
 * is configurable by \p rssiLevel parameter.
 * 
 * \param filterLongPreamble In the case where \p mode is \ref ARM_FSK_WOR_CS or \ref ARM_FSK_WOR_PQT,
 * if \p filterLongPreamble is true the receive frames with long preamble is not push on the serial port.
 * 
 * \return Error available:
 * - \ref ARM_ERR_NONE If successful.
 * - \ref ARM_ERR_NO_SUPPORTED If your \b ARM don't support this function.
 * - \ref ARM_ERR_PARAM_OUT_OF_RANGE If one of the parameters is out of rang.
 * 
 * \note You need to call \ref armUpdateConfig() for update the parameters in you \b ARM.\n
 * After call \ref armUpdateConfig() functions, the \b ARM go to sleep:
 * - If the \b ARMPORT_WITH_nSLEEP is not defined. 
 * - If \b ARMPORT_WITH_nSLEEP is defined and sleep is enable (see \ref armSleep()).
 * 
 * \see armFskGetWorMode()
 * \see armEnableWakeUpUart()
 * \see armFskSetLbtAfaMode()
 * \see armSleep()
 */
armError_t armFskSetWorMode(arm_t* arm, armFskWor_t mode, uint16_t periodTime, uint16_t postTime, int8_t rssiLevel, bool filterLongPreamble);

/*! 
 * \brief Get the \b wake \b on \b radio mode configuration.
 * 
 * Please, for more information about parameters consult the documentation of the \ref  armFskSetWorMode() function.
 * \note If you don't went get a parameter you can give the \b NULL value.
 * \note In the case where this function in not supported by your \b ARM the value of parameters is no modified.
 * 
 * This function is supported by:
 * 	- \b ARM_N8_LP, \b ARM Nano in 868Mhz Low Power (and Sigfox).
 * 	- \b ARM_N8_LD, \b ARM Nano in 868MHz Long Distance.
 * 
 * \param arm Pointer to your \b ARM structure.
 * \param mode If the pointer is valid, the \p mode is set.
 * \param periodTime If the pointer is valid, the \p periodTime is set. If
 * the \p mode is \ref ARM_FSK_WOR_DISABLE the value is not workable.
 * \param postTime If the pointer is valid, the \p postTime is set. If the
 * \p mode is \ref ARM_FSK_WOR_DISABLE the value is not workable.
 * \param rssiLevel If the pointer is valid, the \p rssiLevel is set. If
 * the \p mode is not \ref ARM_FSK_WOR_CS the value is not workable.
 * \param filterLongPreamble If the pointer is valid, the \p filterLongPreamble is set. If
 * the \p mode is \ref ARM_FSK_WOR_DISABLE or \ref ARM_FSK_WOR_LP the value is not workable.
 * 
 * \see armFskSetWorMode()
 */
void armFskGetWorMode(arm_t* arm, armFskWor_t* mode, uint16_t* periodTime, uint16_t* postTime, int8_t* rssiLevel, bool* filterLongPreamble);

/*! 
 * \brief Enable/Disable the \b Wake \b Up \b Uart.
 * 
 * \warning The \b Wake \b Up \b Uart don't supporter the serially baudrate
 * upper than 38400 bps. This function set the baudrate at 38400bps if necessary.
 * 
 * This function is supported by:
 * 	- \b ARM_N8_LP, \b ARM Nano in 868Mhz Low Power (and Sigfox).
 * 	- \b ARM_N8_LD, \b ARM Nano in 868MHz Long Distance.
 * 
 * \param arm Pointer to your \b ARM structure.
 * \param enable \e true to enable \b Wake \b Up \b Uart false to disable.
 * 
 * \return Error available:
 * - \ref ARM_ERR_NONE If successful.
 * - \ref ARM_ERR_NO_SUPPORTED If your \b ARM don't support this function.
 * - \ref ARM_ERR_WOR_ENABLE This errors is returned if you went disable the \b Wake \b Up \b Uart (\p enable = false)
 * and the \b ARMPORT_WITH_nSLEEP is not define and the \b WOR is
 * enable in \ref ARM_FSK_WOR_CS or \ref ARM_FSK_WOR_PQT.
 * 
 * \note The \b Wake \b Up \b Uart can be disable by \ref armFskSetWorMode().
 * \note You need to call \ref armUpdateConfig() for update the parameters in you \b ARM.\n
 * After call \ref armUpdateConfig() functions, the \b ARM go to sleep:
 * - If the \b ARMPORT_WITH_nSLEEP is not defined. 
 * - If \b ARMPORT_WITH_nSLEEP is defined and sleep is enable (see \ref armSleep()).
 * 
 * \see armIsEnableWakeUpUart()
 * \see armFskSetWorMode()
 * \see armSleep()
 */
armError_t armEnableWakeUpUart(arm_t *arm, bool enable);

/*! 
 * \brief Get if \b Wake \b Up \b Uart is enable.
 * 
 * \note In the case where this function in not supported by your \b ARM the returned value is unfeasible.
 * 
 * This function is supported by:
 * 	- \b ARM_N8_LP, \b ARM Nano in 868Mhz Low Power (and Sigfox).
 * 	- \b ARM_N8_LD, \b ARM Nano in 868MHz Long Distance.
 * 
 * \param arm Pointer to your \b ARM structure.
 * \return \e true if the \b Wake \b Up \b Uart is enable or \e false if disable.
 * 
 * \see armEnableWakeUpUart()
 */
bool armIsEnableWakeUpUart(arm_t *arm);

#if defined ARMPORT_WITH_nSLEEP || defined __DOXYGEN__
/*! 
 * \brief Enable/Disable sleep with pin.
 * 
 * This function is supported by:
 * 	- \b ARM_N8_LP, \b ARM Nano in 868Mhz Low Power (and Sigfox).
 * 	- \b ARM_N8_LD, \b ARM Nano in 868MHz Long Distance.
 * 	- \b ARM_N8_LW, \b ARM Nano in 868MHz Lora Wan.
 * 
 * \param arm Pointer to your \b ARM structure.
 * \param sleep \e true to enable sleep false to disable.
 * 
 * \note This function is defined only if \b ARMPORT_WITH_nSLEEP is defined.
 * \note The sleep must be disable if the \b Wake \b Up \b Uart is disable
 * and you want call \ref armSend(), \ref armReceive(),
 * \ref armInfo(), \ref armLwIds() or \ref armUpdateConfig()
 * 
 */
void armSleep(arm_t* arm, bool sleep);
#endif
 
/*! 
 * \brief Enable/Disable and configure the \b Lbt&Afa mode.
 * 
 * \warning If you have the \b WOR mode enable (in \ref ARM_FSK_WOR_CS
 *  see \ref armFskSetWorMode()) and the
 * \p mode is not \ref ARM_FSK_LBTAFA_DISABLE the \p rssiLevel
 * is the same register in \b ARM, so if change this value with this function,
 * the \p rssiLevel value of the \b WOR mode is also modified.
 * 
 * This function is supported by:
 * 	- \b ARM_N8_LP, \b ARM Nano in 868Mhz Low Power (and Sigfox).
 * 	- \b ARM_N8_LD, \b ARM Nano in 868MHz Long Distance.
 * 
 * \param arm Pointer to your \b ARM structure.
 * 
 * \param mode The value available:
 * - \ref ARM_FSK_LBTAFA_DISABLE To disable the LBT&AFA mode. 
 * - \ref ARM_FSK_LBTAFA_LBT To enable Listen Before Talk mode. Use this to emit
 * on the radio if the rssi is less than \p rssiLevel.
 * - \ref ARM_FSK_LBTAFA_AFA To enable Adaptive Frequency Agility mode. Use this to receive
 * on one channel of the two (\p channel in \ref armFskSetRadio() and \p channel2).
 * - \ref ARM_FSK_LBTAFA_LBTAFA To enable Listen Before Talk and
 * adaptive Frequency Agility, listen on the tow channels (\p channel in
 * \ref armFskSetRadio() and \p channel2) and talk on the free channels.
 * 
 * \param rssiLevel This parameter in dBm is used by \ref ARM_FSK_LBTAFA_AFA and
 * \ref ARM_FSK_LBTAFA_LBTAFA (the default value is -95) for define the
 * level rssi who say if the channels is busy or not.
 * 
 * \param nSamples This is the number of rssi sample (the default value is 240).
 * 
 * \param channel2 The secondary channel, the primary channel
 * (and the other radio parameters) must be set with \ref armFskSetRadio() function.
 * - The range possible is of 1 to 559.
 * - The function, return the error \ref ARM_ERR_PARAM_OUT_OF_RANGE if this value is out of rang.
 * 
 * \return Error available:
 * - \ref ARM_ERR_NONE If successful.
 * - \ref ARM_ERR_NO_SUPPORTED If your \b ARM don't support this function.
 * - \ref ARM_ERR_PARAM_OUT_OF_RANGE If one of the parameters is out of rang.
 * - \ref ARM_ERR_PARAM_INCOMPATIBLE The parameter \p channel2 of this function is link
 * with the parameters of the function \ref armFskSetRadio(). Is very important to chose the correct value.
 * For more information, please consulate the main radio parameter page
 * and the documentation of \ref armFskSetRadio() function.
 * 
 * \note To configured the other radio parameters please call \ref armFskSetRadio() function.
 * \note You need to call \ref armUpdateConfig() for update the parameters in you \b ARM.
 * 
 * \see armFskGetLbtAfaMode()
 * \see armFskSetRadio()
 * \see armFskSetWorMode()
 * \see armFskMaxRadioPower()
 */
armError_t armFskSetLbtAfaMode(arm_t* arm, armFskLbtAfa_t mode, int8_t rssiLevel, uint16_t nSamples, uint16_t channel2);

/*! 
 * \brief Get the wake up on mode configuration.
 * 
 * Please, for more information about parameters consult the documentation of the \ref  armFskSetLbtAfaMode() function.
 * \note If you don't went get a parameter you can give the \b NULL value.
 * \note In the case where this function in not supported by your \b ARM the value of parameters is no modified.
 * 
 * This function is supported by:
 * 	- \b ARM_N8_LP, \b ARM Nano in 868Mhz Low Power (and Sigfox).
 * 	- \b ARM_N8_LD, \b ARM Nano in 868MHz Long Distance.
 * 
 * \param arm Pointer to your \b ARM structure.
 * \param mode If the pointer is valid, the \p mode is set.
 * \param rssiLevel If the pointer is valid, the \p rssiLevel is set. If
 * the \p mode is \ref ARM_FSK_LBTAFA_DISABLE  the value is not workable.
 * \param nSamples If the pointer is valid, the \p nSamples is set. If
 * the \p mode is \ref ARM_FSK_LBTAFA_DISABLE  the value is not workable.
 * \param channel2 If the pointer is valid, the \p channel2 is set. If
 * the \p mode is \ref ARM_FSK_LBTAFA_DISABLE  the value is not workable.
 * 
 * \see armFskSetLbtAfaMode()
 */
void armFskGetLbtAfaMode(arm_t* arm, armFskLbtAfa_t* mode, int8_t* rssiLevel, uint16_t* nSamples, uint16_t* channel2);


/*! 
 * \brief Setup the LoraWan radio configuration.
 * 
 * For more information, please consulate the LoraWan radio parameters page.
 * \todo Create the LoraWan parameter page.
 * 
 * This function is supported by:
 * 	- \b ARM_N8_LW, \b ARM Nano in 868MHz Lora Wan.
 * 
 * \note If you don't want set a value, pass the 0 value to parameters.
 * \warning This functions disable automatically the \b Tx \b Adaptive \b Speed if the parameter \p txSf or \p power is not set to 0.
 * \warning This functions disable automatically the \b Adaptive \b Channel if the parameter \p txChannel is not set to 0.
 * \warning This functions disable automatically the \b rx2 \b Adaptive if the parameter \p rx2Sf or \p rx2Channel is not set to 0.
 * 
 * \param arm Pointer to your \b ARM structure.
 * \param txChannel the emission channel.
 * 	- The range possible is of 1 to 9. In this case the \b Adaptive \b Channel is automatically disable.
 * 	- Set 0 if you don't want set this parameter.
 * 	- The function, return the error \ref ARM_ERR_PARAM_OUT_OF_RANGE if this value is out of rang.
 * 
 * \param power the output power.
 * 	- The possibles values are 2, 5, 8, 11, 14 (value in dBm). In this case the \b Tx \b Adaptive \b Speed is automatically disable.
 * 	- Set 0 if you don't want set this parameter.
 * 	- The function, return the error \ref ARM_ERR_PARAM_OUT_OF_RANGE if this value is out of rang.
 * 
 * \param txSf the emission spreading factor.
 * 	- The range possible is of 7 to 12. In this case the \b Tx \b Adaptive \b Speed is automatically disable.
 * 	- Set 0 if you don't want set this parameter.
 * 	- The function, return the error \ref ARM_ERR_PARAM_OUT_OF_RANGE if this value is out of rang.
 * 
 * \param rx2Sf the Rx2 spreading factor.
 * 	- The range possible is of 7 to 12. In this case the \b rx2 \b Adaptive is automatically disable.
 * 	- Set 0 if you don't want set this parameter.
 * 	- The function, return the error \ref ARM_ERR_PARAM_OUT_OF_RANGE if this value is out of rang.
 * 
 * \param rx2Channel the Rx2 channel.
 * 	- The range possible is of 1 to 9. In this case the \b rx2 \b Adaptive is automatically disable.
 * 	- Set 0 if you don't want set this parameter.
 * 	- The function, return the error \ref ARM_ERR_PARAM_OUT_OF_RANGE if this value is out of rang.
 * 
 * \return Error available:
 * 	- \ref ARM_ERR_NONE If successful.
 * 	- \ref ARM_ERR_NO_SUPPORTED If your \b ARM don't support this function.
 * 	- \ref ARM_ERR_PARAM_OUT_OF_RANGE If one of the parameters is out of rang.
 * 
 * \note You need to call \ref armUpdateConfig() to update the parameters in you \b ARM.
 * 
 * \see armLwGetRadio()
 * \see armLwEnableRxWindows()
 * \see armLwEnableTxAdaptiveSpeed()
 * \see armLwEnableDutyCycle()
 * \see armLwEnableTxAdaptiveChannel()
 * \see armLwIsEnableRx2Adaptive()
 */
armError_t armLwSetRadio(arm_t* arm, uint8_t txChannel, uint8_t power, uint8_t txSf, uint8_t rx2Sf, uint8_t rx2Channel);

/*! 
 * \brief Get the LoraWan radio configuration.
 * 
 * Please, for more information about parameter consult the documentation of the \ref armLwSetRadio() function.
 * \note If you don't went get a parameter you can give the \b NULL value.
 * \note In the case where this function in not supported by your \b ARM the value of parameters is no modified.
 * 
 * This function is supported by:
 * 	- \b ARM_N8_LW, \b ARM Nano in 868MHz Lora Wan.
 * 
 * \param arm Pointer to your \b ARM structure.
 * \param txChannel If the pointer is valid, the \p txChannel is set.
 * \param power If the pointer is valid, the \p power is set.
 * \param txSf If the pointer is valid, the \p txSf is set.
 * \param rx2Sf If the pointer is valid, the \p rx2Sf is set.
 * \param rx2Channel If the pointer is valid, the \p rx2Channel is set.
 * 
 * \see armLwSetRadio()
 */
void armLwGetRadio(arm_t* arm, uint8_t* txChannel, uint8_t* power, uint8_t* txSf, uint8_t* rx2Sf, uint8_t* rx2Channel);

/*! 
 * \brief Enable/Disable and set the confirmed frame.
 * 
 * \note In the case where this function in not supported by your \b ARM this functions is ignored.
 * 
 * This function is supported by:
 * 	- \b ARM_N8_LW, \b ARM Nano in 868MHz Lora Wan.
 * 
 * \param arm Pointer to your \b ARM structure.
 * \param nbFrame the value available:
 * 	- 0: Enable \e unconfirmed frame, will use LoRaWan default value,
 * can be adapt by gateway with MacCommand.
 * 	- -1 down -15: Enable \e unconfirmed frame, send unconfirmed frame of 1 up to 15.
 * You can use the \ref ARM_LW_UNCONFIRMED() macro to set a positive value.
 * 	- 1 to 15 : Enable \e confirmed frame, send confirmed frame of 1 up to 15.
 * 
 * \return Error available:
 * 	- \ref ARM_ERR_NONE If successful.
 * 	- \ref ARM_ERR_NO_SUPPORTED If your \b ARM don't support this function.
 * 	- \ref ARM_ERR_PARAM_OUT_OF_RANGE If one of the parameters is out of rang.
 * 
 * eg:
 * \code
 * //Put at 3 the number of frame unconfirmed.
 * armLwSetConfirmedFrame(&myArm, -3);
 * \endcode
 * or (this is same thing):
 * \code
 * //Put at 3 the number of frame unconfirmed.
 * armLwSetConfirmedFrame(&myArm, ARM_LW_UNCONFIRMED(3));
 * \endcode
 * 
 * \note You need to call \ref armUpdateConfig() to update the parameters in you \b ARM.
 * 
 * \see armLwGetConfirmedFrame()
 */
armError_t armLwSetConfirmedFrame(arm_t* arm, int8_t nbFrame);

/*! 
 * \brief Get the setup of confirmed frame.
 * 
 * \note In the case where this function in not supported by your \b ARM the returned value is unfeasible.
 * 
 * This function is supported by:
 * 	- \b ARM_N8_LW, \b ARM Nano in 868MHz Lora Wan.
 * 
 * \param arm Pointer to your \b ARM structure.
 * \return The confirmed frame setup.
 * 
 * eg:
 * \code
 * int8_t nbFrame = armLwGetConfirmedFrame(&myArm);
 * if(ARM_LW_IS_UNCONFIRMED(nbFrame))
 * {
 * 		nbFrame = ARM_LW_UNCONFIRMED(nbFrame);
 * 		//...
 * }
 * else
 * {
 * 		//...
 * }
 * \endcode
 * or (this is same thing):
 * \code
 * int8_t nbFrame = armLwGetConfirmedFrame(&myArm);
 * if(nbFrame <= 0)
 * {
 * 		nbFrame = -1*nbFrame);
 * 		//...
 * }
 * else
 * {
 * 		//...
 * }
 * \endcode
 * 
 * \see armLwSetConfirmedFrame()
 */
int8_t armLwGetConfirmedFrame(arm_t* arm);

/*! 
 * \brief Set the port field.
 * 
 * \note In the case where this function in not supported by your \b ARM this functions is ignored.
 * 
 * This function is supported by:
 * 	- \b ARM_N8_LW, \b ARM Nano in 868MHz Lora Wan.
 * 
 * \param arm Pointer to your \b ARM structure.
 * \param port the value available:
 * 	- 0x00: indicates that the FRMPayload contains MAC commands only
 * 	- 0x01 to 0xDF: application specific
 * 	- 0xE0 to 0xFF: reserved for future standardized application extensions
 * 
 * \note You need to call \ref armUpdateConfig() to update the parameters in you \b ARM.
 * 
 * \see armLwGetPortField()
 */
void armLwSetPortField(arm_t* arm, uint8_t port);

/*! 
 * \brief Get the port field.
 * 
 * \note In the case where this function in not supported by your \b ARM the returned value is unfeasible.
 * 
 * This function is supported by:
 * 	- \b ARM_N8_LW, \b ARM Nano in 868MHz Lora Wan.
 * 
 * \param arm Pointer to your \b ARM structure.
 * \return The port field.
 * 
 * \see armLwSetPortField()
 */
uint8_t armLwGetPortField(arm_t* arm);

/*! 
 * \brief Enable/Disable \b Over \b The \b Air \b Activation.
 * 
 * \note In the case where this function in not supported by your \b ARM this functions is ignored.
 * 
 * This function is supported by:
 * 	- \b ARM_N8_LW, \b ARM Nano in 868MHz Lora Wan.
 * 
 * \param arm Pointer to your \b ARM structure.
 * \param enable \e true to enable \b Over \b The \b Air \b Activation or \e false to disable.
 * 
 * \note You need to call \ref armUpdateConfig() to update the parameters in you \b ARM.
 * The \b ARM will be restart if necessary.
 * 
 * \see armLwIsEnableOtaa()
 */
void armLwEnableOtaa(arm_t* arm, bool enable);

/*! 
 * \brief Get if \b Over \b The \b Air \b Activation is enable.
 * 
 * \note In the case where this function in not supported by your \b ARM the returned value is unfeasible.
 * 
 * This function is supported by:
 * 	- \b ARM_N8_LW, \b ARM Nano in 868MHz Lora Wan.
 * 
 * \param arm Pointer to your \b ARM structure.
 * \return \e true if the \b Over \b The \b Air \b Activation is enable or \e false if disable.
 * 
 * \see armLwEnableOtaa()
 */
bool armLwIsEnableOtaa(arm_t* arm);

/*! 
 * \brief Enable/Disable \b Rx \b windows.
 * 
 * \note In the case where this function in not supported by your \b ARM this functions is ignored.
 * 
 * This function is supported by:
 * 	- \b ARM_N8_LW, \b ARM Nano in 868MHz Lora Wan.
 * 
 * \param arm Pointer to your \b ARM structure.
 * \param enable \e true to enable \b Rx \b windows or \e false to disable.
 * In the case where \p enable is true, the \b ARM will ignore the parameters \p rx2Sf and \p rx2Channel of the function 
 * \ref armLwSetRadio().
 * 
 * \note You need to call \ref armUpdateConfig() to update the parameters in you \b ARM.
 * 
 * \see armLwIsEnableRxWindows()
 */
void armLwEnableRxWindows(arm_t* arm, bool enable);

/*! 
 * \brief Get if \b Rx \b windows is enable.
 * 
 * \note In the case where this function in not supported by your \b ARM the returned value is unfeasible.
 * 
 * This function is supported by:
 * 	- \b ARM_N8_LW, \b ARM Nano in 868MHz Lora Wan.
 * 
 * \param arm Pointer to your \b ARM structure.
 * \return \e true if the \b Rx \b windows is enable or \e false if disable.
 * 
 * \see armLwEnableRxWindows()
 */
bool armLwIsEnableRxWindows(arm_t* arm);

/*! 
 * \brief Enable/Disable \b Tx \b Adaptive \b Speed.
 * 
 * \note In the case where this function in not supported by your \b ARM this functions is ignored.
 * 
 * This function is supported by:
 * 	- \b ARM_N8_LW, \b ARM Nano in 868MHz Lora Wan.
 * 
 * \param arm Pointer to your \b ARM structure.
 * \param enable \e true to enable \b Tx \b Adaptive \b Speed or \e false to disable.
 * In the case where \p enable is true, the \b ARM will ignore the parameters \p power and \p txSf of the function 
 * \ref armLwSetRadio().
 * 
 * \note You need to call \ref armUpdateConfig() to update the parameters in you \b ARM.
 * 
 * \see armLwIsEnableTxAdaptiveSpeed()
 */
void armLwEnableTxAdaptiveSpeed(arm_t* arm, bool enable);

/*! 
 * \brief Get if \b Tx \b Adaptive \b Speed is enable.
 * 
 * \note In the case where this function in not supported by your \b ARM the returned value is unfeasible.
 * 
 * This function is supported by:
 * 	- \b ARM_N8_LW, \b ARM Nano in 868MHz Lora Wan.
 * 
 * \param arm Pointer to your \b ARM structure.
 * \return \e true if the \b Tx \b Adaptive \b Speed is enable or \e false if disable.
 * 
 * \see armLwEnableTxAdaptiveSpeed()
 */
bool armLwIsEnableTxAdaptiveSpeed(arm_t* arm);

/*! 
 * \brief Enable/Disable \b Duty \b Cycle.
 * 
 * \warning The \b Duty \b Cycle should be enable every time.
 * \note In the case where this function in not supported by your \b ARM this functions is ignored.
 * 
 * This function is supported by:
 * 	- \b ARM_N8_LW, \b ARM Nano in 868MHz Lora Wan.
 * 
 * \param arm Pointer to your \b ARM structure.
 * \param enable \e true to enable \\b Duty \b Cycle or \e false to disable.
 * 
 * \note You need to call \ref armUpdateConfig() to update the parameters in you \b ARM.
 * 
 * \see armLwIsEnableDutyCycle()
 */
void armLwEnableDutyCycle(arm_t* arm, bool enable);

/*! 
 * \brief Get if \b Duty \b Cycle is enable.
 * 
 * \note In the case where this function in not supported by your \b ARM the returned value is unfeasible.
 * 
 * This function is supported by:
 * 	- \b ARM_N8_LW, \b ARM Nano in 868MHz Lora Wan.
 * 
 * \param arm Pointer to your \b ARM structure.
 * \return \e true if the \b Duty \b Cycle is enable or \e false if disable.
 * 
 * \see armLwEnableDutyCycle()
 */
bool armLwIsEnableDutyCycle(arm_t* arm);

/*! 
 * \brief Enable/Disable \b Tx \b Adaptive \b Channel.
 * 
 * \note In the case where this function in not supported by your \b ARM this functions is ignored.
 * 
 * This function is supported by:
 * 	- \b ARM_N8_LW, \b ARM Nano in 868MHz Lora Wan.
 * 
 * \param arm Pointer to your \b ARM structure.
 * \param enable \e true to enable \b Tx \b Adaptive \b Channel or \e false to disable.
 * In the case where \p enable is true, the \b ARM will ignore the parameter \p txChannel of the function 
 * \ref armLwSetRadio().
 * 
 * \note You need to call \ref armUpdateConfig() to update the parameters in you \b ARM.
 * 
 * \see armLwIsEnableTxAdaptiveChannel()
 */
void armLwEnableTxAdaptiveChannel(arm_t* arm, bool enable);

/*! 
 * \brief Get if \b Tx \b Adaptive \b Channel is enable.
 * 
 * \note In the case where this function in not supported by your \b ARM the returned value is unfeasible.
 * 
 * This function is supported by:
 * 	- \b ARM_N8_LW, \b ARM Nano in 868MHz Lora Wan.
 * 
 * \param arm Pointer to your \b ARM structure.
 * \return \e true if the \b Tx \b Adaptive \b Channel is enable or \e false if disable.
 * 
 * \see armLwEnableTxAdaptiveChannel()
 */
bool armLwIsEnableTxAdaptiveChannel(arm_t* arm);

/*! 
 * \brief Enable/Disable \b Rx2 windows \b Adaptive.
 * 
 * \note In the case where this function in not supported by your \b ARM this functions is ignored.
 * 
 * This function is supported by:
 * 	- \b ARM_N8_LW, \b ARM Nano in 868MHz Lora Wan.
 * 
 * \param arm Pointer to your \b ARM structure.
 * \param enable \e true to enable \b Rx2 windows \b Adaptive or \e false to disable.
 * In the case where \p enable is true, the \b ARM will ignore the parameter \p rx2Sf and \p rx2Channel 
 * of the function \ref armLwSetRadio().
 * 
 * \note You need to call \ref armUpdateConfig() to update the parameters in you \b ARM.
 * 
 * \see armLwIsEnableRx2Adaptive()
 */
void armLwEnableRx2Adaptive(arm_t* arm, bool enable);

/*! 
 * \brief Get if \b Rx2 windows \b Adaptive is enable.
 * 
 * \note In the case where this function in not supported by your \b ARM the returned value is unfeasible.
 * 
 * This function is supported by:
 * 	- \b ARM_N8_LW, \b ARM Nano in 868MHz Lora Wan.
 * 
 * \param arm Pointer to your \b ARM structure.
 * \return \e true if the \b Rx2 windows \b Adaptive is enable or \e false if disable.
 * 
 * \see armLwEnableRx2Adaptive()
 */
bool armLwIsEnableRx2Adaptive(arm_t* arm);

/*! 
 * \brief Get the IDs.
 * 
 * This function is supported by:
 * 	- \b ARM_N8_LW, \b ARM Nano 868MHz in Lora Wan.
 * 
 * \note If you don't went get a parameter you can give the \b NULL value.
 * 
 * \param arm Pointer to your \b ARM structure.
 * \param devAddr If the pointer is valid, the \p devAddr is set.
 * \param devEui If the pointer is valid, the \p devEui is set.
 * \param appEui If the pointer is valid, the \p appEui is set.
 * \param appKey If the pointer is valid, the \p appKey is set.
 * \param nwkSKey If the pointer is valid, the \p nwkSKey is set.
 * \param appSKey If the pointer is valid, the \p appSKey is set.
 * 
 * \return Error available:
 * 	- \ref ARM_ERR_NONE If success.
 * 	- \ref ARM_ERR_NO_SUPPORTED If your \b ARM don't support this function.
 * 	- \ref ARM_ERR_PORT_WRITE_READ If can't write or read through the port.
 * 	- \ref ARM_ERR_ARM_GET_REG If can't get register from \b ARM.
 * 	- \ref ARM_ERR_ARM_GO_AT If can't go to AT commend.
 * 	- \ref ARM_ERR_ARM_BACK_AT If can't back AT commend.
 * 
 */
armError_t armLwIds(arm_t* arm, 	uint32_t* devAddr,
									uint64_t* devEui,
									uint64_t* appEui,
									uint128_t* appKey,
									uint128_t* nwkSKey,
									uint128_t* appSKey);
									
/*! 
 * \brief Set the \a LED behavior.
 * 
 * \note In the case where this function in not supported by your \b ARM this functions in ignored.
 * 
 * This function is supported by:
 * 	- \b ARM_N8_LP, \b ARM Nano in 868Mhz Low Power (and Sigfox).
 * 	- \b ARM_N8_LD, \b ARM Nano in 868MHz Long Distance.
 * 	- \b ARM_N8_LW, \b ARM Nano in 868MHz Lora Wan.
 * 
 * \param arm Pointer to your \b ARM structure.
 * \param led The behavior of the \a LED:
 * 		- \ref ARM_LED_OFF, The \a LED is 'off' all the time.
 * 		- \ref ARM_LED_OFF_RF, The \a LED is 'off' on RF activity and 'on' other time.
 * 		- \ref ARM_LED_ON_RF, The \a LED is 'on' on RF activity and 'off' other time.
 * 
 * \note You need to call \ref armUpdateConfig() to update the parameters in you \b ARM.
 * 
 * \see armGetLed()
 */
void armSetLed(arm_t* arm, armLed_t led);

/*! 
 * \brief Get the \a LED behavior.
 * 
 * \note In the case where this function in not supported by your \b ARM the returned value is unfeasible.
 * 
 * This function is supported by:
 *	- \b ARM_N8_LP, \b ARM Nano in 868Mhz Low Power (and Sigfox).
 *	- \b ARM_N8_LD, \b ARM Nano in 868MHz Long Distance.
 *	- \b ARM_N8_LW, \b ARM Nano 868MHz in Lora Wan.
 * 
 * \param arm Pointer to your \b ARM structure.
 * \return The behavior of the \a LED:
 * 		- \ref ARM_LED_OFF, The \a LED is 'off' all the time.
 * 		- \ref ARM_LED_OFF_RF, The \a LED is 'off' on RF activity and 'on' other time.
 * 		- \ref ARM_LED_ON_RF, The \a LED is 'on' on RF activity and 'off' other time.
 * 
 * \see armSetLed()
 */
armLed_t armGetLed(arm_t* arm);

/*! 
 * \brief Update the configuration in \b ARM.
 * 
 * None of parameters/modes previously configured, is no set in your \b ARM.
 * This function send/set the necessary registers to apply the previously
 * configuration and reconfigure the port if necessary.
 * 
 * \param arm Pointer to your \b ARM structure.
 * 
 * \return Error available:
 * 		- \ref ARM_ERR_NONE If success.
 * 		- \ref ARM_ERR_NO_SUPPORTED If there is bad \b ARM type.
 * 			Probably the \b ARM structure is not initialized.
 * 			In this case you can call \ref armInit() and check the returned error.
 * 		- \ref ARM_ERR_PORT_CONFIG If the port can't be configured.
 * 		- \ref ARM_ERR_PORT_WRITE_READ If can't write or read through the port.
 * 		- \ref ARM_ERR_ARM_GO_AT If can't go to AT commend.
 * 		- \ref ARM_ERR_ARM_BACK_AT If can't back AT commend.
 * 		- \ref ARM_ERR_ARM_SET_REG If can't set register from \b ARM.
 * 		- \ref ARM_ERR_ARM_CMD If can't execute a AT commend from \b ARM.
 */
armError_t armUpdateConfig(arm_t* arm);

/*! 
 * \brief Send data to \b ARM.
 * 
 * - In the case or the infinity mode is enable, this function send the data.
 * - In the case or the infinity mode is disable, the packet mode is enable,
 * this function send the data to the \b ARM, 120 byte by 120 byte and
 * wait the necessary time to send the data on the radio.
 * 
 * \warning You can use your method to write data to \b ARM (for example:
 * in interruption method), but you don't must influence on the behavior
 * of serial port when \ref armInit(), \ref armReboot(), \ref armInfo(), \ref armLwIds() or \ref armUpdateConfig() is call.
 * 
 * \param arm Pointer to your \b ARM structure.
 * \param buf The buffer.
 * \param nbyte The number of data to send.
 * 
 * \return The number of data write. -1 if error from the serial port.
 * 
 * \see armReceive()
 * \see armFskEnableInfinityMode()
 * \todo Finish implementation and add doc to explained the wait time
 * between send data.
 */
ssize_t armSend(arm_t* arm, const void* buf, size_t nbyte);

/*! 
 * \brief Receive data from \b ARM.
 * 
 * This function is exit when the timeout is achieved from the last receive
 * data or if the \p nbyte is achieved.
 * 
 * \warning You can use your method to read data from \b ARM (for example:
 * in interruption method), but you don't must influence on the behavior
 * of serial port when \ref armInit(), \ref armReboot(), \ref armInfo(), \ref armLwIds() or \ref armUpdateConfig() is call.
 * 
 * \param arm Pointer to your \b ARM structure.
 * \param buf The buffer.
 * \param nbyte The size of buffer.
 * \param timeout The timeout.
 * 
 * \return The number of data read. -1 if error from the serial port.
 * 
 * \see armSend()
 */
ssize_t armReceive(arm_t* arm, void* buf, size_t nbyte, int timeout);

#endif //ARM_H
