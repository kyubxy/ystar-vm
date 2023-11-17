#include <stack.h>
#include <stdlib.h>
#include "CUnit/Basic.h"
#include "tests.h"

// stack should be able to initalise
void sstack_shouldInitAndFree(void)
{
    struct Stack *s = stack_init(sizeof(int), 100);
    CU_ASSERT_PTR_NOT_NULL(s);
    stack_free(s);
}

// should be able to push
void sstack_shouldPush(void)
{
    struct Stack *s = stack_init(sizeof(int), 100);
    stack_push(s);
    stack_push(s);
    stack_push(s);
    CU_ASSERT_EQUAL(3, stack_count(s));
    stack_free(s);
}

// old data should be preserved
void sstack_shouldNotInterfereOnPush(void)
{
    struct Stack *s = stack_init(sizeof(int), 100);
    int *p1 = stack_push(s); *p1 = 1;
    int *p2 = stack_push(s); *p2 = 2;
    int *p3 = stack_push(s); *p3 = 3;
    CU_ASSERT_EQUAL(3, stack_count(s));
    CU_ASSERT_EQUAL(1, *p1);
    CU_ASSERT_EQUAL(2, *p2);
    CU_ASSERT_EQUAL(3, *p3);
    stack_free(s);
}

void sstack_shouldPop(void)
{
    struct Stack *s = stack_init(sizeof(int), 100);
    int *p1 = stack_push(s); *p1 = 1;
    int *p2 = stack_push(s); *p2 = 2;
    int *p3 = stack_push(s); *p3 = 3;
    CU_ASSERT_EQUAL(3, stack_count(s));
    int dest;
    stack_pop(s, &dest);
    CU_ASSERT_EQUAL(2, stack_count(s));
    CU_ASSERT_EQUAL(dest, *p3);
    stack_free(s);
}

void sstack_shouldPopIgnoreNull(void)
{
    struct Stack *s = stack_init(sizeof(int), 100);
    int *p1 = stack_push(s); *p1 = 1;
    stack_pop(s, NULL);
    CU_ASSERT_EQUAL(1,1);
}

// should be able to overwrite popped location
void sstack_shouldPopResume(void)
{
    struct Stack *s = stack_init(sizeof(int), 100);
    stack_push(s); 
    stack_push(s); 
    int *p3 = stack_push(s); *p3 = 3;
    CU_ASSERT_EQUAL(3, stack_count(s));
    stack_pop(s, NULL);
    CU_ASSERT_EQUAL(2, stack_count(s));
    int *p3new = stack_push(s);
    CU_ASSERT_EQUAL(p3, p3new);
    stack_free(s);
}

void sstack_shouldPeek(void)
{
    struct Stack *s = stack_init(sizeof(int), 100);
    int *p1 = stack_push(s); *p1 = 1;
    int *p2 = stack_push(s); *p2 = 2;
    int *p3 = stack_push(s); *p3 = 3;
    CU_ASSERT_EQUAL(3, stack_count(s));
    int *dest = stack_peek(s);
    CU_ASSERT_EQUAL(3, stack_count(s));
    CU_ASSERT_EQUAL(dest, p3);
    stack_free(s);
}

// TODO: whitebox tests


