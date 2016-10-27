%{
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

#include <stdio.h>
#include <string.h>
#include "entity.h"
#include "vt100.h"
#define YYDEBUG	1

//#define __GRA_DEBUG__
#ifdef __GRA_DEBUG__
	#define PRINT(vt100, str) printf(vt100);printf("%s\e[0m\n", str)
#else
	#define PRINT(vt100, str)
#endif

int yylex(void);				
void yyerror(const char * msg);	
extern FILE * yyin;				
%} 

%union {char str[32*1024];}
%type<str> INCLUDE
%type<str> ERROR
%type<str> MAC_IF
%type<str> MAC_ELIF
%type<str> MAC_ELSE
%type<str> MAC_ENDIF
%type<str> DEFINE
%type<str> _DEFINE
%type<str> ENUM
%type<str> STRUCT
%type<str> FUN_PROTO_ARM_PORT
%type<str> _FUN_PROTO_ARM_PORT
%type<str> FUN_STATIC_PROTO_ARM_PORT
%type<str> _FUN_STATIC_PROTO_ARM_PORT
%type<str> FUN_PROTO_ARM
%type<str> _FUN_PROTO_ARM
%type<str> FUN_STATIC_PROTO_ARM
%type<str> _FUN_STATIC_PROTO_ARM
%type<str> FUN_PROTO
%type<str> FUNCTION
%type<str> DOC


%token INCLUDE
%token ERROR

%token MAC_IF
%token MAC_ELIF
%token MAC_ELSE
%token MAC_ENDIF

%token DEFINE
%token _DEFINE

%token ENUM
%token STRUCT

%token FUN_PROTO_ARM_PORT
%token _FUN_PROTO_ARM_PORT
%token FUN_STATIC_PROTO_ARM_PORT
%token _FUN_STATIC_PROTO_ARM_PORT
%token FUN_PROTO_ARM
%token _FUN_PROTO_ARM
%token FUN_STATIC_PROTO_ARM
%token _FUN_STATIC_PROTO_ARM
%token FUN_PROTO

%token FUNCTION

%token DOC

%union {entity_t* ptrEnt;}
%type<ptrEnt> entity
%type<ptrEnt> mac
%type<ptrEnt> mac_elif_ent

%start entity 
%% 

