#include <stack.h>
#include "CUnit/Basic.h"
#include "tests.h"

int sstack_init(void)
{
    return 0;
}

int sstack_clean(void)
{
    return 0;
}

// stack should be able to initalise
void sstack_shouldInitAndFree(void)
{
    struct Stack *s = stack_init(sizeof(int), 100);
    CU_ASSERT_PTR_NOT_NULL(s);
    stack_free(s);
}

void sstack_shouldPush(void)
{
    struct Stack *s = stack_init(sizeof(int), 100);
    stack_push(s);
    stack_push(s);
    stack_push(s);
    CU_ASSERT_EQUAL(3, stack_count(s));
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
    CU_ASSERT_EQUAL(&dest, p3);
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

