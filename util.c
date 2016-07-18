#include "util.h"

double gettime() {
    /*
    struct timespec timeval;
    clock_gettime(CLOCK, &timeval);

    return timeval.tv_sec + timeval.tv_nsec * 1e-9;
    */

    struct timeval tv;
    gettimeofday(&tv, 0);
    return tv.tv_sec + tv.tv_usec * 1e-6;
}