entity		: mac
			{
				PRINT(F_Blue, "mac");
				$$ = $1;
				
				entSetRoot($$);
			}
			| entity mac
			{
				PRINT(F_Blue, "entity mac");
				entPush($1, $2);
				$$ = $1;
			}
			//INCLUDE
			|  INCLUDE
			{
				PRINT(F_Yellow, "INCLUDE");
				
				entity_t* ent1 = entNew(ENT_INCLUDE);
				entStrCat(ent1, $1);

				$$ = ent1;
			}
			| entity INCLUDE
			{
				PRINT(F_Yellow, "entity INCLUDE");
				
				entity_t* ent2 = entNew(ENT_INCLUDE);
				entStrCat(ent2, $2);
				
				entPush($1, ent2);
				$$ = $1;
			}
			//ERROR
			|  ERROR
			{
				PRINT(F_Yellow, "ERROR");
				
				entity_t* ent1 = entNew(ENT_ERROR);
				entStrCat(ent1, $1);

				$$ = ent1;
			}
			| entity ERROR
			{
				PRINT(F_Yellow, "entity ERROR");
				
				entity_t* ent2 = entNew(ENT_ERROR);
				entStrCat(ent2, $2);
				
				entPush($1, ent2);
				$$ = $1;
			}
			//DOC
			|  DOC
			{
				PRINT(F_Light_magenta, "DOC");
				
				entity_t* ent1 = entNew(ENT_DOC);
				entStrCat(ent1, $1);

				$$ = ent1;
			}
			| entity DOC
			{
				PRINT(F_Light_magenta, "entity DOC");
				
				entity_t* ent2 = entNew(ENT_DOC);
				entStrCat(ent2, $2);
				
				entPush($1, ent2);
				$$ = $1;
			}
			//ENUM
			|  ENUM
			{
				PRINT(F_Yellow, "ENUM");
				
				entity_t* ent1 = entNew(ENT_ENUM);
				entStrCat(ent1, $1);
				
				$$ = ent1;
			}
			| entity ENUM
			{
				PRINT(F_Yellow, "entity ENUM");
				
				entity_t* ent2 = entNew(ENT_ENUM);
				entStrCat(ent2, $2);
				
				entPush($1, ent2);
				$$ = $1;
			}
			//STRUCT
			|  STRUCT
			{
				PRINT(F_Yellow, "STRUCT");
				
				entity_t* ent1 = entNew(ENT_STRUCT);
				entStrCat(ent1, $1);
				
				$$ = ent1;
			}
			| entity STRUCT
			{
				PRINT(F_Yellow, "entity STRUCT");
				
				entity_t* ent2 = entNew(ENT_STRUCT);
				entStrCat(ent2, $2);
				
				entPush($1, ent2);
				$$ = $1;
			}
			//FUN_PROTO_ARM_PORT
			|  FUN_PROTO_ARM_PORT
			{
				PRINT(F_Dark_gray, "FUN_PROTO_ARM_PORT");
				
				entity_t* ent1 = entNew(ENT_FUN_PROTO_ARM_PORT);
				entStrCat(ent1, $1);
				
				$$ = ent1;
			}
			| entity FUN_PROTO_ARM_PORT
			{
				PRINT(F_Dark_gray, "entity FUN_PROTO_ARM_PORT");
				
				entity_t* ent2 = entNew(ENT_FUN_PROTO_ARM_PORT);
				entStrCat(ent2, $2);
				
				entPush($1, ent2);
				$$ = $1;
			}
			//_FUN_PROTO_ARM_PORT
			|  _FUN_PROTO_ARM_PORT
			{
				PRINT(F_Dark_gray, "_FUN_PROTO_ARM_PORT");
				
				entity_t* ent1 = entNew(ENT__FUN_PROTO_ARM_PORT);
				entStrCat(ent1, $1);
				
				$$ = ent1;
			}
			| entity _FUN_PROTO_ARM_PORT
			{
				PRINT(F_Dark_gray, "entity _FUN_PROTO_ARM_PORT");
				
				entity_t* ent2 = entNew(ENT_FUN_PROTO_ARM_PORT);
				entStrCat(ent2, $2);
				
				entPush($1, ent2);
				$$ = $1;
			}
			//FUN_STATIC_PROTO_ARM_PORT
			|  FUN_STATIC_PROTO_ARM_PORT
			{
				PRINT(F_Dark_gray, "FUN_STATIC_PROTO_ARM_PORT");
				
				entity_t* ent1 = entNew(ENT_FUN_STATIC_PROTO_ARM_PORT);
				entStrCat(ent1, $1);
				
				$$ = ent1;
			}
			| entity FUN_STATIC_PROTO_ARM_PORT
			{
				PRINT(F_Dark_gray, "entity FUN_STATIC_PROTO_ARM_PORT");
				
				entity_t* ent2 = entNew(ENT_FUN_STATIC_PROTO_ARM_PORT);
				entStrCat(ent2, $2);
				
				entPush($1, ent2);
				$$ = $1;
			}
			//_FUN_STATIC_PROTO_ARM_PORT
			|  _FUN_STATIC_PROTO_ARM_PORT
			{
				PRINT(F_Dark_gray, "_FUN_STATIC_PROTO_ARM_PORT");
				
				entity_t* ent1 = entNew(ENT__FUN_STATIC_PROTO_ARM_PORT);
				entStrCat(ent1, $1);
				
				$$ = ent1;
			}
			| entity _FUN_STATIC_PROTO_ARM_PORT
			{
				PRINT(F_Dark_gray, "entity _FUN_STATIC_PROTO_ARM_PORT");
				
				entity_t* ent2 = entNew(ENT__FUN_PROTO_ARM_PORT);
				entStrCat(ent2, $2);
				
				entPush($1, ent2);
				$$ = $1;
			}
			//FUN_PROTO_ARM
			|  FUN_PROTO_ARM
			{
				PRINT(F_Dark_gray, "FUN_PROTO_ARM");
				
				entity_t* ent1 = entNew(ENT_FUN_PROTO_ARM);
				entStrCat(ent1, $1);
				
				$$ = ent1;
			}
			| entity FUN_PROTO_ARM
			{
				PRINT(F_Dark_gray, "entity FUN_PROTO_ARM");
				
				entity_t* ent2 = entNew(ENT_FUN_PROTO_ARM);
				entStrCat(ent2, $2);
				
				entPush($1, ent2);
				$$ = $1;
			}
			//_FUN_PROTO_ARM
			|  _FUN_PROTO_ARM
			{
				PRINT(F_Dark_gray, "_FUN_PROTO_ARM");
				
				entity_t* ent1 = entNew(ENT__FUN_PROTO_ARM);
				entStrCat(ent1, $1);
				
				$$ = ent1;
			}
			| entity _FUN_PROTO_ARM
			{
				PRINT(F_Dark_gray, "entity _FUN_PROTO_ARM");
				
				entity_t* ent2 = entNew(ENT__FUN_PROTO_ARM);
				entStrCat(ent2, $2);
				
				entPush($1, ent2);
				$$ = $1;
			}
			//FUN_STATIC_PROTO_ARM
			|  FUN_STATIC_PROTO_ARM
			{
				PRINT(F_Dark_gray, "FUN_STATIC_PROTO_ARM");
				
				entity_t* ent1 = entNew(ENT_FUN_STATIC_PROTO_ARM);
				entStrCat(ent1, $1);
				
				$$ = ent1;
			}
			| entity FUN_STATIC_PROTO_ARM
			{
				PRINT(F_Dark_gray, "entity FUN_STATIC_PROTO_ARM");
				
				entity_t* ent2 = entNew(ENT_FUN_STATIC_PROTO_ARM);
				entStrCat(ent2, $2);
				
				entPush($1, ent2);
				$$ = $1;
			}
			//_FUN_STATIC_PROTO_ARM
			|  _FUN_STATIC_PROTO_ARM
			{
				PRINT(F_Dark_gray, "_FUN_STATIC_PROTO_ARM");
				
				entity_t* ent1 = entNew(ENT__FUN_STATIC_PROTO_ARM);
				entStrCat(ent1, $1);
				
				$$ = ent1;
			}
			| entity _FUN_STATIC_PROTO_ARM
			{
				PRINT(F_Dark_gray, "entity _FUN_STATIC_PROTO_ARM");
				
				entity_t* ent2 = entNew(ENT__FUN_STATIC_PROTO_ARM);
				entStrCat(ent2, $2);
				
				entPush($1, ent2);
				$$ = $1;
			}
			//FUN_PROTO
			|  FUN_PROTO
			{
				PRINT(F_Dark_gray, "FUN_PROTO");
				
				entity_t* ent1 = entNew(ENT_FUN_PROTO);
				entStrCat(ent1, $1);
				
				$$ = ent1;
			}
			| entity FUN_PROTO
			{
				PRINT(F_Dark_gray, "entity FUN_PROTO");
				
				entity_t* ent2 = entNew(ENT_FUN_PROTO);
				entStrCat(ent2, $2);
				
				entPush($1, ent2);
				$$ = $1;
			}
			//DEFINE
			|  DEFINE
			{
				PRINT(F_Cyan, "DEFINE");
				
				entity_t* ent1 = entNew(ENT_DEFINE);
				entStrCat(ent1, $1);
				
				$$ = ent1;
			}
			| entity DEFINE
			{
				PRINT(F_Cyan, "entity DEFINE");
				
				entity_t* ent2 = entNew(ENT_DEFINE);
				entStrCat(ent2, $2);
				
				entPush($1, ent2);
				$$ = $1;
			}
			//_DEFINE
			|  _DEFINE
			{
				PRINT(F_Cyan, "_DEFINE");
				
				entity_t* ent1 = entNew(ENT__DEFINE);
				entStrCat(ent1, $1);
				
				$$ = ent1;
			}
			| entity _DEFINE
			{
				PRINT(F_Cyan, "entity _DEFINE");
				
				entity_t* ent2 = entNew(ENT__DEFINE);
				entStrCat(ent2, $2);
				
				entPush($1, ent2);
				$$ = $1;
			}
			//FUNCTION
			|  FUNCTION
			{
				PRINT(F_Magenta, "FUNCTION");
				
				entity_t* ent1 = entNew(ENT_FUNCTION);
				entStrCat(ent1, $1);
				
				$$ = ent1;
			}
			| entity FUNCTION
			{
				PRINT(F_Magenta, "entity FUNCTION");
				
				entity_t* ent2 = entNew(ENT_FUNCTION);
				entStrCat(ent2, $2);
				
				entPush($1, ent2);
				$$ = $1;
			};
			
