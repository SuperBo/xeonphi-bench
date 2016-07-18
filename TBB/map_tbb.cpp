#include <iostream>
#include <tbb/tbb.h>
#include <tbb/task_scheduler_init.h>

#include "util.h"

#ifndef SIZE
#define SIZE 100000
#endif

#define ALPHA 0.2

using namespace tbb;

int main(int argc, char* argv[]) {
    float *x, *y;
    
    y = (float*) _mm_malloc(SIZE * sizeof(float), 64);
    x = (float*) _mm_malloc(SIZE * sizeof(float), 64);

    for (int i = 0; i < SIZE; i++) {
        x[i] = 2 * i % 1000;
        y[i] = 3 * i % 1000;
    }
    
    #ifdef NTHREADS
    task_scheduler_init init(NTHREADS);
    #else
    task_scheduler_init init(task_scheduler_init::automatic);
    #endif

    // Start time
    double run_time = gettime();

    #pragma ivdep
    parallel_for(0, SIZE, [&] (size_t i) {
        y[i] = ALPHA * x[i] + y[i];
    });
    
    // Stop time
    run_time = gettime() - run_time;

    // Print result
    std::cout << "Problem size: " << SIZE << std::endl;
    std::cout << "TBB Map running time: " << run_time * 1e3 << "ms" << std::endl;

    // Free
    _mm_free(x);
    _mm_free(y);

    return 0;
}

