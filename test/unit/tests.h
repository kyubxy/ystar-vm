#ifndef TESTS_H
#define TESTS_H

// stack
int sstack_init(void);
int sstack_clean(void);
void sstack_shouldInitAndFree(void);
void sstack_shouldPush(void);
void sstack_shouldPop(void);
void sstack_shouldPeek(void);

#endif /* TESTS_H */