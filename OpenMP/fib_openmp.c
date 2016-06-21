#include <stdio.h>
#include <omp.h>

#include "util.h"

#ifndef SIZE
#define SIZE 1000
#endif

double fib(int N);

int main(int argc, char** argv) {
    double time = gettime();
    double result;

    #pragma omp parallel shared(result)
    {
        #pragma omp single
        result = fib(SIZE);
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
    n1 = fib(n-1);
    #pragma omp task shared(n2)
    n2 = fib(n-2);

    #pragma omp taskwait
    return n1 + n2;
}
