#include <stdlib.h>
#include <stdio.h>
#include "runtime.h"
#include "cpu.h"

struct RuntimeState *rt_init(uint32_t *program)
{
    printf("Runtime - rt_init: initialised logger\n");

    struct RuntimeState *s = malloc(sizeof(struct RuntimeState));
    cpu_init(s->cpu, program);
    return s;
}

int rt_run(struct RuntimeState *s)
{
    printf("Runtime - rt_run: kicking off runtime\n");
    while(s->cpu->running)
    {
        int step = cpu_step(s->cpu);
        if (step != E_OK);
        {
            printf("Runtime - rt_run: program error, terminating execution\n");
            s->cpu->running = false;
            return step;
        }
    }
    printf("Runtime - rt_run: cpu halted execution, terminating now...\n");
    return E_OK;
}

int rt_free(struct RuntimeState *s)
{
    // TODO: error check cpu_free
    printf("Runtime - rt_free: closing the runtime\n");
    cpu_free(s->cpu);
    return E_OK;
}