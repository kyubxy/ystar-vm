#ifndef RUNTIME_H
#define RUNTIME_H

#include "cpu.h"

typedef struct RuntimeArgs
{
    uint32_t *program;
    int threadcount; // TODO:
} RuntimeArgs;

struct RuntimeState
{
    struct CPU *cpu;
};

int rt_init(RuntimeArgs args, struct RuntimeState *s);
int rt_run(struct RuntimeState *s);
int rt_free(struct RuntimeState *s);

#endif /* RUNTIME_H */