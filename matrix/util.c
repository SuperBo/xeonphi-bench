#include "util.h"

double dtime() {
    struct timeval time;
    gettimeofday(&time, NULL);

    return (double) time.tv_sec + (double) time.tv_usec * 1.0e-6;
}
