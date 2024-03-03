#ifndef ASSEMBLER_H_INCLUDED
#define ASSEMBLER_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>

#include "..\..\Stack\include\stack.h"
#include "..\..\Onegin\include\onegin.h"
#include "..\..\Library\errors.h"

const size_t COMMAND_LEN   =  5;
const size_t REGISTRS_NUM  =  4;
const int    NUMBER_DIGITS =  9;
const size_t ARG_SIZE      =  4;
const size_t COM_SIZE      =  2;
const size_t POISON_ADR    = -1;
const size_t MARK_LEN      =  6;

const char  NUM_MOD        =  0;
const char  REG_MOD        =  1;
const char  RAM_MOD        =  2;

enum argument
{
    HAS_ARG = 1,
    NO_ARG  = 0,
};

enum COMMANDS
{
    PUSH   = 1,
    ADD    = 2,
    SUB    = 3,
    DIV    = 4,
    MUL    = 5,
    OUT    = 6,
    IN     = 7,
    POP    = 8,
    HLT    = -1,
    JMP    = 37,
    JB     = 38,
    JBE    = 39,
    JA     = 40,
    JAE    = 41,
    JE     = 42,
    JNE    = 43,
    CALL   = 21,
    RET    = 22

};

struct operation
{
    char command[COMMAND_LEN];
    int  num;
    int  argMod;
};

struct operation AllCommands[] =
{
    {"push", PUSH, HAS_ARG},
    {"add",  ADD,  NO_ARG},
    {"sub",  SUB,  NO_ARG},
    {"div",  DIV,  NO_ARG},
    {"mul",  MUL,  NO_ARG},
    {"out",  OUT,  NO_ARG},
    {"in",   IN,   NO_ARG},
    {"pop",  POP,  HAS_ARG},
    {"hlt",  HLT,  NO_ARG},
    {"jmp",  JMP,  HAS_ARG},
    {"jb",   JB,   HAS_ARG},
    {"jbe",  JBE,  HAS_ARG},
    {"ja",   JA,   HAS_ARG},
    {"jae",  JAE,  HAS_ARG},
    {"je",   JE,   HAS_ARG},
    {"jne",  JNE,  HAS_ARG},
    {"call", CALL, HAS_ARG},
    {"ret",  RET,  NO_ARG}
};

const size_t COMMANDS_NUM = sizeof(AllCommands) / sizeof(AllCommands[0]);

struct marks
{
    char   name[MARK_LEN];
    size_t address;
};

struct marks AllMarks[] =
{
    {"fact:", POISON_ADR},
    {"skip:", POISON_ADR},
    {"jump:", POISON_ADR},
};

const size_t MARKS_NUM = sizeof(AllMarks) / sizeof(AllMarks[0]);

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

int ReadSourseFile (FILE* sourseF, struct Strings* Str);

int MakeBytecode (FILE* resultF, struct Strings* Str);

int GetArgument (char* command, char* buffer, size_t* ptr);

char *strtokR (char *str, const char *delim);

//char *strtokR (char *str, const char *delim, char **saveptr);

#endif // ASSEMBLER_H_INCLUDED
