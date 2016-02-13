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


#ifndef VT100_H
#define VT100_H

#define C_raz			"\e[0m"
	
#define F_default		"\e[39m"
#define F_black			"\e[30m"
#define F_Red			"\e[31m"
#define F_Green			"\e[32m"
#define F_Yellow		"\e[33m"
#define F_Blue			"\e[34m"
#define F_Magenta		"\e[35m"
#define F_Cyan			"\e[36m"
#define F_Light_gray	"\e[37m"
#define F_Dark_gray		"\e[90m"
#define F_Light_red		"\e[91m"
#define F_Light_green	"\e[92m"
#define F_Light_yellow	"\e[93m"
#define F_Light_blue	"\e[94m"
#define F_Light_magenta	"\e[95m"
#define F_Light_cyan	"\e[96m"
#define F_White			"\e[97m"

#define B_default		"\e[97m\e[49m"
#define B_black			"\e[30m\e[40m"
#define B_Red			"\e[30m\e[41m"
#define B_Green			"\e[30m\e[42m"
#define B_Yellow		"\e[30m\e[43m"
#define B_Blue			"\e[30m\e[44m"
#define B_Magenta		"\e[30m\e[45m"
#define B_Cyan			"\e[30m\e[46m"
#define B_Light_gray	"\e[30m\e[47m"
#define B_Dark_gray		"\e[30m\e[100m"
#define B_Light_red		"\e[30m\e[101m"
#define B_Light_green	"\e[30m\e[102m"
#define B_Light_yellow	"\e[30m\e[103m"
#define B_Light_blue	"\e[30m\e[104m"
#define B_Light_magenta	"\e[30m\e[105m"
#define B_Light_cyan	"\e[30m\e[106m"
#define B_White			"\e[30m\e[107m"

#endif // VT100_H
