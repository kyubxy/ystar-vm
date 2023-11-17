#ifndef TESTS_H
#define TESTS_H

// stack
void sstack_shouldInitAndFree(void);
void sstack_shouldPush(void);
void sstack_shouldPop(void);
void sstack_shouldPeek(void);
void sstack_shouldNotInterfereOnPush(void);
void sstack_shouldPopIgnoreNull(void);
void sstack_shouldPopResume(void);

// frame
void sframe_shouldInitAndFree(void);
void sframe_shouldSetVar(void);
void sframe_shouldGetVar(void);

#endif /* TESTS_H */