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

    printf("Problem size: %d\n", SIZE);

    double start0 = gettime();

    #pragma omp parallel shared(time1, time2, end1, end2, start1, start2)
    {
        #pragma omp sections
        {
            #pragma omp section
            {
                start1 = gettime();
                #pragma offload target(mic:0) out(result1)
                {
                    #pragma omp parallel
                    {
                        #pragma omp master
                        result1 = fib(SIZE);
                    }
                }

                end1 = gettime();
                time1 = end1 - start1;
            }
            #pragma omp section
            {
                start2 = gettime();
                #pragma offload target(mic:0) out(result2)
                {
                    #pragma omp parallel
                    {
                        #pragma omp master
                        result2 = fib(SIZE);
                    }
                }
                end2 = gettime();
                time2 = end2 - start2;
            }
        }
    }

    double time0 = gettime() - start0;

    printf("Overal runtime %lf\n", time0);

    printf("Result 1 is %lf\n", result1);
    printf("Running time 1: %lf\n", time1);

    printf("Result 2 is %lf\n", result2);
    printf("Running time 2: %lf\n", time2);

    printf("-----------Debug info----------\n");
    printf("Start1: %lf\n", start1);
    printf("Start2: %lf\n", start2);
    printf("End1: %lf\n", end1);
    printf("End2: %lf\n", end2);

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
