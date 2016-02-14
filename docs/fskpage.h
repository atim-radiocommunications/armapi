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

/*! \page fsk_page Fsk (Local) radio
 * 
 * The relation between the channel, baudrate and output emission power
 * is given by this table:

 * |Channel| 1200	| 2400	| 4800	| 9600	| 19200	| 38400	| 57600	| 115200|
 * | ----: |:----: |:----: |:----: |:----: |:----: |:----: |:----: |:----: |
 * | 0	|    	|    	|    	|    	|    	|    	|    	|    	|
 * | 1	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|    	|
 * | 2	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|
 * | 3	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|    	|
 * | 4	| 14dBm	| 14dBm	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|
 * | 5	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	| 14dBm	|    	|
 * | 6	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|
 * | 7	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	|    	|    	|
 * | 8	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	| 14dBm	|
 * | 9	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|    	|
 * | 10	| 14dBm	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|
 * | 11	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	| 14dBm	|    	|
 * | 12	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	|    	|
 * | 13	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	|    	|    	|
 * | 14	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|
 * | 15	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|    	|
 * | 16	| 14dBm	| 14dBm	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|
 * | 17	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	| 14dBm	|    	|
 * | 18	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|
 * | 19	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	|    	|    	|
 * | 20	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	|    	|
 * | 21	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|    	|
 * | 22	| 14dBm	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|
 * | 23	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	| 14dBm	|    	|
 * | 24	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	| 14dBm	|
 * | 25	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	|    	|    	|
 * | 26	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|
 * | 27	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|    	|
 * | 28	| 14dBm	| 14dBm	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|
 * | 29	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	| 14dBm	|    	|
 * | 30	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|
 * | 31	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	|    	|    	|
 * | 32	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	|    	|
 * | 33	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|    	|
 * | 34	| 14dBm	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|
 * | 35	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	| 14dBm	|    	|
 * | 36	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	|    	|
 * | 37	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	|    	|    	|
 * | 38	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|
 * | 39	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|    	|
 * | 40	| 14dBm	| 14dBm	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|
 * | 41	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	| 14dBm	|    	|
 * | 42	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|
 * | 43	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	|    	|    	|
 * | 44	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	|    	|
 * | 45	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|    	|
 * | 46	| 14dBm	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|
 * | 47	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	| 14dBm	|    	|
 * | 48	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	|    	|
 * | 49	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	|    	|    	|
 * | 50	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|
 * | 51	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|    	|
 * | 52	| 14dBm	| 14dBm	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|
 * | 53	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	| 14dBm	|    	|
 * | 54	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|
 * | 55	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	|    	|    	|
 * | 56	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	| 14dBm	|
 * | 57	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|    	|
 * | 58	| 14dBm	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|
 * | 59	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	| 14dBm	|    	|
 * | 60	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	|    	|
 * | 61	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	|    	|    	|
 * | 62	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|
 * | 63	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|    	|
 * | 64	| 14dBm	| 14dBm	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|
 * | 65	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	| 14dBm	|    	|
 * | 66	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|
 * | 67	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	|    	|    	|
 * | 68	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	|    	|
 * | 69	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|    	|
 * | 70	| 14dBm	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|
 * | 71	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	| 14dBm	|    	|
 * | 72	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	| 14dBm	|
 * | 73	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	|    	|    	|
 * | 74	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|
 * | 75	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|    	|
 * | 76	| 14dBm	| 14dBm	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|
 * | 77	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	| 14dBm	|    	|
 * | 78	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|
 * | 79	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	|    	|    	|
 * | 80	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	|    	|
 * | 81	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|    	|
 * | 82	| 14dBm	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|
 * | 83	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	| 14dBm	|    	|
 * | 84	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	|    	|
 * | 85	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	|    	|    	|
 * | 86	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|
 * | 87	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|    	|
 * | 88	| 14dBm	| 14dBm	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|
 * | 89	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	| 14dBm	|    	|
 * | 90	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|
 * | 91	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	|    	|    	|
 * | 92	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	|    	|
 * | 93	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|    	|
 * | 94	| 14dBm	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|
 * | 95	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	| 14dBm	|    	|
 * | 96	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	|    	|
 * | 97	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	|    	|    	|
 * | 98	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|
 * | 99	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|    	|
 * | 100	| 14dBm	| 14dBm	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|
 * | 101	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	| 14dBm	|    	|
 * | 102	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|
 * | 103	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	|    	|    	|
 * | 104	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	| 14dBm	|
 * | 105	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|    	|
 * | 106	| 14dBm	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|
 * | 107	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	| 14dBm	|    	|
 * | 108	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	|    	|
 * | 109	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	|    	|    	|
 * | 110	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|
 * | 111	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|    	|
 * | 112	| 14dBm	| 14dBm	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|
 * | 113	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	| 14dBm	|    	|
 * | 114	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|
 * | 115	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	|    	|    	|
 * | 116	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	|    	|
 * | 117	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|    	|
 * | 118	| 14dBm	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|
 * | 119	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	| 14dBm	|    	|
 * | 120	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	| 14dBm	|
 * | 121	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	|    	|    	|
 * | 122	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|
 * | 123	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|    	|
 * | 124	| 14dBm	| 14dBm	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|
 * | 125	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	| 14dBm	|    	|
 * | 126	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|
 * | 127	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	|    	|    	|
 * | 128	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	|    	|
 * | 129	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|    	|
 * | 130	| 14dBm	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|
 * | 131	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	| 14dBm	|    	|
 * | 132	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	|    	|
 * | 133	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	|    	|    	|
 * | 134	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|
 * | 135	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|    	|
 * | 136	| 14dBm	| 14dBm	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|
 * | 137	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	| 14dBm	|    	|
 * | 138	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|
 * | 139	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	|    	|    	|
 * | 140	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	|    	|
 * | 141	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|    	|
 * | 142	| 14dBm	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|
 * | 143	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	| 14dBm	|    	|
 * | 144	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	|    	|
 * | 145	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	|    	|    	|
 * | 146	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|
 * | 147	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|    	|
 * | 148	| 14dBm	| 14dBm	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|
 * | 149	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	| 14dBm	|    	|
 * | 150	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|
 * | 151	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	|    	|    	|
 * | 152	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	| 14dBm	|
 * | 153	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|    	|
 * | 154	| 14dBm	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|
 * | 155	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	| 14dBm	|    	|
 * | 156	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	|    	|
 * | 157	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	|    	|    	|
 * | 158	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|
 * | 159	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|    	|
 * | 160	| 14dBm	| 14dBm	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|
 * | 161	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	| 14dBm	|    	|
 * | 162	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|
 * | 163	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	|    	|    	|
 * | 164	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	|    	|
 * | 165	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|    	|
 * | 166	| 14dBm	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|
 * | 167	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	| 14dBm	|    	|
 * | 168	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	| 14dBm	|
 * | 169	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	|    	|    	|
 * | 170	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|
 * | 171	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|    	|
 * | 172	| 14dBm	| 14dBm	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|
 * | 173	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	| 14dBm	|    	|
 * | 174	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|
 * | 175	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	|    	|    	|
 * | 176	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	|    	|
 * | 177	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|    	|
 * | 178	| 14dBm	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|
 * | 179	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	| 14dBm	|    	|
 * | 180	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	|    	|
 * | 181	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	|    	|    	|
 * | 182	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|
 * | 183	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|    	|
 * | 184	| 14dBm	| 14dBm	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|
 * | 185	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	| 14dBm	|    	|
 * | 186	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|
 * | 187	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	|    	|    	|
 * | 188	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	|    	|
 * | 189	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|    	|
 * | 190	| 14dBm	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|
 * | 191	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	| 14dBm	|    	|
 * | 192	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	|    	|
 * | 193	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	|    	|    	|
 * | 194	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|
 * | 195	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|    	|
 * | 196	| 14dBm	| 14dBm	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|
 * | 197	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	| 14dBm	|    	|
 * | 198	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|
 * | 199	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	|    	|    	|
 * | 200	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	| 14dBm	|
 * | 201	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|    	|
 * | 202	| 14dBm	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|
 * | 203	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	| 14dBm	|    	|
 * | 204	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	|    	|
 * | 205	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	|    	|    	|
 * | 206	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|
 * | 207	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|    	|
 * | 208	| 14dBm	| 14dBm	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|
 * | 209	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	| 14dBm	|    	|
 * | 210	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|
 * | 211	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	|    	|    	|
 * | 212	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	|    	|
 * | 213	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|    	|
 * | 214	| 14dBm	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|
 * | 215	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	| 14dBm	|    	|
 * | 216	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	| 14dBm	|
 * | 217	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	|    	|    	|
 * | 218	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|
 * | 219	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|    	|
 * | 220	| 14dBm	| 14dBm	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|
 * | 221	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	| 14dBm	|    	|
 * | 222	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|
 * | 223	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	|    	|    	|
 * | 224	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	|    	|
 * | 225	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|    	|
 * | 226	| 14dBm	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|
 * | 227	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	| 14dBm	|    	|
 * | 228	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	|    	|
 * | 229	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	|    	|    	|
 * | 230	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|
 * | 231	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|    	|
 * | 232	| 14dBm	| 14dBm	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|
 * | 233	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	| 14dBm	|    	|
 * | 234	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|
 * | 235	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	|    	|    	|
 * | 236	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	|    	|
 * | 237	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|    	|
 * | 238	| 14dBm	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|
 * | 239	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	| 14dBm	|    	|
 * | 240	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	|    	|
 * | 241	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	|    	|    	|
 * | 242	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|
 * | 243	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|    	|
 * | 244	| 14dBm	| 14dBm	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|
 * | 245	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	| 14dBm	|    	|
 * | 246	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|
 * | 247	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	|    	|    	|
 * | 248	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	| 14dBm	|
 * | 249	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|    	|
 * | 250	| 14dBm	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|
 * | 251	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	| 14dBm	|    	|
 * | 252	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	|    	|
 * | 253	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	|    	|    	|
 * | 254	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|
 * | 255	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|    	|
 * | 256	| 14dBm	| 14dBm	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|
 * | 257	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	| 14dBm	|    	|
 * | 258	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|
 * | 259	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	|    	|    	|
 * | 260	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	|    	|
 * | 261	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|    	|
 * | 262	| 14dBm	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|
 * | 263	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	| 14dBm	|    	|
 * | 264	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	| 14dBm	|
 * | 265	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	|    	|    	|
 * | 266	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|
 * | 267	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|    	|
 * | 268	| 14dBm	| 14dBm	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|
 * | 269	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	| 14dBm	|    	|
 * | 270	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|
 * | 271	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	|    	|    	|
 * | 272	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	|    	|
 * | 273	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|    	|
 * | 274	| 14dBm	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|
 * | 275	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	| 14dBm	|    	|
 * | 276	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	|    	|
 * | 277	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	|    	|    	|
 * | 278	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|
 * | 279	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|    	|
 * | 280	| 14dBm	| 14dBm	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|
 * | 281	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	| 14dBm	|    	|
 * | 282	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|
 * | 283	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	|    	|    	|
 * | 284	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	|    	|
 * | 285	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|    	|
 * | 286	| 14dBm	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|
 * | 287	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	| 14dBm	|    	|
 * | 288	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	|    	|
 * | 289	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	|    	|    	|
 * | 290	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|
 * | 291	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|    	|
 * | 292	| 14dBm	| 14dBm	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|
 * | 293	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	| 14dBm	|    	|
 * | 294	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|
 * | 295	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	|    	|    	|
 * | 296	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	| 14dBm	|
 * | 297	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|    	|
 * | 298	| 14dBm	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|
 * | 299	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	| 14dBm	|    	|
 * | 300	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	|    	|
 * | 301	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	|    	|    	|
 * | 302	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|
 * | 303	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|    	|
 * | 304	| 14dBm	| 14dBm	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|
 * | 305	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	| 14dBm	|    	|
 * | 306	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|
 * | 307	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	|    	|    	|
 * | 308	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	|    	|
 * | 309	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|    	|
 * | 310	| 14dBm	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|
 * | 311	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	| 14dBm	|    	|
 * | 312	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	| 14dBm	|
 * | 313	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	|    	|    	|
 * | 314	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|
 * | 315	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|    	|
 * | 316	| 14dBm	| 14dBm	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|
 * | 317	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	| 14dBm	|    	|
 * | 318	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|
 * | 319	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	|    	|    	|
 * | 320	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	|    	|
 * | 321	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|    	|
 * | 322	| 14dBm	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|
 * | 323	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	| 14dBm	|    	|
 * | 324	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	|    	|
 * | 325	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	|    	|    	|
 * | 326	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|
 * | 327	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|    	|
 * | 328	| 14dBm	| 14dBm	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|
 * | 329	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	| 14dBm	|    	|
 * | 330	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|
 * | 331	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	|    	|    	|
 * | 332	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	|    	|
 * | 333	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|    	|
 * | 334	| 14dBm	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|
 * | 335	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	| 14dBm	|    	|
 * | 336	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	|    	|
 * | 337	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	|    	|    	|
 * | 338	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|
 * | 339	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|    	|
 * | 340	| 14dBm	| 14dBm	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|
 * | 341	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	| 14dBm	|    	|
 * | 342	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|
 * | 343	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	|    	|    	|
 * | 344	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	| 14dBm	|
 * | 345	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|    	|
 * | 346	| 14dBm	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|
 * | 347	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	| 14dBm	|    	|
 * | 348	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	|    	|
 * | 349	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	|    	|    	|
 * | 350	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|
 * | 351	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|    	|
 * | 352	| 14dBm	| 14dBm	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|
 * | 353	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	| 14dBm	|    	|
 * | 354	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|
 * | 355	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	|    	|    	|
 * | 356	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	|    	|
 * | 357	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|    	|
 * | 358	| 14dBm	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|
 * | 359	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	| 14dBm	|    	|
 * | 360	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	| 14dBm	|
 * | 361	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	|    	|    	|
 * | 362	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|
 * | 363	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|    	|
 * | 364	| 14dBm	| 14dBm	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|
 * | 365	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	| 14dBm	|    	|
 * | 366	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|
 * | 367	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	|    	|    	|
 * | 368	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	|    	|
 * | 369	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|    	|
 * | 370	| 14dBm	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|
 * | 371	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	| 14dBm	|    	|
 * | 372	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	|    	|
 * | 373	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	|    	|    	|
 * | 374	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|
 * | 375	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|    	|
 * | 376	| 14dBm	| 14dBm	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|
 * | 377	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	| 14dBm	|    	|
 * | 378	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|
 * | 379	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	|    	|    	|
 * | 380	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	|    	|
 * | 381	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|    	|
 * | 382	| 14dBm	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|
 * | 383	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	| 14dBm	|    	|
 * | 384	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	|    	|
 * | 385	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	|    	|    	|
 * | 386	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|
 * | 387	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|    	|
 * | 388	| 14dBm	| 14dBm	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|
 * | 389	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	| 14dBm	|    	|
 * | 390	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|
 * | 391	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	|    	|    	|
 * | 392	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	| 14dBm	|
 * | 393	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|    	|
 * | 394	| 14dBm	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|
 * | 395	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	| 14dBm	|    	|
 * | 396	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	|    	|
 * | 397	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	|    	|    	|
 * | 398	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|
 * | 399	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|    	|
 * | 400	| 14dBm	| 14dBm	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|
 * | 401	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	| 14dBm	|    	|
 * | 402	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|
 * | 403	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	|    	|    	|
 * | 404	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	|    	|
 * | 405	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|    	|
 * | 406	| 14dBm	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|
 * | 407	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	| 14dBm	|    	|
 * | 408	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	| 14dBm	|
 * | 409	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	|    	|    	|
 * | 410	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|
 * | 411	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|    	|
 * | 412	| 14dBm	| 14dBm	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|
 * | 413	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	| 14dBm	|    	|
 * | 414	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|
 * | 415	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	|    	|    	|
 * | 416	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	|    	|
 * | 417	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|    	|
 * | 418	| 14dBm	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|
 * | 419	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	| 14dBm	|    	|
 * | 420	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	|    	|
 * | 421	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	|    	|    	|
 * | 422	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|
 * | 423	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|    	|
 * | 424	| 14dBm	| 14dBm	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|
 * | 425	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	| 14dBm	|    	|
 * | 426	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|
 * | 427	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	|    	|    	|
 * | 428	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	|    	|
 * | 429	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|    	|
 * | 430	| 14dBm	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|
 * | 431	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	| 14dBm	|    	|
 * | 432	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	|    	|
 * | 433	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	|    	|    	|
 * | 434	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|
 * | 435	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|    	|
 * | 436	| 14dBm	| 14dBm	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|
 * | 437	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	| 14dBm	|    	|
 * | 438	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|
 * | 439	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	|    	|    	|
 * | 440	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	| 14dBm	|
 * | 441	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|    	|
 * | 442	| 14dBm	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|
 * | 443	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	| 14dBm	|    	|
 * | 444	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	|    	|
 * | 445	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	|    	|    	|
 * | 446	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|
 * | 447	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|    	|
 * | 448	| 14dBm	| 14dBm	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|
 * | 449	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	| 14dBm	|    	|
 * | 450	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|
 * | 451	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	|    	|    	|
 * | 452	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	|    	|
 * | 453	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|    	|
 * | 454	| 14dBm	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|
 * | 455	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	| 14dBm	|    	|
 * | 456	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	| 14dBm	|
 * | 457	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	|    	|    	|
 * | 458	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|
 * | 459	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|    	|
 * | 460	| 14dBm	| 14dBm	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|
 * | 461	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	| 14dBm	|    	|
 * | 462	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|
 * | 463	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	|    	|    	|
 * | 464	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	|    	|
 * | 465	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|    	|
 * | 466	| 14dBm	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|
 * | 467	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	| 14dBm	|    	|
 * | 468	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	|    	|
 * | 469	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	|    	|    	|
 * | 470	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|
 * | 471	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|    	|
 * | 472	| 14dBm	| 14dBm	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|
 * | 473	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	| 14dBm	|    	|
 * | 474	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|
 * | 475	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	|    	|    	|
 * | 476	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	|    	|
 * | 477	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|    	|
 * | 478	| 14dBm	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|
 * | 479	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	| 14dBm	|    	|
 * | 480	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	|    	|
 * | 481	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	|    	|    	|
 * | 482	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|
 * | 483	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|    	|
 * | 484	| 14dBm	| 14dBm	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|
 * | 485	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	| 14dBm	|    	|
 * | 486	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|
 * | 487	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	|    	|    	|
 * | 488	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	| 14dBm	|
 * | 489	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|    	|
 * | 490	| 14dBm	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|
 * | 491	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	| 14dBm	|    	|
 * | 492	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	|    	|
 * | 493	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	|    	|    	|
 * | 494	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|
 * | 495	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|    	|
 * | 496	| 14dBm	| 14dBm	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|
 * | 497	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	| 14dBm	|    	|
 * | 498	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|
 * | 499	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	|    	|    	|
 * | 500	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	|    	|
 * | 501	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|    	|
 * | 502	| 14dBm	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|
 * | 503	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	| 14dBm	|    	|
 * | 504	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	| 14dBm	|
 * | 505	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	|    	|    	|
 * | 506	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|
 * | 507	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|    	|
 * | 508	| 14dBm	| 14dBm	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|
 * | 509	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|    	|
 * | 510	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|
 * | 511	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|    	|
 * | 512	|    	|    	|    	|    	|    	|    	|    	|    	|
 * | 513	| 21dBm	| 21dBm	| 21dBm	|    	|    	|    	|    	|    	|
 * | 514	| 21dBm	| 21dBm	| 21dBm	| 21dBm	|    	|    	|    	|    	|
 * | 515	| 23dBm	| 23dBm	| 23dBm	|    	|    	|    	|    	|    	|
 * | 516	| 23dBm	| 23dBm	| 23dBm	| 23dBm	| 23dBm	| 23dBm	|    	|    	|
 * | 517	| 27dBm	| 27dBm	| 27dBm	|    	|    	|    	| 27dBm	|    	|
 * | 518	| 27dBm	| 27dBm	| 27dBm	| 27dBm	|    	| 27dBm	|    	|    	|
 * | 519	| 27dBm	| 27dBm	| 27dBm	|    	| 27dBm	|    	|    	|    	|
 * | 520	| 27dBm	| 27dBm	| 27dBm	| 27dBm	|    	| 27dBm	|    	|    	|
 * | 521	| 27dBm	| 27dBm	| 27dBm	|    	|    	|    	|    	|    	|
 * | 522	| 27dBm	| 27dBm	| 27dBm	| 27dBm	| 27dBm	| 27dBm	| 27dBm	| 27dBm	|
 * | 523	| 27dBm	| 27dBm	| 27dBm	|    	|    	|    	|    	|    	|
 * | 524	| 27dBm	| 27dBm	| 27dBm	| 27dBm	|    	| 27dBm	|    	|    	|
 * | 525	| 27dBm	| 27dBm	| 27dBm	|    	| 27dBm	|    	|    	|    	|
 * | 526	| 27dBm	| 27dBm	| 27dBm	| 27dBm	|    	| 27dBm	|    	|    	|
 * | 527	| 27dBm	| 27dBm	| 27dBm	|    	|    	|    	| 27dBm	|    	|
 * | 528	| 23dBm	| 23dBm	| 23dBm	| 23dBm	| 23dBm	| 23dBm	|    	|    	|
 * | 529	| 23dBm	| 23dBm	| 23dBm	|    	|    	|    	|    	|    	|
 * | 530	| 21dBm	| 21dBm	| 21dBm	| 21dBm	|    	|    	|    	|    	|
 * | 531	| 21dBm	| 21dBm	| 21dBm	|    	|    	|    	|    	|    	|
 * | 532	|    	|    	|    	|    	|    	|    	|    	|    	|
 * | 533	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|    	|
 * | 534	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|
 * | 535	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|    	|
 * | 536	| 14dBm	| 14dBm	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|
 * | 537	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	| 14dBm	|    	|
 * | 538	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|
 * | 539	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	|    	|    	|
 * | 540	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	| 14dBm	|
 * | 541	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|    	|
 * | 542	| 14dBm	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|
 * | 543	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	| 14dBm	|    	|
 * | 544	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	|    	|
 * | 545	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	|    	|    	|
 * | 546	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|
 * | 547	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|    	|
 * | 548	| 14dBm	| 14dBm	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|
 * | 549	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	| 14dBm	|    	|
 * | 550	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|
 * | 551	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	|    	|    	|
 * | 552	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	|    	|
 * | 553	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|    	|
 * | 554	| 14dBm	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|
 * | 555	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	| 14dBm	|    	|
 * | 556	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	|    	|
 * | 557	| 14dBm	| 14dBm	| 14dBm	|    	| 14dBm	|    	|    	|    	|
 * | 558	| 14dBm	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|
 * | 559	| 14dBm	| 14dBm	| 14dBm	|    	|    	|    	|    	|    	|
 * | 560	|    	|    	|    	|    	|    	|    	|    	|    	|
 * 
 * You can call \ref armFskMaxPower() to get the maximal possible power 
 * in  function channel and baudrate.
 * 
 * \see group_fsk
 */