mac 		: MAC_IF MAC_ENDIF
			{
				PRINT(F_Light_blue, "MAC_IF MAC_ENDIF");
				
				entity_t* ent1 = entNew(ENT_MAC_IF);
				entity_t* ent2 = entNew(ENT_MAC_ENDIF);
				
				entStrCat(ent1, $1);
				entStrCat(ent2, $2);
				
				entPush(ent1, ent2);
				
				$$ = ent1;
			}
			| MAC_IF entity MAC_ENDIF
			{
				PRINT(F_Light_blue, "MAC_IF entity MAC_ENDIF");
				
				entity_t* ent1 = entNew(ENT_MAC_IF);
				entity_t* ent3 = entNew(ENT_MAC_ENDIF);
				
				entStrCat(ent1, $1);
				entStrCat(ent3, $3);
				
				entPush(ent1, $2);
				entPush($2, ent3);
				
				$$ = ent1;
			}
			| MAC_IF entity mac_elif_ent MAC_ENDIF
			{
				PRINT(F_Light_blue, "MAC_IF entity mac_elif_ent MAC_ENDIF");
				
				entity_t* ent1 = entNew(ENT_MAC_IF);
				entity_t* ent4 = entNew(ENT_MAC_ENDIF);
				
				entStrCat(ent1, $1);
				entStrCat(ent4, $4);
				
				entPush(ent1, $2);
				entPush($2, $3);
				entPush($3, ent4);
				
				$$ = ent1;
			}
			| MAC_IF mac_elif_ent MAC_ENDIF
			{
				PRINT(F_Light_blue, "MAC_IF mac_elif_ent MAC_ENDIF");
				
				entity_t* ent1 = entNew(ENT_MAC_IF);
				entity_t* ent3 = entNew(ENT_MAC_ENDIF);
				
				entStrCat(ent1, $1);
				entStrCat(ent3, $3);
				
				entPush(ent1, $2);
				entPush($2, ent3);
				
				$$ = ent1;
			};
