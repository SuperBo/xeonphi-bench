#include <stdio.h>
#include <omp.h>

#include "util.h"

#ifndef SIZE
#define SIZE 100000
#endif

int main(int argc, char** argv) {
    float* a;

    a = (float*) _mm_malloc(sizeof(float) * SIZE, 64);

    float sum = 0.;
    int i;

    #pragma omp parallel for
    for (i = 0; i < SIZE; i++) {
        a[i] = i + 2 % 1000;
    }

    double run_time = gettime();

    #pragma omp parallel for private(i) reduction(+:sum)
    for (i = 0; i < SIZE; i++) {
        sum += a[i];
    }

    run_time = gettime() - run_time;

    printf("Prolbem size: %i\n", SIZE);
    printf("Sum is %f\n", sum);
    printf("Running time: %.5lf\n", run_time);

    // Free
    _mm_free(a);

    return 0;
}
