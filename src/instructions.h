#ifndef INSTR_H
#define INSTR_H

#include <stdint.h>
#include "cpu.h"

int instr_fetch(uint32_t *opcode_r, struct CPU *cpu);
int instr_execute(uint32_t opcode, struct CPU *cpu);

#endif