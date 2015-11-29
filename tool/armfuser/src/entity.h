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

#ifndef ENTITY_H
#define ENTITY_H

typedef enum
{
	ENT_INCLUDE,
	ENT_MAC_IF,
	ENT_MAC_ELIF,
	ENT_MAC_ELSE,
	ENT_MAC_ENDIF,
	ENT_DEFINE,
	ENT__DEFINE,
	ENT_ENUM,
	ENT_STRUCT,
	
	ENT_FUN_PROTO_ARM_PORT,
	ENT__FUN_PROTO_ARM_PORT,
	ENT_FUN_STATIC_PROTO_ARM_PORT,
	ENT__FUN_STATIC_PROTO_ARM_PORT,
	
	ENT_FUN_PROTO_ARM,
	ENT__FUN_PROTO_ARM,
	ENT_FUN_STATIC_PROTO_ARM,
	ENT__FUN_STATIC_PROTO_ARM,
	
	ENT_FUN_PROTO,
	ENT_FUNCTION,
	
	ENT_DOC,
	ENT_DOC_ARM_N8,
	ENT_DOC_ARM_PORT,
}entType_t;

typedef struct entity_e entity_t;
struct entity_e
{
	entType_t type;
	char str[4*1024];
	
	entity_t* nextEntity;
	entity_t* backEntity;
};

entity_t* entNew(entType_t type);
void entStrCat(entity_t* ent, char* str);
void entPush(entity_t* ent, entity_t* entNext);

void entSetRoot(entity_t* ent);
entity_t* entGetRoot();

void entCToCpp(entity_t* ent);
void entWrite(int fd, entity_t* ent);

int strRepExp(char* str, const char* exp, const char* strRep);

//Debug functions
void entPrintTree(entity_t* ent);
void entPrint(entity_t* ent);



#endif // ENTITY_H
