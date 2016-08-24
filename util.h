#include <sys/time.h>

#define CLOCK CLOCK_MONOTONIC

__attribute__((target(mic)))
double gettime();
