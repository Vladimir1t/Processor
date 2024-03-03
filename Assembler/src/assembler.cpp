#include "..\include\assembler.h"

FILE* ErrorFile = fopen ("..\\..\\Log\error_assembler.txt", "w");

int main (int argc, char* argv[])
{
    if (argc < 3)
        fprintf (ErrorFile, "--too few command arguments--\n");

    struct Strings Str = {0};        /*struct: textPointer, StringsP[], fileSize, nStrings*/
    Str.nStrings = 1;

    FILE* sourseF = fopen (argv[1], "rb");
    assert (sourseF != NULL);

    FILE* resultF = fopen (argv[2], "wb");
    assert (resultF != NULL);

    ReadSourseFile (sourseF, &Str);

    MakeBytecode (resultF, &Str);

    fclose (ErrorFile);

    return 0;
}

int ReadSourseFile (FILE* sourseF, struct Strings* Str)
{

    Str->fileSize = FileSize (sourseF);                                            // measure a size of sourseF
    printf ("size of file: %d\n", Str->fileSize);

    Str->textPointer = (char*) calloc (Str->fileSize + 1, sizeof(char));
    assert (Str->textPointer != NULL);

    if (fread (Str->textPointer, sizeof(char), Str->fileSize, sourseF) != Str->fileSize)
        fputs ("ERROR. wrong fileSize\n", ErrorFile);

    fclose (sourseF);

    fileFormat isR = StringsCount (Str);                                         // count a number of strings

    Str->stringsP = (struct String*) calloc (Str->nStrings, sizeof(struct String)); // make an array of pointers of strings
    assert (Str->stringsP != NULL);

    StringsPointerRead (Str, isR);                                               // divide text into array of strings

    StrPrint (Str);
    //PrintSymbols (Str);

    return 0;
 }

int MakeBytecode (FILE* resultF, struct Strings* Str)
{
    char   sep[]          = {' ', '\0', '\n'};                      // skip these symbols while reading file
    char*  command        = NULL;                                   // command from the array of the text
    size_t nStr           = 0;
    size_t ptr            = 0;
    short  commandInt     = 0;
    char*  pointer        = NULL;

    while (nStr < Str->nStrings)
    {
        command = strtokR (Str->stringsP[nStr].pointer, sep);
        //printf ("<%s>\n", command);
        for (int i = 0; i < COMMANDS_NUM; i++)
        {
            if (!strcmp (AllCommands[i].command, command))
            {
                if (AllCommands[i].argMod == HAS_ARG)
                {
                    ptr += ARG_SIZE;
                }
                ptr += COM_SIZE;
                break;
            }
        }

        pointer = strchr (Str->stringsP[nStr].pointer, ':');
        if (pointer != NULL)
        {
            for (size_t j = 0; j < MARKS_NUM; j++)
            {
                if (!strcmp (AllMarks[j].name,  pointer - (MARK_LEN - 2)))
                {
                    AllMarks[j].address = ptr;
                    break;
                }
            }
        }
        nStr++;
    }

    size_t len = ptr;
    printf ("len %d\n", len);
    command = NULL;
    ptr  = 0;
    nStr = 0;

    char* buffer = (char*) calloc (len, sizeof(char));                            // buffer of chars (bytecode)
    assert (buffer != NULL);

    while (nStr < Str->nStrings)
    {
        command = strtokR (Str->stringsP[nStr].pointer, sep);
        for (int i = 0; i < COMMANDS_NUM; i++)
        {
            if (!strcmp (AllCommands[i].command, command))
            {
                commandInt = (char) AllCommands[i].num;
                memcpy (buffer + ptr * sizeof(buffer[0]), &commandInt, sizeof(char));
                printf ("word[0] = %d\n", *(char*) (buffer + ptr));

                if (AllCommands[i].argMod == HAS_ARG)
                {
                    command = strtokR (NULL, sep);
                    GetArgument (command, buffer, &ptr);
                    break;
                }
                ptr += COM_SIZE;
            }
        }
        nStr++;
    }
    fwrite (buffer, sizeof(char), ptr, resultF);

    fclose (resultF);
    ClearMemory (Str);
    free (buffer);
    free (Str->textPointer);

    return SUCCESS;
}

int GetArgument (char* command, char* buffer, size_t* ptr)
{
    int   arg           = 0;
    int   regFirstSymb  = 0,
          regSecondSymb = 0;

    if (command == NULL)
    {
        fprintf (ErrorFile, "--Error. No argument--\n");
        return ERROR;
    }

    if (command[1] == 'x')
    {
        memcpy (buffer + (*ptr + 1) * sizeof(buffer[0]), &REG_MOD, sizeof(char));   // second byte = 1 (register mode)
        sscanf (command, "%c %c", &regFirstSymb, &regSecondSymb);                   // take 2 symbols of register and make them integers
        arg = regSecondSymb - regFirstSymb;
    }
    else if (command[0] == '[')
    {
        memcpy (buffer + (*ptr + 1) * sizeof(buffer[0]), &RAM_MOD, sizeof(char));    // first byte = 2 (ram mode)
        //printf ("word[0] = %d\n", *(char*) (buffer + ptr + 1));
        sscanf (command, "[%d]", &arg);
    }
    else if (strchr (command, ':') != NULL)
    {
        for (int j = 0; j < MARKS_NUM; j++)
        {
            if (!strcmp (AllMarks[j].name, command))
            {
                arg = AllMarks[j].address;
                printf ("adr %d\n", arg);
            }
        }
    }
    else
    {
        memcpy (buffer + (*ptr + 1) * sizeof(buffer[0]), &NUM_MOD, sizeof(char));    // first byte = 0 (stack mode)
        sscanf (command, "%d", &arg);
    }

    *ptr += COM_SIZE;
    memcpy (buffer + *ptr * sizeof(buffer[0]), &arg, sizeof(int));
    printf ("word[1] = %d\n", *(int*) (buffer + *ptr));
    *ptr += ARG_SIZE;

    return SUCCESS;
}

char* strtokR (char* str, const char* delim)
{
    static char* ptr;

    if (str != NULL)
    {
        ptr = str;
    }
    else
    {
        if (ptr == NULL)
        {
            return NULL;
        }
    }

    while (strchr(delim, *ptr) != NULL)
    {
        ptr++;
    }

    char* start = ptr;
    while (*ptr != '\0' && strchr(delim, *ptr) == NULL)
    {
        ptr++;
    }

    if (*ptr != '\0')
    {
        *ptr = '\0';
        ptr++;
    }

    return start;
}

