// ---------------------------------------------------------------------
// Created date: 14.12.2015
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

/*! \defgroup arm_n8_lpld ARM Nano in 868MHz Low Power (Sigfox network) and Long Distance version.
 * 
 * This group contains the functions using by the \b ARM Nano in 868MHz
 * Low Power (Sigfox network) (\b ARM_N8_LP) and Long Distance (\b ARM_N8_LD).
 * 
 * The functions in this group is only usable if the \ref armType_t returned by \ref armGetInfo()
 * is \ref ARM_TYPE_N8_LP or \ref ARM_TYPE_N8_LD.
 * 
 */
 
 
/*! \defgroup arm_n8_lw ARM Nano in 868MHz Lora Wan network version.
 * 
 * This group contains the functions using by the \b ARM Nano in 868MHz Lora Wan network version (\b ARM_N8_LW).
 * 
 * The functions in this group is only usable if the \ref armType_t returned by \ref armGetInfo()
 * is \ref ARM_TYPE_N8_LW.
 * 
 */
 
/*! \defgroup arm_init_various Initialization and various
 * \ingroup arm_n8_lpld
 * \ingroup arm_n8_lw
 * 
 */
 
/*! \defgroup arm_serial Serial configuration
 * \ingroup arm_n8_lpld
 * 
 */
 
/*! \defgroup arm_local_radio Local radio configuration
 * \ingroup arm_n8_lpld
 * 
 */
 
/*! \defgroup arm_addressing Addressing
 * \ingroup arm_n8_lpld
 * 
 */
 
/*! \defgroup arm_crc Cyclic Redundancy Check
 * \ingroup arm_n8_lpld
 * 
 * In the case where the \b CRC is enable:
 * - The \b ARM module compute the CRC and send on the radio the frame with the CRC.
 * - If the \b ARM module receive the radio frame with the CRC
 * (the emitter must have the CRC enable), the ARM compute the CRC and throw
 * the frame if the CRCs don't match.
 */
 
/*! \defgroup arm_infinity_mode Infinity mode
 * \ingroup arm_n8_lpld
 * 
 */
 
/*! \defgroup arm_whitening Whitening
 * \ingroup arm_n8_lpld
 * 
 */
 
/*! \defgroup arm_power_saving Power saving
 * \ingroup arm_n8_lpld
 * 
 */
 
/*! \defgroup arm_lbt_afa_mode LBT&AFA mode
 * \ingroup arm_n8_lpld
 * 
 */
 
/*! \defgroup arm_send_receive_data Send and receive data
 * \ingroup arm_n8_lpld
 * \ingroup arm_n8_lw
 * 
 */












