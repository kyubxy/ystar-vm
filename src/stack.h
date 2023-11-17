#ifndef STACK_H
#define STACK_H

#include <stdint.h>
#include <stddef.h>

struct Stack
{
    size_t T_size;  // size of each block
    size_t ssize;   // total size of the stack
    void *SP;       // pointer to the end of the topmost block
};

// note that this stack *contiguously stores the actual
// data, not just pointers to data*
// this is basically just a stack based heap allocator

// initialise the stack on the heap
struct Stack *stack_init(size_t T_size, size_t stackSize);

// push memory to top of stack
// returns the next free memory block on the stack
void *stack_push(struct Stack *stack);

// remove topmost item
// popping from the stack means the stack *no longer owns
// the data*
// returns true if successful, false if stack is empty
int stack_pop(struct Stack *stack, void *dest);

// acquire topmost item
// unlike pop, peeking means the stack still owns the data
void *stack_peek(struct Stack *stack);

// get total number of items currently in stack
int stack_count(struct Stack *stack);

// free the stack and its children elements
void stack_free(struct Stack *stack);

#endif /* STACK_H */