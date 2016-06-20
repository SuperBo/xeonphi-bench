#include <stdio.h>
#include <omp.h>

#include "util.h"

#ifndef N
#define N 1000
#endif

int main(int argc, char** argv) {
    double time = gettime();

    #pragma omp parallel
    {
        #pragma omp single
        double result = fib(N);
    }

    time = gettime() - time;

    printf("Running time: %.4lf\n", time);

    return 0;
}

double fib(int n) {
    if (n < 2)
        return (double) n;

    double n1, n2;

    #pragma omp task shared(n1)
    double n1 = fib(n-1);
    #pragma omp task shared(n2)
    double n2 = fib(n-2);

    #pragma omp taskwait
    return n1 + n2;
}
