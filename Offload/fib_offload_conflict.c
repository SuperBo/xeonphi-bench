#include <stdio.h>
#include "util.h"

#ifndef SIZE
#define SIZE 20
#endif

__attribute__((target(mic)))
double fib(int n);

int main(int argc, char* argv[]) {
    double result0, result1;
    double start_time0, end_time0;
    double start_time1, end_time1;

    int flag0 = 0;
    int flag1 = 0;

    printf("Problem size: %d\n", SIZE);
    start_time0 = gettime();
    #pragma offload target(mic:1) out(result0) signal(flag0)
    {
        #pragma omp parallel
        {
            #pragma omp master
            result0 = fib(SIZE);
        }
    }

    start_time1 = gettime();
    #pragma offload target(mic:1) out(result1) signal(flag1)
    {
        #pragma omp parallel 
        {
            #pragma omp master
            result1 = fib(SIZE);
        }
    }


    #pragma omp parallel shared(end_time0,end_time1)
    {
        #pragma omp sections
        {
            #pragma omp section
            {
                #pragma offload_wait target(mic:1) wait(flag0)
                end_time0 = gettime();
            }
            #pragma omp section
            {
                #pragma offload_wait target(mic:1) wait(flag1)
                end_time1 = gettime();
            }
        }
    }
    

   /* 
    #pragma offload_wait target(mic:1) wait(flag0) 
    end_time0 = gettime();

    #pragma offload_wait target(mic:1) wait(flag1)
    end_time1 = gettime();
    */

    double time0 = end_time0 - start_time0;
    double time1 = end_time1 - start_time1;

    printf("Result 0: %lf\n", result0);
    printf("Running time 0: %lf\n", time0);

    printf("Result 1: %lf\n", result1);
    printf("Running time 1: %lf\n", time1);

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

