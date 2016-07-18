#include <iostream>
#include <cilk/cilk.h>

#include "util.h"

#define ALPHA 0.2

#ifndef SIZE
#define SIZE 100000
#endif

int main(int argc, char* argv[]) {
    float *x, *y;
    x = (float*) _mm_malloc(SIZE * sizeof(float), 64); 
    y = (float*) _mm_malloc(SIZE * sizeof(float), 64); 

    for (int i = 0; i < SIZE; i++) {
        x[i] = 2 * i % 1000;
        y[i] = 3 * i % 1000;
    }

    // Start time
    double run_time = gettime();

    y[0:SIZE] = ALPHA * x[0:SIZE] + y[0:SIZE];

    // Stop time
    run_time = gettime() - run_time;

    // Print result
    std::cout << "Problem size: " << SIZE << std::endl;
    std::cout << "Cilk Map Running time: " << run_time * 1e3 << "ms" << std::endl;

    // Free 
    _mm_free(x);
    _mm_free(y);

    return 0;
}
