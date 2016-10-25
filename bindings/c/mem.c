// ---------------------------------------------------------------------
// Created date: 25.10.2016
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
// Implementation functions
// ---------------------------------------------------------------------
#ifndef __DOXYGEN__

void *memset(void *s, int c, size_t n)
{
	if(n > 0)
	{
		for(n--; n>=0; n--)
		{
			((char*)s)[n] = c;
		}
	}
	
	return s;
}

void *memmem(const void *haystack, size_t haystacklen, const void *needle, size_t needlelen)
{
	size_t iHaystack = 0;
    size_t nHaystack = 0;
    size_t nNeedle = 0;
    const char *phaystack = haystack;
    const char *pneedle = needle;
    
    //Check size
    if((haystacklen==0) || (needlelen==0))
        return NULL;
    
    while(1)
    {
        //Find the first char of needle in haystack
        while(phaystack[iHaystack] != pneedle[0])
        {
            iHaystack++;
            if(iHaystack >= haystacklen)
                return NULL;
        }

        //Char found, check next char into string
        nHaystack = iHaystack;
        nNeedle = 0;
        while(phaystack[nHaystack] == pneedle[nNeedle])
        {
            nHaystack++;
            nNeedle++;
            
            //String found ?
            if(nNeedle >= needlelen)
                return (void *)(phaystack+iHaystack);

            if((nHaystack >= haystacklen))
                return NULL;
        }
        iHaystack++;
    }

    return NULL;
}

#endif //__DOXYGEN__

