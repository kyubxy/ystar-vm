#ifndef STACK_H
#define STACK_H

#include <stdint.h>
#include <stddef.h>

struct ElemProp
{
    size_t size;
    int(*free)(void *x);
};

struct Stack
{
    struct ElemProp T;
    unsigned int count; // TODO: maybe make 32 bit
    size_t size; // TODO: replace size with sp
    void *elems;
};

// initialise the stack on the heap
int stack_init(struct Stack *stack_o, struct ElemProp T, size_t stackSize);

// push item to top of stack
int stack_push(struct Stack *stack, void *src);

// remove topmost item
int stack_pop(struct Stack *stack, void *dest);

// acquire topmost item
int stack_peek(struct Stack *stack, void *dest);

// get total number of items currently in stack
int stack_count(struct Stack *stack);

// free the stack and its children elements
int stack_free(struct Stack *stack);

#endif /* STACK_H */