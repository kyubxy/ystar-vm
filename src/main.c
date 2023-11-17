#include <signal.h>
#include <stdio.h>
#include <assert.h>
#include "runtime.h"

static struct RuntimeState *state;

void cleanup(int ec)
{
    rt_free(state);
    printf("Terminated with exit code %i\n", ec);
}

void sighandler(int signum)
{
    // TODO: actually test whether this thing handles signals
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

    // parse args
    uint32_t prog[] = {
        0 // signle noop
    };

    // initialise the program
    state = rt_init(prog);
    assert(state != NULL);

    // run the program
    //int ec = rt_run(state);

    // cleanup and exit
    int ec = 0;
    cleanup(ec);
    return ec;
}
