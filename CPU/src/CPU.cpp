#include "..\include\CPU.h"

FILE* ErrorFile = fopen ("..\\..\\Log\\error_CPU.txt", "w");

int main ()
{
    struct Cpu proc = {0};
    CpuCtor (&proc);

    FillArray (&proc);
                                       // get bytecode from sourse file
    FILE* resultF = fopen ("..\\..\\Log\\result.txt", "w");

    int result = ObeyCommands (resultF, &proc);

    return 0;
}

int ObeyCommands (FILE* resultF, struct Cpu* proc)
{
    elem_t num1    = POISON,
           num2    = POISON,
           num3    = POISON;
    elem_t address = POISON;

    for (size_t IP = 0; IP < proc->arraySize; IP += COM_SIZE)
    {

        switch (GetCommand (proc, IP))
        {
            case PUSH:
                Push (proc, IP);
                IP += ARG_SIZE;
                break;

            case POP:
                Pop (proc, &IP);
                break;

            case ADD:
                GetDigits (proc, &num2, &num1);
                num3 = num1 + num2;
                StackPush (&proc->stk, &num3);
                printf ("push %d\n", num3);
                num1 = POISON;
                num2 = POISON;
                break;

            case SUB:
                GetDigits (proc, &num2, &num1);
                num3 = num1 - num2;
                StackPush (&proc->stk, &num3);
                printf ("push %d\n",  num3);
                num1 = POISON;
                num2 = POISON;
                break;

            case DIV:
                GetDigits (proc, &num2, &num1);
                num3 = num1 / num2;
                StackPush (&proc->stk, &num3);
                printf ("push %d\n",  num3);
                num1 = POISON;
                num2 = POISON;
                break;

            case MUL:
                GetDigits (proc, &num2, &num1);
                num3 = num1 * num2;
                StackPush (&proc->stk, &num3);
                printf ("push %d\n",  num3);
                num1 = POISON;
                num2 = POISON;
                break;

            case OUT:
                for (int j = 0; j < proc->stk.size; j++)
                {
                    fprintf (resultF, "[%d] %d\n", j, proc->stk.data[j]);
                    printf ("[%d] %d\n", j, proc->stk.data[j]);
                }
                break;

            case IN:
                printf ("write a number\n");
                scanf (SPEC, &num1);
                StackPush (&proc->stk, &num1);
                num1 = POISON;
                break;

            case HLT:
                fclose (resultF);
                CpuDtor (proc);
                return 0;
                break;

            case JMP:
                JumpTo (proc, IP);
                break;

            case JB:
                if (proc->stk.data[proc->stk.size - 2] < proc->stk.data[proc->stk.size - 1])
                    IP = JumpTo (proc, IP);
                StackPop (&proc->stk, &num1);
                num1 = POISON;
                break;

            case JBE:
                if (proc->stk.data[proc->stk.size - 2] <= proc->stk.data[proc->stk.size - 1])
                    IP = JumpTo (proc, IP);
                StackPop (&proc->stk, &num1);
                num1 = POISON;
                break;

            case JA:
                if (proc->stk.data[proc->stk.size - 2] > proc->stk.data[proc->stk.size - 1])
                    IP = JumpTo (proc, IP);
                StackPop (&proc->stk, &num1);
                num1 = POISON;
                break;

            case JAE:
                if (proc->stk.data[proc->stk.size - 2] >= proc->stk.data[proc->stk.size - 1])
                    IP = JumpTo (proc, IP);
                StackPop (&proc->stk, &num1);
                num1 = POISON;
                break;

            case JE:
                if (proc->stk.data[proc->stk.size - 2] == proc->stk.data[proc->stk.size - 1])
                    IP = JumpTo (proc, IP);
                StackPop (&proc->stk, &num1);
                num1 = POISON;
                break;

            case JNE:
                if (proc->stk.data[proc->stk.size - 2] != proc->stk.data[proc->stk.size - 1])
                    IP = JumpTo (proc, IP);
                StackPop (&proc->stk, &num1);
                // POP(&num1);
                num1 = POISON;
                break;

            case CALL:
                address = IP;
                StackPush (&proc->stkAdr, &address);
                IP = JumpTo (proc, IP);
                address = POISON;
                break;

            case RET:
                StackPop (&proc->stkAdr, &address);
                IP = address;
                address = POISON;
                break;
        }
    }

    fclose (resultF);
    CpuDtor (proc);
    return 0;
}

