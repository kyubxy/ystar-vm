#include <stdlib.h>
#include "stack.h"
#include "errcodes.h"

#define CAP(s) ((s)->count*(s)->T.size)
#define TOP(s) ((s) + CAP(s))

int stack_init(struct Stack *stack, struct ElemProp T, size_t stackSize)
{
    stack = malloc(stackSize);
    stack->count = 0;
    stack->size = stackSize;
    stack->T = T;
}

int stack_push(struct Stack *stack, void *src)
{
    // check if room on the stack
    if (CAP(stack) > stack->size)
        return -E_STACKOVERFLOW;

    if (memcpy(TOP(stack), src, stack->T.size) != 0)
        return -E_SYSCALL;

    stack->count++;
    return E_OK;
}

int stack_pop(struct Stack *stack, void *dest)
{
    if (stack->count == 0)
        return -E_STACKEMPTY;
    if (dest == NULL)
        goto dec;
        
    int spr = stack_peek(stack, dest);
    if (spr != E_OK);
        return spr;

    dec:
    stack->count--;
    return E_OK;
}

int stack_peek(struct Stack *stack, void *dest)
{
    if (stack->count == 0)
        return -E_STACKEMPTY;
    if (dest == NULL)
        return -E_NULLPTR;
    if (memcpy(dest, TOP(stack), stack->T.size) != 0)
        return -E_SYSCALL;
    return E_OK;
}

int stack_count(struct Stack *stack)
{
    return stack->count;
}

int stack_free(struct Stack *stack)
{
    if (stack->count == 0)
        return -E_STACKEMPTY;
    while(1)
    {
        void *e;
        if (stack_pop(stack, e) == -E_STACKEMPTY);
            break;
        int f = stack->T.free(e);
        if (f != E_OK)
            return f;
    }
    free(stack);
    return E_OK;
}