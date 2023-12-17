#ifndef STRUCT_H_INCLUDED
#define STRUCT_H_INCLUDED

struct String
{
    char* pointer;
    int   size;
};

struct Strings
{
    String* stringsP;
    char*   textPointer;
    int     fileSize;
    int     nStrings;
};

enum Sort
{
    BEGINNING = 1,
    ENDING    = 0,
};

#endif // STRUCT_H_INCLUDED
