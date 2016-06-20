#include <util.h>

double gettime() {
    struct timespec timeval;
    clock_gettime(CLOCK, &timeval);

    return timeval.tv_sec + timeval.tv_nsec * 1.0e-9;
}
