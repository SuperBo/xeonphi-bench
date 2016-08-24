#include <omp.h>
#ifndef __INTEL_COMPILER
#include <mm_malloc.h>
#endif
#include "util.h"

#define WIDTH 10000
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

            // In each tile

            double as[TILE_W][TILE_W] __attribute__((aligned(64)));
            double bs[TILE_W][TILE_W] __attribute__((aligned(64)));

            for (kk = 0; kk < WIDTH; kk+=TILE_W) {
                __assume_aligned(a, 64);
                __assume_aligned(b, 64);

                // Fetch to local variables
                for (i = 0; i < TILE_W; i++){
                    for (j = 0; j < TILE_W; j++) {
                        if (ii + i >= WIDTH || j+kk >= WIDTH)
                            as[i][j] = 0.0;
                        else
                            as[i][j] = a[(ii+i)*width+j+kk];

                        if (kk+i >= WIDTH || jj+j >= WIDTH)
                            bs[i][j] = 0.0;
                        else
                            bs[i][j] = b[(kk+i)*width+jj+j];
                    }
                }

                // Calculate
                for (i = 0; i < TILE_W; i++) {
                    for (k = 0; k < TILE_W; k++) {
                        double aVal = as[i][k];
                        #pragma simd
                        #pragma prefetch c:1:16
                        #pragma prefetch bs:1:16
                    	for (j = 0; j < TILE_W; j++) {
                            if (i + ii >= WIDTH || j + jj >= WIDTH)
                                continue;
                            c[(i+ii) * width + j + jj] += aVal * bs[k][j];
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
