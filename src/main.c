#include <signal.h>
#include "runtime.h"

static struct RuntimeState *state;

void sighandler(int signum)
{
    switch(signum)
    {
        case SIGINT:
        case SIGTERM:
        case SIGKILL:
        case SIGQUIT:
            cleanup(SIGINT);
            break;
    }
}

void cleanup(int ec)
{
    rt_free(state);
    printf("Terminated with exit code %i\n", ec);
}

void intercept_signals()
{
    signal(SIGINT, sighandler);
    signal(SIGTERM, sighandler);
#ifndef WIN32
    signal(SIGKILL, sighandler);
    signal(SIGQUIT, sighandler);
#endif
}

int main(char **args, int argc)
{
    // signals
    intercept_signals();

    // parse args
    uint32_t prog[] = {

    };

    RuntimeArgs rargs;
    rargs.program = prog;
    rargs.threadcount = 1;

    // run the program
    rt_init(rargs, state);
    int ec = rt_run(state);

    // cleanup and exit
    cleanup(ec);
    return ec;
}