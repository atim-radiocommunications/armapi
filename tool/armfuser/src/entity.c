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

#include "entity.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "vt100.h"
#include <sys/types.h>
#include <regex.h>

entity_t* _entRoot = NULL;

entity_t* entNew(entType_t type)
{
	entity_t* tmp = malloc(sizeof(entity_t));
	
	tmp->type = type;
	tmp->str[0] = '\0';
	tmp->nextEntity = NULL;
	tmp->backEntity = NULL;
	
	//set root
	if(entGetRoot() == NULL)
		entSetRoot(tmp);
	
	return tmp;
}

void entStrCat(entity_t* ent, char* str)
{
	size_t len = strlen(str);
	len--;
	while(	(str[len] == '\t') ||
			(str[len] == '\r') ||
			(str[len] == '\n'))
	{
		str[len] = '\0';
		len--;
	}
	
	strcat(ent->str, str);
}

void entPush(entity_t* ent, entity_t* entNext)
{
	entity_t* tmp = ent;
	entity_t* tmpback = NULL;
	
	while(tmp->nextEntity)
	{
		tmpback = tmp;
		tmp = tmp->nextEntity;
	}
	
	tmp->nextEntity = entNext;
	tmp->backEntity = tmpback;
}

void entSetRoot(entity_t* ent)
{
	_entRoot = ent;
}

entity_t* entGetRoot()
{
	return _entRoot;
}

