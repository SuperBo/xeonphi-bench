#include <omp.h>
#ifndef __INTEL_COMPILER
#include <mm_malloc.h>
#endif
#include "util.h"

#define WIDTH 5000
#define TILE_W 32

int main(int argc, char* argv []) {
    // Padded width
    int width = (WIDTH * sizeof(double) + 63) / 64 * 64 / sizeof(double);
    int size = width * WIDTH;
    printf("Matrix size: %d x %d \n", WIDTH, WIDTH);

    double *a, *b, *c;

    a = (double*) _mm_malloc(size * sizeof(double), 64);
    b = (double*) _mm_malloc(size * sizeof(double), 64); 
    c = (double*) _mm_malloc(size * sizeof(double), 64); 

    int i, j, k;
    int ii, jj, kk;
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

    #pragma omp parallel for collapse(2) private(i,j,k,kk)
    for (ii = 0; ii < WIDTH ; ii+=TILE_W) {
        for (jj = 0; jj < WIDTH; jj+=TILE_W) {
            int ii_end = (ii + TILE_W) < WIDTH ? ii + TILE_W : WIDTH;
            int jj_end = (jj + TILE_W) < WIDTH ? jj + TILE_W : WIDTH;

            // In each tile
            for (kk = 0; kk < WIDTH; kk+=TILE_W) {
                int kk_end = (kk + TILE_W) < WIDTH ? kk + TILE_W : WIDTH;

                for (i = ii; i < ii_end; i++) {
                    for (j = jj; j < jj_end; j++) {
                        for (k = kk; k < kk_end; k++) {
                            c[i * width + j] += a[i*width+k] + b[k*width +j];
			}
                    }
                }
            }
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
    _mm_free(a);
    _mm_free(b);
    _mm_free(c);

    return 0;
}
