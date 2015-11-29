%{
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

#include <stdio.h> 
#include <string.h> 
#include "entity.h"
#include "grammar.h"
#include "vt100.h"

//#define __LEX_DEBUG__
//#define __GRA_DEBUG__
#ifdef __LEX_DEBUG__
	#define PRINT(vt100) printf(vt100);printf("%s\e[0m", yylval.str)
	#define RETURN(val) continue
#else
	#define PRINT(vt100)
	#ifdef __GRA_DEBUG__
		#define RETURN(val) printf(#val"->"); return val
	#else
		#define RETURN(val) return val
	#endif
#endif

int accolade=0;
int cmptmac=0;
%}

%option noyywrap
%x inDoc
%x inDef
%x in_def
%x inFun
%x inMacIf
%x inMacElif

/* delete: 	__cplusplus define */
def_cpp			#ifdef[ ]__cplusplus[^#]*#endif[\n]*
/* delete: comment// */
comm1			[/]{2}[^\n]*[\n]*
/* delete: comment */
comm2			\/\*[^!][^\/]*\*\/[\n]*
/* delete: instruction ... */
init_arm				bzero[^\n]*
init_port				"arm->_port = port;"[\n]*

/* include */
include					#include[ \t]+[^\n]*

/* define */
_def_start				#define[ \t]+_
def_start				#define[ \t]+
def_end					[^\\]\n

/* macro */
mac_if					#if
mac_else				#else[^\n]*
mac_elif				#elif
mac_endif				#endif[^\n]*
mac_end					[^\\][\t ]*[\n]

/* doc */
doc_start				\/\*!
doc_addtogroup			\\addtogroup
doc_brief				\\brief
doc_end					\*\/

/* enum and struct */
enum				^[a-zA-Z0-9_ *\t]+enum[a-zA-Z0-9_ *\t\n\r]*\{[^}]+\}[^;]*;
struct				^[a-zA-Z0-9_ *\t]+struct[a-zA-Z0-9_ *\t\n\r]*\{[^}]+\}[^;]*;

/* fuction */
fun_arm_port_proto			^[a-zA-Z0-9_]+[ \t]+armPort[a-zA-Z0-9_]+\(void[a-zA-Z0-9_ \t\r\n,*]+\);
_fun_arm_port_proto			^[a-zA-Z0-9_]+[ \t]+_armPort[a-zA-Z0-9_]+\(void[a-zA-Z0-9_ \t\r\n,*]+\);
fun_arm_port_static_proto	^[a-zA-Z0-9_]+[ \t]+armPort[a-zA-Z0-9_]+\([a-zA-Z0-9_ \t\r\n,*]+\);
_fun_arm_port_static_proto	^[a-zA-Z0-9_]+[ \t]+_armPort[a-zA-Z0-9_]+\([a-zA-Z0-9_ \t\r\n,*]+\);
fun_arm_proto				^[a-zA-Z0-9_]+[ \t]+arm[a-zA-Z0-9_]+\(arm[a-zA-Z0-9]*_t[a-zA-Z0-9_ \t\r\n,*]+\);
_fun_arm_proto				^[a-zA-Z0-9_]+[ \t]+_arm[a-zA-Z0-9_]+\(arm[a-zA-Z0-9]*_t[a-zA-Z0-9_ \t\r\n,*]+\);
fun_arm_static_proto		^[a-zA-Z0-9_]+[ \t]+arm[a-zA-Z0-9_]+\([a-zA-Z0-9_ \t\r\n,*]+\);
_fun_arm_static_proto		^[a-zA-Z0-9_]+[ \t]+_arm[a-zA-Z0-9_]+\([a-zA-Z0-9_ \t\r\n,*]+\);
fun_proto					^[a-zA-Z0-9_]+[a-zA-Z0-9_ \t*]+\([a-zA-Z0-9_ \t\r\n,*]+\);
fun_start					^[a-zA-Z0-9_]+[a-zA-Z0-9_ \t*]+\([a-zA-Z0-9_ \t\r\n,*]+\)[ \t\r\n]\{
fun_end						\}

