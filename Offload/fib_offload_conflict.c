#include <stdio.h>
#include "util.h"

#ifndef SIZE
#define SIZE 20
#endif

__attribute__((target(mic)))
double fib(int n);

int main(int argc, char* argv[]) {
    double result1, result2;
    double time1, time2;

    int flag1, flag2;

    printf("Problem size: %d\n", SIZE);

    time1 = gettime();
    #pragma offload target(mic:0) out(result1) signal(flag1)
    {
        #pragma omp parallel
        {
            #pragma omp master
            result1 = fib(SIZE);
        }
    }

    time2 = gettime();
    #pragma offload target(mic:0) out(result2) signal(flag2)
    {
        #pragma omp parallel
        {
            #pragma omp master
            result2 = fib(SIZE);
        }
    }

    #pragma omp parallel
    {
        #pragma omp sections
        {
            #pragma omp section
            {
            #pragma offload_wait target(mic:0) wait(flag1)
            time1 = gettime() - time1;
            }
            #pragma omp section
            {
            #pragma offload_wait target(mic:0) wait(flag2)
            time2 = gettime() - time2;
            }
        }
    }

    printf("Result 1 is %lf\n", result1);
    printf("Running time 1: %lf\n", time1);

    printf("Result 2 is %lf\n", result2);
    printf("Running time 2: %lf\n", time2);

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