void entCToCpp(entity_t* ent)
{
	char* cstr = NULL;
	switch(ent->type)
	{
		case ENT_MAC_IF:
		break;
		
		case ENT_MAC_ELIF:
		break;
		
		case ENT_MAC_ELSE:
		break;
		
		case ENT_ENUM:
		case ENT_STRUCT:
		{
			//char* fi = index(ent->str, '{');
			//char* li = rindex(ent->str, '}');
			
			//if(fi && li)
			//{
				//cstr = strdup(li);
				//*li = '\0';
				//while(strRepExp(fi, "arm", "Arm::"));
				//strcat(ent->str, cstr);
				//free(cstr);
			//}
			//else
			//{
				//while(strRepExp(ent->str, "arm", "Arm::"));
			//}
		}
		break;
		
		case ENT_MAC_ENDIF:
		break;
		
		case ENT_INCLUDE:
		{
			//strRepExp(ent->str, "<assert.h>",	"<cassert>");
			//strRepExp(ent->str, "<ctype.h>",	"<cctype>");
			//strRepExp(ent->str, "<errno.h>",	"<cerrno>");
			//strRepExp(ent->str, "<float.h>",	"<cfloat>");
			//strRepExp(ent->str, "<iso646.h>",	"<ciso646>");
			//strRepExp(ent->str, "<limits.h>",	"<climits>");
			//strRepExp(ent->str, "<locale.h>",	"<clocale>");
			//strRepExp(ent->str, "<math.h>",		"<cmath>");
			//strRepExp(ent->str, "<setjmp.h>",	"<csetjmp>");
			//strRepExp(ent->str, "<signal.h>",	"<csignal>");
			//strRepExp(ent->str, "<stdarg.h>",	"<cstdarg>");
			//strRepExp(ent->str, "<stdbool.h>",	"<cstdbool>");
			//strRepExp(ent->str, "<stddef.h>",	"<cstddef>");
			//strRepExp(ent->str, "<stdint.h>",	"<cstdint>");
			//strRepExp(ent->str, "<stdio.h>",	"<cstdio>");
			//strRepExp(ent->str, "<stdlib.h>",	"<cstdlib>");
			//strRepExp(ent->str, "<string.h>",	"<cstring>");
			//strRepExp(ent->str, "<time.h>",		"<ctime>");
			//strRepExp(ent->str, "<uchar.h>",	"<cuchar>");
			//strRepExp(ent->str, "<wchar.h>",	"<cwchar>");
			//strRepExp(ent->str, "<wctype.h>",	"<cwctype>");
		}
		break;
		
		case ENT_DEFINE:
			while(strRepExp(ent->str, "arm->", "this->"));
		break;
		
		case ENT__DEFINE:
			while(strRepExp(ent->str, "arm->", "this->"));
		break;
		
		case ENT_FUN_PROTO_ARM:
			strRepExp(ent->str, "[ \t]+armN8", " ");
			strRepExp(ent->str, "armN8_t[* \t]+arm[, \t\n\r]*", "");
		break;
		
		case ENT__FUN_PROTO_ARM:
			strRepExp(ent->str, "[ \t]+_armN8", " _");
			strRepExp(ent->str, "armN8_t[* \t]+arm[, \t\n\r]*", "");
		break;
		
		case ENT_FUN_STATIC_PROTO_ARM:
			strRepExp(ent->str, "[ \t]+armN8", " ");
			cstr = strdup(ent->str);
			strcpy(ent->str, "static ");
			strcat(ent->str, cstr);
			free(cstr);
		break;
		
		case ENT__FUN_STATIC_PROTO_ARM:
			strRepExp(ent->str, "[ \t]+_armN8", " _");
			cstr = strdup(ent->str);
			strcpy(ent->str, "static ");
			strcat(ent->str, cstr);
			free(cstr);
		break;
		
		case ENT_FUN_PROTO_ARM_PORT:
			strRepExp(ent->str, "[ \t]+armPort", " ");
			if(!strRepExp(ent->str, "Open[(]void[* \t]+port[, \t\n\r]*", "Open(void* port"))
				strRepExp(ent->str, "void[* \t]+port[, \t\n\r]*", "");
		break;
		
		case ENT__FUN_PROTO_ARM_PORT:
			strRepExp(ent->str, "[ \t]+_armPort", " _");
			strRepExp(ent->str, "void[* \t]+port[, \t\n\r]*", "");
		break;
		
		case ENT_FUN_STATIC_PROTO_ARM_PORT:
			strRepExp(ent->str, "[ \t]+armPort", " ");
			cstr = strdup(ent->str);
			strcpy(ent->str, "static ");
			strcat(ent->str, cstr);
			free(cstr);
		break;
		
		case ENT__FUN_STATIC_PROTO_ARM_PORT:
			strRepExp(ent->str, "[ \t]+_armPort", " _");
			cstr = strdup(ent->str);
			strcpy(ent->str, "static ");
			strcat(ent->str, cstr);
			free(cstr);
		break;
		
		case ENT_FUN_PROTO:
			cstr = strdup(ent->str);
			strcpy(ent->str, "extern \"C\"{");
			strcat(ent->str, cstr);
			strcat(ent->str, "}");
			free(cstr);
		break;
		
		case ENT_FUNCTION:
		{
			char* lf = index(ent->str, '\n');
			*lf = '\0';
			lf++;
			char strfunc[4*1024];
			strcpy(strfunc, lf);
			

			
			strRepExp(ent->str, "[ \t]+_armN8", " ArmN8::_");
			strRepExp(ent->str, "[ \t]+armN8", " ArmN8::");
			strRepExp(ent->str, "armN8_t[* \t]+arm[, \t\n\r]*", "");


			while(strRepExp(strfunc, "[(][ \t\r\n]*\"", "((const uint8_t*)\""));
			while(strRepExp(strfunc, "[,][ \t\r\n]*\"", ", (const uint8_t*)\""));			
			
			//while(strRepExp(strfunc, "_armN8", "this->_"));
			//while(strRepExp(strfunc, "armN8", "this->"));
	
			
			strcat(ent->str, "\n");
			strcat(ent->str, strfunc);
		}
		break;
		
		case ENT_DOC:
			while(strRepExp(ent->str, "\\\\param[ ]arm[^\n\r]*", ""));
			while(strRepExp(ent->str, "arm", "Arm::"));
			while(strRepExp(ent->str, "struct", "class"));
		break;
		
		case ENT_DOC_ARM_N8:
			while(strRepExp(ent->str, "\\\\param[ ]armN8[^\n\r]*", ""));
			while(strRepExp(ent->str, "armN8", "ArmN8::"));
			while(strRepExp(ent->str, "struct", "class"));
		break;
		
		case ENT_DOC_ARM_PORT:
			while(strRepExp(ent->str, "\\\\param[ ]armPort[^\n\r]*", ""));
			while(strRepExp(ent->str, "armPort", "ArmPort::"));
			while(strRepExp(ent->str, "struct", "class"));
		break;
	}
}

