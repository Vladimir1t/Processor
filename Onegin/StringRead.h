U#ifndef STRINGREAD_H_INCLUDED
#define STRINGREAD_H_INCLUDED

#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "StringStruct.h"

enum fileFormat
{
    YES       =  1,
    NO        =  0,
    UNDEFINED = -1,
};

int StringsCount        (struct Strings* StrP);

void StringsPointerRead (struct Strings* StrP, const int isR);

#endif // STRINGREAD_H_INCLUDED
