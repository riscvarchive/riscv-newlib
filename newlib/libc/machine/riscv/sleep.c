/* copied from libc/posix/sleep.c - sleep function */

/* Written 2000 by Werner Almesberger */

#include <errno.h>
#include <time.h>
#include <unistd.h>
#include "weak_alias.h"

unsigned __sleep(unsigned seconds)
{
    struct timespec ts;

    ts.tv_sec = seconds;
    ts.tv_nsec = 0;
    if (!nanosleep(&ts,&ts)) return 0;
    if (errno == EINTR) return ts.tv_sec;
    return -1;
}

weak_alias (__sleep, sleep)
