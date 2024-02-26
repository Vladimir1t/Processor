#ifndef SPU_H_INCLUDED
#define SPU_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

#include "..\Assembler\Assembler.h"
#include "..\Stack\Stack.h"
#include "..\Onegin\Onegin.h"

const char*  fileSourse  = "res_ass.txt";  // bytecode
const char   MASK        = 3;              // 0000 0011
const size_t RAM_SIZE    = 50;

struct Spu
{
    Stack   stk;           // stack for arguments
    Stack   stkAdr;        // stack for addresses
    char*   arrayCommand;  // buffer of commands and arguments
    size_t  arraySize;     // size of the buffer
    elem_t* ram;           // random access memory
    elem_t  ramSize;
};

void SpuCtor (struct Spu* proc);

void SpuDtor (struct Spu* proc);

void FillArray (struct Spu* proc);

void GetDigits (struct Spu* proc, elem_t* num2, elem_t* num1);

size_t JumpTo (struct Spu* proc, size_t IP);

char GetCommand (struct Spu* proc, size_t IP);

elem_t GetArgument (struct Spu* proc, size_t IP);

void Push (struct Spu* proc, size_t IP);

void Pop (struct Spu* proc, size_t* IP);

#endif // SPU_H_INCLUDED
