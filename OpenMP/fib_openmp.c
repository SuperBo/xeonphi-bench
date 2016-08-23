#include <stdio.h>
#include <omp.h>

#include "util.h"

#ifndef SIZE
#define SIZE 20
#endif

double fib(int N);

int main(int argc, char** argv) {
    double result;

    printf("Problem size %d\n", SIZE);

    double run_time = gettime();

    #pragma omp parallel shared(result)
    {
        #pragma omp master
        result = fib(SIZE);
    }

    run_time = gettime() - run_time;

    printf("Fib(%d) = %lf\n", SIZE, result);
    printf("Running time: %.6lf\n", run_time);

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
