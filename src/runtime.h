#ifndef RUNTIME_H
#define RUNTIME_H

#include "cpu.h"

struct RuntimeState
{
    struct CPU *cpu;
};

// TODO: replace the program pointer with more program args
//  eg. thread count etc
int rt_init(uint32_t *program, struct RuntimeState *s);
int rt_run(struct RuntimeState *s);
int rt_free(struct RuntimeState *s);

#endif /* RUNTIME_H */