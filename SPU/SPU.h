#ifndef SPU_H_INCLUDED
#define SPU_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

#include "..\Assembler\Assembler.h"
#include "..\Stack\Stack.h"

const char* fileSourse = "..\\Assembler\\res_ass.txt.";

struct Spu
{
    Stack   stk;
    Stack   stkAdr;
    elem_t* arrayCommand;
    size_t  arraySize;
};

void SpuCtor (struct Spu* proc);

void SpuDtor (struct Spu* proc);

void FillArray (struct Spu* proc);

void GetDigits (struct Spu* proc, elem_t* num2, elem_t* num1);

int JumpTo (struct Spu* proc, int i);

#endif // SPU_H_INCLUDED
