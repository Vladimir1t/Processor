#include "SPU.h"

int main ()
{
    struct Spu proc = {0};
    SpuCtor (&proc);

    FillArray (&proc);
    FILE* resultF = fopen ("result.txt", "w");

    elem_t num1 = POISON, num2 = POISON, num3 = POISON;

    for (int i = 0; i < proc.arraySize; i++)
    {
        switch (proc.arrayCommand[i])
        {
            case push:
                StackPush (&proc.stk, &proc.arrayCommand[i + 1]);
                printf ("push %d\n", proc.arrayCommand[i + 1]);
                i++;
                break;

            case pop:
                StackPop (&proc.stk, &num1);
                printf ("pop %d\n", num1);
                num1 = POISON;
                i++;
                break;

            case add:
                GetDigits (&proc, &num2, &num1);
                num3 = num1 + num2;
                StackPush (&proc.stk, &num3);
                printf ("push %d\n",  num3);
                num1 = POISON;
                num2 = POISON;
                i++;
                break;

            case sub:
                GetDigits (&proc, &num2, &num1);
                num3 = num1 - num2;
                StackPush (&proc.stk, &num3);
                printf ("push %d\n",  num3);
                num1 = POISON;
                num2 = POISON;
                i++;
                break;

            case dif:
                GetDigits (&proc, &num2, &num1);
                num3 = num1 / num2;
                StackPush (&proc.stk, &num3);
                printf ("push %d\n",  num3);
                num1 = POISON;
                num2 = POISON;
                i++;
                break;

            case mul:
                GetDigits (&proc, &num2, &num1);
                num3 = num1 * num2;
                StackPush (&proc.stk, &num3);
                printf ("push %d\n",  num3);
                num1 = POISON;
                num2 = POISON;
                i++;
                break;

            case out:
                for (int j = 0; j < proc.stk.size; j++)
                {
                    fprintf (resultF, "[%d] %d\n", j, proc.stk.data[j]);
                    printf ("[%d] %d\n", j, proc.stk.data[j]);
                }
                i++;
                break;

            case in:
                scanf ("%d", &num1);
                StackPush (&proc.stk, &num1);
                num1 = POISON;
                i++;
                break;

            case pop_r:
                for (int j = 0; j < REGISTRS_NUM; j++)
                {
                    if (proc.arrayCommand[i + 1] == (int) reg[j].name[1] - (int) reg[j].name[0])
                    {
                        StackPop (&proc.stk, &num1);
                        printf ("popped = %d\n", num1);
                        reg[j].value = num1;
                        num1 = POISON;
                        break;
                    }
                }
                i++;
                break;


            case push_r:
                for (int j = 0; j < REGISTRS_NUM; j++)
                {
                    if (proc.arrayCommand[i + 1] == (int) reg[j].name[1] - (int) reg[j].name[0])
                    {
                        printf ("pushed = %d\n", reg[j].value);
                        StackPush (&proc.stk, &reg[j].value);
                        reg[j].value = POISON;
                        break;
                    }
                }
                i++;
                break;

            case hlt:
                fclose (resultF);
                SpuDtor (&proc);
                return 0;
                i++;
                break;

            case jmp:
                JumpTo (&proc, i);
                break;

            case jb:
                //GetDigits (&proc, &num2, &num1);
                if (proc.stk.data[proc.stk.size - 2] < proc.stk.data[proc.stk.size - 1])
                    i = JumpTo (&proc, i);

                //reg[0].value = num1;
                //printf ("reg = %d\n", reg[1].value);
                StackPop (&proc.stk, &num1);
                num1 = POISON;
                num2 = POISON;
                break;

            case jbe:
                if (proc.stk.data[proc.stk.size - 2] <= proc.stk.data[proc.stk.size - 1])
                    i = JumpTo (&proc, i);
                StackPop (&proc.stk, &num1);
                num1 = POISON;
                break;

            case ja:
                if (proc.stk.data[proc.stk.size - 2] > proc.stk.data[proc.stk.size - 1])
                    i = JumpTo (&proc, i);
                StackPop (&proc.stk, &num1);
                num1 = POISON;
                break;

            case jae:
                if (proc.stk.data[proc.stk.size - 2] >= proc.stk.data[proc.stk.size - 1])
                    i = JumpTo (&proc, i);
                StackPop (&proc.stk, &num1);
                num1 = POISON;
                break;

            case je:
                if (proc.stk.data[proc.stk.size - 2] == proc.stk.data[proc.stk.size - 1])
                    i = JumpTo (&proc, i);
                StackPop (&proc.stk, &num1);
                num1 = POISON;
                break;

            case jne:
                if (proc.stk.data[proc.stk.size - 2] != proc.stk.data[proc.stk.size - 1])
                    i = JumpTo (&proc, i);
                /*{
                    address = proc.arrayCommand[i + 1];
                    printf ("jump to %d\n", address);
                    i = address - 1;
                }   */
                StackPop (&proc.stk, &num1);
                num1 = POISON;
                break;
        }
    }

    fclose (resultF);
    SpuDtor (&proc);
    return 0;
}

