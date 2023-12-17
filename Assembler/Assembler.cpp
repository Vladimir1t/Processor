#include "Assembler.h"

int main (int argc, char* argv[])
{
    //printf ("--%d--\n", NumberCommands);

    struct Strings Str = {0};
    static FILE* FILE_ERR = fopen ("file_error.txt", "w");

    FILE* sourseF = fopen (argv[1], "rb");
    assert (sourseF != NULL);

    FILE* resultF = fopen (argv[2], "w");
    assert (resultF != NULL);

    Str.fileSize = FileSize (sourseF);
    //printf ("size of file: %d\n", Str.fileSize);

    Str.textPointer = (char*) calloc (Str.fileSize + 1, sizeof(char));
    if (fread (Str.textPointer, sizeof(char), Str.fileSize, sourseF) != Str.fileSize)
        fputs ("ERROR. wrong fileSize\n", FILE_ERR);

    fileFormat isR = StringsCount (&Str);

    fclose (sourseF);

    Str.stringsP = (struct String*) calloc (Str.nStrings, sizeof(struct String));
    assert (Str.stringsP != NULL);

    StringsPointerRead (&Str, isR);

    StrPrint (&Str);
    //PrintSymbols (&Str);

    double* buffer = (double*) calloc (Str.nStrings, sizeof(double));
    assert (buffer != NULL);

    char  sep[] = {' ', '\0', '\n'};
    char* command = NULL;
    int   arg = 0;
    int   regFirstSymb = '\0', regSecondSymb = '\0';
    int   nStr = 0;
    int*  word = NULL;

    while (nStr < Str.nStrings)
    {
        command = strtok (Str.stringsP[nStr].pointer, sep);
        for (int i = 0; i < NumberCommands; i++)
        {
            if (!strcmp (AllCommands[i].command, command))
            {
                word = (int*) &buffer[nStr];
                word[0] = AllCommands[i].num;
                //printf ("word[0] = %d\n", word[0]);

                if (AllCommands[i].argMod == HAS_ARG)
                {
                    command = strtok (NULL, sep);

                    if (AllCommands[i].num == pop_r ||
                        AllCommands[i].num == push_r)
                    {
                        sscanf (command, "%c %c", &regFirstSymb, &regSecondSymb);
                        arg = regSecondSymb - regFirstSymb;
                        word[1] = arg;
                        //printf ("word[1] = %d\n", word[1]);
                        break;
                    }
                    else
                    {
                        sscanf (command, "%d", &arg);
                        //printf ("%d\n", arg);
                        word[1] = arg;
                        //printf ("word[1] = %d\n", word[1]);
                        break;
                    }
                }
                break;
            }
        }
        nStr++;
    }
    //for (int i = 0; i < Str.nStrings; i ++)
    //    printf ("%lg\n", buffer[i]);
    fwrite ((double*) buffer, sizeof(double), Str.nStrings, resultF);

    fclose (sourseF);
    fclose (resultF);
    ClearMemory (&Str);
    free (buffer);

    return 0;
}