void CpuCtor (Cpu* proc)
{
    StackCtor (&proc->stk, 2);        // construct Stack of arguments
    StackCtor (&proc->stkAdr, 2);     // construct Stack of addresses

    proc->arrayCommand = NULL;        // buffer
    proc->arraySize = 0;              // size of buffer

    proc->ramSize = RAM_SIZE;         // construct random access memory
    proc->ram = (elem_t*) calloc (RAM_SIZE, sizeof(elem_t));
    for (size_t i = 0; i < proc->ramSize; i++)
        proc->ram[i] = POISON;
}

void CpuDtor (struct Cpu* proc)
{
    for (size_t i = 0; i < proc->stk.size; i++)
        proc->stk.data[i] = POISON;

    StackDtor (&proc->stk);
    StackDtor (&proc->stkAdr);

    for (size_t i = 0; i < proc->arraySize; i++)
        proc->arrayCommand[i] = '\0';
    free (proc->arrayCommand);
    proc->arrayCommand = NULL;

    free (proc->ram);
}

void FillArray (struct Cpu* proc)
{
    struct Strings Str = {0};
    FILE* bytecode = fopen (fileSourse, "rb");
    assert (bytecode != NULL);

    Str.fileSize = FileSize (bytecode);   // measure the size of a bytecode

    proc->arraySize = Str.fileSize;
    proc->arrayCommand = (char*) calloc (proc->arraySize, sizeof(char));
    assert (proc->arrayCommand != NULL);

    if (fread (proc->arrayCommand, sizeof(char), Str.fileSize, bytecode) != Str.fileSize)
        fprintf (ErrorFile, "--Error. file reading error--\n");

    fclose (bytecode);
    free (Str.textPointer);
}

void GetDigits (struct Cpu* proc, elem_t* num2, elem_t* num1)
{
    StackPop (&proc->stk, num2);
    StackPop (&proc->stk, num1);
}

size_t JumpTo (struct Cpu* proc, size_t IP)
{
    printf ("jump to %d\n", GetArgument (proc, IP));
    return  GetArgument (proc, IP) - COM_SIZE;
}

char GetCommand (struct Cpu* proc, size_t IP)
{
    char command = *(char*) (proc->arrayCommand + IP);
    printf ("{%d}\n", command);
    return command;
}

elem_t GetArgument (struct Cpu* proc, size_t IP)
{
    int argument = *(int*) (proc->arrayCommand + IP + COM_SIZE);
    printf ("{%d}\n", argument);
    return argument;
}

void Push (struct Cpu* proc, size_t IP)
{
    elem_t arg = GetArgument (proc, IP);
    elem_t adr = POISON;

    switch (proc->arrayCommand[IP + 1] & MASK)
    {
        case NUM_MOD:
            StackPush (&proc->stk, &arg);
            printf ("push %d\n", arg);
            break;

        case REG_MOD:
            for (int j = 0; j < REGISTRS_NUM; j++)
                {
                    if (GetArgument (proc, IP) == (elem_t) reg[j].name[1] - (elem_t) reg[j].name[0])
                    {
                        StackPush (&proc->stk, &reg[j].value);
                        printf ("pushed from reg = %d\n", reg[j].value);
                        //reg[j].value = POISON;
                        break;
                    }
                }
            break;

        case RAM_MOD:
            adr = GetArgument (proc, IP);
            arg = proc->ram[adr];
            StackPush (&proc->stk, &arg);
            break;
    }
}

void Pop (struct Cpu* proc, size_t* IP)
{
    elem_t arg = POISON;
    elem_t adr = POISON;

    switch (proc->arrayCommand[*IP + 1] & MASK)
    {
        case NUM_MOD:
            StackPush (&proc->stk, &arg);
            printf ("push %d\n", arg);
            break;

        case REG_MOD:
             for (int j = 0; j < REGISTRS_NUM; j++)
                {
                    if (GetArgument (proc, *IP) == (elem_t) reg[j].name[1] - (elem_t) reg[j].name[0])
                    {
                        StackPop (&proc->stk, &arg);
                        printf ("popped into reg = %d\n", arg);
                        reg[j].value = arg;
                        arg = POISON;
                        *IP += ARG_SIZE;
                        break;
                    }
                }
            break;

        case RAM_MOD:
            adr = GetArgument (proc, *IP);
            StackPop (&proc->stk, &arg);
            proc->ram[adr] = arg;
            (*IP) += ARG_SIZE;
            break;
    }
}