void SpuCtor (Spu* proc)
{
    StackCtor (&proc->stk, 2);        // Stack of arguments
    StackCtor (&proc->stkAdr, 2);     // Stack of addresses

    proc->arrayCommand = 0;           // buffer
    proc->arraySize = 0;              // size of buffer
}

void SpuDtor (Spu* proc)
{
    for (size_t i = 0; i < proc->stk.size; i++)
        proc->stk.data[i] = POISON;

    StackDtor (&proc->stk);
    StackDtor (&proc->stkAdr);

    for (size_t i = 0; i < proc->arraySize; i++)
        proc->arrayCommand[i] = POISON;
    free (proc->arrayCommand);
    proc->arrayCommand = NULL;
}

void FillArray (Spu* proc)
{
    struct Strings Str = {0};
    FILE* bytecode = fopen (fileSourse, "rb");
    assert (bytecode != NULL);

    Str.fileSize = FileSize (bytecode);

    Str.textPointer = (char*) calloc (Str.fileSize + 1, sizeof(char));
    assert (Str.textPointer != NULL);

    if (fread (Str.textPointer, sizeof(char), Str.fileSize, bytecode) != Str.fileSize)
        printf ("--Error. file reading error--\n");
    //printf ("size of file: %d\n", Str.fileSize);
    fclose (bytecode);

    fileFormat isR = StringsCount (&Str);

    Str.stringsP = (struct String*) calloc (Str.nStrings, sizeof(struct String));
    StringsPointerRead (&Str, isR);

    //PrintSymbols (&Str);

    size_t bufferSize = Str.fileSize / sizeof(double);
    double* buffer = (double*) calloc (bufferSize, sizeof(double));
    assert (buffer != NULL);

    int j = 0, count = 0;
    for (int i = 0; i < bufferSize; i++)      // fill buffer with doubles
    {
        while (count < 8)
        {
            char* array =  (char*) &buffer[i];
            array[count] = Str.textPointer[j];
            j++;
            count++;
        }
        count = 0;
    }
    (double*) buffer;

    proc->arraySize = bufferSize * 2;
    proc->arrayCommand = (elem_t*) calloc (proc->arraySize, sizeof(elem_t));
    assert (proc->arrayCommand != NULL);

    elem_t* com = NULL;
    int n = 0;

    for (int i = 0; i < bufferSize * 2; i += 2)
    {
        com = (elem_t*) &buffer[n];            // fill arrayCommand with integers: commands and arguments
        //printf ("com[0] = %d\n", com[0]);
        //printf ("com[1] = %d\n", com[1]);
        proc->arrayCommand[i] = com[0];
        proc->arrayCommand[i + 1] = com[1];
        n++;
    }
}

void GetDigits (struct Spu* proc, elem_t* num2, elem_t* num1)
{
    StackPop (&proc->stk, num2);
    StackPop (&proc->stk, num1);
}

int JumpTo (struct Spu* proc, int i)
{
    printf ("jump to %d\n", proc->arrayCommand[i + 1]);
    return proc->arrayCommand[i + 1] - 1;
}













