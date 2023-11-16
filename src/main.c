#include <signal.h>
#include <stdio.h>
#include "runtime.h"

static struct RuntimeState *state;

void cleanup(int ec)
{
    rt_free(state);
    printf("Terminated with exit code %i\n", ec);
}

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

void intercept_signals()
{
    signal(SIGINT, sighandler);
    signal(SIGTERM, sighandler);
#ifndef WIN32
    signal(SIGKILL, sighandler);
    signal(SIGQUIT, sighandler);
#endif
}

int main(int argc, char **args)
{
    // signals
    intercept_signals();

/*
    // parse args
    uint32_t prog[] = {

    };

    // run the program
    rt_init(prog, state);
    int ec = rt_run(state);

    // cleanup and exit
    cleanup(ec);
    return ec;
*/

}
