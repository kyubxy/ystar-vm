#ifndef JOURNAL_H
#define JOURNAL_H

#include <stdio.h>

enum Verbosity
{
    V_DEBUG,
    V_INFO,
    V_WARNING,
    V_ERROR
};

int debug_init(char *logpath);
char* debug_openlog(enum Verbosity verb);
char* debug_close();

#define LOG(v) (debug_openlog(v))

#define LOG_D (debug_openlog(V_DEBUG))
#define LOG_I (debug_openlog(V_INFO))
#define LOG_W (debug_openlog(V_WARNING))
#define LOG_E (debug_openlog(V_ERROR))

#endif /* JOURNAL_H */