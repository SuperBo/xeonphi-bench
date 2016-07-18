#include <iostream>
#include <cilk/cilk.h>

#include "util.h"

#define ALPHA 0.2

#ifndef SIZE
#define SIZE 100000
#endif

const int tile = 32768;

int main(int argc, char* argv[]) {
    float *x, *y;
    x = (float*) _mm_malloc(SIZE * sizeof(float), 64); 
    y = (float*) _mm_malloc(SIZE * sizeof(float), 64); 

    for (size_t i = 0; i < SIZE; i++) {
        x[i] = 2 * i % 1000;
        y[i] = 3 * i % 1000;
    }

    // Start time
    double run_time = gettime();

    cilk_for (size_t i = 0; i < SIZE; i+=tile) {
        size_t len = (SIZE - i > tile) ? tile : SIZE - i;
        y[i:len] = ALPHA * x[i:len] + y[i:len];
    }

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
