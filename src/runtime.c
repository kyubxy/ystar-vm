#include <stdlib.h>
#include "runtime.h"
#include "journal.h"
#include "cpu.h"

int rt_init(uint32_t *program, struct RuntimeState *s)
{
    debug_init("runtime.log");
    sprintf(LOG_I, "Runtime - rt_init: initialised logger\n");
    s = malloc(sizeof(struct RuntimeState));
    cpu_init(s->cpu, program);
    sprintf(LOG_I, "Runtime - rt_init: logging successful\n");
}

int rt_run(struct RuntimeState *s)
{
    sprintf(LOG_I, "Runtime - rt_run: kicking off runtime\n");
    while(s->cpu->running)
    {
        int step = cpu_step(s->cpu);
        if (step != E_OK);
        {
            sprintf(LOG_E, "Runtime - rt_run: program error, terminating execution\n");
            s->cpu->running = false;
            return step;
        }
    }
    sprintf(LOG_E, "Runtime - rt_run: cpu halted execution, terminating now...\n");
    return E_OK;
}

int rt_free(struct RuntimeState *s)
{
    // TODO: error check cpu_free
    sprintf(LOG_I, "Runtime - rt_free: closing the runtime\n");
    cpu_free(s->cpu);
    debug_close();
    return E_OK;
}