mac_elif_ent : MAC_ELIF entity
			{
				PRINT(F_Light_blue, "MAC_ELIF entity");
				
				entity_t* ent1 = entNew(ENT_MAC_ELIF);
				entStrCat(ent1, $1);
				
				entPush(ent1, $2);
				$$ = ent1;
			}
			| MAC_ELIF entity mac_elif_ent
			{
				PRINT(F_Light_blue, "MAC_ELIF entity mac_elif_ent");
				
				entity_t* ent1 = entNew(ENT_MAC_ELIF);
				entStrCat(ent1, $1);
				
				entPush(ent1, $2);
				entPush($2, $3);
				$$ = ent1;
			}
			| MAC_ELSE entity
			{
				PRINT(F_Light_blue, "MAC_ELSE entity");
				
				entity_t* ent1 = entNew(ENT_MAC_ELSE);
				entStrCat(ent1, $1);
				
				entPush(ent1, $2);
				$$ = ent1;
			}
			| MAC_ELSE entity mac_elif_ent
			{
				PRINT(F_Light_blue, "MAC_ELSE entity mac_elif_ent");
				
				entity_t* ent1 = entNew(ENT_MAC_ELSE);
				entStrCat(ent1, $1);
				
				entPush(ent1, $2);
				entPush($2, $3);
				$$ = ent1;
			}
			| MAC_ELIF
			{
				PRINT(F_Light_blue, "MAC_ELIF");
				
				entity_t* ent1 = entNew(ENT_MAC_ELIF);
				entStrCat(ent1, $1);
				
				$$ = ent1;
			}
			| MAC_ELIF mac_elif_ent
			{
				PRINT(F_Light_blue, "MAC_ELIF mac_elif_ent");
				
				entity_t* ent1 = entNew(ENT_MAC_ELIF);
				entStrCat(ent1, $1);
				
				entPush(ent1, $2);
				$$ = ent1;
			}
			| MAC_ELSE
			{
				PRINT(F_Light_blue, "MAC_ELSE");
				
				entity_t* ent1 = entNew(ENT_MAC_ELSE);
				entStrCat(ent1, $1);
				
				$$ = ent1;
			}
			| MAC_ELSE mac_elif_ent
			{
				PRINT(F_Light_blue, "MAC_ELSE mac_elif_ent");
				
				entity_t* ent1 = entNew(ENT_MAC_ELSE);
				entStrCat(ent1, $1);
				
				entPush(ent1, $2);
				$$ = ent1;
			};
%%

void yyerror(const char * msg)
{
	printf("\e[31myyerror:\e[0m %s\n", msg);
}


