void entWrite(int fd, entity_t* ent)
{
	//switch(ent->type)
	//{
		//case ENT_MAC_IF:
		//case ENT_MAC_ELIF:
		//case ENT_MAC_ELSE:
		//write(fd, "\n", strlen("\n"));
		
		//case ENT_ENUM:
		//case ENT_STRUCT:
		//case ENT_FUN_PROTO_ARM:
		//case ENT__FUN_PROTO_ARM:
		//case ENT_FUN_STATIC_PROTO_ARM:
		//case ENT__FUN_STATIC_PROTO_ARM:
		//case ENT_FUNCTION:
		//case ENT_MAC_ENDIF:
		//case ENT_INCLUDE:
		//case ENT_DEFINE:
		//case ENT__DEFINE:
		//case ENT_FUN_PROTO_ARM_PORT:
		//case ENT__FUN_PROTO_ARM_PORT:
		//case ENT_FUN_STATIC_PROTO_ARM_PORT:
		//case ENT__FUN_STATIC_PROTO_ARM_PORT:
		//case ENT_FUN_PROTO:
		//case ENT_DOC:
		//break;
	//}
	
	write(fd, ent->str, strlen(ent->str));
	write(fd, "\n", strlen("\n"));
	
	switch(ent->type)
	{
		case ENT_ENUM:
		case ENT_STRUCT:
		case ENT_FUNCTION:
		case ENT_MAC_ENDIF:
		write(fd, "\n", strlen("\n"));
		
		case ENT_INCLUDE:
		case ENT_MAC_IF:
		case ENT_MAC_ELIF:
		case ENT_MAC_ELSE:
		case ENT_DEFINE:
		case ENT__DEFINE:
		case ENT_FUN_PROTO_ARM_PORT:
		case ENT__FUN_PROTO_ARM_PORT:
		case ENT_FUN_STATIC_PROTO_ARM_PORT:
		case ENT__FUN_STATIC_PROTO_ARM_PORT:
		case ENT_FUN_PROTO_ARM:
		case ENT__FUN_PROTO_ARM:
		case ENT_FUN_STATIC_PROTO_ARM:
		case ENT__FUN_STATIC_PROTO_ARM:
		case ENT_FUN_PROTO:
		case ENT_DOC:
		break;
	}
}

void entPrintTree(entity_t* ent)
{
	if(ent == NULL)
	{
		printf("Tree empty!\n");
		return;
	}
	
	entity_t* entTmp = ent;
	while(entTmp)
	{
		entPrint(entTmp);
		
		entTmp = entTmp->nextEntity;
	}
}

void entPrint(entity_t* ent)
{
	printf(F_Yellow"ent->type="C_raz);
	switch(ent->type)
	{
		case ENT_INCLUDE:
			printf("ENT_INCLUDE");
		break;
		
		case ENT_MAC_IF:
			printf("ENT_MAC_IF");
		break;
		
		case ENT_MAC_ELIF:
			printf("ENT_MAC_ELIF");
		break;
		
		case ENT_MAC_ELSE:
			printf("ENT_MAC_ELSE");
		break;
		
		case ENT_MAC_ENDIF:
			printf("ENT_MAC_ENDIF");
		break;
		
		case ENT_DEFINE:
			printf("ENT_DEFINE");
		break;
		
		case ENT__DEFINE:
			printf("ENT__DEFINE");
		break;
		
		case ENT_ENUM:
			printf("ENT_ENUM");
		break;
		
		case ENT_STRUCT:
			printf("ENT_STRUCT");
		break;
		
		case ENT_FUN_PROTO_ARM_PORT:
			printf("ENT_FUN_PROTO_ARM_PORT");
		break;
		
		case ENT__FUN_PROTO_ARM_PORT:
			printf("ENT__FUN_PROTO_ARM_PORT");
		break;
		
		case ENT_FUN_STATIC_PROTO_ARM_PORT:
			printf("ENT_FUN_STATIC_PROTO_ARM_PORT");
		break;
		
		case ENT__FUN_STATIC_PROTO_ARM_PORT:
			printf("ENT__FUN_STATIC_PROTO_ARM_PORT");
		break;
		
		case ENT_FUN_PROTO_ARM:
			printf("ENT_FUN_PROTO_ARM");
		break;
		
		case ENT__FUN_PROTO_ARM:
			printf("ENT__FUN_PROTO_ARM");
		break;
		
		case ENT_FUN_STATIC_PROTO_ARM:
			printf("ENT_FUN_STATIC_PROTO_ARM");
		break;
		
		case ENT__FUN_STATIC_PROTO_ARM:
			printf("ENT__FUN_STATIC_PROTO_ARM");
		break;
		
		case ENT_FUN_PROTO:
			printf("ENT_FUN_PROTO");
		break;
		
		case ENT_FUNCTION:
			printf("ENT_FUNCTION");
		break;
	}
	
	printf(F_Cyan"\nent->str="C_raz);
	printf("%s\n", ent->str);
}

int strRepExp(char* str, const char* exp, const char* strRep)
{
	regmatch_t pmatch;
	regex_t preg;
	int match = 0;
	
	//Find expression in str
	regcomp(&preg, exp, REG_EXTENDED);
	match = regexec(&preg, str, 1, &pmatch, 0);
	regfree(&preg);
	
	//No expression found ?
	if(match != 0)
		return 0;
	
	//Copy str
	char* cstr = strdup(str);
	
	//replace str
	strcpy(str+pmatch.rm_so, strRep);
	strcat(str, cstr+pmatch.rm_eo);
	
	free(cstr);
	return 1;
}































