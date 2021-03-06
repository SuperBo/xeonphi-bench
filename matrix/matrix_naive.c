#include <omp.h>
#ifndef __INTEL_COMPILER
#include <mm_malloc.h>
#endif
#include "util.h"

#define WIDTH 5000

int main(int argc, char* argv []) {
    // Padded width
    int width = WIDTH;
    int size = width * WIDTH;
    printf("Matrix size: %d x %d \n", WIDTH, WIDTH);

    double *a, *b, *c;

    a = (double*) malloc(size * sizeof(double));
    b = (double*) malloc(size * sizeof(double)); 
    c = (double*) malloc(size * sizeof(double)); 


    long i, j, k;
    double ttime, tstart, tstop;
    double gflops;
    int numthreads;

    // Initialize
    puts("Initializing!");

    #pragma omp parallel
    {
        #pragma omp master
        numthreads = omp_get_num_threads();

        #pragma omp for private(j)
        for (i = 0; i < WIDTH; i++) {
            for (j = 0; j < WIDTH; j++) {
                a[i * width + j] = (i % 2) ? 0.2 : 0.1;
                b[i * width + j] = (i % 2) ? 0.12 : 0.14;
            }
        }
    }

    // Start computing
    printf("Start computing on %d threads\n", numthreads);
    tstart = dtime();

    #pragma omp parallel for private(j, k)
    for (i = 0;i < WIDTH; i++) {
        for (j = 0; j < WIDTH; j++) {
            double t = 0.0;
            for (k = 0; k < WIDTH; k++) {
                t +=  a[i * width + k] * b[k * width + j];
            }
            c[i * width + j] = t;
        }
    }

    tstop = dtime();

    // Print result
    ttime = tstop - tstart;
    gflops = 1.0e-9 * WIDTH * WIDTH * (WIDTH * 2 - 1);

    if (ttime > 0.0) {
        printf("Elapsed time: %10.3lfs\n", ttime);
        printf("GFLOPS: %.3lf\n", gflops / ttime);
    }

    // Clean
    free(a);
    free(b);
    free(c);

    return 0;
}
