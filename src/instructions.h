#include <stdint.h>

struct Inst
{
    uint32_t opcode;
    uint32_t *args;
};

int instr_decode(struct Inst *instr_r, struct CPU *cpu);
int instr_execute(struct Inst *instr_r, struct CPU *cpu);