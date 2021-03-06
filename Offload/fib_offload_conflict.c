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
    double start1, start2;
    double end1, end2;
    double mic_start1, mic_start2;

    int flag1, flag2;

    printf("Problem size: %d\n", SIZE);

    start1 = gettime();
    #pragma offload target(mic:0) out(result1, mic_start1) signal(flag1)
    {
        mic_start1 = gettime();
        #pragma omp parallel
        {
            #pragma omp master
            result1 = fib(SIZE);
        }
    }

    start2 = gettime();
    #pragma offload target(mic:0) out(result2, mic_start2) signal(flag2)
    {
        mic_start2 = gettime();
        #pragma omp parallel
        {
            #pragma omp master
            result2 = fib(SIZE);
        }
    }

    #pragma omp parallel shared(time1, time2, end1, end2, start1, start2)
    {
        #pragma omp sections
        {
            #pragma omp section
            {
                #pragma offload_wait target(mic:0) wait(flag1)
                end1 = gettime();
                time1 = end1 - start1;
            }
            #pragma omp section
            {
                #pragma offload_wait target(mic:0) wait(flag2)
                end2 = gettime();
                time2 = end2 - start2;
            }
        }
    }

    printf("Result 1 is %lf\n", result1);
    printf("Running time 1: %lf\n", time1);

    printf("Result 2 is %lf\n", result2);
    printf("Running time 2: %lf\n", time2);

    printf("Debug info\n");
    printf("Start1: %lf\n", start1);
    printf("Start2: %lf\n", start2);
    printf("End1: %lf\n", end1);
    printf("End2: %lf\n", end2);
    printf("MIC Start1: %lf\n", mic_start1);
    printf("MIC Start2: %lf\n", mic_start2);

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
