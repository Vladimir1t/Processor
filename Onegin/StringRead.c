#include "Onegin.h"

fileFormat StringsCount (struct Strings* StrP)
{
    assert (StrP->textPointer != NULL);
    fileFormat isR = UNDEFINED;

    size_t j = 0;
    for (; j < StrP->fileSize + 1; j++)
    {
        if (StrP->textPointer[j] == '\r')
        {
            StrP->textPointer[j] = '\0';
            (StrP->nStrings)++;
            j++;
            continue;
        }
        else if (StrP->textPointer[j] == '\n')
        {
            StrP->textPointer[j] = '\0';
            (StrP->nStrings)++;
            continue;
        }
    }
    (StrP->nStrings)++;
    //StrP->nStrings = StrP->nStrings  2 + 2;
    printf ("number of strings: %d\n", StrP->nStrings);

    char* elementP = strchr (StrP->textPointer, '\0');
    isR = (fileFormat) (StrP->nStrings > 1 && *(elementP + 1) == '\n');
    //printf ("isr = %d\n", isR);
    return isR;
}

void StringsPointerRead (struct Strings* StrP, fileFormat isR)
{
    assert (StrP->stringsP    != NULL);
    assert (StrP->textPointer != NULL);

    size_t n = 0;
    StrP->stringsP[n].pointer = StrP->textPointer;

    n++;

    for (size_t i = 0; i < StrP->fileSize; i++)
    {
        if (StrP->textPointer[i] == '\0' && n < StrP->nStrings)
        {
            if (isR == YES)
            {
                StrP->stringsP[n].pointer = StrP->textPointer + (i + 2);
                //printf ("strP: %s\n", StrP->stringsP[n].pointer);
                i++;
            }
            else if (isR == NO)
            {
                StrP->stringsP[n].pointer = StrP->textPointer + (i + 1);
                //printf ("strP: %s\n", StrP->stringsP[n].pointer);
            }
            //printf ("address of %d string: %d\n", n + 1, StrP->stringsP[n].pointer);
            n++;
        }
    }
}
