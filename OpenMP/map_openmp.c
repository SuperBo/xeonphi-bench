#include <stdio.h>
#include "util.h"

#define ALPHA 0.2
#define BETA 0.4

#ifndef SIZE
#define SIZE 100000
#endif

int main(int argc, char* argv[]) {
    double a[SIZE];
    double b[SIZE];
    double c[SIZE];

    int i;

    #pragma omp parallel for private(i)
    for (i = 0; i < SIZE; i++) {
        a[i] = 2 * i % 1000;
        b[i] = 3 * i % 1000;
    }

    // Start time
    double run_time = gettime();

    #pragma omp parallel for private(i)
    for (i = 0; i < SIZE; i++) {
        c[i] = ALPHA * a[i] + BETA * b[i];
    }

    // Stop time
    run_time = gettime() - run_time;

    // Print result
    printf("Cilk Map Running time: %.4lf s", run_time);
    
    return 0;
}