#include "instructions.h"
#include "cpu.h"
#include "errcodes.h"

// *yprime instruction table and definitions*

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
    // TODO: try optimising by including a specialised dup instruction
    int x = 0;
    cpu_pop(cpu, &x);
    cpu_push(cpu, x);
    cpu_push(cpu, x);
}

int add(struct CPU *cpu, uint32_t *args)
{
    uint32_t a, b = 0;
    cpu_pop(cpu, &a);
    cpu_pop(cpu, &b);
    int ret = a + b;
    cpu_push(cpu, ret);
}

int sub(struct CPU *cpu, uint32_t *args)
{
    uint32_t a, b = 0;
    cpu_pop(cpu, &a);
    cpu_pop(cpu, &b);
    int ret = a - b;
    cpu_push(cpu, ret);
}

int mul(struct CPU *cpu, uint32_t *args)
{
    uint32_t a, b = 0;
    cpu_pop(cpu, &a);
    cpu_pop(cpu, &b);
    int ret = a * b;
    cpu_push(cpu, ret);
}

// TODO: div and floating point

struct InstDef
{
    char iden[8];
    int argc;
    int (*execute)(struct CPU *cpu, uint32_t *args);
};

struct InstDef table[] = {
    { "PUSH", 1, &push },
    { "POP",  0, &pop },
    { "ADD",  0, &add },
};

int instr_decode(struct Inst *instr_r, struct CPU *cpu)
{
    // TODO:
    return E_OK;
}

int instr_execute(struct Inst *instr_r, struct CPU *cpu)
{
    return table[instr_r->opcode]
        .execute(cpu, instr_r->args);
}
