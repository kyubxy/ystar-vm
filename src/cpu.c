#include <stdlib.h>
#include <stdio.h>
#include "cpu.h"
#include "instructions.h"

int cpu_init(struct CPU *cpu, uint32_t *program)
{
    cpu = malloc(sizeof(struct CPU));
    cpu->PC = 0;
    cpu->program = program;

    // initialise the stacks
    /*
    int e = 0;
    e = stack_init(cpu->frames, (struct ElemProp){sizeof(struct Frame),
            &frame_free}, M_STACKFRAMESIZE);
    if (e != E_OK)
    {
        printf("CPU: failed to initialise stackframe");
        return e;
    }
    e = stack_init(cpu->stack, (struct ElemProp){ sizeof(uint32_t), NULL }, 
            M_STACKSIZE);
    if (e != E_OK)
    {
        printf("CPU: failed to initialise stack");
        return e;
    }

    cpu_sf_pushf(cpu); // push the initial frame
    */
    cpu->running = true;
    return E_OK;
}

// represents one clock cycle of the CPU
int cpu_step(struct CPU *cpu)
{
    uint32_t opcode;
    int fet = instr_fetch(&opcode, cpu);
    if (fet != E_OK) return fet; 
    return instr_execute(opcode, cpu);
}

int fetch(struct CPU *cpu, uint32_t *opcode_r)
{
    *opcode_r = cpu->program[cpu->PC];
    // TODO: PC inc is wrong
    return E_OK;
}

int decode(struct CPU *cpu, uint32_t *opcode_r, instr inst)
{

    cpu->PC += table[*opcode_r].argc + 1;
}

int instr_execute(struct CPU *cpu, instr inst)
{
    // execute the instruction
    return table[opcode]
        .execute(cpu, cpu->program + cpu->PC);
}

int cpu_free(struct CPU *cpu)
{
    cpu->running = false;
    stack_free(cpu->frames);
    stack_free(cpu->stack);
    free(cpu);
}

// NOTE: stack frame semantics don't exactly line up
//      with conventional stack semantics.
//      ie. popping doesn't return the top value.
//      we indicate this with the f suffix

int cpu_sf_current(struct CPU *cpu, struct Frame *dest)
{
    return stack_peek(cpu->frames, dest);
}

// this thing sets the return address to the current
// PC, idk if this is a good idea or not
int cpu_sf_pushf(struct CPU *cpu)
{
    struct Frame *fr;
    frame_init(fr, cpu->PC);
    return stack_push(cpu->frames, fr);
}

int cpu_sf_popf(struct CPU *cpu)
{
    struct Frame *f;
    if (stack_pop(cpu->stack, f) == -E_STACKEMPTY)
        return -E_SF_UNDERFLOW;
    frame_free(f);
    return E_OK;
}

// main stack semantics *do* line up with
// conventional stack semantics which is bing chilling

int cpu_push(struct CPU *cpu, uint32_t value)
{
    return stack_push(cpu->stack, &value);
}

int cpu_pop(struct CPU *cpu, uint32_t *dest)
{
    return stack_pop(cpu->stack, dest);
}

int cpu_peek(struct CPU *cpu, uint32_t *dest)
{
    return stack_peek(cpu->stack, dest);
}
