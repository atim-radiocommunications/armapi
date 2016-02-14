// ---------------------------------------------------------------------
// Created date: 21.12.2015
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

/*! \page arduino_page Quick started with Arduino.
 * \tableofcontents
 * \section arduino_section_hardware_sec Hardware
 * The hardware is composed of acw-duino shield and a antenna,
 * coupled at your Arduino.
 * \image html acw_duino1.png
 * 
 * 
 * \section arduino_section_installation_sec Installation
 * The installation is easy. The first step is to download the
 * API packages. You can find it <a href="http://atim-radiocommunications.github.io/armapi/armapi.zip">here</a>.
 * 
 * Run you arduino IDE and go to a menu Sketch->Include Library->Add .ZIP Library...
 * \image html ide_arduino_add_lib_menu.png
 * Now, chose the armapi.zip file you just download.
 * \image html ide_arduino_add_lib_dialog.png
 * And it is finish, the library is installed.
 *
 * 
 * \section arduino_section_start_to_code_sec Start to code
 * \subsection arduino_subsection_start_read_documentation Read the documentation
 * This documentation is generated from the c binding source, but it easily
 * to understand for a cpp. In c, each functions name start by \b 'arm' 
 * and the first argument is a pointer to \b arm structure.
 * In cpp, it were replace by the \b Arm class.
 * 
 * For example to set a mode:
 * \code {c}
 * //In c
 * armSetMode(&myArm, ARM_MODE_FSK);
 * //In cpp
 * myArm.SetMode(ARM_MODE_FSK);
 * \endcode
 * 
 * In c, some functions don't need a structure, in cpp this function
 * is converted in static method.
 * 
 * For example to get a max power:
 * \code  {c}
 * //In c
 * getMaxPower = armFskMaxPower(42, ARM_BAUDRATE_1200);
 * //In cpp
 * getMaxPower = Arm::FskMaxPower(42, ARM_BAUDRATE_1200);
 * \endcode
 * 
 * \subsection arduino_subsection_start_write_code Write a code
 * Now you are ready to start to write a code. The API require to work
 * a serial link. On Arduino, you must use the \b Serial object and give
 * this object to the API with the Init method. Before it, you need to
 * instanced the Arm object.
 * \code {cpp}
 * //Instanced the Arm object
 * Arm myArm;
 * //Call Init method
 * myArm.Init(&Serial);
 * \endcode
 * You can check the error returned by the Init method to know if the
 * initialization is successful. The Init method detect automatically the
 * arm type (\ref  armType_t) and the library adapts itself. For example,
 * the method LwGetConfirmedFrame() has no effect if the type is no
 * \ref ARM_TYPE_N8_LW, there is not reason to use this method if you
 * \b ARM don't support the Lora network.
 * 
 * About the name of methods:
 * - The methods, prefixed by \b Fsk are used to control the Fsk/local radio mode. See \ref fsk_page
 * - The methods, prefixed by \b Sfx are used to control the Sigfox network. See \ref sfx_page
 * - The methods, prefixed by \b Lw are used to control the Lora network. See \ref lora_page
 * - The methods, without prefixed, can be use in all case.
 * 
 * \see armInit()
 * \see armInfo()
 * 
 * \section arduino_page_examples_sec Examples
 * After have installed the \b armapi you can access and test directing
 * the examples give by the Arduino package. For this go to
 * File->Examples->armapi->example->... menu.
 * \image html ide_arduino_add_exemples_menu.png
 * 
 * \subsection arduino_subsection_example_sigfox_downlink Sigfox downlink
 * This example send periodically 'Hello Sigfox' to Sigfox network.
 * 
 * \ref arduino/sigfox_uplink/sigfox_uplink.ino
 * 
 * \subsection arduino_subsection_example_sigfox_uplink Sigfox uplink
 * This example send periodically 'Hello Sigfox' to Sigfox network
 * and get the message from sigfox to on/off the led.
 * The first byte is user to switch on/off the led.
 * - If the byte is 0 the led is switch to off.
 * - If the byte is different of 0 the led is switch to on.
 * 
 * \ref arduino/sigfox_downlink/sigfox_downlink.ino
 * 
 * \subsection arduino_subsection_example_fsk_echo Fsk(local) echo
 * This example make a radio echo on the radio channel 4
 * with 9600bps radio speed.
 * 
 * \ref arduino/fsk_echo/fsk_echo.ino
 * 
 * \example arduino/sigfox_uplink/sigfox_uplink.ino
 * \example arduino/sigfox_downlink/sigfox_downlink.ino
 * \example arduino/fsk_echo/fsk_echo.ino
 * 
 */
