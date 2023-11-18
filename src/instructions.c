#include "instructions.h"
#include "errcodes.h"

// *yprime instruction table and definitions*

int noop(struct CPU *cpu, uint32_t *args)
{
    asm("nop"); 
    return E_OK;
}

int halt(struct CPU *cpu, uint32_t *args)
{
    return E_EXIT; // we keep this positive to indicate an expected outcome
}

int push(struct CPU *cpu, uint32_t *args)
{
    return cpu_push(cpu, args[0]);
}

int pop(struct CPU *cpu, uint32_t *args)
{
    return cpu_pop(cpu, NULL);
}

int dup(struct CPU *cpu, uint32_t *args)
{
    int x;
    cpu_peek(cpu, &x);
    cpu_push(cpu, x);
    return E_OK;
}

int stor(struct CPU *cpu, uint32_t *args)
{
    struct Frame *frame;
    stack_peek(cpu->frames, frame);
    uint32_t value;
    cpu_pop(cpu, &value);
    frame_set_var(frame, args[0], value);
    return E_OK;
}

int load(struct CPU *cpu, uint32_t *args)
{
    struct Frame *frame;
    stack_peek(cpu->frames, frame);
    uint32_t value;
    frame_get_var(frame, args[0], &value);
    cpu_push(cpu, value);
    return E_OK;
}

int jmp(struct CPU *cpu, uint32_t *args)
{
    cpu->PC = args[0];
    return E_OK;
}

int jmpc(struct CPU *cpu, uint32_t *args)
{
    int cond = false;
    cpu_pop(cpu, &cond);
    if (cond)
        cpu->PC = args[0];
    return E_OK;
}

int call(struct CPU *cpu, uint32_t *args)
{
    cpu_sf_pushf(cpu);
    cpu->PC = args[0]; // jump to specified instr location
    return E_OK;
}

int ret(struct CPU *cpu, uint32_t *args)
{
    struct Frame *fr;
    cpu_sf_current(cpu, fr);
    cpu->PC = fr->returnaddr; // jump back to old location
    return cpu_sf_popf(cpu);
}


int add(struct CPU *cpu, uint32_t *args)
{
    uint32_t a, b = 0;
    cpu_pop(cpu, &a);
    cpu_pop(cpu, &b);
    int ret = a + b;
    cpu_push(cpu, ret);
    return E_OK;
}

int sub(struct CPU *cpu, uint32_t *args)
{
    uint32_t a, b = 0;
    cpu_pop(cpu, &a);
    cpu_pop(cpu, &b);
    int ret = a - b;
    cpu_push(cpu, ret);
    return E_OK;
}

int mul(struct CPU *cpu, uint32_t *args)
{
    uint32_t a, b = 0;
    cpu_pop(cpu, &a);
    cpu_pop(cpu, &b);
    int ret = a * b;
    cpu_push(cpu, ret);
    return E_OK;
}

// TODO: div and floating point

int isgt(struct CPU *cpu, uint32_t *args);
int isgte(struct CPU *cpu, uint32_t *args);
int islt(struct CPU *cpu, uint32_t *args);
int ilte(struct CPU *cpu, uint32_t *args);
int iseq(struct CPU *cpu, uint32_t *args);
int isne(struct CPU *cpu, uint32_t *args);
int land(struct CPU *cpu, uint32_t *args);
int lnot(struct CPU *cpu, uint32_t *args);
int lor(struct CPU *cpu, uint32_t *args);
int lxor(struct CPU *cpu, uint32_t *args);
int lsl(struct CPU *cpu, uint32_t *args);
int lsr(struct CPU *cpu, uint32_t *args);
int asr(struct CPU *cpu, uint32_t *args);


typedef struct Instr
{
    char iden[8];
    int argc;
    int (*execute)(struct CPU *cpu, uint32_t *args);
} Instr;

// **instruction set**
Instr table[] = {
    { "NOOP", 0, &noop },
    { "PUSH", 1, &push },
    { "POP",  0, &pop },
    { "ADD",  0, &add },
    { "HALT", 0, &halt },
};
