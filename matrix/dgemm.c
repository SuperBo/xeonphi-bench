#include <stdio.h>
#include <mkl.h>
#include "util.h"

#define N 10000

int main() {
    double *a, *b, *c;
    int i, j;
    double alpha, beta;
    double start, stop;

    printf("Allocating memory!\n");

    a = (double*) _mm_malloc(N*N*sizeof(double), 64);
    b = (double*) _mm_malloc(N*N*sizeof(double), 64);
    c = (double*) _mm_malloc(N*N*sizeof(double), 64);

    if (a == NULL || b == NULL || c == NULL) {
        printf( "\n ERROR: Can't allocate memory for matrices. Aborting... \n\n");
        mkl_free(a);
        mkl_free(b);
        mkl_free(c);
        return 1;
    }

    printf("Initializing data!\n");
    for (i = 0; i < N*N; i++) {
        a[i] = i + 1;
        b[i] = -i - 1;
        c[i] = 0.0;
    }

    printf("Calculating %d x %d matrix!\n", N, N);
    alpha = 1.0;
    beta = 1.0;
    start = dtime();
    cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,
            N, N, N, alpha, a, N, b, N, beta, c, N);
    stop = dtime();
    printf("Completed in %lf seconds !\n", stop - start);

    _mm_free(a);
    _mm_free(b);
    _mm_free(c);

    return 0;
}
