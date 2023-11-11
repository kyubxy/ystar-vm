#include "instructions.h"
#include "cpu.h"
#include "errcodes.h"

// *yprime instruction table and definitions*

int noop(struct CPU *cpu, uint32_t *args)
{
    asm("nop"); 
    return E_OK;
}

int exit(struct CPU *cpu, uint32_t *args)
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
    // TODO: try optimising by including a specialised dup instruction
    int x = 0;
    cpu_pop(cpu, &x);
    cpu_push(cpu, x);
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
    bool cond = false;
    cpu_pop(cpu, &cond);
    if (cond)
        cpu->PC = args[0];
        return E_OK;
}

int call(struct CPU *cpu, uint32_t *args)
{
    struct Frame *frame;
    int fi = frame_init(frame, cpu->PC);
    if (fi != E_OK)
        return fi;
    if(stack_push(cpu->stack, frame) == -E_STACKOVERFLOW)
        return -E_SF_OVERFLOW;
    cpu->PC = args[0];
    return E_OK;
}

int ret(struct CPU *cpu, uint32_t *args)
{
    struct Frame *frame;
    if (stack_pop(cpu->stack, frame) == -E_STACKEMPTY)
        return -E_SF_UNDERFLOW;
    cpu->PC = frame->returnaddr;
    frame_free(frame);
    return E_OK;
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
    { "PUSH", 1, &push },
    { "POP",  0, &pop },
    { "ADD",  0, &add },
    { "EXIT", 0, &exit },
};

int instr_fetch(uint32_t *opcode_r, struct CPU *cpu)
{
    *opcode_r = cpu->program[cpu->PC];
    cpu->PC += table[*opcode_r].argc + 1;
    return E_OK;
}

int instr_execute(uint32_t opcode, struct CPU *cpu)
{
    // execute the instruction
    return table[opcode]
        .execute(cpu, cpu->program + cpu->PC);
}
