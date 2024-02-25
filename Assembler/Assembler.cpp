#include "Assembler.h"

FILE* ErrorFile = fopen ("ErrorFile.txt", "w");

int main (int argc, char* argv[])
{
    char  sep[] = {' ', '\0', '\n'};                                          // skip these symbols while reading
    char* command = NULL;                                                     // command from the array of the text
    int   arg = 0;
    int   regFirstSymb  = 0,
          regSecondSymb = 0;
    int   nStr = 0;
    int   ptr  = 0;
    short commandInt = 0;

    if (argc < 3)
        fprintf (ErrorFile, "--too few command arguments--\n");

    struct Strings Str = {0};        /*struct: textPointer, StringsP[], fileSize, nStrings*/
    Str.nStrings = 1;

    FILE* sourseF = fopen (argv[1], "rb");
    assert (sourseF != NULL);

    FILE* resultF = fopen (argv[2], "wb");
    assert (resultF != NULL);

    Str.fileSize = FileSize (sourseF);                                            // measure a size of sourseF
    printf ("size of file: %d\n", Str.fileSize);

    Str.textPointer = (char*) calloc (Str.fileSize + 1, sizeof(char));
    assert (Str.textPointer != NULL);

    if (fread (Str.textPointer, sizeof(char), Str.fileSize, sourseF) != Str.fileSize)
        fputs ("ERROR. wrong fileSize\n", ErrorFile);

    fclose (sourseF);
    size_t len = Str.nStrings * 4;

    fileFormat isR = StringsCount (&Str);                                         // count a number of strings

    Str.stringsP = (struct String*) calloc (Str.nStrings, sizeof(struct String)); // make an array of pointers of strings
    assert (Str.stringsP != NULL);

    StringsPointerRead (&Str, isR);                                               // divide text into array of strings

    StrPrint (&Str);
    //PrintSymbols (&Str);

    char* buffer = (char*) calloc (len, sizeof(char));                            // buffer of chars (bytecode)
    assert (buffer != NULL);

    while (nStr < Str.nStrings)
    {
        command = strtok (Str.stringsP[nStr].pointer, sep);
        for (int i = 0; i < NumberCommands; i++)
        {
            if (!strcmp (AllCommands[i].command, command))
            {
                commandInt = (char) AllCommands[i].num;

                memcpy (buffer + ptr * sizeof(buffer[0]), &commandInt, sizeof(char));
                //printf ("word[0] = %d\n", *(char*) (buffer + ptr));

                if (AllCommands[i].argMod == HAS_ARG)
                {
                    command = strtok (NULL, sep);
                    if (command == NULL)
                        fprintf (ErrorFile, "--Error. No argument--\n");

                    if (command[1] == 'x')
                    {
                        memcpy (buffer + (ptr + 1) * sizeof(buffer[0]), &REG_MOD, sizeof(char));   // second byte = 1 (register mode)
                        sscanf (command, "%c %c", &regFirstSymb, &regSecondSymb);                  // take 2 symbols of register and make them integers
                        arg = regSecondSymb - regFirstSymb;
                    }
                    else if (command[0] == '[')
                    {
                        memcpy (buffer + (ptr + 1) * sizeof(buffer[0]), &RAM_MOD, sizeof(char));    // first byte = 2 (ram mode)
                        //printf ("word[0] = %d\n", *(char*) (buffer + ptr + 1));
                        sscanf (command, "[%d]", &arg);
                    }
                    else
                    {
                        memcpy (buffer + (ptr + 1) * sizeof(buffer[0]), &NUM_MOD, sizeof(char));    // first byte = 0 (stack mode)
                        sscanf (command, "%d", &arg);
                    }

                    ptr += COM_LEN;
                    memcpy (buffer + ptr * sizeof(buffer[0]), &arg, sizeof(int));
                    //printf ("word[1] = %d\n", *(int*) (buffer + ptr));
                    ptr += ARG_LEN;
                    break;
                }
                ptr += COM_LEN;
            }
        }
        nStr++;
    }
    fwrite (buffer, sizeof(char), ptr, resultF);

    fclose (resultF);
    fclose (ErrorFile);
    ClearMemory (&Str);
    free (buffer);
    free (Str.textPointer);
    return 0;
}

