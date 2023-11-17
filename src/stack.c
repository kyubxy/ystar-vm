#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include "stack.h"

#include <stdio.h>

#define BASE(stack) ((stack)+sizeof(struct Stack))

void *get_next_block(struct Stack *s)
{
    return BASE(s) + (size_t)s->SP;
}

void *get_current_block(struct Stack *s)
{
    if (s->SP == 0)
        return NULL; // no block exists yet
    return BASE(s) + (size_t)s->SP - s->T_size;
}

// initialise stack
struct Stack *stack_init(size_t T_size, size_t stackSize)
{
    // need to account for header size
    size_t totalSize = stackSize + sizeof(struct Stack);
    struct Stack *loc = (struct Stack*)mmap(NULL, totalSize, PROT_READ | PROT_WRITE, 
        MAP_PRIVATE | MAP_ANONYMOUS, 0, 0);
    struct Stack *hdr = loc;
    hdr->SP = 0;
    hdr->T_size = T_size;
    hdr->ssize = totalSize;
    return loc;
}

// push memory to top of stack
// returns the next free memory block on the stack
void *stack_push(struct Stack *stack)
{
    if ((size_t)stack->SP >= stack->ssize - sizeof(struct Stack))
    {
        // stack is full
        return NULL;
    }

    void *bloc = get_next_block(stack);
    stack->SP += stack->T_size;
    return bloc;
}

// remove topmost item
// popping from the stack means the stack *no longer owns
// the data*
int stack_pop(struct Stack *stack, void *dest)
{
    if (stack->SP == 0)
        return 0;
    memcpy(dest, get_current_block(stack), stack->T_size);
    stack->SP -= stack->T_size;
}

// acquire pointer to topmost item
// unlike pop, peeking means the stack still owns the data
void *stack_peek(struct Stack *stack)
{
    return get_current_block(stack);
}

// get total number of items currently in stack
int stack_count(struct Stack *stack)
{
    return (size_t)stack->SP / stack->T_size;
}

// free the stack 
void stack_free(struct Stack *stack)
{
    munmap(stack, stack->ssize);
}