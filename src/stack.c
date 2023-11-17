#include <stdlib.h>
#include <string.h>
#include "stack.h"
#include "errcodes.h"

// initialise stack
struct Stack *stack_init(size_t T_size, size_t stackSize)
{
    return NULL;
}

// push memory to top of stack
// returns the next free memory block on the stack
void *stack_push(struct Stack *stack)
{

}

// remove topmost item
// popping from the stack means the stack *no longer owns
// the data*
void stack_pop(struct Stack *stack, void *dest)
{

}

// acquire topmost item
// unlike pop, peeking means the stack still owns the data
void *stack_peek(struct Stack *stack)
{

}

// get total number of items currently in stack
int stack_count(struct Stack *stack)
{

}

// free the stack and its children elements
int stack_free(struct Stack *stack)
{

}