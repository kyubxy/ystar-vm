#include <stdint.h>

int instr_fetch(uint32_t *opcode_r, struct CPU *cpu);
int instr_execute(uint32_t opcode, struct CPU *cpu);