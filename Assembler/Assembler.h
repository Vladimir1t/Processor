#ifndef ASSEMBLER_H_INCLUDED
#define ASSEMBLER_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>

#include "..\Stack\Stack.h"
#include "..\Onegin\Onegin.h"

const size_t LEN_COMMAND   = 7;
const size_t REGISTRS_NUM  = 4;
const int    NUMBER_DIGITS = 9;
const size_t ARG_LEN       = 4;
const size_t COM_LEN       = 2;

const char  NUM_MOD        = 0;
const char  REG_MOD        = 1;
const char  RAM_MOD        = 2;

enum argument
{
    HAS_ARG = 1,
    NO_ARG  = 0,
};

enum COMMANDS
{
    push   = 1,
    add    = 2,
    sub    = 3,
    dif    = 4,
    mul    = 5,
    out    = 6,
    in     = 7,
    pop    = 8,
    hlt    = -1,
    jmp    = 37,
    jb     = 38,
    jbe    = 39,
    ja     = 40,
    jae    = 41,
    je     = 42,
    jne    = 43,
    call   = 21,
    ret    = 22

};

struct operation
{
    char command[LEN_COMMAND];
    int  num;
    int  argMod;
};

struct operation AllCommands[] =
{
    {"push",   push,   HAS_ARG},
    {"add",    add,    NO_ARG},
    {"sub",    sub,    NO_ARG},
    {"dif",    dif,    NO_ARG},
    {"mul",    mul,    NO_ARG},
    {"out",    out,    NO_ARG},
    {"in",     in,     NO_ARG},
    {"pop",    pop,    HAS_ARG},
    {"hlt",    hlt,    NO_ARG},
    {"jmp",    jmp,    HAS_ARG},
    {"jb",     jb,     HAS_ARG},
    {"jbe",    jbe,    HAS_ARG},
    {"ja",     ja,     HAS_ARG},
    {"jae",    jae,    HAS_ARG},
    {"je",     je,     HAS_ARG},
    {"jne",    jne,    HAS_ARG},
    {"call",   call,   HAS_ARG},
    {"ret",    ret,    NO_ARG}
};

const size_t NumberCommands = sizeof(AllCommands) / sizeof(AllCommands[0]) + 1;

struct registrs
{
    char   name[3];
    elem_t value;
};

struct registrs reg[REGISTRS_NUM] =
{
    {"ax", POISON},  // 23
    {"bx", POISON},  // 24
    {"cx", POISON},  // 25
    {"dx", POISON}   // 26
};

#endif // ASSEMBLER_H_INCLUDED
