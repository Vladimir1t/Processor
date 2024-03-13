#include "..\include\assembler.h"

FILE* error_file_assembler = fopen ("..\\..\\Log\error_assembler.txt", "w");

int main (int argc, char* argv[])
{
    if (argc < 3)
        fprintf (error_file_assembler, "-- too few command arguments --\n");

    struct Strings Str = {0};        /*struct: textPointer, StringsP[], fileSize, nStrings*/
    Str.nStrings = 1;

    FILE* sourseF = fopen (argv[1], "rb");
    if (sourseF == NULL)
        fprintf (error_file_assembler, "-- sourseF wasn't read --\n");

    FILE* resultF = fopen (argv[2], "wb");
    if (resultF == NULL)
        fprintf (error_file_assembler, "-- resultF wasn't read --\n");

    ReadSourseFile (sourseF, &Str);

    if (MakeBytecode (resultF, &Str) != SUCCESS)
        fprintf (error_file_assembler, "-- bytcode wasn't made --\n");

    fclose (error_file_assembler);

    return 0;
}

int ReadSourseFile (FILE* sourseF, struct Strings* Str)
{

    Str->fileSize = FileSize (sourseF);                                            // measure a size of sourseF
    printf ("size of file: %d\n", Str->fileSize);

    Str->textPointer = (char*) calloc (Str->fileSize + 1, sizeof(char));
    assert (Str->textPointer != NULL);

    if (fread (Str->textPointer, sizeof(char), Str->fileSize, sourseF) != Str->fileSize)
        fputs ("ERROR. wrong fileSize\n", error_file_assembler);

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
    char         sep[]      = {' ', '\0', '\n'};                      // skip these symbols while reading file
    char*        command    = NULL;                                   // command from the array of the text
    size_t       nStr       = 0;
    size_t       ptr        = 0;
    short        commandNum = 0;
    size_t       len        = 0;
    size_t       marksNum   = 0;
    struct mark* allMarks   = (struct mark*) calloc (2, sizeof (struct mark));

    if (FindMarks (Str, &len, allMarks, &marksNum) != SUCCESS)
        return ERROR;

    char* buffer = (char*) calloc (len, sizeof (char));  // buffer of chars (bytecode)
    if (buffer == NULL)
    {
        fprintf (error_file_assembler, "-- buffer wasn't constructed --\n");
        return NULL_PTR;
    }
    while (nStr < Str->nStrings)
    {
        command = strtokR (Str->stringsP[nStr].pointer, sep);
        for (int i = 0; i < COMMANDS_NUM; i++)
        {
            if (!strcmp (AllCommands[i].command, command))
            {
                commandNum = (char) AllCommands[i].num;
                memcpy (buffer + ptr * sizeof (buffer[0]), &commandNum, sizeof (char));
                printf ("word[0] = %d\n", *(char*) (buffer + ptr));

                if (AllCommands[i].argMod == HAS_ARG)
                {
                    command = strtokR (NULL, sep);
                    if (GetArgument (command, buffer, &ptr, allMarks, marksNum) != SUCCESS)
                        return ERROR;
                    break;
                }
                ptr += COM_SIZE;
            }
        }
        nStr++;
    }
    fwrite (buffer, sizeof(char), len, resultF);

    fclose (resultF);
    ClearMemory (Str);
    free (buffer);

    return SUCCESS;
}

int GetArgument (char* command, char* buffer, size_t* ptr, struct mark* allMarks, size_t marksNum)
{
    int    arg           = 0;
    int    regFirstSymb  = 0,
           regSecondSymb = 0;

    if (command == NULL)
    {
        fprintf (error_file_assembler, "-- Error. No argument --\n");
        return ERROR;
    }

    if (command[1] == 'x')
    {
        memcpy (buffer + (*ptr + 1) * sizeof (buffer[0]), &REG_MOD, sizeof (char));   // second byte = 1 (register mode)
        sscanf (command, "%c %c", &regFirstSymb, &regSecondSymb);                     // take 2 symbols of register and make them integers
        arg = regSecondSymb - regFirstSymb;
    }
    else if (command[0] == '[')
    {
        memcpy (buffer + (*ptr + 1) * sizeof (buffer[0]), &RAM_MOD, sizeof (char));    // first byte = 2 (ram mode)
        sscanf (command, "[%d]", &arg);
    }
    else if (strchr (command, ':') != NULL)
    {
        for (int j = 0; j < marksNum; j++)
        {
            if (!strcmp (allMarks[j].name, command))
            {
                arg = allMarks[j].address;
                //printf ("adr %d\n", arg);
            }
        }
    }
    else
    {
        memcpy (buffer + (*ptr + 1) * sizeof (buffer[0]), &NUM_MOD, sizeof (char));    // first byte = 0 (stack mode)
        sscanf (command, "%d", &arg);
    }

    *ptr += COM_SIZE;
    memcpy (buffer + *ptr * sizeof (buffer[0]), &arg, sizeof (int));
    //printf ("word[1] = %d\n", *(int*) (buffer + *ptr));
    *ptr += ARG_SIZE;

    return SUCCESS;
}

int FindMarks (struct Strings* Str, size_t* len, struct mark* allMarks, size_t* marksNum)
{
    char   sep[]    = {' ', '\0', '\n'};                      // skip these symbols while reading file
    char*  command  = NULL;                                   // command from the array of the text
    size_t nStr     = 0;
    size_t ptr      = 0;
    char*  pointer  = NULL;

    while (nStr < Str->nStrings)
    {
        command = strtokR (Str->stringsP[nStr].pointer, sep);
        printf ("<%s>\n", command);
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
            memcpy (allMarks[*marksNum].name, pointer - (MARK_LEN - 1), MARK_LEN);
            printf ("mark %s\n", allMarks[*marksNum].name);
            allMarks[*marksNum].address = ptr;
            (*marksNum)++;

            allMarks = (struct mark*) realloc (allMarks, sizeof (mark) * (1 + *marksNum));
            if (allMarks == NULL)
                return NULL_PTR;
        }
        nStr++;
    }
    *len = ptr;

    for (int i = 0; i < *marksNum; i++)
        printf ("[%d] %s\n", i, allMarks[i].name);

    return SUCCESS;
}

char* strtokR (char* str, const char* delim)
{
    static char* ptr;

    if (str != NULL)
        ptr = str;

    else
    {
        if (ptr == NULL)
            return NULL;
    }
    while (strchr(delim, *ptr) != NULL)
        ptr++;

    char* start = ptr;
    while (*ptr != '\0' && strchr(delim, *ptr) == NULL)
        ptr++;

    if (*ptr != '\0')
    {
        *ptr = '\0';
        ptr++;
    }

    return start;
}
