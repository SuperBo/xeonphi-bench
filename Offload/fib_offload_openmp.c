#include <stdio.h>
#include "util.h"

#ifndef SIZE
#define SIZE 20
#endif

__attribute__((target(mic)))
double fib(int n);

int main(int argc, char* argv[]) {
    double result;
    double time1;

    printf("Problem size: %d\n", SIZE);
    time1 = gettime();

    #pragma offload target(mic:0) out(result)
    {
        #pragma omp parallel
        {
            #pragma omp master
            result = fib(SIZE);
        }
    }
    time1 = gettime() - time1;

    printf("Result is %lf\n", result);
    printf("Running time: %lf\n", time1);


    return 0;
}

double fib(int n) {
    if (n < 2)
        return (double) n;

    double f1, f2;

    #pragma omp task shared(f1)
    f1 = fib(n-1);
    #pragma omp task shared(f2)
    f2 = fib(n-2);

    #pragma omp taskwait
    return f1 + f2;
}
