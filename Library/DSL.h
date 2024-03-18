#ifndef DSL_H_INCLUDED
#define DSL_H_INCLUDED

  /* Library of defines */

#define PUSH_COM(arg)            \
    if (arg == NULL)             \
        return NULL_PTR;         \
    StackPush (&proc->stk, arg); \
     IP += ARG_SIZE;             \

#define POP_COM(arg)                     \
    do                                   \
    {                                    \
        elem_t element = POISON;         \
        StackPop (&proc->stk, &element); \
        *arg = element;                  \
        IP += ARG_SIZE;                  \
    }                                    \
    while (0);                           \

//#define checkResult ()

//#define procDump ()

#define checkPtr(ptr)     \
    if (ptr == NULL)      \
        return NULL_PTR;  \

#define REALLOC(elem, type, size)                            \
    do                                                       \
    {                                                        \
        void* clTmp = realloc (elem, size * sizeof (type));  \
        if (clTmp == NULL)                                   \
            return REALLOC_ERROR;                            \
        elem = (type*) clTmp;                                \
    }                                                        \
    while (0);                                               \

#define CALLOC(elem, type, size)                     \
    do                                               \
    {                                                \
        void* clTmp = calloc (size, sizeof (type));  \
        if (clTmp == NULL)                           \
            return CALLOC_ERROR;                     \
        elem = (type*) clTmp;                        \
    }                                                \
    while (0);                                       \

#define FOPEN(ptr, name, mode)       \
    FILE* ptr = fopen (name, mode);  \
    if (ptr == NULL)                 \
        return OPEN_ERROR;           \

#define MATH_COM(command, operand)   \
    GetDigits (proc, &num2, &num1);  \
    num3 = num1 operand num2;        \
    StackPush (&proc->stk, &num3);   \
    num1 = POISON;                   \
    num2 = POISON;                   \

#define JUMP(command, operand)                        \
    if (proc->stk.data[proc->stk.size - 2] operand    \
        proc->stk.data[proc->stk.size - 1])           \
        IP = JumpTo (proc, IP);                       \
    StackPop (&proc->stk, &num1);                     \
    num1 = POISON;                                    \


#endif // DSL_H_INCLUDED
