#ifndef CPU_H
#define CPU_H

#include <stdint.h>
#include <stdbool.h>
#include "frame.h"
#include "stack.h"
#include "errcodes.h"
#include "runtime.h"

#define M_STACKFRAMESIZE 64
#define M_STACKSIZE 8

struct CPU
{
    bool running;
    int PC;
    uint32_t *program;
    struct Stack *stack;    // stack of uint32_t
    struct Stack *frames;   // stack of struct Frame
};

// create/destroy
int cpu_init(struct CPU *cpu, uint32_t *program);
int cpu_free(struct CPU *cpu);

// execute one instruction on the CPU
int cpu_step(struct CPU *cpu);

// modify the CPU's main stack
int cpu_push(struct CPU *cpu, uint32_t value);
int cpu_pop(struct CPU *cpu, uint32_t *dest);
int cpu_peek(struct CPU *cpu, uint32_t *dest);

// modify the CPU's frame stack - see also the note on stack semantics
// in cpu.c
int cpu_sf_current(struct CPU *cpu, struct Frame *dest);
int cpu_sf_pushf(struct CPU *cpu);
int cpu_sf_popf(struct CPU *cpu);

#endif /* CPU_H */