/* call fuction */
call_fun_arm				armN8[a-zA-Z0-9_]+\(
_call_fun_arm				_armN8[a-zA-Z0-9_]+\(
call_fun_arm_port			armPort[a-zA-Z0-9_]+\(
_call_fun_arm_port			_armPort[a-zA-Z0-9_]+\(

/* in function/define call this arm */
call_this_arm				arm->
/* in function call arm from arm */
call_arm_from_arm			arm(([ \t,]+)|([)]))
/* in function call port from arm */
call_port_from_arm			arm->_port[ \t,]*
/* in function call port open from arm */
call_port_open_from_arm		&arm->_port[ \t,]*

%%
{def_cpp}					{/* delete: __cplusplus define */}
{comm1}						{/* delete: comment */}
{comm2}						{/* delete: comment */}
{init_arm}					{/* delete: comment */}
{init_port}					{/* delete: comment */}
	
{doc_start}					{/* doc */
								strcpy(yylval.str, yytext);
								BEGIN(inDoc);
								//PRINT(B_Blue);
							}
<inDoc>{doc_addtogroup}		{/* doc */
								strcat(yylval.str, yytext);
								//PRINT(B_Blue);
							}
<inDoc>{doc_brief}			{/* doc */
								strcat(yylval.str, yytext);
								//PRINT(B_Blue);
							}
<inDoc>{doc_end}			{/* doc */
								strcat(yylval.str, yytext);
								BEGIN(INITIAL);
								PRINT(B_Blue);
								
								RETURN(DOC);
							}
<inDoc>.|\n					{/* doc */
								strcat(yylval.str, yytext);
								//PRINT(F_Blue);
							}

{enum}						{/* enum and struct */
								strcpy(yylval.str, yytext);
								PRINT(F_Light_green);
								
								RETURN(ENUM);
							}
{struct}					{/* enum and struct */
								strcpy(yylval.str, yytext);
								PRINT(F_Light_green);
								
								RETURN(STRUCT);
							}
	
{include}					{/* include */
								strcpy(yylval.str, yytext);
								PRINT(B_Green);
								RETURN(INCLUDE);
							}
	
{def_start}					{/* define */
								strcpy(yylval.str, yytext);
								BEGIN(inDef);
								//PRINT(B_Yellow);
							}
<inDef>{def_end}			{/* define */
								strcat(yylval.str, yytext);
								BEGIN(INITIAL);
								PRINT(B_Yellow);
								
								RETURN(DEFINE);
							}
<inDef>.|\n					{/* define */
								strcat(yylval.str, yytext);
								//PRINT(F_Yellow);
								
								//RETURN(DEF_IN);
							}
{_def_start}				{/* define */
								strcpy(yylval.str, yytext);
								BEGIN(in_def);
								//PRINT(B_Light_yellow);
							}
<in_def>{def_end}			{/* define */
								strcat(yylval.str, yytext);
								BEGIN(INITIAL);
								PRINT(B_Yellow);
								
								RETURN(_DEFINE);
							}
<in_def>.|\n				{/* define */
								strcat(yylval.str, yytext);
								//PRINT(F_Yellow);
								
								//RETURN(DEF_IN);
							}
{mac_if}					{/* macro */
								strcpy(yylval.str, yytext);
								BEGIN(inMacIf);
							}
{mac_elif}					{/* macro */
								strcpy(yylval.str, yytext);
								BEGIN(inMacElif);
							}
{mac_else}					{/* macro */
								strcpy(yylval.str, yytext);
								PRINT(B_Red);
								RETURN(MAC_ELSE);
							}
{mac_endif}					{/* macro */
								strcpy(yylval.str, yytext);
								PRINT(B_Red);
								RETURN(MAC_ENDIF);
							}
<inMacElif>{mac_end}		{/* macro */
								strcat(yylval.str, yytext);
								
								BEGIN(INITIAL);
									
								PRINT(B_Red);
								RETURN(MAC_ELIF);
							}
<inMacElif>.|\n				{/* macro */
								strcat(yylval.str, yytext);
							}
<inMacIf>{mac_end}			{/* macro */
								strcat(yylval.str, yytext);
								
								BEGIN(INITIAL);
									
								PRINT(B_Red);
								RETURN(MAC_IF);
							}
<inMacIf>.|\n					{/* macro */
								strcat(yylval.str, yytext);
							}
							
{fun_arm_port_proto}		{/* function */
								strcpy(yylval.str, yytext);
								PRINT(B_Magenta);
								
								RETURN(FUN_PROTO_ARM_PORT);
							}
{_fun_arm_port_proto}		{/* function */
								strcpy(yylval.str, yytext);
								PRINT(B_Light_magenta);
								
								RETURN(_FUN_PROTO_ARM_PORT);
							}
{fun_arm_port_static_proto}	{/* function */
								strcpy(yylval.str, yytext);
								PRINT(B_Cyan);
								
								RETURN(FUN_STATIC_PROTO_ARM_PORT);
							}
{_fun_arm_port_static_proto} {/* function */
								strcpy(yylval.str, yytext);
								PRINT(B_Light_cyan);
								
								RETURN(_FUN_STATIC_PROTO_ARM_PORT);
							}
{fun_arm_proto}				{/* function */
								strcpy(yylval.str, yytext);
								PRINT(B_Magenta);
								
								RETURN(FUN_PROTO_ARM);
							}
{_fun_arm_proto}			{/* function */
								strcpy(yylval.str, yytext);
								PRINT(B_Light_magenta);
								
								RETURN(_FUN_PROTO_ARM);
							}
{fun_arm_static_proto}		{/* function */
								strcpy(yylval.str, yytext);
								PRINT(B_Cyan);
								
								RETURN(FUN_STATIC_PROTO_ARM);
							}
{_fun_arm_static_proto}		{/* function */
								strcpy(yylval.str, yytext);
								PRINT(B_Light_cyan);
								
								RETURN(_FUN_STATIC_PROTO_ARM);
							}
{fun_proto}					{/* function */
								strcpy(yylval.str, yytext);
								PRINT(B_Dark_gray);
								
								RETURN(FUN_PROTO);
							}
{fun_start}					{/* function */
								strcpy(yylval.str, yytext);
								accolade=1;
								BEGIN(inFun);
								//PRINT(B_Light_blue);
								
								//RETURN(FUN_START);
							}
<inFun>\{					{/* function */
								strcat(yylval.str, yytext);
								accolade++;
								//PRINT(F_Light_blue);
								
								//RETURN(FUN_IN);
							}
<inFun>{fun_end}			{/* function */
								strcat(yylval.str, yytext);
								accolade--;
								//function end ?
								if(accolade == 0) //yes
								{
									BEGIN(INITIAL);
									PRINT(F_Light_blue);
									
									RETURN(FUNCTION);
								}
							}
<inFun>{call_fun_arm_port}	{/* function -> call fuction */
								strcat(yylval.str, "this->_port.");
								strcat(yylval.str, yytext+sizeof("armPort")-1);
								//strcpy(yylval.str, yytext);
								//PRINT(F_Yellow);
								
								//RETURN(FUN_IN);
							}
<inFun>{call_fun_arm}		{/* function -> call fuction */
								strcat(yylval.str, "this->");
								strcat(yylval.str, yytext+sizeof("armN8")-1);
								//strcpy(yylval.str, yytext);
								//PRINT(F_Green);
								
								//RETURN(FUN_IN);
							}
<inFun>{_call_fun_arm}		{/* function -> call fuction */
								strcat(yylval.str, "this->");
								strcat(yylval.str, "_");
								strcat(yylval.str, yytext+sizeof("_armN8")-1);
								//strcpy(yylval.str, yytext);
								//PRINT(B_Green);
								
								//RETURN(FUN_IN);
							}
<inFun>{call_arm_from_arm}	{/* function -> call arm from arm */
								if(yytext[yyleng-1] == ')')
									strcat(yylval.str, ")");
								else
									strcat(yylval.str, "");

								//PRINT(F_Red);
								
								//RETURN(FUN_IN);
							}
<inFun>{call_port_from_arm}	{/* function -> call port from arm (delete)*/
								//strcpy(yylval.str, yytext);
								//PRINT(B_Red);
							}
<inFun>{call_port_open_from_arm} {/* function -> call port from arm */
								strcat(yylval.str, "port");
								//PRINT(F_Red);
								
								//RETURN(FUN_IN);
							}
<inFun>{call_this_arm}		{/* function -> call this arm */
								strcat(yylval.str, "this->");
								//PRINT(B_Red);
								
								//RETURN(FUN_IN);
							}
<inFun>{init_arm}			{/* delete:  */}
<inFun>{init_port}			{/* delete:  */}
<inFun>.|\n					{/* function */
								strcat(yylval.str, yytext);
								//PRINT(F_Light_blue);
								
								//RETURN(FUN_IN);
							}
							
.|\n						{/* delete */
								strcpy(yylval.str, yytext);
								PRINT(C_raz);
							}
					
%%
















