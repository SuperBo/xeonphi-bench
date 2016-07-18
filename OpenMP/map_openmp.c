#include <stdio.h>
#include "util.h"

#define ALPHA 0.2

#ifndef SIZE
#define SIZE 100000
#endif

int main(int argc, char* argv[]) {
    float *y, *x;
    
    x = (float*) _mm_malloc(SIZE * sizeof(float), 64);
    y = (float*) _mm_malloc(SIZE * sizeof(float), 64);

    int i;

    for (i = 0; i < SIZE; i++) {
        x[i] = 2 * i % 1000;
        y[i] = 3 * i % 1000;
    }

    // Start time
    double run_time = gettime();

    __assume_aligned(x, 64);
    __assume_aligned(y, 64);
    #pragma ivdep
    #pragma omp parallel for simd private(i)
    for (i = 0; i < SIZE; i++) {
        y[i] = ALPHA * x[i] + y[i];
    }

    // Stop time
    run_time = gettime() - run_time;

    // Print result
    printf("Problem size: %d\n", SIZE);
    printf("OpenMP Map Running time: %.3lfms\n", run_time * 1e3);

    // Free resources
    _mm_free(x);
    _mm_free(y);
    
    return 0;
}
